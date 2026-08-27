export const meta = {
  name: 't4-model-ladder-probe',
  description: 'T4 calibration probe: 20 stratified fns x Claude arms (haiku/sonnet/opus) from identical packs; drafts to .run/t4/<arm>/',
  phases: [
    { title: 'Draft', detail: '20 fns x 3 arms = 60 drafting agents, identical packs, local match_one oracle only' },
  ],
}
const REPO = '/home/musashi/bfm-decomp'
const ARMS = [
  { arm: 'haiku', model: 'haiku' },
  { arm: 'sonnet', model: 'sonnet' },
  { arm: 'opus', model: 'opus' },
]
const TARGETS = args.targets
const VERDICT = {
  type: 'object',
  properties: {
    fn: { type: 'string' },
    arm: { type: 'string' },
    status: { type: 'string', enum: ['MATCH', 'NEAR', 'FAIL', 'NO-DRAFT'] },
    closeness: { type: ['integer', 'null'] },
    compiles: { type: 'boolean' },
    draft_path: { type: 'string' },
    note: { type: 'string' },
  },
  required: ['fn', 'arm', 'status', 'closeness', 'compiles', 'draft_path', 'note'],
}
phase('Draft')
const jobs = []
for (const a of ARMS) for (const t of TARGETS) jobs.push({ a, t })
const results = await parallel(jobs.map(({ a, t }) => () => agent(
`You are one arm of a controlled calibration probe in the Brave Fencer Musashi decompilation repo at ${REPO}.
Byte-match ONE PlayStation function: ${t.name} (${t.nins} instructions, binary ${t.binary}).

FIRST read these two files in full — they are your complete brief and your ground truth pointers:
  ${REPO}/.run/WAVE/SYS.md            (the laws; it names tools read_file/grep/match_one/submit — use the CLI equivalents below)
  ${REPO}/.run/WAVE/packs/${t.name}.md (the target pack: asm path, destination TU, card fuel, a warm-start body, any gate feedback)

CLI equivalents (run from ${REPO}):
  read_file  -> cat / sed -n
  grep       -> rg or grep -n (start at docs/cookbook-index.md; \`.venv/bin/python tools/cookbook_index.py --resolve N\` resolves a line number)
  match_one  -> .venv/bin/python tools/match_one.py ${t.name} --c <your_draft.c> --asm-subdir ${t.sub} --json
               (prints JSON with status MATCH/near/... and closeness = masked mismatched instruction count; it is free — use it often)
  submit     -> write your FINAL draft to ${REPO}/.run/WAVE/${a.arm}/${t.name}.c (mkdir -p the dir) and return the JSON verdict.

HARD RULES: never modify anything under src/, config/, include/, asm/, build/ or run make; never touch other arms' dirs; write only to .run/WAVE/${a.arm}/ and scratch under .run/WAVE/${a.arm}/scratch_${t.name}/. Budget: up to ~24 compile/match_one iterations, then stop honestly.
Your final answer is the JSON verdict only: fn, arm="${a.arm}", status (MATCH if match_one says MATCH; NEAR if it compiles with closeness>0; FAIL if it never compiled; NO-DRAFT if you wrote nothing), closeness (integer or null), compiles, draft_path, note (one line: what blocked you, or which cookbook § unlocked it).`,
  { label: `${a.arm}:${t.name}`, phase: 'Draft', model: a.model, schema: VERDICT }
).then(v => v || { fn: t.name, arm: a.arm, status: 'NO-DRAFT', closeness: null, compiles: false, draft_path: '', note: 'agent returned null' })
 .catch(e => ({ fn: t.name, arm: a.arm, status: 'NO-DRAFT', closeness: null, compiles: false, draft_path: '', note: 'agent error: ' + String(e).slice(0, 120) }))))
const byArm = {}
for (const r of results.filter(Boolean)) { (byArm[r.arm] = byArm[r.arm] || []).push(r) }
for (const arm of Object.keys(byArm)) {
  const rs = byArm[arm]
  log(`${arm}: MATCH ${rs.filter(r => r.status === 'MATCH').length} / NEAR ${rs.filter(r => r.status === 'NEAR').length} / FAIL ${rs.filter(r => r.status === 'FAIL').length} / NO-DRAFT ${rs.filter(r => r.status === 'NO-DRAFT').length} of ${rs.length}`)
}
return { results }