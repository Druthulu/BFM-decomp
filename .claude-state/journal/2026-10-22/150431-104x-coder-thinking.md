---
ts: 2026-10-22T21:04:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bLLgUmaRAoqPkEllVuG0
---
Excellent! e1 = 2: only the by/ax order remains (ay is now in the right place).

So the remaining issue: by's addiu must come at 72 (before ax at 73). Currently ax at 72, by at 73.

Now let me combine e1 with v4's source order (by, bx, ax) — v4 put by first but then bx before ax. Hmm. I need by, ax, bx.

e1's source: by, ax, bx (gen_o3 order) → sched1 gives ax, by, bx.
v4's source: by, bx, ax → sched1 gives by, bx, ax.

So sched1 preserves the relative order of the *later* statement? In gen_o3 (by, ax, bx) → (ax, by, bx): sched1 swapped by/ax. In v4 (by, bx, ax) → (by, bx, ax): preserved.

What about source (by, ax, bx) with the ax statement moved slightly, e.g. `by; bx-load?...`.

Let me think about why sched1 swaps by/ax in gen_o3. The dependencies: by = bx - 0x5D uses the bx load (152) and must precede bx's re-set (170, REG_DEP_ANTI). ax = ay + 0x7B uses the ay load (155).

In gen_o3's source, the order is: bx load (152), ay load (155), by (161), ax (165), bx re-set (170).

sched1 launched: 155? then 165 (ax), 161 (by), 170 (bx re-set), 175, 190...

Hmm, since by must precede bx's re-set (anti-dependency), and ax has no constraint, sched1 put ax first (its priority 4 vs by's 4, tie-break by uid? ax's uid 165 > by's 161, so a tie-break by *higher* uid? That seems odd).

In v4's source: bx load, ay load, by (uid X), bx re-set (uid X+1), ax (uid X+2). Then by must be before the re-set, and ax has no constraint. sched1 gave by, bx, ax — i.e., source order. So the tie-break isn't uid-based; something else.

What if I make the source: bx load, ay load, by, ax, then a *dummy* between by and ax that... 

Try: `by = bx - 0x5D; ax = ay + 0x7B;` where the ay load is *after* by (v3: bx load, by, ay load, ax, bx re-set = 4). Let me combine v3 with e1 (the ay fix). v3's diff was the same as gen_o3's (ax first). Hmm.

Let me try combos of e1 with source orders:
f1: e1 + v4 order (by, bx, ax).
f2: e1 + v3 order (by, ay-load, ax, bx).
f3: e1 + v6 order (ax before by).
f4: e1 with `ax` computed before by in source but... 

Let me generate e1 variants with the four source orders and score.
