---
ts: 2026-11-06T13:41:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CmGGUeliP3Gof0Dz4pl5
---
B1 cracked with several do-while placements: v1, v2, v3, v5 all score 0 with B1 removed (B2 still present). 

Now B2 (case 2: `CAST_ALIAS(u16, param_1, 0x34) = 3; unk1C = D_80188A18; [barrier] k = 0x1000; if (unk20 != 0) {...}`).

Let me apply the same pattern to B2 in the v1 body (do-while around the store). Let me look at the B2 source block:

```
            CAST_ALIAS(u16, param_1, 0x34) = 3;
            ((Unkstruct_800B5CB8 *)param_1)->unk1C = D_80188A18;
            __asm__ __volatile__("" ::: "memory");
            k = 0x1000;
            if (((Unkstruct_800B5CB8 *)param_1)->unk20 != 0) {
                ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk18 = k;
                ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk1A = k;
                *(u16 *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x1C) = k;
            }
```
Two stores before the barrier: CAST_ALIAS(u16, param_1, 0x34) = 3 (store to 0x34) and unk1C = D_80188A18 (store to 0x1C).

The diff for w_b2 (B2 removed, B1 present) showed:
```
197  bne v1,v0,3300 | bne v1,v0,3308
198  move v1,zero    | --
203  lw a0,32(s0)    | nop
204  --              | sw v0,28(s0)
205  --              | lw v0,32(s0)
206  --              | nop
207  --              | beqz v0,3214
...
```
Hmm, that was the earlier both-removed diff. Let me get the w_b2 diff specifically.

Actually let me first combine: take v1 (B1 fixed with do-while around the store) and apply the same to B2. Let me look at what B2's target order is. Let me view the target around 0x3200-0x3230 (from the earlier diff indices 203-210).

Let me dump the diff for w_b2 first.
