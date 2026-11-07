---
ts: 2026-11-06T10:36:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1DB86VJN3xASQZcGx85o
---
r1: only the sign-ext temp remains (2 instructions: sll v1,s0 vs sll s0,s0; sra s0,v1 vs sra s0,s0). This is the `extendhisi2` temp (mips.md:2340) allocated to $v1.

To make it in-place, the temp must get $s0 (div's register). The temp is a local qty with refs 2, live 2 → high priority. It gets the first free caller-saved reg ($v1, since $v0 holds ang).

Options:
1. Make $v1 busy at the temp's birth so it picks $s0. But the temp is local (doesn't cross calls), so it prefers caller-saved; if all caller-saved are busy, it'd take a callee-saved one. At the temp's birth (after the jal), v0=ang is live. v1, a0, a1, a2, a3 are free. To make them all busy, I'd need more live values — adds code.

2. Use the two-statement shift (`div << 16; div >> 16`) which is in-place (no temp) — but that shifted the caller-saved bank (r4 = 22). Hmm, r4 is 22. But r4 also has the do-while around the shifts. Let me look at r4's diff.

Actually, wait: r4 (shifts inside do-while) = 22. The two-statement shift removes the temp but shifts the caller-saved bank. Earlier i1/j1 also did this (22).

Hmm. But maybe with the do-while arrangement, a different placement of the shifts fixes the bank. Let me try:
- r5: two-statement shifts NOT in the do-while (just the casts in do-while)
- r6: shifts + a + cur in do-while (r4)
- r7: single-expression `div = div << 16 >> 16` (gives temp? or in-place?)

Let me check r7: `div = div << 16 >> 16` — earlier f4 gave the temp (score 2 with keepalive). Let me test it in the do-while.

Actually, let me think about why the two-statement shift shifts the caller-saved bank. The temp's absence changes local-alloc's qty numbering/order, which affects which regs the block-local temps get.

Hmm, what if I use the two-statement shift but ALSO keep a temp alive to restore the bank? E.g., the extendhisi2 temp exists but is unused? No.

Alternatively, maybe the caller-saved bank shift can be fixed by reordering the statements. Let me try a few:
- r5: shifts after cur
- r6: shifts before a
- r7: shifts in a separate do-while

Let me test.

Actually, let me reconsider: with the in-place shifts (no temp), the caller-saved bank shifts: cur→v1 (target a0), iVar4→a3 (target v1). The target has cur=a0, iVar4=v1.

Why does cur get v1 without the temp? Because v1 is free. With the temp (r1), v1 is busy at cur's birth? Let me check: in r1, the temp (sll v1) is born at position 14 and dies at 18 (the sra). cur is born at position 16 (between them). So the temp is live at cur's birth → v1 is busy → cur gets a0! That's why r1's cur=a0 (matching the target).

So the temp's presence is what makes cur=a0. And the temp itself needs to be in s0 (in-place).

So I need the temp to be in s0 (div's reg) instead of v1. The temp is local; it gets v1 (first free). If v0 and v1 were busy... v0=ang (live until position 17), v1=free.

Hmm, what if the temp's birth is BEFORE v0 becomes free? v0 holds ang until the andi(cur) at position 16. The temp is born at 14 (sll). At 14, v0 is live. So v0 is busy. v1 is free → temp gets v1.

To make the temp get s0: s0 must be the first free reg in reg_alloc_order at the temp's live range. Caller-saved regs (v0,v1,a0-a3,t0-t9) are all preferred. If they're all busy... no.

Alternatively, make the temp CROSS a call (so caller-saved are excluded → callee-saved s0). The temp is born after the jal, so it can't cross.

Hmm.

What if the sign-ext is computed BEFORE the jal (so the temp crosses the call)? Then the temp would get a callee-saved reg (s0, since s1 is taken by a? no, a is local? hmm). But the target has the sign-ext AFTER the jal.

Hmm.

OK, what if I use the two-statement shift (in-place, no temp) AND add a REAL use of ang between the sll and sra to occupy v1? The `cur = ang & 0xFFF` is between them in the target. If cur is computed between the shifts, then v1... hmm, cur would take v1, and then iVar4 gets a0? Not target.

Wait, target: cur=a0, iVar4=v1. So v1 must be free for iVar4 (born later). If cur takes a0 (because v1 is busy at cur's birth), then v1 frees after the temp dies, and iVar4 gets v1.

So the temp occupying v1 at cur's birth is ESSENTIAL. The temp must exist AND be in s0.

For the temp to be in s0: it's a local qty. Hmm, unless... the temp is tied to div (a global qty in s0) via copy preference. combine_regs: the extendhisi2 temp is connected to div by `(set temp (ashift div 16))` and `(set div (ashiftrt temp 16))`. If div were a pseudo with a qty, no tie. But div is global.

Hmm, what if I make div local? No.

Alternatively: what if the sign-extension uses a *named* temp variable in C, so I control its allocation? E.g.:
```
s32 dt;
dt = div << 16;
div = dt >> 16;
```
Then dt is a C variable. If dt is declared in the function scope, it's global-ish? If used only in block 0, local. local-alloc gives it v1 (same problem). Hmm.

But wait — if I declare dt and use it, maybe I can make it a `register`? No pin allowed.

Hmm.

What if dt is declared `s32 dt = div << 16;`? Same.

Hmm. The temp always gets v1.

Let me reconsider: is there a way to get the in-place shifts AND keep cur=a0? The two-statement shift (in-place) frees v1 at cur's birth → cur=v1. To prevent that, something else must occupy v1 at cur's birth.

What if the `cur = ang & 0xFFF` is computed BEFORE the div shifts? Then cur's birth is before the shifts; v1 is free → cur=v1. Hmm.

What if `a = a & 0xFFF` is computed after cur? Doesn't affect v1.

Hmm.

What if I introduce a real C temp that's live across cur's birth and dies before iVar4? E.g., the `t` variable? No.

OK, let me try a few placements of the two-statement shifts and see if any gives a lower score:
- r5: `div << 16; div >> 16` NOT in the do-while (f1 + shifts, score 28 earlier? no, f5 was 28; but f1 now with the do-while around the casts... wait f1 has the do-while around the div block, not the casts. r1 added the do-while around the casts.)

Let me be careful:
- f1 = nopin + do-while around the final if/else (divisions).
- r1 = f1 + do-while around the casts (div sign-ext, a mask, cur mask).

So r1 has TWO do-whiles.

Now let me try r1 with the two-statement shifts instead of `(s16)div`:
- r5 = r1 with `div = div << 16; div = div >> 16;`

Let me test r5 and some placements.

Actually, let me also try: `div = (s16)div;` but with div declared as a `s16` temp... hmm.

Let me test r5 (r1 + two-statement shifts), r6 (r1 with shifts placed after a), r7 (r1 with shifts placed after cur).

Let me create them.
