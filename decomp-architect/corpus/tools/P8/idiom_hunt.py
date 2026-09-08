#!/usr/bin/env python3
"""idiom_hunt.py — Phase 23 T10.7: use a REASONING model (GLM5.2) to DISCOVER new gcc-2.7.2 idioms from
grouped near-misses, not to bank random functions (Drew's reframe: idioms compound, fleet% is linear; R16).

The backlog holds ~3100 near-misses (median closeness 1 — often ONE instruction off byte-match), classified
by residual class (regalloc-order / schedule / iv-combine / remat / struct / ... + a large unclassified pool).
Grouping near-misses of the SAME class and asking a reasoning model "what reusable C transformation makes
gcc-2.7.2 emit these bytes?" turns GLM from a drafter into an IDIOM RESEARCHER: one discovered idiom banks a
whole class (now + forever + for free v3). Some classes are intrinsic walls (def-side, narrow-param) — GLM
CONFIRMS those; that is also progress.

Per batch (same-class near-misses): assemble exemplars (asm + best-draft + the match_one diff) -> GLM ->
save REASONING (.run/idiom_hunt/, the idiom deliverable) -> parse the named idiom + per-fn corrected C ->
byte-gate the corrected C in each fn's binary (gate_stage, sole arbiter G3/P9). Reports idioms found, banks
(validation), and $ spent. **HARD --budget cap** (stops launching batches once spend hits it) — never a
surprise bill; calibrate cheap, scale only if the idiom yield-per-dollar pays.

Env: API_BASE, MODEL, API_KEY (OpenRouter), MAXTOK (default 24000). Usage:
  API_BASE=https://openrouter.ai/api/v1 MODEL=z-ai/glm-5.2 API_KEY=... \
    tools/idiom_hunt.py --max-close 3 --min-nins 16 --count 30 --batch 6 --budget 8 --workers 3
"""
import argparse, glob, json, os, re, subprocess, sys, threading, urllib.request
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = '.venv/bin/python'
API_BASE = os.environ.get('API_BASE', '').rstrip('/')
API_KEY = os.environ.get('API_KEY', 'none')
MODEL = os.environ.get('MODEL', '')
MAXTOK = int(os.environ.get('MAXTOK', '24000'))
OUT = os.path.join(REPO, '.run/idiom_hunt')
COST = [0.0]
_LK = threading.Lock()

SYS = ("You are a PS1 matching-decompilation expert who discovers REUSABLE compiler idioms. The compiler is "
       "gcc-2.7.2 (-O2 -G0 -mips1, C89/K&R). Given several functions that are ALMOST byte-identical to the "
       "target MIPS (a few instructions off, same residual class), you find the ONE reusable C transformation "
       "that makes gcc emit the exact target bytes, name it, and apply it. Bytes are truth; never hand-wave.")


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def cookbook_known():
    """The idiom § headers we ALREADY have — so GLM finds what's NEEDED (new, or a known one applied), not
    re-derive the obvious. Condensed from docs/matching-cookbook.md."""
    try:
        heads = [l.strip('# ').strip() for l in open(os.path.join(REPO, 'docs/matching-cookbook.md'))
                 if re.match(r'#+\s*§', l)]
        return '\n'.join('- ' + h[:110] for h in heads)
    except Exception:
        return '(cookbook unavailable)'


def call(messages, retries=2):
    body = json.dumps({'model': MODEL, 'messages': messages, 'max_tokens': MAXTOK, 'temperature': 0.2}).encode()
    for attempt in range(retries + 1):
        try:
            req = urllib.request.Request(API_BASE + '/chat/completions', data=body,
                                         headers={'Content-Type': 'application/json',
                                                  'Authorization': 'Bearer ' + API_KEY})
            with urllib.request.urlopen(req, timeout=1800) as r:
                d = json.loads(r.read())
            m = d['choices'][0]['message']
            with _LK:
                COST[0] += (d.get('usage') or {}).get('cost', 0) or 0
            return (m.get('content') or ''), (m.get('reasoning') or '')
        except Exception as e:
            if attempt < retries:
                continue
            return '', f'[call error: {e}]'


def asm_of(binary, fn):
    hits = glob.glob(os.path.join(REPO, f'asm/{binary}/nonmatchings/*/{fn}.s'))
    if not hits:
        return '(asm not found)', None
    return open(hits[0]).read(), os.path.relpath(os.path.dirname(hits[0]), REPO)


def diff_of(fn, draft_path, asm_subdir):
    if not (draft_path and os.path.exists(os.path.join(REPO, draft_path)) and asm_subdir):
        return '(no diff)'
    r = sh([PY, 'tools/match_one.py', fn, '--c', draft_path, '--asm-subdir', asm_subdir], timeout=180)
    return '\n'.join((r.stdout + r.stderr).splitlines()[:40])


def build_user(klass, items):
    ex = []
    for it in items:
        draft = ''
        p = it.get('best_draft')
        if p and os.path.exists(os.path.join(REPO, p)):
            draft = open(os.path.join(REPO, p)).read()
        ex.append(f"""----- {it['name']} (binary {it['binary']}, {it.get('nins')} ins, closeness "
{it.get('closeness')}) -----
--- TARGET MIPS ---
{it['asm']}
--- CLOSEST C SO FAR ---
{draft or '(none)'}
--- match_one DIFF (idx | MINE | TARGET) ---
{it['diff']}
""")
    return f"""These {len(items)} functions share the residual class **{klass}** — each is a few instructions
off byte-identical (see the diffs). Find the ONE reusable gcc-2.7.2 C idiom that makes the compiler emit the
exact target bytes for this class, then apply it.

Idioms we ALREADY have (find what's NEEDED — a NEW idiom, or one of these applied; if the class is an
intrinsic wall no C can steer, say so and explain why):
{cookbook_known()}

{chr(10).join(ex)}

OUTPUT:
1) `## IDIOM: <short name>` then 2-5 sentences: the gcc-2.7.2 behavior, the reusable C transformation that
   triggers the wanted bytes, and when it applies. If the class is an intrinsic wall, write `## WALL:` + why.
2) For EACH function, a fenced block `// FN: func_XXXX` then the corrected full C:
   ```c
   // FN: func_XXXXXXXX
   <corrected C>
   ```
Only change what the idiom dictates; keep every other instruction identical.
"""


