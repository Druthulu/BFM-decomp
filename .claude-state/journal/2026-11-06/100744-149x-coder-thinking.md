---
ts: 2026-11-06T17:07:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jBdjheCo61QDhvpoGcdN
---
Interesting: the mask is reg 15 = t7, defined at insns 571-572 as `movsi_internal2` with 16711680 (0xFF0000) then ior 65535 → 0xFFFFFF. Note: `movsi_internal2` (the same pattern as a move) — the constant 0xFF0000 loaded into t7 then ori 0xFFFF. Target: `lui t6,0xff; ori t6,t6,0xffff`.

So the mask pseudo is reg 15 (t7) in nopin. In the target it's t6 (reg 14).

Also note the mask's definition is at insn 571-572, i.e., near the END of the RTL (after the packet stores), but in the final assembly it appears at insn 16-17 due to sched1 hoisting.

So local-alloc gave the mask t7. Which pseudo got t6? reg 14 = t6 was given to... let me find who is in reg 14. From the dispositions: 117 in 14 and 130 in 14. Which is the 0xE100008E constant? Let me search the greg RTL for 0xE100008E (37848718? 0xE100008E = 3774873742 as unsigned; as const_int maybe -520093554). Let me grep for the constant values.

0xE100008E = 3774873742. In 32-bit signed: 3774873742 - 4294967296 = -520093554.

Let me grep for -520093554.
