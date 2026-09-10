#!/usr/bin/env python3
"""delever_pack.py — the pack one T7 agent gets for one residue exemplar (Phase 36 S101; one agent at a time, Drew 2026-09-09).

    tools/delever_pack.py --build [--min-copies 100] [--limit N] [--only X ...]   # .run/P36/agents/<alias>__<fn>/ + ORDER.tsv
    tools/delever_pack.py --list

Everything in a pack is derived WITHOUT writing the tree (`delever_search --try` compiles a scratch copy), so packs can be built
while a run is going. Per exemplar:
  tu.txt          the translation unit path and the function name
  body_tree.c     the function as the tree has it (markers and all)
  body_free.c     the function with every class A/B lever rewritten away — the search's seed and the agent's starting text
  residual.txt    `--try` on the seed: score, class, the register pairs, every differing block as mnemonics (mine | target)
  sites.txt       the ledger's sites with their verdicts (NEEDED with the register each pin names)
  history.txt     every engine attempt on this class (label, start, best, compiles, path) and the best-scoring moves of the last trace
  neighbours.txt  the target's own header in full, its TU neighbours' headers, every @class/@stuck/@crack note (S102)
  best_body.c     the engine's best candidate TEXT (S102)
  related.txt     lever-free bodies anywhere in the overlay sharing a callee/global with the target, ranked (S103)
ORDER.tsv ranks the exemplars: best distance reached so far ascending, then copies descending — the cheapest readings first.
"""
import argparse
import re
import collections
import json
import os
import pathlib
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import delever as dl                # noqa: E402
import delever_search as ds         # noqa: E402

PACKS = REPO / ".run" / "P36" / "agents"
PY = str(REPO / ".venv" / "bin" / "python")


SYM = re.compile(r"\b(?:func|D)_[0-9A-Fa-f]{8}\b")


def related_bodies(tu, fn, target_text, alias, top=6, max_lines=600):
    """related.txt — LEVER-FREE bodies anywhere in the same overlay that share a callee or a global with the target.

    Three T7 agents in S103 found their answer in a lever-free function the pack never showed them: c2 in a sibling
    walking the same `D_801EDABC` list (the shape and the struct type), c4 in a sibling spelled lever-free under a stale
    `@stuck:` note, and c10 in a DIFFERENT FILE (`func_80135888`: the same switch, list walk and parameter pass-through,
    which the residual cannot show because jump2 deletes those moves). neighbours.txt only reaches the target's own TU and
    only its comments; this reaches the bodies, ranked by how many of the target's symbols they share."""
    want = set(SYM.findall(target_text)) - {fn}
    if not want:
        return ""
    files = sorted((REPO / "src" / alias).glob("*.c"))
    inc = re.compile(r'#include\s+"\.\./(shared/[^"]+\.h)"')
    heads = set()
    for f in files:
        try:
            heads.update(inc.findall(f.read_text(errors="surrogateescape")))
        except OSError:
            pass
    cands = []
    for f in files + [REPO / "src" / h for h in sorted(heads)]:
        try:
            txt = f.read_text(errors="surrogateescape")
        except OSError:
            continue
        rel = str(f.relative_to(REPO))
        try:
            recs = dl.sc.scan_text(txt, rel, shared_defs=None)
        except Exception:
            continue
        ls = dl.line_starts(txt)
        for r in recs:
            if r.get("form") != "def" or r.get("name") == fn:
                continue
            body = txt[ls[r["line"] - 1]:ls[r["end"]]] if r["end"] < len(ls) else txt[ls[r["line"] - 1]:]
            if "!FAKE" in body or "__asm__" in body:
                continue
            shared = sorted(want & set(SYM.findall(body)) - {r["name"]})
            if shared:
                cands.append((-len(shared), body.count("\n"), r["name"], rel, r["line"], shared, body))
    cands.sort()
    seen, out = set(), [f"=== lever-free bodies in {alias} sharing a callee or global with {fn} "
                         f"({len(cands)} found; top {top} by shared symbols) — read them for the SHAPE ==="]
    for _, n, name, rel, line, shared, body in cands:
        if name in seen:
            continue
        seen.add(name)
        out += [f"--- {name} ({rel}:{line}) shares {len(shared)}: {' '.join(shared[:12])} ---", body.rstrip(), ""]
        if len(seen) >= top or len(out) > max_lines:
            break
    return "\n".join(out[:max_lines]) + "\n"


