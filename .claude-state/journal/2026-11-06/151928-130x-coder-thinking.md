---
ts: 2026-11-06T22:19:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2lBQWK1s2FhdQIdi8jNC
---
s1.c = score 0! MATCH! 

s1 = i2 + a do-while around the FIRST 3 sxy lines. Score 0, 197 ins, MATCH!

So item 1 is cracked: win.c = s1.c (score 0), lever-free (pins removed, only do-while with !FAKE comment). 

Wait — the do-while is a "lever"? The constraints say: "no `do{}while(0)` only with `// !FAKE: do-while`". The brief: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin..., launder, barrier, keepalive macro or asm; no new lever of any kind." Hmm, "no new lever of any kind" — is a do-while a lever? The MOVES+ section explicitly endorses cookbook C0535 (do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item). And the constraint says "`do{}while(0)` only with `// !FAKE: do-while`" — meaning it's allowed if annotated. So do-while is an allowed C construct, not a banned lever (the banned kinds are pin/launder/barrier/keepalive/asm).

But "no new lever of any kind" — hmm, that could be read strictly. Yet the brief's MOVES+ explicitly recommends C0535 do-while as a move. So it's allowed with the annotation. I'll keep it and note it.

Also note: s1 includes the i2 do-while around the otp block AND the s1 do-while around the first 3 sxy lines. Both annotated `// !FAKE: do-while`. Good.

Let me verify s1 has no asm/register, and the score is 0 on the actual TU (dt.sh says MATCH). Then set win.c = s1.c, update the results row (result MATCH, best 0, wall -, evidence).

The results row for item 1 currently says WALL 13. I need to fix it: change to MATCH, best 0, wall -, evidence.

The row format: dir file func kinds result best tries wall evidence. For MATCH: result MATCH, best 0, tries (now ~65), wall "-".

Let me count tries for item 1: 30 (first round) + i1-i6 (6) + j1-j5 (5) + k_* (6) + l1-l3 (3) + m1-m4 (4) + n5-n7 (3) + o1-o4 (4) + p01-p20 (20) + r1-r3 (3) + s1-s3 (3) = 30+6+5+6+3+4+3+4+20+3+3 = 87. Let me say 87.

Now update the results row. The row is line 2 of results.tsv. I need to replace it. Use a script (python) to rewrite the line. One action.

Also update notes.md and the moves.md line (currently says WALL for item 1 — I should correct it? moves.md is append-only, one line per item. I already appended a WALL line for item 1. Hmm. The brief says "append one line per item" — I shouldn't append a second line for the same item, but the first line is now wrong. Options: leave it (append-only) and note the correction in the log/notes, or append a corrected line. The instruction says append one line per item; a wrong line is worse. Since moves.md is append-only, I'll append a corrected line marked as a correction? That violates "one line per item". Hmm.

Better: since the file is append-only and my earlier line is wrong, I should correct it. The house rule says raw outputs/logs are never edited; moves.md is a shared append-only file. I'll append a second line for the same item with the MATCH result and a "(RM3, corrects the WALL line above)" note. That's the least-bad option. Actually, the expert reads moves.md for mechanisms; a stale WALL line could mislead. I'll append the correction.

Hmm, but "append exactly one row to RM3/results.tsv" — for results.tsv I'll fix the row in place (it's my shard's file, not append-only-shared). The brief says "Per item append exactly one row" — I'll ensure exactly one row by replacing.

For moves.md: "after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (RM3)`". I already appended one line for item 1 (WALL). Now that it's a MATCH, I should correct it. I'll append a corrected line and mention it in the log. Actually, let me check if moves.md allows edits — it's append-only per the header ("append-only, one line per item"). I'll append the corrected line; two lines for one item is a minor deviation I'll note.

Wait, maybe I can edit my own line? The header says append-only. The judge might refuse an Edit on moves.md? Writing to it via Edit is allowed (it's under .run). But the rule says append-only. I'll append the correction.

Let me now:
1. Verify s1 score 0 and lever-free.
2. cp s1.c win.c.
3. Fix results.tsv row 2.
4. Append corrected moves.md line.
5. Update notes.md.

Then do the same for items 2-4? The s1 trick was specific to item 1's tail. But the twins might benefit from a similar do-while EBB split! The twins' residual is the dst bank (135) — a do-while split might fix local-alloc like it did for item 1!

That's a promising idea: wrap the dst block in a do{}while(0) to split the EBB and change local-alloc's allocation. Let me try it on the twins after finishing item 1.

Excellent. Let me proceed.
