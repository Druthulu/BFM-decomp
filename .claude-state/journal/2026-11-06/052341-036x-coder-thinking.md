---
ts: 2026-11-06T12:23:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xw0JBY7IjkpsF68DLln3
---
C0535 is about block splitting for scheduling. Our issue is a local-alloc tie.

Let me check C0414 (dead-reset cse-breaker) — that's about launders.

Actually, our remaining diff (b2) is a REG-caller tie. Maybe I can influence local-alloc's qty priority with extra real refs on pos. If pos has higher priority... but the tie isn't priority.

Hmm, wait. Let me reconsider: maybe the tie can be broken by making the addiu's source NOT die by using pos in the OTHER arm too... no, blocks.

Let me look at the target's actual allocation: pos = t4, var_v0_3 = v0. In b2, pos = t4, var_v0_3 = t4 (tied). What if var_v0_3 were born in a block where pos is live? It is born in the arm where pos dies.

What if we compute var_v0_3 BEFORE the D_801152AA store and use pos again after? E.g.:
```
if (arg1 & 1) {
    var_v0_3 = pos + 2;
    b4b = D_801909C4;
    D_801152AA = 0xFFF;
}
```
pos still dies at the addiu.

What if the order is: `D_801152AA = 0xFFF; var_v0_3 = pos + 2;` — same.

The ONLY way pos isn't dead at the addiu is a later use in the same block. There is none.

Therefore, the target's v0 must come from a different mechanism: maybe var_v0_3 was born BEFORE pos died in the source, e.g., the source had `var_v0_3 = pos + 2;` then used pos again... In the original lever body, the keepalive at the END (after the store, in the join block) kept pos live. So liveness across blocks: at the addiu (arm block), is pos live-out? The keepalive is in the join block, reachable from the arm → yes, pos is live-out of the arm → pos is NOT dead at the addiu (it's live at the block end) → no tie. Right.

So we need pos to be live-out of the arm blocks. A real use after the join. In the join block, after `b4b[1] = var_v0_3;` there's the tail computing D_80126720/22/24 from arg0.

Is there a real way to use pos there? The tail stores midpoints of arg0's fields. No.

BUT: what if we restructure the code so that pos IS needed after the join? E.g., the store `b4b[1] = var_v0_3;` could be written using pos in the address... no.

Hmm, what if the D_801152AA store and the b4b[1] store order changes such that pos's last use is in the join block? E.g.:

```
if (arg1 & 1) {
    b4b = D_801909C4;
    D_801152AA = 0xFFF;
    var_v0_3 = 2;
} else {
    b4b = D_801909C4;
    D_801152AA = -0xFFF;
    var_v0_3 = -2;
}
b4b[1] = pos + var_v0_3;
```
Now pos's last use is in the JOIN block. The join addiu: pos dies at this insn → tie again → dst = t4. Target: addiu v0,t4,2. Damn.

Unless in this shape gcc computes `pos + var_v0_3` where var_v0_3 is a register (not a constant ±2) — then it's `addu`, not `addiu`. Target has addiu.

OK, so the tie needs pos live-out of the join block.

What if the join block's tail uses pos? No.

What if we move the pos use to the very end: `b4b[1] = var_v0_3;` in the join, and then the tail, and then... pos unused.

Alternatively, make pos's value needed in the tail in a REAL way: hmm, what if `D_801152AA` gets set to `pos & 0xFFF`? No, target stores 0xFFF/-0xFFF.

I'm now fairly convinced this is a WALL for a full MATCH, but let me try the do-while trick anyway since it's cheap. Maybe the loop note changes the block structure such that the arms are in the same EBB and pos is live.

Try: wrap the if+store in do{}while(0):
```
do {
  if (arg1 & 1) {...} else {...}
  b4b[1] = var_v0_3;
} while (0);  // !FAKE: do-while
```
Does this extend pos's liveness? The loop body ends after the store; pos isn't used in the loop body after the addiu. No.

Alternative: put the addiu at the END of the do-while and the store after? e.g.
```
do {
  if (...) { ... var_v0_3 = pos + 2; } else { ... }
} while (0);
b4b[1] = var_v0_3;
```
Same.

Hmm.

Let me try a different tack: use the do-while to raise pos's REG_N_REFS so that local-alloc's qty priority makes... the tie is still there.

Actually, WAIT. Let me reconsider the tie mechanics in gcc 2.7.2 local-alloc. The function `qty_phys_copy_sugg` sets copy suggestions for pseudos that are copied. The tie for a 2-address insn comes from `reg_alternate_class`/`qty_phys_sugg`? In local-alloc, `update_equiv_regs`? Hmm.

