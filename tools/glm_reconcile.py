#!/usr/bin/env python3
"""glm_reconcile.py — Option-3 (Phase 23 T10.7): aim a REASONING model at the DEF-side loose-typing WALL,
and CAPTURE its reasoning for the idiom flywheel (R16).

The def-side wall (Phase 16/20, re-confirmed by the T10.7 A/B): a byte-correct function body cannot be
banked because the overlay translation unit already declares the function (or its callees/data) with
signatures/types that conflict with the body's true form -> gcc-2.7.2 C89 `conflicting types`. This caps
ANY drafter -- it is a DECLARATION-reconciliation problem, per-function and situation-specific (mechanical
`fix_arity_callers --any-proto` recovers ~0). "Loose-typing reconciliation is a reasoning problem" (Fable5
review Sec 4.1): give GLM5.2 the body + the actual conflicting declarations + the legal byte-neutral moves,
and let it reason out a consistent, buildable, byte-identical set.

Per function: assemble context -> GLM -> save REASONING (.run/glm_reason/<fn>.txt, the idiom source) ->
parse a ```c block (reconciled C) + a ```relax block (forward-decls to K&R no-proto, in ANY TU file) ->
snapshot the TU, apply, whole-binary byte-gate (harvest_verify, sole arbiter G3/P9) -> keep iff
byte-identical, else restore the snapshot. Final check-all proves the shared-header relaxations are fleet-safe.

Env: API_BASE, MODEL, API_KEY (OpenRouter), MAXTOK (default 32000). Usage:
  API_BASE=https://openrouter.ai/api/v1 MODEL=z-ai/glm-5.2 API_KEY=... \
    tools/glm_reconcile.py --binary ov_SC01_077 --funcs func_A,func_B --bodies .run/ab_glm
"""
import argparse, glob, json, os, re, subprocess, sys, urllib.request

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = '.venv/bin/python'
API_BASE = os.environ.get('API_BASE', '').rstrip('/')
API_KEY = os.environ.get('API_KEY', 'none')
MODEL = os.environ.get('MODEL', '')
MAXTOK = int(os.environ.get('MAXTOK', '32000'))
EC = os.path.join(REPO, 'src/shared/engine_core.h')
REASON_DIR = os.path.join(REPO, '.run/glm_reason')
DRAFTS = os.path.join(REPO, '.run/glm_recon')
COST = [0.0]

TOOLKIT = """LEGAL byte-neutral reconciliation moves under gcc-2.7.2 -O2 -G0 -mips1 (C89/K&R):
- Relax a conflicting file-scope forward-decl to K&R no-prototype: `extern R func_X(void);` OR
  `extern R func_X(T,...);` -> `extern R func_X();`. Byte-neutral for callers ONLY IF the real def's
  params are default-promotion-safe (int/s32/u32/long/pointer). char/short/s8/s16/u8/u16/float BY VALUE
  are NOT safe (K&R default-promotes them) -> do NOT no-proto those; that is the intrinsic narrow-param wall.
- Match a DATA extern's type to what the TU already declares: same-width int/s32/u32 (and their pointers)
  emit identical MIPS, so declare D_x with the type already present in the TU to avoid `conflicting types`.
- Cast a call site to the intended fn-ptr type: `((R(*)(A))func_X)(args)` -- gcc folds the cast of a known
  symbol to a direct `jal`, byte-neutral. Use when a callee is a DEFINITION (can't be re-declared) or its
  canonical decl differs from how THIS body must call it.
- NEVER change the function BODY's computation or control flow (it is already byte-correct); reconcile ONLY
  declarations, extern types, and call-site casts.
The whole-binary SHA1 byte-gate is the sole arbiter (G3/P9): a wrong reconciliation just fails."""

SYS = ("You are a PS1 matching-decompilation expert. The original compiler is gcc-2.7.2 (-O2 -G0 -mips1, "
       "C89/K&R). You reconcile C DECLARATIONS so a byte-correct function compiles into its translation "
       "unit while every function stays byte-for-byte identical. You never change verified computation.")


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def good_sha(b):
    return open(os.path.join(REPO, f'config/check.{b}.sha')).read().split()[0]


