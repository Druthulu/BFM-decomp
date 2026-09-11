# func_80180324 (ov_SC04_007) — agent d20, P36 T7 S104

**Result: `--try` score 0 (328/328), on this function AND all ten other members of its family (table:
`scratch/copies/TABLE.md`).** No register pin, no `asm` of any kind, no `volatile` added (the loop-2
`*(volatile s32 *)` cast was already in body_free.c and is still needed: without it 7, see (e)).

**It is NOT a lever-free close, and I do not claim one.** The body keeps two `if (tpage & 0x200) su = e;`
statements. `tpage` never has bit 9 set, so each test is always false: an invented identically-zero
condition, which step 6 refuses. Both are marked `// !FAKE: dead-branch` as the step-9 minimum-lever body.
Lever count 8 → 2 (tree: 1 `$0` pin + 6 asm keepalives + the pre-existing volatile cast; now: 2
C-level dead branches + the same volatile cast; 0 pins, 0 asm).
Drew's ruling needed: is a C-level dead branch that reproduces a real late-dead branch in the original an
acceptable marked lever, or should it go back to asm keepalives?

## (a) The residual
The lever-free text is 10 instructions short (318 vs 328):
- the target computes `t + spr[2] - 1` and `sv + spr[3] - 1` (lbu/addu/addiu each, the second with its
  load-delay nop) and never reads either;
- it keeps `move s3,a0` (su := t) in the lbu delay slot, and the chain reads `a0` (t), not `s3`;
- it keeps the sv if/else as `beqz; j; addiu s2,a1,-256 | move s2,a1`, where the free text gets
  if-converted;
- in the loop, the counter `i` / the 0xFFFFFF mask / the vtx+4 giv are permuted over t3/t4/t5, and
  sv/uu/vv/0xFF000000 are permuted over a1/s0/s1/s2.

## (b) Mechanism: passes and decisions (every claim here tested on bytes unless it says otherwise)
1. **Dead code survives only if its consumer disappears AFTER flow.** flow's final pass deletes dead sets
   (`flow.c:1478-1490`), and nothing re-runs flow later. combine (after flow) folds a test on a pseudo whose
   `nonzero_bits` (`combine.c:6803`, `simplify_comparison` `:8716`) prove it constant. That turns the
   conditional jump into `(set (pc) (label_ref))` (`combine.c:2353`; seen in `.combine`: jump_insn 164).
   jump2 (`toplev.c:3142`, after sched2) then deletes the unreachable arm. The chain that fed only that arm
   stays as dead code, byte-exact. Micro-reproduced (`scratch/micro/t3.c`) and on the real function.
   This REFUTES the family exemplar's note 1 (ov_SC02_028 `func_801833F0` header, "gcc-2.7.2 deletes any
   pure-C spelling").
2. **The copy must follow the chain's read of t in sched1's order, in the same block.** If the copy comes
   first and t does not die in it, local-alloc's `optimize_reg_copy_1` (`local-alloc.c:700`) rewrites the
   chain to read su. Every separate-temp variant read `s3`/`s2`. The copy is placed last only if it wins
   sched1's tie:
   - `adjust_priority` boosts a "birthing" insn (`sched.c:2469`, `:2539`: dest set once and live after).
     With a fresh `ue`, the chain's final addiu is birthing and wins, and the copy lands above it.
   - Declaring ONE variable `e` for both edges (two live sets) un-boosts it. The tie then goes to
     `INSN_LUID` (`sched.c:2428`), so the copy, textually later, is scheduled last.
   - t then dies in the copy. `combine_regs` refuses to tie it to the global su (`local-alloc.c:1774`), so
     `move s3,a0` survives. sched2 moves it into the lbu delay slot.
3. **sv if/else kept as j+else.** jump.c's `if (...) x = a; else x = b` → `x = b; if (...) x = a` rewrite
   (`jump.c:699`) needs a ONE-insn then-arm (`jump.c:748-749`). Writing the then-arm as
   `y -= 0x100; sv = y;` gives two insns in every pre-flow jump pass. cse's `(set REG0 REG1)` swap
   (`cse.c:7440`) plus flow then fold it back to one `addiu s2,a1,-256`.
4. **Loop permutation t3/t4/t5.** `allocno_compare` (`global.c:587-600`) ranks by `floor_log2(refs)·refs/live`.
   `i` (9/114 → 2368) ranked below the hoisted 0xFFFFFF (13/111 → 3513). Using `i` as the second loop's
   counter too (the target has i and m in the SAME `$t3`, so they are one variable) gives 16/152 → 4210.
   i is then allocated first and takes t3. This also puts vtx (8/184 → 1304) back below the k2 giv
   (1320.8), so the tree's vtx keepalive becomes unnecessary.
