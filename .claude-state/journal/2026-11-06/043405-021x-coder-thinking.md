---
ts: 2026-11-06T11:34:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_X4t6SoNEjS0kBvokeG7l
---
I can adapt dis.sh for my item. But I also need the TARGET asm. How to get target? The target comes from build/ — the built object of the TU (the compiled original with the current src). Wait: the target is the "expected" asm from the original game (the matched object). The build/ directory contains built objects from src; but for a matched function, the target asm is the reference. Hmm.

Actually in this project, when a function is matched, the target is the original ROM disassembly (the "expected" .s). Let me check how the diff in dt.sh obtains target: delever_search.py compares with "the function in build/". So build/ has the reference object (the original game's built object?). Let me look at delever_search.py briefly for how target is obtained.

Let me grep.
