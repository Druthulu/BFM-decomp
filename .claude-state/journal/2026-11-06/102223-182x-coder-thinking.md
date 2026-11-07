---
ts: 2026-11-06T17:22:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0ypmJGmK5GNwnb3mvoO8
---
Now I see: mine materializes the six constants at the top (before the gte asm? where's the gte asm?). Let me look further — the gte macro should be right after. The constants are in $6 (a2), $8 (t0), $14 (t6), $21 (s5), $22 (s6), $23 (s7); then the mask in $15 (t7).

The gte asm uses $12,$13,$14 (t4,t5,t6) as clobbers. But $14 (t6) holds the 0x8E constant and is live across the gte asm! Let me check: the gte asm comes after the constants (insns 13-14). The constant in $14 would be clobbered by `ctc2 $14,$4`? Wait, the clobbers are "$12","$13","$14" — the asm writes $12/$13/$14. So the constant in $14 gets clobbered → the program would be wrong!

Unless the constant is rematerialized after the asm. Let me look at the asm following the constants.

Actually the mask is at $15 (t7) and the gte asm uses $12-$14. In the target, the mask is $14 (t6) — which is clobbered by the asm! But the mask is materialized at insn 16, AFTER the asm (13-14). OK.

In mine, the constant $14 is materialized at insns 5-6 (before the asm) and used at insn 76 (after). If the asm clobbers $14, the value would be wrong... unless gcc knows the clobber and doesn't allow it. But gcc DID allocate it to $14. So either the asm comes before the constants (in the actual chain), or the clobber doesn't apply.

Wait, the final asm listing shows the constants first, then... let me see the next lines (after addu $2,$12,4) to find the gte asm.
