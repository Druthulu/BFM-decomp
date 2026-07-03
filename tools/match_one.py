#!/usr/bin/env python3
"""Per-function matching check: compile ONE function's C standalone (the pinned triple), mask
relocations (jal/j 26-bit + HI16/LO16 immediates, like psyq_identify), and compare to the target
bytes in its splat .s. Fully isolated (own temp dir) so many run in PARALLEL with no shared build --
a real asm-differ loop for an agent to iterate against.

Prints "MATCH (N ins)" on a byte-exact (relocation-masked) match, else a per-instruction diff.
gcc-2.7.2 -O2 compiles each global function independently (no cross-TU inlining of externs), so a
standalone match == the whole-binary byte-gate for that function -- MODULO in-TU declaration
conflicts (def-side loose-typing) and -O0 subsegments; ALWAYS finish on the whole-binary gate (G3/P9).

The masking + objdump live in tools/masked_diff.py (shared with the permuter's MaskedScorer). NOTE
(Phase 24 T2): objdump is now `-drz`, NOT `-dr` -- `-z` keeps runs of nops so GTE-heavy seeds are no
longer under-counted (func_80132784 now reads its true 400 ins, not 384).

  python3 tools/match_one.py func_800D1DB0                 # uses .run/drafts3|2|/<fn>.c
  python3 tools/match_one.py func_800D1DB0 --c /path/to.c  # explicit C file
"""
import subprocess, re, sys, os, argparse
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import masked_diff

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('fn')
ap.add_argument('--c', help='C file (externs + the function def). Default: search .run/drafts3|2|/')
ap.add_argument('--asm-subdir', default='asm/resident/nonmatchings/resident')
ap.add_argument('--work', default='.run/match')
a = ap.parse_args()

CPP = 'mipsel-linux-gnu-cpp'; CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'
MASPSX = 'tools/maspsx/maspsx.py'; AS = 'mipsel-linux-gnu-as'; PY = '.venv/bin/python'
CPPFLAGS = '-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
CC1FLAGS = '-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'.split()
ASFLAGS = '-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0'.split()

cfile = a.c
if not cfile:
    for d in ('.run/drafts3', '.run/drafts2', '.run/drafts'):
        if os.path.exists('%s/%s.c' % (d, a.fn)):
            cfile = '%s/%s.c' % (d, a.fn); break
if not cfile or not os.path.exists(cfile):
    print('FAIL: no C file for', a.fn); sys.exit(2)

wd = '%s/%s' % (a.work, a.fn); os.makedirs(wd, exist_ok=True)
src = open(cfile).read()
# strip inline scalar-typedef redefinitions (common.h provides them; C89 rejects the dup)
src = masked_diff.SCALAR_TYPEDEF_RE.sub('', src)
if '#include "common.h"' not in src:
    src = '#include "common.h"\n' + src
open('%s/t.c' % wd, 'w').write(src)


def pipe(cmd, data=None):
    return subprocess.run(cmd, input=data, capture_output=True)


p = pipe([CPP] + CPPFLAGS + ['%s/t.c' % wd])
if p.returncode: print('CPP FAIL\n' + p.stderr.decode()[-1500:]); sys.exit(1)
p = pipe([CC1] + CC1FLAGS, p.stdout)
if p.returncode: print('CC1 FAIL\n' + p.stderr.decode()[-1800:]); sys.exit(1)
p = pipe([PY, MASPSX, '--aspsx-version=2.56', '--expand-div'], p.stdout)
if p.returncode: print('MASPSX FAIL\n' + p.stderr.decode()[-1500:]); sys.exit(1)
p = pipe([AS] + ASFLAGS + ['-o', '%s/t.o' % wd], p.stdout)
if p.returncode: print('AS FAIL\n' + p.stderr.decode()[-1500:]); sys.exit(1)

# masked compare: my compiled object vs the resolved splat .s (mask driven by my object's relocs)
mine = masked_diff.insns_from_object('%s/t.o' % wd, a.fn)
tgt = masked_diff.insns_from_s('%s/%s.s' % (a.asm_subdir, a.fn))

if not mine:
    print('FAIL: my object has no function', a.fn, '(compile produced nothing?)'); sys.exit(1)

n = max(len(mine), len(tgt))
diffs = []
for i in range(n):
    mw = mine[i]['word'] if i < len(mine) else None
    mask = masked_diff.mask_for(mine[i]['word'], mine[i]['reloc_kind']) if i < len(mine) else 0xFFFFFFFF
    me = (mw & mask) if mw is not None else None
    tg = (tgt[i]['word'] & mask) if i < len(tgt) else None
    if me != tg:
        diffs.append((i,
                      ('%08x %s' % (mine[i]['word'], mine[i]['mnem'])) if i < len(mine) else '--',
                      ('%08x %s' % (tgt[i]['word'], tgt[i]['mnem'])) if i < len(tgt) else '--'))

if not diffs and len(mine) == len(tgt):
    print('MATCH (%d ins)  %s' % (len(mine), a.fn))
    sys.exit(0)
print('DIFF  %s   mine=%d ins, target=%d ins, %d mismatched' % (a.fn, len(mine), len(tgt), len(diffs)))
print('  idx | MINE                          | TARGET')
for i, me, tg in diffs[:40]:
    print('  %3d | %-28s | %s' % (i, me, tg))
sys.exit(1)
