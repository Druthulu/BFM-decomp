---
ts: 2026-10-22T00:42:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_RcArgAZaeWDhiniff9vU
---
masked_diff.py has insns_from_object. I can use `python3 -c` but rules say avoid. Alternatively use tools/asm-differ? Let me check its usage — probably a CLI.

Actually simpler: the `--try` output prints the diff with mine and target instructions. That gives me the target text I need (the diff tail shows target mnemonics). But for full target listing, I want a full disassembly.

Let me check masked_diff.py for a CLI.
