---
ts: 2026-11-06T13:41:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3Y5nzfhYdplTbAG28dvO
---
B2's block: two stores before the barrier:
```
CAST_ALIAS(u16, param_1, 0x34) = 3;     // sh 3,52(s0)
((Unkstruct_800B5CB8 *)param_1)->unk1C = D_80188A18;  // sw v0,28(s0)
[barrier]
k = 0x1000;
if (unk20 != 0) { ... }
```
The diff (w_b2) at index 204: target has `nop; sw v0,28(s0); lw v0,32(s0); nop; beqz...` vs mine `lw a0,32(s0); ...; sw v0,28(s0)`.

So mine sinks the `sw v0,28(s0)` (unk1C = D_80188A18) below the unk20 load; target keeps it before. Same pattern as B1 — a store sinking below a load.

And the `move v1,zero` at 198: mine has it in the bne delay slot, target doesn't. That's the `k = 0x1000`?? No, v1=0. Hmm, `move v1,zero` could be the value of D_80188A18? No, that's a load.

Wait, maybe the `move v1,zero` is from case 3's `unk34 = 0`? Index 198 is in case 2's region though.

Let me look at the target disassembly around 0x32f0-0x3310 to understand.

Actually, let me take the practical route: apply the do-while fix to B2's block (like B1 v1: wrap the first store, or the whole store group) and test. Since B1 needed a do-while around the store to prevent the sink, B2 likely needs the same around the two stores.

Combined body: B1 fixed with `do { unk34 = 2; } while (0);` and B2 fixed with `do { CAST_ALIAS(...)=3; unk1C = D_80188A18; } while (0);`.

Let me generate several B2 placements on top of the B1-fixed body:
- w_c1: B1 v1 + B2 do-while around both stores.
- w_c2: B1 v1 + B2 do-while around the CAST_ALIAS store only.
- w_c3: B1 v1 + B2 do-while around unk1C only.
- w_c4: B1 v1 + B2 do-while around stores + k.
- w_c5: B1 v1 + B2 do-while around the if.

Let me write the generator carefully: start from w_b1_v1_dw_store.c (B1 fixed, B2 present) and replace B2's block.
