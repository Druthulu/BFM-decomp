#!/usr/bin/env bash
# tools/fetch_psyq.sh — OPTIONAL: obtain Sony's PsyQ SDK pieces and build the ELF object dirs that main's link
# swaps in for its INCLUDE_ASM library tiles (P33 B4). The build is byte-identical WITHOUT any of this
# (`make sdk-dual` proves both legs); this only makes `make check BINARY=main` link Sony's REAL objects.
# The repository redistributes none of it (tools/psyq/ is gitignored); every artifact is verified against
# tools/psyq_CHECKSUMS.sha256 before use (rows are relative to tools/psyq/).
#
#   tools/fetch_psyq.sh [--disc <RTL-4.0 "(Track 1).bin">] [--from <dir with the 20 *.LIB>] [--no-build]
#
# What is needed, and where it comes from:
#   psyq-obj-parser          decomp.me's release tarball (URL below); tarball + binary sha256 recorded.
#   RTL 4.2 + libpad 4.2.1   archive.org (URL below) -> tools/psyq/lib421/ (the J421PD.ZIP payload: LIBPAD.LIB 4.2.1
#                            + LIBAPI.LIB 4.2) -> .run/obj42/{libpad421,libapi42}.
#   PsyQ 4.0 libraries (20)  NO public URL. They are PSX/LIB/*.LIB on the redump disc "PlayStation - Programmer
#                            Tools - Run-time Library 4.0 (USA) (PC-CD ROM Release 2.0)" (DTL-S2002, volume
#                            PROGTOOL): pass its Track-1 .bin with --disc (tools/psyq_libs_from_disc.py extracts
#                            them with the project's own ISO walker) or a directory holding the 20 files with
#                            --from. Without either, and without tools/psyq/lib40/ already present, this REFUSES.
# Then the existing builders run — psyq_build_libs.sh (10 libs -> .run/obj40/<lib>), make_libgs.sh
# (.run/obj40/libgs_used), make_snd_used.py (.run/obj40/snd_used), the lib421 ELF step, make_apicard_used.py
# (.run/obj42/apicard_used) — and `make -j$(nproc) sdk-dual` proves main byte-identical WITH and WITHOUT them.
set -euo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO"
say() { printf 'fetch_psyq: %s\n' "$*"; }
die() { printf 'fetch_psyq: %s\n' "$*" >&2; exit 1; }

PARSER_URL='https://github.com/decompme/compilers/releases/download/compilers/psyq-obj-parser.tar.gz'
RTL42_URL='https://archive.org/download/play-station-programmer-tool-runtime-library-version-4.2.7z/PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z'
RTL42='PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z'
CK="$REPO/tools/psyq_CHECKSUMS.sha256"
PSYQ="$REPO/tools/psyq"
SCRATCH="$REPO/.run/psyq_fetch"
DISC=""; FROM=""; BUILD=1
while [ $# -gt 0 ]; do
    case "$1" in
        --disc) DISC="$2"; shift 2 ;;
        --from) FROM="$2"; shift 2 ;;
        --no-build) BUILD=0; shift ;;
        -h|--help) sed -n '2,24p' "$0"; exit 0 ;;
        *) die "unknown argument: $1 (see --help)" ;;
    esac
done
mkdir -p "$PSYQ" "$SCRATCH"

# verify ONE row of the checksum file for a path relative to tools/psyq/ (exit 1 on mismatch or no row)
ck1() {
    local rel="$1"
    local want; want=$(grep -E "  $rel\$" "$CK" | awk '{print $1}' | head -1)
    [ -n "$want" ] || die "no checksum row for $rel in $CK"
    local got; got=$(sha256sum "$PSYQ/$rel" | awk '{print $1}')
    [ "$got" = "$want" ] || die "sha256 MISMATCH for tools/psyq/$rel: got $got, recorded $want — refusing to use it"
    say "verified tools/psyq/$rel"
}
fetch() {  # url -> tools/psyq/<name>, unless a verified copy is already there
    local url="$1" name="$2"
    if [ -f "$PSYQ/$name" ] && ck1 "$name" 2>/dev/null; then return 0; fi
    say "downloading $name"
    curl -fL --retry 3 --max-time 600 -o "$PSYQ/$name.part" "$url"
    mv "$PSYQ/$name.part" "$PSYQ/$name"
    ck1 "$name"
}

# 1) psyq-obj-parser (the .OBJ -> ELF converter every builder needs)
if [ -x "$PSYQ/psyq-obj-parser" ] && ck1 psyq-obj-parser 2>/dev/null; then
    :
else
    fetch "$PARSER_URL" psyq-obj-parser.tar.gz
    tar xzf "$PSYQ/psyq-obj-parser.tar.gz" -C "$SCRATCH"
    p=$(find "$SCRATCH" -type f -name psyq-obj-parser | head -1)
    [ -n "$p" ] || die "psyq-obj-parser not found inside the tarball"
    install -m 0755 "$p" "$PSYQ/psyq-obj-parser"
    ck1 psyq-obj-parser