def build(a):
    ex = [e for e in ds.exemplars(include_done=True) if e["copies"] >= a.min_copies and ds.matches(e, a.only)]
    outs = [json.loads(l) for l in ds.OUTCOMES.read_text().splitlines() if l.strip()] if ds.OUTCOMES.exists() else []
    by_nh = collections.defaultdict(list)
    for o in outs:
        if o.get("kind") == "attempt":
            by_nh[o["nhash"]].append(o)
    rows = []
    for e in ex:
        att = by_nh.get(e["nhash"], [])
        bests = [o["best"] for o in att if o.get("best") is not None]
        e["best"] = min(bests) if bests else None
        rows.append(e)
    rows.sort(key=lambda e: (e["best"] if e["best"] is not None else 10**6, -e["copies"]))
    rows = rows[:a.limit] if a.limit else rows
    PACKS.mkdir(parents=True, exist_ok=True)
    order = ["rank\tfn\talias\tcopies\tbest\tneeded\tkinds\tregs\ttu"]
    for k, e in enumerate(rows, 1):
        tu, fn = e["tu"], e["fn"]
        d = PACKS / f"{e['alias']}__{fn}"
        d.mkdir(parents=True, exist_ok=True)
        raw = (REPO / tu).read_text(errors="surrogateescape")
        sites = ds.sites_by_body().get((tu, fn), [])
        try:
            free = ds.lever_free_body(tu, raw, fn, sites)
        except ds.Unstrippable as u:
            (d / "residual.txt").write_text(f"UNSTRIPPABLE {u.args[0][:3]}\n")
            order.append(f"{k}\t{fn}\t{e['alias']}\t{e['copies']}\t{e['best']}\t{e['needed']}\t{','.join(e['kinds'])}\t{','.join(e['regs'])}\t{tu}")
            continue
        (d / "tu.txt").write_text(f"{tu}\n{fn}\n")
        for name, text in (("body_tree.c", raw), ("body_free.c", free)):
            dd = ds.body_span(text, tu, fn)
            ls = dl.line_starts(text)
            (d / name).write_text(text[ls[dd["line"] - 1]:ls[dd["end"]]] if dd else "", errors="surrogateescape")
        (d / "tu_free.c").write_text(free, errors="surrogateescape")
        r = subprocess.run([PY, "tools/delever_search.py", "--try", tu, fn, (d / "tu_free.c").as_posix()],
                           capture_output=True, text=True, cwd=REPO)
        (d / "residual.txt").write_text((r.stdout or "") + (r.stderr or ""))
        (d / "sites.txt").write_text("\n".join(
            f"{s.get('verdict', '?'):8s} {s['kind']:11s} {s.get('detail', ''):6s} line {s['line']}" for s in e["row"].get("sites", [])) + "\n")
        hist = [f"{o['label']}: verdict {o['verdict']} start {o.get('start')} best {o.get('best')} compiles {o.get('compiles')} "
                f"path {' + '.join(o.get('path', []))}" for o in by_nh.get(e["nhash"], [])]
        tr = ds.TRACE / f"{e['alias']}__{fn}.jsonl"
        if tr.exists():
            cands = [json.loads(l) for l in tr.read_text().splitlines() if l.strip()]
            cands = [c for c in cands if c.get("score") is not None]
            cands.sort(key=lambda c: c["score"])
            # the CLASS as well as the score (T7 agent a3, S102: history.txt recorded only a number, which hid that a
            # move had already turned this body's residual from REG into ORDER — the agent spent its first hour reading
            # the seed's class for a body whose best child was in a different one)
            hist.append("best-scoring single candidates of the last trace (move -> score [residual class]):")
            hist += [f"  {c['move']} -> {c['score']} [{c.get('cls') or c.get('kind') or '?'}] (from {c['parent']})"
                     for c in cands[:12]]
        # NEIGHBOURS (P36 S102): the answer is sometimes written in English a few lines away. Agent b1 closed
        # func_801651B8 on its FIRST --try after reading the `// @class:` header of an already-matched sibling in the
        # same TU, which spelled the whole crack out ("recompute p = &D[i] each iteration (NOT p++) so gcc reduces
        # base+i*0x10 into a SINGLE pointer IV"). The pack sent agents to the cookbook and the compiler source and never
        # to the target's own neighbours — this project has been leaving itself notes for months.
        try:
            ntxt = (REPO / tu).read_text(errors="surrogateescape")
            nlines = ntxt.split("\n")
            defs_at = [(m.start(), m.group(1)) for m in re.finditer(
                r"^[A-Za-z_][\w \t*]*?\b(func_[0-9A-Fa-f]+)\s*\([^;{]*\)\s*\{", ntxt, re.M)]
            here = next((k for k, (_, nm) in enumerate(defs_at) if nm == fn), None)
            out_n = []
            if here is not None:
                for k in range(max(0, here - 3), min(len(defs_at), here + 4)):
                    if k == here:
                        continue
                    ln = ntxt[:defs_at[k][0]].count("\n")
                    head = []
                    j = ln - 1
                    while j >= 0 and len(head) < 40 and (nlines[j].lstrip().startswith("//")
                                                        or nlines[j].lstrip().startswith("*")
                                                        or nlines[j].lstrip().startswith("/*")):
                        head.append(nlines[j])
                        j -= 1
                    if head:
                        out_n.append(f"--- {defs_at[k][1]} (line {ln + 1}) ---")
                        out_n += list(reversed(head))
            # THE TARGET'S OWN HEADER, IN FULL. neighbours.txt used to carry only the @class/@stuck LINES, and agent b9
            # (S102) lost hours to exactly that: its function's header comment is an eight-point English explanation of
            # every lever it carries, including the tail crack stated outright, and the pack had reduced it to two
            # tagged lines. A grep for tags is not a substitute for the paragraph they sit in.
            if here is not None:
                ln0 = ntxt[:defs_at[here][0]].count("\n")
                own, j = [], ln0 - 1
                while j >= 0 and len(own) < 80 and (nlines[j].lstrip().startswith("//")
                                                   or nlines[j].lstrip().startswith("*")
                                                   or nlines[j].lstrip().startswith("/*")
                                                   or nlines[j].strip() == ""):
                    if nlines[j].strip() == "" and own:
                        break
                    if nlines[j].strip():
                        own.append(nlines[j])
                    j -= 1
                if own:
                    out_n = [f"=== THIS FUNCTION'S OWN HEADER ({fn}, line {ln0 + 1}) — read it in full ==="] \
                            + list(reversed(own)) + [""] + out_n
            tagged = [l for l in nlines if "@class:" in l or "@stuck:" in l or "@crack:" in l]
            if tagged:
                out_n.append("--- every @class/@stuck/@crack note in this translation unit ---")
                out_n += tagged[:60]
            (d / "neighbours.txt").write_text("\n".join(out_n[:400]) + "\n")
        except OSError:
            pass
        try:
            (d / "related.txt").write_text(related_bodies(tu, fn, (d / "body_tree.c").read_text(errors="surrogateescape"),
                                                          e["alias"]), errors="surrogateescape")
        except OSError:
            pass
        # the BEST CANDIDATE'S TEXT, not just its move path: history.txt's `@NNNN` line numbers are relative to the
        # EVOLVING text, so hand-reconstructing a path lands somewhere else (agent b9 reconstructed 51 where the engine's
        # own generators reproduce 16 in one round).
        try:
            bp = ds.RUN / "bodies" / f"{e['alias']}__{fn}.c"
            if bp.exists():
                (d / "best_body.c").write_text(bp.read_text(errors="surrogateescape"), errors="surrogateescape")
        except Exception:
            pass
        (d / "history.txt").write_text("\n".join(hist) + "\n")
        order.append(f"{k}\t{fn}\t{e['alias']}\t{e['copies']}\t{e['best']}\t{e['needed']}\t{','.join(e['kinds'])}\t{','.join(e['regs'])}\t{tu}")
        print(f"  {k:3d} {fn} {e['copies']:4d} copies best {e['best']} -> {d.relative_to(REPO)}", flush=True)
    (PACKS / "ORDER.tsv").write_text("\n".join(order) + "\n")
    print(f"delever_pack: {len(rows)} packs under {PACKS.relative_to(REPO)}; ORDER.tsv written")
    return 0


def main():
    ap = argparse.ArgumentParser()
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--build", action="store_true")
    g.add_argument("--list", action="store_true")
    ap.add_argument("--min-copies", type=int, default=100)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--only", nargs="*", default=[])
    a = ap.parse_args()
    os.chdir(REPO)
    if a.list:
        p = PACKS / "ORDER.tsv"
        print(p.read_text() if p.exists() else "no packs built")
        return 0
    return build(a)


if __name__ == "__main__":
    sys.exit(main())
