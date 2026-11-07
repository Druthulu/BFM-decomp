---
ts: 2026-11-06T15:13:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J53nyMqCp6Jv9gVEJBUo
---
In c1, reg/v 196 is set only ONCE (insn 476), and its value is used in the ior at 3144. So the assignment `vol = (vol | ...) & 0xFFFF` got... cse replaced the final andi/ior such that the result is a *different* pseudo, and vol is only set once. Interesting: the tree-level assignment `vol = expr` where expr is the argument — cse/combine kept vol's use but the result went into the call arg temp. So reg_n_sets[196] = 1 → birth boost → pan first. That explains c1.

So the second set must be a real set of the SAME pseudo that survives. In b4, insn 478 sets reg 196 = and(196, 0xFFFF) — survives.

Now: can I make that andi land in a different basic block or be ineligible?

Wait — maybe simpler: what if the mask is `vol &= 0xFFFF` placed BEFORE the vol division? No, vol isn't set yet.

What if vol's second set is at the very START of the block: `vol = 0;`? Dead store, deleted.

What if vol is declared with an initializer at the top of the function? `s32 vol = 0;` — that's a set at function entry, but if it's dead (overwritten before use) flow deletes it. But if vol is used... no.

Hmm, what about using vol as a real temp elsewhere in the function so it's set twice with genuine uses and no extra insns? Look for an existing variable I can replace with vol without changing codegen. E.g., `t` (used twice: t = func_8004787C(...); ... t = func_80047948(...);). If I reuse vol for `t`'s role... but t is live across the calls; vol would then have a set early. Then vol's later division would be the 3rd set. That changes allocation significantly (vol's live range spans the calls). Risky but let me consider: the target has vol in $a1 and t in ... hmm.

Alternatively use vol instead of `d` (block-scoped in the two if blocks)? d is set twice in different blocks (each `s32 d` is a separate block-local though).

What about `flag`/`z`? They're stack slots.

Hmm. What about the `s32 sx` variable — it's set multiple times. If vol were the SAME variable as sx... no.

OK here's another angle: the andi at the launder position is stolen by reorg. What if I put the mask *before* the `if (sx < 0)` construct? Then there's a LABEL (end of the if) between the andi and the branch. stop_search_p stops at a label! Let's check: the `if (sx < 0) { av = -sx; }` compiles to `bgez a2, L; negu a1,a2; L:`. The mask placed before this if would be before the bgez. The backward scan from the bne would stop at label L (stop_search_p stops at CODE_LABEL). So the andi would NOT be stolen → the thread copy of the sll wins → MATCH!

But: is the mask before `if (sx<0)` still a set of vol at the right point? vol is computed AFTER. So `vol = vol & 0xFFFF;` before the if is a dead store (vol not yet live) → flow deletes it. Unless... hmm.

What if I move the vol computation BEFORE the `if (sx < 0)`? vol depends on av, which depends on sx and the if. No.

What if the mask is placed right after `av = sx; if (sx<0) av = -sx;`... that's the current position (after the if, before the vol div? no, after the vol div). Let me place it after the if but BEFORE the vol division: `vol = vol & 0xFFFF;` — vol uninitialized at that point → dead store (and undefined behavior). flow deletes.

So the mask must come after vol's first set. The first set is the division, which is after the if. The next label after that is the label at the end of the `if (sx == 0x10)` block? The bne is that if's branch; the label is after `li a2,15` (the fall-through) — that's AFTER the bne. So no label between the mask and the bne.

Could I introduce a zero-cost label between the vol division and the bne? A control-flow structure that gcc turns into a no-op... e.g. `if (0) { ... }` — gcc deletes it entirely. `do { } while (0)` — no label. A `goto` to a label placed right there? A label with no branch might remain as a CODE_LABEL and stop reorg's scan, but would it also stop jump1/sched? Adding `L: ;` (a label) — but a label needs a use, else it's deleted. Could add `goto L; ... L:` — that's a jump, costs an insn (or is it optimized?).

Hmm, what about using the existing `if (sx == 0x10)` differently: restructure so the mask is inside an if-else? 

Actually — wait. Reconsider: what if the mask is placed in the FALL-THROUGH after the bne, and the sll is before the bne? I.e., reorder the source:
```
sx = (sx + 0xA0) / 0x14;
sx = sx << 8;            // sll before the if
if (sx == 0x1000) sx = 0xF00;   // equivalent? sx<<8 then compare
```
That changes the comparison semantics (compare after shift). But `if (sx == 0x10) sx = 0xF; sx <<= 8;` ≡ `sx <<= 8; if (sx == 0x1000) sx = 0xF00;`. That changes the insn order: sll before bne. Then the delay slot: the backward scan from the bne would find the sll (sets a2 which the branch needs? branch compares a2 → sets a2 ∈ needed → conflict!). Hmm, the branch would compare a2 after the shift, so sll sets a2 which the branch uses → conflict → not eligible. Then thread copy from `li a2, 0xF00`? That gives a different code shape (li 0xF00 vs li 15 + sll). Not matching.

