---
ts: 2026-10-22T00:03:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_eecJpEaZLQZv0PdkZetL
---
Item 5 (func_801536DC): score 11, 74 vs 73 ins. The diff: the `r` value (the return value) is in $2 in the target (li v0,1; sltu v0,zero,v0) but in mine it's in $3 (v1) with copies (`move v0,a0`, `move v0,v1`, `sltu a0,zero,v0`).

Also the load registers differ: target `lh a0,6(s0); lh v1,160(s0); bne a0,v1` vs mine `lh v1,6(s0); lh v0,160(s0); bne v1,v0`.

Interesting! In the target, the FIRST load is in $4 (a0) and the second in $3 (v1). In mine: the first in $3 and the second in $2.

Hmm, and the target's `li v0,1` (the r=1) is in $2, mine's `li a0,1` (in $4).

So in the target, $4 (a0) is used for the first load, $3 (v1) for the second, and $2 (v0) for `r`. In mine, the loads use $3 and $2 and `r` uses $4.

Interesting: so the target's allocation: r → $2, the first load → $4, the second load → $3.
Mine: r → $4, the first load → $3, the second load → $2.

So the "r" variable and the two load temps are permuted. The target's r is in $2 (the return register ✓ since it's the returned value).

So again the same theme: the returned variable must be in $2.

Interesting: in mine, `r` got $4 — hmm, $4 is a0 (the first argument register, which is free here since the function's param is in s0). And the loads got $3 and $2.

Hmm, so the allocation order went: the first load temp → $3, the second load temp → $2, r → $4? That's odd (why not $2 for the first?).

Hmm, the loads are `lh` into temps that are compared. Note in the target: `lh a0,6(s0)` — a0! Since a0 is dead (the param was copied to s0), using a0 for a temp is fine.

Why does mine use $3/$2 for the loads and $4 for r? Because r's live range spans the whole tail (from `r = 1` to the return) while the loads' temps are short-lived. Hmm, but r should get $2 (the copy preference for the return value).

Hmm! Actually maybe the issue is different: in mine, the comparison `*(s16*)(s0+6) == *(s16*)(s0+0xA0)` produces two temps; in the target, the first is in $4 (a0) and the second in $3 (v1), and `r` in $2.

Let me think: maybe in the target, `r`'s pseudo was assigned $2 because of the copy preference (r → the return register). And the two load temps got $4 and $3 (allocated after). In mine, r got $4 and the loads got $3, $2 → so the copy preference was NOT honored.

Why? Because the copy preference (r → $2) applies only if the copy `set $2, r` exists in the RTL. In mine, the copy exists too (`move v0,v1` at the end) ✓. Hmm.

Hmm, but in mine the RESULT_DECL pseudo gets $2 and r gets $4, then the copy `move v0, v1`... wait, mine[66] `move v0,v1` — so mine's r is in $3 and the result in $2. But mine[55] `li a0,1` → r is in $4 initially, then... hmm, `move v0,a0` at ins 60 (mine) — so r was in $4 and copied to $3? Confusing: `r = 1` in $4, then at the end `move v0,a0` (r → $2)?

Let me re-read mine:
```
51 lh v1,6(s0)
52 lh v0,160(s0)
54 bne v1,v0
55 li a0,1        ; r = 1 → r is in $4 (a0)
56 lh v1,10(s0)
57 lh v0,162(s0)
59 bne v1,v0
60 move v0,a0     ; hmm: r ($4) → $2? or the temp?
...
65 sltu a0,zero,v0
66 move v0,v1
```
Hmm, mine[60] `move v0,a0` = the RESULT_DECL ($2) = r ($4)?? then mine[65] `sltu a0,zero,v0` computes into $4, and mine[66] `move v0,v1`...

Anyway: in mine the returned value ends in $2 ✓ but the computation went through extra copies.

The target:
```
51 lh a0,6(s0)
52 lh v1,160(s0)
54 bne a0,v1
55 li v0,1        ; r = 1 in $2 ✓
56 lh a0,10(s0)
57 lh v1,162(s0)
59 bne a0,v1
60 nop
...
65 sltu v0,zero,v0   ; the result in $2 ✓
```
So in the target, `r` is $2 and the load temps are $4 and $3.

So the fix: get `r` into $2. Since r IS the returned variable (the copy to the RESULT_DECL exists), the preference should apply... but it doesn't in mine.

Hmm, but in the target (pinned), `r` is a hard reg $2 → no allocation decision.

So again the lever-free version must make gcc allocate the returned variable to $2.

Hmm! But here's a thought: in the target, the load temps got $4 and $3 — i.e., the allocator gave the "r" pseudo $2 FIRST (priority/birth) and the loads $3, $4 after. In mine, the loads got $3 and $2 and r got $4.

So in mine, the load temps were born before `r`? The loads are at the end of the function (after `r = 1`)... hmm, the source order:
```c
    r = 1;
    if (*(s16 *)(s0 + 6) == *(s16 *)(s0 + 0xA0) && ...) {
        r = ...;
    }
    return r;
```
So `r = 1` comes FIRST, then the loads. So r is born first → should get $2 ✓ in the target. But in mine, the loads got $2/$3 and r got $4.

Hmm, so in mine the allocation order differs. Interesting: in mine, maybe the loads' temps are born earlier in the RTL because gcc moved the `r = 1` set later (sched1 sinking)? Indeed mine[55] `li a0,1` appears AFTER the first load (ins 51-52) → gcc sank the `r=1` set past the loads ✓ (that's why the loads got the low registers). In the target, the `li v0,1` is at ins 55 (also after the loads at 51-52) ✓ — same position! But the target's r is $2 while the loads are $4/$3.

