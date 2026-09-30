#!/usr/bin/env python3
"""lift_types.py — fleet-wide lift of a SPECIFIC type list into src/shared/engine_types.h (§20 cap).

The §20 propagation cap: `dedup_propagate` skips a body referencing a struct type that lives at overlay
file scope (not in the shared header). `build_engine_types` lifts ALL of one overlay's types; this tool
lifts a TARGETED name list fleet-wide, which is what unblocking a few specific cores needs — and it handles
the COLLISION landscape that a single-overlay lift cannot: the same type name has 2–3 distinct defs across
the fleet (canonical + drafter-invented variants). It picks the CANONICAL (majority) def, writes it once to
the header, and strips every local copy (canonical AND variant).

Byte-safety is the whole-binary gate's job (R22), NOT this tool's: stripping a variant is byte-neutral when
the function only COPIES the type (`*(T*)a = *(T*)b`, size-based codegen), but a function that ACCESSES fields
by the variant's names/layout will either fail to compile (different field names) or byte-mismatch — so
`make clean && extract-all && check-all` MUST run after, and any overlay it breaks is a variant-user needing
per-function reconcile (rewrite field access to canonical, or keep that type --excluded). This tool REPORTS
the variant overlays so the reconcile is targeted, and is a no-op-safe dry-run by default.

Usage:
  lift_types.py --types Mat32,Vec8,Buf,MATRIX,VECTOR,M8            # dry-run: canonical + variant report
  lift_types.py --types Mat32,Vec8,Buf,MATRIX,VECTOR,M8 --apply   # write header + strip fleet-wide
Then: make clean && make extract-all && make check-all   (R22 — the arbiter)
"""
import argparse, collections, glob, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_engine_types as bet  # find_defs, find_typedefs, blank_comments — brace-aware (R32-fixed)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEADER = os.path.join(REPO, "src/shared/engine_types.h")


def norm(body):
    return re.sub(r"\s+", " ", body.strip())


def brace_depths(text, offsets):
    """{offset: brace depth} over the comment-blanked text. A def at depth > 0 is BLOCK-scope (a
    function-local typedef/struct): it is not a fleet type — two functions may legally define the
    same name differently, and one may reference another block-local type (T5: `Locs` lifted while
    its member type `Blk8L` stayed local -> parse error in every TU)."""
    b = bet.blank_comments(text)
    out, want = {}, sorted(set(offsets))
    depth, wi = 0, 0
    for m in re.finditer(r"[{}]", b):
        while wi < len(want) and want[wi] <= m.start():
            out[want[wi]] = depth
            wi += 1
        depth += 1 if m.group() == "{" else -1
    for o in want[wi:]:
        out[o] = depth
    return out


def declares_object(raw):
    """True when a struct/union def also DECLARES an object: `struct T {...} var;`. Lifting it would
    define the variable in every TU and stripping it deletes the TU's variable (T5: Ctr34)."""
    tail = raw[raw.rfind("}") + 1:]
    tail = re.sub(r"__attribute__\s*\(\(.*\)\)", "", tail, flags=re.S)
    return tail.strip() not in ("", ";")


def common_typedefs():
    """Typedef names include/common.h already provides (u8/s32/...): never lifted — engine_types.h
    includes common.h, so a second typedef is a redefinition error."""
    return {n for n, _b, _s, _e in bet.find_typedefs(
        bet.blank_comments(open(os.path.join(REPO, "include/common.h")).read()))}


def scan(names=None):
    """Return (hits, carried_tags).  names=None collects EVERY type (the --candidates sweep).
         hits          {(kind, name): {norm_def: {file: [(s, e, raw), ...]}}}
         carried_tags  {tag: {alias, ...}} — tags whose body a typedef carries

    Keyed by (kind, name) — the C NAMESPACE — not by bare name. Bare-name keying is wrong twice:
      * it merges `struct Prim` with `typedef ... Prim` (two legal, INDEPENDENT types in different
        namespaces) into one bucket that then reports a bogus "2 distinct defs" variant conflict;
      * it merges a tagged typedef's tag with its alias into a self-collision, and schedules their
        OVERLAPPING spans for deletion — the corruption resolve_type_defs() now prevents.
    Spans come from bet.resolve_type_defs(), so a tagged typedef is recorded ONCE, under its alias,
    with the FULL span (starting at `typedef`, hence emitting a typedef and not a variable)."""
    hits = collections.defaultdict(lambda: collections.defaultdict(lambda: collections.defaultdict(list)))
    carried_tags = collections.defaultdict(set)
    for f in sorted(glob.glob(os.path.join(REPO, "src/ov_*/*.c")) + [HEADER]):
        text = open(f).read()
        defs, tdefs, carried, partial = bet.resolve_type_defs(text)
        if partial:
            print(f"  [warn] {os.path.relpath(f, REPO)}: {len(partial)} malformed PARTIAL "
                  f"def/typedef overlap(s), skipped: {[d[1] for d in partial[:3]]}")
        for _kind, tag, alias in carried:
            carried_tags[tag].add(alias)
        # file scope only (the lift's contract): block-scope defs and object-declaring defs never enter
        depth = brace_depths(text, [s for _n, _b, s, _e in tdefs] + [s for _k, _n, s, _e in defs])
        for name, _body, s, e in tdefs:
            if depth[s]:
                continue
            if names is None or name in names:
                hits[("typedef", name)][norm(text[s:e])][f].append((s, e, text[s:e]))
        for kind, name, s, e in defs:
            if depth[s] or declares_object(text[s:e]):
                continue
            if names is None or name in names:
                hits[(kind, name)][norm(text[s:e])][f].append((s, e, text[s:e]))
    return hits, carried_tags


def candidates():
    """Classify EVERY fleet type into lift buckets and print the derived LIFTABLE list.

    Replaces the ad-hoc shell pipeline that produced Phase-29's "102 single-def fleet-local types":
    a selection nobody could re-run is a selection nobody can audit (R33 — derive it, and derive it
    in the tool that consumes it). Buckets:
      LIFTABLE  exactly ONE distinct definition fleet-wide and not yet in the header -> safe to lift
      ALREADY   already in engine_types.h and every local copy agrees -> strip-only, no new unblock
      VARIANT   2+ distinct definitions (incl. header-vs-overlay divergence) -> NOT liftable blindly;
                these need the per-camp field-access reconcile, and stripping them would silently
                repoint a TU at a different layout
      CARRIED   a struct tag whose body a typedef carries -> lift the alias instead, never the tag
    """
    hits, carried_tags = scan(None)
    h_defs, h_tdefs, _hc, _hp = bet.resolve_type_defs(open(HEADER).read())
    in_header = ({(k, n) for k, n, _s, _e in h_defs}
                 | {("typedef", n) for n, _b, _s, _e in h_tdefs})
    buckets = collections.defaultdict(list)
    for ent, variants in hits.items():
        nfiles = sum(len(fm) for fm in variants.values())
        if len(variants) > 1:
            buckets["VARIANT"].append((ent, nfiles, len(variants)))
        elif ent in in_header:
            buckets["ALREADY"].append((ent, nfiles, 1))
        else:
            buckets["LIFTABLE"].append((ent, nfiles, 1))
    for name, aliases in sorted(carried_tags.items()):
        buckets["CARRIED"].append((("struct", name), 0, sorted(aliases)))

    for b in ("LIFTABLE", "VARIANT", "ALREADY", "CARRIED"):
        rows = buckets[b]
        print(f"\n=== {b}: {len(rows)}")
        for ent, nfiles, extra in sorted(rows, key=lambda r: -r[1])[:12]:
            note = f"{extra} distinct defs" if b == "VARIANT" else (
                f"carried by {extra}" if b == "CARRIED" else f"{nfiles} files")
            print(f"    {ent[0]:8} {ent[1]:26} {note}")
        if len(rows) > 12:
            print(f"    … and {len(rows) - 12} more")
    # --types takes NAMES, but classification is per ENTITY: `struct Prim` can be LIFTABLE while
    # `typedef Prim` is a deferred VARIANT. Emitting the shared name would drag the deferred entity
    # back in (main's strip invariant now refuses it, but the selector should not propose it).
    variant_names = {ent[1] for ent, _n, _x in buckets["VARIANT"]}
    liftable = sorted({ent[1] for ent, _n, _x in buckets["LIFTABLE"]} - variant_names)
    shadowed = sorted({ent[1] for ent, _n, _x in buckets["LIFTABLE"]} & variant_names)
    print(f"\n--types {','.join(liftable)}")
    print(f"\n[candidates] {len(liftable)} liftable name(s); "
          f"{len(buckets['VARIANT'])} variant entities deferred to the per-camp reconcile; "
          f"{len(buckets['CARRIED'])} carried tags never lifted alone.")
    if shadowed:
        print(f"  withheld (a same-named sibling entity is a deferred VARIANT): {', '.join(shadowed)}")
    return 0


# ======================================================================================================================
# --census mode (P38 T5.1.c2): relocate EVERY outside-canon def the census lists (outside_canon.tsv: ov/md/main .c file-
# and block-scope, src/shared per-function headers, other .h) to a canonical header. Two passes:
#   --rename   make every name (ordinary and tag namespace) carry ONE definition text fleet-wide: a divergent copy is
#              renamed <Name>_<suffix> in its scope (canon keeps the name; else a fixed local def keeps it; else the
#              most-used text). Iterates until no conflict is left.
#   --batch B  move one space's defs (ov-file, ov-block, md, main, headers): each distinct text is written ONCE to
#              engine_types.h when every TU using it sees that header, else to include/struct_types.h (common.h, every
#              TU); every copy is stripped (a file-scope copy of a header type is a redefinition in gcc 2.7.2 even when
#              identical, so a name's copies move together whatever their space). Block-scope defs go to file scope;
#              an object-declaring def `struct T {..} v;` leaves `struct T v;`; an anonymous struct in a cast becomes a
#              G62 typedef `Unkstruct_<addr>` (the cast base global's address, else the enclosing function's).
# Byte-safety is R22's; this tool only guarantees the text moves (law C0067: strip only the textually identical).
# ======================================================================================================================
STRUCT_TYPES = os.path.join(REPO, "include/struct_types.h")
CANON_REL = ("src/shared/engine_types.h", "include/struct_types.h")
BATCHES = ("ov-file", "ov-block", "md", "main", "headers")
C_WORDS = {"struct", "union", "enum", "typedef", "unsigned", "signed", "int", "char", "short", "long", "void", "float",
           "double", "const", "volatile", "static", "extern", "register", "sizeof", "__attribute__", "packed", "aligned"}


