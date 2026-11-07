---
ts: 2026-11-06T06:19:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_24N7iJUHsDM6nSr24U50
---
w2.c scores 0 with the pin kept and the launder cracked → PARTIAL:pin.

Now let me push for MATCH: win.c (both levers gone) at score 11 with the ent/loopptr swap.

Let me try a few moves quickly:

Try A: ent used via a shorter-lived spelling. What if I compute ent *inside* the if block? That changes the code layout (target has it outside). No.

Try B: increase ent's refs. Idea: pass ent to a third call? No.

Try C: lower loopptr's priority by extending its live range: assign `s2` before the two calls (func_80131C78, func_8012A828). Let me try moving `s2 = (u16 *)D_801202A0; s5 = s2 + 0x3240;` to before `func_80131C78(a0);`. This changes source order; sched1 may or may not restore. Cheap test.

Actually hold on — think about what sched1 does: it schedules the whole basic block. The block here contains calls, so the block boundaries are at calls? No — a basic block ends at a jump; calls don't end basic blocks. sched1 works on EBBs (extended basic blocks) and can reorder across calls within the block? In gcc 2.7.2 sched.c, scheduling across calls is allowed if there are no dependencies, but calls are "not scheduled across"? Let me recall: `sched_analyze` for CALL_INSN marks all call-clobbered regs as used, so independent insns CAN move across calls. Yes, sched1 does reorder across calls.

So moving the source assignment earlier might be undone by sched1 (putting it back right before its use). Then live length stays 35. Worth a try — it's one candidate.

Try D: reduce loopptr's refs. What if the loop's comparison uses a count instead? No, changes insns.

Try E: make `ent` and the loop pointer related such that ent gets $17 via copy preference? ent's preferred regs: it's an arg to calls in $5/$6... The preference list would be a1/a2. Not s1.

Try F: What if `s3` (a0+4) and `ent` swap roles? s3 is in $19 in target; it's 3 refs live 31 → pri 967.

Hmm, what about this: **make ent's live range shorter by moving its definition inside the if**, so ent is born just before the calls. Then ent live ~6, refs 3 → pri 1*3/6*1e4 = 5000 < 7714. Still not enough. With live 3: 10000.

Try G: **give ent more refs via a third use that costs nothing**: e.g., `func_8012BC60((void *)s3, (void *)ent)` — what if the source computes `(void *)ent` into a local first? No.

Hmm, what about the possibility that in the original, the loop pointer variable was `u16 *s2` AND there was also a `s5` computed as `s2 + 0x3240`, and ent computed from s2 — exactly as we have. Then how did the ROM get $18? Maybe the ROM's loop pointer had MORE refs (weighted by loop depth!) — wait, in the original (do-while) the loop weighting would make the loop pointer's priority even higher (7714*2 ≈ 15428). That's worse.

Unless... the original loop pointer's live length was longer.

Hmm, hold on. Maybe I should reconsider: in the target, is the pin really needed? We know the pin was added because "NEEDED DIFFERS". The prior agent found that without the pin, the register assignment differs. Maybe the prior agent didn't try the launder crack (which changes the address pseudo and thus the allocation). Our win.c (both removed) gives only the ent/loopptr swap. So the pin is *still* load-bearing for that swap.

Let me try harder on the priority arithmetic. The key numbers:
- loopptr r73: refs 9, live 35, pri 7714.
- ent r80: refs 3, live 12, pri 2500.

Need ent > loopptr.

What if ent gets 4 refs and live 10: floor_log2(4)=2 → 2*4/10*1e4 = 8000 > 7714. ✓
What if ent gets 4 refs and live 9: 8888. ✓
What if ent gets 4 refs, live 11: 7272 < 7714. ✗

So 4 refs + live ≤ 10 works. Currently live 12. If ent's definition moves 2 insns later (live 10), and it gets one more ref...

How to add one ref without an instruction? An extra *use* in the same expression that combine doesn't fold... e.g., `func_8012BC60((void *)s3, (void *)(ent + 0))` — folds. `(void *)(ent - 0)`? folds.

Hmm, what about using ent in the store `unkCC = (s32)s2` — no.

What about: `r2 = func_8012B6D4((s16 *)s3, ent);` and then use ent again... no.

OK, alternative: reduce loopptr's live length is impossible (it must span the loop), but we could *increase* it — no wait, increasing live length LOWERS priority (divides). pri = f(refs)/live. So to lower loopptr below 2500, live must be > 3*9/2500*1e4 = 108. That's a huge extension. Only possible if the loop pointer lives across most of the function — impossible.

So the only path is raising ent above 7714: needs 4 refs with live ≤ 10, or 5 refs with live ≤ 12.

5 refs at live 12: floor_log2(5)=2 → 2*5/12 = 8333 > 7714 ✓. So 5 refs with the current live range works. That's +2 refs.

Can I get +2 refs on ent without extra instructions? Two extra RTL mentions. Hmm... What if the two call args are spelled differently so that a copy is made? No, copies cost instructions.