So in the target, the loads got $4 and $3 (higher regs) while r got $2. In mine the loads got $3/$2 and r got $4.

Hmm, so the difference is which pseudo is "first". Since the loads' temps are born first (they're used before the r=1 set... hmm, in the source `r = 1` comes first but gcc sank it).

OK, whatever the mechanism: the target's r = $2 requires the preference to be honored.

Since these are all "the returned variable must be in $2" cases, maybe there's a general lever: make the returned variable's value NOT need a copy — i.e. make the RESULT_DECL and the variable the same pseudo. In C, that happens when the function returns the variable DIRECTLY and gcc's "return slot" optimization applies... but that only works for aggregates.

Hmm, alternatively: what if the variable is assigned the value and the function's return is `return r;` — gcc creates `set $2, r`. If r is in $2 → no insn. The preference should be honored.

Hmm, hold on! Maybe the difference is the "reg" preference is only honored for pseudos that are NOT "local"... or maybe gcc's local-alloc has a rule: "if a pseudo is used in a comparison that requires a register, allocate the compare temp first".

Honestly, let me try the empirical lever for item 5: change the ORDER of the source so that the loads happen BEFORE `r = 1`:
```c
    if (*(s16 *)(s0 + 6) == *(s16 *)(s0 + 0xA0) && *(s16 *)(s0 + 0xA) == *(s16 *)(s0 + 0xA2)) {
        r = *(s16 *)(s0 + 0xE) != *(s16 *)(s0 + 0xA4);
    } else {
        r = 1;
    }
    return r;
```
Hmm, that changes the structure: the ROM's `li v0,1` at ins 55 is in the fallthrough path (the "not equal" path) → the source is `r = 1; if (...) r = ...;` ✓ (r=1 first). Hmm, but the ROM's ins 55 `li v0,1` comes AFTER the first comparison (ins 51-54) → so in the ROM, `r = 1` was sunk after the first compare. With my alternative source (if/else), the `li v0,1` would be in the else path → also after the compares ✓ possibly the same bytes!

Let me try that variant (call it vR1). Also try: `r` declared before/after other vars, and `r` as `s32` vs `int`.

Hmm, also: in the target the loads use $4 and $3 — i.e., a0 (the first arg reg, dead) and v1. In mine: $3 and $2.

What if the load temps are given a preference for $4 by making them... hmm.

Let me think about the load temps: `*(s16 *)(s0 + 6) == *(s16 *)(s0 + 0xA0)` — gcc creates two temps (or one if it can compare directly with a memory operand: `lh a0,6(s0); lh v1,160(s0); bne a0,v1` — two loads, two temps ✓).

In the target: the first temp → $4 (a0), the second → $3 (v1). In mine: $3 and $2.

