#!/usr/bin/env python3
"""audit_public.py — the first-push gate: no ROM-derived bytes among the tracked files (P33 B7; CI job `audits`;
extended P33.5 task 8).

    tools/audit_public.py                 # every git-tracked file at HEAD's index (git ls-files)
    tools/audit_public.py --paths a b …   # an explicit file list (tests / a pre-commit hook)

Four checks, each derived from something the repo already asserts (R33), never from a typed list of hashes:
  1. PURGE PATHS — no tracked file lies under a rule of tools/public_rewrite/purge_set.txt (the C1 rewrite's own input,
     filter-repo syntax: bare prefix or `glob:`) OR of tools/public_rewrite/untracked_after_rewrite.txt (the audit-only
     sibling: paths untracked AFTER the rewrite without a second rewrite — kept out of purge_set.txt because gate_scan.py
     reads that file as the census of what the rewrite removed from history).
  2. ROM CONTENT — no tracked file's SHA1 is a known ROM-derived hash: every `sha1` in extracted/retail/manifest.jsonl
     (the manifest IS the list of ROM-derived artifacts), every binary's SHA1 in config/check.*.sha, and the redump
     Track-1 SHA1 (tools/bfm_extract/extract_exe.REDUMP_TRACK1_SHA1). A renamed copy is caught by content.
  3. SIZE — no tracked file over 50 MiB (GitHub's warning threshold; nothing legitimately tracked is near it).
  4. CONTENT — no tracked TEXT file carries a long contiguous run of disassembly-shaped lines (an assembler listing, an
     objdump, a splat `/* ADDR HEX hex */` block, a glabel block): the class-3 case a path-and-hash audit cannot see —
     a notes file that pastes a function's instructions is ROM-derived even when the tracked C reproduces the bytes.
     The shapes were derived from the two offenders the P33.5 audit found; the criterion is the LONGEST CONTIGUOUS run
     per file, threshold 64 lines, so a short quoted diff in a cookbook section passes and a full listing does not.
Prints every count with its denominator (R41) and exits 1 on any offender, naming each (R43: loud, never partial).
Ubuntu CI runs it without the disc, asm/, expected/ or build/ — it reads only tracked text and hashes tracked files.
Controls (R39): S87 (before C3) the private tree MUST fail naming exactly the purge set (28 dumps, the EXE, ghidra/**,
tools/psyq/**, the 3 session-archive parts, 2 zips, brave.exe); P33.5 task 8: before the pair was untracked, check 4 MUST
name exactly .run/giants/fable_cd4/{mine_full,target_full}.txt and nothing else (the xsig fixtures, 40 lines, pass).
"""
import fnmatch
import hashlib
import json
import os
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
PURGE = REPO / "tools" / "public_rewrite" / "purge_set.txt"
UNTRACKED_AFTER = REPO / "tools" / "public_rewrite" / "untracked_after_rewrite.txt"
MANIFEST = REPO / "extracted" / "retail" / "manifest.jsonl"
SIZE_CAP = 50 * 1024 * 1024
RUN_CAP = 64                      # contiguous disassembly-shaped lines that make a text file an offender
DISASM_RES = [
    # asm-differ: `12: addiu      $sp, $sp, -0x40`, `44: nop`, `50: j          .L80133D40` (an operand-less mnemonic and a
    # `.L` label operand both continue the run — `nop` lines broke the first cut's run on the target listing, 60 < 64)
    re.compile(r"^\s*\d+:\s+[a-z]{2,8}(?:\.[a-z]+)?(?:\s+(?:\$|-?0x|-?\d|[a-z_.])|\s*$)"),
    re.compile(r"^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+\w+"),                             # objdump / `0: 27bdffc0 addiu sp,sp,-64`
    re.compile(r"^\s*/\* [0-9A-F]{4,} [0-9A-F]{8} [0-9A-F]{8} \*/"),                # splat: `/* 1A2B0 80018730 27BDFFC0 */`
    re.compile(r"^(?:glabel|dlabel)\s"),
]


def read_rules(path, label):
    """filter-repo syntax; refuses regex: rules and an empty file (R43). Returns (prefixes, globs)."""
    if not path.exists():
        sys.exit(f"audit_public: {path.relative_to(REPO)} is missing — cannot derive the {label} rules (R32)")
    prefixes, globs = [], []
    for ln in path.read_text(encoding="utf-8").splitlines():
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
        sys.exit(f"audit_public: {path.relative_to(REPO)} holds no rules — refusing to pass on an empty {label} set (R43)")
    return prefixes, globs


def under_rules(path, prefixes, globs):
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


def longest_disasm_run(path):
    """The longest contiguous run of disassembly-shaped lines in a text file; 0 for a binary file."""
    with open(path, "rb") as f:
        data = f.read()
    if b"\0" in data[:8192]:
        return 0, False
    text = data.decode("utf-8", errors="replace")
    best = run = 0
    for line in text.splitlines():
        if any(r.match(line) for r in DISASM_RES):
            run += 1
            if run > best:
                best = run
        else:
            run = 0
    return best, True


def main(argv):
    if "--paths" in argv:
        files = argv[argv.index("--paths") + 1:]
    else:
        files = tracked_files()
    p_prefixes, p_globs = read_rules(PURGE, "purge")
    u_prefixes, u_globs = read_rules(UNTRACKED_AFTER, "untracked-after-rewrite")
    hashes, n_manifest, n_checks = rom_hashes()
    offenders = []
    n_hashed = n_text = 0
    top_runs = []
    for rel in files:
        p = REPO / rel
        rule = under_rules(rel, p_prefixes, p_globs)
        if rule:
            offenders.append((rel, f"purge path ({rule})"))
        rule = under_rules(rel, u_prefixes, u_globs)
        if rule:
            offenders.append((rel, f"untracked-after-rewrite path ({rule})"))
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
        run, is_text = longest_disasm_run(p)
        if is_text:
            n_text += 1
            if run:
                top_runs.append((run, rel))
            if run >= RUN_CAP:
                offenders.append((rel, f"disassembly-shaped content: {run} contiguous lines (cap {RUN_CAP})"))
    top_runs.sort(reverse=True)
    print(f"audit_public: {len(files)} tracked paths, {n_hashed} files hashed against {len(hashes)} ROM hashes "
          f"({n_manifest} manifest rows + {n_checks} check.*.sha + redump), "
          f"{len(p_prefixes) + len(p_globs)} purge rules + {len(u_prefixes) + len(u_globs)} untracked-after-rewrite rules, "
          f"cap 50 MiB; {n_text} text files scanned for disassembly runs (cap {RUN_CAP} lines), "
          f"longest runs: {', '.join(f'{r} {p}' for r, p in top_runs[:3]) or 'none'}")
    if offenders:
        for rel, why in offenders:
            print(f"  OFFENDER {rel}: {why}")
        print(f"audit_public: FAIL — {len(offenders)} offender(s) among {len(files)} tracked paths")
        return 1
    print(f"audit_public: OK — 0 offenders among {len(files)} tracked paths")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
