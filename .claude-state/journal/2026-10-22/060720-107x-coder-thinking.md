---
ts: 2026-10-22T12:07:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_va0w56QSEIUTXNkgqoUK
---
So `unk20` is `s32` (line 22: `/* 0x0020 */ s32 unk20;`). So `e` is an s32 holding an address.

OK. So the alias trick with a char* cast doesn't change the tree's type in a way that matters.

Let me now think about a DIFFERENT approach for keeping the load in each arm:

**The target's case0 arm:**
```
2040: lw a0,32(s0)     <- func_8001C810's first arg
2044: lui a1,0x0
2048: addiu a1,a1,0
204c: jal func_8001C810
2050: nop
2054: li a0,409
2058: lw v1,32(s0)     <- e's load
205c: j 2084
2060: li a1,2
```
So in case0 there are TWO loads of unk20 (a0 for the call, v1 for e).

And the source is:
```c
case0:
    func_8001C810(((Unkstruct_800B5CB8 *)s0)->unk20, (s32)D_8019CDBC);
    callarg0 = 0x199;
    e = ((Unkstruct_800B5CB8 *)s0)->unk20;
    argmode = 2;
    goto shared;
```
TWO loads of unk20 in the source! And GCC produced 2 loads (a0 and v1) — because the CALL clobbers a0! So the first load's value (in a0) is consumed by the call, and the second load (for e) is a separate load.

Ahh, so in the source there are 2 separate `unk20` reads, and GCC must load twice (the call clobbers the register).

**AND IN MY CANDIDATE**: the same source → 2 loads in case0? Let me check the candidate's disassembly. Hmm, the diff showed my candidate missing the `lw v1,32(s0)` at 36 (the case0 arm) but having `lw v1,32(s0)` at 45.

Hmm, where's my case0's first load (a0)? It must be there (the call needs it).

So in mine: case0 = [lw a0,32(s0); ...call...; li a0,409; j 207c] and the e load is NOT in case0 — it's in the shared block (at 45).

**So GCC moved case0's e-load into the shared block.** That's the "sinking".

WHY? Because `e` is a pseudo with 2 sets (case0 and case1) and the JOIN uses it. GCC's local-alloc/reload: a pseudo with 2 sets in 2 blocks and a use in the join → both sets must write the same register. So both loads write v1. That IS the target's form!

So why did my candidate produce only ONE load (in the join)?

Hmm! Maybe because in my candidate, the case0 and case1 assignments were CSE'd into ONE pseudo with 1 set... Hmm.

**AH WAIT — maybe the difference is the SOURCE ORDER of the e-load relative to the call!** In the original, `e = unk20` comes AFTER the call in case0, and after the call in case1. In my candidate... the same source. Hmm.

Hmm, so why the difference?! The ONLY source difference between orig.c and my base is the removal of the two asm lines!

So the asm in case1 (`__asm__("" : "=r"(e) : "0"(e));`) makes case1's `e` a distinct definition → so `e` has 3 definitions → local-alloc can't merge → the loads stay.

And in case0, the e-load stays because... hmm, in my candidate the case0 load sank to the join. Hmm, why would case0's load sink but not case1's?

In my candidate (w01's diff): the target has lw at 36 (case0) and lw at 45 (case1's e load, at index 45?). Hmm, let me re-read the w01 diff:

```
  replace mine[36:37] target[36:38]
       36  j	207c | lw	v1,32(s0)
       37  --      | j	2084
  insert  mine[44:44] target[45:46]
       44  --      | lw	v1,32(s0)
  delete  mine[45:47] target[47:47]
       45  lw	v1,32(s0) | --
       46  nop       | --
```
So mine[45] = `lw v1,32(s0)` and mine[46] = nop. The target[45] = `lw v1,32(s0)`.

Hmm, so both have a `lw v1,32(s0)` at 45. And the target has an EXTRA one at 36 (in case0).

