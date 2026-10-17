---
ts: 2026-10-17T16:40:37.577Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm digging into why c1 and the pseudo tie at sll16 — it looks like keepalive logic isn't extending the register's lifetime like I expected. I'm now wondering if this is really a priority issue in local-alloc, checking the case where combine_regs handles a hard register tied to a pseudo.

The tie seems to happen because the allocator suggests a0 for the pseudo and uses it as soon as it's free, so I'd need c1 to stay live longer or a0 to be occupied otherwise to avoid it. I try imagining alternate statements that might extend c1's liveness without changing the generated instructions, but nothing obvious works — different shift groupings produce different code. I'm circling back to the residual 302 case to see if the same fix applies there.

Now I'm reconsidering the scoring convention: should "best" mean the body with all levers (including pins) stripped out, or just with the row's specific kind removed while pins stay? I notice I treated func_80185214 inconsistently — reporting the fully lever-free score instead of the row-kind-free one — so I need to correct that row to use the row-kind-free best and just note the fully-stripped score as additional evidence. This affects how I should treat the 8018E428 case too, where the row kind was fully removed but pins were kept.

Rereading the brief's definition more carefully, it seems "lever-free" specifically refers to the absence of row-kind levers (pin, launder, barrier, keepalive macro/asm) — meaning unrelated pins can remain and still count as a match. Under that reading, 8018E428 with both pins kept but the launder removed should count as a MATCH, and 80185214's best score with pins retained should just be 5. I'm also noting 8017BF14 at wall 302 with a best of 2, and thinking about spending more time investigating what's forcing the target temp to v0 there.
