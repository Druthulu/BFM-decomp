---
ts: 2026-11-06T15:44:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WSs3g7WQNgOiHkIfXau9
---
The label line is exactly `func_80181670:`. My awk should have matched `/^func_80181670:/`. But the end pattern `/^$/` — the function may not have a blank line until the next function. Maybe it matched but both files produce identical text? The sizes differ by 17 bytes overall (other functions).

Wait, my awk wrote o4_fn.s; let me check its size.
