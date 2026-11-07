---
ts: 2026-11-06T06:47:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6aJWs6rpOHNyUEDY7wBq
---
Now I see the target clearly:
```
$L261:
	subu	$2,$2,$16     ; var_v0 = 0x20 - var_s0
	move	$4,$2         ; var_a0 = $2  → var_a0 in $4 (a0)
	sll	$2,$2,16
	bgez	$2,$L262
	move	$4,$0
$L262:
	li	$20,-80       ; k50 = $20 (pinned)
	li	$18,-240      ; kF0 = $18 (pinned)
	li	$19,-256      ; k100 = $19 (pinned)
	#APP #NO_APP
	move	$2,$fp       ; var_v0 = var_fp
	move	$3,$23       ; var_t7 = var_s7 ($3 pinned)
	sb	$2,52($sp)
	...
	move	$2,$4        ; var_v0 = var_a0
```
So the target: var_fp in $fp, var_s7 in $23 (s7), var_a0 in $4 (a0).

Interesting: `li $21,-64` (k40) is inside the bgez delay slot — k40 is in $21 (s5) unpinned.

Now mine: var_fp=s8, var_s7=s7, var_a0=v1.

The differences: var_fp in $fp vs s8, and var_a0 in $4 vs $3.

Hmm, "fp" is $30. In mine, var_fp is in s8 ($30 is fp?). MIPS: $30 = fp = s8. Same register! ($30 = fp = s8.) So "s8" and "fp" are the same register — the register pairs "s7->fp x1, fp->s7 x1" are just name differences.

OK so the remaining differences:
1. var_a0: target $4 (a0), mine $3 (v1).
2. The v0/v1 swap in the three computations: target uses $2 (v0) for the temp; mine uses $3 (v1) — because mine's var_a0 is in $3 (v1), the temp can't be $3? No wait, mine: `subu v1,v0,s0; move v0,v1; sll v1,v1,0x10` — the temp is v1 and var_a0 is v0.

Hmm, mine has var_a0 in v0 and the temp in v1; the target has var_a0 in a0 and the temp in v0.

Why does mine put var_a0 in $2? var_a0 is live across the stores (used at `move v0,v1`... hmm).

The difference: in mine, var_a0 (a local pseudo) gets $2 — the first choice in local-alloc. In the target, var_a0 got $4.

Since var_a0 is assigned in the same block and used later, local-alloc gives it the first free reg. In the target, $2 was taken by the temp (var_v0's value?) at that point, so var_a0 got $4? Hmm.

Wait — in the target, the pinned var_t7 = $3 is reserved. So $3 is unavailable for locals! That's why the target's temps use $2 and var_a0 uses $4.

In mine (no pin), var_t7 is a normal pseudo somewhere, freeing $3, so var_a0 lands in $3 (or the temp does).

So the pin on var_t7 = $3 is load-bearing for the local allocation of $2/$3/$4 in this block.

Could plain C make var_a0 land in $4? If var_t7's pseudo naturally took $3... In mine, where does var_t7 go? Let me check the asm.

Hmm, this is again the "hardreg-reserve" mechanism: the pinned reg reserves a register for the whole function, changing all local allocations.

Given the time (item 4 at ~16 min, 40 tries), and the pattern, I'm fairly confident this is a wall.

But let me do one quick check: is there any plain-C way to make the value chain use $2 for the temp? E.g., splitting the reused var_v0 (the temp) so each computation gets its own pseudo, each being block-local and taking $2 first... sp1 did that (64).

Hmm, alternatively: make var_a0 live longer/shorter.

Let me try 2-3 more targeted variants quickly:
- var_a0 declared as u16? no.
- `var_a0 = var_v0 = 0x20 - var_s0;` → `var_v0 = 0x20 - var_s0; var_a0 = var_v0;` (w2 = 54).

I think we're done: record item 4 as WALL with best 45 (v2/v_w3/w4 — the var_a0 direct-store variant), tries ~40, tag `global-hardreg-reserve` (the pin reserves $3/$18/$19/$20 for the whole function; lever-free the local temps take $2/$3 and var_a0 lands in $3).

Hmm, "global-hardreg-reserve" is defined as "the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". That fits!

Let me double check the mechanism with the target: k50=$20, kF0=$18, k100=$19 pinned; lever-free, are they in registers at all? In mine, the `li` constants might be rematerialized. Let me quickly check mine's asm for "li" counts... 

Actually, since both have ~162-163 insns, mine must also keep them in registers (otherwise more insns).

Let me do a final quick check of mine's asm head to confirm the register roles, then record. Actually, time. Let me just record with the evidence I have: the residual is a v0/v1 + s7/s8 bank swap; var_a0 in $3 vs $4; the pins reserve $3/$18/$19/$20.

Hmm, but I should be careful to state only what's backed. My evidence: score 54/45, register pairs v1->v0 x19 etc., and the target asm showing var_a0 in $4 with $3 pinned for var_t7.

Let me do one more experiment that directly tests the hypothesis: keep ONLY the var_t7 pin (drop the other three + the launders) and see if the score drops a lot. If yes, the $3 reserve is the key.

That's a useful diagnostic and cheap. Let me test a few subsets:
- s1: keep only var_t7 pin ($3), launder removed, other pins removed.
- s2: keep only the k pins.
- s3: keep var_t7 + k pins (orig minus launders) = the PARTIAL candidate!

Actually s3 is the PARTIAL test: orig minus the 4 launders, keeping all pins. If that scores 0 → PARTIAL:pin! Let me test that first — it's the most valuable.

The launders here are `__asm__("" : "=r"(k40) : "0"(k40));` etc. Removing them: does the body still score 0? The launders might be doing something (the moves `move $2,$fp` etc.).

Let me test: orig with the 4 launder lines deleted (pins kept).
