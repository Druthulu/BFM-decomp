# func_80148D44 (src/ov_SC04_011/ov_SC04_011_after.c): T7 agent c12, twin of func_80148E54

**CLOSED: score 0** (`--try ... body.c --body`: "score 0 (OTHER; mine 68 ins, target 68) — MATCH"). Both NEEDED levers
(the `$4` pin and the keepalive `asm`) are gone. There is no pin, no `asm`, no added `volatile` and no zero term.
`PACK/body.c` is the text to bank. The whole-object gate is still the coordinator's job.

## The moves (same pair as func_80148E54; the full reading is in ../ov_SC04_011__func_80148E54/mechanism.md)

1. **Pass the angle to the 0x41 handler as its first argument**: `D_80191F64[D_80126C02 >> 12](tmp)`, with the in-body
   table declared `extern s16 (*D_80191F64[])(s32);`. Before, it was `s32 D_80191F64[]` cast to `s16 (*)()` at the call.
2. **Reuse the angle variable for the second `ratan2` result**, as the later operand: `tmp = ratan2(...);
   return (ang + tmp) & 0xFFF;`.

`body.c` also rewrites the tree's goto ladder as the `switch` that func_80148E54 and func_80148AFC use (the same bytes)
and drops the `p`/`res`/`d`/`e` temporaries. The minimal-edit form, which keeps the goto ladder and changes only moves
1 and 2, also scores 0 (`scratch/d2.c`). So the rewrite is for readability only and does not carry the close.

| body (all `--try`, real TU) | score |
|---|---|
| `body_free.c` | 6 (67 vs 68), the copy is missing |
| switch form, move 2 only (`scratch/d4.c`) | 6 (67 vs 68) |
| switch form, move 1 only (`scratch/d5.c`) | 7 (67 vs 68) |
| both, `(tmp + ang)` (`scratch/d3.c`) | 1 (68 vs 68), only the `addu` operand order |
| goto ladder, both moves (`scratch/d2.c`) | **0** |
| **switch form, both moves (`body.c` = `scratch/d1.c`)** | **0** |

## (a) Residual

The target has `andi a0,v0,0xfff` at 0x3498 and `move s0,a0` in the first `beq`'s delay slot at 0x34ac. Then `a0`
reaches `jalr v0` at 0x3504 on the 0x41 path unwritten, so the handler receives the angle. The lever-free body folded
the copy and was one instruction short.

## (b) Mechanism

This is the same as the twin, which was proved on its dumps. This body's own claims rest on the bytes above, not on its
own dumps. The `tu_free` `d = D_80126C01;` statement already separated producer and copy, so cse.c:7454's adjacency
did not apply there. But in the switch form the subject is read in the switch, and both forms close, so adjacency does
not decide anything once move 1 gives the producer its second (implicit) consumer:
- cse.c:856 (`make_regs_eqv`): the reuse puts `tmp`'s last mention in the sum insn, tying `ang`'s. The strict `>` keeps
  `tmp` canonical, so the swap at cse.c:7454 cannot fire and the argument is not re-canonicalised to `ang`.
- combine.c:1458: `tmp` is live past the copy (the call argument), so `added_sets_2` is 1 and combine keeps the copy.

## (d) Generator proposal

Same as the twin: R22 "hidden argument" together with R23 "stay canonical", emitted as one joint candidate.

## (f) Method note

The goto ladder in the tree body is a decompiler artefact. The same switch as in the twin produces identical bytes, so a
twin-aware tool could have proposed the E54 body text directly here, with the globals substituted for the `arg0`
offsets.
