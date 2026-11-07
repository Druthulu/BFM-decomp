---
ts: 2026-11-06T10:37:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1IkHUaRjqsmrugvyCuv9
---
No luck. r9/r10/r11 = 25 (worse).

The sign-ext temp issue is stubborn. Let me think about it from the local-alloc angle: the temp gets v1. To get s0, I need it to be in the "sugg" pass with a copy preference for s0, or for all caller-saved to be busy.

Hmm, what if the div sign-ext is placed BEFORE the jal? Then the temp would be live across the call → gets a callee-saved reg. But the target has it after the jal.

What if I move the sign-ext to before the jal AND it still matches? No, the target has it after.

OK, let me reconsider: maybe the target's in-place sll/sra is NOT from extendhisi2 at all. Maybe the original source had `div = (s16)div` where div is a *hard register*... no.

Or maybe the original source had the divisor as a `s16` function parameter and the sign-extension at each division, with cse hoisting it into... hmm.

Actually, let me reconsider: maybe the target's `sll s0,s0,0x10; sra s0,s0,0x10` comes from `div = div << 16; div = div >> 16;` (two plain shifts, in-place). And the caller-saved bank in the original matched because the original didn't have the do-while tricks.

Our problem: with the two-statement shifts, the bank shifts (cur=v1 vs a0). Why? Because the temp disappears. But in the ORIGINAL (no pin, no keepalive), the bank was correct. So maybe the do-while is what perturbs the bank, not the shifts.

Let me test: two-statement shifts WITHOUT any do-while (just nopin + shifts) = k2 (score 28). Hmm, that's without the cast do-while. With the do-while around the casts (r5) = 22.

What if I use the two-statement shifts and NO do-whiles, but boost div's refs another way? The pin needs the ref boost.

Hmm. What if I boost div's refs via a do-while around ONLY the divisions (f1's do-while) + two-statement shifts + NO cast do-while = f5 (score 28). The a-mask hoist is the issue there.

So: cast do-while fixes the a-mask hoist but perturbs the bank when combined with the in-place shifts.

Let me look at r5's diff to understand the bank shift. Maybe a small reorder fixes it.

Actually, let me try: r1 (cast do-while) + two-statement shifts but with the shifts in their own do-while (separate EBB), or with an extra statement.

Hmm, let me try r12: r1 with `div <<= 16; div >>= 16;` (compound assignment). Might produce different RTL.

And r13: r1 with the shifts expressed as `div = (s16)(div << 16 >> 16);`? no.

Let me test r12.

Actually, let me reconsider the bank shift in r5: cur=v1 vs a0, iVar4=a3 vs v1. The target's bank: cur=a0, iVar4=v1. In r5, cur=v1, iVar4=a3.

In r1 (with the temp), cur=a0, iVar4=v1 (target bank!). So the temp's presence is what gives the right bank.

So I need the temp to be in s0 (in-place) WHILE existing. That means the temp and div share s0. The temp is a separate pseudo; if it's allocated s0, the sll is `sll s0,s0,16` (in-place) and the sra `sra s0,s0,16` (in-place). And cur would see v1 busy? No — if the temp is in s0, then v1 is FREE at cur's birth → cur=v1 (wrong bank).

Wait, no: in r1, the temp is v1 and cur=a0. If the temp were s0, v1 would be free → cur=v1. So the bank would shift. Hmm, so even if the temp got s0, cur would take v1.

Unless the temp being in s0 means div's value... hmm.

Wait, in r1, the temp is v1 and it's live from 14 to 18. cur is born at 16. So v1 is busy → cur=a0. If the temp were s0 (div's reg), then v1 is free at 16 → cur=v1. So the bank shifts. Contradiction.

So the target's in-place sll/sra (temp in s0) AND cur=a0 requires v1 to be busy at cur's birth for another reason.

Hmm, what else could occupy v1 at cur's birth in the target? Let me look at the target asm: at position 16 (andi a0,v0,0xfff = cur), what's in v1? The target's asm:
```
3a18: addiu v0,v0,-1024
3a1c: sll s0,s0,0x10
3a20: andi s1,s1,0xfff
3a24: andi a0,v0,0xfff
```
v1 is not used. So v1 is free at 3a24. Yet cur=a0. 

So in the target, cur is a GLOBAL qty (used in later blocks) and global-alloc assigned it a0 based on priority, not "first free". The local-alloc "first free" doesn't apply to global qtys.

Right! cur is global (used in `diff = cur - a`). So global-alloc assigns it. The bank is determined by global priorities, not local-alloc.

So the temp's allocation (local) doesn't directly affect cur's global allocation. Hmm, but the temp's presence changes the RTL/qty numbering and thus the global order? Maybe.

OK, this is really deep. Let me accept item 3 as WALL with best 2 (r1) instead of 5. Let me update the results and win.c.

r1 scores 2, which is better than f1's 5. Let me use r1 as win.c for item 3 (best 2).

Let me update:
- win.c = r1.c
- results.tsv item 3: best 2, tries 40, evidence updated.

Let me also reconsider the wall tag: the residual is the extendhisi2 temp register (local-alloc gives it v1, target in-place s0). Tag: `lreg-qty-priority`? Or `lreg-index-conflict`? The temp takes v1. Hmm. Actually, the wall is that the sign-extension temp can't be coalesced with div. Tag `lreg-copy-pref-dying-base`? No. 

Let me use `lreg-qty-priority` (local-alloc gives the hard reg to the other pseudo) — the temp gets v1 instead of s0. Hmm, but that's a different mechanism.

Actually, the mechanism: extendhisi2 (mips.md:2340) always creates a temp; local-alloc puts it in $v1; the target has it coalesced into $s0. The coalescing requires div to be a hard reg (the pin). So it's `global-hardreg-reserve` (the pin reserves s0 for div, and the temp follows). Hmm, that fits: the pin's hard-reg pseudo makes div=s0, and the temp coalesces.

Let me use `global-hardreg-reserve` for item 3? But item 4 also uses it. That's fine (tags can repeat).

Hmm, actually the more precise tag: the extendhisi2 temp is a separate pseudo that local-alloc can't tie to div. Let me call it `lreg-qty-priority`.

Hmm, let me look at what the best body r1's residual really is: `sll v1,s0,0x10` vs `sll s0,s0,0x10`. The temp v1 vs s0. This is a local-alloc choice. Tag `lreg-qty-priority` is the closest existing tag ("local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo").

OK. Let me update item 3's row and win.c. Also, let me try a couple more variants to see if I can crack it (since it's at 2).

Idea: make the extendhisi2 temp get s0 by making it a `register` variable? The temp is compiler-generated, not a C variable.

Idea: use a C-level temp with a copy preference:
```
s32 dt;
dt = div << 16;
div = dt >> 16;
```
This gives in-place shifts (no compiler temp) but shifts the bank (r5-like). Hmm.

Wait, r5 (two-statement shifts) = 22. The bank shift. Let me look at r5's diff to see if a small reorder fixes it.

Let me diff r5.
