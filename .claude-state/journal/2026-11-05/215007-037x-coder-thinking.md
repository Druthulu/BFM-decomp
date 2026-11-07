---
ts: 2026-11-06T04:50:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5fTKQcYoc5SrJCJOVPbP
---
All still 38 insns — the nop isn't appearing. So the eager fill still happens.

Let me think about which pass fills it. Maybe it's `fill_simple_delay_slots` backward scan? No.

Wait — maybe it's not the bnez's delay slot at all. Let me re-read the diff: mine[26] bnez vs target[26:28] bnez+nop. Instruction indices are 0-based? The address 4d24 is the bnez. Both have bnez at 4d24, and target has nop at 4d28; mine has li at 4d28. Yes.

So the li is in the delay slot in mine. To stop fill_slots_from_thread: either `! own_fallthrough` with a label, or the insn can't be moved.

Idea: make the fall-through start with a label. When does a CODE_LABEL appear right after a conditional jump in RTL? If the source has a label there. gcc deletes unreferenced labels at `delete_unreferenced_labels` during jump optimization... but labels referenced by a jump that is later removed? Hmm.

Wait — what about a `switch`? no.

Another approach: make the body's first insn set a resource needed at the branch target. What if the epilogue uses v0? It doesn't... but wait: maybe we can make the *branch target* not the epilogue but something that uses v0. Hmm, the target has the branch to 4d48 = epilogue. Fixed.

Hmm, what about `insn_sets_resource_p (trial, &needed, 1)` where `needed` accumulates from previous trials. The first trial is li — needed is empty at that point (set/needed cleared at the start; for the fall-through thread call, `set` and `needed` start cleared). So no.

OK, so what about `may_trap_p`? If the first insn is a load. Can we make the body start with a load while still producing `li v0,128; lui at; sb`? The first insn would then be an extra load — not in target.

Unless the load is one that reorg *deletes* as redundant! `redundant_insn(trial, insn, delay_list)` — if the trial insn duplicates an insn before the branch, it's deleted and the scan continues. But if it can't be placed and can't be deleted, `lose=1`, and the loop continues for own_thread... For own_thread=1, the loop continues after lose. Hmm.

Wait, actually: is own_fallthrough 1 here? Yes presumably.

Let me reconsider: after `lose=1`, `mark_set_resources(trial,...)`. Then the loop continues with the next insn. So the li after the load would still be considered, but now `set` includes whatever the load set. `insn_sets_resource_p (trial=li, &opposite_needed)` — still no. Hmm, but the condition also includes `! insn_sets_resource_p (trial, &needed, 1)` — needed accumulates references of previous trials. A load references memory; `needed.memory` might be set. `insn_sets_resource_p (li, &needed)` — li sets v0, needed.memory doesn't conflict. Hmm.

Actually wait, maybe the mechanism is different: `mark_referenced_resources` for a load sets `needed.memory = 1`, and then for the following insn `insn_sets_resource_p` checks regs only (not memory) — `insn_sets_resource_p(trial, &needed, 1)`: does it check memory? It checks `resource_conflicts_p` on regs and memory? A store sets memory; a `sb` sets memory → conflict with needed.memory → the sb can't move. But li doesn't touch memory.

Hmm. Let me look at fill_slots_from_thread more carefully around the winner condition for the non-owned/owned cases, particularly `lose` and whether a `lose` in own thread prevents a later fill... In the code at 3480: after the winner block, `lose = 1; mark_set_resources...`. Then the loop continues. The next iteration checks `(! lose || own_thread)` — own_thread is 1, so continue. So a losing insn doesn't stop it.

OK. So the only stoppers: stop_search_p (jump/barrier/asm/sequence), labels (when labels_p=1), or... `own_thread` becoming 0 (after passing a label).

Hmm, hold on: maybe the fill isn't from fill_eager at all. What about `fill_simple_delay_slots`'s *backward* scan? That moves an insn from BEFORE the branch into the slot. Not li.

What about `dbr_schedule`'s `fill_eager_delay_slots` "steal from target" (steal_delay_list_from_target)? That takes insns from the target thread. Not li.

What about `optimize_skip`? It annuls the branch. Not this.

Hmm, is it possible that li isn't in a delay slot at all, but rather the branch was *redirected* to skip it? Look: mine bnez v0,4d44 (4d44 = the epilogue? mine's epilogue address is 4d44: target's epilogue is 4d48). In mine, the epilogue starts at 4d44? Let's check mine's tail: mine is 38 insns, one less, so the epilogue is at 4d44. The bnez branches to 4d44 = epilogue. And li at 4d28 is between. So yes li is in the delay slot (executes then falls to 4d2c).