def _line_starts(t):
    return [0] + [m.end() for m in re.finditer("\n", t)]


def _walk(rel):
    """Every struct/union/enum definition and alias typedef of one file, located exactly as type_census.find_definitions
    locates them (same masked text, same DEF_START walk), with RAW offsets. An anonymous struct restarts the walk after
    its brace (the census's `;`-skip hides a second cast on the same statement)."""
    import bisect
    import share_census as sc
    import type_census as tc
    from struct_layout import DEF_START, ATTR_RX, _match_brace, _split_top
    raw = open(os.path.join(REPO, rel), errors="surrogateescape").read()
    masked = tc._blank_dead_guards(sc.mask_text(raw), raw, rel)
    rl, ml = _line_starts(raw), _line_starts(masked)
    line_of = lambda i: bisect.bisect_right(ml, i)
    to_raw = lambda i: rl[line_of(i) - 1] + (i - ml[line_of(i) - 1])
    fn_of_line = {}
    for d in sc.scan_text(raw, rel):
        if d["form"] == "def":
            for ln in range(d["line"], d["end"] + 1):
                fn_of_line[ln] = d["name"]
    recs, pos = [], 0
    while True:
        m = DEF_START.search(masked, pos)
        if not m:
            break
        close = _match_brace(masked, m.end() - 1)
        if close == -1:
            break
        j = masked.find(";", close)
        tail = masked[close + 1:j] if j != -1 else ""
        tail_clean = ATTR_RX.sub("", tail).strip()
        is_td, kind, tag = bool(m.group(1)), m.group(2), m.group(3)
        obj = not is_td and bool(re.match(r"^\**\s*[A-Za-z_]", tail_clean))
        names = []
        if is_td:
            for part in _split_top(tail_clean, ","):
                mm = re.match(r"^\**\s*([A-Za-z_]\w*)", part.strip())
                if mm:
                    names.append(mm.group(1))
        anon = not is_td and not tag
        if anon and not obj:
            form = "anon" if re.match(r"\s*\*+\s*\)", masked[close + 1:close + 40]) else "anon-other"
            end_m = close + 1
        elif obj:
            form, end_m = ("frame" if anon else "obj"), close + 1
        else:
            form, end_m = "def", (j + 1 if j != -1 else close + 1)
        ln = line_of(m.start())
        fn = fn_of_line.get(ln)
        after = masked[close + 1:close + 80]
        recs.append(dict(rel=rel, s=to_raw(m.start()), e=to_raw(end_m - 1) + 1, line=ln, kind=kind, tag=tag, names=names,
                         typedef=is_td, form=form, scope="block" if fn else "file", fn=fn,
                         ntext=norm(masked[m.start():end_m] + (";" if form == "obj" else "")), after=after,
                         body=masked[m.start():end_m]))
        pos = close + 1 if anon else ((j + 1) if j != -1 else close + 1)
    for m in re.finditer(r"(?<![\w.])typedef\s+([^;{}]+?)\s*;", masked):
        txt = m.group(1)
        fp = re.match(r"^.*?\(\s*\*\s*([A-Za-z_]\w*)\s*\)", txt, re.S)
        nm = fp.group(1) if fp else (re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", txt.strip()) or [None])[0]
        if nm:
            ln = line_of(m.start())
            fn = fn_of_line.get(ln)
            recs.append(dict(rel=rel, s=to_raw(m.start()), e=to_raw(m.end() - 1) + 1, line=ln, kind="typedef", tag=None,
                             names=[nm], typedef=True, form="alias", scope="block" if fn else "file", fn=fn,
                             ntext=norm(masked[m.start():m.end()]), after="", body=masked[m.start():m.end()]))
    incs = [os.path.normpath(os.path.join(os.path.dirname(rel), m.group(1))) for m in sc.INCLUDE_LINE.finditer(masked)]
    return rel, recs, incs


def fleet_index(jobs=16):
    """(recs, includes{rel: [inc rel]}) over every tracked src/ .c/.h and include/ .h."""
    from concurrent.futures import ProcessPoolExecutor
    import subprocess
    files = subprocess.run(["git", "ls-files", "src/*.c", "src/*.h", "include/*.h"], cwd=REPO, capture_output=True,
                           text=True, check=True).stdout.split()
    files = sorted(f for f in files if os.path.exists(os.path.join(REPO, f)))
    recs, incs = [], {}
    with ProcessPoolExecutor(jobs) as ex:
        for rel, rs, ic in ex.map(_walk, files, chunksize=16):
            recs += rs
            incs[rel] = ic
    return recs, incs


def _keys(r):
    """The (namespace, name) keys a record DEFINES. Anonymous structs and frames define none."""
    ks = [("ord", n) for n in r["names"]]
    if r["tag"] and r["form"] in ("def", "obj", "frame"):
        ks.append(("tag", r["tag"]))
    return ks


def _includers(incs):
    """header rel -> every file that includes it, transitively (a header included by a header reaches its includers)."""
    direct = collections.defaultdict(set)
    for f, hs in incs.items():
        for h in hs:
            direct[h].add(f)
    out = {}
    for h in direct:
        seen, work = set(), [h]
        while work:
            x = work.pop()
            for f in direct.get(x, ()):
                if f not in seen:
                    seen.add(f)
                    work.append(f)
        out[h] = seen
    return out


def _census_keys(path):
    import csv
    rows = list(csv.DictReader(open(path), delimiter="\t"))
    return {(r["file"], int(r["line"])) for r in rows}, rows


def _movable(r, ckeys):
    if r["rel"] in CANON_REL or r["kind"] not in ("struct", "union"):
        return False
    if r["form"] == "anon":
        return True
    return r["form"] in ("def", "obj") and (r["rel"], r["line"]) in ckeys


def _suffix(r):
    """<Name>_<suffix>: the T5 variant rename's suffix (the defining file's overlay/stem, + the function for block scope)."""
    parts = r["rel"].split("/")
    stem = os.path.splitext(parts[-1])[0]
    if len(parts) == 2 or parts[0] == "include":
        s = stem
    elif parts[1] == "shared":
        m = re.match(r"func_([0-9A-Fa-f]{8})(?:__(\w+))?$", stem)
        s = (m.group(1) + ("_" + m.group(2) if m.group(2) else "")) if m else stem
    else:
        s = re.sub(r"^ov_", "", parts[1])
        m = re.search(r"_jr_([0-9A-Fa-f]{8})$", stem)
        if m and r["scope"] != "block":
            s += "_" + m.group(1)
        if stem != parts[1] and not m and parts[1] not in stem:
            s += "_" + stem
    if r["scope"] == "block" and r["fn"] and not (len(parts) > 2 and parts[1] == "shared"):
        s += "_" + re.sub(r"^func_", "", r["fn"])
    return s


def _taken_names(cands):
    import subprocess
    if not cands:
        return set()
    p = os.path.join(REPO, ".run/lift_types_cands.txt")
    os.makedirs(os.path.dirname(p), exist_ok=True)
    open(p, "w").write("\n".join(sorted(cands)) + "\n")
    return set(subprocess.run(["git", "grep", "-ohwF", "-f", p, "--", "src", "include"], cwd=REPO,
                              capture_output=True, text=True).stdout.split())


_TEXT = {}


def _text(rel):
    if rel not in _TEXT:
        _TEXT[rel] = open(os.path.join(REPO, rel), errors="surrogateescape").read()
    return _TEXT[rel]


def _blanked(rel, _c={}):
    if rel not in _c:
        _c[rel] = bet.blank_comments(_text(rel))
    return _c[rel]


def _block_end(rel, s):
    """Raw offset of the '}' closing the block that contains offset s."""
    b, depth = _blanked(rel), 0
    for m in re.finditer(r"[{}]", b[s:]):
        depth += 1 if m.group() == "{" else -1
        if depth < 0:
            return s + m.start()
    return len(b)


def _occurrences(rel, key, lo=0, hi=None):
    """[(s, e)] of key's name in rel[lo:hi] in key's namespace (member accesses and enum tags excluded)."""
    ns, name = key
    b = _blanked(rel)
    out = []
    for m in re.finditer(r"\b" + re.escape(name) + r"\b", b[:hi] if hi is not None else b):
        if m.start() < lo:
            continue
        pre = b[max(0, m.start() - 48):m.start()]
        if re.search(r"(\.|->)\s*$", pre):
            continue
        k = re.search(r"\b(struct|union|enum)\s*$", pre)
        if k and k.group(1) == "enum":
            continue
        if ("tag" if k else "ord") == ns:
            out.append((m.start(), m.end()))
    return out


def census_rename(tsv, apply, jobs):
    """Pass 1: one text per (namespace, name) fleet-wide. Returns the number of conflicting keys left."""
    for rnd in range(1, 8):
        _TEXT.clear()
        _blanked.__defaults__[0].clear()
        ckeys, _rows = _census_keys(tsv)
        recs, incs = fleet_index(jobs)
        inc_of = _includers(incs)
        by_key = collections.defaultdict(list)
        for r in recs:
            for k in _keys(r):
                by_key[k].append(r)
        plan = {}                      # (id(rec), key) -> new name
        bad = []
        for k in sorted(by_key):
            rs = by_key[k]
            texts = {r["ntext"] for r in rs}
            if len(texts) < 2:
                continue
            canon = sorted({r["ntext"] for r in rs if r["rel"] in CANON_REL})
            fixed = [r for r in rs if not _movable(r, ckeys) and r["rel"] not in CANON_REL]
            mov = [r for r in rs if _movable(r, ckeys)]
            if len(canon) > 1:
                bad.append((k, "two canon texts"))
                continue
            if canon:
                keep = canon[0]
            elif fixed:
                keep = None            # a local def that never moves keeps the name; every movable text is renamed
            else:
                c = collections.Counter(r["ntext"] for r in mov)
                top = max(c.values())
                keep = min((r for r in mov if c[r["ntext"]] == top), key=lambda r: (r["rel"], r["line"]))["ntext"]
            groups = collections.defaultdict(list)
            for r in mov:
                if r["ntext"] != keep:
                    groups[r["ntext"]].append(r)
            if not groups and len({r["ntext"] for r in fixed} | set(canon)) > 1:
                continue               # fixed-vs-fixed / fixed-vs-canon only: pre-existing and legal (never moved)
            for t, g in groups.items():
                first = min(g, key=lambda r: (r["rel"], r["line"]))
                for r in g:
                    plan[(id(r), k)] = (k[1] + "_" + _suffix(first), first["rel"], first["line"])
        # unique new names (one per text group: the first copy's suffix)
        want = sorted({v for v in plan.values()}, key=lambda v: (v[0], v[1], v[2]))
        taken = _taken_names({v[0] for v in want})
        final, used = {}, set()
        for v in want:
            nm, i = v[0], 2
            while nm in used or nm in taken:
                nm = f"{v[0]}_{i}"
                i += 1
            used.add(nm)
            final[v] = nm
        rid = {id(r): r for r in recs}
        edits = collections.defaultdict(dict)       # rel -> {(s, e): new}
        clash = 0
        for (i, k), v in sorted(plan.items(), key=lambda kv: (rid[kv[0][0]]["rel"], rid[kv[0][0]]["line"])):
            r, new = rid[i], final[v]
            regions = []
            if r["scope"] == "block":
                regions.append((r["rel"], r["s"], _block_end(r["rel"], r["s"])))
            else:
                fl = [r["rel"]] + (sorted(inc_of.get(r["rel"], ())) if r["rel"].endswith(".h") else [])
                for f in fl:
                    regions.append((f, 0, None))
            for f, lo, hi in regions:
                shadows = [(o["s"], _block_end(f, o["s"])) for o in by_key[k]
                           if o["rel"] == f and o["scope"] == "block" and o is not r and r["scope"] != "block"]
                for s, e in _occurrences(f, k, lo, hi):
                    if any(a <= s <= b for a, b in shadows):
                        continue
                    prev = edits[f].get((s, e))
                    if prev and prev != new:
                        clash += 1
                    edits[f][(s, e)] = new
        print(f"[rename round {rnd}] conflicting keys {len({k for (_i, k) in plan})}; defs renamed {len(plan)}; "
              f"new names {len(final)}; files {len(edits)}; clashes {clash}; refused {len(bad)}")
        for k, why in bad[:10]:
            print(f"    refused {k}: {why}")
        for v, nm in sorted(final.items())[:6]:
            print(f"    e.g. {v[1]}:{v[2]} -> {nm}")
        if not plan or not apply:
            return len({k for (_i, k) in plan})
        if clash:
            print("  [refuse] an occurrence would take two new names — not writing")
            return 1
        for f, es in edits.items():
            t = _text(f)
            out, p = [], 0
            for (s, e), new in sorted(es.items()):
                out.append(t[p:s])
                out.append(new)
                p = e
            out.append(t[p:])
            open(os.path.join(REPO, f), "w", errors="surrogateescape").write("".join(out))
        log = os.path.join(REPO, ".run/P38/t51/c2_renames.tsv")
        os.makedirs(os.path.dirname(log), exist_ok=True)
        with open(log, "a") as fh:
            for v, nm in sorted(final.items()):
                fh.write(f"{rnd}\t{v[1]}:{v[2]}\t{v[0].rsplit('_', 1)[0]}\t{nm}\n")
    return 1


def _space(r):
    rel = r["rel"]
    if rel.endswith(".h"):
        return "headers"
    top = rel.split("/")[1]
    if top.startswith("ov_"):
        return "ov-block" if r["scope"] == "block" else "ov-file"
    if top.startswith("md_"):
        return "md"
    return "main"


def _dedent(rel, s, text):
    """A block-scope def's text at file scope: drop its first line's indentation from the following lines."""
    t = _text(rel)
    ind = t[t.rfind("\n", 0, s) + 1:s]
    if ind.strip():
        return text
    return "\n".join([ln[len(ind):] if ln.startswith(ind) else ln for ln in text.split("\n")])


def _fn_addr(fn):
    m = re.match(r"func_([0-9A-Fa-f]{8})$", fn or "")
    return m.group(1).upper() if m else None


def census_move(tsv, batch, apply, jobs, excl_path, excl_out):
    ckeys, rows = _census_keys(tsv)
    recs, incs = fleet_index(jobs)
    inc_of = _includers(incs)
    by_key = collections.defaultdict(list)
    for r in recs:
        for k in _keys(r):
            by_key[k].append(r)
    # refuse on any remaining name conflict (pass 1 not run / not converged)
    left = [k for k, rs in by_key.items() if len({r["ntext"] for r in rs}) > 1 and any(_movable(r, ckeys) for r in rs)]
    if left:
        print(f"[refuse] {len(left)} key(s) still carry two texts (run --rename first): {sorted(left)[:6]}")
        return 1
    excl_names = {}
    if excl_path and os.path.exists(excl_path):
        for ln in open(excl_path):
            if ln.strip() and not ln.startswith("#"):
                nm, _t, why = ln.rstrip("\n").partition("\t")
                excl_names[nm.strip()] = why
    mov = [r for r in recs if _movable(r, ckeys)]
    fns = {}                                                  # function -> first-seen address (for named functions)
    # ---- anonymous casts: G62 names
    anon_name = {}
    anon = sorted((r for r in mov if r["form"] == "anon"), key=lambda r: (r["rel"], r["s"]))
    base_of = {}
    for r in anon:
        m = re.match(r"\s*\*+\s*\)\s*\(?\s*&?\s*D_([0-9A-Fa-f]{8})\b", r["after"])
        a = m.group(1).upper() if m else _fn_addr(r["fn"])
        if a is None and r["fn"] is None:                     # a file-scope macro: the next function's address
            t = _blanked(r["rel"])
            mm = re.search(r"\bfunc_([0-9A-Fa-f]{8})\s*\(", t[r["e"]:])
            a = mm.group(1).upper() if mm else os.path.splitext(os.path.basename(r["rel"]))[0]
        base_of[id(r)] = a or r["fn"]
    cands = {"Unkstruct_" + v for v in base_of.values()}
    taken_all = _taken_names(cands | {c + "_" + str(i) for c in cands for i in range(2, 6)})
    canon_ord = {}
    for r in recs:
        if r["rel"] in CANON_REL:
            for k in _keys(r):
                canon_ord[k[1]] = r
    seen_name = {}                                            # name -> ntext it was given to
    for r in anon:
        base, i = "Unkstruct_" + base_of[id(r)], 1
        while True:
            nm = base if i == 1 else f"{base}_{i}"
            held = seen_name.get(nm)
            if held == r["ntext"]:
                break
            if held is None and nm not in taken_all:
                seen_name[nm] = r["ntext"]
                break
            i += 1
        anon_name[id(r)] = nm
    # ---- groups: one per distinct text (anonymous: per assigned name)
    groups = collections.defaultdict(list)
    for r in mov:
        groups[("anon", anon_name[id(r)]) if r["form"] == "anon" else ("t", r["ntext"])].append(r)
    canon_by_text = {r["ntext"]: r for r in recs if r["rel"] in CANON_REL and r["form"] == "def"}
    gname = {}
    for g, rs in groups.items():
        ks = sorted({k for r in rs for k in _keys(r)})
        gname[g] = g[1] if g[0] == "anon" else (ks[0][1] if ks else "?")
    key_group = {}
    for g, rs in groups.items():
        for r in rs:
            for k in _keys(r):
                key_group[k] = g
    for g, nm in gname.items():
        if g[0] == "anon":
            key_group[("ord", nm)] = g

    def users(r):
        if r["rel"].endswith(".h"):
            return sorted(f for f in inc_of.get(r["rel"], ()) if f.endswith(".c"))
        return [r["rel"]]

    vis_cache = {}

    def visible(f):
        if f not in vis_cache:
            vis_cache[f] = bet.type_visible(os.path.join(REPO, f))
        return vis_cache[f]

    def refs(body, own):
        tags = set(re.findall(r"\b(?:struct|union)\s+([A-Za-z_]\w*)", body))
        body2 = re.sub(r"\b(?:struct|union|enum)\s+[A-Za-z_]\w*", " ", body)
        ords = set(re.findall(r"\b[A-Za-z_]\w*\b", body2)) - C_WORDS
        return {("tag", t) for t in tags} | {("ord", o) for o in ords} - set(own)

    canon_key = {}
    for r in recs:
        if r["rel"] in CANON_REL and r["form"] in ("def", "alias"):
            for k in _keys(r):
                canon_key[k] = r
    local_key = collections.defaultdict(list)               # key -> fixed local defs (never moved)
    for r in recs:
        if r["rel"] not in CANON_REL and not _movable(r, ckeys):
            for k in _keys(r):
                local_key[k].append(r)
    info, excluded = {}, {}
    for g, rs in sorted(groups.items(), key=lambda kv: gname[kv[0]]):
        rep = min(rs, key=lambda r: (r["rel"], r["line"]))
        own = [k for r in rs for k in _keys(r)]
        deps, gdeps, cdeps = refs(rep["body"], own), set(), set()
        for k in sorted(deps):
            if k in key_group and key_group[k] != g:
                gdeps.add(key_group[k])
            elif k in canon_key:
                cdeps.add(k)
            elif k in local_key and any(o["rel"] in {x["rel"] for x in rs} for o in local_key[k]):
                excluded[g] = f"depends on the local {k[0]} {k[1]} (not a census def)"
        us = sorted({u for r in rs for u in users(r)})
        present = canon_by_text.get(rep["ntext"]) if g[0] == "t" else None
        info[g] = dict(rs=rs, rep=rep, gdeps=gdeps, cdeps=cdeps, users=us,
                       target="et" if us and all(visible(u) for u in us) else "st", present=present,
                       batch=min(BATCHES.index(_space(r)) for r in rs))
        nm_all = {k[1] for k in own} | {gname[g]}
        hit = nm_all & set(excl_names)
        if hit:
            excluded[g] = f"listed: {excl_names[sorted(hit)[0]]}"
    # exclusion closure: a def that needs an excluded def stays too
    changed = True
    while changed:
        changed = False
        for g, it in info.items():
            if g not in excluded:
                bad = [d for d in it["gdeps"] if d in excluded]
                if bad:
                    excluded[g] = f"depends on excluded {gname[bad[0]]}"
                    changed = True
    # target propagation: a struct_types.h def's deps go to struct_types.h too; a canon engine_types.h dep is relocated
    reloc = set()                                           # canon engine_types.h records moved to struct_types.h
    et_rel = "src/shared/engine_types.h"

    def canon_deps(r):
        own = _keys(r)
        return [canon_key[k] for k in sorted(refs(r["body"], own)) if k in canon_key]

    for g, it in info.items():
        if it["present"] is not None and it["present"]["rel"] == et_rel and it["target"] == "st":
            reloc.add(id(it["present"]))
    changed = True
    rid = {id(r): r for r in recs}
    while changed:
        changed = False
        for g, it in info.items():
            if it["target"] != "st" or g in excluded:
                continue
            for d in it["gdeps"]:
                if info[d]["target"] != "st":
                    info[d]["target"] = "st"
                    changed = True
                if info[d]["present"] is not None and info[d]["present"]["rel"] == et_rel and id(info[d]["present"]) not in reloc:
                    reloc.add(id(info[d]["present"]))
                    changed = True
            for k in it["cdeps"]:
                c = canon_key[k]
                if c["rel"] == et_rel and id(c) not in reloc:
                    reloc.add(id(c))
                    changed = True
        for i in list(reloc):
            for c in canon_deps(rid[i]):
                if c["rel"] == et_rel and id(c) not in reloc:
                    reloc.add(id(c))
                    changed = True
    # batch closure: a def moves no later than any def that needs it
    changed = True
    while changed:
        changed = False
        for g, it in info.items():
            for d in it["gdeps"]:
                if info[d]["batch"] > it["batch"]:
                    info[d]["batch"] = it["batch"]
                    changed = True
    # ---- report
    per = collections.Counter((BATCHES[it["batch"]], it["target"], "present" if it["present"] is not None else "new")
                              for g, it in info.items() if g not in excluded)
    print(f"[census] {len(rows)} census rows; {len(mov)} movable defs in {len(groups)} text group(s) "
          f"({sum(1 for g in groups if g[0] == 'anon')} anonymous-cast names); excluded {len(excluded)}; "
          f"engine_types.h canon defs relocated to struct_types.h: {len(reloc)}")
    for k, n in sorted(per.items()):
        print(f"    {k[0]:9} {k[1]} {k[2]:8} {n}")
    for g, why in sorted(excluded.items(), key=lambda kv: gname[kv[0]])[:20]:
        print(f"    excluded {gname[g]}: {why}")
    unmatched = sorted({(f, l) for f, l in ckeys} - {(r["rel"], r["line"]) for r in mov})
    print(f"    census rows with no movable def found: {len(unmatched)} {unmatched[:4]}")
    if excl_out:
        os.makedirs(os.path.dirname(os.path.join(REPO, excl_out)), exist_ok=True)
        with open(os.path.join(REPO, excl_out), "w") as fh:
            fh.write("# name\tcause\trows (file:line) — lift_types.py --census exclusions (P38 T5.1.c2)\n")
            for g, why in sorted(excluded.items(), key=lambda kv: gname[kv[0]]):
                fh.write(f"{gname[g]}\t{why}\t{','.join(f'{r['rel']}:{r['line']}' for r in info[g]['rs'])}\n")
    todo = [g for g, it in info.items() if g not in excluded and (batch == "all" or BATCHES[it["batch"]] == batch)]
    # a relocated canon def becomes visible to every TU at once: every copy of it moves in the same batch (the md/main
    # copies of an engine_types.h type are a redefinition the moment it sits in struct_types.h)
    todo += [g for g, it in info.items() if g not in excluded and g not in todo
             and it["present"] is not None and id(it["present"]) in reloc]
    stuck = [gname[g] for g, it in info.items() if g in excluded and it["present"] is not None
             and id(it["present"]) in reloc]
    if stuck:
        print(f"[refuse] relocated canon defs have excluded copies: {stuck[:8]}")
        return 1
    print(f"[batch {batch}] {len(todo)} group(s), {sum(len(info[g]['rs']) for g in todo)} def(s); "
          f"to engine_types.h {sum(1 for g in todo if info[g]['target'] == 'et' and info[g]['present'] is None)}, "
          f"to struct_types.h {sum(1 for g in todo if info[g]['target'] == 'st' and info[g]['present'] is None)}")
    if not apply:
        return 0
    # ---- emit
    todo_set = set(todo)
    emit = {"et": [], "st": []}                             # (sort name, deps names, text)
    for g in todo:
        it = info[g]
        if it["present"] is not None:
            continue
        rep = it["rep"]
        raw = _text(rep["rel"])[rep["s"]:rep["e"]]
        if rep["form"] == "anon":
            txt = f"typedef {raw} {gname[g]};"
        elif rep["form"] == "obj":
            txt = raw + ";"
        else:
            txt = raw
        if rep["scope"] == "block":
            txt = _dedent(rep["rel"], rep["s"], txt)
        emit[it["target"]].append((g, txt))
    moved_reloc = [rid[i] for i in sorted(reloc, key=lambda i: rid[i]["s"])]   # all at once: harmless (common.h precedes)
    # dependency order (Kahn, ties by name)
    for hdr in ("st", "et"):
        items = emit[hdr]
        ids = {g for g, _t in items}
        dep = {g: {d for d in info[g]["gdeps"] if d in ids} for g, _t in items}
        order, ready = [], sorted((g for g in ids if not dep[g]), key=lambda g: gname[g])
        while ready:
            n = ready.pop(0)
            order.append(n)
            for m in sorted(ids, key=lambda g: gname[g]):
                if n in dep[m]:
                    dep[m].discard(n)
                    if not dep[m] and m not in order and m not in ready:
                        ready.append(m)
            ready.sort(key=lambda g: gname[g])
        order += sorted((g for g in ids if g not in order), key=lambda g: gname[g])
        txt = dict(items)
        emit[hdr] = [txt[g] for g in order]
    st_add = [r_text.strip() for r_text in
              [_text(r["rel"])[r["s"]:r["e"]] for r in moved_reloc]] + emit["st"]
    banner = f"\n/* --- lift_types.py --census (P38 T5.1.c2, batch {batch}) --- */\n"
    for path, add, marker in ((STRUCT_TYPES, st_add, "#endif /* STRUCT_TYPES_H */"),
                              (HEADER, emit["et"], "#endif /* BFM_ENGINE_TYPES_H */")):
        if not add:
            continue
        t = open(path).read()
        idx = t.rfind(marker)
        assert idx != -1, f"{path}: no {marker}"
        t = t[:idx] + banner.lstrip("\n") + "\n".join(add) + "\n\n" + t[idx:]
        open(path, "w").write(t)
    _TEXT.pop("src/shared/engine_types.h", None)
    _TEXT.pop("include/struct_types.h", None)
    # ---- strip / replace every copy
    edits = collections.defaultdict(list)                   # rel -> [(s, e, replacement or None=delete lines)]
    for g in todo:
        for r in info[g]["rs"]:
            if r["form"] == "anon":
                edits[r["rel"]].append((r["s"], r["e"], gname[g]))
            elif r["form"] == "obj":
                edits[r["rel"]].append((r["s"], r["e"], f"{r['kind']} {r['tag']}"))
            else:
                edits[r["rel"]].append((r["s"], r["e"], None))
    for r in moved_reloc:                                   # engine_types.h: the relocated canon defs (offsets pre-append)
        edits[r["rel"]].append((r["s"], r["e"], None))
    for f, es in sorted(edits.items()):
        text = open(os.path.join(REPO, f), errors="surrogateescape").read()
        if f == "src/shared/engine_types.h" and emit["et"]:
            pass                                            # appended text sits after every relocated span
        out, prev = [], 0
        bet.assert_disjoint([(s, e) for s, e, _n in es], where=f)
        for s, e, new in sorted(es):
            if new is not None:
                out.append(text[prev:s])
                out.append(new)
                prev = e
                continue
            ls = text.rfind("\n", 0, s) + 1
            if not text[ls:s].strip():
                s = max(ls, prev)
            end, nl = e, text.find("\n", e)
            if nl != -1 and not text[e:nl].strip():
                end = nl + 1
            out.append(text[prev:s])
            prev = max(prev, end)
        out.append(text[prev:])
        open(os.path.join(REPO, f), "w", errors="surrogateescape").write("".join(out))
    print(f"[--apply] batch {batch}: wrote {len(emit['et'])} def(s) to engine_types.h, {len(st_add)} to struct_types.h "
          f"({len(moved_reloc)} relocated from engine_types.h); edited {len(edits)} file(s). NEXT: R22.")
    return 0


# ======================================================================================================================
# --fold mode (P38 T5.1.c3): one canonical NAME per duplicate-layout class (type_census dup_gating.tsv). The canonical
# def keeps its body, moved to the class's earliest definition point so every alias follows it (C0224); every other
# name becomes `typedef <Canon> <declarators>;` in place; `struct <OtherTag>` uses are respelled to the alias; a member
# access the canonical body spells differently is respelled from cc1's own `has no member named` errors (same offset,
# same shape; a constant index may be rewritten, anything else is reported). Canonical name: the PsyQ SDK name when the
# layout AND a member-name list are the SDK struct's (layout alone is ambiguous: SVECTOR=RECT, CVECTOR=P_CODE,
# DR_MODE=DR_TWIN=DR_AREA=DR_OFFSET), else the most-used name among the defs carrying the meaningful signature.
# --fold-dead deletes canon defs every name of which is in the census's structs_dead list. Byte-safety is R22's (C0507).
# ======================================================================================================================
SDK_HDRS = ("tools/reference/psyq-sdk/PSX/INCLUDE/LIBGTE.H", "tools/reference/psyq-sdk/PSX/INCLUDE/LIBGPU.H")
SDK_SCALARS = {"u_char": "u8", "u_short": "u16", "u_long": "u32", "u_int": "u32"}
GEN_BLOCK = ("/* head_types:begin */", "/* head_types:end */")
NOMEMBER_RX = re.compile(r"^(.+?):(\d+): (?:structure|union) has no member named `(\w+)'", re.M)


def _tdef(res, t):
    """The struct/union record a type name resolves to through plain alias typedefs, or None."""
    from struct_layout import _norm_type
    t = _norm_type(t)
    for _ in range(8):
        m = re.match(r"^(struct|union)\s+(\w+)$", t)
        d = res.defs.get(m.group(2) if m else t)
        if d is None:
            return None
        if d.get("alias_of"):
            if d.get("alias_stars") or d.get("alias_dims"):
                return None
            t = _norm_type(d["alias_of"])
            continue
        return d if d.get("kind") in ("struct", "union") else None
    return None


def _shape(res, f):
    """A member's shape: ('s', w, sign) | ('p', 4) | ('a', size, n, elem) | ('st', size, kind, members) | ('?', size)."""
    from struct_layout import scalar_of, _norm_type
    if f["stars"]:
        base = ("p", 4)
    elif f.get("nested"):
        base = _struct_shape(res, f["nested"])
    else:
        sc_ = scalar_of(_norm_type(f["type"]))
        d = None if sc_ else _tdef(res, f["type"])
        if sc_:
            base = ("s", sc_[0], sc_[1])
        elif d is not None:
            base = _struct_shape(res, d)
        else:
            lay = res.layout(f["type"])
            base = ("s", 4, "s") if lay == (4, 4, [(0, 4, "s")]) else ("?", lay[0] if lay else None)
    for n in reversed(f.get("dims") or []):
        base = ("a", (base[1] or 0) * (n or 0), n, base)
    return base


def _struct_shape(res, d):
    from struct_layout import field_offsets
    offs = dict(field_offsets(res, d))
    lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in (d.get("attrs") or "")))
    mem = tuple((f["name"], offs.get(f["name"]), _shape(res, f), f.get("bits")) for f in d["fields"])
    return ("st", lay[0] if lay else None, d["kind"], mem)


