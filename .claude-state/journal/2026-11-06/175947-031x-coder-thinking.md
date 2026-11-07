---
ts: 2026-11-07T00:59:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fJh19q8v7RA9MWsDWfZS
---
Interesting! w02 (deadreset) scores 86, worse. And w01 (nn copy) scores 43, same as base — the nn copy didn't survive (cse folded it), and mine is still 99 ins.

Wait, w01 should add `nn = ...; n = nn;` but the score is the same and ins 99. So the copy was folded.

Hmm, the target has `move a2,v0` in the bnez delay slot. In my body, the copy didn't survive because `n` and `nn` are equal and cse merges them; n is only used in `n*8`. In the pinned body, the pins made n a hard reg ($6=a2), so the copy n=nn became a real move.

Lever-free, cse eliminates n=nn (copy propagation). So `move a2,v0` is a pin artifact! Unless we can force the copy.

Similarly the `move v0,s3` (r=p) is the launder artifact.

The deadreset made it worse (86) — it added an instruction? mine 97 (2 fewer than base!). Hmm, w02: `p = 0;` after r=p. It removed instructions? 97 vs 99. Weird — maybe the `p=0` made p dead and the compiler optimized the p=q... Actually with `p = 0` the copy r=p is kept, but maybe p's assignment p=q got folded into r=p? Let's see the diff later.

Anyway, base 43 seems the floor. Let me check whether there's an approach to get the r copy: what if we use a *different type* for r, e.g. `u16 *r = (u16 *)p;` then r-4 and r-1.5... no, target uses -32/-12 byte offsets (r-8 words, r-3 words → u16* r-8 means r is u32* and -8 words = -32 bytes). In the target: `lhu v1,-32(v0)` — v0 = p, offset -32 bytes = r-8 (words). And `lhu a0,-12(v0)` = r-3 words = -12 bytes.

So r is u32* and the loads are u16 loads from r-8 and r-3.

If we declare `u16 *r = (u16 *)(p - 8);` then r[0] += 6 and r[20] += 6. That's a different expression; cse would see r as p-8 and might still fold. But the target's `move v0,s3` is r=p.

Alternatively make r a pointer with a cast that cse can't see through: `u16 *r = (u16 *)(q);` — same value.

Hmm, what about using the C0414 dead-reset but *not* on p — on q? w04 (q=0) scores 43 too. So no change.

Let me look at what w02 (deadreset) actually produced — 97 ins means it LOST 2 ins. Let me dt.sh w02 with the diff to understand. And w20 (q = p + 5) 96 ins, 72.

Actually, more useful: think about whether ANY lever-free body can produce 101 ins with the right regs. The two missing ins are pin/launder artifacts:
1. `move a2,v0` — the nn→n copy (pin $6 on n).
2. `move v0,s3` — the r copy (launder on r).

Plus the register permutation cycle (p,s0↔s3).

Even if we got the ins count right, the registers are wrong. The score 43 counts the mismatched instructions. The prior 28-try attempt concluded WALL callee-saved-order.

Wait, but actually — maybe there's a different angle. What if the parameter *order* changes? No.

What if we reduce p's refs by using `q` for the pre-loop stores, so p's only refs are `q = p` and `p = q`? Let's think: then the stores use q, which is a local pseudo. q would be live from q=p (before stores) to the end. Its refs would be high (~10), live ~25 → priority ~3*10/25*10000 = 12000 → q takes s0. And p (refs 2, live 29) → priority 1*2/29*10000=689 → p gets s3! But the target's s3 pointer is the one doing the stores; if q does the stores and gets s0, we'd have the pointer in s0 and p in s3 with just two moves — doesn't match.

Unless... hmm. In the target, s3 does the pre-loop stores AND is the p of the tail; q (a0) does the loop. So the pre-loop store base and the tail base are the same pseudo (p), while the loop base is a different pseudo (q).

So the target's p is live across the whole function and has the pre-loop refs. It must be low priority. But p has many refs...

Wait — maybe p's priority isn't 11379 in the target because the target's *live length* is different: p (s3) in the target is live from entry to `move v0,s3` — the whole function. Same.

Hold on, maybe I'm wrong that the target's allocation came from priority at all. In the pinned body, s0,s1,s2 are hard-pinned, so p is forced to s3. Right. So the target's assignment is pin-driven, and lever-free it's unreachable unless we replicate the priority inversion.

Could we raise b's refs enough? b has refs 3, live 9 → 3333. To exceed 11379 with live 9, need floor_log2(r)*r > 10.24 → r=5: 2*5=10 no; r=6: 2*6=12 yes → 12*10000/9 = 13333 > 11379. So b with 6 refs would take s0. But the target's b has exactly 3 uses. Adding refs adds instructions → mismatch.

Unless the extra refs are in the *same* instruction (e.g., a register used twice in one insn counts as 2 refs?). "This counts a register twice if it is modified". Hmm, for a use: mark_reg_ref is called per REG occurrence? In flow.c, uses are counted in mark_used_regs per reg, so `b + b` would count 2 refs in one insn but needs 2 uses of b in the same expression — the target has no such insn.

