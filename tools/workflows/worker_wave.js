export const meta = {
  name: 'worker-wave',
  description: 'Phase-21 worker wave: fan out toolkit-aware drafter agents over a target batch; each writes its best matching C to the drafts dir. The orchestrator runs gate_stage on the dir afterward (byte-gate + propagate + backlog).',
  phases: [
    { title: 'Draft', detail: 'one xHigh drafter agent per target' },
  ],
}

// args = { targets: [{name, addr, nins, class, asm, ghidra_c}], draftDir }
// Returns { draftDir, n, drafted: [{fn,status,closeness,klass,where_stuck}] }.
// NOTE: drafting only. The byte-gate / propagate / backlog (gate_stage.py) is run by the
// ORCHESTRATOR after this returns — it mutates+commits the byte-locked tree and must be
// serial (one wave at a time), and its build loop can exceed an agent's Bash timeout.

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
  // -O0 targets (the ov_SC01_077_o0 cluster / whale _o0b): the TU is compiled -O0 by a Makefile
  // target-specific CC1FLAGS, so match_one MUST self-check with --o0 or the agent iterates against
  // the WRONG build step (the Phase-29 Task-1 trap that manufactured the "~3%" swing number: a -O0
  // target compiled -O2 can NEVER match). §53/§54 law: reproduce every build step the target needs.
  const o0flag = t.o0 ? ' --o0' : ''
  const o0note = t.o0
    ? `\n-O0 TARGET (this fn lives in an -O0-compiled split, ${asmSubdir}). Your match_one self-check MUST pass --o0
  (already included below). Read COOKBOOK §18 + §18-P29: this cluster's classic residual is the %lo-fold on
  indexed global access — our cc1 materializes the address (lui;addiu;addu;sw 0(reg)) where the original folds
  %lo (lui;addu idx;sw %lo(sym)(reg), 1 ins shorter). The CRACK (§18/T3a, byte-proven) is the ARRAY-OF-STRUCT
  idiom: \`extern Struct base[];\` with sizeof(Struct)==stride, then \`base[i].field\`. Do NOT write
  \`*(T*)(&sym + i*stride)\` — that materializes &sym. At -O0 there is no DCE, so an unused local reserves its
  var region (frame-pad induction, §42 lever 3) with zero body instructions.\n`
    : ''
  return `Match ONE MIPS function for the Brave Fencer Musashi PS1 matching decompilation (overlay ov_SC01_077).${o0note}
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
   file — the orchestrator's distill step owns all cookbook updates; a drafter appending to the cookbook injects
   UNVERIFIED near-miss idioms that pollute every future wave. Your deliverable is the draft .c and the return value.)
   START the file with TWO comment lines so the residual class travels with the draft (the gate reads them for the learning flywheel + backlog):
     // @class: <one of: regalloc-order | schedule | remat | struct | iv-combine | loop-guard | loose-typing | plumbing | other>
     // @stuck: <one concrete line on the residual that remains, or "none — MATCH">
3. Self-check (fast relocation-masked proxy for the byte-gate):
   .venv/bin/python tools/match_one.py ${t.name} --c ${draftDir}/${t.name}.c --asm-subdir ${asmSubdir}${o0flag}
   - "MATCH (N ins)"  => byte-identical (relocation-masked). You nailed it. Stop.
   - "N mismatched"   => N instructions differ. Apply the toolkit, iterate to reduce N.
4. Iterate a few times; KEEP THE BEST draft in the file (always leave a file, even if imperfect —
   the whole-binary gate + the permuter grinder may finish it; a close near-miss is logged for a human).
5. Return: { fn, status (match|near|fail), closeness (final mismatch count), klass, where_stuck }.

The whole-binary byte-gate (run later) is the sole arbiter — match_one is a proxy, but a MATCH there
almost always banks. Be rigorous; never fabricate a MATCH you didn't observe.`
}

// args may arrive as a JSON-encoded string (harness serialization) — parse robustly (§20 gotcha).
const A = typeof args === 'string' ? JSON.parse(args) : (args || {})
const targets = A.targets || []
const draftDir = A.draftDir || '.run/drafts-wave'
if (!targets.length) { log('worker-wave: no targets'); return { draftDir, n: 0, drafted: [] } }

log(`worker-wave: drafting ${targets.length} targets -> ${draftDir} (xHigh agents)`)
phase('Draft')
const drafted = (await parallel(targets.map(t => () =>
  agent(drafterPrompt(t, draftDir), { label: `draft:${t.name}`, phase: 'Draft', schema: DRAFT_SCHEMA, effort: 'xhigh' })
    .then(r => (r ? { ...r, fn: r.fn || t.name } : null))
))).filter(Boolean)

const matched = drafted.filter(d => d.status === 'match').length
const near = drafted.filter(d => d.status === 'near').length
log(`worker-wave: ${drafted.length}/${targets.length} drafted; self-assessed match=${matched} near=${near}`)
return { draftDir, n: drafted.length, matched, near, drafted }
