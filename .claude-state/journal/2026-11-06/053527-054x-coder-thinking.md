---
ts: 2026-11-06T12:35:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t3G8THH9u1nzgBgtDbDJ
---
This is regclass's precompute: prefclass based on operand constraints of the insns that use the pseudo. For a pseudo that only appears in copies (set v0 = pseudo) and loads, prefclass might be ALL_REGS or a generic class.

This is getting deep. Let me be empirical: try variants and check which gives ret v0.

Quick diagnostic approach: modify c2 (which has ret in a0) by adding a real C use that makes ret prefer v0. Ideas:

1. Use ret in an expression that requires v0? No.
2. Make the STORE/return form: `return ret;` is a copy to v0 → copy preference. It's already there in c2 and ret still got a0 (because pass 0 avoided v0 due to regs_someone_prefers).

Which allocno prefers v0? Probably `ptr` (the func_8012C1B8 result, moved to a0) or `tmp1/tmp2`. In the target, the same preferences exist, yet ret got v0. Hmm, unless in the target the priority order differs so ret is allocated before the v0-preferring allocno.

Wait, actually in c2 the whole function is otherwise identical to the target except the early returns and... hmm, and the target has `ret` in v0. Since c2 differs from orig only in (a) pin removed, (b) asm removed, (c) early returns → 0, maybe the *asm removals* changed the priority order so ret lost v0.

Let's test: c2 + keep everything but the pin? i.e., what does the original (with asms) do if only the pin is removed? That tells whether the pin is the sole cause. But we can't keep asms.

Alternatively, test whether the early `return ret` matters more: c1 (with asms removed, early return ret) gave s0. So the asm removal + early-ret = s0.

OK. So we need to find a lever-free way to make ret's allocno get v0. Options:

(a) Raise ret's priority so it's allocated before the allocno that prefers v0. Priority = floor_log2(n_refs) * n_refs * 10000 / live_length. ret has ~8 refs; live length short. Adding a ref could bump floor_log2 from 3 to 4 (8→16 refs) — that's a lot.

(b) Give ret a copy preference for v0 that beats others: `hard_reg_copy_preferences` for v0 via the `v0 = ret` copy exists. `regs_someone_prefers` includes v0 if any allocno *prefers* it. prune_preferences computes: for each allocno, for each preferred reg, if some OTHER allocno has a conflict... let me read prune_preferences to understand which allocno "prefers" v0.

Actually, maybe simpler: let me test whether removing the early returns to `return ret` but *initializing* ret differently... 

Hmm, hold on. Let me reconsider the whole approach: maybe keep `return ret;` in the early returns and instead make those early returns NOT use ret by using a *different* variable that the target's code also produces naturally. Look at the target's early return at 1aa4: `beqz a0,1e3c` — a0 = ptr, and the return value is v0 which holds... at 1aa0: `move a0,v0` (ptr = func_8012C1B8()) — so v0 = ptr, and `beqz a0` → return. The return value would be v0 = ptr = 0. Interesting: `return ptr;`!? That would emit `move v0,a0`? Hmm, but gcc would then need v0 = a0, and if a0 is dead... it emitted nothing because ptr is already v0? No — at 1aa0 `move a0,v0` copies v0→a0, so v0 still holds ptr. Then `return ptr` → `v0 = a0` — a copy that local-alloc/global-alloc could coalesce... but a0 and v0 are both hard regs at that point (v0 already holds the same value, so gcc's cse/reg move elimination might delete the move as redundant since v0 == a0 value? gcc doesn't know that).

Alternatively `return 0;` at that point: gcc knows ptr==0 in that branch → could emit `move v0,zero`? Mine emitted `move v0,zero` (line 21 of the diff: mine has `j; move v0,zero`).

Hmm what about the FIRST early return: mine emitted `j; move v0,zero` too.

So we need a return expression that produces no insn at all. What if we return the *struct field* we just stored? No.

New idea: what if the two early exits are not `return` but `goto RET` where RET is the epilogue `return ret;`? Then the value in v0 must be ret... that's the same as return ret.

What if the function returns void? No, signature s32.

