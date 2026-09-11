# func_80181E98 — e7 (P36 T7 S104) — score 11 (sweep best 11) -> 0, ZERO levers (was: 1 NEEDED barrier)

(a) Residual: COUNT 124 vs 129. The second `|sxy[1]| < 0x8D` sign-split test: the target keeps two arms
(`bltz v0,NEG; nop; slti 141; beqz ret; move v0,zero; j pass` / `NEG: negu; slti 141; beqz ret; move v0,zero; pass:`),
the lever-free text merges them into a conditional negate (`bgez L; nop; negu; L: slti 141; beqz ret`), -5 insns.
The tree kept them apart with an empty `__asm__ __volatile__("")` before arm 1's `goto pass`.

(b) Pass/decision (dump-verified: `scratch/g2_greg.txt` = post-reload RTL entering jump2, vs `scratch/gt_jump2.txt`):
  Post-reload cross-jump (toplev.c:3142 `jump_optimize (insns, 1, 1, 0)`; the simplejump case jump.c:1971-1999,
  `find_cross_jump` jump.c:2371, minimum 1) compares the insns before arm 1's `j pass` with the insns before label
  `pass`. With `goto ret0` (one shared `return 0;` at the end) arm 2 falls straight into `pass`, both streams end
  `slt 141; beq ret0` and are merged (every goto spelling, and every if/else spelling, scored 11 in the enumeration).
  Written as ONE `if` with a ternary condition and an INLINE `return 0;`:
  `if (t >= 0x105 || (w.sxy[1] >= 0 ? w.sxy[1] >= 0x8D : -w.sxy[1] >= 0x8D)) return 0;`
  `do_jump`'s COND_EXPR case (expr.c:9124-9150) emits each arm as "branch to the if-false label (`pass`) / else
  drop through" and the `return 0` body (`v0 = 0; j return`) is laid out AFTER both arms, i.e. BETWEEN arm 2 and
  `pass` (g2: arm 1 = insns 173 slt / 174 `beq ->189` / 175 `j 200`; arm 2 = 182 neg / 184 slt / 185 `bne ->200`;
  189: `v0 = 0; j 248`; 200: pass). The insn before label `pass` is now the return block's `j 248`, not a
  condjump, so `find_cross_jump` fails on its first comparison (jump.c:2469-2470) and the arms stay apart. Reorg then
  steals `move v0,zero` into each branch's delay slot and inverts arm 2's branch over the return jump — the target's
  `beqz ret; move v0,zero` in both arms.

(c) Moves (joint; found by enumerating 52 structural spellings, `scratch/gen.py` -> `scratch/enum/`):
  - every `goto ret0;` -> an inline `return 0;` (the `ret0:` label deleted);
  - the second sign-split test -> one condition with a ternary per sign (S104 d11's shape);
  - (readability, byte-neutral) the whole goto chain -> structured: `if (t >= 0xAB || (<0x83 ternary>)) { second
    projection …; if (flag) return 0; if (t >= 0x105 || (<0x8D ternary>)) return 0; }` then the pass code.
  Scores: all 4 variants with inline `return 0` + the 0x8D ternary = 0 (goto/structured first test, `t` by if or
  ternary); inline `return 0` with any if/else sign split = 11; `goto ret0` with the ternary = 11; `||`/`&&`-split
  sign test = 17/18. body.c = `scratch/g2.c` (0).

(d) GENERATOR PROPOSAL: when a `barrier` lever sits in one arm of a sign-split range test
(`if (v >= 0) { if (v >= K) goto FAIL; …goto OK; } else { if (-v >= K) goto FAIL; }`) and FAIL is a shared
`return C;` label, rewrite the test as `if (v >= 0 ? v >= K : -v >= K) return C;` with the return INLINE — do_jump
places the return body between the second arm and OK, which cross-jump cannot match (extends S104 d11: the inline
return, not just the ternary, is what closes it here).

(e) Did not work: 48 of the 52 enumerated spellings (listed above by class); f1/f2 (ternary with `goto ret0`) 11/17.
The sweep's R7/R8 moves all 11 (none changes the return placement or the goto chain).

(f) Method: METHOD S104 (d11) named the ternary but not the inline return; the enumeration (d14's lesson, 52 bodies in
under a minute with `xargs -P6` over `--try`) found the joint move, the post-reload RTL (`.greg`) explained it.

(g) Structs: no. The decision is block layout + cross-jump pattern matching; the local `w` is already a struct.
Also noted: the TU's `func_80181E98_impl … __asm__("func_80181E98")` asm-label reconcile (a stale `void` forward
declaration elsewhere in the TU) is untouched — it is a declaration alias, not a lever; fixing the TU's `extern void
func_80181E98(u8 *a0);` to `s32 (void *)` would let the body use its real name (parked, TU-wide change).
