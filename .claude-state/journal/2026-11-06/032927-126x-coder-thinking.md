---
ts: 2026-11-06T10:29:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H1g1wcTMWKobar87MOEe
---
Pinned body alloc:
- r76 (ret): pri 10000, refs 5, live 10, conflicts v1, prefers v0 → gets v0 (preference!)
- r72 (arg0): pri 8333 → s0
- r74 (flags): pri 6666, refs 5, live 15, conflicts v0,v1 → gets a0
- r73 (var_s1): pri 1304 → s1

So with the pin: fcopy is a hard reg (v1, not in the table). ret (r76) has "prefers v0" and conflicts v1 → gets v0. flags (r74) conflicts v0,v1 → gets a0. 

So the pin's role: fcopy occupies v1, so ret can't use v1 → gets v0 (its preference), and flags gets a0.

Lever-free: fcopy is a pseudo (r75, pri 2857). flags (r74, 16000) → v0. ret (r76, 11111) → v1. fcopy → a0.

To match: ret must get v0. With the pin, ret's preference is v0 and it conflicts v1 (because fcopy=v1 is live across ret's range).

Lever-free, ret's preference is v0 too (r76 "prefers v0"). But flags (pri 16000) grabs v0 first.

So: I need flags to NOT take v0. If flags's priority drops below ret's, ret gets v0 (preference), then flags gets... v1 or a0.

Hmm, but in the target flags=a0 (not v1). If flags drops below ret and fcopy, the order would be ret (v0), then fcopy (v1?), then flags (a0). That matches the target!

So I need the priority order: ret > fcopy > flags.

Current: flags (16000) > ret (11111) > fcopy (2857).

To get ret > fcopy > flags:
- ret: 11111 (keep)
- fcopy: must be > flags. Currently 2857 vs flags 16000. Need fcopy > flags.
- flags: must be lowest.

fcopy's pri 2857 (refs 2, live 7). flags 16000 (refs 4, live 5).

To make fcopy > flags: boost fcopy's refs or reduce flags's.

Hmm, this is a 3-way reorder. Hard.

Alternatively, use the pin's exact mechanism: fcopy occupying v1 forces ret to v0 (preference) and flags to a0. Lever-free, fcopy is a pseudo that gets a0 (lowest priority). If fcopy got v1 instead (higher priority than ret?), then ret (prefers v0) would... hmm.

Let me think: the target's allocation order is ret (v0, preference), flags (a0), fcopy (v1). If fcopy's priority were between ret and flags, the order would be ret (v0), fcopy (v1), flags (a0). That matches!

So I need: ret > fcopy > flags.

ret 11111. flags 16000. fcopy 2857.

To get fcopy > flags: fcopy's pri must exceed flags's. If flags's pri drops to ~2000 and fcopy stays 2857, then ret (11111) > fcopy (2857) > flags (2000). 

flags: refs 4, live 5 → 16000. To drop to ~2000: refs 3, live 7 → 1*3/7 = 4285 (still > 2857). refs 2, live 5 → 8000. Hmm.

Or lengthen flags's live: refs 4, live 16 → 1*4/16 = 2500 < 2857! 

flags's live is 5 (short: from the call result to the &0x2000 test). If I extend it to 16, its pri drops to 2500 < fcopy 2857.

How to extend flags's live? Move a use of flags later. The uses are the two tests. If I move the `flags & 0x2000` test later... it's in the else-if chain.

Hmm, alternatively reduce flags's refs to 3 AND lengthen live.

Actually, the simplest: reduce flags's refs by using `fcopy` for one test, and lengthen fcopy's life. Hmm.

Wait, m1 (tests use fcopy) didn't change the score. Because cse merged them.

Hmm.

Let me reconsider. Maybe there's a cleaner approach: make fcopy's refs higher by using it more. fcopy is used in `fcopy & 0x8000`. If I also use fcopy in the tests (m1), fcopy's refs increase and flags's decrease. But cse might still merge.

Let me check m1's alloc. Actually m1 scored 11 (no change), so the alloc didn't change.

Hmm, why not? Because the compiler treats fcopy and flags as the same value (cse) and uses one pseudo for both? The RTL showed r74 (flags) and r75 (fcopy) as separate pseudos with `move r75,r74`. So they're separate.