def call(messages, retries=2):
    body = json.dumps({'model': MODEL, 'messages': messages,
                       'max_tokens': MAXTOK, 'temperature': 0.2}).encode()
    for attempt in range(retries + 1):
        try:
            req = urllib.request.Request(API_BASE + '/chat/completions', data=body,
                                         headers={'Content-Type': 'application/json',
                                                  'Authorization': 'Bearer ' + API_KEY})
            with urllib.request.urlopen(req, timeout=1800) as r:
                d = json.loads(r.read())
            m = d['choices'][0]['message']
            COST[0] += (d.get('usage') or {}).get('cost', 0) or 0
            return (m.get('content') or ''), (m.get('reasoning') or '')
        except Exception as e:
            if attempt < retries:
                continue
            print(f'  [call error after {retries+1} tries: {e}]')
            return '', ''


def tu_files(binary):
    return [EC] + sorted(glob.glob(os.path.join(REPO, f'src/{binary}/{binary}*.c')))


def snapshot(binary):
    return {f: open(f).read() for f in tu_files(binary)}


def restore(snap):
    for f, t in snap.items():
        open(f, 'w').write(t)


def relax_in_tu(binary, fns):
    """Relax `extern <ret> func_X(<params>);` -> `extern <ret> func_X();` in EVERY TU file (engine_core.h
    AND the overlay .c) — the conflicting forward-decl can live in either (fix_arity_callers only did EC)."""
    for f in tu_files(binary):
        txt = orig = open(f).read()
        for fn in fns:
            m = re.search(r'func_([0-9A-Fa-f]+)', fn)
            if not m:
                continue
            ad = m.group(1)
            txt = re.sub(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*[^;)]+?\s*(\)\s*;)', r'\1\2', txt, flags=re.I)
        if txt != orig:
            open(f, 'w').write(txt)


def find_asm(binary, fn):
    hits = glob.glob(os.path.join(REPO, f'asm/{binary}/nonmatchings/*/{fn}.s'))
    return open(hits[0]).read() if hits else '(asm not found)'


def decl_context(binary, fn, body):
    syms = set(re.findall(r'\b(?:func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b', body)) | {fn}
    pat = re.compile(r'\b(' + '|'.join(re.escape(s) for s in syms) + r')\b')
    seen, out = set(), []
    for f in tu_files(binary):
        tag = os.path.basename(f)
        for ln in open(f):
            s = ln.rstrip('\n').strip(' \\\t')
            if not pat.search(s) or 'INCLUDE_ASM' in s:
                continue
            if 'extern' in s or 'DEFINE_func_' in s or re.search(r'\b(?:void|s32|u32|s16|u16|s8|u8|int|char|short|float|struct)\b[^;{]*\(', s):
                key = s[:160]
                if key not in seen:
                    seen.add(key); out.append(f'[{tag}] {key}')
    return '\n'.join(out[:140]) or '(no existing decls found — symbols may be undeclared in the TU)'


def build_user(fn, binary, asm, body, decls):
    return f"""FUNCTION {fn} in overlay {binary}. Its body below is ALREADY byte-correct (matches the
target MIPS), but the overlay translation unit does NOT compile because its declarations conflict with
declarations already present in the TU (from other banked functions). Produce a version that COMPILES in
the whole TU and stays byte-for-byte identical, changing ONLY declarations / extern types / call-site casts.

=== TARGET MIPS (ground truth) ===
{asm}

=== BYTE-CORRECT BODY (keep its computation; reconcile its declarations) ===
{body}

=== EXISTING TU DECLARATIONS that conflict / are relevant ===
{decls}

=== {TOOLKIT} ===

Reason first: name each conflicting declaration and the exact move that resolves it. Then output EXACTLY:
1) a ```c block — the final self-contained C for {fn}: the definition (computation unchanged) plus the
   externs it needs, with types/prototypes CONSISTENT with the TU decls above (reuse their types).
2) a ```relax block — zero or more lines, each a func_XXXX whose EXISTING forward-declaration (in
   engine_core.h OR the overlay .c) must be relaxed to K&R no-prototype `()` (only promotion-safe defs).
"""


