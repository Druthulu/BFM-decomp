export const meta = {
  name: 'family-core-wave',
  description: 'SESSION-21: fan out one drafter agent per h_seq FAMILY EXEMPLAR. Each crack templates to ~138 members, so a bank here is worth 10k-51k instructions. Drafting only — the orchestrator runs the gate ladder afterward.',
  phases: [
    { title: 'Draft', detail: 'one xHigh drafter agent per family exemplar' },
  ],
}

// args = { targets: [...], draftDir }
// Returns { draftDir, n, matched, near, drafted: [...] }
//
// WHY THIS EXISTS ALONGSIDE worker_wave.js: worker_wave predates the SESSION-20 laws (§84-§89) and
// treats every target as an isolated function. These targets are FAMILY EXEMPLARS — the measured
// frontier (SESSION-21 T1) is 1,342 substantial families / 1,298,135 templatable ins = 55% of all
// remaining weighted instructions, and only 9.0% of remaining stubs are h_exact-free. So the
// endgame is exemplar cracks, not 36,020 individual functions, and each draft below carries its
// family's stake so the agent knows what a sloppy near-miss costs.
//
// DRAFTING ONLY. The whole-binary byte-gate (gate_stage.py) is the sole arbiter (G3/P9) and is run
// by the ORCHESTRATOR: it mutates the byte-locked tree, must be serial, and its build loop exceeds
// an agent's Bash timeout.

const DRAFT_SCHEMA = {
  type: 'object', additionalProperties: false,
  required: ['fn', 'status'],
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['match', 'near', 'fail'] },
    closeness: { type: 'integer', description: 'final match_one mismatch count; 0 if MATCH' },
    klass: { type: 'string', description: 'regalloc-order|schedule|remat|struct|iv-combine|loop-guard|loose-typing|plumbing|length-drift|other' },
    symcheck: { type: 'string', description: 'CLEAN | MISMATCH:<detail> | not-run (only meaningful when status=match)' },
    where_stuck: { type: 'string', description: 'one concrete line: what is still off (goes to the backlog)' },
  },
}

