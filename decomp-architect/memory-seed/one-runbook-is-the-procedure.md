---
name: one-runbook-is-the-procedure
description: ONE document is the operating procedure for the campaign loop — read it before every run; each guard in it is paired with the measurement that produced it; keep it current in the same change as any step or tool it names; a superseded runbook gets a banner at once
metadata:
  type: project
---

The campaign loop (draw work → build cards → draft → gate → recover → harvest → verify the fleet → checkpoint) has one
procedure document, and it is read before every run.

**Why:** the most expensive mistakes of one session on the source project were procedural, not technical — a hand-typed target
that invented a function (tens of thousands of tokens), a hand-rolled serial gate while the parallel tool existed (an hour for
minutes of work), a function re-derived at cost because a card said "no banked twin" when the twin scan had not been run on the
world. Each became a guard in the runbook, paired with the measurement that earned it; that pairing is what a generic guide
cannot have. An earlier runbook titled "as it actually runs" kept describing a retired pipeline for weeks and was followed.

**How to apply:** treat the runbook as the deliverable — the shape (guard + measurement) matters as much as the steps. Update it
in the same change as any step or tool it names, the way the ops reference is kept current. When a pipeline is retired, put a
banner at the top of its runbook the same day and point at the successor; a stale procedure document is worse than none.
Every target payload comes from a file the draw tool wrote, never from a hand-typed name.
