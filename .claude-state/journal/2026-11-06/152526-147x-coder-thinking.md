---
ts: 2026-11-06T22:25:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mVcKIloWkWsm4IiXQFdA
---
Everything is consistent:
- Item 1: MATCH, score 0, lever-free.
- Items 2-4: WALL, best 24/24/31 (invalid 16-bit bodies; valid best 135/135/137), lever-free win.c.

One concern: the WALL win.c files use 16-bit dst/tmp which are semantically wrong. The evidence field says "(invalid)". The notes explain. Good.

Final report: starts with "done" as the first word, then ≤10 lines: per item dir result best wall.

Let me write it:

done
- func_80183534 (ov_SC06_029): MATCH score 0, 197 ins — do{}while(0) EBB splits (otp block + first 3 sxy stores) give oidx $3; win.c=s1.c.
- func_801919A0 (ov_SC06_032): WALL best 24 (16-bit dst invalid; valid 135), wall lreg-qty-priority — dst long-lived pointer loses $3 to short temps.
- func_80191C50 (ov_SC06_018): WALL best 24 (invalid; valid 135), same mechanism (twin).
- func_8019059C (ov_SC06_018): WALL best 31 (invalid; valid 137), wall lreg-qty-priority — dst $3 + tmp $2.
- results.tsv 4 rows; moves.md 4 lines + 1 correction; log phase-ends/current/logs/T11.cRM3.md.

That's ≤10 lines. But the RETURN says "nothing else" — per item dir result best wall. I'll keep it minimal.

Note: no git commit (brief says no git, no commit). Good.

Wait — the task says "no git, no commit". Yes, CONSTRAINTS: "no make, no git, no commit". So no commit. Good.

Let me finalize.