def _anon(sh):
    if sh[0] == "a":
        return ("a", sh[1], sh[2], _anon(sh[3]))
    if sh[0] == "st":
        return ("st", sh[1], sh[2], tuple((None, o, _anon(s), b) for _n, o, s, b in sh[3]))
    return sh


def _nodes(sh, off=0, path="", out=None):
    """{path: (off, shape)} for every member node ('.m[1][2]', '.v.vx', …); bit-fields carry off None."""
    out = {} if out is None else out
    if path:
        out[path] = (off, sh)
    if sh[0] == "a" and sh[2]:
        esz = sh[3][1] or 0
        for k in range(sh[2]):
            _nodes(sh[3], None if off is None else off + k * esz, f"{path}[{k}]", out)
    elif sh[0] == "st":
        for nm, o, s, bits in sh[3]:
            if nm:
                _nodes(s, None if (off is None or o is None or bits is not None) else off + o, f"{path}.{nm}", out)
    return out


def _fold_index():
    """Every canon-header struct/union def (type_census's parser) with its raw span, tail, position and shape; the
    Resolver; and the position of every name the canon headers define (the C0224 order check)."""
    import type_census as tc
    from struct_layout import Resolver, layout_hash
    files = list(CANON_REL[::-1]) + sorted(f for f in glob.glob("include/*.h") if f not in CANON_REL)
    order = {rel: i for i, rel in enumerate(CANON_REL[::-1])}      # struct_types.h (via common.h) precedes engine_types.h
    defs, g, tds = [], {}, []
    for rel in files:
        r = tc.walk_file(_text(rel), rel)
        for d in r["definitions"]:
            d["rel"] = rel
        defs += r["definitions"]
        tds += [dict(a, rel=rel) for a in r["typedef_aliases"]]
    for d in defs:
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            g.setdefault(n, d)
    for a in tds:
        g.setdefault(a["name"], dict(kind="alias", alias_of=a["alias_of"], alias_stars=a["alias_stars"], alias_dims=a["alias_dims"]))
    res = Resolver(g)
    out, pos = [], {}
    for rel in CANON_REL:
        spans = collections.defaultdict(list)
        for w in _walk(rel)[1]:
            spans[w["line"]].append(w)
        raw = _text(rel)
        lo, hi = raw.find(GEN_BLOCK[0]), raw.find(GEN_BLOCK[1])
        for w in _walk(rel)[1]:
            for n in w["names"] + ([w["tag"]] if w["tag"] and w["form"] in ("def", "obj") else []):
                pos.setdefault(n, (order[rel], w["s"]))
        for d in defs:
            if d["rel"] != rel or d["kind"] not in ("struct", "union"):
                continue
            ws = [w for w in spans[d["line"]] if w["form"] == "def" and w["kind"] == d["kind"] and w["tag"] == d["tag"]
                  and [n for n in w["names"] if n in d["names"]] == d["names"]]
            if len(ws) != 1:
                continue
            w = ws[0]
            close = raw.rfind("}", w["s"], w["e"])
            lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
            d.update(s=w["s"], e=w["e"], close=close, tail=raw[close + 1:w["e"] - 1], pos=(order[rel], w["s"]),
                     gen=(lo != -1 and lo < w["s"] < hi), lhash=layout_hash(lay), shape=_struct_shape(res, d))
            out.append(d)
    return out, res, pos


