---
ts: 2026-10-17T17:26:10.876Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm comparing my scheduled instruction order against the target sequence, noticing the extra `move a1,a0` and the misplaced `sll` before `lhu` — the dependency on `a0` is lingering too long. I'm thinking about restructuring how `x0` is computed, perhaps deriving it from `dw - n` instead, to naturally shift the scheduling order.

Now I'm trying to figure out why sched1's backward-list priority is placing `sll a0,v1,5` ahead of the `lhu tt` load, since the longer dependency chain through `tt` should normally win priority. I want to try removing the `tt` variable entirely and reading the field directly inline, then retrying variants on the current base with other register configurations to see if that reorders things correctly.
