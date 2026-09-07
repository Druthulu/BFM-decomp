#!/usr/bin/env python3
"""gccmap_cites.py — tag every `file.c:NNN` citation in docs/gcc-2.7.2-map/*.md with the source tree it refers to (P33 E3).

    tools/gccmap_cites.py                 # derive a tag for every cite from the reference trees and WRITE it in place (idempotent)
    tools/gccmap_cites.py --dry-run       # the same derivation and census, nothing written
    tools/gccmap_cites.py --check         # TEXTUAL: exit 0 iff every cite carries a tag and every override is still used
                                          #   (no reference tree needed — safe for CI and `make tools-health`)
    tools/gccmap_cites.py --verify        # re-derive every existing tag from the trees; exit 1 on any disagreement
    tools/gccmap_cites.py --controls      # the known-true cases (R39) — exit 0 iff every one derives as recorded

The problem this solves. The codegen map was written in Phase 23 against `tools/reference/gcc-papermario/`, which is
gcc 2.8.1 — NOT the pinned 2.7.2 — so its line numbers are correct for the wrong compiler (drift up to +611 lines, enough
to land inside a different function); the Phase-29 audit re-derived every claim against the vanilla 2.7.2 subset at
`tools/reference/gcc-2.7.2/` and found the MECHANISMS sound but left the numbers mixed. A reader following a citation
needs to know which tree it belongs to. Tags are written right after the cite (inside the same code span when the cite
is in one):

    sched.c:2469 [2.7.2]        the cited construct sits at that line in the vanilla 2.7.2 subset (checked, not assumed)
    global.c:616 [2.8.1 pm]     the cited construct sits at that line in gcc-papermario (2.8.1); the 2.7.2 line differs
    engine_core.h:24926 [repo]  a project file, not gcc
    reload1.c:779 [?]           undecided by the evidence AND no override — listed; `--check` fails on it

How a tag is derived (R33 — from the trees, never typed):
  1. EVIDENCE: the identifiers in backticked/bold spans within ±160 characters of the cite (only C-looking ones — with an
     underscore, as every real gcc macro/function cited has; prose words and bare RTL codes are dropped), nearest first. For each, the nearest occurrence to the cited line(s)
     in each tree's file, within ±60 lines (a function name sits at the header, the cite often inside the body). The tree
     whose occurrence is nearer wins; an equal distance is a TIE — the line is equally valid in both — resolved by an
     override if one exists, else the author's cue, else 2.7.2. A line
     past the end of a tree's file cannot be that tree. Files absent from the 2.7.2 subset (18 .c files + config/mips)
     can only be `[2.8.1 pm]`.
  2. CUES: the author's own words — `papermario` / `2.8.1` just before the cite, or `→2.7.2 :NNN` just after it, mean
     2.8.1; `2.7.2` just before means 2.7.2. A cue that CONTRADICTS the evidence leaves the cite undecided (R34 — a
     disagreement fails loudly, it is not averaged); a cue alone decides when there is no evidence.
  3. OVERRIDES: docs/gcc-2.7.2-map/cite_overrides.tsv (`file:line<TAB>tag<TAB>reason`) — a human judgment, kept small;
     `--check` refuses an override whose cite no longer exists (a stale override is a lie, R51).
A tag that already exists is never silently changed: a derivation that disagrees is reported and exits 1
(`--retag` accepts the derivation). Tagging, --verify and --controls need both trees and refuse loudly without them
(R43); --check needs neither.
"""
import argparse
import pathlib
import re
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
MAP_DIR = REPO / "docs" / "gcc-2.7.2-map"
OVERRIDES = MAP_DIR / "cite_overrides.tsv"
TREES = {"2.7.2": REPO / "tools" / "reference" / "gcc-2.7.2", "2.8.1 pm": REPO / "tools" / "reference" / "gcc-papermario"}
TAGS = ("2.7.2", "2.8.1 pm", "repo", "?")
# a cite, optionally already tagged:  file.c:NNN[-MMM] [tag]
CITE = re.compile(r"\b([a-z0-9_-]+\.[ch]):(\d+)(?:-(\d+))?(?: \[(2\.7\.2|2\.8\.1 pm|repo|\?)\])?")
SPAN = re.compile(r"`([^`]+)`|\*\*([^*]+)\*\*")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]{2,}")
DROP = {"A23", "PSX", "REG", "MEM", "SET", "USE", "RTL", "RTX", "CSE", "GTE", "LUID", "TRUE", "FALSE", "STEERABLE",
        "INTRINSIC", "DETERMINED", "NOTHING", "SAME", "FILE", "BOTH", "ACROSS", "CALLS", "ORDER", "LEVER", "TEMP", "SLOT",
        "VALUE", "DENOMINATOR", "FORWARD", "BIRTH", "WITHOUT", "FIRST", "CALL", "ALU", "EXPR", "CODE"}
