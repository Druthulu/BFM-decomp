#!/usr/bin/env python3
"""head_types.py — the struct map's head types resolved to one canonical flat layout each (P38 T3).

For each --type, read the record from the struct map (.run/P37/census/struct_map.json), resolve its layout by MAX-SITE SPLIT
(candidates = layout entries ∪ conflict-dict entries; drop bad widths, misaligned, out-of-size; pick the non-overlapping subset
maximising the summed site count by weighted interval scheduling), render the typedef with struct_layout.render_struct, and
write the per-offset decision record. --header / --decisions rewrite only the text between the marker lines; a missing file is
created with its hand-written skeleton. Flat structs only (the rewriter spells flat members; no unions, no nesting).

  .venv/bin/python tools/head_types.py [--type NAME ...] [--map PATH] [--header PATH] [--decisions PATH] [--selftest]
"""
import argparse
import json
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import struct_layout as sl          # noqa: E402  (render_struct, TYPE_OF — the one writer)

REPO = pathlib.Path(__file__).resolve().parent.parent
DEFAULT_TYPES = ("Unkstruct_800B5CB8", "Unkstruct_80126B58")
SIGN_ORDER = {"s": 0, "u": 1, "p": 2}
C_BEGIN, C_END = "/* head_types:begin */", "/* head_types:end */"
MD_BEGIN, MD_END = "<!-- head_types:begin -->", "<!-- head_types:end -->"

C_SKELETON = f"""/* include/struct_types.h — the struct map's canonical layouts (P38 T3). One definition per type, visible to every space through common.h. Generated block below is written by tools/head_types.py from .run/P37/census/struct_map.json; hand-written text outside the markers survives regeneration. Naming law G62: Unkstruct_<addr>, unkHEX fields, 0xNN offset comments. */
#ifndef STRUCT_TYPES_H
#define STRUCT_TYPES_H

{C_BEGIN}
{C_END}

#endif /* STRUCT_TYPES_H */
"""

MD_SKELETON = f"""# Struct-map decisions — the head types (P38 T3)

## Canonical file set

TODO(T3 expert)

## Resolution rule

TODO(T3 expert)

## Unkstruct_80078E00 (the player block)

TODO(T3 expert)

## Per-offset records

Written by `tools/head_types.py` (max-site split). Losers' sites keep their casts; the byte oracle judges them later.
Summary fields: `overlaps` = candidates dropped because a heavier non-overlapping set won; `misaligned` = candidates dropped
for `off % min(w,4) != 0` (or an 8-byte field off 8-alignment); `union_candidates` = offsets whose resolution is
`union-candidate (deferred)`.

{MD_BEGIN}
{MD_END}
"""


def candidates(rec):
    """(size, kept [(off, w, sign, n)], dropped {reason: [(off, w, sign, n)]}) — the filtered candidate set C."""
    size = rec.get("size_hint") or 0
    size = (size + 3) // 4 * 4
    raw = {}
    for (off, w, sg, n) in rec.get("layout") or []:
        raw[(off, w, sg)] = max(raw.get((off, w, sg), 0), n)
    for c in rec.get("conflicts") or []:
        off, d = c[0], c[1]
        if not isinstance(d, dict):
            continue
        for k, n in d.items():
            w, sg = int(k[:-1]), k[-1]
            raw[(off, w, sg)] = max(raw.get((off, w, sg), 0), n)
    kept, dropped = [], {"misaligned": [], "width": [], "size": [], "sign": []}
    for (off, w, sg), n in raw.items():
        c = (off, w, sg, n)
        if w not in (1, 2, 4, 8):
            dropped["width"].append(c)
        elif sg not in SIGN_ORDER:
            dropped["sign"].append(c)
        elif off % min(w, 4) or (w == 8 and off % 8):   # render_struct needs 8-byte fields 8-aligned
            dropped["misaligned"].append(c)
        elif size and off + w > size:
            dropped["size"].append(c)
        elif n > 0:
            kept.append(c)
    kept.sort(key=lambda c: (c[0], -c[1], SIGN_ORDER[c[2]]))
    return size, kept, dropped


def max_split(cands):
    """Weighted interval scheduling over cands (sorted by off, -w, sign): the non-overlapping subset maximising Σn.
    Ties prefer taking the earlier candidate in the sort order (lower off, then wider, then s<u<p)."""
    m = len(cands)
    nxt = []
    for i, (off, w, _, _) in enumerate(cands):
        j = i + 1
        while j < m and cands[j][0] < off + w:
            j += 1
        nxt.append(j)
    best, take = [0] * (m + 1), [False] * m
    for i in range(m - 1, -1, -1):
        t = cands[i][3] + best[nxt[i]]
        if t >= best[i + 1]:
            best[i], take[i] = t, True
        else:
            best[i] = best[i + 1]
    out, i = [], 0
    while i < m:
        if take[i]:
            out.append(cands[i])
            i = nxt[i]
        else:
            i += 1
    return out


def fmt(c):
    return f"{c[1]}{c[2]}"


