---
ts: 2026-11-06T19:08:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LvDPzC6PIgSN4LQLyDxz
---
s4 (a7 = v1+0x68; v1 = a7) gives: `addiu a3,v1,104; move v1,a3` vs target `addiu a3,a3,104; addiu v1,v1,104`. Same score 2 but a different residual (2 insns differ).

Hmm, s4 has the increments in the right ORDER (a3 first) but the wrong instructions (addiu a3,v1 vs addiu a3,a3; move vs addiu).

If a7 and v1 were the same register, `addiu a3,v1,104` would be `addiu a3,a3,104`. But they're different registers.

OK. Let me now decide: item 2 is a WALL at best 2. But wait — maybe I should try the cse canonicalization lever differently: make a7 live LONGER than v1 so cse picks a7 as canonical even with the a7-first increments.

The cse rule: `new` becomes canonical if `uid_cuid[regno_last_uid[new]] > uid_cuid[regno_last_uid[firstr]]` and it lives beyond the block. So the canonical is the one whose LAST use is later.

In w1 (a7-first): v1 became canonical → v1's last use is later than a7's. v1's uses: the load (block 1), the store (else block), the increment (loop block). a7's uses: the increment (loop block), the return (else block).

The else block's return is after the store, so a7's last use (the return) should be later than v1's (the store)... unless the store `*v1 = *a0` in the else block is AFTER the return in the RTL? No, the return is the last statement.

Hmm, but the else block's RTL order: the 7 stores then `return a7`. So a7's return use is the last. So a7's last uid > v1's last uid → a7 should be canonical. But w1 shows v1 canonical (the symbol in v1).

Unless the copy `v1 = a7` at the init is processed by cse BEFORE the last-use info is... the uids are static. Hmm.

Wait, maybe I have it backwards: maybe in w1 the canonical IS a7, and the symbol's pseudo (76) is a7! Let me recheck: w1's .cse: insn 14 sets 76 = symbol; insn 17 sets 74 = 76. The initial .rtl: insn 14 sets 74 (a7) = symbol; insn 17 sets 76 (v1) = 74.

After cse: insn 14 sets 76 = symbol. So cse rewrote the dest of the symbol insn from 74 to 76. If 76 = v1 (initial numbering), the symbol now goes to v1.

But cse's rewriting: make_regs_eqv(new, old) — the equivalence class; the canonical (firstr) is used for substitutions. If a7 (74) and v1 (76) are equivalent, cse substitutes the canonical for both. If the canonical is 76 (v1), the symbol's dest becomes 76.

Per the rule, `new` = the dest being processed. cse_insn processes `(set 76 (reg 74))` (v1 = a7): dest 76, src 74 → make_regs_eqv(76, 74)? or (74, 76)? The function's args: make_regs_eqv(new, old). In cse_insn, for a SET of a reg from a reg: it calls `make_regs_eqv (dest, src)`? Then new=76 (v1), old=74 (a7). The canonical is `old` (74 = a7) unless new (76) lives longer.

The check: new (76) becomes canonical if `uid_cuid[regno_last_uid[76]] > cse_basic_block_end || uid_cuid[regno_first_uid[76]] < cse_basic_block_start` AND `uid_cuid[regno_last_uid[76]] > uid_cuid[regno_last_uid[74]]`.

So if v1 (76) lives beyond the block and its last use is later than a7's (74), v1 becomes canonical. That's what happened in w1: v1's last use is later.

Hmm, so v1's last use IS later than a7's. In w1 (a7-first increments), v1's increment is later. And a7's return... maybe the return's use is in a block that cse doesn't count? Or the return's uid is earlier than the loop's increments? The else block comes after the loop block in the RTL text? The RTL order: the loop body (then branch) first, then the else block (stores + return). So the return's uid > the increments' uids. So a7's last uid (the return) > v1's last uid (the increment). Then v1 shouldn't become canonical...

Unless `regno_last_uid[a7]` is the increment, because the return's use of a7 is... `return a7` — a use. Hmm.

I'm clearly not going to resolve this by reasoning. Let me try a targeted experiment: make the return use a7 *and* make v1's increment earlier (the h049 order) — that's h049 (score 2, correct init). And make the a7 increment first — w1 (score 3).

So the canonical flip follows the increment order. Fine.

