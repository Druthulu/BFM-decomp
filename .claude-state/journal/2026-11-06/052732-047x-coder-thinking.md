---
ts: 2026-11-06T12:27:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5BEpyjbe6okjqBu0atzA
---
MATCH — byte-identical! d1x keeps the launder (asm) and keepalive (asm), pins, and replaces the barriers with do-while(0). So result = PARTIAL:keepalive,launder (barrier cracked).

Now, can we crack more? We know:
- Removing the keepalive: b2-equivalent with do-while barriers → vA = 3. So keepalive is needed.
- Removing the launder: c5x = 4 (with do-while barriers? c5x had real barriers... let me redo: c5x = orig with launder→`a1v = arg1 & 1` and keepalive dropped, barriers kept → 4).

What about launder→real 2nd set + keepalive kept + barriers→do-while? c4x was that with barriers (score 1). With do-while instead of barriers, maybe 0? c4x's only diff was the andi input reg (t3 vs a1) — barriers wouldn't change that. So no.

So the launder can't go. The keepalive can't go. Barriers CAN go (cracked via do-while).

Result: PARTIAL:keepalive,launder. 

But wait — maybe I should double check whether the keepalive can be replaced by a do-while ref-weight trick (moves line 25: "mny keepalive cracked by do-while ref weight"). Let me think: the keepalive keeps pos live past the addiu to avoid the tie. A do-while can't extend liveness. But maybe a do-while with pos used... 

Actually, what if we wrap the whole tail in a do-while where pos is used in the loop condition? `do { ... } while (pos < 0);`? That's a real loop (not while(0)) — changes control flow (would loop if pos<0). Not allowed semantically? Actually if pos < 0 it would loop forever — wrong.

What about `do { ... } while (pos, 0);` — comma operator with pos → a use of pos in the condition, evaluating to 0. That's an identity-ish launder (a dead use of pos) = keepalive by another name. The brief forbids new levers; a dead use is a keepalive. Not allowed.

So keepalive stays. PARTIAL:keepalive,launder.

Hmm, but hold on: is a PARTIAL result acceptable as "done" for the item? The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". So yes.

Let me write win.c = d1x.c and a notes.md, then move to item 2. Time: item 1 took ~50 min (over budget). Let me speed up on the remaining items.

Actually wait — before finalizing, let me try one quick thing: can the keepalive be replaced by extending pos's liveness with a real use in the tail? We established no real use exists. Skip.

Let me write win.c and results row later (one row per item at the end). Actually the brief says append exactly one row per item; I can batch them at the end or after each item. "Per item append exactly one row" — I'll do it after each item.

Result row format: dir file func kinds result best tries wall evidence
- dir: func_80136824__ov_SC04_011_jr_80135D20
- file: src/ov_SC04_011/ov_SC04_011_jr_80135D20.c
- func: func_80136824
- kinds: barrier,keepalive,launder
- result: PARTIAL:keepalive,launder
- best: 0
- tries: count scored candidates. Let me count: a1,a2,a3,a4 (4), b1,b2,b3 (3), vA-vO (15), b4,b5,b6 (3), c1x,c2x,c3x (3), c4x,c5x (2), d1x (1) = 31. 
- wall: PARTIAL needs a tag: the keepalive wall is `lreg-tie-dying-pin` (from moves line 25, exists? It's a tag used in moves; is it in walls.txt? Not listed. walls.txt has `lreg-copy-pref-dying-base`, `lreg-qty-priority`, etc. The moves line 25 uses `lreg-tie-dying-pin` — maybe a tag introduced later. The brief says: wall (WALL/PARTIAL) = a tag from walls.txt or a new `<pass>-<what>`.

For the keepalive: local-alloc ties the addiu temp to the dying pinned pos → target v0. Tag: `lreg-tie-dying-pin` (a new tag, pass=lreg). That matches the moves entry exactly.
For the launder: the andi's input must read the incoming hard reg; real C reads the pseudo. Tag: `global-hardreg-reserve`? Hmm. The launder's wall: "the asm reads the hard reg a1 directly; real C reads the pseudo's home". Could tag `no-c-spelling`? Or `lreg-hardreg-live-end`. Let me phrase: `expand-hardreg-operand`? A new tag: `lreg-hardreg-operand` — the tied asm operand reads the incoming reg, no C spelling. I'll use `no-c-spelling` (exists) with evidence: "launder's tied operand reads the incoming a1; real-C 2nd set reads the pseudo home t3 (score 1)".

Evidence ≤140 chars: "PARTIAL: barriers -> do{}while(0) (cse1 EBB split); keepalive: lreg ties addiu to dying pinned pos (t4) vs v0; launder: tied asm operand reads incoming a1, C 2nd set reads t3 (score 1)". That's >140. Need ≤140 chars. Let me count later.

Let me now write win.c (copy d1x) and notes.md.

Actually, I should double-check that d1x doesn't have any leftover barrier and that the do-while markers are there. Also verify win.c scores 0 via dt.sh at the end.

Let me also reconsider: could we ALSO crack the launder by keeping the keepalive and using the "real 2nd set" plus a trick to read a1? No.

Proceed.