fi

# 2) the Runtime Library 4.2 archive -> lib421/ (LIBPAD.LIB 4.2.1 + LIBAPI.LIB 4.2)
fetch "$RTL42_URL" "$RTL42"
if [ ! -f "$PSYQ/lib421/LIBPAD.LIB" ] || [ ! -f "$PSYQ/lib421/LIBAPI.LIB" ]; then
    command -v 7z >/dev/null || die "7z not found (apt: p7zip-full)"
    rm -rf "$SCRATCH/rtl42"; 7z x -y -bd -o"$SCRATCH/rtl42" "$PSYQ/$RTL42" >/dev/null
    z=$(find "$SCRATCH/rtl42" -iname 'J421PD.ZIP' | head -1)
    [ -n "$z" ] || die "LIB/42PATCH/J421PD.ZIP not found inside $RTL42"
    mkdir -p "$PSYQ/lib421"; unzip -o -q "$z" -d "$PSYQ/lib421"
fi
ck1 lib421/LIBPAD.LIB; ck1 lib421/LIBAPI.LIB

# 3) the 20 PsyQ 4.0 libraries -> lib40/
need40=0
for L in LIBAPI LIBC LIBC2 LIBCARD LIBCD LIBCOMB LIBDS LIBETC LIBGPU LIBGS LIBGTE LIBGUN LIBMATH LIBMCRD LIBPRESS LIBSIO LIBSN LIBSND LIBSPU LIBTAP; do
    [ -f "$PSYQ/lib40/$L.LIB" ] || need40=1
done
if [ "$need40" = 1 ]; then
    if [ -n "$DISC" ]; then
        say "extracting PSX/LIB/*.LIB from the Run-time Library 4.0 disc"
        python3 tools/psyq_libs_from_disc.py "$DISC" "$PSYQ/lib40" >/dev/null
    elif [ -n "$FROM" ]; then
        mkdir -p "$PSYQ/lib40"; cp "$FROM"/*.LIB "$PSYQ/lib40/"
    else
        die "the PsyQ 4.0 libraries are not present and have no public download. They are PSX/LIB/*.LIB on the redump disc
  \"PlayStation - Programmer Tools - Run-time Library 4.0 (USA) (PC-CD ROM Release 2.0)\" (DTL-S2002, volume PROGTOOL):
  re-run with --disc \"<that disc's (Track 1).bin>\" or --from <a directory holding the 20 .LIB files>.
  (Not needed for byte-identity: without them main links its INCLUDE_ASM tiles and still matches.)"
    fi
fi
for L in LIBAPI LIBC LIBC2 LIBCARD LIBCD LIBCOMB LIBDS LIBETC LIBGPU LIBGS LIBGTE LIBGUN LIBMATH LIBMCRD LIBPRESS LIBSIO LIBSN LIBSND LIBSPU LIBTAP; do
    ck1 "lib40/$L.LIB" >/dev/null
done
say "verified the 20 PsyQ 4.0 libraries in tools/psyq/lib40/"

[ "$BUILD" = 1 ] || { say "--no-build: SDK pieces in place, nothing built"; exit 0; }

# 4) the builders (all regenerable; outputs under .run/obj40, .run/obj42, tools/psyq/lib40_elf)
say "psyq_build_libs.sh (10 libraries -> .run/obj40/<lib>)"
tools/psyq_build_libs.sh LIBCD LIBETC LIBGPU LIBMCRD LIBC2 LIBGTE LIBGS LIBSPU LIBSND LIBCARD
say "make_libgs.sh (-> .run/obj40/libgs_used)"
tools/make_libgs.sh >/dev/null
say "make_snd_used.py (-> .run/obj40/snd_used)"
python3 tools/make_snd_used.py >/dev/null
say "lib421 -> .run/obj42/{libpad421,libapi42}"
for pair in LIBPAD:libpad421 LIBAPI:libapi42; do
    L=${pair%%:*}; d=".run/obj42/${pair##*:}"
    rm -rf "$d"; mkdir -p "$d"
    python3 tools/psyq_lib_split.py "$PSYQ/lib421/$L.LIB" "$d" >/dev/null
    for o in "$d"/*.obj; do "$PSYQ/psyq-obj-parser" "$o" -o "${o%.obj}.o" >/dev/null 2>&1 || true; done
done
say "make_apicard_used.py (-> .run/obj42/apicard_used)"
python3 tools/make_apicard_used.py >/dev/null

# 5) prove both legs
say "make -j$(nproc) sdk-dual"
make --no-print-directory -j"$(nproc)" sdk-dual
say "OK — the SDK object dirs are in place and main is byte-identical WITH and WITHOUT them"
