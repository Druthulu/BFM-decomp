---
ts: 2026-10-22T09:37:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_RDUZpvYPdq6Xd3cl3tv9
---
Now let me write a variant generator + batch scorer. I'll write a Python script `gen.py` under the item dir that creates variants from the base with textual replacements, and a scorer script that scores a list of files.

Scorer: reuse bin/sc.sh (one line per candidate) — it loops over files and prints "name: score N (...)". Let me write my own to also capture the diff for the best. sc.sh is fine for scanning.

Let me write the variants for item 80184828.

Variants (each with a set of (old,new) text replacements on the base):

1. v_a: `D_80195AF6_t *p = D_80195AF6;` → `u8 *p = (u8 *)D_80195AF6;` and `((u8 *)p + off + 4)` → `(p + off + 4)`
2. v_b: `((u8 *)p + off + 4)` → `((u8 *)p + (off + 4))`
3. v_c: `((u8 *)p + off + 4)` → `((u8 *)p + 4 + off)`
4. v_d: `s32 off;` → `u32 off;`
5. v_e: `off = ... * 8;` → `off = ... << 3;`
6. v_f: two statements: `u8 *pa = (u8 *)p + off;` before, and load `*(s16 *)(pa + 4)`
7. v_g: newval through p: `s16 newval = D_80195AF6[...].f0;` → `s16 newval = p[...].f0;`
8. v_h: p declared at top: `D_80195AF6_t *p;` in decls; in the arm: `p = D_80195AF6;`
9. v_i: `off` inline in the load: `off = ...;` removed and load uses `((Unkstruct_800B5CB8 *)a0)->unk100 * 8 + 4`
10. v_j: load via `*(s16 *)((u8 *)p + off + 4)` → `*(s16 *)((u8 *)p + off + 4)` with off as `s32` but declared after use? (decl order)
11. v_k: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` → `D_801270C8 = ((s16 *)((u8 *)p + off + 4))[0];` (same)
12. v_l: swap: `D_801270C8 = *(s16 *)((u8 *)off + (u32)(u8 *)p);` (hmm, (u8*)off is a pointer cast of an int — gcc may complain but it compiles)
13. v_m: p as `D_80195AF6_t *p = &D_80195AF6[0];`
14. v_n: the whole load as `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with `off` moved to the top of the function (decl order)
15. v_o: index scaled differently: `off = unk100 * 8` → `off = unk100 << 3` combined with u32 off.
16. v_p: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` → `D_801270C8 = *(s16 *)(p + off + 4);` (p is D_80195AF6_t* → pointer arithmetic with the struct type → off would be scaled by sizeof(struct)! changes semantics unless the struct is 1 byte. Hmm, D_80195AF6_t's size — from the asm, the element stride is 8 (off = unk100*8 explicitly) but the newval access is at byte offset unk100 → so sizeof(D_80195AF6_t) == 1?? That seems odd but possible (a struct with a single char?). Hmm, actually maybe D_80195AF6_t is a union/struct of size 1? Let me check the header.

Let me check the type D_80195AF6_t in the shared header to know its size. That informs the semantics.

Let me grep.
