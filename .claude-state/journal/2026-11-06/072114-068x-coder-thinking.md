---
ts: 2026-11-06T14:21:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f0sfpafXajV0gC3qbHDa
---
The deletion of dead insns is at line 664 (inside the unreachable-block deletion loop), not per-insn dead stores. Hmm, the comment says life_analysis deletes insns whose only effect is a dead store — maybe that's in `mark_used_regs` via `dead_or_set`? Actually, gcc 2.7.2 might not delete dead stores at all (the comment may be aspirational or refers to `delete_dead_code`).

Let me test empirically: add a dead store `i = 0;` (or `i = i;`) inside the loop and see if it scores 0 or adds an instruction.

Actually, a dead store `i = 0` inside the loop would be semantically wrong? No — if I set i=0 at the end of the body before the condition `i < n`, that changes the loop behavior. So the dead store must be truly dead: e.g., `i = i;` (self-assign) — but that's an identity launder (forbidden). Or a store to i whose value is immediately overwritten... e.g., at the top of the loop `i = i + 0;` — identity launder, forbidden and folds.

Hmm, what about a store that's genuinely dead but not an identity launder? Like `i = 0;` immediately followed by `i++`? No, that changes semantics (i would reset each iteration).

What about a separate variable that aliases i? no.

OK, dead-store tricks are dubious.

Let me reconsider. Maybe the right move is to change the loop so that the `slt` uses i in a way that counts twice. For example, `while (i < n)` where the comparison is a `slt` — one use. What if the loop condition is `i < n` but written as a compound that requires two uses of i, e.g., `i < n && i < n`? fold removes.

Hmm, what about `i < n` where `i` appears on both sides via a helper? no.

Let me look at the actual target assembly again for the loop: 
```
$L131:
	lhu	$7,0($9)
	...
	sh	$5,0($11)
	addu	$11,$11,2
	addu	$10,$10,1
	slt	$2,$10,$12
	bne	$2,$0,$L131
	addu	$9,$9,2
```
i (reg $10) appears in 2 insns: `addu $10,$10,1` (dest+src = 2 RTL occurrences) and `slt $2,$10,$12` (1 occurrence). In flow: addu insn at depth 3: 2 occurrences * 3 = 6 refs; slt: 1*3 = 3; i=0 at depth 2: 2. Total 11. Target 14.

The asm adds 3 (one occurrence at depth 3). So the target's i has ONE more RTL occurrence at depth 3 than our version. That occurrence must come from somewhere real. Where could an extra use of i at depth 3 come from in the ORIGINAL source? 

Maybe the original loop had a use of i that was optimized into the existing instructions. For example, the original might have been:
```
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
where loop.c strength-reduced `src[i]` and `dst[i]` into pointers but LEFT the i uses? No, b1 showed it changed things.

OR the original might have used i in the store: `*(dst + i) = out` where dst is a fixed pointer? No.

Wait — maybe the extra ref is from the `dst = src + n` being inside the loop originally? Hmm.

Let me look at other cracked keepalive functions for the exact pattern. Actually, let me look at the WORKED EXAMPLE .run/P40/T10/func_80181F4C/notes.md and win.c. And maybe there are other O-shards with the same function cracked. Let me check other shards' results for func_8013D53C.

Let me grep across .run/P40/T11/*/results.tsv for func_8013D53C.
