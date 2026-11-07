---
ts: 2026-11-06T12:02:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MlLM4sf80IpRoeSfeOjn
---
No luck (g4 = 44, slightly better than 53 but not 0).

I've done ~20 tries on item 3. Let me settle for PARTIAL:barrier with d1 (score 0). That's a solid result.

Wait — but PARTIAL requires win.c to score 0 while keeping only the barrier kind. d1 = 0, keeps the 4 barriers, launders replaced by dead resets. 

But hold on: is d1's dead-reset a legitimate real-C crack? Yes: `_pm2 = 0;` after the use — a real C dead store that flow deletes. Let me verify d1 has no asm other than the 4 barriers.

Let me check: d1 was built from orig with launders removed and dead resets added. So it has 4 barrier asms. Good.

Let me verify d1 = 0 once more and set win.c.

Actually — wait. Let me reconsider whether I can crack the barriers with a *dead reset* trick too! The slider is a zero-byte insn that lengthens my's live range. A dead reset `my = 0;` between the two assignments would... add a store (dead, deleted by flow) but it would *shorten* my's live range? No: `my = 0` after `my = y0` would kill the value. Hmm, that's the opposite.

But what about `mny = 0;` before `mny = y1;`? That's dead and lengthens... no.

Hmm, what about lengthening my's live range with a dead store: `my = y0; <dead use of my>; mny = y1;`. A dead use of my: e.g., `my = my + 0;`? folds.

Hmm, what about `mny = 0;` before the if, i.e., extending mny's range? That would make mny's live range LONGER (from the reset to its use), reducing its priority — the opposite of what we want? We want my and mny tied. Currently my is shorter (higher priority). We want to lengthen my (or shorten mny).

A dead store to my: `my = 0;` — that would define my early and extend its live range from that point to its use! E.g.:
```
my = 0;             /* dead: overwritten in both branches */
if (y0 > y1) { my = y0; mny = y1; } else { mny = y0; my = y1; }
```
This adds a `move my, zero` — would flow delete it? It's a dead store to a register (pseudo) → flow's dead code elimination should delete it. And it would extend my's live range! That's the C0414 "dead-reset" technique again!

That's a great idea. Similarly `mny = 0;`.

Let me try: add `my = 0;` before the if (and/or in the branch), with the barriers removed. The dead store would be deleted but affect the live length.

Wait, but a dead store *shortens* the live range of the *previous* value and starts a new one. Adding `my = 0;` before the if defines my at that point; then the branch redefines it. The allocno's live range includes the region where the value is live... global.c computes live_length per allocno from the liveness info; a dead store creates a use of the allocno? Hmm, the allocno's live range is the union of the live ranges of all its values. If `my = 0` is a definition and my is dead after it (until the branch redefines), the live range extends from the definition to... the next use. Hmm, a dead definition might not extend liveness at all (the value is dead immediately).

Hmm. But the slider (zero-byte insn) doesn't define anything; it just occupies 2 insn slots between the set and the use, lengthening the live range.

A dead store to my would define a new value; the *first* value (from the branch) is unaffected. So no.

What about a dead USE of my? E.g., `my = y0; <something that reads my and is dead>; mny = y1;`. A read that's dead: `if (my) {}` → emits a branch. `mny = my - my + y1;`? folds.

Hmm.

What about a dead store to *another* variable that occupies 2 insns? That would add output.

OK. Another idea: shorten mny's live range by moving its set later. In the then-branch, `mny = y1` is the last statement. Its use is the y2 compare. Can't move later.

Alternatively: what if I *duplicate* the branch to change the liveness structure? No.

Let me accept PARTIAL:barrier for item 3. I have ~23 tries; for a PARTIAL there's no 30-try requirement (that's only for WALL). 

Let me finalize item 3: win.c = d1, score 0, result PARTIAL:barrier.

Wait — actually, let me reconsider one thing: maybe I can crack the barrier with the *dead-reset* trick applied to `my` in a way that extends its live range: what if I write `my = my;` between? Removed.

Hmm, what about using `mny` before its assignment in the then-branch: e.g., the y2 compare reordered so mny is used before my? That's g4 (44).

Let me do 2-3 more quick tries then finalize:
- h1: `my = 0;` before the if (dead store).
- h2: `mny = 0;` before the if.
- h3: both.

Cheap to test.
