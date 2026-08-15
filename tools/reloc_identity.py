#!/usr/bin/env python3
"""reloc_identity.py — the oracle that DISAGREES with match_one about symbol identity (R34).

WHY THIS EXISTS (P31 S52). `match_one` compares a draft's compiled object against the resolved
splat `.s` with relocations MASKED (masked_diff: the whole 26-bit field for jal/j, the low 16 bits
for HI16/LO16). That masking is correct for shape — an unlinked object cannot know final addresses
— but it makes the tool STRUCTURALLY BLIND to *which* symbol each relocation names. A draft that
calls the wrong function, or loads/stores the wrong global, reports a clean MATCH every time
(cookbook §174 law 1c; wave K's `func_8002A234` had two globals swapped and cost 5 gate attempts).

Until now the only thing that caught this was the whole-binary gate — a whole rebuild, and it
reports a hash mismatch, not a cause. But the information is already on disk: the target `.s`
comment column carries the FINAL LINKED WORD, so the true address behind every masked field is
recoverable arithmetically, and `config/symbols*.txt` maps addresses back to names.

    jal/j        true target = ((word & 0x03FFFFFF) << 2) | (pc & 0xF0000000)
    HI16 + LO16  true value  = (hi_word & 0xFFFF) << 16 + sign_extend16(lo_word & 0xFFFF)

So: resolve what the DRAFT's relocation names, compute what the TARGET actually references, and
compare. Deterministic, zero tokens, no rebuild — and it names the fix ("you wrote D_80078EE8, the
target uses D_80078EE4") instead of reporting a hash.

This is the deliberate counterpart to `aprop_symfix`, which reasons about symbol NAMES between a
seed and a draft (the §171 stale-seed class). This tool reasons about ADDRESSES between a draft and
the ground-truth bytes, so it also catches a name that is perfectly plausible and simply wrong.

Usage:
  reloc_identity.py --fn F --binary B --c draft.c [--asm-subdir D] [--o0]
  reloc_identity.py --batch rows.json [-j N]      # [{"fn","binary","draft"}, ...]

Exit 0 = every relocation agrees (or nothing checkable); 1 = at least one MISMATCH.
"""
import argparse, json, os, re, subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def _addr_index(binary):
    """addr -> [names]. Built from the symbol files THIS binary's splat config stacks (corpus
    refuses to invent a fleet-wide union, and so do we)."""
    idx = {}
    for name, addr in corpus.symbols(binary).items():
        idx.setdefault(addr, []).append(name)
    return idx


ADDR_NAME = re.compile(r'^(?:func|D|jtbl|jpt|L)_([0-9A-Fa-f]{8})$')


def resolve_name(name, syms):
    """name -> address, or None.

    The symbol FILES are not the whole namespace: splat auto-generates `func_800123F0` /
    `D_800A4ED4` / `jtbl_8001C9D0` for everything it was not given a curated name for, and those
    never appear in config/symbols*.txt. Their ADDRESS IS THEIR NAME, so derive it. Missing this
    made the checker's first run report 0 relocations checked on a draft whose every callee was
    perfectly correct — a coverage hole (R32), which is exactly the failure mode that makes a
    checker look clean while checking nothing."""
    if name in syms:
        return syms[name]
    m = ADDR_NAME.match(name or "")
    return int(m.group(1), 16) if m else None


def _name_for(idx, addr):
    """Exact name, else a nearby symbol + offset, else the splat-derived name.

    The window is deliberately TIGHT (0x200). An earlier 0x4000 window printed
    `SsGetMute+0xC50` for an address that is simply `func_8001C9D0` — a wrong label is worse than
    no label, because the reader acts on it."""
    if addr in idx:
        return "/".join(sorted(idx[addr]))
    below = [a for a in idx if a <= addr and addr - a <= 0x200]
    if below:
        a = max(below)
        return "%s+0x%X" % ("/".join(sorted(idx[a])), addr - a)
    return "func_%08X (splat-derived)" % addr if 0x80000000 <= addr < 0x80800000 else None


