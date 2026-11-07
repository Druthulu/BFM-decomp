---
ts: 2026-11-06T14:22:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JhzUXfBvHXJFwiG5eoCi
---
The C0414 "dead-reset CSE-breaker" is very relevant:
```
p = expr;        /* name it            */
f(..., p);       /* use it             */
p = 0;           /* DEAD-RESET, immediately after */
```
"flow deletes the dead set before sched1 — so it costs zero bytes and zero LUID/priority disturbance."

Wait — "flow deletes the dead set before sched1". So flow DOES delete dead stores! And crucially, the dead set `p = 0` is deleted by flow. But does flow COUNT it as a ref before deleting? If it's deleted, the ref count might not include it, or it might.

Hmm, but for our purpose, we want to ADD a ref to i. A dead reset `i = <something>` would add a set ref. But `i = 0` would change semantics if not deleted; if flow deletes it, semantics preserved (the value is dead). But if flow deletes it, does it count the ref? The C0414 note says "flow deletes the dead set before sched1 — so it costs zero bytes and zero LUID/priority disturbance". If it's deleted by flow, and flow computes refs in the same pass... The ref might be counted then the insn deleted.

Actually, let me test the idea: add a dead store of i inside the loop and see if the priority flips and the code stays the same.

But what dead store of i is semantically safe? A dead store to i means: `i = X;` where the value of i is never used afterward. But i IS used afterward (in the loop condition). So any store to i would change the value. Unless it's immediately followed by another store of i (the real increment). E.g.:

```
i = <junk>;   // dead: overwritten by i++ before any use? 
i++;
```
No — i is used in the condition AFTER i++. So `i = junk; i++;` then condition uses i = junk+1. Changes semantics.

What if the dead store is at the END of the loop body, after the real i++ but before the condition? Then it would be used by the condition. Not dead.

Hmm. What about a dead store to a DIFFERENT variable that aliases? No.

What about a dead store of i that flow deletes because it's followed by a set of i in the same block with no use in between:
```
do {
   ...
   i = i;      // identity — forbidden
   i++;
} while (i < n);
```
The `i = i` is an identity launder (forbidden and folds).

What about `i = i + 0`? folds.

Hmm.

What about a dead store to a temp that's never read: `s32 t = i;` then never use t. Flow would delete it (dead store), but does it count the ref to i? The read of i in `t = i` IS a use, counted by flow. Then the dead store to t is deleted. So this adds a use of i! And it costs zero bytes if flow deletes the dead store.

Wait, but `t = i` is a copy; flow's dead-store deletion deletes the insn if t is dead (never used). The use of i in the insn would be counted by flow's ref counter (reg_n_refs += loop_depth for the use of i). Then the insn is deleted. That's exactly the asm effect!

But does flow delete it before or after counting refs? The C0414 note says flow deletes the dead set. If the ref to i is counted during the same scan, we get the ref. Let me test!

But hold on: would `s32 t = i;` inside the loop be deleted? It's a copy to a local temp never used. flow's `mark_used_regs` marks t as set; if t is never used, the insn is a dead store. The deletion... Let me check whether flow actually deletes it. The C0414 note says `p = 0;` (dead store of a pointer) is deleted by flow. So yes.

But wait — the dead store deletion in flow: I need to confirm the ref counting order. Let me look at the code that deletes dead insns in life_analysis. Earlier I found flow_delete_insn called at line 664 (unreachable blocks). But C0414 says flow deletes dead sets. Let me search more carefully — maybe in `propagate_block` there's a check. Let me look at lines 1440-1470 (the `loop_depth == 0` bit) and around mark_used_regs.

Actually, let me look for where an insn is deleted for being a dead store: search for "insn = PREV_INSN (insn)" near a deletion, or `PUT_CODE (insn, NOTE)`.
