---
ts: 2026-11-06T07:46:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RlAqfdlI0yuI7SR72MjT
---
Now it's clear:
- orig: `79 conflicts: 79 2 3 12 13 14 18 19 21 29` — includes 21 (s5). So r79 can't take s5; gets 4 (a0). `79 in 4`.
- w1: `79 conflicts: 79 2 3 12 13 14 18 19 29` — no 21. Plus `79 preferences: 21` (copy preference for s5). So it gets 21 (s5).

The conflict with 21 comes from r77 (twicep in s5) being live across r79's range. In orig, r77 has 4 refs/live 116; in w1, 3 refs/live 44.

So to make r79 conflict with 21 in real C, we need twicep (r77) to be live across r79's range. That means a real use of twicep after r79's birth (insn 40) — at least until r79's death (insn ~72).

The natural C MUST have such a use. The target binary shows no s5 use after 40... but a use could be at insn 72+ where s5's value is dead? No, a use would appear.

Hmm, wait: maybe the natural C's r77 is NOT twicep but a DIFFERENT value also in s5. In the target binary, s5 holds twicep from entry to 40. But maybe the compiler assigned the *pointer* `twicep` to s5 AND a different variable also to s5 (same register reused after 40). The conflict in the natural allocation could be between r79 and a *different* allocno that happens to be in s5. But the target's s5 after 40 is dead (no use), so no other value is in s5 after 40.

Unless the natural C has a value live in s5 from 40 to 72 that is never used (dead after allocation but live at allocation time). What value could be live but unused? A variable assigned but its use is in a dead branch? The function is straight-line + if? There's no if in this function (the body has no branches except the final call). Let me check: the body has no if. So all uses are real.

Alternatively, the natural C might have a value that the compiler keeps live because of an asm in the ORIGINAL? No, original is pure C.

Let me reconsider: maybe in the natural C, the *four calls* at the top use twicep, extending its liveness differently? No, the calls are before insn 30.

Hold on — maybe the natural C has twicep used at the END: `func_800174DC();` at line 477 — does it take twicep? The target's final call `jal func_800CAE0C` with `sh v0,48(sp)` in the delay slot; no a0 setup → no args. So no.

Hmm, what if the natural C's `L.w38 = *(u32 *)twicep;` is not at line 440 but LATER, and the target's store at 37 is actually... no.

Let me look at the score-1 candidate the engine found: "R7 block @441|R12 width tmp0 u32->u16 @413". A block at line 441 (blank line between L.w38 and w3c) and a width change at line 413 (o1 field). Maybe "tmp0" refers to a temp created by R7 block? Confusing.

Let me try the `do{}while(0)` block around the w3c load and the v48 stores, and width changes. C0535 says do-while splits cse1 EBB. Maybe wrapping the w3c load + stores in a block changes the liveness/priority.

Actually, let me reconsider the mechanism from the other direction: v5_split got the loaded value into a0! Because splitting reduced its live range/priority such that it got a0. Then only the pointer var needed a0. What if I make the pointer var ALSO get a0 by making its range start at the load's death and reusing the same pseudo? In v5, w3d got v1. Why v1 and not a0? Because at w3d's range (60..72), a0 is still live? w3c (a0) dies at 59 (`sw a0,60(sp)` uses it). w3d born at 60. If they're separate pseudos, a0 is free at 60. But w3d got v1. Hmm, v1 is used for something in that range? Let me look at the diff: mine v5 has `addiu v1,sp,16` at 59 (before the store?) and target `addiu a0,sp,16` at 60. The diff shows delete mine[59] and insert mine[61]. So in v5, the pointer computation happens at insn 59 (earlier) in v1, while target at 60 in a0. This is an ORDER difference too.

What if the source keeps the single variable w3c (so reuse is natural) but makes the loaded value's range shorter by splitting only the LOAD: e.g., `L.w3C = *(u32*)twicep;` then `w3c = (u32)L.o1;`? But target keeps the loaded value in a register until the store, so it's named.

Alternatively, what if the original used a single variable but declared it `u32 w3c` and the LOAD is `w3c = *(u32*)twicep` — that's the base. The only way to get a0 is the conflict. 

Let me try to get the conflict by extending twicep's live range with real C that produces NO extra instruction: a use of twicep whose value is already loaded and can be folded. For example:

