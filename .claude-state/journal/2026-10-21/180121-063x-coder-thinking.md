---
ts: 2026-10-22T00:01:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YPBAnjjuLd9j24ljtwtC
---
P1/P2: 39 ins, score 6. Getting closer. The remaining diff: the ROM has `move v1,v0` (copy of the call result) + `move v0,zero` (the mask-path return 0) — mine lacks both (mine: `beqz v0` directly and no `move v0,zero`).

So mine is missing:
1. the copy of the call result out of $2 → because in mine, $2 is used for the result value and the call result also wants $2 → hmm, mine keeps the call result in $2 and computes the return value in $2 too (sequentially). The ROM copies the call result to $3.

So the ROM's shape: the call result lives in $3, the return value in $2.

This is the same problem: the call result must not stay in $2.

Hmm! What if the call result is used in a way that requires a copy — e.g. if the value is needed AFTER the return value is computed? In the ROM, the mask test (ins 26) happens BEFORE the byte check (ins 29) ✓ so no overlap. Hmm, but the ROM copied it anyway (because $2 was reserved for the pinned result).

What if we force a copy by making the call result live across a point where $2 is busy? E.g. if the byte check (which uses $2) happened BEFORE the mask test? The ROM's order: mask test first, then byte check. So no.

Hmm, what if the source computes the byte check BEFORE the mask test? E.g.:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = (byte == 0x15);
        } else {
            result = 0;
        }
    }
```
Same order.

What if the source is:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
(nopin) — the difference from the ROM was exactly: no `move v1,v0` copy, and the result computed in $3 + a final `move v0,v1`.

So the question remains: how to make gcc (a) copy the call result into $3 and (b) compute the result in $2.

IDEA: What if the call result is copied because the SAME variable is used in two places with a live overlap? E.g., what if the source uses `ret` again AFTER the result is computed? Like:

```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
no.

IDEA: Force the copy by making the call's result value "used" in a way that requires a register different from the return reg: e.g. what if the call is `ret = func_80133784(...)` and `ret` is compared with a *constant* in a way that gcc materializes the constant in $2? no.

IDEA: What if the function's return value is computed into $2 by the "result" variable and the call result is a *global* (allocated by global-alloc → callee-saved) — no, the ROM has it in $3.

Hmm, what about the possibility that the ROM's `move v1,v0` is not a copy of the call result but of something else? ins 24 `move v1,v0` right after the call (ins 22 `jal`) — with ins 23 `move a2,s0` in the delay slot. So yes, it's a copy of the call's return value.

So the ROM: the call result is copied to $3 immediately. Why? Because $2 must be free for the result variable (pinned).

Lever-free equivalent: make the call result be copied to another register because $2 is needed by something else at that point.

What if the source has ANOTHER value that needs $2 at that point? E.g. if `result` were assigned BEFORE the call... (M5/M6 → spill).

Hmm, what if `result` is assigned right after the call, before the tests?
```c
    ret = func_80133784(1, buf1, (int)buf2);
    result = 0;
    if (ret != 0) { ... }
```
= M4 (39 ins, score 8). In M4, `result` was born after the call → still $3? M4's diff showed mine[25] `move v1,zero` (result=0 in $3) — so result got $3 ✗.

Hmm. So even born right after the call, `result` gets $3 and `ret` keeps $2.

The allocation is: ret → $2 (born first, at the call), result → $3.

To flip, `result` must be born BEFORE `ret`. `result` born before the call = live across the call = spill (M5/M6).

Hmm! Unless the pre-call assignment of `result` is dead and gcc eliminates it... In M5, the pre-call `result = 0` was dead (overwritten in all paths) but gcc kept it (spill). Hmm, because gcc 2.7 doesn't DCE pseudo sets across calls? Actually it does DSE... but the value is live across the call in the RTL (the pseudo is live from its set to the merge point).

Hmm, what if the pre-call assignment is to a DIFFERENT variable that's then copied?

Let me think about the target's actual requirement again: the copy `move v1,v0` — maybe I can get it by making the call result used TWICE in a way that gcc copies: e.g.

```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
The two uses of ret are in different blocks → gcc could keep it in $2 across both ✓ (no copy).

Hmm, what if the source used the call result directly in the condition:
```c
    if ((ret = func_80133784(1, buf1, (int)buf2)) != 0) {
```
same.

What if the source computes the mask into a variable:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    mask = ret & 0x8000;
    if (ret != 0) {
        result = 0;
        if (mask != 0) {
```
Hmm! Then `mask` is a separate pseudo (set from $2) → the copy `andi v1,v1,0x8000` would be on the mask pseudo... The ROM: `move v1,v0; beqz v1; andi v1,v1,0x8000; beqz v1` — the same register v1 holds the call result and then the masked value. If the source had a separate `mask` variable, gcc would likely copy: `move v1,v0` (ret→$3?) hmm.

Hmm, what if the source is:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
with `ret` declared as `unsigned short ret;`? → the truncation issue.

Hmm, what about `char ret`? no.

What if `ret` is `int` but the call is assigned through a cast: `ret = (int)func_80133784(...)`? same.

Let me try the "mask variable" variant (Q1) and also a variant where the result variable is assigned from a comparison expression directly to the RESULT_DECL:

Q2:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
        return 0;
    }
    return 0;
