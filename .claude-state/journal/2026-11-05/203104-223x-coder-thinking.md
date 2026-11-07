---
ts: 2026-11-06T03:31:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QgGuZscWJ1HcBRh5OZ3h
---
u15 (swap the two statements: unk2A store before the obj store) gives 57 ins but score 12 (wrong order). No crack.

I've now got 13 + 20 = 33 scored tries on item 5. Time check: ~20:50? Let me record a WALL with best 10 (u13: 56 ins, score 10) or best 11. u13 gives score 10 (56 ins) — the lowest. Let me verify u13's diff to describe it. u13 = do-while around the obj store → score 10.

Best = 10. Wall tag: `cse-global-reload`? The mechanism: cse hoists/caches the D_80126B78 pointer load across the call and the obj store; the barrier forces a reload. A new tag: `cse-fixed-global-cache`.

Let me record item 5 and then do the final checks: all 5 items have results rows, each MATCH/PARTIAL has win.c scoring 0 (none are MATCH/PARTIAL — all WALL), so no win.c needs score 0. But the brief says "each MATCH/PARTIAL has its win.c scoring 0" — all ours are WALL, fine.

Wait — all 5 items are WALL. That's a lot of walls. Hmm, the shard's list had 5 barrier items; all failed. Is that plausible? The moves.md shows many barrier MATCHes too. Maybe I'm missing something systematic.

Let me reconsider item 5 quickly: the barrier is a memory clobber; the target reloads D_80126B78 after the obj store. The C lever could be to make the obj store a *call*? no.

Hmm, what about the `obj` variable: `obj = unk20;` and the store `*(u16*)(obj+0x14)`. The target's store uses a1 = obj. Mine uses... let me look at mine's asm. Actually, maybe the difference is that in the target, the D_80126B78 load is NOT hoisted above the call because the call is a real function call (memory clobber). In mine it IS hoisted — meaning gcc's cse hoisted a memory load above a call, which seems wrong. Unless the call in question (func_8012F14C) is declared `const`? No.

Wait, maybe mine's "early" load at insn 18-20 is not before the call. Let me get mine's asm to see the positions. Let me dump mine's asm.

Actually, time is pressing. Let me finalize item 5 as a WALL with best 10 and then write the log. But first let me quickly check u13's diff to describe the best.

Actually, hold on. Let me reconsider the possibility that a *simple* C change fixes item 5: the target's two loads of D_80126B78. What if the original C stored the pointer in a local variable *after* the call:
```
s32 *g = D_80126B78;   // after the call? 
```
The source order: the first use is in the obj store expression; the second in the unk2A store. Both after the call. Mine hoisted the first load above the call (probably because the call doesn't clobber memory in gcc's model? or because the load is loop-invariant?).

Hmm, if gcc's cse doesn't invalidate memory at calls, then a load can be hoisted above a call — that's the standard gcc behavior only if the call is known not to write memory. For a normal call, cse's `invalidate_for_call` does invalidate memory? Let me check quickly.
