---
ts: 2026-11-06T15:47:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hcmHOggYyFAh40Gaw6vI
---
Baseline 0 (346 ins). Now remove the 3 launder lines and score.

The launders:
1. line 3014: `__asm__("" : "=r"(arg) : "0"(arg));  // !FAKE: launder ...`
2. line 3111: `__asm__ ("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz));  // !FAKE: launder — REFUSED ...`
3. line 3182: same.

Also there are `#line 900 "p.c"` / `#line 901 "p.c"` around the 2-output launders — those affect cross-jump (ASM_OPERANDS rtx_equal_p compares file+line). If I remove the asm, the #line directives become irrelevant; should I remove them? They're not levers, but they set the source line for the following code, affecting jump.c cross-jump equality of two insns' line numbers. Actually the comment says "its two copies carry identical `#line 900 "p.c"` so jump.c can cross-jump the POLY/LINE tails (ASM_OPERANDS rtx_equal_p compares file+line)". If the asm is removed, the #line still sets the line for the subsequent if(n<4) block; cross-jump compares insns' line numbers — identical #line for both copies helps cross-jump. So keep the #line directives.

Let me remove just the 3 asm lines.
