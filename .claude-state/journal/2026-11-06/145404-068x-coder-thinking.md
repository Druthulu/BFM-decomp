---
ts: 2026-11-06T21:54:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fZ28BqZisboUd6vPin2T
---
Score 135, 709 vs 710 ins. The diff shows dst lands in a2 instead of v1. Note the target has v1 = dst, and a0/a1 are temporaries. Mine: a2=dst, v1/a0/a1 temps. So it's a register bank shift: target uses $3 for dst, mine uses $6 (a2).

The 1-ins difference: mine 709, target 710 — one instruction missing.

This is the twin of func_80191C50. Let me look at the tail structure. This body is big (310 lines). The dst blocks: `dst = *(s32*)(arg0+0xD0); ... dst+0x20 ...`.

The pin was needed because local-alloc/global-alloc put dst elsewhere. The $3 pin is a hard-reg preference for a *global* pseudo? dst is live within a block only (each block sets it then uses). It's likely local.

Actually dst is declared once but used in several blocks; each block's dst is a separate qty (local). The pin forces all of them to $3.

Without the pin, dst gets a2 in the block(s) that differ. The diff shows the *last* blocks (mine 663 vs target 664).

Strategy: dst is loaded from arg0+0xD0 and then used as a pointer in 8 statements. To get $3 naturally, we need local-alloc to give it $3. In the target, dst is in v1. In mine, a2.

Given the size, maybe the simplest: check whether the score 135 comes from just the dst bank or also tmp. Let me get the register pairs summary and all diff hunks.

Let me run with more output and capture the pairs line + count hunks.
