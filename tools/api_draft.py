#!/usr/bin/env python3
"""api_draft.py — provider-agnostic matching-C draft worker (the cheap-tier "draft" step).

The script equivalent of one worker_wave drafter agent, for ANY OpenAI-compatible chat endpoint:
local (LM Studio / llama.cpp / vLLM) OR cloud (OpenRouter → GLM/Qwen/DeepSeek). Builds the proven
drafter prompt with the target asm + Ghidra-C + toolkit inlined (the model can't read files), calls
the endpoint, extracts the C, writes it to the draft dir, and ITERATES against match_one — feeding
the per-instruction diff back for up to --iters rounds (context-aware retry), keeping the BEST draft.

Output drafts are scored by tools/ab_score.py exactly like an agent arm (point --out at an arm dir):
  tools/ab_score.py --arms opus haiku local

Config via env (so the SAME script serves local and OpenRouter):
  API_BASE   endpoint base, default http://localhost:1234/v1   (LM Studio default)
  API_KEY    bearer token; blank/"lm-studio" for local; OpenRouter key for cloud
  MODEL      model id as the server names it (e.g. qwen3-coder-30b-a3b, z-ai/glm-5.2)

Usage:
  API_BASE=http://localhost:1234/v1 MODEL=qwen3-coder-30b-a3b \
    .venv/bin/python tools/api_draft.py --targets .run/ab-exp/targets20.json --out .run/ab-exp/local --iters 4
  # OpenRouter / GLM:
  API_BASE=https://openrouter.ai/api/v1 API_KEY=sk-or-... MODEL=z-ai/glm-5.2 \
    .venv/bin/python tools/api_draft.py --targets .run/ab-exp/targets20.json --out .run/ab-exp/glm --iters 4
"""
import argparse, json, os, re, subprocess, sys, time, urllib.request, urllib.error

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = '.venv/bin/python'
API_BASE = os.environ.get('API_BASE', 'http://localhost:1234/v1').rstrip('/')
API_KEY = os.environ.get('API_KEY', 'lm-studio')
MODEL = os.environ.get('MODEL', 'local-model')
TEMP = float(os.environ.get('TEMP', '0.3'))   # thinking-mode models: ~0.6; deterministic drafting: ~0.2
LEAN = os.environ.get('LEAN', '0') != '0'     # LEAN=1: asm-only prompt for a FINE-TUNED model (no cookbook)

# Fair harness: give the no-tool local model the SAME context the agents read themselves — the shared
# type header, the live matching cookbook, and worked byte-matched examples (all inlined). COOKBOOK_FULL=0
# inlines only the matching-relevant sections (§1,§2,§5,§10,§16,§17,§21,§25,§27) instead of the whole file.
def _read(p):
    fp = os.path.join(REPO, p)
    return open(fp).read() if os.path.exists(fp) else ''

COMMON_H = _read('include/common.h')
_CB = _read('docs/matching-cookbook.md')
_FULL = os.environ.get('COOKBOOK_FULL', '1') != '0'
_KEEP = {1, 2, 5, 10, 16, 17, 21, 25, 27}   # the drafting-relevant §N (drop build/linker/fleet-ops)


def _cookbook():
    if _FULL:
        return _CB
    parts = re.split(r'(?m)^(## .*)$', _CB)
    out = []
    for i in range(1, len(parts), 2):
        hdr, body = parts[i], (parts[i + 1] if i + 1 < len(parts) else '')
        m = re.match(r'## §(\d+)\b', hdr)
        if m and int(m.group(1)) in _KEEP:
            out.append(hdr + body)
    return '\n'.join(out).strip()


COOKBOOK = _cookbook()

_CORPUS = None


def load_examples(ov, k, exclude):
    """k smallest byte-MATCHED (asm->C) pairs from the corpus, same overlay first — worked examples."""
    global _CORPUS
    if _CORPUS is None:
        p = os.path.join(REPO, 'datasets/match_pairs/pairs.jsonl')
        _CORPUS = [json.loads(l) for l in open(p)] if os.path.exists(p) else []
    pool = [r for r in _CORPUS if r['fn'] != exclude and r.get('c') and r.get('asm')
            and len(r['asm'].splitlines()) <= 40]                       # small = clear idiom, cheap
    same = sorted((r for r in pool if ov and ov in r['region']), key=lambda r: len(r['asm']))
    other = sorted((r for r in pool if not (ov and ov in r['region'])), key=lambda r: len(r['asm']))
    return '\n\n'.join('--- WORKED EXAMPLE (this toolchain, byte-MATCHED) ---\nTARGET ASM:\n%s\n\nMATCHING C:\n%s'
                       % (r['asm'].strip(), r['c'].strip()) for r in (same + other)[:k])


