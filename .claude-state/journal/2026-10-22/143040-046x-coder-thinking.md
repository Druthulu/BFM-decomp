---
ts: 2026-10-22T20:30:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mJTnY52oBffxOaCPYTuO
---
Multi-set mp → 86 ins (extra reg). Single-set mp = local-alloc s1.

w1 remains the best (2). The two missing addiu's are in delay slots of calls Z and Y. In w1, gcc emits a1 = fp+16 once (in X's delay slot) and assumes it persists. That's actually because the value is in a *hard register* $5 (pinned) and gcc's reload decided the call doesn't clobber... hmm, actually look: the second call has `nop` in its delay slot, meaning a1 was set *before* the `lh a0,20(s0)` insn. There's no addiu there. So a1 is live across call X. GCC would only do that if it thinks a1 is not clobbered by the call — for a call to an external function, a1 IS clobbered (call_used_regs[5]=1). Unless... the pinned register $5 = a1 is treated as "fixed" and reload assumes fixed regs are preserved? That's a known gcc 2.7 bug/hazard with asm pins: a fixed hard register live across a call is not saved, and reload may reuse it.

But the code "works" for the test? Whatever — score is what matters.

Now: the target has 3 addiu. So the target's a1 value is NOT live across calls. In the target, reload rematerializes the constant at each call.

So I need the call argument to be a *constant* (not a hard-reg value) at reload time, while the copy's source is a hard reg.

w4 did that (calls `(void *)m`) → 19 with s1. In w4, the movstr dest pseudo (fp+16) exists and cse uses it for the calls (a reg, not constant).

What if the movstr dest pseudo is *not* fp+16 but a different pseudo: e.g., the copy destination is `src` reused as a pointer: `src = (int *)m; *(Mat32 *)src = D_800AE620;`? Wait, the source also needs src. Order:
```
src = (int *)&D_800AE620;
*(Mat32 *)m = *(Mat32 *)src;   // movstr, dest m (fp+16)
```
the dest address pseudo exists.

What if the copy is `*(Mat32 *)(m) = D_800AE620;` with m accessed via the pinned src as the dest: 
```
src = (int *)&D_800AE620;
*(Mat32 *)m = *(Mat32 *)src;
```
The movstr has both src and dest addresses. The dest (fp+16) pseudo is created regardless.

Hmm, unless the copy destination is a *hard register*: `src = (int *)m;` then `*(Mat32 *)src = D_800AE620;` — dest via hard reg $5, source symbol. Then no dest pseudo; the source base is a symbol (one lui? or per-load?). And the calls use `(void *)m` constant → folded per call (addiu ×3)! And `src` (a1) is set to fp+16 once before the copy, then the copy uses a1 as the dest base (stores at offsets 0,4,...), and after the copy a1 may still hold fp+16 but the calls use the constant, so reload emits addiu per call.

But wait: the movstr source (symbol) needs a register too — gcc would use another reg (v0/v1/a0). Target's source base is a1 and dest stores are sp-relative... In this variant the dest stores would be `sw v0,0(a1)` with a1 = sp+16, not `sw v0,16(sp)`. That differs from the target (which has direct sp offsets). Score would show.

Alternatively `src = (int *)m;` after the copy is what w1 does.

Hmm, what about: copy `*(Mat32 *)m = *(Mat32 *)src;` (w1) AND calls `(void *)m` (constant) — that's w4 = 19 (the dest pseudo). The 19 comes from the dest pseudo being used for calls.

What if the copy's dest is *not* a memory expression with fp+16 but the movstr dest is expressed via a variable that's already dead? Hmm.

Actually, maybe a different trick: make the movstr dest a *different offset* than the call address by copying into a local array `m` at index 0 but declaring m as `int m[9]` and using `m+1`? Then the call address fp+20 vs the copy dest fp+20... same.

