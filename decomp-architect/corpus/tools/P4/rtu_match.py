#!/usr/bin/env python3
"""Real-TU-faithful per-function match check (Phase-25 wave-3, cookbook §42b).

Unlike match_one.py (which compiles ONE function in ISOLATION and is therefore blind to
in-TU declaration conflicts -- the def-side loose-typing / memcpy-builtin / read-global-type
drift class), this compiles the WHOLE split .c with the candidate spliced in and INCLUDE_ASM
neutralized (`-DINCLUDE_ASM(a,b)=`, so no asm/ is needed and no shared overlay build is
touched -> many workers run in PARALLEL, each in its own temp dir). gcc-2.7.2 -O2 compiles each
global function independently, so the neutralized whole-TU compile reproduces the exact ambient
context (types, canonical-sig layer, the `extern memcpy` builtin-disable, file-scope global
types) that the real build sees -> its MATCH holds at the whole-binary gate far more reliably
than match_one's. STILL finish on the real `make build` whole-binary SHA gate (G3/P9).

  tools/rtu_match.py func_80164930 --split ov_SC01_077_after --c cand.c
  # candidate may carry file-scope TU pre-edits as leading directive lines:
  #   //@EDIT old_text||new_text     (applied to the split .c before splicing; e.g. the s16->u16 flip)
  #   the replacement may be MULTI-LINE: a literal backslash-n in new_text becomes a newline
  #   (needed to expand a DEFINE_func_* macro instantiation in place -- the §63 per-overlay-local
  #   decl override).  Use \\n in the directive if you want a literal backslash-n.
  # --stderr-out PATH persists the FULL stderr of every stage.  Since P30 T0b the FAIL verdict
  # itself prints the NON-warning diagnostic lines (first 15; gcc-2.7.2 hard errors carry no
  # `error:` prefix, and these TUs emit hundreds of benign `type mismatch` warnings that drowned
  # the one real line — it cost three probes in SESSION-25). --stderr-out remains the full dump.
"""
import subprocess, re, sys, os, argparse, atexit
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import masked_diff

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('fn')
ap.add_argument('--split', required=True, help='split basename, e.g. ov_SC01_077_after')
ap.add_argument('--c', required=True, help='candidate C (the function def; may lead with //@EDIT lines)')
ap.add_argument('--source', default='ov_SC01_077')
ap.add_argument('--tu', default=None,
                help="the split's real TU path (e.g. a corpus Stub.path). PREFER THIS over "
                     "--source/--split: main's sources are LOOSE FILES in src/ (src/800.c), not "
                     "src/<binary>/<split>.c, so the reconstruction below is overlay-only and "
                     "silently builds a nonsense path for main (measured S68: src/800.c/800.c). "
                     "Pass the path you already have and nothing has to be reconstructed.")
ap.add_argument('--asm-subdir', default=None)
ap.add_argument('--work', default='.run/crack3/rtu')
ap.add_argument('--o0', action='store_true')
ap.add_argument('--maxdiff', type=int, default=60)
ap.add_argument('--stderr-out', default=None,
                help='write the FULL stderr of every stage here (the inline prints are tail-truncated)')
a = ap.parse_args()

# Every stage's stderr, verbatim, flushed on ANY exit path (including sys.exit).  A consumer that
# classifies a failure needs the FIRST non-warning error line; a truncated tail cannot supply it.
_errlog = []
def _flush_errlog():
    if not a.stderr_out:
        return
    d = os.path.dirname(a.stderr_out)
    if d:
        os.makedirs(d, exist_ok=True)
    with open(a.stderr_out, 'w') as f:
        for stage, err in _errlog:
            f.write('### %s\n%s\n' % (stage, err))
atexit.register(_flush_errlog)