```
= P1 (39 ins, score 6). The missing bits: `move v1,v0` and `move v0,zero`.

Hmm, P1 is missing the `move v0,zero` in the mask path — because in P1 the "return 0" (mask path) is a separate return statement → gcc materializes `move v0,zero`? Hmm, it should! Let me look at P1's diff again: mine[27] `nop`, mine[28] `--` vs target[28] `move v0,zero` → so mine lacks the `move v0,zero`.

In P1, the mask path is: `if ((ret & 0x8000) != 0) { return byte==0x15; } return 0;` — the "return 0" should emit `move v0,zero` ✗ it's missing! Hmm, why? Because in P1's layout, the "return 0" for the mask path might be merged with the "return 0" for the ret==0 path (both return 0 → cross-jump merges them into one block) → 1 `move v0,zero` instead of 2 ✓ that explains 39 vs 40 ins.

So the ROM has TWO `move v0,zero` (ins 28, 34) — i.e. the two "return 0" paths are NOT merged. In the original source (with the `result` variable), they're separate blocks because one is in the then-path and one in the else-path ✓ (that's why nopin had 40 ins).

So nopin (40 ins) matches the count; only the registers differ. P1 (39) has the right idea but merges.

So: the source structure should stay (the `result` variable with 2 assignments) — nopin — and I need the registers.

In nopin: mine[24] `beqz v0` (ret in $2), mine[25] `andi v0,v0,0x8000`, mine[26] `beqz v0`, mine[27] `move v1,zero` (result=0 in $3), ..., mine[31] `j`, mine[32] `sltiu v1,v0,1` (result in $3), mine[33] `move v1,zero`, mine[34] `move v0,v1` (copy the result to $2 at the return).

Target: ret in $3 (copied), result in $2 (computed in place).

So: the "result" pseudo must be $2. Since gcc gives $2 to `ret` (born first at the call)...

Hmm, what if `ret` is NOT a variable (the call result used directly in the tests)? Then the call result stays in $2 (no copy) ✗.

What if we force the copy of the call result by making the source do TWO calls? no.

Hmm, what if `ret` is assigned the call result AND the mask test uses a different variable so that `ret` dies early:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
ret is used twice.

What if the source is:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    result = (ret != 0) ? 0 : 0;   /* silly */
```
no.

