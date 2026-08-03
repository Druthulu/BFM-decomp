export const meta = {
  name: 'p30-s7-wave4b',
  description: 'P30 wave 4b: draft the volume-lane B-shape families (10-19 members, <=60 ins)',
  phases: [
    { title: 'Draft', detail: 'one agent per target, size-routed per the §136i ladder (haiku/sonnet/opus)' },
    { title: 'Escalate', detail: 'next rung up (haiku->sonnet, sonnet->opus) on any non-MATCH' },
  ],
}

// args = { targets: [...compact records...], extra: "<idioms promoted from the previous wave>" }
// Accept a JSON string too — an invocation can deliver args stringified and pipeline() then dies.
const A = typeof args === 'string' ? JSON.parse(args) : args
const T = Array.isArray(A) ? A : A.targets
const EXTRA = (Array.isArray(A) ? '' : A.extra) || ''
if (!Array.isArray(T)) throw new Error('args.targets must be an array')

const VERDICT = {
  type: 'object',
  additionalProperties: false,
  required: ['fn', 'status', 'summary'],
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['MATCH', 'DIFF', 'BLOCKED'] },
    closeness: { type: 'number', description: 'mismatching instructions remaining; 0 for MATCH' },
    klass: { type: 'string', description: 'residual class if not MATCH' },
    summary: { type: 'string', description: 'what you did and what the residual is, <=4 sentences' },
    levers: { type: 'string', description: 'cookbook sections / idioms that CLOSED the residual' },
    index_hit: { type: 'boolean' },
    index_gap: { type: 'string' },
  },
}

function prompt(t, escalated) {
  const asm = `${t.sub}/${t.fn}.s`
  return `You are matching ONE PS1 function to byte-identical gcc-2.7.2 output for the Brave Fencer
Musashi decompilation. Your ONLY deliverable is a C file at \`.run/s7/${t.ov}/${t.fn}.c\`.

TARGET
  function      ${t.fn}
  binary        ${t.ov}
  target asm    ${asm}          <- THE GROUND TRUTH. Read this FIRST and in full.
  TU it lands in ${t.tu}
  asm-subdir    ${t.sub}
  size          ${t.n} instructions
  leverage      family of ${t.m} members / ${t.ti} templatable instructions — a byte-match here
                propagates ${t.m}x across the fleet.
${t.seed ? `  ghidra seed   .run/ghidra_c/${t.fn}.c   <- A HINT ONLY. It is sometimes an ENTIRELY
                DIFFERENT body (byte-proven this phase). If it disagrees with the .s, THE .s WINS.` : `  ghidra seed   (none cached — work from the .s)`}
${t.retry ? `  ** RETRY **   A previous wave recorded: "${t.retry}". That is a data point, not a
                verdict. Re-derive from the .s; do not assume the earlier verdict was right.` : ''}

HOW TO WORK (this order is the measured-fastest)
1. \`docs/cookbook-index.md\` is a SYMPTOM-KEYED index of 364 byte-verified idioms. Grep it for your
   residual's symptom BEFORE deriving anything. Measured: index-first took a wave's bank rate from
   57% to 100%. Then read the section it names in \`docs/matching-cookbook.md\`.
   \`docs/gcc-2.7.2-map/{sched,regalloc,loop,cse_expr}.md\` is the compiler-source-derived map for
   scheduling / register-allocation residuals.
2. Read the target \`.s\` completely: frame size, callee-saved registers, jal targets, every
   \`%hi/%lo\` symbol.
3. Read the TU (${t.tu}) for EVERY symbol your draft will name. cc1 reports only the FIRST conflict,
   so a draft can look one edit from done and hold three more. grep the whole TU in ONE pass.
   Match its existing declarations EXACTLY; push any type disagreement to a CAST AT THE USE SITE
   rather than redeclaring the symbol.
4. Write the draft, then verify:
     .venv/bin/python tools/match_one.py ${t.fn} --c .run/s7/${t.ov}/${t.fn}.c --asm-subdir ${t.sub}
   Iterate until it prints MATCH; it names the exact mismatching instructions.

IDIOMS THAT CLOSED RESIDUALS IN THE LAST WAVES (cookbook §135 — all byte-verified)
 1. UNSIGNED switch index => pure equality chain, NO range test. No \`slti\` bound check in the
    target's switch means the index is u32, not s32.
 2. \`a0[0x46]\` (ARRAY_REF) sets MEM_IN_STRUCT_P and lets a load HOIST past a constant-address
    store; \`*(s16 *)((s32)a0 + 0x8C)\` (INDIRECT_REF) keeps the dependence. Many 4-instruction
    "scheduling residuals" are just this type-form choice.
 3. A constant store whose top bit is set in the STORED width needs an UNSIGNED destination:
    \`*(u16 *)p = 0x8C00\` emits \`ori\`; through \`s16\` it folds negative and emits \`addiu\`.
 4. The list scheduler PRESERVES the relative order of disambiguable stores. A store written late
    in source SINKS. If a store lands too late, move it EARLIER IN SOURCE (not a permuter job).
 5. A \`short\` loop counter blocks strength reduction; walking explicit pointers (\`p++\`)
    reproduces the original biv/giv set.
 6. Frame size off by a constant => DEAD LOCALS. If ALL diffs are \`sp\`-relative immediates off by
    one constant delta, add the padding declaration.
 7. An INTERIOR address has no symbol — a \`lui/addiu\` pair can build an offset INTO a symbol.
    Find the containing symbol in the data \`.s\` and index into it; declaring the interior address
    as its own extern link-fails.
 8. NEVER redeclare a C-library name (\`memcpy\` etc.).
 9. Loose typing is pervasive: if the TU declares \`void f(void)\` but the asm passes \`$a0\`, call
    through a cast — \`((void(*)(s32))f)(a0)\` — do NOT change the declaration.
${EXTRA ? `\nPROMOTED FROM THE PREVIOUS BATCH (fresh, byte-verified this session)\n${EXTRA}\n` : ''}
HARD RULES
 * Write ONLY \`.run/s7/${t.ov}/${t.fn}.c\`. NEVER edit \`src/\`, \`asm/\`, \`config/\`, \`include/\`,
   the Makefile, or any tracked file.
 * Do NOT run \`make\`, \`make build\`, \`make extract\`, or \`tools/harvest_verify.py\`. The
   whole-binary gate is the orchestrator's job and the sole arbiter of a match.
 * \`match_one\` MATCH is NECESSARY BUT NOT SUFFICIENT — it compiles standalone and cannot see the
   TU's other declarations. Step 3 is what makes a MATCH actually BANK.
 * Report honestly. A DIFF with a precise residual class routes the next attempt; a false MATCH
   just gets caught by the byte-gate and wastes a cycle.
 * ${escalated ? 'A cheaper rung of the model ladder already attempted this and did not reach MATCH. Read its draft at the path above, but re-derive from the .s rather than trusting it.' : 'Work economically — most functions this size close from the .s plus one or two index lookups.'}

Return the structured verdict.`
}

