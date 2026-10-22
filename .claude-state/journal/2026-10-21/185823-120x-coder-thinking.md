---
ts: 2026-10-22T00:58:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YNlCMgCsEitzSuqfsgXT
---
w13 (t=u16, v=u16): the copy still dissolved (`andi s8,v0,0xfff` — the mask computed directly into s8), but the u16 t caused a `sll a0,s8,0x10; sra a0,a0,0x10` (the sign extension of t for the call arg) ✗.

So the u16 trick doesn't preserve the copy here.

Hmm. So in 8003DF8C the copy survived but in 80181E64 it doesn't. The difference must be the source being a global (in 8003DF8C the source is the parameter pseudo, live across calls).

Hmm, wait, actually, hmm: in 8003DF8C, was it really the u16 that saved the copy? Let me verify: q14 (u32 i/j) = 34 and q15 (u16 i/j) = 0 ✓ — so yes, the u16 made the difference.

Hmm! So an HI←SI copy DOES escape cse in 8003DF8C. Why not in 80181E64?

Hmm! Difference: in 8003DF8C, the copy's SOURCE is the parameter pseudo. Hmm, in gcc, the parameter's pseudo is a GLOBAL (live across calls). And in 80181E64, the source v is a LOCAL.

Hmm, so the rule: cse's copy propagation (the equiv table) applies only to LOCAL pseudos? Hmm, that doesn't sound right either.

Hmm, hmm! Alternative explanation: in 8003DF8C, the copy `i = arg0` — arg0's pseudo is a global whose value is in a callee-saved reg; the copy into the u16 pseudo i is a "reload"-ish copy that gcc keeps because the global's reg is fixed and i's reg is separate ✓ — and cse's equiv propagation... hmm.

OK, empirically: the copy survives when the SOURCE is a global. Let me use that:

For 80181E64: I need the copy's source to be a global. The masked value `v` is dead after the copy ✗.

Hmm! BUT: what if I copy in the other direction — the source is a global and the destination is the value used later? I.e.:
```c
t = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;   /* t = the masked value; the mask is computed into t's reg ✗ (no copy) */
```
✗.

Hmm. What if the masked value comes from a global? Hmm.

Hmm, hold on! What about the ORDER: the target's copy is `move s8,v0` where v0 holds the masked value. In the target, the masked value is in v0 (a caller-saved temp) — so the source of the copy is a LOCAL (v0, a temp) ✗ hmm, that contradicts my "source must be global" theory.

Hmm! In the target, the mask is computed into v0 (a temp reg) and copied to s8. So the source (v0) is a local temp and the copy survived ✓.

Hmm!! So in the original compiler, a local→global copy survived.

OK so the difference must be gcc-specific: in gcc 2.7, the copy `t = v` where v is a local that's dead after → cse propagates v's value into t's uses → the mask is computed directly into t's reg.

Hmm, and in 8003DF8C, `i = arg0` — arg0's pseudo is NOT dead after (it's used later in `func_80041354(arg0 | (arg1 << 8), ...)`) → so cse CAN'T propagate arg0's value into i's uses?? Hmm, it CAN (arg0 isn't modified) — but the propagation would make i's uses read arg0's reg. Hmm, and arg0's reg is a callee-saved (s3) while i is... hmm.

AH, I think I've got it: cse's copy propagation is BLOCKED when the source is live across a call (i.e. the source is a global in a callee-saved reg) and the destination would be in a caller-saved reg — because then propagating would make the value live in a caller-saved reg across the call ✗ invalid. So cse keeps the copy ✓✓✓.

YES! That's the rule: the copy can't be propagated if the source's value must survive across a call (the source is a global) but the destination is a local.

Hmm, hmm. In 80181E64: `t = v` — the source v is dead after the copy → no call-crossing → cse propagates ✗.

So to keep the copy in 80181E64, the SOURCE must be live across a call. The source is the masked value... which is dead after the copy.

Hmm!! Unless the source is a value that IS live across a call. Hmm, what if the copy's source were the PARAMETER arg1 (live across the calls ✓)? But the copy is of the MASKED value ✗.

Hmm, hmm.

Hmm, what about this: the target's `move s8,v0` — maybe the source v0 is the value BEFORE the mask?? No: the target computes `andi v0,v0,0xfff` then `move s8,v0` → the source is the masked value ✓.

Hmm, so in the target the masked value was in a temp (v0) and copied to s8 — and the temp is dead after. gcc 2.7 would merge ✗.

⇒ For gcc 2.7.2, the copy survives only if the source is live across a call.

Hmm, so the masked value must be live across a call. In 80181E64, is there a call before the copy? No — the copy is at the very top, before any call.

Hmm!! But wait: what if the copy were moved AFTER a call? Semantically the masked value must be stored to memory before the calls... hmm, the store `*(s16 *)(arg1 + 0x100) = t;` is before the calls, and the loop uses t.

Hmm, what if the source of the copy were the value that's live across the calls — i.e. `t` itself! Hmm: what if the copy were `x = t` where t is the global? That's the reverse.

