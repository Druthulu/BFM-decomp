---
ts: 2026-11-06T13:27:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SOfH8jwRh2tCZOpSnPK6
---
This block 17 is a different loop (the else branch with rand calls? insns 221-371). Hmm, wait, the function's do-loop body. The ready list starts at T-1 with insn 371 (the loop end / jump). The scheduling is BACKWARD (T-1 = last). So the block's insns are emitted in reverse pick order.

Insn 225 has priority 1 and is picked at T-48/T-49 (last emitted = first in the block). Insn 389 is a call? "ready list at T-48: 225 (1) 389 (1), now 225 389" — so 225 is picked before 389 at T-48, meaning 225 is emitted just before 389. Hmm, backward: at T-49 pick 389, T-48 pick 225... The emitted order is the reverse of the T order? In backward scheduling, T-1 is the last insn, and picks go backward. So the block order (emitted) is: T-49 first, ..., T-1 last. So 225 is emitted at position T-48 (near the end? no...). Ugh.

Let me instead look at the final scheduled RTL listing to see the emitted order, and find the addiu sp+16. The listing after all blocks (starting ~line 25549) shows the scheduled insns. Let me find "sp) (const_int 16)" in the listing (lines 25571, 25584, 25604).

Actually, the block 17 ready list mentions insn 225 with priority 1. Let me find insn 225 in the RTL listing: it's probably `(set (reg:SI 5 a1) (plus:SI (reg:SI 29 sp) (const_int 16)))`. Let me look at lines 25560-25620.
