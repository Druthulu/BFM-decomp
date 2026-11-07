---
ts: 2026-11-06T08:30:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Gyi8hqsAdnT4E5rPbCf6
---
cwd is the shard dir. Need project-relative from /home/musashi/bfm-decomp. Rule says never prefix with cd. Hmm, but cwd changed. The Bash tool: "cd carries to the next call only in the main session". I can use paths from project root only if cwd is project root. I should cd back to project root once. Actually a command like `cd /home/musashi/bfm-decomp` alone — allowed? "Prefer absolute paths — cd in a compound command can trigger a permission prompt." Let me just do a plain `cd /home/musashi/bfm-decomp && pwd`? The house rule says never prefix a command with `cd <dir> &&`. But the working dir got changed to the shard dir by the harness. Hmm. The bin scripts use `cd /home/musashi/bfm-decomp` internally, so they work from anywhere. For Read tool, absolute paths are needed anyway.

For Bash grep of source files, I can use absolute paths /home/musashi/bfm-decomp/src/... That's fine.

Let me read the three functions.
