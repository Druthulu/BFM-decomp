---
ts: 2026-11-06T12:55:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5ioWYfFDWozoJoFfTIiO
---
All ≥ 2. I now have 32 scored tries for item 2 (w0, v1-v5, v8-v11, d_*7, p1-p5, q1-q10 = 1+5+4+7+5+10 = 32). Good — a WALL is legitimate (≥30 tries, ~30 min).

But wait, before declaring the wall, one more idea that's cheap and promising: what if the *y store* is moved into each arm? Let me check the target once more... no, target has one sh at the join.

Actually, hold on. Let me reconsider: maybe I can get the target by making the constant pair NOT hoistable because it's born in a *different basic block*. What if the C64 store moves into an `if (j)`-style block? No.

Hmm, what about the possibility that the target's schedule is produced by making the y store depend on the C64 constant? Wait — actually! What if `y` is stored via a value that also uses v1? No.

One more idea: the sh at 141 uses v0 which holds y. The lui/ori at 142-143 uses v1. What if the constant were built into v0 (the same reg as y)? Then a WAR dependence on the sh would force lui after the sh. In the target it's v1, so this wouldn't match... BUT: maybe if I write the constant into a variable that local-alloc gives v0 (because y dies at the sh), the *emitted* code would be `lui v0; ori v0; sw v0,-14(a1)` and `sh v0,-8(a1)` — but the target has v1 for the constant and v0 for y. So it wouldn't match. Unless the sh's y is in v0 and then the constant in v0 after... the target's sh uses v0, the sw uses v1. If my constant were v0, the sw would be `sw v0,-14(a1)` ≠ target `sw v1,-14(a1)`.

So no.

I'll declare item 2 a WALL with tag `sched1-birth-boost` — evidence: sched1 hoists the 0x64808080 lui/ori pair (a birthing insn) above the preceding y store; only the memory barrier splits the block. Actually, is the birth boost the right mechanism? Let me verify by checking whether the lui's dest pseudo is a "birth". Hmm. The `birthing_insn_p` requires bb_live_regs at block entry to contain the pseudo. The constant pseudo is not live at block entry, so no boost.

Alternative explanation: it's the "sched1-load-order"/"sched1-birth-order" class: "sched1 orders two independent insn births opposite to source". Our case: the constant pair (birth) vs the store. Hmm, `sched1-birth-order` = "sched1 orders two independent insn births opposite to source; reorder moves the other".

Hmm, but here the sh is not a birth. The closer wall tag: `sched1-load-order` is about addiu/lw. `sched-store-sink` is about sinking. Here the pair is HOISTED above a store.

Let me actually test the mechanism properly: dump the sched1 dump? There's tools/cc1_dumps_tu.sh and hdump.sh for header passes. Maybe I can get a sched dump. That's expensive.

Cheaper: reason from a controlled experiment. If the boost is from LAUNCH_PRIORITY: when the sw(-14) is scheduled, its predecessor ori is launched with priority = LAUNCH_PRIORITY. Hmm.

Let me look at `schedule_insn`'s launch logic — it gives `INSN_PRIORITY(insn) = LAUNCH_PRIORITY` for the *just scheduled* insn so its predecessors (which are "reg-killing") get launched early. And then in schedule_insn, predecessors get `new_priority = INSN_PRIORITY(insn) - 1`? Let me read the rest.

Given time constraints, let me do one quick read of schedule_insn to name the mechanism accurately for the wall evidence.
