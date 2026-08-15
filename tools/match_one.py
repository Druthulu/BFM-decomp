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
import json
import masked_diff
import residual_class

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('fn')
ap.add_argument('--c', help='C file (externs + the function def). Default: search .run/drafts3|2|/')
ap.add_argument('--asm-subdir', default='asm/resident/nonmatchings/resident')
ap.add_argument('--work', default=None,
                help='scratch dir. Default: a PRIVATE per-invocation dir (.run/match/<fn>.<pid>). '
                     'It used to default to the SHARED ".run/match", which silently broke the one '
                     'property this tool advertises — see below.')
ap.add_argument('--o0', action='store_true',
                help='compile at -O0 (for the _o0 split subsegments: ov_SC01_077_o0.c, whale _o0b — '
                     'their target bytes are -O0; an -O2 compile can never match them, Makefile:445)')
ap.add_argument('--emit-streams', default=None,
                help='P31 T8 (additive): dump {"fn","mine":[words],"tgt":[words]} to this path — '
                     'the len_tells/family_align input. No effect on stdout.')
ap.add_argument('--json', action='store_true',
                help='emit one JSON result line {status,closeness,nins,residual} (Task-12 structured '
                     'residual telemetry for the permuter-autopsy). Still exits 0 on MATCH, 1 otherwise.')
a = ap.parse_args()

# PRIVATE SCRATCH BY DEFAULT (Phase-28 T5). This tool's own docstring promises "Fully isolated (own
# temp dir) so many run in PARALLEL with no shared build -- a real asm-differ loop for an agent to
# iterate against." That was FALSE: --work defaulted to the shared '.run/match', so every concurrent
# caller compiled into the SAME t.c/t.o. A 16-agent wave found it the only way it can be found — one
# agent read another's function out of its own scratch file ("found another agent's func_800D2650 in
# my t.c") and said so. Every other agent in that wave iterated against a loop that could silently
# hand it someone else's compile, which is worse than a crash: it produces a CONFIDENT WRONG verdict.
# The docstring was the spec; the default contradicted it; nothing checked. Now the default IS the
# promise. (The whole-binary byte-gate was never at risk — it is the sole arbiter, G3/P9 — but the
# iteration loop agents steer by absolutely was.)
if not a.work:
    a.work = os.path.join('.run/match', f'{a.fn}.{os.getpid()}')

CPP = 'mipsel-linux-gnu-cpp'; CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'
MASPSX = 'tools/maspsx/maspsx.py'; AS = 'mipsel-linux-gnu-as'; PY = '.venv/bin/python'
CPPFLAGS = '-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
CC1FLAGS = ('-quiet %s -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'
            % ('-O0' if a.o0 else '-O2')).split()
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
# strip inline scalar-typedef redefinitions (common.h provides them; C89 rejects the dup).
# The T4 primitive splits multi-typedef lines the old regex couldn't cross (42 discarded MATCHes).
src = masked_diff.strip_scalar_typedefs(src)
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

if a.emit_streams:                                        # P31 T8: word streams for len_tells
    json.dump({"fn": a.fn, "mine": [i["word"] for i in mine], "tgt": [i["word"] for i in tgt]},
              open(a.emit_streams, "w"))

# structured residual (shared with gate_stage's near-record + the Task-12 autopsy telemetry)
diffs = masked_diff.structured_diff(mine, tgt)

# Task-13A: the DETERMINISTIC residual class, computed here because this is the only place both
# FULL streams exist. A stored residual is capped at 48 entries, which is exactly enough to hide
# the drift signature that explains an inflated closeness — so the verdict is computed on the
# uncapped streams and carried alongside the (still capped) residual.
#
# The classifier's own closeness is index-wise and must equal len(diffs) by construction. Asserting
# that here is a SECOND ORACLE, not a nicer assertion inside one (R34): structured_diff and
# classify_streams compute it by different routes, so a disagreement is a real defect and says so
# in the output rather than silently picking a winner. A classifier crash degrades to a loud
# ERROR verdict instead of killing the agent iteration loop this tool exists to serve.
try:
    verdict = residual_class.classify_streams(mine, tgt)
    if verdict["closeness"] != len(diffs):
        verdict["closeness_disagree"] = [verdict["closeness"], len(diffs)]
except Exception as e:                                     # noqa: BLE001 — loud in the data
    verdict = {"klass": "ERROR", "profile": None, "bucket": "unknown",
               "closeness": len(diffs), "sig": "ERROR", "detail": {"error": repr(e)}}

if not diffs and len(mine) == len(tgt):
    if a.json:
        print(json.dumps({"status": "match", "closeness": 0, "nins": len(mine), "residual": [],
                          "verdict": verdict}))
    else:
        print('MATCH (%d ins)  %s' % (len(mine), a.fn))
    sys.exit(0)
if a.json:
    print(json.dumps({"status": "near" if diffs else "fail", "closeness": len(diffs),
                      "nins": len(mine), "residual": [[i, me, tg] for i, me, tg in diffs[:48]],
                      "verdict": verdict}))
    sys.exit(1)
print('DIFF  %s   mine=%d ins, target=%d ins, %d mismatched' % (a.fn, len(mine), len(tgt), len(diffs)))
# the class tells you WHICH tool to reach for before you read a single instruction: a `permuter`
# bucket is search-closeable; a `structural` one never is (no local mutation introduces a
# different load width or an extra instruction) and wants the cookbook idiom named in its sig.
print('  class: %s  [%s]  sig=%s%s' % (
    verdict["klass"], verdict["bucket"], verdict["sig"],
    ("  profile=" + verdict["profile"]) if verdict.get("profile") else ""))
print('  idx | MINE                          | TARGET')
for i, me, tg in diffs[:40]:
    print('  %3d | %-28s | %s' % (i, me, tg))
sys.exit(1)
