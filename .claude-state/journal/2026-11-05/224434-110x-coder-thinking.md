---
ts: 2026-11-06T05:44:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xt3gHcxCbanXoN0JWHCl
---
Item 1 done. Time check: let me record `date`. Started 22:09. Now probably ~23:05. Item 1 took ~35 min (a bit over budget but it cracked).

Now the family: func_80175820, func_801758FC, func_801759D8. They're nearly identical. The barrier here is the memory clobber in the middle; known wall `cse-fixed-global-cache`. But now I have a fresh idea from item 1: change the *types/expressions* to alter cse. Maybe there's a similar trick.

The family body:
```c
u8 *p = (u8 *)&D_8011F7A8;
u16 *q;
u32 *ptr;
u32 old;
u32 *p2;
q = (u16 *)&(*(u16 *)&D_800B9A02);
ptr = D_800AE7BC[*q].f0;
old = ptr[2];
ptr[2] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x20) & 0xffffff);
__asm__("" ::: "memory");
p2 = *(u32 **)(p + *q * 4 + 0x18);
*p2 = (*p2 & 0xff000000) | (old & 0xffffff);
{
    s32 acc = D_800AF634[*q].g0;
    s32 t = *(s32 *)(p + *q * 4 + 0x18) - 0x14;
    D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x20) - t) >> 2);
}
return 0;
```

The target (with clobber):
- reloads `*q` after the store: `lhu v0,0(a2)` at 3d24 and 3d54.
- frame vars=16 (unused).

The lever-free version:
- caches `*q` across the store (uses a0 computed before).
- frame 0.

The `cse-fixed-global-cache` wall: cse keeps the global scalar load across a nonscalar store (PLUS address).

Idea from the cse code: the store `ptr[2] = ...` is `(mem:SI (plus (reg ptr) 8))` → nonscalar, not all. If the *load* `*q` were not scalar (e.g., MEM_IN_STRUCT_P or a PLUS address), it would be invalidated by the nonscalar store! Let me check `invalidate_memory`: for nonscalar, it invalidates all refs that are NOT scalar. A "scalar variable" is a mem ref with a non-varying address (fixed) or...? Let me read `invalidate_memory`.

Actually the comment: "writing in a structure element at variable address invalidates all but scalar variables". A scalar variable = a memory ref whose address doesn't vary (fixed address) AND mode != QImode? Let me read the code.

`*q` = `(mem:HI (reg q))` where q holds the constant address of D_800B9A02. `cse_rtx_addr_varies_p` — the address is a REG (pseudo holding a constant) — does it "vary"? Let me check cse_rtx_addr_varies_p: it returns true if the address contains a register that isn't a fixed reg? Hmm. In the target, the load is `lhu v0,0(a2)` where a2 = &D_800B9A02 (a pseudo holding a constant symbol address). cse may know the address is constant via REG_EQUIV.

Let me read `invalidate_memory` to see how it classifies.
