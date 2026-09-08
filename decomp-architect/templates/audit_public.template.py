#!/usr/bin/env python3
"""audit_public.py — the first-push gate and the CI job: no game-derived bytes among the tracked files.
(Installed by decomp-architect Step 3 as tools/audit_public.py; a generalisation of the source project's audit.)

    tools/audit_public.py                 # every git-tracked file (git ls-files)
    tools/audit_public.py --paths a b …   # an explicit file list (the planted-fixture control; a pre-commit hook)

Everything it forbids is DERIVED from config/firewall.txt — purge rules and hash sources — never from a typed list:
  1. PURGE PATHS — no tracked file lies under a `purge:` prefix or a `glob:` rule.
  2. CONTENT HASH — no tracked file's SHA1 appears in the hash set built from the `required:` / `fixture:` / resolvable
     `pending:` sources (a `.jsonl` manifest with a `sha1` key per line, or sha1sum-format checksum files, globs allowed).
     A renamed copy is caught by content. Zero-length files are exempt by content (an empty payload shares the empty
     file's hash).
  3. SIZE — no tracked file over the host's warning threshold (50 MiB).
  4. DISASSEMBLY-SHAPED CONTENT — no tracked TEXT file carries a long contiguous run of lines shaped like an assembler
     listing, an objdump, a splitter's address/word comment or a label block: the case a path-and-hash audit cannot
     see — a notes file that pastes a function's instructions is game-derived even when the tracked C reproduces the
     bytes. The criterion is the LONGEST CONTIGUOUS run per file (cap 64 lines), so a short quoted diff passes.
Coverage is asserted: a missing `required:` source, zero resolvable sources, or zero purge rules is a FAILURE, never a
pass; a missing `pending:` source is warned loudly. Every count prints with its denominator; exit 1 names every offender.
Negative control: the installer plants the fixture blob and asserts this audit FAILS on it before trusting a PASS.
CI runs it without the game: it reads only tracked text and hashes tracked files.
"""
import fnmatch
import glob as globmod
import hashlib
import json
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
CONFIG = REPO / "config" / "firewall.txt"
SIZE_CAP = 50 * 1024 * 1024
RUN_CAP = 64                      # contiguous disassembly-shaped lines that make a text file an offender
DISASM_RES = [
    # asm-differ-style: `12: addiu      $sp, $sp, -0x40`, `44: nop`, `50: j          .Llabel` — an operand-less mnemonic
    # and a `.L` label operand both continue the run
    re.compile(r"^\s*\d+:\s+[a-z]{2,8}(?:\.[a-z]+)?(?:\s+(?:\$|-?0x|-?\d|[a-z_.])|\s*$)"),
    re.compile(r"^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+\w+"),                             # objdump: `0: 27bdffc0 addiu sp,sp,-64`
    re.compile(r"^\s*/\* [0-9A-F]{4,} [0-9A-F]{8} [0-9A-F]{8} \*/"),                # splitter: `/* OFFSET VRAM WORD */`
    re.compile(r"^(?:glabel|dlabel)\s"),
]


def read_config():
    """Returns (prefixes, globs, required, pending, fixtures). Refuses an absent or empty config (a tool must refuse)."""
    if not CONFIG.exists():
        sys.exit(f"audit_public: {CONFIG.relative_to(REPO)} is missing — nothing to derive the forbidden set from")
    prefixes, globs, required, pending, fixtures = [], [], [], [], []
    for raw in CONFIG.read_text(encoding="utf-8").splitlines():
        ln = raw.split("#", 1)[0].strip()
        if not ln:
            continue
        kind, _, value = ln.partition(":")
        kind, value = kind.strip(), value.strip()
        if kind == "purge":
            prefixes.append(value)
        elif kind == "glob":
            globs.append(value)
        elif kind == "required":
            required.append(value)
        elif kind == "pending":
            pending.append(value)
        elif kind == "fixture":
            fixtures.append(value)
        else:
            sys.exit(f"audit_public: unknown rule kind {kind!r} in {CONFIG.relative_to(REPO)} — refusing to guess")
    if not prefixes and not globs:
        sys.exit("audit_public: no purge rules in config/firewall.txt — refusing to pass on an empty forbidden set")
    return prefixes, globs, required, pending, fixtures


def under_rules(path, prefixes, globs):
    for p in prefixes:
        if path == p or path.startswith(p if p.endswith("/") else p + "/"):
            return p
    for g in globs:
        if fnmatch.fnmatchcase(path, g):
            return "glob:" + g
    return None


