---
ts: 2026-11-06T11:59:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hIWoY7iyxGAftcceN9TE
---
Target: after `lw s2,32(s3)` and `lw s0,52(s3)` (obj, ent), the address `lui a1; addiu a1` is materialized and the 8 loads follow.

Mine hoists the address before the obj/ent loads. Hmm.

The address computation is a CONST (D_800AE620). With the pin $5, the pseudo is in a1. sched1 orders it... The address insns (lui/addiu) have priority 1; the loads from s3 also 1. Tie → LUID. In target the address's LUID is after obj/ent; in mine the address LUID is earlier? The source order is: obj, ent, then the block. So the LUID of the address should be after both loads. But sched1 moved it up.

Why? Because the loads `lw s2,32(s3)` etc. depend on s3 (arg0 moved in the prologue) — the prologue's `move s3,a0` is at the block start and sched1 keeps parameter copies unscheduled. The address (lui/addiu) has no dependencies and may be launched early.

In the target, the address is also independent but is scheduled after the two loads — because with the barriers, the block boundaries prevented it? The first barrier is after `obj = ...`, the second after `ent = ...`. With barriers, the address insns (in the third EBB) can't move above.

So the barrier is what keeps the address after obj/ent. Removing it (p2) hoists the address.

Real C to fix: make the address computation depend on the loads? E.g. compute the pointer via an expression involving arg0? Like `Blk20 *s = (Blk20 *)((u8 *)&D_800AE620 + (arg0 & 0));` — fake identity, not allowed.

Alternatively reorder the source: put the Blk20 block after `ang = ...` (p2a) — didn't help (still 8). Because sched1 hoists regardless of source position (it's independent).

Hmm, but the hoist is *to the top of the block*, above the obj/ent loads. If the obj/ent loads had a dependency... 

What if obj and ent are loaded via a temp in a way that gives them higher priority? E.g. `s32 obj = ((...)arg0)->unk20;` init at decl (declaration order/init at decl is a real C move). Hmm, priority is 1 for both.

Alternatively: what if the address materialization is split so only the `lui` is hoisted? No.

OK, this item looks like another WALL, but let me reconsider: p2 = 8 with launders kept. A PARTIAL:launder needs 0. We're 8 away (2 clusters: the hoisted address, the missing nop).

The missing nop (target has one extra insn): target[53] nop before sh v0,14(s3). Mine fills it.

Given the difficulty, maybe there's a real-C move for the address hoist: use a *local copy* of the struct? No, that changes semantics (the function reads D_800AE620 twice; the target re-reads it, so it's not cached).

Wait, actually: what if the two Blk20 blocks read D_800AE620 twice (they do). The second block also materializes the address. In the target, the second block's address is in a1 too (or another reg).

Hmm.

Let me try a few more targeted moves:
- Make `s` a parameter-like temp: declare `Blk20 *sp_;` at the top, assign `sp_ = &D_800AE620;` right before the block, and use it inside without the pin? (p2c without the pin was 24.)
- Use `s32 *s = D_800AE620.w;`? D_800AE620 is `extern Blk20 D_800AE620;` — an array-like struct.

Alternatively, accept WALL for item 3 too? Let me check the tries count: item 3 scored: v0(1), v1(1), p1, p2 (2), p2a-d (4) = 8. Need ≥30 for a WALL. Hmm, that's a lot more.

Hmm, wait. Let me reconsider the item-3 situation: p2 = 8 (barriers gone, launders kept). Maybe the real crack is the other direction: keep barriers, remove launders = 69 — bad. So the launders are essential.

For a MATCH, both must go. v0/v1 = 75.

Let me look at why removing the launders explodes the code (110 vs 94). If I can replace the launder with real C (e.g. using a temp copy of the struct pointer), maybe.

The launder `__asm__("" : "=r"(s) : "0"(s))` forces s into a register and prevents the compiler from folding the address into each load's displacement. Without it, gcc emits `lui/addiu` per load? That would be 16 extra insns (8 loads × 2). Yes! 110-94 = 16 = 8×2. So without the launder, each `s->w[i]` load uses a fresh address materialization (lui+addiu) because the pinned register isn't kept (the pin alone didn't force it?).

Hmm, but the pin `register Blk20 *s __asm__("$5") = &D_800AE620;` should force s into a1... The pin is on the *variable declaration*; maybe without the launder, gcc substitutes the constant address into the loads (the register isn't needed) and the pin is ignored (as pins often are when the pseudo is substituted).

Real C fix: force s to be a real pointer variable, e.g.:
```
Blk20 *s = &D_800AE620;
```
and use `s->w[i]` — gcc may still fold since s is a constant. The launder prevented the substitution.

Real C alternative: make the address non-constant from the compiler's view — e.g. `Blk20 *s = &D_800AE620;` then `s = s;`? folded.

Hmm: what if we use a local copy of the struct? `Blk20 tmp = D_800AE620;` — that would emit 8 loads + 8 stores, not 16 loads/stores.

What about declaring `extern Blk20 D_800AE620;` as `extern Blk20 D_800AE620[1];`? Then `s = D_800AE620;` — array decays to a pointer constant; still foldable.

OK so the launder is hard to replace with plain C. That's a WALL tag: the launder forces a constant-address pointer into a register (otherwise cse/regalloc folds it into displacements).

Given the budget (item 3 ~15 min so far), and the WALL requires ≥30 tries, I should run a batch of ~20 more real-C variants. Let me do a systematic sweep of the p2 body (barriers gone, launders kept) and the v0 body (both gone):

For p2 (target: 0 = PARTIAL:launder):
- address hoist: try `s` declared at function scope with the pin and assigned before the block; try the block moved after vec/ang (done); try `ang` load moved before ent; try ent/obj loads reordered; try the second block's address (pinned $7) placement; try moving the `ang2 = ang + 0x200` statement; try `unk6/unkA/unkE` store order.

For v0 (target: MATCH): 
- try `Blk20 tmp` copy? no.
- try s as a function-scope variable used in both blocks (one address materialization? but target has two).

Let me generate ~24 p2 variants and ~8 v0 variants, score them all in one command (32 × ~4 s ≈ 2 min).

p2 variants (real-C moves):
1. obj/ent load order swapped.
2. ent before obj.
3. ang load before ent.
4. s block moved before ent (after obj).
5. s block moved to the very top (before obj/ent).
6. vec[0] moved before ang.
7. the three output stores (unk6/unkA/unkE) reordered.
8. ang2 = ang + 0x200 moved after the unkE store.
9. the second Blk20 block before the first? no.
10. declare `Blk20 *s5;` at function scope, assign in block.
11. `s32 t0,t1,t2` declared at function scope.
12. vec as s16[8] instead of u16[8].

Let me implement ~14 variants programmatically with text replacements on p2. Given p2's structure is known, I'll write gen6.py.

Actually, simpler: generate variants via a template with knobs:
- order of the three statements obj=, ent=, ang=, and the block
- vec init position
- decl of s/t0t1t2

Let me write it.
