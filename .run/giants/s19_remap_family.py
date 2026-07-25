#!/usr/bin/env python3
"""s19_remap_family.py — family_remap + the §77 PREAMBLE CARRY, in one step.

`tools/family_remap.py` substitutes the per-overlay symbols correctly, but its backward preamble
walk carries only a narrow set of constructs: it accepts a line only if it STARTS with
`extern`/`typedef`/comment, so a MULTI-LINE `typedef struct {…} T;` (which ENDS with `} T;`) halts
the walk and loses everything above it — including ordinary `extern` blocks — and the exemplar's
own `#include` lines are never carried at all (§77, three variants measured in Phase 29 SESSION-19).

Rather than hand-patch each sibling (4 rounds of `CC1 FAIL` apiece), this reproduces the exemplar's
FULL file-scope preamble — everything above its function definition — with `family_remap`'s own
printed substitution map applied to it, then appends family_remap's remapped body.

The whole-binary byte-gate remains the sole arbiter (G3/P9): a wrong carry just fails to compile or
fails the gate. Usage:

  s19_remap_family.py --exemplar <b5.c> --addr 0x8017D960 --from ov_SC03_090 \
                      --to ov_SC03_089 --to-addr 0x8017D960 --out <draft.c>
"""
import argparse, re, subprocess, sys, os

REPO = "/home/musashi/bfm-decomp"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--exemplar", required=True)
    ap.add_argument("--addr", required=True)
    ap.add_argument("--frm", required=True)
    ap.add_argument("--to", required=True)
    ap.add_argument("--to-addr", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    tmp = a.out + ".body"
    r = subprocess.run([sys.executable, "tools/family_remap.py", "--addr", a.addr,
                        "--from", a.frm, "--to", a.to, "--to-addr", a.to_addr, "--out", tmp],
                       cwd=REPO, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("family_remap failed:\n" + r.stdout + r.stderr)

    # family_remap prints `remapped N per-overlay symbol(s) A->B: {'X': 'Y', ...}`
    m = re.search(r"\{.*\}", r.stdout, re.S)
    subs = eval(m.group(0)) if m else {}
    print(f"[remap] {len(subs)} symbol substitutions")

    body = open(os.path.join(REPO, tmp)).read().split("\n")
    ex = open(os.path.join(REPO, a.exemplar)).read().split("\n")

    # the exemplar's ENTIRE file-scope preamble = everything above its function definition
    fn_src = f"func_{int(a.addr, 16):08X}"
    i = next(k for k, l in enumerate(ex)
             if re.match(r"^(void|s32|u32|int|s16|u16)\s+" + fn_src + r"\s*\(", l))
    preamble = ex[:i]

    # apply the SAME substitution map to the preamble (its extern block names per-overlay symbols).
    # Longest-first so a shorter name can never corrupt a longer one containing it.
    out = []
    for line in preamble:
        for k in sorted(subs, key=len, reverse=True):
            line = line.replace(k, subs[k])
        out.append(line)

    # keep only family_remap's function body (drop the partial preamble it managed to carry, so the
    # exemplar's complete one is authoritative and nothing is declared twice)
    fn_dst = f"func_{int(a.to_addr, 16):08X}"
    j = next(k for k, l in enumerate(body)
             if re.match(r"^(void|s32|u32|int|s16|u16)\s+" + fn_dst + r"\s*\(", l))

    open(os.path.join(REPO, a.out), "w").write("\n".join(out + body[j:]) + "\n")
    os.remove(os.path.join(REPO, tmp))
    print(f"-> {a.out}  (preamble {len(out)} lines carried + body from line {j})")


if __name__ == "__main__":
    main()
