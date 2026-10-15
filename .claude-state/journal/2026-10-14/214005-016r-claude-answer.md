---
ts: 2026-10-15T03:40:05.361Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 4deb7ba0-ac16-46be-9938-d162cff48571
usage: {input: 8, cacheRead: 136845, cacheWrite: 4537, output: 2221}
---

The repo is a PC port built on top of our project, not a rival decomp. Its credits name "Druthulu (Drew T), author of Druthulu/BFM-decomp", and I checked that this is our own `origin` remote.

**What it is.** It's an experimental PC port of the US release (SLUS-00726), about two weeks old: first commit 2026-09-30, 7 commits, a Linux release r38 and a Windows test build r41.
- It runs mostly as a hybrid. A CPU interpreter runs the game's original code from your own disc, and compiled native code replaces pieces as they get decompiled.
- It uses SDL2, OpenAL and OpenGL, and draws through PsyCross, an open-source library that reimplements the PlayStation's graphics on a PC.
- It has about 252 hand-matched C functions of its own, all in `main`. Attract mode stops at one unsupported function, and its next goal is a playable Chapter 1 with saving.
- It says it contains none of our code. It does take our splat layout (how the game's binaries are cut into files) and our symbol names for its config, and it checks its own C against ours so it can leave out anything derived from us.

**What we'd gain.** Not much now, nothing that helps 3.40 to 3.45. We have every function matched and are already past the stage it is at. The one useful thing is its architecture doc. It shows a clean "platform seam": one interface the game calls for graphics, audio, input and saves, with a backend behind each. That's worth reading when the next generation starts the shiftable build (a build where code can move in memory and still work), since a port is a natural next step after that.

**What they'd gain.** A lot. They lack typed structs and real names, and they cover only 252 functions where we have all of them. As our 3.40 to 3.43 work lands, they can take whole subsystems from our C instead of matching them again, and our struct types would make their native code readable.

**One thing to check.** Our `tools/` and `docs/` are AGPL-3.0 and our `src/` has no license. Their port is MIT, and part of their config was "derived from the upstream BFM-decomp splat layout." That is probably fine: splat layouts and symbol lists are mostly facts, and they credit us properly. But whether you're happy with MIT reuse of what you've published is your call. It's also a reason to give `src/` an explicit license someday.

**My recommendation:** send Blizz127 a friendly note. Thank them for the credit, point them to our struct and naming phases as the thing that would help them most, and ask them to keep the attribution. Don't change our plan for this. I can save the port's architecture doc as a pointer for the next generation's port or shiftable-build planning, and draft the note if you want one.

Tell me how you'd like to handle it, or if you want to dig into anything first. When you're ready, I'll brief the planner for 3.40 in full, as you chose.
