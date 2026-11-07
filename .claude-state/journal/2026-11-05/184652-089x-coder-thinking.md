---
ts: 2026-11-06T01:46:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xWbkhd3NGrNP6BB3PUH6
---
So v1 (source order store then sh) emits li; sw; sh, and target is li; sh; sw. Only the two stores' order differs at the end. sched1 did NOT reorder them. So we need the source order sh;sw (target) but that reintroduces the merge.

Hmm. So the merge depends on the store being the last insn before the label. v1 shows: with sw not last, no merge. So if we can get source order such that sw is emitted before sh, the merge is prevented but the final order is wrong (score 2).

Can sched1 reorder the two stores to swap them? It didn't with this source. What if we change the aliasing perception: make one store non-struct or via a cast so sched1 thinks they're independent? Target wants sh then sw. So we need the emitted order sh;sw while the source writes sw;sh and the scheduler swaps them. The current v1: source sw;sh → emitted sw;sh. sched1 didn't swap.

What makes sched1 swap? It reorders by dependency and priority. Two independent stores: the scheduler processes the ready list; if both are ready, it picks the higher priority (larger). The store to 244 (sh zero) vs store to 28 (sw v0). Priorities: based on dependents. In target, sh before sw. In v1, sw before sh — the source order preserved.

Hmm, sched1 is a backward-ish? gcc's sched1 uses a forward list schedule with rank_for_schedule comparing INSN_PRIORITY. Both stores have priority 1 maybe; tie broken by INSN_LUID (order). So source order preserved. To swap, give the sh a higher priority: make it a dependency of something? Hmm.

Alternative: find another way to prevent the merge while keeping the order. What if the sh store is placed *after* the store in source but moved before by some other pass (not sched1)? No.

Alternative: use the `li` before sh and sw... target order: li v0,29; sh zero,244; sw v0,28. The li is emitted right before the sh. In source sh;sw, the li comes from the sw's constant. Fine.

Hmm, what if the *dec* block's store is made non-matching instead? The cross-jump compares zero's last insn (sw) with dec's last-before-jump (sw). If dec's block had an extra insn after its store at jump2 that isn't in zero's block, the comparison at i1 would be that extra insn vs zero's sw → no match. What insn could dec have after the store that emits nothing? Or that reorg moves? Target dec: lw; nop; addiu; j; sw(delay). The store is in the delay slot — moved there by reorg from before the jump. So at jump2, dec's store is BEFORE the jump. If dec had an extra real insn after the store and before the jump, reorg would place the store in the delay slot only if it's the insn right before the jump. Hmm, reorg's fill_simple: for a jump, it scans backward from the jump to find an insn to put in the delay slot (from the fall-through? no, from before the jump). It takes the insn immediately before the jump if it's safe. If there were another insn between the store and the jump, that one would go into the delay slot instead, changing the bytes.

So no.

What about making dec's store a different *instruction* at jump2? E.g., if dec's store were `sw v0,28(s0)` but with a REG_DEAD note difference? find_cross_jump doesn't compare notes (except stack regs).

Hmm, what about the sh? find_cross_jump compares zero's tail: sw. If we could make zero's last insn not sw but sh, with the final order still sh;sw... impossible: the last insn before the label is sw in target.

Wait — is it? Target: 1804 sh zero,244; 1808 sw v0,28; 180c epilogue. Yes sw last.

So at jump2 (before reorg), the target's zero block must have ended with sw and the label right after... and yet no merge. The only escape: the jump_chain/fall-through distinction. If zero's block had a jump at jump2 (deleted later by jump-to-next), both sides are j-reached → minimum 2 → no merge. And reorg would then fill... but if the jump is deleted at jump2, then after jump2 there's no jump; reorg doesn't need to fill.

Wait, but vA's return jump was deleted in the FIRST jump pass, not jump2. Why? Because it's a jump-to-next. The deletion code for condjump is at 664, but for simplejump to next... maybe it's in `delete_dead_jumps`? Hmm, but I couldn't find it.

Let me search jump.c for "thread_jumps" and how simple jumps to next are handled — maybe in `delete_insn` cascade via label deletion: after redirect_jump(insn, NULL_RTX) failed?? 

Hold on, maybe the first jump pass DOESN'T delete it; maybe the jump was deleted by `thread_jumps` (line 2859) which runs BEFORE cse and AFTER the .jump dump? No, dump is before thread_jumps.

Unless the .jump dump is written at line 2836 which is AFTER... let me recheck the exact order: line 2827 jump_optimize; 2836 if(jump_opt_dump) print. So dump after. So the jump was deleted inside jump_optimize.

Let me find it definitively by searching for all delete_insn/delete_jump calls with their conditions in the simplejump path. Let me read the block after "Detect jump to following insn" for simplejumps — lines 670-720.
