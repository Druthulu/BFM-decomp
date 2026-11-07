---
ts: 2026-11-06T22:51:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_o1N226IkwOlvvCDXNbbt
---
In w11: d = r74 (9/27, pri 10000); s1ang = r99? (5 refs/10, pri 10000, prefers s0)? Hmm, and there's another allocno at 10000. The .greg order: 77 79 78 74 99 76. r99 is in the .greg order with pri 10000 (5 refs/10). That's u6! So in w11, s1ang is split: r99 = u6? and the s1ang raw pseudo?

Wait, w11 uses `s1ang = s1ang & 0xFFF` (mask-in-place). With s16, the load is `lh` into a HImode pseudo, then the andi. Hmm, the alloc shows r99 (5/10, prefers s0) = the masked value, and r74 = d, and r76 (5/14) = u5.

Where's the s1ang raw load pseudo? It might be local (not shown). Let me see the full table.

Hmm, the .greg order includes r99 (pri 10000) — the masked value. In w6, the masked value (s1ang) was r75 (7/22, 6363). With s16, the masked value is a separate pseudo (5/10, 10000) and the raw load is local.

So s16 changed the structure: the raw load is local (takes $s0), and the masked value is global (r99, prefers s0). d (r74) conflicts $s0 (from the local raw) → $s1.

Hmm. So s16 didn't globalise the raw load.

Let me check the full w11 alloc to see the local pseudos.
