---
ts: 2026-11-06T05:32:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2QysWbgFgpw0ChX7ZlmN
---
No luck. Let me think harder about the priority.

Actually, wait. Let me reconsider whether iVar1's qty really is 8 refs/18 insns in the lever-free build. In a1's lreg: reg73 = 8 refs/18 insns. But is reg73 iVar1? Let me verify by checking the a1 RTL: reg73 is the pointer loaded from a0+0x20. Yes.

Hmm, 8 refs across 18 insns. To beat iVar2 (8 refs/8-10), iVar1 needs live < 10.

Hmm, what if we make iVar1's live range shorter by *not* using it across the arms? What if the arms use a *copy* of iVar1 that's loaded... no.

Alternatively — what if we split iVar1 into TWO variables: iVar1 for the CAST_SIGN and the arms; but the arms need the pointer. Hmm.

What if the two arms use different variables loaded from a0? E.g., in each arm: `((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk10 = ...`? That would add a `lw` per arm — extra instructions. Target has `sh v0,16(v1)` only.

Hmm.

What if iVar1's *refs* increase because the CAST_SIGN is written differently? CAST_SIGN(s16, iVar1, 0x10) expands to `*(s16 *)((iVar1) + 0x10)` — one use.

What if we add a redundant use that folds, e.g., `iVar1 = iVar1;`? Deleted by cse.

Hmm, what about making the *frame* different? No.

Let me reconsider the possibility that the target's iVar2 qty is smaller. In the orig (pinned), iVar2 = 8 refs/10 insns. In a1, iVar2 = 8 refs/8 insns. Why 8 in a1 vs 10 in orig? Because the asm insn is gone (2 insns less).

The priority in a1: 12. In orig: 9.6. Both > 5.33.

Hmm.

What if we could make iVar1's live range 10 insns? Its live range starts at the load (insn 21) and ends at the last use in the arms. The arms are far. Unless the first if's arms don't use iVar1 but a *reloaded* value...

Wait, actually, look at the source: after the arms, there's `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;`. This reload creates a new def. The first iVar1 dies at its last use in the else arm.

