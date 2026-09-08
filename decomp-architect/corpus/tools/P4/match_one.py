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
ap.add_argument('--asm-subdir', default='asm/resident/nonmatchings/resident',
                help='directory holding <fn>.s. THE DEFAULT IS A TRAP FOR ANY BINARY BUT RESIDENT '
                     '(P31 S60): function names are ADDRESS-DERIVED, and overlays share the address '
                     'space, so the same name is often a DIFFERENT function in another binary (the '
                     '§238 homonym trap). A caller that omits this flag silently diffs against '
                     "resident's version and gets a confident verdict about the wrong target. The "
                     'drafting path is safe — api_draft passes dirname(card.asm) — so this warns '
                     'rather than refuses, to avoid breaking resident-era callers that rely on it.')
ap.add_argument('--work', default=None,
                help='scratch dir. Default: a PRIVATE per-invocation dir (.run/match/<fn>.<pid>). '
                     'It used to default to the SHARED ".run/match", which silently broke the one '
                     'property this tool advertises — see below.')
ap.add_argument('--o0', action='store_true',
                help='force -O0 (for the _o0 split subsegments: ov_SC01_077_o0.c, whale _o0b — '
                     'their target bytes are -O0; an -O2 compile can never match them, Makefile:445). '
                     'Normally unnecessary: the opt level is AUTO-DETECTED from the target .s.')
ap.add_argument('--no-reorder', action='store_true',
                help='force the maspsx + as -O1 path even for a TU in the Makefile '
                     'REORDER_TUS island (diagnostic; the island IS the real build path)')
ap.add_argument('--no-auto-o0', action='store_true',
                help='disable the auto-detection and compile -O2 unless --o0 is given')
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

from o0_detect import detect_o0  # one definition, shared (P31 S67)


if '--asm-subdir' not in sys.argv:
    print(f'match_one: WARNING — no --asm-subdir given, defaulting to {a.asm_subdir!r}. If '
          f'{a.fn} belongs to another binary this verdict is about a DIFFERENT function at the '
          f'same address (§238).', file=sys.stderr)
_sub = os.path.basename(a.asm_subdir.rstrip('/'))
# The BINARY, from the asm tree layout: asm/<bin>/nonmatchings/<sub> for every alias except main,
# which splat writes at the tree root as asm/nonmatchings/<sub>.
_parts = os.path.normpath(a.asm_subdir).split(os.sep)
_bin = 'main' if (len(_parts) > 1 and _parts[1] == 'nonmatchings') else (_parts[1] if len(_parts) > 1 else 'main')
# TWO ORACLES, and they answer different questions (R34). The PROLOGUE says what the target bytes
# were compiled as; the SUBSEG NAME says what this build will compile the C as (Makefile:697/702/
# 716/724 give `boot` and every `*_o0*.c` object -O0 flags). Either one alone is wrong somewhere:
# `boot/start.s` has no ordinary prologue yet is built -O0, and an -O0 function sitting in an -O2
# subseg has the prologue but cannot bank until it is carved.
try:
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import corpus as _corpus
    _sub_o0 = _corpus.o0_subseg(_bin, _sub)      # the Makefile is the ground truth, not the name
except Exception:
    _sub_o0 = ('_o0' in _sub) or _sub == 'boot'  # fallback: the old name convention
_tell_o0 = detect_o0('%s/%s.s' % (a.asm_subdir, a.fn))
_o0 = a.o0 or (not a.no_auto_o0 and (_tell_o0 or _sub_o0))
if _o0 and not a.o0:
    print('match_one: compiling at -O0 (%s; pass --no-auto-o0 to override)'
          % ('frame-pointer prologue in the target' if _tell_o0 else 'subseg %r is an -O0 object' % _sub))
if _tell_o0 and not _sub_o0:
    print('match_one: NOTE — %s is an -O0 function in subseg %r, which the build compiles -O2. '
          'A MATCH here CANNOT BANK until the function lives in an -O0 object '
          '(tools/o0_subsplit.py / tools/rollout_o0.py + the Makefile -O0 globs).'
          % (a.fn, _sub))

CPP = 'mipsel-linux-gnu-cpp'; CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'
MASPSX = 'tools/maspsx/maspsx.py'; AS = 'mipsel-linux-gnu-as'; PY = '.venv/bin/python'
CPPFLAGS = '-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
CC1FLAGS = ('-quiet %s -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'
            % ('-O0' if _o0 else '-O2')).split()
ASFLAGS = '-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0'.split()

