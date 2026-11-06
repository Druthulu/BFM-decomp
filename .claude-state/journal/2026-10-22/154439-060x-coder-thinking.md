---
ts: 2026-10-22T21:44:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2X1VW1QZK2JPAT9j1hMQ
---
Confirmed: after sched1, insn 43 (a0 copy) comes BEFORE insn 40 (v1 copy). Before sched1 (rtl), 40 was before 43. So sched1 reorders them → this is a sched1 birth-order issue.

Now: what decides? In gcc 2.7.2 sched.c, `priority()` computes the longest path to the end of the block, and `ready_add` inserts by priority.

insn 40 ($3 copy) → used by the sll chain (later block).
insn 43 ($4 copy) → used by the beqz at 13 (next block).

If priority() walks `next_nonnote_insn` to the end of the function, insn 43's use is closer (13) than 40's (19) → 43 has higher priority → scheduled first. That matches the observation (higher priority first).

So to get $3 first, the $3 copy must have higher priority than the $4 copy, i.e. the $3 value must be used EARLIER in the code than the $4 value.

$4's first use: the beqz at 13 (block 2, immediately after the beq).
$3's first use: sll v1,v1,3 at 19 (block 2, later).

If I move the sb/store earlier... The store `pcVar2[0] = (u8)(byteval * 8 + 8);` is at 25 and the `*(u16*)(pcVar2-2) = ...` at 29. The sll chain for byteval starts at 19.

What if the byteval use comes before the beqz — i.e. inside block 1? There's no such use in the target.

Alternatively: LOWER the priority of the $4 copy so it's scheduled after. Priority depends on the distance from the use to the end of the block/function. If the beqz's block were... hmm.

Alternatively, the target has the $3 copy first — which means in the target's source, the $3 copy had higher priority, i.e., the $3 value was used EARLIER. In the target, $3 (v1) is used at 19. The $4 value at 13. So the target's $4 copy has *lower* priority than the $3's? That contradicts the distance rule... unless the target's $4 copy is not scheduled by sched1 at all but is the result of a different construction.

Hmm, wait. Maybe in the target the ORDER came out this way because of a different *dependency*: e.g. if the $4 copy depended on the $3 copy's result... no, the target's is `move a0,v0` (from v0).

Alternatively, maybe sched1's ready_add puts equal-or-higher priority AFTER (i.e., it's LIFO for equal priorities), and the priorities of 40 and 43 are EQUAL, so the LIFO order puts 43 first. And in the target, they were also equal but the RTL order was 43 before 40 (i.e. the source had testval first)! Then LIFO gives 40 first → target order!

That fits: u8_swap (testval assigned first in source) should then give 40 first... but it didn't. Hmm, u8_swap was based on u8.c (byteval u8). Let me re-check: u8_swap put `testval = src;` before `byteval = src;` and the result was still a0 first (score 2). Hmm, that contradicts.

Unless cse reorders the RTL. Let me check the .cse dump for u8_swap... I'd need another dump run.

Wait, actually, let me reconsider: maybe in u8_swap the RTL order changed but sched1 still put 43 first because the priorities differ (43 higher). And in the target both orders agree because... 

Ugh. Let me test the hypothesis "higher priority (closer use) scheduled first" by looking at the priorities in the dump. The .sched dump might print priority values? Let me grep the sched dump for "priority" or the insn line format. gcc's -dS dump prints:
```
(insn 40 ...)  ... 
```
Hmm, `-dS` prints the insns with their scheduling info in a special format when `sched_verbose`? Not by default.

Alternative empirical test: change the code so that the $3 value's first use is EARLIER than the $4's. E.g. move the `pcVar2[0] = ...` store before the `if`. But that changes semantics (target has the store after the if). Hmm, but does it? Target order: if(...) { uVar4 = 0; } pcVar2 += 0x14; iVar3 += 1; then the store block. The store of byteval*8+8 comes after. Moving it earlier changes the code shape (sb position).

Alternatively, make the $4 value's first use later: the beqz checks testval != 0. What if the condition were `(testval != 0)` evaluated in a *later* block? E.g. restructure as:
```
if (iVar3 == c5) { uVar4 = 0; } else if (testval != 0) { uVar4 = 0; }
```
That would produce two separate branches (beq to a block that sets uVar4 and falls through?) — the target has `beq v0,t2, +0x3c` then `beqz a0, +0x40`: both branches jump to the SAME place (0x3c vs 0x40 differ by 4!). Hmm interesting: beq targets 6474 and beqz targets 6478 — different by 4 bytes. So the beq jumps to 0x3c and beqz to 0x40. That's the || short-circuit: if iVar3==c5 → jump to the uVar4=0 block; else evaluate testval → beqz to the same block (one insn later?).

Hmm.

Given the difficulty, and that this is a documented wall tag (`sched1-birth-order`), let me consider the remaining time. It's ~16:02. I've spent 28 min on item 4. The rule: past 30 min stop and record a wall; a WALL needs ≥20 min and ≥30 scored tries. I have ~25 scored tries so far on item 4 (let me count: e1, u8, s16, cast, castu16, swap, testfrombyte, byteval_outer, u8_swap, u8_late_test, u8_late2, t_u8, decl_order, m_* ×8, nopins, breset, treset, s_cond, s_block, s_outer_t = 7+3+2+1+8+3+3 = 27). Need ≥30. Let me do 5-8 more quick tries, then wall it.

But wait — before walling, one more idea worth testing: the *reverse* of the t_u8 finding. In t_u8 both were QI and the order was right. The problem was the source (v1 instead of v0). What if byteval is QI and testval is QI but assigned from *different* expressions that cse can't merge? E.g.:
- byteval = src; (QI from SI)
- testval = src; (QI from SI)
Both QI from the same SI → merged. What if testval = (u8)(src + 0)? folded.
What if testval is assigned from a *u16* cast: `testval = (u8)(u16)src;`? Still merged probably.

What if byteval = src (QI) and testval = src (SI) but I add a *second set* of testval from a QI value... no.

Another idea: what if the *source* of the $4 copy is a different pseudo by giving testval a real 2nd set inside the same block: `testval = src;` and then `testval = (u8)testval;`? That adds an insn.

Hmm, what about the dead-reset idea applied *before*: e.g. assign byteval = src, then testval = src, then `byteval = 0;`? no.

Let me try the "both QI + explicit distinct sources" combos quickly (4 tries), plus "testval QI assigned from byteval-free expression". Then wall.

Actually, one more promising idea: in the target, the $3 copy is `move v1,v0` — from v0 = src's register. If both are QI and merged, the second copy reads v1. What if I make testval's copy read from v0 by making testval *not* QI but the ORDER right... circular.

Alternatively: make the $3 copy NOT a copy from src but from a different register... no.

Let me try:
1. byteval QI, testval QI, testval assigned BEFORE byteval (both QI, swapped) — maybe order flips to a0,v0 then v1,a0? → wrong.
2. byteval QI, testval QI, with the shift statement between them.
3. byteval QI with an explicit cast, testval QI with an explicit cast.

And one more idea: make byteval's use earlier by computing the sb value early: e.g. add a temp `u32 t = byteval * 8 + 8;` right after the assignment (statement order move). Then the sll chain is born in block 1 and byteval's use is at the top → higher priority → $3 copy first! And the sll/addiu would move to block 1 (indices ~9-10), which is NOT the target (target has sll v1 at 19). Hmm, but sched1 might still sink it... risky but cheap to test.

Let me do these 5.
