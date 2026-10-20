---
ts: 2026-10-20T01:24:41.267Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 88ab4e68-eeae-4ee3-b16f-c731ccb14733
---
I'm puzzling over why the entire .run/keep directory got wiped — wondering if git clean treats an ignored directory as a single untracked unit when you pass a pathspec pointing inside it, which could explain the whole folder disappearing instead of just the one file.

Now I'm checking other paths to confirm the pattern: dirs like P38/t51 that have no tracked files of their own get fully removed even though their parent P38 is tracked, while dirs like P36/engine/score survive because their immediate parent has tracked content.

So I'm tracing exactly what got wiped versus what's recoverable — the keep/ snapshots, P36/regen's tsv/jsonl files, and P38/t51's c2_renames.tsv seem gone, but the live ledgers in P37 and P36 survived since they're tracked directly. Since those ledgers are append-only, the lost snapshots might be reconstructible as prefixes of the current, larger ledger files if I can line up the byte/line counts correctly.

But I'm uncertain whether T4's "restamps" step modifies ledger rows in place rather than just appending — that would break the prefix-recovery assumption. The data isn't recoverable from disk since ext4 deletion is permanent, and there's no backup in the archive repo since T15's ledger_backup was never completed, so my only hope is if the developer copied things off-machine earlier like I'd asked. This is my mistake and I need to assess the full scope of the damage before reporting it honestly.
