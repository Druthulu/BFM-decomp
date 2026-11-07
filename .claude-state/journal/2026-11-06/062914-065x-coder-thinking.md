---
ts: 2026-11-06T13:29:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1xSgfwM5QkhCGqg72JN6
---
Block 17 in orig: from 221 to 373 (vs nobar 221-371). So the asm (insn 371?) is inside the block; the block ends at 373. So the asm does NOT split the basic block. It's just a barrier within the block, creating dependencies.

So in the orig, sched1 schedules the whole loop body in one block with the asm forcing the addiu before it.

Let me look at the orig's block 17 scheduling to see the emitted order. But we know the target's final order.

So we need a real-C construct inside the block that creates a scheduling dependence ordering the addiu before the s0 chain.

Idea: a *memory store* before the s0 chain that aliases with a load after it? The addiu isn't memory.

Hmm, what if we move `d[2] = s0;` (a store) BEFORE the s0 chain? No.

What if the s0 chain's first insn were a *load* that aliases a store before it? Not relevant to the addiu.

Fundamentally: the addiu is a pure register computation; sched1 can move it freely. To pin it, something must depend on it (or it must depend on something ordered). The asm makes EVERYTHING depend on it. Real C: make an early-ordered insn use the a1 value.

What if `aa`/`nn` are passed to an earlier call? E.g., if there were another call between... there isn't.

What if we change the code so that the call's arguments are set up early by using them in the rand calls? No.

What if we compute `nn` as `(s32)buf` and then use `nn` in an expression that's scheduled early: e.g., `t = rand(); s0 = ...;` Hmm.

What if we swap: `nn = (s32)buf;` then immediately `func_80015978` is moved earlier? No.

OK, alternative: accept a different but equivalent target ordering? No — score 0 requires exact.

Hmm, what about *changing the s0 chain* so that its priority drops below the addiu's? sched1's priority = the longest path. If we make the s0 chain shorter, its priority drops. The chain: andi, sll, andi, addiu, addu = 5 insns. The addiu a1 has 1 successor (the call). If the chain's priority were 1, ties are broken by LUID (source order) — source order has nn before the chain, so the addiu would be picked first! 

Wait: the priorities in the dump: insn 310 (addiu a1) priority 1; the chain insns have priority 1-3. The scheduler picks by priority then by LUID. In the "ready list at T-xx" logs, we see e.g. "ready list at T-19: 225 (1) 305 (1) 288 (1) 310 (1), now 310 305 288 225" — at T-19, all four have priority 1 and it picked 310 first. But that's near the end (T-19 of 49). The picks are backward: T-49 first ... T-1 last. So the emitted order is the reverse: the last picked (T-1) is emitted first.

Hmm, actually with backward list scheduling, at each step it picks the insn to place at the LATEST available slot. T-1 is the last insn of the block. So picking 310 at T-19 means it's placed 19 slots before the end. Picking 225 at T-48 means it's placed near the beginning.

So insn 310 was placed at T-19 (late-ish, right before the call at T-18?). The chain insns 315-324 were placed at T-15..T-19? Hmm, the listing shows 310 before 305 before 312 in the final order.

Anyway, priority matters. The chain's last insns (the store 305) have priority 1 too.

What determines whether 310 is placed early? In the backward scheduler, it's picked when ready. 310's dependence: REG_DEP_ANTI 281 (the second rand call) — so it can't be placed before the call 281. That's why it's after the rand calls (matches target: after the second rand). And it can be placed anywhere after.

To force it early, we need an insn that depends on 310 to be placed early. The call 312 depends on 310 (uses a1). The call is placed at the end.

Hmm, so what if we add a *second* use of nn that occurs early? E.g., pass nn to a function... no.

What if we make the s0 chain depend on the addiu? E.g., `s0 &= 0x1F;` where the 0x1F comes from... no, must be a constant.

What if the store `d[2] = s0` aliases with `buf`? If the compiler thinks `d[2] = s0` might alias `buf[?]`, no.

