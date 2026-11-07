---
ts: 2026-11-07T00:14:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EDmik5azqHk7qiyss16v
---
In the pinned body:
- r76 (base): live 42 → s3
- r78: live 32 → s5 (this is y0!)
- r79: live 31 → s1 (y1)

And x0 is not in this list (7x) — maybe x0 is r75? Let me grep more. Also white is pinned so not an allocno.

Hmm, r78 live 32 → y0, r79 live 31 → y1. In the pinned body, y0's live is 32, y1's 31.

The target assignment: y0=s5 (r78, live 32), y1=s1 (r79, live 31), base=s3 (r76, live 42), x0=s1? no, x0 must be elsewhere.

Hmm, r79 in s1 and x0... let me get all registers. Let me grep the full list.

Actually, the key insight: in the pinned body, y0 has live 32 (longer than y1's 31) → y0's pri is LOWER than y1's. So y1 allocates before y0! That's why y1=s2-ish and y0=s5.

In my lever-free body, y0 and y1 both have live 31 → tie → y0 (lower qty) allocates first.

So the difference is a ONE-INSN live-length difference caused by the launder/pin! The launder on x1 adds an insn, extending y0's live by 1 relative to y1's.

Interesting. So to get the target's order, I need y0's live length to be 32 while y1's is 31.

Where does that difference come from? In the pinned body, the launder `__asm__("" : "=r"(x1) : "0"(x1))` is between `x1 = a0 + 3;` and `y1 = a1 + 3;`. This asm is an extra insn in the live range of y0 (which was born before the launder) but not of y1 (born after).

Wait: y0 = a1-3 is the first statement, before the launder. y1 = a1+3 is after the launder. So y0's live range includes the launder insn; y1's doesn't. Hence y0 live 32, y1 live 31.

Lever-free, we need an equivalent: y0's live must be one insn longer than y1's. Without the launder, both are 31.

Hmm! But this is exactly the kind of thing a real C statement between them could do. E.g., if there's a real statement between `y0 = a1 - 3;` and `y1 = a1 + 3;` that is in y0's live range but not y1's.

In the C, between y0 and y1 there is `x1 = a0 + 3;` (and the launder). So y0's live already includes `x1 = a0+3`. To add one more insn, I could add another statement between y0 and y1 that stays in the code.

But any added statement must produce identical target code! Hmm.

Wait — actually, let me reconsider. The live length difference of 1 might arise from a different C structure. In the target, y0's live is 32 and y1's 31. In my lever-free body both 31.

Hmm, but my body's statement order is y0, x1, y1, white, x0. The launder was between x1 and y1. Removing it removes one insn from y0's live range... but also from x1's.

What if I move a statement to be between y0 and y1 such that y0's live grows by 1? E.g., move `white = 0xFF;` between y0 and y1? But then white's birth order changes.

Hmm, but the search over the 120 permutations already explored orders and the best was 22. The live lengths depend on birth order: a variable's live starts at its first assignment. If y0 is born first and y1 later, y0's live is longer by the number of insns between them.

In my permutation search, I permuted the 5 assignments. If y0 is first and y1 is later (with more insns between), y0's live is longer → lower pri → allocated later. The best permutations had y1 before y0 (index 2 first). Hmm.

Wait, in the target, y0 has live 32 > y1's 31 → y0 allocates later. So y0 must be born before y1 by one insn. In the permutation (2,0,1,3,4) = y1, y0, x1, white, x0: y1 is born first, so y1's live is longer → y1 allocates later. That's the opposite!

Hmm, but the search found 22 for that. Let me look at what the 22 body's registers are.

Actually, the live lengths also depend on the *last* use. Let me reconsider.

Let me look at the target's exact live values: y0 (r78) live 32, y1 (r79) live 31, base (r76) 42.

And in my lever-free: y0 live 31, y1 live 31, base 42.

So I need y0 live 32. y0's live = from `y0 = a1-3` to its last use. The last use is `line.y0 = y0` (in the struct stores). So y0's live spans from its assignment to the store. In the C, the stores are after all the assignments.

Hmm, so y0's live = (position of line.y0 store) - (position of y0 = a1-3) + 1. In my body, y0 is assigned first (position 1) and y1 assigned 4th. So y0's live should be LONGER than y1's by 3 insns, not equal.

But the table says both 31! Hmm, maybe the live length isn't death-birth in insns; the dump's "used 3 times across 31 insns" is the live length.

Hmm, y0 assigned at insn ~2, y1 at insn ~5. Both used at the struct stores ~insn 30. So y0 live ~28, y1 live ~25. But the dump says 31 and 31.

I'm confusing myself. Let me look at the actual RTL. Ugh.

Let me step back and take the empirical approach: I searched 120 statement orders and the best is 22. That's a wall-ish result but not 0.

Hmm, but maybe the issue is not the statement order but the *launder replacement*. The launder `x1 = x1` (asm) — lever-free we need a real 2nd set of x1 that produces the same code. The launder is on x1, and x1 = s0 in the target.

Wait, actually, what does the launder DO here? `x1 = a0 + 3; __asm__("" : "=r"(x1) : "0"(x1)); y1 = a1 + 3;`

The launder creates a new x1 pseudo (a copy from the old). In the target, x1 is pinned to s0, so the asm's output is also s0 (tied "0"). The asm emits no instruction (empty), but it's an RTL insn (a set of x1). So it adds an insn to the RTL (which may be deleted later by... it's volatile? No, `__asm__("")` non-volatile — it might be deleted if the output is unused. But x1 is used later).

So the launder adds a set insn for x1. That extra insn affects live lengths.

Lever-free, we need x1 to have a real 2nd set that doesn't add code. Hmm.

What if x1's value is computed twice? E.g., `x1 = a0 + 3;` then later `x1 = x1;`? identity.

Hmm.

OK, given the complexity, let me try a different practical approach: search over (statement order × small variants) but that's a big space.

Let me check the best 22's diff to see what remains. Maybe only 2-3 register pairs are off, and a small tweak fixes it.

Let me score (2,0,1,3,4) and look.

Actually, let me reconsider the whole problem. The target's natural assignment (pins aside) is: x0=s1, y1=s2, base=s3, y0=s5. And x1=s0, white=s4 are pinned.

So I need: x0→s1, y1→s2, base→s3, y0→s5.

Hmm, y0→s5 (last). base→s3.

Let me get the priorities needed:
Order: x0, y1, base, y0 (then s1, s2, s3, s5).
pri(x0) > pri(y1) > pri(base) > pri(y0).

In the pinned body: base live 42 (pri 714), y0 live 32 (pri 937), y1 live 31 (pri 967).

Hmm: y1 967 > y0 937 > base 714. So order by pri: y1, y0, base. But target order is y1, base, y0. So base allocates before y0 in the target.

Hmm, base has pri 714 (lowest) but gets s3 before y0 gets s5. Contradiction unless the register preferences (find_free_reg prefs) put base in s3.

Base is a pointer used as `&base[(u16)D_800B9A02 * 20]` — a call argument. The address computation... hmm.

OK, honestly this is a deep local-alloc puzzle. Given the time (item 3 started 17:10, now ~17:20?), and the budget of 20-30 min, let me do a few more targeted tries and then record a WALL.

Actually — wait. Let me reconsider: maybe the answer is to NOT declare x1/x0/white as s16 but as s32? No, the struct fields are s16.

Hmm, what about the launder's replacement? Let me think about what the launder does to the target's allocation: it's on x1 (pinned). It adds an RTL insn.

What if the launder's real purpose is to make x1's live range longer/shorter, affecting the local-alloc order?

Hmm.

Let me look at this from the "what did the original source look like" angle: the original C probably had:
```
y0 = a1 - 3;
x1 = a0 + 3;
y1 = a1 + 3;
white = 0xFF;
x0 = a0 - 3;
```
with no launder. And the natural allocation would be... my baseline (26). So the original source's allocation differs from my baseline. Why? Because the decomp author's C isn't the original.

The target's assignment x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.

Hmm, interesting: s0=x1, s1=x0, s2=y1, s3=base, s4=white, s5=y0.

What if the original declared the variables in a different order or used different expressions?

Let me think about qty birth order: the order of first assignment. Target's regs suggest the allocation order x1, x0, y1, base, white, y0. If local-alloc assigns in birth order for ties... 

Actually, hold on. Let me reconsider: maybe local-alloc's order here is by pri, and the pri values in the target differ because of the launder.

Target (pinned) lreg: base live 42 (r76), y0 live 32 (r78), y1 live 31 (r79). What about x0 and white? Let me get the full list from the pinned dump. Let me grep r74, r75, r77 too.

Earlier output for the pinned body only showed r72,r73,r76,r78,r79,r89. So x0, white, x1 are hard regs (pinned: x1, white) or... x0 must be an allocno. Maybe r75? It wasn't in the grep because the regex (7[2-9]|8[0-9]) should include r75. Hmm, r75 wasn't printed → maybe x0's pseudo has a different number, or it's in a different block.

Let me print all "Register N used" lines in the pinned function.

Time check — let me be quick.