def _sdk_defs():
    """{lhash: [(name, member names, body text)]} for the SDK headers' typedef structs (u_* spelled as u8/u16/u32)."""
    import type_census as tc
    from struct_layout import Resolver, layout_hash, field_offsets
    defs = []
    for rel in SDK_HDRS:
        defs += [dict(d, raw=_text(rel)) for d in tc.walk_file(_text(rel), rel)["definitions"]]
    g = {n: dict(kind="alias", alias_of={"u8": "unsigned char", "u16": "unsigned short"}.get(v, "unsigned long"),
                 alias_stars=0, alias_dims=[]) for n, v in SDK_SCALARS.items()}
    for d in defs:
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            g.setdefault(n, d)
    res = Resolver(g)
    out = collections.defaultdict(list)
    for d in defs:
        if d["kind"] != "struct" or not d["names"]:
            continue
        lay = res.layout_of_fields(d["fields"], d["kind"])
        mem = [n for n, _o in field_offsets(res, d)] or [f["name"] for f in d["fields"]]
        out[layout_hash(lay)].append((d["names"][0], mem, d))
    return out


def _sdk_text(d, name):
    """`typedef struct { … } NAME;` from an SDK def record (its field declarations re-emitted, u_* respelled)."""
    raw = d["raw"]
    lines = raw.split("\n")
    i, depth, buf = d["line"] - 1, 0, []
    while i < len(lines):
        buf.append(lines[i])
        depth += lines[i].count("{") - lines[i].count("}")
        if depth <= 0 and "}" in lines[i]:
            break
        i += 1
    t = "\n".join(buf)
    body = t[t.find("{") + 1:t.rfind("}")]
    body = re.sub(r"/\*.*?\*/", "", body, flags=re.S)
    for a, b in SDK_SCALARS.items():
        body = re.sub(r"\b%s\b" % a, b, body)
    fields = [re.sub(r"\s+", " ", x).strip() for x in body.split(";") if x.strip()]
    return "typedef struct {\n" + "".join(f"    {x};\n" for x in fields) + "} %s;" % name


