---
ts: 2026-11-06T14:53:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jOfabP2JjQrDM9uZK4Do
---
In c1's jump2 (post-reload), the case 5 code is:
```
code_label 68
insn v0 = 3
jump_insn (eq s0, v0) -> label (L70)
insn v0 = 5
jump_insn (ne s0, v0) -> label (L71)
jump_insn (label_ref) -> ??? (unconditional, to L73)
barrier
code_label 70 (sel_054)
...
```

Wait, the second jump is `(ne s0,v0) -> label_ref N` (the `bne t,5,L71`). Then an unconditional `jump (label_ref N)`. Where does that unconditional jump go? The diff said mine has `(jump_insn (label_ref N))` where orig has the asm + conditional. So mine's unconditional jump goes to L73 (sel_094)? Let me check the target.

Orig:
```
jump_insn (ne s0,v0) -> label (L71)    # bne t,5,L71
insn (asm)                              # launder
jump_insn (ne s0,v1) -> label (L73)     # bne t,3,L73
barrier
code_label 70 (sel_054)
```

Mine:
```
jump_insn (ne s0,v0) -> label (L71)    # bne t,5,L71
jump_insn (label_ref) -> ???            # unconditional
barrier
code_label 70 (sel_054)
```

So mine replaced the `bne t,3,L73` with an unconditional jump. To where? Since the fall-through is sel_054 and the branch was `bne t,3,L73` (always taken when t==5), the unconditional jump goes to L73 (sel_094). Wait, but then the code would be `bne t,5,L71; j L73; sel_054: ...` — if t==5, jump to L73; else L71. That matches the fold.

Hmm, but the final asm for mine was `beq s0,v0,L73; j L71` (from the score diff). That's `if (t==5) goto L73; else goto L71`. The jump2 dump shows `bne s0,v0,L71; j L73`. Different order but equivalent. The assembler/reorg might have inverted it.

OK so the fold is: `bne t,3,L73` -> `j L73` because t==5 on the fall-through.

This is a jump2 optimization. To prevent it, I need jump2 to not know t==5. The asm does that.

Real C: I need an insn between the branches that survives to jump2 and blocks the fold. The target has the asm (empty). Real C can't produce an empty insn.

Hmm, but maybe I can produce a real insn between them that's already in the target? The target has NO insn between the two branches except the asm. So no.

Wait — unless the `li $2,5` (the constant 5) is between them? No, that's before the first branch (delay slot).

So this is a WALL.

Hmm, but let me reconsider: the fold is `bne t,3,L73` -> unconditional because t==5. What if the second branch compares a DIFFERENT register that also holds 5 but jump2 doesn't know? If the comparison uses a copy `u` of t, and u is in a different register... but then the code would compare u, not t. The target compares t ($16). Unless u is coalesced to $16 — but then jump2 sees the same register and folds.

Hmm, post-reload, if u and t are both in $16, the comparison is on $16, and jump2 knows $16==5 from the first branch. Fold.

So the only way is a physical insn between them. WALL.

Wait, but let me reconsider the target's `bne t,3,L73`: the branch compares t ($16) with 3 ($3/v1). The `li $3,3` is in the delay slot of the FIRST branch (`bne t,0,L68`). So $3=3 is loaded early. And the `bne t,3,L73` uses it. 

In mine, the constant 3 is in v0 and reused for 5. The target has 3 in v1 and 5 in v0. This register difference is a consequence of the fold (in mine, the `bne t,3` is gone, so the constant 3 isn't needed there; it's reused).

If I could prevent the fold, the constants would follow.

OK, so the fold is the crux. Let me look at jump2's optimization to see if there's a CFG structure that prevents it. The fold is likely `thread_jumps`: it sees a jump to a block, and threads it. Or it's the "delete_unreachable_code" / "if_then_else" simplification.

Let me look at the jump2 dump's processing to see what optimization did it. The jump2 dump might have comments. Let me look at the c1 jump2 dump's header/comments around the case 5 region.

Actually, let me look at jump.c's `jump_optimize` for the optimization that converts a conditional branch to unconditional based on a known value. Search for "thread" or the code that handles a jump to a label.

Hmm. Actually, the fold `bne t,3,L73` -> `j L73` requires knowing t==5 on the fall-through of `bne t,5,L71`. This is jump.c's "find the value of a register at a point" via `reg_last_set`? Or it's `thread_jumps` following the CFG.

Let me look at the jump2 dump for a comment explaining the optimization. Let me grep the c1 jump2 dump around the case 5 for comments.

Actually, the .jump2 dump is the RTL after the second jump_optimize. The optimization decisions might not be logged.

Let me look at jump.c's `jump_optimize` and find where it simplifies a conditional branch to a jump based on a known comparison. Search for "find_comparison_args" or "record_jump" — no, that's cse. In jump.c, there's `thread_jumps` and `delete_dead_code` and `simplify`...

Hmm, let me grep jump.c for "known" or "condition".
