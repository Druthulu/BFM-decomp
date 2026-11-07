---
ts: 2026-11-06T12:13:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1oIWivME7ygfkTKbMz2m
---
I need a disassembly with real registers. Is there a tool? `tools/asm-differ` maybe. Or `tools/masked_diff.py` with a verbose flag. Simpler: I can write a tiny python script that uses md.insns_from_object and prints word/registers... but that's re-implementing. Let me check md.insns_from_object output fields and if there's a disasm string. Let's grep masked_diff.py for "mnem".
