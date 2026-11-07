---
ts: 2026-11-06T15:08:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lfECNdqp2GI7M2o2aaYg
---
The fold happens in cse: insn 21 becomes `(set (reg a0) (const_int 0))`. Note cse processed block "2 to 24" — a block that ends at the code_label 24. So `s0=0` (insn 14) and the shift (19/21) are in the SAME cse block. 

So if we insert a code label between insn 14 and insn 19, cse would split. The do-while(0) didn't create one (jump pass removed it before cse). Wait — pass order: jump is before cse. The .jump dump shows no extra label.

So we need a label that survives jump1. A `goto` into a label? jump1 (jump_optimize) does thread/delete jumps. A conditional branch that it can't resolve would survive.

Cheap idea: an `if` with a condition that's opaque but whose body is empty, and where both arms converge:
```
s0 = 0;
if (s1) { }
a0 = s0 << 10;
```
Empty body → removed, no label.

What about a conditional that sets s0 to 0 in both arms:
```
s0 = 0;
if (s1) s0 = 0;
a0 = s0 << 10;
```
The if creates a branch and a join label. jump1 keeps the branch (condition opaque). The join label at the merge would split the cse block. But cse would still know s0=0 in both arms and at the join (it intersects equivalence classes; both arms set s0=0, so the join still knows s0=0 — cse's "Processing block" may span the join? cse splits at labels? Let me check: cse processes extended basic blocks; a join label with multiple predecessors ends an EBB. In the cse dump above, "Processing block from 2 to 24" and "from 26 to 89" — labels split. So a join label would split the block, and then at the start of the next block cse doesn't know s0=0 (it resets). But would combine/flow still fold? combine uses LOG_LINKS; after a join, the LOG_LINK for the shift would point to... the shift's operand s0 is a REG; combine's get_last_value follows LOG_LINKS to the set of s0 in the same block. If the shift is in a block where s0 wasn't set (the join block), LOG_LINKS would be absent (or point to a note). So combine wouldn't fold either.

But this adds instructions: `if (s1) s0 = 0;` compiles to a branch — extra code (bnez + delay slot) unless optimized. Since both paths do the same thing, jump.c might merge them: `if (s1) s0 = 0;` — jump1's "if_then_else" optimization might delete the branch because the then-block is empty-ish? Actually the then-block is `s0 = 0` and the else path falls through to `a0 = s0<<10`, but s0=0 is also set before the if. jump1's `thread_jumps` / `delete_jump` might see the condition and... it won't delete a conditional branch just because the body duplicates a previous assignment (that's cse/combine territory).

Hmm, risky but testable.

Another cheap label: `if (s1) s0 = 0; else s0 = 0;` — gcc front end folds identical arms into `s0 = 0`? Possibly.

What about a *loop* that executes at least once and has a label that survives: `do { s0 = 0; } while (s1 & 0);` — condition is constant 0, jump1 deletes.

What about `for (;;) { s0 = 0; if (1) break; }` — jump1 folds.

Hmm, we want the cheapest surviving label. What about a `switch`? too heavy.

Alternative: exploit the existing loop! The code_label 24 (NOTE_INSN_LOOP_BEG) is right after insn 21. If we move the `a0 = s0 << 10;` *into the loop* but keep semantics... we showed the loop-top form gives one sll. Hmm.

Wait — what about placing the pre-loop shift AFTER the loop-entry label but before the loop body? Like:

```
s0 = 0;
do {
    a0 = s0 << 10;
    ...body...
    s0 = s0 + 1;
    a0 = s0 << 10;
} while (s0 < 4);
```
Then a0 is set at loop top; the first iteration's a0 = 0<<10 — but at loop top s0 is not a known constant to cse? Actually cse processes the loop body block; the value of s0 at loop top comes from two paths (entry s0=0 and back edge s0+1). cse splits blocks at labels — the loop head label 24 starts a new block. At the start of that block cse doesn't know s0. So `a0 = s0 << 10` at loop top stays sll. 

