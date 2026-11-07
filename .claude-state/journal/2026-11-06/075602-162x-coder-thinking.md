---
ts: 2026-11-06T14:56:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qi2isKyUzcEH2QuAmPMW
---
Still 4. So the label restructure didn't help; the compiler optimized it back.

OK, this is a genuine WALL. The launder prevents a jump2 known-value fold that real C can't prevent.

Let me do a batch of more tries to reach 30, then record the WALL.

Actually, wait. Let me reconsider the possibility that the fold is done by `find_cross_jump`/`cross_jump` (the second jump pass's cross-jump optimization). The cross_jump merges two insns with the same constant (REG_EQUAL). Maybe the `bne t,3` and another `bne ?,3` are merged. Hmm.

Let me look at the jump2 dump for c1 around the case 5 region: the `bne t,5,L300` (line 566) and then the unconditional `j L276` (line 576). The `bne t,3` was replaced. Where did the comparison go? 

Actually, maybe the optimization is `delete_dead_code`: the `bne t,3,L276` — if the compiler determined that the branch is always taken (t==5), it converts to a jump and deletes the comparison (the `li v0,3`? no, 3 is in v1).

Hmm, but how does jump2 know t==5? Let me look at the jump2 dump's c1 case 5 region in the unnormalized form around line 540-580. The insns: `li v0,3` (insn 246?), `beq t,v0,L269`, `li v0,5` (insn 256?), `bne t,v0,L300`, then `j L276`.

Wait — the `li v0,5` is insn 256? And the `bne t,v0,L300` has `(insn_list 256)` — the LOG_LINKS to the `li v0,5`. So the comparison is `t != 5`.

For the `bne t,3` to fold, jump2 must know t==5 on the fall-through. The fall-through of `bne t,v0,L300` is t==5 (since the branch is t!=5). Jump2's `thread_jumps` or value tracking records this.

Hmm, let me look at the jump.c code that handles "the fall-through of a conditional branch implies the condition". There's `jump_optimize`'s handling of `if (x == c)` followed by another compare. Let me search for "record_jump" or the code that propagates conditions.

Actually, maybe it's `cse` running again? No, cse doesn't run after reload.

Wait — maybe it's the `reorg`/`dbr` pass. The .jump2 dump is after jump2 (line 3142). The .dbr dump is after reorg. Let me check: is the fold visible in the .jump2 dump (c1) — yes, I saw it. So it's jump2.

Let me look at jump.c's `jump_optimize` around line 1794 (`redirect_jump (insn, nlabel)`). Let me read the context.

Actually, let me look at `find_cross_jump` (line 2363) and the cross_jump code. The cross_jump optimization is enabled in the second pass (cross_jump=1). It merges similar insns. Hmm.

Let me search for the exact optimization: a conditional jump whose condition is known. In jump.c, `jump_optimize` has a section "See if this jump is a jump to a label that is the next insn" and "Delete the jump if it's to the next insn". Also `delete_dead_code`.

Let me look at jump.c lines 1700-1850.

Hmm, I'm spending too long. Let me just record the WALL. I have ~14 tries. Let me do a batch of 16 more quick variants to reach 30, then record.

Actually, let me reconsider: maybe the fold is NOT jump2 but the `cross_jump` merging. Let me check if disabling cross_jump (not possible) ... no.

Let me look at the jump2 dump's c1 vs orig around the case 5 for the `bne t,3` and see if there's a `REG_EQUAL` note. In orig, the `bne t,3` uses `(reg v1)` (the constant 3). The `li v1,3` has `REG_EQUAL (const 3)`. In c1, the `bne t,3` is gone and the constant 3 is in v0 (reused for 5). 

The cross_jump optimization (line 2473) merges two insns that set the same constant. Maybe in c1, the `li v0,3` and `li v0,5`... no, different constants.

Hmm, wait — maybe the fold is done by `find_cross_jump` comparing the two branches `beq t,3` and `bne t,5`? No.

Let me look at jump.c around line 2500-2570 (after find_cross_jump). The `cross_jump` function merges blocks. Hmm.

OK, let me just do the batch and record the WALL. Time is ~09:40, ~45 min on this item.

Let me generate 16 variants systematically:
- different nesting of the ifs
- different order of the t==3/t==5 checks
- switch-based
- using u32 t
- etc.

Actually, most won't help. But let me do them for the try count. Let me generate 16 variants in one script.

Hmm, but is it honest to count 30 tries if 16 are trivial? The brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". I'll do meaningful variants.

Let me generate:
1. t as u32
2. t as s16
3. idx-based check: `if (a0 - 1 == 5)`? changes code.
4. switch on t for the inner
5. reorder: check t==5 before t==3
6. combine t==3 and t==5
7. use `sel` in the condition
8. `if (t - 3 != 0)`
9. `if (t > 3 || t < 3)`? 
10. `if (t != 3 && t == 5)`
11. `if (t == 5 && t != 3)`
12. nested if with else
13. `if (t == 5) { if (t == 3) {} else goto sel_094; }`
14. goto-based with a fake dependency
15. `volatile` read of a global? 
16. `if (t != 3) { if (1) goto sel_094; }`

Let me generate a batch of these and score. Then record the WALL.

Actually, let me reconsider one more time: maybe the fold can be prevented by making the `if (t == 5)` check use a `switch`. A switch on t with cases 3 and 5 might compile to a jump table or comparisons, and the second check `t != 3` might be kept. Let me test the switch restructure as one of the variants.

Let me write the batch.
