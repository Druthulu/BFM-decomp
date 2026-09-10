# func_8017B614 (ov_SC04_011) — T7 agent c30 (S103 re-draw)

**Result: score 0, lever-free.** No register pin, no asm, no added volatile, no do-while, no invented term. Whole-object check
on the `--try --keep` object: the objdump of the ENTIRE `.o` (every function, relocations included) is identical to
`.run/P36/delever/baseline/src/ov_SC04_011/ov_SC04_011_jr_8017AE2C.o`, and `.text` compares equal byte-for-byte (`cmp`).
The earlier S102 reading (score 6, with a `do { } while (0)` used as a sched1 barrier) is in `scratch/prev_body.c` and
`scratch/prev_mechanism.md`. Every candidate and its disassembly is in `scratch/c30/` (`a1.c` … `c7.c`, `*.dis`, `dumps_*`).

## (a) The residual in one sentence

Two separate residuals: (1) `param_2` was kept in `$s0` for the whole function (the target compares `$a1` and copies
`$a1 -> $s0` at the top of the block-move arm), and (2) the `li 1; sh D_801F1638` pair came out above the six `lh` loads
where the target has it below them.

## (b) The passes and the decisions (source `file:line`, and what the bytes proved)

### Residual 1: `s0 -> a1` on `param_2`. This is cse's choice of canonical register (cse.c:850-858), then global preferences.

* Lever-free text: the then-arm pointer is block-local (`u8 *src = param_2;`). `make_regs_eqv` (cse.c:850-858) makes a
  new pseudo the class's canonical register only if it lives past the current basic block. A block-local `src` does
  not, so `param_2` stays canonical, the movstr addresses are rewritten to `param_2`, and the copy is deleted. That
  leaves `param_2` live across both `movstrsi_internal` insns, which conflict with the `$v0-$a1` scratch clobbers, so
  it lands in `$s0` (dump: `73 conflicts: … 2 3 4 5`, `73 preferences: 16`).
* The matched sibling **func_8017B238** (same TU, same head, lever-free, banked) spells it with ONE function-scope
  `u8 *src` that is assigned in BOTH arms (`src = param_2` in the copy arm, `src = &D_80193D6C[param_2*16]` in the
  call arm). That `src` lives past the then-arm block, so cse makes it canonical and the copy `src = param_2` survives.
  `param_2` dies at the copy and no longer conflicts with `$a1`. In global.c, `expand_preferences` (global.c:781-821,
  called at :523) merges `param_2`'s preferences into `src` across the dying-source copy. Dump of the final body:
  `74 preferences: 16` goes to `74 in 16` (src = `$s0`), and `73 preferences: 5 16` goes to `73 in 5` (param_2 = `$a1`).
  In the call arm, combine folds `src = off + D` into the first call's argument, so that arm's instructions are the
  same as with two temporaries. Local-alloc's tie still puts the offset in `$s0` (the S102 agent's all-in-one `src`
  rewrite broke exactly this and cost 6).