Let me try the copy-preference angle: the RESULT_DECL pseudo gets $2 (that's how the return value ends up in $2). Our `result` local is copied to the RESULT_DECL at the end (`move v0,v1` in mine). If the source returned `result` directly, the copy is unavoidable unless `result` IS the RESULT_DECL.

In gcc, the RESULT_DECL is a pseudo; the front end creates a local variable for the return value. If the C source is `return <expr>;`, gcc creates the RESULT_DECL pseudo = the expression's value (no local variable). If the source assigns to a local and returns it, there's an extra copy.

In the ROM (pinned), `result` is a hard reg $2 → the copy to the RESULT_DECL ($2) is a no-op ✓ → no extra `move`.

So the lever-free version must have the returned value be the RESULT_DECL directly, i.e. the source must RETURN the value without an intermediate local... but the source's structure (result=0 then conditionally overwritten) requires a local.

Hmm, unless the source is written as:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return 0;
```
= P1-like: the "return 0" for the mask path and the ret==0 path merge → 39 ins ✗ (the ROM has 2 separate `move v0,zero`).

Hmm, how do I keep them separate? Make them different code: e.g.
```c
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
```
The two `return 0`s are in different blocks → gcc's cross-jump might still merge them (they're identical tails). In the ROM they're NOT merged (2 × move v0,zero) — because in the pinned version they're separated by the hard-reg sets? Hmm, cross-jump merging identical blocks: `return 0` in both → the same code → merged. But the ROM has 2. Hmm, so cross-jump didn't merge them in the pinned version (maybe because the hard-reg $2 set blocks the merge, or because the blocks differ in their predecessors).

Hmm, in the ROM: ins 28 `move v0,zero` (mask path) and ins 34 `move v0,zero` (ret==0 path) — two separate blocks, each `move v0,zero; jr $ra`. So not merged.

With the `result` variable version (nopin), the blocks are: mask path = `move v1,zero` (result=0) ... and the ret==0 path = `move v1,zero` → also not merged (mine has 2 sets: mine[27] and mine[33]) ✓ 40 ins ✓.

OK so nopin's structure is right; only the registers differ. Ugh!

So the crux remains: `result` → $2, `ret` → $3.

Hmm, let me think about "copy preferences" in gcc 2.7's global-alloc once more. There IS a mechanism: `cse->hard_reg_copy` — when a pseudo is copied to a hard reg, global-alloc records a preference (pseudo → that hard reg). This applies to GLOBAL pseudos. Our `result` is global (live across blocks) ✓ → it should get a preference for $2 (the copy at the return). But global-alloc first assigns the CALLEE-SAVED regs to globals, and the caller-saved regs are given to the remaining globals by priority — and the preferences are used as tie-breaks or as "prefer" hints.

In gcc 2.7's global.c, `allocno_compare` uses `allocno->size`, `allocno->birth`, and for ties `allocno_compare` compares `ALLOCNO_QTY_PRIORITY` and then the "reg" preference...

The relevant field: `ALLOCNO_REG` / `reg` — the preferred register. In global-alloc, `global_alloc` computes for each allocno a "reg" (the preferred hard reg) from the copy preferences. Then `allocno_compare` (used in `find_reg`/`choose_regs`) prefers the allocno whose `reg` matches the hard reg being allocated! That's the mechanism that gives the returned pseudo $2 ✓.

So `result` (global, with a copy preference to $2) should be preferred for $2 — but `ret` (also global) won. Because `ret`'s priority was higher? Or because the copy preference didn't apply (the copy `set $2, result` might be created AFTER global-alloc? No, it's created by expand_end_function before regalloc).

Hmm, note: `ret` is set by a CALL → the call's return value is in $2 → the pseudo `ret` has a hard-reg copy preference for $2 TOO (the call's result is $2)! So both have $2 preferences → the priority decides → ret won.

To flip: increase `result`'s priority or decrease `ret`'s.

priority = floor(log2(qty)) * qty / live * 1e4.

`ret`: qty = 3 (set + 2 uses), live = from ins 22 to ins 27 ≈ 6 → floor(log2(3))=1 → 1*3/6 = 0.5 → 5000.
`result`: qty = 4 (3 sets + 1 use), live = ins 27..39 ≈ 12 → floor(log2(4))=2 → 2*4/12 = 0.67 → 6700.

Hmm, that says result > ret → result should get $2 ✗ (observed the opposite).

Unless `result` is a LOCAL pseudo (not global) — if a pseudo's live range doesn't cross a call, gcc can treat it as local ("local pseudo" = the pseudo is not live across a call AND is used in one block? In gcc, `local_pseudo` is determined by `REG_N_REFS`/`pseudo->VAR`... hmm, in gcc 2.7, a pseudo is "local" if it has no `pseudo->VAR`... hmm no.

Actually, in gcc 2.7 (final.c), `local_alloc` handles pseudos that are "local" in the sense of `reg_is_local_p` — a pseudo is local if it's not live across a call AND it's not in a "global" allocno. The `result` pseudo is live across the return (the epilogue) — hmm, `result` is live from ins 27 to the return at 39, and there are no calls in between → it could be local ✓ (it's in one "basic block region" — the whole function is one block region here).

Hmm, gcc's local-alloc works per basic block: in the block containing the sets (the innermost if-block), the pseudos live there are allocated. `result` is set in 2 blocks (the then-block and the else-block) → so it's live across blocks → global.

OK. I'm going too deep. Let me do an experiment to test the priority hypothesis: increase `result`'s qty by adding a use. E.g.:

Q3: use `result` in the condition? changes semantics ✗.

Increase `result`'s qty by making it a `u16`/`s16`? no.

Decrease `ret`'s qty: use `ret` only ONCE! E.g.:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
2 uses. What if we restructure to use it once?
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if ((ret & 0x8000) != 0) {     /* hmm, this changes semantics: ret==0 → mask 0 → result=0 ✓ */
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    } else {
        result = 0;
    }
    return result;
```
Hmm! Semantics: original: if ret == 0 → result = 0; else if (ret & 0x8000) == 0 → result = 0; else result = (byte == 0x15). The simplified version: if (ret & 0x8000) != 0 → result = (byte==0x15) — but that's wrong when ret == 0? If ret == 0, then ret & 0x8000 == 0 → result = 0 ✓ same! And if ret != 0 and the mask is 0 → result = 0 ✓. So the semantics are equivalent ✓✓ (since ret==0 implies the mask is 0).

But the ROM's structure has TWO `move v0,zero` and the test `beqz v1` (ret == 0) at ins 25 — so the ROM tests ret == 0 separately ✗. The simplified version has only one test → different structure (fewer insns) ✗.

Hmm.

What if we keep both tests but use `ret` once? The ROM's two tests: `beqz v1` (ret==0) and `andi v1,v1,0x8000; beqz v1` — the second uses the masked value. Both derive from `ret` — so `ret` has 2 uses (the test and the mask) but they're the same register ✓.

Hmm, so `ret`'s qty is 3 (set, use, use).

To DECREASE ret's qty: hmm, what if the source writes the mask test as `if ((ret & 0x8000) != 0)` → that's 1 use of ret. Plus `if (ret != 0)` → another use. Total 2 uses.

What if the source is:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if (ret & 0x8000) {     /* same thing */
```
same qty.

Hmm, what if we make `ret` a `u16`? Hmm, the truncation.

What if we make `ret` hold the MASK instead of the raw value, i.e.:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        ret &= 0x8000;          /* ret = ret & 0x8000 — an extra set of ret (in place) */
        if (ret != 0) {
```
→ the andi in place ✓ (the ROM does `andi v1,v1,0x8000` in place ✓) and `ret`'s qty goes up (3 sets? no: 2 sets, 2 uses = 4) hmm.

But maybe the in-place `ret &= 0x8000` changes the allocation: the pseudo ret is modified in place, so it must be in a register where the copy `move v1,v0` happens first... Actually this doesn't force a copy either.

Hmm hmm. But wait: this variant might change the register allocation! Because now `ret` has an extra set (in-place modification), making it a "modified" pseudo → hmm.

Let me just try a batch of variants for item 4:
Q1: mask into a separate variable.
Q2: `ret &= 0x8000` in place.
Q3: `result` as `unsigned int`.
Q4: `ret` as `unsigned int`.

And also: Q5: use `unsigned char` for the byte comparison? no.

Let me write Q2 and Q4 and test. Time check: I'm at ~1h10m for 3.5 items. I need to speed up. Let me batch 3-4 variants per turn and accept walls.

Actually, let me reconsider the problem from the "what does the pin buy" angle once more: the pin makes `result` = $2 = the return register. The lever-free equivalent: the value returned must be in the return register at the end, and the intermediate computations happen in $2.

In the ROM, the byte check (`lbu v0,30(sp); xori v0,v0,0x15; sltiu v0,v0,1`) is computed IN $2 — because `result` is $2 ✓. Without the pin, gcc computes it in $3 and copies at the end.

Hmm, what if the byte-check expression is returned DIRECTLY (so it's the RESULT_DECL) → gcc computes it in $2 ✓!! That's P1 (39 ins) — but P1 lost the second `move v0,zero` (block merging).

So: combine P1's direct return with a structure that keeps the two "return 0" blocks separate!

P3:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
```
Hmm, gcc may still merge the two `return 0` blocks (cross-jump). In the ROM they're separate because... hmm, in the ROM the mask-path's `move v0,zero` is at ins 28 and the ret==0 path's at ins 34 — separate. With the pin, the blocks differ? Both are "move $2,zero; jr $ra" — identical → cross-jump should merge them ✗ but the ROM doesn't have them merged.

Hmm! Interesting: so in the pinned version, cross-jump did NOT merge them. Why? Because the mask-path block (ins 28) is followed by the byte-check block (ins 29-33) — i.e. ins 28 is NOT a separate block ending in a return; it's the block that falls through into the byte check! I.e. the "result = 0" set is in the mask-path block, and the byte check is a separate block that ends with `j` to the epilogue.

So the ROM's blocks:
- B1 (ins 26-28): `andi v1,v1,0x8000; beqz v1,+0x8c; move v0,zero` — wait, the beqz at 27 jumps to +0x8c (ins 35 = the epilogue) when the mask is 0 → so the mask==0 path returns with v0 = the value set at ins 28 ✓ (so ins 28 is in the fallthrough of the beqz = the mask!=0 path). Hmm, but then the mask==0 path jumps directly to the epilogue with v0 = ??? It needs v0 = 0!

Hmm! Let me re-examine: ins 27 `beqz v1,a500` (+0x8c = ins 35). If the mask is 0 → jump to ins 35 (the epilogue) → returns v0 = whatever v0 holds at that point. What does v0 hold? At ins 27, v0 = ? The last write to v0 was... ins 22's call result (v0 = the call result) — then ins 24 `move v1,v0` copied it. So v0 still holds the call result ✗ (the function would return the call result!).

Hmm, that can't be. Unless the mask==0 path is the one where result=0 (ins 28's `move v0,zero` is BEFORE the branch)...

Let me re-look at the ROM listing:
```
24  move v1,v0
25  beqz v1,a4fc (+0x88)
26  andi v1,v1,0x8000
27  beqz v1,a500 (+0x8c)
28  move v0,zero
29  lbu v0,30(sp)
30  nop
31  xori v0,v0,0x15
32  j a500 (+0x8c)
33  sltiu v0,zero,v0
34  move v0,zero
35  lw ra,36(sp)
...
```
Addresses: ins 25 at +0x64, ins 26 at +0x68, ins 27 at +0x6c, ins 28 at +0x70, ins 29 at +0x74, ins 30 at +0x78, ins 31 at +0x7c, ins 32 at +0x80, ins 33 at +0x84, ins 34 at +0x88, ins 35 at +0x8c.

So +0x88 = ins 34 (`move v0,zero`) and +0x8c = ins 35 (the epilogue `lw ra`).

- ins 25 `beqz v1,+0x88` → if ret == 0 → ins 34 (`move v0,zero`) → returns 0 ✓ (the else branch).
- ins 27 `beqz v1,+0x8c` → if the mask == 0 → ins 35 (the epilogue) → returns v0 = ??? v0 at that point = the call result (from ins 22) ✗✗.

Hmm, that's wrong. Unless... hmm! Wait: is `move v1,v0` (ins 24) really copying the call result? The call is at ins 22 (`jal`) with the delay slot ins 23 (`move a2,s0`). So after the call, $2 = the call result. ins 24 `move v1,v0` → $3 = the call result ✓. So $2 still = the call result.

Then ins 27's branch (mask == 0) → ins 35 (the epilogue) → returns $2 = the call result?! That would be a bug.

Unless the branch at ins 27 goes to ins 34 (the `move v0,zero`)? +0x8c vs +0x88: the labels are 0x88 → "a4fc <func+0x88>" and 0x8c → "a500 <func+0x8c>". And the addresses: the function starts at 0x8014FD54; +0x88 = 0x8014FDDC and +0x8c = 0x8014FDE0.

ins 25 `beqz v1,a4fc` = +0x88 → ins 34 (move v0,zero) ✓
ins 27 `beqz v1,a500` = +0x8c → ins 35 (lw ra) ✓

Hmm, so the mask==0 path returns the call result. That's a ROM quirk? Or my address mapping is off by one instruction.

Let me recount the insns from the probe output:
```
 0 addiu sp,sp,-40      +0x00
 1 sw s0,32(sp)         +0x04
 2 move s0,a0           +0x08
 3 addiu a1,sp,16       +0x0c
 4 move a2,a1           +0x10
 5 li v0,7              +0x14
 6 sw ra,36(sp)         +0x18
 7 sh zero,16(sp)       +0x1c
 8 sh zero,18(sp)       +0x20
 9 jal                  +0x24
10 sh v0,20(sp)        +0x28
11 move a0,s0          +0x2c
12 addiu s0,sp,24      +0x30
13 move a1,s0          +0x34
14 move a2,s0          +0x38
15 li v0,-24           +0x3c
16 sh zero,24(sp)      +0x40
17 sh zero,26(sp)      +0x44
18 jal                 +0x48
19 sh v0,28(sp)        +0x4c
20 li a0,1             +0x50
21 addiu a1,sp,16      +0x54
22 jal                 +0x58
23 move a2,s0          +0x5c
24 move v1,v0          +0x60
25 beqz v1,a4fc        +0x64
26 andi v1,v1,0x8000   +0x68
27 beqz v1,a500        +0x6c
28 move v0,zero        +0x70
29 lbu v0,30(sp)       +0x74
30 nop                +0x78
31 xori v0,v0,0x15     +0x7c
32 j a500              +0x80
33 sltiu v0,zero,v0    +0x84
34 move v0,zero        +0x88
35 lw ra,36(sp)        +0x8c
36 lw s0,32(sp)        +0x90
37 addiu sp,sp,40      +0x94
38 (jr ra)             +0x98
39 nop                +0x9c
```
Hmm, but the function is 40 ins = 0xA0 bytes ✓ (0x00-0x9c).

So +0x88 = ins 34 (`move v0,zero`) ✓ and +0x8c = ins 35 (`lw ra,36(sp)`) ✓.

ins 32 `j a500` = +0x8c → jumps to ins 35 (the epilogue) with the delay slot ins 33 `sltiu v0,zero,v0` (the result) ✓.
ins 27 `beqz v1,a500` = +0x8c → jumps to ins 35 (the epilogue) with v0 = ? v0 at that point = the call result (ins 22) — hmm, unless... 

AH WAIT. ins 28 `move v0,zero` is at +0x70, which is AFTER ins 27 (+0x6c). So the mask==0 path (branch taken at 27) skips ins 28 → v0 = the call result ✗.

Hmm, that means the ROM returns the call result when (ret & 0x8000) == 0?! That can't be right... unless the call result IS 0 in that case? No.

Hmm, hold on: maybe the call result is not in $2 at that point. Let me re-check ins 22 `jal` — the call's return value goes to $2 ✓. Then ins 24 `move v1,v0` copies it to $3. Then $2 still holds it.

Hmm, so the ROM's mask==0 path returns the call result in $2. That's a real ROM behavior (maybe the original code returns `ret` in that case?). Hmm, but the C source says result = 0.

Wait, maybe I've got the branch polarity wrong: `beqz v1,a500` — if v1 == 0 → branch to +0x8c. v1 = ret & 0x8000. So if the mask is 0 → jump to the epilogue → return v0 = the call result (ret).

Hmm! So the ROM returns `ret` when the mask is 0. But the C source says result = 0 in that case.

And the pinned C compiles to these exact bytes... so the pinned C also returns `ret` in that path. How? Because in the pinned C, `result` is $2 and the assignment `result = 0` (ins 28) is in the fallthrough path; the mask==0 path jumps directly to the epilogue with $2 = the call result — because gcc thinks... hmm, that would be a gcc bug (returning an uninitialized/old value).

Hmm, wait. Maybe not: in the pinned C, `result` is a HARD REG $2. The call result is also $2 (the call clobbers $2). So after the call, $2 = the call result; `ret` (a local pseudo) is copied to $3 at ins 24. Then the code:
```
if (ret != 0) {          → beqz v1 (ret==0 → else path)
    result = 0;          → move $2,zero
    if (ret & 0x8000) {  → andi v1,v1,0x8000; beqz → ???
        result = (byte == 0x15);
    }
} else {
    result = 0;
}
return result;
```
In the ROM, the `beqz v1` at ins 27 (mask == 0) jumps to +0x8c = the epilogue — skipping `move $2,zero` (ins 28)! So the "result = 0" (ins 28) is in the mask!=0 path only, and the mask==0 path returns the stale $2.

Hmm, that means gcc 2.7.2 (with the hard-reg pin) mis-compiled the C?! Or the source's structure is different from what's in the header.

AH — maybe the source is NOT `result = 0; if (mask) result = ...;`. Maybe the actual source is:

```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        } else {
            result = 0;      ← hmm
        }
    }
```
Hmm, but then the "result = 0" (ins 28) would be in the else path of the mask test — which is the fallthrough of the beqz at 27? No: the beqz at 27 jumps AWAY when the mask is 0, so the fallthrough (mask != 0) is the byte-check path. So ins 28 `move v0,zero` is in the mask != 0 path — meaning the source has `result = 0;` BEFORE the byte check in the mask!=0 path ✓ = the current source's structure ✓ (`result = 0;` then `if (mask) result = ...`).

And the mask==0 path skips `result = 0` and returns the stale $2 ✗ — a gcc bug (the hard-reg $2 wasn't initialized on that path).

Hmm! Actually no — it's not a bug if gcc knows that $2's value on that path is the call result and the C's `result` is... hmm, the C says result = 0 in the mask==0 path.

Unless the C's structure is:
```c
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = (byte == 0x15);
        }
    }
