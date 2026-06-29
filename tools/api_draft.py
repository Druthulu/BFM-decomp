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

# Condensed §17–20 toolkit (worker_wave inlines file refs; a no-tool model needs the text inline).
TOOLKIT = """THE TOOLKIT (the high-leverage gcc-2.7.2 matching moves):
- Register-allocation ORDER: if call-crossing locals land in the wrong saved reg, PIN them:
  `register s32 v __asm__("$16");`  ($16=$s0,$17=$s1,$18=$s2,...). This is the highest-reach lever.
- Array-of-struct %lo-fold: for indexed global access declare `extern Struct base[];`
  (sizeof(Struct)==stride) and write `base[i].field` — folds %lo into the load/store. Do NOT write
  `*(T*)(&sym + i*stride)` (materializes &sym, adds an instruction).
- for(init;cond;upd) vs do-while schedule the back-branch into the delay slot differently — pick the
  loop form the target's branch layout implies.
- Independent statements emit in source order — reorder to match the target.
- Pick exact integer widths from the loads: lhu->unsigned short, lh->short, lbu->unsigned char, lb->char.
- Don't fret callee extern types; focus on the BODY codegen (a later gate reconciles declarations)."""

SYS = ("You are an expert MIPS (PSX, gcc-2.7.2 -O2) matching-decompilation engineer. You write C that "
       "compiles to BYTE-IDENTICAL machine code vs a target. Reply with ONLY the C (the function "
       "definition + any externs it needs) in a single ```c code block — no prose.")


def build_user(t, asm_text, ghidra_text):
    return f"""Match ONE MIPS function (overlay ov_SC01_077) to BYTE-IDENTICAL machine code under:
gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -msoft-float + maspsx --aspsx-version=2.56 --expand-div.

TARGET: {t['name']} @ {t.get('addr')} — {t.get('nins')} instructions, class hint "{t.get('class')}".

Target asm (ground truth; each "/* off vaddr WORD */ mnemonic" line is one encoded instruction):
{asm_text}

Ghidra-C reference (types/locals/callee names — NOT byte-accurate, a scaffold):
{ghidra_text}

{TOOLKIT}

Write your best C for {t['name']}. Start with two comment lines:
// @class: <regalloc-order|schedule|struct|loose-typing|plumbing|other>
// @stuck: <one line on the residual, or "none — MATCH">
Then the function. Reply with ONLY one ```c block."""


def call_api(messages, max_tokens=4096, temperature=TEMP, timeout=600):
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
    ghidra_text = open(gc_path).read() if os.path.exists(gc_path) else '(no ghidra-c)'

    cfile = os.path.join(outdir, fn + '.c')
    messages = [{'role': 'system', 'content': SYS},
                {'role': 'user', 'content': build_user(t, asm_text, ghidra_text)}]
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
