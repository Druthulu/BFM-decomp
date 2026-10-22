---
ts: 2026-10-22T04:26:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UdTTQPLwYLZtUurgT6YJ
---
The baseline is .run/baseline/... object of the ROM. So the target asm = objdump of that .o. I can objdump it to see the full target listing.

Which object? `self.primary["obj"]` — for the TU. The TU src/shared/ov/func_8014FD54.h is a header included in some TU. Let me find the baseline objects.

Let me just find the .o containing func_8014FD54 in.run/baseline.