```
The mask==0 path: result = 0 was set at ins 28 — but the branch at ins 27 SKIPS ins 28! So gcc put the `move $2,zero` in the wrong place?! 

Hmm, no: the branch at 27 is `beqz v1` where v1 = ret & 0x8000. If the mask is 0, the branch is TAKEN → jumps to +0x8c → the epilogue. The fallthrough (mask != 0) → ins 28 `move $2,zero` → then the byte check.

So in the mask==0 path, `result = 0` was NOT executed → the ROM returns the stale $2 (the call result). 

So gcc 2.7.2 with the hard-reg pin mis-scheduled the `result = 0` set into the mask!=0 path only, leaving the mask==0 path with a stale $2. That IS a miscompilation (a real gcc 2.7.2 bug with hard-reg pseudos).

Hmm! Interesting. That means the ROM's bytes encode a gcc BUG. Reproducing it without a pin seems very unlikely: without the pin, gcc would compute `result` correctly (the value would be 0 in the mask==0 path).

Hmm, wait. But the score for nopin was 9 — the differences were exactly: no `move v1,v0` copy, the registers swapped, and the `move v0,zero` placement. Hmm, mine[27] `move v1,zero` (the result=0 set in $3) is at the fallthrough of the mask test → the same placement as the ROM's ins 28 ✓ (the same structure!).

So nopin's structure matches the ROM's structure except the registers! (mine: ret in $2, result in $3; ROM: ret in $3, result in $2.)

So the only difference is the register assignment. And the ROM's assignment is what the pin forces.

Hmm, so for item 4 I need: result → $2, ret → $3.

Let me try the "increase result's qty" lever: what if `result` is used in more places, e.g. the source assigns `result = 0` in the then-path AND the else-path AND uses it in the return (3 uses + 3 sets = 6 refs)?

Currently: sets 3 (ins 28, 34 + the comparison), uses 1 (the return) → qty 4.

Hmm what if the source is written as:
```c
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
= the current source. qty(result) = 4, qty(ret) = 3.

