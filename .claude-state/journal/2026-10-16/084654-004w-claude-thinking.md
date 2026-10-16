---
ts: 2026-10-16T14:46:54.933Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aede67d56d4362411
model: claude-opus-5-5[1m]
effort: medium
turnId: 25ddd874-0949-491c-a87c-0e1a6c0ee67b
---
I'm noting that drift types are distinct from band types since they're new cluster hashes formed from leftover regrouping, not actual band types to fix. The expert's proposed rule treating singleton drift as BELOW-BAND evidence risks inflating the fleet count past the frozen 6,976 tail limit.

So I'm deciding drift shouldn't go into BELOW-BAND beyond the cap—instead, drift types need lineage back to their parent band type, a legitimate residual layout class, or an explicit definition. This keeps things within the milestone's constraints without needing developer sign-off, so I'll record this as an amendment to T4's done-when criteria.

For T5, I need to add a follow-up drift-decision task with proper dependencies and a verify command, but the plan_edit tool rejects shell metacharacters like `&&`, `;`, and `|`, so I'll simplify the verify string to a single check-casts command with a residue flag and note the TNC-zero requirement in the done-when text instead. T5 itself will also hit this same drift issue, so I need to make sure its verify step accounts for that too.

Actually I could absorb drift into T5 itself via append-change, which keeps T5's verify valid and avoids a new task—though T5 is already large with multiple sweeps. Still, a separate task is cleaner for size, so I'll go with new task T17 after T5, with the append-change noting that T5's verify grep clause moves there, and now I need to draft the actual commands.

Now I'm working out the done-when criteria for this new task: deciding every remaining TNC map type via a new restruct.py decide-band mode, assigning drift types to a band/fold first, then a residual layout class, while ensuring drift types never get TYPE-BELOW-BAND and the frozen tail stays bounded.

I need to add an iteration guard since re-sweeps can generate new drift — I'll cap it at two decide-sweep rounds, with any remaining drift after round two triggering a question back to the developer rather than continuing indefinitely. I'm also noting that defining singletons creates one-off structs, which the developer previously disliked for readability reasons, so I need to account for that tension in the final rule.

So my resolution: try lineage matching first since drift types likely trace back to band type fragments, and only define true singletons left over — with a sanity cap, say 500, before flagging back to the developer. Then I can draft the release note to the T4 expert: accept the amendment, close T4 as done, and leave drift types unrelabeled. Now let me write out the actual commands.
