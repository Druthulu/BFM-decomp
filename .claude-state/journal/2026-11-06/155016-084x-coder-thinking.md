---
ts: 2026-11-06T22:50:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ITPWo41wJt4BSv6rWG9G
---
The scheduler selects among same-priority insns by potential hazard (function unit). This depends on the pipeline model, not the ref_count. The ref_count difference in the dump is just informational (from `insn_ref_count` used for the "insn is dead" analysis?).

The scheduling difference between w0 and w6 must come from a dependency difference. Let me look at the dependency: in w6, s1ang is reassigned (`s1ang = s1ang & 0xFFF`), which is insn 69? The bne (insn 72) depends on insn 69 (the and). In w0, the bne depends on insn 69 (u6 = and). Same.

Hmm, but the dump shows insn 72 ref_count 2147483529 (w6) vs 2147483528 (w0). The high bit set suggests a special encoding (0x80000000 | count). The difference is 1 vs 0 in the low bits: the number of something. Let me look at the dump print at line 3648.

Actually, maybe the ref_count is the number of "references" for the dependence analysis, and the bne in w6 has one more because s1ang is also live (used in later blocks?). Hmm.

Honestly, the schedule difference might be due to the REG_DEAD/live info: in w6, s1ang (r75) is live across more blocks, so the bne's ref_count includes it.

Given the difficulty, let me try to see if the *arg0 copy* can be restored by a different means. The tie between arg0 and the pointer requires arg0 to die at the lw. In w6, the schedule puts the lw first. What if I reorder the SOURCE so the pointer load comes after the lh uses? The source order is: s1ang = *(s16*)(*(s32*)(arg0+0x20)+0x12) — the pointer load is part of this statement, which is BEFORE the u5 statement. In the target, the lw is before the lh uses... but the target's arg0 copy exists because the lw is after the lh uses (the scheduler reordered).

Hmm, wait: in the target, the order is lh14, lh(D_80126CB8), lh6, lw, subu, lh(D_80126CB4), lh(s1ang), jal. So the lw is after the lh uses. And the s1ang lh is after the lw (it needs the pointer).

In w0, the same order. In w6, the order is lw, lh14, lh(D_80126CB4), lh6, lh(s1ang), lh(D_80126CB8), subu, jal.

So in w6, the scheduler put the lw early. The sched priorities are the same; the difference is the tie-break.

Hmm, let me try adding a do-while around the pointer load or changing the statement order to influence the scheduler. For example, move the s1ang load AFTER the u5 computation (w3 did this, score 45). In w3, the s1ang load was after u5 in the source, and sched1 still ordered it before the call (good) but the alloc was off.

Let me try: w6 with the s1ang load statement after the u5 statement (source order swap) + mask-in-place. Maybe the scheduler then gives the w0 order.

Let me create w10 = w6 with the s1ang load after u5. And w11 = w6 with `s16 s1ang`.

Actually, let me think about the "move $2,$4" more. It exists because the arg0 pseudo r72 got $v0. In w6, r72 got $a0 (no copy). The difference is the tie with the pointer (r80). In w6, the tie failed because r72 was live after the lw.

If the tie succeeded, r72 would be $v0 and the copy emitted. So I need the tie to succeed: r72 must die at the lw. That requires the lh uses to be before the lw.

The scheduler decides. Can I influence it via C? The scheduler's order depends on the insn priorities (critical path). The priorities are the same. The tie-break is the hazard. Hmm.

What if I change the source so the lh uses are *before* the lw in the RTL (pre-sched)? E.g., compute the ratan2 arguments before the s1ang load:
```
d = arg1;
u5 = (ratan2(*(s16*)(arg0+0xE) - D_80126CB8, D_80126CB4 - *(s16*)(arg0+6)) - 0x400) & 0xFFF;
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
...
```
That's w3 (score 45). Hmm, w3 had the lw first too? Let me check w3's alloc: r72 = s0 (4 refs/8, crosses a call) — a local pseudo got $s0! Interesting: in w3, r72 (arg0) crossed a call and took $s0. So the schedule/ties differ.

Hmm.

OK, let me try a batch of variants and score them. I'll create w10-w15 with various tweaks:
- w10: w6 but s1ang load after u5.
- w11: w6 with s16 s1ang.
- w12: w6 with the mask on u6 kept: `u6 = s1ang & 0xFFF; s1ang = u6;` hmm.
- w13: w0 + mask-in-place of a different variable (u6 = s1ang & 0xFFF; then s1ang = u6; use s1ang in the arms).
- w14: w6 with the declarations reordered.
- w15: w6 with `q` computation using a different form.

