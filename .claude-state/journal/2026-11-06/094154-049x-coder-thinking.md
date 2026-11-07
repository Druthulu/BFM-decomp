---
ts: 2026-11-06T16:41:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QMALKgMwHo2KQ0iigiKy
---
All 11 — the second sets are all deleted/folded before sched1.

New idea: make the second set *live* by using pv after it in a zero-byte way. The only zero-byte use... hmm.

Wait — what about making pv live-out of the function (i.e., in $v0 return)? No.

What about the *pinned* hard register: `register u32 pv __asm__("$3")`. If we make a second set to pv that is *live* because pv is used later in a *different* block — but there is no later block.

What if we reorder: move the `pv = *(u32*)p;` load to the TOP of the function? Then it's live across many blocks and used in the tail. reg_n_sets still 1 → boost still applies? The boost applies to the SET insn itself (the load), wherever it is. Moving the load earlier changes its position (maybe out of the problem area). Hmm, but the target has the load at a specific position.

Alternative: defeat the boost by making the load insn have a REG_DEAD note (n_deaths>0)? Not controllable.

Alternative: the boost is `if (max > INSN_PRIORITY(prev)) INSN_PRIORITY(prev) = max;` — it raises the load's priority to max_priority. That makes it fire early. The target wants the load earlier than mine. Wait, mine has the load LATER than target (lw v1 at 137 vs 130). The boost raises the load's priority so it fires early... hmm, the comment says the boost sinks it to just before its consumer. Whatever.

Let me think differently: instead of killing the boost, restructure the source so the load is born at the right position regardless. E.g., split the load from its use:
```
pv = *(u32 *)p;
... other statements ...
*(u32 *)p = (pv & 0xFF000000) | ...;
```
It already is. The scheduler moves it.

What if we make pv's load a *non-birthing* set by having pv live at block entry — i.e., initialize pv earlier in the same block? e.g., `pv = 0;` at the top of the block, then `pv = *(u32*)p;`. Then reg_n_sets(pv)=2 (the first set is live? if the first `pv=0` is dead, it's deleted). If we then use pv before the load... no.

Hmm, what if the first set is `pv = *(u32*)p;` and the second is a *real* use that redefines pv via a compound assignment that's needed? No.

Let me reconsider: is the residual really only fixable by the launder? The comment says so, from prior analysis. Let me verify by looking at the target and trying alternative source shapes for the tail.

Target tail (from target.s, item2). Let me read the target.s around the tail.
