---
ts: 2026-10-22T00:12:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OAsZizPClXhS5DWv0AlS
---
The baseline object: build/src/ov_SC02_026/ov_SC02_026_jr_8017C180.o — but this is the *current* build (which includes the banked body = score 0 = identical to target). Hmm, but the score compares against the BASELINE snapshot (BASELINE dir) if it exists. Either way, the object contains func_801832A8 as the target code (since the banked body matches the target byte-for-byte).

So I can objdump this object to see the target code! I need a mips objdump. Let me find one: the psyq toolchain in tools/psyq? Let me check for objdump binaries.
