#!/usr/bin/env python3
"""audit_public.py — the first-push gate: no ROM-derived bytes among the tracked files (P33 B7; CI job `audits`).

    tools/audit_public.py                 # every git-tracked file at HEAD's index (git ls-files)
    tools/audit_public.py --paths a b …   # an explicit file list (tests / a pre-commit hook)

Three checks, each derived from something the repo already asserts (R33), never from a typed list of hashes:
  1. PURGE PATHS — no tracked file lies under tools/public_rewrite/purge_set.txt (the C1 rewrite's own input,
     filter-repo syntax: bare prefix or `glob:`).
  2. ROM CONTENT — no tracked file's SHA1 is a known ROM-derived hash: every `sha1` in extracted/retail/manifest.jsonl
     (the manifest IS the list of ROM-derived artifacts), every binary's SHA1 in config/check.*.sha, and the redump
     Track-1 SHA1 (tools/bfm_extract/extract_exe.REDUMP_TRACK1_SHA1). A renamed copy is caught by content.
  3. SIZE — no tracked file over 50 MiB (GitHub's warning threshold; nothing legitimately tracked is near it).
Prints every count with its denominator (R41) and exits 1 on any offender, naming each (R43: loud, never partial).
Ubuntu CI runs it without the disc, asm/, expected/ or build/ — it reads only tracked text and hashes tracked files.
Control (S87, before C3): on the current private tree it MUST fail naming exactly the purge set (28 dumps, the EXE,
ghidra/**, tools/psyq/**, the 3 session-archive parts, 2 zips, brave.exe) — that is the R39 negative control.
"""
import fnmatch
import hashlib
import json
import os
import pathlib
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
PURGE = REPO / "tools" / "public_rewrite" / "purge_set.txt"
MANIFEST = REPO / "extracted" / "retail" / "manifest.jsonl"
SIZE_CAP = 50 * 1024 * 1024


def purge_rules():
    prefixes, globs = [], []
    for ln in PURGE.read_text(encoding="utf-8").splitlines():
        ln = ln.strip()
        if not ln or ln.startswith("#"):
            continue
        if ln.startswith("glob:"):
            globs.append(ln[5:])
        elif ln.startswith("regex:"):
            sys.exit(f"audit_public: regex: rules are not supported here ({ln}) — R43")
        else:
            prefixes.append(ln)
    if not prefixes and not globs:
        sys.exit(f"audit_public: {PURGE} holds no rules — refusing to pass on an empty purge set (R43)")
    return prefixes, globs


def under_purge(path, prefixes, globs):
    for p in prefixes:
        if path == p or path.startswith(p if p.endswith("/") else p + "/"):
            return p
    for g in globs:
        if fnmatch.fnmatchcase(path, g):
            return "glob:" + g
    return None


def rom_hashes():
    """Every SHA1 the repo itself declares ROM-derived. Coverage-asserted: each source must exist and be non-empty."""
    out = {}
    n_manifest = 0
    if not MANIFEST.exists():
        sys.exit(f"audit_public: {MANIFEST} is missing — the ROM-hash set cannot be derived (R32)")
    for ln in MANIFEST.read_text(encoding="utf-8").splitlines():
        if ln.strip():
            o = json.loads(ln)
            out[o["sha1"].lower()] = "manifest:" + o["path"]
            n_manifest += 1
    checks = sorted((REPO / "config").glob("check.*.sha"))
    if not checks:
        sys.exit("audit_public: no config/check.*.sha files — cannot derive the binary hashes (R32)")
    for c in checks:
        for ln in c.read_text(encoding="utf-8").splitlines():
            parts = ln.split()
            if len(parts) >= 2 and len(parts[0]) == 40:
                out[parts[0].lower()] = f"{c.name}:{parts[1]}"
    sys.path.insert(0, str(REPO / "tools" / "bfm_extract"))
    from extract_exe import REDUMP_TRACK1_SHA1  # the disc itself
    out[REDUMP_TRACK1_SHA1.lower()] = "redump:Track 1"
    if n_manifest < 1000:
        sys.exit(f"audit_public: manifest has {n_manifest} rows (expected the 1,801-row retail manifest) — refusing (R32)")
    return out, n_manifest, len(checks)


def tracked_files():
    r = subprocess.run(["git", "ls-files", "-z"], cwd=REPO, capture_output=True, check=True)
    return [p for p in r.stdout.decode("utf-8", "surrogateescape").split("\0") if p]


def sha1_of(path):
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def main(argv):
    if "--paths" in argv:
        files = argv[argv.index("--paths") + 1:]
    else:
        files = tracked_files()
    prefixes, globs = purge_rules()
    hashes, n_manifest, n_checks = rom_hashes()
    offenders = []
    n_hashed = 0
    for rel in files:
        p = REPO / rel
        rule = under_purge(rel, prefixes, globs)
        if rule:
            offenders.append((rel, f"purge path ({rule})"))
        if not p.is_file():          # a submodule gitlink or a file deleted in the worktree — nothing to hash
            continue
        size = p.stat().st_size
        if size > SIZE_CAP:
            offenders.append((rel, f"{size:,} bytes > 50 MiB"))
        if size == 0:                # the empty-file SHA1 is also a zero-length disc payload's (SC05/029/1.6) — not ROM bytes
            continue
        h = sha1_of(p)
        n_hashed += 1
        if h in hashes:
            offenders.append((rel, f"ROM-derived content: sha1 == {hashes[h]}"))
    print(f"audit_public: {len(files)} tracked paths, {n_hashed} files hashed against {len(hashes)} ROM hashes "
          f"({n_manifest} manifest rows + {n_checks} check.*.sha + redump), "
          f"{len(prefixes) + len(globs)} purge rules, cap 50 MiB")
    if offenders:
        for rel, why in offenders:
            print(f"  OFFENDER {rel}: {why}")
        print(f"audit_public: FAIL — {len(offenders)} offender(s) among {len(files)} tracked paths")
        return 1
    print(f"audit_public: OK — 0 offenders among {len(files)} tracked paths")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
