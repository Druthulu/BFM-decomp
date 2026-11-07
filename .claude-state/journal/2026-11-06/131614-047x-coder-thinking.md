---
ts: 2026-11-06T20:16:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2OgBdbXHHWagqdi3BPEm
---
Item 2 is much bigger: kinds=launder, and the row kinds are "launder" (only the trailing `__asm__ __volatile__("" : "=r"(pv));`). But the def also has TWO pins (`ang` $4, `pv` $3) that are NOT row kinds (they're pins — the brief says "levers of other kinds the def already had (pins under other causes) may stay, never added").

So for this item: remove the launder (the out-only asm), keep the pins (they may stay). The launder's purpose: "zero-byte 2nd SET: kills the sched1 birthing boost" on pv. The notes say: "1. KILL the boost on the load's destination — pv gets a second SET from a zero-byte dead __asm__ __volatile__("" : "=r"(pv)); at the end... a plain C reassignment does not work, cse/flow removes it; reusing one local across BOTH addPrim halves does kill the boost but makes pv a 2-death GLOBAL allocno that loses $v1".

Hmm. The launder is the last line. Removing it → score? Let me first remove just the launder and score (keeping both pins).

Wait, but the row says kinds=launder only. So orig = score 0, and I need to replace the launder with real C.

Ideas from moves.md for launder: C0414 dead-reset; "value-preserving real 2nd set"; do{}while(0) splits cse1 EBB; u16 flags; etc.

Here the launder creates a second SET of `pv` at the end (after all uses), which kills the sched1 birthing boost on the `pv = *(u32*)p` load. Real C equivalent: a second assignment to pv that survives cse/flow. The notes say a plain C reassignment does not work (cse/flow removes it) and reusing one local across both addPrim halves kills the boost but makes pv a global allocno that loses $v1.

Wait — but the pin `register u32 pv __asm__("$3")` is KEPT. So pv is pinned to $3. The concern about "loses $v1" — with the pin, pv is $3 (=v1). Hmm, the pin forces $3 = v1. So that concern is moot.

But "a plain C reassignment does not work, cse/flow removes it": if I add `pv = 0;` at the end (after the last use), flow's dead code elimination removes it — unless the value is used? The launder is `asm("" : "=r"(pv))` — it's a SET with a side-effect-ish asm, not removable.

Real C options to create a live second SET of pv that survives:
- Use pv again after the reassignment, in a way that doesn't change code? E.g., `pv = *(u32*)p;` at the end and use it... that's a load, changes code.
- C0414 "dead-reset": `pv = 0;` after the last use — deleted by delete_dead_from_cse.

Hmm. The note says the launder is needed because a plain C reassignment gets removed. But maybe we can make the second set survive by making pv live at a later point where it's not used... no.

Wait — what does the launder actually do at the RTL level? `asm("" : "=r"(pv))` writes a new value into pv (output), with no instructions. This makes pv have 2 sets: one at the load, one at the asm (end of function). pv's live range then extends to the end, making it a global allocno (2 deaths?) and killing the birth boost on the load.

Alternatives that produce a real 2nd set surviving to sched1:
1. A conditional assignment: `if (0) pv = 0;` — folded away.
2. Assign pv inside a branch that flow keeps: `if (arg0 < 0) pv = 0;` — adds a branch, changes code.
3. Use `pv` in a `do{}while(0)`? no set.
4. `pv = pv;` — cse removes (self-set). Actually a self-set `pv = pv` might be removed by cse1.
5. Reuse pv for the second half: the notes say "reusing one local across BOTH addPrim halves does kill the boost but makes pv a 2-death GLOBAL allocno that loses $v1" — but with the pin, pv IS $v1. So maybe that works now! Let's re-read: the note was written when the pin was the thing keeping pv in $v1... The note says "without it, local-alloc gives $v1 to the shorter, denser index quantity and pv lands in $a1/$t0". With the pin, pv is $3. So "reusing pv across both halves" might now work.

What does "reusing one local across BOTH addPrim halves" mean? The addPrim sequence:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (...);
ot = ...;
((Unk*)ot)->unk40 = (((Unk*)ot)->unk40 & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
The second half reads the OT word. The target's second half: `lw v0,0x40(v1)`? Let me look at the target asm tail to understand.

Let me view target.s tail.
