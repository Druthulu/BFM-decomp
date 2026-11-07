---
ts: 2026-11-06T12:52:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Qjx8C6vxFSq2msZ56RYg
---
One barrier (memory clobber) at line 3682 (3636+47-1 = 3682). Function ends at 3636+179-1 = 3814.

The kinds = barrier. Note: the memory clobber is the key lever 12 in the header comment: "THE DISPATCH-BLOCK MEMORY CLOBBER (closed the old case-3 residual, 3 -> 0)". And it says the header explains why alternatives fail:
- volatile-cast index load: forces reload but loop.c can't join giv.
- asm clobber at the case-3 head: reload+giv fine but reorg.c stop_search_p halts fill_slots_from_thread at ANY asm insn, so the addu never hoists into the bne's delay slot.

So this is a documented WALL: the memory clobber is needed to invalidate cse's memory table at the dispatch point. The header says a non-volatile clobber "invalidates cse's memory table at zero bytes".

Real-C alternatives: a non-volatile memory clobber has no C spelling... The comment says all alternatives were ruled out by reading the pinned gcc.

So this is likely a quick WALL. But I must try ≥ 20 min and ≥ 30 scored tries before recording a WALL. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need to actually run 30 scored tries. That's the cost. Let me first get the baseline and understand.

Wait — but note the header also says this barrier is "NEEDED DIFFERS (P36 rung B t8_tus2)". Let me copy orig.c and check the baseline score.

Also important: the function's comment says "MATCH, 343/343". So orig scores 0.

Let me set up and try real-C replacements for the memory clobber:
1. Remove it entirely (baseline).
2. Replace `idx = p->unkA; dsp = sv[idx];` with a direct load `dsp = *(u8*)(sv + idx)`.
3. Use a volatile load for idx: `idx = *(volatile u16 *)(p + 0xA);`
4. Use a volatile read of sv.
5. Reorder: put the load of dsp after a store.
6. etc.

Let me extract orig.c first and score it.
