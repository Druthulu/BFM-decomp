---
ts: 2026-11-06T04:04:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2xRmLKywTpAHtsKVWVwH
---
This is deep. Let me step back and consider the practical approach: test whether the do-while around the FIRST block (diff) plus variable reuse etc. produce 59 with the double load.

Actually, c1 (do-while around x2 block) got 59 ins but still one lh? Wait c1 had 59 ins. Let me recount c1's stream: 77c8 lh v1,46; 77cc li a0,8; ... 77d8 sll v1,v1,6 (reuse). That's one lh. But 59 ins vs baseline 58: the extra ins is the do-while loop's nop? Actually 77dc lhu v0,14; 77e0 nop — the nop is the load-delay. Hmm.

So do-while added a nop, not a load. Interesting but not the fix.

Let me think about cse's load forwarding more: the entry for a load is `MEM → dest`. It's invalidated when the dest register is SET by a non-equivalent value (invalidate(dest)). If we can make the compiler emit a *second* assignment to the same pseudo between the loads that is NOT removed as dead... 

What if we reuse the variable x and the second load is *before* the first's use ends? c4 did x reused but cse still forwarded because the lookup occurs before the invalidation of the same insn.

Trick: make the value register differ. If the two loads are assigned to *different* variables, each load has its own pseudo; cse's entry value = first pseudo; forwarding the second load would generate `x2 = x1` (a copy) — that's a copy, and cse does replace the MEM with a REG, then the copy `x2 = x1` might be removed by copy propagation. That's what happened in the baseline.

To stop forwarding, we need the entry gone. Store or call. There's no store/call between. 

UNLESS the first load's result pseudo is *clobbered* by an intervening instruction that writes it. The only writes are... hmm.

What if the second block starts with a computation that assigns to the same C variable as the first load's destination? We tried; forwarding happens at the load insn itself before the assignment.

Wait, but cse processes insns in order; the insn `(set (reg x) (mem 0x2E))` — when cse encounters it, it looks up the src MEM. The table entry MEM→(reg x) was inserted earlier. Validation: for the entry to be usable, it checks `reg_in_table[REGNO(x)] == reg_tick[REGNO(x)]`. The tick for x: when was it last changed? At the first load, x was set and the entry recorded. Since then, nothing set x. So valid → forward → `(set (reg x) (reg x))` → deleted. Yes.

What if the destination of the second load is a DIFFERENT pseudo (x2), and the first's pseudo x was *invalidated* by a set. So: assign the first load's result to x; then reassign x to something before the second load. That's the dead-assignment problem: it must be live. Make it live by using it in the output! E.g.:

```
s32 x = *(s16*)((s32)s0 + 0x2E);
s32 diff = 8 - x;
t = diff << 9;
x = t;                 // reassign x to a live value (t is used later!)
...
x2 = *(s16*)((s32)s0 + 0x2E);
```
But `x = t` then x unused → dead unless used. We could use x in the final stores: `((Unk*)s2)->unk1A = t;` → use x there? That changes register allocation maybe. Hmm, this is contorted and would add a move.

What about making the first load's value flow into something that clobbers its register via a call? There's the call func_80182654 before. No.

Hold on — maybe I'm overcomplicating. Let me reconsider the target: perhaps the first `lh v0,46(s0)` is NOT the same pseudo as the second because the first is a **u16** load sign-extended differently? Let me check the instruction encoding: `lh` = load halfword sign-extend. Both are lh.

Hmm, let me look at whether the ORIGINAL source might have had the second load as part of a *different statement order* where cse's table was flushed by the first block's structure. What flushes the table besides stores/calls? A jump/BB boundary! cse works on extended basic blocks; if the two blocks are in different basic blocks (e.g., separated by a conditional branch), the table is flushed at block boundaries. Is there a branch between? In the target, no branch between 77cc and 77d8.

But a *label* / control flow could still split cse's EBB even without emitting a branch? If the source had something like `if (1) { ... }` the compiler folds it. A `do{}while(0)` creates a loop but cse processes the loop body; cse_around_loop might flush? c1 didn't flush.

What about `goto`? A goto to a label that immediately follows creates a jump that jump.c optimizes away, but cse may treat the label as a block boundary. Hmm! If there's a CODE_LABEL between the two blocks, cse_basic_block starts a new EBB at the label and flushes the table? Let me check: cse's cse_basic_block processes a range; at labels, it does... `cse_end_of_basic_block` and cse_basic_block's loop: when it hits a CODE_LABEL, it may continue if the label isn't a branch target? Labels from gotos are branch targets initially; jump.c may remove the jump (if it's a jump to the next insn) and then the label becomes unreferenced and deleted by... jump.c's delete_unreferenced_labels. Hmm.

Actually there's a classic trick: a `goto` label splits the EBB for cse even if the branch is later optimized? Not reliable.

Let me look at cse_basic_block's handling of labels: it starts at a label? cse_main calls cse_basic_block for each basic block; blocks are delimited by jump insns and labels (BB boundaries computed from the CFG). If the label remains, cse flushes. But jump.c (before cse? order: jump, cse1) removes jumps-to-next and unreferenced labels. If the label is unreferenced after jump.c, it's removed. But wait, jump.c also does cross-jumping and thread optimization; a label that is a target of a jump that gets deleted becomes unreferenced and is removed by jump.c. So a goto wouldn't leave a label.

Hmm, but a `do{}while(0)` creates a label and a backward branch; cse processes it as a loop (cse_around_loop) and c1 showed no flush.

OK let me look at what cse does at loop start: cse_basic_block, upon seeing NOTE_INSN_LOOP_BEG, calls cse_around_loop? and `cse_check_loop_start`? Let me read cse_basic_block.
