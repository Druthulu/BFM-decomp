---
ts: 2026-10-22T21:11:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TAqgRHRXqGf4VtMOVbIR
---
These are the source defs (with levers). I need to find a lever-free body that scores 0 (compiles to the same target).

Let me set up the item dir: copy the current def to orig.c and nopin.c (base), then test the lever-free version.

First, let me see the target and how delever_search works. Let me check how many includers exist for these headers.

Let's look at delever_search.py usage/help.
