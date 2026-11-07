---
ts: 2026-11-06T16:56:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_34mZCdtl1iDVRdnGkpPa
---
Mine matches the target through 8e60. The difference starts at the second computation (after `t = (s32)sp10` etc.): mine uses v1, target uses s0.

So the first modulo temp correctly uses s0 in both. Then our explicit n computations use v1 in mine, s0 in target.

To make n use s0, we need it to be in a callee-saved register. Since n doesn't cross a call in the source, local-alloc gives it a caller-saved scratch (v1). But s0 is already saved and free at that point — if we make n *live across* a call, it would go to s0.

Wait, but is there a call between n's def and use? The computation:
```
q = rand();       <- call
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
if ((rand() & 1) == 0) m = -m;   <- call
```
n dies before the second rand. So no.

Hmm, but in the target, the n computation's live range: `move s0,v0` (delay slot of bgez), then addiu/sra/sll, then `subu s0,v0,s0`, then `sll s0,s0,0x10` — all within one block, no call. Yet s0.

Why does the target use s0? Because the pin forced n to $16. The pin is the lever. Without it, the allocator uses a scratch (v1). We need a real-C way to make the allocator choose s0.

Hmm. local-alloc assigns registers per block in order of "quantity" (birth order / refs / live length). The candidates for the n temp: v0, v1, a0-a3, t0-t9, s0... local-alloc prefers caller-saved? Actually local-alloc allocates from the full register set; a pseudo that dies within the block can go to any free register, and local-alloc prefers... In the target, s0 is chosen because the pin reserves $16.

What if we restructure the C so that the n value *is* live across a call? For example, if the original source computed both vel X and vel Z with a shared helper or used n across the rand() for the sign bit. Look at the target: the sequence for vel X:
```
jal rand          (q)
bgez/move s0,v0
...
subu s0,v0,s0     (m = q - n)
jal rand          (sign)
sll s0,s0,0x10
andi v0,v0,1
bnez v0 ...
negu s0,s0
jal rand          (next q)
sw s0,16(s1)      <- store vel X
```
The s0 value (m) is live across the `jal rand` for the sign AND the `jal rand` for the next q! So the *result m* is live across calls. But m is a different variable; it's also in s0 because... the pin made n = s0 and m reused it.

Ah, I see: the target's s0 holds n during the modulo, then m = (q-n)<<16 in s0, and m stays in s0 across the sign rand and the next q rand, then stored. So s0 is the register for BOTH n and m — a single pseudo reused (local-alloc ties them because n dies when m is born).

In mine, n = v1 and m = s0 (m is live across calls → s0). Wait, mine's diff said `sll s0,v0,0x10` in target vs `sll s0,v0,0x10`? Let me check mine's later part.

Actually the diff earlier:
```
mine[68:73] vs target[68:73]:
68 move v1,v0    | move s0,v0
69 addiu v1,v0,3 | addiu s0,v0,3
70 sra v1,v1,2   | sra s0,s0,2
71 sll v1,v1,2   | sll s0,s0,2
72 subu v0,v0,v1 | subu s0,v0,s0
replace mine[74:75] target[74:75]
74 sll s0,v0,0x10 | sll s0,s0,0x10
```
So in mine, n=v1, and at 74 `sll s0,v0,0x10` — mine computes m = (q-n)<<16 into s0 directly. In target, `sll s0,s0,0x10` (m reuses s0 = n's register).

So in mine, n dies and m (live across calls) gets s0. In target, n gets s0 (pinned) and m reuses it.

To reproduce: n must be in s0 and m must reuse it. Since m is live across calls, it gets a callee-saved reg anyway (s0 in mine). If n were also in s0 (dying just before m is born), local-alloc would tie them: `sll s0,s0,0x10`.

So the goal: make n allocate to s0. n is a short-lived temp; local-alloc's qty priority decides. The registers available in that block: v0 (q, live), v1 (free), a0-a3, t0-t9, s0 (free after the first modulo temp dies at 8e04/8e50...). Hmm, s0 IS live from the first modulo (8df0) until `move a1,s0` at 8e50. So s0 is occupied until 8e50. Our n computation starts after 8e5c. So s0 is free.

local-alloc assigns the "best" register per quantity. With many free caller-saved regs, why would it pick s0? It wouldn't — unless something forces it.

The pin forced it. Real C alternative: make n live across a call → s0. But the target's n doesn't cross a call... Hmm, wait: does it? The first computation's n (s0) is live across the `jal rand` at 8e00? No, that's the modulo temp.

Hold on, let me re-examine: the target's first computation is `rand() % 0x1000` — but the source has our explicit n computations later. Let me match the target's s0 uses:
- 8df0-8e04: modulo for rand()%0x1000 (compiler-generated)
- 8e94-8eac: `n = q+3; n>>=2; n<<=2; subu s0,v0,s0` (our n)
- 8eb0-8ebc: `sll s0,s0,0x10; ... negu s0,s0` (m)
- 8ecc-8edc: second n computation
- 8ee4-8ef4: second m

So our n and m share s0 in the target, and s0 was already used for the modulo temp. The pin made n's hard reg $16; local-alloc then also used $16 for the modulo temps (since they're in the same block and the pin reserves it? no...).

