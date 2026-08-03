export const meta = {
  name: 'p30-s8-reconcile',
  description: 'P30 wave 4a reconcile lane: fix the 7 declaration-blocked drafts (blockers captured)',
  phases: [{ title: 'Reconcile', detail: 'one Opus agent per PLUMBING failure, blocker line embedded' }],
}

const A = [{"fn": "func_801832A8", "ov": "ov_SC02_026", "tu": "src/ov_SC02_026/ov_SC02_026_jr_8017C180.c", "sub": "asm/ov_SC02_026/nonmatchings/ov_SC02_026_jr_8017C180", "blocker": "src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:5030: conflicting types for `func_8012BE98' || src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:4745: previous declaration of `func_8012BE98' || src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:5031: conflicting types for `func_8012B744' || src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:4746: previous declaration of `func_8012B744'", "no_build": false}]
const T = Array.isArray(A) ? A : A.targets
if (!Array.isArray(T)) throw new Error('args must be an array of targets')

const VERDICT = {
  type: 'object',
  additionalProperties: false,
  required: ['fn', 'status', 'summary'],
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['FIXED', 'STILL-BLOCKED', 'DIFF'] },
    lever: { type: 'string', description: 'which byte-neutral lever closed it' },
    summary: { type: 'string' },
    index_gap: { type: 'string' },
  },
}

phase('Reconcile')

const results = await pipeline(T, (t) =>
  agent(`A byte-correct C draft is being REFUSED by the whole-binary byte-gate for a DECLARATION
reason, not a codegen reason. Fix the declarations. Do NOT rewrite the function body unless you
prove it is actually wrong.

  function   ${t.fn}
  binary     ${t.ov}
  draft      .run/s8/${t.ov}/${t.fn}.c      <- edit THIS FILE IN PLACE; it is your only deliverable
  TU         ${t.tu}
  asm-subdir ${t.sub}
  target asm ${t.sub}/${t.fn}.s

THE COMPILER'S OWN ERROR, captured by splicing your draft into the TU and building ${t.ov}:

    ${t.blocker}

You cannot run the gate yourself — that error line IS the evidence. Without it this reads like a
codegen wall; with it, this lane has closed 12 of 12 across the last two waves.

THE TWO BYTE-NEUTRAL LEVERS (use these; do NOT edit any shared header)
 (A) **Conform the declaration, cast at the USE site.** When the conflict is on a symbol OTHER than
     the function you are defining: copy the TU's existing declaration VERBATIM into your draft, and
     push every type disagreement to a cast at the call/use site —
     \`((s32(*)(s32))func_X)(a)\` for a call, \`*(T *)&D_Y\` for data. Zero bytes change.
 (B) **The §37/§124 asm-label alias**, when the conflict is on the function you are DEFINING (its
     return type or arity disagrees with a banked caller's declaration):
        \`<ret> aF${t.fn.replace('func_', '')}(<params>) __asm__("${t.fn}");\`
     and define that alias instead. It sidesteps the collision at ZERO blast radius. The data form
     exists too: \`extern struct B16_x aD800A5E88 __asm__("D_800A5E88");\`

CRITICAL — cc1 reports only the FIRST conflict, so more may hide behind this one. **grep the WHOLE
TU (including BELOW your splice point) for EVERY symbol your draft names, in one pass**, and
reconcile them all at once. One wave-2 draft had invented prototypes for six symbols the TU already
declared, two of them below the splice point.

Never redeclare a C-library name (\`memcpy\` etc.) — one TU declares it three incompatible ways.

VERIFY: \`.venv/bin/python tools/match_one.py ${t.fn} --c .run/s8/${t.ov}/${t.fn}.c --asm-subdir ${t.sub}\`
must still report MATCH after your edit. If it does NOT, your declaration change altered codegen —
back it out and use a cast instead.

${t.no_build ? `⚠️ **DO NOT RUN ANY BUILD** (\`make\`, \`make build\`). Another agent is reconciling a
different function in this SAME TU concurrently, and two splice-builds would clobber a tracked file.
\`match_one\` is fine — it uses a private scratch dir.` : `You may run \`match_one\` freely. Do NOT run \`make build\` or \`harvest_verify\` — the orchestrator gates.`}

Write ONLY \`.run/s8/${t.ov}/${t.fn}.c\`. Never edit src/, asm/, config/, include/, or the Makefile.

If after honest work the residual turns out to be a real byte difference rather than a declaration
problem, say so (status DIFF) with the evidence — that routes it correctly and is worth more than a
forced fix.`, {
    label: `reconcile:${t.fn}`,
    phase: 'Reconcile',
    model: 'opus',
    schema: VERDICT,
  }).then((v) => ({ t, v })),
)

const ok = results.filter(Boolean)
log(`reconcile: ${ok.filter((r) => r.v && r.v.status === 'FIXED').length}/${T.length} claim FIXED`)
return {
  fixed: ok.filter((r) => r.v && r.v.status === 'FIXED').map((r) => r.t.fn),
  verdicts: ok.map((r) => ({ fn: r.t.fn, ov: r.t.ov, status: r.v && r.v.status,
                             lever: r.v && r.v.lever, summary: r.v && r.v.summary,
                             index_gap: r.v && r.v.index_gap })),
}