OK. Different approach: accept the andi but make the *target* also effectively... no.

Let me reconsider the whole thing: maybe there's a different second set that doesn't add an insn AND isn't in the bne's block. What if vol is set twice because the two if-blocks each recompute it? E.g., the source naturally: vol computed once. 

Hmm, what about the function's *first* block? `((Unkstruct_800B5CB8 *)a0)->unkFC = CAST_SIGN(u16,a0,0xFC)+1;` — no.

What about using `vol` as the destination of a real computation in the same block that already exists: e.g. `vol = ((0xA0 - av) * 0x7F) / 0xA0;` is set 1; then `sx = (sx + 0xA0) / 0x14;` sets sx. What if I write the pan computation using vol as an intermediate? No, they're independent.

What about: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then later `sx = (sx + 0xA0) / 0x14; if (sx == 0x10) sx = 0xF; sx <<= 8;` and then `vol = vol | (0x3000|sx);` (dropping the outer & 0xFFFF, since combine might add it?). Then the call `func_8002D4C8(0xA9B, vol & 0xFFFF);` — hmm, this is c2 which scored 4 (237 ins). Let me look at c2's diff: maybe it's closer than b4? c2 was: `vol = vol | (0x3000|sx); func(0xA9B, vol & 0xFFFF);` → score 4. Let me see its diff.

Actually, let me try the variant where the mask is at the call but the *division result* is stored into vol via a compound assignment that keeps 2 sets... 

Hmm, actually here's a thought: what if the second set is the `sll`? I.e., reuse vol for the pan shift:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
vol = sx << 8;     // instead of sx = sx << 8
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
No — vol is needed for the |.

What about `vol = (vol | (0x3000 | sx)) & 0xFFFF` at the call (c1) but ALSO keeping a use of vol such that cse can't collapse the set? The issue was reg_n_sets=1 because cse forwarded. What if I add a use of vol between? E.g.:

```
vol = ((0xA0-av)*0x7F)/0xA0;
sx = ...;
if (...) ...;
sx = sx << 8;
vol = (vol | (0x3000 | sx)) & 0xFFFF;
func(0xA9B, vol);
```
c1 — cse kept vol set once and used it in the ior; the assignment's result went to the arg temp. Because at the tree level, `vol = expr` where expr = (vol|X)&0xFFFF — cse sees vol's value in the ior, and the assignment to vol... Actually the RTL showed insn 476 sets vol, and the ior at 3144 uses vol; the and/or result is a different pseudo (the arg). So gcc's expand turned `vol = expr` into: compute expr into a temp, then copy to vol? But no copy appeared. Maybe flow/cse removed the copy because vol was dead after (only the arg uses it) — i.e., cse forwarded the arg to use the temp directly and the vol set became dead and was deleted. So reg_n_sets=1.

To prevent that, vol must be used *after* the second set in a way that cse can't forward. E.g., use vol in a store or pass it. c1 passes vol — but cse forwarded. Hmm.

What if the second set is `vol = (vol | (0x3000|sx)) & 0xFFFF;` and then the call uses `vol` — the RTL shows the ior uses vol and the result is the arg. The set of vol (the copy from the temp) was deleted because vol dies. So we need vol live after.

What if vol is also used in the `if (unkFC == 0x18)` block at the end? E.g., `... = vol`? That changes code.

OK let me try yet another angle: the delay-slot issue. In b4, the andi is in the delay slot. What if the mask is an insn that reorg cannot move because it's a `lw`/`sw` with a memory reference that conflicts? The branch doesn't reference memory. Hmm.

What if the mask is a *store* to memory (e.g., `*(volatile u16*)&... `)? No, changes semantics.

What about making the second set a `move` that reorg treats differently? All simple insns are eligible.

Hmm, what about `vol = vol & 0xFFFF;` placed after `sx = (sx + 0xA0)/0x14;` and BEFORE the `if`? Same block, same problem (the andi is before the bne).

