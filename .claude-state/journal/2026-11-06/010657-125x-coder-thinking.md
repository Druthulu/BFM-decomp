---
ts: 2026-11-06T08:06:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FaJQhPZTNlO4MQoWzJmU
---
v20_dw_mang scores 5 with 70 ins (2 extra). The do-while adds 2 insns? That's odd (do-while should be 0). Wait, mine 70 vs target 68 — the do-while block may prevent optimizations, adding insns. Hmm.

Let me look at v20's diff. It might show a different residual. But 70 ins is worse.

The core issue: the m/ang computation is sunk. What real-C forces it early? The keepalive is at the point right after `t = obj->unkA;`. It requires m and ang in registers THERE. In the natural C, maybe m and ang are used in a statement right there. Is there any statement? The next statements are the two stores. What if the original stored `m` or `ang` to a temporary field? No.

Wait — maybe the original source has the `if (obj->unk50 == 0)` check BEFORE the stores? No, target has the check after the stores.

Hmm, let me reconsider: maybe the keepalive isn't about m/ang ordering but about their REGISTERS. The keepalive forces m and ang to be live in registers at that point. The target's m is in a0, ang in s1. The lever-free body has m in v1, ang in s1. The register pair v1->a0 x2 is the residual.

The scheduling difference (sinking) is the main issue. Let me check: does the do-while (C0535) around the m/ang computation split the cse1 EBB so sched1 keeps them? v20 gave 5 with 70 ins. Let me see its diff.