If the tests use fcopy, then r75's refs increase and r74's decrease. But the score didn't change, so the allocation stayed. Hmm.

Let me dump m1's alloc to check.

Actually, time. Let me reconsider the whole item 4. I've spent ~10 min. The score is 11. Let me try a few more targeted things:

Idea: make `ret`'s preference for v0 stronger or its priority higher. ret pri 11111. If I boost ret via a do-while (n1 did, no change — because the do-while boosts flags too).

Let me check n1's alloc.

Hmm, let me think about the CLEANEST fix: the target's key is fcopy=v1 (occupying v1 so ret gets v0). Lever-free, fcopy gets a0. To make fcopy get v1, boost its priority above flags's and... but ret also wants v0.

Order needed: ret(v0), fcopy(v1), flags(a0).

Actually, maybe simpler: make fcopy's priority HIGHER than ret's? Then fcopy gets v0? No, ret prefers v0.

Hmm, the allocation is by priority order, but preferences matter: ret "prefers v0". In global-alloc, a qty with a preference gets that reg if free when allocated. The order is by priority: 76 (ret) first, then 72, then 74 (flags), then 73. With the pin, fcopy is a hard reg (v1) and is in the conflict set.

Lever-free order: 74 (flags, 16000) first → v0. Then 76 (ret, 11111) → v1 (v0 taken). Then 72 (arg0) → s0. Then 75 (fcopy) → a0. Then 73 → s1.

Target order: 76 (ret) → v0, 72 → s0, 74 (flags) → a0, 73 → s1. And fcopy=v1 (hard).

So lever-free, flags is FIRST. To match, flags must not be first.

flags pri 16000. If I could reduce flags's priority below ret's 11111, ret would go first → v0. Then flags (second or third) → v1 or a0. If fcopy (2857) is after flags, flags → v1, fcopy → a0. Target has flags=a0, fcopy=v1. So I need fcopy > flags.

So: ret > fcopy > flags.

flags must be LAST among the three. flags pri 16000, fcopy 2857. Need fcopy > flags.

If flags's pri drops to 2000 (refs 4, live 20): then ret 11111 > fcopy 2857 > flags 2000. 

flags's live = 5. To make it 20, extend the live range. flags is born at the call result (insn 52) and dies at the last use (insn ~63-82). Hmm, live 5 is short. The RTL insn numbers: flags def insn 52, last use ~57? Let me look: r74 used at insn 52 (def), 55 (fcopy=flags), 59 (and 0x4000), 87 (and 0x2000, dies). Live 5 means (87-52)/... hmm, the table says live 5. Maybe the insn numbers are compressed.

Hmm, flags's live is 5, which is already short. To lengthen it, I'd need to move a use later — but the uses are already spread.

Wait, the table says flags live 15 in the PINNED body (r74 live 15) and 5 in the nopin body (r74 live 5). Interesting! The pin changes flags's live length from 5 to 15. Why? Because the keepalive is also present in the pinned body. The keepalive on flags extends its live range to the end of the function (the asm use at the end)! That's why live 15 vs 5.

So the keepalive EXTENDS flags's live to the end → pri drops from 16000 (live 5) to 6666 (live 15). That's the keepalive's role!

In the nopin (keepalive removed), flags live 5 → pri 16000 → grabs v0.

So I need a REAL use of flags near the end of the function to extend its live range, replacing the keepalive. 

The keepalive `__asm__ __volatile__("" : : "r"(flags));` at the end is a use of flags at the end. A real C use of flags at the end... The function returns `ret`. Could I use flags in the return? E.g., `return ret;` → maybe `return ret + (flags & 0);`? identity, forbidden.

Hmm. But the target's flags=a0 requires flags's live to be long. In the target, flags IS used at the end? Let me look: the target's flags (a0) is used in the tests (dd70, dd84) and... the last use is dd84 (`andi v0,a0,0x2000`). After that, a0 isn't used. So flags dies at dd84. Its live is from dd6c to dd84 = short.

Hmm, but the pinned body's flags live is 15 (extended by the keepalive). And the target (byte-identical) has flags=a0. So the keepalive is what makes flags=a0!