What if the mask is placed INSIDE the `if (sx == 0x10)` fall-through:
```
if (sx == 0x10) sx = 0xF;
vol = vol & 0xFFFF;   // right here, after the if
sx = sx << 8;
```
Then order: bne, li a2,15 (fall-through), andi, sll. The backward scan from the bne stops... the insns after the bne aren't in the backward scan (they're the thread). The thread copy picks the first insn of the fall-through? `fill_slots_from_thread` tries the insns at the start of the thread: `li a2,15` — eligible? It sets a2, which is live (used by sll). Moving it into the delay slot: it's executed anyway. Then the next thread insn... Actually reorg copies insns from the thread into the delay slots. It would copy `li a2,15` first (wrong: target copies the sll). Hmm, but `li a2,15` is only executed on the fall-through path; copying it to the delay slot would execute it also on the branch-taken path, which is WRONG unless the target path also sets a2... no, on the taken path a2 stays 16<<8. So reorg can only copy an insn that's safe on both paths. `li a2,15` is not safe. The sll is safe (a2<<8 on both paths, and on the fall-through a2 was just set to 15). Wait, on the fall-through path, `li a2,15` then sll → 15<<8. If the sll is copied into the delay slot, on the fall-through it executes BEFORE `li a2,15` → uses the unclamped value → wrong? But reorg also keeps the original sll after li, so the fall-through computes li 15; sll (delay, dead); sll (real) = 15<<8. Correct. On the taken path: delay sll gives 16<<8 = 0x1000, and no further sll (branch skips to after the original sll? target: bne a2,v0,598 — 598 is after the sll at 594). So the taken path gets one sll from the delay slot. Correct.

So reorg copies the sll (safe because dead on fall-through). If I put the andi between the if and the sll:
```
if (sx == 0x10) sx = 0xF;
vol = vol & 0xFFFF;
sx = sx << 8;
```
The thread is: li a2,15; andi a1; sll a2. Thread copy candidates: li (unsafe), andi (safe? andi a1 executes unconditionally — yes safe), sll (safe). Reorg would copy the first safe one: the andi! Then it'd be in the delay slot again, but the sll wouldn't be duplicated → same as b4? Actually then the delay slot would be the andi and the sll at 594 — that's exactly b4's output. Hmm, no gain.

What if the mask goes AFTER the sll (d1)? Then the thread is li; sll; andi. Reorg copies the sll (first safe) into the delay slot → target's shape! And the andi stays after. That's exactly what d1 did — but d1 had 238 ins (the andi extra). So the shape is right but the andi is an extra insn.

So the remaining problem: eliminate the extra andi. What if the andi merges with the final `& 0xFFFF`? In d1, the final call is `(vol | (0x3000|sx)) & 0xFFFF`. If vol is masked first: `(vol & 0xFFFF) | ...` then `& 0xFFFF`. combine: `(X | Y) & 0xFFFF` where X = vol & 0xFFFF → could become `((vol & 0xFFFF) | Y) & 0xFFFF`. combine's distributive laws might merge the two ands: `(A & M) & M` = `A & M`. But here it's `(A & M) | Y` then `& M` — the outer and applies to the or. combine can rewrite `(A & M) | Y` ... only if Y is known within M. sx<<8 can be up to 0xF00 (12 bits) — combine doesn't know ranges. Hmm.

What if I write the expression to explicitly avoid the outer mask: `vol = vol & 0xFFFF;` then `func(0xA9B, vol | ((0x3000 | sx) & 0xFFFF));` — since sx <= 0xF after the clamp, sx<<8 <= 0xF00 < 0x10000, and 0x3000|sx < 0x10000. But the compiler must emit the outer andi anyway unless it can prove. The target HAS the outer andi at 5a8. So the target's `& 0xFFFF` is the one andi. If I mask vol separately, I get 2 andis.

Unless... the target's andi at 5a8 could be the vol mask instead! I.e., the target's `andi a1,a1,0xffff` at 5a8 applies to the OR result. If the source were `vol = (vol | (0x3000|sx)) & 0xFFFF; func(vol);` we saw cse kills it.

What if the source is `vol = (vol | (0x3000|sx)); vol = vol & 0xFFFF; func(vol);`? Two statements — cse might keep both sets. Then: vol set 1 (div), set 2 (or), set 3 (and). The or writes vol, the andi writes vol — 3 sets. Insn count: the or and andi are exactly the target's `or a1,a1,a2; andi a1,a1,0xffff`. So zero extra! And vol's reg_n_sets = 3 → no birth boost. The position of the andi is after the sll (before the jal) → reorg copies the sll. This could be it!

Let me test: 
```
sx = sx << 8;
vol = vol | (0x3000 | sx);
vol = vol & 0xFFFF;
func_8002D4C8(0xA9B, vol);
```
The concern: cse forwarding again (the final vol use could be forwarded to the andi's temp). But now vol is set twice in a row, and the final use is the call arg. cse might still forward: the andi sets vol; the call uses vol. The call arg is vol directly (no copy needed) — since the arg is `vol`, gcc's expand will put vol into a1 (already there). Actually the arg temp IS vol's reg. In c1, the problem was `func(0xA9B, vol)` where vol's set was a copy from a temp — the copy was deleted because vol died at the call (the call reads it; a REG_DEAD). Hmm, cse forwarded the *value* so that the call uses the temp directly.

Hmm. But with three sets, maybe cse's equivalence gets broken (each set invalidates). Let's just test it.

Also test a variant: keep `vol` live by using it in a way that cse can't forward, e.g., the call arg `vol` (same).

Let me test e1.