SYS = ("You are an expert at MATCHING decompilation for MIPS (PSX, gcc-2.7.2 -O2). Given a target's asm you "
       "write C that the pinned toolchain compiles to BYTE-IDENTICAL machine code. You are given the project's "
       "matching cookbook, the shared type header, and worked examples — USE them. "
       "Reply with ONLY the C (function definition + needed externs) in one ```c block, no prose.")


def build_user(t, asm_text, ghidra_text):
    ov = t['asm'].split('/')[1] if t.get('asm') and '/' in t['asm'] else ''
    examples = load_examples(ov, 2, t['name'])
    return f"""Write C that compiles BYTE-IDENTICAL to this MIPS function, under:
gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -msoft-float + maspsx --aspsx-version=2.56 --expand-div.

=== SHARED HEADER (common.h is AUTO-INCLUDED — these types/macros are PREDEFINED; do NOT redefine u8/s32/etc) ===
{COMMON_H}

=== MATCHING COOKBOOK (the project's live, proven gcc-2.7.2 idioms — apply them) ===
{COOKBOOK}

=== WORKED EXAMPLES (real byte-matches from this game, same toolchain) ===
{examples}

=== YOUR TARGET: {t['name']} @ {t.get('addr')} ({t.get('nins')} ins, class {t.get('class')}) ===
TARGET ASM (ground truth; "/* off vaddr WORD */ mnemonic" = one encoded instruction):
{asm_text}

GHIDRA-C SCAFFOLD (types/locals/callees — NOT byte-accurate):
{ghidra_text}

Now write byte-matching C for {t['name']}:
- common.h types are predefined — declare only OTHER externs (callees/globals); don't fret callee arg types, the gate reconciles them.
- First two lines: // @class: <regalloc-order|schedule|struct|loose-typing|plumbing|other>  then  // @stuck: <residual or "none — MATCH">
- Reply with ONLY one ```c block."""


# LEAN mode — keep in sync with tools/format_finetune.py (train/inference must match). The
# "translate EVERY instruction / never-empty" clause was added 2026-06-30 after a prompt test took
# the small-leaf band 0/3 -> 2/3 MATCH (the v2 corpus overfit an empty `void f(void){}` leaf pattern;
# the instruction it most often dropped was the return value / a store). MIRROR this in format_finetune
# before retraining corpus-v3, else train/inference drift.
LEAN_SYS = ("You are an expert at MATCHING decompilation for MIPS (PSX, gcc-2.7.2 -O2 -G0 -mips1 -mcpu=3000 "
            "-msoft-float + maspsx). Given a function's target assembly, output C that the pinned toolchain "
            "compiles to BYTE-IDENTICAL machine code. The types u8/u16/u32/s8/s16/s32/f32/s64/u64/f64 are "
            "predefined (common.h). Output ONLY the C (the function definition + any externs it needs). "
            "Translate EVERY instruction — NEVER output an empty body. A `jr $ra` with `addiu $v0,$zero,N` "
            "in its delay slot is `return N;`; a `sw/sh/sb $aK,off($a0)` is a store "
            "`*(T*)((u8*)arg0+off)=argK;` (T=s32/s16/s8); a `lw/lh/lb` is a load. Produce C whose compiled "
            "output IS the shown instructions.")


# Bridge: real OPEN stubs are splat .s (headers, 3-field comment, spaced operands, resolved jal); the
# fine-tuned model trained on objdump/corpus style. NORMALIZE_ASM=1 converts .s -> that style so a
# fine-tuned model sees its training format on real stubs (no retrain needed).
NORMALIZE = os.environ.get('NORMALIZE_ASM', '0') != '0'


def normalize_asm(asm):
    out = []
    for line in asm.splitlines():
        m = re.match(r'\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/\s*(\S.*)', line)
        if not m:
            continue                                   # drop glabel/endlabel/nonmatching/blank headers
        vaddr, leword, rest = m.group(1).upper(), m.group(2).upper(), m.group(3).strip()
        parts = rest.split(None, 1)
        mnem = parts[0]
        ops = re.sub(r',\s+', ',', parts[1]) if len(parts) > 1 else ''   # "$sp, $sp" -> "$sp,$sp"
        out.append(('/* %s %s */  %-9s %s' % (vaddr, leword, mnem, ops)).rstrip())
    return '\n'.join(out)


def build_user_lean(t, asm_text, ghidra_text):
    asm = normalize_asm(asm_text) if NORMALIZE else asm_text.strip()
    return ("Target assembly (each `/* vaddr WORD */ mnemonic` line is one encoded instruction):\n"
            + asm + "\n\nWrite the byte-matching C function.")