function drafterPrompt(t, draftDir) {
  const asmSubdir = t.asm.replace(/\/[^/]+$/, '')
  const o0flag = t.o0 ? ' --o0' : ''

  const prior = t.prior_closeness !== null && t.prior_closeness !== undefined
    ? `\nPRIOR ATTEMPT reached closeness ${t.prior_closeness} (class "${t.prior_stuck || '?'}"). Treat that as a
  HYPOTHESIS WITH A CITATION, not a foundation (§88e — a round-2 refuted round-1's named lever three
  different ways). Re-derive from the bytes. The cookbook has gained §84-§89 since that attempt.\n`
    : ''

  const o0note = t.o0
    ? `\n⚠️ -O0 TARGET — this function lives in ${asmSubdir}, an -O0-compiled split (Makefile target-specific
  CC1FLAGS). Your match_one self-check MUST pass --o0 (already in the command below) or you will iterate
  against the WRONG build step — that exact trap manufactured Phase-29's bogus "~3%" swing number.
  Read cookbook §18. The classic -O0 residual here is the %lo-fold on indexed global access: our cc1
  materializes the address (lui;addiu;addu;sw 0(reg)) where the original folds %lo (lui;addu idx;
  sw %lo(sym)(reg), one instruction shorter). THE CRACK (§18/T3a, byte-proven) is the ARRAY-OF-STRUCT
  idiom: \`extern Struct base[];\` with sizeof(Struct)==stride, then \`base[i].field\`. Do NOT write
  \`*(T*)(&sym + i*stride)\` — that materializes &sym. At -O0 there is no DCE, so an unused local still
  reserves its var region (frame-pad induction).\n`
    : ''

  const giant = t.nins > 150
    ? `\nGIANT (${t.nins} ins) — read cookbook §27 + §44 + §69 as well. Order of moves:
  (1) The cached Ghidra-C body structure is usually CORRECT (straight-line + many calls) — start there.
  (2) ARG-ARITY is the #1 giant blocker: declare each callee to match the ACTUAL call site — count the
      $a0-$a3 (+stack) registers SET before each \`jal\`, never a canonical guess.
  (3) SIBLING TEMPLATES (§71): grep src/shared/engine_core.h for an already-matched DEFINE_func_* in the
      same family (GPU-packet builder, coord transform) and MIRROR its proven C.
  (4) The last mile on a giant is usually regalloc-COALESCING (one extra callee reg for an accumulator
      spill). Get STRUCTURALLY matched and leave the best draft — the gate + permuter finish that mile.
  (5) §83a: on a LENGTH drift the index-wise mismatch count is NOT a progress signal — a +5 length delta
      smears every later index. Report the structural delta, not the raw count.\n`
    : ''

  return `Match ONE MIPS function BYTE-IDENTICALLY for the Brave Fencer Musashi PS1 matching decompilation
(overlay ov_SC01_077). Target compiler, exactly:
  tools/bin/gcc-2.7.2-psx/cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
  -> maspsx --aspsx-version=2.56 --expand-div -> mipsel-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0

★ WHY THIS ONE MATTERS: ${t.name} is the EXEMPLAR of an h_seq structural family with ${t.members} members
  across the overlay fleet. Cracking it templates mechanically to all of them — this single draft is worth
  ~${t.templ_ins.toLocaleString()} instructions of the remaining game. A near-miss you abandon costs all of that;
  a rigorous near-miss with a precisely-named residual is still valuable (it routes to the permuter/backlog).

TARGET: ${t.name} @ ${t.addr} — ${t.nins} instructions.${prior}${o0note}${giant}
- Ground truth asm: ${t.asm}
  (lines read "/* off vaddr w0 w1 */ mnemonic ..." — the exact encoded instructions.)
- Ghidra-C scaffold (types/locals/callee names; NOT byte-accurate): ${t.ghidra_c}
- This function's translation unit: ${t.src}

════════ THE FOUR INTEGRATION RULES (§58 / §87) — obey these or a perfect body still cannot bank ════════
1. DATA SYMBOL NAMES: use the splat spelling \`D_<UPPERHEX>\` (e.g. D_801D9C20). NEVER Ghidra's
   \`DAT_801d9c20\` / \`PTR_DAT_...\`. match_one links your own extern so it will NOT notice; the
   whole-binary link then fails \`undefined reference\`. Verify a label exists before you rely on it:
     grep -rn "D_<UPPERHEX>" asm/ov_SC01_077/data/ config/symbols.ov_SC01_077.txt config/symbols.us.txt
2. NEVER INVENT A SYMBOL. A draft that declares an extern no symbol table defines reads MATCH under
   match_one (which COMPILES but never LINKS, §87) and can never bank. No \`_s\` suffixes, no aliases.
3. CALLEE SIGNATURES: prefer the canonical sig already in src/shared/engine_core.h (grep for
   \`DEFINE_${'${'}callee}\` / its extern). If you must diverge, diverge in the BODY, not by redeclaring —
   the gate's cast_call_sites/sig_unify reconcile most extern+arity mismatches afterward.
4. Do NOT chase declaration plumbing. Spend your effort on BODY CODEGEN; the gate ladder
   (canon_resident_calls -> cast_call_sites -> reconcile_tu -> arity -> sig_unify) fixes decls.

════════ THE CODEGEN TOOLKIT (read the live docs — they accrue idioms between waves) ════════
READ FIRST: docs/matching-cookbook.md §17 (the core toolkit), §31 (the gcc-2.7.2 codegen-map INDEX +
residual->lever triage table), and §55a (the newest byte-proven levers). For a residual you cannot place,
the map itself is docs/gcc-2.7.2-map/{sched,regalloc,loop,cse_expr}.md — each entry is source-cited to the
real gcc-2.7.2 and says either "here is the C lever" or "intrinsic -> permuter".

High-leverage levers, in rough order of reach:
- REGALLOC ORDER: call-crossing locals landing in the wrong saved register. Pin them:
  \`register s32 v __asm__("$16");\` ($16=$s0 $17=$s1 $18=$s2 …). BUT §72: a pin is a PREFERENCE, not a
  reservation, and §74: a CALLER-saved pin spanning a \`jal\` is a hazard. Prefer the pin-free levers first
  (declaration order, def/use placement, variable reuse — §76: allocno CLASS is the dominant lever and C
  reaches it only through declaration scope and variable reuse).
- SCHEDULING: statement order controls sched1 placement. §55a: routing a load through a temp assigned in
  BOTH halves of a branch makes reg_n_sets==2, killing the birthing_insn_p priority boost at zero byte cost.
  \`__asm__("" : "=r"(v) : "0"(v))\` is a zero-code CSE fence.
- LOOPS: for(;;) vs do-while changes the back-branch/delay-slot layout — pick the form the target implies.
- SWITCH: CASE_VALUES_THRESHOLD is 5. Fewer than 5 cases => gcc emits a branch TREE, not a jump table, so a
  guard like \`if (x != 0)\` must stay OUTSIDE the switch or a 5th case forces a table (§55a).
- §88: cross_jump will NOT merge a common suffix containing a CALL — write those tails longhand, never
  hand-factor a call-bearing tail. And §88c: there is no \`beqi\`, so \`==\` constants are ALWAYS
  materialised — the §78 literal-position law applies to ORDERED comparisons only.

════════ PROCESS (you have Bash + Read; work ONLY in your own files) ════════
0. Read the cookbook sections above. Read the target asm and the Ghidra-C.
1. Write your best C (the definition + the externs it needs) to: ${draftDir}/${t.name}.c
   Begin the file with exactly two comment lines so the class travels with the draft:
     // @class: <regalloc-order|schedule|remat|struct|iv-combine|loop-guard|loose-typing|plumbing|length-drift|other>
     // @stuck: <one concrete line on the remaining residual, or "none — MATCH">
2. Self-check (relocation-masked proxy for the byte-gate):
     .venv/bin/python tools/match_one.py ${t.name} --c ${draftDir}/${t.name}.c --asm-subdir ${asmSubdir}${o0flag}
   "MATCH (N ins)" => byte-identical under masking. "N mismatched" => iterate; apply the toolkit.
3. IF AND ONLY IF you reach MATCH, run the symbol-set guard (this is what makes a MATCH bankable, §67a/§87):
     .venv/bin/python tools/symcheck.py ${t.name} --c ${draftDir}/${t.name}.c --asm-subdir ${asmSubdir}${o0flag}
   Report its verdict in the \`symcheck\` field. A MISMATCH means you referenced the wrong or a
   non-existent symbol — fix it; that draft cannot bank otherwise.
4. Iterate. ALWAYS leave a file, even imperfect — a close near-miss with a named residual is real value.

════════ HARD CONSTRAINTS ════════
- Write EXACTLY ONE file: ${draftDir}/${t.name}.c . Do NOT edit src/, config/, docs/, the cookbook, or any
  other tracked file. (A drafter appending to the cookbook injects UNVERIFIED idioms into every future wave;
  the orchestrator owns distillation.)
- ⛔ NEVER run \`make clean\`, \`make extract\`, \`make extract-all\`, or any make target that rebuilds or
  mutates the tree. Other agents are reading asm/ concurrently and you will destroy their ground truth.
  \`match_one\` and \`symcheck\` are self-contained and safe. Nothing else builds.
- Never report a MATCH you did not literally observe in match_one's output (G3/P9). An honest "near,
  closeness=7, regalloc-order, the accumulator lands in $s3 not $s2" is worth more than a false MATCH.

Return: { fn, status (match|near|fail), closeness, klass, symcheck, where_stuck }.`
}

