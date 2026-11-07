---
ts: 2026-11-06T09:59:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KsTwSad6uqcQ0rwBnG19
---
These three are header items with a pin and a keepalive.

Item 2 (func_8012BA10): pin $16 (s0) on `d` (divisor) and keepalive on u5.
- `register s32 d __asm__("$16")` pinned to $s0 because divisor live across jal.
- keepalive on u5 anchors u5 before the (s16)d cast.

Interesting: the comment says "scheduling barrier: anchor u5 before the (s16)d cast". So the keepalive is used to prevent sched1 from moving `d = (s16)d` before the ratan2 result computation? Hmm.

Let me test the lever-free version and see the residual.

First, let me get the includers count. tryinc.py <k> <header> <fn> <body> for k-th includer. And for headers, MATCH only if score 0 on every includer.

Let me find includers. There's a helper tryinc.py. Let me check its usage and the number of includers.

Let me test item 2: remove pin (plain s32 d) and keepalive.

Let me first count includers: grep -rl '#include.*func_8012BA10.h' src/ | wc -l. But maybe tryinc handles it. Let me look at tryinc.py.
