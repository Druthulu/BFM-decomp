---
ts: 2026-11-06T21:54:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QqVWo7MrG6PbjLcvvzNy
---
The missing insn: target has an extra `li a3,6` at 312. Mine at 306-307: `bnez v1,858; li a3,6`. Target: `bnez v1,85c; li v0,6` then at 312 `li a3,6`. So target has both `li v0,6` (delay slot) and `li a3,6` after. Mine has `li a3,6` in the delay slot and no second li.

This corresponds to `tmp = 6; ... unk34 = tmp;` around line 224 in source:
```
        tmp = 6;
        ...
        ((Unkstruct_800B5CB8 *)arg0)->unk34 = tmp;
```
Target has tmp=6 (li v0,6) in the delay slot AND another li a3,6 later. So the target computes tmp=6 twice? Or has two different variables both =6.

Let me look at source lines 215-235.
