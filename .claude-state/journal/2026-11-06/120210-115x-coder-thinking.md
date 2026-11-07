---
ts: 2026-11-06T19:02:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3jjiWAXp27c16CKvieIT
---
In h049: insn 37 = 76 += 104, insn 40 = 74 += 104, insn 43 = 73 += 1 (a6), insn 46 = 75 += 104 (a5), insn 111 = slt (the test).

The final order: 37, 40, 43, 46, 111. So 76's increment first, then 74's. Which is a7? In h049's source, the increments are B(v1), A(a7), C(a6), D(a5) — the source order. The RTL: 37 = 76 (the first increment = v1), 40 = 74 (a7), 43 = a6, 46 = a5.

The target: a7's increment first, then v1's. In h049: v1 (76) first, then a7 (74).

The scheduler's order: 37, 40 — the RTL order is preserved (37 then 40) because their priorities are equal (1) and the ready list order at T-5/T-6... The trace: at T-3 the ready list is "46 (1) 40 (1) 37 (1) 43 (1)" → picked 46. Then T-4: "43 (1) 40 (1) 37 (1)" → 43. T-5: "40 (1) 37 (1)" → 40. T-6: 37.

So in the backward pass: 46, 43, 40, 37 — the last scheduled is 37 (the first in the final order). The ready list order at each T: the insns are added in some order; the scheduler picks the first of the highest priority. At T-5, the list is "40, 37" → picks 40 (scheduled), then 37. So the final order has 37 first (since it was scheduled last).

To get a7 (40) first in the final order, 40 must be scheduled LAST in the backward pass. The ready list at T-5 is "40 (1) 37 (1)": 40 is at the head. The scheduler picks the head → 40 first. So the final order = ...37, 40? Hmm, I need to be careful: each scheduled insn is prepended to the final sequence. The order of scheduling: 46, 43, 40, 37 → the final order is 37, 40, 43, 46 (reverse). So 37 (the last scheduled) is FIRST in the final code.

So to get 40 (a7) first in the final code, 40 must be scheduled last, i.e., the ready list must have 40 at the END when only 40 and 37 remain. The ready list at T-5 is "40 (1) 37 (1)" — 40 at the head. The list order depends on the insertion order, which follows the LOG_LINKS/dependency traversal.

The ready list is a LIFO/FIFO? In the new scheduler, `ready` is a vector; `schedule_insn` adds prev insns at the end (ready[new_ready++] = prev). `schedule_select` then picks... The trace shows the list "40 (1) 37 (1)" — 40 first. 

To flip the order, the RTL order of the two increments would need to swap (37 ↔ 40). The RTL order follows the source order (h049: v1 first). In g001 (a7 first), the RTL would have a7 first (37 = a7), but the allocation flips (wrong registers).

So: I need the source order a7-first (for the RTL/scheduling) AND the allocation a7=$7. In the sweep (192), the a7-first variants (perm A first) gave the wrong allocation (score 3). The v1-first variants gave the right allocation but the wrong order.

Hmm, unless a different combination (e.g., the init order or the store order) flips the allocation with a7-first increments. The sweep covered the init order (2), load (2), return (2) with all 24 perms — no 0.

What else could flip the allocation? The *store order* in the else block (7 stores), the declaration order, the loop test form, the a5 increment position (covered), etc.

The allocation flip mechanism: with the a7-first increments, the RTL has 74 (a7) first and 76 (v1) second; cse/combine then swap them (as seen: the .lreg had 14→76 and 17→74). The swap depends on cse's copy propagation.

Hmm, actually, maybe I can decouple: make the a7 increment's RTL first while the source has v1 first? The RTL order follows the source. Unless a statement reorder by the compiler changes it.

Alternatively: change the *pseudo* structure so that the allocation doesn't depend on the order. E.g., make a7 and v1 *not* copies of each other: if v1 were computed independently (e.g., `v1 = &D_8011FD10; a7 = &D_8011FD10;` — two symbol_refs), then no copy, and the target's `move v1,a3` would be missing.