const A = typeof args === 'string' ? JSON.parse(args) : (args || {})
const targets = A.targets || []
const draftDir = A.draftDir || '.run/drafts-s21'
if (!targets.length) { log('family-core-wave: no targets'); return { draftDir, n: 0, drafted: [] } }

const stake = targets.reduce((s, t) => s + (t.templ_ins || 0), 0)
log(`family-core-wave: ${targets.length} family exemplars -> ${draftDir} | combined stake ${stake.toLocaleString()} templatable ins`)
phase('Draft')

const drafted = (await parallel(targets.map(t => () =>
  agent(drafterPrompt(t, draftDir), {
    label: `crack:${t.name}(x${t.members})`, phase: 'Draft', schema: DRAFT_SCHEMA, effort: 'xhigh',
  }).then(r => (r ? { ...r, fn: r.fn || t.name, members: t.members, templ_ins: t.templ_ins, nins: t.nins } : null))
))).filter(Boolean)

const matched = drafted.filter(d => d.status === 'match')
const near = drafted.filter(d => d.status === 'near')
const wonStake = matched.reduce((s, d) => s + (d.templ_ins || 0), 0)
log(`family-core-wave: ${drafted.length}/${targets.length} returned; self-assessed MATCH=${matched.length} near=${near.length}`)
log(`family-core-wave: self-assessed MATCH stake = ${wonStake.toLocaleString()} templatable ins (CANDIDATES — the byte-gate decides)`)

return { draftDir, n: drafted.length, matched: matched.length, near: near.length, wonStake, drafted }
