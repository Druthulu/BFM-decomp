---
ts: 2026-11-06T06:20:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EtW3zubv5aD85cB5i0e6
---
Score 13, worse than 11. Let me check the pairs.

Actually, let me think about it differently. Let me check what the pairs are for w3.

Actually, let me stop this line and try the opposite: reduce the loop pointer's priority by reducing refs. 

Hmm, one more idea I haven't tried: what if `s2` is declared as `u16 *s2` but assigned from a *cast of an int*? no.

Let me look at the target's register allocation from a different angle: what if the original code's loop pointer was in a variable that ALSO is used for something outside the loop, making its live range span the whole function and its priority low? E.g., if the ROM's source reused `s2` for the earlier `s2`-like job... 

Interesting thought: s2/s3/s4/s5 are our names for $18/$19/$20/$21. In the target: s2=$18 (loop ptr), s3=$19 (a0+4), s4=$20 (flag), s5=$21 (end ptr). 

What if in the original, the variable that ends up in $18 was declared/used differently...

OK. Time check: I started item 1 at 23:05, it's now maybe 23:35. Let me check the time and decide. I've done ~8 scored tries on this item. The brief says a WALL needs ≥20 min and ≥30 scored tries. But PARTIAL:pin is already banked at score 0 — that's a valid result (not a WALL). PARTIAL is a legitimate outcome per INTERFACES: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)".

So for item 1: PARTIAL:pin with w2.c as win.c (score 0). Good. I could keep trying for a full MATCH but time budget matters. Let me try 2-3 more quick ideas, then finalize.

Quick idea list:
1. w3 (longer live) → 13. no.
2. ent as a local `s16 *ent` declared inside the loop? no.
3. Make the loop pointer's live length longer AND ent's refs +1 via a zero-cost use.

Hmm, what about making ent's refs 4 by using it in the `unkCC` store: `((Unkstruct_800B5CB8 *)a0)->unkCC = (s32)ent - 2;` — that emits `addiu a1,s1,-2`? An extra insn. No.

What about `if (func_8012BC60((void *)s3, (void *)ent) < 0x4000)` → keep, and `r2 = func_8012B6D4((s16 *)s3, ent);` → the same.

4. What if ent's declaration is moved to the top of the function (like s2, s3, s4, s5 are declared at function scope)? Currently `ent` IS declared at function scope (line 9: `s16 *ent;`). Yes.

5. What if `s3` (a0+4, r74, pri 967) and ent swap? no.

Let me try one more: make the loop pointer's live length long by moving the *initialization* to the top of the `if (D & 0x1000)` block (before the stores), i.e., right at the start of the case-2 if-true block. But that block is a different branch than the else where the loop is. s2 would be assigned in one block and used in another — global alloc would then treat it as live across blocks → live length much longer → priority drops a lot. And the insns: the lui/addiu s2 would be emitted in the if-true block, which is NOT the target's position (target has it at 207 in the else block). So the insns would be in the wrong place. Unless sched1 moves... no, different blocks.

Hmm, BUT: what if I initialize s2 at the *top of the else block* (the `} else {` branch)? The else block starts with:
```c
            } else {
                t = ((Unkstruct_800B5CB8 *)a0)->unk1C + 1;
                ((Unkstruct_800B5CB8 *)a0)->unk1C = t;
                if (t >= 0x11) {
                    func_80131C78(a0);
                    ...
```
Moving `s2 = (u16*)D_801202A0; s5 = s2 + 0x3240;` to before `t = ...` would put them in the same block? No — the `t >= 0x11` if creates a branch, so the insns would be in the outer block, before the branch. Different position than the target.

w3 already tried moving them before the two calls in the same block (score 13). The live length extension didn't help; instead it broke something else.

Let me look at w3's pairs to understand.

Actually, let me just accept PARTIAL:pin for item 1 and move on. I have 3 more items. But before that, let me do a sanity check on how much time I've used.

Actually — wait. One more important idea! The ref count of the loop pointer includes refs *weighted by loop depth*. With the goto loop there are no LOOP notes... but flow computes depth from the notes; if there are none, depth = 1 everywhere. Fine.

But here's the thing: what if I *keep* the do-while (orig) and the loop weighting makes loopptr even higher? Already known.

