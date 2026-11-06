---
ts: 2026-10-22T21:44:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GLJS9DjqOwR7J761YzVh
---
Target order: ..., sw ra, li v0,-64, sh zero,16, sh v0,18, lui a1, ...

Mine: li v0,-64, sw ra, sh zero,16, sh v0,18, ...

So it's purely the sw ra vs li swap.

Hmm — what determines sched2's pick between them? In the target, the barrier is present. The barrier insn sits between the prologue and the stores; sched2 can't move insns across it. So the li (born after the barrier) cannot be scheduled before the barrier, and sw ra (before it) cannot move after. Hence the target order is forced by the barrier's position.

In plain C there's no barrier. But maybe I can make the li be born *later* — i.e., after the store of zero. In C: `loc.a.raw[2] = -0x40;` after `loc.a.raw[0] = 0;` — already the case, and sched2 hoisted it.

To prevent hoisting of the li, the li must depend on something scheduled later. E.g. make the value a computed one: `*(s16 *)&loc.a.raw[2] = (s16)(iVar2 * 0 - 0x40);` folds.

What if the -0x40 store reads a variable that is set from a memory location? Adds a load.

Alternatively, accept the order and see whether the ROM might have had a different source order... The target's order is exactly: sw ra, li, sh zero, sh v0. If I could get sched2 to emit li, sh zero, sh v0 without moving sw ra... 

What if I make sw ra *not* movable by having a store before it that aliases? The prologue sw ra is emitted by the prologue expander at the top.

Hmm, here's a thought: sched2's tie-break `rank_for_schedule` prefers... in mine it picked li over sw ra. What if the two are not in the same "ready list" tie — e.g. if there were an insn between them that depends on sw ra... no.

What if the function's frame were larger/smaller? no.

OK — different approach: maybe make the FIRST statement a call? no.

Let me try the item-2 trick adapted: make the loc stores into a *declaration initializer* by declaring a small local array first:

```
s16 tmp[2] = {0, -0x40};
*(s32 *)&loc.a.raw[0] = *(s32 *)tmp;   // sw, not sh
```
No.

What about: `S16_SC02_005_8017F7CC loc;` then `*(s16*)&loc.a.raw[0] = 0;` — the initializer trick only applies to declarations.

New idea: **declare `loc` with an initializer for the first store only**:
```
S16_SC02_005_8017F7CC loc = { {0, 0, 0xC0, 0xFF, 0, 0, 0, 0} };
```
byte stores → no.

Hmm, what about `s16 loc0 = 0;`? no.

Time check: 15:52. Item 3 at 11 min, 19 tries. Let me try 4-5 more (including a couple of wild ones) then WALL.

Wild ones:
d1: swap decl order: `s32 iVar2; S16_SC02_005_8017F7CC loc;`
d2: `*(s16 *)&loc.a.raw[2] = -0x40;` moved to just before the b copy (already) — same.
d3: use a `u8` cast: `*(u16 *)&loc.a.raw[2] = 0xFFC0;`
d4: make the b copy a separate statement first? (c4 = 11)
d5: `loc.a.raw[0] = 0;` + `loc.a.raw[2] = -0x40;`... no, raw[2] is a byte.
d6: hoist the `unk204` load before the stores: `iVar2 = ... - 1;` first, then stores, then the store back.

d6 might work: the `lw v0,516(s0)` is a memory op that comes before the li → could block the li's hoisting! In the target the lw is after the lwl/lwr copy. So moving it earlier changes asm. But maybe sched2 reorders... risky but cheap to test.

Let me test d1, d3, d6 and two more.