Let me think about w13: 
```
u6 = s1ang & 0xFFF;
s1ang = u6;              // copy, coalesced
if (u6 == u5) return 0;
iVar4 = u5 - u6;
...
if (iVar4 > 0x800) { t = s1ang + 0x1000; ... }   // s1ang used in the arm
```
Here the load pseudo is used only in block 0 (u6). The copy s1ang = u6 makes s1ang a global pseudo used in the arms. But the LOAD pseudo stays local. So d still conflicts $s0. No good.

Hmm. Unless the copy is `s1ang = s1ang & 0xFFF` and cse merges...

OK let me think about what makes the load pseudo global: it must be referenced in 2+ blocks. The only reference is the and. So the and must be in a different block than... the load is in block 0. If the and is in block 2, then the load pseudo is global. But then the compare (block 0) needs the masked value → the and must be in block 0.

Unless the compare uses the load pseudo RAW and the and is elsewhere. The compare is `u6 == u5`. If we write `if (s1ang == u5)` where s1ang is raw, that's wrong (s1ang isn't masked). BUT what if we mask u5 instead? `if (s1ang == (u5 & 0xFFF))` — u5 is already masked. Then the compare is `s1ang == u5` (raw s1ang vs masked u5) — semantically wrong unless s1ang is already masked.

Hmm, what if we mask s1ang at the LOAD: `s1ang = (*(s16 *)(...)) & 0xFFF;`? Then the load+and are one expression in block 0. The pseudo for the and result is s1ang (global, used in later blocks). The load's result pseudo is local (used once by the and in block 0). Hmm, the load pseudo would be local.

Wait, but the target has `lh $17,18($2)` then `andi $17,$17,0x0fff` — the load result and the and result are the SAME register $s1. If the load pseudo is local and the and result is global, the and result (s1ang) would be assigned by global-alloc. The load pseudo (local) takes $s0 (if it crosses the call)... 

Hmm, wait: if the source is `s1ang = (*(s16*)(...)) & 0xFFF;` with s1ang global, then the RTL is: temp = load; s1ang = temp & 0xFFF. The temp is local (2 refs, block 0, crosses the call) → takes $s0! Same problem.

Hmm, unless the temp and s1ang are tied/coalesced so that s1ang's hard reg is used and the temp is eliminated. In the target, they share $s1.

Hmm, in the target, the load pseudo (r75) is LOCAL and takes $s1 (because $s0 is pinned). The and result (r77) is global and prefers r75's reg → $s1. So they share.

Without the pin, the load pseudo takes $s0. To avoid, the load pseudo must not cross the call... or be global with lower priority than d.

