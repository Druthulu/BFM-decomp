export const meta = {
  name: 'wave-binary',
  description: 'Binary-aware crack wave: fan out toolkit-aware drafter agents over a target batch in ANY binary (not just ov_SC01_077). Each target carries its own asm subdir + cached Ghidra-C + jtbl/o0 flags + an optional matched-ov077 sibling to adapt. Drafting only; the orchestrator runs the byte-gate/bank/sweep serially afterward.',
  phases: [
    { title: 'Draft', detail: 'one xHigh drafter agent per target' },
  ],
}

// args = { binary, targets: [{name, addr, nins, reach, asm, asm_subdir, ghidra_c, own_jtbl, o0, sibling_ov077, kind}], draftDir }
// Returns { draftDir, n, matched, near, drafted: [{fn,status,closeness,klass,where_stuck}] }.
// The whole-binary byte-gate / sweep / propagate is run by the ORCHESTRATOR after this returns
// (it mutates+commits the byte-locked tree, must be serial, and its build loop can exceed an agent Bash timeout).

const DRAFT_SCHEMA = {
  type: 'object', additionalProperties: false,
  required: ['fn', 'status'],
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['match', 'near', 'fail'] },
    closeness: { type: 'integer', description: 'final match_one mismatch count; 0 if MATCH' },
    klass: { type: 'string', description: 'residual class: regalloc-order|schedule|struct|loose-typing|plumbing|jtbl|other' },
    where_stuck: { type: 'string', description: 'one line: what is still off (for the backlog)' },
  },
}

