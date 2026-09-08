---
name: consult-the-tool-dictionary-first
description: Before designing a new tool or debugging one that misbehaves, look the NEED up in the tool dictionary — the proven implementation is the jumping-off point, its incident row the failure mode to avoid, its Adapt column what differs here
metadata:
  type: feedback
---

The source project finished with several hundred tools, each earned by a need and most by a recorded incident; the kit carries them
verbatim as a dictionary keyed by the need they answer, with what proved each one and what it hard-codes. A new tool written without
the lookup re-learns an incident that was already paid for; a tool debugged without it re-derives a refusal that already exists.

**Why:** the owner's judgement at the kit's design — the working tools are the most valuable part of the source project, proven to
the last binary — and the measured cost of not looking: sessions spent rebuilding verdict ladders, gates and censuses that a
neighbouring tool already had.

**How to apply:** when a need appears ("I need to know whether this draft's body matches before the gate", "which symbol first
diverges in a red build"), grep the tool index by the need phrase, read the matching tool's docstring and its incident row, and start
from its design — the verdict layers it consumes, the inputs it refuses, the denominators it prints. When a tool misbehaves, find
the dictionary entry for the same need and compare before patching. Record what you adapted in your own tool's docstring.