What if we move the reload to *before* the arms? No, semantics (the arms modify unk20's target).

Hmm.

What if we declare iVar1 as `s32` and do the pointer casts — same.

OK, let me look at this from yet another angle: maybe the answer is to make the copy `tmp = iVar2` where tmp is a **different size** (HImode, size 2) so tmp's priority halves, letting iVar2 take $2? No, target wants tmp in $2.

Hmm wait, actually — what if iVar2 takes $2 and tmp takes... no.

Let me re-examine the target: tmp (v0) is used in the arms: `addiu v0,v0,128`, `sh v0,16(v1)`, `sll v0,v0,0x10`. iVar2 (a0) only in the two tests. iVar1 (v1) in the stores and loads.

Alternative allocation possibility: what if tmp is in v0 because it's used in the arms, iVar1 in v1 because it's live longest, and iVar2 in a0 because it's short? That's the *natural* allocation if the priority order were tmp > iVar1 > iVar2. 

Given the formula, to get iVar1 > iVar2 we need to reduce iVar2's priority below 5.33.

iVar2: 8 refs, live 10 (orig). pri 9.6.
If iVar2 had 4 refs and live 10: 2*4*4/10 = 3.2 ✓.

So reducing iVar2's ref count to ≤ 6 would work (2*6*4/10 = 4.8 ✓). Currently 8.

What are iVar2's 8 refs? Let me look at the RTL: 
- insn 26 def (1)
- jump 29 use (1)
- insn 33 copy use (1)
- jump 38 use (1)
That's 4. But the dump says 8. Maybe REG_N_REFS counts each occurrence and the subreg/notes... Or the sign-extend chain (reg76/77) is separate. Hmm, maybe reg74 is also used in the second block? No, it's redefined there (a new qty).

Let me actually look at the .lreg dump for reg74 in orig2 — the dump shows "used 8 times". Maybe the jump insns count the reg twice (in the condition and something).

Anyway, empirically: what source changes reduce iVar2's refs? If the copy used a subreg (HImode) maybe... d2/d5 didn't help.

Hmm, let me look at the actual ref counts in a1 vs what we want. What if the copy is moved to use a *subreg* so it doesn't count as a use of the SI reg? E.g., `tmp = (s32)(s16)iVar2` — the subreg still references reg74.

I'm stuck on the priority. Let me consider the WALL route: I've done ~20 scored tries on item 2 (n1, a1-a4, b1-b4, d1-d6, e1-e3,e5 = 1+4+4+6+4 = 19). Need ≥30. I can do 10 more quick variants then record a WALL.

But wait — maybe there's a smarter idea. Let me reconsider the target's iVar1 live range: 18 insns in a1. Hmm, what if we *split* iVar1's first live range by reloading it just before the arms? E.g.:

```c
iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    tmp = iVar2;
    iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;   // reload inside the if
    if (iVar2 < 0) {
```
This would add a `lw` instruction (not in target). No.

What if the arms use `((Unkstruct_800B5CB8 *)a0)->unk20` directly and gcc CSEs it with the earlier load? The first load `iVar1 = unk20` and the arm's `*(s32*)(a0+0x20)` are the same memory. If gcc CSEs, the arm uses iVar1's register — same as now. If not, extra lw.

Hmm.

Let me try one more class of ideas: change the *order* of the two statements at the top:
```c
iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
```
What if we inline: `iVar2 = CAST_SIGN(s16, ((Unkstruct_800B5CB8 *)a0)->unk20, 0x10);` and keep iVar1 = ... separately? Then iVar1's live range starts at its def and... same.

What if iVar1 is defined AFTER iVar2? 
```c
iVar2 = CAST_SIGN(s16, ((Unkstruct_800B5CB8 *)a0)->unk20, 0x10);
iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
```
That's 2 loads (gcc would CSE them into one, but the order changes). Hmm, that might change the live ranges: iVar1 defined after iVar2, so iVar1's live range starts later → shorter! And the first load (for iVar2) is a temp.

Hmm, but the target's asm order is `lw v1,32(s0)` (iVar1) then `lh a0,16(v1)`. If the source computes iVar2 first from a fresh load, the asm might be `lw v1; lh a0,16(v1)` after CSE — same!

And iVar1's live range would start at the load (same insn). No change.

OK. Let me try another approach: what if we make iVar2's live range longer by making the second test occur AFTER the copy in a way that... it already is.

Hmm, hold on! Let me reconsider: in the target, does the second test really use iVar2 (a0)? Yes.

What if we could get the *target* by making iVar2 live longer: e.g., use iVar2 in the arms as well (in addition to tmp). For example:

```c
if (iVar2 < 0) {
    tmp += 0x80;
    ((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;
    if (0 < tmp * 0x10000) {
```
If we add `iVar2` into the expression in a foldable way... e.g., `tmp += 0x80;` could be `tmp = tmp + 0x80;` same.

What about the condition `if (0 < tmp * 0x10000)` — could be written using iVar2? No, changes value.

Hmm.

OK, let me try the "reference boosting" approach from moves.md: keepalive was a lever, but a *real* use that folds. What if we use iVar1 in a comparison that gcc folds? E.g., `if (iVar1 != 0 && iVar2 != 0)`. That changes the branch structure.

What if we use iVar1 in the CAST_SIGN twice: `CAST_SIGN(s16, iVar1, 0x10)` — hmm.

I think this is heading to a WALL (the class would be "local-alloc-priority" / greg-pri-refs). But let me try 10 more variants quickly to hit 30 tries, including some different structures.

Actually — WAIT. One more idea: what if we make the copy `tmp = iVar2` a *signed* copy through a different variable that the allocator treats as having size 2 but still SI... no.

Another idea: **declaration order** affects qty numbering (tie-break). If priorities tie, lower regno wins. iVar1 is reg73, iVar2 reg74. If we could make their priorities EQUAL (both 8 refs/live 12?), iVar1 wins. iVar2 live 12 would give 8. iVar1 live 18 gives 5.33. Not equal.

Hmm.

What about making iVar2 a `u8`? Then the load is lbu (wrong).

OK, what about making iVar1's live range end earlier by making the else arm's store use a *different* pointer variable that's also iVar1... no.

Let me look at the target asm once more for a clue about iVar1's usage: 
```
2a44 lw v1,32(s0)     iVar1 = unk20
2a4c lh a0,16(v1)     iVar2
...
2a68 sh v0,16(v1)     then arm store
2a84 sh v0,16(v1)     else arm store
2a94 lw v0,32(s0)     unk20 reload for the inner store
2aa0 lw v1,32(s0)     iVar1 reload
```
So iVar1 is live from 2a44 to 2a84 = ~16 insns. In a1 it was 18.

Hmm, in a1 the allocation was iVar1=a0, iVar2=v1. What if we just accept a1 and try to nudge? The diff a1: mine a0<->v1 swapped. If we could flip the two... 

What determines it: priority. a1's iVar2 pri 12 vs iVar1 5.33.

Let me try making iVar2 *live longer* by moving the copy after the second test:
```c
if (iVar2 != 0) {
    if (iVar2 < 0) {
        tmp = iVar2;
        tmp += 0x80;
```
Hmm, then tmp is used in the arm; the copy is in the arm. iVar2's live range is the same.

What if the copy is placed at the END of each arm (after the store)? Then tmp = iVar2 in each arm... two copies.

Hmm.

Let me try to *lengthen* iVar2's live range by moving its definition earlier and using it later — e.g., use iVar2 in the `skip2` block:
```c
skip2:
    if (*(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x10) == 0) {
```
No.

Alright, let me try the last batch of ~10 and then WALL:

f1: `iVar2 = CAST_SIGN(...); if (iVar2 != 0) { tmp = (s16)iVar2; ...` = a1 (already 18).
f2: a1 + `s16 tmp;`
f3: a1 + declaration order swap.
f4: a1 + hoist copy before if.
f5: a1 + `u16` cast.
f6: a1 with the second test on tmp.
f7: copy via a pointer: `s32 *pt = &tmp; *pt = iVar2;`? Might add insns.
f8: `tmp = iVar2;` with iVar1 declared `void *` (same).
f9: `tmp = iVar2;` + `tmp = (s16)tmp;`
f10: `tmp = iVar2 + (iVar1 - iVar1);`? combine folds.

Hmm, f10 could work: `tmp = iVar2 + (iVar1 - iVar1)` — folds to iVar2. No.

What about `tmp = iVar2 ^ 0;`? folds.

OK, let me think about whether there's an entirely different source that yields the target without the pin. 

Actually! Maybe the target's `move v0,a0` isn't a C-level copy at all: what if `tmp` is the *sign-extended* version and iVar2 is HImode, and gcc materializes the sign-extend as a move? E.g., if iVar2 is `s16` and the tests use the HImode value, gcc needs the sign-extended SI value for the arms (tmp). With iVar2 HImode in a0 (loaded by lh, already sign-extended in the register), the SI value tmp = sign_extend(iVar2) is just a copy `move v0,a0` if gcc knows the register is already sign-extended.

That's d1-ish but d1 used lhu. Why lhu? Let me look at d1's source: `s16 iVar2;` and `iVar2 = CAST_SIGN(s16, iVar1, 0x10);` — the assignment is HI = HI. gcc emitted `lhu`?? That's suspicious. Maybe because `CAST_SIGN(s16,...)` with iVar2 s16 → gcc sees the value only used in comparisons after truncation... Hmm.

Let me look at the target more carefully: the target's `lh a0,16(v1)` is a signed load. If iVar2 were HImode, the load is `lh` into an HI reg. Then `beqz a0` tests it. Then tmp = sign_extend.

d1 got `lhu v0,16(v1)` — maybe because in d1 tmp is also s16, so everything is HImode and gcc used lhu (unsigned?) Hmm, weird.

Let me try: iVar2 s16, tmp s32, copy `tmp = iVar2;` = b1 (merged, score 8).
Let me look at b1's asm to see if it used lh or lhu.

Actually, let me try the variant: iVar2 s16, tmp s32, copy `tmp = (s32)iVar2;` and ALSO make the second test use iVar2. That's d2 (score 8).

Hmm.

Let me look at b1's diff/asm to understand.
