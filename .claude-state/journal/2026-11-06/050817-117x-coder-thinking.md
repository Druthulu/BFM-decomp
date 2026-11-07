---
ts: 2026-11-06T12:08:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BBEqyoAalV3kRPV6otUy
---
Wait, v_both_argfirst uses `a1 = 0x980;` but a1 is not declared. That would be a compile error. Let me remove that variant or declare a1. Actually, let me just test the first 3 and drop argfirst. Let me edit the script.

Actually, let me just run and see; the argfirst will compile-error, which is fine (counts as a try). But let me fix it to be meaningful. Let me change to `s32 aa = 0x980;` and use aa.

Let me rewrite gen17 quickly.
