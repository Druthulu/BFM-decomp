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
        for name, _body, s, e in tdefs:
            if names is None or name in names:
                hits[("typedef", name)][norm(text[s:e])][f].append((s, e, text[s:e]))
        for kind, name, s, e in defs:
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--types", help="comma-separated type NAMES to lift")
    ap.add_argument("--candidates", action="store_true",
                    help="classify every fleet type into LIFTABLE/VARIANT/ALREADY/CARRIED and emit "
                         "the derived --types list (reproducible; no ad-hoc pipeline)")
    ap.add_argument("--apply", action="store_true", help="write the header + strip fleet-wide (else dry-run)")
    ap.add_argument("--exclude", default="", help="comma-separated names to skip (leave local)")
    args = ap.parse_args()
    os.chdir(REPO)
    if args.candidates:
        return candidates()
    if not args.types:
        ap.error("--types is required (or use --candidates to derive it)")
    names = set(t.strip() for t in args.types.split(",") if t.strip())
    names -= set(t.strip() for t in args.exclude.split(",") if t.strip())

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
