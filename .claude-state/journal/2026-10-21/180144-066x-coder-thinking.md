---
ts: 2026-10-22T00:01:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_5RfFw7PNZKr1ZhSWVtaW
---
The current time is 18:00 (the earlier timestamps in my session were 17:34 at start, and the date now says 18:00). So the elapsed time is ~26 minutes, not 1.5 hours — I was misreading. Let me reconstruct the timeline with the actual clock:

- 17:34:31 start (first date).
- 18:00:54 now.

So the whole session is 26 minutes. My per-item times:
- Orientation + 8017E4E0: 17:34–17:50 (~16 min)
- 8017EEB0: ~17:50–17:53
- 8017D3A0: ~17:53–17:56
- 8017FB50: ~17:56–17:59
- 8014CF04: ~17:57–18:00 (overlaps)
- Write-up: 18:00+

Since the budget is 20-30 min per item and I have 5 items, I actually have time left! The total per item was only ~5 min each. Hmm, but I've already concluded the walls. Should I spend more time on the walls?

I have ~4 items at WALL. The budget says 20-30 min per item. I've spent ~5 min per item on the wall items. Given the clock shows only 26 minutes elapsed, I could invest more in the two most promising: 8017FB50 (score 2!) and 8014CF04 (34).

8017FB50 at score 2 is very close: the only diff is the sll/sra pair. Let me think harder about it now that I have time.

The s16 trick: `s16 tmp` → the value is stored in a 16-bit pseudo, which wins $16 (priority), but the promotion to s32 for the func_801823D4 call costs 2 insns.

What if instead of `s16 tmp` I use a *32-bit* tmp but give the call result a shorter live range in a different way? The priority: pri = log2(n_refs)*n_refs*size/live_length. For the call result to beat the arg pointers (10/L_a), we need 2/L_r > 10/L_a.

Alternatively — what if the arg pointers had FEWER refs? Their n_refs = 5 = 1 set + 4 uses. What if the pointer variables were assigned by a COPY from a common base, e.g.:

```
s32 *p_out = (s32 *)&v[3];
s32 *flag_out = p_out + 1;
```
Then: p_out = 1 set + 4 uses = 5 refs; flag_out = 1 set (a copy from p_out) + 4 uses = 5 refs. Same.

What if flag_out were NOT a variable but the expression `p_out + 1` used in the 4 calls? Then:
- p_out: 1 set + 4 uses = 5 refs.
- p_out+1: CSE'd into 1 pseudo: 1 set + 4 uses = 5 refs. Same. BUT the asm: the target has `addiu s1,sp,52` — a separate addiu from sp. If GCC computes p_out+1 = s2+4, the asm would be `addiu sX,s2,4` → different. Unless GCC's CSE computes the constant address sp+52 directly (since &v[3]+1 is a frame constant, GCC's cse might fold it to the constant sp+52 and materialize it with `addiu sX,sp,52`)! That's plausible: the address is a constant offset from the frame pointer; GCC's RTL would be (plus (reg sp) (const 52)) — and if p_out = (plus (reg sp) (const 48)), then p_out+1 = (plus (plus (reg sp) 48) 1) → cse/could fold to (plus (reg sp) 59)? No: 48+1 = 49?? Careful: &v[3] is at sp+48 and &v[3]+1 (as s32*) is sp+52 (4 bytes). The C expression `(s32 *)&v[3] + 1` = sp+48+4 = sp+52 ✓ (pointer arithmetic on s32* scales by 4).

So the RTL for `p_out + 1` where p_out = sp+48: (plus (reg:sp) (const 52)) after folding → GCC's fold would produce a single addiu from sp ✓ — the same as the target!

So writing the 4th argument as `p_out + 1` (or as the literal `(s32 *)&v[3] + 1`) might produce the same asm as the target: `addiu s1,sp,52` ✓.

But would the n_refs change? The 4 uses of `p_out+1` would be CSE'd into one pseudo with 4 uses + 1 set = 5 refs. Same as before. Hmm. Unless the CSE merges the *set* differently: e.g. if the 4 uses of the constant address are folded to a constant expression, then reload would materialize `addiu a3,sp,52` in each call (4 addiu's) instead of 1 + 4 moves. The target has 1 addiu + 4 moves → so the target's flag_out is a variable with 4 uses.