```
L.w38 = *(u32 *)twicep;
w3c = *(u32 *)twicep;
...
L.w3C = w3c;
w3c = (u32)L.o1;
```
What if we add `L.w3C = *(u32 *)twicep;` AND remove the `w3c` loaded-value variable, i.e.:
```
L.w38 = *(u32*)twicep;
...
w3c = *(u32*)twicep;   // third read at line ~451
L.w3C = w3c;
w3c = (u32)L.o1;
```
Then twicep is used at 40 and at ~59, keeping it live across r79's range. But the target's load is at 40, and this would put a load at 59. Two loads total? The source has L.w38 read (load at 37) + w3c read (load at 40). If we move the w3c read to 451, the loads would be at 37 and ~59. Target has them at 37 and 40. Sched1 might hoist the second load to 40? The second load is independent; sched1 could schedule it early. Actually in target, the second load at 40 is right after the first. If the source has it at line 451 (after several stores), sched1 might hoist it up to fill a slot. Possible!

Let me test v11_late_w3c (already did: score 18, 134 ins — it emitted 2 extra insns, so no).

What if we keep the load at 442 (line 40) AND add a third read that is CSE'd to the same value without an instruction? A third read `L.w3C = *(u32*)twicep;` would be a second load (cse might CSE it with the w3c load if no aliasing store intervenes; but there are stores to L between). cse can't.

Hmm, what about using twicep in a pure computation that folds: `w3c = *(u32*)twicep; ... if (twicep) ...`? adds a branch.

What about `L.w3C = w3c + (twicep - twicep);`? That's an identity launder and likely folded.

What about passing twicep to the GTE macro? gte_stsv takes a pointer; the source passes w3c/L.o1. No.

Let me look at the target's r77 liveness in the ORIGINAL binary via the RTL of a candidate that scores 0 (orig with keepalive). In orig, r77's live length is 116 because of the asm. The target's natural r77 live length is unknown; it could be 44 (like w1) and still conflict if the conflict is at the boundary. Let me check: in w1, r79's conflict list lacks 21. r79's range [40,72]. r77's range [entry,40]. Do they overlap at insn 40? Apparently not (no conflict). In the target, they must overlap, so r77 must extend beyond 40.

Let me examine the target's actual register allocation by looking at the target binary's callee-saved usage: s5 is saved/restored, used at 37,40. Its value is dead after 40. So the target's r77 live length is ~44. Yet the target's w3c is a0. So the conflict is NOT from r77! Then why does orig (keepalive) conflict with 21?

Maybe the conflict in orig is from a different allocno in 21. In orig, hard regs used include 21 for r77. The conflict list for 79 includes 21 because r77 is live across 79's range in orig. In the TARGET (natural), r77 is NOT live across, so 79 should get 21 (s5) — but the target has a0! So the target's natural allocation must differ in another way: r79's preference/conflicts differ.

Wait, maybe in the natural target, r79 is not a single allocno. Maybe the natural C has TWO separate variables (loaded value + pointer), each with its own allocno, and BOTH get a0 (one after the other, coalesced by reuse). In w1 (single variable), r79 is one allocno that prefers s5. In the natural C, the loaded value is a short-lived allocno with high priority that gets a0 (like v5), and the pointer is another short-lived allocno that also gets a0 (reusing the dead a0). v5 got the loaded value a0 but the pointer v1. Maybe with a different spelling the pointer also gets a0.

In v5, w3d (pointer) got v1. Why? Let me look at the conflict/preferences for v5. Let me dump v5's alloc table. Maybe the pointer allocno conflicts with a0 because w3c's death and w3d's birth ordering. Let me check.

Actually, the diff for v5 showed mine: `addiu v1,sp,16` at insn 59, target `addiu a0,sp,16` at 60. So v5's pointer computation is one insn EARLIER and in v1. This is an order/live-range difference. If I could delay w3d's birth by one insn, it might reuse a0. The target's `addiu a0,sp,16` comes after `sw a0,60(sp)`. In v5, `addiu v1,sp,16` comes BEFORE `sw a0,60(sp)` (at 59 vs 60). Source order in v5: `L.w3C = w3c;` then `w3d = (u32)L.o1;` — so the addiu should come after the store. But sched1 reordered it before? The diff says mine[59] addiu, target[59] store, mine[61] nothing, target[61] addiu. So mine has addiu at 59, store at 60? Let me see the full mine listing. Let me dump v5's object.

Actually, let me first check: maybe the fix is to make the pointer variable a separate `u16 *dst` (v7) but ensure it gets a0. v7 same diff.

Let me get the alloc table for v5 to understand the pointer's allocation.