NEAR, WIDE = 3, 60
SKIP = {"README.md"}
# the known-true cases the map's own text records (audited S23 / t7g); --controls derives them and compares
CONTROLS = [("sched.md", "sched.c:2469", "2.7.2"), ("regalloc.md", "global.c:616", "2.8.1 pm"),
            ("regalloc.md", "local-alloc.c:1745", "2.8.1 pm"), ("cse_expr.md", "cse.c:8621-8644", "2.8.1 pm"),
            ("loop.md", "loop.c:4819", "2.7.2"), ("t7g-giant-harvest.md", "engine_core.h:24926", "repo")]


def tree_file(tree: pathlib.Path, name: str):
    for cand in (tree / name, tree / "config" / "mips" / name):
        if cand.is_file():
            return cand
    return None


_cache = {}


def lines_of(path: pathlib.Path):
    if path not in _cache:
        _cache[path] = path.read_text(encoding="utf-8", errors="replace").split("\n")
    return _cache[path]


_spans = {}


def spans_of(text: str):
    """Every backticked / bold span of the WHOLE document, paired once (pairing inside a window starting mid-span
    inverts the pairs and silently drops the identifiers right next to a cite — an S88 defect)."""
    key = id(text)
    if key not in _spans:
        # fenced code blocks would pair their backticks with the prose's and invert everything after them:
        # blank them (same length, so every offset stays valid) before pairing
        blanked = re.sub(r"```.*?```", lambda m: " " * len(m.group(0)), text, flags=re.S)
        _spans[key] = [(m.start(), m.end(), m.group(1) or m.group(2)) for m in SPAN.finditer(blanked)]
    return _spans[key]


def identifiers_near(text: str, start: int, end: int, own_file: str):
    """C-looking identifiers from backticked/bold spans within ±160 chars, nearest to the cite first."""
    lo, hi = max(0, start - 160), min(len(text), end + 160)
    found = []
    for s, e, span_text in spans_of(text):
        if e < lo or s > hi:
            continue
        dist = min(abs(s - start), abs(e - end))
        for ident in IDENT.findall(span_text):
            if ident in DROP or ident == own_file.split(".")[0]:
                continue
            if "_" not in ident:        # every real gcc macro/function cited has one; bare ALL-CAPS words (NOT, AND, DEST) are prose
                continue
            found.append((dist, ident))
    found.sort()
    out, seen = [], set()
    for _, ident in found:
        if ident not in seen:
            seen.add(ident); out.append(ident)
    return out[:8]


def nearest(tree: pathlib.Path, name: str, a: int, b: int, ident: str):
    """Distance (in lines) from the cited range to the nearest occurrence of ident in this tree's file, within WIDE;
    None = file absent; -1 = the cited line is past the end of the file; WIDE+1 = not found within the window."""
    f = tree_file(tree, name)
    if f is None:
        return None
    L = lines_of(f)
    if a > len(L):
        return -1
    pat = re.compile(r"\b" + re.escape(ident) + (r"" if "_" in ident else r"\b"))
    best = WIDE + 1
    for i in range(max(0, a - 1 - WIDE), min(len(L), b + WIDE)):
        if pat.search(L[i]):
            d = 0 if a - 1 <= i <= b - 1 else (a - 1 - i if i < a - 1 else i - (b - 1))
            best = min(best, d)
    return best


def cue(text: str, start: int, end: int):
    """The author's own words: a prefix cue (tie-breaker) or the arrow form `→2.7.2 :NNN` (decisive — the author
    states both numbers, so the cited one is the 2.8.1 line). Returns (tag, decisive)."""
    strip = re.compile(r" \[(?:2\.7\.2|2\.8\.1 pm|repo|\?)\]")       # never read the tags this tool itself wrote (R57)
    before = strip.sub("", text[max(0, start - 40):start])[-24:]
    after = strip.sub("", text[end:end + 30])[:14]
    if re.search(r"`?→\**2\.7\.2 ?:", after):
        return "2.8.1 pm", True
    if "papermario" in before or "2.8.1" in before:
        return "2.8.1 pm", False
    if re.search(r"2\.7\.2 ?`?$", before) or before.endswith("2.7.2 "):
        return "2.7.2", False
    return None, False


