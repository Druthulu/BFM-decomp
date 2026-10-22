---
ts: 2026-10-22T08:14:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_heNYJ0sU7Q8uQ1z5u7Wx
---
HUGE finding! t10:
```c
int t10(int t) { unsigned u; u = t; if (t) { t = u - 1; } return t; }
```
→
```
move v0,a0       ; u = t   <-- THE COPY SURVIVED!
beqz v0,18
nop
addiu v0,v0,-1
jr ra
```
The copy `move v0,a0` SURVIVED because u has 2 uses (the branch test `if (t)` — no wait, the branch tests t, not u).

Hmm, in t10, `u` is used only in `t = u - 1`. But the copy survived! Why? Because the branch `if (t)` means the copy `u = t` is in a block where... hmm. Interesting: with the branch, the copy is in the entry block and the use is in the then-block. Since u crosses a basic block boundary, u becomes a GLOBAL pseudo → and cse (block-local!) can't propagate it!

THAT'S THE KEY: **cse is per-basic-block**. If the copy and the use are in different basic blocks, cse doesn't propagate the copy → the copy survives → local_alloc gives u a different reg → `or v1,v0`!

And in t9 (no branch), the copy and the use are in the same block → cse propagates → gone.

So for 80182ED4, I need the copy `u = t` and the use `t = u - 1` to be in DIFFERENT basic blocks!

In the target:
```
80cc: lh v0,132(s0)
80d4: bnez v0,8134     ; if (t != 0) goto else
80d8: move v1,v0       ; u = t    [delay slot of the branch]
...
8134: addiu v0,v1,-1   ; t = u - 1
```
The copy is in the fall-through block (t==0 path) and the use is at 8134 (the else arm) — DIFFERENT BLOCKS! But wait, the copy is in the delay slot of the branch, so it's executed on both paths but belongs to the fall-through block.

Hmm, so in the target, the copy `u = t` is in the "t == 0" block and the use is in the "t != 0" block. But then how does the value get from the copy to the use? The copy is in the delay slot → it executes before the branch → so v1 holds the copy when jumping to 8134. But the CFG says v1 is defined in the fall-through block, not in the else block — that's a CFG inconsistency! gcc's RTL would place the copy in the block that dominates both (or in the else block). Hmm, since the copy is in the delay slot of the branch, gcc's "delay slot filling" moves an instruction from a dominating block into the delay slot. So the copy is in the block BEFORE the branch (dominating both paths) — i.e. the copy is defined before the branch, and the else-block uses it. So in the RTL, the copy IS in a dominating block → u is a global pseudo → cse (block-local) doesn't propagate!

Hmm, but hold on: in the target's source, the copy `u = t + zr` is INSIDE the else arm:
```
if (t == 0) { A } else { u = t + zr; t = u - 1; }
```
So in the RTL, the copy is in the else block, together with the use. Same block! Then how did it survive cse? Because at cse time, the RHS was `(plus t (reg 0))` → not a copy → cse didn't propagate. And then the delay-slot filler moved it up into the branch's delay slot.

Hmm OK. So for the target, the copy is in the same block as the use, and survived thanks to the plus-with-reg-0.

BUT my t10 experiment shows: if the copy is in a DIFFERENT block from the use, the copy survives cse! So:

