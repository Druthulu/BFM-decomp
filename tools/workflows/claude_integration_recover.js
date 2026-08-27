export const meta = {
  name: 'claude-integration-recover',
  description: 'Recover wave drafts that are BYTE-CORRECT in isolation (match_one MATCH) but CC1-FAIL in their real TU: one agent per function fixes the DRAFT-side declaration conflict, never a shared header',
  phases: [
    { title: 'Recover', detail: 'one agent per integration-blocked draft; fix the draft until the real TU compiles AND match_one still MATCHes' },
  ],
}
// args: { items: [{fn, binary, draft, sub, blocker}], outdir: '.run/<wave>/integ_fixed' }
// Produced by staging every un-banked draft whose match_one says MATCH (bucket "integration").
const REPO = '/home/musashi/bfm-decomp'
const OUT = args.outdir
const VERDICT = {
  type: 'object',
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['FIXED', 'STILL-BLOCKED', 'NOT-INTEGRATION'] },
    blocker: { type: 'string' },
    fix: { type: 'string' },
    tu_compiles: { type: 'boolean' },
    match_one: { type: 'string' },
    out_path: { type: 'string' },
    note: { type: 'string' },
  },
  required: ['fn', 'status', 'blocker', 'fix', 'tu_compiles', 'match_one', 'out_path', 'note'],
}
phase('Recover')
log(`${args.items.length} integration-blocked draft(s) to recover into ${OUT}`)
const results = await parallel(args.items.map(it => () => agent(
`You are recovering ONE byte-proven decompilation draft in the Brave Fencer Musashi repo at ${REPO}.

FUNCTION: ${it.fn}   BINARY: ${it.binary}
DRAFT (byte-correct in ISOLATION — match_one says MATCH, closeness 0): ${REPO}/${it.draft}
DESTINATION TU: ${it.tu}
STATIC BLOCKER CLASS reported by tools/recover_integration.py: ${it.blocker}

THE SITUATION. The draft's function BODY is already byte-identical to the target — that is proven and
is NOT in question. It was refused by the whole-binary gate because, when pasted into its real TU, the
translation unit does not COMPILE: the draft's own declarations (its externs, its local typedefs, its
callee prototypes) conflict with declarations the TU or its headers already carry.

YOUR JOB: change the DRAFT ONLY, until the real TU compiles AND the body is still byte-identical.

  1. See the real error:
       cd ${REPO} && .venv/bin/python tools/recover_integration.py --draft-dir <a dir containing just your draft, laid out as <dir>/${it.binary}/${it.fn}.c> --binary ${it.binary} --no-propagate --probe-only
     Read .run/recover/*/blockers.json for the per-symbol detail. You may also just read the TU and
     its headers directly (src/${it.binary}/, src/shared/engine_core.h) and compare every declaration
     your draft makes against what is already declared there.
  2. Fix the draft the CHEAPEST way that preserves the bytes, in this order of preference:
       (a) DELETE a redundant declaration from your draft and rely on the TU's existing one (law 2 —
           the TU's spelling is authoritative and adopting it is the point);
       (b) adopt the TU's exact spelling for a type/typedef your draft re-declared differently;
       (c) if the TU's own declaration of YOUR function is what conflicts, prefer a cast-at-use or a
           no-proto form over changing the shared header.
  3. NEVER edit src/, config/, include/, asm/ or build/. NEVER touch src/shared/engine_core.h or any
     other binary's files. If the only possible fix is a shared-header edit, STOP and report
     STILL-BLOCKED with that finding — a fleet-tier edit is not yours to make (blast-radius law §65a).
  4. Re-verify BOTH oracles before you finish:
       .venv/bin/python tools/match_one.py ${it.fn} --c <your fixed draft> --asm-subdir ${it.sub} --json
     must still print "status": "match", closeness 0 — if your fix changed the bytes, it is wrong; and
     the probe from step 1 must report MATCH (not CC1-FAIL) for the real TU.
  5. Write the fixed draft to ${REPO}/${OUT}/${it.binary}/${it.fn}.c (mkdir -p the dir).

Work only under ${REPO}/${OUT}/ and your own scratch under ${REPO}/${OUT}/scratch_${it.fn}/.
Your final answer is the JSON verdict only: fn, status (FIXED only if BOTH oracles pass; STILL-BLOCKED
if it needs a shared-header edit or you could not fix it; NOT-INTEGRATION if the real TU compiles and
the body actually DIFFs), blocker (the concrete conflict you found, e.g. "TU declares extern s32 f(s32),
definition is void"), fix (what you changed, one line), tu_compiles, match_one ("MATCH"/"near N"/...),
out_path, note (one line).`,
  { label: `recover:${it.binary}:${it.fn}`, phase: 'Recover', model: 'sonnet', schema: VERDICT }
).then(v => v || { fn: it.fn, status: 'STILL-BLOCKED', blocker: it.blocker, fix: '', tu_compiles: false, match_one: '', out_path: '', note: 'agent returned null' })
 .catch(e => ({ fn: it.fn, status: 'STILL-BLOCKED', blocker: it.blocker, fix: '', tu_compiles: false, match_one: '', out_path: '', note: 'agent error: ' + String(e).slice(0, 120) }))))
const t = {}
for (const r of results.filter(Boolean)) t[r.status] = (t[r.status] || 0) + 1
log('recovery self-reports: ' + JSON.stringify(t) + ' (the whole-binary gate decides — R14)')
return { outdir: OUT, results }
