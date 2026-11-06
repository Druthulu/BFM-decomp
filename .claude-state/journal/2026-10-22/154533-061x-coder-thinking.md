---
ts: 2026-10-22T21:45:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IVlS1nknRgjqeaBIBVBu
---
q_cast (both QI with explicit casts) = 1 REG-caller — probably the same as t_u8 (order right, source v1).

Let me check q_cast's listing quickly; if it's `move v1,v0` then `move a0,v1` (score 1 = one register mismatch), then the residual is only the copy source.

Hmm! Wait. What about making testval QI and assigned from `src` where src is u32, and byteval QI assigned from `src`, but with a *dead reset* of byteval between them? E.g.:

```
byteval = src;
testval = src;
```
cse merges them. If I put `byteval = 0;`... no, byteval is used later.

What if the merge is broken by giving byteval a second set of a *different* value that is then... no.

Actually, in q_cast the source of the a0 copy is v1. If the copy is `move a0,v1` (from $3), the target is `move a0,v0`. The values are identical; only the register differs. To break the cse merge between the two QI values, one of them must have a real 2nd set or a different mode.

Idea: make byteval QI and testval QI, but assign testval from src BEFORE byteval truncates... same.

Idea: make byteval QI and testval HI (u16) — m_u8_s16 was 2 ORDER (wrong order). Hmm.

Let me count tries: 27 + 5 = 32 scored tries. Time: 16:06, item started 15:34 = 32 min. Past 30 min → stop and record a WALL.

Best = 2 (ORDER) with u8 (or s16/cast/decl_order/matrix variants all 2). The best lever-free body: score 2, 32 ins, only the two copies' order swapped.

Wall tag: `sched1-birth-order` (exists in walls.txt, G16 func_801372B0: "sched1 orders two independent insn births opposite to source; reorder moves the other"). Evidence: the sched dump shows sched1 reorders insn 40 (v1 copy) and 43 (a0 copy) — the RTL order is v1 first, the scheduled order a0 first; the $4 value's use (beqz) is nearer, so it gets higher priority; the only spelling that flips the order (both QI) makes cse merge the two values so the a0 copy reads $3.

Hmm, but wait — is `sched1-birth-order` the right tag? The tag description: "sched1 orders two independent insn births opposite to source; reorder moves the other". Yes, exactly matches: two independent births, opposite to source, and reorder doesn't help (I tested both source orders).

Let me write win.c = the best lever-free body (u8.c, score 2) and record a WALL with best 2.

Wait: the "best" column should be the lowest score of a lever-free body = 2.

But hold on — is u8.c lever-free? It drops the launder but keeps the pins (allowed). Yes.

Hmm, but should win.c be the u8 variant or the plain e1 (u32, score 3)? The best is 2, so use u8.c. But is changing byteval to u8 an added lever? No — it's a real C move (widths are in the C0505 catalog).

Actually, let me reconsider one thing before walling: the sched dump showed the order swap happens in sched1. But maybe there's a lever-free way to change the priority: the $4 copy is scheduled first because its use (beqz at 13) is closer to the end of... Let me check if priority is computed over the block only. If block-only, both would be 1 and the tie would go to RTL order (v1 first) — which contradicts. So priority spans blocks.

Since priority = distance to function end (roughly), the $4 use at 13 is far from the end (14→...→30), the $3 use at 19 is closer to the end. So $4 has a LONGER path → higher priority → first. To flip, the $3 use must be farther from the end than the $4 use. The $3 use is at 19, $4 at 13. So I'd need the byteval use to be earlier... which it isn't.

Therefore this is structural: in the target, how could v1's copy come first? Unless in the target the $3 copy was NOT scheduled by sched1 (e.g. born by reload/greg after sched1, or the asm launder anchored it). Indeed with the launder, the asm insn anchored the copy at birth (asm can't move).

So: the wall tag could be `sched1-birth-order`. Good enough; evidence will state it.

One more consideration: maybe I should double check the "best" body: is there a variant scoring 2 with fewer changes? All the single-width variants score 2. I'll use u8.c (byteval u8) — hmm, actually simpler: m_u32_u8 (testval u8)? No, keep u8.c.

Actually, for the record, the cleanest is `s16` or `u8`. I'll take u8.c and note it.

Hmm, wait. Let me reconsider one more possibility quickly (1 try): what if I use `u8` for byteval AND keep testval u32, but assign testval from a *u8 cast of src*: `testval = (u8)src;` with testval u32 → the value is the same SI value (known <16) → probably no change.

Or: make the $4 copy come from the andi result directly by writing `testval = src & 0xf;`? folded.

I'll stop here and record the wall. Time 16:07.

Actually — one thing worth 1 more try: what if the byteval assignment is moved to *after* the `if` (so its birth is later)? Then the copy would be in the second block... and the target has it at 7 (before the beq). No.

Let me also reconsider: is score 2 with `u8` really "the lowest score of a lever-free body"? I tested many. Yes, 2.

Record item 4 as WALL, best 2.

Wait — but the result format allows PARTIAL:<kinds still kept> only if win.c scores 0 keeping those levers. Not our case. WALL it is.

Let me write win.c = u8.c, results row, moves.md line, notes.md for the dir, and clean up the dump dir (disk!). Then do the log.

Also I should double-check my items 1-3 win.c files exist and the results rows are right. And delete scratch dumps.

Let me also verify the results.tsv format: `dir file func kinds result best tries wall evidence`. My rows for items 1-3 use tabs? I used printf with \t — yes.

For item 4: dir=func_80177F84__func_80177F84, file=src/shared/ov/func_80177F84.h, func=func_80177F84, kinds=launder, result=WALL, best=2, tries=32, wall=sched1-birth-order, evidence=gcc pass + mechanism ≤140 chars.

Evidence: "sched1 reorders the two pinned copies: rtl v1 copy (insn40) before a0 copy (insn43), scheduled a0 first (beqz use nearer = higher priority); both-QI spellings flip the order but cse merges them (a0 reads v1)" — that's ~200 chars. Trim to ≤140:
"sched1: rtl insn40 ($3 copy) before insn43 ($4), scheduled $4 first (beqz use nearer = higher prio); QI spellings flip order but cse merges (a0 reads v1)" = ~150. Trim more:
"sched1: $4 copy (beqz use nearer = higher prio) scheduled before $3 copy; QI spellings flip order but cse merges them (a0 reads v1)" ~130. Good.

Let me finalize.