Hmm, the target's structure: the mask → v0 (temp) → copy → s8 (t, the global). The copy's source (v0) is the temp. Hmm, but the temp's value... hmm.

Hmm, hmm! Maybe in gcc 2.7 the copy survives if the DESTINATION is live across a call and the SOURCE is not! I.e. cse propagates the source's value into the destination's uses only if the destination's uses are... hmm, no: cse propagates dst→src (the destination's uses become the source's).

Hmm! Let me re-think: cse propagates `dst = src` by replacing the uses of dst with src — that's only valid if src's value is still available at those use points, i.e. src is not modified AND src's register is not clobbered. If src is a local in a caller-saved reg and the dst's uses are after a call → invalid! So cse must NOT propagate in that case.

In 80181E64: `t = v` — dst = t (a global, in s8), src = v (a local, in some caller-saved reg). The uses of t are AFTER the calls (in the loop) → so propagating t→v would be INVALID (v's reg is clobbered by the calls) → cse should NOT propagate ✓✓✓!!!

But empirically it DID propagate (the mask went directly into s8). Hmm!! Because the propagation happened in COMBINE (not cse), and combine doesn't know about the call-clobbering.

Hmm. Hmm! Combine's copy propagation: combine works within a basic block. The copy `t = v` is in the entry block, and t's uses are in the loop block → combine wouldn't propagate across blocks. Hmm.

Hmm, so the propagation must be cse's (cross-block). And cse should have refused (v's reg is clobbered).

Hmm, unless v's reg IS a callee-saved one (then propagating would be valid but would change the allocation). Hmm! In my candidate, the mask is computed into s8 directly, so there's only one pseudo.

Hmm, hmm. Hmm, what if the order of the passes is: combine (which propagates within the block) then cse? The copy `t = v` is in the entry block; t's uses (the store `sh t,256(a1)`) are ALSO in the entry block! → combine propagates within the block → the store's use of t becomes v's use ✓ → then v's live range extends to the store ✓ and the copy is dead → removed ✓. And the loop's uses of t (in another block) — combine doesn't touch them ✓ (they still read t's pseudo, which now holds... hmm, t's pseudo = v's pseudo after the propagation ✓).

So: the propagation happened because the STORE's use of t is in the same block as the copy ✓.

⇒ If the store's use were in a DIFFERENT block, combine couldn't propagate → the copy would survive ✓✓✓!

How to move the store into a different block? Hmm, the store `*(s16 *)(arg1 + 0x100) = t;` is right after the copy. Hmm, if there were a branch between them... hmm, that changes the code.

Hmm! But hold on: what if the copy is in the same block and the store is in another? Hmm.

Hmm, alternatively: what if the value v is used in the same block (so that the copy is needed)? Hmm.

Hmm, hmm! Let me reconsider: in 8003DF8C, the copy `i = arg0` — i's uses: `func_80040DE8(i | (j << 8), 1, 1, 1)` — in a nested block (the if/else inside the loop) → NOT in the same basic block as the copy (which is at the top) → so combine couldn't propagate ✓✓✓ and cse couldn't either (the source arg0 is live across calls) → the copy survived ✓✓✓.

And in 80181E64, the store `*(s16*)(arg1+0x100) = t;` is in the SAME block as the copy → combine propagates ✗.

⇒ LEVER: move the store's use of t out of the copy's basic block, OR make the copy's source live across a call.

Hmm! In 80181E64, the copy `t = v` is at the top and the store is right after. What if the source `v` were live across a call? Hmm, v is dead after.

Hmm, what if the ORDER were: the copy first, and the store later (after some calls)?! The store `*(s16 *)(arg1 + 0x100) = t;` must happen before the loop (semantically it stores the initial value). Hmm, but the loop modifies t. Hmm, so the store must be before the loop.

Hmm, but the loop is AFTER the setup (mp = D_801BF5CC etc.) — those are loads, not calls. Hmm, the first call in the function is inside the loop.

Hmm! So there's no call between the copy and the store ✗.

Hmm. Hmm, but what if the copy were moved to just before the loop (i.e., after the setup)? Then between the copy and the store... hmm, the store must be before the loop.

Hmm, hmm. Let me re-read the source:
```c
    {
        v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
        t = v + zr;
    }
    *(s16 *)(arg1 + 0x100) = t;
```
Hmm! The block `{ ... }` — with the block, the copy is inside a nested block. In gcc, a nested block doesn't create a basic block by itself (unless there are branches).

Hmm, what if the block contained a BRANCH? E.g.:
```c
    {
        v = ...;
        if (v != v) { }     /* hmm, a fake branch */
        t = v;
    }
```
✗ (a fake branch).

Hmm.

OK, let me think about 800D0D7C with the "combine within a block" theory:
- `r = now` (the copy) and `now` is used later in the same block (`(r & 0xFF) >= ...` and `now & 0xFF00` in the branches). The copy's destination r is used in the same block (`r & 0xFF`) → combine propagates ✗.
- The target has the copy surviving.

Hmm, so for 800D0D7C, the copy's destination r IS used in the same block (the comparison) → combine propagates ✗.

Hmm!! But hold on: in 8003DF8C, the copy's destination i was used only in nested blocks ✓.

⇒ For 800D0D7C, r's first use is in the same block → combine propagates.

Hmm, unless r's uses were all in nested blocks. The condition `if ((r & 0xFF) >= ((u32)arg1 & 0xFF))` is in the entry block ✗.

Hmm, hmm.

OK, so for 800D0D7C the copy `r = now` needs `now` to be live across a call (there are no calls) OR r's uses to be in nested blocks (they're not).

