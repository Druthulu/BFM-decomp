---
ts: 2026-11-06T20:54:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sPu3Wsq5DbqlKfzbXJux
---
vAY, vBB, vBC all score 6 (OTHER) with 69 insns — probably all with the frame 48 issue (the +8 stack temp).

Let me check vAY's diff: if it's just the frame, we're close. The `OTHER` score type suggests the frame difference.

The frame issue: the `(v[0]^v[0])&1` expression uses HI subregs → a stack temp.

What if I use `out[0]` (also HI) — same. vBB used out[0]: 6.

What about an s32 expression: `((s32)v[0] ^ (s32)v[0])` — vAY: still 6.

Hmm. What creates the 8-byte temp? Let me look at the .rtl of vAY for a stack temp.

Alternatively, maybe the frame growth is because the expression's temps need a stack slot due to `subreg` of memory. Let me try an expression on a *pointer* value: e.g., `(s32)a0 + ((s32)(a0 ^ a0) & 1)` — a0 is SI, no subregs! `a0 ^ a0` where a0 is void* — need a cast: `(s32)a0 ^ (s32)a0`. That's SI xors. cse would fold to 0. And no stack temp (a0 is in a register).

But careful: `(s32)a0 ^ (s32)a0` — two casts of the same value; the compiler might fold `x^x` at the tree level? vAQ's `v[0]^v[0]` wasn't folded (two loads). For a register value, fold() might still not simplify x^x (it doesn't). So the RTL would be `xor reg, a0, a0` then `& 1` then `+ a0`. cse folds x^x = 0 → a0 + 0 → the add survives!

And no stack temp (all SI registers).

Let me test:
vBD: `ent = (s32)a0 + (((s32)a0 ^ (s32)a0) & 1);`

Hmm, but this is an identity expression — a launder-like trick. The brief bans identity-statement launders: "w = (w>>16<<16)|x, identity address spellings do NOT count as a crack". `(a0 ^ a0) & 1` is an identity zero — this is exactly an identity launder. Hmm.

But `(v[0] ^ v[0]) & 1` is equally an identity. Both are "compute 0 from a value". The brief's examples: `w = (w>>16<<16)|x` (an identity statement) and identity address spellings. So these would NOT count as a crack.

Hmm. That's a problem: my vAQ-style approach is an identity launder, which the brief explicitly says doesn't count.

So even if I get a MATCH this way, the expert would reject it as an identity launder.

Wait, but the difference: the pin `a0 + zr` is also an identity add (a0 + 0). The whole point is that the target's code IS `addu a0,s0,$0` — an identity add. The target's source (with the pin) does exactly `ent = a0 + $0`. So any crack must reproduce an identity add — which is inherently an "identity" operation.

The brief bans identity launders as cracks. So this item may be inherently uncrackable lever-free: the target's instruction is an identity add, and no non-identity C expression produces it.

Hmm, but the *intent* of the ban is to prevent fake value-preserving tricks. Here, the target's code genuinely contains an identity add (the $0 pin). A "real C" crack would need... hmm.

Let me reconsider: is the `move a0,s0` really an identity add? In the target, `move a0,s0` could also be a genuine register copy (a move instruction), which is what a C copy would compile to IF it survived. The issue is only that copy propagation removes the C copy.

So a legitimate crack would be a C construct that keeps a copy alive — not an identity arithmetic trick. The `(x^x)&1` trick is an identity launder → banned.

Hmm. Is there a legitimate way to keep a copy? What if the copy is *needed* semantically? E.g., if `ent` is modified later (a real modification) — but the target doesn't modify it.

OK so: item 4 is a WALL (no legitimate plain-C crack), and the identity-mask/xor probes (3 and 6) are not cracks. 

I should record the best as the clean lever-free 7.

Hmm, but wait: the brief says for a WALL, "best = lowest score of a lever-free body". If the identity probes count as lever-free bodies (they have no asm), then best = 3 (the mask). But they're identity launders, which the brief says don't count as cracks — but for the "best" of a WALL, it's just a score.

I'll report best 3 with a clear note that it's an identity-mask probe, and the clean best is 7. Hmm, or best 7.

Let me think about what the expert wants: the WALL row's "best" is the closest a lever-free body got. If I report 3, the expert sees we got within 3 mismatches using an identity mask. If I report 7, they see the clean best.

The instruction says "best = lowest score of a lever-free body". The mask body is lever-free by the mechanical definition (no row-kind levers). I'll report 3 and note it in the evidence.

Hmm, but the brief also says "no new lever of any kind" — a mask could be seen as a new lever (a launder). If it's a lever, the body isn't lever-free, and best=7.

I'll go with best 3 but explicitly label it in the evidence as an identity-mask probe (not a crack). Actually, you know what — the evidence field has limited space and the notes have the detail. Let me report best 3, wall tag `cse-copy-merge`, evidence: "combine propagates ent=a0; target's addu a0,s0,$0 has no C spelling; identity-mask probe 3 (+1 insn), clean lever-free 7".

Hmm, wait. Let me reconsider once more. The vAQ result (69 insns, frame 48) and the mask results (70 insns, frame 40, score 3) are both identity tricks. The clean best is 7.

Given the ambiguity, I'll report best 3 and explain. Actually... let me look at the definition once more: "WALL (best = lowest score of a lever-free body)". The vAQ body: `ent = a0 + ((v[0]^v[0])&1)` — that's an identity launder (a "launder" kind!), which is one of the row kinds? No — the row kind is "pin" for this item. A launder is a different kind, but adding a launder is "a new lever of any kind" → banned.

So vAQ is NOT lever-free (it adds a launder). Therefore best = 7 (clean) or 3 (mask, also a launder).

Hmm, the mask `& 0xFFFFFFFC` — is it a launder? It's a value-preserving mask on an aligned pointer. That's exactly the "identity address spelling" ban. So it's a launder too.

Therefore the lowest score of a *lever-free* body is 7. Best = 7.

OK, decision: best = 7, wall `cse-copy-merge`, evidence notes the identity probes (3/6) were rejected as launders.

Now, time: it's ~13:55. Let me check the time and finish. I need item 4 to reach 20 min (13:58).

Let me record the results row, moves line, and the notes update. The notes already say end 13:58 and mention the masks. Let me add the xor probe (6) to the notes.

Let me update the notes and then append the rows.
