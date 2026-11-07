---
ts: 2026-11-06T14:09:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FYvUfzH4BWpWOWFQQso3
---
This is a big register table. I need to identify the pseudos for i, dst, src, n in block 14 (the loop). Let me look at the RTL for block 14. Let me find "block 14" in the RTL portion.

The lreg dump structure: register table first (lines 4351-~), then the RTL per block. Let me find where the RTL starts. Search for ";; Register dispositions" or "Code for " or "Basic block".

Let me grep in the function range for "block" headers.
