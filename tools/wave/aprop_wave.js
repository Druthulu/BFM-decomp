export const meta = {
  name: 'p30-s49-aprop-wave',
  description: 'Lane-A word-diff wave: one proven body, N siblings that differ by a handful of immediates/registers',
  phases: [
    { title: 'Adapt', detail: 'per batch: re-emit the proven body once per sibling with its measured word deltas' },
    { title: 'Verify', detail: 'independent re-gate of every claimed draft, sha1 re-checked LAST' },
  ],
}

// ⚠ TEMPLATE-LITERAL MINEFIELD: prompts are backtick strings — a markdown backtick or literal
// dollar-brace in prose kills the workflow at parse time. Use "double quotes" for inline code.
//
// Cards: tools/family_cousins.py --aprop-cards -> .run/aprop_cards.json, chunked into batches by
// the orchestrator. A batch = {family, nins, seed{...}, members:[{name,binary,addr,sub,n_sites}], idx}
// Each agent reads its OWN full card (with every member's word sites) from the cards file — the
// orchestrator never inlines them.
//
// WHY THIS WAVE EXISTS (S49): these members share their family's h_seq with an ALREADY-MATCHED
// sibling, so the mnemonic streams are identical by construction and the mechanical remap still
// refuses them (unresolved immediates / register drift): the >=16-reach head swept 0/245 banked
// with 188 refused. The differences are WORDS — a struct offset, a data symbol, a register — and a
// median member differs in TWO of them. That is an edit, and it is why one agent takes a whole batch.
const REPO = '/home/musashi/bfm-decomp'
const ALL = typeof args === 'string' ? JSON.parse(args) : args
const BATCHES = ALL.filter(b => b.family && b.members)
const WAVE = (ALL.find(b => b.wave) || {}).wave || 'aprop'
const CARDS = (ALL.find(b => b.cards) || {}).cards || '.run/aprop_cards.json'

const BATCH_SCHEMA = {
  type: 'object',
  required: ['family', 'drafts', 'notes'],
  properties: {
    family: {type: 'string'},
    drafts: {
      type: 'array',
      description: 'one entry per sibling you produced a draft for',
      items: {
        type: 'object',
        required: ['fn', 'verdict', 'draft_path'],
        properties: {
          fn: {type: 'string'},
          verdict: {type: 'string', enum: ['MATCH', 'NEAR', 'FAIL']},
          draft_path: {type: 'string'},
          diff_ins: {type: 'integer'},
          sha1: {type: 'string'},
          edit: {type: 'string', description: 'the exact substitution you made for THIS sibling'},
        },
      },
    },
    notes: {type: 'string', description: 'the parameterization you found; anything that did not fit it'},
  },
}
const VERDICT_SCHEMA = {
  type: 'object',
  required: ['fn', 'confirmed', 'evidence'],
  properties: {
    fn: {type: 'string'},
    confirmed: {type: 'boolean'},
    file_exists: {type: 'boolean'},
    sha1_after: {type: 'string'},
    evidence: {type: 'string'},
  },
}

function batchPrompt(b) {
  const list = b.members.map(m =>
    `  ${m.name}  in ${m.binary}  (${m.n_sites} differing word(s))  asm: ${m.sub}/${m.name}.s`).join('\n')
  return `You are re-emitting ONE proven function body for ${b.members.length} sibling copies — Brave Fencer Musashi matching decomp (PS1, gcc-2.7.2 + maspsx). Repo: ${REPO}. This is a SUBSTITUTION task, not a decompile.

THE FAMILY: ${b.family} — ${b.nins} instructions, ${b.reach} open copies fleet-wide, class ${b.cls}${b.jr ? ' (mid-function jr / jump table)' : ''}.
THE PROVEN BODY: ${b.seed.name} in ${b.seed.binary} — ${b.seed.kind === 'macro'
    ? 'the DEFINE_' + b.seed.name + '() macro in ' + b.seed.path
    : 'the plain definition in ' + b.seed.path}. It is byte-matched. Do not redesign it.

EVERY sibling below has the SAME instruction skeleton as that body. They differ only in WORDS —
a struct offset, a data-symbol address, sometimes a register. Your card lists the exact differing
word positions for each sibling, both sides disassembled. PRINT YOUR CARD FIRST:
  cd ${REPO} && python3 -c "import json;c=json.load(open('${CARDS}'))[${b.idx}];print(c['seed']);[print(m['name'],m['binary'],m['n_sites'],m['sites']) for m in c['members']]"

SIBLINGS IN YOUR BATCH:
${list}

METHOD:
1. Read the proven body. Work out the PARAMETERIZATION: which C expressions produce the differing
   words. A changed "lbu \$v0, 0xC1(\$a0)" -> "lbu \$v0, 0x1A0(\$a0)" is a struct FIELD OFFSET in the
   source; a changed "lw \$v0, 0x6EAC(\$at)" -> "0x115C" is a DIFFERENT GLOBAL (a different D_ symbol).
   A changed register is regalloc drift — usually a different local's live range, occasionally a
   different variable order.
2. For EACH sibling: write ${REPO}/.run/${WAVE}/<FN>/<FN>.c defining that sibling, with the symbol
   surface taken from ITS OWN .s (callees, D_ globals, jump-table labels — the .s is ground truth,
   never the seed's symbols) and the offsets/constants its card specifies.
3. Verify each: cd ${REPO} && python3 tools/match_one.py <FN> --c .run/${WAVE}/<FN>/<FN>.c --asm-subdir <ITS SUB>
4. Report every sibling you attempted with its own verdict and sha1. A sibling you could not close
   is NEAR with its exact residual — that is useful, not a failure. Do not skip siblings silently:
   the batch is judged on coverage as well as matches.

OUTPUT DISCIPLINE (a previous wave lost 21 verified drafts to a shared directory):
- One directory per sibling: ${REPO}/.run/${WAVE}/<FN>/ — create it, work there.
- NEVER delete, move or modify ANY file outside your own directories. Sibling agents are working in
  adjacent directories RIGHT NOW. Do NOT clean up.
- NEVER write to src/, config/, include/ or any tracked file — not even a typedef, not even a
  header. An agent did that last wave and blocked the whole gate. No make. No git.

RULES: gcc-2.7.2 emits no "error:" prefix — read the raw compiler text. match_one MATCH is a
CANDIDATE (cookbook §52b); state your integration surface in notes. Match register allocation
exactly (G3). If the proven body is a DEFINE_ macro, expand it to a plain function definition in
each draft — do not emit a macro.`
}

