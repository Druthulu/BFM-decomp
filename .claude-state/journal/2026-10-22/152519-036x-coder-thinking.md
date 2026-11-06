---
ts: 2026-10-22T21:25:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TutRojgDEWlT740Bog0E
---
a2 is worse: s0 holds mid, and p2 went to s1 (callee-saved). Bad.

So the pointer reuse idea with one variable holding &mid across the call is the crux.

New thought: what if the buffer for call1's third arg is NOT the same object as call2's first arg? Look at the semantics: call1 writes a matrix into mid (mtx+0x34 result?), call2 (func_8012EFB8) takes mid as param_1 and out as param_2. Hmm, maybe in the original C, call1's third arg was `mid` and call2's first arg was `&mid[0]`... same.

What if call1's arg is a *different* stack object of the same size that gcc coalesced into the same slot? No, gcc doesn't share stack slots for distinct objects (it can, with -fstack-sharing? no).

Hmm — but what if `mid` is declared *inside* a block after the first call? Like:

```
Vec3 in; Vec3 out; s32 p2; ...
```
No, mid is needed at call1.

OK, what about making the two address computations differ by the *base* they're computed from: target has both `addiu aX,sp,32` (sp-based). So both come from the frame pointer.

Let me consider the "dead copy" trick from moves line 199: "dead copy vol2=vol + a 2nd def". For pointers, a dead copy: `m2 = mid;` where m2 is never used → dead, eliminated. Hmm.

What about making cse break by a *store to mid between the calls*: 
```
m1 = mid;
call1(..., m1);
mid[0] = 0;      // or some store
m2 = mid;
call2(m2, &out);
```
cse: the address (plus sp 32) is still equivalent; a store doesn't invalidate address equivalences. No.

What about making mid a *parameter-like* pointer: `s32 *mb = mid;` then... same.

Alternative: could the s-reg be avoided by making the value live range end before the call and re-materialize? What if the pointer is computed from something that dies at the call, e.g.:
```
s32 *m1 = mid + (mtx & 0);
```
No, hacky.

Let's reconsider: maybe the crack isn't about cse at all. What if the m1 launder also served to give the a2 addiu a *late* birth, and the real requirement is just the schedule + frame? In nopin (both dropped), the frame was 56 with s1 — that's the big cost.

Hmm what about `-fno-...`? no.

What if I make the mid buffer a parameter of a nested helper? no (signature change).

What if `mid` is accessed as a struct with the two calls taking different members... e.g.
```
struct { s32 a[2]; } mid;
call1(..., mid.a);
call2(mid.a, &out);
```
same.

What if the pointer passed to call1 is `&mid[0]` where mid is `s32 mid[2]`, and to call2 `&mid[1] - 1`? That's identity arithmetic → not allowed, and emits extra.

OK here's another thought: what if the value is NOT held because its live range is short — i.e., if call2's a0 comes from a *different* pseudo that happens to be the same address, computed by a separate addiu. That requires cse to not merge. cse merges (plus sp 32) always.

BUT: cse's merging only matters if both are in the same cse pass scope. What if the second address computation is in a different basic block? cse works per extended basic block; two blocks = two cse scopes. But there are no branches here... unless I add a branch that's always taken/unconditional — that's a real C construct but adds insns.

Alternatively: a loop? no.

Hmm, what about the "2nd set" applied to the *address expression* via a different variable with a different mode: e.g. use `(s32 *)(u8 *)mid`? cse: (plus sp 32) same.

What if mid is `u8 buf[8]` and I cast at each use: `(s32 *)buf` and `(s32 *)&buf[0]`? same.

I think cse-merge is unavoidable for two uses of the same constant address in one ebb, so a single pseudo lives across the call, and global-alloc gives it a callee-saved reg... 

BUT WAIT: gcc's global-alloc, for a pseudo live across a call with *few* references, might prefer spilling if the class has a low priority. There's the known behavior: `REG_LIVE_LENGTH` and `floor` priorities. In func_8014DD8C (moves line 54) they manipulate ref counts to change priorities. If the mid-address pseudo gets *more* uses (higher ref count), it's more likely to get a register. Fewer uses → spill → rematerialize!

In nopin, the merged pseudo has 2 uses (call1 arg, call2 arg). In the target it's rematerialized. Hmm, so why did the allocator give it s1? Because global-alloc prefers a callee-saved reg for a value live across a call if available... 

Let's test the extreme: make the address have exactly ONE use each in two *different* pseudos by making the values differ — impossible.