So: mine has ONE e-load (at 45, in the shared block) and the target has TWO (at 36 in case0 and at 45 in... hmm, where is 45? Let me figure out: the target's layout is
```
36: lw v1,32(s0)   (case0's e load)
37: j 2084
38: li a1,2   (delay)
39: lw a0,32(s0)  (case1's call arg)
...
44: li a0,409
45: lw v1,32(s0)  (case1's e load)
46: li a1,3
47: lw v0,4(v1)   (shared)
```
So the target's 45 = case1's e load. ✓.

And mine: 45 = the e load (in the shared block, since it's used by the shared block) and 46 = a nop.

Hmm, so mine has ONE load at 45 and the target has TWO loads (36 and 45).

So mine's load at 45 is in the shared block (or in case1?). Hmm. Mine: 36 = `j 207c` (case0's jump to the shared block), so mine's case0 arm has NO e load. And mine's case1 arm... the shared block is at 207c? Hmm, mine's `j 207c` — so case0 jumps to 207c. And the shared block starts at 207c? Then mine's 45 = `lw v1,32(s0)` would be at 0x... hmm, the indices are instruction indices, not addresses. Let me not over-interpret.

**Conclusion: mine is missing the case0-arm e-load.** In the target, case0 has its own e-load.

So GCC sank case0's e-load into the join but kept case1's? Hmm, or GCC eliminated case0's load as redundant (CSE with case1's) and kept case1's.

