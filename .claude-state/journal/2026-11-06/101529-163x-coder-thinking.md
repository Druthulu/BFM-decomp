---
ts: 2026-11-06T17:15:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5rDs87hcPemL8cJOKV59
---
Now real numbers:
- mask 87: birth 571, death 549?? The uses are at insns 429,439,...,549 — BEFORE the def at 571! That's because sched1 reordered? No, these are the lreg dump insn numbers; the ands at 429-549 use the mask defined at 571-572 — impossible in a single block unless the dump's insn chain order differs from the numbers (the insn numbers are UIDs; the RTL chain order is given by the prev/next pointers). So the mask is defined at UID 571-572 but scheduled/placed earlier in the chain (sched1 moved it before the ands, and the UIDs stayed). The lreg summary "13 times across 179 insns" — hmm.

- constant 117: def 563-564, use 170 (the store). UID 170 < 563, again sched1 hoisted it earlier in the chain.

So UID-based live ranges: mask 87: min UID 429? max 572 → 143 span; constant 117: min 170, max 564 → 394 span.

pri: mask 13 refs: 3*13*4/143 = 1.09. constant 2 refs: 1*2*4/394 = 0.02. The mask should win by far!

Yet the constant got t6. So local-alloc's priority is NOT what decides here. Something else: maybe local-alloc's `qty_order` sorts and the mask IS allocated first, taking t6... but then why does the final asm have the mask in t7?

Maybe regmove (after global alloc) swapped registers! regmove optimizes copy insns. Is there a copy involving the mask? The mask is computed as `lui t7,0xff; ori t7,t7,0xffff` — two insns into t7. Hmm.

OR: reload/regmove. Let me check the .greg dump's RTL for the mask: does it show t7 or a pseudo? The greg dump dispositions said 87 in 15. The greg dump is after global-alloc (which here allocates nothing). So local-alloc decided 15.

Wait, maybe local-alloc's find_free_reg for the mask found t6 occupied because the constant 117's *qty* was allocated first due to a *copy preference* or because the mask's qty has `qty_min_class`... Hmm.

Let me look at the local-alloc source for the allocation order: `qty_order` is filled with qtys that have no hard reg; sorted by qty_compare_1; then for each q, find_free_reg(qty_min_class[q], ...). The sort is by priority descending.

Unless the mask's qty was merged with another qty (reg_qty) — e.g., the mask pseudo might share a qty with the 0xFF000000 constant? No.

Hmm, hold on: maybe the mask's qty was allocated t7 because t6 was *already assigned to the constant in a previous pass*: `reg_qty` for the constant could have been given a *hard reg suggestion* via combine_regs from a copy. The store `(set (mem) (reg 117))` — no.

I could read local-alloc's dump more carefully: the lreg dump's disposition list order is the allocation order? Let me check the code: dump_local_alloc prints for each i in 0..max_reg: if reg_renumber[i] >= 0, print. So it's by regno, not allocation order.

Let me test a hypothesis empirically: if the mask were allocated before the constant, the mask would take t6. We can't control the order, but we CAN remove the competing constant's register pressure at the mask's birth by making the constant's use *later* than the mask's... they already overlap.

Alternatively, maybe the constant 117 is not block-local but gets a hard reg via `REG_EQUAL`/`REG_EQUIV` — the constant's insn has `(expr_list:REG_EQUAL (const_int -520093554))`. cse may have made it a REG_EQUIV, and local-alloc treats it as a *constant* that can be rematerialized... In local-alloc, `qty_const`? There's `reg_equiv_constant` handling: pseudos with REG_EQUIV constants can be replaced by the constant at reload, and local-alloc may give them a register early.

I'm going too deep. Let me try the empirical lever: change the mask so it's NOT a pure constant but computed, e.g., `m24 = 0xFFFFFF;` vs `m24 = 0xFF0000 | 0xFFFF;` (folded) vs `m24 = (u32)0xFFFFFF;`. Tried a5/a6/a7/a10 — all 21.