def _count_words(args):
    rel, names = args
    return collections.Counter(w for w in re.findall(r"\b[A-Za-z_]\w*\b", open(os.path.join(REPO, rel), errors="replace").read())
                               if w in names)


def _uses(names, jobs=16):
    """Token count of each name outside the canon headers (src/ and include/)."""
    import subprocess
    from concurrent.futures import ProcessPoolExecutor
    files = [f for f in subprocess.run(["git", "ls-files", "src", "include"], cwd=REPO, capture_output=True, text=True,
                                       check=True).stdout.split() if f not in CANON_REL and f.endswith((".c", ".h"))]
    total = collections.Counter()
    with ProcessPoolExecutor(jobs) as ex:
        for c in ex.map(_count_words, [(f, frozenset(names)) for f in files], chunksize=64):
            total.update(c)
    return total


def _members(d):
    return [f["name"] for f in d["fields"]]


def _sdk_ev(d, smem):
    """SDK evidence beyond the layout: the SDK member list itself, or the same wildcard signature with a meaningful name."""
    sig = [tc_name_sig(dict(name=n)) for n in smem]
    return _members(d) == smem or (len(sig) == len(d["fields"]) and any(x != "*" for x in sig)
                                   and [tc_name_sig(f) for f in d["fields"]] == sig)


