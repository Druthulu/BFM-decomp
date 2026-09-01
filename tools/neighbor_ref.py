#!/usr/bin/env python3
"""neighbor_ref.py — for an OPEN stub, the already-MATCHED functions worth reading as WORKED
EXAMPLES, ranked. (P31 S68)

WHY, WITH THE MEASUREMENT. `seed_ref` finds a BYTE-IDENTICAL twin by signature hash — when one
exists the body is free. This answers the weaker but far more common question: *"which matched
function should I READ before drafting this one?"*

S68 measured a ~20x swing on exactly that variable. Every one of the cheapest large matches came
from an agent finding a matched neighbour; the expensive ones had none:

    func_800D1254   555 ins    72k tokens   an -O0 SIBLING in the same binary
    func_800D12D0   657 ins   122k tokens   the -O0 sibling banked minutes earlier, FIRST COMPILE
    func_8018AD9C   397 ins    87k tokens   a banked twin, §193-A one-shot
    func_80189240   551 ins   156k tokens   pure symbol remap of a banked twin, first try
    func_8017BEBC   753 ins   177k tokens   a near-twin IN THE SAME FILE
    ---------------------------------------------------------------------------
    main fns with no neighbour   ~80 ins   200-350k tokens each

**And the failure that motivated this file: `func_8017BEBC`'s card asserted "no banked twin" while a
MATCHED 755-instruction near-twin sat 3,700 lines up IN ITS OWN DESTINATION FILE**, its header
comment documenting the four levers the target needed. `seed_ref` could not see it because it joins
on signature hashes and the two bodies are not hash-identical. Three other S68 agents found their
unlock the same way, unprompted, by reading around the destination TU.

WHAT IT RANKS ON, in priority order — derived from what actually worked, not from intuition:
 1. **SAME TU.** The strongest signal by a distance. A matched function in the destination file was
    solved against the SAME decl environment, the same neighbours' types, the same carve — and its
    header comment usually records the levers. Every S68 same-TU unlock was cheap.
 2. **Same binary.** Same overlay/module: shared globals, shared engine idioms.
 3. **Shape similarity** from `.run/feat.<bin>.jsonl` (already computed for all 213 binaries, 21 s
    fleet-wide): the li-normalised skeleton `h_seqn`, the call-sequence hash, the reloc-kind
    sequence, the CFG counts and the 16-bucket opcode histogram.
 4. **Instruction-count proximity.** A 750-instruction target learns little from a 20-instruction
    example.
 5. **-O0 agreement.** An -O0 target must read an -O0 example; opt level is a property of the FILE
    (§116) and an -O2 example actively misleads.

WHAT THIS IS NOT. It does NOT claim the neighbour's body can be remapped — §168 law 1 measured that
at 0/26 ("a cousin is a seeded crack, never a remap"). A neighbour is a WORKED EXAMPLE to read, not
an answer to copy. `seed_ref` remains the tool for the byte-identical case.

    tools/neighbor_ref.py --binary ov_SC06_010 --fn func_8017BEBC
    tools/neighbor_ref.py --binary main --fn func_80024054 --json --top 5
"""
import argparse
import json
import math
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus            # noqa: E402
import overlay_src_split as oss   # noqa: E402


def _addr(v):
    """int address from either an int or a "0x..." string; None if unusable."""
    if isinstance(v, int):
        return v
    try:
        return int(v, 16) if str(v).lower().startswith("0x") else int(v)
    except (TypeError, ValueError):
        return None


def _feats(binary):
    """{addr: featrow} from the precomputed atlas features; {} if absent."""
    p = os.path.join(REPO, ".run/feat.%s.jsonl" % binary)
    out = {}
    try:
        with open(p) as fh:
            for ln in fh:
                ln = ln.strip()
                if not ln:
                    continue
                try:
                    r = json.loads(ln)
                except ValueError:
                    continue
                # ADDRESSES ARE HEX STRINGS HERE AND INTS ELSEWHERE. The atlas writes
                # "0x80128158"; corpus.Stub.addr is an int. This project has already been bitten by
                # exactly this once (T4's verifier compared ZERO rows because of a string-vs-int
                # addr mismatch — the R32 silent-no-op class). Normalise both ways, loudly.
                a = _addr(r.get("addr"))
                if a is not None:
                    out[a] = r
    except OSError:
        pass
    return out


def _ophist_cos(a, b):
    """cosine over the 16-bucket opcode histogram; 0.0 when either is missing."""
    if not a or not b or len(a) != len(b):
        return 0.0
    na = math.sqrt(sum(x * x for x in a)) or 1.0
    nb = math.sqrt(sum(x * x for x in b)) or 1.0
    return sum(x * y for x, y in zip(a, b)) / (na * nb)


def _same_tu_matched(binary, tu_path):
    """{addr: name} of functions MATCHED in this TU — the strongest signal (see docstring)."""
    out = {}
    try:
        syms = oss.load_ov_syms(binary) if hasattr(oss, "load_ov_syms") else {}
    except Exception:
        syms = {}
    try:
        _, items = oss.parse_overlay_c(open(os.path.join(REPO, tu_path)).read(), syms)
    except Exception:
        return out
    for addr, name, kind, _ in items:
        if kind in ("def", "define", "nonmatch") and name and addr is not None:
            out[addr] = name
    return out


