---
ts: 2026-10-22T00:18:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_k7bHpGsX6RWxQEf7FaGi
---
Interesting! The boolean variant gives 39 ins (matching the target's count!) and score 13. The diff shows:
- mine: `lh v1,174(a1); andi v0,a3,0xffff; and v0,v1,v0; sltiu v0,v0,1; beqz v0` — the boolean is materialized with sltiu ✗ (an extra insn vs the target's `and v0,v0,v1; bnez v0`).
- The target: the AND in $2, `bnez v0` ✓.

So gcc 2.7 does NOT invert the comparison into a branch (it computes sltiu) ✗. Hmm, but the instruction COUNT is 39 in both — because the target has `bnez` while mine has `sltiu` + `beqz` (2 insns) and elsewhere mine has one fewer.

So the boolean approach changes the mask test's shape ✗.

OK. Item 3 remains a wall.

Let me now reconsider item 4 with the same "the returned value must be $2" insight:
The ROM's structure: `move v1,v0` (the call result copied to $3) then the tests on $3, and the result computed in $2.

Lever-free: the call result is in $2 (natural) and the result in $3 (computed) with a final copy.

For the ROM's shape, the call result must be copied out of $2 — which requires $2 to be occupied by the result at that moment. The result's set (`move v0,zero` at ins 28) is AFTER the call ✗.

Hmm, unless the result's pseudo is allocated $2 (global-alloc, via the copy preference) and the call result is a LOCAL pseudo... In item 4, the call result `ret` is used in 2 blocks → a global? and `result` too.

From the earlier analysis: in item 4's nopin, mine had `beqz v0` (the call result in $2) — so the call result got $2 ✓ (natural) and `result` got $3.

For the ROM: the call result in $3, `result` in $2. So `result` must win $2 over the call result.

The call result has a "hard reg copy preference" for $2 (the call's return value is in $2) → it prefers $2 ✓✓. And `result` (the RESULT_DECL) also prefers $2 (the return value) ✓. So both prefer $2 → the priority decides.

`result`'s refs = 3 (2 sets + 1 use), live ~12 → pri = 1*3/12 = 0.25 → 2500.
`ret`'s refs = 3 (1 set + 2 uses), live ~6 → pri = 1*3/6 = 0.5 → 5000 → ret wins $2 ✗.

To flip: make `result`'s live shorter or refs higher, or `ret`'s live longer / refs lower.

Hmm! What if `ret`'s live range were longer? E.g. if the source used `ret` LATER (after the result is computed)? The ROM's structure has the mask test before the byte check ✓.

Hmm, what if the source stored the mask into a variable:
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
Hmm.

What if `ret` is used only ONCE (folding the two tests)? The ROM has both tests (beqz v1 and andi v1) — hmm, the second test uses the masked value, so `ret` has 2 uses. But if the source wrote:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        ret &= 0x8000;             /* in-place: ret = ret & 0x8000 */
        if (ret != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
Here `ret` has 3 refs (set, use in the test, use in the &=) — hmm, plus the in-place set = 4 refs? The `&=` is a set+use of ret → refs = 1 (call) + 1 (test) + 1 (&= use) + 1 (&= set) + 1 (test 2) = 5 → pri = floor(log2(5))=2 → 2*5/live.

Hmm, but that changes the bytes? `ret &= 0x8000` → `andi v1,v1,0x8000` ✓ (the ROM has exactly that!) ✓ and the test `if (ret != 0)` → `beqz v1` ✓.

Hmm, but the ROM's order is: `beqz v1` (ret==0 test) THEN `andi v1,v1,0x8000` THEN `beqz v1`. In my variant: the `andi` comes before the second test ✓ same.

But hmm, the `&=` version has `ret` live longer (from the call to the second test) — the same as now.

Let me think about the priority differently: `result` (the RESULT_DECL) has refs 3, live 12 → 2500. To beat `ret` (5000), result needs pri > 5000: floor(log2(refs))*refs/live > 0.5 → with live 12: floor(log2(4))*4 = 8 → 8/12 = 0.67 ✓ → refs ≥ 4 gives pri 6667 ✓!

So: give the RESULT_DECL 4 refs. How? The RESULT_DECL's refs = the number of references to it: with `result` as a local variable and a single return, the RESULT_DECL has 1 set (the copy) + 1 use (the return) = 2? Hmm, the table isn't available for item 4 (I'd need a dump).

Alternatively, give `ret` fewer refs: `ret` with 2 refs (1 set + 1 use) → pri = 1*2/live.

Hmm, how about this for item 4: use the call result ONCE by folding the tests:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
Hmm, the two tests both use ret.

What if the source computes the mask first:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    mask = ret & 0x8000;
    if (ret != 0) {
        result = 0;
        if (mask != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
Then `ret` has 2 refs (set + the != 0 test) + 1 (the mask) = 3 ✗ same.

Hmm.

OK, let me try the alloc-table approach for item 4 (dump the nopin candidate) to see the actual numbers, then design the lever. That's the systematic path and I have time.

Let me set up the dump for item 4's nopin.

Actually, hold on. Let me reconsider the whole approach for items 3/4/5: all three need "the returned value in $2". In item 6/7 the same pattern was solved by the call-site cast (the call's return value in $2 naturally). Hmm!

For item 4: the ROM's `move v1,v0` copies the call result out of $2. What if the source's call result is consumed via a call-site cast? No, the call is a normal int call.

Hmm, what if the source assigns the call result to a variable of a different type so the copy is needed? E.g. `short ret;` → the truncation ✗.

Hmm, what if the source passes the call result through a function pointer cast? no.

What about making the call result's copy happen because the RESULT_DECL is allocated $2 and the call result's pseudo is live across... hmm, the call result is born at the call; the RESULT_DECL is born at the return. They're not live simultaneously ✗ → both can use $2 ✗ (that's the problem).

Unless the RESULT_DECL is born EARLIER. Hmm: the RESULT_DECL's set = the copy from `result` at the return.

What if the source has MULTIPLE returns? Then the RESULT_DECL is set in several blocks → hmm, still late.

What if the source's returned value is computed EARLY (before the call)? ✗ semantics.

Hmm, hmm. What if the source returns the value of a variable that is assigned BEFORE the call? E.g.:

```c
    result = 0;                      /* before the call */
    ret = func_80133784(1, buf1, (int)buf2);
    ...
```
→ `result` is live across the call → a callee-saved reg ✗ (M5/M6 gave a spill to $s1 and 41 ins) ✗.

Hmm, unless the assignment is dead (overwritten) → gcc DCEs it... In M6 the pre-call `result = 0` was followed by `result = 0` in the branches → gcc kept it (spilled) ✗.

What if the pre-call assignment is to a DIFFERENT variable that is then copied? Hmm.

Let me try the alloc table for item 4 to see the numbers, then decide. Actually, let me first try a couple of cheap variants for item 4:

(a) `ret` declared `unsigned int` (tried Q2 → 9).
(b) the `ret &= 0x8000` in-place variant (changes ret's refs to 4-5).
(c) the source order: put the byte check first? no.

Let me try (b) — it's cheap.

Also for item 5, one more idea based on the analysis: the temps take $2 because the RESULT_DECL is born at the return. What if the RESULT_DECL is born EARLIER — e.g. if the function has an early `return` statement? Hmm, in item 5 there IS an early return: `return 0;` inside the `if (q < 0x40 || ...)` block! So the RESULT_DECL is set there (early!) — hmm, but that's in a different path.

Hmm! In item 5's source: `return 0;` (early) and `return r;` (at the end). The early `return 0` sets the RESULT_DECL early (in that block) → so the RESULT_DECL is live from there ✗ (different path).

Hmm, the RESULT_DECL's live range: it's set in the early-return block AND at the end → the global-alloc sees it as live in the early block and at the end → the live range spans a lot → it gets a callee-saved reg?? Hmm.

OK, let me do the alloc table for item 4's nopin (the most promising) and item 5's... hmm.

Let me be pragmatic: try (b) for item 4 now, and simultaneously dump item 4's nopin alloc table.

Actually, let me try a different, potentially high-yield idea for item 4 first: what if the call result is copied because the source uses the call result in a context where $2 is busy — e.g. if the byte check happened BEFORE the mask test? The ROM's order is fixed ✗.

Hmm, what about: the source assigns the call result to `ret` and then the ROM's `move v1,v0` is actually the copy of the call result into `ret`'s pseudo ✓ (that's what it is). For gcc to make that copy, `ret`'s pseudo must be in a different reg than $2 → i.e. $2 must be taken by something else at that point.

In the ROM, $2 is taken by `result` (the pinned hard reg) — the RESULT_DECL. So if the RESULT_DECL were allocated $2 AND live from the call onward, the copy would happen ✓.

The RESULT_DECL is live from the return ✗. Hmm, BUT: with the early `return 0` inside the branch (item 4 has no early return; item 5 does)...

Hmm, in item 4 the function has ONE return (at the end) → the RESULT_DECL is born at the end ✗.

Hmm, what if the source had an early return? E.g. the source's structure:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret == 0) return 0;      /* early return */
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    }
    return result;
```
This is a restructured version (the `else` branch → an early return). The RESULT_DECL would then be set early (in the `ret == 0` path) → live from there → allocated $2 (with the preference) → and the call result would need a copy ✓✓!

But the byte structure would change: the ROM has the "ret == 0" path as a block with `move v0,zero` at ins 34 (a separate block at the end) — hmm, the ROM's structure:
```
24 move v1,v0
25 beqz v1,+0x88   → ins 34 (move v0,zero) → the epilogue
26 andi v1,v1,0x8000
27 beqz v1,+0x8c   → ins 35 (the epilogue) — hmm, +0x8c = ins 35 = `lw ra` — wait, earlier I determined +0x88 = ins 34 and +0x8c = ins 35.
```
So the mask==0 path jumps to +0x8c (the epilogue) and the ret==0 path to +0x88 (ins 34: move v0,zero → then the epilogue).

Hmm, so the mask==0 path returns the stale $2 (the call result) ✗ (the gcc bug I noted).

With my restructured source (early return for ret==0), the structure would be:
```
24 (call)
25 move v1,v0      ← the call result copied to $3 ✓
26 beqz v1, → the "ret == 0" block (move v0,zero; epilogue)
...
```
Hmm, the order of the blocks might match ✓.

Let me try this restructured variant for item 4 (vR2):
```c
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    int result;
    buf1[0] = 0; buf1[1] = 0; buf1[2] = 7;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf1, buf1);
    buf2[0] = 0; buf2[1] = 0; buf2[2] = (short)0xffe8;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf2, buf2);
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret == 0) {
        return 0;
    }
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    }
    return result;
}
```
Hmm, wait: this changes the structure: the ROM has the "ret == 0" path at the END (ins 34) and the mask==0 path jumping to the epilogue (ins 35). With my restructure, the "ret == 0" path is early (a block with `move v0,zero`) and the mask==0 path returns the stale $2 ✓ hmm.

Let me just try it (cheap) and also the in-place `ret &= 0x8000` variant.

Let me write bothand score.
