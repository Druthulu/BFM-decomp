#!/usr/bin/env python3
"""diff_regions.py — classify WHERE a family-remapped member's compiled bytes diverge from its target.

The T3b swing-number probe (Phase-29 Task 1) + the P29–P31 agent-iteration aid (the roadmap's
deferred P28 tool). Given a MATCHED exemplar and a same-family stub MEMBER, remap the exemplar C to
the member (`family_remap.remap_hseq` — EXACTLY what `family_sweep --hseq` stages), compile it at the
EXEMPLAR's real optimization level (a per-location member's target was compiled at the same level as
its exemplar — same engine function, same per-file opt), and diff the compiled object against the
member target (`match_one`'s pinned triple + `masked_diff`'s masking oracle), classifying each member:

  * O0-FLAG   — the draft masked-MATCHes at -O0 but not -O2 (or the auto level differs from -O2):
                a COMPILE-FLAG artifact, NOT a codegen wall. Fix = an -O0 split file (the
                `ov_SC01_077_o0` / whale `_o0b` precedent + the Makefile -O0 rule). This is the class
                that made the Phase-28 T3b "~3%" (`family_sweep` compiled -O0 members at -O2).
  * MASKED-MATCH — masked-MATCH at the exemplar's real opt level: the codegen is reproduced. Any
                remaining whole-binary failure can only be a RESOLVED-RELOC (symbol) issue (case a,
                a `family_remap.symbol_map` gap) — confirm on the whole-binary gate.
  * REGALLOC  — masked-DIFF at the correct opt level with mismatches in opcode/register bits away
                from reloc slots: genuine TU-context codegen drift (a real per-member wall — §52 work).
  * LEN       — instruction-count delta (structural / wrong body).
  * REMAP-REFUSED — `remap_hseq` refuses (STRUCT / unresolved-immediate / symbol-map): not this
                tool's class (family_remap's own pre-filter).

The whole-binary byte-gate stays the SOLE arbiter (G3/P9): this classifies a CANDIDATE's residual to
ROUTE the fix; it never banks. `match_one` is masked/isolated — a MASKED-MATCH is a candidate, not a
bank (§52b). Reuses masked_diff + match_one + family_remap (composed, not re-implemented — R33).

  tools/diff_regions.py --family 0x8013c964 [--exemplar-ov ov_SC01_077] [--members 8] [--opt both]
  tools/diff_regions.py --addr 0x8013c964 --member-ov ov_SC01_000 [--member-addr 0x8013c964]
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import family_remap as FR
import masked_diff

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
WORKROOT = ".run/diff_regions"

_O0_SET = None


def o0_srcfiles():
    """The set of src/*.c files the build compiles at -O0, DERIVED from the Makefile's own
    `-O0` object rules (R33 — never a hand-kept list, which rots as splits are added). Two shapes:
    explicit `build/src/X.o: CC1FLAGS := … -O0 …` targets, and a wildcard over `src/ov_*/ov_*_o0b.c`
    (the whale rollout). Returns (explicit_paths:set, matches_o0b:callable)."""
    global _O0_SET
    if _O0_SET is None:
        mk = open(os.path.join(REPO, "Makefile")).read()
        explicit = set()
        for m in re.finditer(r"^build/(src/\S+?\.o):\s*CC1FLAGS\s*:=[^\n]*-O0\b", mk, re.M):
            explicit.add(m.group(1)[:-2] + ".c")            # build/src/X.o -> src/X.c
        o0b = bool(re.search(r"WHALE_O0B_OBJS\s*:=.*ov_\*_o0b\.c", mk))
        _O0_SET = (explicit, o0b)
    return _O0_SET


def is_o0(src_rel):
    """True iff the build compiles this src/*.c at -O0 (per the Makefile)."""
    if not src_rel:
        return False
    explicit, o0b = o0_srcfiles()
    base = src_rel.replace("\\", "/")
    if base in explicit:
        return True
    return o0b and re.search(r"/ov_[^/]*_o0b\.c$", "/" + base) is not None


def exemplar_srcfile(ex_ov, addr):
    """the src file where the exemplar's def lives (via extract_unit's own resolution). Returns the
    .c path (or a src/shared/*.h for a macro-lifted body). Used only to detect the -O0 opt level."""
    _unit, cf = FR.extract_unit(ex_ov, addr)
    return cf


def member_subdir(mem_ov, addr):
    """the asm subdir holding this member's target .s (globbed). None if the member has no .s."""
    hits = glob.glob(os.path.join(REPO, f"asm/{mem_ov}/nonmatchings/*/func_{addr:08X}.s"))
    if not hits:
        return None
    # asm/<ov>/nonmatchings/<subdir>/func_X.s  ->  asm/<ov>/nonmatchings/<subdir>
    return os.path.dirname(os.path.relpath(hits[0], REPO))


def _run_match_one(fn, cfile, subdir, o0, wd):
    """compile the draft standalone (match_one's pinned triple) at the given opt, masked-compare to the
    target .s. Returns (status, ndiff, nmine, ntgt, reason). status in {MATCH, DIFF, FAIL}. On FAIL,
    `reason` is the first cc1/cpp error line (to distinguish an ISOLATION plumbing fail — an undeclared
    shared type the real TU carries — from a hard fail; this tool compiles ISOLATED so it cannot see
    src/shared/engine_types.h, exactly the blind spot family_sweep --no-preclassify + the real-TU gate
    resolve)."""
    cmd = [PY, "tools/match_one.py", fn, "--c", cfile, "--asm-subdir", subdir, "--work", wd]
    if o0:
        cmd.append("--o0")
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO)
    out = r.stdout.strip()
    m = re.search(r"MATCH \((\d+) ins\)", out)
    if m:
        return "MATCH", 0, int(m.group(1)), int(m.group(1)), ""
    m = re.search(r"DIFF\s+\S+\s+mine=(\d+) ins, target=(\d+) ins, (\d+) mismatched", out)
    if m:
        return "DIFF", int(m.group(3)), int(m.group(1)), int(m.group(2)), ""
    # CPP/CC1/AS fail — surface the first real error line (skip the "FAIL\n<stage> FAIL" header)
    err = next((ln for ln in out.splitlines() if re.search(r"error|undeclared|parse", ln)), out[:120])
    return "FAIL", -1, 0, 0, err


def probe_member(ex_ov, ex_addr, mem_ov, mem_addr, opt_mode="both"):
    """Remap the exemplar to the member and classify. opt_mode: 'auto' (exemplar's level only),
    'both' (compile -O0 AND -O2 to detect the O0-FLAG class). Returns a result dict."""
    fn = f"func_{mem_addr:08X}"
    draft, info = FR.remap_hseq(ex_addr, ex_ov, mem_ov, mem_addr)
    if draft is None:
        return {"member": f"{mem_ov}@{mem_addr:08X}", "class": "REMAP-REFUSED", "why": info}
    subdir = member_subdir(mem_ov, mem_addr)
    if subdir is None:
        return {"member": f"{mem_ov}@{mem_addr:08X}", "class": "NO-TARGET",
                "why": "no target .s (member already matched?)"}
    wd_base = os.path.join(WORKROOT, f"{mem_ov}_{mem_addr:08X}")
    cfile = os.path.join(REPO, wd_base + ".c")
    os.makedirs(os.path.dirname(cfile), exist_ok=True)
    open(cfile, "w").write(draft + "\n")

    ex_o0 = is_o0(exemplar_srcfile(ex_ov, ex_addr))
    res = {"member": f"{mem_ov}@{mem_addr:08X}", "exemplar_opt": "O0" if ex_o0 else "O2",
           "symbol_map": info.get("symbol_map"), "subdir": subdir}

    levels = {}
    want = [ex_o0] if opt_mode == "auto" else [True, False]   # both: -O0 and -O2
    for o0 in want:
        st, nd, nmine, ntgt, why = _run_match_one(fn, cfile, subdir, o0, wd_base + ("_o0" if o0 else "_o2"))
        levels["O0" if o0 else "O2"] = {"status": st, "ndiff": nd, "mine": nmine, "tgt": ntgt, "why": why}
    res["levels"] = levels

    auto = levels["O0" if ex_o0 else "O2"]
    other = levels.get("O2" if ex_o0 else "O0")
    if auto["status"] == "MATCH":
        # matches at the exemplar's real opt. If it needs the OTHER (wrong-for-the-sweep) opt, the whole
        # class was the -O0 compile-flag artifact (the sweep stages into the member's -O2 stub file).
        res["class"] = ("O0-FLAG" if ex_o0 else "TEMPLATES") if (other and other["status"] != "MATCH") \
            else "TEMPLATES"
    elif auto["status"] == "FAIL":
        # This tool compiles ISOLATED, so an undeclared shared type / carried-extern parse error is a
        # match_one blind spot the real TU (which #includes engine_types.h) does not have — a recoverable
        # §40a/§8d plumbing class, NOT a codegen wall. Label it so, honestly (R35).
        w = auto.get("why", "")
        res["why"] = w
        res["class"] = "PLUMBING-ISO" if re.search(r"undeclared|parse error before", w) else "COMPILE-FAIL"
    elif auto["mine"] != auto["tgt"]:
        res["class"] = "LEN"
    else:
        res["class"] = "REGALLOC"                            # masked-diff, non-reloc bits differ = a real wall
    return res


def load_family(addr, exemplar_ov=None):
    """the family_hseq record for exemplar addr (optionally pinned to an overlay). Returns the dict."""
    d = json.load(open(os.path.join(REPO, ".run/family_hseq.json")))
    fams = d if isinstance(d, list) else d.get("families", d)
    for f in fams:
        ex = f.get("exemplar", {})
        if int(ex.get("addr", "0x0"), 16) == addr and (exemplar_ov is None or ex.get("ov") == exemplar_ov):
            return f
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--family", help="exemplar addr (hex) — pull members from .run/family_hseq.json")
    ap.add_argument("--exemplar-ov", default=None)
    ap.add_argument("--members", type=int, default=8, help="how many stub members to probe (--family)")
    ap.add_argument("--addr", help="exemplar addr (hex) for a single explicit --member-ov probe")
    ap.add_argument("--member-ov")
    ap.add_argument("--member-addr", default=None)
    ap.add_argument("--opt", choices=["auto", "both"], default="both")
    ap.add_argument("--json", action="store_true", help="emit the raw result list as JSON")
    a = ap.parse_args()
    os.chdir(REPO)

    results = []
    if a.addr and a.member_ov:
        ex_addr = int(a.addr, 16)
        mem_addr = int(a.member_addr, 16) if a.member_addr else ex_addr
        ex_ov = a.exemplar_ov or "ov_SC01_077"
        results.append(probe_member(ex_ov, ex_addr, a.member_ov, mem_addr, a.opt))
    elif a.family:
        ex_addr = int(a.family, 16)
        fam = load_family(ex_addr, a.exemplar_ov)
        if not fam:
            print(f"no family_hseq record for {a.family}"); sys.exit(2)
        ex_ov = fam["exemplar"]["ov"]
        print(f"family func_{ex_addr:08X} @ {ex_ov}: nins={fam.get('nins')} band={fam.get('band')} "
              f"diff_class={fam.get('diff_class')} has_mid_jr={fam.get('has_mid_jr')} "
              f"n_members={fam.get('n_members')}  exemplar_opt="
              f"{'O0' if is_o0(exemplar_srcfile(ex_ov, ex_addr)) else 'O2'}")
        n = 0
        for mov, addr_s in fam["members"]:
            if n >= a.members:
                break
            maddr = int(addr_s, 16)
            if (mov, maddr) == (ex_ov, ex_addr):
                continue
            r = probe_member(ex_ov, ex_addr, mov, maddr, a.opt)
            results.append(r)
            print(f"  {r['member']:24s} {r['class']:14s} "
                  + " ".join(f"{k}:{v['status']}({v['ndiff']})" for k, v in r.get("levels", {}).items())
                  + (f"  [{r.get('why','')}]" if r["class"] in ("REMAP-REFUSED", "NO-TARGET") else ""))
            n += 1
    else:
        ap.error("give --family 0xADDR or --addr 0xADDR --member-ov ov_X")

    from collections import Counter
    dist = Counter(r["class"] for r in results)
    print(f"\nDISTRIBUTION ({len(results)} members): {dict(dist)}")
    if a.json:
        print(json.dumps(results, indent=2))


if __name__ == "__main__":
    main()
