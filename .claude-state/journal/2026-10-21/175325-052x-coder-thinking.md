---
ts: 2026-10-21T23:53:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_TMgHx29nFXVuEDsE8BEZ
---
Confirmed: pri = floor_log2(n_refs)*n_refs*size/live_length. Shorter live length → higher priority. n_refs dominates.

For 8017FB50: p_out/flag_out n_refs=5 → 2*5=10; tmp n_refs=2 → 1*2=2. live lengths: p_out/flag_out live from init to the 4th call; tmp from the 1st call to the end.

To make tmp win, I need 2/L_tmp > 10/L_p → L_p > 5*L_tmp. L_tmp spans from call 1 to func_801823D4 — that's most of the function. L_p spans from the init (just before call 1) to call 4 — also most of it. So no.

BUT: what if the pointers are initialized MUCH earlier — e.g. at the very top of the function, before the v[] setup (which is ~40 instructions)? Then L_p ≈ L_tmp + 40. If L_tmp ≈ 30, then L_p = 70 > 5*30? No, 70 < 150.

Hmm. Alternatively: make tmp's live length shorter. tmp's live range: from the 1st RotTransPers call to the func_801823D4 call. What if the func_801823D4 call came right after the 1st RotTransPers call? That changes the call order in the asm → the target's order is: 4 RotTransPers calls, then func_801823D4. Moving it would change the instruction order → the score would rise (not a MATCH).

Hmm, BUT: what if the C reordering still produces the same asm? No — the asm order follows the calls.

Alternatively, reduce the arg pointers' n_refs from 5 to 4 (if the "set" is not counted?). n_refs counts the set as a ref too. Hmm: 1 set + 4 uses = 5.

What if the pointers are set via a copy (e.g. `p_out = something_else`)? Then the copy's source...

What if the two pointers were passed as the same variable to different args? Not possible (different values).

Hmm, what if the 4 calls were changed so that only 2 of them use the pointers... no, semantics.

So 8017FB50 = WALL (global-alloc: the 5-ref arg pointers outrank the 2-ref call-result).

Hmm, wait. One more idea for 8017FB50: the target's `move s0,v0` puts the call result in $16. What if, instead of `tmp = RotTransPers(...)`, I write it so that the result is used directly: `idx = func_801823D4(RotTransPers(...), -0x1A);` — no, the other 3 calls come between.

Alternatively: what if the *first* RotTransPers call is moved to the END (after the other 3)? Then tmp's live range would be short (from the last call to func_801823D4) → tmp would outrank → tmp gets $16! But the call order in the asm changes → the target's order is call1(base), call2(v[0]), call3(v[1]), call4(v[2]).

Hmm, wait. Actually, let me look at the target asm more carefully: the 4 calls are:
1. RotTransPers((s32)&base, obj+8, p_out, flag_out)
2. RotTransPers((s32)&v[0], obj+0xC, p_out, flag_out)
3. RotTransPers((s32)&v[1], obj+0x10, p_out, flag_out)
4. RotTransPers((s32)&v[2], obj+0x14, p_out, flag_out)

The first call's result → tmp ($16) → used by func_801823D4.

If the first call were moved last, the asm order changes → not a match.

OK: 8017FB50 = WALL.

Now, let me reconsider the overall situation. I have 5 items:
- 8017E4E0: WALL 11 (const-qty priority)
- 8017D3A0: WALL 11 (same)
- 8017EEB0: MATCH 0 ✓
- 8017FB50: WALL 12 (global-alloc n_refs priority)
- 8014CF04: WALL 34 (loop.c address base + callee-saved order)

Before finalizing, let me give 8014CF04 a couple of shots with new ideas, since 34 is far from 0 and the mechanism (extra base) might be steerable:

Idea A: write the q[-1] store as `*(u8 *)(q - 1) = 1;` — same.
Idea B: change `q[-1] = 1;` to `q[0xFFFFFFFF] = 1;`? Silly.
Idea C: change the loop to a `for` loop: `for (; p < end; p += 0x86, q += 0x10C)`. The loop shape changes → the target's asm has a do-while structure (the loop test at the bottom: `sltu v0,s0,v0; bnez v0,...`). A for loop with the same condition would produce the same shape if the compiler rotates it. Hmm, the previous attempt may have tried that.
Idea D: Make the condition shorter so the extra base isn't worth it.

Honestly, the extra base (q-1) is created by loop.c's "ivopts"/"address base" pass. In gcc 2.7 loop.c, there's `loop_iv`/`strength_reduce`...

Let me test a couple of quick variants for 8014CF04 to see if any changes the shape (e.g. the extra base disappearing). Cheap to test:
1. `*(u8 *)(q - 1) = 1;`
2. for-loop shape
3. `q[-1] = 1;` with q declared as `unsigned char *` (same as u8)
4. Splitting the condition: compute `*(u16 *)(q - 0x19) & 0x400` into a temp variable.
5. Reordering the && terms.
6. Using `param_1 + 0x178` etc. — same.

Let me look at what the previous attempt's variants did (summarize) so I don't repeat. Let me run summarize.py on that dir and skim.
