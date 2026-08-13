export const meta = {
  name: 'p30-s49-adapt-wave',
  description: 'Micro-adapt wave: edit a proven matched body onto a near-identical cousin (LI-ONLY / SMALL-EDIT cards)',
  phases: [
    { title: 'Adapt', detail: 'cheap-tier seeded edits — the diff names the <=6 tokens that change' },
    { title: 'Verify', detail: 'independent re-gate + existence proof, sha1 re-checked LAST' },
  ],
}

// ⚠ TEMPLATE-LITERAL MINEFIELD (same as crack_wave.js): prompts are backtick strings — a markdown
// backtick or a literal dollar-brace in prose TERMINATES the string and the workflow dies at parse
// time. Use "double quotes" for inline code in prose, escape any literal \` and \${.
//
// Cards come from: tools/family_cousins.py --adapt-cards  ->  .run/adapt_cards.json
// Each card: {name, binary, addr, nins, sub, reach, jr, klass, sim,
//             seed:{name,binary,addr,nins,kind,path}, diff:[{kind,member_at,member_words,
//             member_disasm,seed_at,seed_words,seed_disasm}], n_blocks, n_tokens}
// Invoke: Workflow({scriptPath:"tools/wave/adapt_wave.js", args:[{wave:"wave7a"}, ...cards]})
const REPO = '/home/musashi/bfm-decomp'
const ALL = typeof args === 'string' ? JSON.parse(args) : args
const CARDS = ALL.filter(c => c.name && c.seed)
const WAVE = (ALL.find(c => c.wave) || {}).wave || 'wave7a'
// The edit is small regardless of body size, but a long body copy still wants the mid tier.
const modelFor = c => (c.nins <= 60 ? 'haiku' : 'sonnet')

const ADAPT_SCHEMA = {
  type: 'object',
  required: ['fn', 'verdict', 'draft_path', 'notes'],
  properties: {
    fn: {type: 'string'},
    verdict: {type: 'string', enum: ['MATCH', 'NEAR', 'FAIL']},
    draft_path: {type: 'string'},
    diff_ins: {type: 'integer'},
    sha1: {type: 'string', description: 'sha1sum of the draft you are leaving on disk'},
    notes: {type: 'string', description: 'the exact edit you made (constant/statement), the symbol renames, integration surface; exact residual if NEAR'},
  },
}
const VERDICT_SCHEMA = {
  type: 'object',
  required: ['fn', 'confirmed', 'evidence'],
  properties: {
    fn: {type: 'string'},
    confirmed: {type: 'boolean'},
    file_exists: {type: 'boolean'},
    sha1_after: {type: 'string', description: 'sha1sum re-run LAST, after the gate'},
    evidence: {type: 'string'},
  },
}

// The diff blocks can be inlined on the card (small slates) OR left on disk and read by the agent
// (large slates — keeps the orchestrator's args, and its context, small). `slate` + `idx` select
// the card; the agent prints it with one command.
function diffBlock(c) {
  if (c.diff && c.diff.length) {
    return c.diff.map((d, i) =>
      `  block ${i + 1} [${d.kind}] at member instr ${d.member_at} / seed instr ${d.seed_at}:
    member words: ${d.member_words.join(' ')}   (${d.member_disasm.join(' | ')})
    seed words  : ${d.seed_words.join(' ')}   (${d.seed_disasm.join(' | ')})`).join('\n')
  }
  return `  (${c.n_blocks} block(s), ${c.n_tokens} token(s)) — PRINT YOUR CARD FIRST, it holds the
  exact sites with both sides' words and disassembly:
    cd ${REPO} && python3 -c "import json;c=json.load(open('${c.slate}'))[${c.idx}];print(json.dumps(c['diff'],indent=1))"`
}

function adaptPrompt(c) {
  const seedWhere = c.seed.kind === 'macro'
    ? `${c.seed.path} — the body is the DEFINE_${c.seed.name}() macro (read it there; it is the byte-proven body)`
    : `${c.seed.path} — the plain definition of ${c.seed.name}`
  return `You are ADAPTING a proven byte-matched body onto a near-identical sibling function — Brave Fencer Musashi matching decomp (PS1, gcc-2.7.2 + maspsx). Repo: ${REPO}. This is an EDIT task, not a from-scratch crack.

TARGET: ${c.name} in ${c.binary} — ${c.nins} instructions${c.jr ? ' (mid-function jr / jump table)' : ''}. Asm truth: ${c.sub}/${c.name}.s
SEED (${(c.sim * 100).toFixed(1)}% skeleton-similar, already byte-matched as ${c.seed.name} in ${c.seed.binary}): ${seedWhere}

THE MEASURED DIFF — the target differs from the seed at exactly ${c.n_blocks} site(s), ${c.n_tokens} instruction(s) total (class ${c.klass}):
${diffBlock(c)}

METHOD:
1. Read the seed body. Copy it to ${REPO}/.run/${WAVE}/${c.name}/${c.name}.c as the definition of ${c.name}.
2. RENAME the symbol surface to the TARGET's own: every callee "func_XXXXXXXX", data "D_XXXXXXXX",
   and jump-table label must come FROM THE TARGET .s (${c.sub}/${c.name}.s) — the .s is the symbol
   ground truth. Do not keep the seed binary's symbols. Positional correspondence: the bodies align
   1:1 outside the diff blocks above.
3. Apply the minimal SEMANTIC edit the diff implies. An insert/delete of lui/ori/addiu is almost
   always a changed CONSTANT — decode the target's words above (lui hi16 + ori/addiu lo16) and use
   the TARGET's value in the C literal. An inserted load/store or branch token usually means one
   added or removed statement/condition. Make the smallest edit that explains the diff.
4. Iterate: cd ${REPO} && python3 tools/match_one.py ${c.name} --c .run/${WAVE}/${c.name}/${c.name}.c --asm-subdir ${c.sub}
5. On MATCH: sha1sum the draft, report it, STOP. If two honest attempts leave a residual, report
   NEAR with the exact remaining diff — NEAR is a resumable state, not a failure.

OUTPUT DISCIPLINE (a previous wave lost 21 verified drafts to a shared directory):
- Your ONLY output dir is ${REPO}/.run/${WAVE}/${c.name}/ — create it, work there.
- Final draft MUST be exactly ${REPO}/.run/${WAVE}/${c.name}/${c.name}.c
- NEVER delete, move or modify ANY file outside your own directory. Sibling agents are working in
  adjacent directories RIGHT NOW. Do NOT clean up at the end.
- Never write to src/, config/, include/ or any tracked file. No make. No git.

RULES: gcc-2.7.2 emits no "error:" prefix — read the raw compiler text. match_one MATCH is a
CANDIDATE (cookbook §52b) — state your integration surface in notes: which callees/globals you
declare and whether the host TU declares them differently (§161c). Match register allocation
exactly (G3). If the seed body is a DEFINE_ macro, expand it to a plain function definition in your
draft — do not emit a macro.`
}