def load_hash_source(rel):
    """Every SHA1 a source declares. `.jsonl` = one object per line with a `sha1` key; anything else = sha1sum lines."""
    out = {}
    p = REPO / rel
    if p.suffix == ".jsonl":
        for ln in p.read_text(encoding="utf-8").splitlines():
            if ln.strip():
                o = json.loads(ln)
                out[o["sha1"].lower()] = f"{rel}:{o.get('path', '?')}"
    else:
        for ln in p.read_text(encoding="utf-8").splitlines():
            parts = ln.split()
            if len(parts) >= 2 and len(parts[0]) == 40:
                out[parts[0].lower()] = f"{rel}:{parts[1]}"
    return out


def rom_hashes(required, pending, fixtures):
    """The forbidden hash set, coverage-asserted: every required/fixture source exists and is non-empty; a pending one
    that exists is used, a missing one is warned; zero resolvable sources is a failure."""
    hashes, n_sources = {}, 0
    for kind, sources in (("required", required), ("fixture", fixtures), ("pending", pending)):
        for pattern in sources:
            matches = sorted(globmod.glob(str(REPO / pattern))) if any(c in pattern for c in "*?[") else [str(REPO / pattern)]
            matches = [m for m in matches if pathlib.Path(m).is_file()]
            if not matches:
                if kind == "pending":
                    print(f"audit_public: WARNING pending hash source {pattern} does not exist yet — promote it when its phase creates it")
                    continue
                sys.exit(f"audit_public: {kind} hash source {pattern} is missing — the forbidden set cannot be derived")
            for m in matches:
                rel = pathlib.Path(m).relative_to(REPO).as_posix()
                found = load_hash_source(rel)
                if not found and kind != "pending":
                    sys.exit(f"audit_public: {kind} hash source {rel} holds no hashes — refusing to pass on an empty source")
                hashes.update(found)
                n_sources += 1
    if n_sources == 0:
        sys.exit("audit_public: zero resolvable hash sources — refusing to pass vacuously")
    return hashes, n_sources


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
    """The longest contiguous run of disassembly-shaped lines in a text file; (0, False) for a binary file."""
    with open(path, "rb") as f:
        data = f.read()
    if b"\0" in data[:8192]:
        return 0, False
    text = data.decode("utf-8", errors="replace")
    best = run = 0
    for line in text.splitlines():
        if any(r.match(line) for r in DISASM_RES):
            run += 1
            best = max(best, run)
        else:
            run = 0
    return best, True


def main(argv):
    files = argv[argv.index("--paths") + 1:] if "--paths" in argv else tracked_files()
    prefixes, globs, required, pending, fixtures = read_config()
    hashes, n_sources = rom_hashes(required, pending, fixtures)
    offenders, top_runs = [], []
    n_hashed = n_text = 0
    for rel in files:
        p = REPO / rel
        rule = under_rules(rel, prefixes, globs)
        if rule:
            offenders.append((rel, f"purge path ({rule})"))
        if not p.is_file():          # a submodule gitlink or a file deleted in the worktree — nothing to hash
            continue
        size = p.stat().st_size
        if size > SIZE_CAP:
            offenders.append((rel, f"{size:,} bytes > 50 MiB"))
        if size == 0:
            continue
        h = sha1_of(p)
        n_hashed += 1
        if h in hashes:
            offenders.append((rel, f"game-derived content: sha1 == {hashes[h]}"))
        run, is_text = longest_disasm_run(p)
        if is_text:
            n_text += 1
            if run:
                top_runs.append((run, rel))
            if run >= RUN_CAP:
                offenders.append((rel, f"disassembly-shaped content: {run} contiguous lines (cap {RUN_CAP})"))
    top_runs.sort(reverse=True)
    print(f"audit_public: {len(files)} paths, {n_hashed} files hashed against {len(hashes)} forbidden hashes from "
          f"{n_sources} source(s), {len(prefixes) + len(globs)} purge rules, cap 50 MiB; {n_text} text files scanned for "
          f"disassembly runs (cap {RUN_CAP} lines), longest runs: {', '.join(f'{r} {p}' for r, p in top_runs[:3]) or 'none'}")
    if offenders:
        for rel, why in offenders:
            print(f"  OFFENDER {rel}: {why}")
        print(f"audit_public: FAIL — {len(offenders)} offender(s) among {len(files)} paths")
        return 1
    print(f"audit_public: OK — 0 offenders among {len(files)} paths")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
