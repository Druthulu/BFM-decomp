---
ts: 2026-11-06T09:56:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_W8YsoKbWnxsBy6vPwgAh
---
Good, sc.sh gives one line per candidate. Perfect for batch scoring.

Now let me think about the first item more. Actually, let me reconsider: the residual shift suggests that removing barriers changed allocation. The barriers' role: 13 zero-byte fences after `pkt = D_800A5E60;`. The comment says 13 → MATCH, and it's "pure §47 live-length arithmetic".

What is §47? Probably cookbook about live-length arithmetic — adding fences changes live ranges of pseudos so global alloc priority changes.

A lever-free way to change live length: use a variable later (extend live range) or earlier (shorten), e.g., reorder statements, add a use.

Given the difficulty, and that this is 1 of 4, let me allocate ~20-30 min each. Let me start with the simplest item: func_800CD314 (44 ins). That's small and may crack quickly.

Let me do item func_800CD314 first. Read the whole orig.c (47 lines).
