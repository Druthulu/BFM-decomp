---
ts: 2026-11-06T05:56:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZkyvYZZn7yk7oSkJlxx8
---
k10: mine has an extra `andi v0,s1,0xffff` before the `bne`. The rest matches except the v0/v1 swap (the pointer/load register allocation, which is also in n1/n3).

So with k10, the second test survives! And the remaining issues:
1. The extra `andi` (from the mask).
2. The v0/v1 swap: target `lw v0,32(s0); lhu v1,18(v0); addiu s3,v1,256; addiu v1,v1,-896; sh v1,18(v0)` vs mine `lw v1,32(s0); lhu v0,18(v1); addiu s3,v0,256; addiu v0,v0,-896; sh v0,18(v1)`.

Wait — the diff at [12:13] says mine `lw v1,32(s0)` target `lw v0,32(s0)`. Hmm, but earlier (n1/n3) mine had `lw v1` and target `lw v0` too? Let me check the n3 diff: yes, "11 lw v1,32(s0) | lw v0,32(s0)" — same swap. So this swap exists in all variants.

Hmm, so there are two remaining issues: the v0/v1 swap and (in k10) the extra andi.

Interesting: in k10 the register pairs show only v0->v1 x5 and v1->v0 x3 (the swap), plus the andi.

Now, the v0/v1 swap: target has q (the unk20 pointer) in v0 and u (the load) in v1. Mine: q in v1, u in v0.

Wait, but earlier the target asm showed:
```
1850 lw v0,32(s0)      q = unk20
1858 lhu v1,18(v0)     u = q->unk12
1860 addiu s3,v1,256   hold
1864 addiu v1,v1,-896  u -= 0x380
1868 jal func_8012BD3C
186c sh v1,18(v0)      q->unk12 = u
```
Yes: q=v0, u=v1.

Mine: q=v1, u=v0.

Hmm, why? The pin `one`=$18 shouldn't affect q/u. Let me check: in the original (pinned), q=v0, u=v1. Without the pin, mine has q=v1, u=v0. So the pin affects q/u's allocation!

Hmm, because `one` is a *global allocno* (live across blocks), and pinning it to $18 removes it from the competition... but q/u are local. Hmm.

Actually, in the target, `hold` is s3, `one` s2, cc s1. Without the pin, `hold` s2, `one` s1, cc v0. And q/u swap.

Hmm, this is a global-alloc priority effect. Ugh.

OK, so item 4 needs: (a) the launder replacement that keeps the second test (k10 does, with an extra andi), and (b) the pin replacement that fixes the allocation.

Both are hard. Let me see if I can remove the extra andi in k10.

The `andi v0,s1,0xffff` comes from `(cc & 0xFFFF) != one`. Since cc is known to be in [-32768,32767]... gcc doesn't know that (cc = (s16)call — it should know). Hmm.

What if we use `(u16)cc` instead? `if ((u16)cc != one)` — a cast to u16 then promoted to int → zero-extend → andi. Same.

Hmm.

What if the mask is applied to `one` instead? `if (cc != (one & 0xFFFF))` — one is 1, folds.

Hmm.

What if we use a different opacity: `if (cc != one)` where cc is compared via a *signed/unsigned* trick that makes gcc uncertain without an extra instruction?

Idea: make `cc` an `s16` variable and compare `if (cc != one)` — h1 (s16 cc) = 26. Hmm.

OK, what about the v0/v1 swap? That's the pin's effect. Let me isolate: in k10 the pin is removed. What if I keep the pin? Then it's not lever-free.

Hmm.

Let me think about the pin's mechanism: `register s32 one __asm__("$18")`. This makes `one` a hard-reg variable in s2. Effects:
1. `one` doesn't compete for registers → other locals shift.
2. The `li s2,1` is forced.

Without the pin, `one` is a global allocno; it took s1 in n2 (and cc went to v0, q/u swapped).

To get the target's allocation without the pin, we'd need `one` to be in s2 naturally. That's a global-alloc priority thing.

Hmm, this looks like a WALL. But k10 gives 10, which is better than 24. For the WALL, "best = lowest score of a lever-free body" → best 10.

But wait — maybe I can combine k10's idea with other tweaks to fix the v0/v1 swap. Let me think about the swap: q and u are locals in the first block. Target: q=v0, u=v1. Mine: q=v1, u=v0.

Local-alloc assigns by density. q is a pointer (used 3 times?), u is the loaded value (used 4 times). Hmm.

Hmm, actually in the target, q=v0. With the pin, `one` is hard $18, so it doesn't take any of $2/$3. The locals q and u compete for $2/$3: target q=$2, u=$3.

Without the pin, `one` (a global allocno) is allocated by global_alloc, which... hmm, global_alloc assigns global allocnos first, then local-alloc handles the rest. The pin removes `one` from global_alloc's set.

Hmm, but why would q/u swap because of the pin? The pin also affects... hmm.

Let me look at the target's asm again: `one` is in s2 ($18) — a callee-saved reg. cc in s1 ($17), hold in s3 ($19). Without the pin, one in s1, hold in s2, cc in v0.

So the pin's removal shifts: one: s2→s1, hold: s3→s2, cc: s1→v0.

Interesting. The global allocnos: one, hold, cc are all live across blocks? hold is live across the call (used at rejoin). cc is live across the call.

Hmm, in n2 (pin removed), cc is in v0 — but v0 is call-clobbered and cc is live across the call! That would be wrong... unless gcc inserts a copy (the `move v0,s1` we saw). Indeed, n2 had `move v0,s1` before the beq — so cc is moved to s1 before the call and back? Hmm.

Wait, in n2 the asm had `move v0,s1; beq v0,s1,18c8`. So cc was copied to s1 before the call, then compared. So gcc put cc in v0 and also in s1? That's the "move v0,s1" at insn 27. Hmm, confusing.

OK. This item is a WALL. Let me record it with best 10 (k10).

But I need ≥30 tries and ≥20 min. Item 4 started at ~22:52 (when I read the def). Now 22:57 maybe. I have ~18 tries (orig, n1, n2, n3, g1-g4, h1, h2, k1-k10 = 19 lever-free). Need 30. Let me do 11 more tries.

Let me explore more around k10: 
- k10 + different widths
- k10 + `(u16)cc`
- k10 + the mask in the second test instead of the first
- k10 + `cc & 0xFF` etc.

And also try to fix the v0/v1 swap with declaration orders.

Let me generate ~11 variants.

Actually, let me think about the andi removal: `(cc & 0xFFFF) != one`. Since cc = (s16)func(...), gcc knows cc's range is [-32768,32767]... apparently not enough to fold the AND. But maybe if we write the cast as `(u16)` and compare to `(u16)one`... hmm.

Alternatively, use a mask that gcc knows is redundant for the range but still creates opacity? E.g., `cc & 0xFFFFFFFF`? folds.

What about `(s32)(s16)(cc & 0xFFFF)`? Hmm.

Let me try `if ((u16)cc != one)` and `if (cc != (s16)one)`.

Also, what about applying the opacity to `one` instead: `if (cc != (one & 0xFFFF))`? one=1, folds.

Hmm.

Let me also try: the first test `if (cc != one)` replaced by `if ((cc & 0xFFFF) != (one & 0xFFFF))` — 2 andis. Worse.

Let me generate a batch and score.