Actually gcc 2.7.2's local-alloc: for each insn, it finds `qty` for operands; `reg_qty`; the "preferences" come from `find_free_reg` with `qty_phys_num_sugg`. The tie (dst = src) is suggested when the insn is a "copy" pattern or when the machine description says the output can share the input? For `addiu`, the MIPS md pattern is `(set (match_operand:SI 0 "general_operand" "=d,d") (plus:SI (match_operand:SI 1 "general_operand" "d,d") ...))` — with `d` constraints, the register allocator CAN use the same register for 0 and 1 (that's the whole point of "d" = general reg; the allocator decides). The tie is suggested by local-alloc when `reg_qty[src]` dies in this insn: `if (src dies) dst prefers src's reg`.

So yes.

Given the time (I'm ~35 min on item 1), let me decide: record a WALL? The brief: "Budget 20-30 min wall per item; past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

Hmm, I have only ~10 scored tries. A WALL requires ≥30 scored tries. That's a lot but they're cheap (a few seconds each). I could generate variants programmatically and score them in bulk with sc.sh (one line per candidate). That's the intended workflow: generate 20-30 candidates and score.

Let me be smart: write a generator that produces variants of the b2/b1 bodies with different tail shapes, and score them all. Each score takes ~1-2s.

But actually, maybe better to spend the remaining effort on making b2 → 0. The diff is tiny. Let me think about how gcc could produce `addiu v0,t4,2` with real C.

Insight: maybe var_v0_3 doesn't need to be a separate pseudo — the target's `addiu v0,t4,2` could come from a different C expression: what if the store is `b4b[1] = pos + 2;` but pos is kept alive because... 

What if pos is used AFTER in the tail via the `p` variable? No.

Alternatively, what if the value stored is computed as `var_v0_3 = (s16)(pos + 2)` where var_v0_3 is s16 and the store is `b4b[1] = var_v0_3`, and then var_v0_3 is ALSO used later in the tail? No.

What if we make var_v0_3 live after the join by using it in the tail's computation: e.g., `D_80126724 = ... + (var_v0_3 & 0)`? identity.

Hmm hmm. What if the tail's D_80126724 store uses `var_v0_3` legitimately... it doesn't.

Let me look at the ORIGINAL body again for the tail:
```
b4b[1] = var_v0_3;
keepalive(pos);
D_80126720 = ...;
D_80126722 = ...;
D_80126724 = ...;
```
The keepalive(pos) is between the store and the tail. That keeps pos live into the join block. Without it, pos dies at the addiu.

So real C needs a use of pos in the join block. Is there ANY semantically valid use? The function returns 1. The globals don't use pos.

What if we reorder the code so that the `b4b[1] = var_v0_3` store happens in the ARMS and the join block has... no.

Alternatively: change where var_v0_3 is computed. What if `var_v0_3 = pos + 2` is computed in the JOIN block (after the if), using a delta computed in the arms:
```
if (arg1 & 1) { b4b = ...; D_801152AA = 0xFFF; delta = 2; }
else { ...; delta = -2; }
var_v0_3 = pos + delta;
b4b[1] = var_v0_3;
```
Target: addiu v0,t4,2 — but with a delta variable, gcc would emit `addu v0,t4,delta` (register add), not addiu. Unless delta is a constant propagated: gcc's cse/jump might propagate the constant into the join block (it does! cse propagates constants across blocks with `cse` in -O2? There's `cse-follow-jumps`; constants can be propagated). If delta becomes constant 2 in the join, `pos + 2` → addiu. And pos dies there → tie.

Argh.

OK, let me consider a completely different possibility: maybe the tie can be avoided by making pos's register NOT the tie candidate because pos is a HARD register (pinned $12). In b2, pos is pinned $12 = t4! The addiu ties to t4. In target, pos is also pinned $12 and the addiu goes to v0. So the tie happens even with the pin.

Hmm, so in target, the keepalive was essential.

What if the keepalive is replaced by a REAL use of pos that's dead-code-eliminable but not identity: e.g., an extra condition that's always true but uses pos? Like `if (pos >= 0) { ... }` — that's a fake branch (changes code).

I think this is the `lreg-tie-dying-pin` wall from func_8017BF14: "c1 ($4 pin) dies at c1<<16; local-alloc ties sll temp to a0, target v0; mny keepalive cracked by do-while ref weight".

In that case, the keepalive was on `mny`, not on c1. The tie was between c1 and the sll temp. And it was cracked by "do-while ref weight" — adding refs to the OTHER pseudo (mny) changed... hmm, actually maybe the do-while raised the priority of the temp so it got v0 instead of tying? The tie preference isn't priority-based though.

Let me read that cookbook/notes if available. Search cookbook for lreg-tie.
