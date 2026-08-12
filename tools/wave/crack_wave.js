export const meta = {
  name: 'p30-s48-stage1-wave4',
  description: 'Stage-1 wave 4: 39 top-weight families, hardened harness (per-agent dirs, sha1-last verify)',
  phases: [
    { title: 'Crack', detail: '39 cracks, size-routed, 9 seeded with prior-attempt notes' },
    { title: 'Verify', detail: 'independent re-gate + existence proof, sha1 re-checked LAST' },
  ],
}

const REPO = '/home/musashi/bfm-decomp'
const ALL = typeof args === 'string' ? JSON.parse(args) : args
const TARGETS = ALL.filter(t => t.sub)          // a banked target has no .s — drop it

const CRACK_SCHEMA = {
  type: 'object',
  required: ['fn', 'verdict', 'draft_path', 'notes'],
  properties: {
    fn: {type: 'string'},
    verdict: {type: 'string', enum: ['MATCH', 'NEAR', 'FAIL']},
    draft_path: {type: 'string'},
    diff_ins: {type: 'integer'},
    match_one_output: {type: 'string'},
    sha1: {type: 'string', description: 'sha1sum of the draft you are leaving on disk'},
    notes: {type: 'string', description: 'idioms, integration surface, exact residual if NEAR; flag any NEW law'},
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

function crackPrompt(t) {
  const priorBlock = t.prior ? `
⚡ A PREVIOUS AGENT ALREADY ATTEMPTED THIS FUNCTION. Read its notes FIRST — they contain the body
shape, the idioms it proved load-bearing, and the EXACT residual it could not close:
  cd ${REPO} && python3 -c "import json;print(json.load(open('.run/jr48/prior_notes.json'))['${t.name}'])"
Treat it as a strong prior from a peer, NOT as gospel: its claims about what is load-bearing are
reconstructions. If a note contradicts what you measure, the measurement wins — and say so.
` : ''
  return `You are cracking ONE function for the Brave Fencer Musashi matching decompilation (PS1, gcc-2.7.2 + maspsx). Repo: ${REPO}.

TARGET: ${t.name} in ${t.binary} — ${t.nins} instructions, family reach ×${t.reach}${t.jr ? ' (mid-function jr / jump table)' : ''}.
Splat asm subdir: ${t.sub}. Asm file: ${t.sub}/${t.name}.s
${priorBlock}
WHY IT MATTERS: zero-crack sibling family — this ONE exemplar templates to ${t.reach - 1} more binaries mechanically.

OUTPUT DISCIPLINE (a previous wave lost 21 verified drafts to a shared directory):
- Your ONLY output dir is ${REPO}/.run/wave4/${t.name}/ — create it, work there.
- Final draft MUST be exactly ${REPO}/.run/wave4/${t.name}/${t.name}.c
- NEVER delete, move or modify ANY file outside your own directory. No \`rm\` outside it, ever.
  Sibling agents are working in adjacent directories RIGHT NOW.
- Do NOT clean up at the end. Leave everything in place.
- Never write to src/, config/, include/ or any tracked file. No make. No git.

METHOD:
1. STEP 0 — §160g callee-set sibling search (mandatory). Extract the callee set + magic literals from
   the .s, grep already-matched C in src/ for the same shape. Highest-value hits are IN THE
   DESTINATION TU ITSELF — an already-matched caller often gives the exact signature, and the host TU
   fixes every symbol type for free. Read the destination TU before any cross-overlay grep.
2. A Ghidra seed may exist at .run/ghidra_c/${t.name}.c — VERIFY it is for THIS address before trusting it.
3. Cookbook — READ THESE FOUR BLOCKS, they are this campaign's own harvest and the most relevant
   knowledge in the file (~100 entries banked over the last four waves):
     §160a/b/c and §161a/b/c — the base idioms.
     §162 — jump-table MAXVAL mirror ("check BOTH edges"), temp SCOPE as a live-range lever, the
       LICM movable/preheader-order laws, non-void return visible in delay slots, cross-jump
       DIRECTION as a source-shape oracle, the unreferenced-local frame oracle, and defeating
       local-alloc's optimize_reg_copy_1 with an in-place shift — a class where REGISTER PINS
       PROVABLY CANNOT HELP.
     §163a-e — decl-conflict severity is SCOPE-DEPENDENT (block scope is a conflict SOLVENT); the
       switch-index parameter-WIDTH oracle (sll/sra straddling the minval subtract);
       case_values_threshold is 5 (an empty case glued to default can be the only thing that emits a
       table); cse deleting a copy by rewriting the PREVIOUS insn's SET_DEST (§162j's symptom in a
       DIFFERENT pass); the frame as a PSEUDO-NUMBER oracle.
     §164-01..82 and §165-01..47 — 129 further laws, each vetted by an independent skeptic and
       carrying its evidence grade. **§164z and §165z list 48 REFUTED claims between them — read
       them before spending time on a mechanism, so you do not re-derive something disproved.**
       Note §165-01 BOUNDS §163a: `conflicting types` ⇒ block scope is a solvent (move the typedef
       AND the extern into the block); `too many arguments` ⇒ no decl spelling at any scope helps,
       cast the call site (§17a-1/§161c).
   Search these before inventing a mechanism: of 190 laws the last waves claimed as new, 57% were
   already here or did not survive scrutiny.
4. Iterate: cd ${REPO} && python3 tools/match_one.py ${t.name} --c .run/wave4/${t.name}/${t.name}.c --asm-subdir ${t.sub}
5. On MATCH: run sha1sum on the draft, report it, and STOP.

RULES: gcc-2.7.2 emits no \`error:\` prefix — read the raw compiler text; "no diagnostic" never means
"compiler wall". match_one MATCH is a CANDIDATE (§52b) — state your integration surface: which
callees/globals you declare and whether the host TU declares them differently (§161c). A block-scope
decl that CONFLICTS with a visible file-scope one is a gate failure; one that AGREES is free — and
you cannot simply drop the decl, because match_one compiles standalone. Report NEAR honestly with the
exact residual. Match register allocation exactly (G3).`
}

function verifyPrompt(c, t) {
  return `ADVERSARIAL verification, Brave Fencer Musashi decomp. Repo: ${REPO}.

${c.fn} (${t.binary}, ${t.nins} ins) claimed MATCH at ${c.draft_path}; claimed sha1 ${c.sha1 || '(none)'}.

REFUTE it. Default confirmed=false. In this order:
1. \`ls -l ${c.draft_path}\` and \`sha1sum ${c.draft_path}\` — it must EXIST.
2. Gate it yourself: cd ${REPO} && python3 tools/match_one.py ${c.fn} --c ${c.draft_path} --asm-subdir ${t.sub}
   ("FAIL: no C file for <fn>" means the draft is MISSING — that is a refutation, never a pass.)
3. The draft must DEFINE ${c.fn} (not a renamed/stub body), with no INCLUDE_ASM, no #include of a
   nonexistent path, no hand-written inline asm standing in for compiled code.
4. Re-run \`sha1sum ${c.draft_path}\` LAST, after everything else, and report it as sha1_after. If the
   file vanished or its hash changed since step 1, say so loudly — a previous wave lost 21 verified
   drafts to exactly that and nothing detected it.
Do NOT edit or delete anything. Report failures; do not fix them.`
}

phase('Crack')
const results = await pipeline(
  TARGETS,
  t => agent(crackPrompt(t), {label: `crack:${t.name}`, phase: 'Crack', model: t.model, schema: CRACK_SCHEMA})
        .then(r => (r ? {...r, t} : null)),
  r => {
    if (!r || r.verdict !== 'MATCH' || !r.draft_path) return r
    return agent(verifyPrompt(r, r.t), {label: `verify:${r.fn}`, phase: 'Verify', schema: VERDICT_SCHEMA})
      .then(v => ({...r, verdict_check: v}))
  }
)

const rows = results.filter(Boolean)
const confirmed = rows.filter(r => r.verdict === 'MATCH' && r.verdict_check && r.verdict_check.confirmed
                                   && r.verdict_check.file_exists !== false)
const refuted = rows.filter(r => r.verdict === 'MATCH' && !confirmed.includes(r))
const near = rows.filter(r => r.verdict === 'NEAR')
const fail = rows.filter(r => r.verdict === 'FAIL')
log(`wave4: confirmed ${confirmed.length} / refuted ${refuted.length} / near ${near.length} / fail ${fail.length} of ${rows.length}`)
return {
  counts: {targets: TARGETS.length, returned: rows.length, confirmed: confirmed.length,
           refuted: refuted.length, near: near.length, fail: fail.length},
  confirmed: confirmed.map(r => ({fn: r.fn, binary: r.t.binary, reach: r.t.reach, nins: r.t.nins,
                                  jr: r.t.jr, model: r.t.model, prior: !!r.t.prior,
                                  draft_path: r.draft_path, sha1: r.sha1, notes: r.notes})),
  refuted: refuted.map(r => ({fn: r.fn, draft_path: r.draft_path,
                              evidence: r.verdict_check ? r.verdict_check.evidence : 'verifier died'})),
  near: near.map(r => ({fn: r.fn, binary: r.t.binary, model: r.t.model, prior: !!r.t.prior,
                        diff_ins: r.diff_ins, draft_path: r.draft_path, notes: r.notes})),
  fail: fail.map(r => ({fn: r.fn, binary: r.t.binary, notes: r.notes})),
}
