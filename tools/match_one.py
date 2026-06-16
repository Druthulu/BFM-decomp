#!/usr/bin/env python3
"""Per-function matching check: compile ONE function's C standalone (the pinned triple),
mask relocations (jal/j 26-bit + HI16/LO16 immediates, like psyq_identify), and compare to
the target bytes embedded in its splat .s. Fully isolated (own temp dir) so many run in
PARALLEL with no shared build -- a real asm-differ loop for an agent to iterate against.

Prints "MATCH (N ins)" on a byte-exact (relocation-masked) match, else a per-instruction diff.
gcc-2.7.2 -O2 compiles each global function independently (no cross-TU inlining of externs),
so a standalone match == the whole-binary byte-gate for that function.

  python3 tools/match_one.py func_800D1DB0                 # uses .run/drafts3|2|/<fn>.c
  python3 tools/match_one.py func_800D1DB0 --c /path/to.c  # explicit C file
"""
import subprocess, re, sys, os, struct, argparse

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('fn')
ap.add_argument('--c', help='C file (externs + the function def). Default: search .run/drafts3|2|/')
ap.add_argument('--asm-subdir', default='asm/resident/nonmatchings/resident')
ap.add_argument('--work', default='.run/match')
a = ap.parse_args()

CPP = 'mipsel-linux-gnu-cpp'; CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'
MASPSX = 'tools/maspsx/maspsx.py'; AS = 'mipsel-linux-gnu-as'; PY = '.venv/bin/python'
OBJDUMP = 'mipsel-linux-gnu-objdump'
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
src = re.sub(r'^[ \t]*typedef\b.*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64)[ \t]*;[ \t]*\n', '', src, flags=re.M)
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


def my_insns(obj, fn):
    """objdump the function; return (words, masks, mnemonics). mask=0 on jal/j 26-bit,
    0xFFFF0000 on HI16/LO16 reloc immediates, else 0xFFFFFFFF."""
    d = subprocess.run([OBJDUMP, '-dr', '-j', '.text', obj], capture_output=True, text=True).stdout
    words, masks, mnem = [], [], []
    infn = False
    for line in d.splitlines():
        h = re.match(r'^[0-9a-f]+ <([^>]+)>:', line)
        if h:
            infn = (h.group(1) == fn); continue
        if not infn:
            continue
        mi = re.match(r'\s+([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)', line)
        if mi:
            w = int(mi.group(2), 16)
            words.append(w); mnem.append(mi.group(3).strip())
            masks.append(0 if (w >> 26) in (2, 3) else 0xFFFFFFFF)
        elif 'R_MIPS' in line and words:
            masks[-1] = 0 if '_26' in line else 0xFFFF0000
    return words, masks, mnem


def target_insns(fn):
    """parse the splat .s: each  /* off vaddr LEHEX */ mnemonic  line -> (word, mnemonic)."""
    words, mnem = [], []
    for line in open('%s/%s.s' % (a.asm_subdir, fn)):
        mi = re.match(r'\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s+(.*)', line)
        if mi:
            words.append(struct.unpack('<I', bytes.fromhex(mi.group(1)))[0])
            mnem.append(re.sub(r'\s+', ' ', mi.group(2).strip()))
    return words, mnem


mw, mask, mmn = my_insns('%s/t.o' % wd, a.fn)
tw, tmn = target_insns(a.fn)

if not mw:
    print('FAIL: my object has no function', a.fn, '(compile produced nothing?)'); sys.exit(1)

n = max(len(mw), len(tw))
diffs = []
for i in range(n):
    me = (mw[i] & mask[i]) if i < len(mw) else None
    tg = (tw[i] & (mask[i] if i < len(mask) else 0xFFFFFFFF)) if i < len(tw) else None
    if me != tg:
        diffs.append((i,
                      ('%08x %s' % (mw[i], mmn[i])) if i < len(mw) else '--',
                      ('%08x %s' % (tw[i], tmn[i])) if i < len(tw) else '--'))

if not diffs and len(mw) == len(tw):
    print('MATCH (%d ins)  %s' % (len(mw), a.fn))
    sys.exit(0)
print('DIFF  %s   mine=%d ins, target=%d ins, %d mismatched' % (a.fn, len(mw), len(tw), len(diffs)))
print('  idx | MINE                          | TARGET')
for i, me, tg in diffs[:40]:
    print('  %3d | %-28s | %s' % (i, me, tg))
sys.exit(1)
