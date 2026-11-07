---
ts: 2026-11-06T05:30:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZXGkYcm5O0BFUBQN5WNz
---
Wait, in dflt_last, case 4 falls through to `hit:` inside the switch, then after the switch `return 0`. With my edit, case 3 goes to tail, case 4's hit block ends with the store then `tail:` label inside the switch — the `tail:` label is inside the switch block, after the hit code. That's fine syntactically. But case 3's `goto tail` jumps into the switch block — legal C.

Hmm, but case 4/hit after `*(s16*)...=10;` falls into `tail:` — good.

Also note: `hit:` in case 4 and `tail:` label inside a switch — fine.

Let me run.
