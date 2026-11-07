---
ts: 2026-11-06T06:05:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AV2uEgjIrBOK20TeFUzr
---
All folded or worse. Time 23:05.

OK, item 4 is a WALL. Let me write it up now. ~14 min elapsed. I'll do a final couple of tries while writing.

Let me write the notes, results row, and moves line for item 4, then move to item 5.

Best = 10 (k10 and many variants).

Wall tag: "flow-known-value" (new tag) — the flow pass knows cc == 1 on the fall-through, so the second `if (cc == one)` folds; the launder (opaque asm) was the only thing keeping it. Also the q/u swap is a local-alloc consequence.

Hmm, but wait: the WALL should have a single tag. Let me use "flow-known-value" and mention the local-alloc part in the evidence.

Actually, is there an existing tag? walls.txt has "flow-unused-result". The moves.md has "flow-known-nonzero". I'll use "flow-known-value" as a new tag.

Evidence ≤140 chars: "flow: cc==1 known on the fall-through, so the 2nd if(cc==one) folds (89 ins); a real 2nd set folds too; the zero-byte launder was the only keeper. best 10 (extra andi)".

Hmm, that's ~150. Let me trim: "flow knows cc==1 on the fall-through so the 2nd if(cc==one) folds (89 ins); real 2nd sets fold; only the zero-byte launder kept it; best 10 (mask keeps it, +1 andi)". ~160. Trim more: "flow knows cc==1 on fall-through; the 2nd if(cc==one) folds (89 ins), real 2nd sets fold; only the zero-byte launder kept it; best 10 (mask version +1 andi)". ~150. Hmm.

Let me count later.

Let me write the files.