def parse_fns(content):
    """map func_XXXX -> corrected C, from ```c blocks tagged `// FN: func_XXXX`."""
    out = {}
    for blk in re.findall(r'```c?\s*\n(.*?)```', content, re.S):
        m = re.search(r'//\s*FN:\s*(func_[0-9A-Fa-f]+)', blk)
        if m:
            out[m.group(1)] = re.sub(r'//\s*FN:\s*func_[0-9A-Fa-f]+\s*\n', '', blk, count=1)
    return out


def idiom_name(content):
    m = re.search(r'##\s*(IDIOM|WALL):\s*(.+)', content)
    return (m.group(1) + ': ' + m.group(2).strip()[:80]) if m else '(none stated)'


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--max-close', type=int, default=3, help='only near-misses within N mismatches')
    ap.add_argument('--min-nins', type=int, default=16, help='hard band only')
    ap.add_argument('--max-nins', type=int, default=150)
    ap.add_argument('--class', dest='klass', default=None, help='restrict to one residual class')
    ap.add_argument('--count', type=int, default=30, help='near-misses to pull')
    ap.add_argument('--batch', type=int, default=6, help='near-misses per GLM call (same class)')
    ap.add_argument('--budget', type=float, default=8.0, help='HARD $ cap — stop launching batches at this spend')
    ap.add_argument('--workers', type=int, default=3)
    a = ap.parse_args()
    if not (API_BASE and MODEL):
        sys.exit('set API_BASE, MODEL, API_KEY')
    os.makedirs(OUT, exist_ok=True)

    recs = [r for r in backlog.load_best()
            if r.get('status') == 'near' and isinstance(r.get('closeness'), int)
            and r['closeness'] <= a.max_close and r.get('best_draft')
            and a.min_nins <= (r.get('nins') or 0) <= a.max_nins
            and (not a.klass or (r.get('klass') or '').split()[0] == a.klass)]
    for r in recs:
        r['binary'] = r.get('binary') or 'ov_SC01_077'   # legacy records default to the canonical binary
    # group by class, then chunk each class into batches
    byc = {}
    for r in sorted(recs, key=lambda x: (x.get('klass') or 'z', x['closeness'])):
        byc.setdefault((r.get('klass') or 'unclassified').split()[0], []).append(r)
    batches = []
    taken = 0
    for kl, lst in sorted(byc.items(), key=lambda kv: -len(kv[1])):
        for i in range(0, len(lst), a.batch):
            if taken >= a.count:
                break
            grp = lst[i:i + a.batch]
            batches.append((kl, grp)); taken += len(grp)
    print(f'idiom_hunt: {len(recs)} eligible near-misses -> {len(batches)} batches '
          f'(classes: {sorted(byc)[:8]}), budget ${a.budget}')

    # enrich each item with asm + diff
    for _, grp in batches:
        for it in grp:
            it['asm'], sub = asm_of(it['binary'], it['name'])
            it['diff'] = diff_of(it['name'], it.get('best_draft'), sub)

    results = []

    def run_batch(idx_kl_grp):
        idx, (kl, grp) = idx_kl_grp
        if COST[0] >= a.budget:
            return None
        content, reasoning = call([{'role': 'system', 'content': SYS},
                                   {'role': 'user', 'content': build_user(kl, grp)}])
        open(os.path.join(OUT, f'batch{idx:02d}_{kl}.txt'), 'w').write(
            f'=== class {kl} ({len(grp)} fns) ===\nIDIOM: {idiom_name(content)}\n\n=== reasoning ===\n{reasoning}\n\n=== content ===\n{content}\n')
        return (idx, kl, grp, content)

    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for res in ex.map(run_batch, list(enumerate(batches))):
            if res:
                results.append(res)

    # validate: gate the corrected C per binary (gate_stage recovery + whole-binary byte-gate)
    import gate_stage
    banked_all, idioms = [], []
    bydir = {}
    for idx, kl, grp, content in results:
        idioms.append((kl, idiom_name(content)))
        fns = parse_fns(content)
        for it in grp:
            c = fns.get(it['name'])
            if not c:
                continue
            d = os.path.join(OUT, 'drafts', it['binary'])
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, it['name'] + '.c'), 'w').write(c)
            bydir.setdefault(it['binary'], d)
    for b, d in sorted(bydir.items()):
        try:
            r = gate_stage.run_gate(os.path.relpath(d, REPO), binary=b, propagate=False, commit=False,
                                    compute_fleet=False, lock_path=f'.run/auto/gate.{b}.lock')
            banked_all += r.get('verified', [])
        except Exception as e:
            print(f'  [gate {b}: {e}]')

    print(f'\n=== idiom_hunt summary ===  cost ${COST[0]:.3f}')
    print(f'idioms/verdicts proposed ({len(idioms)}):')
    for kl, nm in idioms:
        print(f'  [{kl}] {nm}')
    print(f'validation banks (idioms that byte-gated): {len(banked_all)} — {" ".join(banked_all) or "(none)"}')
    print(f'reasoning + idioms saved -> {OUT}/  (review + distill the winners into cookbook §)')


if __name__ == '__main__':
    main()
