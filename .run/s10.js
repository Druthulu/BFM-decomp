export const meta = {
  name: 'p30-s10-x29-w2-SONNET',
  description: 'P30 wave 4b: draft the volume-lane B-shape families (10-19 members, <=60 ins)',
  phases: [
    { title: 'Draft', detail: 'one agent per target, size-routed per the §136i ladder (haiku/sonnet/opus)' },
    { title: 'Escalate', detail: 'next rung up (haiku->sonnet, sonnet->opus) on any non-MATCH' },
  ],
}

// args = { targets: [...compact records...], extra: "<idioms promoted from the previous wave>" }
// Accept a JSON string too — an invocation can deliver args stringified and pipeline() then dies.
const A = {targets: [{"fn": "func_8017D174", "ov": "ov_SC03_103", "sub": "asm/ov_SC03_103/nonmatchings/ov_SC03_103_jr_8017C294", "tu": "src/ov_SC03_103/ov_SC03_103_jr_8017C294.c", "n": 793, "m": 5, "ti": 3965, "model": "sonnet", "seed": 1}, {"fn": "func_80186E24", "ov": "ov_SC04_018", "sub": "asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C", "tu": "src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c", "n": 611, "m": 5, "ti": 3055, "model": "sonnet", "seed": 1}, {"fn": "func_8017E2EC", "ov": "ov_SC03_114", "sub": "asm/ov_SC03_114/nonmatchings/ov_SC03_114_jr_8017BEBC", "tu": "src/ov_SC03_114/ov_SC03_114_jr_8017BEBC.c", "n": 296, "m": 7, "ti": 2072, "model": "sonnet", "seed": 1}, {"fn": "func_8018A2E0", "ov": "ov_SC04_018", "sub": "asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C", "tu": "src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c", "n": 250, "m": 6, "ti": 1500, "model": "sonnet", "seed": 0}, {"fn": "func_8017C8FC", "ov": "ov_SC03_014", "sub": "asm/ov_SC03_014/nonmatchings/ov_SC03_014_jr_8017AE2C", "tu": "src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c", "n": 210, "m": 7, "ti": 1470, "model": "sonnet", "seed": 0}, {"fn": "func_8017F2E8", "ov": "ov_SC06_008", "sub": "asm/ov_SC06_008/nonmatchings/ov_SC06_008_jr_8017C294", "tu": "src/ov_SC06_008/ov_SC06_008_jr_8017C294.c", "n": 207, "m": 7, "ti": 1449, "model": "sonnet", "seed": 1}, {"fn": "func_80181EE0", "ov": "ov_SC06_008", "sub": "asm/ov_SC06_008/nonmatchings/ov_SC06_008_jr_8017C294", "tu": "src/ov_SC06_008/ov_SC06_008_jr_8017C294.c", "n": 198, "m": 7, "ti": 1386, "model": "sonnet", "seed": 1}, {"fn": "func_8017CDF0", "ov": "ov_SC07_000", "sub": "asm/ov_SC07_000/nonmatchings/ov_SC07_000_jr_8017BEBC", "tu": "src/ov_SC07_000/ov_SC07_000_jr_8017BEBC.c", "n": 693, "m": 2, "ti": 1386, "model": "sonnet", "seed": 1}, {"fn": "func_80181688", "ov": "ov_SC02_026", "sub": "asm/ov_SC02_026/nonmatchings/ov_SC02_026_jr_8017C180", "tu": "src/ov_SC02_026/ov_SC02_026_jr_8017C180.c", "n": 230, "m": 6, "ti": 1380, "model": "sonnet", "seed": 1}, {"fn": "func_8017E9F4", "ov": "ov_SC06_011", "sub": "asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017BEBC", "tu": "src/ov_SC06_011/ov_SC06_011_jr_8017BEBC.c", "n": 221, "m": 6, "ti": 1326, "model": "sonnet", "seed": 1}, {"fn": "func_8017D318", "ov": "ov_SC03_014", "sub": "asm/ov_SC03_014/nonmatchings/ov_SC03_014_jr_8017AE2C", "tu": "src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c", "n": 184, "m": 7, "ti": 1288, "model": "sonnet", "seed": 0}, {"fn": "func_801829BC", "ov": "ov_SC02_028", "sub": "asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_8017D898", "tu": "src/ov_SC02_028/ov_SC02_028_jr_8017D898.c", "n": 150, "m": 8, "ti": 1200, "model": "sonnet", "seed": 1}, {"fn": "func_8018F060", "ov": "ov_SC06_018", "sub": "asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", "tu": "src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c", "n": 397, "m": 3, "ti": 1191, "model": "sonnet", "seed": 1}, {"fn": "func_8017F624", "ov": "ov_SC06_008", "sub": "asm/ov_SC06_008/nonmatchings/ov_SC06_008_jr_8017C294", "tu": "src/ov_SC06_008/ov_SC06_008_jr_8017C294.c", "n": 170, "m": 7, "ti": 1190, "model": "sonnet", "seed": 1}, {"fn": "func_80190144", "ov": "ov_SC02_005", "sub": "asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", "tu": "src/ov_SC02_005/ov_SC02_005_jr_8017AE2C.c", "n": 128, "m": 9, "ti": 1152, "model": "sonnet", "seed": 1}, {"fn": "func_801813D0", "ov": "ov_SC06_008", "sub": "asm/ov_SC06_008/nonmatchings/ov_SC06_008_jr_8017C294", "tu": "src/ov_SC06_008/ov_SC06_008_jr_8017C294.c", "n": 163, "m": 7, "ti": 1141, "model": "sonnet", "seed": 1}, {"fn": "func_8018D870", "ov": "ov_SC06_018", "sub": "asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", "tu": "src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c", "n": 380, "m": 3, "ti": 1140, "model": "sonnet", "seed": 1}, {"fn": "func_8017E3AC", "ov": "ov_SC04_018", "sub": "asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C", "tu": "src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c", "n": 125, "m": 9, "ti": 1125, "model": "sonnet", "seed": 1}, {"fn": "func_8018797C", "ov": "ov_SC02_011", "sub": "asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", "tu": "src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c", "n": 219, "m": 5, "ti": 1095, "model": "sonnet", "seed": 1}, {"fn": "func_80188428", "ov": "ov_SC04_018", "sub": "asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C", "tu": "src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c", "n": 212, "m": 5, "ti": 1060, "model": "sonnet", "seed": 0}, {"fn": "func_8017F40C", "ov": "ov_SC03_028", "sub": "asm/ov_SC03_028/nonmatchings/ov_SC03_028_jr_8017AE2C", "tu": "src/ov_SC03_028/ov_SC03_028_jr_8017AE2C.c", "n": 174, "m": 6, "ti": 1044, "model": "sonnet", "seed": 1}, {"fn": "func_80187DD0", "ov": "ov_SC06_018", "sub": "asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", "tu": "src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c", "n": 174, "m": 6, "ti": 1044, "model": "sonnet", "seed": 1}, {"fn": "func_801880EC", "ov": "ov_SC04_018", "sub": "asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C", "tu": "src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c", "n": 207, "m": 5, "ti": 1035, "model": "sonnet", "seed": 0}, {"fn": "func_8018A21C", "ov": "ov_SC02_027", "sub": "asm/ov_SC02_027/nonmatchings/ov_SC02_027_jr_8017D898", "tu": "src/ov_SC02_027/ov_SC02_027_jr_8017D898.c", "n": 128, "m": 8, "ti": 1024, "model": "sonnet", "seed": 1}, {"fn": "func_80187674", "ov": "ov_SC03_118", "sub": "asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_8017FB84", "tu": "src/ov_SC03_118/ov_SC03_118_jr_8017FB84.c", "n": 145, "m": 7, "ti": 1015, "model": "sonnet", "seed": 0}, {"fn": "func_80189000", "ov": "ov_SC06_018", "sub": "asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", "tu": "src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c", "n": 161, "m": 6, "ti": 966, "model": "sonnet", "seed": 1}, {"fn": "func_8018457C", "ov": "ov_SC06_018", "sub": "asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", "tu": "src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c", "n": 160, "m": 6, "ti": 960, "model": "sonnet", "seed": 1}, {"fn": "func_8018A390", "ov": "ov_SC03_014", "sub": "asm/ov_SC03_014/nonmatchings/ov_SC03_014_jr_801848E4", "tu": "src/ov_SC03_014/ov_SC03_014_jr_801848E4.c", "n": 136, "m": 7, "ti": 952, "model": "sonnet", "seed": 0}, {"fn": "func_8017D38C", "ov": "ov_SC02_041", "sub": "asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", "tu": "src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c", "n": 231, "m": 4, "ti": 924, "model": "sonnet", "seed": 1}, {"fn": "func_801858BC", "ov": "ov_SC03_089", "sub": "asm/ov_SC03_089/nonmatchings/ov_SC03_089_jr_8017CA80", "tu": "src/ov_SC03_089/ov_SC03_089_jr_8017CA80.c", "n": 231, "m": 4, "ti": 924, "model": "sonnet", "seed": 1}], extra: "START HERE \u2014 SIBLING-FIRST IS THE FASTEST ROUTE (\u00a7136c, measured this session: it produced several\nFIRST-DRAFT matches). Before you derive anything from the .s:\n  1. grep src/shared/engine_core.h for a `DEFINE_func_*` macro body that is a NEAR-TWIN of your\n     target (same struct-offset chain, same shape, differing only in constants/one call). This is a\n     family wave \u2014 the twin usually EXISTS, because that is what a family is.\n  2. grep your own TU for an already-BANKED sibling (a real function definition, not an INCLUDE_ASM).\n  3. Reuse its EXPRESSION FORMS and its DECLARATION FORMS verbatim. They are already byte-proven to\n     produce the gcc-2.7.2 schedule and register assignment you need.\nSearch order: engine_core.h near-twin -> same-TU banked sibling -> the .s -> the Ghidra seed LAST\n(the seed was byte-proven to be an ENTIRELY DIFFERENT body twice this session).\n\nTHE LOCAL-VARIABLE LEVER (\u00a7136 \u2014 highest-yield finding, 25 banks). gcc-2.7.2 allocates ONE PSEUDO\nPER C LOCAL, and local-alloc.c:472 REFUSES a local allocno whose REG_N_DEATHS > 1 \u2014 promoting it to\na GLOBAL allocno that loses the low register. The number and scope of your locals moves whole\nregister assignments. REACH FOR THIS BEFORE register __asm__ PINS.\n L1. Same $v0/$v1 pair swapped in ONE arm only => you reused ONE local across N arms. SPLIT it into\n     per-arm block-scoped locals.\n L2. One extra `sw $sN` in the prologue, frame otherwise identical => SPLIT a compound initializer:\n     `x = *(u8*)p << k;` makes TWO pseudos; `x = *(u8*)p; x = x << k;` reuses one.\n L3. An extra `addu $vX,$v0,$zero` after a `jal` AND a later copy of the same value => the source\n     had TWO variables with the first PINNED (an unpinned pseudo coalesces the pair away).\n L4. LENGTH-DRIFT short by `addiu $sN,$sp,K` + a save/restore pair => write a POINTER local assigned\n     before the loop and used only inside it.\n L5. Local stack slots are assigned in DECLARATION order ascending from 0x10, independent of use\n     order. Frame-offset drift with correct code is a declaration-ORDER problem.\n\nTYPE-FORM RULES:\n T1. A real `mult $rX,$rY` with a small constant => the multiplier is a NON-CONST LOCAL, not a\n     literal (a literal goes through synth_mult's sll/addu chain). `s32 r = K;` as its own statement.\n T2. `li $sN,0xfff0` + `addu` where the target has `addiu $vN,$vN,-0x10` => gcc narrowed to HImode.\n     Hoist the call to its own statement; put the load+subtract in a BLOCK-SCOPED s32 temp.\n T3. `andi $vN,0xffff` after a `jal` the target lacks => the TU declares that callee u16/s16-\n     returning. Do NOT change the decl \u2014 cast at the call (idiom 9 on the RETURN axis).\n T4. Unexplained `addu $vX,$aY,$zero` near a conditional branch (including in its DELAY SLOT,\n     consumed only by the fall-through arm) + the feeding `lh` loads out of order => the value is an\n     s16 LOCAL, not s32; LOAD_EXTEND_OP folded the widening extend into a plain move.\n T5. LENGTH-DRIFT +1 with a narrow load of the SAME stack slot => gcc narrowed a memory-operand\n     `local >> 16`. Bind the local to an s32 temp used twice.\n T6. A symbol read once at a constant offset but built into $s1 by lui/addiu => cache it in a\n     POINTER LOCAL. A direct D_xxx[k] folds %lo per use and shrinks the frame.\n T7. BRANCH POLARITY: if match_one prints BRANCH-POLARITY, invert the source condition \u2014 gcc-2.7.2\n     flips the branch to place the longer block as the fall-through. (Closed 8 mismatches in one\n     edit this wave; the index keys the literal string \"BRANCH-POLARITY\" straight to \u00a73-T4.)\n\nSCHEDULING:\n S1. The MEM_IN_STRUCT_P escape does NOT apply when the blocking store has a VARYING (register-base)\n     address \u2014 true_dependence() only drops the edge for a CONSTANT-address store. Then the lever is\n     SOURCE ORDER: assign the load to a temp ABOVE the stores. (But same-base `reg+const` addresses\n     ARE disambiguated by memrefs_conflict_p, so those hoists are free.)\n S2. An unfilled load-delay nop where the target fills it with a trailing call's arg setup => hoist a\n     LOAD: split `*p = *p + 1` into `v = *p + 1; ... *p = v;`.\n S3. NEVER pin an incoming PARAMETER \u2014 it turns the param's `move` into a schedulable body insn and\n     reshuffles the whole prologue. Pin loop variables only.\n S4. If no C lever moves a 3-6 instruction schedule/regalloc residual, a \u00a721 ZERO-BYTE RE-TIE\n     barrier can anchor it: `__asm__ __volatile__(\"\" : \"=r\"(v) : \"0\"(v));` between the loads and the\n     use. Try the source-level levers first; this closed one case after six other variants failed.\n\nDECLARATION SURFACE (decides whether a byte-correct draft BANKS):\n D1. `conflicting types` for a D_ symbol you cannot find declared in the split .c => the decl lives\n     inside a DEFINE_func_*() MACRO BODY in src/shared/engine_core.h. Reuse its canonical type.\n     An 8-byte-stride table declared `s32 D_x[][2]` must be indexed [i][0]/[i][1].\n D2. cc1 reports only the FIRST conflict. EVERY reconciled draft this session had a SECOND hidden\n     conflict, sometimes BELOW the splice point. grep the WHOLE TU in ONE pass for every symbol.\n D3. A DECLARATION CONFLICT ABORTS THE COMPILE, so it hides the byte question entirely. If you are\n     handed a draft as \"byte-correct, only declaration-blocked\", RUN match_one ON IT FIRST \u2014 two of\n     three such drafts this session also had a real codegen residual behind the conflict.\n D4. If you compile anything, use a PROCESS-UNIQUE scratch path. A shared one silently compiled\n     another agent's file and returned a meaningless success this session.\n\n\nx2-9 BAND. \u00a7136c sibling-first still applies but CHECK the twin EXISTS first (\u00a7136e) \u2014 if the whole\nfamily is in nonmatchings, go straight to the .s. \u00a7136j: sub-120-ins targets tend to fail on\nDECLARATIONS, 120+ on real codegen; do the whole-TU one-pass symbol grep (D2) either way.\nIf match_one reports REGALLOC-PERM (a clean 2-register swap), see \u00a7137: it is a TWO-COMPILE\nARITHMETIC problem \u2014 read R and L from `cc1 -dl -dg`, evaluate floor_log2(R)*R/L*1e4*size for both\ncontenders AND their ranked neighbours to get the admissible window, then place a zero-byte\n`__asm__ __volatile__(\"\" ::\"r\"(v))` so L lands inside it. Do NOT reach for the permuter first.\n"}
const T = Array.isArray(A) ? A : A.targets
const EXTRA = (Array.isArray(A) ? '' : A.extra) || ''
if (!Array.isArray(T)) throw new Error('args.targets must be an array')