function verifyPrompt(r, c) {
  return `ADVERSARIAL verification, Brave Fencer Musashi decomp. Repo: ${REPO}.

${r.fn} (${c.binary}, ${c.nins} ins, ADAPTED from ${c.seed.name}) claimed MATCH at ${r.draft_path}; claimed sha1 ${r.sha1 || '(none)'}.

REFUTE it. Default confirmed=false. In this order:
1. "ls -l" and "sha1sum" the draft — it must EXIST.
2. Gate it yourself: cd ${REPO} && python3 tools/match_one.py ${r.fn} --c ${r.draft_path} --asm-subdir ${c.sub}
   ("FAIL: no C file" means the draft is MISSING — that is a refutation, never a pass.)
3. The draft must DEFINE ${r.fn} as a plain function (no INCLUDE_ASM, no macro emission, no inline
   asm standing in for compiled code), and its symbol surface must come from the TARGET .s, not the
   seed binary (spot-check two callee/data names against ${c.sub}/${r.fn}.s).
4. Re-run "sha1sum" LAST, after everything else, and report it as sha1_after. If the file vanished
   or changed since step 1, say so loudly.
Do NOT edit or delete anything. Report failures; do not fix them.`
}

phase('Adapt')
const results = await pipeline(
  CARDS,
  c => agent(adaptPrompt(c), {label: `adapt:${c.name}`, phase: 'Adapt', model: modelFor(c), schema: ADAPT_SCHEMA})
        .then(r => (r ? {...r, c} : null)),
  r => {
    if (!r || r.verdict !== 'MATCH' || !r.draft_path) return r
    return agent(verifyPrompt(r, r.c), {label: `verify:${r.fn}`, phase: 'Verify', schema: VERDICT_SCHEMA})
      .then(v => ({...r, verdict_check: v}))
  }
)

const rows = results.filter(Boolean)
// A DEAD ORACLE IS NOT A NEGATIVE VERDICT (P30 S48): UNVERIFIED is its own outcome — re-verify,
// never bank, never discard.
const claimed = rows.filter(r => r.verdict === 'MATCH')
const unverified = claimed.filter(r => !r.verdict_check)
const confirmed = claimed.filter(r => r.verdict_check && r.verdict_check.confirmed
                                      && r.verdict_check.file_exists !== false)
const refuted = claimed.filter(r => r.verdict_check && !confirmed.includes(r))
const near = rows.filter(r => r.verdict === 'NEAR')
const fail = rows.filter(r => r.verdict === 'FAIL')
log(`adapt wave: confirmed ${confirmed.length} / refuted ${refuted.length} / UNVERIFIED ${unverified.length}`
    + ` / near ${near.length} / fail ${fail.length} of ${rows.length}`)
return {
  counts: {cards: CARDS.length, returned: rows.length, confirmed: confirmed.length,
           refuted: refuted.length, unverified: unverified.length,
           near: near.length, fail: fail.length},
  unverified: unverified.map(r => ({fn: r.fn, binary: r.c.binary, draft_path: r.draft_path,
                                    sha1: r.sha1, note: 'VERIFIER NEVER RAN — re-verify, do not discard'})),
  confirmed: confirmed.map(r => ({fn: r.fn, binary: r.c.binary, reach: r.c.reach, nins: r.c.nins,
                                  klass: r.c.klass, seed: r.c.seed.name, model: modelFor(r.c),
                                  draft_path: r.draft_path, sha1: r.sha1, notes: r.notes})),
  refuted: refuted.map(r => ({fn: r.fn, draft_path: r.draft_path,
                              evidence: r.verdict_check && r.verdict_check.evidence})),
  near: near.map(r => ({fn: r.fn, binary: r.c.binary, diff_ins: r.diff_ins, notes: r.notes,
                        draft_path: r.draft_path})),
  fail: fail.map(r => ({fn: r.fn, binary: r.c.binary, notes: r.notes})),
}
