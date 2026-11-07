---
ts: 2026-11-06T15:10:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qrbwS80ScUYTOIbNZQ5y
---
In b4: insn 484 (pan mult) launches at T-10, then 472 (vol mult) at T-22. So PAN mult is FIRST in b4's sched1?! But b4's final code has vol mult first (554) then pan (564)... Hmm wait, the ready list order at T-10: "launching 484 before 473" — 484 is the pan mult. Then 472 later. So sched1 emits pan first, then vol. But the final disassembly has vol's mult at 554 and pan's at 564. Contradiction?

Hold on: in b4's disassembly (which I dumped from cand.o), let me recheck. Earlier the a2 dump showed:
```
550 subu v1,v1,v0
554 mult v1,a0
558 mfhi t1
55c addiu v0,a2,160
560 nop
564 mult v0,a0
```
And a2 == b4 (same mask). Hmm, but sched1 says 484 (pan) first. Wait — which is which? insn 472's mult uses reg 204 (vol's numerator: `(0xA0-av)*0x7F`), so 472 = vol mult. insn 484's mult uses reg 209 = sx+160 → pan mult.

sched1 order: 484 first (pan), then 472 (vol). But the final disassembly: `mult v1,a0` at 554 (v1 from the `subu v1,v1,v0` at 550, i.e. vol) then `mult v0,a0` at 564 (pan). So the final order is vol first?! Unless the final is after sched2, which reorders. sched2 (post-reload) runs after reorg? No, order is: sched1, local-alloc, global-alloc, reload, sched2, ... reorg last. sched2 can reorder too.

Hmm, so the final order comes from sched2. OK this is getting deep.

Actually, wait: in b4 the score is 2, so the schedule is essentially right. The sched1 log shows pan first in BOTH orig and b4? Let me check orig's dump. But I don't have an orig dump (the "b4" dump might be orig if the copy was stale). Ugh.

Let me settle this: the b4 dump's RTL at insn 478 showed `and reg/v 196, 65535` — the b4 mask. So the dump IS b4. Good.

Now let me dump the no-launder (a0) and compare the sched1 launch order. If a0 shows vol first (or a different order), then the difference is in sched1.

Actually the b4 sched1 order: 484 (pan) at T-10, 472 (vol) at T-22. Interesting — pan first, yet the final code has vol first. So the final order must be from sched2 (post-reload). In the no-launder case, the final order is pan first. So the difference is downstream (sched2 or reorg), not sched1's launch order.

Hmm OK. Let me just dump a0 and diff the sched2 (.sched2) final order and the .dbr.

Let me do that: dump a0.