def resolve(rec):
    """-> (typedef text, summary line, [decision lines])."""
    name = rec["name"]
    size, cands, dropped = candidates(rec)
    win = max_split(cands)
    wset = set(win)
    losers = [c for c in cands if c not in wset]
    by_winner = {w: [] for w in win}
    for c in losers:
        for w in win:
            if c[0] < w[0] + w[1] and w[0] < c[0] + c[1]:
                by_winner[w].append(c)
                break
    conf_offs = {c[0] for c in rec.get("conflicts") or [] if isinstance(c[1], dict)}
    win_at = {w[0]: w for w in win}
    lines, n_union = [], 0
    for off in sorted(set(conf_offs) | {w[0] for w in win if by_winner[w]}):
        w = win_at.get(off)
        if w is None:
            cov = next((x for x in win if x[0] < off < x[0] + x[1]), None)
            where = f"inside {fmt(cov)}@0x{cov[0]:03X}" if cov else "no field"
            lines.append(f"0x{off:03X}: chosen none ({where}); losers listed there; resolution: split")
            continue
        ls = by_winner[w]
        union = any(l[3] >= 50 and l[3] >= 0.2 * w[3] for l in ls)
        n_union += union
        lt = ", ".join(f"{fmt(l)} n={l[3]}@0x{l[0]:03X}" for l in ls) or "none"
        res = "union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split" if union else "split"
        lines.append(f"0x{off:03X}: chosen {fmt(w)} n={w[3]}; losers: {lt}; resolution: {res}")
    for why in ("width", "sign", "size"):
        if dropped[why]:
            lines.append(f"dropped ({why}): " + ", ".join(f"{fmt(c)} n={c[3]}@0x{c[0]:03X}" for c in sorted(dropped[why])))
    entries = []
    for (off, w, sg, n) in win:
        t = "void *" if sg == "p" else sl.TYPE_OF[(w, sg)]
        entries.append((off, t, f"unk{off:X}", None, None))
    end = max((o + w for (o, w, _, _) in win), default=0)
    sz = max(size, end)
    al = 8 if any(w == 8 for (_, w, _, _) in win) else 4
    sz = (sz + al - 1) // al * al
    comment = (f"P37 struct map: {rec['sites']} sites in {rec['bodies']} bodies; evidence {rec.get('evidence')}" +
               (f"; at {','.join(rec.get('globals_at', [])[:3])}" if rec.get("globals_at") else "") +
               "; resolved by tools/head_types.py (max-site split); decisions: docs/struct-map-decisions.md")
    txt = sl.render_struct(name, entries, size=sz or None, comment=comment)
    summary = (f"fields={len(win)} kept_sites={sum(c[3] for c in win)} dropped_sites={sum(c[3] for c in losers)} "
               f"conflict_offsets={len(rec.get('conflicts') or [])} overlaps={len(losers)} misaligned={len(dropped['misaligned'])} "
               f"union_candidates={n_union}")
    return txt, summary, lines


def splice(path, skeleton, begin, end, body):
    """Replace the text between the marker lines of path (created from skeleton when absent). True when the file changed."""
    p = REPO / path if not pathlib.Path(path).is_absolute() else pathlib.Path(path)
    old = p.read_text() if p.exists() else skeleton
    i, j = old.find(begin), old.find(end)
    if i < 0 or j < i:
        sys.exit(f"head_types: {path} lacks the markers {begin} … {end}")
    new = old[:i + len(begin)] + "\n" + body + old[j:]
    if p.exists() and new == old:
        return False
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(new)
    return True


def selftest():
    rec = dict(name="Unkstruct_TEST", sites=10, bodies=2, size_hint=10, evidence={}, globals_at=[],
               layout=[[0, 4, "s", 5], [2, 2, "u", 4], [4, 2, "s", 3], [6, 2, "u", 3], [7, 1, "u", 9], [8, 4, "s", 2]],
               conflicts=[[0, {"4s": 5, "2u": 3, "2s": 1}], [2, {"2u": 4, "1u": 1}], [3, {"2s": 6}], [6, {"4s": 7, "2u": 3}]])
    txt, summary, lines = resolve(rec)
    # C after filters: 0:4s5 0:2u3 0:2s1 2:2u4 2:1u1 4:2s3 6:2u3 7:1u9 8:4s2 (3:2s and 6:4s misaligned; size 10 -> 12)
    # best: 0:2u3 + 2:2u4 + 4:2s3 + 7:1u9 + 8:4s2 = 21 vs 0:4s5 + 4:2s3 + 7:1u9 + 8:4s2 = 19
    want = "fields=5 kept_sites=21 dropped_sites=10 conflict_offsets=4 overlaps=4 misaligned=2 union_candidates=0"
    ok = summary == want and "/* 0x0007 */ u8 unk7;" in txt and "/* 0x0006 */ u8 pad6[0x1];" in txt and "size = 0xc" in txt
    print("OK" if ok else f"FAIL\n{summary}\n{txt}\n" + "\n".join(lines))
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--type", action="append", help="struct-map type name (repeatable; default the two head types)")
    ap.add_argument("--map", default=".run/P37/census/struct_map.json")
    ap.add_argument("--header", help="C header to rewrite between /* head_types:begin */ … /* head_types:end */")
    ap.add_argument("--decisions", help="markdown to rewrite between <!-- head_types:begin --> … <!-- head_types:end -->")
    ap.add_argument("--selftest", action="store_true")
    a = ap.parse_args()
    if a.selftest:
        return selftest()
    smap = json.loads((REPO / a.map).read_text())
    by = {t["name"]: t for t in smap["types"]}
    chunks, md = [], []
    for n in a.type or DEFAULT_TYPES:
        if n not in by:
            sys.exit(f"head_types: {n} not in {a.map}")
        txt, summary, lines = resolve(by[n])
        print(f"{n}: {summary}")
        chunks.append(txt)
        md.append(f"### {n}\n\n`{summary}`\n\n" + "".join(f"- `{l}`\n" for l in lines))
    if a.header:
        ch = splice(a.header, C_SKELETON, C_BEGIN, C_END, "\n".join(chunks))
        print(f"head_types: {a.header} {'written' if ch else 'unchanged'}")
    if a.decisions:
        body = f"Source: `{a.map}` head `{smap.get('head', '?')}`.\n\n" + "\n".join(md)
        ch = splice(a.decisions, MD_SKELETON, MD_BEGIN, MD_END, body)
        print(f"head_types: {a.decisions} {'written' if ch else 'unchanged'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