Hmm, so the target has 2 variables (p_out, flag_out) with 5 refs each. To match, I need 2 variables with 5 refs each, and the call result (2 refs) to win $16. Impossible by the priority formula...

UNLESS the priority formula's tie-break works in my favor: if the call result had 5 refs too... no.

Hmm, what about the `size` factor: pri *= allocno_size. If the call result's allocno had size 2 → 2*2=4 (n_refs=2) vs the args' 10. Still less. Size 5? No.

What if the call result's n_refs were 4 (1 set + 3 uses)? log2(4)=2 → 8 < 10. n_refs=5 → 10 = tie → the tie-break by allocno number decides! The call result's allocno number: allocnos are numbered in the order the regs are renumbered (by first appearance in the RTL?). If the call result's pseudo appears BEFORE the arg pointers' pseudos in the RTL, its allocno number is lower → it wins the tie → $16!

How to get the call result to 5 refs? Its refs: the set (from the call) + the use (in func_801823D4) = 2. Each extra use = an extra instruction... unless the extra uses are FREE (e.g. dead code eliminated? no, then no refs).

Hmm, what about the copies: in the target, `move s0,v0` — the call result is copied to s0. That's a copy insn: (set (s0) (v0)) — a hard-reg copy, not a pseudo ref.

What if the tmp variable were used in a comparison that GCC folds but keeps a ref? E.g. `if (tmp == tmp)` → GCC removes it entirely (no refs).

What about `idx = func_801823D4(tmp, -0x1A);` and also `idx = func_801823D4(tmp, -0x1A);` twice? That would be 2 calls → different asm.

Hmm, what if tmp is passed to a function that takes it and returns it... no.

OK, so the priority route is closed. What about a completely different route: the "hard_reg_preferences" mechanism! In global-alloc, an allocno that is copied to/from a hard reg gets a preference for that hard reg. The call result is copied to s0... no wait, s0 is a hard reg here (the callee-saved). In the unpinned version, the call result is a pseudo, and the copy `move sX,v0` is a pseudo→hard copy, which gives the *hard* reg a preference (not the pseudo).

Hmm! But the TARGET has `move s0,v0` — a hard-to-hard copy. The preference for s0 would be attached to the allocno that is copied to s0 — but in the target, the allocno IS the hard reg s0 (pinned).

Hmm OK.

Let me try yet another approach for 8017FB50: what if the *tmp* variable is declared as `s32` but the value is stored via a `u16` temp and then widened... no (extra insns).

Actually, WAIT. What about making the 16-bit trick work without the extension: the extension happens because the value is passed to a function taking s32. What if the *call* to func_801823D4 took the value from a 32-bit variable that GCC keeps in the same register? E.g.:

```
s16 tmp16;      /* the trick: short-lived pseudo wins $16 */
s32 tmp;
tmp = RotTransPers(...);      /* 32-bit: move sX,v0 */
tmp16 = (s16)tmp;              /* sll sY,sX,16 — an extra insn */
idx = func_801823D4(tmp, -0x1A);
```
Extra insns → score > 0.

Hmm, but hold on! What if the *truncation* is free because the s16 pseudo and the s32 pseudo get the SAME register (the allocator ties them)? Then `sll s0,s0,0x10` (in place) — that's 1 insn, and the target has 0 extra... no, the target has just `move s0,v0` (the call result → s0) and later `move a0,s0`. With the trick, we'd have `move s0,v0` (or `move sX,v0`) + `sll s0,s0,0x10` → 1 extra insn.

So the best case with the s16 trick is 1 extra insn (score ~1?). fb_d had 2 extra insns (sll + sra) because the s16 value had to be widened for the call.

Hmm! What if the value is used in a way that needs no widening — e.g. if the *stored* value were the s16? No, the call needs s32.

OK, let me try ONE more idea for 8017FB50: the "move a0,s0" in the target is the copy of tmp into a0 for the func_801823D4 call. What if the C passed the value in a way that GCC emits `move a0,sX` from a 32-bit reg holding tmp? That's the current s32 case (which loses $16).

So the fundamental tension: the 32-bit tmp must be in $16, and the arg pointers must be in $17/$18, but the priority gives $16 to the 5-ref pointers.

Hmm, hold on! What if the arg pointers' n_refs are lower because their 4 uses are *copies* that the allocator ties? In gcc's global-alloc, there's a "copy preference" mechanism: `hard_reg_copy_preferences` — when an allocno is copied to a hard reg, the hard reg gets a preference. But the allocno's n_refs still counts 5.