Priority: result: floor(log2(4))=2, live=? ; ret: floor(log2(3))=1.

For result to win, we need 2*4/live_r > 1*3/live_t → 8/live_r > 3/live_t → live_r < 2.67*live_t. The result's live range: from ins 27/28 to the return (ins 39) ≈ 12; ret's live: from ins 22 to ins 27 ≈ 6 → 12 < 2.67*6 = 16 ✓ → result should win ✗ (observed ret won).

So my priority model is wrong, OR `result` is a LOCAL pseudo (allocated by local-alloc, not global-alloc). If `result` is local (allocated per-block) and `ret` is global, then the caller-saved regs go to globals first...

Hmm, in gcc, local pseudos are allocated AFTER global ones, from the leftover regs. The globals get the callee-saved regs first, then the caller-saved.

Ugh. Both `ret` and `result` are in the same function; `ret` is set by a call and used across blocks (2 blocks) → global; `result` is set in 2 blocks → global.

Hmm, so both are global. Then the priority decides, and my model says result should win. But the observation is the opposite.

Unless... the "live" for result is longer than I think: result is set at ins 28 and 34, and used at the return (ins 39) — but its live range must cover the whole range from the FIRST set (ins 28) to the use (ins 39) = 11 insns, but ALSO the second set (ins 34) is in a different path... For global-alloc, the live length is computed per allocno as the number of instructions in the live range.

