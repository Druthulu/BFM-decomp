---
ts: 2026-11-06T16:30:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vt6mnHA0eNZTV3NYiaTh
---
No luck. Let me think harder about the mechanism. The target has ret in $3 and m in $2, and the call result comes back in $2. The move v1,v0 is a copy of the call result.

Wait, actually — maybe the call's return value isn't in v0 at the copy point. The target:
```
344: jal func_801638A0
348: addiu a1,sp,32     (delay slot)
34c: move v1,v0
```
Yes the call returns v0.

Hmm, what if instead the C assigns the call result to a variable that is live across the *else* branch and the andi? Let's see: ret is used at the test and the andi only. If ret were also used in the else arm (e.g., as a call argument), it'd be live in that block, changing the shape.

What if the test is on `m` and the andi on `ret`? Target tests v1 (ret) with beqz, then andi v0,v1. Hmm.

Let me look at the dumps. I should get the cc1 dumps for the natural body and see the RTL/insn order, and maybe understand why the pinned version gets move v1,v0. Use hdump.sh? That's for header items. For a TU item, tools/cc1_dumps_tu.sh + alloc_table.py.

Let me check tools/cc1_dumps_tu.sh usage.

Actually, more useful: the target is 103 insns and mine 102. The pinned body is 103 with the move. So the whole diff is the move plus branch displacements.

The key question: what C makes local-alloc keep a copy of the call result? The RM1 idiom: "HImode copy escapes cse equivalence class". Let me look at the actual winning body for func_80182ED4 in src to see the idiom concretely.

Let me find it.
