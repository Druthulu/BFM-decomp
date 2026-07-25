#!/usr/bin/env python3
"""s19_remap_tu.py — family_remap + §77 preamble carry, sourcing the exemplar from its OVERLAY TU.

Companion to s19_remap_family.py (which carries the preamble from a standalone draft file). Here the
exemplar is a function already MATCHED inside a big overlay `.c`, so its "file-scope preamble" is the
decl/macro block between the end of the previous top-level function and its own definition line.

Why this is needed at all (§77): `family_remap`'s backward walk accepts a line only if it STARTS with
`extern`/`typedef`/comment, so it halts at the first `#define` (or at the `} T;` line closing a
multi-line typedef) and loses everything above — routinely the externs and gte_* macros the body
needs. The result compiles standalone only by luck.

Also emits the two includes `match_one` does not add (`engine_types.h` carries the lifted structs).

The whole-binary byte-gate remains the sole arbiter (G3/P9).

  s19_remap_tu.py --addr 0x8017E6D8 --frm ov_SC06_018 --to ov_SC06_010 \
                  --to-addr 0x8017DECC --out <draft.c>
"""
import argparse, re, subprocess, sys, os, glob

REPO = "/home/musashi/bfm-decomp"
INC = ('#include "common.h"\n'
       '#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"\n')
DEF = re.compile(r"^(void|s32|u32|int|s16|u16|u8|s8|char|long)\s+%s\s*\(")


def exemplar_preamble(ov, addr):
    """The decl/macro block immediately above the exemplar's definition, in its own TU."""
    name = f"func_{addr:08X}"
    for f in glob.glob(os.path.join(REPO, f"src/{ov}/*.c")):
        L = open(f).read().split("\n")
        pat = DEF.pattern % name
        d = next((i for i, l in enumerate(L) if re.match(pat, l)), None)
        if d is None:
            continue
        s = d
        while s > 0 and not (L[s - 1].startswith("}") and s - 1 < d - 1):
            s -= 1
        return L[s:d], f
    raise SystemExit(f"exemplar {name} not defined in src/{ov}/")


def main():
    ap = argparse.ArgumentParser()
    for a in ("addr", "frm", "to", "to-addr", "out"):
        ap.add_argument("--" + a, required=True)
    a = ap.parse_args()
    src, dst = int(a.addr, 16), int(a.to_addr, 16)

    tmp = a.out + ".body"
    r = subprocess.run([sys.executable, "tools/family_remap.py", "--addr", a.addr, "--from", a.frm,
                        "--to", a.to, "--to-addr", a.to_addr, "--out", tmp],
                       cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("family_remap failed:\n" + r.stdout + r.stderr)
    m = re.search(r"\{.*\}", r.stdout, re.S)
    subs = eval(m.group(0)) if m else {}

    pre, tu = exemplar_preamble(a.frm, src)
    out = []
    for line in pre:
        for k in sorted(subs, key=len, reverse=True):       # longest-first: a short name can
            line = line.replace(k, subs[k])                 # never corrupt a longer one
        out.append(line)

    body = open(os.path.join(REPO, tmp)).read().split("\n")
    j = next(i for i, l in enumerate(body) if re.match(DEF.pattern % f"func_{dst:08X}", l))
    open(os.path.join(REPO, a.out), "w").write(INC + "\n" + "\n".join(out + body[j:]) + "\n")
    os.remove(os.path.join(REPO, tmp))
    print(f"[{a.to}] func_{dst:08X}: {len(subs)} subs, preamble {len(out)}L from {os.path.basename(tu)}")


if __name__ == "__main__":
    main()