Hmm, what about `allocno_n_refs` being "weighted"? In global.c: "Number of refs (weighted) to each allocno" — the weighting might count the refs differently for copies. Let me look at how allocno_n_refs is computed in global.c (the scan). If a copy to a hard reg counts less...

Let me look at the code that computes allocno_n_refs.

Actually, let me try a cheap experiment instead: what if the 4 calls pass the pointers in a way that reduces their refs — e.g. by using a helper macro? No.

What if the two pointers are stored in a 2-element array and the calls pass `outs[0]`, `outs[1]`? Then GCC would load them from the stack (extra insns) — unless it keeps them in regs and the array in the stack (extra stores).

Hmm.

Let me try a different framing: what if the *result* tmp were given 5 refs by using it twice in a way that produces no extra instructions? For example, if tmp is compared with 0 in a way that GCC folds...

What about: `idx = func_801823D4(tmp, -0x1A);` — what if tmp is also used as the *value* of another variable that is dead? GCC removes dead assignments before allocation → no refs.

OK, one more idea: what if the *first* RotTransPers call's result is assigned to tmp AND the compiler keeps it in a register with more refs because the 4 calls' `move a2,sX` copies reference the same register? No, those are the pointers.

I'll accept 8017FB50 as a WALL with best 2. But let me do one quick experiment: does `s16 tmp` + `(u32)` cast give a different (maybe 1-instr) result? And does `short tmp` with the call passing `tmp` give 2? Let me test 3 variants quickly (1 min):
- fb_f: s16 tmp, call `func_801823D4((u32)tmp, -0x1A)`.
- fb_g: u16 tmp, call `func_801823D4(tmp, -0x1A)`.
- fb_h: s16 tmp, but tmp assigned from a separate s32 var (so the s16 truncation is a separate insn).

Let me also test for 8014CF04 a couple of new ideas (10 min budget):
- The "single base" trick: what if the q-relative accesses are written so that the q-1 base is not a common base? E.g. spell the store as `q[-1] = 1;` (current) — the store is the 5th use of q-1. What if the store is spelled `*(u8 *)(q - 1) = 1;`? Tried (s02) → 34.

Hmm, what if the four negative accesses were spelled with a *different* base so that no single base covers 5 uses? E.g. use `q - 0x19` for one of them and `q - 0x1D` for another... they already are.

Actually, what if I make the accesses use offsets from q that are NOT all negative-relative? Hmm.

Let me think about why GCC chose q-1 as the base. In gcc 2.7's reload.c, the "address base" selection for a memory reference: it tries to find a base register among the pseudo-registers that can hold the address, and it has a cost model. The address `q - 0x19` can be formed as q + (-25). The reload pass would prefer to use the existing pseudo q (already in a reg) with an offset. But the "q-1" pseudo might have been created by loop.c as a derived IV.

Let me test: what if the loop's `q += 0x10C` were spelled `q = q + 0x10C` (cf_d) → 34. What if the *store* `q[-1] = 1` were moved outside the loop? No, semantics.

Let me try: what if I use a separate variable for the q-1 store, e.g. `u8 *qm = q - 1; ... *qm = 1;`? Then qm is a separate register (extra insn) → worse.

Hmm, what if the 4 negative accesses were rewritten to use `q` as a `u16 *`? The offsets are in bytes; the target's asm has byte offsets (-25, -29, -107, -85) → the base is a byte pointer.

What if the loop pointer were `s32 *q`? Then the offsets would be scaled → different asm.

OK: 8014CF04 = WALL, best 22.

Given the time (18:00) and that I've spent 26 min total, I have some budget left. Let me do the 3 quick 8017FB50 variants and a couple of 8014CF04 ideas, then finish.

Actually, one more promising idea for 8014CF04: the target's `q` is in $17 and the loop's `p` in $16 (s0). The candidate has p in s0 ✓ (s0 is the loop pointer in both). The candidate's problem: q is in $20 and there's an extra base in $18.

What if the C declared the loop pointer `p` as `u16 *` (as now) and `q` as `u8 *`... that's the current.

What if the *order* of the declarations changed (q before p)? The decl order might affect the callee-saved order! In the target, the order is q($17), param_1($18), param_3($19), param_2($20) — q first. The candidate: param_1($17), q-1($18), param_3($19), q($20), param_2($21).

