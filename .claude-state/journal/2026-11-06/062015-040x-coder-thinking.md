---
ts: 2026-11-06T13:20:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ck1vOCnqJEdvFbo52QMl
---
v08_ge_inv scored 0! 196 ins. Excellent — inverting the guard to `if (p->unk1C >= 0x10) goto HITSTUN; goto TAIL;` keeps both copies AND produces the same machine code (the branch is canonicalized back to beqz HITSTUN + j TAIL, but the RTL differs enough at cross-jump time — the conditional jump's target differs: in one copy the conditional jumps to HITSTUN directly and the other has the original structure... anyway).

Wait, that's interesting: the source change is in case 3, and the final code is identical. Score 0! MATCH.

But hold on: is v08's machine code really identical, or did the branch direction change? Score 0 = byte-identical (masked). 196 ins. 

So item1 is cracked: remove the barrier, invert the case-3 guard.

Now let me confirm this is the only barrier in the function (yes, one). And the pins: this function has none (I didn't see register vars in item1's def). Right, item1's def had no pins.

Wait, but item1's `kinds` is barrier only, so no pins to keep. Good.

Let me set win.c = w_v08_ge_inv.c and verify score 0 again, then write results row.

Before that: the FRESH check — orig.c was just generated from current src, no stale issue.

Also need to check the moves.md append and notes.md.

Let me first double-check the win.c content (diff vs orig).

Actually, one concern: the `// !FAKE` marker isn't needed since no do-while in v08. Good.

Let me copy w_v08_ge_inv.c to win.c and re-score.
