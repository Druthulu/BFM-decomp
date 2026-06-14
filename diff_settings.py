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
def apply(config, args):
    config["arch"] = "mipsel"                                # little-endian MIPS, R3000 (PSX CPU)
    config["baseimg"] = "expected/build/us/SLUS_007.26.elf"  # image-mode target (byte-identical baseline)
    config["myimg"] = "build/us/SLUS_007.26.elf"             # image-mode current build
    config["mapfile"] = "build/us/SLUS_007.26.map"           # GNU ld -Map: symbol -> object + address
    config["map_format"] = "gnu"
    config["expected_dir"] = "expected/"                     # -o: expected path = expected_dir + objpath
    config["build_dir"] = "build/"                           #     (objpath "build/src/800.o" -> expected/build/src/800.o)
    config["source_directories"] = ["src", "asm", "include"]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["makeflags"] = []
