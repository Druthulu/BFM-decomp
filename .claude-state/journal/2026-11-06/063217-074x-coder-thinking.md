---
ts: 2026-11-06T13:32:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jSAvuoZZ3FSx7Zs2c00d
---
Now I see the orig: insn 291 is the real addiu `a1 = fp+16`, then insn 293 is the asm barrier, then the chain, then 310/312 are the no-op moves at the call.

So in BOTH orig and nobar, after cse there are two a1 sets: 291 (real) and 312 (no-op move). The difference: in orig, the asm at 293 sits between 291 and the chain. In nobar, no asm.

Now, which insn survives to sched1? In nobar's sched dump, insn 291 was absent and 310 present. In orig's sched dump, what's present? Let me check the orig sched dump's block 17 ready list for 291/312.

If in orig both 291 and the no-op survive, then sched1 has 291 early. In nobar, 291 got deleted and only the no-op (310) remains, which cse's REG_EQUAL turns into the addiu at the call site.

Who deletes 291 in nobar? Probably `delete_dead_from_cse`: the no-op move 310 `a1 = a1` with REG_EQUAL fp+16 — cse may have determined that insn 291's value is dead because 310 re-sets a1 to the same value... Hmm.

Actually wait: in nobar, insn 308/310 are `a0 = a0` and `a1 = a1`. delete_dead_from_cse deletes insns whose results are unused. But 291 sets a1, used by 310 (a1=a1) and the call. So not dead.

Hmm, but sched's dump shows 310 as the addiu with the chain 302→310→305. Maybe the UIDs got renumbered: perhaps jump_optimize (noop_moves=0) did something. Actually! The pass at line 2923: `jump_optimize (insns, 0, 0, 1)` (before cse2) — with cross_jump=0, noop_moves=0. Hmm.

Hmm, wait: maybe in nobar, insn 291 IS present in the sched dump but I mis-read. The ready list showed "insn[ 288]: priority = 1" and no 291. Let me directly grep the sched dump's block 17 listing for 291.

Actually, let me approach differently: what I really want is a source change that keeps the early addiu. The mechanism in orig: the asm. In nobar, the addiu at 291 exists after cse but is gone at sched1.

Let me find which pass removed it: compare nobar.i.cse (291 present) with nobar.i.loop / nobar.i.jump (after the jump_optimize at 2923) / nobar.i.cse2.

If 291 is deleted by the jump_optimize before cse2, then it's the noop_moves... no (0).

Let me check nobar.i.jump (the jump dump after line 2923's jump_optimize? The dump file "jump" is written after the FIRST jump_optimize (line 2836). The second jump_optimize at 2923 doesn't dump (jump_opt_dump is only written once at 2836). Hmm. The cse2 dump is written at 2908 before cse2.

Let me check nobar.i.cse2 for 291.
