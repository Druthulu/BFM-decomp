---
ts: 2026-10-22T10:35:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_C7uNzJydu8ewrg9POCxU
---
Still 14 for 8018389C (85 scored tries). Time ~04:37.

Let me now do the same for 8017D81C (needs ~15 more min), then write up.

Let me think about 8017D81C once more, with the "pseudo birth" insight. The target's x/y/z are born at the assignment point. The launder's asm reads them there.

Hmm, what if the constants' pseudos were born at the assignment because they're used by a *later* pseudo that's born earlier? no.

Hmm, what if the constants were assigned to variables whose values are used in the *same* statement where they're assigned? no.

Hmm — what if the assignment statement itself USES the variable? Like `x = -0x680;` → the set's dest is x; cse's forwarding replaces the uses of x with the constant and the set dies. If the SET were not dead... hmm: the set dies because all its uses were replaced by the constant.

Hmm! What if x were used in a way that is NOT a simple read — e.g. its ADDRESS taken? That would force it into memory ✗.

What if x were used as a *call argument*? Hmm! A call argument use is still a read → cse would forward it too (the argument becomes the constant). Hmm, but then the call's argument setup would show "li v0,-1664" — hmm, that IS what the target shows, but as a separate li in a register ✓.

Hmm! Wait: in the target, the li's are in v1/a1/a0 — a *register*, not a caller-saved arg reg necessarily.

Hmm, hmm. What if x/y/z were used by the do-while loop... no.

Let me try a couple of "extra use" variants to see the effect (they're levers-ish, but let me at least learn): e.g. `D_80192CE0 = x;` → `D_80192CE0 = x;` hmm.

Honestly, let me accept the wall. Let me use the remaining time on more mechanical tries for 8017D81C (the requirement is time + tries) and then write everything up carefully.

Let me do 2 more batches of ~12 for 8017D81C with the new classes Ilisted.