Wait, actually, is that true? If li is at 4d28 and the branch is at 4d24, MIPS semantics: the instruction at 4d28 is the delay slot. Yes.

So the eager fill moved li there. To prevent: the target thread's opposite_needed must include v0. Hmm.

New idea: make `li` set a register that IS needed at the epilogue by having the epilogue use v0... The epilogue is fixed: lw ra; addiu sp; jr ra. But what if the branch target isn't the epilogue? What if we restructure so the join is elsewhere and v0 is live? But then instructions differ.

Alternatively, make the first body insn set `at`? `lui at,0x0` — the address load. If the body's first insn were the `lui at` (i.e., the li moved before the branch), then the delay slot would be filled with lui at (safe: at not needed at epilogue) — code differs.

Hmm, so maybe this item is genuinely a WALL unless there's a C-level trick with labels.

Let me explore the label idea concretely: what if the if-body's first statement is the target of a `goto` from the *else* branch? E.g.:

```
if (*(u32 *)(a0 + 0x44) & 1) {
   ...
} else {
   D_80078EBF = 0;
}
```
No.

What about restructuring the whole function so the clamp block is reached by two jumps (shared tail)? That would add instructions in the target... The target doesn't have a shared tail.

Hmm, wait. Let me reconsider the problem from the other end: maybe we don't need to block the fill; maybe we need the fill to happen *and* have an extra nop elsewhere that the diff aligns. No — diff is positional; a nop in the middle at a different place wouldn't align.

Alternatively, maybe there's a C form where the clamp branch's fall-through starts with an insn that reorg cannot move because it's a `set` of a register live at the *opposite* thread — and the opposite thread here... let me compute opposite_needed precisely. mark_target_live_regs(opposite_thread) where opposite_thread = insn_at_target = the first active insn at the label 4d48. At 4d48: `lw ra,16(sp)`. Hmm, but mark_target_live_regs might include registers live at the *end* of the block... The epilogue block: lw ra; addiu sp; jr ra; nop. Live at entry: ra? No! ra is loaded *inside* the block. Live-in to the block: sp (needed by lw/addiu), and ra? ra is dead (it's being restored). Hmm, mark_target_live_regs computes live at the target by scanning forward to find what's used before set. At 4d48, the used regs before set: sp (used by lw ra,16(sp)), then ra set... So opposite_needed = {sp}. 

So an insn that sets sp would be blocked. In C, the only thing that sets sp is a stack allocation/call — not in the body.

Hmm! But what if the body contained a call? No.

What about `mark_target_live_regs` including memory? If the target block references memory, needed.memory=1, and an insn that sets memory (a store) would conflict. The epilogue `lw ra,16(sp)` references memory! So `needed.memory` = 1 at the opposite thread. Then `insn_sets_resource_p (trial, &opposite_needed, 1)` for the first body insn: if it's a *store* (sets memory), it conflicts → can't move. So if the body's FIRST insn is a store (`sb`), the eager fill would fail → nop!

So: make the body's first instruction the `sb`. That means the value and address must already be in registers before the branch. The target has `li v0,128; lui at; sb` inside the body. If we hoist li and lui before the branch, the body is just `sb v0,0(at)` — the delay slot is then `sb` (can't move) → nop. But the code before the branch would have li+lui, which differs from target... unless sched1 moves them back? Hmm.

Wait, but what if only the address (lui at) is hoisted before the branch (e.g., by writing the store through a pointer computed earlier), leaving `li v0,128; sb v0,0(at)`? First insn still li.

Unless... `redundant_insn` deletes the li? no.

Hmm, what about making the first insn a store that reorg CAN'T move: the store `sb` to a global. In C, `D_80078EBF = 0x80;` compiles to lui at; sb (2 insns) or li v0; lui at; sb. The li comes first.

What if we write the store through an lvalue that gcc computes as a *constant address* needing only one insn? The global address is 0x80078EBF → lui at,0x8008 + sb at,-0x7141(at). Two insns.

So body = li v0,128; lui at; sb. li is first.

Could the value 0x80 be loaded into a register already holding something? E.g., if v0 already held 0x80? No.

What if we write the clamp as `D_80078EBF = add;` with add = 0x80 computed *before* the branch — then the body starts with lui at, sb v1. Then the first insn `lui at` is movable → fill. Hmm.