Hmm, actually the modulo temp in the target is s0 in BOTH mine and target — because it's live across a call. So that's natural.

Then our n: pinned to $16 = s0, which is free at that point (after 8e50). So n = s0 naturally if we could tell the allocator "use s0".

Without a pin, can real C make n go to s0? Perhaps by making n live across a call, e.g. moving the `q = rand()` assignment before... hmm.

What if we restructure: instead of
```
q = rand();
n = q; ...
m = (q - n) << 16;
if ((rand() & 1) == 0) m = -m;
```
we write it so n is computed and used across the sign call? E.g.:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
if ((rand() & 1) == 0) ... 
m = (q - n) << 16;
```
Moving `m = (q-n)<<16` AFTER the sign rand would make n live across the sign call → n gets a callee-saved register (s0). But the target's instruction order has `subu s0,v0,s0` BEFORE the sign rand, then `sll s0,s0,0x10` after the call (in the delay slot area). Look at target:
```
8e9c sra s0,s0,2
8ea0 sll s0,s0,2
8ea4 subu s0,v0,s0     <- m = q - n
8ea8 jal rand           <- sign
8eac sll s0,s0,0x10     <- m <<= 16  (delay slot!)
```
So the sub happens before the call; the shift after. The source `m = (q - n) << 16;` would compute both before the call... but sched1 moved the sll after the call (into the delay slot). In RTL, m = (q-n)<<16 is one expression: sub then sll, both before the rand. Sched1 reordered the sll into the delay slot.

If n were live across the sign call, the sub couldn't happen before... Actually if the source is `m = (q - n) << 16;` then n dies at the sub, before the call. So n doesn't cross.

To make n cross a call in the RTL, we could move the sub after the call:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
sign = rand() & 1;      /* hmm, changes structure */
m = (q - n) << 16;
if (sign == 0) m = -m;
```
This would put the sub after the rand, making n live across the call → n gets a callee-saved reg. But the target's RTL has the sub before the call. Sched1 could still move the sub before the call (it's a pure computation and q,n are available). Hmm, but then n's live range in RTL crosses the call (the RTL says n is used after the call), so local-alloc would give n s0; sched1 may then hoist the sub before the call. That's plausible!

Actually, that's a real C move: hoisting the sign computation into a variable (`s32 sgn = rand() & 1;`) before computing m. But it changes the C structure. Would it change the target's instruction order? Let's try.

Alternatively, a simpler real-C change: make `n` function-scope and *used after* the call, e.g. the second computation. Since n is reassigned, no.

Hmm, let me think about the actual original source. The target is what the ORIGINAL game's compiler produced. The decompiler's source has `q = rand(); n = q; if (q < 0) n = q + 3; n = n >> 2; n = n << 2; m = (q - n) << 16; if ((rand() & 1) == 0) m = -m;`. This is the decompiler's guess. The original likely had `rand() % 4` — which the compiler expands to exactly this. And the register allocation would be as in the target: n is the `%` temp.

Hmm! Maybe the original source is:
```
m = (rand() % 4) << 16;
if ((rand() & 1) == 0) m = -m;
```
Then the `%4` temp is compiler-generated and local-alloc assigns it. Why would it be s0 in the target? Because... the sign rand() call comes after, and the temp is dead before it. Same as ours.

Unless the original used the SAME temp across both vel X and vel Z computations? No.

Wait — maybe the key is the pin's second effect: the hard-reg pseudo reserves $16 for the whole function (wall "global-hardreg-reserve"). With the pin, $16 is reserved, so local-alloc gives the modulo temps $16 too. Without it, they'd get v1/v0. But we see the FIRST modulo temp uses s0 in BOTH. So s0 is already used naturally.

Hmm, let me look at mine's later code to see what registers the two computations use.