function drafterPrompt(t, binary, draftDir) {
  const o0flag = t.o0 ? ' --o0' : ''
  const o0note = t.o0
    ? `\n-O0 TARGET (this fn is compiled -O0 by a Makefile target-specific CC1FLAGS). Your match_one self-check MUST pass --o0 (included below) or you iterate against the WRONG build step. Read COOKBOOK §18: the classic -O0 residual is the %lo-fold on indexed global access — the CRACK is the ARRAY-OF-STRUCT idiom (\`extern Struct base[];\` sizeof==stride, then \`base[i].field\`; NOT \`*(T*)(&sym+i*stride)\`). At -O0 there is no DCE.\n`
    : ''
  const jtblnote = t.own_jtbl
    ? `\nHAS AN IN-BODY JUMP TABLE (computed jump). Write a C \`switch\` whose case set + default matches the target's dispatch; gcc-2.7.2 emits a jump table when the cases are dense (CASE_VALUES_THRESHOLD). Read COOKBOOK §8/§8e for the jtbl idioms. The whole-binary BANK of a jtbl fn needs a rodata carve (the orchestrator handles that) — your job is byte-correct C for the body incl. the switch.\n`
    : ''
  const sibnote = t.sibling_ov077
    ? `\n★ THERE IS AN ALREADY-MATCHED SIBLING. This function is a per-location family member: the SAME function at address ${t.sibling_ov077} in overlay ov_SC01_077 is ALREADY byte-matched. Its C is your STARTING POINT — find it and ADAPT it to THIS overlay's bytes:
  - Find the matched C: \`grep -n "DEFINE_func_${t.name.replace('func_','').toUpperCase()}\\|func_${t.sibling_ov077.replace('0x','')}" src/shared/engine_core.h src/ov_SC01_077/*.c\` (the body is a DEFINE_func_* macro or an inline def).
  - This overlay's variant differs from ov_SC01_077 ONLY in per-location constants: immediate values, data-symbol addresses (D_*), and callee targets. The CONTROL FLOW / structure is identical.
  - Read THIS overlay's target asm below and rewrite the sibling's C with THIS overlay's exact immediates/symbols. Verify every literal against the asm; the sibling's ov_SC01_077 immediates are WRONG for this overlay.
  - This is the phase's key experiment: a member cracked fresh HERE (not remapped from ov_SC01_077) is expected to sweep across the whole family. Be exact.\n`
    : ''
  const giant = t.nins > 150
    ? `\nGIANT (>150 ins) — READ COOKBOOK §27. (1) The Ghidra-C body structure is usually correct — start there (or the matched sibling above). (2) ARG-ARITY is the #1 giant blocker: declare each callee to the ACTUAL call site (count $a0-$a3 set before each jal), not a canonical guess. (3) grep src/shared/engine_core.h for an already-matched DEFINE_func_* in the same idiom family and mirror its proven C. (4) §17-pin a whole-register regalloc SHIFT, but leave the last-mile regalloc-COALESCING residual for the gate+permuter — get STRUCTURALLY matched and keep the best draft.\n`
    : ''
  return `Match ONE MIPS function for the Brave Fencer Musashi PS1 matching decompilation, in overlay ${binary}.${o0note}${jtblnote}${sibnote}${giant}
GOAL: write C that the pinned compiler (gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker + maspsx --aspsx-version=2.56 --expand-div) compiles to BYTE-IDENTICAL machine code for THIS overlay (${binary}).

TARGET: ${t.name} @ ${t.addr} — ${t.nins} instructions, cross-overlay family reach ${t.reach}.
- Target asm (THE ground truth — ${binary}'s bytes): ${t.asm}
  (each line "/* off vaddr w0 w1 */ mnemonic ..." is the exact encoded instruction.)
- Ghidra-C reference (types/locals/callee names — a scaffold, NOT byte-accurate): ${t.ghidra_c}

THE TOOLKIT (docs/matching-cookbook.md §17–§20, §8, §27, §31 — read the relevant sections; high-leverage moves):
- Register-allocation ORDER: if a call-crossing local lands in the wrong saved reg, PIN it: \`register s32 v __asm__("$16");\` ($16=$s0…). Add a scheduling barrier if the schedule is off. Highest-reach lever.
- Array-of-struct %lo-fold (§18): indexed global access -> \`extern Struct base[];\` (sizeof==stride) + \`base[i].field\`; do NOT materialize \`&sym\`.
- for vs do-while + statement/for-update ORDER (§17) control the branch/delay-slot schedule — pick the form the target's branch layout implies.
- Declaration plumbing: don't over-fret callee extern types — the gate's canon_resident_calls + cast_call_sites + sig_unify reconcile most extern/arity mismatches. Focus on BODY codegen.

PROCESS (you have Bash + Read + Write):
0. Read the LIVE cookbook docs/matching-cookbook.md (the relevant §§ above; it accrues newly-distilled idioms between waves).
1. Read the target asm and the Ghidra-C (and the matched sibling if one is named above).
2. Write your best C (the function definition + any externs it needs) to: ${draftDir}/${t.name}.c
   Write ONLY this one draft file. Do NOT edit docs/, src/, config/, or any other tracked file (the orchestrator owns all cookbook/src edits; a drafter appending to the cookbook injects UNVERIFIED idioms).
   START the file with TWO comment lines (the gate reads them for the flywheel + backlog):
     // @class: <regalloc-order | schedule | remat | struct | iv-combine | loop-guard | loose-typing | plumbing | jtbl | other>
     // @stuck: <one concrete line on the residual, or "none — MATCH">
3. Self-check (fast relocation-masked proxy for the byte-gate):
   .venv/bin/python tools/match_one.py ${t.name} --c ${draftDir}/${t.name}.c --asm-subdir ${t.asm_subdir}${o0flag}
   - "MATCH (N ins)" => byte-identical (relocation-masked). You nailed it. Stop.
   - "N mismatched"  => N instructions differ. Apply the toolkit, iterate to reduce N.
4. Iterate several times; KEEP THE BEST draft in the file (always leave a file, even if imperfect — the whole-binary gate + permuter may finish it; a close near-miss is logged for a human).
5. Return: { fn, status (match|near|fail), closeness (final mismatch count), klass, where_stuck }.

The whole-binary byte-gate (run later by the orchestrator) is the sole arbiter — match_one is a proxy, but a MATCH there almost always banks. Be rigorous; never fabricate a MATCH you did not observe with match_one.`
}

const A = typeof args === 'string' ? JSON.parse(args) : (args || {})
const binary = A.binary || 'ov_SC01_077'
const targets = A.targets || []
const draftDir = A.draftDir || `.run/drafts-${binary}`
if (!targets.length) { log('wave-binary: no targets'); return { draftDir, n: 0, drafted: [] } }

log(`wave-binary: drafting ${targets.length} targets in ${binary} -> ${draftDir} (xHigh agents)`)
phase('Draft')
const drafted = (await parallel(targets.map(t => () =>
  agent(drafterPrompt(t, binary, draftDir), { label: `draft:${t.name}`, phase: 'Draft', schema: DRAFT_SCHEMA, effort: 'xhigh' })
    .then(r => (r ? { ...r, fn: r.fn || t.name } : null))
))).filter(Boolean)

const matched = drafted.filter(d => d.status === 'match').length
const near = drafted.filter(d => d.status === 'near').length
log(`wave-binary: ${drafted.length}/${targets.length} drafted; self-assessed match=${matched} near=${near}`)
return { draftDir, n: drafted.length, matched, near, drafted }