So the keepalive is doing double duty: extending flags's live to drop its priority.

A real C use of flags at the end: what could it be? The function returns ret. If the original source had something like `flags` used in the return... 

Hmm. Wait — maybe the original source used `fcopy` at the end (the &0x8000 test is near the end). fcopy's use extends fcopy's live. But flags?

The target: flags=a0. flags's last use is dd84 (the 0x2000 test). fcopy's last use is dd8c (the &0x8000 test). So fcopy dies later than flags.

Hmm.

OK, this is the keepalive's role: extend flags's live. To replicate with real C, I need a real use of flags after the 0x2000 test. 

What real use? Maybe the original source had `if (flags & 0x8000)` instead of `fcopy & 0x8000`? Then flags is used at dd8c (later) → live longer! And fcopy would be... hmm.

Let me test: use `flags & 0x8000` instead of `fcopy & 0x8000`. Then flags's last use is later → live longer → pri drops. And fcopy might become unused (its only use was the &0x8000) → fcopy would be dead! Unless fcopy is used elsewhere.

Hmm. The source has `fcopy = flags` and `if ((fcopy & 0x8000) == 0)`. If I change to `flags & 0x8000`, fcopy is unused → dead → the copy disappears. That changes the code.

Hmm.

What if BOTH: `if ((flags & 0x8000) == 0)` AND fcopy is used somewhere? 

Actually, let me reconsider the original source. The `fcopy` variable was likely introduced by the reconstruction to force a copy. The original might have used `flags` directly. Let me test: remove fcopy entirely, use flags everywhere:
```
if (flags & 0x4000) ...
else if (flags & 0x2000) ...
else { ret = 4; if ((flags & 0x8000) == 0) ret = var_s1; }
```
Then flags is used at the end (the &0x8000 test) → live longer → pri drops. And no fcopy. But the target has a `move v1,a0` (fcopy copy) — so the original DID have a copy. Hmm.

Hmm, the target's `move v1,a0` at dd78 (delay slot) and `andi v1,v1,0x8000` at dd8c. So v1 holds a copy of a0 (flags) used for the &0x8000 test. That's fcopy!

So the original had a copy `fcopy = flags` used for the &0x8000 test. And fcopy=v1.

OK so the original source is like ours. The keepalive in our reconstruction extends flags's live. In the original, flags's live was already long enough because... hmm.

Wait — maybe in the original, `flags` was used AFTER the &0x8000 test? Or the original's variable structure made flags live longer.

Hmm, let me look at the target asm: is a0 (flags) used after dd84? Let me check dd88-dd98: `beqz v0,dd98; andi v1,v1,0x8000; j; li v0,1; bnez v1,...; li v0,4; move v0,s1`. No a0 use. So flags dies at dd84.

But the RTL live length is computed pre-scheduling. The RTL order might have the &0x2000 test later. Hmm.

OK, let me try the practical approach: find a real C construct that extends flags's live to the end. What about using flags in the return expression legitimately? 

The function returns ret. What if `ret`'s last assignment is `ret = var_s1;` and we... no.

Hmm. What if I move the `fcopy = flags` statement to AFTER the tests? Then flags is used later (at the fcopy assignment). But the target's `move v1,a0` is at dd78, between the 0x4000 and 0x2000 tests. Hmm, so fcopy=flags is in the middle.

What if `fcopy = flags` is placed after the 0x2000 test (just before the &0x8000 test)? Then flags's last use is later → live longer. But the target has the copy at dd78 (before the 0x2000 test). Hmm.

Actually, let me just try: move `fcopy = flags;` to after the if/else-if, inside the else block before the &0x8000 test. And other placements. Let me test empirically.

Let me also test: remove fcopy and use flags in the &0x8000 test (the copy would then be... hmm).

Let me batch:
- o1: `fcopy = flags;` moved to just before the `if ((fcopy & 0x8000)...)` inside the else.
- o2: use `flags & 0x8000` instead of fcopy, keep fcopy assignment (fcopy unused → maybe dead).
- o3: `fcopy = flags;` at the very end (after the if/else), and use flags in the tests.
- o4: move the keepalive... no.

Let me test o1-o3.
