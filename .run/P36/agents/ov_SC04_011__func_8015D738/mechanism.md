# func_8015D738 (ov_SC04_011_jr_8015C32C.c) — T7 agent c5

**Result: score 0 (201/201, byte-identical by `--try`), barrier lever gone, no pin, no asm, no volatile, no zero term.**
`PACK/body.c` is the close. It carries ONE `do { … } while (0);` around a real statement (the first read of `arg0->0x178`).
Please read "Verdict on the do-while" below before banking: whether that counts as a close is your call.

## (a) The residual

COUNTED first. The lever-free text is 4 instructions SHORT (197 vs 201), not a register problem: both `s1 != 0` tests collapse.
The first `beqz s1` is retargeted past the second test, straight to the call block, and the second `lhu 0(s1)` is gone
(`a1` reused). The target keeps both: the first `beqz s1` lands ON the second `beqz s1` (0x1470), and the second test reloads
`lhu v0,0(s1)`.

## (b) The pass and the decision (source read, then proved on bytes)

- **thread_jumps** (`jump.c:4161`) runs twice: `toplev.c:2863` before cse1 and `toplev.c:2935` after cse2. It retargets b1
  when b1 and b2 test `rtx_equal_for_thread_p` operands. REG case (`jump.c:4383-4410`): same regno and not written between
  the label and b2 means equal. A different regno where either side is a user variable means NOT equal, and so does a
  regno written in between (`mark_modified_reg`, `jump.c:4135`). The walk back from b2 (`jump.c:4270-4300`) also has to reach
  b1's label through pattern-equal insns, so any differing insn in between stops the thread.
  **Oracle (cookbook §353), 1 compile:** `body_free.c` with `-fno-thread-jumps` gives exactly the target's shape here. The
  whole residual is thread_jumps. (PROVED)
- **cse1 vs cse2.** `cse_end_of_basic_block` (`cse.c:8008`) takes b1 AROUND the lhu block into the second test's label
  when that label has one use (`cse.c:8110-8175`). The `arg0->0x178` value comes along; the skipped block's lhu result is
  invalidated. `cse.c:8054` (`if (! after_loop && NOTE_INSN_LOOP_END) break;`) ends cse1's path at a LOOP_END note, and
  cse2 (`after_loop=1`, `toplev.c:2926`) walks straight through it. `delete_dead_from_cse` (`cse.c:8684`) runs after cse1
  ONLY (`toplev.c:2867`), so nothing deletes a copy that cse2 turns dead or no-op before thread #2. Flow does that later. (PROVED
  on dumps, `scratch/dumps_t3`, `scratch/dumps_t8`.)

## (c) The moves (each proved with `--try`)

1. **17 → 1: re-read the pointer before the second test.** `s1 = *(s32 *)(arg0 + 0x178);` (or the expression itself,
   a fresh block-local, a ternary, a switch: v1/w2/b1/b2/b4/b5/c2/c4 all score 1). Thread #1 stops firing because b2 now
   tests a fresh pseudo, or a written one. The second lhu comes back (201 = 201). But cse1, on the AROUND path, folds the
   re-read into `s1`, `delete_dead_from_cse` removes the leftover, and thread #2 still threads b1 (the one remaining diff,
   `beqz s1,1488` vs `1470`).
2. **1 → 0: wrap the FIRST read in `do { … } while (0);`.** The LOOP_END note ends cse1's path before b1, so cse1 never
   sees the re-read as redundant and leaves the real load (`.cse`: `(set (reg/v 74) (mem (plus 72 376)))` at the label).
   cse2 walks through the note and rewrites it to the no-op `(set (reg/v 74) (reg/v 74))` (`.cse2`). Nothing deletes that
   before thread #2, which sees reg 74 written between the label and b2 and refuses. Flow then deletes the no-op
   (`.flow`: NOTE_INSN_DELETED). Result: one `lw`, both tests, the second lhu, and the register assignment unchanged.
   `goto block_7F4` also goes: the second test is written as `if (s1 == 0 || *(u16 *)s1 == 0) { …; return; }`.

## Verdict on the do-while (read before banking)

`scratch/t3.c` puts an EMPTY `do { } while (0);` right after the load, and it is ALSO byte-identical. So the construct's only
effect here is a cse1-only barrier: a LOOP_END note, the same job the `asm volatile("")` did by other means. `body.c`
(t8) wraps a real statement (the load it guards), which is the shape project precedent banks. It is rung-R recipe R7
(`do { stmt; } while (0);`), cookbook §158a, and the S102 a4/b8 closes, and levers.md classes A–G do not count it. I do
not claim it is what the original author wrote. If the phase rules that a do-while whose whole effect is a barrier is a
lever (METHOD refusal 6, "dummy dependency"), then the honest lever-free result is **score 1**: `scratch/v1.c`/`scratch/w2.c`,
one branch target off, with the mechanism above. A disabled debug macro that expands to `do { } while (0)` right after the
load is one plausible original, but it is not evidence.

## (d) Generator proposal

When the target has two back-to-back identical tests of one local (the first branch lands ON the second test, and the
second test re-derives what the first already loaded) and the lever-free body is short by the second test's instructions,
do this. Re-read the local from memory right before the second test. If that scores exactly one branch target off (thread
#2 still fires), also wrap the local's FIRST assignment in `do { … } while (0);`. Check first with one `-fno-thread-jumps`
compile: if the residual vanishes, this is the family.

## (e) Tried, did not work (bytes)

- w1, two variables (`t` for the first test, `s1` re-read for the second): the thread is blocked, but `t` gets `a1` and
  `move s1,a1` survives (14). global.c propagates only hard-reg preferences. A pseudo-to-pseudo copy is not a preference
  unless one side already has a hard reg (`expand_preferences` `global.c:781`, `set_preference` `:1535`).
- w3, an unused label before the second test: jump deletes it (17).
- t1, `do-while(0)` around the FIRST TEST: the if's exit jump is threaded to the loop-exit label, and the AROUND path skips
  the note. Still threaded, plus an s0/s1 swap from loop-depth ref weighting (56).
- t4, `do-while(0)` around the whole prologue: 6 (ORDER; loop weighting).
- t6, plain block `{ s1 = load; }`: 1 (BLOCK notes do not stop cse).
- t9, the A body written out in place instead of `goto block_808`: count right, but the two extra `arg0` refs swap s0/s1 (56).
- c1/c3, re-reading in BOTH tests: 87. b6/b7, a ternary on `s1`: 17.

## (f) Where the method fell short

- The residual printout read as a register residual (`a1->v1`) plus branch targets. Only counting (197 vs 201) and
  the whole-function objdump showed a missing TEST. METHOD step 2 is right, and it should come before the register-pair line.
- `residual_moves.md` has no thread_jumps row. The cheapest diagnosis was cookbook §353's `-fno-thread-jumps` oracle:
  one compile named the pass. It belongs in METHOD step 3's list ("a missing re-test = run the per-pass disable flag first").
- The pack's `scratch/score.sh` (left by an earlier run) cd's before resolving a relative path, so every call died with a
  traceback. My `scratch/sc.sh` resolves the path first.
- `delever_search`'s moves (R7 block / do-while at @2003, @1972, @1960, @1949) never put a do-while on the LOAD (@1952), and
  never paired it with a re-read. This close is a JOINT edit: the re-read alone gives 1, and the do-while alone gives 17
  (scratch/t10.c, PROVED), because thread #1 already fires before cse1.
