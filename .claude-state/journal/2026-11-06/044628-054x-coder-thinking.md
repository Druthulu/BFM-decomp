---
ts: 2026-11-06T11:46:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_D5twlJ1v02PS83qlCZTW
---
Line 144: `pin | func_80145C54 | WALL cse-copy-merge — the target keeps a1 in $5 and v1 in $3 with a live move a1,v1; cse make_regs_eqv folds the a1=v1 copy into one pseudo, so s16 a1 (which keeps the copy) still lands both in $3 (best 6 of 38)`. So "cse make_regs_eqv folds the copy into one pseudo". And s16 a1 keeps the copy but lands in the wrong reg.

So the a1 copy is a "cse-copy-merge" wall. Interesting — the wall tag is `cse-copy-merge` (in walls.txt: "cse-copy-merge cse merges a copy the target keeps in its own reg (G22x)").

Our function has TWO such copies: `move a1,a0` and `move v1,a0`. Both are cse-copy-merge candidates. But the original cracked them with `+ zr` (opaque $0-add). Without the opaque copy, real C must keep them.

Given the WALL evidence for cse-copy-merge, this looks like a genuine wall. But let me not give up too early — I have budget. Let me try a few more real-C approaches:

1. For cpy = d0: maybe a `do { cpy = d0; } while (0)` (C0535 splits cse1 EBB) keeps the copy? Let me try.
2. For a1: maybe a `do { a1 = a0v; } while (0)`?
3. Dead-reset (C0414) between the loads?
4. Union member for d0.

Let me also reconsider: the target's `move a1,a0` might be reproducible if a1 is a `u8*` and a0v is s32 AND a1 is used in a context requiring a pointer... no.

Actually, let me look at the func_80145C54 wall more: "s16 a1 (which keeps the copy) still lands both in $3". So declaring a1 as s16 keeps the copy! But a1 is a pointer here. However, maybe I can exploit: what if a1 is declared as s16? No, it's used as an address.

Hmm, but wait — maybe I can keep the copy by making `a1` an s16-indexed thing? No.

Let me try the do-while wrapper on the copies (C0535) — it splits cse1's EBB. Let me test:
- v_dw_a1: `do { a1 = a0v; } while (0);`
- v_dw_cpy: `do { cpy = d0; } while (0);`
- v_dw_both
- v_dw_cpy_sr (with struct reload)

And the dead-reset C0414: e.g., `a1 = 0; a1 = a0v;`? The dead reset is a launder-ish; but "identity-statement launders do NOT count as a crack". A dead-reset `a1 = 0;` is not identity (it's a reset), and C0414 is cited as a legitimate move. But `a1 = 0; a1 = a0v;` — the first store is dead, deleted by delete_dead_from_cse. Hmm.

Let me test a batch. Also, maybe `a1 = a0v;` where a0v is used later via a separate expression. 

Actually, here's a thought: the target's `move a1,a0` might arise naturally if a1 is a `u8 *` AND a0v is used as an s32 in the function (e.g., the return). But the return is `result`. Hmm.

Let me just try the do-while and dead-reset variants.

Let me write gen3.py:
- v_dwa1: do{a1=a0v;}while(0)
- v_dwcpy: do{cpy=d0;}while(0)
- v_dwboth
- v_dwboth_sr: + struct reload
- v_reset_a1: a1 = 0; a1 = a0v;  (dead reset)
- v_reset_cpy: cpy = 0; cpy = d0;
- v_reset_both

Let me test.