What if the source has both `a7 = &D_8011FD10;` and `v1 = &D_8011FD10;`? cse would merge them (same value) and keep one copy.

Hmm.

Let me look at the *score-2 variants'* allocation: a7=$7, v1=$3. The only issue is the increment order (RTL order). What if I make the a7 increment's RTL come first while the source has v1's first, by introducing a dependency: e.g., `v1 = (unsigned short *)((char *)a7 + 0x68); a7 = (unsigned short *)((char *)a7 + 0x68);` — v1's increment reads a7 (old), a7's increment writes a7. The source order: v1 first, then a7. The RTL: v1 = a7+0x68; a7 = a7+0x68. The scheduler would put a7's increment... hmm, the instructions: `addiu v1_reg, a7_reg, 104` (v1 = a7+104) and `addiu a7_reg, a7_reg, 104`. The target has `addiu v1,v1,104` (v1 = v1+104). With different registers ($3 vs $7), `addiu v1,a3,104` ≠ target.

Unless... after the register allocation, a7=$7 and v1=$3, so `addiu $3,$7,104` — not the target's `addiu $3,$3,104`.

So no.

What if the increments are written as `a7 = (unsigned short *)((char *)a7 + 0x68);` and `v1 = (unsigned short *)((char *)v1 + 0x68);` but the source order is (v1, a7) — the score-2 case. The scheduler produces v1 first. Hmm.

The target's order: a7 first. The target's RTL (pinned): let me check the orig's RTL order of the increments — it's the source order (a7 first). And sched1 kept a7 first. In h049 (v1 first), sched1 kept v1 first. So sched1 preserves the RTL order for these independent insns (the ready-list order).

So I need the RTL order a7-first AND the allocation a7=$7. The allocation flip came with the v1-first source. Is there another way to flip the allocation with the a7-first source?

The allocation depends on: priorities (refs/live), conflicts, preferences. With the a7-first source, the RTL: a7 = symbol (74), v1 = 74 (76); the increments: 74 += 104 (a7), 76 += 104 (v1)...

With the v1-first source: the RTL: a7 = symbol (74), v1 = a7 (76); the increments: 76 += 104 (v1), 74 += 104 (a7)...

The difference is the increment order in the RTL, which affects cse/combine's canonicalization (the copy propagation direction) and the pseudo numbering/priorities.

Hmm. What if I keep the a7-first increments but change the *init* to `v1 = &D_8011FD10; a7 = v1;` (INIT2)? That was covered (h...). 

What about changing the *return* or the load? Covered.

What about the *declaration order*? In GCC 2.7.2, decls don't affect the RTL order (pseudos are created at first use).

What about the *store order* in the else block? That changes the RTL and could flip the allocation. The sweep fixed the store order. Let me sweep the store order (a few permutations) with the a7-first increments.

The stores:
1. `*(int*)((char*)&D_8011FA1C + a5) = *(int*)((char*)a0 + 0x8);`
2. `*v1 = *a0;`
3. `...D_8011F9D6... = ...a0+0x2`
4. `...D_8011F9DA... = ...a0+0x4`
5. `...D_8011F9DE... = ...a0+0x6`
6. `...D_8011FA20... = ...a0+0xC`
7. `...D_8011FA24... = ...a0+0x10`

The target's order (from the asm): lw 8(a0); sw; lhu 0(a0); sh; lhu 2; sh; lhu 4; sh; lhu 6; sh; lw C; sw; lw 10; sw. That's the source order.

