---
ts: 2026-11-06T11:57:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Df2SoM9odRrP8LSjmCuU
---
y07 has the correct instruction ORDER (all 37 match in order) but the registers are rotated: target a0,v0,v1 → mine v1,a0,v0.

So it's purely a register assignment issue (REG-caller). The rotation: temp_a0: target a0, mine v1. temp_v0: target v0, mine a0. temp_v1: target v1, mine v0.

Interesting — it's a cyclic shift. Why?

In the target, the allocation is: temp_a0=a0, temp_v0=v0, temp_v1=v1.
In mine: temp_a0=v1, temp_v0=a0, temp_v1=v0.

Hmm, maybe the intervening store's presence in the source (as the first sh store) changes the local-alloc order. Since sched1 moved the intervening store to after the sb5, the final order is the same, but the *pseudo numbering / use order* at local-alloc time differs.

local-alloc assigns regs based on the order pseudos are first used in the block. The block at local-alloc time is the sched1 output. Since the final order is the same, the allocation should be the same... unless the insn uids differ, affecting the tie-breaks.

Hmm, local-alloc's `block_alloc` iterates over insns in the block and assigns registers. The order is the same. But the "qty" priorities and the `reg_qty` might differ due to the intervening store's uid.

Alternatively, global-alloc (for pseudos that cross blocks) might be involved. The temps are block-local.

Let me try to fix the allocation by changing the declaration order or the types:
- temp_a0 as s32 gave score 2 earlier (x05) — different.
- Maybe declaring temp_v1 first, or temp_v0 first.

Actually, local-alloc assigns by use order, not declaration. The first-used pseudo is temp_a0 (lbu 5). Target: a0. Mine: v1. So temp_a0 didn't get a0 in mine.

Why would temp_a0 get v1? Maybe because a0 is already taken by something else at that point? At the start of the block, the function prologue uses s0 (arg0) and the stack. a0 is free after `move s0,a0`. So temp_a0 should get a0... unless local-alloc's order gave a0 to temp_v0 (which is defined next) — but temp_a0 is defined first.

Hmm, in mine temp_v0 got a0. And temp_v0 is defined after temp_a0. So local-alloc assigned a0 to temp_v0 before temp_a0? That suggests local-alloc's qty priority (uses/live) rather than first-def.

temp_v0 has more uses (subu, andi, sb, sh×4) than temp_a0 (subu, addiu). So temp_v0 has higher qty → gets a0 first. In the target, temp_v0 got v0 (better than a0) — so the target's priority order differs.

Wait, in the target temp_v0=v0, temp_a0=a0, temp_v1=v1. If qty priority: temp_v0 (many uses) gets v0 (the best). Then temp_v1 gets v1, temp_a0 gets a0. That matches target!

In mine: temp_v0=a0 (not v0), temp_v1=v0, temp_a0=v1. So the priority order gave v0 to temp_v1, a0 to temp_v0, v1 to temp_a0. Hmm.

The difference must be the live ranges: with the intervening store, the live ranges at local-alloc time changed.

Hmm, but the final asm order is identical. Unless the *uids* differ (sched1 output order same but uids from source order). local-alloc uses `regno` and `qty`, not uids, for priority. But tie-breaks use the insn order.

Let me look at the alloc table for y07 vs orig.

Actually, maybe I should try a different intervening store that doesn't perturb the allocation as much. The `sh 16` store uses temp_v1; moving it between changes temp_v1's live range.

What if the intervening store uses temp_v0 (e.g., sh 22)? y03 (sh 22) = 14 too. Same issue.

What if the intervening store is a store that was ALREADY between them in the target order? None.

Hmm. What if I use the `sb +5` as the intervening store (y07) — it uses temp_a0. Still 14.

Let me look at the allocation table to understand.

Actually, maybe the rotation is due to the intervening store being the FIRST use of temp_v1 (before the reload). In the target, temp_v1's first use is `sh 16` after the sb5. With the intervening store, temp_v1 is used earlier (between sb6 and lbu6), extending its live range and changing priority.

Let me check the alloc table for y07.

Alternatively, I could try intervening stores that use temp_v0 (the reload's register) — that would also extend temp_v0's live range.

Hmm, let me think about what determines the assignment. Let me get the alloc table for y07 and orig (orig has the pins, so not comparable). Let me compare y07 vs w1 (score 1, correct allocation but forward). w1's allocation: temp_a0=a0, temp_v0=v0, temp_v1=v1 (correct, since only the lbu differs). So w1's regalloc is right.

So the intervening store broke the regalloc. I need an intervening store that doesn't change the live ranges/priority.

Idea: use a store that's already between them in the target order but to a location that cse considers varying... Hmm, none.

Idea: make the intervening store a **write to the same address +6** with the same value? That would be a redundant store; cse might merge.

Idea: use a store whose source is a value that doesn't extend any temp's live range: e.g., a store of a constant! `*(s16*)(arg0+0x??) = 0;` — but that adds an instruction (li+sh) and changes the code.

Idea: use the `sb +5` store (temp_a0) — extends temp_a0's live range slightly. y07 = 14.

Hmm.

Let me look at the alloc table for y07 to see why the rotation.

Actually, maybe the rotation is due to the *insn uid order* affecting local-alloc's tie-break. Since sched1 reordered the intervening store back, the final order is the same but the uids differ. local-alloc processes insns in uid order? No, it processes in the block's insn chain order (which is the sched1 output order).

Wait, the final asm order IS the same as target (y07 diff shows the order matches). So local-alloc sees the same order. Then why different regs?

Unless local-alloc's `block_alloc` uses `INSN_UID` for tie-breaking among equal-priority pseudos, and the uids differ because the source order differs.

The alloc table shows "TIE (lower allocno wins, global.c:607)" — global-alloc. So these are global-alloc pseudos, not local! If they're in the .greg table, global-alloc assigns by priority with allocno-number tie-breaks (global.c:607). The allocno number depends on the order pseudos are encountered (creation order = source order). Since my source declares the temps in the same order (temp_a0, temp_v1, temp_v0), the allocno numbers should be the same... but the intervening store changes the *ref counts* and *live lengths*, hence priority.

Let me get the alloc table for y07.

Time: ~05:02. Let me do this quickly.
