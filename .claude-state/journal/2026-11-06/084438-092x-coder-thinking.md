---
ts: 2026-11-06T15:44:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xE3tHwMsrvWC3YF4wrNl
---
The diff shows:
- orig: `lw $2,D_80126950; nop; addu $2,$2,500; mult $6,$2` and the `#APP/#NO_APP` (the asm).
- a1: `lw $3,D_80126950; nop; addu $3,$3,500` placed earlier, `mult $6,$3`.

So with the asm, the constant goes to $2; without, $3. And the placement differs.

Interesting: the asm block sits between the n addiu and the constant load. Since sched1 can't move insns across... hmm, actually ASM insns are treated as schedulable but not movable? The placement difference: in a1 the constant load chain is hoisted *before* the asm position (into the mflo delay region); in orig the asm's presence constrains.

Since the real-C body can't have the asm, I need to change the register allocation (constant in $2 vs $3) and the schedule.

$2 = v0, $3 = v1. The constant temp is an anonymous pseudo (the result of `D_80126950 + 0x1F4`). Its allocation: v0 vs v1.

What if I make it a named variable and control its position? f1 (temp c) gave 9. Hmm.

What if the launder's second set of n makes n "born" at the asm, so the allocator gives the constant pseudo $2 instead of $3? Local-alloc priorities.

Let me look at the .lreg dump to see the pseudo numbers and allocations for both. Compare the local-alloc tables.

Actually, maybe a simpler idea: the asm's output on n ($6 pinned) makes the addiu `n = q+8` a *dead* set (n is redefined by the asm), so the addiu's destination is... hmm, the asm's input is the addiu's output, so it's live.

Wait, actually the asm consumes n and redefines it. In the final code the asm emits nothing. But for the allocator, n has 2 sets.

The register difference $2 vs $3: v0 is special (it's the function-return/first temp). Local-alloc gives $2 to a pseudo... The constant temp is a local pseudo; in orig it gets $2, in a1 $3.

What C change would make the constant temp get $2? Perhaps the *order* of the two multiplications. In mine, the `mult v0,s1` (e*sc) at 888 has its result in v0 then mflo t0, sra v0, addiu a2. Then the constant chain. The constant temp could take $2 after v0 dies.

Let me look at the lreg dumps for the pseudo allocations. Actually, let me try a different tack: since the asm acts as a scheduler barrier, maybe a `do{}while(0)` block can replicate the ordering. E.g., wrap `n = q + 8;` in a do-while, or wrap the `d = ...` line.

The asm sits between `n = q+8` and `d = ...`. sched1 schedules each basic block separately! A do-while(0) around `n = q + 8;` would split the block → the addiu goes in its own block and the d computation in another. That could reproduce the ordering.

But careful: splitting blocks affects the whole region. Let's test:
g1: `do { n = q + 8; } while (0);` before d.
g2: `do { d = n * (D_80126950 + 0x1F4) / (ret * 4); } while (0);`
g3: `{ n = q + 8; }` plain block — no effect.
g4: `n = q + 8; { s32 nn = n; d = nn * (...) / ...; }` — copy.

Also g5: the dead-reset of n after d? n is used in d only, so after d `n = 0;` is dead — doesn't help the scheduling.

Hmm, what about making n's addiu and the mult in different blocks via a do-while around the whole `d` computation:
```
do {
    d = n * (D_80126950 + 0x1F4) / (ret * 4);
} while (0);
```
The block boundary before it would force sched1 to finish the previous block (containing n=q+8) before scheduling d's block. That matches the asm's barrier role!

Let me test g1 and g2.
