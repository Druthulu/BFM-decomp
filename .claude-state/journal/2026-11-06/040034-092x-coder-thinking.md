---
ts: 2026-11-06T11:00:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_24FjG7JOVLpLt6k4cZ9c
---
r_S2S3S4 = 2 (the do-while around the load). Same as item 1.

Now I have 32+ tries on item 2. Let me record the wall for item 2 with best 2 and the same tag.

But before that — the twin's best (r_S2S3S4) differs from item 1's best in the diff detail? Let me check r_S2S3S4's diff: probably the store sink (same as d_S2S3S4).

Let me just confirm and record.

Actually, let me spend a couple of minutes trying one new idea that could crack BOTH: the "store sink" is because the RMW is ready. What if I make the RMW's load+ori depend on the store through a *memory* dependence by making the load's address vary? I tried p_ptr (folded).

What if the store's address varies and the load is fixed? Same thing.

What if the load and store are of different modes such that memrefs_conflict_p returns true? Let me look at memrefs_conflict_p to see when base+const vs base+const can conflict. If the offsets differ, it returns 0 (no conflict). Unless the offsets are unknown.

What if I make the store's offset *unknown* by using an index variable that's 0? e.g., `((u16 *)a0)[46 + k]` with k=0? cse folds.

What if the address is `(s32)a0 + 0x58` where the pointer is a `s32` variable that gcc can't prove is the same as the struct pointer? Hmm, `(s32)a0` — a conversion, same pseudo.

I'll stop and record.

Actually, wait. Let me reconsider the problem from the *bank* perspective: these items were marked "singleton crack shard" meaning they're expected to be crackable. Maybe the intended solution for the store sink is a *different statement order* that makes sched1 not sink. 

Let me look at the target once more: the store to 88 comes BEFORE the ori. In the source (orig C), the store is before the ori too. So the source order matches. sched1 reorders because the ori is ready.

What if the store's value computation (lui/addiu) is placed AFTER the load in source (it is) — and the ori depends on the load. So in the block, the order of readiness: load (cycle 0), address (cycle 0), store (cycle 1), ori (cycle 2). sched1 SHOULD pick the store at cycle 1. But in d_S2S3S4, the load is in a PREVIOUS block, so the ori is ready at cycle 0 → picked first.

So in a single block with the load first, sched1 produces the target. That's exactly the target. So the do-while must NOT split between the load and the RMW.

So the split must be BEFORE the load only. v_dw5 did that (do-while around unk5C) but the constant materialization was late (reload). In the target, the constant is materialized at f38-f3c (right after the load). Why? Because with the barrier, reload placed it there. In v_dw5, reload placed it after the lw32.

Hmm, so the barrier affects reload's placement. Why? Reload's spill/constant placement depends on the register allocation and the insn order. 

Hmm, in v_dw5 the schedule was: lw, nop, ori, sw196, lw32, lui, addiu, sw88. The constant was placed after the lw32 — that looks like sched1 moved the store late, and reload placed the constant right before the store.

In the target: lw, lui, addiu, sw88, ori, sw196, lw32. The constant is right after the load.

The difference could be sched1's ordering in v_dw5 vs the target. In v_dw5 the ori went right after the load (with a nop), while the target put the address first. Why? sched1's priority: the ori depends on the load; the address (lui/addiu) is independent. At cycle 0, the load is issued. At cycle 1, ready: the lui (independent). At cycle 2, the ori. sched1 should issue the lui at cycle 1! But v_dw5 emitted ori at cycle 1 with a nop...

Unless in v_dw5 the constant pseudo wasn't in the block (it's a reload artifact placed after sched1). Right! sched1 runs BEFORE reload; the constant is a pseudo (reg_equiv_constant). So sched1 schedules the ori and the store, and reload later materializes the constant right before the store. Since sched1 put the store after the ori/sw, reload placed the lui/addiu there too.

In the target, sched1 put the store BEFORE the ori — because... the same block! Wait, in v_dw5 the block also contains the load and the store. Why did sched1 put the ori first there but not in the target?

Hmm, maybe in v_dw5 the block does NOT start at the load: the do-while around unk5C creates a LOOP note; maybe the block boundary is elsewhere. Or the sched1 block includes the unk5C store.

Let me look at v_dw5's schedule again: f2c li v0,0x8000; f30 sh v0,92(s0) (unk5C); f34 lw v0,196; f38 nop; f3c ori. So the load is right after the unk5C store, and the ori right after the load with a nop.

In the target: same up to the load, then lui/addiu/sw/ori.

So sched1's choice differed. Why? The load's priority vs the store's. In v_dw5, the ori was chosen at cycle 1 (before the lui). Hmm, that means the ori was ready at cycle 1 — i.e., the load latency was 1. And the lui wasn't in the block (it's a constant materialized later).

In the target, the address lui/addiu IS in the block at sched1 time? No — the address is a constant pseudo too (in the orig C, `unk58 = (s32)&D_801907C4`). So it's also a reload artifact. But the target's final code has lui/addiu at f38 — placed by reload/sched2.

So the difference is purely in sched1's ordering of the store vs the ori. In v_dw5, the store to 88 (a constant-address store) — its address is a pseudo too, so at sched1 time it's `sw (pseudo), 88(s0)` and the pseudo is materialized later.

Sched1's ordering: the store's priority vs the ori's. Same as before.

Why would the target differ? Because in the target, sched1's block might be split by the barrier into two scheduling regions? If the barrier splits the *basic block* into two scheduling regions, then the load/store/ori are in the same region. Hmm.

Wait, maybe the barrier DOES split the basic block: `find_basic_blocks` splits after a CALL_INSN; an asm volatile is not a call. But maybe `flow.c`'s `split_block`? Hmm.

Let me directly test: dump the .sched for the orig and see the block boundaries. The .sched dump prints ";; -- basic block number N from X to Y --". Let me grep the orig's .sched for func_8018966C's blocks.

That would settle whether the barrier splits the block. Let me do it — it's quick (the dump is already generated under the item dir).
