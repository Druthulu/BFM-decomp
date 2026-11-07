---
ts: 2026-11-07T00:06:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8uhArz5iPzZVfFNFhWzN
---
Now I see the target clearly:

Prologue: s2=p1, s4=p2, s5=p3, s3=p4, s0=iVar1, s1=iVar5.

Then:
```
lw v1,88(s2)          ; *(u32*)(param_1+0x58)
bnez v1, ...
lui v0,0xfff
j ...; li s1,128      ; iVar5 = 0x80
...
ori v0,v0,0xffff
and a0,v1,v0          ; uVar3 = v1 & 0xfffffff
lh v0,4(a0)           ; t = load +4
lh v1,6(a0)           ; iVar4 = load +6
bgez v0, 5aec         ; if (t<0)
move s1,v0            ; iVar5 = t
negu s1,s1
bgez v1, 5af8         ; if (iVar4<0)
nop
negu v1,v1
slt v0,s1,v1          ; if (iVar5 < iVar4)
beqz v0, 5b08
nop
move s1,v1            ; iVar5 = iVar4
```

So:
- t = v0 (the load +4)
- iVar4 = v1 (the load +6)
- iVar5 = s1
- a0 = uVar3

Interesting: iVar4 is in v1 (a caller-saved reg) — the launder pseudo. And t is v0.

Block 2:
```
lh v0,8(a0)     ; t = load +8
nop
bgez v0, 5b1c
move v1,v0      ; iVar4 = t
negu v1,v1
slt v0,s1,v1
```
So iVar4 = v1 again (copy from v0).

So t is always v0 and iVar4 always v1. Nice and simple: t→v0, iVar4→v1.

Lever-free, we need the same: t in v0 and iVar4 in v1, with the copy `iVar4 = t` surviving.

The key: t must be a distinct pseudo from iVar5/iVar4. In the C, `t` is a separate variable reused for all the loads. The problem: cse merges `iVar5 = t` (first block) and `iVar4 = t`.

Hmm, with the t pin, t is a hard reg so it's forced. Without, t merges.

For the lever-free body, we need t to be a *separate variable* that the compiler doesn't merge. Since t is reassigned 5 times (once per load), it's a multi-set pseudo. cse's equivalence: `t = load; iVar5 = t;` → merges t and iVar5 (same value). Then `if (t<0) iVar5 = -iVar5` sets iVar5 → breaks. Hmm, then t is still the load value.

Actually the issue is that `iVar5 = t` is a copy; cse merges them so the load goes to s1 and the negu is on s1.

For the target, the load goes to v0 (t) and then move s1,v0. So t and iVar5 are distinct.

What C construct makes `iVar5 = t` a real copy? A real 2nd set of t, or...

Hmm! Wait. What if the ORIGINAL source didn't have `t` at all but had the load assigned directly to iVar5 and iVar4, and the v0/v1 split is just the compiler's choice? Let's see: target block 1:
```
lh v0,4(a0)
lh v1,6(a0)
bgez v0,...
move s1,v0     ; iVar5 = t
negu s1,s1
bgez v1,...
negu v1,v1
slt v0,s1,v1
```
If the C were:
```
iVar5 = *(s16*)(uVar3+4);
iVar4 = *(s16*)(uVar3+6);
if (iVar5 < 0) iVar5 = -iVar5;
if (iVar4 < 0) iVar4 = -iVar4;
if (iVar5 < iVar4) iVar5 = iVar4;
```
then the loads would go directly to s1 and v1: `lh s1,4(a0); lh v1,6(a0); bgez s1; negu s1; ...`. That's what mine does (`lh s1,4(a0)`).

So the target's `move s1,v0` means there IS an intermediate t. And `lh v0` then `move s1,v0` — the load is in v0.

Why would the compiler put the load in v0 and copy to s1? Because t is a separate variable whose value is copied to iVar5. Without a pin, cse merges.

So we need a real C reason for t to be distinct. The C has `t = load; iVar5 = t;` — but cse merges.

Hmm, unless t is used elsewhere. Look: t is reused for the next loads (`t = load+8; iVar4 = t;`). So t is multi-set. cse's merge at `iVar5 = t` still happens.

What breaks it? A real 2nd set of t *between* the load and the copy? No.

Hmm, what about the launder on iVar4? That's on iVar4, not t.