```c
if (t == 0) { A } else { u = t; t = u - 1; }
```
Here the copy and the use are both in the else block → same block → cse propagates → dead. (that's our current win.c)

But if I restructure so the copy is BEFORE the branch:
```c
u = t;                    /* before the if */
if (t == 0) { A; t = 0x1E; } else { t = u - 1; }
```
Now the copy is in the entry block and the use is in the else block → different blocks → the copy survives! And u becomes a global pseudo (live across the branch) → local_alloc/global_alloc assigns u a different reg than t → `or v1,v0`!

But: the copy would be scheduled into the bnez delay slot? The delay slot filler picks an instruction from the block before the branch — the copy `u = t` is a candidate! It might land in the delay slot → matching the target's `move v1,v0` at 80d8!

Also the `beqz v0` at 80c4 (the first test) — the copy would be after the `lh` and before the `bnez`, so it could be scheduled into the bnez's delay slot.

But careful: the copy would then execute on BOTH paths (it's before the branch). On the t==0 path, u is dead → but the copy still executes (it's in the delay slot). Hmm, if u is dead on the t==0 path, gcc's DCE might remove the copy... but u is live on the else path, so the copy is live overall. It's placed before the branch → executes always. ✓.

Also: does the copy's placement before the branch change the target's insn order? The target has `lh v0,132(s0)` then `bnez` then `move v1,v0` (delay slot) then the if-block's insns. If our copy is scheduled into the delay slot → same!

But there's a catch: in the target, the `lh` is at 80cc and the `bnez` at 80d4, with `nop` at 80d0 (the delay slot of nothing... hmm, 80d0 is a nop). Wait:
```
80cc: lh v0,132(s0)
80d0: nop            <- delay slot of ... hmm
80d4: bnez v0,8134
80d8: move v1,v0
```
Hmm, 80d0 is a nop BEFORE the bnez. That's odd — normally the nop would be in the delay slot (after the branch). Here we have nop at 80d0 then bnez at 80d4 then move at 80d8. So the bnez's delay slot is at 80d8 = `move v1,v0`. And the nop at 80d0 is a delay slot for... the previous branch? The previous branch is `beqz v0,813c` at 80c4 with its delay slot at 80c8 (nop). So 80d0's nop is just a filler.

OK. So the target's structure: `lh` → `nop` → `bnez` → delay slot `move v1,v0`.

Now, if I write:
```c
t = unk84;
u = t;                       /* copy before the branch */
if (t == 0) { ...; t = 0x1E; } else { t = u - 1; }
```
gcc would emit: `lh v0` ; `or v1,v0` ; `beqz/bnez v0` ... and the copy might be scheduled into the delay slot → `bnez v0, ...` with `or v1,v0` in the delay slot. That matches!

BUT: there's a semantic problem! In the original code, the else arm is `u = t + zr; t = u - 1;` — the copy happens only in the else arm. If I hoist the copy before the branch, the copy executes always (fine, no side effect).

BUT the register allocation changes: u is now live across the whole if/else (a global pseudo) → u would get a callee-saved register (s0/s1) instead of v1! Because a value live across a call... hmm, is there a call in the if-branch? YES: `func_80133784` and `func_8002D4C8` are called in the t==0 branch. So u, being live across those calls, must be in a CALLEE-SAVED register → the asm would be totally different! ✗✗

Hmm. Unless the copy is placed after the calls... but the calls are in the t==0 branch and the copy must dominate the else branch.

Hmm, so hoisting the copy before the branch is bad.

Hmm. But hold on! What if the copy is in the else block but the USE is in a different block? Like:

```c
if (t == 0) { ...; t = 0x1E; }
else { u = t; goto lab; }
lab: t = u - 1;
```
Hmm, that adds a goto → the target has the use at 8134 reached by a branch from 80d4. Actually the target's use at 8134 IS in a separate block (the else block)! And the copy at 80d8 (delay slot) belongs to the block BEFORE the branch (the "t==0" block)!

Hmm, so in the target's RTL, where is the copy? If the copy `u = t + zr` is in the else block in the source, then the RTL has it in the else block. But the delay-slot filler moved it into the bnez's delay slot — that means the instruction was hoisted from the else block into the delay slot of the branch that targets the else block. GCC's delay slot filling CAN do this ("fill the delay slot with an instruction from the target block" — the "cycle skipping" / "reordering" in sched1: `machine_dependent` → `mips_fill_delay_slot` can use an instruction from the block that is branched to? Actually gcc's delay-slot filling picks from the block BEFORE the branch (the fall-through path) usually, but "cycle skipping" allows taking from the target block if the instruction is safe (doesn't depend on the branch's outcome) — in the "reorder" mode, `mips_reorder_insns` can move an instruction from the target block into the delay slot.

So the copy could be in the else block in the RTL and moved into the delay slot. Fine.

OK so back to the plan: I need the copy and the use in different blocks, without a call in between.

In the target, the else block is:
```
8134: addiu v0,v1,-1
8138: sh v0,132(s0)
```
Both the copy (80d8, moved) and the use (8134) are in the else block.

Hmm, so how do I get them into different blocks without a call?

Option: put a `goto` in the else block:
```c
} else {
    u = t;
    goto lab1;
}
lab1:
t = u - 1;
```
This creates two blocks: the else block (with the copy) and the lab1 block (with the use). But gcc would likely merge them (jump threading) → back to one block. Hmm. Unless the goto prevents merging... gcc's `jump` pass merges blocks aggressively. If the blocks are merged, the copy and the use are in the same block again → cse (which runs BEFORE the jump pass? or after?) — cse runs early (before flow/jump). At cse time, the blocks are as the front-end/gcse produced them → the goto creates a real block boundary → cse sees them separately → the copy survives!

But then the jump pass would merge them and the copy would remain in the RTL (as a copy) → local_alloc would give u a separate reg → `or v1,v0`!

But would the merged block produce the same asm? The goto would be eliminated by the jump pass (the block merge), so the asm should be the same as without the goto... maybe. Risk: the "goto" changes the block ordering / branch structure.

Hmm, but actually there's a subtlety: at cse time, is the `goto` present? Yes (gcse/cflow runs before cse? order: cflow2 → jump → cse? Let me recall gcc's pass order: `pass_cflow2` (rebuilds CFG), `pass_gcse`, `pass_cse`, ... and `pass_jump` (the jump threading/branch optimization) comes AFTER cse? In gcc 2.7's pass list: ... `pass_cflow2`, `pass_gcse`, `pass_cse`, `pass_jump`, `pass_loop`, `pass_flow`, ...

Hmm, actually `pass_jump` (jump optimization) comes after `pass_cse`? Let me recall the order in gcc 2.7's `passes.c`:
```
  NEXT_PASS (pass_cflow2);
  NEXT_PASS (pass_gcse);
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_jump);
  ...
```
Hmm, I believe `pass_jump` comes before `pass_cse`? In modern gcc: cflow2 → jump → cse → gcse? Hmm.

In gcc 2.7's passes.c the order is roughly:
```
  NEXT_PASS (pass_fixup_cfg);
  NEXT_PASS (pass_jump);
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_gcse);
  NEXT_PASS (pass_flow1);
  ...
```
Hmm. If `pass_jump` runs BEFORE cse, the goto would be optimized away before cse → the blocks merged → cse propagates → dead. If cse runs first, the copy survives.

Risky but testable! And my tc.sh harness lets me test quickly.

But wait — is a `goto` an acceptable "plain C move"? The brief's constraint list mentions "loop shape, statement order" as allowed moves. A goto to split a block is a structural change that adds a label — the target's source (decompiled) probably wouldn't have it. But it doesn't change the asm (hopefully). Hmm, it's like the "for → goto loop" moves that other shards did ("for -> goto loop (no LOOP notes)"). So gotos are acceptable in this project!

But hold on: is the goto even needed? Let me think about a cleaner way to split the block: the use could be in a different block if there's a natural branch. E.g.:

```c
} else {
    u = t;
    t = u - 1;
}
```
Both in the else block.

Hmm, what about the `if (t == 0)` structure — what if we write it as:
```c
if (t != 0) {
    u = t;
    t = u - 1;
} else {
    ...;
    t = 0x1E;
}
```
Then the else block (with the copy) is the `t != 0` block — the copy and the use are still in the same block. ✗

Hmm. What about making the use happen in the block AFTER the join? Like:
```c
if (t == 0) { ...; t = 0x1E; }
else { u = t; }
t = u - 1;   /* hmm, but the t==0 path sets t=0x1E, so this would be wrong */
```
Semantics broken.

Hmm, what about:
```c
s32 t, u;
t = unk84;
if (t == 0) {
    ...;
    t = 0x1E;
    u = t;        /* hmm */
} else {
    u = t;
}
t = u - 1;  /* wrong for the t==0 path */
```
✗

What about:
```c
t = unk84;
if (t == 0) {
    ...
    t = 0x1E;
} else {
    u = t;
    goto lab;
}
lab:
t = u - 1;
```
Hmm, but then the `t == 0` path falls through to `lab` and would do `t = u - 1` with u undefined. ✗ (need the else path only).

Hmm. So the goto must be within the else arm:
```c
} else {
    u = t;
    goto lab1;
}
lab1:
t = u - 1;
```
The `lab1` block is reached only from the else arm. ✓ semantics preserved.

But: would the jump pass merge the else block and lab1? The else block ends with an unconditional jump to lab1 → the jump pass would merge them (redirect the branch). If the jump pass runs BEFORE cse → merged → cse propagates → dead.

Alternatively, use a construct that keeps two blocks without an unconditional jump. Hmm.

What about making the copy's block end with a conditional branch? Hmm.

Hmm, what about this: **put the copy at the END of the if-branch (t==0 path)**? No — the copy must be in the else path.

Hmm, alternatively: **hoist the copy to just before the branch, but ensure u is not live across a call.** The calls are in the t==0 branch. If the copy is before the branch, u is live across the calls in the t==0 path → callee-saved reg → different asm. ✗

Hmm, unless... u is live across the calls only on the path where it's dead. gcc's live analysis: u is live at the call if u's value is needed after. On the t==0 path, u is not needed → but the call is on that path only. So on the t==0 path, u is dead at the call → u doesn't need to be callee-saved there. But u IS live across the branch into the else path... The calls are inside the t==0 block; u is dead in that block (not used after the branch on that path). So u does NOT need to be callee-saved!

Hmm! Live range analysis in gcc is per-block with "crossing" liveness. u's live range: [copy] → [use in else block]. The call in the t==0 block: is u live there? u's value isn't used after the call on that path → not live → the call doesn't force u into a callee-saved reg.

But gcc's global-alloc handles u (a global pseudo) — it would be allocated a callee-saved reg if it's live across any call... The liveness in the t==0 block: u is defined before the branch (in the entry block) and used in the else block. In the t==0 block, u is not live (it's dead on that path). But gcc's global_alloc computes the "crossing" liveness per block: u is live IN to the t==0 block? u is defined in the entry block and used in the else block, so at the entry block's end, u is live-out. In the t==0 block, u is live-in but dead (not used, and the block doesn't flow to a use). gcc's flow analysis would compute u as NOT live in the t==0 block (since the t==0 path doesn't reach a use). So the call in the t==0 block doesn't constrain u.