And ret: set at ins 22 (the call), used at 25 and 27 → live 22..27 = 6.

Hmm, so result: 2*4/11 = 0.727; ret: 1*3/6 = 0.5 → result wins. But observed ret won. So the model is off, OR the copy preference for the RESULT_DECL/return register matters more.

Hmm, hold on! Maybe `result` is NOT global but LOCAL: in gcc 2.7, "local" pseudos are those whose live range doesn't cross a call... `result` doesn't cross a call ✓; `ret` is set BY a call ✓. Hmm, both local then.

OK: in gcc 2.7's final.c, `local_alloc` handles ALL pseudos that aren't "global allocnos". The distinction: global-alloc handles pseudos that are live across a CALL (or that need callee-saved regs). Hmm.

I'm burning time. Let me try empirical variants that could plausibly flip the allocation:
(a) make `result` a `s32`/`u32` vs `int` — no change.
(b) Give `result` more refs: e.g. write the else-branch as `result = 0;` and the then-branch as `result = 0;` — already.
(c) Make `ret` have fewer refs: use the call result in a single expression:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
Hmm.

(d) What if the mask test is done on the CALL RESULT directly (no `ret` variable) — but then the call would be repeated ✗.

(e) What if the source assigns the call result to `ret` and then uses `ret` only once by combining the tests:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if (ret & 0x8000) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
```
same qty.

(f) What if the `result` variable is used in the `if` condition: e.g. `if (ret != 0) { result = 0; ...}`.

(g) What if the two branches' `result = 0` are written differently, e.g. the else as `result = (ret == 0) ? 0 : 0;`? silly.

(h) What if `result` is declared `volatile`? = barrier ✗.

(i) What if the source assigns `result` from a comparison in a way that adds refs: e.g.
```c
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
```
✓ as is.

Let me try a different lever: the C0505 catalog mentions "s16/u8 widths". What if `ret` is declared `short`? Then the call result (int) → truncated to 16 bits: the ROM has `move v1,v0` (a plain copy, no truncation) — but gcc might know the call's result fits? no.

Hmm, what if `ret` is declared `unsigned short` and the mask test uses `(ret & 0x8000)`: the ROM's `andi v1,v1,0x8000` — for a u16 value, the mask 0x8000 & value → the zero-extended value → `andi` ✓ (the zero-extension would need `andi v1,v1,0xffff` ✗ extra insn).

OK, let me try yet another approach: what if we can get the compiler to copy the call result by using it in a context where $2 is busy — e.g. if the byte check happened BEFORE the mask test. The ROM's order is fixed. ✗.

Hmm, what if `result` is computed EARLY (before the mask test) and the mask test's `ret` use comes after? The ROM: ins 28 `move v0,zero` (result=0) is AFTER the mask test (ins 26-27) but BEFORE the byte check.

Hmm, what if the source is:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
= nopin. The difference from the ROM is only the registers.

Hmm, let me try the "copy preference" lever: what if the source assigns the result to the RESULT_DECL directly via a *comma* expression or a conditional:
```c
    return (ret != 0) ? ((ret & 0x8000) != 0 ? (*(unsigned char *)((char *)buf2 + 6) == 0x15) : 0) : 0;
