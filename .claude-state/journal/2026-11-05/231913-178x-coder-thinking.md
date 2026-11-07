---
ts: 2026-11-06T06:19:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ht0CDr0aOFvVMVAPw2s6
---
Still 1. The base register is stubbornly a0.

Hmm. Let me reconsider: maybe the issue isn't regmove but the *source's* expression. In my body, the pointer expression is `(s32)a0`. gcc allocates the parameter to $16. The load's base should be $16. But the asm shows a0.

Wait — maybe the `move a0,s0` at 292c is NOT the call arg setup but something else, and gcc actually uses a0 as the *parameter's* home at that point? No, the parameter is in $16.

Let me look at s5's asm again around 292c-293c:
```
292c move a0,s0
2930 lui v1, D_80184CCC
2934 addiu v1,v1,0
2938 lh v0,256(a0)
293c lh a1,112(a0)
```
Both loads use a0! So gcc uses a0 for the base of both loads. In the target, the first uses s0 and the second a0.

The second load `*(s16 *)(pa0 + 0x70)` uses pa0 = a0 (the copy). The first `((Unkstruct_800B5CB8 *)s0)->unk100` uses s0 in the target.

In my body, both use `(s32)a0`, so both use a0. Makes sense.

So to match, the first must use s0 (the callee-saved copy). Since my source uses the parameter (which IS in s0), gcc chose the a0 copy (created by the move).

Hmm — maybe gcc's local-alloc/regmove replaced the base with a0 because a0 was set to s0 just before. This is the "copy propagation into a use" optimization.

To prevent it, the source's base must not be the same pseudo as the call argument. So I need a separate variable for the unk100 access that gcc keeps in $16.

Hmm, but any copy of the parameter would be in the same register...

What if the unk100 access uses a variable that is NOT a copy of a0 but the *parameter itself*, while the call arg uses a *copy*? That's what I have (the parameter vs pa0 = a0). But gcc propagated.

Hmm. What if I make the call arg a copy that gcc can't coalesce with a0? E.g., pass `(void *)(s32)a0` to func_8012AD50 but declare pa0 as a separate variable... it already is.

OK. What if the unk100 load is moved to a *different basic block* (e.g., inside an if)? That would change the structure.

Alternatively — maybe I can make the target's instruction sequence by having the unk100 load happen BEFORE the `move a0,s0`. In the target, the move is at 292c and the load at 2938 — after. Hmm.

Hmm, what if the move a0,s0 is *after* the load in mine? Then the load would use s0 (a0 not yet set). The source order: pa0 = a0 (the copy) → gcc emits move a0,s0 there. If the copy were after the unk100 load, the move would be after.

u2 tried moving the pa0 copy after the unk100 computation — score 1. Hmm, but maybe sched1 hoisted the move anyway.

Let me check u2's asm... Actually u2 = 1 with 65 ins, so the move is somewhere.

Let me try: put the unk100 load FIRST in the last block (before any a0 use):
```c
{
    s32 v0, v1;
    s32 pa0;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;
    v0 |= 0x40000000;
    pa0 = (s32)a0;
    *(s32 *)(pa0 + 0x58) = v0;
    ...
```
u2 did this and stayed 1.

Hmm.

Let me look at u2's asm to see where the move is.

Actually, let me step back and consider: is `lh v0,256(a0)` vs `lh v0,256(s0)` really the only diff? Score 1 = 1 mismatch. Yes.

Maybe I can fix it by making the *second* load (`pa0 + 0x70`) use a0 and the first use s0 via a different expression: e.g., make the first access go through a *struct field* with a different type? Hmm.

What if I write the unk100 access with the `s0` variable from the *top* but only there... 

Hmm, let me try declaring a variable at the top: `s32 s0;` and `s0 = (s32)a0;` and using `s0` ONLY in the last block's unk100 access (and `(s32)a0` elsewhere). Then gcc would have the s0 variable live from the top to the last block (crossing calls) → a callee-saved reg. And the parameter also crosses calls. Two callee-saved regs? Unless coalesced.

Hmm, the parameter's uses would be `(s32)a0` everywhere; the s0 variable used once at the end. gcc would allocate s0 to... a copy of a0 at the top. Then s0 and the parameter are the same value but different pseudos → 2 regs (the p1 issue).

Unless gcc coalesces them (they're connected by a copy). p1 didn't coalesce.

Hmm.

What if I assign s0 = a0 *inside the last block* and use it? Then s0 is a local copy → coalesces with a0 → same as now.

Argh.

Let me look at this from the perspective of the target's RTL: the unk100 access uses the hard reg 16 because the source variable is pinned. In a lever-free body, the pointer is a pseudo in $16 and the access uses it — unless regmove/copy-prop changes it.

Let me check whether it's really regmove. In gcc 2.7.2, regmove runs after reload? Actually regmove is before reload. Hmm.

Let me look at the s5 .lreg/.rtl for the last block to see the base pseudo and whether a copy was introduced.

Let me find the func_8017EF9C region in s5.i.rtl and look at the last block.

Let me get the function start line and search for the CCC symbol within.
