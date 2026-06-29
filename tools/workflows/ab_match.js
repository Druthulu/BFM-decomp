export const meta = {
  name: 'ab-match',
  description: 'A/B matching experiment: fan out the SAME worker_wave drafter prompt over a frozen target batch, once per ARM (e.g. opus vs haiku), each arm writing to its own draft dir. Opus stays the orchestrator (this script); the per-target drafters run on whatever model the arm specifies. DRAFTING ONLY — no gate_stage, no source mutation, no commits. Ground-truth scoring is done afterward by tools/ab_score.py re-running match_one on every draft (the agents self-report is NOT trusted).',
  phases: [
    { title: 'Draft', detail: 'one drafter agent per (target × arm)' },
  ],
}

// args = { targets:[{name,addr,nins,class,asm,ghidra_c,prior_stuck?,prior_closeness?}],
//          baseDir?:'.run/ab-exp', arms?:[{id,model,effort}] }
// Returns { baseDir, arms, n, byArm:{<id>:{drafted,match,near,fail}}, results:[{fn,arm,status,closeness,klass,where_stuck}] }.

const DRAFT_SCHEMA = {
  type: 'object', additionalProperties: false,
  required: ['fn', 'status'],
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['match', 'near', 'fail'] },
    closeness: { type: 'integer', description: 'final match_one mismatch count; 0 if MATCH' },
    klass: { type: 'string', description: 'residual class: regalloc-order|schedule|struct|loose-typing|plumbing|other' },
    where_stuck: { type: 'string', description: 'one line: what is still off (for the backlog)' },
  },
}

const ASM_SUBDIR = 'asm/ov_SC01_077/nonmatchings/ov_SC01_077'

// --- VERBATIM from worker_wave.js (the proven drafter prompt); only draftDir is per-arm now. ---
function drafterPrompt(t, draftDir) {
  const prior = t.prior_stuck
    ? `\nPRIOR ATTEMPT got stuck here (closeness ${t.prior_closeness}): "${t.prior_stuck}". This is a CLASS-FOCUSED re-attempt — concentrate on that residual; the cookbook may now have a newly-distilled idiom for it.\n`
    : ''
  const giant = t.class === 'GIANT'
    ? `\nGIANT (>150 ins) — READ COOKBOOK §27 (the giant recipe) TOO. Key moves, in order:
  (1) The cached Ghidra-C body structure is usually CORRECT (straight-line + many calls) — start from it.
  (2) ARG-ARITY is the #1 giant blocker: declare each callee to match the ACTUAL call site — count the $a0-$a3
      (+ stack) registers SET before each \`jal\`, NOT a canonical guess. e.g. a helper called with 3 args (a3
      untouched in the asm) -> declare it 3-arg. (The gate reconciles the shared-header canonical later.)
  (3) SIBLING TEMPLATES: grep src/shared/engine_core.h for an already-matched DEFINE_func_* in the same family
      (GPU-packet builder, coord transform) and MIRROR its proven C — e.g. coord strength-reduce
      \`((s32)(D * 10355) << 1) >> 16\`, GPU linked-list pointer \`((u32)addr & 0xFFFFFF) | 0x3000000\`.
  (4) §17-pin the regalloc-SHIFT (whole-hog param->wrong-$s reg), BUT do NOT pin a var whose register the target
      REUSES for a later spill (pinning reserves it -> gcc grabs an EXTRA callee reg). The last-mile residual is
      usually regalloc-COALESCING (one extra callee reg for an accumulator spill) -> get STRUCTURALLY-matched and
      leave the best draft; the gate + permuter grinder finish that mile.\n`
    : ''
  // Region-aware: split-file (_a/_o0) targets carry their own asm subdir in t.asm
  // (asm/ov_SC01_077/nonmatchings/ov_SC01_077_a/<fn>.s). Derive the dir so the match_one
  // self-check finds the right .s; fall back to the main subdir if t.asm is absent.
  const asmSubdir = (t.asm && t.asm.indexOf('/') >= 0) ? t.asm.replace(/\/[^/]+$/, '') : ASM_SUBDIR
  return `Match ONE MIPS function for the Brave Fencer Musashi PS1 matching decompilation (overlay ov_SC01_077).
GOAL: write C that the pinned compiler (gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker + maspsx --aspsx-version=2.56 --expand-div) compiles to BYTE-IDENTICAL machine code.

TARGET: ${t.name} @ ${t.addr} — ${t.nins} instructions, class hint "${t.class}".${prior}${giant}
- Target asm (the ground truth): ${t.asm}
  (each line "/* off vaddr w0 w1 */ mnemonic ..." shows the exact encoded instructions.)
- Ghidra-C reference (types/locals/callee names — NOT byte-accurate, a scaffold): ${t.ghidra_c}

THE TOOLKIT (docs/matching-cookbook.md §17–§20 — read those sections for depth; the high-leverage moves):
- Register-allocation ORDER: if call-crossing locals land in the wrong saved reg vs the target,
  PIN them: \`register s32 v __asm__("$16");\` ($16=$s0,$17=$s1,$18=$s2,…). Add a scheduling barrier
  (a dummy volatile read or reordering) if the schedule is off. THIS is the highest-reach lever.
- Array-of-struct %lo-fold (§18): for indexed global access, declare \`extern Struct base[];\`
  (sizeof(Struct)==stride) and write \`base[i].field\` — folds %lo into the load/store. Do NOT write
  \`*(T*)(&sym + i*stride)\` (that materializes &sym and adds an instruction).
- For-loop vs do-while (§17): \`for(init;cond;upd)\` schedules the back-branch into the delay slot
  differently than a do-while; pick the loop form the target's branch layout implies.
- Statement / for-update order: independent statements emit in source order — reorder to match.
- Declaration plumbing: don't fret callee extern types — the gate's canon_resident_calls +
  cast_call_sites + sig_unify fix most extern/arity mismatches. Focus on the BODY codegen.

PROCESS (you have Bash + Read):
0. Read the LIVE cookbook docs/matching-cookbook.md §17–20 FIRST (and §27 if this is a GIANT) — it accrues newly-distilled idioms between waves; a quirk you'd otherwise grind on may already be solved there.
1. Read the target asm and the Ghidra-C.
2. Write your best C (the function definition + any externs it needs) to: ${draftDir}/${t.name}.c
   (Write ONLY this one draft file. Do NOT edit docs/matching-cookbook.md, src/, config/, or any other tracked
   file — this is an isolated experiment; a drafter mutating the tree pollutes it. Your deliverable is the draft .c and the return value.)
   START the file with TWO comment lines so the residual class travels with the draft:
     // @class: <one of: regalloc-order | schedule | remat | struct | iv-combine | loop-guard | loose-typing | plumbing | other>
     // @stuck: <one concrete line on the residual that remains, or "none — MATCH">
3. Self-check (fast relocation-masked proxy for the byte-gate):
   .venv/bin/python tools/match_one.py ${t.name} --c ${draftDir}/${t.name}.c --asm-subdir ${asmSubdir}
   - "MATCH (N ins)"  => byte-identical (relocation-masked). You nailed it. Stop.
   - "N mismatched"   => N instructions differ. Apply the toolkit, iterate to reduce N.
4. Iterate a few times; KEEP THE BEST draft in the file (always leave a file, even if imperfect —
   the whole-binary gate + the permuter grinder may finish it; a close near-miss is logged for a human).
5. Return: { fn, status (match|near|fail), closeness (final mismatch count), klass, where_stuck }.

The whole-binary byte-gate (run later) is the sole arbiter — match_one is a proxy, but a MATCH there
almost always banks. Be rigorous; never fabricate a MATCH you didn't observe.`
}

