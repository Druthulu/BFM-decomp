---
ts: 2026-11-07T00:58:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_in7yVM6jEARJCeL9cKbB
---
Wait, w10 has `p += 5; p -= 5;` then q = p — that's wrong semantically (q should be p+5). Actually p_adv replaces "  p += 5;\n" with "  p += 5;\n  p -= 5;\n" so then q = p (original p) — wrong. Drop that idea. Let me remove w10 and w11 (z unused). Also w18 writes to absolute 0 — that's UB/not equivalent. Remove.

Also w21 flag init: flag=0; flag=0x1000000 — dead store eliminated, harmless.

Let me fix the dict: remove w10, w11, w18. Add different ones:
- w10: `t = ((n << 3) + 8) | 0x4000;` — that's a different spelling of n*8; combine should fold. Actually `n * 8` becomes sll. Keep.
- Add a variant with declarations in a different order (the decl order affects nothing for priority but could affect local-alloc ties).

Let me simply remove the bad ones and add:
- w10: mk(nn=True, reset="  p = 0;\n", p_adv="  p += 5;\n") same as w03 (duplicate) — no.
Let me instead add:
- w10: nn=True, reset, with `col` declared before q (decl order variant) — needs a different template. Skip; decl order is a weak lever but C0505 lists it. I could do a simple post-hoc string reorder for a few.

Simpler: I'll write the final set of ~22 and then create a few more by post-processing (statement order swaps) in a second batch if needed.

Fix the dict now.
