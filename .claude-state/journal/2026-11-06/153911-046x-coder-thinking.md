---
ts: 2026-11-06T22:39:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_q8aOw6qND2GiXqSMHHxP
---
Now d ($16) IS in $s0! And s1ang is $17=$s1. Excellent — the mask-in-place worked for the register assignment. But the code has other differences:
- The arg0 copy `move $2,$4` is missing; instead it uses $4 directly for the loads. Target has `move $2,$4` and uses $2.
- `lw $2,32($4)` vs target `lw $2,32($2)`.
- The cast: mine `sll $2,$16,16; sra $16,$2,16` vs target `sll $16,$16,16; sra $16,$16,16` (mine uses a temp $2).
- `lh $6,14($4)` vs target `lh $3,14($2)`.
- iVar4 in $5 vs target $3.
- u5 in $3 vs target $4.

Score 38 but with the right d/s1ang assignment! The mask-in-place changed the ref counts: s1ang (r75) now has 7 refs/22 → pri 6363, but d is 10000 so d wins $s0. 

Now I need to fix the other differences. The target has `move $2,$4` (arg0 copy) and `lw $2,32($2)` — mine uses $4 directly. Why? Because in w6, r72 = arg0 copy got $a0 (4 refs/6 insns, blk 0) — the copy `move $2,$4` was coalesced/eliminated? In the target, arg0 is copied to $v0 and the loads use $v0. Hmm, target: `move $2,$4` then `lh $3,14($2)`, `lh $5,6($2)`, `lw $2,32($2)`. So arg0 is copied to $2 (v0), then the pointer load `lw $2,32($2)` overwrites $2.

In w6, r72 = a0 (the arg0 pseudo stayed in $a0), and the loads use $4. Why did w0 have `move $2,$4`? In w0, r72 = v0 (4 refs/6 insns, blk 0) → the copy `move $2,$4`. Hmm, so in w6 the arg0 copy was assigned $a0 (no copy). 

The difference: in w6, s1ang's mask-in-place changed the refs and the local-alloc qty for r72. In w0, r72 was 4 refs/6 → pri 13333, and it got $v0 (local-alloc). In w6, r72 = 4 refs/6 → pri 13333, blk 0, got $a0. Hmm, why a0? Maybe because $v0 was taken by another local pseudo. Actually r72 in w6 got a0 — meaning the arg0 value stayed in its argument register $a0, and the loads use $4.

Hmm, the target wants arg0 copied to $v0. The arg0 pseudo's live range: it's used for `lh 14`, `lh 6`, `lw 32` — three uses. Then the pointer load overwrites $v0.

Why did w0 get `move $2,$4`? Because local-alloc gave r72 $v0. In w6, local-alloc gave r72 $a0. The difference must be the qty ordering in block 0: w6 has different local pseudos. In w6, r75 (s1ang) is now global (not local), so the local qty list is different, and r72 got $a0 instead of $v0.

Hmm. Why would r72 get $a0? $a0 is the same register as the input arg (no copy needed) — local-alloc's suggestion: r72 is a copy of arg0 ($a0), so it suggests $a0 (qty_phys_copy_sugg). If $a0 is free (arg0 dies after the loads), local-alloc puts r72 in $a0 → no copy instruction. In w0, r72 got $v0 because... hmm, why? In w0, r72 = v0 4refs/6insns blk 0. Maybe the suggestion for $a0 was blocked because arg0 ($a0) is live across... In w0, r72 conflicts? Let me look at the w0 greg dump: "72 in 2" (v0). In w6: "72 in 4" (a0).

The difference: in w0, the call `ratan2` uses $a0 as an argument (the subu result is in $a0). So arg0's $a0 is reused for the call arg. If r72 (arg0) were in $a0, it would conflict with the call's use of $a0. But r72's live range ends before the call (the loads are before the call). Actually the last use of r72 is `lw $2,32($2)` which is before the call. So $a0 is free after.

Hmm, in w6 the `lw $2,32($4)` uses $4 and then the call arg `subu $4,$6,$2` writes $4. So r72 is dead before $4 is reused.

