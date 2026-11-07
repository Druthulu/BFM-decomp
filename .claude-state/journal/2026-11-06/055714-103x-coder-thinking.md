---
ts: 2026-11-06T12:57:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vkjR6tR3h3xYS1rD6crh
---
No change. Let me try a fundamentally different route for the ba liveness: give `ba` a use that gcc keeps but that emits no extra insn. 

What emits no insn but keeps a value live? A *comparison that's already implied*? No.

Hmm, what about making `dst = ba` not the last use: `dst = ba; ... *dst = tv` — the loop's first use of dst could be written as `*ba = tv`? Then ba is used → but the target's store is via a0 (dst).

Hmm, what about writing the FIRST store as `*dst = tv;` and the SECOND as `*(ba + 1) = tv;`? no.

OK, radical idea: what if the copy `dst = ba` uses a *cast through a different type* that cse can't fold, e.g. `dst = (u16 *)(void *)ba;`? Same rtx.

What if the value assigned to ba is not directly forwardable: make it depend on a memory load cse can't duplicate, e.g. `ba = (u16 *)(tmp + (u8 *)dp);` where `tmp` is a variable... cse forwards `tmp`'s value.

Hmm — actually, what if I make the expression include a *volatile-free* but non-copyable operation like a division? no.

New angle: what if `dst` is NOT pinned and `ba` keeps its pin? Then the C: `register u16 *ba __asm__("$5")` (allowed, stays) and `u16 *dst;` (pin removed — removing a pin is allowed). Then `dst = ba` → `move <pseudo>, $5`; the loop uses the pseudo. The pseudo would be allocated a0 by local-alloc (first free?) → `move a0,a1` and the loop uses a0. That's exactly the target! And cse would still forward `$5` into the move and delete the $5 set... unless the pin forces the $5 set to exist (it does: `ba = ...` must set $5 — but if all uses are folded, the set is dead).

Hmm, cse deletes dead hard-reg sets. So the same issue.

Unless the pin makes $5 "used" (a `use` of $5 is emitted for pinned variables? gcc emits `(use (reg 5))`? no).

Let me test the hypothesis quickly: remove dst's pin and keep ba's. If we get `addu a1,...; move a0,a1` (2 insns) then cse did NOT delete it, and I'd have the target shape (with a0 from local-alloc).

That's a 30-second test. Let me also try removing ba's pin and keeping dst's.

Actually, careful: removing the dst pin means the target's $4 must come from local-alloc. Let me test both.
