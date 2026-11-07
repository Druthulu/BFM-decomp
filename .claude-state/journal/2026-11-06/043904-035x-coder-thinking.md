---
ts: 2026-11-06T11:39:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dMvbMDFsFRTpUtNA7g6c
---
All 30 score 81. Source order doesn't matter — sched1 always produces the same schedule. So this is a solid WALL: `global-hardreg-reserve` — the pins reserve v0-v1 (and a0-a3) so lever-free sched1 hoists Blk8#1 above the group A stores.

That's 30 scored tries + the earlier ones. Time spent ~8 min, but the requirement is ≥20 min AND ≥30 tries. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need 20 minutes too. Let me continue exploring for a few more minutes with real-C attempts that could create a dependency.

Ideas with real C dependencies:
1. Make the Blk8 copy's source address depend on a loaded value in a non-launder way. E.g., use a pointer variable:
```
s32 *src = &D_80120210;   // address-of in a var
```
But then the address is computed into a pseudo and the code would differ (target uses lui/addiu inline). Actually target does use lui a1; addiu a1,a1,0 for the address, so a pointer variable could match! Target:
```
lui a1,0x0
addiu a1,a1,0
```
That's &D_80120210 in a1. And `lui a0; addiu a0,0` = &D_80126960 in a0. So the addresses ARE in registers a1 and a0 — consistent with pointer variables or the compiler's choice for BLKmode copy (which needs the address in a register).

So the original might have used pointer variables! And that could create dependencies.

What if:
```
Blk8 *d = &D_80126960;
Blk8 *s = (Blk8 *)&D_80120210;
...
```
No dependency on the stores though.

2. What if the group A values are stored via a pointer that aliases? No.

3. What if the Blk8 destination is a field of a struct that also contains D_80126950? E.g.:
```
struct { s32 a,b,c,d; Blk8 e; Blk8 f; u16 ... } *p = &D_80126950;
```
Then `p->e = *(Blk8*)&D_80120210;` — the compiler sees p->a etc. stores, and p->e is a different field, so no aliasing (different offsets). Still no dep.

But if the copy were `p->e = *(Blk8*)&p->a;`... no.

4. What if the source of the Blk8 copy is D_80120210 which overlaps with the group A source? No.

Hmm, what creates a real dependency? The Blk8 copy must depend on the group A stores or the group A loads.

Real C: `D_80126960 = *(Blk8*)&D_80120210;` — no dep.

If the original used `memcpy(&D_80126960, &D_80120210, 8)` → call.

What if the original was:
```
r2 = *(s32*)&D_80120210; ... 
```
i.e., the Blk8 copy data flows through r2/r3, which are also the group A temps. Then the copy's lwl would write v0 (=r2 pinned) creating a dependency with the group A stores (which read v0). THAT's the dependency! In the pinned version, r2=v0, r3=v1 are read by the stores then overwritten by the Blk8 copy loads — a WAR dependency forcing the copy after the stores.

But how would C express an 8-byte struct copy through the s32 temps? Maybe:
```
union { Blk8 b; s32 w[2]; } u;
u.b = *(Blk8*)&D_80120210;
D_80126960 = u.b;
```
That would go through memory, not registers.

Or the original might be:
```
r2 = *(s32*)&D_80120210;   // lw (aligned assumption)
```
No lwl.

Hmm, what if the original wrote the struct copy as `D_80126960 = *(Blk8*)&D_80120210;` and the compiler's BLKmode move uses 2 registers that happen to be v0,v1. Then the dependency exists in the pinned version only because r2/r3 are pinned to v0/v1. Without pins, the BLKmode move's registers are chosen later, and sched1 has no dependency, so it hoists.

Therefore the dependency is purely from the pins. This IS the `global-hardreg-reserve` wall.

To confirm, I could look at the RTL dump of both orig and w1 to show the schedule. Let me do a quick cc1 dump using hdump.sh for the header item, comparing orig and w1 — evidence for the log.

Actually, evidence ≤140 chars: "gcc sched1: lever-free Blk8#1 lwl chain priority 4 > 4-lw group's 2, hoists above the 4 sw; pins r2/r3=$v0/$v1 make the copy's v0/v1 a WAR dep after them".

That's the mechanism. Let me verify with a dump that Blk8#1 is hoisted in w1 and not in orig. The target asm already shows orig keeps it after; w1 shows it hoisted. That's direct evidence from the disassembly, no need for dumps.

Actually wait — the target asm is from orig.c (which scored 0). And w1.s shows the hoist. So the evidence is clear.

But hold on: is it possible that the hoist is in cse1 rather than sched1? Let me check the pass order. In gcc 2.7.2, does cse1 reorder? cse doesn't reorder instructions, it replaces/substitutes. sched1 reorders. So sched1.

Let me verify by looking at the RTL dumps? Could be useful to name the pass correctly. Let me do hdump for orig and w1 and compare the sched1 output. hdump.sh needs an includer TU and header basename. For a header item, the includers come from the oracle. Let me find an includer of func_8012A1BC.h.

Let me use tryinc.py? That's for scoring includers. For hdump I need a TU path that includes the header. Let me grep.

Actually simpler: `grep -rl 'func_8012A1BC.h' src/` might be large. Let me use pa_ext ask? No, simple grep is fine but could be slow. Let me grep in src/ov_*.

Actually, the time constraint: I need 20 min on item 1. It's 04:40 now, started 04:32. Let me spend a few more minutes on evidence dumps.

Let me find an includer.
