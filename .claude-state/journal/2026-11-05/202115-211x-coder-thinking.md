---
ts: 2026-11-06T03:21:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HkGLD51tAWFq56xj3D5L
---
`Sub20_1CDC` has `u8 pad0[0x14]; u16 unk14;` at 0x14 — a struct with a u16 field at 0x14. I can cast obj to `Sub20_1CDC *` and access `unk14`. That makes the store MEM_IN_STRUCT.

The computation: `*(u16*)(obj+0x14) = *(u16*)(obj+0x14) + (unk2A - D_80126B78[0x12])`.

Try: 
```
Sub20_1CDC *o = (Sub20_1CDC *)obj;
o->unk14 = o->unk14 + (((Unk*)a0)->unk2A - *(u16*)((u8*)D_80126B78 + 0x12));
```
This changes the store/load to MEM_IN_STRUCT. The codegen should be the same (sh/lhu 20(a1)), but cse's alias analysis may now invalidate the global across the store → the second D_80126B78 load is re-emitted.

Let me test this. Also try using a struct type with the field at 0x14 as u16 (Sub20_1CDC).

Also, the reload must happen for the *second* use (the unk2A store). Let me test.

Also note: the target's first global load is at 52b4 (after the call), and mine's is early. With the struct store, cse invalidates after the store, so the second load is re-emitted. But the first load's position: mine loads early (18-20) because the compiler hoisted it above the call? Hmm, the target loads it after the call at 52b4. Mine's early load at 18-20 is before the call? Let me look at mine's asm. Actually the diff showed mine's insns 18-20 (lui a2; lw a2; lhu v1,42(s0)) deleted relative to target. Those are before the call? The call is at ~5288 in the target = insn ~? Let me not worry; the struct-store change may fix the reload and the positions.

Let me test the struct-store variant.