phase('Draft')

const results = await pipeline(
  T,
  (t) => agent(prompt(t, false), {
    label: `draft:${t.fn}(${t.n}i,x${t.m})`,
    phase: 'Draft',
    model: t.model,
    schema: VERDICT,
  }).then((v) => ({ t, v })),

  async ({ t, v }) => {
    if (!v) return { t, v: { fn: t.fn, status: 'BLOCKED', summary: 'agent returned no verdict' }, tier: t.model }
    if (v.status === 'MATCH' || t.model === 'opus') return { t, v, tier: t.model }
    // §136i ladder: haiku -> SONNET -> opus. Never haiku -> opus directly.
    const nextTier = t.model === 'haiku' ? 'sonnet' : 'opus'
    const v2 = await agent(prompt(t, true), {
      label: `escalate:${t.fn}`,
      phase: 'Escalate',
      model: nextTier,
      schema: VERDICT,
    })
    return { t, v: v2 && v2.status === 'MATCH' ? v2 : (v2 || v), tier: nextTier + '-escalated' }
  },
)

const ok = results.filter(Boolean)
const matched = ok.filter((r) => r.v && r.v.status === 'MATCH')
log(`wave4b: ${matched.length}/${T.length} claim MATCH (the gate is the arbiter)`)

return {
  claimed_match: matched.map((r) => r.t.fn),
  verdicts: ok.map((r) => ({
    fn: r.t.fn, ov: r.t.ov, nins: r.t.n, members: r.t.m, tier: r.tier,
    status: r.v ? r.v.status : 'NONE',
    closeness: r.v ? r.v.closeness : null,
    klass: r.v ? r.v.klass : null,
    levers: r.v ? r.v.levers : null,
    index_hit: r.v ? r.v.index_hit : null,
    index_gap: r.v ? r.v.index_gap : null,
    summary: r.v ? r.v.summary : null,
  })),
}