Hmm, interesting: the target uses a0 (the caller's first arg reg) — which is dead here. So the allocator used $4 for a temp, meaning $2 and $3 were taken by r and the other temp.

So in the target, r got $2 (highest priority) ✓ and the temps got $3, $4.

In mine, r got $4 (lowest!) and the temps got $3, $2. So in mine, r has the LOWEST priority. Because r's live range is long (from the `li 1` to the return) and the temps' live ranges are short → the priority formula (refs/live) gives the temps higher priority ✓ consistent with the priority model!

And in the target (pinned), r is $2 by force.

So: to make gcc give r a HIGHER priority than the temps, I need r's refs/live to be better, or the temps' worse.

r's refs: 2 sets + 1 use = 3 → floor(log2(3)) = 1 → 1*3/live_r.
The temps: 1 set + 1 use = 2 → floor(log2(2)) = 1 → 1*2/live_temp.
live_r ≈ 20 ins, live_temp ≈ 4 → r: 3/20 = 0.15; temp: 2/4 = 0.5 → the temps win ✓ (observed).

To flip: r needs more refs. E.g. if `r` were used more times. In the source, `r` is used once (the return).

Hmm! What if the source uses `r` in a way that adds refs without changing the bytes? E.g.:
```c
    r = 1;
    if (...) { r = ...; }
    return r;
```
What if we write:
```c
    r = 1;
    if (...) {
        r = *(s16 *)(s0 + 0xE) != *(s16 *)(s0 + 0xA4);
    } else {
        r = r;      /* ??? */
    }
    return r;
```
Ugly.

Hmm, what about the "loop shape" trick: wrap `r = 1;` in a do-while(0) → the ref count gets the loop weighting → r's priority increases ✓✓ (the T10 worked example: "flow REG_N_REFS += loop_depth").

That's the sanctioned do-while trick. Let me test it for item 5:
```c
    do { r = 1; } while (0);  // !FAKE: do-while
```
Hmm, but does the do-while change the bytes? It shouldn't (the loop is optimized away but the ref weight changes).

Let me test that for item 5. And also for item 3 (the "1" variable) — wait, in item 3 the "1" was folded, so no.

For item 5, the do-while might make r's priority higher than the temps' → r gets $2 ✓.

Let me write it and test. Also for item 6, the situation is different: the diff was about a callee-saved register ($s1 vs $2) and the frame size. Let me look at item 6 more closely:

```
mine[35] bnez s1,2ba8 | target[34] bnez v0,2ba4
```
So in mine, the call result went to $s1 (callee-saved, spilled to the stack!) while in the target it's in $2 (v0). And the frame: mine -48 vs target -40 (mine saves $s1).

So in mine, `ret` (the call result) was allocated $s1 (a callee-saved reg) → requiring a stack slot ✗. In the target, the call result is in $2 (v0) ✓ (the natural return register).

So for item 6, the lever-free version must keep the call result in $2. Since a call's result naturally comes in $2, why did mine put it in $s1? Because the pseudo `ret` was assigned a callee-saved register by global-alloc (it's live across... hmm, `ret` is set by the call and used right after → it's not live across any call).

Hmm, global-alloc gave `ret` $s1 because its priority was high (it's a global pseudo? it's used in one block → local?). Hmm.

Anyway: in the target, the call result stays in $2 ✓ (the pseudo was allocated $2 = the natural place). In mine, gcc moved it to $s1 (probably because the copy from the call's $2 to a pseudo was made and the pseudo got $s1).

The lever: make the source use the call result DIRECTLY (no variable):
```c
    func_80161418((void *)a0);
    if (ret != 0) { return; }
```
→
```c
    if (func_80161418((void *)a0) != 0) {
        return;
    }
```
Hmm! But the call's return type is `void` in the header (`extern void func_80161418(void *a0);`) → comparing a void call ✗ (that's the "expand-void-return" tag from moves.md! line 19: "keepalive | func_800D2A24 | WALL expand-void-return — void def (caller TU K&R void decl); target li v0,0/1 on exits; expand drops void return values"). Hmm, but here the pin says the call returns a value in $2 — so the callee's real prototype returns something (s32?). moves.md line 43: "both $2 result pins -> call-site return-type casts ((s32 (*)(s32))f)(a0)".

So the lever for item 6 could be a call-site cast: `if (((s32 (*)(void *))func_80161418)((void *)a0) != 0) { return; }` — that's a "call-site return-type cast" (used in moves.md as a MATCH lever for $2 result pins). But is that allowed here? The constraint says "no signature or decl change outside the body (callers stay as they are)" — a call-site cast inside the body changes the call's type at the call site (the callee's declaration stays). moves.md used it as a MATCH lever ✓.

Hmm, but it might be considered a "lever" (a cast)? It's not in the lever taxonomy (pin/launder/barrier/keepalive). And it's a real C move (call-site cast) per moves.md precedent.

Alternatively, declare a local function pointer variable... that changes the call (an extra indirection) ✗.

Let me try for item 6:
S1: `if (((s32 (*)(void *))func_80161418)((void *)a0) != 0) { return; }`
S2: keep the variable but make it `s32 ret;` — that's nopin (score 8).

Hmm, S1's call: `((s32 (*)(void *))func_80161418)((void *)a0)` — the call returns in $2 ✓ and the comparison is `bnez v0` ✓ (the target's ins 34 `bnez v0,2ba4` ✓✓). That looks right!

But: the cast requires the callee's declaration to be visible; `extern void func_80161418(void *a0);` — casting a void-returning function pointer to s32-returning is a type mismatch but compiles (with a warning?). In C, casting a function pointer type is allowed ✓.

Let me write S1 and test. Also test the do-while variant for item 5.

Let me write both files and score.