// args may arrive as a JSON-encoded string (harness serialization) — parse robustly.
const A = typeof args === 'string' ? JSON.parse(args) : (args || {})
const targets = A.targets || []
const baseDir = A.baseDir || '.run/ab-exp'
const arms = A.arms || [
  { id: 'opus', model: 'opus', effort: 'xhigh' },
  { id: 'haiku', model: 'haiku', effort: 'high' },
]
if (!targets.length) { log('ab-match: no targets'); return { baseDir, arms, n: 0, byArm: {}, results: [] } }

log(`ab-match: ${targets.length} targets × ${arms.length} arms [${arms.map(x => x.id).join(', ')}] -> ${baseDir}/<arm>`)
phase('Draft')

// Flatten to (target × arm) jobs; each arm writes to its own subdir.
const jobs = []
for (const t of targets) for (const arm of arms) jobs.push({ t, arm })

const results = (await parallel(jobs.map(j => () =>
  agent(drafterPrompt(j.t, `${baseDir}/${j.arm.id}`), {
    label: `${j.arm.id}:${j.t.name}`, phase: 'Draft', schema: DRAFT_SCHEMA,
    model: j.arm.model, effort: j.arm.effort,
  }).then(r => (r ? { ...r, fn: r.fn || j.t.name, arm: j.arm.id } : null))
))).filter(Boolean)

const byArm = {}
for (const arm of arms) {
  const rs = results.filter(r => r.arm === arm.id)
  byArm[arm.id] = {
    drafted: rs.length,
    match: rs.filter(r => r.status === 'match').length,
    near: rs.filter(r => r.status === 'near').length,
    fail: rs.filter(r => r.status === 'fail').length,
  }
}
log(`ab-match: self-reported -> ${arms.map(a => `${a.id} match=${byArm[a.id].match}/${byArm[a.id].drafted}`).join('  ')}`)
log('ab-match: run tools/ab_score.py for GROUND-TRUTH match_one scoring (self-report above is not authoritative).')
return { baseDir, arms, n: targets.length, byArm, results }
