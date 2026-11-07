---
ts: 2026-11-06T06:17:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xO0kl3enpJunKUZkxgQt
---
u1 (do-while) = 6 (66 ins, worse). u2 = 1.

Hmm. The `lh v0,256(a0)` persists.

Let me think about this differently. The target's instruction is `lh v0,256(s0)`. Mine is `lh v0,256(a0)`. The base register differs but the value is the same (a0 == s0 at that point).

What if I change the *source* so the pointer is in a register that gcc won't substitute? The issue is the parameter a0 being equivalent to s0.

Hmm, what if the function's parameter is used in a way that keeps a0 "dirty" at that point? E.g., if a0 held something else at 2938, gcc would use s0. But gcc set a0 = s0 at 292c for the call.

What if the call arg setup happened *later* (after the unk100 load)? Then a0 would be free at 2938... but the unk100 load needs a base; a0 doesn't hold the pointer (clobbered by the earlier call), so it'd use s0.

So: if I can make the `move a0,s0` happen after the unk100 load, gcc would use s0 for the load.

In the source, the call arg setup comes from `func_8012AD50((void *)pa0)` where pa0 = (s32)a0. If pa0 were a *distinct* variable assigned later (closer to the call), sched1 might still hoist the move.

The target has the move at 292c (early), so it doesn't matter there.

Hmm, in the target the load uses s0 because the source is a hard reg.

OK — maybe I should try harder to keep a distinct variable for the pointer that gcc maps to s0 without splitting.

IDEA: use the parameter directly but make the *unk100 load's base* a distinct variable `q` assigned from a0 at the very start of the last block, where gcc would... propagate.

IDEA: make the last block's unk100 access use `((Unkstruct_800B5CB8 *)s0v)` where `s0v` is assigned from a0 *in a different basic block* (e.g., before the last call). Hmm.

Hmm, let me look at the target's RTL: the unk100 access uses the hard reg 16 (s0). In a lever-free body, the equivalent is the callee-saved pseudo.

What if I use a variable `s0` (declared at the top) but ensure gcc doesn't split? Let me look at p1's RTL more: reg72 (parameter) is used 10 times, reg73 (s0) 5 times. The propagation splits.

What if the copy is `s0 = (s32)a0` and the *parameter is used before the copy*? No.

What if we make the parameter's mode different from s0's so they can't coalesce? Then we'd get 2 regs (worse).

Hmm.

OK, let me look at this from the "what's the difference" angle: mine uses a0 for the unk100 load; the target uses s0. If I could make a0 NOT equal s0 at that point, gcc would use s0.

What if the last block's first statement clobbers a0? E.g., `v1 = (s32)&D_80184CCC[0];` — that doesn't set a0.

What if I reorder: `func_8012AD50((void *)pa0);` is the last statement; its arg setup (move a0,s0) is hoisted. What if I put something between that requires a0 to be free?

Hmm.

Alternatively: what if the `pa0` variable is not a copy of a0 but a *reload* of the pointer from memory? E.g., `s32 pa0 = *(s32 *)(...);`? Hmm.

Actually — here's a thought: what if the last block's stores use `(s32)a0 + 0x58` etc. (as in s5, no pa0)? Then gcc needs a0 = the pointer, so it sets a0 = s0 before. Same.

Hmm.

Let me try: make the func_8012AD50 call use `(void *)(s32)a0` and put the unk100 load *before* it in a way that sched1 keeps the move after. Scheduling is hard to control.

Alternatively, accept score 1? The task requires 0 for a MATCH; 1 is not a MATCH. Hmm, but it's very close.

Let me try more variants:
- v1: use a `s32 s0v` variable assigned from a0 at the top of the function, and use it ONLY for the unk100 load (so gcc doesn't split?).
- v2: use `(s32)a0` for the unk100 load but wrap the whole last block in a do-while(0) to change scheduling.

Hmm, u1 (do-while on the load) = 6.

Let me try v2 (do-while around the whole last block).

And v3: declare `s32 s0v;` at the top, assign `s0v = (s32)a0;` right before the last block's unk100 load.

Hmm, s0v would be a copy → gcc coalesces with a0 → same.

Let me think about what makes gcc choose s0 vs a0 for a load base. If both are available and equal, gcc's local-alloc picks the register of the pseudo. The pseudo here is the parameter (allocated to s0). The `move a0,s0` creates a copy; cse/regmove might replace uses of s0 with a0 (a "regmove" optimization: copy propagation to eliminate the copy's source use). Hmm.

What if the parameter pseudo is NOT s0 but something else? In q1/s5, the parameter is allocated to s0 (callee-saved) because it's live across calls.

Hmm, what if we make the parameter live in a different callee-saved reg (s1) by using a second variable? Then the unk100 load would use s1? No, the target uses s0.

Hmm, the register name must be s0 ($16).

What determines the callee-saved register choice? Global alloc assigns the first available. In q1/s5, the parameter gets $16 (s0). Good.

So at 2938, the parameter is in $16. gcc used a0 instead. That's the regmove/copy-prop.

Can I prevent the copy `move a0,s0`? It's the call arg setup for func_8012AD50. The call needs the pointer in a0. So the move is required.

