---
ts: 2026-11-06T20:30:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Hn7gK6qGaZNesTP7UWnT
---
All 10. Let me check whether vG's RTL materialized the const earlier (maybe the score stayed 10 due to the barrier cluster only). Let me diff vG.

Actually, if vG materialized the const early and fixed cluster 2, the score would drop to ~4. It stayed 10, so no.

Let me check vG's lreg to see if the const moved.

Hmm, let me think about `store_expr`: for `r = 0xFFF80000;` where r is a local, gcc emits a move to the pseudo at the assignment point. But the RTL showed insn 108 (const) at the call. That means the assignment insn was *moved* there by some pass (cse? loop? combine?) or expand deferred it.

Wait — actually, look again at the .lreg dump: insn 95 (move a0), 101 (li 7), 103 (sh), 108 (const a1). The const insn number 108 > 103, so it was created later than the store — consistent with expand placing the constant at the call's arg setup, NOT at the assignment.

Why? Because gcc's expand_assignment for `r = CONST` with a register target uses `store_expr` → for a constant, it may leave it as a REG_EQUAL note on a pseudo and let it be materialized at the use (gcc's `force_operand`/`expand_expr` with `EXPAND_SUM`?). Hmm, actually in gcc 2.7.2, `expand_assignment` for a scalar VAR_DECL to a constant: it calls `store_expr (from, to, ...)`, which for a CONST_INT does `emit_move_insn (to, from)` — that should emit at the assignment point!

Unless the C `s32 r = 0xFFF80000;` declaration initializer is handled by `expand_decl_init` which calls `store_expr`... same.