What if the mask is loaded from memory? Adds an instruction.

What if we swap the roles: use the mask for the packet store constants? no.

Hmm, what if we change the *constant that competes*: the 0xE100008E. In the target, that constant is in t7. In mine, in t6. What if we reorder the six packets so a different constant is materialized in that slot, one that would prefer t7 anyway? But the target has exactly the 0x8E in t7, so the other constants' registers would differ.

Actually, what if the constants are materialized in a different ORDER by sched1, so that the 0x8E is not the third? The target's order: a2=0x8A, t0=0x8C, t7=0x8E, s5=0x9A... Hmm, in the target the third is t7 because t6 was taken by the mask.

Let me try a totally different approach: brute-force the mask's C form with a search over small variants (constant spellings, declaration positions, type). I've done ~15. All 21.

Maybe the intended lever-free crack is impossible → WALL with best 21. That's a good result (21 of 215).

Time: 10:14, item 3 started 10:05:34 → 8.5 min. Let me try a few more promising things, then decide.

Idea: the mask could be given a copy preference by assigning it to a variable that's copied: e.g., `m24 = 0xFFFFFF; m24b = m24;` then use m24b — the copy might tie them and give the same reg... no help.

Idea: make the mask's definition *not hoisted* by sched1, so it stays near the uses and its live range is short → higher priority? The hoisting moves it earlier in the chain, but UID-based priority uses UIDs, not chain position. So hoisting doesn't change the priority.

Hmm, then why is the constant allocated first? Let me look at the local-alloc dump for the *qty order*: the lreg dump prints "Register X used..." lines in qty order? The lines I read are in regno order? Let me check the order of the "Register ... used" lines: 72,73,74,...,87,89,... — ascending regno. So no.

OK here's another thought: maybe the mask pseudo 87 is *not* allocated by local-alloc at all; it might be a global pseudo? The greg dump shows "Register dispositions: ... 87 in 15" — that's local-alloc's list (printed in the local dump too). If 87 were global, it'd be in the greg's "N regs to allocate" list. The greg dump had no such list, so all were allocated locally.

Local-alloc assigns a register only if the qty is "local" (dies in one block). All are local.

The order: qsort by priority. My computed priority for 87 (1.09) vs 117 (0.02). Unless the numbers differ: maybe `qty_n_refs` for 117 is huge because the constant pseudo is merged into a qty with many refs? The `REG_EQUAL` note might cause cse to replace uses of the constant with the constant, creating multiple pseudos?

Let me just dump the lreg's qty info: local_alloc's dump prints "Register N used ..." for each *regno*, not qty. Hmm.

Alternative: use the --explain trace? No.

Let me try a completely different approach to the crack: maybe the intended lever-free body uses the mask inline and lets the constant be *shared*: if the mask constant (0xFFFFFF) and the packet constants are all materialized by cse, the register assignment might differ if we change the ORDER of the 12 statements. E.g., interleave the unk0 and *ot updates differently.

Actually, wait. Let me reconsider the target: `lui t6,0xff; ori t6,t6,0xffff` at insns 16-17, and the 0x8E constant at `lui t7,0xe100; ori t7,t7,0x8e` at insns 5-6. In the TARGET (pinned), the mask is forced to t6. The constant then takes t7.

Lever-free, we need the allocator to give the mask t6 naturally. Since the allocator's choice seems robust, maybe the actual original source had the mask as a *parameter/global* or the constant as something else.

Hmm, what if the original source didn't have `m24` at all but used `0xFFFFFF` inline in all 12 expressions (a1) — gcc's cse would create ONE pseudo for the constant. a1 = 21, same.

What if the original had the mask as `u32 m24 = 0xFFFFFF;` and the packet constants as... same.

I think this is a wall. Let me do a few more tries and then record WALL with best 21 (nopin).

Actually, let me try one more idea: make the mask's register preference to t6 via a *copy* from a value that's in t6. For example, compute something in t6 first? No control.

Or: use the mask in an expression where the other operand is already in t6? no.

