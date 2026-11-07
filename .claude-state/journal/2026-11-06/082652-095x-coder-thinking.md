---
ts: 2026-11-06T15:26:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ppKIY5UxWvzy0Yjy9RsT
---
08:26:47. Let me try one final family that I haven't: making the t!=3 test a *switch* on t inside the t==5 block? No.

Actually — let me try the "compare with a variable that's dead-reset" idea (five variable):
w1:
```
    s32 five = 5;
    ...
        if (t == five) {
            five = 0;    // dead-reset after the branch
            if (t != 3) ...
```
Hmm, five is declared at the top and initialized. The `five = 0` inside the block is dead (five not used after) → flow deletes. cse sees five=0 → invalidates five's const. But t's class...

Let me test it — cheap and it directly applies C0414.

w2: put the dead-reset BEFORE the test but after the branch: same thing.

Let me test w1 and w2 (w2 with `t = t;`-like... no, w2 = five=0 before the test).

Actually w1 IS five=0 before the test (inside the block, before the test). Let me write it.

Also w3: `five = 0;` before the `if (t == five)` — that would make the branch compare t with 0. No.

Let me test w1.