But the RTL shows the const at the call. So maybe the assignment insn WAS emitted at the declaration point, and then cse/combine moved/merged it into the call arg. Since `r` is used once, cse's `delete_dead_from_cse`... no, cse can substitute a REG_EQUAL constant into the use and delete the original if the pseudo dies (`cse` does "constant propagation" for pseudos with REG_EQUAL when the value dies). That's it: cse (or combine) propagates the constant to the use and deletes the original insn. The launder's asm makes r's value opaque (the asm's output is not the constant), so cse can't propagate.

So the mechanism is cse constant propagation of a single-use constant. Real-C way to block: make the pseudo have more than one use or make the value not a "known constant".

The value is 0xFFF80000 = -524288. Any C expression producing it is constant-folded.

Hmm, what if we give r a second use that is dead? Deleted.

What if we give r a second use that's real but free? e.g., use r in the store's value with a mask that's folded... constant folding happens at the tree level before cse.

What if we use r in a comparison that's folded? Same.

OK: what about making r NOT a compile-time constant by using a value from a global that the compiler can't fold? That would add a load.

Hmm, hold on: what about the *other* arm? Both arms have the same structure. Maybe we can restructure so that r is assigned in both arms to the same pseudo? They're different scopes.

What if we hoist r's declaration and assignment before the if, then assign in each arm? The constant would be materialized once before the bnez — target has it in each arm.

OK. Let me look at this from the "is this a WALL?" perspective. Cluster 2's mechanism: cse propagates the single-use constant into the call arg; the launder's opaque asm blocks it. In plain C, a single-use constant always gets propagated. Wall tag candidates: `cse-const-addr`? No — that's about addresses. There's `combine-argcopy-sink`: "combine folds 1-use a1 pseudo into call-arg set at the call, sched1 keeps la a1 late; keepalive 2nd use blocks merge (best 4)". Similar: a 1-use pseudo folded into the call arg. Here the launder blocks the fold.

Hmm, but the target's const IS at the call arg setup? No — the target's lui a1 is before the store, i.e., not folded into the call arg. Right.

So cluster 2 = "cse/combine folds the 1-use constant into the call arg; only an opaque re-tie keeps it at its source position".

And cluster 1 = "reorg's dbr fill copies the join's xori into the bnez delay slot; only an asm barrier stops the search".

Both are asm barriers in effect. A WALL for both seems plausible, with best = 10.

But wait — the brief says WALL needs ≥20 min and ≥30 scored tries on the item. Item 3 started at 13:19. It's now maybe 13:35. I have ~10 tries. To claim a WALL I need 30 scored tries. That's a lot of cheap variants. Let me think harder for a crack first.

Alternative idea for cluster 2: prevent the constant propagation by making r's use *not* the direct call arg. E.g., pass `r` through a variable that's already there: `func_8012B178(q, r);` → what if we use `v` as the arg? `v` is later set to 0x20. `v = 0xFFF80000; ... call(q, v); v = 0x20;` — then v has 2 sets; the constant might still be propagated to the call. But maybe the store... hmm.

What about making the call's second arg a *memory* value that's already loaded? no.

What if we swap the two statements so the store comes after the call setup... no.

Let me think about cluster 1 differently. The reorg fill copies the xori into the bnez delay slot. What if we make the xori's operands depend on the else arm's load in a way that prevents the copy? The xori's operand is v (loaded in both arms). The copy is legal because v is dead in the then path.

What if `v` were a different pseudo in the then arm vs the else arm? Then the xori at the join would take a phi. Hmm.

What if we write `v ^= 1;` as `v = v ^ 1;` with v being... same.

What if the xori's destination were a NEW variable `w` and then `unkDC = w`? That adds a copy.

Hmm.

Let me look at the actual target vs mine for cluster 1 once more:
Target: bnez v1,2194; nop — branch target is the join point after the else's load (2190 lw; 2194 nop).
Mine: bnez v0,219c; xori — the branch target is after the xori, with the xori in the delay slot.

Note also the register: target's bnez tests v1, mine tests v0. Hmm, target at 217c: `bnez v1,2194` but the load at 2174 is `lw v0,220(s0)`. Wait, target: 2174 `lw v0,220(s0)` then 217c `bnez v1,...`? Let me re-read the target listing:

```
216c: 10400008 	beqz	v0,2190
2170: 02002021 	move	a0,s0
2174: 8e0200dc 	lw	v0,220(s0)
2178: 00000000 	nop
217c: 14400005 	bnez	v0,2194
2180: 00000000 	nop
```
Yes, bnez v0. I misread earlier (that was 21b0 `bnez v1`).

OK so target: `lw v0,220(s0); nop; bnez v0,2194; nop`. Mine: `lw v0,220(s0); nop; bnez v0,219c; xori v0,v0,1`.

So the only difference in cluster 1: the delay slot (nop vs xori) and the branch target.

What if the xori at the join were not the first insn after the else's load? The else arm is just `v = unkDC;` (lw + nop). Then the join's xori.

If the else arm had one more insn, the xori wouldn't be adjacent... but that changes code.

What if we reorder the join: `v ^= 1; unkDC = v;` → `unkDC = v ^ 1;`? Then the store's source is `v ^ 1` — the compiler would emit xori then sw. Same.

Hmm, what about `((Unk*)s0)->unkDC = v ^ 1;` and removing the separate `v ^= 1;`? Then v is used as the source of xori; the store follows. Let me check the target: `xori v0,v0,1; jal func_8012B200; sw v0,220(s0)` — the xori's result is stored to unkDC after the call (in the delay slot). If we write `unkDC = v ^ 1;` and then `func_8012B200(p);`, the RTL would be: xori v0 = v^1; sw unkDC,v0; call. Hmm, the sw might be scheduled into the delay slot as in the target. But `v` is also used later? No, v is dead after. Actually the current code is:
```
v ^= 1;
((Unk*)s0)->unkDC = v;
func_8012B200(p);
```
The target's sw is in the call's delay slot, and the xori is before the call.

If I write `((Unk*)s0)->unkDC = v ^ 1;` then v is used by the xori, and the store uses the xori result. Same RTL (maybe). Could change sched/reorg. Worth a try.

But that doesn't address the bnez fill. Hmm.

Actually, wait: maybe the reason reorg copies the xori into the bnez delay slot is that the xori is "the first insn of the join thread" and the else arm is empty-ish. If the xori were not movable (e.g., had a side effect), reorg wouldn't copy. 

What if `v ^= 1` were a 16-bit operation: `v = (s16)(v ^ 1);`? That adds a sign-extend (sll/sra) — no.

Hmm, what about making `v` a u16 variable? Then `v ^= 1` would be a 16-bit xori? The store is `sw` (32-bit) in the target, so v is 32-bit.

Let me look at the reorg dump to see which optimization copies the xori and whether there's a flag to exploit. The .dbr dump might show the fill decisions with comments. Let me grep for "delayed" or the insn near the branch in the .dbr dump of nolau.

Actually, from the .dbr RTL dump, the bnez insn would be a SEQUENCE with the xori in the delay slot. Let me find it and see if there are notes explaining.

Let me search the nolau .dbr for the xori (const_int 1 xor).
