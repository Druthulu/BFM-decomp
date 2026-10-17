---
ts: 2026-10-17T17:07:52.151Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm checking whether g1 still matches as a partial-pin case since the pin itself stays while keepalive disappears, and exploring whether the size assignment can be made non-movable—maybe by wrapping it in a nested loop or using a do-while(0) trick so the compiler can't hoist it out like it does with the plain style.

Wrapping the set in `do { size = 8; } while (0)` makes it its own trivial loop, but since loop.c scans innermost loops first, the invariant would just get moved to that loop's preheader—right before the statement, same spot. I'm also considering whether scan_loop treats nested-loop insns the same way for the outer loop, and as a fallback, trying to set `size` twice so it's no longer a single invariant assignment.
