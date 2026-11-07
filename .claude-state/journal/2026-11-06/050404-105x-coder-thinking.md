---
ts: 2026-11-06T12:04:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ye4Wtor6D7dONDLzbyKz
---
The sibling's notes confirm: "only the memory clobber works" and real-C attempts don't hold it. Best 2. So item 4 is the same WALL.

I'm confident. But I need to spend ~20 min on item 4. It's 05:04. Item 4 started ~04:56. 8 min. Let me do a few more genuine attempts (the sibling tried do-while around the store, etc.). Let me try the dead-init and a couple of others, then finalize at ~05:16.

Actually, let me reconsider: the sibling tried many real-C attempts (do-while around store, etc.) and concluded only the memory clobber works. I've confirmed the same. I've done ~34 tries. Let me do a few more (dead-init, tail reorder) to be thorough and consume time, then write up.

Let me test:
- v_dead_init_mid: `s32 zz = 0;` unused in the middle block.
- v_tail_temp: use temps for the tail values (init at decl).
- v_store_twice: store v twice (dead first)? No, extra insn.

Let me test the dead-init and tail-temp variants.

Actually, the sibling's conclusion is strong. Let me just do 2-3 more and then write up. The 20-min requirement: I'll be at ~10-12 min. Hmm. Let me spend more time genuinely.

Let me try a fundamentally different approach to the store sink: what if I reorder the v computation so the store's value is computed LATER (closer to the tail), changing the sched? E.g., compute v, then do the tail stores, then store v? No, target has store right after v.

Alternatively, what if I use the `s8 two` + do-while and ALSO restructure the tail to make the li a0 less hoistable. The li a0 is for func_8002D4C8(0x980, 0). What if I pass 0x980 as `(s32)(u16)0x980`? folds.

What if I make func_8002D4C8's first arg a variable computed from the struct? No.

Let me try: `func_8002D4C8(0x980, 0)` → `func_8002D4C8(2432, 0)` same.

Let me try splitting the call: `func_8002D4C8(0x900 + 0x80, 0)`? folds to 0x980.

Hmm.

Let me try making the store 0x10 use a different base variable, e.g., a local pointer `q = (u8*)a0; ... *(s32*)(q+0x10) = v;`. Maybe the sched treats it differently. Let me test.

Also: `CAST_WIDTH(s32, (u8*)a0, 0x10) = v;` → `*(s32*)((u8*)a0 + 0x10) = v;` (different spelling). Let me test.

Let me generate a batch:
- v_store_ptr: use a local pointer q for the store.
- v_store_spell: `*(s32*)((u8*)a0+0x10) = v;`
- v_dead_init: unused local init.
- v_tail_temps: temps for tail values.

Let me test.