def fold_plan(tsv, only, exclude, want_tier1, want_sdk):
    """[class dict(names, canon, canon_text|None, defs, sdk, why)] and [(lhash, cause)] refused."""
    import type_census as tc
    defs, res, pos = _fold_index()
    by_name = {}
    for d in defs:
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            by_name.setdefault(n, []).append(d)
    sdk = _sdk_defs()
    rows = [ln.rstrip("\n").split("\t") for ln in open(tsv)][1:]
    classes, refused = [], []
    for tier, lh, _size, _n, names in rows:
        if (only and lh not in only) or lh in exclude or (not only and not (want_tier1 and tier == "1")):
            continue
        classes.append(dict(lhash=lh, tier=tier, names=set(names.split(","))))
    if want_sdk:        # SDK layout AND an SDK member-name list (or the SDK name itself) in canon: fold onto the SDK name
        for lh, ss in sdk.items():
            for sname, smem, _sd in ss:
                grp = {n for d in defs if d.get("lhash") == lh and (_sdk_ev(d, smem) or sname in d["names"])
                       for n in d["names"] + ([d["tag"]] if d["tag"] else [])}
                if not grp or grp == {sname} or (only and lh + ":sdk" not in only
                                                 and not any(c["names"] & grp for c in classes)):
                    continue
                hit = [c for c in classes if c["names"] & grp]
                if hit:
                    for c in hit:
                        c["names"] |= grp
                    if len(hit) > 1:
                        hit[0]["names"] = set().union(*[c["names"] for c in hit])
                        classes = [c for c in classes if c not in hit[1:]]
                else:
                    classes.append(dict(lhash=lh + ":sdk", tier="sdk", names=set(grp)))
    uses = _uses({n for c in classes for n in c["names"]})
    plan = []
    for c in classes:
        ds = []
        for n in sorted(c["names"]):
            for d in by_name.get(n, []):
                if d not in ds:
                    ds.append(d)
        missing = sorted(n for n in c["names"] if n not in by_name)
        if missing:
            refused.append((c["lhash"], f"not defined in a canon header: {', '.join(missing[:4])}"))
            continue
        if any(d["gen"] for d in ds):
            refused.append((c["lhash"], "a member sits in the generated head_types block"))
            continue
        base = c["lhash"].split(":")[0]
        lh_all = {d["lhash"] for d in ds}
        if len(lh_all) != 1:
            refused.append((c["lhash"], f"members carry {len(lh_all)} layouts"))
            continue
        lh = lh_all.pop()
        # SDK: the layout's SDK struct whose member names one of the class's defs carries (or whose name is in the class)
        cands = [(sn, sm, sd) for sn, sm, sd in sdk.get(lh, []) if want_sdk and (sn in c["names"] or any(_sdk_ev(d, sm) for d in ds))]
        canon_text, sdk_name = None, None
        if len({sn for sn, _m, _d in cands}) == 1 and cands[0][0] in by_name and not any(cands[0][0] in d["names"] for d in ds):
            refused.append((c["lhash"] + " (note)", f"SDK {cands[0][0]} is defined with another layout: folded under a non-SDK name"))
            cands = []
        if len({sn for sn, _m, _d in cands}) == 1:
            sdk_name = cands[0][0]
            same = [d for d in ds if _members(d) == cands[0][1]]
            canon = sdk_name
            if not any(sdk_name in d["names"] for d in ds):
                src = same[0] if same else None
                canon_text = (("typedef %s %s;" % (re.sub(r"^\s*(?:typedef\s+)?(struct|union)\s*\w*\s*\{", r"\1 {",
                                                           _text(src["rel"])[src["s"]:src["close"] + 1]), sdk_name))
                              if src else _sdk_text(cands[0][2], sdk_name))
        else:
            sig = collections.Counter(tuple(tc_name_sig(f) for f in d["fields"]) for d in ds)
            meaningful = [sg for sg in sig if any(x != "*" for x in sg)]
            pool = [d for d in ds if tuple(tc_name_sig(f) for f in d["fields"]) in meaningful] or ds
            cn = [n for d in pool for n in d["names"]] or [d["tag"] for d in pool if d["tag"]]
            canon = sorted(cn, key=lambda n: (-uses[n], n))[0]
        cdef = next((d for d in ds if canon in d["names"] or (not d["names"] and d["tag"] == canon)), None)
        first = min(ds, key=lambda d: d["pos"])
        body = canon_text or _text(cdef["rel"])[cdef["s"]:cdef["e"]]
        plan.append(dict(lhash=c["lhash"], tier=c["tier"], names=c["names"], canon=canon, cdef=cdef, canon_text=canon_text,
                         first=first, defs=ds, sdk=sdk_name, body=body))
    # C0224: the canonical body moves to its class's first def; every type it names must be defined there. A type named in
    # the body that is itself folded is spelled as its class's canon when that canon lands earlier; else the class waits.
    while True:
        at = {n: (c["canon"], c["first"]["pos"]) for c in plan for n in c["names"]}
        drop = []
        for c in plan:
            fields = set()
            for d in c["defs"]:
                fields |= {f["name"] for f in d["fields"] if f["name"]}
            own = {c["canon"]} | c["names"]
            b = bet.blank_comments(c["body"])
            late, subst = [], {}
            for tok in sorted(set(re.findall(r"\b[A-Za-z_]\w*\b", b)) - own - fields):
                if tok in pos and pos[tok] > c["first"]["pos"]:
                    if tok in at and at[tok][1] < c["first"]["pos"]:
                        subst[tok] = at[tok][0]
                    else:
                        late.append(tok)
            if late and not c["sdk"] and c["cdef"] is not c["first"]:
                f0 = c["first"]     # the first def's own body is in place already: it becomes the canonical one
                n0 = f0["names"][0] if f0["names"] else f0["tag"]
                refused.append((c["lhash"] + " (note)", f"{c['canon']} needs {', '.join(late[:3])} (defined later): "
                                                       f"canonical is the first def {n0}"))
                c.update(canon=n0, cdef=f0, canon_text=None, body=_text(f0["rel"])[f0["s"]:f0["e"]])
                continue
            if late:
                refused.append((c["lhash"], f"canonical body needs {', '.join(late[:3])} defined after the class's first def"))
                drop.append(c)
            elif subst:
                c["body"] = re.sub(r"\b(%s)\b" % "|".join(map(re.escape, subst)), lambda m: subst[m.group(1)], c["body"])
        if not drop:
            break
        plan = [c for c in plan if c not in drop]
    # a member name the canon spells at ANOTHER node (TrailEntry.f2 @4 vs Entry8018F07C.f2 @2) compiles unchanged and reads
    # the wrong field: the cc1-driven respell cannot see it, so the class is refused
    keep = []
    for c in plan:
        cdef = c["cdef"]
        if cdef is not None:
            cn = _nodes(cdef["shape"])
        else:
            import type_census as tc
            cn = _nodes(_struct_shape(res, tc.walk_file(c["body"], "sdk.h")["definitions"][0]))
        hit = sorted({(d["names"] or [d["tag"]])[0] + p for d in c["defs"] if d is not cdef
                      for p, (o, sh) in _nodes(d["shape"]).items() if p in cn and (cn[p][0] != o or _anon(cn[p][1]) != _anon(sh))})
        # packed/aligned(1) beside naturally aligned defs: one layout hash, two codegens (lwl/lwr vs lw on a copy)
        attrs = {re.sub(r"\s+", "", d.get("attrs") or "") for d in c["defs"]}
        if len(attrs) > 1:
            refused.append((c["lhash"], f"defs differ in attributes ({' vs '.join(sorted(a or 'none' for a in attrs))[:80]})"))
        elif hit:
            refused.append((c["lhash"], f"member name at another node in canon {c['canon']}: {', '.join(hit[:3])}"))
        else:
            keep.append(c)
    return keep, refused, res


def tc_name_sig(f):
    n = f.get("name") or ""
    return "*" if re.match(r"^(?:unk|f|field_?|pad|p|a|b|c|d|w|v|m|t|x|s|u|_|arr|buf|data|val|word|byte|half|tmp|r|q|n)?"
                           r"[0-9A-Fa-fx_]*$", n) else n


def _alias_text(d, canon):
    """`typedef <canon> <d's declarators>;` (attributes dropped); a tag-only def aliases its tag."""
    from struct_layout import ATTR_RX
    tail = ATTR_RX.sub("", d["tail"]).strip()
    if d["typedef"] and tail:
        return f"typedef {canon} {tail};"
    return f"typedef {canon} {d['tag']};"


def _respell_map(res, old, canon_shape):
    """{member: [(old path, off, shape)]} of the old def's nodes whose spelling is not canon's (same path, same shape)."""
    on, cn = _nodes(old["shape"]), _nodes(canon_shape)
    diff = collections.defaultdict(list)
    for p, (o, sh) in on.items():
        if cn.get(p) != (o, sh):
            diff[re.match(r"\.(\w+)", p).group(1)].append(p)
    return {m: ps for m, ps in diff.items()}


def _rewrite_access(text, i, old_nodes, canon_nodes):
    """Given `text[i:]` starting at a member name, return (end, replacement) mapping the longest parsable constant path to
    canon's node of the same offset and shape (shortest mapping prefix first), or None."""
    segs, j = [], i
    m = re.match(r"\w+", text[j:])
    segs.append(("." + m.group(0), j + m.end()))
    j += m.end()
    while True:
        m = re.match(r"\s*\[\s*(0[xX][0-9a-fA-F]+|\d+)\s*\]", text[j:]) or re.match(r"\s*\.\s*([A-Za-z_]\w*)", text[j:])
        if not m:
            break
        tok = m.group(1)
        idx = int(tok, 16) if tok.lower().startswith("0x") else int(tok) if tok.isdigit() else 0
        segs.append((segs[-1][0] + (f"[{idx}]" if m.group(0).lstrip().startswith("[") else "." + tok), j + m.end()))
        j += m.end()
    by_off = collections.defaultdict(list)
    for p, (o, sh) in canon_nodes.items():
        by_off[(o, sh)].append(p)
    anon = collections.defaultdict(list)
    for p, (o, sh) in canon_nodes.items():
        anon[(o, _anon(sh))].append(p)
    for k, (p, e) in enumerate(segs):
        if p not in old_nodes:
            break
        o, sh = old_nodes[p]
        if o is None:
            return None
        hit = by_off.get((o, sh)) or (anon.get((o, _anon(sh))) if k == len(segs) - 1 or segs[k + 1][0] not in old_nodes else None)
        if hit:
            best = min(hit, key=lambda q: (q.count("["), len(q)))
            if best == p:
                return None
            return e, best[1:]
    return None


def _cc1_errors(rels, jobs):
    """{rel: stderr} of cpp | cc1 -o /dev/null for each TU (the Makefile's flags, via compile_only)."""
    import subprocess
    from concurrent.futures import ThreadPoolExecutor
    import compile_only as co
    tcx = co.toolchain(co.MK.read_text())

    def one(rel):
        cmd = " ".join(tcx["cpp"] + [rel]) + " | " + " ".join(tcx["cc1"] + tcx["cc1flags"] + ["-o", "/dev/null"])
        r = subprocess.run(["bash", "-c", cmd], cwd=REPO, capture_output=True, text=True, errors="replace")
        return rel, r.stderr if r.returncode else ""
    with ThreadPoolExecutor(jobs) as ex:
        return {rel: err for rel, err in ex.map(one, sorted(rels)) if err}


def _all_tus():
    import compile_only as co
    return sorted({rel for _a, rel, _act in co.plan(sorted(co.src_dirs()))})


