---
ts: 2026-11-06T14:43:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nsHRpgqUlBjLDezIye6j
---
The function has one launder:
```
        if (t == 5) {
            __asm__ ("" : "=r"(t) : "0"(t));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)
            if (t != 3) {
                goto sel_094;
            }
```
This is a self-launder: `t` in, `t` out, same register. It forces `t` into a register at that point (the "=r"/"0" constraint). Without it, the code differs.

The kinds row is `launder`. I need to remove it and score 0.

Let me first establish the baseline (orig scores 0) and the lever-free score (asm removed). Then work on it.

Let me score.
