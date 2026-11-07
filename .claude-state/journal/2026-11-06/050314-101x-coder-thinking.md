---
ts: 2026-11-06T12:03:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wj7BqehcJ1BrVRQf5MSY
---
p2 (barrier removed, launders kept) = 4, single cluster: the address `addiu sp,16` (f.cx address) is materialized in a register v0 and moved around, vs target uses `addiu a1,sp,16` and `addiu a0,sp,16` directly.

Mine:
```
18: addiu v0,sp,16
20: move a2,v0
25: move a1,v0
```
Target:
```
19: addiu a1,sp,16
21: move a2,a1
```
and later `addiu a0,sp,16`.

So mine materializes the address into v0 once and copies; target materializes twice (a1 and a0).

The launder `__asm__("" : "=r"(va) : "0"(va))` is kept in p2 — it forces va into a register. Target: va = a1? and vb = a2.

Hmm, the difference: mine's `addiu v0,sp,16` + moves vs target's `addiu a1,sp,16`.

This looks like a local-alloc/regalloc choice: the address pseudo is v0 vs a1. Real C moves: declaration order, using `&f.cx` directly, temps.

Let me try a few variants on p2:
1. drop the `va` temp: `f.cy = arg2; vb = (u8*)&f.cx;` etc.
2. use `&f.cx` directly in the call: `func_80149350(node, &f.cx, &f.cx)`.
3. reorder: va/vb assignments.
4. declare va/vb at function scope.

Note: with launders kept, the asm outputs force va/vb into regs. The p2 body has:
```
    va = (u8 *)&f.cx;
    __asm__ __volatile__("" : "=r"(va) : "0"(va));
    f.cy = arg2;
    vb = va;
    __asm__ __volatile__("" : "=r"(vb) : "0"(vb));
```
So va is laundered (new pseudo) and vb = va laundered.

Target: a1 = &f.cx (va), a2 = va (vb).

Mine: v0 = &f.cx, a2 = v0, a1 = v0.

Try: remove the `vb = va` copy and use `vb = (u8*)&f.cx;`? That changes the copy structure.

Let me test 6 variants quickly.

Also for a full MATCH: v0 = 18 (both gone, 159 ins). The main cluster there is a bigger reordering (s2/lui/li) — the prologue.

Priority: get p2 from 4 → 0 for PARTIAL:launder.

Variants on p2:
a. `vb = (u8 *)&f.cx;` instead of `vb = va;`
b. va/vb declared at function scope (not in the body? they already are: `u8 *va; u8 *vb;` declared at the top).
c. Move `f.cy = arg2;` before `va = ...`.
d. Drop the `va` temp entirely: call with `&f.cx`.
e. Use `vb = va;` but with the launder before f.cy.
f. reorder decls va/vb.

Let me generate and score.