Why did w0 put r72 in $v0? Let me check the w0 lreg: r72 = 4 refs across 6 insns in block 0. In w6, r72 = 4 refs/6. Same. The local-alloc qty order differs because r75 (s1ang) is now global (not in the local list). Maybe the qty order changed such that $v0 was taken by another local qty first in w6, leaving $a0.

Wait, in w6's alloc table, r72 got a0 and the other block-0 locals: r80 v0 (5000), r87 v0 (5000), r91 v1 (5000), r84 a2 (4000), r94 a1 (6666), r99 v0 (40000)... The ones with hard regs are local-alloc'd.

The target: `move $2,$4` means arg0's pseudo is $v0. So we need r72 to take $v0.

Hmm, the difference between w0 and w6: in w0, s1ang (r75) was local and took $s0; in w6, s1ang is global. Does that affect r72's choice? Local-alloc processes each block independently; the presence of r75 in block 0's qty list affects the allocation order/conflicts, but not $v0 availability for r72... unless r75's qty changed the order such that another qty took $v0 first.

Actually, look: in w6 the arg0 pseudo is r72 with 4 refs/6 insns. In w0 it's also r72 4 refs/6. Hmm, but in w0, r72 = v0. In w6, r72 = a0.

Wait, maybe the difference is the copy-suggestion: in w0, the arg0 pseudo is a *copy* of the parameter (d = arg1? no). Hmm, actually r72 is the parameter arg0 itself? "Register 72 used 4 times across 6 insns in block 0" — a parameter pseudo used 4 times. Parameters are born at entry. In w0, r72 got $v0 via a copy suggestion? The target has `move $2,$4`, so the parameter pseudo (arg0) was allocated $v0 and a copy from $a0 to $v0 was emitted.

Why would arg0 prefer $v0? Maybe because of the `lw $2,32($2)` — the pointer load's result is used as a base for `lh $17,18($2)`. Hmm.

Actually, the pointer temp r81 (2 refs, 3 insns, pointer) got $v0 in w0 ("81 in 2"). In the target, `lw $2,32($2)` writes $v0 and then `lh $17,18($2)`. So the pointer temp is $v0 and the arg0 copy is $v0 too (reused).

In w6, r80 = v0 5000 pointer, and the arg0 pseudo r72 = a0. So the arg0 copy was eliminated (arg0 stayed in $a0), and the pointer load uses $4 as base.

So in w6, the target's `move $2,$4` is missing. Why did w0 emit it? Because in w0, the arg0 pseudo (r72) had a *preference* for $v0? Or because r72's qty was allocated $v0 by local-alloc due to the qty order.

Hmm, let me compare the local-alloc for block 0 in w0 vs w6. The difference: w6 has s1ang global, so block 0's local qty list is one smaller. The qty allocation order (by priority) might assign $v0 to r72 in w0 but to something else in w6.

Actually, maybe the real reason is the copy-suggestion: `r72 = a0` (the parameter pseudo is tied to the hard reg $a0, suggesting $a0). In w0, why didn't r72 take $a0? Because in w0, $a0 is used by the call (the subu result is in $a0 = the ratan2 arg). r72's live range ends before the call, so no conflict... Hmm, but local-alloc's conflict is per-insn.

Wait, in w0, is r72 the *parameter* or a *copy*? Let me look at the w0 lreg: "Register 72 used 4 times across 6 insns in block 0". The parameter arg0 is r4 (a0) — the parameter is a hard reg, not a pseudo. A pseudo r72 would be a copy of arg0 created by... hmm, gcc creates a pseudo for the parameter? No — parameters are in hard regs at entry; gcc copies them to pseudos when needed (e.g., if the parameter is used multiple times and the hard reg is clobbered).

In the target: `move $2,$4` creates a copy of arg0 into $v0 (r72). Why? Because arg0 is used across the call? No — arg0's uses (loads) are before the call. Hmm, but the pointer `lw $2,32($2)` uses arg0, and then... Actually, the copy exists because the source `*(s32 *)(arg0 + 0x20)` is evaluated, and arg0 is used 3 times; gcc may copy it to a pseudo to avoid the hard reg being clobbered.