Let me look at w1's RTL: how does the dest get expressed? Let me dump w1 and see whether a dest pseudo exists and why calls reuse a1. Maybe the fix is tiny: the `src = (int *)m;` set before the calls produces `set a1, fp+16` once; cse then replaces `(void *)m`... no, calls use src.

In w1, the calls use `(void *)src`. The generated code has a1 set once. The target has addiu per call. If I could make gcc re-emit `set a1, fp+16` for each call... reload normally does that when the value is not in a reg. Since src is a *fixed* hard reg, gcc thinks it's always in a1.

What if the calls use `(void *)(src = (int *)m)` — an assignment expression inside the argument! Real C:
```
RotMatrixX(..., (void *)(src = (int *)m));
```
Each call has its own set of src → 3 sets. cse may remove the redundant ones... but each set is a separate insn and cse's constant propagation might merge them (w5 tested 3 sets = 19, worse). Hmm w5 was 19 because 3 sets of a hard reg → maybe an extra reg appeared? w5's score 19 with 86 ins.

Why would w5 be worse than w1? w5: three `set a1, fp+16` insns; cse removes duplicates? then same as w1? But it scored 19 (86 ins) — an extra callee-saved reg appeared. Odd.

Let me diff w5 to see. Actually, let me think about what target's C really is. The target has:
- source base a1 (one lui/addiu) for 8 loads at offsets — movstr from a symbol or from a pointer.
- dest stores direct sp offsets.
- 3 calls each with addiu a1,sp,16 in the delay slot.
- no extra callee-saved reg.

w1 matches everything except the 2 missing addiu. The difference is that the target reloads a1 for each call. If the calls used a *constant* expression (fp+16) at reload, we'd get exactly that. In w1 the calls use src (hard reg a1) which is already loaded.

So: can I get the source base into a1 *without* using the pinned src as the call argument? The movstr source is the symbol; gcc allocates a1 for it naturally (as in c_struct, where the source base was a1). Yes! In c_struct, the source base was a1 and the calls used the constant m. The only problem in c_struct was the dest pseudo (fp+16) → s1.

So I need to kill the dest pseudo. In c_struct, the dest pseudo came from the movstr's dest address (fp+16). What if the movstr dest address is NOT a constant but the pinned `src`? i.e.:
```
src = (int *)&D_800AE620;
```
Hmm, we need the dest to be m.

What if I write the copy as: `*(Mat32 *)m = *(Mat32 *)&D_800AE620;` — c_struct-like.

The dest pseudo arises from expand_block_move: it creates a pseudo for the dest address if it can't use a constant. When the dest is a local array at a known offset, does expand use a constant address? In c_struct, the dest stores are direct fp offsets in the final asm — so the dest pseudo was eliminated by cse folding it to the constant. But cse also created/kept a pseudo for fp+16 used by the calls.

Actually let me look at c_struct's RTL at .cse to see the insn that creates r80 (insn 21 in lreg = `set (reg 80) (plus fp 16)`). In the .lreg dump, insn 21 is `(set (reg:SI 80) (plus fp 16))` and it's used by `set a1, r80` ×3. So cse created this base register for the 3 call args (not from the movstr). In score-0, cse did NOT create it — it folded the constant into each `set a1`.

Why the difference? cse creates a base register when the constant is used *more than once* and... in score-0 the constant also appears 3 times. Hmm! Unless in score-0 the three call args are in *different basic blocks*? No, same block.

Wait — maybe in c_struct, the movstr expansion (expand_block_move) itself creates a pseudo for fp+16 (as the dest base), and cse then uses that pseudo for the calls. In score-0 there's no movstr, so no such pseudo. Yes, that's what I hypothesized. And the dest stores being direct fp offsets later is reload's doing (the pseudo is rematerialized for the stores? no...).

Let me look at the .cse dump for c_struct to find where r80 comes from. Search for "reg 80" in the cse dump around the function. Actually, easier: check the .rtl (initial) dump for a `(set (reg ...) (plus fp 16))` before the copy. Let me grep the function's rtl section for the first insns.
