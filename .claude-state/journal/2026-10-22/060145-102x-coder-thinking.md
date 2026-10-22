---
ts: 2026-10-22T12:01:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_U9CuRVO2G2GmPdfXbbW6
---
Excellent progress! v17 (u16 v1) gives 89 ins (exact) and score 8. The remaining differences:

1. `sltiu v0,v1,2` vs `slti v0,v1,2` — SIGNED vs UNSIGNED comparison! The u16 v1 made the comparison unsigned. The target uses SIGNED (`slti`).
   → Fix: keep v1 as s32 for the comparison but... hmm. The u16 declaration made the copy materialize. But it changed the comparison to unsigned.
   
   Hmm! The target's `slti v0,v1,2` is signed. So v1 must be signed. But then how do we get the copy?
   
   Hmm, maybe `s16 v1` instead of u16! s16 would give `slti` (signed) and might still materialize the copy (the SUBREG trick per the cookbook: "an s16/u16/u8 local for a value used narrow keeps a SUBREG copy cse cannot fold").
   
   Let me try `s16 v1;`.

2. The unk20 load: mine has it at 45 (with a nop at 46), the target at 44-45... wait:
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
So: in the target, index 36 = `lw v1,32(s0)` (the unk20 load in case0) and 37 = `j 2084`. In mine, 36 = `j 207c` and 37 = something.
And the target has `lw v1,32(s0)` at 45; mine has it at 45 and a nop at 46.

So the difference: the target has an EXTRA `lw v1,32(s0)` (in case0, at index 36) that mine lacks, and mine has an extra nop.

Recall the target's case0 arm:
```
2054: li a0,409
2058: lw v1,32(s0)     <- e's load
205c: j 2084
2060: li a1,2
```
and case1:
```
2078: li a0,409
207c: lw v1,32(s0)     <- e's load
2080: li a1,3
```
So the target has the unk20 load in BOTH arms.

