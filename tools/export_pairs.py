#!/usr/bin/env python3
"""export_pairs.py — mine gate-verified (target asm <-> byte-matching C) pairs into a fine-tune corpus.

For the BFM/PSX-gcc-2.7.2 matching specialist (docs/gen2-mips-matching-model.md). A banked function's
byte-matching C lives in src/*/*.c; its target asm comes from the BUILD objects (byte-identical to ROM;
asm/ itself is gitignored ROM-derived content, so git can't recover the splat .s). We objdump every
build code object, reformat each function to a splat-LIKE layout (/* vaddr LEWORD */ mnemonic $regs,
relocations as trailing comments), and pair it with the function's C definition.

NOTE (format): this is splat-LIKE, not byte-identical to the on-disk .s api_draft feeds at inference
(relocations render as trailing `; R_MIPS_*` comments rather than inline %hi/%lo). For a perfectly
format-matched corpus, regenerate the .s via spimdisasm/splat — see docs/gen2-mips-matching-model.md.
Good enough to validate the pipeline and start LoRA experiments.

Output: <out>/pairs.jsonl  ({fn, region, asm, c}) + train.jsonl / test.jsonl (~90/10 by fn hash).

  tools/export_pairs.py [--out datasets/match_pairs] [--limit N] [--test-frac 0.1]
"""
import argparse, glob, hashlib, json, os, re, subprocess, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = 'mipsel-linux-gnu-objdump'
# a banked C def: "<type ...> func_XXXX(<params>) {" at column 0 (type-only prefix, no operators/parens
# before the name) — same shape gen_harvest_targets uses to avoid matching indented call expressions.
DEF_RE = re.compile(r'^([A-Za-z_][\w \t\*]*?\bfunc_[0-9A-Fa-f]+\s*\([^;{]*\))\s*\{', re.M)
REG_RE = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra)\b')


def sh(args):
    return subprocess.run(args, capture_output=True, text=True, cwd=REPO)


def _le(word8):
    """objdump big-endian-printed instruction word -> little-endian byte string (splat's LEWORD)."""
    return ''.join(reversed([word8[i:i + 2] for i in range(0, 8, 2)])).upper()


def objdump_funcs():
    """fn -> splat-like asm text, from every build code object (byte-identical to ROM)."""
    funcs = {}
    for obj in glob.glob(os.path.join(REPO, 'build/**/*.o'), recursive=True):
        r = sh([OBJDUMP, '-dr', '-j', '.text', obj])
        cur, lines, base = None, [], 0
        for line in r.stdout.splitlines():
            h = re.match(r'^([0-9a-f]+) <([^>]+)>:', line)
            if h:
                if cur and cur.startswith('func_') and lines and cur not in funcs:
                    funcs[cur] = '\n'.join(lines)
                base, cur, lines = int(h.group(1), 16), h.group(2), []   # base = section offset of label
                continue
            mi = re.match(r'\s+([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)', line)
            if mi and cur and cur.startswith('func_'):
                off, word, mn, ops = int(mi.group(1), 16), mi.group(2), mi.group(3), mi.group(4).strip()
                vaddr = int(cur[5:], 16) + (off - base)             # intra-function offset + abs func addr
                lines.append(('/* %08X %s */  %-9s %s' % (vaddr, _le(word), mn, REG_RE.sub(r'$\1', ops))).rstrip())
            elif 'R_MIPS' in line and cur and lines:
                lines[-1] += '   ; ' + line.strip()
        if cur and cur.startswith('func_') and lines and cur not in funcs:
            funcs[cur] = '\n'.join(lines)
    return funcs


