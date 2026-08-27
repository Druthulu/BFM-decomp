export const meta = {
  name: 'claude-wave-draft',
  description: 'Claude-subagent drafting wave (P31 S62 T5; born as the T4 model-ladder probe): one agent per target, model = target.arm, identical api_agent packs; drafts to <wave>/<arm>/<fn>.c',
  phases: [
    { title: 'Draft', detail: 'one drafting agent per target (sonnet <=120 ins / opus >120 + residue), local match_one oracle only; tools/wave_judge.py is the judge' },
  ],
}
// args: { wave: '.run/t5a', targets: [{name, binary, nins, sub, arm}, ...] }  — from tools/t5_targets.py
// (targets.json + SYS.md + packs/ live under <wave>, built by tools/claude_wave_packs.py)
const REPO = '/home/musashi/bfm-decomp'
const WAVE = args.wave
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
log(`wave ${WAVE}: ${TARGETS.length} targets (${TARGETS.filter(t => t.arm === 'sonnet').length} sonnet / ${TARGETS.filter(t => t.arm === 'opus').length} opus)`)
const results = await parallel(TARGETS.map(t => () => agent(
`You are one drafting agent of a Claude wave in the Brave Fencer Musashi decompilation repo at ${REPO}.
Byte-match ONE PlayStation function: ${t.name} (${t.nins} instructions, binary ${t.binary}).

FIRST read these two files in full — they are your complete brief and your ground truth pointers:
  ${REPO}/${WAVE}/SYS.md            (the laws; it names tools read_file/grep/match_one/submit — use the CLI equivalents below)
  ${REPO}/${WAVE}/packs/${t.name}.md (the target pack: asm path, destination TU, card fuel, a warm-start body, any gate feedback)

CLI equivalents (run from ${REPO}):
  read_file  -> cat / sed -n
  grep       -> rg or grep -n (start at docs/cookbook-index.md; \`.venv/bin/python tools/cookbook_index.py --resolve N\` resolves a line number)
  match_one  -> .venv/bin/python tools/match_one.py ${t.name} --c <your_draft.c> --asm-subdir ${t.sub} --json
               (prints JSON with status MATCH/near/... and closeness = masked mismatched instruction count; it is free — use it often)
  submit     -> write your FINAL draft to ${REPO}/${WAVE}/${t.arm}/${t.name}.c (mkdir -p the dir) and return the JSON verdict.

HARD RULES: never modify anything under src/, config/, include/, asm/, build/ or run make; never touch other agents' files; write only to ${WAVE}/${t.arm}/${t.name}.c and scratch under ${WAVE}/${t.arm}/scratch_${t.name}/. Budget: up to ~24 compile/match_one iterations, then stop honestly.
Your final answer is the JSON verdict only: fn, arm="${t.arm}", status (MATCH if match_one says MATCH; NEAR if it compiles with closeness>0; FAIL if it never compiled; NO-DRAFT if you wrote nothing), closeness (integer or null), compiles, draft_path, note (one line: what blocked you, or which cookbook § unlocked it).`,
  { label: `${t.arm}:${t.name}`, phase: 'Draft', model: t.arm, schema: VERDICT }
).then(v => v || { fn: t.name, arm: t.arm, status: 'NO-DRAFT', closeness: null, compiles: false, draft_path: '', note: 'agent returned null' })
 .catch(e => ({ fn: t.name, arm: t.arm, status: 'NO-DRAFT', closeness: null, compiles: false, draft_path: '', note: 'agent error: ' + String(e).slice(0, 120) }))))
const byArm = {}
for (const r of results.filter(Boolean)) { (byArm[r.arm] = byArm[r.arm] || []).push(r) }
for (const arm of Object.keys(byArm)) {
  const rs = byArm[arm]
  log(`${arm}: self-reported MATCH ${rs.filter(r => r.status === 'MATCH').length} / NEAR ${rs.filter(r => r.status === 'NEAR').length} / FAIL ${rs.filter(r => r.status === 'FAIL').length} / NO-DRAFT ${rs.filter(r => r.status === 'NO-DRAFT').length} of ${rs.length} (the gate decides — R14)`)
}
return { wave: WAVE, results }
