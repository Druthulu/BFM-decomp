---
ts: 2026-11-06T10:16:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_64xhDwnuXFnBlWwUrAV0
---
c31 (r2 as s16) drops to 21! Big improvement. Let me check c31's diff.

c31: `s16 r2;` — r2 = r + zr removed. r2 is used in `(u32)(r2 & 0x7FF0) >> 4` and `q = r2 & 0x803C`. As s16, the value truncates but codegen differs (sh/sll/sra). It improved to 21 with 189 insns (1 more than target).

Let me see the diff.
