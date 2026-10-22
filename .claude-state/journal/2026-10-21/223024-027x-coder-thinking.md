---
ts: 2026-10-22T04:30:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4A9jkcrIYiChWTHRWmzK
---
Mine (39 ins):
```
24 beqz v0
25 andi v0,v0,0x8000
26 beqz v0
27 nop
28 lbu v0,30(sp)
29 nop
30 xori v0,v0,0x15
31 j
32 sltiu v0,zero,v0
33 move v0,zero
...
```
Target:
```
24 move v1,v0
25 beqz v1
26 andi v1,v1,0x8000
27 beqz v1
28 move v0,zero    (delay slot)
29 lbu v0,30(sp)
30 nop
31 xori v0,v0,0x15
32 j
33 sltiu v0,zero,v0
34 move v0,zero
```

So indeed in mine, the call result stays in v0 and the RESULT_DECL is also v0 (the boolean is computed in v0). That means gcc merged the call-result pseudo with the RESULT_DECL? Interesting — in mine, the call result pseudo is v0 and RESULT_DECL is... hmm the boolean is computed in v0, so RESULT_DECL = v0. But the call result is also v0. They're different pseudos but share the register since their live ranges don't overlap? Actually the call result is live until the tests (ins 26), and the RESULT_DECL's live range starts... the `move v0,zero` at ins 33 for the zero paths. But the boolean path computes into v0 at ins 28-32. So they're overlapping in v0 with the RESULT_DECL live from ins 27 onwards. Fine, they're different pseudos allocated the same reg because their live ranges don't overlap (call result dead after ins 26).

Hmm, but that's exactly the target structure except the target keeps the call result in a separate reg $3.

In the target the call result is in $3 (v1) — which means gcc allocated `ret` to $3 in the pinned version. Why $3? Because $2 was reserved for the pinned `result`.

So to get the same without the pin, we need $2 reserved for the RESULT_DECL from the start, or the call result to be allocated a different register.

Think about how gcc decides. In the pinned version, `result` is a hard-reg pseudo ($2). The call result pseudo must be in a different reg → v1 ($3).

Lever-free: gcc has both the call-result pseudo and the RESULT_DECL as v-preferencing pseudos. Global allocation picks one for $2.

What if we could make gcc treat the call result as a "call result pseudo" with a hard preference... Actually gcc's call result pseudo is a "call" pseudo which has the hard reg preference v0 but is a separate pseudo (the call's return value in $2 is the hard reg, and the pseudo copies it).

Wait: in mine, there's no `move v0,v0` copy; the call result pseudo IS v0 directly? The `beqz v0` reads $2 directly after the jal — that's the hard reg $2 (v0) being used directly. In the target, `move v1,v0` copies $2 into $3, and then the tests use $3.

So gcc's IR: after the call, the result is in a pseudo (call_result) which is copied from hard reg v0. Normally gcc would coalesce that copy into the pseudo (using v0 as the pseudo's reg). In the target, the pseudo `ret` got $3 instead, so the copy `move v1,v0` remains.

So: what makes gcc allocate the call-result pseudo to $3 rather than $2? A conflict with another pseudo needing $2 in the same region.