```
→ P1-like (39 ins).

OK, let me try to think about which C change could make gcc allocate $2 to `result`.

What if `result` is a GLOBAL variable? no.

What if the function's return type is `int` and `result` is `int` ✓.

Hmm, what if we make `result` the value returned via a *pointer*? no.

What if we introduce a dummy use of $2 before the call? Hmm! What if the source has something that occupies $2 across the call... e.g. a variable that's live across the call → it'd be spilled to $s0 (as in M5) ✗.

Hmm, what if the source keeps the call result in a variable that is USED after the result is computed, forcing a copy? E.g. the ROM's mask test is before the byte check, so `ret` is dead before the byte check ✓ no overlap.

Hmm, so the copy `move v1,v0` in the ROM is purely because $2 was reserved.

=> Item 4 might be a WALL (tag: "copy-pref-return-reg" or "lreg-return-pseudo").

Hmm, but hold on: what if the `result` variable's *use* is in the return statement and the RESULT_DECL copy is a no-op because gcc gives the RESULT_DECL... hmm.

Actually WAIT. What if we write the source so that the RETURN VALUE IS the `result` variable directly — i.e. `result` IS the RESULT_DECL. In C, that's not expressible... BUT: gcc's front end (the "result" of a function) — when you write `return result;`, gcc creates a copy. However, if the local variable's address is never taken and it's only used in the return, gcc's "return slot optimization" (a gcc 2.7 feature? "local return slot") might merge them. Hmm, gcc 2.7 does have the "return slot" optimization for aggregates only.

Hmm.

Let me try a slightly different tack: what if the `result` variable is declared as the LAST local (after ret)? M2 tested result-before-ret. Let me test ret-before-result (which is the original order!) — nopin = 9. Yeah.

Hmm, so decl order doesn't matter (M2 = 9 = nopin).

Let me try the alloc table after all — it's the sanctioned tool for exactly this ("the table settles arguments the residual cannot"). I need cc1 dumps of the TU. The dumps need a real TU file (an includer's .c). I can use the includer .c directly (the script accepts a .c file) — but that compiles the PINNED header (the real src) — which is what I want to analyze! Actually I want to analyze the LEVER-FREE candidate's allocation. Hmm, but the allocation table of the pinned version is also informative (it shows the priority numbers for ret/result).

Hmm, but the pinned version has `result` as a hard reg → not in the table.

So I'd need the dump of my candidate. The dump script takes a .c file → I can create a modified copy of an includer .c where the header include is replaced by my candidate body... but the header also declares externs (needed). Hmm, my candidate body file (nopin.c) contains just the function; the includer includes the header for the externs.

I could create a scratch TU: copy the includer .c, and replace the `#include "../shared/ov/func_8014FD54.h"` line with the header's content but with the pinned line replaced by my candidate. Since the header contains only externs + the function, I can write a modified header into a shadow dir and a modified includer that includes it... but the includer's include path is relative.

Simpler: create a scratch dir with:
- `func_8014FD54.h` = the header with the pin removed (my candidate),
- `t.c` = a copy of the includer .c with the include path rewritten to "func_8014FD54.h"... but the includer may include other headers too, and the cpp -I flags: the script does `-I"$(dirname $tc)"` and `-Isrc/shared` ✓. The includer's other includes (`#include "../shared/xxx.h"`) resolve relative to the includer's dir — but my copy is in a different dir ✗. The script adds `-Isrc/shared` which handles `../shared/xxx.h`? No: `-Isrc/shared` + the include `"../shared/xxx.h"` → resolved relative to -I dirs → `src/shared/../shared/xxx.h` = `src/shared/xxx.h` ✓!! (since -Isrc/shared + ../shared/ = src/shared/../shared/ = src/shared ✓). Clever.

So: my scratch dir needs the header file at the path relative to the includer's dir: the includer includes `"../shared/ov/func_8014FD54.h"` → with `-I<scratch>` hmm, the script uses `-I"$(dirname $tc)"` (the scratch dir) → so `"../shared/ov/func_8014FD54.h"` relative to the scratch dir → `<scratch>/../shared/ov/...` ✗. But the script ALSO has `-Isrc/shared` → `src/shared/../shared/ov/...` = `src/shared/ov/func_8014FD54.h` (the real one) ✗ — I need my modified one.

I could put my modified header in a dir structure `<scratch>/../shared/ov/func_8014FD54.h` — i.e. create `<scratch>/../shared/ov/` — that means writing outside my shard dir ✗ (the constraint: write only under .run/P40/T11/G08/). Hmm, I could use a scratch dir under my shard dir with a sibling structure: e.g. `<shard>/dumps_item4/work/t.c` and `<shard>/dumps_item4/shared/ov/func_8014FD54.h` — then `"../shared/ov/..."` from `<shard>/dumps_item4/work/` resolves to `<shard>/dumps_item4/shared/ov/...` ✓✓ (since -I<work> + ../shared/ov/ = <shard>/dumps_item4/shared/ov/ ✓).

OK that's doable but takes several steps (copy the includer, write the modified header, run the dump script — but the dump script is a .sh under tools/ → can I run it? `bash tools/cc1_dumps_tu.sh` — earlier `bash .run/...dt.sh` was DENIED. Hmm! That was the .run path. Maybe `bash tools/xxx.sh` is allowed? Let me test later.

