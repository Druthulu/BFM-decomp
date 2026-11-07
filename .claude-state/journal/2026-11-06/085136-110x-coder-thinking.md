---
ts: 2026-11-06T15:51:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nP0LzrVgKGKEjnXRSj3U
---
Item 5 MATCH. All 5 items done:
1. func_8017E178 — MATCH (u16 flags + ret=0 dead-reset)
2. func_8017E880 — MATCH (s0 = s0 & 0x8000)
3. func_8017EC4C — MATCH (keep/reset/restore block)
4. func_80181670 — MATCH (do-while(0) around n = q+8)
5. func_8018F060 — MATCH (address temp + dead-reset)

Now:
1. Append one row per item to O04x/results.tsv.
2. Append lines to .run/P40/T11/moves.md.
3. Write notes.md in each item dir.
4. Write phase-ends/current/logs/T11.cO04x.md.
5. Clean up scratch (dumps dirs, --keep scratch under .run/P36).

Let me check time: started 08:20, now ~08:55. Good, within budget.

First, clean up the dump dirs (disk capped). Delete $D/dumps and the *_tu.c files? The brief says cc1 dumps go under the item dir and are deleted as soon as read. Also `--keep` scratch is removed after use. Let me remove the dumps dirs and the --keep scratch dirs I created (p* dirs under .run/P36/engine/score/...). But careful: those p dirs are shared scratch; other agents may be using them. The tool removes them unless --keep. I should remove the ones I created. But I don't know which pids are mine vs others'. Hmm — the brief says "`--keep` scratch is removed after use". I'll remove only the specific dirs I created. I recorded: p3, p4, p5, p15 (item4?), etc. Risky to delete others' — but the dirs are named p<pid>, and each of my runs created a unique one. The pids I saw: p3, p5, p4, p15... Actually all my runs are mine; other coders' runs would have their own pids. Deleting a dir another coder is using would break them. Safer: leave them? The brief says to remove --keep scratch. The tool's own cleanup removes non-keep dirs. Since I used --keep, they persist. I'll delete the ones I can identify as mine by listing dirs and their mtimes? Hmm.

Actually, each --try call with --keep leaves a dir; the tool removes dirs without --keep. My last run in each function's dir is the one I need to remove. I can list the score dirs and remove those whose cand.o mtime is within my session and whose TU matches my candidate. That's still ambiguous.

Simpler: I'll remove the item dumps dirs (definitely mine) and the *_tu.c copies (mine). For the .run/P36 scratch, I'll leave it — actually no, disk is capped and the brief says to remove. Let me check the size of those dirs first. If small (a few MB), leaving them is not a disaster, but the brief is explicit. Let me check what's there and remove dirs that contain my candidate bodies (I can check if the TU contains e.g. "s0 = s0 & 0x8000").

Let me first do the results.tsv rows and moves.md appends, then notes, then cleanup, then the log.

results.tsv format: `dir file func kinds result best tries wall evidence` (tabs). MATCH rows: wall `-`.

For each item:
1. func_8017E178__ov_SC03_113_jr_8017C294 | src/ov_SC03_113/ov_SC03_113_jr_8017C294.c | func_8017E178 | launder | MATCH | 0 | N | - | evidence
   tries: how many candidates? a1,a2,a3,a4,a5,a6,a7,b1,b2,b3,b4,d1,d2,d3,d4,d5,d6 = 17. Let me count: a1-a7 (7), b1-b4 (4), d1-d6 (6) = 17 scored tries.
2. func_8017E880: a1,b1,b2,b3,b4,b6,b7 = 7 tries.
3. func_8017EC4C: a1,b1,b2,b3,c1,c2,d1,d2,e1,e2 = 10 tries.
4. func_80181670: a1,f1,f2,f3,f5,f6,f7,g1,g2,g3,g4 = 11 tries.
5. func_8018F060: a1,b1,b2,b3,c1,d1,e1,e2 = 8 tries.

Evidence ≤ 140 chars, gcc pass + mechanism.

Let me write the results rows and moves lines.

moves.md line format: `kind | func | MATCH: move / WALL tag — mechanism (O04x)`.

Rows:
launder | func_8017E178 | MATCH: u16 flags (masks 0x8000/0x6000 are low-16, so the truncation is value-preserving) keeps raw local $v0 / flags $s1; C0414 dead-reset `ret = 0;` after `fire = ret` keeps the fire copy (O04x)
launder | func_8017E880 | MATCH: s0 = s0 & 0x8000 (value-preserving 2nd set) after the inner if; cse/flow can no longer fold the surviving dead re-test (O04x)
launder | func_8017EC4C | MATCH: C0414 dead-reset `{ s32 keep = n; n = 0; n = keep; }` after `rem = d - n*128` empties n's cse class so the second `d - n*128` re-derives sll/subu (O04x)
launder | func_80181670 | MATCH: do{}while(0) around `n = q + 8` splits the sched1 block, so the D_80126950 load is not hoisted into the mult delay slots and takes $2 (O04x)
launder | func_8018F060 | MATCH: address temp a = mb + 0x18, `a = 0;` dead-reset after the first call empties cse's const-addr class so the second mb+0x18 re-derives addiu a0,s0,24 (O04x)

Note: the moves.md file is over 20,000 chars, and appends are allowed. I need to append. Using a shell `printf >>` — is that allowed? The brief says appends to moves.md are allowed. Use `cat >>` with a heredoc? The tool rules say avoid echo/cat for reading; appending is fine but the judge might refuse? Let me use python to append (a script file, not inline -c). Actually "Scripts, not inline python -c". I'll write a small script under my shard.

Let me now create notes.md files and results rows. I'll write a script that appends.

First, the results.tsv rows. Format is tab-separated.

Let me create the script.