If I reorder the stores, the asm order changes (they're in the else block, scheduled in order) → the target's order must be preserved. So no store reordering.

Hmm. What about the *a5 increment* position: covered by the permutation sweep.

What about the loop test: `a6 < 0x14` vs `0x14 > a6`? The target: `slti v0,a2,20` (a6 < 20). The reversed form `0x14 > a6` → `slt v0,20,a6`? different.

What about `a6 != 0x14`? no.

OK, let me think about the allocation flip differently: the score-2 variants have the RIGHT registers. The only issue is the increment order in the RTL. Since sched1 preserves the RTL order for these insns, I need the RTL order a7-first. The RTL order follows the source. But the source order a7-first flips the allocation to the wrong one.

UNLESS: the allocation flip is caused not by the increment order per se but by the *cse canonicalization* of the copy `v1 = a7`. Let me look at the g001 (a7-first) build's .lreg: insn 14 → 76 (a7?) etc. The cse renamed the pseudos. 

Hmm, what if I make the copy direction explicit differently: `a7 = &D_8011FD10; v1 = a7;` (INIT1) vs `v1 = &D_8011FD10; a7 = v1;` (INIT2). Both were swept.

Let me look at the actual allocation difference between a score-2 variant (h049) and g001:
- h049: increments (v1, a7, a6, a5) → a7=$7, v1=$3.
- g001: increments (a7, v1, a6, a5) → a7=$3, v1=$7.

The increment order changed the allocation. Why? The priorities: a7's refs/live vs v1's. Hmm, the refs/live shouldn't depend on the order... but the *cse* canonicalization does: with v1's increment first, cse may treat v1 as the canonical pseudo and merge differently, changing which pseudo is a7 and which is v1 in the final RTL, hence the priorities.

Let me look at h049's .lreg table vs g001's. If the priorities differ, maybe I can adjust refs/live via a C change.

Actually, here's a cleaner idea: the target's a7-first increment order is what the source has. What if I make the *v1 increment* not exist as a separate statement — e.g., v1 = a7 after the increments? Let me think:

```
if (*v0 != 0) {
    a7 = a7 + 0x68;
    v1 = a7;        // instead of v1 = v1 + 0x68
    a6 = a6 + 1;
    a5 = a5 + 0x68;
}
```
Then the RTL: a7 += 104; v1 = a7 (a copy!). The asm would be `addiu a3,a3,104; move v1,a3` — but the target has `addiu v1,v1,104`. Different instruction (move vs addiu). No.

What about the opposite: v1 = v1 + 0x68; a7 = v1;? The asm: addiu v1,v1,104; move a3,v1. Target: addiu a3,a3,104; addiu v1,v1,104. No.

Hmm.

What if the a7 increment is expressed as `a7 = (unsigned short *)((char *)a7 + 0x68);` and the v1 increment as `v1 = (unsigned short *)((char *)v1 + 0x68);` but I reorder the *source* to (a7, v1) and add a dummy statement between them to flip the allocation? E.g., a no-op that doesn't generate code? `a6 = a6;`? dead.

What about the loop body's `v0 = v1;` — the load. In the sweep, LOAD1/LOAD2 were covered.

What about `v0 = v1; if (*v0 != 0)` vs `if (*(v0 = v1) != 0)`? Same RTL.

Hmm, let me look at the .lreg of g001 vs h049 to understand the allocation flip. Maybe I can find a targeted change.

Actually, maybe simpler: in the target's build, the increments' order is a7-first because the source is a7-first. The allocation in the target is a7=$7 due to the PIN. Lever-free, the a7-first source gives a7=$3. So the allocation difference is inherent to the pin's removal, not the order. And the v1-first source gives a7=$7 by luck (the allocation flip), but the increment order then follows the source (v1-first).

So to crack it, I need the allocation a7=$7 with the source a7-first. Since the allocation depends on the pseudo numbering (which depends on the statement order), maybe another statement's order can compensate.

Let me look at what determines a7=$7 vs $3: the priorities. In g001 (a7-first): the .lreg table (from the earlier dump) had 76 (a7?) pri 20000 and 74 (v1) 5833. In h049, maybe the priorities swap. Let me dump h049's table and compare with g001's.

From the h049 dump (dumph), let me run alloc_table.
