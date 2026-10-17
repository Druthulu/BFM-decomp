---
ts: 2026-10-16T16:44:41.311Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae95ad707bdd40ce3
model: claude-opus-5-5[1m]
effort: medium
turnId: f7b8a33c-ceaf-47c8-aacd-9e21fd244f0a
---
I'm noticing twins_stale is now 0 while dup_classes jumped to 241, and dead_kept dropped to 2, suggesting the band defs went live or got pruned. The dup_classes count represents tier-1 duplicate classes lacking justification as twins, while twins themselves dropped from 381 to 310 as the documented listing justified tier-2 classes with distinct-entity evidence.

The 71-class gap between the old and new dup counts likely comes from tier-2 twins of dead T3 defs citing TNC bodies as use sites -- after restamping, those bodies no longer count as TNC, so the evidence disappears and the class gates. This points to needing C0512-style folding (collapsing duplicate struct defs onto one canonical type), which means real source edits across many bodies plus R22 changes -- a genuine edit-build-test loop that belongs with a coder rather than something I resolve here, and likely part of T5's done-when criteria regardless of whether T4 already claimed a passing check-structs run. I want to brief a coder with pointers on what dup_gating means and the C0512 cookbook entry, so I'm planning to grep the cookbook for the C0512 headline and check the check-structs dup gating output (possibly a dup_gating.tsv under the census run directory) to confirm whether these 241 classes trace back to the T3 Unkstruct band defs.