Time check: ~1h20m elapsed, 2 items done (1 wall, 1 in progress). 6 items to go. I must speed up dramatically.

Let me make a decision for item 4: try 2-3 more variants (10 min), then wall it if needed.

Actually, let me try ONE promising thing: the "copy preference" can be created if the source's returned value is compared/used... hmm.

Hmm, actually! NEW IDEA: what if the source returns `result` but `result` is assigned the byte comparison, and the byte comparison's result is a "sltiu" — the ROM computes it in $2 in place. In nopin, mine computes `sltiu v1,v0,1` (in $3) then copies. What if the byte check expression were the RESULT_DECL (direct return) — then it'd be computed in $2 ✓ (P1) — but P1 lost a `move v0,zero`.

What if I combine: keep the `result` variable structure (2 sets of zero) BUT make the byte-check path return the expression directly? Can't mix.

Hmm, what if the source is:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
        return result;
    }
    return 0;
```
Hmm: the mask path returns `result` (=0) and the ret==0 path returns 0 → two separate `move v0,zero`? They'd be: the mask path → `move v0,zero` (from result=0) then `jr`; the ret==0 path → `move v0,zero`. But gcc might merge them (identical) — hmm, the mask path's block is "result=0; return result" and the else's is "return 0" → both `move $2,zero; jr $ra` → merged ✗ (the ROM has them separate).

Ugh, the ROM's separation comes from the hard-reg set not being merged (the blocks differ: the mask path's block falls through to the byte check).

Hmm, in the ROM, the mask-path's `move v0,zero` (ins 28) is NOT a return block — it's the fallthrough into the byte check. So the mask==0 path (branch at 27 → the epilogue) skips it. That's the gcc bug.

So to reproduce: the source must have `result = 0;` (a set) in the then-path, followed by the byte check, with the "return" happening at the END of the function (not in the branch) — i.e. the source's `result` variable with a single return at the end ✓ = nopin's structure ✓.

So the ONLY difference is the register assignment. Which means: I need gcc to assign $2 to `result` and $3 to `ret`.

Let me try to make `ret` a "local" pseudo (used in ONE block) so that it doesn't compete for the caller-saved regs in global-alloc but gets one in local-alloc (after the globals). Hmm, but `ret` is used in 2 blocks (the test at ins 25 and the mask at ins 26 — wait, are those in the same block? ins 25 `beqz v1` and ins 26 `andi v1,v1,0x8000` — the branch at 25 ends the block; the mask test is in the next block → 2 blocks ✓ global.

What if the source used a single test that combines both? E.g.:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0 && (ret & 0x8000) != 0) {
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    } else {
        result = 0;
    }
```
Hmm: the && fold → the mask test is in the same block as the ret test? gcc would emit `beqz v1` then `andi` in the same block (the && short-circuits → 2 blocks). Hmm.

Also this changes the structure: only 1 `move v0,zero` ✗ (the ROM has 2).

Hmm, but wait: with `&&`, the "result = 0" would be in the else path (1 set) and the byte check in the then path → 2 sets total (sltiu + move) vs the ROM's 3 (move, sltiu, move) ✗.

OK. Let me try to make `ret` local by using it once:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if (ret & 0x8000) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
```
Still 2 uses.

What if:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    result = 0;
    if (ret != 0) {
        if (ret & 0x8000) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
```
= M4 (39 ins, score 8): mine[24] `beqz v0`, mine[25] `move v1,zero` (result=0 in $3), mine[26] `andi v0,v0,0x8000` — hmm, here the result=0 set (ins 25) is BEFORE the mask test (ins 26) — in the ROM the `move v0,zero` is AFTER the mask test (ins 28 vs 26-27). ✗ different order.

Hmm, in the ROM: ins 26-27 (mask test) then ins 28 (result=0). So the source order is: the mask test FIRST, then result=0?? But the source is `result = 0; if (mask) result = ...;` → the set comes before the test. Yet the ROM has the set AFTER the test — because gcc's scheduler moved it (the set is dead on the byte-check path... no wait, it's needed on the mask==0 path).

Ugh, gcc moved the `move $2,zero` down into the mask!=0 path (a scheduling artifact of the hard-reg set — the "bug").

OK. So the ROM's shape has quirks that only the hard-reg pin reproduces.

DECISION: Item 4 → WALL with tag "lreg-return-copy" (the result pseudo must be the return register $2; without the pin gcc keeps the call result in $2 and computes the result in $3, adding a final copy). Best = 8 (M4) or 9 (nopin)? The "best" = the lowest score of a lever-free body = 8 (M4). Hmm, but M4 changed the structure (39 ins). The best score overall = 8.

Hmm, wait. Before walling, let me try 2 quick things (5 min):
(a) `result` declared as `unsigned int` — might change the priority? (no)
(b) the `else` branch written as `result = 0;` vs the if-branch: what if we SWAP the branches:
```c
    if (ret == 0) {
        result = 0;
    } else {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
```
This is a branch inversion (statement order) — the ROM's ins 25 `beqz v1` (ret == 0 → the zero path) ✓ and the mask test in the else ✓. This might change the block layout and the allocation! Cheap to test.

(c) Also: make `ret`'s test `if (ret == 0)` instead of `!= 0`.

Let me test (b) and (c) together in one file, and also a variant where the result variable is `unsigned int`.

Let me write 2 variants and scorethem.