So u could get a CALLER-SAVED reg (v1) even if it's live across the branch! Because gcc's local_alloc handles "live across a call within a block" and u is not live at any call.

Hmm, but there's a catch: u's live range crosses the branch. gcc's `local_alloc` vs `global_alloc`: a pseudo that crosses a block boundary is a "global" pseudo, allocated by global_alloc, which allocates callee-saved registers for globals... Actually gcc's global_alloc allocates globals from the "global register" pool (callee-saved) and from call-clobbered regs if they're not live across calls. Specifically, global_alloc picks a reg considering whether the pseudo is live across calls (via the "REG_LIVE_ACROSS_CALLS" / "call_used" computation). If a global pseudo is not live across any call, it can get a call-clobbered reg.

Hmm, in our case u is live from the copy (entry block) to the use (else block), and the calls are in the t==0 block. Is u "live across" those calls? The call is in a block where u is dead → so no.

Hmm, but actually gcc's global_alloc's "live across calls" analysis: a pseudo is live across a call if it's live at the call point. u is dead in the t==0 block (from the block's start, since the block's live-in set... hmm). Let me think: u is defined in the entry block. The entry block flows to two blocks: the t==0 block and the else block. u is used in the else block. So in the entry block, u is live-out (on the path to the else). In the t==0 block, u is live-in per the entry's live-out set... gcc's flow analysis computes live-in of the t==0 block as the intersection? No: gcc computes live-out per block = union of live-in of successors. The t==0 block's live-out = ... the t==0 block flows to the join (where unk84 = t is stored). u is not used at the join. So the t==0 block's live-out doesn't include u → u's live-in for the t==0 block = (live-out of t==0) ∪ (uses in t==0) = {} → u is dead in the t==0 block.

