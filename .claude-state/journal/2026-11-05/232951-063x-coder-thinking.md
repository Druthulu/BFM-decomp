---
ts: 2026-11-06T06:29:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4UfAL9dyXTRcbjMyFUyB
---
w3's residual: base and sign swapped registers: mine base=$21(s5), sign=$22(s6); target base=$22(s6), sign=$21(s5).

So the launder's removal swapped two callee-saved allocnos (base and sign).

Their priorities: base (3 refs?) and sign (refs?). The launder's asm gave tmp a second set, changing ref counts... Since the pins are still there, the launder affects the priority order of base and sign.

Hmm, so to crack the launder I need base and sign to swap back. Plain C: give `base` or `sign` a second set / different live length.

In the target with the launder: base=$22(s6), sign=$21(s5). The launder is `asm("" : "=r"(tmp) : "0"(tmp))` — it sets tmp from tmp. How does that affect base/sign? Maybe through the ref counts of `base`... hmm, the launder forces tmp to be an output operand, so `base = tmp` must complete before it, and `mod = (tmp<<16)>>18` after. It doesn't touch base or sign.

But loop.c's move_movables decisions may differ: in the target the launder insn blocks some hoist, changing live lengths.

Hmm, w3 has the same 106 insns and no hoisting (pins block it). So the launder only shifts base/sign priority slightly.

Let me get the alloc table for w3 vs target to see the priorities. That's the precise way.

Actually, let me think about what the launder does in RTL: `(set (reg $2) (asm_operands ...))` — it's a set of the hard reg $2 from an asm with input $2. This is a "second set" of tmp's hard reg. Since tmp is a hard reg variable, that's fine.

In w3 (no launder), tmp = u*0x600+0x2000 and base = tmp. base is a pseudo. The `move s5,v0` (base = tmp) — v0 is the hard reg $2.

Priorities of base and sign: base (reg 76?) and sign.

Let me look at the alloc tables. But honestly, maybe a simpler approach: try adding a real 2nd set to `base` or `sign` to flip them.

Since sign = half >> 31 and half is fixed, sign is set once per inner iteration. base is set once per outer iteration.

What if I write `sign = half >> 31;` as before but move the `base = tmp;` assignment after the launder position? Hmm, the launder sits between base=tmp and mod=... 

Alternatively: since the launder is between `base = tmp` and `mod = ...`, and its effect is to keep tmp's value alive... 

Let me look at the actual priorities. Let me dump w3 and compare with the target's allocation.

Time check: item 2 started 23:21, now ~23:45? Let me check. I've spent a lot. Let me be efficient: dump w3's alloc table, find base/sign priorities, adjust.

Actually — better idea. Let me reconsider the FULL MATCH once more with fresh eyes:

The three things the pins do:
(a) base copy survives,
(b) tmp/hh in $2,
(c) loop.c blocked.

Hmm, what if instead of `base = tmp` I use a genuinely different computation for base that yields the same value but is a separate pseudo: `base = u * 0x600 + 0x2000;` computed *after* tmp = same expression? Then cse would merge them (same expression) — cse merges identical expressions into one pseudo. Hmm, but cse's REG_EQUAL/equivalence: `u*0x600+0x2000` computed twice → cse would replace the second with the first, no copy.

What if base is computed as `base = tmp;` where tmp was already used for mod? Order: `tmp = ...; mod = (tmp<<16)>>18; base = tmp;` — the copy might survive? cse still merges copies.

What about `base = tmp | 0;`? combine folds.

What about making base a different mode: `s16 base`? No, it's used as a 32-bit value.

OK so (a) needs the hard reg. Conclusion: the pin is load-bearing. Let me aim for PARTIAL:pin (score 0 with pins kept) by cracking the launder, and for that I need to flip base/sign.

To flip base and sign in w3: they're both callee-saved; base currently $21 (s5), sign $22 (s6); target: base $22 (s6), sign $21 (s5). So I need sign's priority > base's (or vice versa).

Let me get the alloc table for w3 and see the numbers.
