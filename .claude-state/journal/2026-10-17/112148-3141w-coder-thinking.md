---
ts: 2026-10-17T17:21:48.125Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm puzzled by the stack pointer adjustment appearing early in the instruction sequence, wondering whether GCC 2.7's MIPS prologue is being emitted as RTL rather than text, which would explain the scheduling position I'm seeing.

Maybe the original had a dead stack store that gcc 2.7 doesn't eliminate, which would create a dependency keeping the sp adjustment first. I'm also wondering whether mips_expand_prologue emits a blockage instruction in gcc 2.7 that would pin the sp adjust before scheduling, which could explain the ordering difference without needing any real stack usage.

This matches the combine-copy-merge pattern from item1, with a3 scoring 10 at includer 0. I don't need to check other includers for a WALL case, so I'll go ahead and write it up.
