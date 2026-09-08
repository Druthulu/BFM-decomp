---
name: the-byte-gate-is-the-only-claim
description: "Matched" means the compiled output is byte-identical AND the whole binary's hash still equals the original; nothing "functionally equivalent" counts; "banked" is written only from a tool's printed success line
metadata:
  type: project
---

A function is matched when its compiled output is instruction-identical to the original, register allocation included, and the
whole binary still hashes to its recorded value with that function compiled from source. A diff that "looks right", a closeness
score, a compiler that "ran without errors", an agent's verdict — none of these is a result. The gate is the arbiter; every other
signal is a filter that feeds it, and each filter is blind to something (a masked standalone compile cannot see symbol identity;
a real-translation-unit probe cannot see link-time identity; only the whole-binary hash sees everything).

**Why:** the documented failure mode of AI-driven reverse engineering is fake success — stubs, shortcuts, redefined terms. An
incorruptible oracle is what makes an autonomous agent's work trustworthy at all. On the source project the whole-binary hash ran
inside every build of every binary, a clean rebuild followed every batch, and twice a ledger claimed a "bank" that had not
happened — a helper had no-op'd on an empty list; a wrong draft directory — because the message was written from intent.

**How to apply:** verify from a clean rebuild, never an incremental one, after any batch that touches shared code. Write "banked"
or "matched" only by quoting the gate's own printed success line. Never ship a default build that links unmatched C (a guard keeps
logically-correct-but-unmatched code out of it). When a claim rests on a tool's output, name the tool that produced it.
