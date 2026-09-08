---
name: checkpoint-means-everything-is-already-in-a-file
description: When the developer says "checkpoint", the checkpoint block is the LAST thing written — every perishable piece of session context is already in a file in the load order; a good commit message feels like documentation and is not
metadata:
  type: feedback
---

By the time the checkpoint block is written, everything the session learned that would otherwise be lost is already in a file
the next session loads: idioms in the cookbook, tools in the ops reference, pivots in the decision log, late discoveries in the
accelerator ledger, procedures in the runbook, and every stale assertion the session invalidated corrected. Not a plan to bank
it; not a commit message describing it.

**Why:** on the source project a full checkpoint was declared done, and a sweep the developer had to ask for found four things
missing — an entire byte-proven procedure that existed only in commit messages, two tools without ops rows, no decision-log entry
for a session that pivoted the phase, no accelerator entry — plus a stale caveat in a tool still asserting something the session
had disproved hours earlier. The trap is specific: a really good commit message, with measurements and controls, produces a
strong false sense that the knowledge is banked. The commit log is not in the load order. If it is only in a commit message, it is
lost.

**How to apply:** before writing the block, run the sweep every time: idioms (from your own debugging, from agents' reports —
notifications truncate the long notes — and from near-miss diagnoses; grep before claiming novelty; name any wall verdict
overturned) → the cookbook; every new or changed tool → its ops row and its consumers; pivots and dead ends → the decision log;
"this would have saved earlier work" → the accelerator ledger; procedures → the runbook, not a docstring; hunt the stale
assertions; regenerate derived artifacts and run the health check; then verify each item is present in HEAD, not just on disk.
Verification-layer lessons — what a check can and cannot prove — count as idioms.
