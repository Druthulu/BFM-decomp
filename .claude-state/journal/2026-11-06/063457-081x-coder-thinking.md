---
ts: 2026-11-06T13:34:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oLOdfZWnY3D2cXL5QCUQ
---
Combine doesn't do global DCE. But `try_combine` merges insns: it might have combined 291 (a1 = fp+16) with the no-op 312 (a1 = a1)?? They're far apart, no.

Hmm, wait. Maybe the addiu at 310 in the combine dump is the result of combining 291 with... no, 310 is at the call site.

Actually, hold on: maybe the insn numbers changed because combine *recreated* the addiu at the call site from the no-op's REG_EQUAL. Combine's `subst` uses REG_EQUAL notes: for the no-op `a1 = a1` with REG_EQUAL (plus fp 16), combine's try_combine may replace it with the REG_EQUAL expression. And then 291 (the original addiu) is dead and combine deletes it via `undo_all`/`delete_insn`? Hmm, combine can delete insns when `added_sets` etc.

Actually, `record_value_for_reg` and `record_dead_and_set_regs` are used for the "I1/I2/I3" window. Not global.

Alternatively, flow_analysis might have marked 291's result dead and combine's `try_combine` deleted it. Hmm.

Whatever the exact pass, the empirical fact: in orig, the asm between the real addiu (291) and the no-op (312) prevented this. The mechanism is likely combine's `reg_dead_at_p` scanning: it scans forward from an insn to see if a register is dead, and it stops at an asm? Hmm.

Honestly, for the purposes of the task: I need a real-C construct between the `nn = ...` assignment and the s0 chain that prevents combine from sinking the addiu. Candidates that produce real code: a store, a load, a call. Any of those would add code — UNLESS it replaces an existing insn.

Hmm, wait! What about reordering the existing code so that an existing insn sits between? E.g., move the `aa = (s32)(q + 1);` assignment AFTER `nn = (s32)buf;`? Both are before the chain; the order would be nn then aa. Would that help? No, combine's issue is between 291 and 312.

What if the s0 chain's first insn is moved between? It already is.

Hmm, what about the `d[2] = s0` store? It's after the chain.

Actually, maybe the mechanism is not "combine needs a barrier" but the REG_EQUAL note on the no-op. If the no-op at the call site didn't have the REG_EQUAL note, combine couldn't substitute. The note comes from cse's canon_reg. Where does cse get a1 = fp+16? From insn 291's set. 

What if the *source* made the call's argument not a copy of nn but a fresh expression, so there's no no-op? E.g., `func_80015978(aa, (s32 *)nn);` — the argument is the variable nn (a hard reg). cse's canon_reg turns the argument setup into `a1 = a1` with REG_EQUAL. If instead we wrote `func_80015978(aa, (s32 *)(buf + 0));`? Then the argument is the address expression, expanded at the call → addiu at the call site (late). Not good.

What if we pass `(s32 *)nn` where nn is NOT pinned? Then the call's argument is a pseudo copy; the value would be materialized early? Hmm, v21 (unpinned nn) gave 27.

OK, let me try a different practical approach: since the barrier's effect is to prevent combine from substituting the no-op, what real-C construct has a similar effect on combine? Combine's window is 3 insns, but the REG_EQUAL substitution of a no-op is done by... let me actually look at what combine does with `(set (reg) (reg))` with REG_EQUAL.

Hmm, time. It's 06:50ish. I've spent ~45 min on item2. Let me step back and prioritize the whole task: 5 items, each 20-30 min. Item1 done in ~15. Items 2-5 remain. I should not sink 45 min into item2. Let me do a handful more cheap tries and then mark it WALL/PARTIAL if not cracked, moving on.

Actually — an important realization: for a WALL, "best = lowest score of a lever-free body" — score 2 is the best. A WALL needs ≥30 tries. Let me do a batch of ~12 more quick variants to reach ~31.

But maybe there's a smarter idea: since the problem is combine folding the no-op, what if we make the call's argument setup happen *before* the chain in source, i.e., compute `nn` and then use it? Hmm, the argument setup is at the call by construction.

What if we add a *use* of nn before the chain that emits no code... 

What if we declare `nn` as `volatile`? `volatile s32 nn` pinned to $5? Volatile applies to memory objects, not registers; gcc might complain.