So the calls don't constrain u. u can be allocated a call-clobbered reg (v1).

So the plan:
```c
t = unk84;
u = t;                      /* the copy, in the entry block */
if (t == 0) { ...; t = 0x1E; }
else { t = u - 1; }
unk84 = t;
```
Hmm, but wait: this changes the ORDER: the copy now happens before the branch. The target's copy is at 80d8 (the delay slot of the bnez) — which is right after the `lh` and the branch. So the copy is effectively right before the branch too! ✓

And the `lh` is at 80cc, the `bnez` at 80d4, the copy in the delay slot at 80d8. So the copy is BETWEEN the lh and the bnez in program order (as a delay slot). ✓ That matches "the copy is before the branch".

So this could work! But there's a subtlety: the copy would be scheduled into the delay slot of the bnez. gcc's delay-slot filler picks from the block before the branch. The copy `u = t` is in the entry block → eligible. ✓

Hmm, but also: the `beqz v0,813c` at 80c4 (the first test) has a nop delay slot at 80c8. And the copy can't be scheduled there because it's defined after the lh (80cc). ✓

Let me now also handle: the `t == 0` test uses t (v0). The copy `u = t` must come after the lh. ✓

And the else arm: `t = u - 1` → `addiu v0,v1,-1` where v1 = u's reg. For u to get v1 (not v0), u must conflict with t... u's live range [copy..use] and t's live range [lh..addiu]. They overlap → conflict → u gets a different reg. local_alloc would give u v1 (the next free) and t v0. ✓

