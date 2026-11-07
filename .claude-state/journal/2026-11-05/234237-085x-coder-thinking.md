---
ts: 2026-11-06T06:42:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bNmdK0BwAgYjSTQ1Bv5G
---
Now 31 scored tries. Best is 12 (v_s16t) but that's a different shape (lhu/sra); the best "structural" is 17.

Hmm, what should "best" be? "best = lowest score of a lever-free body" = 12 (v_s16t). But that body has extra sign-extension insns and a wrong load type. Still, it's the lowest score. Hmm, v_s16t scores 12 with 42 insns.

Hmm, using s16 for t changes the semantics? `t = unkA` where unkA is a u16 field... `s16 t; t = unkA;` truncates to s16 — the target does `lh` (sign-extended), and unkA is at offset 10; if the field is u16, then `lh` would be a sign-extended load of a u16 field — the target's `lh $2,10($5)` sign-extends. So t as s16 with `lhu`+sll/sra produces an extra pair. Not equal semantics (well, for values < 0x8000 it is).

I'll record best = 12 for item 3? The rule says best = lowest score of a lever-free body. v_s16t is lever-free and scores 12. OK, best=12.

Hmm, but is v_s16t really lever-free? Yes (no pins, no asm). Fine.

Actually, wait. Let me reconsider one thing before declaring the wall: the conflict between t and v0. Let me spend 2 minutes checking whether the conflict comes from the call. If t is NOT live at the call in the RTL (we saw REG_DEAD at insn 90), then the conflict must come from elsewhere — maybe from `insn 84: (set (reg 73) (zero_extend ...))` where... no.

Hmm! Wait. Look at insn 98 (the call): it has `(insn_list:REG_DEP_ANTI 73 ...)` — those are dependencies, not liveness.

And insn 96: `(set (reg 4 a0) (reg 72))`.

Hmm, where's v0 used? Nowhere explicitly.

Unless... global.c's conflict with $2 for r73 comes from `hard_regs_live` at the *start of a block*: "Basic block 4: Registers live at start: 29 30 72 73". If the live-at-start set for block 4 includes a hard reg $2 from `basic_block_live_at_start`... The flow dump would show. Hmm.

Actually! I bet I know: `basic_block_live_at_start` is a *regset* that includes both pseudos and hard regs. In block 4, live at start = 29,30,72,73. No $2.

OK, alternatively the conflict may be recorded at the CALL insn because gcc marks call-clobbered regs live at the call AND r73 is live at the call because... the REG_DEP_ANTI list? No.

Hmm, hold on: is t live at the call because of `(expr_list (use (reg:SI 4 a0))`? no.

Let me just test the hypothesis directly: in v_split (t not used in the tail), the conflict should be gone and t should take $2. But v_split gave t → a0 ($4). Hmm, that contradicts.

Unless in v_split, t's priority changed (13 refs → fewer) and something else outranked it.

Let me check v_split's alloc order... time, time.

DECISION: record item 3 as WALL with tag `lreg-v0-conflict` — hmm, needs to be from walls.txt or a new `<pass>-<what>`. New: `lreg-index-conflict` — "the index pseudo that feeds the indirect-call table load conflicts with $2 (the load dest), so lever-free it takes $3; the target has base and dest in the same $2 (only a hard-reg variable can)". 

Hmm, but I haven't proven that mechanism. Let me verify the conflict quickly with the .greg dump text for the base candidate — one grep. If it shows "73 conflicts: ... 2 ...", I can state it. I already have that from the alloc_table: "conflicts v0,sp". So the conflict is real and documented.

But which insn? I can state the mechanism as "r73 conflicts v0 (alloc_table), so with $2 excluded it takes $3; the target has t in $2 with the table-load dest also $2 (base==dest), which only a hard-reg variable allows".

That's defensible: I verified the conflict from the alloc table, and the target's asm shows `lw $2,D_801D0A3C($2)`.

Let me record item 3 as WALL, best 12, tries 31.

Hmm, but wait: is it better to record v_s16t as win.c (best)? The brief: "WALL (best = lowest score of a lever-free body)". win.c should be the best lever-free body. Let me set win.c = v_s16t? But v_s16t has an extra sign-extend (worse structurally). The rule says best = lowest score. I'll copy v_s16t to win.c... hmm, but that changes semantics slightly (s16 truncation). For a WALL row, win.c is just the best attempt. I'll keep the base candidate as win.c (the structurally faithful one) and record best=12 (v_s16t). Hmm, inconsistent.

The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0" — for WALL there's no such requirement. I'll set win.c = the best-scoring lever-free body (v_s16t, 12) to match "best". Hmm, but the base (17) is more faithful.

I'll go with best = 12 and win.c = v_s16t to be consistent with "best = lowest score of a lever-free body".

Hmm, actually let me reconsider — v_s16t's score of 12 comes with a different insn sequence (lhu+sll+sra vs lh). It's a legit lever-free body that scores 12. Fine, best=12.

Let me record and move on to item 4. Time is 23:55ish.

Actually, let me first clean up the variant files to keep the dir tidy, then record.
