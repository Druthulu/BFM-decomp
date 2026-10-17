---
ts: 2026-10-16T16:55:26.155Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6262df0e8a0d472a
model: claude-opus-5-5[1m]
effort: medium
turnId: 7850ba3c-c3b4-45a3-a86f-0ae36df32364
---
I'm looking at two struct map clusters both belonging to func_80162834, which appear to be overlay-specific copies of the same routine that got split differently. I'm working out the fold action in type_folds.tsv to merge these duplicate cluster definitions back into a single named target.

For a safe merge, I need to pick a canonical name per component, rewrite all source tokens referencing the duplicate names to point to the canonical one, and respell member names in the affected bodies if they diverge — then delete the stale defs and update type_folds.tsv so future reads stay consistent. I'm weighing this against a typedef-alias approach, which minimizes source edits to just the header but still requires respelling member accesses if the names differ between the two structs.

An alias wouldn't count as a definition in the census dup class since dup_gating only sees layout defs, so it wouldn't get pulled into struct_twins either — that's fine. But ordering matters: the canonical struct must be defined before any alias, and definitions might be spread across multiple headers or TUs, not all consolidated in one place. I'm now checking whether lift_types' fold mechanism could take a custom TSV subset rather than folding an entire class at once.

I've traced the duplicates to T3 band defs, where two identical struct-map clusters got separate define targets—affecting 312 components and 557 names to fold. Now checking if `lift_types.py --fold` supports component-level TSV input instead of requiring whole classes.
