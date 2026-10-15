---
ts: 2026-10-15T16:14:37.742Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a86ec957c38e69a06
model: claude-opus-5-5[1m]
effort: medium
turnId: d2ceb926-9b47-40f5-bac5-5608e57c3046
---
Since the body has no typed bases with deref sites left, rung S has nothing left to draw and can't redraw the row. I'm considering a fix where restruct carries forward the prior row's KEPT entries for macro sites still present, though the carried-forward entry's base becomes a nested reference that needs handling.

The real complication is rekeying: the census key uses a different base form than the carried-forward entry, so a plain carry-forward won't match unless I rekey it to match the current census site's base by cls+off. This likely means the fix belongs in the --residue merge path, where a body's latest row gets merged with census macro sites and restamped with the current base key, since residue already has normalized base/offset info available there.

I need to confirm which code path actually writes new rung-S rows — draw/apply wouldn't revisit these bodies, and residue only fires when there are uncovered sites, which might not be the case here. I should outline restruct.py's structure to pin down where this logic lives.
