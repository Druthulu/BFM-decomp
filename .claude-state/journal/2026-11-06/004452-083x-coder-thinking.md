---
ts: 2026-11-06T07:44:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mLYIexDGRmSo87XSlqWO
---
The keepalive is at line 466. The trace's @441 is line 441 (blank). @413 is `s16 o1[4]` — a width move on a struct field! "R12 width tmp0 u32->u16 @413": changing something at line 413 (o1 field) to u16. Hmm, "tmp0" is a generated temp.

The score-1 chain: R7 block @441 (wrap lines around 441 in a block) then R12 width tmp0 u32->u16 @413. Hard to reconstruct.

Let me take a different approach: use the engine's own search! delever_search has a --run mode, but that's a long campaign. Or I can use `--explain` on the lever-free body and then apply moves with `--path`. The --explain output lists "NEEDED sites" and the moves. Maybe I can use `--explain` with `--path "R7 block @441|R12 width tmp0 u32->u16 @413"` to see the residual (score 1) and its text? It says --path applies moves and prints the residual; but does it print the resulting text? Let me check the explain function. It prints class and diff, not text. Hmm.

Actually, the key realization: the score-1 candidate changes `s16 o1[4]` to u16? That seems odd. "width tmp0 u32->u16 @413" — tmp0 might be a temp introduced by R7 block? No.

Let me instead think about the real-C mechanism for making w3c get a0. Let me try variants directly.

Idea: the `L` struct's `o1[2] = 1` at line 472 and `gte_stsv((u16 *)w3c)` where w3c = L.o1. Hmm.

Another idea: the original might declare `w3c` as `void *` or `s32`, changing its class (pointer vs integer). r79 is not marked "pointer" in the alloc table, so w3c is an integer. Fine.

Let me try: split w3c into two variables (`u32 w3c; u16 *dst;`), etc.

Actually, let me focus on the register conflict: in orig, r77 (twicep) conflicts with r79 (w3c). The natural C must make twicep live across w3c's range. What if the original source used `twicep` in the GTE region? Wait — look at the source: `L.w38 = *(u32 *)twicep;` at line 440, then `w3c = *(u32 *)twicep;` at 442. What if the original did NOT have the `w3c` variable but instead:
```
L.w38 = *(u32 *)twicep;
...
L.w3C = L.w38;   // ???
```
No, target loads twicep twice.

What if the original had `w3c = *(u32 *)twicep;` and then LATER `L.w38 = w3c;`? Then the load happens early and the store of w3c to both L.w3C and L.w38... no.

Hmm, let me look at the target instruction order: insn 37 `lw v0,0(s5); sw v0,56(sp)` (L.w38), insn 40 `lw a0,0(s5)`. So two loads close together.

What if the original is:
```
L.w38 = *(u32 *)twicep;
w3c = L.w38;    // copy
```
Then only one load! But target has two loads. So no.

What if the original had `w3c = *(u32 *)twicep;` and `L.w38 = w3c;`? Then one load, and the store to L.w38 after. Target has `lw v0,0(s5); sw v0,56(sp)` — could be the one load stored to L.w38, then `lw a0,0(s5)` a second load. Two loads = two reads of twicep.

OK so the natural code reads twicep twice. And twicep must stay live past w3c. The only way: a third read or a use.

WAIT. Maybe I mis-identified which pseudo conflicts. r77 (s5) has 4 refs in orig (with keepalive) and 3 in w1. The keepalive adds 1 ref. In the natural target, r77 would have... the target's natural C might have 3 refs (two loads + initial load from stack = 3). So r77's liveness in the natural target is short (dies at 40). Yet w3c gets a0. So the conflict explanation may be wrong; maybe the difference is elsewhere: the keepalive's extra ref changes r77's *priority* (qty_compare uses refs), which changes the allocation ORDER, which changes which reg w3c gets.