def call_api(messages, max_tokens=512, temperature=TEMP, timeout=600):  # 512 caps the no-stop-token ramble
                                                                         # (a small-fn draft is ~100-300 toks;
                                                                         # giants pass an explicit larger cap)
    body = json.dumps({'model': MODEL, 'messages': messages,
                       'max_tokens': max_tokens, 'temperature': temperature}).encode()
    req = urllib.request.Request(API_BASE + '/chat/completions', data=body,
                                 headers={'Content-Type': 'application/json',
                                          'Authorization': 'Bearer ' + (API_KEY or 'none')})
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            d = json.loads(r.read())
        return d['choices'][0]['message']['content']
    except urllib.error.URLError as e:
        print('  API error:', e, file=sys.stderr)
        return None


def extract_code(text):
    """Pull the C from a model reply: strip <think> blocks, take the largest ```c fence, else raw."""
    if not text:
        return ''
    text = re.sub(r'<think>.*?</think>', '', text, flags=re.S)
    blocks = re.findall(r'```(?:c|cpp|C)?\s*\n(.*?)```', text, flags=re.S)
    if blocks:
        return max(blocks, key=len).strip() + '\n'
    return text.strip() + '\n'   # model ignored the fence instruction; use as-is


def match_one(fn, cfile, asm_subdir):
    """('match',0,out) | ('near',k,out) | ('fail',None,out) via match_one (relocation-masked)."""
    p = subprocess.run([PY, 'tools/match_one.py', fn, '--c', cfile, '--asm-subdir', asm_subdir],
                       capture_output=True, text=True, cwd=REPO)
    out = p.stdout + p.stderr
    if re.search(r'MATCH \(\d+ ins\)', out):
        return ('match', 0, out)
    m = re.search(r'(\d+) mismatched', out)
    if m:
        return ('near', int(m.group(1)), out)
    return ('fail', None, out)


def draft_one(t, outdir, iters):
    fn = t['name']
    asm_path = os.path.join(REPO, t['asm'])
    asm_subdir = os.path.dirname(t['asm'])
    gc_path = os.path.join(REPO, t.get('ghidra_c', ''))
    asm_text = open(asm_path).read() if os.path.exists(asm_path) else '(asm missing)'
    ghidra_text = open(gc_path).read() if (t.get('ghidra_c') and os.path.isfile(gc_path)) else '(no ghidra-c)'

    cfile = os.path.join(outdir, fn + '.c')
    sys_msg = LEAN_SYS if LEAN else SYS
    usr = (build_user_lean if LEAN else build_user)(t, asm_text, ghidra_text)
    messages = [{'role': 'system', 'content': sys_msg},
                {'role': 'user', 'content': usr}]
    best = (None, 10 ** 9)   # (code, closeness)

    for i in range(max(1, iters)):
        reply = call_api(messages)
        code = extract_code(reply)
        if not code.strip():
            print('  %s: empty reply (iter %d)' % (fn, i)); break
        open(cfile, 'w').write(code)
        status, close, out = match_one(fn, cfile, asm_subdir)
        score = 0 if status == 'match' else (close if status == 'near' else 10 ** 8)
        if score < best[1]:
            best = (code, score)
        tag = 'MATCH' if status == 'match' else ('near %d' % close if status == 'near' else 'compile-fail')
        print('  %s iter %d: %s' % (fn, i, tag))
        if status == 'match':
            break
        if i < iters - 1:   # feed the diff back for a revision (context-aware retry)
            diff = '\n'.join(out.splitlines()[:45])
            messages += [{'role': 'assistant', 'content': '```c\n' + code + '```'},
                         {'role': 'user', 'content':
                          'Not byte-identical yet. match_one diff (idx | MINE | TARGET):\n' + diff +
                          '\nApply the toolkit (register pins, width/loop-form/schedule fixes) and reply '
                          'with the corrected full function in ONE ```c block.'}]

    # write the BEST draft seen (not necessarily the last)
    if best[0] is not None:
        open(cfile, 'w').write(best[0])
    return best[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--targets', default='.run/ab-exp/targets20.json')
    ap.add_argument('--out', default='.run/ab-exp/local')
    ap.add_argument('--iters', type=int, default=4, help='max draft↔match_one rounds per function')
    ap.add_argument('--limit', type=int, default=0, help='only the first N targets (0 = all)')
    a = ap.parse_args()

    os.makedirs(os.path.join(REPO, a.out), exist_ok=True)
    outdir = os.path.join(REPO, a.out)
    targets = json.load(open(os.path.join(REPO, a.targets)))
    if a.limit:
        targets = targets[:a.limit]
    print('api_draft: %s @ %s -> %d targets, %d iters -> %s' % (MODEL, API_BASE, len(targets), a.iters, a.out))

    t0 = time.time()
    matched = 0
    for t in targets:
        close = draft_one(t, outdir, a.iters)
        matched += (close == 0)
    print('\napi_draft done: %d/%d match_one MATCH in %.0fs. Now: tools/ab_score.py --arms ... %s'
          % (matched, len(targets), time.time() - t0, os.path.basename(a.out)))


if __name__ == '__main__':
    main()
