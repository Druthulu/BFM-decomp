---
ts: 2026-11-06T11:35:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Bw6CaY9H7TWy0H8Rhrul
---
It is in 800.o but objdump --disassemble printed nothing? Maybe the symbol is local/global mismatch or objdump needs -j .text. Let me try objdump -d and grep around symbol.
