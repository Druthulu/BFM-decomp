---
ts: 2026-11-06T10:10:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iLXESYq358TYcidlID5d
---
Now I have the case-1 loop pseudos:
- f = reg 75 (`reg/v:SI 75` set 0, set 1). refs4 live16. Global pri 5000.
- i1 = reg 77 (`reg/v:SI 77` set 0, increment). refs7 live11. pri 12727.
- limit = reg 177 (const 5). refs3 live20. pri 1500.
- giv = reg 234 (symbol D_801AECD8, plus 4). refs7 live9, pointer. pri 15555.

In mine: f=r75→a1, i1=r77→a0, limit=r177→a2, giv=r234→v1.

Allocation order (priority descending): ... 234(15555) ... 77(12727) ... 75(5000) ... 177(1500) ... and 236(12727), 230(20000), etc.

Wait, the order line: 80 114 232 230 79 234 77 236 207 76 78 85 106 131 74 96 75 142 72 144 218 177 125 187 208 73.

Relevant: 234 comes before 77, which comes before 75, which comes before 177.

Allocation: 234 (giv, pri 15555) gets the first free reg. The regs available (caller-saved, not conflicting): conflicts for 234 are "v0,sp" (from the table: "conflicts v0,sp"). So it can't take v0 or sp. It takes... v1? Yes, mine: giv=v1.

Hmm, but wait — 234 conflicts with v0 but not v1, so it takes v1 (the next in order). But there's also a0 (4) — why v1 not a0? Because v1=3 < a0=4. Yes.

Then 77 (i1, pri 12727) — conflicts v0,sp. Free regs: a0(4), a1(5)... takes a0=4.
Then 75 (f, pri 5000) — conflicts v0,sp. Takes a1=5.

Target: f=v1(3), i1=a0(4), giv=a1(5). So in target, f is allocated BEFORE the giv (f gets v1), then i1 a0, then giv a1.

That means in target: pri(f) > pri(i1) > pri(giv)? Or at least f > giv. Since f gets v1 (first free after v0 conflict), f must have higher priority than both i1 and giv.

Hmm, but the keepalive adds refs to i1, not f. How would that raise f above i1 and giv?

Wait — maybe the keepalive's presence changes the *loop structure* such that the giv isn't created by loop.c but computed differently, changing its refs. Let me check the target's dump... but the target is the binary, not a dump. However, the current src (with pin+keepalive) scores 0, so I can dump THAT and see the priorities!

Let me dump the current orig body (with pin+keepalive) and compare the alloc table. That will show exactly what the keepalive did to the priorities.

Let me do that: --try orig.c --keep, then dump.

Note: orig.c has `register s32 f __asm__("$3")` and the keepalive. Let me dump it.