The RESULT_DECL is live from... in the target, `result` (pinned $2) is set at the `result = 0` inside the branch and at the boolean. So the RESULT_DECL is live only after the call. But the pin reserves $2 for the whole function (the pseudo has a fixed hard reg, so it's allocated $2 regardless, and other pseudos can't use $2 at any point where it's live... but the RESULT_DECL's live range is short, so why can't the call-result use $2? Because in global allocation, the hard-reg pseudo occupies $2 and conflict graph excludes $2 only where live. Hmm, but the target shows the call result in $3 anyway — because the call-result pseudo and the RESULT_DECL... hmm, the RESULT_DECL is live from ins 24ish (the branch `beqz v1` at 25 requires $2 = 0 on the fallthrough path? no).

Hmm. Actually in the pinned version, `result` is a variable (pinned to $2) that is assigned in the branch. Its live range covers [ins 25ish .. 28ish] and also the merged path. The call result's live range is [24..26]. They overlap at ins 25-26? The `result = 0` assignment happens after the `ret != 0` test → so result's live range starts at ins 25 (in the branch). The call result is live until ins 26 (the andi test). So they overlap → conflict → the call result can't be $2 → gets $3. And the copy `move v1,v0` remains because the call-result pseudo is a copy of hard reg v0.

So the essential structure: the RESULT_DECL (or a variable) must be live at the same time as the call result, and get $2.

In lever-free C, how do we get a variable live across the call? Like:

```
int result = 0;      /* live from here */
ret = call();
if (ret != 0) { if (ret & 0x8000) result = (u8)buf2[6] == 0x15; }
return result;
```
Here `result` is a local var live across the call. But is `result` the RESULT_DECL? No: `return result;` copies result into RESULT_DECL at the return. So there would be: `result` (some reg) → RESULT_DECL ($2) copy at the end → extra `move v0,v1`. Unless gcc coalesces.

Hmm. But wait: in the target, is there a copy at the end? The epilogue: ins 34 `move v0,zero` for the zero path, ins 33 sltiu v0 for the boolean path. Then lw ra... no `move v0, v1` at the end. So the RESULT_DECL is directly in $2.

So in the target, the boolean assignment `result = ...` writes to the RESULT_DECL in $2 (result IS the RESULT_DECL because `return result;` and result is the only assignment → gcc's "return result" is a copy but with the variable being the RESULT_DECL? No.

In gcc, if a function's result variable is a local var with the same type and you `return result;`, gcc (with -fno-... ) may create a copy. But here `result` is declared as a local variable and returned. gcc creates RESULT_DECL and copies. Hmm, but in the original ROM code the pin forces $2 for `result`, so the copy `move v0,v1`? — since the RESULT_DECL is a copy of `result` which is in $2, the copy to RESULT_DECL would be `move v0,v0` (no-op) — gcc would coalesce.

OK. Practical approach: just try many spellings. The score is cheap (1.7s). Let's generate a bunch of candidate bodies and score them.

Candidate ideas:
A. `int result = 0;` declared at top with init, and the original structure:
```
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    int result = 0;
    buf1[0]=0; ...
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
}
```
Here `result` is live across the call → it takes a callee-saved reg maybe ($s?) — no, it's live across a call so gcc would put it in $s0? but $s0 is used for param_1. Hmm, that would change the prologue (sw s0 already there, so maybe reuse). Actually param_1 is copied to s0 at the start. So a second callee-saved would need a new sw → changes the insn count. Unless gcc keeps it in a caller-saved reg across the call — not allowed for a value live across a call (it would be clobbered). So gcc must either spill it or use a callee-saved reg. That changes the code. So A is likely bad.

Hmm! But in the target, is anything live across the call? The RESULT_DECL `result` is set AFTER the call. The call result is copied to $3 immediately.

So the key structural requirement: the pseudo that holds $2 must be live at the same time as the call result. In the target, $2 holds `result` which is assigned 0 inside the `ret != 0` branch — i.e. `result = 0;` happens in the branch (after the test on ret). But the copy `move v1,v0` at ins 24 happens BEFORE the test. So at ins 24-26, $2 contains the call result (hard reg) and $3 contains the copy.

So the conflict: the call-result pseudo (in $3) and `result` ($2) — `result`'s live range starts in the branch after the first test. But the copy pseudo's live range extends to ins 26 (the andi test). Do they overlap? `result = 0` is inside the `ret != 0` branch, which is after the `beqz v1` test at ins 25. The call result is live until ins 26 (andi) — inside the branch. So yes, they overlap in the branch region: the call result is live at ins 25-26 and `result` is live from ins 25 (in the taken branch) → conflict → different regs.

But hold on: in the PINNED version, `result` is pinned to $2 and the call result gets $3 automatically. The pinned pseudo doesn't need conflict resolution — it's a hard reg. But gcc still knows $2 is occupied by `result` in that region so the call-result pseudo can't take $2 (they'd conflict as they're both live). Right.

So lever-free: if `result` is a normal variable (not the RESULT_DECL) and is assigned in the branch, then `result`'s live range starts in the branch → it conflicts with the call result → call result gets $3, result gets $2 — IF result has priority over the call-result pseudo. But then `return result;` copies result ($2) into RESULT_DECL → the copy `move v0, v0`? RESULT_DECL prefers $2 too → the copy is coalesced into nothing (both in $2). Hmm! That's exactly the target structure!

But the original body has `result` pinned; if I remove the pin and keep `result` as a plain local `int result;` with `result = 0;` in the branches and `return result;` at the end — that's the nopin.c candidate! It scored 9. Hmm.

Let me look at nopin.c and its diff. Let me score nopin.c and look at the diff.

Actually, the notes say nopin = 9. Let me check its diff to see the structure.

Let me score nopin.c with a biggertail.
