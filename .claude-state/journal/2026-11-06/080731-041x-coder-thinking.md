---
ts: 2026-11-06T15:07:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yHO6wKzL3kV8TpKuRcGn
---
Excellent. Now I see the RTL. `reg/v:SI 196` is vol. In b4, insn 476 sets reg 196 (vol) and insn 478 sets it again with the and 65535 — so reg_n_sets[196] = 2. The smulsi3_highpart insn 472 sets reg 205 (a temp) — that's the vol division's mult. So vol's division result goes through 205→207→196.

`birthing_insn_p` checks SET_DEST is REG and live at block start and reg_n_sets==1. Which insn is boosted? The one setting a value live at block start. reg/v 194 is sx (the pan). Let's see: insn 481 sets reg 209 = sx + 160; insn 484 mult; 485/486/488 → reg/v 194 = pan. So reg 194 (sx) is set by insn 488. Is reg 194 live at block start? YES — sx is set earlier in an earlier block? Hmm, actually in this block sx's value is read at insn 481 (`reg/v:SI 194`) and then set at 488. So reg 194 is live at block start (it's read before set in this block) → birthing_insn_p(insn 488) = true if reg_n_sets[194] == 1.

But reg 194 is set earlier too (sx = (s16)...; sx = 0xF...). So reg_n_sets[194] > 1. Hmm.

Wait, which insn does sched1 boost to make PAN first? Let's look at the scheduling log for insn 472 (vol mult) vs 484 (pan mult) priorities. Let me grep the log.

Actually, let's look at the sched dump's log part: lines ~1300-1500 contain ";; insn[NNN]: priority = ...". Let me find 472/484/481/476.