def fold_apply(plan, res, apply, jobs, report):
    """Rewrite the canon headers, respell `struct <Tag>` uses and member accesses. Returns the unresolved sites."""
    import subprocess
    edits = collections.defaultdict(list)          # rel -> [(s, e, text)]
    tags, respell, canon_shape = {}, {}, {}
    for c in plan:
        canon, cdef, first = c["canon"], c["cdef"], c["first"]
        ctext = c["body"]
        cshape = cdef["shape"] if cdef is not None else None
        if cshape is None:      # a new SDK body: its shape is the class's (same layout), members from the text
            import type_census as tc
            nd = tc.walk_file(ctext, "sdk.h")["definitions"][0]
            cshape = _struct_shape(res, nd)
        # at most one alias per NAME: a tag-only def whose tag is also a typedef name of the class (or the canon) emits
        # no alias (`struct V3 {..}` beside `typedef struct {..} V3;`); its `struct V3` uses respell to `V3`
        tdnames = {canon} | {n for d in c["defs"] for n in d["names"]}
        kept_tag = cdef["tag"] if cdef is not None and c["canon_text"] is None else None
        for d in c["defs"]:
            if d is cdef:
                continue
            if d["names"] or d["tag"] not in tdnames:
                txt = _alias_text(d, canon if cdef is None or cdef["names"] else f"{cdef['kind']} {canon}")
            else:
                txt = ""
            if d is first:
                txt = ctext + ("\n" + txt if txt else "")
            edits[d["rel"]].append((d["s"], d["e"], txt))
            alias = d["names"][0] if d["names"] else d["tag"]
            if d["tag"] and d["tag"] != kept_tag:     # the tag no longer exists after the fold
                tags[d["tag"]] = (alias, d["rel"])
            rm = _respell_map(res, d, cshape)
            if rm:
                key = alias if alias not in respell else f"{alias}#{d['rel']}:{d['s']}"
                respell[key] = dict(members=rm, old=_nodes(d["shape"]), canon=_nodes(cshape), cls=c["lhash"])
                for n in d["names"][1:]:
                    respell[n] = respell[key]
        if cdef is not None and cdef is not first:
            edits[cdef["rel"]].append((cdef["s"], cdef["e"], ""))
        elif cdef is None and first is None:
            pass
    nm = sum(len(v) for v in edits.values())
    print(f"[fold] {len(plan)} class(es): {nm} def edit(s); {len(tags)} tag(s) to respell; "
          f"{len(respell)} alias(es) whose member spelling differs from canon")
    if report:
        with open(report, "w") as fh:
            for c in plan:
                fh.write(f"{c['lhash']}\ttier{c['tier']}\t{c['canon']}\t{'sdk' if c['sdk'] else ''}\t{len(c['names'])}\t"
                         f"{','.join(sorted(c['names'] - {c['canon']}))}\n")
    if not apply:
        for a, r in sorted(respell.items())[:40]:
            print(f"  respell {a} ({r['cls']}): " + ", ".join(f"{m}" for m in sorted(r["members"])))
        return []
    for rel, es in edits.items():
        t = _text(rel)
        for s, e, txt in sorted(es, reverse=True):
            if not txt:     # delete whole lines when the span owns them
                ls, le = t.rfind("\n", 0, s) + 1, t.find("\n", e)
                le = len(t) if le == -1 else le
                if not t[ls:s].strip() and not t[e:le].strip():
                    s, e = ls, min(le + 1, len(t))
            t = t[:s] + txt + t[e:]
        open(os.path.join(REPO, rel), "w", errors="surrogateescape").write(t)
        _TEXT[rel] = t
    _blanked.__defaults__[0].clear()
    # `struct <Tag>` uses -> the alias (a forward decl / self-typedef of the tag is dropped)
    if tags:
        p = os.path.join(REPO, ".run/lift_types_fold_tags.txt")
        open(p, "w").write("\n".join(sorted(tags)) + "\n")
        files = subprocess.run(["git", "grep", "-lwF", "-f", p, "--", "src", "include"], cwd=REPO, capture_output=True,
                               text=True).stdout.split()
        rx = re.compile(r"\b(?:struct|union)\s+(%s)\b" % "|".join(map(re.escape, sorted(tags))))
        nt = 0
        for rel in files:
            _TEXT.pop(rel, None)
            t, b = _text(rel), bet.blank_comments(_text(rel))
            out, last = [], 0
            for m in rx.finditer(b):
                alias = tags[m.group(1)][0]
                ls, le = t.rfind("\n", 0, m.start()) + 1, t.find("\n", m.end())
                line = b[ls:le if le != -1 else len(b)]
                if re.match(r"^\s*(?:struct|union)\s+\w+\s*;\s*$", line) or re.match(
                        r"^\s*typedef\s+(?:struct|union)\s+(\w+)\s+%s\s*;\s*$" % re.escape(alias), line):
                    if ls >= last:
                        out.append(t[last:ls])
                        last = (le + 1) if le != -1 else len(t)
                    continue
                if m.start() < last:
                    continue
                out.append(t[last:m.start()] + alias)
                last = m.end()
                nt += 1
            if last:
                t = "".join(out) + t[last:]
                open(os.path.join(REPO, rel), "w", errors="surrogateescape").write(t)
                _TEXT[rel] = t
        print(f"[fold] respelled {nt} `struct <Tag>` use(s) in {len(files)} file(s)")
    # member accesses: cc1's `has no member named` errors, fixed per line, until none or no progress
    unresolved = []
    if not respell:
        return unresolved
    by_member = collections.defaultdict(list)
    for a, r in respell.items():
        for m in r["members"]:
            if r not in by_member[m]:
                by_member[m].append(r)
    todo = _all_tus()
    for rnd in range(1, 7):
        errs = _cc1_errors(todo, jobs)
        sites = collections.defaultdict(set)
        other = 0
        for tu, err in errs.items():
            hits = NOMEMBER_RX.findall(err)
            other += len([ln for ln in err.splitlines() if ": " in ln and "has no member" not in ln
                          and "warning" not in ln and "In function" not in ln and "At top level" not in ln])
            for f, ln, mem in hits:
                sites[(os.path.relpath(os.path.join(REPO, f), REPO) if not f.startswith("/") else os.path.relpath(f, REPO),
                       int(ln))].add(mem)
        print(f"[fold] cc1 round {rnd}: {len(errs)} TU(s) with errors, {len(sites)} no-member line(s), {other} other error line(s)")
        if not sites:
            if errs:
                for tu, err in sorted(errs.items())[:8]:
                    unresolved.append((tu, 0, "other", err.strip().splitlines()[-1][:200]))
            break
        fixed = 0
        for (rel, ln), mems in sorted(sites.items()):
            t = _text(rel)
            ls = [0] + [m.end() for m in re.finditer("\n", t)]
            s0, e0 = ls[ln - 1], (ls[ln] - 1 if ln < len(ls) else len(t))
            line = t[s0:e0]
            new, last, changed = [], 0, False
            for m in re.finditer(r"(\.|->)\s*(\w+)\b", line):
                if m.group(2) not in mems or m.start(2) < last:
                    continue
                outs = set()
                for r in by_member[m.group(2)]:
                    w = _rewrite_access(line, m.start(2), r["old"], r["canon"])
                    if w:
                        outs.add(w)
                if len(outs) != 1:
                    unresolved.append((rel, ln, m.group(2), f"{len(outs)} candidate rewrite(s): {line.strip()[:160]}"))
                    continue
                e, rep = outs.pop()
                new.append(line[last:m.start(2)] + rep)
                last, changed = e, True
            if not changed and not any(u[0] == rel and u[1] == ln for u in unresolved):
                unresolved.append((rel, ln, ",".join(sorted(mems)), f"no rewritable access on the line: {line.strip()[:160]}"))
            if changed:
                line = "".join(new) + line[last:]
                t = t[:s0] + line + t[e0:]
                open(os.path.join(REPO, rel), "w", errors="surrogateescape").write(t)
                _TEXT[rel] = t
                fixed += 1
        if not fixed:
            break
        todo = sorted(errs)
    for u in unresolved[:60]:
        print(f"  UNRESOLVED {u[0]}:{u[1]} `{u[2]}` — {u[3]}")
    print(f"[fold] {len(unresolved)} unresolved site(s). NEXT: R22.")
    return unresolved


