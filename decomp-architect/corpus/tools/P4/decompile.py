#!/usr/bin/env python3
"""decompile.py — m2c scaffold helper for the BFM matching loop (Phase 6+).

Given a function's splat label (e.g. func_80015A74, main, GameModeDispatch), locate
its disassembly under asm/nonmatchings/ and run m2c (target mipsel-gcc-c) to emit a C
scaffold to stdout. The scaffold is a STARTING POINT only — refine it by hand against
asm-differ until the diff score is 0 (G3), then paste the matched body into src/ in
place of the INCLUDE_ASM stub.

Usage:
    tools/decompile.py <function>                       # m2c scaffold -> stdout
    tools/decompile.py <function> --context src/800.c   # seed m2c with existing C types
    tools/decompile.py <function> --stack-structs       # also emit stack-struct templates

Notes:
  - m2c parses splat's annotated .s natively (no preprocessing needed).
  - For complex functions, Ghidra's decompiler (via MCP get_code) is often a richer
    starting point than m2c; use whichever is closer, then converge with asm-differ.
"""
import argparse
import glob
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
M2C = os.path.join(REPO, "tools", "m2c", "m2c.py")


def find_asm(fn):
    return glob.glob(os.path.join(REPO, "asm", "nonmatchings", "**", fn + ".s"), recursive=True)


def main():
    ap = argparse.ArgumentParser(description="m2c scaffold helper for the BFM matching loop")
    ap.add_argument("function", help="splat function label, e.g. func_80015A74")
    ap.add_argument("--context", help="preprocessed C file to seed m2c types/structs (e.g. src/800.c)")
    ap.add_argument("--target", default="mipsel-gcc-c", help="m2c target (default: mipsel-gcc-c)")
    ap.add_argument("--stack-structs", action="store_true", help="emit stack-struct templates")
    args = ap.parse_args()

    hits = find_asm(args.function)
    if not hits:
        sys.exit(f"decompile.py: no asm/nonmatchings/**/{args.function}.s "
                 f"(is {args.function} still an INCLUDE_ASM stub in src/?)")
    if len(hits) > 1:
        sys.stderr.write(f"decompile.py: {len(hits)} matches, using {hits[0]}\n")

    cmd = [sys.executable, M2C, "-t", args.target, "-f", args.function]
    if args.context:
        cmd += ["--context", args.context]
    if args.stack_structs:
        cmd.append("--stack-structs")
    cmd.append(hits[0])
    sys.exit(subprocess.run(cmd).returncode)


if __name__ == "__main__":
    main()
