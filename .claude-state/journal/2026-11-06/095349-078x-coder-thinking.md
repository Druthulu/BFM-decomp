---
ts: 2026-11-06T16:53:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9SAHlEBVwSBxxcgWmKKu
---
Still 9/10. Time ~09:58. Item 3 started 09:44 → 14 min. Need 20 min (until 10:04) for a WALL.

Let me try a few more angles:
- What if the pin is replaced by making the function's v0 the *return value*? No.
- What if `v0` is used as a function argument at some point (forcing $a0)? no.

Actually, here's an idea: the target's v0=$2 might come naturally if v0 were the *first* variable born in the function and had many refs. The priority formula uses refs and live length. v0's live length is long. What if we SPLIT v0 into more variables to shorten the live ranges (C0505 R28 inverse)? p02 split at JOIN → 10. Let me split v0 into block1-only and branches separately, with the branches' variable being short-lived.

Actually q01 did a three-way split (block1 v0, branches v0b, JOIN v0c) → 29, worse.

Hmm, p02's structure: v0 (block1+branches) = $a0, v0b (JOIN/K) = $v0. The target has $v0 in both. So we want to swap: v0→$v0, v0b→something else. If v0b went to $a0, that would match the target's JOIN/K? Target JOIN/K: `lh v0,112(s0)` etc. — uses $v0. Hmm, target uses $v0 in JOIN/K too. And $a0 is used for a0r in the branches.

Wait, but the target's JOIN/K region: does it use $v0? Yes (3424 lh v0; ...; 342c bnez v0). So $v0 is used in JOIN/K, and $a0 is used in the branches (a0r).

In p02, v0b (JOIN/K) = $v0 (correct!), and v0 (block1+branches) = $a0 — correct for the branches' a0r? No: in the branches, a0r should be $a0 and the temp v0 should be $v0. p02 gives v0=$a0, which is the a0r register — so the loaded value went to a0 and a0r coalesced with it, and the modified value went to $v0.

Hold on: if v0 (the source var) is $a0, then in block1 `lh v0,112(s0)` would be `lh a0,112(s0)`. But the diff shows block1 is CORRECT (mine[?] matches target). Let me re-check: p02's diff only shows differences in the branches, and the register pair summary says a0->v0 x4. So in the branches, a0↔v0 are swapped; block1 is fine.

That means the pseudo in the branches is NOT the same as block1's v0. So p02's v0 in the branches... wait, p02 renamed only from JOIN onward. So block1 and the branches both use v0. But if the same pseudo, the register would be the same everywhere. Unless the compiler split it (local-alloc per block?) — no, a global pseudo has one register.

Unless... the diff's "register pairs (mine -> target): a0->v0 x4" means in those 4 insns mine uses a0 where target uses v0 — these are the *loaded value* and *a0r* pseudo, not necessarily v0.

Let me look at p02's branch: `lh a0,0(at)` — if the load writes v0 (source), it should be $v0. But it's $a0. So the load's dest pseudo is a0r (combine propagated the copy so the load writes a0r directly), and v0 is a separate pseudo ($v0) used for the modified value.

So combine/cse rewrote `v0 = load; a0r = v0;` into `a0r = load; v0 = a0r - 0x30`. In the target, it kept `v0 = load; a0r = v0;`.

Why would combine do that? Copy propagation `a0r = v0` where v0 dies after the copy → replace a0r with v0? That's the reverse. Actually combine does `subst` — it propagates a register's value into its uses. `a0r = v0` then later `v0 = v0 - 0x30` (v0 redefined). a0r's only use is the store. Combine might propagate a0r = v0 into the store: `store v0` — but v0 is modified before the store, so it can't. Hmm.

Unless the order is: `v0 = load; a0r = v0; v0 = v0-0x30; if (...) store a0r;` — the store uses a0r. Combine sees a0r = v0 (copy) and tries to replace a0r's use with v0, but v0 is modified in between → blocked. So the copy should survive.

But mine's asm shows `lh a0,0(at)` then `addiu v0,a0,-48` — no copy insn. So the copy was eliminated by making the load write a0r and computing v0 from a0r. That's local-alloc coalescing the copy (a0r and v0 same reg) — no, they're different regs (a0 and v0).

Hmm, actually: `lh a0,0(at)` (a0r = load), `addiu v0,a0,-48` (v0 = a0r - 48). This is exactly `a0r = *(s16*)at; v0 = a0r - 0x30;` — the u01 spelling! But p02's source has `v0 = *(s16*)at; a0r = v0; v0 = v0 - 0x30;`. The compiler rewrote it to load into a0r and compute v0 from a0r. That's a valid transformation (the load's dest is chosen by regalloc: since v0 = a0r - 0x30, the load could target either).

Hmm, in the target the load targets v0 and then `move a0,v0`.

This is a regalloc outcome. The two forms differ by which pseudo the load writes.

OK. I've spent 14 min. Let me consider the possibility that this is a WALL (the pin is genuine). The evidence: the target's $v0/$v1/$a0/$a1 assignment requires the pin; lever-free the sign-extension temp / global priority rotates the temps.

But let me try ONE more high-value idea: use a *local* (block-scoped) declaration for the branch temps to change the allocno class (C0087). E.g., wrap each branch's body in a block declaring its own temps. That's a bigger rewrite.

Alternatively: since the function is small, maybe write the whole body differently, e.g., using `for`/`while`. Too speculative.

Given time, let me do a final batch of 5-6 quick variants and then record WALL with best 9.

Actually, wait. Let me reconsider the score-9 body t01: 65 ins vs 67. The missing `move a0,v0` is a real structural loss. The score 9 counts differences. Best = 9.

Hmm, but a WALL's best should ideally be the closest. 9 is decent.

Let me try: can I get the `move a0,v0` back while keeping the self-set extension? The move is missing because the load writes a0r. If I prevent that by making a0r's value differ... e.g., `a0r = v0 + 0;`? folds.

What if a0r is declared as a different type (s16)? `s16 a0r; a0r = v0;` then the store `sh a0r` and the move might survive. Let me try.

Also try `a0r` used in the comparison instead of v0.

Let me do a last batch: w01: t01 + `s16 a0r`; w02: t01 + a0r = (s16)v0; w03: p02 + a0r s16.