Specifically, r79 (w3c) priority 3076 (4 refs, 26 live). r77 priority 689 (4 refs, 116 live) in orig; 681 (3 refs, 44 live) in w1. The global allocator orders allocnos by priority; r79 (3076) is much higher than r77, so r79 is allocated first and gets its choice. The conflict with s5: in orig r77 is live across r79's range → r79 can't take s5 → takes a0. In w1, r77 dies before → r79 takes s5.

But in the natural target, r77 dies at 40 too, yet r79 takes a0. So the natural C must have ANOTHER global pseudo in s5 live across r79's range, OR r79's priority/choice differs.

Hmm, maybe in the natural target, the value in s5 that conflicts with r79 is not twicep but something else that the allocator placed in s5, and the keepalive merely approximates it. The target binary's s5 is twicep (loaded at entry, used at 37/40). So s5 IS twicep.

Unless the natural C had a different variable in s5 that happens to be loaded from 180(sp) and used at 37/40 — that's twicep.

So the natural C must keep twicep live across r79's range with no instruction. How? A use that's dead but not eliminated before allocation... 

OH! Maybe the original has `L.w38 = *(u32 *)twicep;` and `w3c = *(u32 *)twicep;` but the SECOND read is actually at line 440 and the FIRST at 442, and the keepalive is... no.

Alternatively, the natural C might pass `twicep` to one of the earlier function calls? No, target's calls are before the load.

Let me look at the calls: `func_80013F3C(L.mat); RotMatrixZ(*angp, L.mat); func_8004914C(L.mat); func_800491AC(L.mat);` — 4 calls (matches "crosses 4 calls"). twicep is not passed.

Hmm, "crosses 4 calls" for r77: twicep is live from entry (loaded at entry) across the 4 calls to insn 40. That's why it's in s5 (callee-saved). Its live length 44 in w1. r79's range ~40..59. If r77 dies at insn 40 and r79 is born at 40, global-alloc might or might not conflict depending on birth/death ordering (2*insn vs 2*insn+1).

Let me check global.c's conflict test. In global-alloc, two allocnos conflict if their live ranges overlap at an insn. A value used at insn 40 (twicep) and defined at insn 40 (w3c) — does that overlap? The death is after the use; the birth is at the def. If death index = 2*40 and birth = 2*40, maybe they don't overlap, allowing reuse. In the target, they must overlap. 

The natural C might make w3c's birth EARLIER (before twicep's death). E.g., if the source computes `w3c` from a different expression before... no.

Wait, maybe the natural C has w3c born at insn 39 (one earlier), e.g. the load scheduled one insn earlier. Target: `lw v0,0(s5)` at 37 (L.w38), `lw a0,0(s5)` at 40. Hmm, if the natural source had `w3c = *(u32*)twicep;` BEFORE `L.w38 = *(u32*)twicep;`, then w3c's birth would be at 37 and twicep's use... still at 37.

Let me try swapping lines 440 and 442 (the two twicep reads): `w3c = *(u32 *)twicep;` before `L.w38 = *(u32 *)twicep;`. The bytes might still match (sched1 orders them). Let me test.

Also try: merge them as `L.w38 = w3c = *(u32*)twicep;`? That's one load; no.

Let me try a batch of real-C variants for item2:
1. swap the two twicep reads.
2. `L.w38 = *(u32*)twicep; w3c = L.w38;` (one load) — probably wrong bytes.
3. separate pointer `u32 *tw = (u32*)twicep;` used twice.
4. `w3c = *(u32*)twicep; L.w3C = w3c;` moved earlier.
5. declare `u32 w3c; u32 w3d;` split.
6. `L.w3C = *(u32*)twicep;` (third read) and drop the early w3c for L.w3C.
7. Use `twicep` again after GTE: `L.w3C = w3c + (twicep == 0);`? adds code.
8. Make `w3c` a `void *` or `u16 *` and cast.
9. Change `w3c = (u32)L.o1;` to `w3c = (u32)&L.o1[0];` (same).
10. Use `L.o1` array decay.

Let me test a batch quickly.
