---
ts: 2026-11-06T11:58:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jEAkmbR2BrH9FoQP2g2h
---
Mine:
- lw v1,32(s0) (p in v1)
- li v0,2 (two in v0)
...
- li a0,2432 (insn 29)
- sw v0,16(s0) (insn 30)  <- target has sw at 29, li a0 at 30
- lui v0,0x20 (31)
- sw v0,20(s0) (32)
...

So two issues confirmed: the p/two register swap, and the sw/li order.

For the sw/li order: target has sw BEFORE li a0. Mine has li a0 BEFORE sw. This is the scheduler order. The barrier prevented moving the store after the li. 

Hmm, actually the `li a0,2432` is the argument setup for the LAST call func_8002D4C8(0x980, 0). It's scheduled early. The target keeps it after the sw. Without the barrier, sched moves the li before the sw.

Real C: maybe reorder the statements so the store is naturally before the li. But the li is for the final call, which is after all the stores. The scheduler hoisted it.

Let me think: the barrier at the end of the middle block is AFTER the `CAST_WIDTH(...,0x10) = v;`. So the barrier prevents sched from moving insns across it. Without it, the li a0 sinks up past the store. Hmm.

To fix in real C: I could add a dependence between the store and the li? The li a0=0x980 is independent of the store. 

Maybe reorder the source: move the `CAST_WIDTH(...,0x10) = v;` to AFTER the middle block (outside), closer to the other stores. But the target has it right after the v computation. Hmm.

Alternatively, put the store in a `do{}while(0)` — tested (v_store_dw = 8, no change).

Let me focus on the register swap first, since it's 6 mismatches (the bigger driver).

The swap: p in v1, two in v0 (mine) vs p in v0, two in v1 (target).

Idea: make p's pseudo born EARLIER or give it higher priority. p is already born first (lw at insn 4). But local-alloc gave two v0. 

Wait — maybe local-alloc allocates in order of pseudo REGNO, and `two` has a lower regno than p? In the source, `p` is declared before `two`. But after the pin removal, the declarations are `s32 *p; s32 two;`. p declared first → lower regno → allocated first → v0. But mine gives two v0. Contradiction.

Hmm, unless the assignment order matters: `p = ...; two = 2;`. p's def is first. 

Let me look at local-alloc's ordering. Actually, maybe the issue is that `two` is a constant and gets a "quantity" with a REG_EQUAL note, and local-alloc treats constants specially (they're cheap to rematerialize). 

Alternatively, maybe the swap is because gcc's reload/global-alloc, not local-alloc. But this is a leaf-ish function (calls, but no loop). The registers v0/v1 are caller-saved, allocated by local-alloc within basic blocks.

Let me try: make `two` a variable that's NOT a simple constant, so it doesn't get a REG_EQUAL. E.g., `two = 2; ` but read it twice? Or `two = 2; two = two;`? identity.

Or: `two = 2; ... unk2 = two; ... two` used again? No.

Hmm. Let me try making `two` a `u16` with a cast: `two = (u16)2;` folds.

Let me try reordering the declarations and assignments:
- v_decl_two_first: declare two before p.
- v_assign_two_first: two = 2 before p = ...
- v_p_last: assign p after two.

Let me also try: `p` as a different type (u8*) — might change allocation.

Let me generate a batch:
1. v_two_first_decl: `s32 two; s32 *p;` (two declared first)
2. v_two_first_assign: `two = 2; p = ...;`
3. v_p_u8: `u8 *p;`
4. v_p_s32_reorder: move the p assignment after the unk2 store.

Let me test.

Also for the store: try moving the 0x10 store to before the v computation? No, v depends.

Let me test the register variants.
