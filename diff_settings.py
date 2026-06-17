# asm-differ project config — BFM-decomp (SLUS_007.26, USA, PSX little-endian R3000).
#
# The matching oracle: diff one function's codegen in our build against the
# byte-identical `expected/` baseline. Object mode (-o) is the default workflow:
#   .venv/bin/python tools/asm-differ/diff.py -mo <function>     # -m rebuild, -o vs object
# Score 0 = matched (instruction-identical incl. regalloc); anything else = not matched.
#
# `expected/` is a snapshot of a SHA1-GREEN build (= the original bytes, since the
# all-INCLUDE_ASM build is byte-identical). Re-snapshot it ONLY after a green build
# (`make expected`) — a stale baseline causes phantom matches/regressions (SETUP.md §6.4).
import os

# Per-binary asm-differ images (Phase 9). asm-differ calls apply(config, args) with a fixed
# signature we don't control, so the active binary is selected via the BFM_BINARY env var
# (default main = the retail EXE; a Gen2 binary adds an entry + sets BFM_BINARY=<alias>).
BINARIES = {
    "main": dict(baseimg="expected/build/us/SLUS_007.26.elf",
                 myimg="build/us/SLUS_007.26.elf",
                 mapfile="build/us/SLUS_007.26.map"),
    "resident": dict(baseimg="expected/build/resident/resident.elf",
                     myimg="build/resident/resident.elf",
                     mapfile="build/resident/resident.map"),
    "ov_SC01_077": dict(baseimg="expected/build/ov_SC01_077/ov_SC01_077.elf",
                        myimg="build/ov_SC01_077/ov_SC01_077.elf",
                        mapfile="build/ov_SC01_077/ov_SC01_077.map"),
    "ov_SC01_005": dict(baseimg="expected/build/ov_SC01_005/ov_SC01_005.elf",
                        myimg="build/ov_SC01_005/ov_SC01_005.elf",
                        mapfile="build/ov_SC01_005/ov_SC01_005.map"),
    "ov_SC01_006": dict(baseimg="expected/build/ov_SC01_006/ov_SC01_006.elf",
                        myimg="build/ov_SC01_006/ov_SC01_006.elf",
                        mapfile="build/ov_SC01_006/ov_SC01_006.map"),
    "ov_SC03_001": dict(baseimg="expected/build/ov_SC03_001/ov_SC03_001.elf",
                        myimg="build/ov_SC03_001/ov_SC03_001.elf",
                        mapfile="build/ov_SC03_001/ov_SC03_001.map"),
    "ov_SC01_000": dict(baseimg="expected/build/ov_SC01_000/ov_SC01_000.elf",
                        myimg="build/ov_SC01_000/ov_SC01_000.elf",
                        mapfile="build/ov_SC01_000/ov_SC01_000.map"),
    "ov_SC01_001": dict(baseimg="expected/build/ov_SC01_001/ov_SC01_001.elf",
                        myimg="build/ov_SC01_001/ov_SC01_001.elf",
                        mapfile="build/ov_SC01_001/ov_SC01_001.map"),
    "ov_SC02_000": dict(baseimg="expected/build/ov_SC02_000/ov_SC02_000.elf",
                        myimg="build/ov_SC02_000/ov_SC02_000.elf",
                        mapfile="build/ov_SC02_000/ov_SC02_000.map"),
    "ov_SC02_003": dict(baseimg="expected/build/ov_SC02_003/ov_SC02_003.elf",
                        myimg="build/ov_SC02_003/ov_SC02_003.elf",
                        mapfile="build/ov_SC02_003/ov_SC02_003.map"),
    "ov_SC03_002": dict(baseimg="expected/build/ov_SC03_002/ov_SC03_002.elf",
                        myimg="build/ov_SC03_002/ov_SC03_002.elf",
                        mapfile="build/ov_SC03_002/ov_SC03_002.map"),
    "ov_SC03_006": dict(baseimg="expected/build/ov_SC03_006/ov_SC03_006.elf",
                        myimg="build/ov_SC03_006/ov_SC03_006.elf",
                        mapfile="build/ov_SC03_006/ov_SC03_006.map"),
    "ov_SC04_000": dict(baseimg="expected/build/ov_SC04_000/ov_SC04_000.elf",
                        myimg="build/ov_SC04_000/ov_SC04_000.elf",
                        mapfile="build/ov_SC04_000/ov_SC04_000.map"),
    "ov_SC04_018": dict(baseimg="expected/build/ov_SC04_018/ov_SC04_018.elf",
                        myimg="build/ov_SC04_018/ov_SC04_018.elf",
                        mapfile="build/ov_SC04_018/ov_SC04_018.map"),
    "ov_SC04_019": dict(baseimg="expected/build/ov_SC04_019/ov_SC04_019.elf",
                        myimg="build/ov_SC04_019/ov_SC04_019.elf",
                        mapfile="build/ov_SC04_019/ov_SC04_019.map"),
    "ov_SC05_000": dict(baseimg="expected/build/ov_SC05_000/ov_SC05_000.elf",
                        myimg="build/ov_SC05_000/ov_SC05_000.elf",
                        mapfile="build/ov_SC05_000/ov_SC05_000.map"),
    "ov_SC06_000": dict(baseimg="expected/build/ov_SC06_000/ov_SC06_000.elf",
                        myimg="build/ov_SC06_000/ov_SC06_000.elf",
                        mapfile="build/ov_SC06_000/ov_SC06_000.map"),
    "ov_SC07_000": dict(baseimg="expected/build/ov_SC07_000/ov_SC07_000.elf",
                        myimg="build/ov_SC07_000/ov_SC07_000.elf",
                        mapfile="build/ov_SC07_000/ov_SC07_000.map"),
    # <<< overlays: tools/new_overlay.sh inserts ov_* entries above this line (Phase 13) >>>
}


def apply(config, args):
    _bin = os.environ.get("BFM_BINARY", "main")
    if _bin not in BINARIES:
        raise SystemExit(f"diff_settings: unknown BFM_BINARY={_bin!r} (known: {', '.join(BINARIES)})")
    _cfg = BINARIES[_bin]
    config["arch"] = "mipsel"                                # little-endian MIPS, R3000 (PSX CPU)
    config["baseimg"] = _cfg["baseimg"]                      # image-mode target (byte-identical baseline)
    config["myimg"] = _cfg["myimg"]                          # image-mode current build
    config["mapfile"] = _cfg["mapfile"]                      # GNU ld -Map: symbol -> object + address
    config["map_format"] = "gnu"
    config["expected_dir"] = "expected/"                     # -o: expected path = expected_dir + objpath
    config["build_dir"] = "build/"                           #     (objpath "build/src/800.o" -> expected/build/src/800.o)
    config["source_directories"] = ["src", "asm", "include"]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["makeflags"] = []