But then the loop has TWO a0 assignments (top and bottom) — one redundant? No: the top one sets a0 for this iteration; the bottom sets it for the next. If both are present, the bottom is redundant with the next iteration's top. gcc might CSE/eliminate: the bottom `a0 = s0<<10` and the top `a0 = s0<<10` — same value (s0 at bottom == s0 at next top). cse could merge them: after the bottom set, the top set is redundant → deleted, giving one sll in the delay slot. That yields 32 ins vs 33.

Unless we *only* put it at the top (no bottom): then the first iteration computes it at top; after the loop the a0 is dead. The static code has one sll at the loop top. Target has two (pre-loop + delay slot). Hmm.

But wait: with only the top assignment, reorg might steal the top sll into the bnez delay slot for the back edge — but that's incorrect for the first iteration (delay slot executes only on the back edge, and the top is the branch target; stealing from target to delay slot is legal only if the insn is dead on the fall-through... The delay slot executes on both taken and not-taken? No! In MIPS, the delay slot always executes. reorg's "steal from target" moves the insn from the branch target to the delay slot, which executes even when the branch is not taken. If the insn is dead on the fall-through path (after the loop, a0 is dead), it's legal. So it CAN steal. Then the loop top starts with sll v0 and the delay slot has sll a0,s0,0xa. But the FIRST iteration: the branch is at the bottom; on first entry we jump/fall into the loop top directly (the do-while body), so the top's sll was stolen → first iteration doesn't execute it → a0 uninitialized in first iteration → WRONG codegen (but the compiler wouldn't do that if a0 is live in the loop). Since a0 is used in the loop body, stealing would break it. reorg checks liveness: the stolen insn is dead on the fall-through (exit) path but live in the loop; the delay slot executes on the back edge (loop continues) and on the exit... hmm, the delay slot executes always. On the exit path a0 is dead, so it's safe. On the back edge, it sets a0. But the first iteration enters the loop top WITHOUT passing through the delay slot. So if the top insn is stolen, first iteration lacks it. reorg's analysis: it considers the insn at the branch target as executing each iteration, and stealing moves it to the delay slot which also executes each iteration (except the first entry). reorg is supposed to check "the target insn is not needed on the path from loop entry"? Actually the standard MIPS delay-slot fill from the target ("steal") is used when the branch target insn can be executed in the delay slot because the delay slot executes regardless; but that's exactly wrong for loop entry unless the target insn is dead on entry. reorg checks `insn` liveness at the branch and whether the target insn is the first insn. Hmm.

This is getting too speculative. Let me just test candidate shapes empirically. The compiler will tell us.

Candidate list (all launder-free):
e1: `if (s1) s0 = 0;` between init and shift.
e2: `if (s1) s0 = 0; else s0 = 0;`
e3: top-shift loop:
```
s0 = 0;
do {
  a0 = s0 << 10;
  v0 = ...
  ...
  s0 = s0 + 1;
  ... (remove bottom a0)
} while (s0 < 4);
```
e4: both top and bottom shift.
e5: `s0 = 0; while (s1) { s0 = 0; break; }` hmm.
e6: `s0 = 0; do { } while (0);` empty (C0535) before shift — probably removed.
e7: use `goto` with a label before the shift and a jump from an opaque condition:
```
s0 = 0;
if (s1 & 0x10000) goto L;
L:
a0 = s0 << 10;
```
jump1 removes jump to next insn.
e8: two-arm branch with different expressions that both evaluate 0 but are not statically equal:
```
s0 = 0;
if (s1) s0 = s0 + 0; else s0 = s0;
```
The then-arm folds to s0 = s0 (deleted); the else is empty; branch might be deleted.

Hmm, how about making the branch body do something opaque: `if (s1) s0 = s0 & 0;` — then cse knows 0 in the arm too.

Actually, the key is: after the join, cse must NOT know s0. If both arms set s0 to 0, cse's intersection gives 0. If one arm sets s0 to 0 and the other leaves it (from before = 0), cse... the before value is 0; cse would propagate into the join? cse processes blocks linearly; at a join it intersects. The fall-through arm would carry s0=0 equivalence from before the branch; the taken arm sets 0. Intersection: both 0 → still 0. Hmm.

To make cse NOT know 0 at the join, one arm must set s0 to an unknown value. But then the runtime value might not be 0.

