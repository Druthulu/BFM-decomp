---
ts: 2026-11-06T09:32:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GlMPmMeaNBLPkkKLpmbO
---
Removing the keepalive: score 2. Diff:
- target has `sh zero,392(s0)` at insn 37, mine has it at 40 as `sh zero,392(a0)`.
So the store `*(u16 *)(s0 + 0x18A) = 0;` — target uses s0, mine uses a0 (a copy of s0?). The keepalive `"r"(s0)` at line 27 (after the store) forced s0 to be live, so the store used s0; without it, s0 gets copied to a0? Let me see the full insn listing.

Let me print insns 20-50 for win.c.
