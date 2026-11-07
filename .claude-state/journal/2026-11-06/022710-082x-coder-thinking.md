---
ts: 2026-11-06T09:27:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kE8CJ4CC44kUe9y4Ic8c
---
Differences: the constant temps c80/cFF/cDF/mlo are assigned differently: mine uses a2/a3/t0/t1, target a3/a2/t1/t2. It's a caller-saved temp assignment permutation. The keepalive gave mlo 6 refs; removing it changes mlo's allocation. The pin $10 for ob: ob in $10 (t2?) — hmm.

The target's registers: a2 = cFF? a3 = c80? t0/t1 = mlo/cDF? The differences are all among the constant temps (c80, cFF, cDF, mlo) and maybe ob.

Interesting: target's `and v1,v1,a2` vs mine `and v1,v1,t1`. So mlo in target is a2 (or t2?). This is a priority/order issue.

Real-C moves: declaration order of c80, cFF, cDF, mlo; init at decl; widths; reuse. The pin $10 for ob: if ob naturally gets $10 (t2), maybe the pin is redundant and only the keepalive matters. Let me check what register ob is in target: `addu v1,v1,t2` / `and a0,a0,t3`... Let me get the full target dump around the address computations and see which regs hold what.

Actually, a smarter approach: try lever-free variants and see if any reach 0. Since 297 insns and only ~10 diffs, maybe a decl-order tweak fixes it.

Variants:
- Remove the pin but keep the keepalive (PARTIAL:keepalive) — test first: that isolates the pin's effect.
- Remove keepalive but keep pin (PARTIAL:pin).

Let me test both.