**AH, THAT'S IT**: CSE eliminated case0's load (redundant with case1's, same MEM) — but they are in different blocks, so a forward CSE would be invalid... unless the value is forwarded to the join.

Hmm, GCC 2.7's cse.c DOES do this: "cse forwards only within a block" per the cookbook. Hmm.

OK, alternatively: **jump.c's `jump_combine`** — hmm.

Hmm, let me think about it from the ORIGINAL's side: the original's case1 has an asm → the e value in case1 is the asm's output → NOT the same as case0's load → no CSE → both loads stay. And the register allocator gives v1 to both (the asm's output in case1 is coalesced with the load).

So: **in plain C, to prevent the elimination of one of the two loads, the two arms' e-loads must not be CSE-able.** My char*-vs-struct test didn't help → GCC CSE'd them anyway (the MEM is the same after expansion).

**NEW IDEA: make the two arms' e-loads have DIFFERENT MEMs that still produce the same value.** Impossible... UNLESS the address differs but the value is the same. Hmm.

**NEW IDEA: prevent the elimination by making one of the loads a different WIDTH or a different access.** E.g. case0: `e = *(s32 *)((u8 *)s0 + 0x20);` and case1: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — tried (w04-w11), no effect.

Hmm, so CSE folded them anyway. GCC's cse folds MEMs with the same address and alias set... the alias set differs (char* vs struct) but the MEM's alias set is what matters. Hmm, GCC's `immutable`/`equiv` check for MEMs requires the same alias set? Actually CSE's `equiv_find` for a MEM compares the address and the alias set. With different alias sets, they shouldn't be equivalent... but the fold happened.

Hmm, maybe the folding isn't CSE but the REGISTER ALLOCATOR + local-alloc's "reg_n_sets" logic: e has 2 sets; local-alloc might merge the two definitions if it can prove they're the same value ("local-alloc.c:1016-1064" keeps a constant off REG_EQUIV's doubled live length — interesting!).

**"keeps a constant off REG_EQUIV's doubled live length (local-alloc.c:1016-1064)"** — hmm, this says: a variable with 2 identical sets has a "doubled live length" in REG_EQUIV. So local-alloc handles the 2-set case.

Hmm, so in the plain-C case, `e` has 2 identical sets → local-alloc's REG_EQUIV sees the doubled live length and... merges them? That would explain the single load!

And the ASM gives `e` a 3rd set (a different value) → no merging → 2 loads.

**SO: to keep 2 loads, `e` must have a definition that is NOT identical.** In plain C, we could make case0's e assignment differ in a way that produces the same value but a different expression... tried.

**OR: give `e` a 3rd definition somewhere** — e.g. in the `tail:` block there's already `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` (line 71)! So `e` has 3 definitions: case0, case1, and tail. Hmm! And in the target, the tail's load is at 2108: `lw v1,32(s0)`.

So in the target there are THREE loads of unk20 for e: case0's, case1's, and tail's. And in my candidate: case0's is missing.

Hmm! So the target has 3 e-loads and mine has 2 (case1's + tail's, or the join's + tail's).

Hmm, so what makes case0's load survive in the target? The asm in case1! Because with the asm, case1's e is a different value → local-alloc can't merge case0's and case1's → 3 separate loads.

Hmm, but then in the target, are the 3 loads' values all merged into one register v1? The target: case0's load → v1, case1's load → v1, tail's load → v1. All in v1! So they're the same register but separate loads.

Hmm, so local-alloc gave v1 to all three (they're in exclusive blocks) but each block has its own load.

**SO: to get the same in plain C, I need `e`'s three definitions to NOT be mergeable into fewer loads.** The asm makes case1's different.

**IDEA**: make the TAIL's `e` assignment differ (it's in a different block anyway) — hmm, the tail's load is at 2108 which is present in mine too.

**IDEA**: What if case0's `e` load is expressed with a DIFFERENT (but equivalent) address computation that GCC can't CSE with case1's? E.g.:
- case0: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;`
- case1: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — identical.

To differ: use a different POINTER variable for case1: e.g.
```c
void *s1 = s0;   /* a copy */
...
case1: e = ((Unkstruct_800B5CB8 *)s1)->unk20;
```
Then the address is `s1 + 0x20` where s1 = s0 (a copy). GCC would copy-propagate s1 → s0 (making them identical) unless the copy is used in a way that forces 2 registers. Hmm, `s1 = s0` then `s1` used once → GCC propagates.

Hmm, what if s1 is used in BOTH arms? Then s1 is live across the branch → it gets a callee-saved register → the address would be `s1+0x20` with s1 in a different register → the generated code would be `lw v1,32(s1)` instead of `lw v1,32(s0)` → WRONG code.

Hmm.

**IDEA: make the two loads have different alias sets by using a `volatile`?** no.

**IDEA: use a struct-typed pointer with a different struct type!** e.g. cast s0 to a DIFFERENT struct type in case1: `e = ((Unkstruct_800B5CB8_2 *)s0)->unk20;` — but that struct must have unk20 at the same offset and the same type. Is there another struct with unk20 at 0x20? Hmm, `Unkstruct_80126B58` has unk20 at 0x20! (from item 2: `((Unkstruct_80126B58 *)p)->unk20`). Its type at 0x20 might be s32 or a pointer. If s32, then:
```c
case1: e = ((Unkstruct_80126B58 *)s0)->unk20;
```
→ a different alias set → CSE can't fold with case0's → 2 loads!

Hmm, but does GCC's CSE really care about the alias set for two loads with the same address? GCC's cse.c's `equiv_find`/`record_eqv` for MEMs: cse records `reg_equiv` entries only for REG/constant sources, not MEMs. But cse DOES eliminate a redundant load within a block. Across blocks, cse's "cse_basic_block" is per block but cse.c has a "cross-block" mechanism via `update_flow` (which handles the flow of equivalences between blocks).

Hmm. Honestly, the "elimination" might not be CSE but **reload/reload1**: the pseudo e has 2 sets; local-alloc gives it a register; reload1 might merge the 2 loads into 1 if it can prove they're the same... Hmm.

OK, let me just TRY the different-struct-type idea plus a few others. Cheap.

**ITEM 1 ROUND 3 VARIANTS (base = w01's s16 v1):**
x01: s16 v1 + case1's e via Unkstruct_80126B58 (different alias set)
x02: s16 v1 + case0's e via Unkstruct_80126B58
x03: s16 v1 + BOTH arms via Unkstruct_80126B58 (hmm, then they're the same again)
x04: s16 v1 + case1's e via `(s32 *)s0` deref [tried, no effect]
x05: s16 v1 + the shared tail DUPLICATED per arm
x06: s16 v1 + the `e` load moved BEFORE the func_8001C810 call in each arm
x07: s16 v1 + `e` declared as `s32 *e`? (unk20 is s32, so `e = ((Unkstruct*)s0)->unk20;` wouldn't typecheck. Skip.)
x08: s16 v1 + the shared block rewritten to use `e` via a pointer variable
x09: s16 v1 + `argmode`/`callarg0` as s16/u16
x10: s16 v1 + `e` assigned via a helper variable: `s32 e0; e0 = unk20; e = e0;`

Hmm, x10: `e0` is a single-set local assigned in both arms → same merging issue.

**IDEA x11 (PROMISING!)**: What if `e`'s assignment in case1 is moved INTO a nested block scope, or what if `e` is assigned via a comma/conditional?

**IDEA x12 (VERY PROMISING)**: What if the arms use DIFFERENT VARIABLES for the two e values and the join picks... no, the join needs one.

**IDEA x13**: What if the `e` load in case0 is kept by making case0's `e` assignment the FIRST statement of case0 (before the call)? Then the load is before the call → the call clobbers a0 → the load's register must survive the call → it'd be in a callee-saved reg → wrong code.

Hmm.

**IDEA x14**: Make case0's `e` load and case1's `e` load have different ADDRESSES that are equal at runtime — e.g. `e = unk20;` in case0 and `e = *(s32 *)((u8 *)s0 + 0x20);` in case1 → same address (tried).

Hmm. Since the tree difference doesn't stop the merge, the merge must be at the RTL level where both MEMs are identical.

**IDEA x15 (THE ALIAS-SET ONE)**: use a DIFFERENT STRUCT TYPE for one arm so the MEM's alias set differs → the RTL MEMs differ → CSE can't fold them. Let me find a struct with an s32 at offset 0x20. `Unkstruct_80126B58` — from item 2, `((Unkstruct_80126B58 *)p)->unk20` is used as a pointer (`func_8001D0E8(t, ...)`) — so unk20 might be a pointer there. Hmm.

Let me check what struct has an s32 at 0x20. Hmm, `Unkstruct_800B5CB8` has unk20 = s32 at 0x20. Are there others? Let me grep for "0x0020 */ s32".

Let me do that grep.

Alternatively: use a **char* cast in ONE arm and the struct in the other** — tried, no effect. Hmm, but maybe the alias set difference wasn't enough.

Hmm, hold on: maybe the fold happens because both loads are in DIFFERENT blocks and GCC's cse processes them in an order where it records the equivalence and then... hmm.

**COMPLETELY DIFFERENT IDEA (x16)**: What if we make the JOIN not use `e` at all, but instead have the arms pass the value via the call's arguments? E.g. restructure so that the shared block's work is done in the arms... no (duplication).

**IDEA x17**: What if the shared block is entered via a `goto` from both arms but the `e` assignment is hoisted OUT of the arms into the block BEFORE the branch? Then the load would be before the branch → the target doesn't have that.

**IDEA x18**: Hmm! What if we change the CONTROL FLOW so the join has only ONE predecessor? E.g., make case1 fall through to case0? Hmm:
```c
case1:
   ... argmode = 3;
   goto shared;
case0:
   ...
```
The order in the source determines the layout. The target has case1 falling through into the shared block and case0 jumping.

Hmm, what if I reorder the case blocks in the source (case1 before case0)? Then the fall-through/jump structure changes. The target's layout: case0's block ends with `j 2084` and case1's falls through. If in the source case1 comes first, then case1 would be the fall-through... Let me try swapping the case0/case1 blocks in the source!

That's a cheap and plausible variant. Let me add:
x19: swap the case0 and case1 blocks.

Hmm, but the target's code has case0 first (at 2040). Hmm, the source order affects the layout. If I swap, case1's code would come first → the layout would differ → probably worse. But worth a try.

OK, let me prioritize the most promising:
- x01: s16 v1 + case1's e via a different struct type (alias set)
- x05: s16 v1 + the shared tail duplicated
- x06: s16 v1 + the e load before the call
- x19: s16 v1 + case0/case1 swapped

Let me first check which struct has an s32 at offset 0x20. Let me grep.

Hmm, time: 07:15. I need to wrap up item 1 and do items 3, 4, 5, plus the results/log.

Let me be pragmatic: I'll do one more round of ~10 variants for item 1, then move on to the other items (each getting enough tries), then write everything up.

Let me grep for the struct and create the round-3 variants.
