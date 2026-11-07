---
ts: 2026-11-06T20:26:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2XYaNMY7voyxCBNRkzRc
---
In nolau block 7, all priorities are 1. The ready list at T-4: `103 (1) 95 (1) 108 (1), now 108 103 95` — the scheduler picked 108 (the const a1) first, then 103 (the store), then 95. Wait, the order in "now" is the ready list after picking. The printed order is the *new* ready list sorted by priority.

Hmm, at T-3 it picked 110 (the call? no, 110 is the call insn... actually 110 = call). At T-3: 110, T-2: 113, T-1: 116 (the jump). Hmm, the scheduler schedules backwards? The dump lists from T-1 upward, so the schedule is built in reverse: T-1 is the last insn. So the final order (forward) is: 95, 101, 103, 108, 110, 113, 116? Let's see: at T-6 picked 101 (after 95), T-5 picked 103, T-4 picked 108, T-3 picked 110, T-2 113, T-1 116. Forward order: 95, 101, 103, 108, 110(call), 113, 116.

Wait, but the actual RTL in .dbr showed: 95 (move a0), 101 (li v0,7), 103 (sh), then call seq [call 110, const 108 in delay slot]. Hmm, but sched2's order says 108 before 110 (call). Then reorg put the const (108) in the delay slot of the call. Yes: the const is right before the call, so reorg moves it into the delay slot.

In orig, the block has the asm (insn 102) which is a barrier; the const (100) and asm (102) are in the same block? The volatile asm forces ordering.

So in nolau: order 95(move a0), 101(li), 103(sh), 108(const), call. Reorg picks 108 (immediately before the call) for the delay slot.
Target: order move a0, const, li, sh, call. Reorg picks sh.

So sched2 in nolau placed the const LAST (after the store). All priorities equal (1). The tie-breaking at T-4: ready list `103 95 108` and it picked 108. The ready list order is by priority then by... `rank_for_schedule` uses INSN_PRIORITY, then `INSN_LUID` (later LUID first? since scheduling backwards). Hmm.

In the orig (target) version, the block structure differs due to the asm barrier: the const and the store are in different scheduling blocks! Let me check orig block 7.

Actually in orig's .sched2, block 7 is "from 110 to 120" (different insn numbers). Let me look.
