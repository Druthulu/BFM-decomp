---
ts: 2026-11-06T06:14:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zqlXvCVBpgQvO7fz0JCx
---
Hmm, this is p1's lreg — reg72 is used 10 times across 23 insns, crosses 2 calls, pointer. reg73 used 5 times across 33 insns, crosses 3 calls.

Wait, p1's source replaced s0 with (s32)a0? No — p1 still has `s32 s0; s0 = (s32)a0;` (p1 only removed pa0). Let me recheck: p1 = n2 with pa0 removed; n2 has s32 s0; s0 = (s32)a0.

So in p1, reg72 = the parameter a0 (used 10 times, crosses 2 calls, pointer) and reg73 = the s0 variable (5 times, crosses 3 calls).

Hmm, so the parameter is used 10 times across 23 insns — meaning gcc kept using the parameter directly for some accesses, and s0 for others.

Interesting: the source has `s0 = (s32)a0;` and then all uses are `s0`. So why is the parameter used 10 times? Because gcc's copy propagation replaced some uses of s0 with a0! (The copy s0 = a0, and if a0 is available, gcc can use it.)

So the two allocnos both exist because the uses are split between a0 and s0.

In the target, s0 is pinned ($16), so all uses go to $16 (no propagation to a0).

Hmm. To make lever-free work, we want ONE allocno. If gcc propagates the copy, all uses become a0 → then a0 is live across calls → gcc copies it to a callee-saved reg → `move s0,a0` in the prologue, and the uses are `move a0,s0` before calls + s0 elsewhere. That's exactly q1's shape (which scored 11).

Hmm, q1 = 64 ins, 11 score. s5 = 65 ins, 1 score.

s5 is better. Let me focus on s5's single mismatch: `lh v0,256(a0)` vs `lh v0,256(s0)`.

In s5, the pointer is the parameter (a0), copied to s0. The unk100 access uses `(s32)a0`. gcc emitted a0.

In the target, the unk100 access is via the pinned s0.

What if I write the unk100 access with an explicit *variable* that's a copy of a0 at the start of the last block, so it's not the parameter pseudo? E.g., s6's pa0. That didn't help.

What if the variable is assigned *before* the calls (at the top)? That's the s0 variable → the extra copy issue.

Hmm, what if I introduce a second variable at the top that gcc can coalesce with the parameter? The issue was gcc splitting uses between a0 and s0.

Wait — in p1, the parameter and s0 are separate because gcc propagated some uses. If I could make gcc NOT propagate (so all uses are s0), then s0 would be the only allocno → 1 callee-saved reg.

Hmm, but gcc's propagation is what creates the two.

What if I use the parameter directly everywhere (q1) — then there's one pseudo (the parameter) → one callee-saved reg. q1 = 64 ins (one less than target!).

q1's diff: the v1 register issue (fixed by s1's s16 v1) and the last block.

So let me combine q1's approach with s1's v1 fix: that's s5? No — s5 derives from s1 which derives from q1. Yes! s5 = q1 + s16 v1 + v1w. And s5 = 65 ins, score 1.

The only remaining: `lh v0,256(a0)` vs `lh v0,256(s0)`.

In s5, all source uses are `(s32)a0`. The pointer pseudo is the parameter. gcc's asm: the prologue `move s0,a0` (copy to callee-saved), calls use `move a0,s0`, and the unk100 load uses a0.

The target uses s0 for the unk100 load.

Hmm, since a0 and s0 both hold the pointer at that point, this is a register-choice detail. Can I nudge it?

Idea: reorder the last block so the unk100 load happens *before* the `move a0,s0` (which is the call-arg setup). The `move a0,s0` at 292c is scheduled early (for the call at 2954). If the unk100 load were scheduled before it... the scheduler decides.

Idea: change the source order so `v0 = (unk100 << 4) + v1;` comes before the pa0 stuff — it already does.

Hmm, the `move a0,s0` at 292c is the arg setup for func_8012AD50 at 2954 — sched1 hoisted it. In the target, it's also at 292c. So both have it.

At 2938, a0 = s0. The target uses s0 for the load, mine uses a0.

Why? Because in the target, the source's expression uses the hard reg $16. In mine, the source uses the parameter pseudo, which is in s0, but gcc's cse/combine may have substituted the a0 copy.

