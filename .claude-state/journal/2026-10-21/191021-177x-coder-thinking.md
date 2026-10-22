---
ts: 2026-10-22T01:10:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bGzRbw13A4KlXYEug847
---
The target:
```
1b28: lw a0,32(s0)      ; case0: the arg for func_8001C810
1b2c: lui a1,0x0
1b30: addiu a1,a1,0
1b34: jal func_8017BEBC
1b38: nop
1b3c: li a0,409          ; callarg0 = 0x199
1b40: lw v1,32(s0)       ; e = unk20
1b44: j 1b6c             ; goto shared
1b48: li a1,2            ; argmode = 2 (delay slot)
1b4c: lw a0,32(s0)       ; case1
...
1b60: li a0,409
1b64: lw v1,32(s0)
1b68: li a1,3
1b6c: lw v0,4(v1)        ; shared
```
So the target has the `li a0,409` BEFORE the `lw v1,32(s0)`.

My candidate (pg017) has them swapped: `lw v1,32(s0)` then `li a0,409`.

So the scheduler put the `li` in the delay slot of the *jal* (1b34) in the target, and in mine it's after the `lw`.

Hmm, the delay slot of the jal at 1b34 is 1b38 (nop). Hmm, so the `li a0,409` at 1b3c is *after* the jal (in the fallthrough).

So the target's order: [jal, nop], [li a0,409], [lw v1,32(s0)], [j shared], [li a1,2].
Mine: [jal, nop], [lw v1,32(s0)], [li a0,409], [j shared], [li a1,2]?

Hmm, from the earlier residual: "insert mine[44:44] target[44:45]: 44 -- | li a0,409" and "delete mine[45:46] target[46:46]: 45 li a0,409 | --". So the target has li a0,409 at 44 and mine at 45 — with the target having *something else* at 45. Hmm, since both have 89 instructions, the difference is a swap of two instructions: the target [44]=li a0,409, [45]=lw v1,32(s0)?? and mine [44]=lw v1,32(s0), [45]=li a0,409.

So the *order* of the two instructions differs: the target loads the constant first, then the pointer; mine loads the pointer first.

That's a scheduling choice between two independent instructions. The scheduler (sched1/sched2) ordered them differently. The launder's removal changed the scheduling.

To flip it: hmm, the statement order in the source is `callarg0 = 0x199; e = unk20;` — so the source order matches the target's instruction order (the li first, then the lw). In mine, the scheduler reordered them (the lw first).

Hmm! So the scheduler *reordered* them in mine but not in the target. The scheduler's decision depends on the block's contents.

Hmm, what if I *swap* the source order (e = unk20; callarg0 = 0x199;)? I tried the permutations (ordgen) — all 12 scored 2. Hmm, so the source order doesn't matter (the scheduler normalizes).

Hmm. What else? The number of instructions in the block (the do-while adds a block). Hmm.

Let me try: the *e* site's replacement = a do-while + a real re-read (re26: cast_dowre = 2). Hmm.

What if the e site's replacement were something that adds a *different* kind of instruction to the block? E.g. a real re-read of e (a `lw`) — that's what "dowre" does (2).

Hmm, what if the v1 site's replacement were a *real 2nd set* (v1 = mode) instead of the cast? Let me check the re2 results: re26_cast_dowre = 2; the "re_*" variants (the first site = a real 2nd set) — they weren't in the top 5. Let me get the full list.

Let me try a couple of specific things:
1. The v1 site: `v1 = mode;` (a real 2nd set) — hmm, the re* variants cover it.
2. The e site: the do-while + the re-read.

Let me look at the full re2 list for D96C.
