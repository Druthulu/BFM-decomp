---
ts: 2026-10-21T23:53:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hwOHcQb53GYMoHRgA4wo
---
Same 11 plateau for 8017D3A0. Both $3-constant items are at the same wall.

Now let me spend a bit on 8014CF04 and 8017FB50 with new ideas, since those are the two remaining with real hope (different mechanisms).

For 8014CF04, the key differences in the unpinned version:
1. An extra base register q-1 (extra addiu + extra loop increment + extra sw).
2. The callee-saved register order: q should be $17 (first), but the candidate has param_1 in $17, q-1 in $18, param_3 in $19, q in $20, param_2 in $21.

The target's order (q, param_1, param_3, param_2) suggests q has the highest priority (the loop induction variable gets priority in global-alloc: loop-depth weighting).

In the candidate, the extra q-1 base stole $18 and pushed q to $20.

So the root cause is the extra base. If I can prevent GCC from creating the q-1 base, the allocation might match the target exactly (q in $17, param_1 $18, param_3 $19, param_2 $20).

How to prevent the q-1 base? The q-1 base is created because q-1 is used 5 times (4 loads + 1 store) and GCC's loop.c "address base" optimization (in gcc 2.7, `loop.c`'s `loop_optimize` has a step that computes "induction variable" bases) hoists it.

Hmm, actually in gcc 2.7, the relevant pass is loop.c's "iv elimination" / "address base" — hmm.

Alternatively the q-1 base might come from a different source: the RTL peephole/loop optimization that recognizes the common base.

How could I write the C so that q-1 is not a common base? If the offsets were spelled differently, e.g. `q[-1]` vs `*(u8 *)(q - 1)` — the same.

What if the -0x19/-0x1D/-0x6B/-0x55 accesses used a *different* anchor that GCC can't fold into q-1? For example, use `param_1`-relative? No.

What if the q-1 store is written as `*(u8 *)(q - 1) = 1;`? Same.

Hmm, what if I introduce a separate pointer variable for the group, e.g. `u8 *r = q - 0x19;` and then use r[0], *(s32*)(r-4), *(s16*)(r-0x52), *(s32*)(r-0x3C)? That would compute r = q-0x19 (one addiu) — the same shape as the candidate's s2 = q-1... but with different offsets. The candidate's base is q-1 (because it includes the q[-1] store). If I split: use q for the q[-1] store and q[0], and a separate base r = q-0x19 for the 4 accesses, then the offsets from r would be 0, -4, -0x52, -0x3C — different numbers than the target's (-0x19, -0x1D, -0x6B, -0x55 from q). The target's asm has lhu v0,-25(s1) etc. → base = q. So the target has ONE base (q) with all offsets from it.

So the target's compiler did NOT create a second base. Why? Because with q pinned to $17 (a hard reg), the loop optimization couldn't create the derived base (maybe because it would need an extra register and the pressure was higher, or because the pin changed the "cost" analysis).

So: how to make GCC keep a single base q? Reduce the number of uses of q-1? The uses of q-1: the 4 accesses + the store. Can't reduce without changing the code.

Alternatively: increase the register pressure so that creating the extra base is too expensive? Hmm, that could change the allocation.

Alternatively: change the loop shape so that the q-1 base isn't loop-invariant... it is invariant.

Hmm, what if the loop is written as a `for` loop with the increment inside, vs the do-while? The orig uses do-while. The target presumably came from the same source with the pin.

