---
ts: 2026-11-06T13:03:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Isoj5fiI0a0Mu0c7IKsG
---
Both ranges give 196 insns?! But symbol sizes say 218 and 217. 0x368/4 = 218. My byaddr range 0x1050..0x13B8 should give 218. It gave 196 — because some lines aren't in the 4-tab format (e.g. `nop` might be printed as a separate line? no).

Hmm, 196 vs 218 = 22 missing. Some insns might be in `.text` but objdump prints `...` for zero-filled? Actually objdump -d skips zero words by default (prints "..."). The target may have zero words (nop = 0x00000000) that objdump collapses into "...". That's why: `nop` is 0x00000000 and objdump -d omits runs of zeros!

So the missing 1 insn in mine is a `nop` (a zero word) that the target has. And objdump hides them. I need `-D` or `-z` to show zero insns. Let me use `objdump -dz`.

So the target has one extra `nop`. Where? Let me diff with -z.