Wait — the launder `"=r"(iVar4)` creates a NEW iVar4 pseudo. That's after `iVar4 = load+6`. Hmm.

OK, so how do we get t→v0 lever-free? 

IDEA: make `t` a different type so the load goes through a SUBREG copy! E.g., declare `t` as `s16`? Then `t = *(s16*)...; iVar5 = t;` — the s16→s32 conversion would produce a sign-extend (sll/sra), not a plain move. Not right.

IDEA: `iVar5 = t` where iVar5 is `u32`? Same mode.

IDEA: Make t a *pointer*? No.

IDEA: Reorder so that `iVar4 = load+6` comes before `iVar5 = t`? The target has both loads first: `lh v0,4; lh v1,6; bgez v0; move s1,v0`. The C order is t=load+4; iVar4=load+6; iVar5=t; if(t<0)... So the loads are adjacent. Fine.

Hmm, so what makes `iVar5 = t` a real copy? cse's make_regs_eqv merges t and iVar5. Unless t has a second set that cse knows about... 

OH WAIT. Maybe the answer: `t` is assigned FIVE times (multi-set). cse1 processes block by block. Within block 1, t is set once. Hmm.

Hmm, but actually — maybe the mechanism is different. The t pin is `$2` (v0), and the comment says "keep the loaded halfword in $v0 so abs copies $v0->$v1". The target has `move s1,v0` for iVar5, and `move v1,v0` for iVar4 in later blocks. So t=v0 is load-bearing.

Lever-free, can we get t=v0? The allocation: t is a short-lived temp (live ~2 insns), so it gets a caller-saved reg. The question is which one. v0 vs v1 vs a0.

Hmm, and whether the copy survives.

Let me think about the `iVar5 = t` copy. If t and iVar5 are merged by cse, there's no copy and the load goes to iVar5's reg (s1). If they're not merged, the load goes to t's reg (v0) and a copy to s1.

For cse not to merge: at `iVar5 = t`, t must have no valid qty. That happens if the RTL between the load and the copy invalidates the table... 

Hmm, in the C, between `t = load+4` and `iVar5 = t` there's `iVar4 = load+6`. A memory load! cse's table for registers isn't invalidated by a load (loads don't clobber registers). But it might if... no.

Hmm. What about `if (t < 0)`? That's after `iVar5 = t`.

OK so cse merges. How did the original do it?

Maybe the original's `iVar5 = t` is not a copy but the original wrote `iVar5 = t;` where t is a *volatile*? No.

Hmm, maybe the original used a different structure:
```
t = load+4;
iVar4 = load+6;
iVar5 = t;
```
where `t` is... hmm.

WAIT. Maybe the original had `iVar5` as the running max and the load assigned via a function-like macro? No.

Let me reconsider: maybe the target's `move s1,v0` is NOT `iVar5 = t`. Maybe `t` is the load, and `iVar5 = t` is inlined differently. Hmm.

Actually, hold on! Let me reconsider: maybe the C is:
```
iVar5 = t = *(s16*)(uVar3+4);
```
No.

Hmm, what if the load is `t = (s32)*(s16 *)(uVar3 + 4);` and `iVar5 = t;` — and the reason the copy survives is that t is a *hard reg pinned* in the original source (a real Sony macro?). But the pin comment says "NEEDED DIFFERS", meaning the decomp author added it.

OK, so lever-free we need a C trick. The known trick for making a copy survive is the dead-reset (C0414) or a real 2nd set.

What if we do:
```
t = load+4;
iVar4 = load+6;
iVar5 = t;
t = 0;          // dead reset of t? but t is reused later
```
Hmm, t is reused: `t = load+8` later. So t already has multiple sets. A dead reset would add another.

But the issue is the copy `iVar5 = t` being merged. The dead reset AFTER doesn't prevent the merge.

Hmm.

What if we make the copy `iVar5 = t` happen in a different basic block? No.

Hmm, let me look at what happens with the pins but without the t pin (nopin had all 3 pins removed). Let me isolate: remove ONLY the t pin (keep param pins), and remove only the param pins (keep t pin).

Let me test:
- only_t_removed
- only_params_removed

That tells me which contributes what.

Actually from nopin (all removed) score 34 and nolau score 2, I know the pins contribute 34. Let me isolate.

Let me also reconsider: maybe the param permutation and the t issue are linked.

Let me do the isolation quickly.
