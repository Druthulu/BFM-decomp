---
ts: 2026-10-22T04:28:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8V0WAmZF2NgnCkDy7cEW
---
Now I have the full target (40 insns):

```
 0 addiu sp,sp,-40
 1 sw s0,32(sp)
 2 move s0,a0
 3 addiu a1,sp,16
 4 move a2,a1
 5 li v0,7
 6 sw ra,36(sp)
 7 sh zero,16(sp)
 8 sh zero,18(sp)
 9 jal func_80149290
10 sh v0,20(sp)      (delay slot)
11 move a0,s0
12 addiu s0,sp,24
13 move a1,s0
14 move a2,s0
15 li v0,-24
16 sh zero,24(sp)
17 sh zero,26(sp)
18 jal func_80149290
19 sh v0,28(sp)
20 li a0,1
21 addiu a1,sp,16
22 jal func_80133784
23 move a2,s0     (delay slot)
24 move v1,v0
25 beqz v1,+0x88
26 andi v1,v1,0x8000
27 beqz v1,+0x8c
28 move v0,zero
29 lbu v0,30(sp)
30 nop
31 xori v0,v0,0x15
32 j +0x8c
33 sltiu v0,zero,v0
34 move v0,zero      (the ret==0 path)
35 lw ra,36(sp)
36 lw s0,32(sp)
37 addiu sp,sp,40
38 jr ra
39 nop
```

So the "move v1,v0" copies the call result into $3 (v1). Then tests on v1. Then the final value in v0 ($2).

Note ins 24 `move v1,v0` — in gcc, this looks like a copy of the call result. Why would gcc emit `move v1,v0`? Because the call result pseudo is in v0 ($2) and it's copied to another pseudo that's used later — i.e. the call result is assigned to a variable that lives in $3.

And why is the final value in $2? Because RESULT_DECL prefers v0.

So the pattern: call result assigned to a local var `ret` which got $3, and the RESULT_DECL got $2.

In the lever-free version, gcc gave the call result $2 and RESULT_DECL $3. Hmm — so the allocno tie-break matters: the RESULT_DECL should get $2 (prefers v0) but the call-result pseudo also prefers v0 and gets first pick.

Wait — actually in the pinned version, the RESULT_DECL is `result` pinned to $2, so $2 is reserved for it, and the call-result pseudo can't have $2, so it takes $3 — and the copy `move v1,v0` is emitted because the call result is in $2 (hard reg return) and gets moved to $3.

So in the target, the call result was in $2 at the call (obviously, jal returns to v0) and copied to $3 because the pseudo for `ret` was allocated $3. And `ret` has more uses (3 uses: != 0 test, & 0x8000 test) → but the RESULT_DECL had higher priority.

In the lever-free version, gcc assigns the call-result pseudo (the copy of the returned value from v0) to $2 directly, so no copy is needed, and the RESULT_DECL gets $3 (or the boolean is computed in v0 directly?).

Hmm, actually in my version the diff shows mine[24] `beqz v0` — so the call result stayed in v0 and was tested there. Then the boolean computed... let's see the whole mine listing to understand. Let me get mine's full listing from the diff output — dt.sh with tail 40 only showed diffs. Let me use `--explain`? Or use the tool's scratch. Simpler: dt.sh --keep prints the candidate object path, then objdump it. But `--keep` writes scratch under .run (fine, under my item dir? it says "keep the per-call scratch and print the candidate object path"). The constraint says "--keep scratch is removed after use".

Alternatively, I can reason without it.

Key question: how to make gcc allocate the call result to $3 and the RESULT_DECL to $2?

Observations about gcc's regalloc: For a non-static function, the return value is placed in $2 (v0) at return: `move v0, <result>`. In the target, the final value is computed directly in v0 and no copy at return (ins 34 `move v0,zero` for the zero path; the sltiu path computes into v0). So the RESULT_DECL is in v0.

In my version, the boolean is probably computed into v1 and copied `move v0,v1` at return — that would be an extra instruction... but mine has 39 ins vs 40, and the diff showed only the region 24-28 and 31-32. So mine's later part matched the target except offsets! Interesting: the diff shows "replace mine[31:32] target[32:33]" — a `j` offset difference. So the rest of the function matches, meaning the boolean IS computed in v0 in mine too?

Wait: mine[29..] must equal target[29..]. Let me get the full mine listing. If mine[29] = lbu v0,30(sp), then the boolean is in v0 in mine too, and the only difference is the missing `move v1,v0` and the extra `nop` at mine[27] (delay slot) vs target's `move v0,zero`.

So mine: after the call, `beqz v0` (call result in v0), `andi v0,v0,0x8000`, `beqz v0` + nop, then lbu v0...

So mine has the call result in $2 and the boolean also in $2 (reusing it after the tests). Target has call result in $3, boolean in $2.

So the difference: target's `ret` variable in $3, and RESULT_DECL in $2, with the boolean computed directly into $2.

In mine: `ret` in $2 (call result pseudo), RESULT_DECL presumably in $3? But then the boolean would be computed in $3 and copied. Unless gcc computed the boolean into v0 directly because the RESULT_DECL is v0... Hmm but then the tests would be on the RESULT_DECL?

Wait. In mine the structure is: ret = call(); if (ret != 0) { if (ret & 0x8000) return (byte)buf2[6]==0x15; return 0; } return 0;

In the direct-return form, each `return expr` sets the RESULT_DECL. The RESULT_DECL is a single pseudo merged at the end; gcc copies it to v0 at the epilogue... but the diff shows no extra `move v0,v1` in mine. Hmm, so in mine the RESULT_DECL is v0 and the boolean computed into v0 directly, while `ret` is also v0?? They'd conflict.

Hmm — maybe in mine, `ret` is in v0 (the call result) and the RESULT_DECL is in... let me actually look at mine's full listing. Let me get it.

Plan: run dt.sh with --keep to get the object path, objdump it, then delete scratch. Actually dt.sh doesn't pass --keep. I can call the tool directly with --keep:

/usr/bin/python3 tools/delever_search.py --try src/shared/ov/func_8014FD54.h func_8014FD54 <file> --body --keep

That prints the candidate object path. Then objdump it. Then remove the scratch (the tool says it cleans up unless --keep). With --keep, I must delete manually. The constraint: "--keep scratch is removed after use" — fine.

But careful: the object is a full TU compile of the header? For a header TU, the tool compiles a stub. Let's try.

Let me do this now.
