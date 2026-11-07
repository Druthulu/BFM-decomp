---
ts: 2026-11-06T08:50:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3Y8ESNwo4OMvrGQCNc61
---
No `(use reg78)` in the initial RTL. So it's created later. Which pass? The .cse dump has 0, the .combine has 1. Combine created it. Why would combine create a USE of reg78?

GCC combine's try_combine: when combining i2 into i3, if the destination of i2 (reg78) is used elsewhere (here, the later stores? no, those are i3's successor...), combine may need to keep the value. Actually here's the thing: combine merged i2 (copy reg78=reg77) into i3 (neg reg78) producing neg reg77. The original i2's destination reg78 is *also* used by the later stores (i3's successors), so combine must keep the value of reg78 = reg77! It creates... hmm, no: combine's merge of i2 into i3 is only valid if reg78's value after i3 is the neg — the later uses of reg78 (the stores) use the merged value. Fine, no USE needed.

But the USE it created is of reg78 *before* i3 — a "use" to keep the copy's value alive? That would be exactly the semantics of "the old val value is needed" — but it isn't.

Hmm, wait. Let me reconsider: maybe the USE comes from `(insn 265 ...)` being the RTL of the *asm* in the original function... in a DIFFERENT function's numbering? The lreg dump line numbers I grepped: `grep -n "use (reg/v:SI 78)"` found the one in func_80187988. Fine.

Let me search GCC 2.7.2 combine.c for `gen_rtx (USE` to see when combine creates a use. tools/reference/gcc-2.7.2/combine.c is available.

Actually, maybe more productive: the *target* (orig with asm) — let me dump it too and compare the RTL. If the orig's RTL shows the copy + a USE + neg (where USE is from the asm), and c1's shows the same USE, then... they'd be identical, but the scores differ (c1 = 1). Hmm.

Wait, actually! Maybe the p3 scratch .c used for the dump is NOT c1 but the *orig* body: the tool may splice the body into the TU but the p3 scratch I grepped is from the last --keep which was... I ran --keep with c1.c. Hmm.

Let me settle it: the c1 score was 1, so its object differs in the negu operand. The combine dump I read shows `(set reg78 (neg reg77))` — the merged form. So the dump matches c1. And the USE at 265 exists in c1. Since c1 has no asm, combine created the USE.

Let me look at combine.c to understand. grep "USE" in tools/reference/gcc-2.7.2/combine.c.
