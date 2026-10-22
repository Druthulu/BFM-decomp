---
ts: 2026-10-22T12:08:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3JQDUgpo90ksxFCowVUc
---
There are several structs with s32 at 0x20. Line 133 is `Unkstruct_80126B58` (from item 2). Let me use `Unkstruct_80126B58` for one arm.

Hmm, but is `Unkstruct_80126B58` visible in this TU? The TU includes shared headers. Unkstruct_80126B58 is used in ov_SC03_092. In ov_SC02_039 it might not be declared. Let me check if the type name is available (struct_types.h is included globally?). Let me check whether `Unkstruct_80126B58` appears in the ov_SC02_039 TU or its includes.

Hmm, risky. Let me check quickly.

Actually, let me use a simpler approach for the alias-set difference: cast to a DIFFERENT struct type that's definitely available in this TU — e.g. `Unkstruct_800B5CB8` vs... hmm.

Alternatively: the alias set of a load through `u8 *` is 0 (aliases everything) vs through a struct pointer is a specific set. I tried that (char*) — no effect. So alias sets don't matter here.

OK. Let me think about the merge ONE more time.

**IDEA: What if the two e-loads are merged by the "reload" pass because the pseudo e is a "constant-like" pseudo?** Hmm.

**IDEA: What if I make `e` a local with THREE definitions in the arms?** no.

**IDEA: What if the merge is because `e` is dead after the join, and GCC's "jump" pass (jump.c) does "thread_prologue_and_epilogue" moving the shared block's code into the preds... no.

Hmm, let me look at the candidate's actual disassembly around the case0 arm to understand what's there. Let me get it via --keep + idx.py.

Hmm, that's 2 Bash calls. Let me do it — understanding beats guessing.

Actually, let me try a DIFFERENT tack that's likely to work: **the cookbook's R41: "A store in EACH arm when the target reloads a global after it"**. Hmm.

And: "each arm's store BEFORE its counter".

Hmm.

Let me try: **give the arms' e-loads a purpose that keeps them in the arm: make the shared block's use of `e` come from a variable that's ALSO used in the arms.**

Hmm.

**SIMPLEST IDEA I HAVEN'T TRIED**: what if `e` is assigned in the arms but the JOIN uses a DIFFERENT variable? I.e.:
```c
case0:
    ... e = unk20; argmode = 2; goto shared;
case1:
    ... e = unk20; argmode = 3; goto shared;
shared:
    { s32 t = CAST_WIDTH(s32, e, 4); ... }
```
What if instead:
```c
case0:
    ... e0 = unk20; argmode = 2; goto shared;
case1:
    ... e1 = unk20; argmode = 3; goto shared;
shared:
    { s32 t = CAST_WIDTH(s32, e0, 4); ... }
```
Hmm, then the join uses e0 (defined only in case0) → invalid on the case1 path.

Hmm.

**IDEA: use `e` in the shared block but define it in BOTH arms with a `switch`-like structure where the two definitions have different TYPES.** Hmm.

OK, let me try the empirical route with a bunch of structural variants, including some that change the flow. Let me define round 3 (10 variants) on the s16-v1 base:

x01: case1's e via `Unkstruct_80126B58` (if available)
x02: case0's e via `Unkstruct_80126B58`
x03: the shared tail duplicated into both arms
x04: the e load before the call in each arm
x05: case0/case1 blocks swapped
x06: `e` loaded into a variable declared in each arm's scope (e.g. a nested block)
x07: the shared block's `t` rewritten in place (`CAST_WIDTH(s32, e, 4) |= 0x8040;`)
x08: `e` used with `argmode` computed in the arms
x09: the `e` assignment placed at the START of each arm (before the call)
x10: `v1` as s16 + `e` as `s16`? no.

Hmm, x06: "e loaded into a variable declared in each arm's scope" — e.g.
```c
case0:
    { s32 e0 = ((Unkstruct_800B5CB8 *)s0)->unk20; ... }
```
Hmm, the shared block needs e.

Let me instead do:
x06: the two arms' e assignments replaced by a single assignment in a block BEFORE the branch:
```c
    /* after the chain, before case0/case1 */
```
No.

Hmm, let me think about what would make GCC emit 2 loads writing the same register.

**!!!! NEW IDEA !!!!**: What if the target's 2 loads come from the fact that in the ORIGINAL, case1's `e` is the ASM's output — and the ASM's copy is coalesced with case1's LOAD. And case0's load is separate. So the target has 2 loads because there are 2 DIFFERENT pseudo definitions (case0's e and case1's e) — i.e., the ASM broke the phi.

For plain C: what if the two arms assign `e` from DIFFERENT sources that are equal at runtime? The only way: one of them computes the same address differently.

**AH — HERE'S ONE**: case0: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` and case1: `e = *((s32 *)((u8 *)s0 + 0x20));` — tried.

**ANOTHER**: case1: `e = ((Unkstruct_800B5CB8 *)(void *)s0)->unk20;` — the (void*) cast might change the alias set? Probably not.

Hmm, since the char* cast didn't change anything, the MEM is identical.

**FINAL IDEA for the load**: what if we make the JOIN's use of `e` go through a variable that is assigned in the arms via a `?:` or a nested `if`?

Hmm, let me try something totally different: **what if the `e` loads are in the arms because the shared block is NOT a join but the arms are duplicated and then MERGED by cross-jump?**

Cross-jump (jump.c) merges identical blocks. If the two arms' tails are identical (including the e load and the shared work), cross-jump merges them into one block. Hmm, but the arms differ in argmode.

**BUT WHAT IF argmode is set BEFORE the duplication point?** I.e.:
```c
case0:
    func_8001C810(unk20, D_8019CDBC);
    callarg0 = 0x199;
    e = unk20;
    argmode = 2;
    goto shared;
case1:
    func_8001C810(unk20, D_8019D81C);
    callarg0 = 0x199;
    e = unk20;
    argmode = 3;
    goto shared;
```
The two arms differ in: the D_ symbol and argmode. Hmm.

What if we hoist `argmode` and `callarg0`... no, they differ per arm.

OK — I think I should consider that item 1's remaining issue (the case0 e-load) might be reachable via the **`e` variable having 3 definitions with one of them in the TAIL**: the tail also has `e = unk20`. Hmm! In the target, the tail's load is separate (2108). So `e` has 3 definitions in the target: case0, case1, tail. And local-alloc gives them all v1.

In MY candidate, `e` has 2 definitions (case0, case1 merged into one?) + tail. Hmm, so maybe the merge of case0's and case1's definitions IS the issue.

**AH — maybe the fix is to make `e` have a definition in the TAIL that's DIFFERENT so local-alloc doesn't merge the others!** Hmm.

Hmm, the tail's `e = unk20;` is at line 71 (after `goto tail`). Hmm.

Hmm, hold on! What about this: the TAIL block is also a join (from the if/else and the gotos). In the target, the tail has `lw v1,32(s0)` at 2108 — its own load. So the tail's e is separate.

OK, let me just try a bunch and see. Actually, let me first get the candidate's disassembly to see exactly what's in the case0 arm. That's 2 calls and gives real information.

Let me do it.
