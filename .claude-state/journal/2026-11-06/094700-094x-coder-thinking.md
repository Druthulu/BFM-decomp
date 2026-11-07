---
ts: 2026-11-06T16:47:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WFoK4p32rYo9ObzayEDG
---
Target uses s0-s6 (7 callee-saved) + ra. Frame 128.

The registers in target:
- s1 = &sv0 (sp+0x28) — for RotTransSV
- s2 = &L.flag (sp+0x50) — RotTransPers arg a3
- s0 = fp (pinned) and also D_800AF648 address
- s3 = prim
- s4 = buf
- s5 = table? (s5 = D_8019E16C maybe)
- s6 = cbase? 

Mine (no_fp) uses s0 = ? and s7 extra.

This is a big allocation cascade. The fp pin is the cause of one register shift; the others follow.

Honestly, cracking this within budget seems unlikely. Let me try a few C moves on fp:
- fp declared `u8 *` instead of `s8 *`? The pointer arithmetic fp-0x1E etc. — with u8* same.
- fp = (s8*)prim + 0x22 vs fp = (s8*)(prim + 0x22)?
- Move the fp assignment before cbase/table assignments.
- Use fp only in the loop (it is).

The register allocation is priority-based: fp's priority = refs*size/life. Pinning s0 forces it. Without, it gets s3 or whatever. To make fp=s0 naturally, fp must be the highest-priority callee-saved candidate at the point s0 is allocated.

Given the size, let me estimate the chance. The 3-pin cascade has a full shift; each C tweak might just shift it differently.

Let me try a quick batch of fp variants with ot and t0c pinned, measuring the score (no_fp = 47). Variants:
f1: `u8 *fp;` (type change; but the expression `fp - 0x1E` etc. with u8* is fine; assignments `fp = (u8*)prim + 0x22;`)
f2: move `fp = ...` earlier (before table/cbase).
f3: `fp = (s8 *)(prim + 0x22);`
f4: declare fp in the loop's block instead of function scope? It's declared at function scope and used only in the loop block. Moving it into the block changes the pseudo's birth (expand_decl) — might change priority ordering.
f5: initialize fp at declaration inside the block: `s8 *fp = (s8 *)prim + 0x22;`

Also the loop variables: `s32 *table`, `s8 *cbase`, `s8 *fp`, `s32 i`. Order: table, cbase, fp, i (i is function-scope though).

Let me test f1..f5 with ot/t0c pinned. Build them from orig.c by replacing the fp pin line and possibly moving the assignment.

Let me write a small script that generates variants from orig.c with regex.

f1: replace `register s8 *fp __asm__("$16");` → `u8 *fp;` and `fp = (s8 *)prim + 0x22;` → `fp = (u8 *)prim + 0x22;` (cast uses of fp remain (s8*)... the stores use `*(s32 *)(fp - 0x1E)` — pointer arithmetic on u8* vs s8*: both scale by 1. OK.)
f2: move the fp assignment to before `table = ...`:
   `s8 *cbase; fp = (s8 *)prim + 0x22; table = D_8019E16C; cbase = ...`
f3: `fp = (s8 *)(prim + 0x22);`
f4: declare fp inside the block: remove the function-scope decl, add `s8 *fp;` in the block after cbase.
f5: `s8 *fp = (s8 *)prim + 0x22;` inside the block (declaration with init).

Let me generate and score.
