---
ts: 2026-10-22T21:46:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7F8QkNXm3DBhuZdmlgXx
---
Hmm, k_mask (u32 byteval with & 0xFF) = 3, worse than e1's 3? Same 3. k_shift3 = 3 too (so `<<3` vs `*8` matters! e1 was 3 with *8; k_shift3 also 3 — maybe different residual).

Let me check whether there's a variant of the u8 base that fixes the order. The two-copy order problem remains.

New idea: what if byteval's copy is scheduled first because its *destination* $3 is also... hmm.

Let me try to understand sched1's priority empirically from the dump: are there priority numbers? Let me check the .sched dump format for a "priority" annotation. gcc's -dS output doesn't include priorities.

Alternative: gcc 2.7.2's sched.c `priority()`:
```
static int
priority (insn)
{
  int this_priority = -1;

  if (GET_CODE (insn) == NOTE)
    return priority (next_nonnote_insn (insn));

  /* Find the next real insn */
  ...
  if (INSN_PRIORITY_STATUS (insn))
    return INSN_PRIORITY (insn);

  /* Compute the priority */
  ...
  for (successors) this_priority = max(this_priority, priority(succ) + 1)
```
I recall in 2.7.2:
```
  next = next_nonnote_insn (insn);
  if (next) this_priority = priority (next) + 1;
```
plus loop/block edges.

If priority is over the whole function, the $4 copy (used at 13, i.e. priority of the beqz ~ 17) vs $3 (used at 19, priority ~ 11). So $4 is higher → scheduled first (2.7.2's ready_add puts higher priority first).

To flip, I need the $3 use to be farther from the end than the $4 use. The $3 use is at 19 (sll v1) — the sb at 25 and the sh at 29 come after. The $4 use is at 13 (beqz), and after that the code continues to 14...30.

So no. Unless I move the $4 use later: the beqz is the branch. What if the testval check were moved to a later point in the code? E.g. the target's shape: if ((iVar3 == c5) || (testval != 0)) uVar4 = 0;. The beqz at 13 targets 0x40 (the same uVar4=0 block). What if I write:

```
if (iVar3 == c5) uVar4 = 0;
else if (testval != 0) uVar4 = 0;
```
This gives beq (iVar3) → block A; else beqz testval → block A. Hmm, the code shape would be: beq v0,t2, A; nop?; beqz a0, A; ... The target has beq then (delay sll) then beqz. Actually the target's beq is at 11 with delay slot sll a1 at 12, then beqz at 13. That's a short-circuit OR compiled as: beq v0,t2, target(0x3c); delay slot sll a1; beqz a0, target(0x40). Two branches to nearby targets.

Anyway the priority issue stands.

Let me consider: maybe I can make the $4 copy NOT be a copy in block 1 but a copy created later (e.g. by making the branch operand need it in block 2). E.g. write the condition so testval's value is used only after a copy... 

What if testval is assigned from `src` *inside* the uVar4=0 arm? No, it's used in the condition.

OK — time check: 15:46. Need to reach 15:54 (20 min from 15:34). Let me spend the remaining 8 minutes on 6-8 more variants with different structural ideas, then finalize.

Ideas:
1. Move the `pcVar2 += 0x14; iVar3 += 1;` before the if (statement order).
2. Assign `uVar4 = 0;` differently.
3. Use a `do { } while(0)` around the two copies.
4. Reorder the loop body: put the store block before the if (no).
5. Give byteval a use in the if: `if ((iVar3 == c5) || (testval != 0) || byteval == 0x10)` — changes branches.
6. Change `iVar3` to `s32` (it is s16!). `iVar3` is s16 → the `sll v0,a3,0x10; sra` sequence. What if iVar3 were s32? That would remove the sll/sra → breaks the match.

7. Try `u8 byteval` with `testval` assigned as `(u8)src` and testval u32: `testval = (u8)src;` — the QI cast then converted to SI: gcc emits a zero-extend? For known <16, no insn. Might give the QI cse class for the source and an SI value for testval → different cse classes → maybe order right and source v0! Worth a try.

8. `testval = (u16)src;` similarly.

Let me try 7/8 plus a couple of statement-order ones.
