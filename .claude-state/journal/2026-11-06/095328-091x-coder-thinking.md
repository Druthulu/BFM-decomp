---
ts: 2026-11-06T16:53:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KWPWQG6exXR1jvEs0Nps
---
y2 scores 0! The move: name both the symbol address `m` and the `m + 0x30` derived pointer `n` as locals, and add dead resets `m = 0; n = 0;` after each call. That's C0414's dead-reset cse-breaker — sanctioned by the brief's MOVES+.

Let me verify: no asm, no register, no other lever. And check the win.c has no `__asm__`. Also confirm dt.sh says MATCH.

Wait — is `s32 n = m + 0x30;` a real C move? Yes, naming a derived pointer (catalog: "A named derived pointer"). And the dead reset is C0414.

Let me run dt.sh for the MATCH message.