What if one arm sets s0 = s1 - s1 (unknown to cse? but it's provably 0... cse might fold s1-s1? cse's fold_rtx may fold x-x to 0 for the same register? Not sure). Or `s0 = s1 & 0`? folds to 0. Or `s0 = s1 * 0`? folds.

What about `s0 = (s32)(u16)(s1 - s1)`? probably folds.

Hmm what about using the *loop counter* trick: initialize s0 from itself in a way... 

NEW IDEA: What if we make `s0` have more than one set BEFORE the shift, where the extra set is the loop's `s0 = s0 + 1` seen by combine? No, order.

ANOTHER IDEA: combine's condition `reg_n_sets == 1` — for a register set only ONCE in the whole function, combine folds regardless of labels. If s0 were set only once (init) and the loop used a different counter... no.

Let me reconsider. Maybe the answer is much simpler: maybe we can get the target's `sll a0,s0,0xa` by having the shift read a variable that cse can't const-prop because it's *not a pseudo but a hard register*. moves line 134: "target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold". So hard registers are opaque to combine. 

What if s0 is a `register` variable? Not allowed ("no `register` vars"). Hmm, but the constraint says no `register` vars. Right.

What about using the existing pinned `a0`/`a1`? They're hard regs but assigned via pins.

Hmm, what about a value that comes from the *stack*: e.g., read a local array element that was set to 0? gcc might keep it in memory or fold. E.g.:

```
s32 t[1];
t[0] = 0;
s0 = t[0];
a0 = s0 << 10;
```
gcc would likely keep t in memory (address taken) — extra stores/loads.

What about `s0 = 0;` where s0 is `volatile`? banned-ish.

Hmm, let me look at what the ORIGINAL launder does at the RTL level in the tree's own body — maybe I can mimic its *effect* with a plain-C construct that gcc treats as an opaque set. The asm creates `(set (reg s0) (unspec))`. A plain-C construct that creates an opaque set: an assignment from a function call result, or from a volatile read.

What about assigning s0 from `((Unkstruct_800B5CB8*)s1)->unk70` and then... no, the value must be 0.

WAIT. Actually — do we need s0's pre-loop value to be 0 *as known by the compiler*? What if we *reorder*: set s0 = 0 AFTER computing a0? Like:

```
a0 = s0 << 10;   // s0 not yet initialized!
s0 = 0;
```
No — undefined behavior, but gcc 2.7.2 might... no, it would use garbage and the object would differ.

What if we initialize s0 = 0 via the loop-carried mechanism: 
```
s0 = 0;
a0 = s0 << 10;
```
→
```
s0 = 0;
a0 = (s0 << 10);
```
same.

Hmm, what about making a0's pre-loop value come from a *copy of a variable that cse can't resolve*, e.g., a variable assigned in a conditional earlier:

```
s32 t;
if (s1 == 0) t = 0; else t = 0;
a0 = t << 10;
```
Both arms 0 → cse intersects to 0. But maybe cse doesn't propagate through a join with two identical constants? It might. Worth a test — cheap.

Actually, let's test a batch of these structural candidates and see. Even if they add instructions, I learn what cse does. Let me generate e1..e8.

Actually, better idea first: check `if (s1) s0 = 0;` where the then-arm is a *store to a dead variable*? no.

Hmm, hold on. Let me reconsider the loop shape. What if we keep the structure but make the pre-loop `a0` assignment the SAME expression as the loop bottom by hoisting it via a goto that jumps into the loop? 

```
s0 = 0;
goto entry;
do {
  ...
  a0 = s0 << 10;
} while (s0 < 4);
```
No.

What about:
```
s0 = 0;
do {
  if (s0 == 0) a0 = 0; else a0 = s0 << 10;   // no
```

OK let me test the batch. I'll write gen2.py.

Candidates:
e1: `if (s1) s0 = 0;` after init.
e2: `if (s1) s0 = 0; else s0 = 0;`
e3: top-shift loop (move pre-loop shift to loop top, keep bottom).
e4: top-shift loop only (no bottom).
e5: `while (s1) { s0 = 0; break; }` after init.
e6: `do { } while (0);` after init (empty).
e7: `if (s1 & 1) { } else { }` — empty if with else; probably removed.
e8: split: `s0 = 0; s1 = s1;` no.

Let me write them.
