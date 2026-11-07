---
ts: 2026-11-06T14:26:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_S5mynmxCcPtJj0Nc5NZz
---
sched.c line 4947: `reg_live_length[regno] = sched_reg_live_length[regno];` — sched1 RECOMPUTES reg_live_length from the scheduled blocks! So the live_length used by global-alloc is the SCHEDULED one (post-sched1), not flow's. That explains the .lreg values (39/36) differing from .flow (45/42).

So the priority that matters is computed on the post-sched1 live lengths. And sched1's live lengths depend on the scheduled order. Since b2's sched1 result is identical to c1's (score 6, same regs), the live lengths are the same (39/36).

Hmm. So the statement reorder didn't change the sched1 output (it reordered back), hence the same live lengths.

OK. So to change the priority, I need to change either the refs (flow, pre-sched) or the post-sched live lengths. The refs are the same (11). The post-sched live lengths are 39/36.

Since sched1 reorders, moving statements in C might not change the scheduled result.

Let me look at the target: i live 41, dst live 37 (post-sched). Wait, the target .lreg showed i=41, dst=37. Ours: i=39, dst=36. So the target's i live is 2 longer (due to the asm insn adding 2 to the live count) and dst 1 longer.

So the target's priority: i = 3*14/41 = 1.024; dst = 3*11/37 = 0.892.
Ours: i = 33/39 = 0.846; dst = 33/36 = 0.917.

To flip, I need i's refs up or live down, or dst's down/up.

Since sched1 recomputes live_length from the scheduled blocks, and the scheduled code is identical (the target's code minus the asm insns, which add 2 to i's live), the live lengths are fixed at 39/36 for any variant that produces the same scheduled code. So the only lever is REFS (flow, pre-sched).

Therefore: I MUST increase i's refs (or decrease dst's) in the flow pass, without changing the scheduled code.

flow's refs are computed pre-sched, pre-combine. So a use of i that combine removes later would count. But we showed dead stores are deleted by flow itself (final pass) before counting.

BUT: combine runs after flow. Combine can merge/remove insns. So if I add a use of i that flow counts (because its dest is live), and combine then folds it away (merging into an existing insn), the ref counts and the final code would be unaffected.

Wait, but if flow counts a use of i, the insn must have a LIVE dest (else deleted). If combine folds it into an existing insn, the final code is the same. What insn could that be?

Idea: `dst = dst + 0;`? The dest dst is live, so not deleted. But `dst + 0` folds to dst at the tree level (no insn). Hmm.

Idea: a copy `t = i;` where t is live (used later). Flow counts the use of i. Combine might propagate t into its use and delete the copy. If t's use is the loop condition or an address, combine could fold. But if t is used in a way that requires a copy (e.g., a different register), combine might keep it.

Hmm, but the target code is fixed; a copy would be an extra instruction unless combine removes it.

Idea: use i in the comparison via a temp: `t = i; ... while (t < n);` — combine might fold t into the slt. But the slt's operand would be i directly (same as target). And flow counts the use of i in `t = i` (dest t live). Then combine folds t into the slt and deletes the copy. This adds 1 ref to i at depth 3! 

But wait: `t = i` inside the loop, then `while (t < n)`. Hmm, t would be used in the condition. Let me structure:
```
do {
    ...
    t = i;      // copy
    i++;
    src++;
} while (t < n);   // uses t (== old i)
```
Wait, that changes semantics: t = i (old i), then i++, then `t < n` compares old i. The original compares new i. So I'd need `t = i + 1` or reorder: i++; t = i; while (t < n). Then t = new i, compare t < n. Same semantics!

So:
```
do {
    ...
    i++;
    t = i;
    src++;
} while (t < n);
```
Now `t = i` is a copy with a live dest (t used in the condition). Flow counts the use of i (+1 ref at depth 3). Then combine: can it fold `t = i` into `t < n`? The copy is immediately before the comparison (within combine's 3-insn window), so combine's `try_combine` would substitute i for t in the slt, producing `i < n` and deleting the copy. That gives the target's `slt $2,$10,$12`! And the extra ref to i is counted by flow (before combine).

But wait: cse2 runs BEFORE flow. cse2 would see `t = i; ... t < n` and propagate t=i into the comparison, deleting the copy BEFORE flow counts it. Damn. cse2 (line 2926) is before flow (2983).

Hmm. Unless cse2 can't propagate because... cse does copy propagation within an EBB. The copy `t = i` and the use `t < n` are in the same block (the latch), consecutive. cse would propagate. So the copy is gone before flow. No ref.

Unless I use the do-while(0) split to prevent cse2 from propagating! The C0535 trick: `do { t = i; } while (0);` splits the EBB so cse doesn't propagate t. Then combine (after flow) sees the copy and folds it? But combine works on insns; if the copy is in a separate EBB (after a label/barrier), combine's window might not span the boundary. Hmm.

Actually, the do-while(0) creates a block boundary (a label). cse1's EBB split prevents propagation. But combine also processes per basic block. If `t = i` is in its own block and `t < n` in the next, combine won't fold across blocks. Then the copy remains as an extra instruction. Bad.

Hmm.

Wait, maybe I don't need the do-while(0). Let me reconsider: does cse2 actually propagate copies? cse's `cse_insn` handles SETs and can do "copy propagation" for registers? gcc's cse does constant and expression CSE, and it also does copy propagation via `reg_eqv`? Actually, cse does track `reg_hash` for register values (equivalent registers). Yes, cse can replace a register with its equivalent. So `t = i; t < n` -> cse would make `t` equivalent to `i` and use `i` in the comparison, then the copy `t = i` becomes a self-copy and is deleted. So the copy disappears before flow.

Hmm. But wait — cse2's copy propagation is limited. Let me just TEST it empirically. Let me create the variant with a temp copy before the comparison and see if the score is 0 (and check the greg order).

Actually, simpler: let me test with a dead-ish copy. Let me write:
```
do {
    ...
    i++;
    src++;
    t = i;
} while (t < n);
```
with `s32 t;` declared in the block.

Let me also try `t = i + 1` style variants.

Let me test this. If it scores 0, we're done.

Actually, there's an even simpler variant that might work: since the target has `slt $2,$10,$12`, and our code has the same, adding a copy `t = i` that combine folds into the slt would be perfect. Let me test.

Let me create g1.
