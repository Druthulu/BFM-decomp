#!/usr/bin/env python3
"""eval_lora.py — gate-true eval of a fine-tuned model on HELD-OUT banked functions.

The held-out test pairs (datasets/match_pairs/test.jsonl) are banked, so they have no .s — but the
corpus carries each one's target asm (with reloc markers). So: feed the model the LEAN asm prompt
(same shape as training), compile its C with the pinned toolchain, objdump it, and compare to the
corpus target (relocation-masked, exactly like match_one). Same format on both sides (objdump) → no
train/eval format confound; functions the model never trained on → real generalization signal.

Reports match / near / fail vs the stock-local floor (~0). Optional --iters feeds the diff back.

  LEAN=1 API_BASE=http://<host>:1234/v1 MODEL=bfm-match-7b \
    .venv/bin/python tools/eval_lora.py --test datasets/match_pairs/test.jsonl --iters 3
"""
import argparse, json, os, re, struct, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import api_draft  # call_api, build_user_lean, extract_code, LEAN_SYS (module-level argparse-free)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CPP = 'mipsel-linux-gnu-cpp'; CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'; MASPSX = 'tools/maspsx/maspsx.py'
AS = 'mipsel-linux-gnu-as'; OBJDUMP = 'mipsel-linux-gnu-objdump'; PYV = '.venv/bin/python'
CPPF = '-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
CC1F = '-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'.split()
ASF = '-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0'.split()
_TD = re.compile(r'^[ \t]*typedef\b.*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64)[ \t]*;[ \t]*\n', re.M)


def compile_obj(c, wd):
    """pinned pipeline -> object path, or None on compile failure."""
    os.makedirs(wd, exist_ok=True)
    open(os.path.join(wd, 't.c'), 'w').write('#include "common.h"\n' + _TD.sub('', c))
    p = subprocess.run([CPP] + CPPF + [os.path.join(wd, 't.c')], capture_output=True, cwd=REPO)
    if p.returncode: return None
    p = subprocess.run([CC1] + CC1F, input=p.stdout, capture_output=True, cwd=REPO)
    if p.returncode: return None
    p = subprocess.run([PYV, MASPSX, '--aspsx-version=2.56', '--expand-div'], input=p.stdout, capture_output=True, cwd=REPO)
    if p.returncode: return None
    p = subprocess.run([AS] + ASF + ['-o', os.path.join(wd, 't.o')], input=p.stdout, capture_output=True, cwd=REPO)
    return os.path.join(wd, 't.o') if p.returncode == 0 else None


def my_insns(obj, fn):
    d = subprocess.run([OBJDUMP, '-dr', '-j', '.text', obj], capture_output=True, text=True, cwd=REPO).stdout
    words, masks, infn = [], [], False
    for line in d.splitlines():
        h = re.match(r'^[0-9a-f]+ <([^>]+)>:', line)
        if h:
            infn = (h.group(1) == fn); continue
        if not infn: continue
        mi = re.match(r'\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+', line)
        if mi:
            w = int(mi.group(1), 16); words.append(w)
            masks.append(0 if (w >> 26) in (2, 3) else 0xFFFFFFFF)
        elif 'R_MIPS' in line and words:
            masks[-1] = 0 if '_26' in line else 0xFFFF0000
    return words, masks


def parse_target(asm):
    """corpus asm (/* vaddr LEWORD */ mnem  ; R_MIPS_*) -> (words, masks)."""
    words, masks = [], []
    for line in asm.splitlines():
        m = re.match(r'\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s*(.*)', line)
        if not m: continue
        words.append(struct.unpack('<I', bytes.fromhex(m.group(1)))[0])
        masks.append(0 if 'R_MIPS' in m.group(2) and '_26' in m.group(2)
                     else (0xFFFF0000 if 'R_MIPS' in m.group(2) else 0xFFFFFFFF))
    return words, masks


def diff(mw, mmask, tw, tmask):
    n = max(len(mw), len(tw)); ds = []
    for i in range(n):
        me = (mw[i] & mmask[i]) if i < len(mw) else None
        tg = (tw[i] & tmask[i]) if i < len(tw) else None
        if me != tg:
            ds.append('idx %d: mine=%s target=%s' % (i, '%08x' % mw[i] if i < len(mw) else '--',
                                                      '%08x' % tw[i] if i < len(tw) else '--'))
    return ds


def eval_one(r, iters, wd):
    fn, asm = r['fn'], r['asm']
    tw, tmask = parse_target(asm)
    msgs = [{'role': 'system', 'content': api_draft.LEAN_SYS},
            {'role': 'user', 'content': api_draft.build_user_lean(r, asm, '')}]
    best = 10 ** 9
    for i in range(max(1, iters)):
        code = api_draft.extract_code(api_draft.call_api(msgs))
        if not code.strip(): break
        obj = compile_obj(code, wd)
        if not obj:
            ds = ['compile-fail']; close = 10 ** 8
        else:
            mw, mmask = my_insns(obj, fn)
            mismatch = diff(mw, mmask, tw, tmask)
            close = 0 if (not mismatch and len(mw) == len(tw)) else (len(mismatch) or 1)
            ds = mismatch
        best = min(best, close)
        if close == 0: return 0
        if i < iters - 1:
            msgs += [{'role': 'assistant', 'content': '```c\n' + code + '```'},
                     {'role': 'user', 'content': 'Not byte-identical. Diff:\n' + '\n'.join(ds[:40])
                      + '\nFix and reply with the corrected full function in ONE ```c block.'}]
    return best


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--test', default='datasets/match_pairs/test.jsonl')
    ap.add_argument('--iters', type=int, default=3)
    ap.add_argument('--limit', type=int, default=0)
    a = ap.parse_args()
    rows = [json.loads(l) for l in open(os.path.join(REPO, a.test))]
    if a.limit: rows = rows[:a.limit]
    print('eval_lora: %s @ %s -> %d held-out fns, %d iters\n' % (api_draft.MODEL, api_draft.API_BASE, len(rows), a.iters))
    match = near = fail = 0
    for r in rows:
        c = eval_one(r, a.iters, os.path.join(REPO, '.run/_eval_lora'))
        tag = 'MATCH' if c == 0 else ('compile/near-fail' if c >= 10 ** 8 else 'near %d' % c)
        if c == 0: match += 1
        elif c >= 10 ** 8: fail += 1
        else: near += 1
        print('  %-16s %s' % (r['fn'], tag))
    n = len(rows)
    print('\n=== eval: MATCH %d/%d  near %d  fail %d  (stock-local floor: ~0) ===' % (match, n, near, fail))


if __name__ == '__main__':
    main()
