---
ts: 2026-11-06T21:14:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4bk8kr4iKJGjnDJSz2ha
---
Hmm, only 1 set of v0 in cse/combine/flow dumps. That means the `rv = (s32)a0` was already eliminated before cse (by expand/flow at the tree/rtl level). The dump files may be cumulative or each pass's output. The .flow shows 1 (the lw). So the dead move never reached cse — it was deleted early (by expand or the first flow/cleanup).

Wait, but with the keepalive asm, the move exists. In w2 (no asm, no pin), the value rv = a0 is dead at the tree level? GCC's expand generates the assignment; then the first `flow` pass (or `jump`/`cleanup`) deletes it. Actually the .rtl dump (after expand) should show it. Let me check the .rtl dump.

The .rtl dump is printed after expand (the first -dr). Let me grep.
