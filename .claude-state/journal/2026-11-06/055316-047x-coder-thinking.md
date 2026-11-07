---
ts: 2026-11-06T12:53:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fSno99HUTl5uNJChVzIe
---
This is the "LAUNCH_PRIORITY" mechanism: an insn just scheduled gets LAUNCH_PRIORITY so reg-killing insns launch early.

Time is passing; I have 5 items and a 20-30 min budget each. Item 2 is already ~15 min. Let me be pragmatic: try a focused batch of real-C variants, and if none works, record a WALL with the tag (sched1-birth-order or sched1-load-order... the wall list has `sched1-birth-order`).

But wait — before giving up, let me reconsider the do-while result in item 1: it worked there. Maybe here the do-while needs to wrap a *different* statement. In item 1 the do-while wrapped the store that the sched wanted to reorder.

Here the moved insns are the constant pair for the 0x4 store. Let me try wrapping the 0x4 store in a do-while (v4 did that plus the y store). Let me try ONLY the 0x4 store in a do-while.

Also try: `do { *(u32*)out = 0x04000000; } while (0);` and `do { *((u8*)out+0xC) = 0x78; } while (0);`.

And the reverse: maybe wrap the *y* computation+store.

Let me generate a matrix of single-statement do-while wraps: around C400, C78, C64, CE, Y, and pairs. That's cheap (each ~10s). Let me do 6 single wraps + a few combos.

Actually wait. Let me reconsider the problem: the residual is the lui/ori pair placed one insn too early. In the target, they are placed right after the sh. The target's order = source order (sh, then the constant build for the 4th store). So the target simply didn't reorder the join block at all (except the constant pair hoisting from position 4 to position 2 — wait, in source the constant pair belongs to the 4th statement, but in target it's at position 2, before the 0x400 store at position 3. So the target DID hoist the pair by 2 slots).

Target join block order: sh(Y), lui/ori(C64), sw 0x400(C400), li/sb(C78), li/sh 0x4056(CE), lw/lw(vsum), sh vsum(S8), sh eight(S10), sh eight(S12), ...

Hmm interesting: CE (the 0x4056 sh) is at 150, after the sw -14 (C64) at 149. In source CE comes after C64. Fine.

So the target hoisted the C64 constant pair from its birth position (4th) to just after the first insn (sh). Mine hoisted it to position 0 (before the sh).

This is the classic "sched1 hoists a constant build to fill the earliest slot". The difference is one slot.

Idea: give the sh a higher "birth" priority by making it depend on... hmm.

Alternative idea: what if the sh were scheduled in the *arm* blocks? The join block starts at 62c. In target, is the sh at 62c the first insn of the join block? Yes (62c is the jump target from 5e0).

Hmm — actually! Maybe the target's sh at 62c is NOT in the join block but in the *else* arm, and the arm0 path jumps to it... no, both paths reach it.

Wait, maybe there's a subtlety: in target the arm0 does `j 62c` with delay `addiu v0,v0,-2`, and the else arm falls through 610 → ... → 628 addiu v0,v0,1 → 62c. So 62c is the join. Both arms compute y into v0. Good.

So the join block's first insn is the sh. In mine, the join block's first insn is lui.

What if the join block in mine is entered differently... no, same.

OK, let me think about the LAUNCH_PRIORITY mechanism: "Give INSN high enough priority that at least one (maybe more) reg-killing insns can be launched ahead of all others." After scheduling an insn, its predecessors that are "reg-killing" get launched early. The `schedule_insn` function adds ready predecessors. A "reg-killing" insn = one that sets a register (kills it). The lui sets v1 → reg-killing. The sh doesn't set a register.

So when the scheduler schedules the sw(-14), its predecessor ori becomes ready with LAUNCH_PRIORITY? Hmm.

The key: LAUNCH_PRIORITY is given to the just-scheduled insn so that its predecessors get launched. Let me look at schedule_insn to see how priorities propagate.

This is a rabbit hole. Let me just try the empirical batch: single-statement do-while wraps. If one flips the order, great.

Let me write mk3.py generating do-while wraps around each single tail statement.
