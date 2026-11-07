---
ts: 2026-11-06T22:08:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jhwvt4fEUxO7Lcxe85py
---
With dst pinned, tmp s16 = 25 (but 677 ins, semantically wrong shift). Not 0.

Let me try more tmp moves with dst pinned: the double-li issue. In x1, target has an extra `li a3,6`. That's because `tmp = 6` and `tmp = 0x96` (two different constants) — wait the insert is `li a3,6`. The target's tmp is v0; at 358 `li v0,6` (delay slot) and at 363 `li a3,6`. So target materializes 6 in v0 (tmp) and again in a3 (another variable). Mine materializes only a3,6. The other 6 in the target (a3) is some other variable — maybe `unk34 = 6` or `cnt`?

Look at the source around the case-8 area of item 4. Let me look at lines 170-190 of orig.

Actually, the missing insn is a *target* instruction, i.e., the target has one more instruction than mine. Since mine's code is 1 ins shorter, the compiler merged two identical `li` (one for tmp, one for another var) because tmp is not pinned. With tmp pinned to v0, the two `li`s have different destinations → both emitted. Lever-free, both have the same destination → merged.

To reproduce without the pin, we'd need the two constants in different registers — i.e., force the other variable into a different register. The other variable is likely `n34` or `cnt`. Let me find which. At target 363 `li a3,6` — a3 is $7, likely a local. Let me look at the source near the `tmp = 6` at line 180.

Let me view orig lines 165-200.
