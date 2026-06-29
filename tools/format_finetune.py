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
import argparse, json, os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

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
    a = ap.parse_args()
    indir, outdir = os.path.join(REPO, a.indir), os.path.join(REPO, a.out)
    os.makedirs(outdir, exist_ok=True)

    for split in ('train', 'test'):
        src = os.path.join(indir, split + '.jsonl')
        if not os.path.exists(src):
            print('missing', src); continue
        rows = [json.loads(l) for l in open(src)]
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