Given the time (item 2 at ~25 min, ~260 tries), and the best is 2 (ORDER), I'll record a WALL with best 2. But let me do a couple more experiments to see if the increment order can be fixed via a *different* statement placement, e.g., putting the a7 increment after the a6 increment but before v1's? The permutations covered all 24 orders; the score-2 ones are those where... let me check which perms gave score 2 and whether any has a7's increment before v1's but with a5 first (perm D,A,...). The score-2 perms: 6 (B,A,C,D), 7 (B,A,D,C), 8 (B,C,A,D)? Let me get the exact list from the log: h049 (perm 6), h051 (perm 6? n=51 → perm 6, init 0, load 1, ret 0), h053 (perm 6, init 0, load 0, ret 1), h055 (perm 6, init 0, load 1, ret 1), h057 (perm 7), h059 (perm 7), h061 (perm 7), h063 (perm 7), h065 (perm 8), h067 (perm 8), h069 (perm 8), h071 (perm 8), h161 (perm 20), h163 (20), h165 (20), h167 (20), h169 (21), h171 (21), h173 (21), h175 (21).

So perms 6 (B,A,C,D), 7 (B,A,D,C), 8 (B,C,A,D), 20 (D,B,A,C), 21 (D,B,C,A).

All have B (v1) before A (a7) except... perm 20/21: D,B,A,C — a5 first, then v1, then a7. So in all score-2 cases, v1's increment is before a7's in the RTL.

For the target's asm order (a7 first), I'd need A before B in the RTL, which gives the wrong canonical (score 3).

Hmm, unless sched1 reorders when the priorities differ. The priorities in the loop block were all 1. If I could make the a7 increment's priority higher than v1's, sched1 would pick it earlier in the backward pass → LATER in the final order (worse). To get a7 first in the final order, it must be scheduled LAST in the backward pass → LOWER priority than v1's? Let me check: in the orig's trace, the ready list at T-5 was "42 (1) 39 (1)" and it picked 42 (a7? no, 42 = v1 in the orig) — hmm.

In the orig's block 3: the insns 39, 42, 45, 48 with the final order 39, 42, 45, 48 (39 = a7 first). The trace: T-3 picked 48, T-4 45, T-5 42, T-6 39. So the LAST scheduled (T-6) is 39 = a7. The ready list at T-6 had only 39.

So the scheduler picks the ready-list order; the insns became ready in the order 48, 45, 42, 39 (reverse RTL). So the final order = RTL order.

For h049: 46, 43, 40, 37 → final 37, 40, 43, 46 (RTL order).

So sched1 preserves the RTL order for these. No priority trick.

Therefore: item 2 is a WALL at best 2 (ORDER: the two loop increments swapped), with the init matching.

Hmm, but hold on — maybe I can change the RTL order without changing the source order via a *dependency* that forces the a7 increment to be emitted first even though it's second in the source? No — the RTL order follows the source.

What if the source order is (v1, a7) but the *asm* order becomes (a7, v1) because of a scheduling dependency: e.g., if v1's increment were moved after a6's... The permutations (B,C,A,D) = v1, a6, a7, a5: the final asm order? It scored 2, so the asm has a7 after v1 presumably.

Hmm, what if I write the increments as (v1, a6, a7, a5) — the asm order would be v1, a6, a7, a5? The target is a7, v1, a6, a5. Hmm.

What about (a5, v1, a7, a6) = perm 20 → score 2. Its asm order: a5, v1, a7, a6? The target: a7, v1, a6, a5.

So no.

Let me accept the WALL for item 2. Actually wait — one more idea: the target's increment order (a7 first) with the correct canonical could be achieved if the *return* is the a7 use that makes a7 canonical AND the increments are a7-first. In w1, v1 became canonical. Why? Let me actually check the cse dump for w1: the canonical became v1 (the symbol in 76 = v1). Let me verify the initial pseudo numbers: in the initial .rtl, insn 14 = 74 (a7), insn 17 = 76 (v1). After cse: insn 14 = 76, insn 17 = 74. So cse substituted 74 (a7) with 76 (v1) — v1 canonical.

Per make_regs_eqv(new=76, old=74): 76 (v1) becomes canonical if it lives beyond the block and its last use > a7's last use.

v1's last use: the increment (loop) or the store (else block). a7's last use: the return (else block, after the stores). Hmm, the store `*v1 = *a0` is in the else block, before the return. So a7's last use (the return) is after v1's last use (the store)! Then v1 should NOT become canonical...

Unless the increments are in the loop block which is textually BEFORE the else block, and the return is in the else block. So a7's last uid = the return > v1's last uid = the store (if the increments are before). Hmm, but v1's increment (loop block) is before the else block too. So a7's last use (return) > v1's last (store or increment) → a7 canonical. But the dump shows v1 canonical.

So my understanding of the dump's numbering must be wrong: maybe 76 = a7 after all, and the "swap" is something else.