Honestly, 8014CF04 looks like a WALL too (the pin shapes loop.c's address-base decision + the callee-saved priority).

But wait — what about the "keepalive" style trick: the extra base exists because GCC wanted it. What if the C spells the offsets so that q-1 has only 1 use? E.g., write the store as `q[-1] = 1;` → uses q-1 once; the 4 loads use q-0x19 etc. Then the common base of the 4 loads would be q-0x19 (or q-0x1D) → the candidate would compute a base like q-0x1D (s0+0x58) and offsets +4, 0, -0x4E, -0x38 → different from the target's -25/-29/-107/-85.

So the target's single-base form is what GCC produced with the pin. The unpinned form always creates a second base.

Unless the second base is created only because of a register shortage/order. Hmm.

Let me try a couple of quick variants for 8014CF04:
(a) `*(u8 *)(q - 1) = 1;` instead of `q[-1] = 1;`
(b) use `q - 1` spelled as `(u8 *)(q - 1)`
(c) reorder the condition terms
(d) use a for loop with explicit increments
(e) declare q as `u8 *` vs `char *` (same)
(f) make the accesses use a temp pointer for one group

Let me look at what the previous attempt tried (summarize.py on that dir) to avoid repeats — it tried s*, u*, v*, x*, m* variants (many). Let me check a couple of them.

Actually, time is limited. Let me make a decision: I'll do a focused 15-minute push on each of 8014CF04 and 8017FB50 with a handful of new ideas, then write everything up.

Idea for 8014CF04: the target's asm has q in $17 and NO extra base. What if the C avoids the extra base by making the *first* access use a different spelling that anchors on q? E.g. the target's offsets from q: -0x19, -0x1D, -0x6B, -0x55, -1, 0. GCC chose q-1 as the base in the unpinned version, so its offsets are -0x18, -0x1C, -0x6A, -0x54, 0, +1.

To force the base to be q, the number of uses must favor q: q is used 2 times (q[0] load, and the increment) vs q-1 5 times. GCC's choice isn't about counts then — it's about the loop induction variable: GCC's loop.c recognizes that `q` is the induction variable and computes "iv offsets" relative to it. Then the base would be q (the IV) and the offsets from q — that's the target. The unpinned version instead created q-1 as a base and used it for everything, keeping q as the IV.

Why the difference? Maybe gcc's loop.c has a heuristic: if the IV is in a hard reg, use it as the base; else create a new base.

Hmm, so this is pin-dependent → WALL.

Let me quickly check one thing though: what if the C uses a *different* induction variable spelling, e.g. `q += 0x10C` vs `q = q + 0x10C`, or using a for loop? The previous attempt tried many.

OK, let me now also reconsider: maybe I'm missing a simpler lever for these two: the "keepalive" and "launder" kinds are not in the row kinds (only "pin"), so the result must be MATCH (pin gone) or WALL.

Let me spend the remaining effort wisely:
1. Write up the results (5 rows).
2. Try a handful of new variants for 8014CF04 and 8017FB50.

Let me try 8017FB50 ideas first (the diff is tiny — just the callee-saved assignment; maybe a small change flips it):

Target: tmp→$16, flag_out→$17, p_out→$18.
Candidate: flag_out→$16, p_out→$17, tmp→$18.

Idea: swap the declaration order so p_out is declared first: then p_out→$16, flag_out→$17, tmp→$18. Still tmp not $16.

Idea: make the arg pointers have fewer refs. What if the 4 calls are made with the SAME variable for the 3rd arg and a *different* expression for the 4th? E.g.:
```
s32 *p_out = (s32 *)&v[3];
s32 *flag_out = (s32 *)&v[3] + 1;
```
Both are used 4 times.

Hmm, what if flag_out is used only 3 times... no, 4 calls.

Idea: increase tmp's refs: `idx = func_801823D4(tmp, -0x1A);` — what if tmp is also used in a comparison that doesn't add instructions? E.g. `if (tmp == tmp)` → removed.

What if the RotTransPers result is stored in a variable that's ALSO used as a call argument? No.

Idea: change the type of tmp from s32 to s16/u16 → changes the RTL mode; the `move s0,v0` copy would still be there. Hmm, the copy `move s0,v0` is a reg-reg move of the call result. The qty for tmp has 2 refs (the move's dest + the use in func_801823D4)...

Wait! Actually, maybe I mis-assumed the priority formula. In gcc 2.7's global-alloc, the qty priority has a "loop depth" factor and also considers the *number of hard regs* the qty needs. But importantly, in global-alloc there's the notion of "reg alloc order" for the class: for MIPS, the alloc order might put s0 first.

But here's a thought: in global-alloc, the qtys are allocated in priority order, BUT there's also a mechanism where a qty that is the destination of a copy from a call's return reg (v0) gets a "preferred" hard reg. In the target, tmp's qty got $16 (s0) — the first callee-saved. In the candidate, the arg pointers got $16/$17.

If the priority order were (arg pointers, tmp), the arg pointers would get $16/$17. The candidate shows flag_out→$16, p_out→$17, tmp→$18. So yes.

To flip: tmp must outrank the arg pointers. tmp's n_refs = 2 (1 set + 1 use) vs 5. pri = log2(2)*2/(len) = 2/L_t; pri_p = log2(5)*5/L_p = 10/L_p. For tmp to win: 2/L_t > 10/L_p → L_p > 5*L_t. L_t = the range of tmp = from the 1st call to the func_801823D4 call. L_p = from the p_out init to the 4th call. The 4 calls are close together, so L_p ≈ L_t. Can't get 5x.

UNLESS the arg pointers' live range is made much longer: init them at the very top of the function (before the v[] setup, which is ~30 instructions). Then L_p ≈ L_t + 30. Still not 5x.

Hmm, but wait: is the formula really log2(n)*n/len? For local-alloc yes; for global-alloc gcc 2.7's `qty_compare` might be different. Let me look at gcc-2.7.2/global.c's priority computation. Let me grep quickly — this could reveal that "more refs = higher priority" isn't the mechanism, and maybe a "loop depth" or "call crossing" factor is decisive.

Actually, let me check the reference source for global.c qty priority.