# THE TU PATH. --tu wins when given (see its help); otherwise reconstruct the OVERLAY layout.
# A reconstruction that names a path which does not exist is REFUSED here rather than handed to cpp,
# because cpp's "No such file" surfaces as a CPP FAIL and reads as a broken draft (R43/R40).
SPLIT_SRC = a.tu or ('src/%s/%s.c' % (a.source, a.split))
if not os.path.exists(SPLIT_SRC):
    sys.exit('rtu_match: TU %r does not exist (from %s). main keeps its sources as LOOSE FILES in '
             'src/, so --source/--split cannot address them — pass --tu <path> instead.'
             % (SPLIT_SRC, 'the --tu you passed' if a.tu else '--source/--split reconstruction'))
# -I for the split's relative `#include "../shared/..."`: the TU's own directory, which is src/ for
# main and src/<binary>/ for an overlay.
SRC_INCDIR = os.path.dirname(SPLIT_SRC) or 'src'
ASM_SUBDIR = a.asm_subdir or ('asm/%s/nonmatchings/%s' % (a.source, a.split))
CPP='mipsel-linux-gnu-cpp'; CC1='tools/bin/gcc-2.7.2-psx/cc1'
MASPSX='tools/maspsx/maspsx.py'; AS='mipsel-linux-gnu-as'; PY='.venv/bin/python'
CPPFLAGS='-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
CC1FLAGS=('-quiet %s -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker' % ('-O0' if a.o0 else '-O2')).split()
ASFLAGS='-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0'.split()

split_txt = open(SPLIT_SRC).read()
cand_raw = open(a.c).read()

def _unescape_nl(s):
    """`\\n` -> newline, `\\\\` -> a literal backslash.  A //@EDIT directive is one LINE, so a
    multi-line replacement (expanding a DEFINE_func_* macro in place) can only be written escaped."""
    out, i = [], 0
    while i < len(s):
        if s[i] == '\\' and i + 1 < len(s) and s[i + 1] in 'n\\':
            out.append('\n' if s[i + 1] == 'n' else '\\')
            i += 2
            continue
        out.append(s[i])
        i += 1
    return ''.join(out)

# extract //@EDIT directives (file-scope pre-edits), strip them from the spliced body
edits = []
body_lines = []
for ln in cand_raw.split('\n'):
    m = re.match(r'\s*//@EDIT\s+(.*?)\|\|(.*)$', ln)
    if m:
        edits.append((_unescape_nl(m.group(1)), _unescape_nl(m.group(2))))
    else:
        body_lines.append(ln)
body = '\n'.join(body_lines).rstrip('\n')
for old, new in edits:
    if old not in split_txt:
        print('EDIT-FAIL: text not found in split: %r' % old); sys.exit(2)
    split_txt = split_txt.replace(old, new, 1)

pat = re.compile(r'INCLUDE_ASM\([^;]*\b' + re.escape(a.fn) + r'\)\s*;')
if pat.search(split_txt):
    split_txt = pat.sub(lambda m: body, split_txt, count=1)
elif re.search(r'\b%s\s*\(' % re.escape(a.fn), split_txt):
    pass  # already defined (validation mode: compile as-is)
else:
    print('ERR: no INCLUDE_ASM stub nor def for %s in %s' % (a.fn, a.split)); sys.exit(2)

wd = '%s/%s' % (a.work, a.fn); os.makedirs(wd, exist_ok=True)
open('%s/t.c' % wd, 'w').write(split_txt)

def pipe(stage, cmd, data=None):
    p = subprocess.run(cmd, input=data, capture_output=True)
    _errlog.append((stage, p.stderr.decode('utf-8', 'replace')))
    return p


def _diagnostics(raw, tail):
    """The real errors, IN the verdict output (P30 T0b — cost three probes in SESSION-25).

    A raw tail is all warnings on a big TU: gcc-2.7.2 warns for the whole split, and its HARD errors
    carry no `error:` prefix (the S22 lesson) — so `[-2000:]` printed 2 KB of warnings while the one
    line that killed cc1 sat mid-stream, reachable only via --stderr-out + a hand grep. This applies
    that exact working recipe in-tool: drop warning/context/progress lines; what survives IS the
    error set (2.7.2 hard errors are bare `file:line: message`; ICE/signal lines also survive).
    Falls back to the raw tail if the filter leaves nothing — never print LESS than before."""
    keep = [l for l in raw.splitlines()
            if l.strip()
            and 'warning:' not in l
            and not re.search(r'In function|At top level|^###', l)]
    if not keep:
        return raw[-tail:]
    head = keep[:15]
    more = '' if len(keep) <= 15 else '\n  ... +%d more non-warning lines (--stderr-out for all)' % (len(keep) - 15)
    return '\n'.join(head) + more