Hmm. Hmm, so 800D0D7C is hard. Hmm.

BUT: the `h = arg0` copy DID survive with h as u16 (w13 showed `move a3,a0` ✓)! Because h's uses are in nested blocks (the second if) ✓ and arg0 is live across... hmm, there are no calls in 800D0D7C! Hmm, but the copy survived anyway (the u16 mode change made it an HI copy that combine doesn't propagate? hmm).

So: the u16 trick worked for `h = arg0` ✓ (the destination h's uses are in nested blocks → combine can't propagate) but not for `r = now` (r's uses are in the same block).

Hmm! So for `r = now`: what if r's first use were in a nested block? The condition `if ((r & 0xFF) >= ...)` — hmm, what if the condition were computed differently, e.g. via a temp? Hmm:

```c
    if (((now) & 0xFF) >= ((u32)arg1 & 0xFF)) {     /* hmm, uses now instead of r ✗ changes the semantics */
```
Hmm, but semantically `r == now` at that point (r is a copy of now) ✓!! So using `now` in the condition is semantically identical ✓✓.

Then r's uses would be only in the branches (nested blocks) → the copy `r = now` survives ✓✓✓!

Hmm!! But the target's code reads `andi v0,a2,0xff` (a2 = r, the copy) for the comparison ✗ — the target compares the COPY (a2), not the original (a3).

Hmm!! So the target's comparison uses the copy ✓ (that's the point of the opaque copy: the comparison reads a2).

Hmm. So the source spelling must use `r` in the comparison ✗ (it must be r, not now).

Hmm, but wait: if the source used `now` in the comparison, gcc would compute the comparison from `now` (a3) → `andi v0,a3,0xff` ✗ (the target has a2).

Hmm. Hmm, unless the copy is preserved and the comparison reads r ✓ — that's what we want.

Hmm, so: the source says `if ((r & 0xFF) >= ...)` and the target's code reads the copy's reg (a2) ✓. For gcc to keep the copy, the propagation must be blocked. The propagation is blocked if r's uses are in nested blocks OR the source is live across a call.

Hmm, the comparison is in the entry block ✗.

Hmm, hmm! What if the whole if/else were inside a block that gcc treats as a nested scope? Hmm, blocks don't create basic blocks.

Hmm, what if the comparison were computed in a nested block? E.g.:
```c
    if (((r & 0xFF) >= ((u32)arg1 & 0xFF))) {
```
Hmm.

Hmm, hmm! What if I introduce a block for the condition via a helper variable?
```c
    u32 c1;
    c1 = r & 0xFF;      /* hmm, that's another copy */
    if (c1 >= ((u32)arg1 & 0xFF)) {
```
Hmm, that adds a pseudo (c1) → the condition would read c1's reg ✗ (the target reads a2).

Hmm.

OK. Let me step back and consider the time budget. It's ~19:30. I've been going ~3.5h. The new rule requires ≥30 scored tries and ≥20 min per WALL item. Let me check the counts:

- func_801415C0: 7 + 30 (q01-q30) = 37 ✓; time 16:08-19:2x = way over 20 min ✓.
- func_800D0D7C: 10 + 20 (q) + 16 (w01-w16) = 46 ✓; time 17:49-19:2x ✓.
- func_8012944C: MATCH ✓.
- func_80180480: 27 tries → need ≥30. Let me add a batch.
- func_8003DF8C: 1 + 30 (q) = 31 ✓; time 18:14-19:2x ✓.
- func_80181E64: 3 + 28 (q) + 16 (w) = 47 ✓; time ✓.
- func_800D2650: 6 tries → need ≥30. Let me add a batch.

And the new results: func_8003DF8C is now a MATCH (score 0) ✓✓✓!

So I need to:
1. Write win.c for func_8003DF8C (the q15 body) and verify.
2. Update results.tsv (8003DF8C → MATCH, and the tries counts for all).
3. Update moves.md (the 8003DF8C line → MATCH with the u16 lever).
4. Update the notes.md for 8003DF8C.
5. Add ≥30 tries for func_80180480 and func_800D2650.
6. Update the log.

Let me also try the u16 trick on func_800D2650 (the byte/const locals: bVar1 is already u8; sVar2 is short) and func_801415C0 (the allocation).

Let me first do the 8003DF8C win.c + verification, then the remaining batches.

Let me write win.c for 8003DF8C = q15's body.
