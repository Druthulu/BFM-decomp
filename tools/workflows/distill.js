export const meta = {
  name: 'distill',
  description: 'Phase-21 learning flywheel: after a wave gates, extract any NEW byte-verified gcc-quirk idiom from the wave\'s banked matches and append it to the cookbook, so the next wave inherits it.',
  phases: [{ title: 'Distill', detail: 'one agent reads the banked drafts + cookbook, appends a new idiom' }],
}

// args = { draftsDir, verified: [fn,...] }  (verified = the fns the byte-gate banked this wave)
// Returns { appended: bool, idiom: string|null, note: string }.
const A = typeof args === 'string' ? JSON.parse(args) : (args || {})
const draftsDir = A.draftsDir || '.run/drafts-wave'
const verified = A.verified || []
if (!verified.length) { log('distill: no banked matches this wave — nothing to distill'); return { appended: false, idiom: null, note: 'no banks' } }

const SCHEMA = {
  type: 'object', additionalProperties: false, required: ['appended'],
  properties: {
    appended: { type: 'boolean' },
    idiom: { type: 'string', description: 'the one-line idiom appended (or empty)' },
    note: { type: 'string', description: 'why appended / why not' },
  },
}

phase('Distill')
const prompt = `You are the LEARNING step of the Brave Fencer Musashi matching flywheel (R16). A worker wave just
BYTE-MATCHED these functions (whole-binary gate-verified — they are byte-identical to the original):
  ${verified.join(', ')}
Their winning C is in: ${draftsDir}/<fn>.c (each starts with // @class and // @stuck comments naming the gcc
quirk it overcame and the technique used).

YOUR JOB: decide whether any of these wins teaches a NEW, GENERALIZABLE gcc-2.7.2 idiom that is NOT already in
docs/matching-cookbook.md (§17–§20), and if so append it — so the NEXT wave's drafters (which read the live
cookbook) inherit it. This is exactly how Phase 18 drove the close-rate 33%→56%→90%.

PROCESS (you have Read, Bash, Edit):
1. Read each banked draft in ${draftsDir} for the verified fns — note the // @class, // @stuck, and the actual
   C technique (register pins, array-of-struct, statement reordering, casts, struct layout, etc.).
2. Read docs/matching-cookbook.md §17–§20. Is the technique ALREADY documented there?
3. DISTILL CONSERVATIVELY (R14/R16 — the cookbook is authoritative, byte-honest):
   - Append ONLY a genuinely NEW + generalizable idiom (a C *shape* that triggers the wanted codegen for a
     whole CLASS of functions), backed by these byte-verified wins. Cite the fn(s) as evidence.
   - Do NOT append one-offs, restatements of existing §17–20 idioms, or anything you can't tie to a byte-match.
   - If nothing is new/general, append NOTHING (that is the correct, common outcome — say so).
4. If appending: add a tight bullet under a "### §21 — wave-distilled idioms (Phase 21)" heading at the END of
   docs/matching-cookbook.md (create the heading once if absent). Format: **<class>:** <the C shape> — *fixes
   <quirk>; evidence <fn>*. Preserve all existing content (H5). Keep it to 1–3 lines.
5. Commit ONLY the cookbook if you changed it:
   git add docs/matching-cookbook.md && git commit -q -m "docs(phase-21): distill — <class> idiom from <fn>"
6. Return { appended, idiom, note }.

Be rigorous: a wrong/over-broad idiom pollutes every future wave. When in doubt, append nothing.`

const r = await agent(prompt, { label: 'distill', phase: 'Distill', schema: SCHEMA })
log(`distill: ${r && r.appended ? 'APPENDED — ' + (r.idiom || '') : 'nothing new (' + ((r && r.note) || '') + ')'}`)
return r || { appended: false, idiom: null, note: 'agent returned null' }
