---
ts: 2026-11-06T09:01:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_if2QXFJC4T7n5wJX6hN3
---
Pass order: cse1, loop, cse2, jump, flow_analysis, combine, sched1, local_alloc, global_alloc, reload, sched2, ...

Dead code: `delete_dead_from_cse` after cse1 — deletes dead sets from CSE. flow_analysis does liveness but not DCE? Actually in 2.7.2, dead code elimination is done by `delete_dead_from_cse` (after cse) and `delete_noop_moves`? And `jump_optimize` removes unreachable code. A dead `pal = something` after the loop: cse1's `delete_dead_from_cse` removes sets of dead registers? Hmm, `delete_dead_from_cse` deletes insns whose only effect is a dead set (from the cse table). A `dst = pal;` where dst is dead would be deleted there.

But note: a *use* of pal in a set that's dead would still be deleted with the insn.

What about a use of pal in an instruction that combine eliminates? combine runs AFTER flow and cse2 and BEFORE sched1/local_alloc. So combine-eliminated uses don't extend liveness at local-alloc.

So any dead use is gone by local-alloc. The only way to extend pal's liveness to local-alloc is a use that survives to local-alloc and is eliminated later (reload/sched2) or that costs no instruction anyway.

What survives local-alloc and gets removed by reload/sched2? Reload can remove? Hmm, sched2 doesn't remove insns. reorg/dbr don't. jump2 doesn't.

Alternatively, a use that is *free*: e.g., an instruction that uses pal as an extra operand without adding cost. Like a `move` that's needed anyway: if pal is copied to dst at the loop start, that's the copy. A use after the loop can't be free.

Hmm, wait: what about a use of pal in the *same* instruction as another use, e.g., `*dst = *pal;`? That's a load and store (2 insns) — but semantically the target's loop reads from src (t4), not pal.

What about the loop's first iteration reading `*pal` instead of `*dst`? Semantically the same value, but it would need a branch or would use pal in every iteration.

Hmm hold on. Let me reconsider whether the keepalive is truly needed for score 0 or whether a different arrangement of the *other* real-C moves can fix the register shift. The shift (mine a1..t4 vs target a2..t5) is exactly "a1 is free in mine but reserved in target". The keepalive reserves a1. Without it, the allocator uses a1 and shifts everything down.

Alternative: reserve a1 by pinning something else to a1! But that's a lever (pin) — "no new lever of any kind". The existing pins: bp $3 (v1), kk $2 (v0), pal $5 (a1). pal is pinned to a1 already; we need it live.

Alternative: make the loop's pseudos *prefer* a2.. by adding a fake live range via real C in a way that shifts... 

What if we introduce a real variable that occupies a1 during the loop and is genuinely used? For example, keep the tag or n in a1? That's a new temp with real uses — but it must not add instructions. The target's loop already has a1 free; adding a real value in a1 would change the allocation.

Hmm, what if `pal` is used as the loop's *source* pointer in the A case? src = REC->base (a1?) no, src is base (bp).

Let me look at the target again: insn 43 `addu a1,v1,v0` (pal), insn 45 `move t3,a1` (dst). Between them: `blez a0`. So pal is used only at the loop start. If the real C had a use of pal after the loop, the target's asm would show... nothing, because the keepalive is zero-byte. A real C use would emit code. So the target's source must have a *zero-cost* use of pal after the loop.

What zero-cost use exists in C? Only something the compiler can prove dead but that still affects liveness at local-alloc... contradiction, since liveness is computed after DCE.

UNLESS: the use is in an instruction that sched1 keeps but reload/sched2 turns into nothing. Hmm, what about a use in a *compare* whose result is used by a branch that jump2 later simplifies? No.

What about `if (pal == dst)` where the comparison is folded because pal==dst is known? Not known.

What about a use in an instruction that's a *nop* after reload because the destination is the same as the source? E.g., `pal = pal;` — a self-set: cse1 deletes it? `delete_dead_from_cse` might delete it as dead. Hmm, but the instructions say identity-statement launders do NOT count as a crack anyway.

So a real C crack seems impossible for this item unless the allocation can be fixed another way.

Alternative approach: change the *loop body* so that a1 is naturally occupied. For example, if one of the channel temps were a real C variable whose live range spans the loop in a1... The loop's temps are r,g,b,tr,tg,tb,cur,tgt,result. They're all local to the loop. If the source reuses a variable that also appears after the loop (e.g., `result` used after the loop), its live range extends. But the target's code shows the loop temps in a0,a2,a3,t0,t1,t2 — with a1 reserved. If we extend a temp's live range past the loop, the allocator might put IT in a1 and shift others... but the target has no value in a1 during the loop.

Wait, actually the shift means: target uses registers a2..t5, mine uses a1..t4. The register *file* used is one slot higher in the target, meaning a1 is reserved (by pal). If instead a1 were used by a real long-lived temp, the rest would shift up too! The identity of the a1 occupant doesn't matter for the shift — only that a1 is occupied. But then a1's occupant would emit code using a1, whereas the target has no a1 use inside the loop. Hmm, unless the occupant is pal (which is only used at the loop start — the addu a1 and the copy).

So pal in a1 with a long live range is exactly it.

Hmm, wait. Let me reconsider: maybe the real C *does* have a use of pal after the loop, but it's a use that gcc removes in a later pass while still extending liveness. Which passes run after local-alloc? reload, sched2, reorg, dbr, jump2. Does reload ever delete a dead move? `reload` can delete? No. But `sched2`... no. `jump2` can delete insns in unreachable blocks. Hmm.

Actually, maybe flow_analysis (before combine/sched1/local_alloc) does NOT do dead code elimination, and the only DCE is delete_dead_from_cse after cse1. If the dead use is created AFTER cse1 (e.g., by loop.c or cse2), it might survive to local-alloc and be deleted by... nothing? Then it would emit an instruction. Unless it's a zero-byte use like an asm — which is the lever.

Alternatively, a dead set could be deleted by `combine` (combine removes dead insns: `try_combine` can delete a dead set). If the use is deleted by combine (which runs BEFORE sched1/local_alloc), liveness is not extended.

Hmm, so what about the case where the use is in a `set` that combine turns into a *no-op move* but keeps? No.

Let me try yet another angle: maybe the register shift can be fixed by changing the pins' arrangement — e.g., removing the pal pin and letting pal be a normal variable, then the keepalive-equivalent could be a real use. But pins are needed (other kinds may stay but removing might break).

Actually, let me test what happens if I remove the keepalive AND the pal pin (letting pal be a normal variable). Then maybe the allocation changes. The constraint allows removing other-kind levers? "levers of other kinds the def already had (pins under other causes) may stay, never added" — implies they may also go. MATCH only requires the kinds in <dir>/kinds (keepalive) gone. So I can remove pins if that helps! Let me try removing the pal pin along with the keepalive, and see.

Actually the pins were "NEEDED DIFFERS" for score 0 with the keepalive. Without the keepalive, maybe different pins are needed. Let me try a few pin/keepalive combos:
j1: no keepalive, keep all pins → 41 (done).
j2: no keepalive, no pal pin.
j3: no keepalive, no pins at all.
j4: no keepalive, keep bp/kk pins, no pal pin.

Let me score these.