DEF_HEADER = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*) \(")      # gcc-2.x style: the function name at column 0, then " ("
_extents = {}


def enclosing(tree: pathlib.Path, name: str, line: int):
    """The function whose definition header is the last one at or before `line` in this tree's file (None = unknown)."""
    f = tree_file(tree, name)
    if f is None or not name.endswith(".c"):
        return None
    if f not in _extents:
        _extents[f] = [(i + 1, m.group(1)) for i, ln in enumerate(lines_of(f)) if (m := DEF_HEADER.match(ln))]
    if line > len(lines_of(f)):
        return "<past EOF>"
    last = None
    for start, fn in _extents[f]:
        if start > line:
            break
        last = fn
    return last


def snippets_near(text: str, start: int, end: int):
    """Backticked spans within ±160 chars that look like quoted source (≥ 6 chars, not a lone identifier/cite)."""
    lo, hi = max(0, start - 160), min(len(text), end + 160)
    out = []
    for s0, e0, span_text in spans_of(text):
        if e0 < lo or s0 > hi or text[s0] != "`":
            continue
        s = " ".join(span_text.split())
        if len(s) >= 6 and not CITE.search(s) and not re.fullmatch(r"[A-Za-z0-9_.$-]+", s):
            out.append((min(abs(s0 - start), abs(e0 - end)), s))
    return [s for _, s in sorted(out)][:6]


def snippet_distance(tree: pathlib.Path, name: str, a: int, b: int, snippet: str):
    """Distance from the cited range to the nearest line containing the whitespace-normalized snippet (see nearest())."""
    f = tree_file(tree, name)
    if f is None:
        return None
    L = lines_of(f)
    if a > len(L):
        return -1
    best = WIDE + 1
    for i in range(max(0, a - 1 - WIDE), min(len(L), b + WIDE)):
        if snippet in " ".join(L[i].split()):
            d = 0 if a - 1 <= i <= b - 1 else (a - 1 - i if i < a - 1 else i - (b - 1))
            best = min(best, d)
    return best


def evidence(name, a, b, idents, snippets=()):
    """The tree the identifiers point at, or None; plus a note. Quoted source snippets first (strongest), then function
    extents (a cite inside a long body is far from the header), then the nearest-occurrence distance (macros, globals,
    headers)."""
    for s in snippets:
        d27, d28 = snippet_distance(TREES["2.7.2"], name, a, b, s), snippet_distance(TREES["2.8.1 pm"], name, a, b, s)
        ok27 = d27 is not None and 0 <= d27 <= WIDE
        ok28 = d28 is not None and 0 <= d28 <= WIDE
        if ok27 and (not ok28 or d27 <= d28):
            return "2.7.2", f"quoted `{s}` at distance {d27} (pm {d28 if d28 is not None else 'n/a'})"
        if ok28:
            return "2.8.1 pm", f"quoted `{s}` at distance {d28} (2.7.2 {'n/a' if d27 is None else ('past EOF' if d27 == -1 else d27)})"
    for ident in idents:
        if "_" in ident and name.endswith(".c"):
            e27, e28 = enclosing(TREES["2.7.2"], name, a), enclosing(TREES["2.8.1 pm"], name, a)
            in27 = e27 is not None and (e27 == ident or e27.startswith(ident))
            in28 = e28 is not None and (e28 == ident or e28.startswith(ident))
            if in27 and in28:
                return "tie", f"line {a} is inside `{ident}` in both trees"
            if in27:
                return "2.7.2", f"line {a} is inside `{e27}` (pm: `{e28}`)"
            if in28:
                return "2.8.1 pm", f"line {a} is inside `{e28}` (2.7.2: `{e27}`)"
    for ident in idents:
        d27, d28 = nearest(TREES["2.7.2"], name, a, b, ident), nearest(TREES["2.8.1 pm"], name, a, b, ident)
        ok27 = d27 is not None and 0 <= d27 <= WIDE
        ok28 = d28 is not None and 0 <= d28 <= WIDE
        if ok27 and ok28 and d27 == d28:
            return "tie", f"`{ident}` at the same distance {d27} in both trees"
        if ok27 and (not ok28 or d27 < d28):
            return "2.7.2", f"`{ident}` at distance {d27} (pm {d28 if d28 is not None else 'n/a'})"
        if ok28:
            note = f"`{ident}` at distance {d28} (2.7.2 {'n/a' if d27 is None else ('past EOF' if d27 == -1 else d27)})"
            return "2.8.1 pm", note
    return None, ("no C-looking identifier near the cite" if not idents else f"none of {idents[:4]} within ±{WIDE} lines in either tree")


def derive(text: str, m: re.Match, overrides):
    name, a = m.group(1), int(m.group(2))
    b = int(m.group(3)) if m.group(3) and int(m.group(3)) >= a else a
    key = cite_key(m)
    if (REPO / "src" / "shared" / name).exists():
        return "repo", "project file"
    c, decisive = cue(text, m.start(), m.end())
    if decisive:
        return c, "the text gives both numbers (→2.7.2 :NNN), so this is the 2.8.1 line"
    f27 = tree_file(TREES["2.7.2"], name)
    if f27 is not None and a > len(lines_of(f27)):
        f28 = tree_file(TREES["2.8.1 pm"], name)
        if f28 is not None and a <= len(lines_of(f28)):
            return "2.8.1 pm", f"line {a} is past the end of the 2.7.2 file ({len(lines_of(f27))} lines)"
    idents = identifiers_near(text, m.start(), m.end(), name)
    ev, note = evidence(name, a, b, idents, snippets_near(text, m.start(), m.end()))
    if ev == "tie":                                   # equally valid in both: the human override may resolve it, else 2.7.2
        if key in overrides:
            return overrides[key][0], f"override resolves a tie ({note}): {overrides[key][1]}"
        return c or "2.7.2", note + (f"; the text's cue [{c}] decides" if c else "; a tie is a valid 2.7.2 line")
    if ev and c and ev != c:
        return "?", f"evidence says [{ev}] ({note}) but the text's cue says [{c}] — resolve by hand (override)"
    if ev:
        return ev, note + (f"; cue agrees" if c else "")
    if c:
        return c, f"cue only ({note})"
    if key in overrides:
        tag, reason = overrides[key]
        return tag, f"override: {reason}"
    if tree_file(TREES["2.7.2"], name) is None:
        note += " (file not in the 2.7.2 subset)"
    else:
        note += f" — line {a} is inside 2.7.2 `{enclosing(TREES['2.7.2'], name, a)}` / pm `{enclosing(TREES['2.8.1 pm'], name, a)}`"
    return "?", note


def load_overrides():
    out = {}
    if OVERRIDES.exists():
        for ln in OVERRIDES.read_text(encoding="utf-8").splitlines():
            ln = ln.rstrip()
            if not ln or ln.startswith("#"):
                continue
            key, tag, reason = (ln.split("\t") + ["", ""])[:3]
            if tag not in TAGS or tag == "?":
                sys.exit(f"gccmap_cites: bad override tag {tag!r} for {key} in {OVERRIDES}")
            out[key.strip()] = (tag, reason.strip())
    return out


def map_files():
    return [p for p in sorted(MAP_DIR.glob("*.md")) if p.name not in SKIP]


def cite_key(m):
    return f"{m.group(1)}:{m.group(2)}" + (f"-{m.group(3)}" if m.group(3) else "")


def require_trees():
    for tag, path in TREES.items():
        if not path.is_dir():
            print(f"gccmap_cites: reference tree for [{tag}] missing at {path} — see docs/SETUP.md §5.6 (re-clone / fetch); "
                  f"--check needs no tree")
            return False
    return True


def run_check():
    overrides = load_overrides()
    used, untagged, n = set(), [], 0
    for p in map_files():
        text = p.read_text(encoding="utf-8")
        for m in CITE.finditer(text):
            n += 1
            key = cite_key(m)
            if key in overrides:
                used.add(key)
            if m.group(4) is None or m.group(4) == "?":
                untagged.append((p.name, key, m.group(4)))
    stale = sorted(set(overrides) - used)
    print(f"gccmap_cites --check: {n} cites in {len(map_files())} files, {len(untagged)} untagged/undecided, "
          f"{len(overrides)} overrides ({len(stale)} stale)")
    for f, k, tag in untagged:
        print(f"  UNTAGGED {f}: {k}" + (" [?]" if tag == "?" else ""))
    for k in stale:
        print(f"  STALE override {k}: no such cite any more — delete it from {OVERRIDES.name}")
    if untagged or stale:
        return 1
    print("gccmap_cites --check: OK")
    return 0


def run_controls():
    if not require_trees():
        return 2
    overrides = {}
    bad = 0
    for fname, key, want in CONTROLS:
        text = (MAP_DIR / fname).read_text(encoding="utf-8")
        got = None
        for m in CITE.finditer(text):
            if cite_key(m) == key:
                got, why = derive(text, m, overrides)
                break
        status = "ok  " if got == want else "FAIL"
        bad += got != want
        print(f"  {status} {fname} {key}: derived [{got}] (want [{want}]) — {why if got is not None else 'cite not found'}")
    print(f"gccmap_cites --controls: {len(CONTROLS)} known-true cases, {bad} failed")
    return 1 if bad else 0


def run_explain():
    """For every undecided cite: the map's own sentence and the cited lines in both trees — the input to an override."""
    if not require_trees():
        return 2
    overrides = load_overrides()
    n = 0
    for p in map_files():
        text = p.read_text(encoding="utf-8")
        for m in CITE.finditer(text):
            tag, why = derive(text, m, overrides)
            if tag != "?":
                continue
            n += 1
            name, a = m.group(1), int(m.group(2))
            ctx = " ".join(text[max(0, m.start() - 110):m.end() + 70].split())
            print(f"\n[{n}] {p.name} {cite_key(m)} — {why}\n    text: …{ctx}…")
            for tag_, tree in TREES.items():
                f = tree_file(tree, name)
                if f is None:
                    print(f"    {tag_:9s}: (file absent)"); continue
                L = lines_of(f)
                show = [f"{i + 1}: {L[i].rstrip()[:110]}" for i in range(a - 1, min(len(L), a + 1)) if i >= 0]
                print(f"    {tag_:9s}: " + (" | ".join(show) if show else f"(past EOF, {len(L)} lines)"))
    print(f"\ngccmap_cites --explain: {n} undecided cites shown")
    return 0


def run_derive(write: bool, verify: bool, retag: bool):
    if not require_trees():
        return 2
    overrides = load_overrides()
    totals = {t: 0 for t in TAGS}; disagreements = []; undecided = []; changed_files = 0; n = 0; over_used = 0
    over_keys_used, cite_keys = set(), set()
    for p in map_files():
        text = p.read_text(encoding="utf-8")
        out, pos, file_changed = [], 0, False
        for m in CITE.finditer(text):
            n += 1
            tag, why = derive(text, m, overrides)
            cite_keys.add(cite_key(m))
            if why.startswith("override"):          # "override: …" and "override resolves a tie …"
                over_used += 1; over_keys_used.add(cite_key(m))
            existing = m.group(4)
            totals[tag] += 1
            if tag == "?":
                undecided.append((p.name, cite_key(m), why))
            if existing and existing != "?" and existing != tag:
                disagreements.append((p.name, cite_key(m), existing, tag, why))
                if not retag:
                    tag = existing        # never silently change a tag
            new = f"{m.group(1)}:{m.group(2)}" + (f"-{m.group(3)}" if m.group(3) else "") + f" [{tag}]"
            if new != m.group(0):
                file_changed = True
            out.append(text[pos:m.start()]); out.append(new); pos = m.end()
        out.append(text[pos:])
        if file_changed:
            changed_files += 1
            if write:
                p.write_text("".join(out), encoding="utf-8")
    mode = "verify" if verify else ("write" if write else "dry-run")
    print(f"gccmap_cites ({mode}): {n} cites in {len(map_files())} files — [2.7.2] {totals['2.7.2']} · [2.8.1 pm] "
          f"{totals['2.8.1 pm']} · [repo] {totals['repo']} · undecided {totals['?']} · override hits {over_used} "
          f"({len(overrides)} rows) · files {'written' if write else 'that would change'}: {changed_files}")
    for f, k, why in undecided:
        print(f"  UNDECIDED {f}: {k} — {why}")
    for k in sorted(set(overrides) & cite_keys - over_keys_used):
        print(f"  REDUNDANT override {k}: the evidence decides it — delete the row from {OVERRIDES.name}")
    for f, k, old, new, why in disagreements:
        print(f"  DISAGREE {f}: {k} tagged [{old}], derived [{new}] ({why})" + ("" if retag else " — kept; --retag to accept"))
    if verify:
        return 1 if (disagreements or undecided) else 0
    return 1 if undecided else 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--dry-run", action="store_true")
    g.add_argument("--check", action="store_true")
    g.add_argument("--verify", action="store_true")
    g.add_argument("--controls", action="store_true")
    g.add_argument("--explain", action="store_true", help="show the undecided cites with the map's sentence and both trees' lines")
    ap.add_argument("--retag", action="store_true", help="accept a derivation that disagrees with an existing tag")
    a = ap.parse_args(argv)
    if a.check:
        return run_check()
    if a.controls:
        return run_controls()
    if a.explain:
        return run_explain()
    return run_derive(write=not (a.dry_run or a.verify), verify=a.verify, retag=a.retag)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