Hmm — maybe the `move a0,s0` creates a REG_EQUAL note (a0 == s0), and cse substitutes a0 for the parameter's uses after the move. That's why mine uses a0.

In the target, the source's s0 is a hard reg; cse's substitution of a0 for $16? It wouldn't (different hard regs, and the move a0,s0 sets a0 = s0; cse could still know a0 == s0, but using a0 instead of s0... cse doesn't replace hard regs).

So: to get s0, the source must reference a pseudo that isn't the a0 parameter... but the only pointer we have is the parameter.

Hmm, unless we use a variable that gcc allocates to s0 and doesn't propagate to a0. That's the `s0` variable — but it splits uses.

Hmm, what if we use a *second* variable assigned from the parameter at the top, and use it ONLY in the last block? Then gcc would propagate it to a0 (since it's a copy)... 

OK, what if the last block's unk100 access is written to use the *value stored in the struct* differently, e.g., via a local pointer `s16 *p = ...`? Hmm.

Let me think about the exact instruction: target `lh v0,256(s0)` — loads the s16 at s0+0x100. Mine `lh v0,256(a0)`.

What if I add a `do { } while (0)` around the last block's first statement to prevent the cse substitution? Hmm.

Or what if the last block uses a *different* expression for the pointer that gcc can't equate with a0? For example, `(s32)(void *)a0`? Same.

Hmm, what if I declare a local `s32 s0v` and assign it at the top of the last block from a0, then use s0v for the unk100 access? gcc would propagate s0v = a0 → same.

What if s0v is assigned from a0 *before* the calls (at the top of the function)? Then s0v crosses calls → a callee-saved reg. But gcc would coalesce s0v with the parameter... that's the p1 issue (2 allocnos).

Hmm, wait — p1 had 2 allocnos because gcc propagated *some* uses to a0. If I use s0v for ALL uses (no parameter uses), gcc might still propagate some.

Hmm.

Let me try: keep the parameter unused (only the copy) and use s0v everywhere:
```c
void func_8017EF9C(void *a0) {
    s32 loc[5];
    s32 s0;
    s0 = (s32)a0;
    ...all uses via s0...
}
```
That's the orig without the pin. p1 = 67 ins (extra copy).

The extra copy is `move s1,s0` — gcc allocated the parameter to $16 and s0 to $17, then copied. Why not coalesce? Because the parameter is used 10 times (propagated) and s0 5 times — two live ranges that overlap.

Hmm, if gcc didn't propagate, the parameter would be used once (at the copy) and s0 everywhere → coalescible.

How to prevent gcc from propagating the copy into the uses? The propagation happens because s0 = a0 and a0 is available. Hmm.

What if the copy is `s0 = (s32)a0` but a0 is clobbered early (by the first call)? The first call `func_8012C1B8()` happens right after the copy. So a0 is clobbered at the call → uses after the call must use s0. Uses before the call could use a0.

In the target, the uses are: `unk20 = call()` (before/at the call), then after.

Hmm, the first use `((Unkstruct_800B5CB8 *)s0)->unk20 = ...` is a store to s0+0x20 after the call.

Hmm, so a0 is clobbered by the first call, so only the first statement could use a0... but the first statement is after the call.

Wait, the source:
```c
s0 = (s32)a0;
((Unkstruct_800B5CB8 *)s0)->unk20 = ((s32 (*)(void))func_8012C1B8)();
```
The store target address is computed... the call happens first (or the address is computed before). In the target asm: `jal func_8012C1B8; move s0,a0; bnez v0; sw v0,32(s0)`. So `move s0,a0` is in the jal's delay slot (the copy), and the store uses s0.

In p1: `move s0,a0` at 2874, `sw s1,44; move s1,s0` at 2880/2884 — the second copy.

Hmm.

OK, let me try a different tack: maybe I can fix the last-block register by making the unk100 load use a *different* addressing expression. E.g., instead of `((Unkstruct_800B5CB8 *)(s32)a0)->unk100`, use `*(s16 *)((s32)a0 + 0x100)`. gcc might treat it differently. Let me test.

Also try: `CAST_SIGN(u16, a0, 0x100)`.

Let me test a few.
