---
name: the-matching-flywheel
description: Consult the knowledge base (the idiom cookbook, the pinned toolchain, the permuter harness, the decompiler's context) BEFORE every match, and feed the generalizable lesson back into BOTH the cookbook AND the tooling after it
metadata:
  type: project
---

Matching runs on a deliberately compounding knowledge base: a cookbook of compiler idioms (each with the residual it explains,
the mechanism, the lever and the byte proof), the pinned compiler/assembler triple, a permuter harness for near-misses, and the
decompiler's context file of known globals and types. Each part is consulted before a match and updated after it.

**Why:** compiler nuances repeat across nearly every function; an autonomous loop scales only if each match makes the next one
cheaper. The goal is to drive the average function toward one-shot and shrink the hard tail — not literal zero-intervention.

**How to apply:** before matching, grep the cookbook by symptom (never read it whole once it is large — keep a symptom index)
and scaffold with the decompiler. After a hard-won match, extract the GENERALIZABLE lesson — a recurring class, not a one-off —
and feed it into both the cookbook and the tooling (a permuter recipe or weight, a context entry, a helper). Two laws learned at
cost: harvest lessons only from byte-proven results, and strip a credited lever from the accepted body and recompile before it
enters the base — about one in three credited levers was byte-inert. A name on a work card must resolve in the knowledge base
by the words on the card; a label a worker cannot look up costs a search and buys nothing.
