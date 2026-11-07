---
ts: 2026-11-06T09:29:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5o8uHDeUe37wFlm51WNF
---
Item 4 lever-free: mine 56, target 58. Missing: `move v0,s1` and `move v0,zero` (the two return-value copies). Plus a scheduling diff (bgez/nop vs sra placement) and a j/goto difference.

Best lever-free 8.

Now, could a lever-free real-C move get item 4 to 0? The two missing moves are the return values. No.

OK. So all 5 are walls:
- item 1: WALL expand-void-return, best 19
- item 2: WALL expand-void-return, best 14 (need to check if real-C can do better)
- item 3: WALL ? (best 56)
- item 4: WALL expand-void-return, best 8
- item 5: WALL expand-void-return/lreg-copy-pref, best 1

Hmm, that's a disappointing shard but it matches the G24 precedent (same TU wall). But wait — the mod chose these items for a "crack shard", expecting some cracks. Let me reconsider item 3 and item 2 more.

Item 3: best 56 lever-free. But maybe real-C moves can fix it. Let me think about the two levers:
1. pin $10 ob: forces ob into t2.
2. keepalive mlo×6: boosts mlo to a2.

Lever-free mine: ob→t3, mlo→t1, c80→a2, cFF→a3, cDF→t0, mask→t2.
Target: ob→t2, mlo→a2, c80→a3, cFF→t0, cDF→t1, mask→t3.

So the whole caller-saved pool is a permutation. The natural allocation order fills regs in some order by priority. If I change the *relative priorities* of the constants via real C (ref counts, live lengths), I might reproduce the target's assignment.

What determines priority? global-alloc for these (they're live across the whole function? c80 etc. are used in all 4 packet blocks, so they're global pseudos allocated by global-alloc). Priorities = refs × live-length. Target's assignment: a3(c80), t0(cFF), t1(cDF), a2(mlo), t3(mask), t2(ob).

Global-alloc allocates in priority order into the available regs. The available caller-saved order in reg_alloc_order (mips.h) — let me check: likely a0-a3, t0-t9, v0,v1. In target, the hard $10 (t2) is reserved by ob's pin, so ob gets t2 regardless. Then the others fill a2, a3, t0, t1, t3 in priority order. Target: mlo=a2 (highest priority among the 5?), c80=a3, cFF=t0, cDF=t1, mask=t3.

Mine (no pin): the 6 pseudos fill a2,a3,t0,t1,t2,t3 in priority order: c80=a2, cFF=a3, cDF=t0, mlo=t1, mask=t2, ob=t3. So the priority order in mine: c80 > cFF > cDF > mlo > mask > ob.

Target's (excluding ob pinned): mlo=a2 > c80=a3 > cFF=t0 > cDF=t1 > mask=t3. So the keepalive boosted mlo to the top. And ob would otherwise be lowest.

So without the pin, we need the priority order to be: mlo > c80 > cFF > cDF > mask > ob. Mine: c80 > cFF > cDF > mlo > mask > ob. So only mlo needs boosting above c80. That's exactly the keepalive's job (mlo gets +6 refs).

Real-C move to boost mlo's priority without asm: mlo = 0xFFFFFF is used 4 times (`& mlo`). c80 used 12 times (4 packets × 3 stores). cFF 12 times. cDF 8? So c80/cFF naturally high. To boost mlo above them we'd need... mlo's refs would need to exceed 12. We can't add real uses without adding insns.

Alternative: *lower* c80/cFF's priority by making them not constants in registers: e.g. use `0x80` literals inline instead of a variable (then no register, immediate in store? `sb` with a constant needs a reg... `li` each time — more insns).

Alternative: reorder so mlo is computed later (shorter live) — priority = refs × live. mlo is set at `mlo = 0xFFFFFF;` before the first packet and used in all 4. c80 set before the first packet too.

Hmm. What if mlo is assigned *twice* (reassigned at each packet)? That would give more sets but the same refs; and might extend life. Actually more sets = more refs → higher priority. But an extra `li` insn per packet — target has one li? Let me check target for mlo: target `li a2,...`? Let me grep the target dump for "a2" assignments.

Target has: `li a3,128` (c80), `li t0,255` (cFF), and later `li t1,223` (cDF), and mlo = 0xFFFFFF → `li a2,0xffffff`? Let me look. And the mask 0xFF000000 → `lui t3,0xff00`.

Let me dump more of the target to see the mlo setup and count.