You know what? The empirical facts: w1 → the init has the symbol in $3 (v1's reg) and the copy in $7 (a7's reg); h049 → the symbol in $7 (a7's reg) and the copy in $3 (v1's reg). The target needs h049's init.

h049 has the increments v1-first. The target needs a7-first increments.

I've exhausted the obvious levers. Let me try ONE more idea: the *load* `v0 = v1` placed differently — e.g., inside the if? `if ((v0 = v1, *v0 != 0))`? That's a comma expression — same RTL.

Or `v0 = v1; if (*v0)` — same.

What about the loop shape: a `for` loop? Let me try converting the do-while to a for loop:
```
for (a6 = 8; a6 < 0x14; a6++) { ... }
```
But the init/order changes (a6 = 8 is before the loop; the increment is in the loop body). The RTL might differ. Hmm, the target's a6 init is before the loop (li a2,8 at the top) and the increment at the loop tail. A for loop would put the init before and the increment at the tail. Let me try:

```
a5 = 0x340;
a7 = &D_8011FD10;
v1 = a7;
for (a6 = 0x8; a6 < 0x14; a6 = a6 + 1) {
    v0 = v1;
    if (*v0 != 0) { a7 += ...; v1 += ...; a5 += ...; }
    else { ...stores...; return a7; }
}
return 0;
```
The order of the increments in the RTL: the for-increment (a6) is placed at the end (after the body), so the RTL order would be a7, v1, a5, a6? The target's asm order: a7, v1, a6, a5. Hmm.

This is a real possibility: the for-loop's increment is emitted at the loop tail, after the body's increments. The source body's increments would be a7, v1, a5 (in that order), and the for-increment a6 last. The target's asm: a3, v1, a2 (a6), a1 (a5) — so a6 BEFORE a5. Hmm.

With the do-while, the source order (a7, v1, a6, a5) matches the target. So the do-while is right.

OK, let me also try: `for (; a6 < 0x14; a6 = a6 + 1)` with the body increments a7, v1, a5 (the a6 increment from the for) — the RTL order: a7, v1, a5, a6? The target has a6 before a5. No.

Let me stop here. Item 2 = WALL at best 2.

Hmm, wait. Actually, let me reconsider the score-2 residual: the a3 increment is one slot late. The target's asm has it in the slot BEFORE v1's increment. What if I *duplicate* the a7 increment? E.g.:
```
a7 += 0x68;
v1 += 0x68;
```
vs
```
a7 += 0x68;
v1 += 0x68;
```
No.

What if the a7 increment is split: `a7 = a7 + 0x68;` — same.

Hmm, what if the a7 increment is written as `a7 = (unsigned short *)((char *)a7 + 0x68);` but placed AFTER the a6 increment in the source (order v1, a6, a7, a5)? The RTL order would be v1, a6, a7, a5 → the asm v1, a6, a7, a5 ≠ target.

OK. Let me also try the loop test position: the target's bne at f18 with the delay slot a1+=104. In h049, the bne's delay is a5+=104 ✓.

Alright: WALL. Let me record item 2: best 2, wall tag. The mechanism: cse's make_regs_eqv canonicalization of `v1 = a7` picks the pseudo with the later last use; the pin (hard reg a3) prevented cse from substituting it, keeping the symbol in $7 and the copy in $3. Lever-free, the init order and the loop-increment order are coupled: the order that makes a7 canonical (v1's increment first) also fixes the asm increment order to v1-first, one slot off the target.

Wall tag: `cse-copy-canonical` (from walls.txt: "cse canonicalises a reg copy onto the older pseudo; target keeps the pinned reg (W48)"). That's EXACTLY this item! Great — the tag exists (W48, probably this very function). So item 2 = WALL cse-copy-canonical, best 2.

Hmm interesting — the W48 line in moves.md says "cse-copy-canonical | cse | cse canonicalises a reg copy onto the older pseudo; target keeps the pinned reg (W48)". That's likely this func_80146750 item, already recorded as a wall in another shard? The moves.md line 45 area was from W48. So this item may be a known wall. Good.

Wait, but if it's already in moves.md, maybe the shard expects me to try anyway. The line says "target keeps the pinned reg (W48)" — the wall tag. So yes, item 2 is a known wall; I confirm it with score 2 (better than the prior?).

Let me now record item 2 and write the notes. Then the log and the final report.

Time: 12:10. Item 2: 11:45 → 12:10 = 25 min, ~260 tries.

Let me write the notes and the results row, clean up the dumps, then write the log.

Actually, one more thought on item 2: since the W48 moves.md line already records this wall, maybe the expected outcome is exactly this. Fine.

Let me write the notes.
