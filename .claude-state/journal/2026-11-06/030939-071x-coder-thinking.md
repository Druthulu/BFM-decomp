---
ts: 2026-11-06T10:09:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UdBZJpttNZj24uu30uPz
---
The ordering: mine has `sll s0,s0,0x10` at position 17, target has it at 19. So the keepalive anchors u5's computation (addiu/andi) before the sll. Without the keepalive, sched1 moves the sll earlier (to position 17).

To fix with real C: make u5's computation depend on something that forces it before the sll, or make the sll depend on u5.

The target order (positions 17-22):
```
17: addiu v0,v0,-1024   (u5 = ratan2 - 0x400)
18: andi a0,v0,0xfff    (u5 &= 0xFFF)
19: sll s0,s0,0x10      (d = (s16)d)
20: andi s1,s1,0xfff    (u6)
21: bne s1,a0
22: sra s0,s0,0x10
```
Mine (p2):
```
17: sll s0,s0,0x10
...
20: ...
```
So the sll moved before the addiu/andi.

Why? The sll (d = (s16)d) is independent of u5. Sched1 can hoist it. The keepalive creates a use of u5 right after its computation, which... hmm, actually the keepalive asm is a "use" of u5 that must stay in place, preventing the sll from moving above it? The asm is a scheduling barrier for the *value* u5.