Another idea: reduce the number of competing constants by expressing the packet constants as pointer stores with the constant in a *different type*: e.g., `*(u32 *)(p2 + 4) = 0xE100008E;` vs `((Unk*)p2)->unk4 = 0xE100008E;` — same.

What about storing the constant as a *negative* signed value: `*q2 = -0x1EFFFF72;` — the same const_int in RTL. Tried a8 (OR expression) — 21.

What if the six constants were written with different types (e.g., `(u32)0xE100008E` vs plain)? Same.

Let me try shifting the whole mask/tail block's order: move `m24 = 0xFFFFFF;` to be the FIRST statement of the function (before the packets). c1 did that (declaration) but not the assignment. a3 did (after pbase) → 23.

Hmm.

Let me try a *structural* change: replace the 12 `m24` uses with a helper variable that's re-assigned between statements? e.g., set m24 again before each use (13 assignments) — that would create multiple defs and probably change everything.

I'll accept a WALL for item 3. But wait — the budget says 20-30 min per item; a WALL needs ≥20 min and ≥30 tries. I have ~15 tries and 9 min. Let me continue trying for another 10 min with genuine variants, since 21 is close.

Let me think about what determines the mask's register. Let me look at the local-alloc allocation order directly by instrumenting? I could read local-alloc.c's dump for the qty order... Actually, the lreg dump prints "Register N used ..." lines — maybe those ARE in qty order (the order local_alloc processes them)? The code in local-alloc.c `dump_local_alloc` prints:

```
for (i = 0; i < max_regno; i++)
  if (reg_qty[i] >= 0) ... fprintf ("Register %d used %d times ...")
```
Probably in regno order.

Let me instead use a debug approach: patch? No.

Empirical: try to give the mask a higher ref count by using it in the 0xFF000000 position too, but that changes bytes.

Alternatively, reduce the mask's refs to lower its priority? That's backwards.

Hmm wait — maybe the allocation is NOT by priority here because all these qtys have the same `qty_min_class` and local-alloc's find_free_reg scans `reg_alloc_order` (default: ascending), and the first free reg at the mask's birth was t7 because t6 was occupied by a *live* qty at that time — regardless of priority. The mask's live range (UID 429..572) overlaps the constant 117's (170..564). If the constant was allocated first (priority 0.02 vs mask 1.09 — mask should be first), the mask would take t6.

Unless the priority formula's `qty_n_refs` for the mask is much lower. "Register 87 used 13 times" — maybe that's 13 refs but the *qty* includes only... hmm.

Let me try yet another empirical approach: change the mask to have MORE refs by splitting the 12 statements into 24 mask uses? No.

You know what? Let me test whether the priority ordering is by refs at all: if I make the mask's uses fewer (e.g., use 0xFFFFFF inline in 6 of the 12 and m24 in the other 6), the mask's refs drop to 6 and it might take a different reg — if the result is still t7, then priority isn't the driver.

Actually, a cheaper experiment: make the mask's definition a *copy from another variable* so it has a copy preference:
```
u32 mm = 0xFFFFFF;
m24 = mm;
```
Then m24 = mm is a copy; combine folds it. Hmm.

Let me try the "constant computed into a variable used in the same and twice" no.

OK, time to be pragmatic: continue with a batch of 10 more variants; if none crack, record WALL.

Variants:
d1: mask = 0xFFFFFF but the expression uses `& 0xFFFFFF` inline for the unk0 stores and m24 for the *ot stores (6+6).
d2: the reverse.
d3: mask as u32 via a cast at use: `(*ot & (u32)m24)`.
d4: swap the order of the two expressions in each statement (store *ot first, then unk0).
d5: put all 12 and-expressions in one block {}.
d6: declare m24 as `unsigned long`.
d7: m24 assigned from a volatile? no.
d8: use `m24 = 0xFFFFFF; m24 = m24;` (extra def).
d9: use `(m24 & *ot)`.
d10: use `(*ot & m24 & 0xFFFFFFFF)`.