Let me TEST this with the real function. Let me write c5:

```c
void func_80182ED4(s32 arg0) {
    s32 t;
    s32 u;
    u16 sp10[10];
    u16 x, y, z;
    if ((u32)((Unkstruct_80182ED4 *)arg0)->unkC2 < 3U) {
        t = ((Unkstruct_80182ED4 *)arg0)->unk84;
        u = t;
        if (t == 0) {
            x = ...; ...
            t = func_80133784(1, sp10, (s32)&sp10[4]);
            if ((t & 0x6000) == 0) return;
            func_8002D4C8(0x83C, 0);
            t = 0x1E;
        } else {
            t = u - 1;
        }
        ((Unkstruct_80182ED4 *)arg0)->unk84 = t;
    }
}
```

Wait, but there's an issue: `u = t` is executed even when t == 0 (the t==0 path) — u is dead there, but the copy insn still executes. That's fine for the asm (the copy is in the delay slot).

Hmm, but hold on: if u is dead on the t==0 path, gcc's DSE might... no, the copy is before the branch, it's executed once.

Hmm, but another issue: with `u = t` before the branch, gcc might schedule the copy into the delay slot of the `beqz v0,813c` (the first branch at 80c4)? No — the copy is defined after the lh (80cc) which is after the beqz (80c4). So the copy can only go into the bnez's delay slot. ✓

Let me test it!

Also note: the target's `move v1,v0` is in the delay slot, and the target also has `nop` at 80d0. Fine.

Let me write c5 and score it. Also c6: the same but with the copy placed after the `if (t == 0)` test but before the branch... same thing.

Let me go.
