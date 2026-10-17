---
ts: 2026-10-17T13:31:16.405Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a13c1de15ca946b2d
model: claude-opus-5-5[1m]
effort: medium
turnId: 62af40ee-cefb-4871-a954-45c335ce416f
---
I need to draft the approach note plus four coder briefs covering five functions each, with each coder working from a scratch directory under the run path and using delever_search --try as the official scoring tool against the oracle. I'm setting a time-box per function of around 40 minutes or 150 attempts, stopping early on a match, and clarifying that "lever-free" means avoiding pins, assembly hints, or register-level tricks.

Coders shouldn't touch src directly — they should just report the winning body path, which then gets applied by a single banking coder who handles the TSV rewrite, strict checks, R22, and the commit. For balance, I'm grouping the twenty functions into four sets of five based on kind and size mix: group A, B, C, and D each spanning across the numbering. Each coder will track per-function wall time and attempt counts, and I'll apportion total token usage based on those wall times once I get the notification. I'll write the explain-before-coding note first before handing off the briefs.

I'll mirror T9's setup: four coders crack five sampled functions each in parallel within scratch space, using a fixed time budget per function so crack rate and cost stay comparable. Since R22's `make clean` can't run concurrently and the sampled bodies share headers that fan out across many objects, I'll funnel all winning edits through a single serial coder to apply changes to `src/`, update the TSV, and run the strict check plus R22.