OK, what about the `sb` being first because the value is already in v0: e.g., the previous store `D_80078EBF = D_80078EBF + add;` leaves the result in v0, and the clamp stores 0x80 — no.

Hmm, let me think about `may_trap_p` more: `! may_trap_p(pat)` — for a store, may_trap_p is true? Let me check gcc 2.7.2's may_trap_p. In rtlanal.c, may_trap_p returns 1 for any MEM reference? Let's check.

Actually, in the condition: `if (condition == const_true_rtx || (! insn_sets_resource_p (trial, &opposite_needed, 1) && ! may_trap_p (pat)))`. So either no conflict with opposite_needed AND no trap.

If may_trap_p(store) is true, then a store can't be moved. Let me verify in the source: grep may_trap_p in rtlanal.c.

But regardless, we can't make the store first.

Alternative: make `lui at` first by having the address computed before the branch. Then the body is `li v0,128; sb`. Wait no: if the address is computed before the branch (lui at), the body is li; sb — first insn li.

If the *value* is computed before the branch, the body is lui at; sb — first insn lui (movable, sets at; at is not live at the epilogue... but is `at` special? mark_target_live_regs might treat at as always needed? Probably not).

Hmm, what if BOTH are before, body = sb only? Then the body's only insn is a store → may_trap → blocked → nop. But the target's body has li inside. So the instructions wouldn't match.

Unless the li and lui are hoisted by sched1 to before the branch in the target too? No, the target clearly has li at 4d2c (after the branch).

OK. Let me look at this from a completely different angle: maybe there's a C construct that generates an extra insn in the delay slot area that is a nop naturally. For instance, if the branch's delay slot is a `nop` because of a hazard (sched2)? No.

What if we change the comparison so the branch is `beqz` (inverted) and the fill behavior differs? Let's test: `if (0x80 >= D_80078EBF) { } else { D_80078EBF = 0x80; }`. The empty then-arm might produce a different CFG. Let me test a few inverted forms.

Actually, hmm, wait. Let me reconsider whether the fill is from eager or from the *backward* scan of fill_simple_delay_slots. In the backward scan, it moves an insn from before the branch into the delay slot. Our li is after the branch. So no.

What about `optimize_skip`? It's for annulling the branch (skip the delay slot when not taken). Not applicable to MIPS? Let me check the MIPS delay slot definition: `#define ANNUL_IFTRUE_SLOTS`? Probably not defined for mips. Actually GCC's mips.md defines `(define_delay ... (and (eq_attr "type" "branch") ...) [(and (eq_attr "type" "load") ...) ...])` — the MIPS delay slot may only accept certain insn types! In modern GCC, the delay slot accepts any non-jump. In 2.7.2 mips.md: 

```
(define_delay (eq_attr "type" "branch")
  [(and (eq_attr "type" "!branch,jump,call") ...) (nil) (nil)])
```

Something like that. Let me check the actual mips.md in the reference tree. The delay slot eligibility (eligible_for_delay) uses the machine description. Let me grep.

Actually, the key: in the target, the delay slot is nop. In mine, it's li. The difference is caused by the asm. So eligibility isn't the issue.

Let me consider: is it possible that with the asm present, the *basic block structure* differs such that `own_fallthrough` = 0? The asm insn doesn't create a label.

Hmm, but wait: `stop_search_p` returns 1 for the asm → in fill_slots_from_thread the loop doesn't even start (trial = thread = the asm insn) → no fill. That's the direct mechanism, confirmed by the code.

So we need the first insn of the thread to be an asm or jump or label, or be unmovable.

Let me check `may_trap_p` for a `sb`: grep in rtlanal.c. If a store counts as may_trap, then getting the store first would work — but the instruction order must match the target, so the store can't be first.

Unless the target's first body insn (li) is *also* unmovable for a different reason: `insn_sets_resource_p (trial, &opposite_needed, 1)` where opposite_needed includes... v0? Wait, maybe mark_target_live_regs for the epilogue includes v0 because the function's return value? The function returns void. Hmm.

Actually hold on — maybe the branch target is NOT the epilogue in the RTL sense. JUMP_LABEL is the label at 4d48. But the target block might be a *different* label that jumps... Let me look at the CFG: the `else` branch sets D_80078EBF=0 at 4d40-4d44, then falls into 4d48. The bnez at 4d24 jumps to 4d48 (skipping the clamp). Hmm.

