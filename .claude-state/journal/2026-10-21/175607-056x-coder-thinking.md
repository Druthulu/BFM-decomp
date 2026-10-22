---
ts: 2026-10-21T23:56:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_LTzaz4nITs44nIRvChcT
---
The last jal is func_801823D4 (the relocation name differs) with a0 = s0 (tmp) in the delay slot and a1 = -26 in the next slot. So the target passes tmp (the first RotTransPers result) as a0 to func_801823D4.

My fb_d (s16 tmp) produces `sll s0,s0,0x10; sra a0,s0,0x10` — the sign-extension of the s16 tmp. So the target's tmp is passed WITHOUT sign extension → tmp is s32 in the target.

But fb_d with s16 got the callee-saved allocation right! (s0=tmp, s1=flag_out, s2=p_out). So the s16 type changed the priority (the n_refs / live length) in a way that made tmp win $16 — but it also introduced the sign extension.

Hmm! So: with s32 tmp, tmp loses $16 to the arg pointers; with s16 tmp, tmp wins $16 but the value gets sign-extended (2 extra insns).

What if tmp is u16? Then the extension would be `sll s0,s0,0x10; srl a0,s0,0x10` (zero-extend) — also 2 insns. Hmm.

What if tmp is s32 but I make the priority work differently? The key insight from fb_d: the sign-extension changed the *live range* of tmp (the s16 value is in a narrow register, so the copy is a separate pseudo?) — the allocation changed because of the extra pseudo (the sll/sra)?

Hmm, in fb_d the target's `move a0,s0` became `sll s0,s0,0x10; sra a0,s0,0x10`: the sll writes s0 (dead after) and sra reads s0 → a0. So the value lives in s0 (16-bit) and is extended into a0.

The callee-saved allocation: in fb_d, s0 = tmp (the s16 value) ✓ matches the target's s0 = tmp.

So what I need: tmp in $16 AND passed to func_801823D4 as a plain 32-bit move.

Idea: what if tmp is declared s32 but the *value* is stored via a 16-bit intermediate? E.g.:

```
s32 tmp;
...
tmp = RotTransPers(...);   // s32
```
The issue is the priority. In fb_d, changing tmp's type to s16 changed the allocation. What else could change the priority of tmp while keeping it s32?

The priority: pri = log2(n_refs)*n_refs*size/live_length. With s16, size=1 but the mode is SI vs SI... hmm, for MIPS s16 is stored in a register as HImode (a subreg). The n_refs might be counted differently (the subreg creates an extra pseudo).

Let me think: with s16 tmp, GCC's RTL: the call returns an SI value; the assignment to an HImode pseudo requires a truncation → `sll s0,s0,0x10` (or a `move` + truncation). The tmp pseudo is HImode → its n_refs and live length differ → priority higher → wins $16.

What if instead I use a `u16` tmp? Then the zero-extension: `sll s0,s0,0x10; srl a0,s0,0x10`. Also 2 insns but the value's bits differ (the target passes the full 32-bit value). If the call's return value's low 16 bits are what matters... the target passes the full s32. With u16, the upper bits would be zeroed → different value → different code (and the asm would have srl instead of move). The score would be ~2 as well but with a different instruction.

Hmm, what about keeping tmp as s32 but adding a *separate* s16 variable to shift the priority? That's hacky but might work: e.g. `s16 tmp16; ... tmp = RotTransPers(...); tmp16 = (s16)tmp;` — no, that adds instructions.

Alternative: what if the difference in fb_d is not the type but the fact that the s16 assignment creates an extra pseudo (the truncation) whose priority is high? Then in the s32 case, tmp's priority is lower than the arg pointers.

Let me think about the numbers again:
- arg pointers: n_refs=5 (1 set + 4 uses) → log2(5)=2 → 2*5=10; live_length = ? The live length of the allocno is the max of the regs' live lengths. Hmm, `allocno_live_length` is the "guess at live length" = reg_live_length (the number of insns the reg is live).
- tmp: n_refs=2 → 1*2=2; live_length similar magnitude.

So pri_arg = 10/L, pri_tmp = 2/L → args win by 5x. With s16 tmp, what changed? Maybe the s16 version has n_refs=3 (the truncation insn adds a ref) → log2(3)=1 → 3; still less than 10. Hmm, that wouldn't flip it.

Unless the live_length changed: with s16, the live length of tmp is shorter? Hmm.