def _header_comment(tu_path, name):
    """The comment block immediately above a definition — where the LEVERS are written down.

    This is the payload an agent actually consumes. S68's func_8017BEBC was unlocked by a
    neighbour's header listing four levers, all reused verbatim.
    """
    try:
        lines = open(os.path.join(REPO, tu_path), errors="replace").read().splitlines()
    except OSError:
        return ""
    pat = re.compile(r"\b%s\b" % re.escape(name))
    for i, ln in enumerate(lines):
        if pat.search(ln) and ("(" in ln or "DEFINE_" in ln):
            j, block = i - 1, []
            while j >= 0 and (lines[j].lstrip().startswith(("*", "/*", "//")) or not lines[j].strip()):
                if lines[j].strip():
                    block.append(lines[j].rstrip())
                j -= 1
                if len(block) > 40:
                    break
            return "\n".join(reversed(block))
    return ""


def neighbors(binary, fn, top=5):
    stubs = corpus.stubs(binary)
    st = next((s for s in stubs.values() if s.symbol == fn), None)
    if st is None:
        return {"error": "no open stub %s:%s" % (binary, fn)}
    sp = os.path.join(st.asm_dir, fn + ".s")
    nins = corpus.s_ins_count(sp) if os.path.exists(sp) else 0
    from o0_detect import detect_o0
    o0 = detect_o0(sp) if os.path.exists(sp) else False

    feats = _feats(binary)
    me = feats.get(st.addr, {})
    same_tu = _same_tu_matched(binary, st.path)
    matched = corpus.matched(binary)

    cands = []
    for addr, row in matched.items():
        f = feats.get(addr, {})
        n2 = f.get("nins") or row.get("nins") or 0
        if not n2:
            continue
        score = 0.0
        why = []
        if addr in same_tu:
            score += 100.0
            why.append("SAME TU")
        else:
            score += 20.0
            why.append("same binary")
        if o0 == bool(f.get("o0")):
            score += 15.0
            if o0:
                why.append("-O0 like the target")
        else:
            score -= 40.0
            why.append("OPT-LEVEL MISMATCH — misleading (§116)")
        if me:
            if f.get("h_seqn") and f["h_seqn"] == me.get("h_seqn"):
                score += 60.0; why.append("identical li-normalised skeleton")
            if f.get("res_calls_h") and f["res_calls_h"] == me.get("res_calls_h"):
                score += 30.0; why.append("same call sequence")
            if f.get("rk_seq_h") and f["rk_seq_h"] == me.get("rk_seq_h"):
                score += 25.0; why.append("same relocation-kind sequence")
            c = _ophist_cos(f.get("ophist"), me.get("ophist"))
            if c > 0.9:
                score += 20.0 * c; why.append("opcode mix %.2f" % c)
            for k, w, lbl in (("nblk", 8, "CFG blocks"), ("ncond", 8, "branches"),
                              ("nback", 6, "loops")):
                if f.get(k) is not None and me.get(k) is not None and f[k] == me[k]:
                    score += w; why.append("same %s" % lbl)
        ratio = min(nins, n2) / max(nins, n2, 1)
        score += 25.0 * ratio
        if ratio < 0.25:
            why.append("size far off (%d vs %d)" % (n2, nins))
        cands.append((score, addr, row.get("name") or same_tu.get(addr) or "func_%08X" % addr,
                      n2, same_tu.get(addr) is not None, why))

    cands.sort(key=lambda t: -t[0])
    out = {"binary": binary, "fn": fn, "nins": nins, "o0": o0, "tu": st.path,
           "matched_in_tu": len(same_tu), "matched_in_binary": len(matched), "neighbors": []}
    for score, addr, name, n2, in_tu, why in cands[:top]:
        out["neighbors"].append({
            "name": name, "addr": "0x%08x" % addr, "nins": n2, "same_tu": in_tu,
            "score": round(score, 1), "why": why,
            "header": _header_comment(st.path, name)[:1200] if in_tu else "",
        })
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary", required=True); ap.add_argument("--fn", required=True)
    ap.add_argument("--top", type=int, default=5); ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    r = neighbors(a.binary, a.fn, a.top)
    if a.json:
        print(json.dumps(r, indent=1)); return 0
    if r.get("error"):
        print("ERROR:", r["error"]); return 1
    print("%s:%s  %d ins%s\n  TU %s — %d matched functions in it, %d in the binary"
          % (r["binary"], r["fn"], r["nins"], "  [-O0 TARGET]" if r["o0"] else "",
             r["tu"], r["matched_in_tu"], r["matched_in_binary"]))
    if not r["neighbors"]:
        print("  no matched neighbours — this really is a cold start")
    for n in r["neighbors"]:
        print("\n  %-18s %s  %4d ins  score %-6s %s"
              % (n["name"], n["addr"], n["nins"], n["score"],
                 "<< SAME TU" if n["same_tu"] else ""))
        print("     why: %s" % "; ".join(n["why"]))
        if n["header"]:
            first = [l for l in n["header"].splitlines() if l.strip("/* \t")][:4]
            print("     its header records:")
            for l in first:
                print("       %s" % l.strip()[:110])
    return 0


if __name__ == "__main__":
    sys.exit(main())