const VERDICT = {
  type: 'object',
  additionalProperties: false,
  required: ['fn', 'status', 'summary'],
  properties: {
    fn: { type: 'string' },
    status: { type: 'string', enum: ['MATCH', 'DIFF', 'BLOCKED'] },
    closeness: { type: 'number', description: 'mismatching instructions remaining; 0 for MATCH' },
    klass: { type: 'string', description: 'residual class if not MATCH' },
    summary: { type: 'string', description: 'what you did and what the residual is, <=4 sentences' },
    levers: { type: 'string', description: 'cookbook sections / idioms that CLOSED the residual' },
    index_hit: { type: 'boolean' },
    index_gap: { type: 'string' },
  },
}

function prompt(t, escalated) {
  const asm = `${t.sub}/${t.fn}.s`
  return `You are matching ONE PS1 function to byte-identical gcc-2.7.2 output for the Brave Fencer
Musashi decompilation. Your ONLY deliverable is a C file at \`.run/s10/${t.ov}/${t.fn}.c\`.

TARGET
  function      ${t.fn}
  binary        ${t.ov}
  target asm    ${asm}          <- THE GROUND TRUTH. Read this FIRST and in full.
  TU it lands in ${t.tu}
  asm-subdir    ${t.sub}
  size          ${t.n} instructions
  leverage      family of ${t.m} members / ${t.ti} templatable instructions — a byte-match here
                propagates ${t.m}x across the fleet.
${t.seed ? `  ghidra seed   .run/ghidra_c/${t.fn}.c   <- A HINT ONLY. It is sometimes an ENTIRELY
                DIFFERENT body (byte-proven this phase). If it disagrees with the .s, THE .s WINS.` : `  ghidra seed   (none cached — work from the .s)`}
${t.retry ? `  ** RETRY **   A previous wave recorded: "${t.retry}". That is a data point, not a
                verdict. Re-derive from the .s; do not assume the earlier verdict was right.` : ''}

HOW TO WORK (this order is the measured-fastest)
1. \`docs/cookbook-index.md\` is a SYMPTOM-KEYED index of 364 byte-verified idioms. Grep it for your
   residual's symptom BEFORE deriving anything. Measured: index-first took a wave's bank rate from
   57% to 100%. Then read the section it names in \`docs/matching-cookbook.md\`.
   \`docs/gcc-2.7.2-map/{sched,regalloc,loop,cse_expr}.md\` is the compiler-source-derived map for
   scheduling / register-allocation residuals.
2. Read the target \`.s\` completely: frame size, callee-saved registers, jal targets, every
   \`%hi/%lo\` symbol.
3. Read the TU (${t.tu}) for EVERY symbol your draft will name. cc1 reports only the FIRST conflict,
   so a draft can look one edit from done and hold three more. grep the whole TU in ONE pass.
   Match its existing declarations EXACTLY; push any type disagreement to a CAST AT THE USE SITE
   rather than redeclaring the symbol.
4. Write the draft, then verify:
     .venv/bin/python tools/match_one.py ${t.fn} --c .run/s10/${t.ov}/${t.fn}.c --asm-subdir ${t.sub}
   Iterate until it prints MATCH; it names the exact mismatching instructions.

IDIOMS THAT CLOSED RESIDUALS IN THE LAST WAVES (cookbook §135 — all byte-verified)
 1. UNSIGNED switch index => pure equality chain, NO range test. No \`slti\` bound check in the
    target's switch means the index is u32, not s32.
 2. \`a0[0x46]\` (ARRAY_REF) sets MEM_IN_STRUCT_P and lets a load HOIST past a constant-address
    store; \`*(s16 *)((s32)a0 + 0x8C)\` (INDIRECT_REF) keeps the dependence. Many 4-instruction
    "scheduling residuals" are just this type-form choice.
 3. A constant store whose top bit is set in the STORED width needs an UNSIGNED destination:
    \`*(u16 *)p = 0x8C00\` emits \`ori\`; through \`s16\` it folds negative and emits \`addiu\`.
 4. The list scheduler PRESERVES the relative order of disambiguable stores. A store written late
    in source SINKS. If a store lands too late, move it EARLIER IN SOURCE (not a permuter job).
 5. A \`short\` loop counter blocks strength reduction; walking explicit pointers (\`p++\`)
    reproduces the original biv/giv set.
 6. Frame size off by a constant => DEAD LOCALS. If ALL diffs are \`sp\`-relative immediates off by
    one constant delta, add the padding declaration.
 7. An INTERIOR address has no symbol — a \`lui/addiu\` pair can build an offset INTO a symbol.
    Find the containing symbol in the data \`.s\` and index into it; declaring the interior address
    as its own extern link-fails.
 8. NEVER redeclare a C-library name (\`memcpy\` etc.).
 9. Loose typing is pervasive: if the TU declares \`void f(void)\` but the asm passes \`$a0\`, call
    through a cast — \`((void(*)(s32))f)(a0)\` — do NOT change the declaration.
${EXTRA ? `\nPROMOTED FROM THE PREVIOUS BATCH (fresh, byte-verified this session)\n${EXTRA}\n` : ''}
HARD RULES
 * Write ONLY \`.run/s10/${t.ov}/${t.fn}.c\`. NEVER edit \`src/\`, \`asm/\`, \`config/\`, \`include/\`,
   the Makefile, or any tracked file.
 * Do NOT run \`make\`, \`make build\`, \`make extract\`, or \`tools/harvest_verify.py\`. The
   whole-binary gate is the orchestrator's job and the sole arbiter of a match.
 * \`match_one\` MATCH is NECESSARY BUT NOT SUFFICIENT — it compiles standalone and cannot see the
   TU's other declarations. Step 3 is what makes a MATCH actually BANK.
 * Report honestly. A DIFF with a precise residual class routes the next attempt; a false MATCH
   just gets caught by the byte-gate and wastes a cycle.
 * ${escalated ? 'A cheaper rung of the model ladder already attempted this and did not reach MATCH. Read its draft at the path above, but re-derive from the .s rather than trusting it.' : 'Work economically — most functions this size close from the .s plus one or two index lookups.'}

Return the structured verdict.`
}

