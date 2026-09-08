---
name: translate-the-source-idiom-through-the-pass
description: An inherited cookbook idiom is a symptom + a NAMED compiler pass + a lever + a byte proof; use it directly on the same compiler family (and re-prove it on your bytes), and on another compiler read the same pass in that compiler's source and find your own lever — never copy the lever alone
metadata:
  type: project
---

The inherited cookbook and codegen map are per-compiler facts about one compiler family. What transfers to another compiler is the
structure of each entry: the tell in the diff, the pass that produces it, the source files that implement that pass, and the
reproducer that isolates it. The idiom therefore tells the agent exactly what to read in the new compiler to build the corresponding
entry; the lever itself does not transfer.

**Why:** the source project's highest-value idioms came from reading four files of the compiler's source, and its two formal proofs of
unmatchability each failed on a producer missing from a census — a lever copied without its pass is a guess wearing a citation.

**How to apply:** same compiler family — look the symptom up, apply the lever, then re-prove on your own bytes before the idiom enters
your cookbook. Different compiler — look the symptom up, read the named pass in your compiler's source, build a five-line reproducer
that shows the symptom, find your lever, and write your own entry in the same shape (symptom, pass, lever, byte proof). Either way,
strip a credited lever from the accepted body and recompile before it enters the base; about one in three credited levers is inert.
