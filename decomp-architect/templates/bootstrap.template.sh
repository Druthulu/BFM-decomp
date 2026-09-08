#!/usr/bin/env bash
# tools/bootstrap.sh — fresh-clone setup (installed by decomp-architect Step 5 as a SKELETON; each TODO is a phase task).
# Idempotent; never sudo. What a build needs, in order:
#   1. system packages      — only CHECKED here: the missing ones are printed as one install line.
#   2. the Python venv      — created from the pinned requirements file.
#   3. the submodules       — the assembler shim, the differ, the decompiler, the permuter (Phase 3/4 pin them).
#   4. the vintage compiler — fetched or extracted from a tracked, checksum-verified archive (Phase 4).
#   5. the preflight        — `make check-env`; its exit status is this script's (Phase 3).
# Then: stage your own dump under disks/ and run the extract + fleet-check commands from docs/ops-setup.md.
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO"
say() { printf 'bootstrap: %s\n' "$*"; }

# 1) system packages — presence only; print the install line, never run it.
# TODO(phase-3): fill the list once the toolchain is chosen (binutils for the target, a C preprocessor, clang-format, make,
# the archive tools the extractor needs, python3-venv). TODO(platform): the package names differ per target and per distro.
PKGS="git make python3-venv clang-format"
if command -v dpkg >/dev/null 2>&1; then
    missing=()
    for p in $PKGS; do dpkg -s "$p" >/dev/null 2>&1 || missing+=("$p"); done
    if ((${#missing[@]})); then
        say "MISSING packages (${#missing[@]}) — run this, then re-run bootstrap:"
        printf '  sudo apt-get install -y %s\n' "${missing[*]}"
    else
        say "packages: all present"
    fi
else
    say "no dpkg on this system — install the equivalents of: $PKGS"
fi

# 2) the venv (pinned requirements; the file is created in Phase 1 with the extractor's dependencies)
if [ ! -x .venv/bin/python ]; then
    say "creating .venv"
    python3 -m venv .venv
fi
if [ -f requirements-python.txt ]; then
    say "installing pinned Python requirements (no-op when satisfied)"
    .venv/bin/pip install -q -r requirements-python.txt
else
    say "requirements-python.txt not present yet — TODO(phase-1)"
fi

# 3) submodules (no-op when populated; none until Phase 3 adds the shim, the differ, the decompiler and the permuter)
if [ -f .gitmodules ]; then
    say "submodules: git submodule update --init"
    git submodule update --init
else
    say "no submodules yet — TODO(phase-3)"
fi

# 4) the vintage compiler — TODO(phase-4): verify the tracked archive's checksum (`sha256sum --check`), extract each
#    candidate into its OWN directory, and print the pinned triple from docs/ops-setup.md. Never download without a
#    checksum to verify against; never vendor a compiler whose license forbids it (keep a fetch step + checksum instead).
say "vintage compiler: TODO(phase-4) — nothing to fetch until the candidate ladder exists"

# 5) the preflight (its exit status is ours) — TODO(phase-3): `make check-env` asserts the toolchain executes, the
#    assembler version is the pinned one and the dump's hash matches.
if grep -q '^check-env:' Makefile 2>/dev/null; then
    say "make check-env"
    make --no-print-directory check-env
else
    say "make check-env not present yet — TODO(phase-3); bootstrap ends here"
fi