phase('Draft')

const results = await pipeline(
  T,
  (t) => agent(prompt(t, false), {
    label: `draft:${t.fn}(${t.n}i,x${t.m})`,
    phase: 'Draft',
    model: t.model,
    schema: VERDICT,
  }).then((v) => ({ t, v })),

  async ({ t, v }) => {
    if (!v) return { t, v: { fn: t.fn, status: 'BLOCKED', summary: 'agent returned no verdict' }, tier: t.model }
    if (v.status === 'MATCH' || t.model === 'opus') return { t, v, tier: t.model }
    // §136i ladder: haiku -> SONNET -> opus. Never haiku -> opus directly.
    const nextTier = t.model === 'haiku' ? 'sonnet' : 'opus'
    const v2 = await agent(prompt(t, true), {
      label: `escalate:${t.fn}`,
      phase: 'Escalate',
      model: nextTier,
      schema: VERDICT,
    })
    return { t, v: v2 && v2.status === 'MATCH' ? v2 : (v2 || v), tier: nextTier + '-escalated' }
  },
)

const ok = results.filter(Boolean)
const matched = ok.filter((r) => r.v && r.v.status === 'MATCH')
log(`wave4b: ${matched.length}/${T.length} claim MATCH (the gate is the arbiter)`)

return {
  claimed_match: matched.map((r) => r.t.fn),
  verdicts: ok.map((r) => ({
    fn: r.t.fn, ov: r.t.ov, nins: r.t.n, members: r.t.m, tier: r.tier,
    status: r.v ? r.v.status : 'NONE',
    closeness: r.v ? r.v.closeness : null,
    klass: r.v ? r.v.klass : null,
    levers: r.v ? r.v.levers : null,
    index_hit: r.v ? r.v.index_hit : null,
    index_gap: r.v ? r.v.index_gap : null,
    summary: r.v ? r.v.summary : null,
  })),
}