Alternatively — what if the loop pointer's live length can be increased without moving its birth: by making it live until AFTER the loop, e.g. use s2 after the loop in a dead computation that flow deletes? A dead assignment is deleted by flow before the live-length computation? Flow computes live length from the RTL it sees; dead code is removed by... cse/jump/flow's dead code elimination (flow.c's `delete_dead_jumps`? no, dead stores are removed by `flow` in `life_analysis`? Actually dead code elimination happens in `jump_optimize`/`delete_dead_code`? In gcc 2.7.2, dead stores are removed by `flow.c`'s `delete_dead_code`? Hmm, there's `dce` in jump.c? The C0414 dead-reset move says "deleted by delete_dead_from_cse" — so dead sets are deleted by cse.

If I add `s2 = 0;` after the loop, cse's delete_dead_from_cse would delete it (dead store to a dead pseudo), so it wouldn't extend live length. Hmm.

What if I add a use that's cheap: `s4 = s4;`? no.

What about `if (s4) ...`? already.

Hmm, what if after the loop I add `s2 = 0;` — if cse deletes it, no effect; if not, it extends live length to the end of the function → pri = 3*9/200 = 1350 < 2500 → ent wins! But it would also add an instruction (li s2,0) unless deleted. Risky but cheap to test. Actually the C0414 move relies exactly on dead resets being deleted. So cse deletes them → no live-length extension.

OK, what about a *real* use of s2 after the loop that the target also has? No.

Decision: PARTIAL:pin for item 1. Actually hold on, let me try ONE thing: what if the loop pointer is `s5` and the end is `s2`... no, semantics.

Hmm, actually, let me reconsider the possibility that ent's priority can be raised by giving it 5 refs via a **second store** of ent... no.

Let me look at the problem from the "what would the original C look like" perspective once more. In the target:
```
212 addiu s3,s0,4     ; s3 = a0+4
213 lhu v1,0(s2)      ; *s2
     ... compare/branch
216 addiu s1,s2,4     ; ent = s2+2 (as bytes)
```
Wait: `addiu s1,s2,4` = s2+4 bytes = s2+2 elements (u16). Yes ent = (s16*)(s2+2).

The order: ent is computed AFTER the lhu and after the branch? In the target asm, 213 is the lhu and 216 the addiu — but where's the branch? Between them (214-215)? The diff shows only mismatched lines; 214-215 matched, so they exist in both. Let me look at the actual target asm. Let me get the candidate .s and the target .s. I can get the target asm by compiling the src TU? The build/ has the object; I can objdump it. Hmm.

Actually, I could look at the .s of my candidate: $D/dmp/dumps_cand/cand.s. And for the target, I could use the build object with objdump. Let me not.

I'll go with PARTIAL:pin. Actually, wait — let me reconsider ONE more structural idea that's cheap and plausible: declare the loop pointer as `u16 *s2` and the *end* as an int count. No.

Decision made: PARTIAL:pin, win.c = w2.c.

Actually hold on. Let me reconsider the whole framing: is `register ... __asm__("$18")` the only pin? The kinds say "launder,pin". Yes.

For PARTIAL:pin, win.c = orig with only the launder replaced (w2.c, score 0). Good.

Let me now write results and move on to item 2, but first record the time.

Actually, let me try ONE more quick idea since it's cheap: what if the loop pointer gets $18 because ent's *live range* is 10 or less AND refs 4? Let me look for a zero-cost 4th ref: what if the first call passes `ent` and the second passes `ent` and additionally the source *stores* `s4 = 1` ... no.

Alternatively, what if `ent` is used as `func_8012B6D4((s16 *)s3, ent)` and I add `(s16 *)` casts around both — no refs.

Alright, PARTIAL:pin. Let me finalize item 1.

Actually, hmm, wait. One more genuinely promising idea: **the `ent` variable could be `s16 *ent` but the target's ent might be the same pseudo as something else via coalescing**. Forget it.

Let me record item 1 and move to item 2. I'll note the mechanism precisely: global-alloc order: the pin's hard-reg pseudo... no, actually here the pin at $18 removes $18 from the pool and the loop pointer (pri 7714) takes it; lever-free the loop pointer's priority (7714) beats ent's (2500), so it takes $17.

Wall tag: this is closest to "greg-alloc-order" (from walls.txt: "global-alloc: ... the allocno tie-break"). Our tag must be from walls.txt or a new `<pass>-<what>`. But since it's PARTIAL (not WALL), the wall field for PARTIAL rows... The format says: "wall (WALL/PARTIAL) = a tag from walls.txt or a new `<pass>-<what>`". So PARTIAL rows need a wall tag too. I'll use a new tag `global-pri-pin-bank` or use the existing `global-hardreg-reserve`? Let me think: "global-hardreg-reserve — the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". Ours: the pin reserves $18; lever-free the loop pointer (pri 7714 > ent 2500) takes $17 and ent gets $18 — it's a *priority order* issue among callee-saved allocnos. A new tag: `global-pri-order` — hmm, existing "greg-alloc-order" is in walls.txt? Yes: "global-alloc: ... the allocno tie-break (global.c:607)". Not a tie here.

I'll define a new tag: `global-pri-bank-order` — "lever-free the loop pointer's allocno priority (floor_log2(refs)*refs/live) beats the derived-pointer temp, so it takes $17 and the temp $18". That's precise.

Let me now check my time and write item 1's result.

Actually — hold on. Before I finalize, let me reconsider ONE cheap variant: what if I keep `ent` but ALSO give it a use that flow keeps: e.g. `if (ent == 0) ...`? adds insns.

OK, finalize.

Time: let me get the date.
