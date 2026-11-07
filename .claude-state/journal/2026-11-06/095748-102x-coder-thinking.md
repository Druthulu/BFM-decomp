---
ts: 2026-11-06T16:57:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hmoIA93fltNDdd1ATMGU
---
z1 got worse (119 ins, more registers). The sign variable added a register (s3) and changed the frame.

Let me reconsider. The cleanest: keep the source structure and find a way to make n's live range cross a call *without* extra variables.

What if we swap the sign rand's position in the expression:
`if ((rand() & 1) == 0) m = -m;` where m = (q-n)<<16.
Currently: `m = (q - n) << 16; if ((rand() & 1) == 0) m = -m;`
If we write `m = (q - n) << 16;` after... hmm.

Alternative: make n live across the *second* computation's rand by reusing n:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
if ((rand() & 1) == 0) m = -m;
```
What if we keep n's value for the second computation? No.

Hmm, let me think about the pin differently. Maybe the real C original is:
```
m = (rand() % 4) << 16;
```
and the `%` expansion creates a temp live across... no, same.

Wait — maybe the original used the SAME `n` across both computations in a way that makes it one live range. Look at the target: s0 is used for n in comp 1 AND comp 2 AND the first modulo. That's because the pin made n = $16 and local-alloc reused $16 for other block-local quantities (the modulo temp) since n wasn't live there. So s0 is a "shared scratch" across the block.

Without the pin, mine: the first modulo temp = s0 (natural, crosses a call), n = v1, m = s0. Hmm, mine's n = v1 but m = s0. In the target, n = s0 and m = s0.

What if we make n's live range cross the *first* modulo's call? No.

Let me reconsider: is there a real-C way to make local-alloc pick s0 for a block-local quantity? find_free_reg picks the lowest-numbered free register, but it excludes call-clobbered regs only if qty_n_calls_crossed > 0. For n with 0 calls crossed, v1 is picked (lowest free).

Unless v0/v1/a0... are all occupied at n's birth. Then it'd pick s0. In the target, at n's birth (8e94), what's live? s2=a0, s1=ent, s0=modulo temp... wait, the modulo temp s0 dies at 8e04/8e50. By 8e94, s0 is free. v0=q is live. v1 is free. So v1 would be picked.

In the target, n is s0 because of the pin. To get s0 naturally, we'd need v1 to be occupied. Not possible with real C in this block.

Alternative: make n cross a call so local-alloc is forced to s0. Let me try a subtle version: use n in the *store* after the call? Hmm.

What if we rewrite `m = (q - n) << 16;` as `m = (q - (n)) << 16;` — no.

What if the source computes the sign BEFORE m but as part of the same expression:
`m = (q - n) << 16;` then `if ((rand() & 1) == 0) m = -m;`
→ `m = (rand() & 1) ? (q - n) << 16 : -((q - n) << 16);` — this puts the rand call before the (q-n) computation, making n live across the call! And it's real C (a ternary). The target's instruction order: `subu s0,v0,s0` BEFORE the jal, `sll s0,s0,0x10` in the delay slot, `andi v0,v0,1`, `bnez`, `negu`. With a ternary `(rand()&1) ? A : -A`, the compiler would evaluate rand, then compute A... but sched1 could hoist the sub before the call. And the sll might land in the delay slot. Hmm, plausible.

But the sign test in the target: `andi v0,v0,1; bnez v0, skip; negu s0,s0` — i.e., if (rand()&1)==0 negate. A ternary `? :` with -A in one arm would produce a branch and two computations of A? No: A is common, so the compiler computes A once then negates conditionally — same as the if form. Good.

Let me try:
```
m = (rand() & 1) ? (q - n) << 16 : -((q - n) << 16);
```
Hmm, that's an invented conditional-expression form; the compiler might fold it to the same. Let's test.

Actually, better: move the rand call explicitly before the m computation but keep the if:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
if ((rand() & 1) == 0) {
    m = -((q - n) << 16);
} else {
    m = (q - n) << 16;
}
```
This duplicates the expression in both arms; cse would compute (q-n) once, but WHERE? cse's placement might be before the call. Hmm.

Let me try the ternary first.
