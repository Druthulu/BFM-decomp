---
ts: 2026-11-06T05:32:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yXe0cqdRkvoemMHKMLIG
---
No virtual stack refs in the RTL/lreg dumps. So the 16 extra vars come from reload (`alter_reg`) — a spill slot for a pseudo not allocated a reg. In lreg (before greg/reload), no stack. After reload, a spill slot appears. Since it's unused in the final asm, the pseudo must be dead after reload.

So the 16 bytes = one or more spill slots allocated by reload. To eliminate it in pure C, we'd need to reduce register pressure so the pseudo gets a reg. But the target achieves it only via the clobber changing the whole allocation.

Actually, wait: the clobber version has vars=24 (no spill) and 95 insns; the nobar has vars=40 (spill) and 89 insns. The clobber's memory clobber forces reloads (more insns) but also changes register pressure.

This looks like a WALL: `cse-store-forward` (the comparison value forwarded into the store) plus a reload spill artifact. But maybe the cse-forwarding is the primary and the frame follows.

Hmm, but actually — maybe there's a pure-C move that changes the register pressure and forces the reloads. The C0505 catalog moves (temps, decl order, widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse) are exactly for this kind of thing. Let me try many variants.

Key candidate ideas for item 1:
1. Reorder the arm stores (0x78,0x7a,0x7c order) → target order is 0x78=a0, 0x7a=a2, 0x7c=a4.
2. Compare using locals: `s32 av = *(s16*)(a+2); s32 bv = *(s16*)(b+2); if (av < bv)`.
3. Compare `*(u16*)` instead of `*(s16*)`.
4. Use `a[2]`/`b[2]` via u16 pointer.
5. Compute the comparison before `r5`/`r6`? No.
6. Reorder the two calls.
7. Move `if (r6==0) b[2]=0x7fff;` before/after.
8. `if ((r5|r6) != 0)` vs `if (r5 || r6)`.
9. Store the arms via a temp array copy.
10. Use `__builtin_memcpy` for the a stores too.
11. Change the decl order of a/b/out.
12. Use `u16` arrays instead of `u8` arrays? The arrays are u8[8] with s16 stores. Changing to `s16 a[4]` would change the code.
13. Assign `*(s16*)(a+2)` from the comparison into a variable and store it.
14. The else-arm: target stores b[0],b[2],b[4] and memcpy from D_801152A8.
15. Statement order inside the arms.
16. `*(u16*)(e+0x7e) &= 0xfffe;` vs `&= ~1`.
17. Use `!= 0` vs `> 0`.
18. Add a `s32` cast.

Let me also consider: the target reloads ALL THREE a values in the then-arm. In mine, a[0] and a[4] are already reloaded; only a[2] is forwarded. So the fix is specifically to block the a[2] forward.

Idea: make the comparison read a[2] *unsigned* and the store *signed*? Or make the store value come from a different mode. In mine, the comparison is `lh v0,18(sp)` (signed), and the store `sh a1,122(s0)` where a1 is the lh result. combine folded the HImode store to use the lh value. If the store expression were `*(u16*)(a+2)` (lhu) and the comparison `*(s16*)(a+2)` (lh), combine still uses the register (low 16 bits same). 

What if the store expression is `*(s16*)(a+2) + 0`? Still.

What if the store is `*(s16*)(e+0x7a) = *(u16*)(a+2) & 0xffff;`? The `& 0xffff` would force a zero-extend (andi) — extra insn.

Hmm. What if the comparison uses the *value from e* instead of the stack array? No, target loads from stack.

What if the comparison is done *after* the arm's first store? Statement order: e.g., 
```
if ((r5|r6) != 0) {
    if (*(s16*)(a+2) < *(s16*)(b+2)) { ... }
```
Same.

What if we make the condition read `b[2]` first: `if (*(s16*)(b+2) > *(s16*)(a+2))`? Might change reg allocation.

What if we use a temporary for the comparison *difference*: `if (*(s16*)(a+2) - *(s16*)(b+2) < 0)`. That emits subu+slti or slt; different code.

Honestly, the cse-forward is hard to block. But let me try ~30 variants.

Also note: the frame difference (vars 40 vs 24) is a separate artifact. If the cse-forward is fixed, the frame might also fix. Or not.

Given the difficulty, this item is likely a WALL too (`cse-store-forward` or a reload-spill wall). Let me try candidates and see.

Let me write a generator for item 1 with ~30 variants.

Actually, let me first check what the best possible is: maybe a variant that reduces the insn count. Let me try a few quick textual variants and see if any gets below 22.

Let me write gen.py for item 1.
