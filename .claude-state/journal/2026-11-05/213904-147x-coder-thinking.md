---
ts: 2026-11-06T04:39:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cnHlTrxR5NonDqzt6aam
---
Score 6 confirmed. Now fix the results row for item 4 (its own step). I'll rewrite results.tsv replacing the item-4 row. Let me use awk to replace the line starting with func_801810A4__.

New row:
func_801810A4__ov_SC06_016_jr_8017C8D0	src/ov_SC06_016/ov_SC06_016_jr_8017C8D0.c	func_801810A4	barrier	WALL	6	45	sched1-load-order	reuse p for obj->1C then p=model forces the reload after the chain (6), but sched1 issues +0x600 addiu before the lw (target lw,addiu) leaving a nop; 109 vs 108 ins

Evidence ≤140 chars: let me count roughly: "reuse p for obj->1C then p=model forces the reload after the chain (6); sched1 puts +0x600 addiu before the lw (target lw,addiu), leaving a nop; 109 vs 108" ~155 chars. Trim: "p reused for obj->1C then p=model: reload stays after the chain (6), but sched1 puts addiu +0x600 before the lw (target lw,addiu), leaving a nop; 109 vs 108" ~150. Trim more: "p reuse (obj->1C then model) keeps the reload after the chain (6), but sched1 puts +0x600 addiu before the lw (target lw,addiu), leaving a nop; 109 vs 108" ~152. Hmm ≤140. Let me do: "p reuse (obj->1C then model) keeps the reload after the chain (6), but sched1 puts +0x600 addiu before the lw (target lw,addiu); extra nop, 109 vs 108" = ~145. Trim: "p reuse (obj->1C then model) keeps the reload after the chain (6); sched1 still puts +0x600 addiu before the lw (target lw,addiu), extra nop; 109 vs 108" ~150.

Let me count precisely: "p reuse (obj->1C then model) keeps the reload after the chain (6); sched1 puts +0x600 addiu before the lw (target lw,addiu), extra nop; 109 vs 108"
p(1)+space=2; "reuse"(5)=7+space=8; "(obj->1C"=8 chars? Let me just keep it around 130 by shortening: "p reused for obj->1C then model: reload after the chain (6); sched1 puts +0x600 addiu before the lw (target lw,addiu), extra nop; 109 vs 108" — roughly 137. Good.

Tag: I'll use `sched1-load-order` (new). Actually, maybe reuse the existing `sched1-birth-order`? The walls.txt: "sched1-birth-order	sched1	sched1 orders two independent insn births opposite to source; reorder moves the other (T11 G16b func_801372B0)". Here the addiu and lw are independent-ish (the addiu depends on the chain, the lw is independent); source order lw then addiu; sched1 put addiu first; reordering the source didn't move it (z9). Hmm, "reorder moves the other" didn't hold. So a new tag is more honest: `sched1-load-order`.

Let me fix the row with awk.
