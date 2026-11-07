---
ts: 2026-11-06T15:18:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H4HLQBZYlFCV2WRo8qml
---
h1: the do-while around the vol computation changed the schedule (score 16, 236 ins). The insertion shows target has an extra 4 insns in that region (mfhi t1, addiu, nop, mult) while mine has them later. So mine's vol mult is delayed.

Hmm. The do-while did something but not enough.

Let me now seriously consider that this is a WALL. But the brief wants a lever-free body that scores 0; PARTIAL keeps some levers. For launder-only items, a PARTIAL isn't possible (PARTIAL:<kept> means keeping some row kinds — but our only row kind is launder; PARTIAL would keep launder = WALL). So it's MATCH or WALL.

Before giving up, let me try the "real second set" ideas that keep the code identical: maybe the target's extra insn (the nop after addiu) is a hint: the target's `addiu v0,a2,160; nop; mult v0,a0` — the nop is a hazard barrier between addiu and mult? Actually MIPS I mult has a 1-cycle latency to hi/lo; the nop might be the "hazard" for mfhi. Hmm.

Let me try one more class: reorder the source statements so that sched1's ready list matches. The key difference in sched1: a0 launches 472 (vol mult) at T-9; b4 launches 484 (pan mult) at T-10 then 472 at T-22. Wait, b4's order (pan first in sched1) matches... and the final code (after sched2) is vol-first. a0's sched1 order is vol-first and the final is pan-first. So sched2 *reverses* sched1's order in both cases! Interesting: sched1 pan-first → final vol-first (target); sched1 vol-first → final pan-first.

So I need sched1 to put pan first (like b4). In b4, why? Because of the extra node 478 changing the ready list. 

What real C could make sched1 put 484 before 472 without an extra insn? The ready list order depends on the DAG and the insn uids. If the pan computation's nodes are *born earlier* (lower uid), they'd be ready earlier. The pan `addiu v0,a2,160` (481) is currently after the vol multiply chain (462-472). If the source computed the pan numerator (sx + 0xA0) earlier, its uid would be lower.

Idea: hoist `sx + 0xA0` into a variable computed before vol:
```
s32 p = sx + 0xA0;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = p / 0x14;
```
That gives p a separate pseudo (addiu into a new reg), then vol, then p/0x14. The addiu's uid is early → the pan mult may become ready earlier. But p is a new pseudo → maybe an extra register, and the addiu is the same insn. Insn count unchanged! Let's test (i1).

Also:
```
s32 p = sx + 0xA0;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
if ((sx = p / 0x14) == 0x10) sx = 0xF;
```
Hmm, careful with semantics.

Variant i2: 
```
s32 p = sx + 0xA0;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = p / 0x14;
```

Let me test i1/i2 and also the reverse: compute vol's numerator early:
```
s32 n = (0xA0 - av) * 0x7F;
sx = (sx + 0xA0) / 0x14;
vol = n / 0xA0;
```
That changes order/DAG. Test i3.

Also i4: keep vol's expression but compute the pan before:
```
sx = (sx + 0xA0) / 0x14;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
(g1) — let me include.

Let me run i1-i4.