def extract_defs(src_text):
    """fn -> [preceding extern block] + the brace-matched C def (corpus-v2: self-contained/compilable).

    The src declares each fn's globals/callees as `extern ...;` lines immediately ABOVE the def, with
    the correct byte-verified types. v1 dropped them -> half the corpus failed standalone compile and the
    HARD (global/struct) fns were filtered out, biasing training trivial. Capturing the contiguous extern
    block above each def recovers them (52%->92% standalone-compile) AND teaches the right global types."""
    out = {}
    for mt in DEF_RE.finditer(src_text):
        nm = re.search(r'func_[0-9A-Fa-f]+', mt.group(1))
        if not nm:
            continue
        fn = nm.group(0)
        depth, j, end = 0, mt.end() - 1, None
        while j < len(src_text):
            c = src_text[j]
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0:
                    end = j + 1
                    break
            j += 1
        if end is None:
            continue
        func = src_text[mt.start():end]
        # contiguous extern/comment/blank lines immediately above, back to the previous def's `}`
        keep = []
        for ln in reversed(src_text[:mt.start()].split('\n')):
            s = ln.strip()
            if s.startswith('extern ') or s == '' or s.startswith(('//', '*', '/*')) or s.endswith('*/'):
                keep.append(ln)
            else:
                break
        externs = [l for l in reversed(keep) if l.strip().startswith('extern ')]
        out[fn] = ('\n'.join(externs) + '\n\n' + func) if externs else func
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--out', default='datasets/match_pairs')
    ap.add_argument('--limit', type=int, default=0, help='cap pairs (0 = all)')
    ap.add_argument('--test-frac', type=float, default=0.1)
    a = ap.parse_args()

    outdir = os.path.join(REPO, a.out)
    os.makedirs(outdir, exist_ok=True)

    print('disassembling build objects (ROM-identical) ...', file=sys.stderr)
    asm = objdump_funcs()
    print('  %d functions with asm in build/' % len(asm), file=sys.stderr)

    # collect banked C defs from the live source tree (track which src file = region)
    defs = {}   # fn -> (body, region)
    for root, _, files in os.walk(os.path.join(REPO, 'src')):
        for f in files:
            if f.endswith('.c'):
                region = os.path.relpath(os.path.join(root, f), os.path.join(REPO, 'src'))[:-2]
                for fn, body in extract_defs(open(os.path.join(root, f)).read()).items():
                    defs.setdefault(fn, (body, region))
    print('  %d func defs in src' % len(defs), file=sys.stderr)

    pairs, skipped = [], {'no_asm': 0}
    for fn, (body, region) in sorted(defs.items()):
        if fn not in asm:
            skipped['no_asm'] += 1
            continue
        pairs.append({'fn': fn, 'region': region, 'asm': asm[fn], 'c': body})
        if a.limit and len(pairs) >= a.limit:
            break

    # deterministic ~split by fn-hash (no randomness; reproducible)
    def is_test(fn):
        h = int(hashlib.sha1(fn.encode()).hexdigest(), 16)
        return (h % 1000) < int(a.test_frac * 1000)

    allp = os.path.join(outdir, 'pairs.jsonl')
    trp = os.path.join(outdir, 'train.jsonl')
    tep = os.path.join(outdir, 'test.jsonl')
    with open(allp, 'w') as fa, open(trp, 'w') as ft, open(tep, 'w') as fe:
        ntest = 0
        for p in pairs:
            line = json.dumps(p) + '\n'
            fa.write(line)
            if is_test(p['fn']):
                fe.write(line); ntest += 1
            else:
                ft.write(line)

    print('\n=== export_pairs ===')
    print('pairs written : %d  (train %d / test %d)' % (len(pairs), len(pairs) - ntest, ntest))
    print('skipped       : %d defs with no asm in build/ (lib/inline/not-compiled)' % skipped['no_asm'])
    print('out           : %s {pairs,train,test}.jsonl' % a.out)
    if pairs:
        ex = pairs[0]
        print('\n--- sample pair: %s (region %s) ---' % (ex['fn'], ex['region']))
        print('ASM (first 3 lines):')
        for l in ex['asm'].splitlines()[:6]:
            if l.strip():
                print('  ' + l)
        print('C (first 2 lines):')
        for l in ex['c'].splitlines()[:2]:
            print('  ' + l)


if __name__ == '__main__':
    main()
