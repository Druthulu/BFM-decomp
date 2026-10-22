---
ts: 2026-10-22T09:59:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_cMdbtO3Mj7D2YauXIbKj
---
I've spent a lot on item 1 and I'm now deep into item 2. Time management: I have 4 items left (8018483C, 8017DA30, 8017D81C, 8018389C) and I've used ~2h. The remaining work per item: generate variants, score, record. Let me cap each remaining item at ~25-30 min with 30+ tries (batches of 15-20 variants are fast).

For item 8018483C (best 5, missing the v0+copy), the mechanism: cse folds the constant into the copy, so p is materialized directly into s0.

Idea for a lever-free crack: make the *source* of the copy a non-constant REG. The only C-level way: the pointer value must come from something not foldable. Hmm.

But WAIT — maybe there's another way to get "lui v0; addiu v0; move s0,v0": if the value is used in a *caller-saved* context first. E.g., if the address is passed to a function as an argument before the copy. In the target, is &D_800B99DC passed anywhere? The target's asm: "lhu v0,0(s0)" — the load uses s0. Hmm.

What if the value must be in a caller-saved reg because of the ORDER: e.g. if the assignment `p = &D_800B99DC;` happens where the pseudo is a caller-saved temp and then p (callee-saved) copies from it. That's exactly the target. When does gcc create a caller-saved temp for the constant? When the constant is materialized in a block where the pseudo is short-lived (used once) — e.g. `u16 *pb = &D_800B99DC; p = pb;` with pb used ONCE — but cse folds pb's use.

Hmm, but what if pb is used once and the copy is NOT folded because... hmm, the notes' x3 tried exactly that.

What if pb is used once but the copy is to a *different type* (e.g. `void *pv = pb;`)? Hmm.

What if the copy is through a *union* or a cast that gcc keeps?

Let me think about cse's folding rule: the notes say "cse's forward scan forwards that reg_equiv into every use". In cse.c, the relevant code is in `cse_main`'s main loop: when an insn's source is a REG that is in a class with a constant (is_const), cse replaces the source with the constant — but only under certain conditions. Let me look at cse.c's main loop for where it replaces a REG source with the class's constant.

Search cse.c for "elt->is_const" usage.