def _split_op(op):
    """objdump reloc operand -> (symbol, addend). Forms: `sym`, `sym+0x10`, `sym-0x4`."""
    if op is None:
        return None, 0
    for sep, sign in (("+", 1), ("-", -1)):
        if sep in op:
            s, _, t = op.partition(sep)
            try:
                return s.strip(), sign * int(t.strip(), 0)
            except ValueError:
                return op.strip(), 0
    return op.strip(), 0


def check(fn, binary, draft, asm_subdir=None, o0=False):
    """Returns a verdict dict. 'mismatches' is the actionable part."""
    stubs = {s.symbol: s for s in corpus.stubs(binary).values()}
    st = stubs.get(fn)
    if not st:
        return {"fn": fn, "binary": binary, "status": "NOT-A-STUB",
                "note": "already banked or unknown — nothing to check"}
    sub = asm_subdir or st.asm_dir
    syms = corpus.symbols(binary)
    idx = _addr_index(binary)

    with tempfile.TemporaryDirectory(dir=os.path.join(REPO, ".run")) as td:
        streams = os.path.join(td, "s.json")
        cmd = [".venv/bin/python", "tools/match_one.py", fn, "--c", draft,
               "--asm-subdir", sub, "--emit-streams", streams]
        if o0 or st.region == "boot":
            cmd.append("--o0")
        r = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO)
        out = r.stdout + r.stderr
        if not os.path.exists(streams):
            return {"fn": fn, "binary": binary, "status": "COMPILE-FAIL",
                    "note": out.strip().splitlines()[-1][:200] if out.strip() else "no output"}
        d = json.load(open(streams))

    mine, tgt = d["mine"], d["tgt"]
    relocs = {int(k): v for k, v in d.get("mine_relocs", {}).items()}
    base = st.addr
    shape = "MATCH" if ("MATCH" in out and "NOMATCH" not in out) else "DIFF"

    mismatches, unresolved, checked = [], [], 0

    # ---- jal / j: the whole 26-bit field is masked, so the callee identity is never compared.
    for i, rl in sorted(relocs.items()):
        if rl["kind"] != "26" or i >= len(tgt):
            continue
        sym, addend = _split_op(rl["op"])
        pc = base + 4 * i
        true_addr = ((tgt[i] & 0x03FFFFFF) << 2) | (pc & 0xF0000000)
        want_base = resolve_name(sym, syms)
        if want_base is None:
            unresolved.append({"i": i, "kind": "jal", "symbol": sym,
                               "target_addr": "0x%08X" % true_addr,
                               "target_name": _name_for(idx, true_addr)})
            continue
        checked += 1
        want = want_base + addend
        if want != true_addr:
            mismatches.append({"i": i, "kind": "jal", "draft_symbol": sym,
                               "draft_addr": "0x%08X" % want,
                               "target_addr": "0x%08X" % true_addr,
                               "target_name": _name_for(idx, true_addr)})

    # ---- HI16/LO16: pair each HI16 with the next LO16 naming the same symbol (the gcc pattern).
    his = [i for i, rl in relocs.items() if rl["kind"] == "HI16"]
    los = [i for i, rl in relocs.items() if rl["kind"] == "LO16"]
    used = set()
    for i in sorted(his):
        sym_i, add_i = _split_op(relocs[i]["op"])
        j = next((k for k in sorted(los)
                  if k > i and k not in used and _split_op(relocs[k]["op"])[0] == sym_i), None)
        if j is None or i >= len(tgt) or j >= len(tgt):
            continue
        used.add(j)
        true_val = ((tgt[i] & 0xFFFF) << 16) + sext16(tgt[j] & 0xFFFF)
        true_val &= 0xFFFFFFFF
        hi_base = resolve_name(sym_i, syms)
        if hi_base is None:
            unresolved.append({"i": i, "kind": "hi/lo", "symbol": sym_i,
                               "target_addr": "0x%08X" % true_val,
                               "target_name": _name_for(idx, true_val)})
            continue
        checked += 1
        # MIPS o32 uses REL relocations: THE ADDEND LIVES IN THE INSTRUCTION, not in the reloc
        # entry, so objdump prints a bare `D_801F9DAC` for what is really `D_801F9DAC+1`. Reading
        # the addend off the operand string therefore reports 0 for every struct-field and array
        # access and manufactures a mismatch. Recover it the way the linker does: from my own
        # object's hi/lo immediate fields. (Caught by the +1/+2/+3 signature on func_801F0734 --
        # a byte-array walk that the first version called three symbol errors.)
        addend = ((mine[i] & 0xFFFF) << 16) + sext16(mine[j] & 0xFFFF)
        want = (hi_base + addend) & 0xFFFFFFFF
        if want != true_val:
            mismatches.append({"i": i, "kind": "hi/lo", "draft_symbol": sym_i,
                               "draft_addr": "0x%08X" % want,
                               "target_addr": "0x%08X" % true_val,
                               "target_name": _name_for(idx, true_val)})

    # INDEX ALIGNMENT IS THE PRECONDITION. Instruction i of my object corresponds to instruction i
    # of the target ONLY when the streams are the same shape — which is exactly the case this tool
    # is built for (a match_one MATCH that the gate rejected). When the shapes differ, a single
    # inserted instruction shifts every later index and manufactures phantom mismatches: my own
    # NC-C mutant produced one (a callee "wrong" purely because the stream had shifted under it).
    # So say so, rather than emitting confident nonsense (R35: an instrument must know when it
    # cannot answer).
    aligned = (shape == "MATCH") and len(mine) == len(tgt)
    status = ("MISMATCH" if mismatches else
              ("UNRESOLVED" if unresolved and not checked else "AGREE"))
    if not aligned and mismatches:
        status = "MISMATCH?"
    return {"fn": fn, "binary": binary, "shape": shape, "checked": checked, "aligned": aligned,
            "status": status, "mismatches": mismatches, "unresolved": unresolved,
            "caveat": None if aligned else
                      "streams are not index-aligned (shape differs) — verdicts are ADVISORY; "
                      "fix the shape first, then re-check"}


