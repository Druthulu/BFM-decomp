---
ts: 2026-11-06T10:21:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bKxsQ2N9yHfdpquVZTxX
---
Oops, I made all variants identical except p1-p5. That's sloppy. Let me rewrite the generator properly with distinct variants. Let me be efficient and write meaningful distinct variants.

Item 3 base structure:
```
    uVar2 = param_1;
    obj = func_801290DC(0x44, (u8 *)uVar2);
    if (obj != 0) {
        sub = *(s32 *)(obj + 0x20);
        ((Unkstruct_800B5CB8 *)sub)->unk20 = (s32)D_80193AAC;
        ((Unkstruct_800B5CB8 *)sub)->unk28 = 0x290;
        ((Unkstruct_800B5CB8 *)sub)->unk2A = 0x1A0;
        ((Unkstruct_800B5CB8 *)sub)->unk27 = 0x70;
        ((Unkstruct_800B5CB8 *)sub)->unk1A = 1;
        ((Unkstruct_800B5CB8 *)sub)->unk18 = 1;
        CAST_WIDTH(s32, (u8 *)sub, 0x4) |= 0x50000000;
        *(s32 *)(obj + 0x1C) = 1;
        w = param_2;
        *(s32 *)(obj + 0x2C) = w;
        chn = w;
        ((Unkstruct_800B5CB8 *)sub)->unk26 = chn;
        ((Unkstruct_800B5CB8 *)sub)->unk25 = chn;
        ((Unkstruct_800B5CB8 *)sub)->unk24 = chn;
    } else {
        rv = 0;
    }
```

Variants:
1. Use a pointer `q = (Unkstruct_800B5CB8 *)sub;` for the stores.
2. Remove `chn`: use w directly.
3. Remove `w`: use param_2.
4. Remove uVar2.
5. Reorder the unk20..unk18 stores.
6. Reorder the chn stores.
7. Move `w = param_2;` earlier (before the stores).
8. `*(s32 *)(obj + 0x1C) = 1;` before/after the CAST_WIDTH.
9. Decl order permutations.
10. `if (obj == 0) { rv = 0; } else { ... }`.
11. Split sub into a pointer.
12. Use `sub = *(s32 *)(obj + 0x20);` vs `sub = ((u8*)obj)[0x20]`? no.
13. chn as u16?
14. `w = param_2; chn = w;` merged: `chn = w = param_2;`
15. `*(s32 *)(obj + 0x2C) = param_2;`
16. Cast spellings.

Let me write this properly with a full-body replacement per variant. It's verbose but correct.

Let me define the full body as a template and substitute the block.

I'll write the file.
