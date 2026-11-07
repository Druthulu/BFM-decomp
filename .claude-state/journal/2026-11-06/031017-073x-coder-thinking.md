---
ts: 2026-11-06T10:10:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ii2CoTKQFqqYxunELgFh
---
Hmm, in g1, s1ang is in s1 (good? "s1->s0 x6, s0->s1 x3" — mixed). Wait: `lh s0,18(v0)` in mine[10] — so s1ang is in s0 still? Let me see: mine[10] `lh s0,18(v0)` and mine[17] `andi s0,s0,0xfff`. So s1ang (the loaded value) is in s0, and the andi result... Also mine has `sll v1,s1,0x10; sra s1,v1,0x10` — that's d's sign extension in s1. So d is in s1, s1ang in s0. Still swapped!

And the instruction count dropped by 1 because the `andi` for u5 and the `andi` for s1ang got... hmm, mine[17] `andi s0,s0,0xfff` (s1ang), and where's u5's andi? mine[20] bne s0,a0 — a0 = u5 (masked where?). The u5 andi must be merged into `subu a0,a2,v0`? Let me see: mine[15] `subu a0,a2,v0` (u5 = ratan2 - 0x400), then... no andi? Hmm, `subu a0,a2,v0` then `sll v1,s1` then `andi s0,s0`. Where's `andi a0,a0,0xfff`? Missing! That's the lost instruction.

Because `u5 = (ratan2(...) - 0x400) & 0xFFF` and then `if (s1ang == u5)` — hmm, maybe gcc combined the andi with something. Actually, the `andi a0,a0,0xfff` should be there. Let me look at mine's full asm. The diff shows mine[14:18] deleted relative to target[17:17]: mine 14 jal, 15 subu a0,a2,v0, 16 sll v1,s1, 17 andi s0,s0. So u5's andi is missing! gcc must have optimized `(x & 0xFFF) == (y & 0xFFF)`? No... 

Oh wait, maybe gcc's `& 0xFFF` on u5 and then comparing with s1ang (which is also & 0xFFF) — it might have folded the u5 mask into the comparison? Hmm.

Actually — maybe the issue is `s1ang = s1ang & 0xFFF` made gcc realize the comparison `s1ang == u5` where both are masked... no.

Hmm, this variant lost an instruction, so it's wrong. Let me reconsider.

Maybe I should make s1ang global WITHOUT overwriting it: use `s1ang` in a later block via a *separate* masked variable but keep s1ang alive... no.

Alternatively: make u6 global but ALSO make s1ang global by using s1ang in a later block. Hmm.

Wait — actually, let me reconsider g1's register result: "s1->s0 x6, s0->s1 x3" means mine has s1 where target has s0 (6 times) and s0 where target has s1 (3 times). Since mine has d in s1 and s1ang in s0, that's still swapped. So making s1ang global did NOT happen (or didn't help).

Let me check the alloc table for g1. But the instruction loss suggests the RTL changed. Let me abandon g1.

Let me think differently: maybe use a *separate* variable that is a copy of s1ang but used later, making s1ang... no.

Hmm, what if the target's s1ang IS local and got s1 because of a different reason: the qty ordering in local-alloc. Let me look at qty_compare: priority = refs*log2(refs)/live. s1ang: refs 2, live 7 → 2857. If there were another local qty crossing the call with HIGHER priority, it'd get s0.

What if we introduce a *second* variable that crosses the call and has higher priority, but whose allocation doesn't add instructions? For example, if `u5` were computed before the call... no.

What about the `d` sign-extension: `d = (s16)d` creates a value. If the sign-extension were done BEFORE the call (at the prologue), then... the target has it after.

Hmm, what about `t`? no.

OK, let me look at this from the "how many tries" perspective. I've done ~15 scored tries on item 2. The brief wants 30 for a WALL. Let me try a few more clever variants, then if nothing, mark WALL with tag `lreg-qty-order` (or `greg-alloc-order`).

Actually — wait. Let me reconsider the possibility of making `d` local. What if the division uses a *different* variable in each block, both loaded from a saved value? E.g.:

Actually, here's a thought: what if the divisor is stored in a *static/global* variable? No, target uses s0.

Hmm, what if the source uses `arg1` directly in the divisions and there's no `d` variable, and gcc's "save_call_clobbered_regs" puts arg1 in s0 via reload? But we saw v4 (no d) scored 25 (with pin removed). Let me test v4 with pin kept? No.

Let me reconsider: the target's d is in s0 because... maybe the ORIGINAL source had `d` as a *parameter* to an inline? no.

OK here's another idea: the *order of the qty priority* — what if we make s1ang's live range longer by moving its LOAD earlier (before other code) so that its priority drops below... it's the only local-crossing qty, so it still gets s0.

Unless we make a SECOND local-crossing qty. What if we load `s1ang` into a temp `s1t` before the call, use it after, and also keep another value? No.

Hmm, hold on — what if we make `u5` cross the call? u5 is the ratan2 result (born at the call). Can't cross.

What if we compute `u5` from a pre-call value? No, it's the call result.

Let me look at the problem from the target's *prologue*: the target saves s0 and s1. The save order: `sw s0,16(sp); move s0,a1; sw ra,24(sp); sw s1,20(sp)`. Hmm, the saves are ordered by register number? s0 (16) at 16(sp), ra (31) at 24(sp), s1 (17) at 20(sp). Not by number. It's the order the prologue emits: `sw s0` first (because s0 is set early by move s0,a1?), then sw ra, then sw s1. 

In the nopin, `move s1,a1; sw ra; sw s0`. So d's assignment to s1 happens first, then ra save, then s0 save.

Hmm.

Let me try a fundamentally different idea: use `s32 d = arg1;` but reference `d` in the s1ang load's address, e.g.:
```
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
```
No.

What if we reorder so `d` is used before the call (e.g., `if (d == 0) ...`)? That adds code.

OK. Let me look at whether there's a known technique for "local qty takes s0 before global". Let me grep moves.md for "local" + "s0" or read the lreg-qty-order entries.

Line 178: func_801415C0 WALL lreg-qty-order — "locals c,d take $s0/$s1 before globals a,b,e; the target has a=$s0,b=$s1 and no plain-C spelling flips the order (G07)".

Hmm, that's the opposite direction (locals take s0/s1, target wants globals to). In our case, one local takes s0 and the target wants the global to have s0.

Let me grep moves.md for MATCH with a similar flip. Search "lreg" in moves.md.
