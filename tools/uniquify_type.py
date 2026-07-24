#!/usr/bin/env python3
"""uniquify_type.py — give each CAMP of a same-named type its own name, so every camp becomes liftable.

THE PROBLEM THIS SOLVES (Phase 29 SESSION-14, cookbook §64 follow-up)
=====================================================================
`lift_types.py --candidates` defers any type with 2+ distinct definitions as a VARIANT, because
lifting one camp's layout fleet-wide would silently repoint the other camp's TUs at the wrong
struct (measured: doing exactly that to `Prim` broke 103 binaries). The obvious remedy — "pick a
canonical layout and reconcile the others' field access" — is WRONG for most of these names:

    Vec8  = { s32 w[8] }              in 180 files   (32 bytes)
    Vec8  = { s16 unk0,unk2,unk4,unk6 } in 139 files (8 bytes)

Those are not one type with two spellings; they are two DIFFERENT types that happen to share an
identifier, in different TUs of the same overlay. Reconciling them would merge them. The correct
operation is the opposite: keep both layouts and give them DISTINCT NAMES.

Renaming a type is byte-neutral — a type name emits no code — and it is TU-local by construction
(the definition and every use live in the same file, which is why they diverged in the first
place). Once each camp is uniquely named, each has exactly ONE definition fleet-wide, so
`lift_types.py` lifts them all by its normal rules and the §20 propagation cap lifts with them.

    reconcile  -> merges two layouts        -> breaks the minority camp   (WRONG)
    uniquify   -> preserves both layouts    -> both become liftable       (RIGHT)

WHAT IT REFUSES TO DO
=====================
Renames ONLY inside files that define the camp locally. A file that merely USES the name without
defining it is getting the type from somewhere else (the shared header) and must not be touched —
renaming there would break the reference. `\\bNAME\\b` word boundaries keep `Buf` from matching
`Buf80153978`. The byte-gate (R22) is the sole arbiter, as always.

Usage:
  uniquify_type.py --type Buf                 # dry-run: show the camps + the names it would assign
  uniquify_type.py --type Buf --apply         # rename every NON-majority camp in its own files
Then: lift_types.py --candidates   (the name is now LIFTABLE)  ->  --apply  ->  R22.
"""
import argparse, collections, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_engine_types as bet
import lift_types as lt

REPO = lt.REPO


def camps(name):
    """[(rank, norm_text, {file: [(s,e,raw)]})] for `name`, majority first, DETERMINISTICALLY
    ordered (file-count desc, then the normalized text) so a re-run assigns the same suffixes."""
    hits, _carried = lt.scan({name})
    out = []
    for ent, variants in sorted(hits.items()):
        ranked = sorted(variants.items(), key=lambda kv: (-len(kv[1]), kv[0]))
        out.append((ent, ranked))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--type", required=True, help="the type NAME whose camps to separate")
    ap.add_argument("--apply", action="store_true", help="rewrite the files (else dry-run)")
    a = ap.parse_args()
    os.chdir(REPO)

    total_files = 0
    for ent, ranked in camps(a.type):
        kind = ent[0]
        if len(ranked) < 2:
            print(f"  {kind} {a.type}: 1 camp — nothing to uniquify (already liftable)")
            continue
        print(f"\n=== {kind} {a.type}: {len(ranked)} camps")
        for rank, (norm, fmap) in enumerate(ranked):
            files = sorted(f for f in fmap if f != lt.HEADER)
            tag = "MAJORITY — keeps the name" if rank == 0 else f"-> {a.type}_c{rank}"
            print(f"  [{rank}] {len(fmap):4} files  {tag}")
            print(f"       {norm[:96]}")
            if rank == 0:
                continue
            newname = f"{a.type}_c{rank}"
            # `files` are exactly the TUs that DEFINE this camp (fmap came from their def spans),
            # which is the whole safety argument: a file that merely USES the name is not in this
            # list, keeps referring to whatever it got the type from, and is never touched.
            for f in files:
                text = open(f).read()
                n = len(re.findall(rf"\b{re.escape(a.type)}\b", text))
                print(f"       {os.path.relpath(f, REPO):58} {n} occurrence(s)")
                if a.apply:
                    open(f, "w").write(re.sub(rf"\b{re.escape(a.type)}\b", newname, text))
                    total_files += 1

    if a.apply:
        print(f"\n[--apply] rewrote {total_files} file(s).")
        print("  NEXT: lift_types.py --candidates   (the camps are now separately LIFTABLE)")
        print("  PRE-FILTER: make build BINARY=<an affected overlay>")
        print("  THEN: make clean && make extract-all && make check-all   (R22 — the SOLE arbiter)")
        print("  UNDO: git checkout -- src/")
    else:
        print("\n[dry-run] re-run with --apply. A type NAME emits no code, so this is byte-neutral —")
        print("          but R22 is still the arbiter (it always is).")
    return 0


if __name__ == "__main__":
    sys.exit(main())
