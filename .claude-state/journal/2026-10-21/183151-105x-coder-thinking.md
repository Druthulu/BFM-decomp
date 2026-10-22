---
ts: 2026-10-22T00:31:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_65HYKrh8B7TLUtMFvitV
---
Same as c1 (4). The source order of the p10 assignment doesn't matter.

Item 4: WALL. best (lever-free) = 28 (v1). Let me record: WALL, best=28, tries=4 (base 39, v1 28, c1 4 — hmm, c1 is not lever-free; c2 6814 not lever-free; c3 4 not lever-free). The "tries" = the number of candidates scored. Let me count all scored candidates: base, v1, c1, c2, c3 = 5. best = 28 (the lowest score among lever-free bodies: base=39, v1=28).

Hmm, "best = lowest score of a lever-free body" → 28 ✓.

Wall tag: the mechanism = the p10 re-tie is load-bearing (it prevents the switch→jump-table conversion and it provides the hole/nop footprint); removing it explodes the function (6814). And the v6 re-tie can go but leaves a 4-residual (a nop in the wrong slot). Tag: I'll use "sched1-birth-boost"? Hmm, the dominant mechanism is the jump-table prevention (cse/jump-table conversion). There's a wall tag "cse-copy-merge" and "flow-unused-result"...

The switch→jump table conversion is a "cse" thing (gcc 2.7's cse.c does the case-table construction). So the tag "cse-const-addr"? No. Let me use a new tag: `cse-jump-table` (a `<pass>-<what>` new tag) — the re-tie inside the switch case blocks prevents gcc's cse.c from building a case table (the asm's presence keeps the block from being recognized as a simple switch case).

Hmm, is that accurate? The p10 asm is inside `case 0:`. Its presence prevents the switch from being converted to a jump table (the asm makes the case body non-trivial). Yes, plausible: gcc's cse builds a jump table when all the case bodies are simple enough; the asm's memory clobber changes that.

I'll use the tag `cse-case-table` with that mechanism. Hmm, but the tag should describe the wall mechanism. Let me phrase: "cse-case-table: the p10 re-tie inside case 0 keeps gcc's cse from building a case table (removing it: 6814 ins, a jump table); the v6 re-tie can go but leaves its nop one slot off (4)".

Hmm, that's a long evidence. Keep it ≤140 chars:
"cse-case-table: p10 re-tie blocks cse's case table (removing it: 6814 ins); v6 re-tie removable but its nop lands one slot off (4)"

That's ~130 chars ✓.

Now items 1 and 2 (the vol launder). Let me try the compound-assignment idea quickly:
Item 1: the launder is between the vol computation and the pan computation. Variants:
(a) `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` (compound division)
(b) `sx = sx + 0xA0; sx /= 0x14;`
(c) both.

Let me test (c) and (a)/(b) separately. Actually, let me think about which could matter: the launder's effect is a scheduling barrier between the two chains. A compound assignment changes the *set* structure of vol (2 sets) → maybe the vol chain's mfhi gets a different priority...

Let me just try:
V1: vol split with a compound division.
V2: pan split with a compound division.
V3: both.

Let me generate them from base.c (item 1's base = the launder-free version, score 30).

base.c's relevant text:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            
            sx = (sx + 0xA0) / 0x14;
```
V1: `vol = (0xA0 - av) * 0x7F;\n            vol /= 0xA0;`
V2: `sx = sx + 0xA0;\n            sx /= 0x14;`
V3: both.

Let me generate and score. 3 sed/scoring rounds = ~6 calls. Time is a concern but let me do it.

Note: the `&=` trick worked in items 5/8 because the masked value had a real op. Here `vol /= 0xA0` is a real division (in-place) — the same division, just split. The generated code should be identical (the div by a constant is expanded the same way) — hopefully.

Let me try.
