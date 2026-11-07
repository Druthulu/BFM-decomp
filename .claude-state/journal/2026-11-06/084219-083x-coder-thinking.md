---
ts: 2026-11-06T15:42:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vFBtBYIkhi8GOL8D7gU0
---
Mine: the constant load (lui v1; lw v1; nop; addiu v1,v1,500) is scheduled *before* the mflo/sra/addiu a2 chain (interleaved into the mult's delay slots), using v1. Target: the constant load happens after `addiu a2,v0,8`, using v0.

This is a sched1 ordering thing: the launder (a 2nd set of n) pins the n chain so the constant load isn't hoisted into the mult delay slots? The moves list has "sched1-call-group" and "sched1-birth-boost".

The launder makes n's second set opaque — sched1 can't move the constant load before n's birth? Hmm.

Since n is pinned to $6 (a2), the launder `"=r"(n)` is a second set of a hard-reg variable. Removing it lets sched1 hoist the `lui/lw/addiu` constant chain above `mflo/sra/addiu a2`.

So I need a real 2nd set of n (or an ordering device) that keeps the schedule.

n = q + 8 where q = p >> 12, p = e * sc.

A real 2nd set that's value-preserving: n = q + 8. Since q is an s32 from `p >> 12`... unknown range.

Ideas:
- `n = q + 8; n = n;` no.
- Use the C0414 dead-reset pattern: save n, reset, restore. But n is pinned to $6; a reset/restore would emit moves (a2=0 then a2=keep) — could be coalesced away if keep is also in a2... but a2 is pinned, so keep would need a different reg → extra move. Hmm.

Wait, but in item 3 the dead-reset trick worked. Here n is pinned; a `n = 0; n = keep;` would emit `move a2,zero; move a2,keep` — but maybe dbr removes them if... risky.

- What about a real 2nd set via `n = n + 0`? folds.

- The moves list: "func_8017E780 WALL sched1-call-group — the t re-tie keeps the unk20 load OUT of sched1's call+argsetup group; without it the load joins the group and lands one slot late (score 2)". Similar situation!

- "func_8018FB5C WALL sched1-birth-boost-dbr-delay — the re-tie does 2 jobs: 2nd SET of the pinned $16 pseudo (kills sched1 birth boost; plain drop hoists li a0,16 to slot 5, score 2) AND a zero-width RTL insn... a do-while 2nd SET restores the order but the li falls in the delay slot, score 4".

So a 2nd set of n kills the sched1 birth boost of n's chain. What 2nd set emits nothing for a pinned hard-reg variable?

Idea: `n = (s32)(s16)n;`? n's value: q + 8. Unknown range.

Hmm, but maybe there's a *different* real-C route: reorder the source so sched1 naturally produces the target order. E.g. move the `d = ...` computation after something, or introduce a temp for the constant: `s32 c = D_80126950 + 0x1F4; d = n * c / (ret * 4);` — a named temp might change the birth order.

Let me look at the cse/sched dumps for orig vs a1 to understand precisely. But first, cheap experiments:

f1: `d = n * (D_80126950 + 0x1F4) / (ret * 4);` with a temp: `s32 cst = D_80126950 + 0x1F4; d = n * cst / (ret * 4);`
f2: swap: compute `d` after `x = o.sxy[0]; y = o.sxy[1];`? Statement order changes.
f3: dead-reset: `{ s32 keep = n; n = 0; n = keep; }` before d.
f4: `n = q + 8; n = (s32)(u16)n;`? not value-preserving.

Actually, what is the launder doing in RTL? Let me dump the orig cse/sched for this function and compare with a1. The dumps take a bit but are decisive. Let me do it.

Actually, first let me try the cheapest: a real 2nd set of n as `n = q + 8;` again? no.

What about making the launder a real statement: `n = q + 8; if (n == 0) { }`? no.

Think about "real 2nd set" that emits nothing for n: what if n's value is provably in a small range? q = p >> 12, p = e * sc; e is derived from func_8004787C * 3 / 8 - 0x800 or 0x800 - ...; sc = D_80192870 (a global s32). Unknown.

Hmm. Let me look at what sched1 does. Dump the orig and a1 .sched dumps.