Let me try to see what registers are live at 4d48: `lw ra,16(sp)` uses sp; `addiu sp,sp,24`; `jr ra`. So live-in: sp. ra is loaded. So {sp}.

What if the code were such that the epilogue also restores a saved register (e.g., s0)? Then the epilogue would have `lw s0,...` and s0 would be live... no, s0 is set inside the epilogue, not live-in. Live-in is only sp (and maybe the return value register v0 for the function's return, but void).

Hmm what about `at`? If the epilogue's lw uses `at`? no.

OK, so the only way with resource conflict is setting sp. Not possible.

Therefore: labels. Let me investigate whether a label can be made to appear at the start of the if-body and survive. 

When does gcc 2.7.2 keep a CODE_LABEL with LABEL_NUSES >= 1 that is immediately after a conditional branch? A `goto` target. The jump that references it must not be eliminated. If the goto is the only path, jump optimization turns it into a fall-through and deletes the label (delete_unreferenced_labels). But what if the label is referenced by a jump that itself is optimized away later? Then it's deleted too.

BUT: here's a classic — a label at the start of a loop body referenced by the loop's backward jump! `do { ... } while (cond)` creates a CODE_LABEL at the loop head and a backward jump. But we can't have a real loop (it would add insns and a branch). Unless loop.c converts a do-while(0)... it's trivially true so the loop is removed.

Hmm, what about `do { } while (0)` surviving to reorg? C0535 says it splits cse1 EBB, which suggests the loop notes survive through cse. Loop.c would delete a do-while(0)? A `do{}while(0)` has a note but no jump back (the condition is constant true → the loop has no exit... hmm). Actually a do-while(0) in RTL: LOOP_BEG note at the body start, LOOP_END note at the end, no branch. loop.c may remove the notes. cse1 runs before loop.c, so the EBB split happens at cse1 time. Then loop.c sees a loop with no branch and might do nothing. reorg would see no label.

So do-while(0) might not create a label at reorg time.

Hmm. But we could test: my b1 (do-while(0)) scored 5 with 38 insns — no nop. So no label effect at reorg.

What about a `while` loop that gcc can prove runs once? no.

Let me reconsider — maybe the answer is simpler: maybe the target's nop comes not from reorg but from a **branch hazard** in sched2 or from `dbr` not filling because... hmm.

Alternatively, maybe we can make `li v0,128` redundant with an earlier insn so reorg deletes it and then the next insn (lui at) also can't move? No: if reorg deletes li as redundant and then moves lui, the code changes.

Hmm, hold on. Let me reconsider the direction: maybe we should make the branch *not* have a delay slot filled by changing the branch's target so that `insn_at_target` is used. If prediction > 0 (likely taken), fill_slots_from_thread first tries the target thread (epilogue). If it succeeds in filling from the target (e.g., with a copy of lw ra), the code changes.

What if the target thread contains an insn that's blocked (sets sp), so it fails, then falls to the fall-through... same.

OK, let me look at this from the "what does the target's RTL look like" angle: maybe with the asm, reorg *did* fill the slot — with the asm insn itself (the asm emits nothing → the delay slot encodes nop). That's consistent: eager fill took the asm insn into the delay slot (it's not eligible? stop_search_p stops... wait, if stop_search_p stops at the asm, no fill).

Hmm, but score 0 with the asm means the output bytes are identical. If reorg didn't fill, the nop is emitted. Either way.

Let me test one thing: what if I put an *unmovable real insn* at the body start that is then deleted? no.

New idea: **Make the delay slot fill impossible by making the branch's delay slot already occupied by a nop from `fill_simple_delay_slots`?** no.

Alternative idea: **change the branch condition to a form whose fall-through first insn is a load**. The clamp could be written so the body loads the global before storing:
```
if (0x80 < D_80078EBF) {
    D_80078EBF = 0x80;
}
```
already loads before.

What about writing the clamp as:
```
if (D_80078EBF > 0x80) {
    D_80078EBF = D_80078EBF;  // no
}
```

Hmm.

Let me step back and consider the possibility that this item is a WALL and spend my budget on the other 4 items. But before that, let me check the moves.md for similar functions from the same family. These headers are "P36 rung B headers1" barriers. Maybe other shards already cracked similar header barriers. Let me grep moves.md for "headers1" or for these function names / nearby functions. Also grep the results of other shards for "PARTIAL" with barrier on headers.

Let me grep moves.md for "0x8014A" and "0x8014B" and "0x8014D" and "0x8014F".