* Proven on bytes: `scratch/c30/a1.c` (the lever-free body plus B238's arm shape, nothing else) scores **6**. Every
  register is correct and only residual 2 is left.

### Residual 2: the `li 1; sh D_801F1638` placement. Caused by sched1, but FIXED in sched2's memory-dependence test.

* sched1 (sched.c, backward list scheduling): each load becomes ready once its `sw` is scheduled. `adjust_priority` →
  `birthing_insn_p` (sched.c:2469-2499, :2539-2545) raises it to LAUNCH_PRIORITY (0x7f000001). The `sh` stores keep
  priority 1. After `sh 30`/`li 30` are placed, the loads beat `sh 1` and sched1 emits `sb; li 1; sh 1; loads; li 30;
  sh 30`. That happens in EVERY spelling, including the final one: the `.sched` order of the matching body is still
  `105:sb 108:li 110:sh1 122..159:loads 113:li 115:sh30`.
* sched2 (after reload) re-sorts only if the loads do not depend on `sh 1`. Once the pointer is a hard register,
  `(mem (reg s0))` can no longer be told apart from `(mem (symbol D_801F1638))` via `reg_known_value`. The test that
  CAN still separate them is the MEM_IN_STRUCT_P rule in `true_dependence` / `anti_dependence` (sched.c:817-835). A
  struct access at a varying, non-QImode address never conflicts with a non-struct access at a fixed address.
  * The two register-based loads (`lh v1,0(s0)` / `lh a2,0(s1)`), spelled as struct members
    (`((SV4_8017B368 *)&D_801EECD4)->a`), are `mem/s` (expr.c:4888, COMPONENT_REF). They then do not depend on the
    scalar `sh 1`. sched2 sinks it below the loads through `schedule_select`'s "greater potential hazard" pick
    (sched.c:2660-2690). This is exactly what the matched sibling **func_8017B490** does (same tail, lever-free, the
    same `.a` spelling, and its own sched1/sched2 dumps show the same hoist-then-resort).
  * That also frees the scalar `sb zero,D_8012694C`, which sinks too (b1.c = 4: it lands between `li 30` and `sh 30`).
    The store must stay ABOVE the struct loads, so it must itself be a struct access at a fixed address. Then neither
    exemption applies, `memrefs_conflict_p` cannot separate `(symbol D_8012694C)` from `(reg s0)`, and the loads keep a
    true dependence on it. `extern u8 D_8012694C[]; D_8012694C[0] = 0;` is an ARRAY_REF that goes through the
    COMPONENT_REF path, so it gets MEM_IN_STRUCT_P = 1 (expr.c:4888). It keeps the relocation symbol `D_8012694C` the
    scorer compares (`masked_word` includes `reloc_op`).
  * Evidence the original was an aggregate store: `D_8012694C` is `D_80126948 + 4`, and `D_80126948` is the camera
    object that the engine passes by address (`func_8012A094((s32)D_80126948)`, `func_8012A048(D_80126948, …)`,
    `u8 *cam = D_80126948; *(s32 *)(cam + 0x50)`). The six `s32` targets `D_80126984..D_80126998` are its fields
    +0x3C..+0x50. The original wrote a member of that struct. The `[0]` spelling is the closest form that keeps the
    project's symbol (writing `D_80126948[4]` would change the relocation operand to `D_80126948+4`).
* Final `.sched2` order (proven): `sb/s; load/s; ECD6; ECD8; load/s; ECCE; ECD0; li 1; sh 1; li 30; sh 30; six sw`,
  which is the target order.

## (c) The source moves that closed it

1. **One function-scope `u8 *src` assigned in both arms** (func_8017B238's banked spelling, byte for byte):
   13 → 6 (a1.c).
2. **Register-based tail loads as struct-member reads:** `D_80126990 = ((SV4_8017B368 *)&D_801EECD4)->a;` and the
   same for `D_801EECCC` (func_8017B490's banked spelling). Alone on top of 1: 6 → 4 (b1.c).
3. **The camera-field store as an aggregate element:** `extern u8 D_8012694C[]; D_8012694C[0] = 0;`. Alone on top of 1:
   still 6 (c2.c). On top of 1+2: **0** (b2.c). This is a joint close. Neither 2 nor 3 moves the score alone to where
   the pair lands.
4. Readability, all still 0: the `s16 *p794/p78C` locals and the six `v…` temporaries dropped (cse recreates the
   pointer registers by itself, c5.c). The tail is written in func_8017B490's order (`D_801F1638 = 1;
   D_801EEC5C = 0x1E;` before the reads, c3.c/c4.c). The call through a cast replaced by the plain
   `func_8012A018((s32)func_8017BE60, 0);` (c7.c = `body.c`).

## (d) GENERATOR PROPOSALS

* **ORDER, scalar constant store hoisted above loads through a pointer register:** rewrite those register-based loads
  as struct-member reads of the pointee (`((T *)&SYM)->field`, T an existing struct type of the right size) so sched2
  may sink the store (sched.c:817-835). Then, for any scalar fixed-address store that the target keeps ABOVE those
  loads, re-declare it as an aggregate element (`extern u8 X[]; X[0] = v;`) so it keeps its dependence. Score the two
  moves JOINTLY: alone they read 4 and 6.
* **REG, a parameter in `$sN` where the target compares `$aN` and copies to `$sN` in one arm** (block moves, scratch
  clobbers): hoist that arm's pointer to function scope and also assign it in the sibling arm, to the value that arm
  already computes first. The longer-lived pseudo becomes cse's canonical register (cse.c:850-858), so the copy
  survives and global's `expand_preferences` (global.c:781) hands it `$sN`.
* **Method rule:** before any sched1 barrier, diff the `.sched` order against the `.sched2` order of the SAME
  function, plus a matched sibling's pair. If the sibling's sched1 shows the same "wrong" order and its sched2 repairs
  it, the fix is a dependence flag (MEM_IN_STRUCT_P / alias), not a barrier.

## (e) What did not work, or only partly (byte evidence)

* a1.c (arm shape only): 6. The sched residual is unchanged: sched1 hoists `sh 1`, and sched2 cannot repair it because
  the `0(s0)` load conflicts with the scalar `sh`.
* b1.c (a1 + struct-member loads): 4. `sh 1` is correct, but the scalar `sb` is now also free and sinks between
  `li 30` and `sh 30`.
* c2.c (a1 + aggregate `sb` only): 6. It changes nothing on its own.
* The earlier S102 body (all-in-one `src`, including the call arm's offset): 6 on the call arm's schedule. Its
  `do { } while (0)` around the loads was a sched1 LOOP-note barrier. That is not the permitted reference-weight form
  and is no longer needed.

## (f) Where the method fell short

* **The attribution control was only half right.** S102's `-fno-schedule-insns` control proved that sched1 CREATES
  the misorder. It did not show that sched2 is where the target REPAIRS it, which the matched sibling func_8017B490
  does in its own dumps. Printing the `.sched` and `.sched2` insn orders side by side (a 20-line script,
  `scratch/c30` shows the shape) would have made this a first-hour read. Recommend it for every ORDER residual.
* **`related.txt` held both answers:** func_8017B238 for residual 1 (verbatim) and func_8017B490 for residual 2 (the
  `.a` member reads). The first `--try` of B238's arm shape settled residual 1 in one compile. Reading the matched
  siblings' BODIES (METHOD_S103 §3, c10/c2/c4) was the whole crack again. Reading them against a pass dump of the
  sibling (not only its text) was the new step.
* **Tool drift mid-run:** `delever_search.py --try` switched to per-pid scratch directories plus `--keep` while this
  agent ran. The old shared `cand.o` path stayed on disk, and my first disassembly read it (a stale object from an
  earlier compile). `scratch/c30/t.sh` now uses `--keep` and deletes the per-pid directory after dumping.
