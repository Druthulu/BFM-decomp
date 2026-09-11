# func_800359B0 (src/800_c.c) — P36 S104 agent e21 — score 18 -> 0, ZERO levers (the §336 barrier removed), no goto

## (a) The residual
COUNT 165 vs 167: case 16's `func_800434BC(); goto do_flag;` loses its own `jal func_800434BC` — its `>= 301` branch jumps
into case 9's call instead (`beqz v0,89c`) — and every later branch target shifts by 8 bytes. The target keeps both calls,
each followed by `j 8d0; li v0,1`, where 8d0 is the `D_80076214 = 1` store it shares with the `sync == 5` path.

## (b) The pass decision (dump-proven, `scratch/dumps_free/` vs `scratch/dumps_f5/`, `.greg` = before jump2, `.jump2` after)
- Post-reload cross-jump (`jump_optimize (insns, 1, 1, 0)`, toplev.c:3142). In the tree text case 9's call (insn 195)
  FALLS THROUGH into `code_label 196 "do_flag"`; case 16 is `call 386; jump 196`. For an unconditional jump, jump.c:1978
  first runs `find_cross_jump (insn, JUMP_LABEL (insn), 1, …)` against the insns falling into the label, with
  MINIMUM 1, so one matching call is enough. `do_cross_jump` deletes call 386. `.greg` has 5 `func_800434BC` calls, and
  `.jump2` has 4.
- Closing text: each arm spells out its own tail `func_800434BC(); D_80076214 = 1; *(u8 *)(arg0 + 2) = 0;`. jump2 first
  cross-jumps the store TAILS onto the `sync == 5` path's copy and creates `code_label 463` in front of it (`.jump2` line
  610; the highest uid in `.greg` is 455). Both calls are now `call; jump 463`. The "try each other jump to this label"
  loop is guarded by `INSN_UID (JUMP_LABEL (insn)) < max_uid` (jump.c:1984), and a label created during this pass never
  passes that guard. The fallthrough into 463 is the `andi`/`beqz` of the `sync == 5` test, not a call, so it matches
  nothing. Both calls survive, which is the target's `jal; nop; j 8d0; li v0,1` twice. reorg then fills the `li v0,1`
  slots from the jump target.
  `.jump2` has 5 calls. Bytes: `--try` 0 (167/167).
- Where the guard sits was read in the source. That the uid guard is the only thing stopping the merge is inferred: the
  dumps show the new label and the surviving calls, not the skipped loop.

## (c) The move that closed it
Delete the `do_flag` label and the `goto`. Write the flag tail out in both arms (scratch/f5.c = body.c):

    case 9:  … if ((s16)D_80076104 >= 0x12D) { func_800434BC(); D_80076214 = 1; *(u8 *)(arg0 + 2) = 0; break; } …
    case 16: … if ((s16)D_80076104 >= 0x12D) { func_800434BC(); D_80076214 = 1; *(u8 *)(arg0 + 2) = 0; } break; …

Every `return`/`break` and `>= 301`/`< 301 break` combination of the two arms scores 0 (f1-f7).

## (d) GENERATOR PROPOSAL
When a zero-byte barrier sits between a call and a `goto L`, and L directly follows an identical call elsewhere (the lever
fences off the one-insn fallthrough cross-jump, jump.c:1978), delete the label and duplicate L's tail into each goto
site. jump2's tail cross-jump re-creates the shared code under a fresh label that the jump-chain loop cannot see
(jump.c:1984), so the calls stay apart. This is the S103 c10 / S104 d3 "goto → structured" family.

## (e) What did not work (bytes)
- Keep the goto and move `do_flag:` into the `sync == 5 && …` arm, so both calls `goto` it (a1): 18. The two jumps to one
  OLD label now meet in the jump-chain loop with minimum 2. The condjump before each call jumps around its jump, so
  jump.c:2521-2525 lowers the minimum and case 9's call merges into case 16's instead. The bytes show the merge
  (`beqz v0,99c` into case 16's `jal`). Which rule allows it is inferred and was not dumped. The same count, mirrored.

## (f) Where the method fell short
Nothing in the pack pointed at it: neighbours.txt was empty, and related.txt's siblings (func_8003602C, func_80035C4C)
have no goto. Step 14's "a goto chain → structured C" rule was the right one. Every generator mutates the goto text, so
the sweep sat at 18 across 329 compiles.

## (g) Structs question
No. The pass is post-reload cross-jump, which compares insn patterns and knows nothing of types. `arg0` as a struct
pointer (`u8 f02, f03` fields at +2/+3) would read better but cannot change this decision. Not tested.