def fold_dead(census_json, apply):
    """Delete every canon def all of whose names are in the census's structs_dead list."""
    import json
    dead = set(json.load(open(census_json)).get("structs_dead") or [])
    defs, _res, _pos = _fold_index()
    edits, done, partial = collections.defaultdict(list), [], []
    for d in defs:
        own = set(d["names"]) | ({d["tag"]} if d["tag"] else set())
        if not own & dead:
            continue
        if own <= dead and not d["gen"]:
            edits[d["rel"]].append((d["s"], d["e"]))
            done += sorted(own)
        else:
            partial.append(sorted(own))
    print(f"[fold-dead] {len(done)} dead name(s) in {sum(map(len, edits.values()))} def(s); {len(partial)} def(s) with a live "
          f"name kept: {partial[:10]}; not found: {sorted(dead - set(done) - {n for p in partial for n in p})}")
    if apply:
        for rel, es in edits.items():
            t = _text(rel)
            for s, e in sorted(es, reverse=True):
                ls, le = t.rfind("\n", 0, s) + 1, t.find("\n", e)
                le = len(t) if le == -1 else le
                if not t[ls:s].strip() and not t[e:le].strip():
                    s, e = ls, min(le + 1, len(t))
                t = t[:s] + t[e:]
            open(os.path.join(REPO, rel), "w", errors="surrogateescape").write(t)
    return 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--types", help="comma-separated type NAMES to lift")
    ap.add_argument("--candidates", action="store_true",
                    help="classify every fleet type into LIFTABLE/VARIANT/ALREADY/CARRIED and emit "
                         "the derived --types list (reproducible; no ad-hoc pipeline)")
    ap.add_argument("--apply", action="store_true", help="write the header + strip fleet-wide (else dry-run)")
    ap.add_argument("--exclude", default="", help="comma-separated names to skip (leave local)")
    ap.add_argument("--census", metavar="TSV", help="census mode: relocate every def in type_census's outside_canon.tsv")
    ap.add_argument("--rename", action="store_true", help="--census pass 1: one text per name (divergent -> <Name>_<suffix>)")
    ap.add_argument("--batch", choices=BATCHES + ("all",), help="--census pass 2: move this space's defs")
    ap.add_argument("--exclude-file", help="--census: names to leave, one per line `name<TAB>cause`")
    ap.add_argument("--excluded-out", help="--census: write every excluded def with its cause here")
    ap.add_argument("--fold", metavar="TSV", help="fold mode: one canonical name per class of type_census's dup_gating.tsv")
    ap.add_argument("--fold-tier1", action="store_true", help="--fold: every tier-1 class")
    ap.add_argument("--fold-sdk", action="store_true", help="--fold: also fold canon defs with an SDK layout+member names")
    ap.add_argument("--fold-class", help="--fold: only these lhashes (comma-separated; `<lh>:sdk` for an SDK group)")
    ap.add_argument("--fold-exclude", help="--fold: skip these lhashes (comma-separated)")
    ap.add_argument("--fold-report", help="--fold: write one row per folded class (lhash, tier, canon, sdk, n, aliases)")
    ap.add_argument("--fold-dead", metavar="CENSUS_JSON", help="delete canon defs whose every name is in structs_dead")
    ap.add_argument("-j", "--jobs", type=int, default=16)
    args = ap.parse_args()
    os.chdir(REPO)
    if args.fold_dead:
        return fold_dead(args.fold_dead, args.apply)
    if args.fold:
        only = set(x for x in (args.fold_class or "").split(",") if x)
        excl = set(x for x in (args.fold_exclude or "").split(",") if x)
        plan, refused, res = fold_plan(args.fold, only, excl, args.fold_tier1, args.fold_sdk)
        for lh, why in refused:
            print(f"  REFUSED {lh}: {why}")
        unresolved = fold_apply(plan, res, args.apply, args.jobs, args.fold_report)
        return 1 if unresolved else 0
    if args.census:
        if args.rename:
            return 0 if census_rename(args.census, args.apply, args.jobs) == 0 or not args.apply else 1
        if not args.batch:
            ap.error("--census needs --rename or --batch")
        return census_move(args.census, args.batch, args.apply, args.jobs, args.exclude_file, args.excluded_out)
    if args.candidates:
        return candidates()
    if not args.types:
        ap.error("--types is required (or use --candidates to derive it)")
    names = set(t.strip() for t in args.types.split(",") if t.strip())
    names -= set(t.strip() for t in args.exclude.split(",") if t.strip())
    provided = names & common_typedefs()
    if provided:
        print(f"  SKIP (include/common.h provides): {', '.join(sorted(provided))}")
        names -= provided
    # an overlay-LOCAL header (src/ov_*/*.h, src/md_*/*.h) that defines the same name collides with
    # the lifted copy in every TU including both (T5: ov_SC02_005_shared.h -> `conflicting types`)
    in_local_h = collections.defaultdict(set)
    for h in sorted(glob.glob(os.path.join(REPO, "src/ov_*/*.h")) + glob.glob(os.path.join(REPO, "src/md_*/*.h"))):
        d, t, _c, _p = bet.resolve_type_defs(open(h).read())
        for n in {n for _k, n, _s, _e in d} | {n for n, _b, _s, _e in t}:
            if n in names:
                in_local_h[n].add(os.path.relpath(h, REPO))
    for n, hs in sorted(in_local_h.items()):
        print(f"  SKIP {n}: also defined in overlay-local header {', '.join(sorted(hs))}")
    names -= set(in_local_h)

    hits, carried_tags = scan(names)
    # what the header ALREADY defines — derived by parsing it, not guessed by a regex (R33)
    htext = open(HEADER).read()
    h_defs, h_tdefs, _hc, _hp = bet.resolve_type_defs(htext)
    in_header = ({(k, n) for k, n, _s, _e in h_defs}
                 | {("typedef", n) for n, _b, _s, _e in h_tdefs})
    h_norm = {(k, n): norm(htext[s:e]) for k, n, s, e in h_defs}
    h_norm.update({("typedef", n): norm(htext[s:e]) for n, _b, s, e in h_tdefs})

    canon = {}       # (kind, name) -> canonical raw def text
    strip_by_file = collections.defaultdict(list)   # file -> [(s,e), ...] spans to delete
    blind = collections.defaultdict(set)            # TU that cannot see the header -> types kept local
    divergent = collections.defaultdict(set)        # entity -> overlays whose local def differs
    for name in sorted(names):
        # resolve_type_defs() already folds a carried tag into its typedef, so a carried tag never
        # reaches `hits`. An empty result is therefore the exact signal — and it must NOT be tested
        # before the entity lookup: the usual shape here is `typedef struct X {...} X;`, where the
        # tag and the alias share a spelling, so skipping the whole NAME would refuse to lift the
        # very typedef we want (the selector and this loop would then disagree about the same type).
        ents = sorted(k for k in hits if k[1] == name)
        if not ents:
            if name in carried_tags:
                print(f"  {name}: SKIP — a struct tag whose body is carried by typedef "
                      f"{'/'.join(sorted(carried_tags[name]))}. Lift that alias instead; it carries "
                      f"this tag's definition with it.")
            else:
                print(f"  {name}: NOT FOUND in any overlay — skip")
            continue
        for ent in ents:                       # `struct X` and `typedef X` are independent entities
            kind, variants = ent[0], hits[ent]
            # canonical = the def in the most FILES
            ranked = sorted(variants.items(), key=lambda kv: -len(kv[1]))
            canon_norm, canon_files = ranked[0]
            canon_raw = next(iter(canon_files.values()))[0][2]
            nfiles = sum(len(fm) for fm in variants.values())
            variant_ovs = []
            for vnorm, fmap in ranked[1:]:
                variant_ovs += [os.path.basename(os.path.dirname(f)) for f in fmap]
            tag = f"{len(ranked)} distinct def(s) across {nfiles} files"
            if len(ranked) > 1:
                tag += f"  ⚠ VARIANTS in: {', '.join(sorted(set(variant_ovs))[:6])}{'…' if len(set(variant_ovs))>6 else ''}"
            print(f"  {kind} {name}: {tag}")
            print(f"      canonical ({len(canon_files)} files): {norm(canon_raw)[:90]}")
            if ent in in_header:
                print(f"      already in engine_types.h — stripping local copies only")
            else:
                canon[ent] = canon_raw
            # THE STRIP INVARIANT: remove a local definition ONLY when the definition that becomes
            # visible in its place is TEXTUALLY IDENTICAL to it. Anything else is not consolidation,
            # it is silently repointing a TU at a different layout — which changes codegen, compiles
            # perfectly, and is invisible until the fleet byte-gate. (Measured: stripping 103
            # overlays' local `typedef ... Prim;` in favour of the header's DIFFERENT Prim broke
            # exactly those 103 binaries.) The guard lives HERE, at the mutation, not in the
            # selector — a selector bug must not be able to reach the source.
            visible = h_norm.get(ent) if ent in in_header else norm(canon_raw)
            for vnorm, fmap in ranked:
                if vnorm != visible:
                    divergent[ent] |= {os.path.basename(os.path.dirname(f))
                                       for f in fmap if f != HEADER}
                    continue
                for f, spans in fmap.items():
                    if f == HEADER:
                        continue
                    if not bet.type_visible(f):
                        blind[os.path.relpath(f, REPO)].add(name)
                        continue
                    for (s, e, raw) in spans:
                        strip_by_file[f].append((s, e))

    for ent, ovs in sorted(divergent.items(), key=lambda kv: -len(kv[1])):
        print(f"\n  [divergent] {ent[0]} {ent[1]}: {len(ovs)} overlay(s) define it DIFFERENTLY from "
              f"the shared version — kept local, NOT stripped: "
              f"{', '.join(sorted(ovs)[:5])}{'…' if len(ovs) > 5 else ''}\n"
              f"      (these are the per-camp field-access reconcile work, not lift work.)")

    for f, kept in sorted(blind.items()):
        print(f"\n  [visibility] {f} does not include engine_types.h — keeping {len(kept)} local "
              f"def(s) there: {', '.join(sorted(kept)[:6])}{'…' if len(kept) > 6 else ''}\n"
              f"      (stripping a type out of a TU that cannot see the replacement DELETES it; the "
              f"link error that follows names an unrelated data symbol.)")

    if not args.apply:
        print(f"\n[dry-run] would lift {len(canon)} type(s) to engine_types.h and strip "
              f"{sum(len(v) for v in strip_by_file.values())} local def(s) across "
              f"{len(strip_by_file)} files. Re-run with --apply, then R22.")
        return 0

    # 1) append canonical defs to the header (before the #endif), if not already present.
    #    Emit in DEPENDENCY order (a type whose body has a value member of another lifted type must
    #    follow it) — else cc1 errors on the forward value reference. Topological sort (Kahn).
    htext = open(HEADER).read()
    pending = sorted(canon)          # already filtered against the header's parsed contents
    dep = {ent: set() for ent in pending}
    for ent in pending:
        body = canon[ent]
        inner = body[body.find("{") + 1:body.rfind("}")] if "{" in body else ""
        for other in pending:
            if other != ent and re.search(rf"\b{re.escape(other[1])}\b", inner):
                dep[ent].add(other)
    ordered_names, ready = [], sorted(ent for ent in pending if not dep[ent])
    while ready:
        n = ready.pop(0)
        ordered_names.append(n)
        for m in pending:
            if n in dep[m]:
                dep[m].discard(n)
                if not dep[m] and m not in ordered_names and m not in ready:
                    ready.append(m)
        ready.sort()
    ordered_names += [ent for ent in pending if ent not in ordered_names]  # any cycle: append as-is
    add = [canon[ent].strip() for ent in ordered_names]
    if add:
        block = "\n/* --- lift_types.py fleet lift --- */\n" + "\n".join(add) + "\n"
        idx = htext.rfind("#endif")
        htext = htext[:idx] + block + htext[idx:] if idx != -1 else htext + block
        open(HEADER, "w").write(htext)
    # 2) strip local copies. Built as the COMPLEMENT of the spans in ONE pass over the original
    #    text — no offset ever mutates mid-loop, so an adjacent span cannot be mis-cut. Spans are
    #    asserted pairwise disjoint first (R32); an overlap here is the defect that silently
    #    over-deletes past a span's end and corrupts the following declaration.
    for f, spans in strip_by_file.items():
        text = open(f).read()
        out, prev = [], 0
        for (s, e) in bet.assert_disjoint(spans, where=os.path.relpath(f, REPO)):
            # Delete WHOLE LINES when the span owns them. Removing only text[s:e] leaves the
            # removed line's indentation behind and — with the newline swallowed — glues it onto
            # the next line: semantically inert, but it churns thousands of unrelated lines in the
            # diff and strands the def's trailing comment. So extend to the line start when only
            # whitespace precedes, and past the newline only when only whitespace follows.
            ls = text.rfind("\n", 0, s) + 1
            if not text[ls:s].strip():
                s = max(ls, prev)
            end, nl = e, text.find("\n", e)
            if nl != -1 and not text[e:nl].strip():
                end = nl + 1
            out.append(text[prev:s])
            prev = max(prev, end)
        out.append(text[prev:])
        open(f, "w").write("".join(out))
    print(f"[--apply] lifted {len(add)} new type(s) to engine_types.h; stripped local copies in "
          f"{len(strip_by_file)} files.")
    print("  PRE-FILTER (seconds, catches compile/link errors before a full fleet cycle):")
    print("      make build BINARY=ov_SC01_077     # the most complex TU set: split files, -O0 split, jtbl carves")
    print("    A per-binary pass is NOT a fleet byte claim — it has authorised a fleet-wide break before (§61).")
    print("  NEXT: make clean && make extract-all && make check-all (R22 — the SOLE arbiter).")
    print(f"  UNDO: git checkout -- src/shared/engine_types.h src/ov_*/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
