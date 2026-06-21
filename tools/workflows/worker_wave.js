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
  return `Match ONE MIPS function for the Brave Fencer Musashi PS1 matching decompilation (overlay ov_SC01_077).
GOAL: write C that the pinned compiler (gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker + maspsx --aspsx-version=2.56 --expand-div) compiles to BYTE-IDENTICAL machine code.

TARGET: ${t.name} @ ${t.addr} — ${t.nins} instructions, class hint "${t.class}".
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
1. Read the target asm and the Ghidra-C.
2. Write your best C (the function definition + any externs it needs) to: ${draftDir}/${t.name}.c
3. Self-check (fast relocation-masked proxy for the byte-gate):
   .venv/bin/python tools/match_one.py ${t.name} --c ${draftDir}/${t.name}.c --asm-subdir ${ASM_SUBDIR}
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
