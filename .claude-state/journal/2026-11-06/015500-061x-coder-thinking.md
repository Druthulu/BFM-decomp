---
ts: 2026-11-06T08:55:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MaXdqaDjhNioJr4bhxwS
---
All 46 insns — the load-first-then-store structure always loses the nop. The orig structure (loads and stores interleaved as in orig) is the only one preserving 47. So the orig statement order is right.

Best so far: score 2 (w2, t3 keepalive kept). Lever-free best: score 9 (w1, both removed). And d3 (lever-free!) score 4 with 47 insns — that's a lever-free body scoring 4! Let me confirm d3 has no asm: yes, d3 has no asm. Best lever-free = 4.

Can I improve d3? Its issue: t3's store at position 34 (after h[1]) instead of 21, and t4=v0. The store position is the main mismatch (insert/delete). Hmm.

What about placing the t3 store after h[0] (d2: 46 insns, score 4) — lost an insn.

What if the t3 store is placed right after the fifth load's store (e2/c1: 46 insns)? no.

What if we place the t3 store after h[2] but before the call (d4)? Let me try. Also try t3 store after the call? invalid (call reads sp10).

Actually, maybe the right structure is: don't store t3 at all in the store block; instead store it later but ALSO keep the store in the block? No.

Hmm, what if t3's value is stored via a different statement form that sched1 schedules earlier? E.g., `*(s32*)((char*)sp10 + 12) = t3;` vs `sp10[3] = t3;` — same.

What if the fifth load and t3's store are swapped in a way that keeps the nop? The nop appears when the load is immediately followed by its dependent store. In d3, the fifth load at 24 is followed by `sw v0,32(sp)`? d3's diff shows mine[23:24] lw v0 → target[24:25] lw v1, replace mine[25:26] sw v0,32(sp) → target[26:27] sw v1,32(sp). So mine has lw v0 at 23, sw v0 at 25 (with a nop between? position 24 in mine might be the nop). Actually mine has 47 insns and the diff only shows 4 replacements + insert/delete of the t3 store. So the nop is present. Good.

So d3's only problems: the t3 store position (34 vs 21) and t4's register (v0 vs v1).

If the t3 store position were fixed, we'd have score 2. Is there a way to make sched1 place the t3 store at 21 while keeping t3's live range long? The store's position in the emitted code follows the RTL order from sched1. If the store is in the source at position 21 but t3 is live later due to... only an asm.

Hmm, wait: what if t3 is used later by a *second* store that gcc deletes? E.g., store t3 to sp10[3] twice? The second store would be dead-store-eliminated by flow (if to the same address and no read between). Then t3's live range extends to the second store's position, and the first store stays at 21! But flow's dead-store elimination: `sp10[3] = t3;` twice with no intervening read → the first store is dead (overwritten). Flow would delete the FIRST store, leaving the second — position wrong.

Unless the intervening h[] reads (lhu of sp10[0..2]) don't touch sp10[3], so the first store is dead. Yes, deleted.

What if we store t3 to sp10[3] and later READ sp10[3] and store it back? That adds instructions.

What if t3 is used in a computation whose result is stored where the target has nothing? adds instructions.

OK, d3 (score 4) is my best lever-free. Let me also try a couple more variants to see if the store can be hoisted:
- f1: t3 store after h[1] but written before the t4 load? no, then live shorter.
- f2: d3 with the fifth load moved before sp10[2]'s store? 
- f3: d3 with the t3 store written as `h[3] = t3;`? h is u16*, h[3] is 2 bytes — wrong.
- f4: d3 with `sp10[3] = t3;` replaced by `*(s32*)((char*)sp10 + 0xC) = t3;` — same.

Let me test f4 and also d3 with the h[1] line order swapped (h[0], h[1] as is). And maybe place the t3 store between h[1] and h[2] (that's d3) vs after the lhu of h[1]... 

Actually, hmm, what about placing the t3 store after the h[0] *statement* but before h[1] — that's d2 (46 insns, score 4). The missing insn in d2 might be the nop or the addiu. Let me check d2's diff to see if it's fixable.