In w6, the loads use $4 directly, so no copy. In w0, the copy to $v0 exists.

Why the difference? Possibly because in w0, the pseudo r72 (arg0 copy) got $v0 due to a copy suggestion from the pointer load: `lw $2,32($2)` — the pointer temp r81 is $v0, and the arg0 copy... no.

Hmm, let me think about the qty tie: `lw $2,32($2)` is an insn where the base (arg0) and dest (pointer temp) are both $v0 — that requires them to be tied. In the target, `lw $2,32($2)`: base $2 = arg0 copy, dest $2 = pointer temp. That's an in-place load: the pointer temp overwrites the base. Local-alloc ties them (combine_regs) if the base dies in the insn. Indeed, arg0 dies after this load? The target: `lh $3,14($2)`, `lh $5,6($2)` use $2 before, then `lw $2,32($2)` uses and overwrites $2. After that, $2 is the pointer. So arg0 dies at the lw.

So r72 (arg0) and r81 (pointer) are tied → same qty → $v0. That's why the copy to $v0 exists: the qty got $v0.

In w6, the arg0 pseudo got $a0 and the pointer got $v0 separately, so no in-place load: `lw $2,32($4)`.

Why didn't the tie happen in w6? The tie requires the base to die in the insn. In w6, maybe arg0 is used again after the lw? No.

Hmm, wait: in w6, `lh $17,18($2)` uses the pointer r80=$v0. And arg0 ($4) is dead after `lw $2,32($4)`.

Hmm, the tie in local-alloc happens if combine_regs succeeds: `lw` with dest r80 and base r72; r72 dies → tie. In w6, the qty for r80/r72... The alloc table shows r80 = v0 (2 refs/4 insns, pointer, pri 5000) and r72 = a0 (4 refs/6). So they were NOT tied. Why? Maybe because in w6, r72 has a copy suggestion for $a0 (from being a copy of the parameter?) and r80... 

