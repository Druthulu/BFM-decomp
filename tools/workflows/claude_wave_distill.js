export const meta = {
  name: 't4-idiom-distill',
  description: 'R16 flywheel: distill the unlocking lesson from each byte-proven T4 transcript, verify novelty against the cookbook, return §-formatted candidates',
  phases: [
    { title: 'Extract', detail: '31 transcripts -> one lesson each' },
    { title: 'Verify', detail: 'novel claims grepped against docs/matching-cookbook.md' },
  ],
}
const REPO = '/home/musashi/bfm-decomp'
const WFDIR = '/home/musashi/.claude/projects/-home-musashi-bfm-decomp/b0026d2d-2724-4aed-813a-3deef224d210/subagents/workflows/wf_c691ef44-320/'
const LESSON = {
  type: 'object',
  properties: {
    fn: { type: 'string' }, arm: { type: 'string' },
    title: { type: 'string' },
    mechanism: { type: 'string' },
    asm_tell: { type: 'string' },
    c_shape: { type: 'string' },
    evidence: { type: 'string' },
    cookbook_refs_used: { type: 'array', items: { type: 'string' } },
    novel_claim: { type: 'boolean' },
    trivial: { type: 'boolean' },
  },
  required: ['fn', 'arm', 'title', 'mechanism', 'asm_tell', 'c_shape', 'evidence', 'cookbook_refs_used', 'novel_claim', 'trivial'],
}
const VERDICT = {
  type: 'object',
  properties: {
    fn: { type: 'string' }, title: { type: 'string' },
    verdict: { type: 'string', enum: ['COVERED', 'NEW', 'ADDENDUM', 'REFUTED'] },
    covered_by: { type: 'string' },
    entry_markdown: { type: 'string' },
    why: { type: 'string' },
  },
  required: ['fn', 'title', 'verdict', 'covered_by', 'entry_markdown', 'why'],
}
const lessons = await pipeline(
  args.targets,
  t => agent(
`You are distilling ONE byte-proven decompilation transcript for the project's matching cookbook (docs/matching-cookbook.md, gcc-2.7.2 MIPS idioms). Repo: ${REPO}.
Transcript (JSONL, an agent's full tool trace): ${t.transcript.replace("WF/", WFDIR)}
Function: ${t.fn} (arm ${t.arm}); the whole-binary byte-gate ACCEPTED the final draft, so the final body is ground truth. The agent's own closing note was: "${t.note}"

Read the transcript. Find the moment(s) the masked diff (match_one closeness) dropped to 0 and what C change caused it. Report ONE lesson — the most generalizable one — as:
  title: <=12 words, symptom-keyed (what you see in the diff)
  mechanism: why gcc-2.7.2 emits it (one or two sentences; say "unknown" honestly if the transcript only shows the fix)
  asm_tell: the instruction pattern that signals it
  c_shape: the C construct that reproduces it (a short snippet is fine)
  evidence: the closeness path (e.g. "closeness 7 -> 0 after X"; quote the exact match_one line(s))
  cookbook_refs_used: every § the agent grepped/cited that mattered
  novel_claim: true only if the transcript did NOT get the fix from an existing cookbook §; false if it merely applied one
  trivial: true if the lesson is "read the asm / fix a typo / use the right symbol" (no compiler law)
Read only; write nothing.`,
    { label: `extract:${t.arm}:${t.fn}`, phase: 'Extract', model: 'sonnet', schema: LESSON }),
  (lesson, t) => {
    if (!lesson || lesson.trivial || !lesson.novel_claim) return lesson ? { ...lesson, verdict: lesson.trivial ? 'TRIVIAL' : 'APPLIED-EXISTING' } : null
    return agent(
`You are the cookbook verifier for the Brave Fencer Musashi decompilation (repo ${REPO}). A distiller claims a NEW gcc-2.7.2 idiom from a byte-proven transcript:
  fn: ${t.fn}   title: ${lesson.title}
  mechanism: ${lesson.mechanism}
  asm_tell: ${lesson.asm_tell}
  c_shape: ${lesson.c_shape}
  evidence: ${lesson.evidence}
  refs the agent used: ${JSON.stringify(lesson.cookbook_refs_used)}
Check docs/matching-cookbook.md (grep for the mechanism, the instruction pattern, the C construct; docs/cookbook-index.md is symptom-keyed) and decide:
  COVERED  — an existing § already states this law (name it in covered_by)
  ADDENDUM — an existing § is close but this adds a byte-proven refinement (name it; entry_markdown = a 3-8 line addendum paragraph starting "**Addendum (P31 S62 T4, ${t.fn}):**")
  NEW      — no § states it; entry_markdown = a full section in the book's style, header "## §NNN — <TITLE IN CAPS> (P31 S62 T4; byte-proven ${t.fn})" with NNN left literally as NNN, then the tell, the mechanism, the C shape, the evidence line
  REFUTED  — the claim contradicts a byte-proven § or the evidence does not support it (say why)
Quote the § numbers you checked in why. Read only; write nothing.`,
      { label: `verify:${t.fn}`, phase: 'Verify', model: 'opus', schema: VERDICT }).then(v => ({ ...lesson, ...(v || { verdict: 'UNVERIFIED', why: 'verifier returned null' }) }))
  }
)
const out = lessons.filter(Boolean)
const tally = {}
for (const l of out) tally[l.verdict] = (tally[l.verdict] || 0) + 1
log('verdicts: ' + JSON.stringify(tally))
return { lessons: out }