What about the possibility that `ent` in the original was used for the *load* `*s2 == 0xF2` too? I ruled that out (lh vs lhu).

Hmm, what if ent is a `void *` and the load is `*(u16 *)ent`... no, different address.

Wait wait. What if the original code is:
```c
ent = (s16 *)(s2 + 2);
if (*s2 == 0xF2) {
    if (func_8012BC60((void *)s3, (void *)ent) < 0x4000) {
```
and the target's `addiu s1,s2,4`... 

Alternatively the original might have had `s2` as a `s16 *` or the loop over a struct with ent = &s2[1]...

Honestly, maybe I should check whether the *refs* of ent can rise via the `(void *)` cast being a real conversion. In gcc, `(void *)ent` from `s16*` is a NOP. 

New idea: what if `ent` is declared as `u16 *ent` and the calls take `ent` directly with an implicit conversion... no change.

New idea: **use ent twice more by storing through it**? Changes instructions.

OK, different tack: what if the LOOP POINTER is a different variable with fewer refs? What if the loop is written to use a *byte* offset and the pointer is recomputed? No, insns would change.

Hmm, let me reconsider the refs count. r73 has 9 refs, live 35. What if the entry test `if (s2 != s5)` is dropped and the do-while kept (that's orig)? Then refs = 8 (one less test) and loop-weighted (depth 2): 8*2=16 weighted refs... reg_n_refs is the weighted count. floor_log2(16)=4 → 4*16/35*1e4 = 18285. Worse.

What if the goto loop has refs 9 with live 35.

What if I make the loop pointer's increment use a *different* variable... 

OK here's another thought: what if `s5` is the loop variable and `s2` the bound? I.e., invert: the ROM's loop pointer is s2 (moving forward to s5). Can't invert.

Let me try a couple of empirical variants quickly and see the score:
V1: move `s2 = ...; s5 = s2 + 0x3240;` before the two calls (longer live).
V2: compute ent later (inside, right before the first call).
V3: make ent a u16* and use `(u16*)s2 + 1`? same.

Let me batch-generate a few variants and score them with sc.sh in one command. Each variant file w3.c, w4.c, ...

Actually, hmm, V1: extending live length makes pri = 3*9/45*1e4 = 6000 — still > 2500. Not enough. Dead end.

So really we need ent up. Since ent's refs are structurally 3 (1 def + 2 uses), the only free parameter is live length: 3 refs, need pri > 7714 → 3/live*1e4 > 7714 → live < 3.9 → live ≤ 3. Impossible (2 uses in different places with a call between; the call is 1 insn, so def + call + ... at minimum live ~4-5).

With 4 refs: live ≤ 10.
Hmm, is there a way to get a 4th ref on ent with no insn? What if ent is passed to the first call twice? No.

What if the first call is `func_8012BC60((void *)s3, (void *)ent)` and the second `func_8012B6D4((s16 *)s3, ent)` — and additionally the *comparison* `if (func_8012BC60(...) < 0x4000)`... no.

OK so what if ent's *definition* is moved to right before the calls (inside the if), making live ~5, with 3 refs → 6000. Still < 7714.

Hmm, and 4 refs at live 5 → 8000. ✓ But I need a 4th ref.

Hmm, is `ent` maybe used as an argument to func_8012BC60 with a cast that creates a temp pseudo? No.

Let me step back and consider: maybe the target's ent isn't a separate variable at all but `s3 + something`? Target: s3 = s0+4 (a0+4), ent = s2+4 (s2+2). Different bases.

Alright: the pin seems genuinely load-bearing for the ent/loopptr order. That's a legitimate PARTIAL. But before concluding, let me check the move history for a similar case: "lreg-qty-priority", "greg-alloc-order". Our case: the pinned reg was $18 (third callee-saved) and lever-free the loop pointer takes $17. There's a known wall: "global-hardreg-reserve" (the pin reserves a reg for the whole fn). Here it's more like: the pin puts the loop pointer third.

Hmm, but wait. Let me reconsider one more possibility: what if we can make the *param* and others take $16/$17 so that loopptr gets $18 by having TWO other allocnos outrank it? Currently the order after a0 is r166 (12500), then r73 (7714), then r80 (2500). r166 — what is it? 5 refs, live 8, pri 12500, "dies in 2 places", conflicts v0,sp. That's a short-lived temp that takes a caller-saved reg. If it took a callee-saved reg... no, it's caller-saved.

Hmm, so among callee-saved-needing allocnos (crossing calls): r72 (19266), r73 (7714), r80 (2500), r74 (967), r75 (857), r76 (454). Six of them, exactly filling $16-$21. Target: r72→$16, r80→$17, r73→$18, r74→$19, r75→$20, r76→$21.

So we need to swap r73 and r80 in the priority order. 

New idea: what if `s5` (r76, the end pointer) ... no.

New idea: what if the loop pointer variable is declared as `u16 *s2` but the *loop* uses `s2` with a different increment variable... 

OK, radical idea: what if we give the loop pointer MORE live length by starting it earlier — I computed that doesn't lower it enough (6000 > 2500). What if we ALSO raise ent's refs by 1 → 4 refs, live 12 → 6667 > 6000 ✓!! 

So: extend loopptr's live length (move its init earlier → live ~45-50, pri ~5400-6000) AND add one ref to ent (4 refs, live 12 → 6667). Then ent > loopptr. But both changes affect the instruction stream:
- Moving `s2 = D_801202A0; s5 = s2+0x3240;` earlier changes the insn order (target has them right after the calls at 207-209). sched1 might sink them back — actually if sched1 sinks them back to just before the beq, the live length shrinks back and the priorities revert. But live length is computed by flow BEFORE sched1 (flow runs before local/global alloc, sched1 runs after global-alloc). So the RTL order at flow time determines live length, and sched1 later reorders for output. Interesting! So moving the source line earlier would extend the live length in flow's view, but sched1 could still place the insns where the target has them. That's promising!

But moving the assignment earlier in the source also risks changing the instruction order after sched1.

Hmm, but what about the *first* idea of all: this is a 281-insn function and we have 11 mismatches from one allocno swap. Let me try the "move the loop init earlier" + see the score. If the score drops to 3 (just the ent/loopptr), we're closer.

Actually, simpler experiment: does moving `s2 = ...; s5 = ...` earlier alone change anything? Let me try it.

Where to move? Before `func_80131C78(a0);`? That's at the top of the `if (t >= 0x11)` block. The block is large. Actually s2's live length would then span from that point to the loop end.

But careful: s2/s5 are declared at function scope, and this is case 2's else branch. Moving the assignment before func_80131C78(a0) means s2 is live across those two calls — that could change... hmm, the register would still be callee-saved. Fine.

Let me test V1: move the two lines up before func_80131C78.

Actually wait. There's a subtlety: live length counts insns where the pseudo is live — including the gap across the calls. That's ~10 more insns. 3*9/45 = 6000. ent 2500. Still loopptr wins. And with 4 refs on ent (6667) ent would win. But I can't easily add a ref.

Hmm, so V1 alone won't work. Unless... let me reconsider the refs of ent. Let me actually look at the .lreg RTL for r80 to count its refs and see if any is foldable.

Actually — hold on. What about making ent's live length SHORTER by computing it inside the if? Target has `addiu s1,s2,4` before the branch though. If I compute ent inside the if, the addiu would move inside — mismatch (2 insns moved). Not good.

Alternatively: keep ent's def where it is but make its last use earlier? No.

Hmm, what about the reverse: make ent's *first* use later? No.

OK here's yet another idea: **what if ent is not a pointer variable but the second call takes `(s16 *)(s2 + 2)` again?** Then ent wouldn't exist and the arg would be computed into a1 twice. Target has one addiu s1 + two moves. So no.

Let me look at this from a totally different angle — maybe the original code used a struct pointer:
```c
ent = (s16 *)(s2 + 2);
```
What if it was `s16 *ent = (s16 *)&s2[1];`? Same.

Alright, let me consider the possibility that the pin is load-bearing and record PARTIAL:pin. But the brief says MATCH = kinds gone; PARTIAL is allowed. Given the 20-30 min budget per item and 4 items, I should time-box this one. It's been ~25 min. Let me do ONE more experiment (V1: extend loopptr live length), and if it doesn't give 0, bank PARTIAL:pin and move on.

Actually, let me reconsider one more time — there might be a cheaper trick: what if the loop pointer gets a *longer* live length naturally by using `s5 = s2 + 0x3240` computed BEFORE the loop (it is) — the live length counts from the first insn where it's live (the def) to the last use. 

Alternatively, reduce the loop pointer's refs by 1: what if the entry test `if (s2 != s5)` were removed? Then the do-while runs at least once — different codegen (target has the beq). No.

What if the loop's *increment* used `s2 += 0x86` but the comparison is `s5 != s2`? Same.

Hmm, one more: the `(s32)s2` store for unkCC. What if instead we write `unkCC = (s32)ent - 2`? Then ent gets the ref and s2 loses one, plus an addiu -2? That would add an instruction. No.

Let me try V1 and also V2 (ent defined later) in one batch.

V2: move `ent = (s16 *)(s2 + 2);` to just before the first call inside the if? It's used in the if condition itself, so it can't be inside. It must be before.

OK just V1.

Actually — hmm, what about making the loop pointer live LONGER by making `s5` computed from it at the very top of the function? s5 = s2 + 0x3240 requires s2's value which comes from D_801202A0. We could initialize s2 at the top of the function: `s2 = (u16 *)D_801202A0;` — but that would change the insn position (the lui/addiu would be emitted at the top). sched1 could sink it into the block... but sched1 doesn't move insns between basic blocks (EBBs). The top of the function is a different block than case 2's block? The switch has separate blocks. So the insns would stay at the top → mismatch.

Let me just do V1 within the same block: move the assignment up past the two calls. Same basic block, so sched1 may reorder freely. Let me test.
