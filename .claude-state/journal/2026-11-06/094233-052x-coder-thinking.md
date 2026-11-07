---
ts: 2026-11-06T16:42:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RADJTyuRYYJuwJZzWfeL
---
Target: `1ee8 lhu a0,0(a2)` then `1eec lw v1,0(s1)` in the load-delay slot. So the `lw v1,0(s1)` (pv = *(u32*)p) is right after the `lhu a0`. In w1 (no launder), mine has `lw v1,0(s1)` at index 137 (7 insns later), and `lui a0,0xff00` takes the slot at 130.

So we need the `lw` to be scheduled right after the `lhu`. The launder achieves this by killing the birthing boost (so the load isn't given max priority and thus isn't deferred? confusing).

Let me look at the schedule: with the boost, the load's priority is max → it fires early... but it ends up LATE. The sched is a backward-ish list schedule? In gcc 2.7.2 sched.c, the schedule is built forward but the ready list is sorted by priority; higher priority = scheduled earlier. Hmm, but the comment says the boost sinks the load. Whatever the direction, the launder fixes it.

Key question: can real C achieve the same? C0505: "Set counts steer three passes: a second identical assignment demotes sched1's birthing boost". So the catalog says a second *identical assignment* demotes the boost. "Identical assignment" — e.g., `pv = *(u32 *)p;` twice, where the second is not cse'd because of a store in between that may alias. In our code, between the load and the use there are stores to `p` (the packet) and to globals. If we write:

```
pv = *(u32 *)p;
*(u32 *)p = ...pv...;   // uses pv
pv = *(u32 *)p;         // second identical assignment, AFTER the store to *p
```
The second load is a real instruction (can't be cse'd because *p changed). That adds an instruction (lw) — but if the second load is dead, flow deletes it. Ugh.

Unless the second assignment is *live*: if pv is used after it. But there's no use after.

Hmm. Wait — maybe we can put the second assignment BEFORE the first use, in a way that changes semantics? No.

Let me look at this from another angle: maybe we don't need reg_n_sets==2; we need the *load* to not be a birthing insn. birthing_insn_p requires the dest reg to be live at block start. If pv were NOT live at block start, no boost. Why is pv live at block start? Because pv is pinned to $3 and... hmm, `bb_live_regs` — let me check what it is. In sched.c, `bb_live_regs` is `basic_block_live_at_start` for the block being scheduled? If pv ($3) is live at block start, then $3 holds something from a previous block. Since pv is pinned to $3, maybe another value is in $3 at block start.

Actually: `reg_n_sets[i]` for a hard register counts SETs across the whole function. With the pin, pv's SET is a set of $3. If $3 is also set elsewhere (e.g., by another pseudo allocated to $3), reg_n_sets[$3] > 1 and no boost. The launder adds a set. 

Could we instead cause $3 to be set elsewhere *for real*? That's a register allocation change (other temps in $3) — that's the `pin` kind, and adding a pin is forbidden, but the existing pin is allowed. Hmm, we can't add.

What if we change the *pv pin* to a different register? That's modifying a lever, not removing. The pins "may stay" — but changing them? The constraint says levers of other kinds may stay, never added. Changing the pin's register is arguably a new lever. Risky.

Hmm, but wait: maybe the item's intended crack IS possible via the "second identical assignment" and I'm missing a live use. Let me look at the source again:

```
bidx = (u16 *)&D_800B9A02;
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (CAST_NONSTRUCT(...) & 0xFFFFFF);
ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
```

pv is used once. The target's `lw v1,0(s1)` is in the delay slot of `lhu a0,0(a2)`.

What if we write the expression as `pv = *(u32 *)p;` and then use pv in the second store too? That would add code.

Alternative: what if we *remove* the pv local and inline `*(u32 *)p` in the expression? Then there's no birthing SET at all; the load is part of the expression and the scheduler places it... Let me try! The pv pin would go away (it's a pin lever of another kind, allowed to stay but not required). Removing the pv local means removing the pin too — but pins are "other kinds" that "may stay" — removing them is fine (the MATCH only requires the launder gone; other kinds may stay, not must). Actually, careful: "levers of other kinds the def already had (pins under other causes) may stay, never added". So I can remove them.

So candidate: inline the load:
```
*(u32 *)p = ((*(u32 *)p) & 0xFF000000) | (...);
```
But the target's register allocation uses v1 for pv and the pin forces $3. Without the pin, the allocation may differ. But maybe it works out. Let me test this and variants.

Also: use `u32 pv = *(u32 *)p;` (init at decl) — same.

Also try: keep the pin but assign pv via a temp: `pv = *(u32*)p;` → no.

Let me also try the "second identical assignment" in a form where the second load is dead but NOT deleted because it's a volatile read? no.

Hmm, wait. What about this: make pv's second set a *real* assignment that is live because we use pv in the `func_80016638` call's *third* argument position? `func_80016638(&D_800A6518[...], 0x10, pv);` — target's third arg is 1 (`li a2,1`). If we pass pv (which equals the tag word, not 1), semantics change and bytes differ. no.

OK let me test the inlined-load idea and a few shapes.