Hmm, actually in w6, r72 = a0 with 4 refs — it IS tied to the hard reg $a0? No, "hard a0" means allocated to $a0. And no copy instruction means the parameter's pseudo was coalesced into $a0. Hmm, how can a pseudo be in $a0 with no copy? The parameter arg0 is already in $a0; the pseudo r72 is a *copy* of it... Actually, gcc's parameter handling: at function entry, the parameter is in $4 (a0); gcc creates a pseudo and a `move` from $4. If the pseudo is allocated $a0, the move is a no-op and eliminated (register coalescing in local-alloc's combine_regs? or global?).

In w0, the pseudo r72 got $v0, so a `move $2,$4` was emitted. In w6, r72 got $a0, no move.

So the difference: in w0, r72 was tied with r80 (pointer) into a qty that got $v0; in w6, r72 was not tied (or tied with something that got $a0).

Hmm, why? The tie between r72 and r80 in the `lw`: in w0, both are in block 0 and the tie works. In w6, maybe r80 is now in a different qty... Actually the alloc table in w6 shows r80 v0 and r72 a0 — not tied.

Hmm, the tie depends on the order of processing and `combine_regs`. Maybe in w6, r72 was already "born" with a qty from an earlier insn and the tie failed.

Wait, actually: in w6, the arg0 uses are `lh 14($4)`, `lh 6($4)`, `lw 32($4)`. In w0, the same. Hmm.

Let me look at the difference in the RTL between w0 and w6 around the arg0 copy. Maybe in w6 the `lw` is scheduled differently.

Actually, maybe the real difference is the ORDER: in w6, `lw $2,32($4)` comes BEFORE `lh $6,14($4)`, whereas in the target, `lh 14`, `lh 6`, then `lw 32`. Wait, in w6's asm:
```
lw $2,32($4)
lh $6,14($4)
lh $3,D_80126CB4
lh $5,6($4)
lh $17,18($2)
lh $2,D_80126CB8
```
So the `lw` is first. In the target:
```
lh $3,14($2)
lh $4,D_80126CB8
lh $5,6($2)
lw $2,32($2)
subu $4,$3,$4
lh $3,D_80126CB4
lh $17,18($2)
```
The lw is 4th. So the scheduling differs, which may affect the tie.

Hmm. In w6, the s1ang load `lh $17,18($2)` is after the lw. In the target too.

The key issue: in w6, arg0 stayed in $a0 and the `lw` base is $4. This is because local-alloc allocated r72 to $a0 (its input reg) instead of tying it with the pointer.

Hmm. Maybe the mask-in-place move changed the qty ordering in block 0 such that r72 (the parameter pseudo) took $a0. Let me compare the w0 and w6 block-0 local qtys.

In w0: r72 v0 (4/6), r75 s0 (2/7), r80 v0 (4/4), r81 v0 (2/3), r85 v1 (2/3), r88 a0 (2/2), r92 v1 (2/4), r95 a1 (2/3), r99 v0 (2/2), r100 v0 (4/2), r101 v0 (2/2 block2), r102 v0 (block4)...

In w6: r72 a0 (4/6), r75 global (7/22), r80 v0 (2/4), r84 a2 (2/5), r87 v0 (2/4), r91 v1 (2/4), r94 a1 (2/3), r98 v0, r99 v0, r100, r101...

So in w6, r72 got a0. The tie with r80 (pointer) failed. 

Why? In local-alloc, the tie in `lw` requires `combine_regs(base, dest)`. The base r72 and dest r80. If r72 already has a qty (from the parameter copy) and r80 is born here... combine_regs tries to tie. The condition: `reg_qty[sreg] == -2` (not yet born) or something. Let me look at combine_regs conditions.

Hmm, this is getting deep. Let me try a different formulation: keep u6 as a separate variable but ALSO do something to globalise s1ang without mask-in-place. The mask-in-place gave d=$s0 (great!) but broke the arg0 copy.

What if we do the mask-in-place AND keep the u6 variable for the arms? E.g.:
```
s1ang = s1ang & 0xFFF;   // globalise s1ang
u6 = s1ang;              // copy (coalesced?)
```
Hmm, that might not globalise.

Or: keep the structure but add a *second* reference to s1ang in a later block to make it global, using the arms:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = (s1ang & 0xFFF) + 0x1000; ... }  // extra andi?
```
No.

Alternative: make s1ang global by using it in the arms directly with the mask-in-place, but keep u6 as a separate variable for the compare:
```
u6 = s1ang & 0xFFF;       // block 0
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = s1ang + 0x1000; ... }   // s1ang raw used later
```
But s1ang raw is the unmasked value; using it unmasked is wrong (needs &0xFFF). Unless we do `s1ang = s1ang & 0xFFF;` after u6? Hmm.

Wait, what if:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
s1ang = s1ang & 0xFFF;   // reassign, used in arms
if (iVar4 > 0x800) { t = s1ang + 0x1000; ... }
```
This computes the mask twice (u6 and s1ang) — cse might merge. And s1ang is used in later blocks → global. But the extra andi... cse2 might merge the second andi into u6, eliminating it, but then s1ang dies at the first andi → local again? No wait — s1ang is reassigned at `s1ang = s1ang & 0xFFF` and used later; if cse merges, the reassignment becomes `s1ang = u6` (a copy), which is coalesced → s1ang = u6, still used later → global.

Hmm, that might work: s1ang becomes global with refs including the later uses. But the priority would rise a lot (like mask-in-place, 6363), still below d 10000. And the arg0 copy issue may persist (since it's the same globalisation).

Let me first understand the arg0-copy issue. Maybe it's not caused by the globalisation but by something else. Let me test: take w0 (no pin, u6 separate) and add the mask-in-place *in addition* to u6? No.

Actually, let me check: maybe the arg0 copy difference is due to the *scheduling* order (lw first vs 4th). Let me try to get the target order.

Hmm, actually in w0 the asm order (from the diff) — let me get w0's full asm to compare with the target.

Let me print w0's asm from the dump_w0 dir.
