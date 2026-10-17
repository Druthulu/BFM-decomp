---
ts: 2026-10-17T04:01:58.171Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: a6cb61f7-5c97-4a0b-8b48-ee8961b1996a
usage: {input: 6, cacheRead: 108096, cacheWrite: 56542, output: 972}
---

PA3 3.28.8 is out, and its main fix is the false "expert stopped" bug you saw on T2 and T5.

What changed:
- **No more false stops while an expert waits.** Experts and coders now hand back only once, when their work is done, so they stay on Claude Code's agent list while they wait on a coder. If an expert drops off the list while its coder is still working, the mod now treats it as waiting, not stopped. And if a stop was only guessed from a missing expert, that expert's own report clears it and the next task starts. That is exactly the loop from this morning.
- **Pictures reach me.** A picture you drag into the terminal or paste as a file path now gets passed to me, and I open it. A screenshot pasted straight from the clipboard still has no file, so I still see text only for those.
- **Fuller agent cards.** A closed expert or coder card now shows the report's text, not just its "Summary: <path>" line.
- **Keep-warm by role.** A "keep-warm" ping is a small message the mod sends a waiting agent so its cached context doesn't expire. Coders now get one about every 4.5 minutes while they wait on their own background job, for up to 2.5 hours; before, coders got none. Experts are kept warm for up to 12 hours, or 7 hours once their context passes 250k. I'm kept warm for between 2 and 12 hours, depending on how large my context is. Past 175k, a fresh Claude takes your next message.

**Project Architect 3.28.8 is installed and loaded. Ready to continue work.**

This update also changed a setting that only takes effect after a restart, so please restart Claude Code when convenient: /exit, then `claude --continue`.

Nothing has changed with the work. T5 is still paused, its tree is clean and its last commit is e033c139c5. When you're back and want to go on, tell me and I'll resume T5. With this fix, its expert should be able to wait on its coder without the false stops.
