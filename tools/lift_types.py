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


def scan(names):
    """Return {name: {norm_def: {file: [(s,e,raw), ...]}}} for typedefs+named structs matching `names`."""
    hits = collections.defaultdict(lambda: collections.defaultdict(lambda: collections.defaultdict(list)))
    for f in sorted(glob.glob(os.path.join(REPO, "src/ov_*/*.c")) + [HEADER]):
        text = open(f).read()
        hscan = bet.blank_comments(text)
        for name, body, s, e in bet.find_typedefs(hscan):
            if name in names:
                hits[name][norm(text[s:e])][f].append((s, e, text[s:e]))
        for kind, name, s, e in bet.find_defs(hscan):
            if name in names:
                hits[name][norm(text[s:e])][f].append((s, e, text[s:e]))
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--types", required=True, help="comma-separated type NAMES to lift")
    ap.add_argument("--apply", action="store_true", help="write the header + strip fleet-wide (else dry-run)")
    ap.add_argument("--exclude", default="", help="comma-separated names to skip (leave local)")
    args = ap.parse_args()
    os.chdir(REPO)
    names = set(t.strip() for t in args.types.split(",") if t.strip())
    names -= set(t.strip() for t in args.exclude.split(",") if t.strip())

    hits = scan(names)
    canon = {}       # name -> canonical raw def text
    strip_by_file = collections.defaultdict(list)   # file -> [(s,e), ...] spans to delete
    header_has = open(HEADER).read()
    for name in sorted(names):
        variants = hits.get(name)
        if not variants:
            print(f"  {name}: NOT FOUND in any overlay — skip")
            continue
        # canonical = the def in the most FILES
        ranked = sorted(variants.items(), key=lambda kv: -len(kv[1]))
        canon_norm, canon_files = ranked[0]
        canon_raw = next(iter(canon_files.values()))[0][2]
        canon[name] = canon_raw
        already = f"}} {name};" in header_has.replace(" ", " ") and name in header_has
        nfiles = sum(len(fm) for fm in variants.values())
        variant_ovs = []
        for vnorm, fmap in ranked[1:]:
            variant_ovs += [os.path.basename(os.path.dirname(f)) for f in fmap]
        tag = f"{len(ranked)} distinct def(s) across {nfiles} files"
        if len(ranked) > 1:
            tag += f"  ⚠ VARIANTS in: {', '.join(sorted(set(variant_ovs))[:6])}{'…' if len(set(variant_ovs))>6 else ''}"
        print(f"  {name}: {tag}")
        print(f"      canonical ({len(canon_files)} files): {norm(canon_raw)[:90]}")
        # schedule strip of ALL copies (canonical + variant) from every overlay file (not the header)
        for vnorm, fmap in ranked:
            for f, spans in fmap.items():
                if f == HEADER:
                    continue
                for (s, e, raw) in spans:
                    strip_by_file[f].append((s, e))

    if not args.apply:
        print(f"\n[dry-run] would lift {len(canon)} type(s) to engine_types.h and strip "
              f"{sum(len(v) for v in strip_by_file.values())} local def(s) across "
              f"{len(strip_by_file)} files. Re-run with --apply, then R22.")
        return 0

    # 1) append canonical defs to the header (before the #endif), if not already present
    htext = open(HEADER).read()
    add = []
    for name in sorted(canon):
        if re.search(rf"}}\s*{re.escape(name)}\s*;", htext) or re.search(rf"\bstruct\s+{re.escape(name)}\b", htext):
            continue  # already in header
        add.append(canon[name].strip())
    if add:
        block = "\n/* --- lift_types.py fleet lift --- */\n" + "\n".join(add) + "\n"
        idx = htext.rfind("#endif")
        htext = htext[:idx] + block + htext[idx:] if idx != -1 else htext + block
        open(HEADER, "w").write(htext)
    # 2) strip local copies (delete highest offset first so earlier spans stay valid)
    for f, spans in strip_by_file.items():
        text = open(f).read()
        for (s, e) in sorted(spans, reverse=True):
            # extend to swallow a trailing newline
            end = e
            if end < len(text) and text[end] == "\n":
                end += 1
            text = text[:s] + text[end:]
        open(f, "w").write(text)
    print(f"[--apply] lifted {len(add)} new type(s) to engine_types.h; stripped local copies in "
          f"{len(strip_by_file)} files.")
    print("  NEXT: make clean && make extract-all && make check-all (R22 — the arbiter).")
    print(f"  UNDO: git checkout -- src/shared/engine_types.h src/ov_*/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