# THE REORDER ISLAND (P31 S76). Four of main's TUs are NOT built through maspsx at all: the
# Makefile pipes them through `tools/reorder_passthrough.py` into `as -O2` (ASFLAGS_REORDER),
# which is the ONLY path that emits the `jr $ra` + `addiu $sp`-in-delay-slot epilogue and fills
# branch delay slots. That island landed 2026-09-01 and banked 20 functions; this oracle never
# learned about it, so for a function in one of those TUs it modelled the WRONG assembler and
# reported a phantom ±1 LENGTH-DRIFT in the epilogue.
#
# Measured, S76: six main drafting agents in one wave hit that residual, correctly recognised it
# as the §182/§188 epilogue shape, read `oracle_reorder.py`'s (now stale) "UNREACHABLE from any C
# source" docstring, and each fell back to submitting a §265 verbatim-asm body — for functions
# whose plain C the real build would have accepted. An oracle that models a build path the project
# no longer uses does not report a wall; it MANUFACTURES one (R35, and `lane-blockers-are-harness-
# not-model`).
#
# DERIVED FROM THE MAKEFILE, never a second copy of the list (R33/R51: a derived property stored
# as config goes stale and takes a binary with it — which is precisely how this defect arose).
def _reorder_tus():
    try:
        mk = open('Makefile').read()
        m = re.search(r'^REORDER_TUS\s*:?=\s*(.*)$', mk, re.M)
        return set(m.group(1).split()) if m else set()
    except OSError:
        return set()


REORDER_PASSTHROUGH = 'tools/reorder_passthrough.py'
ASFLAGS_REORDER = '-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O2 -G0'.split()
_tu_stem = os.path.basename(a.asm_subdir.rstrip('/')) if a.asm_subdir else ''
_REORDER = (_tu_stem in _reorder_tus()) and not a.no_reorder
if _REORDER:
    print('match_one: NOTE — %s is in the Makefile REORDER_TUS island, so this compile uses '
          'reorder_passthrough + as -O2 (the real build path for that TU), NOT maspsx + as -O1. '
          'A ±1 epilogue drift under the maspsx path is an artifact of the wrong oracle, not a '
          '\u00a7188 wall. --no-reorder forces the maspsx path.' % _tu_stem, file=sys.stderr)

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


def toolchain_fail(stage, err):
    """A toolchain failure must still answer in the REQUESTED format (R43 / R35).

    `--json` used to print bare `CC1 FAIL\n<gcc stderr>` and exit 1, so every programmatic caller
    got `json.loads` of a non-JSON line. Measured P31 S66: claude_wave_packs' residual measurement
    swallowed 4 of 19 prior drafts as "residual not measured: Expecting value" — the instrument
    reported nothing where the true answer ("the prior draft does not COMPILE, here is the error")
    is the most actionable datum a pack can carry. Emit it as JSON; keep the human text on stderr.\n"""
    txt = err.decode(errors='replace')[-1800:] if isinstance(err, bytes) else str(err)[-1800:]
    if a.json:
        print(json.dumps({"status": stage.lower().replace(' ', '-'), "closeness": None,
                          "nins": None, "residual": [], "error": txt}))
    else:
        print('%s\n%s' % (stage, txt))
    sys.exit(1)


p = pipe([CPP] + CPPFLAGS + ['%s/t.c' % wd])
if p.returncode: toolchain_fail('CPP FAIL', p.stderr)
p = pipe([CC1] + CC1FLAGS, p.stdout)
if p.returncode: toolchain_fail('CC1 FAIL', p.stderr)
if _REORDER:
    p = pipe([PY, REORDER_PASSTHROUGH], p.stdout)
    if p.returncode: toolchain_fail('REORDER FAIL', p.stderr)
    p = pipe([AS] + ASFLAGS_REORDER + ['-o', '%s/t.o' % wd], p.stdout)
else:
    p = pipe([PY, MASPSX, '--aspsx-version=2.56', '--expand-div'], p.stdout)
    if p.returncode: toolchain_fail('MASPSX FAIL', p.stderr)
    p = pipe([AS] + ASFLAGS + ['-o', '%s/t.o' % wd], p.stdout)
if p.returncode: toolchain_fail('AS FAIL', p.stderr)

# masked compare: my compiled object vs the resolved splat .s (mask driven by my object's relocs)
mine = masked_diff.insns_from_object('%s/t.o' % wd, a.fn)
tgt = masked_diff.insns_from_s('%s/%s.s' % (a.asm_subdir, a.fn))

if not mine:
    print('FAIL: my object has no function', a.fn, '(compile produced nothing?)'); sys.exit(1)

if a.emit_streams:                                        # P31 T8: word streams for len_tells
    # P31 S52 (additive): also carry MY object's relocations. match_one MASKS them, so it is
    # structurally blind to symbol identity (§174 law 1c) -- a draft calling the wrong function
    # reports a clean MATCH. tools/reloc_identity.py is the disagreeing oracle (R34) and needs
    # the reloc kind/operand per instruction index; existing consumers read "mine"/"tgt" only.
    json.dump({"fn": a.fn, "mine": [i["word"] for i in mine], "tgt": [i["word"] for i in tgt],
               "mine_relocs": {str(n): {"kind": i["reloc_kind"], "op": i["reloc_op"]}
                               for n, i in enumerate(mine) if i["reloc_kind"]}},
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
