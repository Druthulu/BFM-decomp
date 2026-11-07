---
ts: 2026-11-06T05:47:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4UOOfterDCUHyNuiPKpL
---
Good. Now let me write the family generator. For each item, the orig body is:
```
/* header comment */
s32 func_XXXX(void)
{
    extern s16 D_800B9A02;
    extern S_AE7BC_XXX D_800AE7BC[];
    extern S_AF634_XXX D_800AF634[];
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u16 *q;
    u32 *ptr;
    u32 old;
    u32 *p2;
    q = (u16 *)&(*(u16 *)&D_800B9A02);
    ptr = D_800AE7BC[*q].f0;
    old = ptr[K];
    ptr[K] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + OFF1) & 0xffffff);
    __asm__("" ::: "memory");  // barrier
    p2 = *(u32 **)(p + *q * 4 + OFF2);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + OFF2) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + OFF1) - t) >> 2);
    }
    return 0;
}
```
(For 759D8 there's an extra early `if (D_8011F7B1 != 0) return;` and extern u8 D_8011F7B1.)

The nobar is this minus the asm line.

Candidates (real-C moves):
1. struct-member load: replace `q = (u16 *)&(*(u16 *)&D_800B9A02);` with a struct pointer and use `sq->v` for all `*q` occurrences.
2. recompute q after the store.
3. q as `s16 *`.
4. Use a local `s32 idx = *q;` and `idx` for all uses.
5. Use `p + idx * 4` variants.
6. Reorder: put the acc block before the p2 block.
7. Make the second use `*(u16*)&D_800B9A02` directly (a global read, not through q).
8. Make the second use through a *different* pointer variable q2.
9. Use `*(u16 *)((u8 *)&D_800B9A02)`.
10. Recompute `ptr` after the store.
11. Combine the acc block with p2.
12. Use `u32 *base = (u32*)(p + *q*4);` and index.
13. Store via `*(u32*)((u8*)ptr + K*4)`.
14. `old` as s32/u32.
15. `acc` as u32.
16. Reorder the `s32 acc` and `s32 t` declarations.
17. `t` as s32.
18. Use `>> 2` vs `/ 4`.
19. Replace `(*p2 & 0xff000000)` with `*p2 & 0xff000000` (same).
20. Use `|` vs `+`.

Let me focus on the struct-member idea first, as it's the most promising.

Struct-member load: 
```c
typedef struct { u16 v; } W;  // can't typedef inside a function? Yes, you can: `struct { u16 v; } *sq;`
```
We need a pointer to a struct with a u16 member at offset 0, pointing to D_800B9A02. Inside the function:
```c
struct S9 { u16 v; };
struct S9 *sq;
sq = (struct S9 *)&D_800B9A02;
...
ptr = D_800AE7BC[sq->v].f0;
...
p2 = *(u32 **)(p + sq->v * 4 + OFF2);
```
The load `sq->v` is a struct member → MEM_IN_STRUCT_P. Codegen: `sq` = &D_800B9A02 → `lhu v0,0(a2)`. Should match.

But careful: `sq->v * 4` — the multiplication. Same as `*q * 4`.

Let me write the variants. I'll generate from the orig text by replacing `*q` with `sq->v` and the q assignment.

Let me write a Python generator that reads orig.c, strips the asm, and applies transformations.

Actually, since the three items have slightly different texts, let me do it programmatically per item.

Let me write family_gen.py that takes the item dir and generates variants.
