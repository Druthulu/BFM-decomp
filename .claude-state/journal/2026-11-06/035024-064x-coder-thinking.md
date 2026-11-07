---
ts: 2026-11-06T10:50:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VGRGHWd9RyggopCVVAJn
---
Same as v_param: the load still hoisted (cse folded p). 

Time to decide. I've used a lot of time on item 1. Let me check the actual elapsed time.

Let me be pragmatic: I have two very close candidates (score 2) with complementary defects. Let me try a couple more targeted combos, then if not, record a WALL with best=2.

Actually, wait. Let me reconsider the v_addr5 case (order perfect, t global got v1). If t is global and got v1, maybe I can make it get v0 by making `v0`'s pseudo (the call result) not take $2. In v_addr4 t got v0. The difference between v_addr4 and v_addr5: v_addr4 has a in block2 with the RMW; v_addr5 has a+store in block2 and the RMW in block3.

In v_addr5, global allocnos include t and the call-result v0 pseudo. If t got v1, then v0's pseudo took $2 and t took $3. In v_addr4, t got $2 — maybe because in v_addr4, the call-result pseudo's last use is earlier?

Hmm, the call-result v0's uses: stored to unk20, compared, and passed to func_8001CA1C. Its live range ends at the func_8001CA1C call. In both variants that's the same.

Hmm, why would t get v0 in one and v1 in the other? Global-alloc priority: t's live length differs! In v_addr4, t is defined in block1 and used in block2 (the ori). In v_addr5, t is defined in block1 and used in block3. The live length is longer in v_addr5 → lower priority → loses to the call-result pseudo. In v_addr4, t's live range is shorter → higher priority → gets $2 before the call-result pseudo.

So: t's priority vs the call-result pseudo. In the target, t got $2 (pinned, but the pin is what we're removing). Lever-free, we need t to outrank the call-result pseudo.

The call-result pseudo's live range: from the call to the last use (func_8001CAE4? no—func_8001CA1C call in the else branch). That's a long range spanning the branch. Its priority: refs=3 (store, compare, arg), floor_log2(3)=1, so 3*4/len. t: refs=2, 2*4/len_t.

To beat it, t's live range must be much shorter. In v_addr4 t is live from block1's load to block2's ori — across the do-while boundary but short in insn count? Global-alloc's live length counts insns.

Alternatively, make the call-result pseudo's range shorter or lower priority — e.g., use the call result directly in the comparison and the store... it already is.

Hmm, what if we avoid the `v0` local entirely: `((Unkstruct*)a0)->unk20 = func_8012C1B8();` then `if (((Unkstruct*)a0)->unk20 == 0)`? That would reload. No.

What if the call result is stored and the comparison uses a *different* copy? That changes codegen.

OK, alternative: make t's live range shorter by putting the RMW right after the load, in the same block, and the store in between... that's dw2 (7).

I think I should try the "wrap the load and the RMW in the same do-while with the store between" = dw2 (7, regs swapped).

Hmm.

Let me try ONE more idea: the target's schedule could arise if the address computation is *hoisted* into block1 while the store stays in block2, and the store is scheduled first in block2 because it's ready. That's v_addr (score 8): order perfect, regs swapped (t v1, a v0) because both local in block1 with a born later.

What if I make a's birth EARLIER than t's in block1? Then a's live range is longer → t (born later) gets v0. Source: `do { a = (s32)&D_801907C4; t = unkC4; } while(0)` = v_addr3, which gave the load AFTER the address in the schedule (lui, addiu, lw) — sched1 kept source order. Only the load position wrong.

So v_addr3 has correct regs and order except the load should be first. Can I get sched1 to move the load above the address computation? The load is independent; sched1 might not reorder because of priorities. If I make the load *more urgent* (e.g., it has a use soon), no.

Hmm, what if the address computation is placed in a *separate do-while* before the load's block? Then blocks: [a] [t] [store, RMW]. The store in block3 would be first (ready) then ori. Let me test:
```
do { a = (s32)&D_801907C4; } while(0);
do { t = unkC4; } while(0);
unk58 = a;
unkC4 = t | 2;
```
Regs: a is local to block1 → could get v0; t is global (used in block3) → gets a hard reg after global alloc; if a took v0 in block1 (local-alloc runs after global), then t would have v0 (global) and a would get v1. Global alloc assigns t some caller-saved reg — it may pick v0. Then a (local) gets v1. That's the target!

Order: block1: lui, addiu; block2: lw; block3: sw a, ori, sw. Hmm, but the target has lw FIRST, then lui/addiu. That would be wrong: we'd get lui/addiu before lw.

Unless the blocks get merged in the final output... no, block order is preserved.

So the target's load-first means the address computation must be in the same block AFTER the load. v_addr (both in block1, load first) gives that order but swaps regs.

Hmm, what if the address is in block1 with the load, and the store + RMW in block2? That's v_addr (score 8, regs swapped).

So the crux: in v_addr, both t and a are local to block1; a is born later → wins v0. To make t win v0, t must be born later — but then the order flips (v_addr3).

Unless... we make a's qty lower priority by giving it a *larger size*? No, same size. Or by making a have FEWER refs? Both 2. Or by making a's death-birth larger: a dies in block1? If a's last use were in block1, its range would end there. But the store is in block2.

What if a is dead at the end of block1 (i.e., its use is in block1) and the store is also in block1? Then block1 = lw, lui, addiu, sw, and block2 = ori, sw. That's e_S2S3S4-ish = 7 (regs swapped). Hmm, in that case t and a both die in block1: t's last use is the ori (block2), so t is live at block1's end; a dies at the store in block1. Then a's range is shorter → a wins v0. Still swapped.

To make t win v0: t's range in block1 must be shorter than a's. t born at the load, dies at the ori (block2) → live to block end. a born at the address, dies at the store (block1) → shorter. a wins. Always.

Unless t is born AFTER a: v_addr3 (a first, t second) → t wins v0 but the load is scheduled after the address.

So: can I have the source order a-then-t but the *scheduled* order t-then-a? sched1 kept source order in v_addr3. Why? Because sched1 lists ready insns; the address (lui/addiu) is ready immediately, and the load is also ready. Priorities: the load has a dependent (the ori later); the lui/addiu feed a store. Hmm.

What if the load is made *more urgent* by having its result used sooner (e.g., the ori right after)? No.

OK, what if I place the address computation *textually* after the load but with a construct that makes its birth index later yet keeps... that's v_addr (swapped).

I'm going in circles. Let me check the elapsed time and decide. Let me look at the clock.