What if we make `buf` volatile? Then the address is still the same; but loads/stores to buf become volatile (extra code? no, same instructions, but different scheduling). The `nn = (s32)buf` address computation might be treated differently. Actually volatile on the array would affect the mem refs, not the address. And the reads after the call (buf[0], buf[1]...) are already loads. Might change scheduling. Worth a try? It would change the codegen of the loads? Volatile prevents cse of the loads — the loads are already distinct. Hmm, could add code.

What about making the *store* `d[2] = s0` volatile? That prevents combine from moving things? Might change the delay slot.

Let me think about the actual target order once more: target has `addiu a0` and `addiu a1` adjacent right after `move s0,v0`, then the chain. In the ORIGINAL source (with asm), after cse2+combine, the addiu stayed at 291 (right after a0). So the target's source is exactly our source minus the asm plus *something* that has the same combine-blocking effect.

Since the asm's effect is at combine (between 291 and the chain), a zero-byte real-C construct that combine respects... Combine's window: it processes insns and for each it tries combinations with the next 2 insns. The REG_EQUAL substitution of the no-op happens when combine processes the no-op itself (I2 = no-op, and it substitutes the REG_EQUAL). Hmm, that's local. So why would an insn 20 positions earlier matter?

Unless combine's substitution uses `record_value_for_reg`: combine records the value of registers as it scans and uses it for `subst`. The scan (`record_dead_and_set_regs`) runs over the whole function, recording register values. When it sees the asm, does it reset the record? Let me look at `record_dead_and_set_regs_1`: it's called via note_stores for each insn; for an asm, note_stores would see the clobber (mem:BLK) → not a register → no reset. Hmm.

Alternatively, `reg_dead_at_p` scans forward from an insn and stops at... Let me look at reg_dead_at_p.

I'm going too deep. Let me do the practical thing: generate ~12 more variants exploring this hypothesis empirically, then wall it.

Variants to try (each quick):
- v40: `nn = (s32)buf;` then `aa = (s32)(q + 1);` (swap order of aa and nn).
- v41: assign nn twice: `nn = (s32)buf; nn = (s32)buf;` (the second is a no-op that may kill the REG_EQUAL chain).
- v42: `nn = (s32)buf; nn = nn + 0;`
- v43: make buf volatile: `volatile u16 buf[4];`
- v44: `nn = (s32)(void *)buf;`
- v45: `nn = (s32)buf; t = t + 0;`? fold.
- v46: put the call args in locals: `s32 *np = (s32 *)buf; func_80015978(aa, np);` — hmm, this changes the call arg (np is a pseudo).
- v47: `func_80015978(aa, (s32 *)(buf));` (direct, no nn) — changes nn usage.
- v48: move `d[2] = s0;` before the chain? no.
- v49: `nn = (s32)buf;` then `if (nn) {}` (empty if) — gcc may keep a test? no.
- v50: `s32 *np = buf; nn = (s32)np;` tested (v31) = 17.

Actually, v41 `nn = (s32)buf; nn = (s32)buf;` — the second assignment is a redundant set of a1; cse might delete it (dead store to a register). Hmm.

Let me also try: use `buf` in a way that makes the address's REG_EQUAL note not exist. The REG_EQUAL note on the no-op comes from... the copy `a1 = a1` gets REG_EQUAL from the copy propagation of reg69's value. If reg69 were not a simple address but computed via a non-REG_EQUAL-able expression... 

What if buf's address is computed via a pointer variable that is *modified*: `u16 *bp = buf; bp = bp;`? no.

Let me just run the batch. I'll write gen4.py with 12 variants.

Actually, wait. Before that, let me reconsider the possibility that the target's early addiu comes from a DIFFERENT source structure entirely: maybe the original source assigned nn BEFORE the rand calls and the code we see is the result. But then the target's addiu would be before the rand calls, not after. Unless the addiu was moved by sched1 to after the rand calls due to... the rand calls clobber a1! a1 is caller-saved. So an assignment to a1 BEFORE a call would be destroyed by the call. So the compiler must place the a1 assignment AFTER the last call before its use. That's why the addiu is after the second rand! 

So: the addiu must be after the last call (rand at 281) and before the chain (source order). sched1 placed it at 291 in orig. Without the barrier, combine/cse sink it to the call site.

Hmm OK, so what if there were a *third* call? No.

Let me try the batch.
