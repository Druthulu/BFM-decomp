# func_80188A30 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e17)

**Result: score 0 in plain C with a SIGNATURE change — PARKED.** The return type is `s32` instead of `void`, the body is the
lever-free `body_free.c` unchanged, and the function falls off the end (no `return` statement, like a K&R implicit-int
function). No pin, no asm, no added volatile. Levers go from 1 to 0 (the `"memory"` barrier at tree line 11065).
It needs the TU's later prototype changed too: line 13461 `extern void func_80188A30(s32 a0);` becomes
`extern s32 func_80188A30(s32 a0);`. The whole-TU candidate is `scratch/tu_ret.c` (scored WITHOUT `--body`: 0). Its only
caller, `func_8018C260` (line 13485, ignores the result), is also byte-identical under the new prototype (0).
`body.c` alone does NOT compile with `--body` (the unchanged `extern void` conflicts); score it with the whole TU.

## (a) The residual in one sentence
One instruction missing (36 vs 37). The target leaves the delay slot of `beqz v0,<epilogue>` (the call-result test)
EMPTY (`nop`). Mine fills it with `li v0,24`, the first insn of the fall-through arm (`D_80126B98 = 0x18`).

## (b) The pass and the decision (source read; proven on bytes)
reorg, `fill_eager_delay_slots` → `fill_slots_from_thread` (`reorg.c:3270-3380`). For a conditional branch it steals from
the fall-through thread only an insn that does not set anything live on the OPPOSITE thread (`reorg.c:3375`,
`! insn_sets_resource_p (trial, &opposite_needed, 1)`). The opposite thread is the jump target, the function end, so
`opposite_needed` comes from `mark_target_live_regs` (`:3293`), which returns `end_of_function_needs` there (`:2458`).
`init_resource_info` seeds that set with the return-value register when `current_function_return_rtx` is a REG
(`reorg.c:4274-4277`). In a `void` function it is not, `$v0` is dead at the epilogue, and `li v0,24` is stolen. In an
`s32` function `$v0` is live at the epilogue, `li v0,24` sets it, the steal is refused, and the slot stays `nop`.
This is cookbook §162f1 ("a non-void return type is observable in delay slots") exactly: `li v1,1` in the second
epilogue-bound `bnez` slot is still filled in both, because it does not set `$v0`.

## (c) The move that closed it
`void func_80188A30(s32 a0)` → `s32 func_80188A30(s32 a0)` (and the extern at 13461). Nothing else. The function emits no
extra instruction: no path gains a `move v0,…`.

## (d) Generator proposal
When the only residual is an EMPTY delay slot (`nop`) on a branch to the epilogue where mine fills it with an insn that
sets `$v0`, flip the function's return type from `void` to `s32` (and its prototypes in the TU); if a caller uses no result
the callers' bytes do not change (§162f1). This is a signature change, so the generator should emit it as a parked
candidate with the prototype edits listed.

## (e) What did NOT work
- The sweep (R7 blocks, R9 swaps, R10 param copy, R18 bystanders): 2 on every move; no generator touches the return type.
- I know of no plain-C `void` spelling that reaches this (reasoned, not enumerated): in a void function `$v0` is not live at the end
  (`current_function_return_rtx == 0`), and the fall-through's first insn is the constant load in every order the target
  allows (the target's order is `li v0,24; lui at; sh`, the same as mine). The fallback, if the signature change is refused,
  is the tree's body (1 marked barrier lever, the minimum).

## (f) Where the method fell short
Nothing blocked. Reading the whole objdump (METHOD step 1) showed the missing insn is a `nop` in a slot mine fills with a
`$v0` write before an epilogue branch. That shape is already in the cookbook (§162f1, found by grepping
`end_of_function_needs`), but neither PROMPT nor METHOD lists "empty slot before the epilogue → return type". Add it to
METHOD step 3's list of what emits a missing instruction.

## (g) Structs question
No. The decision is reorg's liveness at the function end, set by the return type. No memory access is involved. (`a0` is an
actor; `+0x106` is an s16 "already triggered" flag, and a struct would not change this.)

Files: `body.c` (the `s32` definition), `scratch/tu_ret.c` (whole TU with the prototype changed: 0 for `func_80188A30` and
for its caller `func_8018C260`), `scratch/free.o` (the free body's object, 36 ins).
