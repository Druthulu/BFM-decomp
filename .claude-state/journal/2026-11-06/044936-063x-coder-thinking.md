---
ts: 2026-11-06T11:49:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dRxWPbzUXZoh2ZE1kjY9
---
All still 1. Let me look at the cse dump to understand. Actually, let me check whether the target's lbu is really a reload of the same address. Could it be that the original code stored to +6 then loaded from +6 but the compiler didn't forward because of the `sb` mode vs `lbu` mode (QI store from SI subreg vs QI load zero-extended)?

Let me look at the RTL dumps. Let me use hdump for orig and w1 and diff the cse output.

Actually, maybe there's a simpler explanation: in the target, the reload `lbu v0,6(s0)` might be from a *different* C statement — maybe the original read byte[6] again into a *different* variable, not reusing temp_v0. E.g.:
```
temp_a1 = *(u8*)(arg0+6);
```
and then stored temp_a1. But the target uses v0 for both, so a different variable could still land in v0.

If the reload is into a DIFFERENT variable (say temp_a1), then cse might still forward the stored value... same memory.

Hmm.

Wait, actually maybe the original's store was `*(u8 *)(arg0 + 6) = temp_v0;` where temp_v0 is s32, and the reload `temp_v0 = *(u8*)(arg0+6)` — but between them the original had `temp_v1` usage. No.

Let me look at the cse dump. I'll run hdump for w1 and orig, then diff the .cse files for the function.

Let me do that.