In mine (v17): the case0 arm lacks the load (it's sunk to the shared block) and there's a nop.

So I need the `e` load to stay in each arm — the alias-set trick (v13/v15 didn't help). Hmm, but v13/v15 were scored with the s32 v1 (13). Let me now combine: u16/s16 v1 + the e-load alias trick.

Let me test:
- v26: `s16 v1;` + the rest as v01.
- v27: `u16 v1;` + case1's e via char* 
- v28: `u16 v1;` + case0's e via char*
- v29: `s16 v1;` + case1's e via char*
- v30: `s16 v1;` + case0's e via char*
- v31: `u16 v1;` + BOTH arms via char* (2 edits)

Hmm, also: for the comparison to be signed with a u16 v1... `slti` requires a signed comparison. With `u16 v1`, GCC promotes to int (signed) → hmm, but it produced `sltiu`. Because v1's value is u16 (0..65535) and GCC knows v1 >= 0 → it can use an unsigned comparison! Clever GCC.

With `s16 v1`, v1 could be negative → GCC must use `slti`. 

And the target's `beq v1,v0` (equality) is the same either way.

So `s16 v1` might give BOTH the copy materialization AND the signed comparison! Let me test.

Hmm, but wait: with s16 v1, would the copy still materialize? The u16 case materialized it (89 ins). Let's see.

Also: the `mode` value is 0..3, so v1 (as u16 or s16) is 0..3. GCC doesn't know that (mode is `X & 3` — hmm, actually GCC DOES know mode = X&3 ∈ [0,3]! Then v1 = mode ∈ [0,3] → the comparison `v1 >= 2` could be unsigned or signed, both fine. But GCC chose `sltiu` for u16 v1 — because for u16, GCC knows v1 ∈ [0,65535] so `v1 < 2` ≡ `v1 >= 2` false... hmm, it used sltiu for `v1 >= 2`? The target has `slti v0,v1,2` (i.e. v1 < 2) then `beqz v0`. So `v1 >= 2` is computed as `v1 < 2` → `slti`.

With u16 v1: `v1 < 2` → GCC knows v1 ∈ [0,3]? If GCC knew that, it would fold the comparison entirely! It didn't, so GCC doesn't know the range. With u16, `v1 < 2` → unsigned compare (sltiu) since v1 is unsigned 16-bit → promoted to int? Hmm, `v1 < 2` where v1 is u16: the comparison is done in int (after integral promotion), so it should be signed! But GCC generated sltiu. Hmm, because GCC knows v1's range is [0,65535] and 2 is int → the comparison can be done unsigned. Right, GCC's optimize_mode for a comparison with an unsigned operand and a non-negative constant uses an unsigned comparison.

With `s16 v1`: v1's range is [-32768, 32767] → the comparison must be signed → `slti`. 

So `s16 v1` should give the target's `slti`. And will the copy materialize? The u16 case materialized it — probably because the u16→int conversion of the copy creates a SUBREG/zext that cse can't fold (per the cookbook). With s16, the copy would be a sign-extension — which ADDS an instruction (sra+srl or a `sext` insn). Hmm, that might change the count.

Hmm. Since v1 = mode where mode = X & 3 (0..3), the sign-extension of v1 is a no-op semantically but GCC doesn't know mode's range... wait, mode = CAST_SIGN(u16,...) & 3 → GCC DOES know mode ∈ [0,3]. So `v1 = mode` with v1 being s16: the sign-extension is provably a no-op → GCC folds it → v1 ≡ mode → no copy! Hmm, that would give 88 ins again.

Hmm. But with u16, the zext is also a no-op given mode ∈ [0,3]... yet the copy materialized. Hmm, so GCC did NOT use the range knowledge. Interesting — maybe because `mode` is `CAST_SIGN(u16, (u8 *)s0, 0x70) & 3` and the `& 3` gives the range... Hmm, GCC's range info for `X & 3` is [0,3] — yes, GCC 2.7 has that (unsigned_and_range). Then zext(s16→int) of a [0,3] value is a no-op → GCC would fold it. But the copy materialized with u16 (89 ins). So GCC did NOT fold it.

OK whatever — empirical. Let me test s16 and other widths:
- s16 v1
- u8 v1
- s8 v1
- u32 v1 (baseline)
- and v1 as `unsigned char`? etc.

Let me now run a batch for item 1:
w01: s16 v1
w02: u8 v1
w03: s8 v1
w04: u16 v1 + case1 e via char*
w05: u16 v1 + case0 e via char*
w06: s16 v1 + case1 e via char*
w07: s16 v1 + case0 e via char*
w08: u16 v1 + both arms char* (2 edits → do in round 2)
w09: u16 v1 + `v1 = v1;` second set
w10: u16 v1 + the chain's `v1 == 1` → hmm, the u16 changes the comparison.

Also: with u16 v1, does the case-table issue appear? The count is 89 (exact), so no case table. 

And the remaining residual after fixing slti/sltiu and the e-load: 
- 2 comparison fixes (sltiu→slti) — that's 2 mismatches
- the e load in case0 (1 insert + ...) 

Let me think about the e load issue more. The target has the unk20 load in BOTH arms. Mine sinks it to the shared block. 

**The alias-set trick**: if case0's `e` load uses a char* cast and case1's uses the struct spelling, the two loads have different alias sets → GCC can't CSE them → each stays in its arm. But v13/v15 (with s32 v1) gave 13 — because they didn't fix the count issue, so the diff was masked. Let me combine with u16.

Hmm, but actually: does the "sink to shared" happen because both arms load the same value? With different alias sets, GCC would have two different pseudos → a phi at the join → GCC would need to merge them at the join (a phi → a register copy in one arm). Hmm, that could add instructions.

Hmm. Let me think about the target more carefully:
```
case0:  func_8001C810(unk20, D_8019CDBC);   <- lw a0,32(s0)  (arg)
        callarg0 = 0x199;                    <- li a0,409
        e = unk20;                           <- lw v1,32(s0)
        argmode = 2;                         <- li a1,2 (in the j's delay slot)
        goto shared;
case1:  func_8001C810(unk20, D_8019D81C);   <- lw a0,32(s0)
        callarg0 = 0x199;                    <- li a0,409
        e = unk20;                           <- lw v1,32(s0)
        argmode = 3;                         <- li a1,3
shared: t = e->4; ...                        <- lw v0,4(v1)
```
So in the target, the shared block uses `v1` which was set in the arm. Two loads in the two arms, and the join uses v1.

For GCC to keep a load in each arm and have the join use it, the two `e` values must be DIFFERENT pseudos (not CSE'd). Then at the join, GCC needs a phi → GCC 2.7 (no SSA) would insert a copy in one arm or use the "cross-jump" mechanism.

Hmm, so how did the ORIGINAL produce this? The asm! `__asm__("" : "=r"(e) : "0"(e));` in case1 → e in case1 is a NEW definition (the asm's output) → so case1's `e` ≠ case0's `e` → no CSE → the phi at the join is real → GCC keeps the load in case1 AND in case0 (since they're different values, no sinking).

Hmm, but then the join's phi needs a register copy... The target shows the join using v1 directly. With GCC 2.7's local register allocation, a phi at a join is implemented by having the same register name in both arms — i.e., the two arms both define "v1" (the same pseudo) → the loads write v1 in each arm. That's exactly the target!

So in plain C: if the two arms' `e` values are NOT CSE-able, GCC would assign the same pseudo to both (via the phi) and each arm loads into it. 

**So the alias-set trick should work!** Let me test it.

Hmm, but would GCC's phi handling insert a copy in one arm? In GCC 2.7 (no SSA), a phi is a pseudo with 2 definitions (one per pred) — the register allocator handles it as "the pseudo is live across the join and has 2 sets". Both arms write to it. But the loads in the arms write to DIFFERENT pseudos (e1, e2) → then the join needs e1==e2 → a copy. Hmm.

Unless GCC's "local-alloc"/"reload" assigns the same register to e1 and e2 (they're equivalent by the phi). GCC 2.7 handles this: at the join, the pseudo has 2 sets in different blocks; the register allocator can allocate one reg to both if they don't overlap... but they're in exclusive branches, so YES — one register can serve both. And the loads write directly to it. So the target's form arises naturally!

So: making the two arms' loads non-CSE-able should give the target's form. The alias-set trick (char* vs struct) might work — but careful: GCC's alias analysis might still see them as the same because both are "load from s0+0x20" and the alias sets differ → not CSE'd. 

Hmm, but there's a subtlety: GCC's CSE for two loads requires the same MEM (same address expression) — the address expressions differ syntactically (`((Unkstruct*)s0)->unk20` vs `*(s32*)((u8*)s0+0x20)`), so CSE would need to prove the addresses equal. GCC's CSE works on the MEM RTL: `(mem (plus (reg s0) (const_int 32)))` for both — actually both lower to the SAME RTL MEM! The struct member access lowers to `(mem (plus (reg s0) (const_int 32)))` and the char* cast also lowers to the same. So CSE WOULD fold them regardless of the C-level alias sets. Hmm!

Hmm, but the alias set matters for whether the LOAD is safe to move/CSE across stores. The MEM's alias set is determined by the pointer type: a `char*` pointer has alias set 0 (or the "all" set), while a struct pointer has a specific alias set. So the two MEMs would have different ALIAS_SETs → CSE's `immutable`/`equiv` check... CSE requires the two MEMs to be "equivalent" which includes the alias set. So they wouldn't be CSE'd. But the MEM RTL differs only in ALIAS_SET, so the generated code is the same.

Hmm, but the address computation: `(plus (reg s0) (const_int 32))` for the struct case; for the char* case `(plus (reg s0) (const_int 32))` too. So the RTL is identical except ALIAS_SET. 

So the trick may work. v13/v15 gave 13 — but they were with s32 v1 (88 ins, so the diff was dominated by the missing move). The score didn't improve, meaning the alias trick didn't change anything OR the score is masked. Hmm, v13 (case0 via char*) = 13 and v15 (case1 via char*) = 13 — same as v01. So the alias trick had NO effect (the load still sank).

Hmm. So GCC CSE'd them anyway (or the sinking happened for another reason).

Hmm. Why does the load sink to the shared block? Because in the shared block, `e` is used. GCC's "jump threading"/"cross-jumping" or the PRE/hoisting. Actually — I bet it's GCC's **jump threading**: the `shared` block has 2 preds; the load is in each pred; the value is the same → GCC's "jump" pass merges the preds? no.

Hmm, alternatively: GCC's cse hoists the load to the common block? CSE doesn't hoist loads across blocks. But the "jump" pass's `thread_prologue_and_epilogue` can move code from a block into its predecessors, not into the join.

Hmm, what sinks it INTO the join? That's GCC's **"sinking"**? Or maybe the ORIGINAL C doesn't have the load in the arms at all — maybe GCC's optimizer moved it.

Hmm, actually here's a thought: maybe GCC put the load in the shared block from the START because the RTL for `e` is a phi, and the phi is "resolved" by... hmm.

OK, let me stop theorizing and just TEST the combination. Since v13/v15 gave no change, let me find another way to make the two arms' loads distinct:
- Use a different POINTER expression that lowers to a different address but the same value? e.g. `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` in case0 and `e = *(s32 *)((u8 *)s0 + 0x20);` in case1 → same RTL.
- Use `s0` vs `a0` (the parameter!) as the base: `e = ((Unkstruct_800B5CB8 *)a0)->unk20;` — hmm, a0 is the parameter (a copy of s0). The RTL: `(mem (plus (reg a0_copy) 32))` vs `(mem (plus (reg s0) 32))`. GCC would copy-propagate a0 → s0. Hmm.

Hmm, what about the TARGET's structure: the load is in each arm because the asm broke the CSE.

**Alternative approach for the e load: make the SHARED block's use of `e` require a per-arm value.** E.g. the shared block does `t = e->4; t |= 0x8040; e->4 = t;`. If instead each arm did its own part... no, the shared block is shared.

**Alternative: restructure so the shared block is DUPLICATED into each arm** (the cookbook: "a shared tail written out per site"). Then each arm has its own `e` load and the shared code is duplicated → the load stays in each arm! But that would DUPLICATE the instructions (the target has them once). Hmm, unless cross-jumping re-merges them (the cookbook says "cross-jump re-merges duplicated tails (jump.c:2371) at zero bytes"). Hmm, if it re-merges, we're back to the same.

Hmm! But wait: if the tail is duplicated and cross-jump re-merges it, the merge would put the tail in the shared block and the loads would... hmm.

**Let me try it**: duplicate the shared block into case0 and case1:
```c
    case0:
        func_8001C810(...);
        callarg0 = 0x199;
        e = ...unk20;
        argmode = 2;
        {
            s32 t = CAST_WIDTH(s32, e, 4);
            t |= 0x8040;
            CAST_WIDTH(s32, e, 4) = t;
            func_8012C658(callarg0, argmode, (s32)s0);
        }
        goto tail;

    case1:
        ... same with argmode = 3 ...
        goto tail;
```
This is a REAL attempt. Cross-jump might re-merge the two tails into a shared block (since they're identical except argmode's value)... hmm, argmode differs (2 vs 3), so the tails aren't identical → no merge → the code would be duplicated (more instructions). Hmm.

But the target has ONE shared block. So that won't match.

Hmm.

**Let me look at the residual once more**: 
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
So in the target: index 36 = lw, 37 = j. In mine: 36 = j, 37 = (something, maybe li a1,2 in the delay slot).
And the target has lw at 45; mine has lw at 45 and nop at 46.

Hmm, so mine has: [j 207c][li a1,2?] ... [lw v1,32(s0)][nop]
Target: [lw v1,32(s0)][j 2084][...] ... [lw v1,32(s0)]

Hmm, mine's case0 arm: `j 207c` — the target's is `j 2084`. So the case0 arm's jump target differs (207c vs 2084) — that's just a consequence of the block layout.

And mine's second lw is at 45 with a nop at 46; the target's is at 45 (hmm, "insert mine[44:44] target[45:46]" says the target has lw at 45 and mine has -- at 44; "delete mine[45:47] target[47:47]" says mine has lw at 45 and nop at 46 which the target doesn't have).

So: mine = [.., lw v1,32(s0) at 45, nop at 46]; target = [.., lw v1,32(s0) at 45]. So mine has an EXTRA nop at 46 and the target has an extra lw at 36 (in case0).

Hmm, so mine is missing the case0-arm load (which the target has) and has an extra nop. 

Hmm! Interesting: the nop at 46. Where does that come from? Probably the delay slot of a branch. In the target, the case0 arm's load is at 36 (in the delay slot of something?) and there's no nop.

So: if I get the load into the case0 arm, the nop would disappear → the count stays 89 and the diff might drop to just the 2 slti/sltiu issues → score 2! Then fixing the signedness → MATCH!

**So the whole game for item 1 is: get the unk20 load into BOTH arms, and use s16 (or another signed type) for v1.**

Let me think about how to keep the load in the arms.

**IDEA**: the shared block uses `e` as a POINTER (`CAST_WIDTH(s32, e, 4)` = `*(s32*)((u8*)e+4)`). What if `e` were a POINTER TYPE in C (`s32 *e`)? Then `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — hmm, unk20's type? If unk20 is `s32 *`, then `e` should be `s32 *`. Let me check the struct type!

If `e` is declared as a pointer (`s32 *e`), then the two arms' assignments are pointer values → the phi at the join is a pointer phi → GCC's "local-alloc" for pointers... The load would still be CSE'd. Hmm.

Hmm, BUT: the `CAST_WIDTH(s32, e, 4)` macro — let me look at what it does. If e is `s32` (an integer), CAST_WIDTH(s32, e, 4) probably casts e to a pointer: `*(s32*)((u8*)(e) + 4)`. Let me check the macro definition to write correct C.

Let me grep for CAST_WIDTH in the include dir.

Also let me check the type of unk20 in Unkstruct_800B5CB8.

Let me do these lookups.

Actually, let me first test the quick wins:
- s16 v1 (with the s32-e) → does it give 89 ins and signed compares?
- u16 v1 + the e-load variants.

Let me create a batch of item-1 variants:
w01: s16 v1
w02: s8 v1
w03: u8 v1
w04: u16 v1 + case1 e char*
w05: u16 v1 + case0 e char*
w06: s16 v1 + case1 e char*
w07: s16 v1 + case0 e char*
w08: u16 v1 + e as a pointer type (s32 *e) — needs the right type
w09: u16 v1 + the `shared` block using `e` differently
w10: u16 v1 + `e` loaded in each arm BEFORE the func_8001C810 call (statement order)

Hmm! **IDEA w10**: move the `e = unk20` load BEFORE the `func_8001C810(...)` call in each arm. Then the load is before the call → it can't be sunk to the shared block (a call is a barrier for sinking?). Hmm, but the target has the load AFTER the call (at 2058, after the jal at 204c). Hmm, but the final ORDER could still be that. Hmm, the load's position in the RTL would be before the call → the final code would have the load before the call. The target has it after. So no.

Hmm.

**IDEA w11**: make the `e` load depend on the call's result? No.

**IDEA w12**: Use `e` in each arm with a different offset spelling that lowers to a different address but the same value — impossible.

**IDEA w13**: Make the two arms assign `e` from a value that GCC can't prove equal: e.g. case0 `e = unk20;` and case1 `e = unk20;` — hmm.

**IDEA w14**: What if the arms load `e` via a helper that's a MACRO with a different type? Same.

**IDEA w15 (PROMISING)**: What if the shared block's use of `e` is such that the load can't be sunk — e.g. if the shared block's use is a STORE (`e->4 = t`), the store's alias analysis might prevent the sinking. Hmm, the store is already there.

**IDEA w16 (VERY PROMISING)**: the difference might be that in the target, `e` is a value that is LIVE ACROSS the call `func_8001C810` (since the load is after the call in the target... no, the load is after the call).

Hmm, hold on! In the target:
```
2040: lw a0,32(s0)     <- func_8001C810's arg (before the call)
2044: lui a1,...
2048: addiu a1,...
204c: jal func_8001C810
2050: nop
2054: li a0,409
2058: lw v1,32(s0)     <- e's load (AFTER the call)
205c: j 2084
2060: li a1,2
```
So `e`'s load is AFTER the call. And the source order is: call first, then `e = unk20`. Consistent.

And in case1:
```
2064: lw a0,32(s0)
...
2070: jal func_8001C810
2074: nop
2078: li a0,409
207c: lw v1,32(s0)     <- e's load
2080: li a1,3
```
Same.

So the loads are after the calls in both arms. In MY candidate, the load ended up in the shared block (2084-ish), i.e. sunk past the join.

**WHY does GCC sink it?** Because the shared block is the join and the load is the same in both arms → GCC's "jump"/"cse" merges. Hmm.

**AH — here's the thing: maybe it's not "sinking" but CSE + the phi.** In the shared block, `e` is a phi of two identical loads. GCC's cse: the two loads are in different blocks → CSE (which works within a block) can't merge them. But GCC's **"jump" pass (jump.c)** has `jump_combine` and also the **"thread_prologue"**... 

Hmm, actually GCC's cse.c DOES work across blocks in one direction: it can propagate a value from a dominating block. The shared block is dominated by neither arm. So CSE can't.

**Hmm, what about the front end?** GCC's front end (c-typeck/expr) creates a PHI for `e` at the join. In GCC 2.7's tree representation, the join's statement is `e = phi(e0, e1)` — the front end creates an explicit PHI node! And GCC's front end's "phi" handling: `c_expand_expr` for a PHI → it creates a copy. Hmm, but GCC 2.7's front end has the "phi" optimization where identical phi args are folded!

**YES**: GCC's front end (c-typeck.c / stmt.c) has `c_phi` / the "phi optimization": if all the phi's arguments are the SAME variable, the phi is replaced by that variable (no code). That's the "identical phi args" optimization.

So `e`'s phi has args (e0, e1) where e0 = unk20 (case0) and e1 = unk20 (case1) — the SAME expression → the phi is replaced by a single value → GCC then has ONE load of unk20 → and since it's used in the shared block, the load is placed in the shared block (the common dominator... hmm, or it stays in each arm with a phi).

Hmm, but if the phi is replaced by a single expression, GCC would re-expand the load ONCE, at the join! That's the sinking.

**SO: to keep the load in each arm, the two arms' `e` values must be DIFFERENT expressions** so the phi isn't folded. Then GCC emits 2 loads and a phi → the join uses a phi register → each arm's load writes it. That gives the target!

But my v13/v15 (char* vs struct) gave the same score 13 → the phi was still folded. Because the front end's phi-folding compares the TREES, and `((Unkstruct*)s0)->unk20` vs `*(s32*)((u8*)s0+0x20)` are different trees! So the phi should NOT have been folded...

Hmm, unless the front end doesn't fold phis at all, and the sinking happens later.

Hmm, v13 (case0 via char*) = 13 (88 ins). Let me check v13's actual diff — maybe it DID change the load placement but the score stayed 13 for other reasons. Let me look at v13's diff!

Let me run dt.sh on v13.

That's worth checking. Let me do it along with the s16 test.

Let me create the next batch of item-1 variants AND check v13's diff in the same message.

Batch:
w01: s16 v1 (base + decl change)
w02: s8 v1
w03: u8 v1
w04: u16 v1 + case1 e char*
w05: u16 v1 + case0 e char*
w06: s16 v1 + case1 e char*
w07: s16 v1 + case0 e char*
w08: u16 v1 + case1 e via `((s32*)s0)[8]`
w09: u16 v1 + case0 e via `((s32*)s0)[8]`
w10: u16 v1 + BOTH arms via `((s32*)s0)[8]` (2 edits - do in round 2)

Hmm, for these I need 2 edits for some. Let me structure: message 1 = 10 sed copies (with the base ranges) + 10 Edits (1st edit) + dt.sh on v13 (independent). Then message 2 = the 2nd edits. Then message 3 = sc.sh.

Hmm, the sed copies must precede the Edits. So:
Message A: 10 sed copies + dt.sh(v13) [independent]
Message B: 10 Edits (1st edit each)
Message C: 2nd edits (for the combined ones) 
Message D: sc.sh all

That's 4 messages. OK.

Actually, let me simplify: for w04-w09 I can build the base with the sed ranges (which already exclude the asm lines) and then ONE edit that changes BOTH the decl and the e line? They're not contiguous. Hmm.

Alternative: use sed to build a variant where the decl line is replaced... can't (sed can't substitute).

OK: 2 edits for the combined ones. Let me do:
Message A: 12 sed copies (w01..w12)
Message B: 12 Edits (the first edit for each)
Message C: 4 Edits (the second edit for the 4 combined ones)
Message D: sc.sh

Let me define:
w01: s16 v1 — edit: decl
w02: s8 v1 — edit: decl
w03: u8 v1 — edit: decl
w04: u16 v1 (decl) + case1 e char* (2nd)
w05: u16 v1 (decl) + case0 e char* (2nd)
w06: s16 v1 (decl) + case1 e char* (2nd)
w07: s16 v1 (decl) + case0 e char* (2nd)
w08: u16 v1 (decl) + case1 e s32* (2nd)
w09: u16 v1 (decl) + case0 e s32* (2nd)
w10: u16 v1 (decl) + case1 e struct→`(void*)` cast? hmm
w11: u16 v1 (decl) + `e` as `s32 *` (2nd: the decl of e)
w12: s16 v1 (decl) + the shared block's e use rewritten

Hmm, w11: `s32 e;` → `s32 *e;` would break `CAST_WIDTH(s32, e, 4)`. Let me skip.

Let me define w10: u16 v1 + case1's e loaded via `*(s32 *)((void *)s0 + 0x20)` 
w11: u16 v1 + case0's e via `*(s32 *)((void *)s0 + 0x20)`
w12: u16 v1 + the `shared` block: `s32 t = CAST_WIDTH(s32, e, 4);` → `s32 t = *(s32 *)((u8 *)e + 4);`

OK. And for the "slti vs sltiu" issue, s16 should fix it.

Let me also add: w13: u16 v1 + the chain's `v1 >= 2` → `v1 > 1` (might change the compare form).

Let me now do message A: 13 sed copies + dt.sh(v13) + also dt.sh(v17) for reference? I already have v17's diff.

Let me go.

Wait — one important thing: the sed base for the variants that change the decl or the e lines: the base excludes lines 19 and 45. Good, same base for all.

Let me write message A.
