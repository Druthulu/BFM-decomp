---
ts: 2026-10-22T21:24:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Orwgm2OUcKtAonniAWex
---
Still s1 (the mid address held across call1) — the `move a0,s1` at 18. So the 2nd set did not shorten the live range: cse merged the two `m1 = mid` sets into one pseudo? Since both sets assign the same value, cse might make the second set a no-op/delete it... Actually gcc kept 2 sets (36 ins) but the value is still in s1.

Hmm. The value &mid is live across call1 in the first set → assigned s1. Then `m1 = mid` after the call is a copy from... the same pseudo, so s1 again.

What if the 2nd set uses a different expression so cse can't fold it into the same pseudo: e.g. after call1, set `m1 = &mid[0];` while the first is `m1 = mid;`? cse: (plus sp 32) both. Same.

OK, cse merging is the wall. What breaks cse equivalence? A memory clobber between them? cse doesn't invalidate address equivalences on calls.

Hmm, but wait: in the target, how did the *original* C (before levers were added) look? The launder was added by a previous phase as "NEEDED DIFFERS" — meaning the body originally had something else. Maybe the original body passed the address differently, e.g. `func_8012F14C(mtx + 0x34, pin, &mid)` and `func_8012EFB8(&mid[0], &out)` — different spellings but same cse value.

Let me think about how to get two materializations of sp+32 with no cross-call live value. cse merges equal address values into one pseudo. The pseudo is live across the call → s-reg. UNLESS the pseudo is rematerializable and reload decides to remat (it doesn't; global-alloc assigns a callee-saved reg first).

Key: global-alloc gives a callee-saved reg because the pseudo is live across calls. If instead the pseudo's value is *reloaded* per use — that requires the pseudo not to be in a register at all, e.g. reload rematerializes REG_EQUIV constants when the pseudo is not allocated (spilled). For a pseudo live across a call with few uses, the allocator prefers s-reg over spill.

So: make the pseudo have MANY uses so spilling/remat is cheaper? Or make the value not live across the call by ensuring the *first* use's value is dead before the call... but it's used AT the call (as the arg). The arg is set before the jal, and after the jal the value is still needed for call2 → live across.

Therefore, the only lever-free way: ensure the two uses are different values. If they're different values, cse can't merge... but the address expression is identical.

UNLESS: I introduce an intervening statement that makes the address non-invariant from cse's view — e.g. a store through a pointer that might alias the stack? gcc's cse invalidates REG_EQUAL for addresses if... no, the address &mid is a constant.

Hmm, what about making mid's address depend on a variable that changes? E.g.:
```
s32 mid[2];
s32 *m1 = mid;
...
```
What if `mid` is a VLA? no.

What about using an alloca-like pointer: `s32 *base = mid;` ... same.

What if the buffer is passed as an offset from another pointer that is a *variable*, e.g. `pin + 4` (s32*)? pin is s16*; pin+4 = sp+16+8 = sp+24 (that's out, not mid).

Interesting alternative: reorder the stack layout so that mid's address = a1 + 16 (a1 = sp+16 = &in)! If I pass `(s32 *)(pin + 8)` for call1's third arg (pin is s16*, +8 = +16 bytes → sp+32 = mid), gcc would compute `addiu a2,a1,16` — but the target has `addiu a2,sp,32`. gcc's address computation from a1 (which is &in in a register) would produce addiu a2,a1,16, not sp-based. Not matching.

So the target must have computed from sp. OK.

New idea: what if the value isn't a single pseudo because the two calls take different *modes* — e.g., call1's arg is `(void *)mid` and call2's is `mid`? Different modes still same address in ptr_mode? Pointers are SImode. Same.

What if call1's arg is `&mid` (address of array, s32 (*)[2]) cast to s32*? `(s32 *)(&mid)` — cse equates.

Hmm. Let me look at this from a different angle: maybe the s1 register is not for &mid. Look at c1: index 15 `addiu a2,sp,32` (materialized at the call, good!), then after the call `move a0,s1`. What is s1? If a2 already got the value, s1 must be... maybe s1 = mid's address is held because after the call `m1 = mid` is a 2nd set and global-alloc put the value in s1 (a callee-saved reg) so the 2nd set is a no-op copy, then `move a0,s1` is that copy. So the 2nd set `m1 = mid` = copy from the merged pseudo.

So the merged pseudo is used at: call1 (a2) and the 2nd set. If the 2nd set's value is the same pseudo, the copy is register-to-register and needs the value in s1 across the call.

What if I make the 2nd set read from memory instead of from the merged pseudo? E.g. store the pointer to a stack slot and reload it:
```
s32 *pm;
...
pm = mid;
call1(..., pm);
m2 = pm;     // reload from memory
call2(m2, &out);
```
Here pm is a *memory* variable (address-taken? no, just a local whose address is not taken). gcc would keep pm in a register anyway (it's a local scalar). Unless pm's address is taken: e.g. `pm = mid; call1(...); m2 = *(s32 **)&pm;` — hacky.

Alternative: use a real memory round-trip that's natural C: `mid[0] = ...`? no.

OK, think about the target's shape again:
```
addiu a2,sp,32   (call1 arg3, materialized before call1)
jal call1
addiu a0,a0,52   (delay slot)
addiu a0,sp,32   (call2 arg1, materialized fresh)
jal call2
addiu a1,sp,24
```
So call2's a0 = sp+32 is computed right after the first call's delay slot. That's consistent with: the value for call2 was computed fresh (rematerialized), not held.

For gcc to rematerialize, the pseudo must be REG_EQUIV to a constant address and not assigned a register (spilled). gcc's local-alloc/global-alloc... With `-O2` and `flag_expensive`? In gcc 2.7.2, reload's rematerialization happens for pseudos that don't get a hard reg. A pseudo live across a call gets a callee-saved reg if one is free and the class has priority. Here there are 2 callee-saved regs available (s1..s7 in this TU?).

Hmm, what if we *increase register pressure* so the allocator can't give s1? That's ugly.

Alternative: what if the value is used in a *loop*? no.

Let me revisit: is the launder on m1 really needed, or could a different real-C restructure produce the target without it? Let me try the "split into two variables with different types/offsets" idea:

What if `mid` is a single array but call1 gets `mid` and call2 gets `mid` — a2.c = 22 (36 ins). Let me see a2's diff: maybe there the a2 and a0 are both materialized at the calls and the failure is elsewhere (e.g. an extra s-reg for something else). 36 ins, score 22. Let me look.
