#!/usr/bin/env python3
"""format_finetune.py — turn the match-pairs corpus into a LoRA instruction dataset.

Reads datasets/match_pairs/{train,test}.jsonl ({fn,region,asm,c}) and emits Qwen chat-template
JSONL ({messages:[system,user,assistant]}) for Unsloth/TRL. The prompt is LEAN — just the target
asm (+ a one-line predefined-types note) — because the whole point of fine-tuning is to bake the
gcc-2.7.2 matching precision into WEIGHTS, so inference needs no inlined cookbook (short prompt =
fast). Train/inference prompts must match: api_draft.py --lean produces the SAME shape.

NOTE (format): corpus asm is splat-LIKE (objdump, relocations as `; R_MIPS_*`); the eval feeds the
real .s (inline %hi/%lo). Minor gap; for a pilot it should generalize. See docs/gen2-mips-matching-model.md.

  tools/format_finetune.py [--in datasets/match_pairs] [--out datasets/match_pairs]
"""
import argparse, json, os, re, subprocess

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# the pinned standalone-compile pipeline (match_one.py) — used to keep only completions that COMPILE
# (the bare src defs reference TU-header externs; undeclared globals/structs fail cc1. A non-compilable
# completion teaches the model to emit uncompilable code, so filter them for a clean pilot corpus).
_CPP = 'mipsel-linux-gnu-cpp'; _CC1 = 'tools/bin/gcc-2.7.2-psx/cc1'; _MASPSX = 'tools/maspsx/maspsx.py'
_AS = 'mipsel-linux-gnu-as'; _PYV = '.venv/bin/python'
_CPPF = '-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'.split()
_CC1F = '-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'.split()
_ASF = '-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0'.split()
_TD = re.compile(r'^[ \t]*typedef\b.*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64)[ \t]*;[ \t]*\n', re.M)


def compiles(c):
    src = '#include "common.h"\n' + _TD.sub('', c)
    wd = os.path.join(REPO, '.run/_ft_cc'); os.makedirs(wd, exist_ok=True)
    open(os.path.join(wd, 't.c'), 'w').write(src)
    p = subprocess.run([_CPP] + _CPPF + ['.run/_ft_cc/t.c'], capture_output=True, cwd=REPO)
    if p.returncode: return False
    p = subprocess.run([_CC1] + _CC1F, input=p.stdout, capture_output=True, cwd=REPO)
    if p.returncode: return False
    p = subprocess.run([_PYV, _MASPSX, '--aspsx-version=2.56', '--expand-div'], input=p.stdout, capture_output=True, cwd=REPO)
    if p.returncode: return False
    p = subprocess.run([_AS] + _ASF + ['-o', '.run/_ft_cc/t.o'], input=p.stdout, capture_output=True, cwd=REPO)
    return p.returncode == 0

SYS = ("You are an expert at MATCHING decompilation for MIPS (PSX, gcc-2.7.2 -O2 -G0 -mips1 -mcpu=3000 "
       "-msoft-float + maspsx). Given a function's target assembly, output C that the pinned toolchain "
       "compiles to BYTE-IDENTICAL machine code. The types u8/u16/u32/s8/s16/s32/f32/s64/u64/f64 are "
       "predefined (common.h). Output ONLY the C (the function definition + any externs it needs).")


def user_msg(asm):
    return ("Target assembly (each `/* vaddr WORD */ mnemonic` line is one encoded instruction):\n"
            + asm.strip() + "\n\nWrite the byte-matching C function.")


def convert(rows):
    out = []
    for r in rows:
        if not (r.get('asm') and r.get('c')):
            continue
        out.append({'messages': [
            {'role': 'system', 'content': SYS},
            {'role': 'user', 'content': user_msg(r['asm'])},
            {'role': 'assistant', 'content': r['c'].strip()},
        ]})
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--in', dest='indir', default='datasets/match_pairs')
    ap.add_argument('--out', default='datasets/match_pairs')
    ap.add_argument('--no-verify', action='store_true', help='skip the standalone-compile filter')
    a = ap.parse_args()
    indir, outdir = os.path.join(REPO, a.indir), os.path.join(REPO, a.out)
    os.makedirs(outdir, exist_ok=True)

    for split in ('train', 'test'):
        src = os.path.join(indir, split + '.jsonl')
        if not os.path.exists(src):
            print('missing', src); continue
        rows = [json.loads(l) for l in open(src)]
        if not a.no_verify:
            kept = [r for r in rows if r.get('c') and compiles(r['c'])]
            print('%-5s : %d/%d completions compile standalone (filtered)' % (split, len(kept), len(rows)))
            rows = kept
        conv = convert(rows)
        dst = os.path.join(outdir, split + '_ft.jsonl')
        with open(dst, 'w') as f:
            for c in conv:
                f.write(json.dumps(c) + '\n')
        print('%-5s : %d examples -> %s' % (split, len(conv), os.path.relpath(dst, REPO)))

    # show one example so the shape is obvious
    ex = convert([json.loads(open(os.path.join(indir, 'train.jsonl')).readline())])[0]
    print('\n--- sample training example (messages) ---')
    for m in ex['messages']:
        body = m['content']
        print('[%s] %s' % (m['role'], body[:280] + ('…' if len(body) > 280 else '')))


if __name__ == '__main__':
    main()
