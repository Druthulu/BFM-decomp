---
name: a-slow-gate-is-a-bug
description: Banking, not drafting, is the bottleneck of a matching campaign; nothing in the gate is serial; pass -j to every build; measure the gate before fearing it; gate in isolated worktrees under a per-binary lock
metadata:
  type: feedback
---

A gate that takes tens of minutes per binary is a defect to fix, not a cost to absorb. Drafting is cheap and parallel; the
byte gate — a build and a hash per draft — is where a campaign's wall-clock goes.

**Why:** on the source project one binary's gate ran for an hour while thirty-seven finished drafts queued behind it; sixteen
binaries were once gated serially to protect one carving job, an hour for what the parallel form did in minutes; and a single
binary's build without `-j` was measured six times slower than with it, byte-identical either way. The gate had been believed
to cost forty to sixty minutes; clean, it cost fifteen seconds — the stalls were bisects.

**How to apply:** parallel is the default — each binary gates in its own worktree (isolation: a carving worker writes only inside
its tree) under a per-binary lock (mutual exclusion: two lanes never gate the same binary). Every tool that shells a build passes
the parallel flag; a bad parallel build fails the hash, it cannot bank wrong bytes. Batch the expensive population behind a strong
pre-filter and bisect on failure. Merge carve state — per-binary files adopted whole, a shared registry spliced by block — so two
workers never clobber each other. If you find yourself writing a serial loop over binaries, stop: that is the hour-long mistake.
