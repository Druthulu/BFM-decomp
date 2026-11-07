---
ts: 2026-11-06T04:46:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dGBrTbcDqpYZrMxT2jzM
---
Confirmed: the only difference is the delay slot of `bnez v0` — target has `nop`, mine has `li v0,128` (reorg filled the branch delay slot with the first insn of the taken-through block... wait, bnez branches to 4d48 (the epilogue); the delay slot is executed regardless. Target has nop; mine moved `li v0,128` into the delay slot (safe because the branch target doesn't use v0 before setting it... actually it's the epilogue).

So the barrier asm (an empty asm insn) was placed in the if-body before the store, which prevented reorg from filling the delay slot? Hmm, but the asm is before `D_80078EBF = 0x80;` i.e., between the branch and li v0,128. So it adds a real insn (asm) — but score 0 means the asm produced no instruction... Actually an empty asm produces no code but does create an insn in the RTL stream that blocks reorg's delay-slot fill? Apparently the final object is identical with the barrier (score 0). So the empty asm is invisible in the final code but its presence stops reorg from moving li v0,128 into the delay slot.

Wait, but then how does the target have exactly the same bytes? Because with the barrier, reorg leaves the nop. Yes: the asm is a barrier for reorg (can't move insns across it? Actually reorg's fill_simple_delay_slots scans from the branch forward; the asm note... hmm, an asm insn after the branch is where the scan starts; but the branch's delay slot is right after, and the first insn after the branch in the target block is the asm... wait order: branch at 4d24, then the if body: asm, then store (li v0,128...). With asm first, the delay slot candidate would be the asm (which emits nothing) — so reorg finds nothing to fill? Actually the asm insn itself would be moved into the delay slot, emitting nothing → nop. That's it: the empty asm gets moved into the delay slot and emits nothing, leaving a nop.

So to crack it lever-free: make reorg NOT fill the delay slot with `li v0,128`. This is the `dbr-delay-fill` wall (tag exists: line 19). Hmm.

But maybe a real-C move changes the shape. Options:
1. Force the constant to be materialized differently — e.g. the target's `li v0,128` then `sb`. If I write `D_80078EBF = 0x80;` that's what we have.
2. Change so the store is a different insn group, e.g. `D_80078EBF = 0x80 + 0;` no.
3. Make the branch a different shape so reorg has no candidate: e.g. `if (!(0x80 >= D_80078EBF))`? same.
4. Introduce something between the branch and the store that cannot be moved into the delay slot, like a function call — no.

Wait — what if we write the store differently so that the delay-slot candidate is not `li v0,128`? For instance use a variable: `add = 0x80; D_80078EBF = add;` Hmm, `li` still.

Actually reorg's fill_simple_delay_slots with a "safe" candidate: it can fill the slot if the candidate's insns are safe (don't use regs set on the branch path). `li v0,128` is safe because v0 is dead. In the target, why not? Because the asm was there. In plain C, could we arrange the branch condition to have a dependency on v0? Hmm.

Alternative: make the if-body's first real insn not safe. If we write:
```
if (0x80 < D_80078EBF) {
    add = 0x80;
    D_80078EBF = add;
}
```
add is v1... The `li v1,128` — still safe.

What if we compute `D_80078EBF = D_80078EBF - D_80078EBF + 0x80;` — that reads D_80078EBF, creating a use of the register loaded on the branch path? Hmm, but the value is already loaded (lbu v0 at 4d08, then addu v0,v0,v1, sb, andi, sltiu...). After sltiu v0 is 0/1. So v0 is clobbered.

Actually, what registers does the branch target (epilogue) use? ra, sp. So anything except ra/sp is safe to fill. Hmm.

Alternative approach: change the branch to a different form where the delay slot cannot be filled — e.g. if the delay slot insn would be a jump target. If the fall-through block starts with a label that's jumped to from elsewhere, reorg won't fill. That's the classic. Could we create a shared block? E.g.:

```
if (0x80 < D_80078EBF) {
    D_80078EBF = 0x80;
}
```
No label.

What about making the `j 4d48` and bnez both target the same, and reorg's `fill_simple_delay_slots` for the bnez uses `next_trial`... The classic lever: a label at the fall-through start (e.g. via a goto from elsewhere). But that changes CFG/instruction count.

Hmm, let's consider the movability: target has j 4d48 with delay nop too. Mine: j 4d44 (also nop? we saw mine j 4d34... let me check mine's j delay slot: after j at 4d34 comes probably nop at 4d38, then 4d3c? The mine listing cut at 4d34). Mine is 38 insns vs target 39: only one extra nop in target (the bnez delay slot). The j delay slot in both is nop.

So we need exactly to prevent the bnez delay slot fill.

Idea: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; }` — what if the store uses a value that must be computed on the branch path, e.g. `D_80078EBF = 0x40 * 2;`? combine folds to 0x80 → li. Still safe.

Idea: use a variable that's live after: `add = 0x80; D_80078EBF = add;` If `add` is used after the if (e.g. returned or used in a later computation), then `li v1,128` would NOT be safe to move into the delay slot because it's live at the branch target (the epilogue)... Actually if add is live after the join, the delay slot move would still be safe (the delay slot executes on both paths), and the value would be set on both paths — but on the fall-through path it's set correctly; on the branch path it would incorrectly set add! Wait no: delay slot executes regardless of branch. If add should only be set when the condition is true, moving it to the delay slot sets it also when the branch is taken — which changes semantics if add is used later. GCC's reorg checks this: it won't move an insn into the delay slot if its destination is live on the branch path (it checks `resources` / uses). Actually reorg's `fill_simple_delay_slots` checks whether the insn sets registers used at the branch target via `reg_used_between_p`? Let me recall: it computes `slots_to_fill` and checks the insns in the delay slot are "safe": `! insn_references_resource_p (trial, &set_resources, ...)` etc. It marks `set_resources` from the branch target's live-ins. So if add (v1) is live at 4d48 (epilogue), reorg will not put `li v1,128` in the delay slot.

But then the code shape changes: the epilogue would need to use add. Hmm, that changes the function. Unless... we can make a variable live at the epilogue without changing the target instructions? The target's epilogue only uses ra/sp. So no.

Alternative: make the value stored not a simple constant but something whose set is not safe. E.g. `D_80078EBF = D_80078EBF & 0x80;`? That's a different value.

Hmm, wait. Let's reconsider: maybe the actual best move is different — maybe we can restructure so that the branch is the *last* thing (tail merge) and the `li` is hoisted before the branch. In the target, `li v0,128` is inside the if-body after the branch. What if we write the code such that the constant is computed before the branch?

```
if (0x80 < D_80078EBF) {
    D_80078EBF = 0x80;
}
```
The `li v0,128` could be moved before the bnez by sched1? Then the branch delay slot would be filled by something else, and the li would be before. But target has li after branch. Hmm, but what if the delay slot then gets nop because the next insn after the branch is the lui? Let's think: if li is before the branch, the block after the branch starts with `lui at` (the address). Reorg filling the delay slot with `lui at,0x0` + `sb v0,0(at)`? The lui uses at which is... it might be safe too (at is scratch). Hmm, but moving `lui at` into the delay slot is fine only if at is dead at the target. It is. So reorg might fill with lui+sb? No, fill_simple_delay_slots fills with up to 2 insns (annul? no). It typically fills one insn (one delay slot). So it'd take lui at. That would change the code (lui at moved) → mismatch elsewhere.

Let me instead check what the barrier actually does in RTL. But easier: experiment. Try a few bodies quickly.

Experiment ideas:
A. `add = 0x80; D_80078EBF = add;` with add also used after? No.
B. Reorder: store then compare? no.
C. Use a do-while(0) around the body (C0535).
D. Use `if (D_80078EBF > 0x80)` vs `if (0x80 < D_80078EBF)` — same.
E. Write the clamp as `if (!(D_80078EBF <= 0x80))`.
F. Use `D_80078EBF = (u8)0x80;`
G. Dead reset (C0414): insert `r = 0;`? Hmm.

Let me think about what reorg does: `fill_simple_delay_slots` for a conditional branch: it tries `next_trial` = insns after the branch (fall-through). It checks the insns are safe to execute unconditionally: they must not use registers set by insns between the branch and them, and must not set registers live at the branch target (`set_resources` intersection with `regs_live_at` of the target?). In reorg.c: `fill_simple_delay_slots`:

```
/* Try to fill the delay slot with the insns after the branch... */
for (trial = next_nonnote_insn (insn); ...)
  {
    if (trial == ... ) 
    if (GET_CODE (PATTERN (trial)) == SEQUENCE) ...
    if (INSN_UID (trial) >= ...)
    /* If this insn is a set of a register that is live at the branch target, don't */
    ...
    resources...
  }
```

Actually it uses `insn_references_resource_p (trial, &set_resources, ...)` where set_resources is set by scanning the branch target? Let me look at the actual GCC 2.7.2 source in tools/reference/gcc-2.7.2/reorg.c. That's the authoritative route. Let me grep for fill_simple_delay_slots.

But before deep-diving, let me just try cheap experiments: a handful of bodies. Each score is ~1s? Let's see.

Experiment 1: `if (0x80 < D_80078EBF) { add = 0x80; D_80078EBF = add; }` — add is dead after; but the store of add... Actually add was used for the previous store; reassigning is fine.

Experiment 2: do-while around the store: `if (...) { do { D_80078EBF = 0x80; } while (0); }` — the loop note may stop reorg.

Experiment 3: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; }` with the comparison written as `if (D_80078EBF > 0x80)` — but D_80078EBF is u8, compare with 0x80: target uses sltiu v0,129 after andi 0xff — fine.

Experiment 4: swap if arms: `if (0x80 >= D_80078EBF) { } else { D_80078EBF = 0x80; }` — empty then-arm may produce a branch to the join differently.

Experiment 5: compute the clamp without a branch: `D_80078EBF = (D_80078EBF < 0x80) ? D_80078EBF : 0x80;` — different code.

Let me think about what's likely: the empty-then-else form (`if (!(0x80 < D_80078EBF)) goto skip; ...`) — the goto form creates a label at the fall-through... Actually a `goto` to the join would create a label, and reorg may still fill.

The most promising: do-while(0) (C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item"). Here it's reorg/delay slot. Hmm.

Wait — actually maybe the issue is not reorg but the branch itself: the asm being an insn placed first in the if-body means the branch's delay slot is filled with the asm insn (which emits nothing). If instead we can make the first insn after the branch something that reorg won't move... The empty asm is "not safe" maybe because asm insns are volatile and reorg won't move them? If reorg doesn't move asm insns, then the delay slot stays empty (nop) — that's the mechanism! reorg refuses to move an insn containing asm (`volatile` / `asm_noperands`). So the nop appears because the asm can't be moved, and the slot remains empty.

So to replicate: we need an insn that reorg won't move, or a natural barrier. A real C move that makes the first insn after the branch immovable... e.g. if the first insn is a jump target label? Reorg won't move an insn that is a branch target (`INSN_LABEL`? it checks `LABEL_P` before, and in fill_simple_delay_slots it checks `! INSN_FROM_TARGET_P`...). Hmm.

Actually: if the fall-through block begins with a label that some other jump targets, reorg won't fill the delay slot with it (`if (INSN_UID (trial) >= ...)`? Let me check the source. Let's read reorg.c's fill_simple_delay_slots.

Actually, I recall: `fill_simple_delay_slots` has:

```
  /* Fill the delay slot with the insn after the branch... */
  next_trial = next_nonnote_insn (insn);
  ...
  if (next_trial && ... )
```

and there's a check: "Don't put anything in the delay slot if the insn is a jump" and "if the insn has a REG_LABEL reference" (can't move an insn that references a label because the label's address may change?). Hmm.

Let me read the source. grep fill_simple_delay_slots in reorg.c.
