---
ts: 2026-10-22T15:51:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3SBBI55CIZJ3u36adgeO
---
I can use `--try ... --keep` to get the candidate object and then dump.py to compare instructions. Also I can dump RTL for the candidate TU if I have the TU text. `--keep` prints the scratch path with the candidate TU (t.c). Then run cc1_dumps_tu.sh on that file with DUMP_ROOT under my item dir.

Let me do that: run delever_search --try ... --body --keep on c_struct.c to get the scratch path, then dump RTL (cse2) to see the address equivalence.

Actually maybe a faster empirical approach: try to break the &m pseudo by making the address used in the calls come from a *different* expression than the copy dest. The copy dest `m` and the calls `(void*)m` — both address of the same object. cse merges them because the address expression is identical. If the copy dest were `m` and the calls `(void*)(m + 0)`, still same. What if the calls take `(void*)(int)m`? Same.

What if the calls pass a *pointer variable* that is assigned after the copy:
```
int *mp = m;
*(Mat32 *)m = D_800AE620;
RotMatrixX(..., (void *)mp);
...
```
Then mp is a real variable set once; cse folds `mp = m` into the uses (address sp+16) and the copy dest is also sp+16 → still merged. Hmm.

What if we make the copy dest an *offset* of a pointer that starts elsewhere: `int *mp = m; *(Mat32 *)(mp) = ...` — same.

OK, let me look at the RTL to understand which pass creates the reg. Use --keep + cc1_dumps_tu.sh with DUMP_ROOT.

Actually, wait. Maybe the residual isn't "&m in s1" due to cse but due to *sched1/loop*? The instruction `addiu s1,sp,16` is placed at index 9 (before the copy) — hoisted. That's what sched1 or cse does. Hmm, "sched1-birth-boost" wall tag: "sched1 vs local-alloc birthing-insn priority boost against a local-alloc constant". The &m pseudo's birth insn is the copy's dest address, and sched1 hoisted it. Hmm.

But actually the instruction order in mine: [9] addiu s1,sp,16 — this is before the loads from a1. In target, no such insn; instead each call has addiu a1,sp,16.

So the address pseudo for m exists in mine. In target it doesn't. The difference must be CSE creating an equivalence. The block move dest is a MEM; cse's `find_best_addr` may decide `(plus sp 16)` is worth a register because it appears in a MEM that's used multiple times (the copy's dest + the calls). In w1, the dest is 8 separate MEMs `(plus sp 16 + k)`, each with a different address, so cse doesn't create a single reg for sp+16 (the common base) — it rematerializes each.

So the block move dest address (sp+16) is used once by the move but cse registers it. Hmm.

Idea: make the block move destination not be exactly sp+16 by using an array with a variable index? No.

Idea: do the copy as two struct copies at offsets:
```
*(Mat32 *)(m + 0) = ...
```
No.

Idea: use *two* half-size copies with a different type so the destination addresses are sp+16 and sp+16+16 — two different addresses, neither shared with the calls? They're still sp+16 (first half) → merged with calls.

Idea: shift m's base so the copy dest is not the same as the call address. E.g. declare `int m[10];` and use m+1 as the matrix? Then the copy dest is sp+20, calls use sp+20 → same address again.

The fundamental issue: the copy dest address equals the call address, so cse sees one address with many uses and keeps it.

But in the target, why didn't cse keep it? Maybe because the target's compiler had a different *order*: the copy might come before... no.

Wait. Maybe the target's C did NOT use a block move but 8 separate loads with a *pointer variable* that cse kept in a1 while the destination stores used sp offsets. That's exactly: 8 `lw` from one base register, 8 `sw` to sp offsets. The source base kept in a register — that's what the launder did. Without a launder, cse folds the constant address... unless the source is *not* a constant expression.

Hmm! What if the source is a *struct-typed global variable* accessed via a struct copy but the destination is a local array — that's what we have.

Alternatively: what if the source is `D_800AE620` but with the address computed from a *pointer that cse cannot prove constant* — e.g. an extern pointer variable? Not available.

Let me look at the RTL dumps to see the difference between the launder version (score 0) and c_struct version. Actually, more useful: dump the target? We don't have target RTL, only the ROM object.

Let me dump cse2 RTL for c_struct and see what the equivalence is.

Plan: 
1. `delever_search --try ... --body --keep` on c_struct.c → prints candidate object path + scratch dir (contains t.c). 
2. DUMP_ROOT=$d/dumps bash tools/cc1_dumps_tu.sh <scratch>/t.c cstruct

Then grep the .cse2/.lreg/.greg dumps for the address.

But careful about disk: delete dumps after reading.

Let me do it.
