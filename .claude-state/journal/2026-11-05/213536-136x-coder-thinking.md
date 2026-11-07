---
ts: 2026-11-06T04:35:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Ss3hkAjwrB8BvOvQEGU
---
z10 = 19 (worse than z8's 6). The duplicated store changed the block layout.

z8 = 6 is the best. The remaining diff is just the order of the p load vs the addiu and the extra nop (109 vs 108). That's 2 instructions' worth of order: mine addiu, lw, nop, sh; target lw, addiu, sh.

To fix: get the p load before the addiu. Since the addiu's birth in z8 (source p then add) is after p, but sched still put add first... Let me look at z8's sched priorities via a dump. Maybe the p load's WAW dependency with the obj->1C value delays it, and the addiu is ready earlier.

In z8's RTL: p = obj->1C (load into p); v = p*3*32 (sll/addu/sll); p = model (load into p); v = v+0x600. The p reload (load into p) has a WAW/anti-dependency with the previous p value used by the sll chain. So it can only issue after the last read of p (the sll at 4940 / the addu? the sll uses the addu result, not p; the addu reads p (v1) at 493c). So p's last read is the addu (493c). The p reload can issue after the addu. The addiu (v+0x600) depends on the sll at 4940. So both ready after 4940/4941.

Target order: sll(4940), lw p(4944), addiu(4948), sh(494c). So the p load issued before the addiu. In z8: sll(4940), addiu(4944), lw p(4948), nop, sh. 

The scheduler chose addiu first. Priorities: addiu → store = 2; lw p → store = 2. Equal. Tie-break by... the ready list sort. Let me look at how the ready list is sorted: `schedule_block`'s sort uses `rank` = priority, then `insn_unit`, then... Let me read `schedule_insn`'s selection and the `rank` function. Actually, there's `debug_ready_list` and the sort uses `rank (insn)` which returns INSN_PRIORITY + something. Let me grep "rank (".