Hmm, hold on! What about making the early exits `return ret;` but declaring `ret` so that its live range doesn't cross the calls — the uninitialized use at entry is the problem. What if we move those early returns to use a *separate* variable `s32 rv;` that is also uninitialized? Then rv's allocno: live entry→use, crossing a call → callee-saved reg. That adds a saved reg (bad).

Unless... rv's use is *before* any call in the first case? No: `func_8012CAE4(...); return rv;` — the call is before the use.

Hmm, what if rv is used at a point where a call-clobbered reg is allowed: the allocno's `calls_crossed` counts calls crossed by the live range. For the first early return: rv live from entry to that point crosses func_8012CAE4? Yes (the call precedes the use).

OK so that doesn't work either.

Completely different approach: maybe accept `return 0` but the target's 2 insns difference could be compensated... no, we need exact.

Wait wait. Let me re-look at the target's first early return region:

```
1a78: lui s0,0
1a7c: addiu s0,s0,0
1a80: bnez v0,1a98
1a84: nop
1a88: jal func_8012CAE4
1a8c: nop
1a90: j 1e3c
1a94: nop
```
So `j 1e3c; nop` — a j with a nop delay slot. If the C were `return 0;`, we'd get `li v0,0` + `j` and the li would be in the delay slot (`j 1e3c; li v0,0`)? reorg might put li v0,0 in the j's delay slot. In mine (c2): `j 1e2c; move v0,zero` — yes, the move is in the delay slot. So `return 0` costs exactly 1 insn per early return (2 total).

Target has a nop delay → no value setup. So the target's early return value is a pseudo that ends up in v0 (dead) — i.e., `return ret;` with ret in v0.

So the whole puzzle is: get ret into v0 without the pin. This is exactly the "expand-void-return"-family wall, but here with a real return.

Idea: what if the two early returns return ret, but we ADD a definition of ret at entry that gcc can fold into v0's existing value? Like `ret = 0;`? Then live range entry→early-return crosses the call → callee-saved.

Idea: make the early returns not cross a call: the first early return is after func_8012CAE4. What if the source order were `return ret;` before the call? Can't — the call must happen.

Hmm, but wait: does the live range from entry to the first use really cross a call? The live range starts at function entry (insn 0). func_8012CAE4 is called at 1a88, before the use at 1a90. So yes.

BUT: if ret is *defined* before that call (e.g. at entry), the live range starts at the def; still crosses the call.

What if the early returns use a *s16* value? no.

Alternative: what if we make `ret` a pseudo that is only live in short ranges AND the early returns use a *different* dead value, e.g. `return (s32)ptr;`? At the second early return, ptr is 0 there. `return ptr;` → move v0,a0 — 1 insn (target has none). Hmm, but wait: maybe local-alloc would coalesce v0 and a0? They're hard regs; no.

OK, radical alternative: maybe restructure the C so that there are NO early returns at all, and the target's `j 1e3c` early exits come from a different construct. For instance:

```
if (cond) { call; }
else { ... }
```
The target's `j 1e3c` after the call — could come from a `goto RET;` where RET: is the return. If the C were:

```
if (D_801ED4E4[...] == 0) {
    func_8012CAE4(param_1);
    goto RET;
}
...
STORE:
    unk2 = ret;
RET:
    return ret;
```
Then `goto RET` + `return ret` → the goto jumps to the return block; the return block does `v0 = ret` (a move). At the early goto, v0 = ret must hold... The target has no move at the early goto. Same problem.

Hmm, unless ret is v0 anyway.

Let me try yet another angle: force ret into v0 by *using* ret in a place where v0 is required, e.g. pass ret as a function argument? No.

What about the classic: make the variable's only "home" v0 via a copy chain that local-alloc ties? E.g. `ret = func_returning_v0();`? In the arms, ret = constant.

Hmm, what about using `(s32)(((struct...)->unk2 = ret))`... 

Let me look at this from the data: in c2 ret got a0. In the target ret has v0. What if the difference is only about which allocno prefers v0? `regs_someone_prefers` — prune_preferences. Let me read it: for each allocno, for each preferred hard reg r, if the reg is "preferred" by another allocno that conflicts... Let me read lines 829-890.