OK, radically different idea: what if we make `nn` be computed NOT from `buf` but from a value already in a register that requires an add? The target insn is `addiu a1,sp,16` — the address of buf. Any way to make that address computation depend on something early? The frame pointer is available at entry.

What if we use `(s32)(buf + 0)` where the add depends on a variable that is set early? E.g., `nn = (s32)buf + (i - i);`? fold x-x=0? Let me check: gcc's fold does fold `x - x` to 0 only if x has no side effects and isn't volatile — yes, it does (in 2.7.2? "A - A -> 0" might require !flag_trapv... it's a standard fold). If it folds, no dep.

What about `nn = (s32)buf;` and then using `nn` in a *volatile* read? no.

Hmm, let me reconsider the whole thing: maybe the barrier isn't about sched1 but about sched2 (post-reload). The asm also affects sched2 (the same dependency analysis runs post-reload). The final order difference could come from sched2. In the sched1 dump above (nobar), the order after sched1 is: ..., 302, 310, 305, 312. In the final object, the order is: addu(302), addiu a1(310), jal(312), sh(305 delay). So sched1's order is what we see. If we could make sched1's order match the target's, sched2 might keep it.

So we need sched1 to place 310 early.

Insight: sched1's backward scheduling places an insn early if it has high priority (long chain to the end). What if we make 310's result feed a long chain? I.e., use `nn` in the s0 computation. But that changes the code... unless the use is in a computation that's *removed later* by dead code elimination? Hmm, sched1 runs after flow (dead code removed) — a dead use would be gone before sched1.

What if the use is a *copy* that gets coalesced: e.g. `s32 x = nn; ...` and x is used in the s0 chain? That changes the chain's registers but might produce the same code if x coalesces to $5? Hmm: `s0 = s0 + (x & 0)` no.

Let me think about the target's code again:
```
37e0: jal rand
37e4: move s0,v0
37e8: addiu a0,s3,4      ← aa
37ec: addiu a1,sp,16     ← nn
37f0: andi s0,s0,0x1f
...
```
Both addius are together. So the original source order likely had aa and nn assignments right there (as now), and the barrier pinned them.

Given the difficulty, this might be a WALL. But wait — the task says these items are in a "crack shard" where the expectation is to crack barriers. Items 3,4,5 also have barriers. Maybe item2 is one of the hard ones.

Before giving up, let me try a couple more:
1. Move `nn = (s32)buf;` to the very top of the loop body (before the rand calls) — then sched1 would place the addiu right after the loop head, before the rand calls. Target has it after the rand calls. But maybe sched1's anti-dependence with the rand call... the addiu doesn't depend on the rand. If placed before the rand calls, it'd be at the loop head. Not target.

2. What if we make the call's a1 setup use a *constant* dependency: e.g. `nn = (s32)(buf + i * 0);`? fold.

3. What if we declare `buf` with an initializer so that the address is taken early? e.g. `u16 buf[4] = {0};` — the initialization stores to buf at the top, generating `addiu a1,sp,16` (or a0?) early + stores. That adds code.

4. What if `d[2] = s0;` is written as `*(u16 *)(nn + 12) = s0;`? Then the store uses nn as the base, creating a dependence: the store (early-ish? no, the store is late) uses nn. The store is at the end. Hmm, but that could create a chain: addiu a1 → store. The store is late anyway.

5. What if the s0 chain is written to use `buf` — no.

6. What about making `aa` and `nn` used in a *conditional* before? no.

Let me look at the sched1 priority formula to see if there's a cheap way to raise 310's priority. In sched.c, `priority()` computes: for each insn, `INSN_PRIORITY = cost + max over successors`. The successor of 310 is the call 312 (priority maybe 1). The chain insns have higher priority because they feed the store/call.

Actually, wait: the store 305 has priority 1 too, and the call 312 has priority 1. So everything is priority 1 at the end. The scheduler picks the highest priority; ties broken by LUID (higher LUID first in backward scheduling). 310's LUID is HIGHER than the chain insns' (it's later in source: 310 > 305 > 302...). So in a tie, 310 should be picked FIRST among priority-1 insns... and in backward scheduling, picked first = placed latest. Hmm, that gives late placement. 

So to place 310 early, it needs a LOWER LUID or higher priority. Lower LUID = earlier in source. But it's already before the s0 chain in source (nn = (s32)buf is before s0 &= ...). Wait, the insn numbers: 310 (addiu a1) vs 305 (store d[2]) vs 302 (addu). The RTL insn numbers are assigned in expansion order; 310 is HIGHER than 305 — because the address computation for the call arg was expanded after the store? Hmm, in the source, `nn = (s32)buf;` comes before the s0 chain, so its insn should have a lower number. But insn 310 > 305. That means the address computation `(plus fp 16)` was generated *at the call site* — i.e., the compiler didn't materialize nn early; it rematerialized the address at the call! 

Indeed: `nn` is a pinned hard reg; the assignment `nn = (s32)buf` is a set of a1, but the compiler may have kept it as a REG_EQUIV and recreated it... no. Actually insn 310 is `(set (reg:SI 5 a1) (plus:SI (reg:SI 30 $fp) (const_int 16)))` with insn_list:REG_DEP_ANTI 281. Insn 281 is the second rand call. So this insn was created right after the rand call — matching the source order (nn = (s32)buf is after the rand calls). And the s0 chain insns are 293-305 (also after). So 310 > 305 because the address computation comes AFTER the s0 chain in the RTL? But source order has nn before the chain!

Hmm wait, look at the RTL: 288 is probably `aa = ...`? Let me look at the source: 
```
s0 = rand();     // 228
t = rand();      // 233
aa = (s32)(q + 1);   // 288?
nn = (s32)buf;   // 310?
s0 &= 0x1F;      // 293?
```
The insn numbers suggest nn's set is 310, after the chain (293-305). So the compiler DEFERRED the address computation to the call. Why? Because `nn` is a hard-reg variable and the assignment `nn = (s32)buf` was... hmm, actually the register allocator (local-alloc? no, this is before). At sched1 time (before local_alloc), the RTL has pseudos. The dump shows `(reg:SI 5 a1)` — a hard reg! Because nn is pinned via `register ... __asm__("$5")`, the variable is a hard register from the start (not a pseudo). So `nn = (s32)buf` is `(set (reg:SI 5 a1) (plus ...))`.

Why is its insn number 310, after the chain? Because expand processes statements in order: `nn = (s32)buf;` should produce an insn before the chain. Unless... the C source order is different from what I think! Let me re-read the orig block:

```
            s0 = rand();
            t = rand();
            aa = (s32)(q + 1);
            nn = (s32)buf;
            __asm__ __volatile__("" ::: "memory");
            s0 &= 0x1F;
            ...
            d[2] = s0;
            func_80015978(aa, (s32 *)nn);
```
So nn's set should be before s0 &=. But the RTL numbers say 310 > 293.

Unless the compiler *sank* the assignment at the tree level? No, expand emits in order.

OH WAIT. Maybe the barrier's presence changes things: in the nobar dump, the RTL numbers are 310 for the addiu. Hmm, but the source has nn before the chain. Unless the statement `nn = (s32)buf;` was optimized: since `nn` is only used at the call, and the address is rematerializable, gcc's cse/fold may have moved... no, cse doesn't move insns.

Hmm, let me look at the actual insn numbers in the nobar RTL listing: 288, 293, 295, 297, 299, 302, 305, 310, 312. Let me map:
- 288: probably `aa = (s32)(q+1)` (addiu a0, s3, 4)
- 293-302: the s0 chain
- 305: d[2] = s0
- 310: nn = (s32)buf
- 312: call

So the source order in the RTL is: aa, s0 chain, d[2], nn, call. That means the `nn = (s32)buf;` statement is NOT where I think it is! Let me re-read orig.c around there. Maybe the source has nn assigned just before the call, not before the barrier!

Let me check orig.c.
