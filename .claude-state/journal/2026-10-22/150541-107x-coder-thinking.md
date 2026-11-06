---
ts: 2026-10-22T21:05:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rb36tuFUJqHjViX59Zxb
---
f2 same as e1 (ax first).

So f1 is the closest: by correct, ax at 74 instead of 73 (bx at 73). I need ax before bx.

In f1's source: by, bx re-set, ax. sched1 keeps that order. To get by, ax, bx, the source should be by, ax, bx — but that gives ax, by, bx.

Hmm, what if the source is: `by; ax; bx;` but with `ax` written as a *dependent* of something that makes sched1 put by first? E.g., make by's uid lower (it is) and ax's uid between by and bx (it is). sched1's tie-break seems to favor the insn with the later uid (ax, uid > by).

Wait: in gen_o3, by uid 161, ax uid 165 → sched1 launched ax (higher uid) first. In f1, by uid X, bx re-set X+1, ax X+2 → sched1 kept by, bx, ax (source order). So the tie-break isn't simply "higher uid first" — in f1, ax has the highest uid but was launched last.

The dependency: in f1, ax (uid X+2) depends on the ay load (uid 155); by depends on the bx load. Hmm.

In gen_o3, why was ax launched before by? Both priority 4. The sched1 log showed the ready list and a birth boost (0x7f000001) for 161 (by). The birth boost is given to insns whose operands were *just* scheduled (the "birth" of a value). If by's operand (bx load) was scheduled *later* than ax's (ay load), then by is born later, and once born it gets the 0x7f000001 priority — but it's launched immediately upon birth? That would explain: sched1 schedules a "born" insn right away.

In gen_o3, the ay load (155) is scheduled before the bx load (152) — "launching 152 before 165 at T-117" means 152 (bx load) is launched at T-117, after 165 (ax) at T-116. So the loads' order was swapped by sched1: ay load first, then ax, then bx load, then by (born). That's why ax precedes by.

In the target, the loads are bx then ay (source order) and the adds by, ax, bx.

So the key is the *load* order: sched1 launched the ay load before the bx load in gen_o3. Why? Both loads are independent; priority 1 each. Hmm.

In f1 (by, bx, ax), sched1 kept by, bx, ax — so it launched the bx load first (by's birth) then ax.

What if the source order is (bx load, ay load, by, ax, bx) — gen_o3 — and sched1 swaps the loads. The loads' order in the ready list is determined by their uids: bx load uid 152 < ay load uid 155. sched1's tie-break for equal priorities: it picks the *last* in the ready list? The ready list is sorted by priority; for equal priorities, gcc's `rank_for_schedule` uses the uid: it prefers the insn with the *larger* uid? In f1, the loads are also bx then ay.

Hmm, gen_o3's log at T-115 showed "161 (7f000001)" — by was born at T-115. So the bx load was scheduled at T-114 or so, and then by (born) was launched. Then ax at T-116. Wait, that gives by before ax — contradicting the final order!

Unless the .sched dump's printed order isn't the launch order. The .sched dump prints the RTL *after* sched1 in the *original* insn order? The chain fields (insn 165 149 161) show the linked list order after scheduling: 149 → 165 → 161. Hmm.

I'm confused by the log vs the dump. Let me look at the .sched2 dump (after sched2) or the final .lreg order: in .lreg, the order is the final. Let me check the .lreg for these insns' order.

Actually, the residual diff (dt.sh) compares the final object code, which is ground truth: ax at 72, by at 73.

The sched1 dump I read (o3.i.sched) shows 165 before 161 — consistent with the final code (ax=165 at 72, by=161 at 73).

And the log lines: at T-115 the ready list shows 161 with 7f000001 and at T-116 it's gone — so 161 was launched at T-115... but the dump shows 165 first. The T numbering may be a countdown (T-115 = the 115th-from-last cycle), so higher T = earlier. T-115 vs T-116: T-116 is *later* than T-115 in a countdown? No: "T-115" then "T-116" — the log counts down from T-1? Ugh.

Whatever. The empirical result: source (by, bx, ax) → by, bx, ax; source (by, ax, bx) → ax, by, bx.

What if the source is (by, ax, bx) but with the *bx re-set* written to use a separate temp so its anti-dependency on by is removed? E.g. `bx = out.vy - 0x57;` (v5 = 4). Then by and bx are independent; sched1 might order by, ax, bx.

v5's source: bx load, ay load, by, ax, `bx = out.vy - 0x57;`. Score 4 (with the old ay handling). Let me combine v5 with e1: h1.

Also: what if I make the ax statement depend on by's value via a *no-op* that survives? no.

Try h1 = e1 + v5 order (bx = out.vy - 0x57). And h2 = e1 + (by, ax, then bx re-set from out.vy). Also h3: e1 with the source (by, ax, bx) but the bx re-set moved *before* by:
```
bx = out.vy;
ay = out.vx;
bx = bx - 0x57;   // hmm, then by = bx - 0x5D uses the NEW bx (wrong semantics!)
```
No.

h4: compute by from the load and bx from the load:
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
ax = ay + 0x7B;
bx = out.vy - 0x57;
```
= v5+e1 = h1.

Let me run h1 and a variant where the ay load comes after by (h2).