Alternative: reduce the frame so s1 is "not worth" it? no.

OK, radically different approach: give `mid` a different stack offset per call by splitting it into two arrays that gcc merges? no.

Hmm, what about this: the target's call1 arg is `addiu a2,sp,32` and call2's `addiu a0,sp,32`. What if in the original C, the object was a *local array accessed via a pointer that is recomputed*, and the reason no s-reg appears is that the pseudo's live range doesn't cross the call because the call's arg setup happens... no, the arg is used at the call.

Hmm, actually: is it live across the call? The pseudo P = &mid is used at call1 (as a2, before the jal) and at call2 (as a0, after). So P's live range spans the call. Yes.

Unless the value used at call2 is a different pseudo P2 = &mid, and P dies at call1. Then no cross-call value at all! That's exactly what the launder achieved (opaque output breaks equivalence). And cse merging is the obstacle.

So: how to get two cse-distinct pseudos with the same constant address? cse's `make_regs_eqv` merges REG_EQUAL values. If the second computation is a *different expression that isn't folded*, e.g. `(s32 *)((char *)mid + 0)` — expand folds it. `mid + 0` — folded by expand.

What about `&mid[0]` vs `mid`? Both folded to the same REG.

What about taking the address via a volatile pointer variable? volatile qualifier on a pointer *variable* is not a barrier lever... e.g. `s32 * volatile pm;` — hmm, that would force a memory store/load, adding insns.

What about computing the second address from a *different* base register that is also sp-based... e.g. `out` at sp+24: `(s32 *)((char *)&out + 8)` → gcc computes (plus sp 32) again after folding the +8 into the offset. Expand folds &out + 8 to sp+32? &out = sp+24, +8 = sp+32 → yes, folded at RTL generation into (plus sp 32) with the same MEM/REG_EQUAL → cse equates.

Hmm, unless the fold doesn't happen because out is a struct and the +8 is a char* offset — still folded.

OK, let me consider whether cse really is the issue. In c1 (m1 2nd set), we saw `addiu a2,sp,32` materialized at the call (good!) AND `move a0,s1` after. So the a2 was materialized fresh (because m1's 2nd set made the first value's... hmm) and the 2nd set's value came from s1.

Wait, in c1: `m1 = mid; call1(m1); m1 = mid; call2(m1);`. The a2 was addiu sp,32 (fresh!) and after the call move a0,s1. So s1 holds &mid. Why? Because the 2nd `m1 = mid` assignment is a copy from the constant address, and since the same pseudo (the constant) is live... the copy source is the constant; global-alloc assigned it s1 and reload didn't remat it. So the copy source got a reg. If instead the 2nd set's source is a *fresh* computation at the 2nd set, it'd be addiu a0,sp,32.

Why did the 1st set get rematerialized (addiu a2,sp,32) but the 2nd not? Because after the first call, the value is needed again... this is the same pseudo live from the first set to the second set — so it's ONE pseudo live across the call, held in s1, used by the copy; and reload rematerialized a2 for the call (because the copy... hmm, confusing).

Ugh. Actually maybe: the pseudo P (constant &mid) has 2 uses: call1's arg (a2) and the 2nd set. Local-alloc might have allocated a2 directly for the call arg (combined) and s1 for the other.

Let me step back and think about a completely different real-C approach: **the second call's pointer could come from `mid` being passed by a different type that forces a separate temp**, e.g. call2's first param is `s32 *`; if I pass `(s32 *)&out`... wrong value.

Alternatively: **swap the roles**: make the *first* call use the fresh computation and the second use the held one? Target wants both fresh.

Hmm, let me look at the sibling functions in the same family: func_801495C4 (item 2 in my list) has the same structure with launders on mtx and m1 (m1 = buf), and func_8014964C is its sibling. Maybe other shards cracked a similar function: search moves.md for 801495C4 or "mid"/"m2 =". moves.md line 44: "launder: p = *abase; p += 0x2D (self-reassign stales cse...)". Line 57: "launder -> real 2nd set `pv = *p; pv &= 0xFF000000; *p = pv | ...`".

Let me grep moves.md for "801495" and for "buf" and for functions with two calls to the same buffer.

Also there's .run/P40/T10/func_80181F4C/notes.md as a worked example. And maybe a cookbook entry on launders/cse. Let me grep cookbook/INDEX.md for cse-const-addr / launder.

Time check: started item 2 at ~15:18? Let me track. Budget 20-30 min per item. It's 15:2x. Let me be efficient: grep cookbook + moves for launder-crack patterns.