If the load pseudo is global with priority < d (10000), d wins $s0. The load pseudo (2 refs/7 = 2857) < d. So making the load pseudo global works IF its priority stays low. The mask-in-place makes it 7 refs/22 = 6363 (still < d's 10000 with the do-while). Good.

So the mask-in-place is the way. The side effects are the schedule/arg0.

Hmm, let me try to fix the schedule by changing the *statement order* in the mask-in-place version. The schedule difference is the bne's ref_count, which comes from the live-range structure. Maybe if I keep u6 for the compare but reassign s1ang for the arms, the live ranges change.

w13: 
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
```
plus, to globalise the load pseudo, add a reassignment of s1ang in a later block... 

Hmm, what if the arms use s1ang masked via a reassignment placed inside the first arm? Like:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { s1ang = s1ang & 0xFFF; t = s1ang + 0x1000; iVar4 = u5 - t; }
```
The reassignment is in the first if arm (block 3). The load pseudo is used in block 0 (u6) and block 3 (the reassign) → global. But cse2 might merge the and into u6's value (the arm is in the same EBB as block 0? The branch to block 3 is from block 2's `bne`; cse follows if single ref → same EBB → merges → the load pseudo's use becomes u6 → local again).

Hmm, unless the arm block has multiple preds. The first if arm: `if (iVar4 > 0x800) {...}` — the arm is entered from the bne in block 2, single ref. So cse follows.

The second if arm: `if (iVar4 < -0x800) {...}` — the bne in block 4 (after the merge), single ref. Hmm.

What about the merge point (after both ifs, before the div)? That block has 2 preds. If s1ang is used there (e.g., `q = iVar4 / d` — no s1ang). Hmm.

OK, I'm running low on productive ideas. Let me do a batch of empirical variants and score them. Then decide on MATCH vs WALL.

Let me create:
- w10: w6 with s1ang load after u5 (source reorder).
- w11: w6 with `s16 s1ang`.
- w12: w6 with the do-while around the load too.
- w13: w6 but with `u6` kept and the arms using s1ang (masked at the compare)...
- w14: w6 with `t` declared inside the arms (scope).
- w15: w6 with `d` as `s32 d = arg1;` (init at decl).

Let me write them.

Actually, let me reconsider the arg0 copy once more. The tie between arg0 (r72) and the pointer (r80) happens if arg0 dies at the lw. In w6, the schedule puts the lw first. But maybe I can make the tie happen regardless by making the pointer load the ONLY use of arg0? No, arg0 is used for the lh's too.

Hmm, what if I introduce a separate variable for the pointer base so arg0's last use is the lw? E.g.:
```
s32 p = *(s32 *)(arg0 + 0x20);
s1ang = *(s16 *)(p + 0x12);
```
Then arg0's uses: lh14, lh6, and `lw p` — the lw is the last use → arg0 dies at the lw. The tie would then be between arg0 and p. Hmm, but the order still matters: if the lw is scheduled first, arg0 is still used by the lh's after.

The target has arg0's last use at the lw. So the source should have arg0's last use at the lw, and the scheduler should place it after the lh's.

Hmm, what if the arg0 uses are reordered in the source so the pointer load is last? The source: `s1ang = *(s16*)(*(s32*)(arg0+0x20)+0x12)` is first, then u5 uses arg0. So arg0's last use in the SOURCE is in u5's statement. The scheduler can reorder within the block.

I think the schedule difference is a consequence of the mask-in-place, and it's hard to control.

Let me just run the batch and see.

Actually — wait. Let me reconsider the w6 diff once more. The missing `move $2,$4` and the `lw $2,32($4)`: in w6, arg0 stays in $a0. But the target's arg0 copy is $v0. What if I explicitly copy arg0 to a variable?
```
s32 a0 = arg0;
```
Then the copy exists in the source. If a0 gets $v0... Let me try: declare `s32 base = arg0;` and use base for the loads. Then gcc must emit the copy (unless coalesced). If base is assigned $v0, we get `move $2,$4`. If it's assigned $a0, the copy is eliminated.

In w0, the copy exists naturally. In w6, it's eliminated. With an explicit `base = arg0`, local-alloc might keep the copy if base conflicts with arg0... Hmm, actually the copy is coalesced if possible (combine_regs). 

Hmm, what if I use arg0 in a way that prevents coalescing, e.g., use both arg0 and base? No.

Let me try w16: explicit base copy.

Actually, let me look at the target's RTL: `(insn 4 (set (reg/v:SI 72) (reg:SI 4 a0)))` — a copy of arg0 to r72. In w6's RTL, is there an insn 4? Yes: "(insn 4 2 6 (set (reg/v:SI 72) ...)". So the copy EXISTS in the RTL; it's just allocated $a0 (coalesced, so the move is a no-op and the assembler drops it). Wait, if r72 is allocated $a0 and r4 is $a0, the move `$a0 = $a0` is a no-op. Does the assembler emit it? No, the `movsi` with the same reg is eliminated by the assembler (or by final). So the instruction count is 74.

In w0, r72 = $v0 → `move $2,$4` emitted.

So the question is r72's assignment: $a0 (w6) vs $v0 (w0). The tie with the pointer (r80/r81) determines it: in w0, r72 and r81 are tied → $v0; in w6, they're separate.

The tie requires r72 to die at the lw. In w6, r72 is live after the lw (because the lh uses are after). 

Hmm, so the ROOT issue is the schedule: the lw is placed before the lh uses in w6.

Let me try to force the schedule by making the s1ang load depend on something that forces it late... or by reordering the source so the lh uses come first.

What if I write:
```
d = arg1;
u5 = (ratan2(*(s16 *)(arg0 + 0xE) - D_80126CB8, D_80126CB4 - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF;
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
do { d = (s16)d; s1ang = s1ang & 0xFFF; } while (0);
...
```
(w10: w8 with the load after u5). Let me test.

Let me also test the pure w0 structure (u6, do-while cast) with the load after u5 (w3 was that, score 45 — but with the plain cast? w3 had the do-while cast and the load after u5 → 45).

Hmm.

Let me batch: w10, w11, w12, w16.

w10: w8 with the s1ang load after u5.
w11: w6 with s16 s1ang.
w12: w6 with the load also in a do-while.
w16: w6 with an explicit base copy.

Let me write them.
