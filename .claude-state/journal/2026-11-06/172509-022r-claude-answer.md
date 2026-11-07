---
ts: 2026-11-07T00:25:09.600Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: 0c8f5840-357d-42c1-bb65-c4611ff09eba
usage: {input: 6, cacheRead: 204399, cacheWrite: 870, output: 797}
---

FYI: T11's expert added a third DeepSeek note, for every DeepSeek coder in every project. The judge refuses any `../` in a command as outside the project, so include strings should go in a file instead. To undo it, run `/usr/bin/python3 tools/pa_ext.py set --drop-model-note openrouter-deepseek/deepseek 3`.

There's a problem with its wording, though. It tells coders to "write absolute paths", which contradicts the standing note that says to use project-relative paths. I've asked the expert to reword it so the two agree: no `../`, and paths relative to the project root. This false refusal of `../` paths is also worth adding to the PA3 bug report, next to the sandbox failures.
