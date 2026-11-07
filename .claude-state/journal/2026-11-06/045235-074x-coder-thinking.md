---
ts: 2026-11-06T11:52:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2vybN307hZaTWATGrXh6
---
p1 residual: the else branch's registers a0/a2 are swapped (m24 in a0 vs a2, mFF in a2 vs a0), plus one lw position. All in the else branch. That's exactly what the launder affected.

Target else branch:
```
3fa0: lui a2,0xff; ori a2,a2,0xffff     (m24 in a2)
3fa8: lui a0,0; lhu a0,0(a0)            (D_800B9A02)
3fb0: lw v1,0(t1)                       (pv = *p)
3fb4: sll v0,a0,2 ...
3fcc: lui a0,0xff00                     (mFF in a0)
3fd0: lw v0,0(v0)
3fd4: and v1,v1,a0
3fd8: and v0,v0,a2
...
```
Mine (p1):
```
lui a0,0xff; ori a0 (m24 in a0)
lui v1; lhu v1
lui a2,0xff00 (mFF in a2)
...
lw v1,0(t1) later
```
So mine has m24 in a0, mFF in a2; target m24 in a2, mFF in a0. Also mine keeps D_800B9A02's lhu in v1, target in a0.

In the target, pv is pinned to $3 (v1) in the else branch. Wait, pin $3 = v1. In target's else: `lw v1,0(t1)` = pv; then `and v1,v1,a0`; ... `sw v1,0(t1)`. Yes pv=v1.

Mine p1: `lw v1,0(t1)` too. Good. The difference is which register holds m24 and mFF.

Why? The launder `__asm__ __volatile__("" : "=r"(pv));` after the tag store forces pv to be live/defined there, affecting the register allocation of the two masks.

Real C moves to try for the else branch:
- reorder declarations of m24/mFF
- swap the statement order in the else
- write m24 as a literal inline instead of a variable (0x00FFFFFF) — target materializes `lui a2,0xff; ori a2,a2,0xffff` = 0x00FFFFFF in a2, so it's a variable.
- use `u32 mFF = 0xFF000000; u32 m24 = 0x00FFFFFF;` order swap.

Also the `ot` variable and the order of `ot = ...; *ot = ...`.

Let me try a sweep on p1 (barriers kept, launder gone):
1. swap m24/mFF decl order in the else block.
2. m24/mFF declared in the if branch too? They're separate in both branches.
3. in the else, reorder: `ot = ...; *ot = ...` before `*(u32*)p = ...`.
4. `pv` used for both: `u32 *ot = (u32 *)D_800AE7BC[...].a; pv = *p; *p = (pv & 0xFF000000) | (*ot & m24); *ot = (*ot & 0xFF000000) | ((u32)p & m24);`
5. widths: u32 vs s32.

But careful: the else branch has the pin `register u32 pv __asm__("$3")`. Keep it.

Let me look at the full else-branch source and generate variants.

Target else-branch code:
```
3fa0 lui a2,0xff ; ori a2 -> m24 = 0x00FFFFFF in a2
3fa8 lui a0,D_800B9A02 ; lhu a0
3fb0 lw v1,0(t1)            pv
3fb4 sll v0,a0,2
3fb8 addu v0,v0,a0
3fbc sll v0,v0,2
3fc0 lui at,D_800AE7BC ; addu at,at,v0
3fc8 lw v0,0(at)
3fcc lui a0,0xff00          mFF
3fd0 lw v0,0(v0)            *ot
3fd4 and v1,v1,a0
3fd8 and v0,v0,a2
3fdc or v1,v1,v0
3fe0 sw v1,0(t1)
3fe4 lui v1,D_800B9A02 ; lhu v1
3fec nop
3ff0 sll v0,v1,2 ...
4004 lw v1,0(at)
4008 move a1,zero
400c lw v0,0(v1)
...
```
So `ot` is recomputed (a second lookup of D_800AE7BC[...].a) — the launder prevented cse from reusing the pointer, forcing a second load. Without the launder, cse may reuse. In p1, is `ot` recomputed? The diff only shows the mask registers, so yes it still recomputes.

Let me now try the variants. Write gen script for item 2 with ~16 candidates on the p1 base:
- swap m24/mFF decl order (in else, and in if)
- swap the two mask decl lines
- move `ot = ...` before the pv lines
- declare ot at the top of the else
- use `s32`/`u32` mixes
- inline the mask constants in one place

Let me first view the exact p1 else source to write variants.