Real C alternative: make the sll (d's sign extension) depend on u5. E.g., reorder statements so that `d = (s16)d;` comes AFTER a statement that uses u5. But the source already has `d = (s16)d;` after `u5 = ...`. Sched1 reorders because there's no data dependency.

What if we make d's sign-extension data-dependent on u5 via real C? E.g., `d = (s16)(d + (u5 & 0));`? That's an identity launder — forbidden ("identity-statement launders do NOT count as a crack"). Hmm, `+ (u5 & 0)` is an identity fold, likely optimized away.

What if we reorder so that the sign extension is computed in a context after u6? E.g.:
```
u6 = s1ang & 0xFFF;
d = (s16)d;
```
w1 scored 21 (with the pin). Let me test w1 with the pin (p2 variant): pin kept, keepalive removed, and u6 before d.

Hmm. Let me think: the target order is addiu, andi(u5), sll(d), andi(u6). So d's sign extension is between u5's andi and u6's andi. In the source: u5=..., d=(s16)d, u6=s1ang&0xFFF. That's the source order. Sched1 reorders d's sll earlier. 

The keepalive anchors u5. What real C construct anchors u5's computation? A *use* of u5 that the scheduler can't move. For example, if `u5` is used in the next statement in a way that creates a dependency. The next statement is `d = (s16)d;` which doesn't use u5. What if we compute `u6` from u5? No.

Hmm, what if we reorder to:
```
u5 = ...;
u6 = s1ang & 0xFFF;
d = (s16)d;
```
Then the source order is u5, u6, d. Sched1 might produce addiu, andi(u5), andi(u6), sll(d)? The target has sll before andi(u6). Hmm.

What about:
```
u5 = ...;
if (u5 == u6) return 0;   // uses u5
d = (s16)d;
```
Then u5 is used in the branch, but the branch must come after u6's andi... the target order is sll(d) then andi(u6) then bne. Hmm.

Let me look at the target order again: addiu(u5), andi(u5), sll(d), andi(u6), bne. So sll(d) is between andi(u5) and andi(u6). 

Sched1 schedules within a block based on dependencies and priorities. The sll(d) can be placed anywhere after d's birth and before d's uses. It got placed early (position 17) without the keepalive.

To force it later, make d's sign-extension depend on u5. Real C: `d = (s16)(d & ~(u5 - u5))`? Identity, optimized away.

What about using u5 in the sign extension legitimately? E.g., the original source might have computed something like:
```
d = (s16)d;
```
no dependency.

Hmm, what if the *sign extension* is done differently: `d = (s16)(d + 0);`? Still independent.

Wait — maybe the keepalive is anchoring not u5's computation but the *call result*. Let me re-read the comment: "scheduling barrier: anchor u5 before the (s16)d cast". So it anchors u5's computation before d's cast.

Real C alternative: make the d cast depend on u5 by computing d's cast after a use of u5. Hmm.

What if we move `d = (s16)d;` to AFTER the `if (u6 == u5) return 0;`? No — d is needed in the divs later, but the sign extension could be delayed. But the target has the sll at position 19 (before the bne at 21). If we move it after the if, the sll would be in a later block. No.

What if the C uses `u5` in the computation of u6? `u6 = (s1ang & 0xFFF);` — no.

Hmm. What if the sign-extension is expressed as part of the division: `q = iVar4 / (s16)d;`? Then the sign extension might be hoisted by cse to the earliest point. In v3 I tested `s16 d` (score 25 with pin removed). Let me test `s16 d` with the PIN KEPT to isolate.

Actually, let me reconsider: the original source probably had `d = (s16)d;` exactly as we have it, and the keepalive was added because the reconstruction differed. So the original must have had something else that anchors u5.

Idea: the original might compute `d = (s16)d;` BEFORE u5 (i.e., right after `d = arg1`), but the scheduler moves it... no, then the sll would be in the prologue.

Hmm, wait. Let me reconsider: maybe the original didn't have the `d = (s16)d` statement at all; instead `d` was declared as `s16` and the sign extension happens at the division. Let me test that with the pin kept: `s16 d;` + pin.

Actually, let me be systematic. I'll test with the pin KEPT (so the register issue is out of the way) various ways to eliminate the keepalive:
- k1: `s16 d` (pin on a s16? the pin is `register s32 d __asm__("$16")` — with s16, use `register s16 d __asm__("$16")`).
- k2: move u6 before d cast.
- k3: `d = (s16)d;` moved after u6.
- k4: `q = iVar4 / (s16)d;` and remove `d = (s16)d`.

Hmm, this is getting long. Let me prioritize: the PIN is the bigger problem (score 38). If I can't solve the pin, the keepalive doesn't matter. So let me focus on the pin first.

Actually, wait — the p2 result (score 2) is encouraging: the keepalive replacement might be solvable. And the pin replacement is the hard part.

Let me think about the pin once more. We need d→s0, s1ang→s1. 

IDEA: What if we make `s1ang` GLOBAL by giving it a use in a later block *that replaces u6's uses*? Specifically, what if we eliminate u6 and use `s1ang & 0xFFF` directly everywhere? Then:
- s1ang's def (load) in block 0, used in block 0 (first andi) and later blocks.
- CSE would compute the andi once in block 0 → the CSE temp is global.
- But s1ang itself: used only in block 0's andi → local.

Unless CSE doesn't hoist and each use recomputes the andi → s1ang used in multiple blocks → global. That would add instructions (multiple andi). Score worse.

Hmm.

IDEA 2: What if `d` is made local by ensuring all its uses are in block 0? The divisions are in blocks 6,7,9. What if we compute the division results in block 0 and select later? That changes code.

IDEA 3: What if we change the *type* of s1ang to make its qty size 2 (DImode)? Then qty_size=2 → priority doubles → still s0 (it's alone). No.

IDEA 4: Make s1ang's qty *tie* with a hard register s1 via a copy. If s1ang is copied to/from s1, local-alloc's copy suggestion would put it in s1. How to get a copy from s1? If we write `s1ang = some_value;` where some_value is a function's return in s1? No.

Hmm, but actually, a *copy preference* doesn't force the reg; it makes the qty allocated in the "sugg" pass first. If s1ang had a copy preference for s1, find_free_reg with `just_try_suggested` would try s1. That would give s1!

How to create a copy preference for s1? In RTL, a `(set (reg:SI 17) (reg:SI s1ang))` or `(set (reg s1ang) (reg:SI 17))` — a move between s1ang and hard reg 17. There's no such move in the target.

But what about the *store* `sh s1, ...`? No.

Hmm.

IDEA 5: What if the original's d is allocated by local-alloc because the function has only ONE block at that stage? No.

Let me look at the actual target's alloc order by comparing with the nopin. The nopin global order: 78 80 79 77 76 74. If s1ang were global, the order would include it. Its pri 2857 → last (after 74's 5185). So order: 78 80 79 77 76 74 75. Then r74 (d) gets s0 (first free callee-saved) and r75 (s1ang) gets s1. 

So if s1ang is global, target achieved.

How to make s1ang global: its live range must span blocks. The def is `lh s1,18(v0)` in block 0, the use `andi s1,s1` in block 0. 

What if the def is in block 0 and the use is in block 1 (after the `if (u6 == u5) return 0;` branch)? That would change the instruction order (andi after bne). Not target.

What if the def is in a block BEFORE block 0? Impossible.

Hmm, what if the load is in a *conditional* block that's entered before block 0? No.

What if we make the andi's *result* (u6) and s1ang the SAME qty by writing `s1ang = s1ang & 0xFFF; u6 = s1ang;`? Then s1ang is used in later blocks (via u6? no, u6 is a copy). Hmm: `s1ang &= 0xFFF; u6 = s1ang;` — u6 is a copy of s1ang. Then s1ang is used in the andi (block 0) and the copy (block 0). Still local. u6 global.

What if we write `s1ang &= 0xFFF;` and then use `s1ang` everywhere u6 was used? Then s1ang is used in blocks 1,2,3 → global! And the andi is `andi s1ang,s1ang,0xfff` in block 0. That matches the target's `andi s1,s1,0xfff`! And s1ang would be global with priority: refs (load + andi + subu + 2 addiu = 5), live length long. pri = floor_log2(5)*5/live. live ~ 40 → 0.25 → 2500. d's pri 5185 > 2500, so d gets s0 and s1ang gets s1! TARGET!

But wait — does this change the instruction count? Currently u6 is a separate variable used in blocks 1,2,3. If we replace u6 with s1ang (after masking), the instructions are identical: `andi s1,s1,0xfff` then uses. The only difference is the variable name/identity. Let me try:

```
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
u5 = ratan2(...) - 0x400) & 0xFFF;
d = (s16)d;
s1ang = s1ang & 0xFFF;      // or s1ang &= 0xFFF
if (s1ang == u5) return 0;
iVar4 = u5 - s1ang;
...
```
But this requires removing u6. However, the source also has `u6` used in the comparisons. Let me rewrite using s1ang everywhere.

Hmm, but the ANDI in-place: `s1ang = s1ang & 0xFFF` where s1ang is global. The load's pseudo (the original s1ang before masking) is a different value; if we overwrite s1ang, the original load's result and the masked value are different pseudos (SSA-like). In gcc RTL, `s1ang = s1ang & 0xFFF` is `(set (reg s1ang) (and (reg s1ang) 0xFFF))` — the same pseudo is both source and dest. That's a self-set, which gcc might handle as: the load defines r75, then `(set r75 (and r75 0xFFF))`. Both are the same pseudo r75. Then r75 is global (used in later blocks) → global-alloc. 

But does the self-set create the same RTL? The target has `lh s1,18(v0)` then `andi s1,s1,0xfff`. Yes.

But careful: gcc might see `s1ang = s1ang & 0xFFF` and create a new pseudo for the andi result, then the load's pseudo dies at the andi (local). Depends on RTL generation: for `x = x & c`, gcc generates `(set (reg:SI x) (and:SI (reg:SI x) (const_int c)))` — the same pseudo. Yes, in RTL, the assignment to the same variable reuses the pseudo (it's not SSA).

