---
ts: 2026-11-06T10:06:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gxsNyduQIHEFOImo5I0M
---
None flip. v5/v6/v7 same 21.

Let me reconsider. The core issue is local-alloc giving s1ang s0. Let me examine local-alloc's qty_sugg pass: qtys with copy preferences are allocated FIRST in a separate pass. If s1ang had a copy preference for s1, it would get s1. How to create one? 

Actually, maybe the solution is different: what if we DON'T tie s1ang to u6 in-place, so u6 (global) is allocated independently? The target has them in the same reg (s1) via the in-place andi. Hmm.

Alternatively, maybe we can get the target by making u6's global priority such that it takes s1, and s1ang follows... no, local runs first.

Hmm, wait. Let me reconsider: is s1ang really local-alloc'd? "Register 75 used 2 times across 7 insns in block 0; crosses 1 call". Yes, block 0. And "Register 75 in 16". So local-alloc gave it s0.

Now, why did the original get s1? Let me look at the `func_8012B8E4.h` sibling — same body, also pinned. Maybe there's a THIRD variant of this function in a non-header TU that's lever-free. Let me search for the distinctive `ratan2` + `0xFFF` + division pattern. Search for "iVar4 / d" or "q = iVar4".

Let me grep src for "iVar4 / d".
