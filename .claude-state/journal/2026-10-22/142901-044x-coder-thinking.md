---
ts: 2026-10-22T20:29:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n7y8bGoY3duntwRycYLY
---
Very close: the first call has `addiu a1,sp,16` in the delay slot; the next two have `nop` because a1 already holds sp+16 (cse/flow knows a1 is unchanged after the call? No — a1 is call-clobbered! But the callee is a known function? GCC knows RotMatrixZ might clobber a1...). Actually the `addiu a1,sp,16` before the first call sets a1; after the call a1 is clobbered. Yet gcc emits nop for the 2nd/3rd → it must think a1 is still live/unchanged. Hmm, that would be a miscompile unless... wait, the sequence: `addiu a1,sp,16` in the X delay slot; then `lh a0,20(s0)`; `jal Z`; `nop`. If a1 is clobbered by X, the nop is wrong. But this is gcc 2.7.2 and the target has addiu in each. So mine has a *bug-like* reuse: probably the `src = (int *)m` set is a single pseudo (hard $5?) — since src is pinned to $5, after the first `set a1, fp+16`, subsequent uses reuse the value because it's a hard-reg value that cse considers equal and flow doesn't kill across the call (calls clobber a1, but maybe the call insn's clobber set is only ra? For a call to a function, gcc marks call-clobbered regs as clobbered in CALL_INSN... In 2.7 the call insn doesn't list a1 as clobbered; `call_used_regs` handles it at flow/global level. Since a1 is call-clobbered, flow should kill it. But here the value in a1 is used after the call, which means gcc considers it live across the call — because the *pseudo* src (hard $5) is live and gcc allows hard regs to be call-clobbered only if... hmm, this would be a real bug. Unless RotMatrixX's return... no.

Anyway: the target has `addiu a1,sp,16` in each delay slot. I need gcc to re-materialize the address at each call. Mine does it only once.

The difference: mine's address pseudo is a hard reg ($5) set once, and the calls use `(void *)src`; gcc reuses a1 across calls without reloading (because the pseudo is a hard reg and the calls' delay slots are filled by reorg; the reload of a1 for the next call... hmm).

What if the calls use `(void *)m` after the `src = m` assignment? Then cse equates m's address (constant) with src's value... 

Alternative: make each call's argument a *fresh* set of src: e.g. `src = (int *)m; RotMatrixX(..., src); src = (int *)m; RotMatrixZ(...); src = (int *)m; RotMatrixY(...);` — three real sets of the hard reg → three `addiu a1,sp,16` (or `addiu` once and reuse? each set is a separate insn; cse might remove the redundant sets as they're the same value... but they're separated by calls that clobber a1? If cse thinks a1 isn't clobbered, it removes the redundant sets).

Hmm. Let me look at what the target does: `addiu a1,sp,16` in each delay slot. That's reload rematerializing a constant at each use. Mine sets a1 once and reuses across calls (which is actually wrong at runtime, but the target differs).

Let me try: calls with `(void *)(src + 0)`? identity.

Try instead: after the copy, don't assign src; keep the calls as `(void *)m` but with the copy from src:
w4: `src = (int *)&D_800AE620; *(Mat32 *)m = *(Mat32 *)src;` then calls `(void *)m`.
That's the c_struct shape with the source via the pin. cse will create the fp+16 base pseudo from the movstr dest (as before) → s1 → 19? Or maybe not, since the source is a hard reg... Let me test.

Also w5: `src = (int *)&D_800AE620; *(Mat32 *)m = *(Mat32 *)src; src = (int *)m; RotMatrixX(..., src); src = (int *)m; RotMatrixZ(..., src); src = (int *)m; RotMatrixY(..., src);`

And w6: use `src` for the calls but with `src = (int *)m;` placed inside each call argument? no.

Also: maybe the issue is the second/third call reuse a1 because the *first* `addiu` is in the delay slot and gcc's reorg moved the reload into the delay slot; for the others, the reload insn was `set a1, src` where src was coalesced to a1 → no-op → nop. If each call had its own `set a1, (const fp+16)`, reorg would fill each delay slot. So the problem is cse merging the three uses into one value that stays in a1.

Hmm, but a1 is call-clobbered; gcc reusing it across a call is odd. Unless gcc's cse2/flow knows the calls are to functions whose... no. Let me check: maybe the value is re-materialized but the *reload* insn `set a1, fp+16` gets moved by reorg into the delay slot only for the first, and for the others the reload insn is placed *before* the `lh a0` (i.e., `addiu a1,sp,16` appears at 33d8? No, we see `lh a0,20(s0)` at 33d8, then jal, then nop).

So after call X, gcc believes a1 still = fp+16. That's only valid if X preserves a1. Since RotMatrixX is an external function, a1 is call-clobbered. GCC 2.7's `flow` kills call-clobbered regs... unless the value's pseudo is hard $5 and the hard reg is marked as *not* used across the call due to a missing clobber. This is the "pin" hazard: a pinned hard register used across calls can produce code that reuses it. But it scored 2 and gcc emitted it; whatever.

Target wants the reload each time. So I need gcc to NOT coalesce/keep the value in a1 across the calls. If the calls use `(void *)m` (constant) after the `src = m` trick, cse might keep the constant and emit addiu per call (like score-0). But the movstr dest pseudo may again win.

Let me test the batch:
w4: copy from src; calls `(void *)m`.
w5: triple sets of src.
w6: copy from src; calls `(void *)(int *)m`? identity.
w7: copy from src; then `mp = m;` (int *mp) and calls mp (a normal pseudo, single set → local-alloc s1? maybe global? Let me see).
w8: copy from src; calls with `(void *)m` but assign `src = (int *)m;` and then `m[0] = m[0]`? no.

Also w9: use the `o2` variable (int, already declared) as a temp for the address: `o2 = (int)m;` then calls `(void *)o2` — a cast of an int; cse equates with the constant; probably folds to addiu per call like score-0. But `(void *)o2` where o2 is int → gcc may keep the constant. Try.

Let me test these.