def _fail(stage, p, tail):
    print('%s FAIL\n%s' % (stage, _diagnostics(p.stderr.decode('utf-8', 'replace'), tail)))
    _flush_errlog()
    sys.exit(1)
# -Isrc/<source> so the split's relative `#include "../shared/..."` resolves from the temp dir
p = pipe('CPP', [CPP]+CPPFLAGS+['-I'+SRC_INCDIR, '-DINCLUDE_ASM(a,b)=', '%s/t.c'%wd])
if p.returncode: _fail('CPP', p, 1500)
p = pipe('CC1', [CC1]+CC1FLAGS, p.stdout)
if p.returncode: _fail('CC1', p, 2000)
# THE REORDER ISLAND — THE FOURTH COPY OF THIS DEFECT (P31 S76). The Makefile pipes
# REORDER_TUS through tools/reorder_passthrough.py into `as -O2`; this tool hardcoded
# maspsx + `as -O1` like match_one did, so for those TUs it reported a phantom +1 epilogue
# instruction and `recover_integration --probe-only` booked it as a real DIFF. Found by a
# drafting agent on func_8005D4B8: match_one (already fixed) said MATCH 14/14 while rtu_match
# said 15/14, and the agent correctly identified its own oracle as the liar.
# Derived from the Makefile, never copied (R51).
_REORDER_TUS = set()
try:
    import re as _re
    _m = _re.search(r'^REORDER_TUS\s*:?=\s*(.*)$', open('Makefile').read(), _re.M)
    _REORDER_TUS = set(_m.group(1).split()) if _m else set()
except OSError:
    pass
_stem = os.path.splitext(os.path.basename(SPLIT_SRC))[0]
if _stem in _REORDER_TUS:
    print('rtu_match: NOTE — %s is in the Makefile REORDER_TUS island; assembling with '
          'reorder_passthrough + as -O2 (the real build path), not maspsx + as -O1.' % _stem,
          file=sys.stderr)
    p = pipe('REORDER', [PY, 'tools/reorder_passthrough.py'], p.stdout)
    if p.returncode: _fail('REORDER', p, 1500)
    p = pipe('AS', [AS] + '-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O2 -G0'.split()
             + ['-o', '%s/t.o' % wd], p.stdout)
    if p.returncode: _fail('AS', p, 1500)
else:
    p = pipe('MASPSX', [PY, MASPSX, '--aspsx-version=2.56', '--expand-div'], p.stdout)
    if p.returncode: _fail('MASPSX', p, 1500)
    p = pipe('AS', [AS]+ASFLAGS+['-o', '%s/t.o'%wd], p.stdout)
    if p.returncode: _fail('AS', p, 1500)

mine = masked_diff.insns_from_object('%s/t.o'%wd, a.fn)
tgt = masked_diff.insns_from_s('%s/%s.s' % (ASM_SUBDIR, a.fn))
if not mine: print('FAIL: object has no function', a.fn); sys.exit(1)
diffs = masked_diff.structured_diff(mine, tgt)   # ONE comparer (R33); carries the internal-j target check
if not diffs and len(mine) == len(tgt):
    print('MATCH (%d ins)  %s' % (len(mine), a.fn)); sys.exit(0)
print('DIFF  %s   mine=%d ins, target=%d ins, %d mismatched' % (a.fn, len(mine), len(tgt), len(diffs)))
print('  idx | MINE                          | TARGET')
for i, me, tg in diffs[:a.maxdiff]:
    print('  %3d | %-28s | %s' % (i, me, tg))
sys.exit(1)
