---
ts: 2026-11-06T14:55:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pjaXg4ETX3qXjAfDka3y
---
Line 566: `jump_insn 257 ... (label_ref 300)` — that's the `bne t,5,L71` (branch to label 300). Line 576: `jump_insn 262 ... (label_ref 276)` — an unconditional jump to label 276. And line 551: `jump_insn 247 ... (label_ref 269)` — the `beq t,3` (branch to label 269 = sel_054).

So label 276 = sel_094 (L73). So mine's `bne t,3,L73` became `jump (label_ref 276)` = `j L73`. Confirmed.

In orig, the `bne t,3,L73` is a conditional jump to label 276.

So the fold is in jump2. Let me look at the jump2 code that does this. It's a known-value fold. Let me search jump.c for where a conditional jump is converted to a simple jump based on the register's value.

Actually, maybe it's the `thread_jumps` function: it follows a jump to a label and threads. The `jump_insn 257` (bne t,5,L300) — L300 is the "after" block. The fall-through is the `bne t,3,L276`. Hmm.

Wait, maybe the fold is: the block containing `bne t,3,L276` is reached from the fall-through of `bne t,5,L300`. thread_jumps might see that the fall-through block's condition is implied... no.

Let me look at `thread_jumps` in jump.c. Let me find it.

Actually, let me look for `find_cross_jump` (line ~2363). The cross_jump optimization merges identical code sequences. Maybe the `bne t,3,L276` was merged with another `j L276`? Hmm.

OK, let me just look at the jump.c `thread_jumps` function.