So s1ang would be a single pseudo defined by the load, redefined by the andi, used later. Live range: from the load (block 0) to the last use (block 3) → global. 

Then: is the load's pseudo the same as the andi's? Yes. So the pseudo is live across the call AND across blocks → global. 

Now the priority: refs = load-def + andi-use + andi-def + subu-use + 2 addiu-uses = 6 refs; live length = from load to last use ~ 40-50. pri = floor_log2(6)*6/live = 2*6/45 = 0.267 → 2667. d: refs 7, live 27 → 5185. So d > s1ang → d gets s0, s1ang s1. TARGET!

And the sign extension of d: `d = (s16)d` — in this variant, where does it go? The target has sll(d) between andi(u5) and andi(s1ang). The keepalive (still present in this test? no, we're removing it too). Let me first test this variant WITH the pin kept and keepalive kept? No — let me test it fully lever-free (pin removed, keepalive removed) and see the score.

Wait, but if s1ang becomes global, the `lh s1,18(v0)` and `andi s1,s1,0xfff` — the load pseudo is global and gets s1. The andi is in-place. 

Let me write this variant: replace u6 with s1ang throughout, and remove the separate `u6` variable.

Original:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
```
Variant:
```
s1ang = s1ang & 0xFFF;
if (s1ang == u5) return 0;
iVar4 = u5 - s1ang;
if (iVar4 > 0x800) { t = s1ang + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = s1ang - 0x1000; iVar4 = u5 - t; }
```
Let me create it and score (lever-free, i.e., no pin, no keepalive).

Note: the declaration `s32 u6;` would remain unused (harmless) or remove it.

Let me write g1.c.