Or maybe the difference is that in fb_d the *sign extension* creates an extra pseudo (a0's source) and the register assignment changed for other reasons (the "hard_reg_preferences" mechanism: a qty copied into a0 prefers...).

Honestly, empirically: s16 tmp → the callee-saved allocation matches the target exactly, but 2 extra instructions appear (the sign extension).

So now: can I get the same allocation with a 32-bit pass-through? What if tmp is s16 but the call to func_801823D4 is made with an explicitly cast value: `func_801823D4((s32)tmp, -0x1A)` — that's exactly the sign extension → the same 2 insns. Hmm, but with s16 tmp the compiler already sign-extends.

What if tmp is u16 and the call is `func_801823D4((s32)tmp, -0x1A)` → zero-extension: `sll s0,s0,0x10; srl a0,s0,0x10` → 2 insns, and the value differs (upper bits zeroed) — the target has the full value. The value of the RotTransPers return is presumably small (a rotation result), so the upper bits might be 0 anyway. But the asm differs from the target (`sll/srl` vs `move`) → not a MATCH.

Hmm. So I need tmp to be s32 AND allocated to $16.

What made fb_d's allocation match? Let me test a variant: tmp as s32 but with an extra s16 variable to change the priority... Actually, let me test several type/mode variants quickly:
(a) tmp as s32 (baseline) → 12.
(b) tmp as s16 → 2.
(c) tmp as u16 → ?
(d) tmp as s32, but the func_801823D4 call takes `(s32)(s16)tmp` → hmm, that adds the sign extension (2 insns) but tmp stays s32 → the allocation might match AND we'd have 2 extra insns (score ~2).
(e) tmp as short, with the call `func_801823D4(tmp, -0x1A)` → same as (b).

Hmm, what about (f): keep tmp s32 but make the arg pointers have fewer refs...

Wait. Let me reconsider. Maybe the allocation difference in fb_d is not about tmp's type but about the *number of live registers*: with s16 tmp, the sign-extension pseudos change the pressure.

Let me test (c) u16 and a couple of others to see the landscape. And also try: `s32 tmp` but with the first RotTransPers result assigned to a *separate* s32 variable that is then copied...

Actually, here's a cleaner idea: what if the priority of tmp is boosted by making it live ACROSS more refs? E.g. if tmp were used twice (but the target has 1 use)...

Alternatively, what if I *reduce* the arg pointers' n_refs from 5 to 4 by not counting the set? Can't.

Hmm, what about this: the arg pointers are `s32 *`. What if they're declared as `u8 *` or `void *`? The RotTransPers signature takes s32* — passing a u8* would need a cast (no extra insn). The mode of the pseudo (pointer) is the same. No change.

What if the pointers are stored in a struct? No.

Let me look at the problem from the "what does the target need" angle:
- target: s0 = tmp (s32, 32-bit), s1 = flag_out, s2 = p_out.
- The passes: `move a0,s0` (a plain 32-bit move of tmp to a0).

In fb_d the allocation matched but the value needed extension. What if I make tmp a 32-bit value but with a *narrower* live range... no, the priority is the issue.

Hmm, hold on. Maybe the allocation in fb_d matched for a different reason: the s16 tmp means the call result is truncated to 16 bits, so the pseudo for the call result (32-bit) is a different allocno from tmp (16-bit). The 32-bit call-result pseudo has n_refs=1 and a very short live range (just the truncation) → high priority → it would win $16?! But the target has the call result in $16 (s0 = tmp = the truncated value). Hmm, in fb_d: `sll s0,s0,0x10` — s0 is the destination of the sll, i.e. the 16-bit tmp is in s0. And the call result came in v0.

OK whatever the mechanism, fb_d gets the allocation right. I need to find a variant with the allocation right AND a plain 32-bit move.

Idea: what if the truncation is not needed but the priority effect is achieved by another means? Let me test: tmp s32, but the call to func_801823D4 passes tmp through a u16 temp:
```
u16 t16 = (u16)tmp;
idx = func_801823D4(t16, -0x1A);
```
→ zero-extend (2 insns) → the value differs (upper 16 bits lost) → but does the asm match? The target has `move a0,s0` (1 insn). No.

Idea: `idx = func_801823D4((s32)(s16)tmp, -0x1A);` with tmp s32 → sign extension: `sll`+`sra` = 2 insns vs the target's 1 `move`. No.

Hmm, so the target's `move a0,s0` means the value passes unchanged in 32 bits, and tmp is in $16.

What if the *first* RotTransPers call's result were assigned to a variable of type s32 that is *never* truncated, but the priority boost comes from elsewhere? Let me test whether the priority flip in fb_d is due to the truncation pseudo or due to the HImode.

Experiment: keep tmp as s32 but add a separate unused-ish s16 variable? That would add instructions.

Experiment 2: tmp as s32, but the func_801823D4 call's first arg is a *different* variable: e.g.
```
s32 tmp = RotTransPers(...);   // s32
...
idx = func_801823D4(tmp, -0x1A);
```
same.

Let me look at it from a different angle: what if the arg pointers' n_refs could be reduced by passing the SAME pointer variable for both args in a way GCC merges? Hmm, what if flag_out were computed as `p_out + 1` INSIDE the calls: `RotTransPers(a0, a1, p_out, p_out + 1)`. Then:
- p_out: 1 set + 4 uses = 5 refs.
- p_out+1: computed 4 times → CSE merges into 1 pseudo with 4 uses + 1 set = 5 refs? Or the address `p_out+1` is computed in a pseudo (n_refs=5). Hmm, same.

But the asm would differ: the target computes `addiu s1,sp,52` (a separate address) — if GCC computed p_out+1 from p_out, the asm would be `addiu sX,sY,4` → different.

OK, let me try yet another angle: maybe the priority of the arg pointers is lower than I think and the actual mechanism for fb_d's match is different. Let me just try a bunch of type/structure variants and see which ones give 12 → 2 → 0. Let me enumerate:

1. tmp s16, call `func_801823D4(tmp, -0x1A)` → 2 (sll+sra).
2. tmp s16, call `func_801823D4((s32)tmp, -0x1A)` → same 2.
3. tmp u16 → ?
4. tmp s32 with the *first* call's result in a separate variable `t0` (s32) and tmp = t0 → probably 12.
5. tmp s32, but the four RotTransPers calls' pointer args reordered? Not allowed.
6. tmp as `long`? Same as s32.
7. tmp s32 but the RotTransPers calls take the pointers as *variables of type int* (s32) instead of s32*: `int p_out_i = (s32)&v[3];` → then the call args are ints. The asm: `move a2,s2` — the same. But the priority might change! The p_out variable's n_refs: 1 set + 4 uses = 5. Same.

Hmm.

8. What about making the arg pointers' live range longer by initializing them before the v[] setup (fb_c gave 28 — worse).

9. What if the v[] setup is reordered so that the pointers are initialized later (shorter range → higher priority for the arg pointers — wrong direction).

10. What if the *first* RotTransPers call is moved to the end? Then tmp's live range is short → tmp wins $16 → but the call order changes → the asm order changes → not a match. BUT hmm, what if the asm order stays the same? The target's call order: base, v[0], v[1], v[2]. If I reorder the source to v[0], v[1], v[2], base — the asm would differ (the args differ) → score > 0.

11. What if tmp is used in the func_801823D4 call but the *value* is a 32-bit reg that GCC allocates to s0 because of a copy preference? In the target, `move a0,s0` — the copy from s0 to a0. In fb_d, `sll s0,s0,0x10; sra a0,s0,0x10` — the copy from s0 (16-bit) to a0.

Interesting: in both, s0 holds tmp. So the allocation matches; only the extension differs.

12. What if I declare tmp as `s32` but assign the call result to a 16-bit variable first and then to tmp? e.g.
```
s16 t16 = RotTransPers(...);   // truncation
s32 tmp = t16;                  // sign extension
```
→ more insns.

13. What if the *type* of the flag_out/p_out variables changes to affect their priority? E.g. make them `int` (s32) instead of `s32 *`: then the call `RotTransPers((s32)&base, ..., p_out, flag_out)` would need casts (no insns). The n_refs stay 5 each.

Hmm, but their live LENGTH might change? No.

14. What if I add a *use* of tmp that is free? E.g. `idx = func_801823D4(tmp, -0x1A);` — what if tmp is also used in a comparison folded away? Like `tmp = tmp + 0;`? GCC removes it.

Hmm, what about `idx = func_801823D4(tmp + 0, -0x1A);`? GCC folds tmp+0 → tmp.

15. What if the *second* argument of the 4 calls is different...

Let me test the "s16 tmp + explicit (s32)" variants and a few type variants to see if any gives 0. Actually, what if tmp is s16 and the func_801823D4 call is `func_801823D4((u32)tmp, -0x1A)`? → zero-extend (sll+srl) → 2 insns. No.

Hmm, what if tmp is s16 and the ROT call's result is stored in an s16 but the value passed is used as `(s16)` → the target's value semantics: `move a0,s0` passes the 32-bit value. If the true 32-bit value has garbage in the upper 16 bits, the s16 version differs semantically but the ASM is what matters: 2 extra insns → score 2.

So the question: can I get the 32-bit tmp into $16 without the s16 trick?

IDEA: What if the priority flip is caused not by the type but by the fact that the s16 assignment creates a *separate* pseudo for the call result (v0 → s16 pseudo) whose live range is tiny → it wins $16... no wait, in fb_d the s16 tmp IS in s0.

Hmm, let me think about fb_d's RTL:
- call → v0 (call result, 32-bit)
- `tmp16 = (s16)v0` → the pseudo for tmp16 is HImode; the RTL: `sll tmp16, v0, 16`? Actually on MIPS, storing an SI into an HImode pseudo = a truncation: `(set (pseudo16) (sign_extend:SI (reg:HI v0)))` → expanded to `sll pseudo16, v0, 16` (and the HI reg is the low half of pseudo16). Hmm, in gcc 2.7 with a HI mode pseudo, the sll writes the full reg and the uses read the low half.

So the RTL: `sll p16, v0, 16` (p16 is a 16-bit pseudo) then `move a0, p16`?? The asm shows `sll s0,s0,0x10; sra a0,s0,0x10` — so the sll wrote s0 and then sra read s0 → a0. That's because the pseudo p16 was allocated s0 and the sign-extension for the call arg was done in a0.

So: p16 (the truncated call result) got $16 (s0) and the other two (flag_out, p_out) got $17/$18 — matching the target's assignment of $16 to the first call's result!

In the target (s32 tmp), the call-result pseudo has n_refs=2 (set + use) → lower priority than the arg pointers (5 refs) → the args win $16/$17 and tmp gets $18.

In fb_d, p16 has n_refs=2 as well... but it won $16?! Hmm. Unless the HImode pseudo's size is different (allocno_size). Hmm, pri = log2(n_refs)*n_refs*size/live_length. For a 16-bit pseudo on MIPS, size might be 1 (HImode fits in a 32-bit reg).

Wait, maybe the difference is the live_length: the s16 pseudo is live only until the sign extension (very short) → high priority! While the s32 tmp is live from the call to the func_801823D4 call (long). Yes! That's it: the truncation splits the value into two short-lived pieces: p16 (born at the call, dies at the sll) — hmm, no: p16 is born at the sll and dies at the sra (short!) → very high priority → wins $16 ✓.

So the mechanism: to give the call result $16, its live range must be short. In the target, the call result IS in $16 and lives until func_801823D4 (long!). Hmm, that contradicts.

Wait, in the target: `move s0,v0` (at ddc) — the call result is moved to s0 immediately after the 1st call, and s0 is used at e08 (`move a0,s0`) — a long live range (spanning the 3 other calls). And yet s0 = $16 was given to it, while the arg pointers got $17/$18.

So in the target, the arg pointers (5 refs) did NOT outrank the call result (2 refs). Because in the target they're pinned! Right — the pins forced flag_out→$17, p_out→$18, leaving $16 for the call result.

So without pins, the arg pointers (5 refs, long range) beat the call result (2 refs, long range) → $16/$17 for the args, $18 for the result.

To flip this without pins, I need the call result to outrank the arg pointers. pri_result = 2/L_r; pri_arg = 10/L_a. Need L_a > 5*L_r.

L_r = the live length of tmp = from the 1st call to the func_801823D4 call ≈ the whole call sequence (say 20 insns). L_a = the live length of p_out = from its init to the 4th call ≈ also ~20 insns. To get L_a > 5*L_r, I'd need the pointers' init to be ~100 insns before the calls. The function has a big v[] setup before the calls! If the pointers were initialized at the TOP of the function (before the v[] setup), L_a would grow by the setup's length (~40 insns?) → L_a ≈ 60, L_r ≈ 20 → 60 < 100. Not quite 5x. Hmm, close-ish. fb_c (pointers at the top) gave 28 (worse — probably an extra instruction).

Hmm, what if the pointers are initialized even earlier AND the call result's live range is shortened? The call result's live range is fixed by the call order.

Alternatively: reduce the arg pointers' n_refs from 5 to 3 (log2(3)=1 → 3*1=3 < 2? no, 3 > 2). To 2: log2(2)=1 → 2*1=2 = same as tmp's 2 → tie → then the tie-break is by allocno number (order). Hmm! If the arg pointers had n_refs=2 (1 set + 1 use) they'd tie with tmp, and the tie-break (allocno order) would decide. But the pointers are used 4 times...

Unless... the 4 calls are restructured so that the pointers are used fewer times! What if the 4 calls are in a loop? The target has 4 explicit calls (the loop would be a different asm).

Hmm, what about the `hard_reg_preferences` mechanism: an allocno that is copied to/from a hard reg gets a preference for that reg. In the target, `move a2,s2` — the copy from s2 (p_out's reg) to a2 creates a preference for a2?? But a2 is a call-clobbered reg, so it can't be the allocno's reg. Hmm, but the copy preference mechanism in global-alloc: "hard_reg_preferences" — the allocno p_out is copied TO a2, so a2 is in p_out's preference set. That's for the *hard* reg, not the callee-saved.

Interesting: the target's `move a3,s1` (flag_out→a3). So flag_out has a preference for a3 and p_out for a2 — but those are caller-saved and the values live across calls, so the callee-saved regs are chosen.

OK. Let me try the "make the pointers' live range longer" idea more aggressively: initialize the pointers at the very top of the function AND make the v[] setup bigger? No, can't change the code.

Alternatively: think about pri for the *arg pointer* allocno: n_refs=5 → log2(5)=2 → 10/L_a. If the arg pointers were s16 or had fewer refs...

Hmm, what if the pointers are stored in a *struct/array* so that one base register is used with offsets? E.g. `s32 outs[2]; outs[0] = (s32)&v[3]; outs[1] = (s32)&v[3]+1;` then the calls pass outs[0], outs[1] → GCC would need the values in regs (loads from the stack) → different asm.

What if the pointers are passed as `p_out` and `p_out + 1`? Then p_out has 5 refs (4 uses + 1 set) and the derived one has 5 refs too (CSE merges the 4 `p_out+1` computations into one pseudo with 4 uses + 1 set = 5). Hmm, but the derived pseudo's live range is shorter (born later) → higher priority → it wins $16! And the asm: the target has `addiu s1,sp,52` — if GCC computes p_out+1 from p_out it'd be `addiu sX,sY,4` → different asm → not a match. Unless CSE/loop produces sp+52 anyway... Actually, GCC's addressing: `p_out + 1` where p_out = sp+48 → the address sp+52 could be computed directly from sp if GCC rewrites it (it's a constant address: &v[3]+1 = sp+52 — a compile-time constant!). Since v is a local array, &v[3] is a frame address → constant → GCC computes sp+48 and sp+52 directly from sp. So writing `p_out + 1` in the call would still give `addiu sX,sp,52`!

Wait, but then the 4 uses of `p_out+1` would be CSE'd into one pseudo with 4 uses. Hmm, same n_refs=5.

Hmm, but hold on: what if I write the calls with the *literal* addresses: `RotTransPers((s32)&base, ..., (s32 *)&v[3], (s32 *)&v[3] + 1)`? Then each call has the same constant address → CSE merges them into 2 pseudos with 4 uses each (no "set" insn — they're constants! CSE would replace the address with a constant? For a frame address, GCC materializes it in a reg).

Hmm, if the address is a constant (sp+48), CSE might keep it as a constant expression and each call would do `addiu a2,sp,48` → 4 addiu's instead of 2 + 4 moves. The target has 2 addiu's + 4 moves. So no.

OK, let me try a different approach to the priority problem: what if the arg pointers' live range is lengthened by initializing them at the top AND the call result's live range is shortened by...

Hmm, actually, wait! What about `allocno_live_length` — "Guess at live length of each allocno. This is actually the max of the live lengths of the regs." reg_live_length is the number of insns the reg is live. For the arg pointers, they're live from the init to the 4th call. For the call result, from the 1st call to func_801823D4.

Since the 1st call comes right after the init, the arg pointers' live length ≈ the call result's live length + a few.

To get a 5x difference, the pointers' init must be ~100 insns earlier. The v[] setup: 3 iterations of a 24-byte copy + adjustments ≈ maybe 30-40 insns. Plus the obj setup. Hmm, fb_c put the pointers at the top of the function (before obj = func_80010A08) — that gave 28 (worse!). Why worse? Because initializing the pointers before the `v[]` array is set up changes the frame layout/order → maybe the addresses changed (v[] is a local array; &v[3] is sp+48 — if the pointers are initialized earlier, GCC might allocate the array differently? no...). Or because the extra insns changed. Let me look at the fb_c diff to understand. Actually fb_c = 28 (COUNT; mine 120 ins) → 2 extra instructions. Because initializing the pointers at the top adds 2 addiu's in a different place... no, same count. Hmm, 120 vs 118: 2 extra.

OK, I'm going too deep. Let me take stock:

Time: ~19:05. I've used 90 minutes. The remaining work: 5 result rows, 5 notes.md, the log file, the moves.md appends, and the final report. That's maybe 20-30 min. Let me allocate ~30 more minutes of cracking attempts (focused on the most promising: 8017FB50 at score 2 — the allocation matches with s16 tmp; and 8014CF04 at 34) and then write up.

For 8017FB50, let me try these variants:
(a) tmp s32, but p_out/flag_out declared as `int` (s32 values instead of pointers).
(b) tmp s32, p_out/flag_out as `u32`.
(c) tmp s32, the pointers' init moved to just after the v[] setup (shorter live range → higher priority for the args — wrong direction).
(d) tmp s16 + the call `func_801823D4((s32)tmp, -0x1A)`: probably the same 2.
(e) tmp as s16 but assigned from a s32 variable: `s32 t = RotTransPers(...); s16 tmp = (s16)t;` → extra insns.
(f) tmp s32, but the 4 calls' pointer args are the SAME variable for the 3rd arg and a distinct one for the 4th — that's the current.
(g) What about the *order* of the two pointer declarations AND their types: `s32 *p_out` first vs `flag_out` first — tested (fb_a/fb_b both 12).

Hmm (a)/(b): if the pointers are passed as s32 values (ints), the n_refs are the same but the *mode* is SI vs pointer. Might change the priority? Unlikely.

Let me think about (h): make the call result's live range SHORTER by using it in the middle: e.g. compute `idx = func_801823D4(tmp, -0x1A)` right after the 1st call, and move the other 3 calls AFTER it? That changes the call order in the asm → no.

(i) What if the func_801823D4 call comes first (before the 4 RotTransPers calls)? The asm order changes → no.

So the only way is the priority flip via the live length of the arg pointers, or via a shorter live range for the call result.

Hmm, wait! What about making the call result's live range shorter by having the compiler *copy* it early? Like:
```
tmp = RotTransPers(...);
...
```
No.

Actually — hmm! What about the "size" factor? pri = log2(n_refs)*n_refs*size/L. If the arg pointers' allocno had size 2 (a doubleword), its priority would double! Can I make a pointer allocno have size 2? Not on MIPS 32-bit.

Alternatively, what if the arg pointers are in the same allocno as something else...

Let me try the opposite: what if tmp is a *pointer-sized* value? No.

OK, let me try the remaining cheap experiments for 8017FB50:
- tmp as s16 with `(s32)` cast (check the score).
- p_out/flag_out as s32 ints.
- p_out/flag_out as u32.
- tmp s32 with the pointers initialized right before the calls (as now) but declared in the other order (tested).
- Add `volatile`? No (barrier).
- tmp as `short` (same as s16).
- tmp as `unsigned short` (u16) → check the score; if it gives 2 with srl, that's a variant of the same.

And for 8014CF04, let me try:
- q as u16* (tried), u8* (m01).
- The loop written as a for loop.
- q[-1] = 1 spelled differently (tried).
- The condition's q-based tests reordered.
- Using `*(u8 *)(q - 1) = 1;` (tried).
- Making the `q[0]` load use a different form: `func_8014C918(param_1, q[0])` → `func_8014C918(param_1, *(u8*)q)` (same).
- Introducing a second pointer for the q-0x19 group: `u8 *r = q - 0x19;` — but that changes the asm.

Hmm. Honestly, for 8014CF04, the extra base (q-1) is a loop.c decision. Let me check: is the extra base maybe caused by the *order* of the q-relative accesses? The candidate uses s2 = q-1 as the base for 5 accesses. If I could make GCC use q as the base, the asm would match. The choice in loop.c's "ivopts"/"address base" is: it picks the base that minimizes the number of registers.

Wait, actually, maybe the q-1 base isn't from loop.c but from the RTL "address selection" in reload (the reload pass chooses the base register for each memory reference). In reload, for each memory operand, it picks a base register: for `q - 0x19` it can use q with offset -0x19, or q-1 with -0x18. Reload prefers to use a register that's already available. The extra `addiu s2,s0,116` is a real instruction, so GCC decided to compute q-1 once (a "reload" of the address into a pseudo base).

In reload, there's the concept of "address base" selection with a cost model: using an existing reg with a small offset is cheap. The target's choice (q with offsets -0x19 etc.) is the natural one. The candidate chose q-1 (an extra reg computed once). Why? Because q-1 was needed for the `q[-1] = 1` store and for the 4 loads — reload found that using one base (q-1) for 5 references was cheaper than using q for 5 references with different offsets? Both are 1 register... but with q as the base, the offsets are -0x19, -0x1D, -0x6B, -0x55, -1, 0 — all fit in 16 bits. With q-1 as the base: -0x18, -0x1C, -0x6A, -0x54, 0, +1 — all fit too. Hmm, so why the extra register?

Because reload's "address base" for a *loop* considers the induction variable: it might have created a new IV (q-1) in loop.c as a strength-reduction of the address `q-1` (which is loop-invariant relative to q, i.e. q-1 = q + (-1) → the "derived IV" is q-1). GCC's loop.c creates a derived IV when the address is used multiple times and the offset doesn't fit or when it reduces the offset size. Since -0x6B etc. fit, hmm.

Actually, in gcc 2.7 loop.c, there's a step: "If the address is too large or there are many uses, create a new induction variable". The new IV here is q-1, and then the offsets become smaller. The cost model decides based on the number of insns saved vs. the extra register.

Whatever the mechanism, it happened in the unpinned version but not in the pinned one. With the pin, q is a hard reg and loop.c can't create a derived IV from a hard reg? Plausible: creating a derived IV requires a new register, and GCC's cost model with a hard-reg IV... hmm.

I've got to stop. Let me do a final quick batch for 8017FB50 (the most promising, score 2) and then write up.

Variants for 8017FB50 (fb_*):
1. tmp s16 + `(s32)` cast in the call.
2. tmp u16.
3. p_out/flag_out as s32 (int) values.
4. p_out/flag_out as u32.
5. tmp s32 + the pointers declared as `void *`.
6. tmp s32 + p_out/flag_out declared at the top of the function (fb_c was 28) — skip.
7. tmp s32 + the func_801823D4 call's first arg cast to (s32) — no change.

Hmm, what about this: the target's arg-pointer regs are $17 (s1) for flag_out and $18 (s2) for p_out — i.e. flag_out FIRST, then p_out. In fb_d, the allocation matched exactly (s0=tmp, s1=flag_out, s2=p_out) — so with the s16 trick, the tie-break gave flag_out → $17. Interesting: so in fb_d, the arg pointers' tie (both 5 refs) was broken by the order: flag_out is declared first in the source (fb_b = flag_out first). Note fb_a (p_out first) also gave 12, and fb_d used the fb_a ordering (p_out first)... wait, fb_d was derived from `unp` = fb_a (p_out first, flag_out second). And fb_d gave 2 with the allocation matching the target: s0=tmp, s1=flag_out, s2=p_out. Hmm, so with p_out declared first, the allocation gave flag_out $17? Let me verify by checking the fb_d diff — the diff showed only the sll/sra difference, and the context lines showed `move a2,s2`/`move a3,s1`? Let me check the fb_d asm to see which reg holds what.

Actually the x.py diff showed the ONLY difference was the sll/sra vs move. So fb_d's allocation = target's: p_out in s2 ($18), flag_out in s1 ($17) ✓.

So in fb_d (p_out declared first, tmp s16), the arg pointers got $17/$18 with flag_out in $17. Good.

So the missing piece is just the value pass-through. What if tmp is s16 but the *stored* value is sign-extended... the target passes the raw 32-bit.

Hmm, what if tmp is s16 and the call is `func_801823D4((u32)tmp, -0x1A)` → zero-extend → the asm would be sll+srl → 2 insns → score ~2.

What if tmp is s16 and the call is `func_801823D4(tmp, -0x1A)` (implicit promotion) → sign-extend (sll+sra) → 2 insns.

So the s16 route always costs 2 insns. Unless the truncation is FREE: e.g. if the value's low 16 bits are what matter and the high bits are known zero... The target's `move a0,s0` passes the full 32-bit value.

Therefore: the allocation needs a 32-bit tmp in $16. The priority formula says n_refs dominates. tmp has 2 refs; the arg pointers have 5.

Hmm, hold on! What if I make the arg pointers have n_refs=4 instead of 5 by removing the "set" ref? Not possible.

What if the arg pointers' live length could be 5x tmp's? tmp's live length = from the 1st RotTransPers call to the func_801823D4 call. The 3 other RotTransPers calls are in between. If those 3 calls were... hmm.

WAIT. What if the 3 other calls are moved BEFORE the first call?! I.e. the source order: v[0], v[1], v[2], base. Then the call result (tmp) is born at the LAST RotTransPers call → its live range = just the func_801823D4 call → very short → high priority → tmp wins $16 ✓✓. But the asm's call order would change: the target's order is base, v[0], v[1], v[2]. So the asm would differ → score > 0.

Unless the 4 calls' arguments make the reorder invisible? No, the args differ (sp+32 vs &base).

Hmm, but hold on: how does the score work? It's a diff of the instruction streams. A reordered call sequence = a big diff. No good.

OK: what if instead I make the arg pointers' live ranges longer by moving their initialization earlier, AND the call result's live range shorter? The call result's live range is fixed by the call order (base is the 1st call).

L_a (arg pointers' live length) must be > 5 * L_r. L_r ≈ (distance from the 1st call to the func_801823D4 call). The 4 calls are ~40 insns total (each call + moves ≈ 6 insns) → L_r ≈ 30-40 insns. L_a would need to be > 175 insns. The function is 118 insns. Impossible.

So: 8017FB50 = WALL, with the mechanism "global-alloc priority: the 5-ref arg pointers outrank the 2-ref call result, so $16 goes to an arg pointer; a 16-bit tmp flips the priority (s16) but adds a sign-extension pair (2 insns)".

That's a nice, precise wall tag: e.g. "global-alloc-prio-nrefs" — the tag must be `<pass>-<what>`: "global-alloc-nrefs-prio".

Hmm, but wait. fb_d is score 2 — is that a PARTIAL? No: PARTIAL means the win.c scores 0 while keeping some levers. fb_d scores 2, not 0. So WALL with best=2.

Hmm, but hold on! What if I combine: s16 tmp (for the priority) AND make the sign-extension free? What if the value passed to func_801823D4 is the s16 value but the target's value is the same 32-bit value? The asm differs (sll+sra vs move) → the score would be 2 (the tool counts the 2 extra insns). So no.

Let me try ONE more idea for 8017FB50: what if the arg pointers' n_refs drop because the 4 calls are made with a *shared* variable that GCC copies? E.g.:

```
s32 *outs[2];  // no
```

Or what if p_out and flag_out are passed via a struct? The callee's signature is fixed: RotTransPers(s32, s32, s32*, s32*).

Hmm, what if I pass the SAME variable for both p_out and flag_out in some calls? That changes semantics.

OK. Let me also quickly try: does the *order* of the two pointer declarations matter for which gets $17 vs $18? In fb_d (p_out declared first) the result matched the target (flag_out→$17, p_out→$18). Good, but it doesn't matter since we're at 2.

Final answer for 8017FB50: WALL best 2 (lever-free), tag "global-alloc-nrefs-prio".

Hmm, hold on. Wait. Let me reconsider: the best lever-free score is 2 (fb_d). But what if I combine fb_d's s16 trick with something that removes the extension? The extension exists because the value is stored in a 16-bit pseudo. What if the s16 variable is only used for the *allocation trick* and the actual value passed comes from a 32-bit variable? E.g.:

```
s16 tmp16;      // trick
s32 tmp;
...
tmp = RotTransPers(...);
tmp16 = (s16)tmp;    // truncation -> extra insns (sll) : changes the asm
```
No good.

What if the s16 variable is assigned but never used? Then GCC removes it → no effect.

So: WALL, best 2.

Now let me do the same kind of quick check for 8014CF04 — is there any variant below 34? The previous attempt's best was 34; x08 was 22 (different insn count). Let me look at x08 (22) — maybe it's closer in a different way. Actually 22 < 34 but with 87 ins. Both are walls.

Let me try a couple of quick new variants for 8014CF04:
(a) Make the q-relative accesses use a base that's not q-1: e.g. write the 4 negative accesses as offsets from q-0x19 explicitly? Same.
(b) Try making `q` a `char *` (signed) — tried (m04).
(c) Try the loop with `q` incremented by a different expression.
(d) Try the "single base" by using a temp pointer for the q[-1] store: `*(u8 *)(q - 1) = 1;` — tried (s02 → 34).
(e) Try moving the `q[-1] = 1;` store to a different position in the block? It's a single store in the if-body.
(f) Try declaring q as `u8 *q;` and using `q - 1` in a way that the base is q...

Honestly, let me try the "for loop" and "while loop" variants (I did cf_b: while → 35). Let me try a for-loop with the same shape:
```
for (; p < end; ) { ... p += 0x86; q += 0x10C; }
```
Same as while.

Let me try instead: keep the do-while but compute the loop bound once into a variable (the target recomputes it each iteration: `lui v0,0x0; sltu v0,s0,v0` — the bound is a constant address).

I think 8014CF04 = WALL, best 34 (or 22 with x08). The "best" for the row = the lowest score of a lever-free body = 22 (x08.c). Hmm, but x08 has 87 ins (COUNT) — the score 22 vs 34: the lower is better. Let me check x08's diff to describe the mechanism. Actually, the score metric is what the tool says; "best = lowest score of a lever-free body" → 22.

Hmm, but a lower score with a different instruction count might be a red herring. The tool's score is the metric used for MATCH (0). I'll report best=22 and mention the mechanism from the primary diff (the 34-diff: extra q-1 base + callee-saved order).

Hmm, let me reconsider: is x08 lever-free? Let me check its diff vs orig.

Let me be careful with the "best" value: I should report the lowest score among lever-free bodies. Let me check x08 quickly.

Time: 19:10. Let me wrap up the cracking phase: run a final scoring sweep over all candidate files in all 5 item dirs to get the true best per item (cheap: ~150 files × 1s = 2.5 min). That also validates that all candidates are lever-free (I should check for `register`/`__asm__` in them — the previous attempt's files might contain pins! e.g. m06.c for 8014CF04 had a duplicate `u8 *q;` (compile error) — fine).

Important: for the WALL rows, the "best" must come from a LEVER-FREE body. Some candidate files might still contain the pin (e.g. a file that only changed something else). Let me filter: any candidate containing "register" or "__asm__" is not lever-free.

Let me write a script that scans all .c files in each item dir, checks for levers, scores the lever-free ones, and reports the best.
