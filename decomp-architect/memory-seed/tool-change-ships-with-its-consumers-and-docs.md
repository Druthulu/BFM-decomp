---
name: tool-change-ships-with-its-consumers-and-docs
description: The commit that creates or changes a tool also wires the sibling tools that should use it AND updates the docs (the ops row, the cookbook or runbook entry); integrating an agent's tool change IS a tool change; no end-of-session documentation audits
metadata:
  type: feedback
  upstream: PA
---

Whenever a tool is created or updated, the same change (1) updates the related tools so they know how and when to use it —
wire it in, call it, refuse without it; a tool nobody calls is a tool nobody uses — and (2) updates the docs that consume that
knowledge: the ops reference row, the cookbook or runbook entry. If those are not in the diff, the change is not finished.

**Why:** asked a plain yes/no question — "are the tools and docs up to date with this session's changes?" — the agent once
answered by launching a nine-agent audit that burned about a million tokens before the developer stopped it; the answer was yes,
and the agent already knew it, because the wiring and docs had gone in with each change. Later the same day the honest answer
was NO, and the gap had one shape: every tool change that came from a SUBAGENT had shipped with a rich commit message and no
docs. A report is not an ops row and not a cookbook section.

**How to apply:** budget documentation per MERGE, not per session — when an agent's report contains a law (a measurement, a
refuted premise, a new lever), it goes into the cookbook before the merge is called done. When asked whether things are up to
date, answer from what you did, briefly, with concrete examples; cheap deterministic checks (an index check, a grep for a
hard-coded path, the health target) are fine, an agent fan-out is not. Scale the response to the question: a yes/no question gets
a yes or a no. Do not run end-of-session audits — an audit at the end is a symptom of not having done it during.