def _fmt(v):
    head = f"{v['status']:11s} {v['fn']:18s} [{v['binary']}]"
    if v["status"] in ("NOT-A-STUB", "COMPILE-FAIL"):
        return head + "  " + v.get("note", "")
    head += f"  shape={v.get('shape')} relocs_checked={v.get('checked')}"
    if v.get("caveat"):
        head += f"\n    (advisory: {v['caveat']})"
    for m in v.get("mismatches", []):
        head += (f"\n    ‼ i={m['i']:<4d} {m['kind']:6s} draft names {m['draft_symbol']} "
                 f"({m['draft_addr']}) but the target references {m['target_addr']}"
                 f"{' = ' + m['target_name'] if m['target_name'] else ''}")
    for u in v.get("unresolved", [])[:4]:
        head += (f"\n    ? i={u['i']:<4d} {u['kind']:6s} {u['symbol']} is not in this binary's "
                 f"symbol files; target references {u['target_addr']}"
                 f"{' = ' + u['target_name'] if u['target_name'] else ''}")
    return head


def propose_fix(v, draft_path, binary):
    """Mechanical repair for a MISMATCH: rename the draft's wrong symbol to the one the TARGET
    actually references. Only when the evidence is unambiguous.

    For a relocation naming symbol S with in-instruction addend A against target value T, the
    corrected base is T - A. A rename is proposed only if EVERY mismatch naming S implies the SAME
    corrected base -- i.e. the draft is consistently pointed at one wrong symbol (the §171
    stale-seed-symbol shape, where all of a draft's per-location symbols are off by one delta).
    If the implied bases disagree, the draft is wrong in more than one way and a rename would be a
    guess: refuse and say so (R39 -- a fixer that guesses is worse than one that declines)."""
    if not v.get("aligned") or v["status"] != "MISMATCH":
        return {"fn": v["fn"], "action": "skip", "why": "not an aligned MISMATCH"}
    syms = corpus.symbols(binary)
    idx = _addr_index(binary)
    implied = {}
    for m in v["mismatches"]:
        s = m["draft_symbol"]
        d, t = int(m["draft_addr"], 16), int(m["target_addr"], 16)
        base = resolve_name(s, syms)
        if base is None:
            return {"fn": v["fn"], "action": "refuse", "why": f"cannot resolve {s}"}
        implied.setdefault(s, set()).add((t - (d - base)) & 0xFFFFFFFF)
    renames = {}
    for s, bases in implied.items():
        if len(bases) != 1:
            # SYMBOL COLLAPSE: the draft used ONE extern where the target references N distinct
            # globals. A textual rename cannot fix it (every occurrence would move together) --
            # the draft needs N separate externs, one per site. Name the class and the sites so
            # the repair is mechanical for whoever picks it up.
            sites = [f"i={m['i']}->{m['target_addr']}" for m in v["mismatches"]
                     if m["draft_symbol"] == s]
            return {"fn": v["fn"], "action": "refuse", "klass": "SYMBOL-COLLAPSE",
                    "why": f"{s} stands in for {len(bases)} DISTINCT globals "
                           f"({', '.join('0x%08X' % b for b in sorted(bases))}) at {', '.join(sites)}"
                           f" — split it into one extern per site; a rename moves all of them"}
        b = bases.pop()
        exact = [n for n, a in syms.items() if a == b]
        renames[s] = (sorted(exact)[0] if exact
                      else ("func_%08X" if s.startswith("func_") else "D_%08X") % b)
    text = open(draft_path).read()
    new = text
    for old, nw in renames.items():
        new = re.sub(r'\b%s\b' % re.escape(old), nw, new)
    if new == text:
        return {"fn": v["fn"], "action": "refuse", "why": "no textual occurrence to rewrite"}
    return {"fn": v["fn"], "action": "rename", "renames": renames, "text": new,
            "path": draft_path}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fn")
    ap.add_argument("--binary")
    ap.add_argument("--c", dest="draft")
    ap.add_argument("--asm-subdir")
    ap.add_argument("--o0", action="store_true")
    ap.add_argument("--batch", help='JSON list of {"fn","binary","draft"}')
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--out", help="write all verdicts here as JSON")
    ap.add_argument("--fix", action="store_true",
                    help="rewrite each unambiguously-wrong symbol to the one the TARGET "
                         "references (refuses whenever the evidence is not unambiguous)")
    ap.add_argument("--dry-fix", action="store_true", help="show what --fix would do, change nothing")
    a = ap.parse_args()

    if a.batch:
        rows = json.load(open(a.batch))
        with ThreadPoolExecutor(max_workers=a.j) as ex:
            verdicts = list(ex.map(
                lambda r: check(r["fn"], r["binary"], r["draft"],
                                r.get("asm_subdir"), r.get("o0", False)), rows))
    else:
        if not (a.fn and a.binary and a.draft):
            ap.error("need --fn/--binary/--c, or --batch")
        verdicts = [check(a.fn, a.binary, a.draft, a.asm_subdir, a.o0)]

    for v in verdicts:
        print(_fmt(v), flush=True)

    if a.fix or a.dry_fix:
        rowmap = {}
        if a.batch:
            rowmap = {r["fn"]: r for r in json.load(open(a.batch))}
        elif a.fn:
            rowmap = {a.fn: {"fn": a.fn, "binary": a.binary, "draft": a.draft}}
        print("\n--- %s ---" % ("FIX" if a.fix else "DRY-FIX"), flush=True)
        for v in verdicts:
            if v["status"] != "MISMATCH":
                continue
            row = rowmap.get(v["fn"])
            if not row:
                continue
            pr = propose_fix(v, row["draft"], v["binary"])
            if pr["action"] == "rename":
                pairs = ", ".join(f"{o} -> {n}" for o, n in pr["renames"].items())
                if a.fix:
                    open(pr["path"], "w").write(pr["text"])
                print(f"  {'RENAMED' if a.fix else 'would rename'} {v['fn']}: {pairs}", flush=True)
            elif pr["action"] == "refuse":
                print(f"  REFUSED {v['fn']}: {pr['why']}", flush=True)
    if a.out:
        json.dump(verdicts, open(a.out, "w"), indent=1)

    n = {}
    for v in verdicts:
        n[v["status"]] = n.get(v["status"], 0) + 1
    if len(verdicts) > 1:
        print("\n" + "  ".join(f"{k}={c}" for k, c in sorted(n.items())), flush=True)
    sys.exit(1 if (n.get("MISMATCH") or n.get("MISMATCH?")) else 0)


if __name__ == "__main__":
    main()
