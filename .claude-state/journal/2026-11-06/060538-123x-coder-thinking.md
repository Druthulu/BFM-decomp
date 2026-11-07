---
ts: 2026-11-06T13:05:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QivGREKCvSMvflTj3x7e
---
Still 2. Let me think about sched1's choice differently.

In the target, the order after `lw v1,0(a0)` is `li v0,36; addiu a0,a0,4; subu`. So sched1 scheduled the li before the addiu.

Priorities: the li (376) feeds the subu (379) which feeds the sll/addu chain that feeds the addu for ba. The addiu (388) feeds a0 which feeds the addu (393).

Both chains end at the same place (ba). The li's chain: 376→379→381→383→385→393→395 (long). The addiu's: 388→390→393→395 (shorter). So the li has a HIGHER priority → scheduled first. But in mine, the addiu came first! Contradiction.

Unless the addiu is not 388 but something else... In mine's asm: `lw $3,0($4); addu $4,$4,4; li $2,36; subu`. Hmm, `addu $4,$4,4` — that's 388+390 combined (the copy folded).

So sched1 scheduled 388/390 before 376. With priority: 390 (set a0 = 153) is a "copy to a hard reg" — its priority might be very high because a0 is live...

Hmm, the scheduler treats hard-reg writes specially? `insn_priority` uses `INSN_PRIORITY` = the length of the longest path to the end. The chain 390→393→395 is 3; 376→379→...→395 is 6. So 376 should be first.

Unless the scheduler's ready list had 376 not ready (hazard) — e.g., the li writes v0, and v0 was used by the previous insn (the loop's `sra v0,v0,16`? or `lhu v0`?). Let me look at the previous insns: the block before is `$L216: move $5,$10; la $4,D_80127548; lw $3,0($4)`. Hmm, in mine's asm the preceding insns: `move $5,$10` (a1 = base?) then `la $4,...`.

Hmm, in mine: `lw $3,0($4)` — dcount in v1. Then `addu $4,$4,4`. Then `li $2,36`.

Maybe the li is blocked by a hazard on v0 (the previous instruction wrote v0?). Let me look at the full region in mine's asm: line 205-212 of the .s:
```
$L216:
	move	$5,$10
	la	$4,D_80127548
	lw	$3,0($4)
	addu	$4,$4,4
	li	$2,0x00000024
	subu	$2,$2,$3
```
Hmm, `la $4,D_80127548` then `lw $3,0($4)` — a load-use hazard (lw after la? no, la is lui+addiu macro, the lw depends on it → the assembler fills the delay).

OK, the scheduler put the addiu between the lw and the li — that also serves as the load-delay fill! `lw $3,0($4)` followed by `addu $4,$4,4` fills the load delay slot. In the target, `lw v1,0(a0)` is followed by `li v0,36` — also a delay fill (li doesn't use v1). Both are delay fills; the scheduler chose differently.

The choice: both are ready; the scheduler picks by priority. In mine the addiu won, in the target the li.

Since the priority of 390 (a0 = 153) is likely boosted by the hard-reg use, and in the target... hmm.

What if `dp` weren't pinned to $4? The pin is a lever that may stay, but removing it is allowed too! If dp weren't pinned, the register choice might differ — but the target has dp in a0 ($4). So the pin matters.

Hmm, what if `dp` is pinned but the `dp = dp + 1;` is written to avoid the extra copy insn (153)? `dp += 1;` same.

Let me try: `dp = (s32 *)((u8 *)dp + 4);` — that would emit addiu with a different expression.

Or `dp = &dp[1];` — gcc folds to plus 4.

Let me try 2 more and then stop (time 06:08, 16 min on item 3).

Actually, let me reconsider: maybe I can find the difference by comparing with the ORIGINAL (with all asm). The original scores 0, so its sched1 order matches the target. The original had the keepalive asm before `df = c36 - dcount;` — that asm is a scheduling barrier-ish (an asm insn can't be moved across? sched1 treats asm as a barrier? In 2.7.2, sched1 gives asm insns a "barrier" property? Actually `__asm__` insns with no outputs are volatile and sched1 treats them as... they're in the stream and have dependencies).

The keepalive `__asm__("" : : "r"(c36), "r"(dcount))` reads c36 and dcount — so it must come after both. It was placed between `c36 = 0x24;` and `df = c36 - dcount;`. Hmm, that asm reads c36 → it forces the li (376) before the asm; and it reads dcount.

But the asm is gone now (keepalive removed). The remaining order difference is the addiu vs li.

Hmm, in the original RTL, the asm sits between 376 (li) and 379 (subu). sched1 can't move the addiu before the asm? It could.

Let me test: what if I keep a *dead* non-volatile asm... no, that's a keepalive (forbidden).

What about a real C statement that reads c36 before the addiu? e.g. `df = c36 - dcount;` is already there (before the addiu in RTL).

Hmm, the RTL order: li(376), subu(379), ..., addiu(388). sched1 moved the addiu up to right after the lw, jumping over the li and the subu. If the scheduler can't move the addiu above the subu (which depends on the li)... it can, they're independent.

Why did the target keep it after? Because in the target the addiu is at position 3 (after lw, li) — so the target's sched1 moved it up only past the subu? Hmm, the target: lw(1), li(2), addiu(3), subu(4). Pre-sched RTL order: lw, li, subu, sll, addu, sll, addiu, addu. So the target moved the addiu up 5 positions, mine moved it up 6 (before the li).

The difference is just one slot. Since both insns are independent, the choice is by hazard/priority. In the target, the li went first.

What if I make the addiu depend on the li indirectly? No...

What if `df` were computed BEFORE `c36 = 0x24;`... impossible.

What if the C's `dp = dp + 1;` moves *after* the `ba` line and `ba` uses `dp` before? no.

Hmm, what if I write `ba = (u16 *)(tmp + (u8 *)dp + 4); dp = dp + 1;`? Then the addiu might fold into the addu... 

Alternatively: `dp = dp + 1;` → `dp = (s32 *)((u8 *)dp + 4);`. Let me test that (w1) and `dp = dp + 1` with `dp` as `u8 *`? no.

Let me do 2 final tries then move on: I'm at 16 min on item 3.

Actually — wait. Let me try the OTHER direction: what if the addiu gets a *lower* priority by making `ba`'s computation not depend on dp directly? E.g. `ba = (u16 *)(tmp + (u8 *)dp);` where the addu uses a0. If instead we compute `ba` from a copy of dp made before the increment:

```
s32 *dp0 = dp;      /* no */
```

Hmm.

OK, let me stop item 3 as a WALL: lever-free best 18 (c1); with the launder kept (p2) 2.

Hmm, but hold on — the p2 result is interesting: score 2 with the launder kept. Since a PARTIAL requires 0, it's a WALL. But the WALL's best should be the lever-free best = 18.

Wait, actually — maybe I misjudge: is `__asm__ __volatile__("" : "=r"(decoy) : "r"(ba))` still a "launder"? Yes. And p2 keeps ONLY the launder kind (both keepalives gone). If p2 scored 0 it'd be PARTIAL:launder. It's 2, so WALL.

Let me record item 3 now: WALL, best 18, tries ~55, wall tag: `cse-hardreg-copy-forward` (new) or reuse `cse-store-forward`. The mechanism: "the launder's read of the pinned $5 (ba) is what keeps `addu a1,...; move a0,a1`; lever-free cse folds the $5 set into the $4 copy (dst=ba) and the copy-loop source takes a1 instead of a2".

Let me check the time and then write the row. Also I need to check the item-4 verification progress.