5. **a1/s0/s1/s2 permutation.** A v dead arm written as `sv = e` gives sv 8 refs → 1764, so sv takes a1
   before vv. Writing the v arm into `su` instead gives sv 7/135 → 1037. That drops sv below vv (1250),
   uu (1238.9) and the 0xFF000000 constant (1238.5), which is the target's order: vv=a1, uu=s0, const=s1,
   sv=s2, su=s3.

## (c) The moves (from body_free.c, 43)
- one `s32 e` holds both edge values: `e = t + w - 1; su = t; if (C) su = e;` and, after the tpage
  if/else, `e = sv + h - 1; if (C) su = e;` (C = `tpage & 0x200`, always false). 43 → 32.
- loop 2's counter `m` replaced by `i` (declaration of `m` deleted). 32 → 18.
- the v dead arm writes `su`, not `sv`. 18 → 1.
- then-arm `y -= 0x100; sv = y;` (else `sv = y;`, the `(u16)` cast gone). 1 → 0.
- conditions that also give 0: any pair drawn from {`tp & 4`, `tpage & 0x200`, `tpage & 0x400`,
  `tpage & 0x1000`} (13 of 256 pairs scored 0; `scratch/c2search.py`).

## (d) Generator proposals
- **G-a (natural, broad):** when a tree has `x = y + zr` (a `$0`-pin copy) in an else-arm whose then-arm is
  `x = y OP K`, rewrite the then-arm as `y OP= K; x = y;` and the else as `x = y`. The two-insn arm blocks
  jump.c:748's if-conversion; cse.c:7440 and flow fold it back to one insn.
- **G-b (natural):** when a tree keeps `asm("" :: "r"(i))` density reads on a loop counter, and a LATER
  loop's counter lands in the same hard register in the target, merge the two counters into one variable
  (refs and live length add; global.c:595).
- **G-c (lever-to-lever, marked):** when a tree keeps `asm("" :: "r"(expr))` for a value the target
  computes and never reads, replace it with `if (<test combine proves false>) X = expr;`. X is a variable
  set on the live path and live afterwards; enumerate X, and enumerate the test over bits a live pseudo
  provably lacks. Same lever count, but it moves the lever from asm to C and lets the other levers go.

## (e) What did not work (byte evidence)
- A fresh `ue`/`ve` per edge: the chain reads s3 (optimize_reg_copy_1), 60-87.
- `su = C ? e : t` with C always true (`if (!C) su = t; else su = e;`): combine leaves
  `move v0,zero; bnez v0`, 60.
- The same test on `fl` twice: cse shares the and-result and combine cannot fold both jumps (`move v1,zero`).
  Tests on `fl` also add refs to fl and change which pseudos spill.
- The v arm writing `sv`/`vv`/`uu`/`y`, or a su/sv swap: 29-38.
- `i = 1` before the dead branch with the branch holding the copies: a loop-entry test appears
  (slti/beqz), 96-141.
- sv else-arm `(u16)y`, `(u32)(u16)y`, `y & 0xFFFF`: blocks the if-conversion but leaves
  `andi s2,a1,0xffff`, 1. combine only simplifies inside a LOG_LINK pair, and the else block has one insn.
  A fresh masked `yy` reshuffles the whole allocation (109-126). Ternary / `y -= ((c) ? 0x100 : 0)`: 29.
  Inverted test, `== 0` test or switch: the arms swap, 3.
- Dropping the loop-2 volatile, or spelling that read as `((s32 *)q)[13]` + `q++`, a struct field, a local
  `z` pointer, `ot + …`, or indexing by the counter: 5-7. loop.c eliminates the q biv.

## (f) Where the method fell short
- Neither the method nor the cookbook explains how a dead value can survive, and the exemplar header said
  it cannot. The "DEAD CODE IS REAL" keepalive is a reproducible pass sequence (flow → combine fold →
  jump2), testable in a 10-line micro. A `.combine` grep for `(set (pc) (label_ref` would have shown it.
- The allocation table misled until I matched pseudo numbers to variables by hand (declaration order).
  The tool should print variable names.
- `pkill -f` killed my own shell once (the memory note is right). The coordinator's regen fleet was running
  (40 `--try` processes), so compiles took ~2 s each.

## (g) Structs
Struct typing does not plausibly change what keeps the two dead-branch levers. They exist because the
target contains unread arithmetic, and only a consumer removed after flow (or an asm use) produces that.
Tested: a UV pair as a local struct goes to the stack (stores kept); as a union it vanishes but leaves an
orphan 48-byte frame (`scratch/micro/t4.c`). Neither is the target shape.

For the pre-existing loop-2 volatile, a body-local `struct { u32 a[13]; s32 z; } *` field read scores 7,
the same as the plain read: loop.c's biv elimination does not look at MEM_IN_STRUCT_P, so a struct is not
the missing piece there either.

The one struct question left open: the original likely had real flip/UV-edge code (a sprite RECT struct
or flag field) whose test the compiler could prove false. Finding that field in the entity or sprite
layout would turn the invented `tpage & 0x200` into the original's test.
