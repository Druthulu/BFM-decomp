---
ts: 2026-11-06T06:16:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9aSz04KwB8YLzrHHxUJ9
---
All still 1 — the same `lh v0,256(a0)`.

Let me think differently: maybe I can make the *whole last block* use a variable that gcc keeps in s0 by making the source use a local variable assigned from a0 *before* the block's calls.

Hmm. Or maybe the issue is the opposite: the target uses s0 because its source's last block references the `s0` variable, which is the pinned hard reg. In a lever-free body, the pointer is the parameter; gcc will use a0 or s0 depending on the scheduling.

Hmm, what if I *reverse* the roles: make the call-arg setup use s0 (not a0) at that point? No.

What if the func_8012AD50 call's arg is a *different* variable, so a0 isn't set early? E.g.:
```c
{
    s32 v0, v1;
    s32 pa0;
    pa0 = (s32)a0;
    v1 = ...;
    v0 = (unk100 << 4) + v1;
    ...
    func_8012AD50((void *)pa0);
}
```
Here pa0 = a0 is a copy. gcc would allocate pa0 to a0 (coalescing) and the call uses a0. But the `move a0,s0` would happen at the copy point (before the unk100 load), so the unk100 load could use a0 or s0.

s6 did exactly this and stayed at 1.

Hmm. What if the copy is placed AFTER the unk100 load?
```c
v0 = (unk100 << 4) + v1;
...
```
The pa0 copy is used for the stores and the call. If the copy is after the unk100 load, then at the load point a0 might still hold... hmm, a0 was clobbered by the previous call (func_8012B14C at 2924). So a0 doesn't hold the pointer at the block start; gcc must load it from s0.

So the unk100 load would need `move a0,s0` first (1 extra instruction) unless it uses s0 directly.

In the target, the unk100 load uses s0 (no move needed), and the `move a0,s0` is for the call arg later.

In mine, gcc hoisted the `move a0,s0` before the unk100 load (sched1) and used a0.

If I could delay the `move a0,s0`... The source order: pa0 = a0 (the copy) → gcc emits `move a0,s0` at that point (early). If the copy were later in the source (after the unk100 load), the move would be later.

In s6, the pa0 copy is first (matching the target's launder position). The target's launder `pa0 = s0` is also first, and its asm `move a0,s0` is at 292c — which is *after* the unk100 load? Let me check the target: 292c move a0,s0, 2930-2934 lui/addiu v1, 2938 lh v0,256(s0), 293c lh a1,112(a0). So the move is at 292c, BEFORE the unk100 load at 2938. And the load uses s0 anyway.

So in the target, even with a0 == s0, the load uses s0. In mine, it uses a0.

Hmm! Why? Because in the target, the source's unk100 expression uses the hard reg $16 — cse can't rewrite it to a0.

In mine, the source uses the parameter pseudo (in s0), and cse sees `move a0,s0` (a0 = s0) and rewrites the load's base to a0 (a copy the target doesn't make).

Hmm, would cse rewrite a base register like that? cse's REG_EQUAL/reg_eqv could.

Hmm, actually maybe it's not cse but the register allocator choosing a0 for the load's base (since a0 == s0 and both are available).

Either way, to prevent it, the source's base must be a variable that's NOT copy-equivalent to a0 at that point.

Idea: make the parameter a0 dead after the prologue copy by using a distinct variable... that's the s0 variable (which causes 2 allocnos).

Hmm, but maybe the 2-allocno issue can be fixed! Let me revisit: p1 had reg72 (parameter, 10 uses) and reg73 (s0, 5 uses). If gcc's copy propagation split the uses, maybe I can force all uses to s0 by making the parameter unused... it IS unused except the copy.

Wait, p1's reg72 is used 10 times — that means gcc replaced 10 uses of s0 with a0. Hmm.

What if I declare the parameter as `void *a0` and the copy as `s0 = (s32)a0`, and gcc propagates... 

What if the copy is made *after* the first call (so a0 is dead/clobbered)? E.g.:
```c
void func_8017EF9C(void *a0) {
    s32 loc[5];
    s32 s0;
    s0 = (s32)a0;    // before the call
```
The copy must be before the pointer's first use.

Hmm, what if we avoid the copy by using a0 directly but adding a *do-while* or something to prevent cse from substituting a0 at the unk100 load?

Let me try wrapping the unk100 load in a do-while(0) (block split) — maybe that stops the substitution.

Also try: computing the unk100 value into a variable *before* the pa0 copy.

Let me test:
- u1: `do { v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1; } while (0);`
- u2: compute `s32 u = ((Unkstruct_800B5CB8 *)(s32)a0)->unk100;` before the pa0 copy.

Let me run.
