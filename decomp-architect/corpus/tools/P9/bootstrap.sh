#!/usr/bin/env bash
# tools/bootstrap.sh — fresh-clone setup for BFM-decomp (P33 B3). Idempotent; never sudo.
#
# What a build needs, in order (docs/SETUP.md §4):
#   1. apt packages (§4.5)   — only CHECKED here: the missing ones are printed as one install line.
#   2. the Python venv (§4.6) — created from requirements-python.txt (pinned; pycparser < 3.0).
#   3. the four submodules   — maspsx (a build input), asm-differ, m2c, decomp-permuter.
#   4. the two vintage cc1s (§4.7) — the tracked old-gcc 0.17 tarballs, sha256-verified, each
#      extracted into its OWN subdir (they are flat and share file names).
#   5. `make check-env`      — the preflight; its exit status is this script's.
# Then: stage your redump dump under disks/ and run `make disc-extract && make extract-all && make check-all`.
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO"
say() { printf 'bootstrap: %s\n' "$*"; }

# 1) apt packages — presence only (dpkg); print the install line, never run it.
PKGS="bchunk binutils-mipsel-linux-gnu bsdmainutils clang-format coreutils curl gcc-mipsel-linux-gnu git libelf-dev make ninja-build p7zip-full python3-pip python3-venv unzip wget"
if command -v dpkg >/dev/null 2>&1; then
    missing=()
    for p in $PKGS; do dpkg -s "$p" >/dev/null 2>&1 || missing+=("$p"); done
    if ((${#missing[@]})); then
        say "MISSING apt packages (${#missing[@]}) — run this, then re-run bootstrap:"
        printf '  sudo apt-get install -y %s\n' "${missing[*]}"
    else
        say "apt packages: all present"
    fi
else
    say "no dpkg on this system — install the equivalents of: $PKGS"
fi

# 2) the venv (Python >= 3.12; pinned requirements)
if [ ! -x .venv/bin/python ]; then
    say "creating .venv"
    python3 -m venv .venv
fi
say "installing pinned Python requirements (no-op when satisfied)"
.venv/bin/pip install -q -r requirements-python.txt

# 3) submodules (no-op when populated)
say "submodules: git submodule update --init"
git submodule update --init

# 4) the vintage compilers: verify the tracked tarballs, extract each into its own dir once
say "cc1 tarballs: sha256sum --check tools/bin/CHECKSUMS.sha256"
( cd tools/bin && sha256sum --check --quiet CHECKSUMS.sha256 )
for v in psx cdk; do
    if [ ! -x "tools/bin/gcc-2.7.2-$v/cc1" ]; then
        say "extracting tools/bin/gcc-2.7.2-$v.tar.gz -> tools/bin/gcc-2.7.2-$v/"
        mkdir -p "tools/bin/gcc-2.7.2-$v"
        tar xzf "tools/bin/gcc-2.7.2-$v.tar.gz" -C "tools/bin/gcc-2.7.2-$v"
    else
        say "cc1 present: tools/bin/gcc-2.7.2-$v/cc1"
    fi
done

# 5) the preflight (its exit status is ours)
say "make check-env"
make --no-print-directory check-env