If the extra base weren't created, would q get $17? Probably (q has many refs: the loop pointer with ~10 uses).

So the extra base is the root cause. Let me try to kill it: what if the accesses are written with explicit casts that make them look different to the address optimizer? E.g. `*(u16 *)(q - 0x19)` vs `*((u16 *)q - 12)`? Hmm: (u16*)q - 12 = q - 24 bytes → the offset -24 from q, and the target has -25. Different.

What about `*(u16 *)(q - 0x19)` — that's what we have.

Hmm, what if the store is `q[-1] = 1;` → the address q-1 → and GCC's loop.c sees "q-1" as a derived IV of q (since q is the IV and -1 is a constant offset) and creates a new IV (q-1) to share the offset with the other accesses. loop.c's "ivopts" in gcc 2.7 (loop.c's `loop_iv_...`)? gcc 2.7's loop.c does have an "address base" optimization that creates a new IV when the offset is used by many references AND the new offset is smaller.

In the target (pinned q), the same optimization would apply... unless with a hard reg the "new IV" can't be created (it would need a new register, and gcc's cost model said no) — but in the unpinned case it created one (and used an extra reg!). That's odd, unless the cost model differs because with a hard reg, the derived IV would need to be allocated (a new reg → pressure) and gcc rejected it; unpinned, gcc created it because the "new IV" could reuse a dead pseudo reg.

Hmm, whatever the reason, can I prevent it? If the offset -1 were not shared by 5 refs but fewer... e.g. if the store `q[-1] = 1` were written as `*(u8 *)(q - 1) = 1` — same address.

What if the store were `q[0xFFFFFFFF]`? Same.

What if the -1 store used a *different* pointer expression, e.g. `((u8 *)q)[-1]`? Same.

I think the extra base is unavoidable.

Let me do the quick 8017FB50 tests and then finish. Actually, let me reconsider one more time whether there's a smarter lever for 8017FB50's 2 → 0.

The diff: target `move a0,s0` vs fb_d `sll s0,s0,0x10; sra a0,s0,0x10`.

What if tmp is s16 and the func_801823D4 call's first argument is `tmp` (s16 → promoted to int) — that's the sra. The sll is the truncation of the call result into the 16-bit tmp.

What if the truncation were FREE — i.e. if the call result were already 16-bit? The call returns s32.

Hmm, what if the ROT call's result is stored in a 16-bit variable but the *promotion* is free because the value's upper bits are known? No.

What if instead of `s16 tmp` I use a *bitfield* or a union? A union with a u16 member: `union { s32 s; u16 h; } tmp;` → tmp.s = RotTransPers(...); then `func_801823D4(tmp.s, -0x1A)` → the union makes the value live in one reg; but the 16-bit read of the union would alias... GCC would keep the value in a 32-bit reg (the union's s32 member) → no truncation → the allocation stays as the s32 case (12).

What about a union where the 16-bit member is read to create a short-lived pseudo? E.g.:
```
union { s32 s; u16 h; } u;
u.s = RotTransPers(...);
idx = func_801823D4(u.s, -0x1A);
```
The `u.h` is never read → no truncation → 12.

What if the code reads u.h somewhere (to create the short-lived 16-bit pseudo) but in a way that costs nothing? E.g. `if (u.h == 0xFFFF) idx = ...` — that's extra code.

OK. Done with 8017FB50: WALL best 2.

Let me do the 3 quick variants to confirm the floor (and to have the data), then write the log and finish. Actually, my sweep already covered the current candidates; the extra variants (fb_f/g/h) are cheap. Let me run them for completeness, and then write the log.

Actually, one more important idea for 8017FB50! What if the *pointers* are declared as `s32` (integers) instead of `s32 *`? Then the calls would be `RotTransPers((s32)&base, (s32)obj+8, p_out, flag_out)` where p_out/flag_out are s32 values. The n_refs stay 5 each. BUT: the *mode* changes from pointer to SI, which might change the "size" or how the copies are made (`move a2,s2` — the same). Probably no change. Cheap to test.

And another: what if the pointers are passed as the SAME variable for both args in the first call... no.

Let me just run the 4 variants (fb_f: s16+(u32), fb_g: u16, fb_i: pointers as s32 ints) and finish.