function verifyPrompt(d, b) {
  const m = b.members.find(x => x.name === d.fn) || {}
  return `ADVERSARIAL verification, Brave Fencer Musashi decomp. Repo: ${REPO}.

${d.fn} (${m.binary || '?'}, family ${b.family}) claimed MATCH at ${d.draft_path}; claimed sha1 ${d.sha1 || '(none)'}.

REFUTE it. Default confirmed=false.
1. "ls -l" and "sha1sum" the draft — it must EXIST.
2. Gate it: cd ${REPO} && python3 tools/match_one.py ${d.fn} --c ${d.draft_path} --asm-subdir ${m.sub || ''}
   ("FAIL: no C file" means the draft is MISSING — a refutation, never a pass.)
3. It must DEFINE ${d.fn} as a plain function — no INCLUDE_ASM, no macro emission, no inline asm
   standing in for compiled code — and its symbols must come from ITS OWN .s, not the seed binary's
   (spot-check two names against ${m.sub || ''}/${d.fn}.s).
4. Re-run "sha1sum" LAST and report it as sha1_after; say so loudly if it changed or vanished.
Do NOT edit or delete anything. Report failures; do not fix them.`
}

phase('Adapt')
const results = await pipeline(
  BATCHES,
  b => agent(batchPrompt(b), {label: `aprop:${b.family}[${b.members.length}]`, phase: 'Adapt',
                              model: b.model || 'sonnet', schema: BATCH_SCHEMA})
        .then(r => (r ? {...r, b} : null)),
  r => {
    if (!r || !r.drafts || !r.drafts.length) return r
    const claimed = r.drafts.filter(d => d.verdict === 'MATCH' && d.draft_path)
    if (!claimed.length) return r
    return parallel(claimed.map(d => () =>
      agent(verifyPrompt(d, r.b), {label: `verify:${d.fn}`, phase: 'Verify', schema: VERDICT_SCHEMA})
        .then(v => ({fn: d.fn, v}))
    )).then(vs => ({...r, checks: vs.filter(Boolean)}))
  }
)

const rows = results.filter(Boolean)
const all = rows.flatMap(r => (r.drafts || []).map(d => ({...d, family: r.b.family, checks: r.checks || []})))
const claimed = all.filter(d => d.verdict === 'MATCH')
// A DEAD ORACLE IS NOT A NEGATIVE VERDICT (P30 S48): UNVERIFIED is its own outcome.
const chk = d => (d.checks.find(c => c.fn === d.fn) || {}).v
const confirmed = claimed.filter(d => chk(d) && chk(d).confirmed && chk(d).file_exists !== false)
const unverified = claimed.filter(d => !chk(d))
const refuted = claimed.filter(d => chk(d) && !confirmed.includes(d))
const near = all.filter(d => d.verdict === 'NEAR')
log(`aprop wave: batches ${rows.length}/${BATCHES.length} · drafts ${all.length} · confirmed ${confirmed.length}`
    + ` · refuted ${refuted.length} · UNVERIFIED ${unverified.length} · near ${near.length}`)
return {
  counts: {batches: BATCHES.length, returned: rows.length, drafts: all.length,
           confirmed: confirmed.length, refuted: refuted.length,
           unverified: unverified.length, near: near.length},
  confirmed: confirmed.map(d => ({fn: d.fn, family: d.family, draft_path: d.draft_path, sha1: d.sha1, edit: d.edit})),
  unverified: unverified.map(d => ({fn: d.fn, family: d.family, draft_path: d.draft_path,
                                    note: 'VERIFIER NEVER RAN — re-verify, do not discard'})),
  refuted: refuted.map(d => ({fn: d.fn, evidence: (chk(d) || {}).evidence})),
  near: near.map(d => ({fn: d.fn, family: d.family, diff_ins: d.diff_ins, draft_path: d.draft_path})),
  notes: rows.map(r => ({family: r.b.family, notes: r.notes})),
}
