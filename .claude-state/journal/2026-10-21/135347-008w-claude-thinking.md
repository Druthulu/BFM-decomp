---
ts: 2026-10-21T19:53:47.919Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 347c80a9-cb0f-4d61-9ea9-11388d81f921
---
I should note that the mod overwrote TASK_PROGRESS with a recovery digest, so the actual committed note lives in git history — I need to point the expert to that committed version rather than the working file, which may differ from HEAD. Also the old ext lane process pids are likely dead after restarts, so that's not a concern.

The key insight is that T11's "external lane" used a custom single-shot API drafting loop, while the new PA3 external coders run full pa-coder in headless Claude Code with tools — much more capable, worth testing properly. I'm also weighing model guidance from the skill (DeepSeek recommended, GLM weak on hard tasks, Qwen pricier) and whether the developer's three configs (deepseek, glm, qwen) have guardrails set, which I can't verify. Bubblewrap/socat checks passed, so that's fine. The phrase "we should have an update" is ambiguous — it could mean a PA3 version update already installed via the recent commit, or simply a status update on where T11 stands; I lean toward it referring to an update tied to the PA 3.3 external coders feature.

I'm now sketching how to actually use the external coders: T11 looks like the ideal testbed given its independent cracking functions, byte-identical oracle, and committer gate. One option is swapping Haiku out for DeepSeek on T11's remaining Haiku-first shards to trade subscription tokens for cash costs; another is running a bake-off across DeepSeek, GLM, and Qwen on separate shards to compare performance fairly without overlapping work.

I'm also considering retiring the old single-shot external lane (0/9 cracked, $0.21 sunk) now that real external coders exist, and sorting out CLI settings — coder defaults, lane assignments, escalation to Opus, and whether external coders count against the existing max-coders cap given it was originally meant for subscription spend, not cash. On the mechanism side, I need to figure out how to steer work to T11's expert since T11 is currently stopped — resuming it releases the session but there's no clear way to attach a note to the expert, so I'll sort that out once I get an answer.

Before writing settings, I should ask first using the picker tool, since the SubagentHandback has to come last. I'm drafting options: a bake-off across DeepSeek, GLM, and Qwen with Opus retries on failures (my recommendation), DeepSeek-only on all shards, or keeping T11 unchanged and trying external coders starting at T12 — plus room for their own answer, folding in the old lane retirement as part of the first option.
