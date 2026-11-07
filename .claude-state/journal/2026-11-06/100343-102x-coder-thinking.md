---
ts: 2026-11-06T17:03:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BlIPdKsNV9g2cnh6APAN
---
MATCH for item 4! win.c scores 0, and the only remaining lever is the a0 pin ($16) — an "other-kind" lever (pin) that was already in the def, allowed to stay. The row kinds (keepalive, launder) are all gone:
- s-launder → replaced by `m = D_800AE620;` (struct assignment) wrapped in do-while(0).
- keepalive → gone with the hand-expanded copy.
- q-launder → dead-reset `q = 0;`.

Wait, let me double check the q block in ah04. z01 had the q block with `q = 0;`. ah04 replaced `m = D_800AE620;` with the do-while. So the q block is still:
```
    {
        void *q = &m;
        RotMatrixY(ang & 0xFFF, q);
        q = 0;
    }
```
Yes. Good.

Also check: the do-while has the required `// !FAKE: do-while` marker. Yes.

Now let me write item 4's notes and append the results row.

Tries count for item 4: orig + w1-w4 (4) + x1-x3 (3) + y01-y04 (4) + z01 (1) + aa01-03 (3) + ab01-03 (3) + ac01-03 (3) + ad01-04 (4) + ae01-03 (3) + af01 (1) + ah01-04 (4) = 1+4+3+4+1+3+3+3+4+3+1+4 = 34. Good (≥30).

Time: item 4 started ~09:56, now ~10:04 = 8 min. Hmm, but it's a MATCH, not a WALL, so the 20-min rule doesn't apply (that's only for WALL). Good.

Let me write notes and the row.

Result row: MATCH, best 0, tries 34, wall -, evidence "cse EBB: do-while(0) around the `m = D_800AE620` struct assign splits cse1's block so &m is remat, not cached; q launder -> dead reset; 73/73".

Then all four items are done. Let me also append to moves.md per item (the brief says after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (W47)`). I haven't done that yet! Let me do it for all four now (it says after each item; I'm doing it at the end, which is acceptable but not ideal — I should have done it per item). Let me append all four lines now.

Then write the log file phase-ends/current/logs/T11.cW47.md.

Wait — the brief says "write only under .run/P40/T11/W47/ plus appends to .run/P40/T11/moves.md". But the LOG is phase-ends/current/logs/T11.cW47.md — that's required by the LOG section. OK, that's allowed (the constraint lists the scratch writes; the log is a deliverable).

Also, no commit (the brief says "no make, no git, no commit"). Interesting — this shard task explicitly says no commit. So I just write the log and return.

Let me write item 4 notes first.
