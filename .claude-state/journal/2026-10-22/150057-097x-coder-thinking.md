---
ts: 2026-10-22T21:00:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4EUFqntkTTKtEI0ZUYbT
---
Identical residual in all: sched1's order. 

Interesting: insn 72 in mine is `addiu s0,s1,123` (ax) and in target `addiu s4,s2,-93` (by). And insn 75 mine = addiu s1,117 (ay); target 79.

Let me try a *dependency* trick: make by's value feed ax in a no-op way that survives to RTL but is eliminated? e.g. `ax = ay + 0x7B;` unchanged... 

What about making the two adds into a single expression so they're scheduled in order? e.g. `ax = ay + 0x7B, by = bx - 0x5D;` (comma) — same.

What about using a pointer for one? no.

Given 25 min and 60 tries, wall. The residual is 4 (ORDER), which is a sched1 ordering of two independent addiu's and the ay add vs the index chain.

Wall tag: `sched1-birth-order` (new). Evidence: "sched1 birth boost launches ax(165) before by(161) and ay before the D_800B9A02 index chain; target keeps source order (by,ax,bx,chain,ay); best 4 ORDER".

Hmm, is that a fair mechanism? From the dump: at T-115 the ready list is `165 (4) 208 ... 161 (7f000001)` — 161 has the birth priority and gets launched at T-116, while 165 (priority 4) was launched at T-115. Wait, the log at 10482-10484:
```
T-115: 165 (4) 208 (3) ... 161 (7f000001), now 161 165 208 ...
T-116: 165 (4) 208 ... now 165 208 ...
launching 152 before 165 at T-117
```
Hmm, the "now" list is sorted by priority: 161 (7f000001 = birth) comes first. So at T-115, 161 was born and launched (priority 0x7f000001). Then 165 at T-116. So the actual launch order is 161 (by) before 165 (ax)! But the dump's RTL shows 165 before 161... 

Wait, the insn numbers in the log are the RTL uids; the dumped final order was 165, 161, 170, 175, 190. Hmm, the log says 161 launched at T-115 and 165 at T-116 — but the final RTL order in the .sched dump is 165 161 170... The .sched dump is printed *after* scheduling (the dump shows the scheduled order). Hmm, but then it contradicts.

Actually the .sched dump prints the RTL in the order after sched1? The insn chain fields (insn 165 149 161) show 165's prev=149, next=161; 161's prev=165, next=170. So the order is 149, 165, 161, 170, 175, 190. The log says 161 launched at T-115 and 165 at T-116... maybe the log's T numbers are reverse or the "now" list ordering isn't the launch order.

Whatever. The mechanism: sched1 interleaves by/ax differently from the target.

Actually, hold on. Maybe the real difference isn't sched1 but the *uid order*: in the target, by's RTL insn comes before ax's (source order); in mine, ax's comes first because of how the C was parsed? The C source order is by then ax. But gcc's expand may reorder statements? The .rtl dump would show the initial order. If the initial RTL has ax before by, then the C's *expression* order differs (e.g., because `bx = bx - 0x57`'s dependency moved by).

Let me check the .rtl dump for the initial order of these insns. If the initial order already has ax first, the fix is in the C (a real reorder); if the initial order is by first and sched1 swapped, it's a scheduling wall.

Let me check quickly.
