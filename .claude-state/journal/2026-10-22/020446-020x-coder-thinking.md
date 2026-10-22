---
ts: 2026-10-22T08:04:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_wpYIWizLZKSBT8IobUgh
---
There's `build/asm/` — maybe .s files. Let me check for the .s of ov_SC04_004_jr_8017AE2C.

Actually the target function is the CURRENT src compiled (with the pins). So the target asm = the pinned version compiled. build/src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.o presumably. Let me objdump func_80182ED4.

Let me check if there's an objdump for mips available. The tool probably uses a mips objdump. Let me check tools/delever_search.py for how it disassembles.

Simpler: use `tools/` — is there an mips-objdump? Let me check.
