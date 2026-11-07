---
ts: 2026-11-06T13:31:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hS02Y9vjydkqXyD6ahoY
---
Now I see the pre-sched1 RTL (after jump_opt/cse? this is the "jump_opt" dump, i.e., after the first jump_optimize, before cse).

Order: 283 (t = rand result), 286 (aa address computation: reg106 = reg74+4), 288 (a0 = reg106), 291 (a1 = reg69 — reg69 is the buf address pseudo!), 293-302 (chain), 305 (store), 310 (nn?...).

Interesting: insn 291 is `(set (reg/v:SI 5 a1) (reg:SI 69))` — a COPY from reg69 (the buf address pseudo). And reg69 was computed somewhere earlier (probably at the top of the block: reg69 = fp+16). So `nn = (s32)buf` became: reg69 (address) then copy to a1.

Wait, why is there a copy to a1 (a hard reg) at 291 but the sched dump showed insn 310 as the addiu a1? Because cse2 or combine propagated the copy: after cse, insn 291 (copy a1←reg69) was folded into the addiu a1 (310) — cse substituted reg69 with its value (fp+16), creating the addiu at 310. Yes! cse's canon_reg replaced the copy source with the address expression, and the copy became `a1 = fp+16` at position... hmm, but then the insn position should stay 291.

Actually the sched dump showed insn 310 = `(set (reg:SI 5 a1) (plus (reg:SI 30 $fp) (const_int 16)))` with next chain 302 → 310 → 305. So the insn was renumbered 291→310? No... Hmm, cse deletes and re-creates? Whatever.

Key insight: at the source level, `nn = (s32)buf` first computes the address into a pseudo (reg69) and then copies to the hard reg a1. The address pseudo reg69 is computed EARLY (at the top of the loop body, before the rand calls?). Let me find where reg69 is set.

If reg69 is born early (e.g., at the loop head), then the a1 copy depends on it, and the copy is a separate insn. In the target, the addiu a1 is early. 

Hmm, what if we make `buf` be used earlier so that reg69 is born early — it already is. The copy `a1 = reg69` is at 291 (right after aa). Then cse turned it into `a1 = fp+16` (310) because reg69's value was known. In the ORIG (with the barrier), the asm prevented cse from propagating reg69's value across the asm! Because the asm has a memory clobber but reg69 is a pseudo... hmm, cse's REG_EQUAL propagation: reg69 = fp+16 (a constant-ish expression). cse would record reg69's equivalent and substitute it at uses. The asm clobber would invalidate memory but reg69 is a register.

Hmm, but the ORIG has the asm between `nn = (s32)buf` (116) and the chain. If cse propagated reg69 into a1, the copy would become an addiu at 291. In the orig, the barrier is at 117, right after nn. So cse sees: reg69 = fp+16; asm; a1 = reg69... cse's equivalence table persists across the asm? cse invalidates at basic block boundaries, and an asm with memory clobber doesn't end the block. Hmm.

Wait, actually the difference between orig and nobar at the RTL level: in nobar, insn 291 (copy) became the addiu at 310 (moved after the chain!). In orig, presumably the addiu stayed at 291. Why would cse move it after the chain? It wouldn't move it; it must be that in nobar the copy at 291 was *deleted* (because a1 = reg69 and reg69's value was propagated to the call's use?) and a NEW addiu was created at the call site (310) by... hmm.

Let me look at the cse dump for nobar around that area. The .cse dump is after cse. Let me find the relevant insns in nobar.i.cse.

Actually, this is a deep rabbit hole. Let me time-box: item2 has taken ~35 min. The rules say 20-30 min per item; a WALL needs ≥20 min and ≥30 scored tries. I have ~16 scored tries so far (1+10+4+... let me count: w1, 10 variants, 4 pin variants, 4 copy variants = 19). Need ≥30 for a WALL.

Let me do a few more targeted tries (11 more) then decide.

Insight from the RTL: in the orig, the copy `a1 = reg69` (insn 291) exists and is early. In nobar, cse/combine turned it into an addiu placed after the chain. So the difference might be that the *barrier* prevented combine/cse from propagating reg69 into the copy... Actually in the nobar sched dump, insn 310's next is 305 (the store) and prev 302. So insn 310 sits between the chain and the store. That's a *new* position. Where did insn 291 go? Let me check if 291 still exists in the sched dump.

Let me grep "(insn 291 " in nobar.i.sched.