Then gcc's regmove pass may rewrite the unk100 load's base from s0 to a0 (since a0 == s0). That's the "regmove" optimization (gcc 2.7.2 has regmove.c). It tries to eliminate the copy by using the destination register in the source's uses.

In the target, the source's base is a hard reg $16, so regmove can't rewrite it? Hmm, regmove works on pseudos.

So: to prevent regmove, the load's base must be a hard reg or a pseudo that regmove can't change. Hmm.

Actually, regmove only rewrites within a basic block and if profitable. Hmm.

Let me try: make the unk100 load happen in a *different basic block* than the copy. E.g., wrap the load in an if? No.

Hmm, what if the `move a0,s0` is in a different block? The call arg setup is in the same block.

Hmm, what if I restructure the last block so the call comes first and the load after? Then the move would be before the load in the same block.

OK. Let me try yet another approach: maybe the target can be matched with a completely different structure that produces `lh v0,256(s0)`.

Let me look at the target's last block again:
```
292c move a0,s0
2930 lui v1,D_80184CCC
2934 addiu v1,v1,0
2938 lh v0,256(s0)
293c lh a1,112(a0)
2940 sll v0,v0,0x4
2944 addu v0,v0,v1
2948 lui v1,0x4000
294c or v0,v0,v1
2950 sw v0,88(a0)
2954 jal func_8012AD50
2958 sw a1,28(a0)
```
So: s0 is used for the unk100 load; a0 (pa0) for the rest.

In my body, if I use a `pa0` variable for the pointer-arithmetic accesses and the *parameter* for unk100, gcc might use s0 for unk100 if regmove doesn't rewrite. s6 did that and got a0.

Hmm.

Let me try making the unk100 access use a variable that gcc allocates to a *different* register than a0. E.g., a variable `s0v` that's live across the call... but then it'd be callee-saved and maybe $17.

Hmm.

Let me try: declare `s32 s0v;` at the top, assign `s0v = (s32)a0;` and use s0v ONLY for the unk100 load in the last block, while everything else uses `(s32)a0`. gcc would allocate s0v... it's live from the top to the last block (across calls) → callee-saved, maybe $17 (if the parameter is in $16). Then the load would use $17, not $16. Wrong.

Hmm.

What if s0v is assigned right before the load (in the last block)? Then it's a copy of a0 → coalesces → same.

Hmm.

OK, let me try the opposite: make the *whole* last block use s0v where s0v is a copy assigned at the top... 

Actually, let me revisit the p1 approach (s0 variable) and try to fix the extra copy differently. In p1, the parameter and s0 are separate. What if I make the parameter unused by casting it immediately: `s32 s0 = (s32)a0;` and then never use a0. gcc propagates some uses back to a0 (10 uses). Hmm.

What if the parameter is declared `void *a0` and I immediately assign `s32 s0 = (s32)a0;` and then use s0 — gcc's copy propagation (in the front end or expand) may use a0 directly for some uses because a0 is a hard reg with the value.

To prevent that, make a0 clobbered early: the first call does that. Uses after the first call must use s0.

But p1's reg72 (parameter) had 10 uses — so gcc used a0 for 10 uses, meaning a0 was live... but the calls clobber it. Hmm, unless those uses are before the first call. There's only one statement before: the store `unk20 = call()`. Hmm.

Wait — maybe reg72 isn't the parameter but something else. Let me look at the RTL again:
```
(insn 4 2 5 (set (reg/v:SI 72) (reg:SI 4 a0)))
(insn 11 8 14 (set (reg/v:SI 73) (reg/v:SI 72)))
```
reg72 = the parameter value; reg73 = s0.
reg72 used 10 times across 23 insns, crosses 2 calls, pointer.

So reg72 IS used across calls. That means gcc uses the parameter pseudo for many accesses across calls. Since a0 is clobbered by calls, reg72 must be in a callee-saved reg ($16).

And reg73 (s0) in $17.

So both are callee-saved. The copy at insn 11 (s0 = a0) is between them.

If gcc had propagated all uses to one, we'd have 1 reg.

Hmm, gcc's "copy propagation" (gcse/cse) should equate reg72 and reg73 at insn 11... but they're both live afterwards (split uses).

To force one: maybe make the copy's source dead? Hmm.

OK, I'm spending a lot on item 5. It's 23:16 now; item 5 started ~23:07. ~9 min. Let me continue — this is crackable (score 1).

Let me try a few more:
- w1: use `s32 s0 = (s32)a0;` and replace all uses with s0, but ALSO make the parameter's value die immediately by using a different cast... hmm.

- w2: what if the source uses `s0` for everything and the function parameter is named the same? no.

- w3: what if I make the last block's unk100 access via a *pointer variable* `s16 *p = (s16 *)s0 + 0x80;`? Adds an instruction.

Hmm.

Let me look at the regmove hypothesis: maybe gcc's `regmove` rewrote the load's base from s0 to a0 to eliminate the `move a0,s0`. If so, making the copy *not* eliminable would help. Hmm.

Actually, wait — maybe it's not regmove but *scheduling*: sched1 might have changed the register? No, sched doesn't change registers.

Let me look at the .lreg/.greg for s5 to see the disposition of the load's base pseudo.

Let me dump s5.
