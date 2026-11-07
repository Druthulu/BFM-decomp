---
ts: 2026-11-06T20:57:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rXywvyZ60dYXEGmPgwKN
---
vBN: only ONE mismatch — `sh v0,6(a0)` vs target `sh v0,6(s0)` at position 38. Everything else matches, including the `move a0,s0` at 37 and the later stores on a0.

So the target's first store `((Unk*)a0)->unk6 = v[0];` uses s0 (the parameter's home), while the later stores use a0 (ent). In vBN, the first store also uses a0 (because the store was reordered after the copy, or the register allocator used a0).

Hmm, in the target, `sh v0,6(s0)` is the store BEFORE the `ent` block (the source line `((Unkstruct_800B5CB8 *)a0)->unk6 = v[0];` uses a0, the parameter → s0). In vBN, the compiler put that store after the `move a0,s0` and used a0.

The scheduling: in the target, `move a0,s0` is at ed4c, between the v[0] load (ed48) and the store (ed50). So the copy is scheduled into the load-delay slot, and the store uses s0.

In vBN, the copy might be scheduled before the store, and the store uses a0 (the copy's value = the same, so the compiler substituted).

Hmm, one mismatch. It's an identity launder though. But wait — maybe I can fix this one mismatch with a real-C change, and then... the body would still contain the identity expression `(v[0]^v[0]) > 0` → a launder. Not a crack.

Hmm. But this is tantalizing: score 1. Let me think about whether there's a NON-identity way to get this.

The expression `(v[0]^v[0]) > 0` produced a real add at expand (the comparison result). The compiler folded it to 0 later. 

What if we use a *real* comparison that's semantically meaningful? E.g., `ent = a0 + (v[0] == v[0] ? 0 : 1)`? Hmm.

Or a real value that's 0 at runtime: e.g., `(v[0] - v[1]) & 0`? folds.

Hmm, what about using a genuinely-needed zero from the data? There's none.

The item is a WALL for legitimate C. The identity probes are launders.

But hold on: is `(v[0] ^ v[0]) > 0` really an identity launder by the brief's definition? The brief's examples: `w = (w>>16<<16)|x`, identity address spellings. A "compute 0 from x" is the same family. Yes, it's a launder.

So I'll keep the WALL with best 7 (clean). But the probes at 3 and 1 are notable — the expert may want to know. My evidence mentions the 3 probe; let me add the 1 probe (vBN) to the notes.

Hmm, actually — wait. Let me reconsider. The WALL "best" is the lowest score of a lever-free body. If the identity probes count as bodies, best = 1. If not, 7.

The brief says a crack must not be an identity launder. For a WALL, "best = lowest score of a lever-free body". A body with an identity-zero expression is not lever-free (it has a new lever: a launder). So best = 7.

I'll keep best 7 but mention the 1 in the notes (and maybe the evidence).

Let me update the notes to include vBN = 1 and vBO = 6.

Time: 13:57. Item 4 started 13:38:17 → 18.7 min. Almost 20. Let me finish the notes update (takes time) and then be at ~13:58.

Let me update the item-4 notes with the vBN finding.
