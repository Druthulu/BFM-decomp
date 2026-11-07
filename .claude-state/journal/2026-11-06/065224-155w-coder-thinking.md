---
ts: 2026-11-06T13:52:24.149Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a9242f8c917e0a5c4
model: claude-opus-5-5
effort: medium
turnId: 88b25866-c9e8-45b1-81c6-d2f63ee67e57
---
I'm checking whether one function is defined in the overlay file, and I'll confirm it's unique when the swap runs. Bank_swap runs on every shard except the one I'm handling by hand, but it has no exclude option, so I'll need to work around that.

I'm planning the swap for G31y: bank_swap goes to every shard except that one, then I'll run G31y with --only for func_8017DEF0, and copy win.c over for func_80177EA4 once I've confirmed it's a whole file.