def gate_fn(binary):
    entries = [(f'src/{binary}/{binary}.c', f'asm/{binary}/nonmatchings/{binary}')]
    for p in sorted(glob.glob(os.path.join(REPO, f'src/{binary}/{binary}_*.c'))):
        n = os.path.basename(p)[:-2]
        sub = f'asm/{binary}/nonmatchings/{n}'
        if os.path.isdir(os.path.join(REPO, sub)):
            entries.append((f'src/{binary}/{n}.c', sub))
    banked = []
    for src, asm in entries:
        sh([PY, 'tools/harvest_verify.py', '--binary', binary, '--src', src, '--asm-subdir', asm,
            '--out', f'build/{binary}/{binary}', '--good-sha', good_sha(binary),
            '--drafts', os.path.relpath(DRAFTS, REPO), '--chunk', '1',
            '--verified-out', '.run/glm_recon_v.txt', '--failed-out', '.run/glm_recon_f.txt'], timeout=1800)
        vp = os.path.join(REPO, '.run/glm_recon_v.txt')
        banked += [w for w in (open(vp).read().split() if os.path.exists(vp) else []) if w.startswith('func_')]
    return banked


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--binary', default='ov_SC01_077')
    ap.add_argument('--funcs', required=True)
    ap.add_argument('--bodies', default='.run/ab_glm')
    a = ap.parse_args()
    if not (API_BASE and MODEL):
        sys.exit('set API_BASE, MODEL, API_KEY')
    os.makedirs(REASON_DIR, exist_ok=True); os.makedirs(DRAFTS, exist_ok=True)
    funcs = [x.strip() for x in a.funcs.split(',') if x.strip()]
    banked_all, relaxed_all = [], []

    for fn in funcs:
        bpath = os.path.join(REPO, a.bodies, fn + '.c')
        body = open(bpath).read() if os.path.exists(bpath) else '(no prior body — draft it byte-correct from the asm)'
        content, reasoning = call([{'role': 'system', 'content': SYS},
                                   {'role': 'user', 'content': build_user(fn, a.binary, find_asm(a.binary, fn), body,
                                                                          decl_context(a.binary, fn, body))}])
        open(os.path.join(REASON_DIR, fn + '.txt'), 'w').write(
            f'=== {fn} reasoning ({len(reasoning)} chars) ===\n{reasoning}\n\n=== content ===\n{content}\n')
        cblocks = re.findall(r'```c?\s*\n(.*?)```', content, re.S)
        relax_funcs = re.findall(r'func_[0-9A-Fa-f]+', '\n'.join(re.findall(r'```relax\s*\n(.*?)```', content, re.S)))
        if not cblocks:
            print(f'  {fn}: no C block returned'); continue
        snap = snapshot(a.binary)
        if relax_funcs:
            relax_in_tu(a.binary, set(relax_funcs))
        for old in glob.glob(os.path.join(DRAFTS, '*.c')):
            os.remove(old)
        open(os.path.join(DRAFTS, fn + '.c'), 'w').write(max(cblocks, key=len))
        if fn in gate_fn(a.binary):
            banked_all.append(fn); relaxed_all += relax_funcs
            print(f'  {fn}: BANKED (relax={relax_funcs or "none"})')
        else:
            restore(snap)
            print(f'  {fn}: fail (reconciliation did not byte-gate)')

    print(f'\nglm_reconcile: BANKED {len(banked_all)}/{len(funcs)}: {" ".join(banked_all) or "(none)"}')
    print(f'  relaxed: {sorted(set(relaxed_all)) or "(none)"}  cost ${COST[0]:.4f}  reasoning -> {REASON_DIR}/')
    if banked_all:
        print('  fleet-safety check-all (engine_core.h relaxations are shared)...')
        print('  ' + (sh(['make', 'check-all'], timeout=3600).stdout.strip().splitlines() or ['?'])[-1])


if __name__ == '__main__':
    main()
