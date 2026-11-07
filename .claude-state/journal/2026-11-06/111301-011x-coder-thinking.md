---
ts: 2026-11-06T18:13:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yTb2pcMCeMvIErErQrIr
---
All orig.c match the current src. Good, FRESH check done for all three (identical text).

Now let's set up. Approach note first (I'll write it in my next message as working lines). Then experiments.

Let me plan the workflow: For each item, create candidate bodies in the item dir as w1.c etc, run sc.sh over them.

Item 3 first — quick test: plain s32 v1.

Let me write candidates. But before coding, per the rules I must write the approach note in my working lines. Let me do that now:

"Three items. Item 3 (func_80184B70): the $3 pin holds the unkCC pointer; lever-free I need the load to land in $3 by real C means (temp splitting/order). Item 2 (header, $7 pin): a7 and v1 are equal pointers kept in two regs; cse merges equal copies, so I try mode/type spellings that escape cse. Item 1 (keepalive): a1's address constant must stay early; try do-while splits and statement order. Start with the cheap direct removals to see the residual."

Let me create item3 candidate w1.c: plain s32 v1.

Wait — the body file format: delever_search --try <TU> <fn> <file> --body. What does the body file contain? "write a lever-free body of func in W48x/<dir>/win.c (bare definition)". So bare definition (whole function definition). orig.c is that. Good.

Let me write w1 for item 3.