What about c? c refs 3, live 18 → 1666.

What about *reducing p's live length*? live larger → lower priority. p's live is 29 (function length ~101). If p's live range were, say, 60, priority = 300000/60 = 5000 < b 3333? No, 5000 > 3333 still. Need live > 90: 300000/90=3333. Hmm! If p were live for 90+ insns, p's priority drops below b's. p is live from entry to the end (~29?). Wait, "live 29" — the function has 101 instructions. Why is p's live only 29? Because reg_live_length counts... hmm, maybe live length counts basic blocks or something? flow.c: reg_live_length is incremented per insn where the reg is live? That would be ~101 for p. But the note says 29.

Hmm, maybe the note's numbers were computed differently. Let me not trust them. Let me instead measure directly: use the cc1 dumps / alloc_table.py to see actual priorities. The brief mentions tools/alloc_table.py for TU dumps. That would give ground truth.

But time. Item 1 budget: 20-30 min. Started ~17:57. Now ~18:20 maybe. I've done 22 tries + base. Need 30 tries. Let me do another batch of ~12 variants targeting the two artifacts and different shapes, then call it.

Actually, let me reconsider the live-length angle more concretely, since it's the one lever that could flip p below b: if p's live length can be *increased* (or if my numbers are off), the priorities change.

Alternatively, think about what the target's *own* (unpinned) plain C would do: prior note says p(11 refs/29 live)=11379. Let me verify with alloc_table on the current body... that's a dump, expensive. Hmm.

Actually, a cheaper decisive test: is the plain-C assignment p=s0? Yes, observed (mine: move s0,a0). So p outranks b. Wall.

But wait — one more idea: what if the *parameters* are ordered differently in the pseudo world? No.

What about making p's refs lower by *not* using p for the pre-loop stores but using the *parameter's* incoming hard reg? No.

OK, let me try a targeted set of ~12 more:
1. Stores through a temp pointer `u32 *z = p;` then z[0..3], p += 5; q = p. (splits p's refs; z is a local)
2. z = p - 5 for the first store value only.
3. `u32 *z = p + 5; p += 5;` etc.
4. `p[0]` with a separate `u32 m = (u32)p - 20;`
5. b as u16 (changes b's insns? `b += 8` on u16 needs andi → invalid).
6. c as u16: c is `c <<= 16` and `c | (b & 0xffff)`; if c is u16, c <<= 16 on u16 → 0. Invalid.
7. i as u32.
8. i as int.
9. loop as do-while (// !FAKE: do-while).
10. loop as while.
11. p[3] via cl before cl is set? no.
12. reorder the pre-loop stores (p[1] before p[2]).
13. `flag` as a u32 with value 0x1000000 set in both branches.
14. `cs` temp instead of c <<= 16.

Also try the two-artifact combos with the loop restructured.

Honestly, the outcome will be a WALL. But the brief demands ≥30 tries. I have 23. Let me do ~12 more quickly via a second generator batch, then record.

Wait — actually, hold on. Let me reconsider the *nn copy* and the *r copy* once more, because those are 2 of the 101 instructions and might be crackable with C0414-style moves:

nn copy: `nn = (a << 16) >> 28; n = nn;` — cse folds. C0414 dead-reset on nn: `nn = ...; n = nn; nn = 0;`? Then nn is dead; the copy n=nn must materialize. But nn=0 adds an insn that must be deleted later. Try it.

Actually the target has `move a2,v0` — v0=nn, a2=n. So the copy is nn→n. A dead reset of nn after the copy would force it.

r copy: `p = q; r = p; p = 0;` — tried (w02), score 86 (worse). Let me see why: 97 ins. Maybe p=0 got kept and something else vanished. Let me check the diff for w02. If the copy appeared but an extra instruction was added (p=0), the score would be 1-ish different... 86 is much worse, suggesting a different register allocation.

Hmm, w02's score 86 with 97 ins: the dead reset probably made p's live shorter and changed allocation badly.

Let me look at w02's diff to learn.

Actually, let me first test the nn dead-reset variants and the pointer-split variants. Let me generate batch 2.

Also worth trying: `p = 0; r = p;` — no. Or reset via a volatile? Not allowed (barrier/launder kind).

Another thought on the r copy: the target's `move v0,s3` could also arise if r is used with a *different mode*: e.g. `u16 *r = (u16 *)p;` then `r[-16] += 6; r[-6] += 6;`. cse sees r == (u16*)p but the addressing mode differs; it would still fold r into p and use offsets -32/-12. Hmm, but the `move v0,s3` in the target exists because r is a *separate* pseudo. 

What about making r = p but with a store in between that cse can't cross: `r = p; *((u16*)(p-8)) += 6;` — no.

Try: `r = p; p += 0;`? no.

Let me look at w02's diff to understand the mechanism before more guessing.

Actually time is limited. Let me do: dt.sh w02 with diff (80 lines).
