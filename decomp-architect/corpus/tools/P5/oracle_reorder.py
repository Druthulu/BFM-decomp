#!/usr/bin/env python3
"""oracle_reorder.py — decide whether a NEAR residual is a C defect or an ASSEMBLER artifact.

WHY (P31 S53, cookbook §188). The `jr $ra` + `addiu $sp` epilogue tail — and unfilled branch delay
slots generally — are produced by GNU `as` at `-O2`, NOT by cc1. The project pins `ASFLAGS -O1`
(Makefile:563) and maspsx force-emits `.set noreorder` after every `.ent`
(tools/maspsx/maspsx/__init__.py:856-859), so under the pinned triple that shape is UNREACHABLE from
any C source. A draft can therefore be perfectly correct and still sit at a stubborn residual.

THE DIAGNOSTIC: re-assemble the SAME draft two ways and compare.
  maspsx + as -O1  (the pinned path)      -> the residual you already see
  bypass  + as -O2 (maspsx skipped)       -> if this is 0 diffs, THE C IS ALREADY RIGHT
A 0 in the second cell means the C IS ALREADY RIGHT under a reorder-mode assembler.

*** CORRECTED P31 S76 — READ THIS BEFORE CONCLUDING "WALL". ***
This file used to end that sentence with "file IMMOVABLE, stop grinding, no C-level work can ever
close it", and the header above still says the shape is "UNREACHABLE from any C source". That was
true when it was written and is now FALSE FOR FOUR TUs. On 2026-09-01 the build gained a reorder
island: `REORDER_TUS := 800c2 800c2_2 800c2_3 800c3` in the Makefile pipes those TUs through
`tools/reorder_passthrough.py` into `as -O2` (ASFLAGS_REORDER) instead of maspsx + `as -O1`. For a
function in one of them, a 0 here does NOT mean immovable — it means THE DRAFT WILL BANK, because
the second cell IS the project's real build path for that file.

Measured S76: seven main drafting agents in one wave hit the epilogue residual, ran this oracle,
read the old wording, and each submitted a §265 verbatim-asm body instead of the plain C the build
would have accepted. `match_one` now selects the reorder path automatically for those TUs (deriving
the list from the Makefile), so the phantom residual no longer appears. Same draft, func_8005ECC0:
closeness 5 / 36 ins under maspsx, closeness 2 / 35 ins under reorder — the whole epilogue drift was
the oracle, not the compiler.
Measured on func_80061FA8 (target 103 ins): pinned 57 diffs/106 ins; bypass+-O2 0 diffs/103 ins.

Promoted verbatim from .run/wave_p31r/oracle61.py because a cookbook section may not cite evidence
that lives under a gitignored path (the verifier that found this flagged exactly that).
"""
"""Byte-exact oracle for the 0x8005D000-0x80062600 PsyQ island: cpp -> cc1 -> (move->addu) -> as -O2.
Reproduces the ORIGINAL assembler's reorder-mode delay-slot swapping, which maspsx (forced
`.set noreorder`) + the pinned `as -O1` cannot emit. Diagnostic only -- NOT the project gate."""
import subprocess,sys,re,os
sys.path.insert(0,'tools'); import masked_diff
CPP='mipsel-linux-gnu-cpp'; CC1='tools/bin/gcc-2.7.2-psx/cc1'; AS='mipsel-linux-gnu-as'
CPPFLAGS='-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
CC1FLAGS='-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'.split()
ASFLAGS='-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O2 -G0'.split()
cfile,fn,sub=sys.argv[1],sys.argv[2],sys.argv[3]
wd='.run/match/oracle61'; os.makedirs(wd,exist_ok=True)
s=masked_diff.strip_scalar_typedefs(open(cfile).read())
if '#include "common.h"' not in s: s='#include "common.h"\n'+s
open(wd+'/t.c','w').write(s)
p=subprocess.run([CPP]+CPPFLAGS+[wd+'/t.c'],capture_output=True)
assert not p.returncode,p.stderr.decode()[-1500:]
q=subprocess.run([CC1]+CC1FLAGS,input=p.stdout,capture_output=True)
assert not q.returncode,q.stderr.decode()[-2500:]
asm=re.sub(r'\tmove\t(\$\w+),(\$\w+)', lambda m:'\taddu\t%s,%s,$0'%(m.group(1),m.group(2)), q.stdout.decode())
r=subprocess.run([AS]+ASFLAGS+['-o',wd+'/t.o'],input=asm.encode(),capture_output=True)
assert not r.returncode,r.stderr.decode()[-1500:]
mine=masked_diff.insns_from_object(wd+'/t.o',fn); tgt=masked_diff.insns_from_s('%s/%s.s'%(sub,fn))
d=masked_diff.structured_diff(mine,tgt)
print('ORACLE %s mine=%d tgt=%d diffs=%d'%(fn,len(mine),len(tgt),len(d)))
for i,m,t in d[:15]: print('   ',i,m,'|',t)
