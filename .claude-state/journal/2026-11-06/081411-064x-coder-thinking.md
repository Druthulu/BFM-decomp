---
ts: 2026-11-06T15:14:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6gyi7Wn0CA96mQvgP1QH
---
The .dbr dump is big. Let me find the region near the bne with the delay slot decision. Let me search for the insn numbers 478 and the branch. Alternatively, look at the final .sched2 RTL (post-sched2, pre-reorg) to see the order of the andi and the bne.

Actually, an easier empirical approach: test variants of b4 where the mask is placed at slightly different source positions, and see which score 0. The key is to get the andi out of the delay slot.

Let me think about where the andi lands in the final code and why reorg picked it. In b4's final:
```
584 li v0,16
588 bne a2,v0,594
58c andi a1,a1,0xffff
590 li a2,15
594 sll a2,a2,8
```
The andi at 58c is between the branch and `li a2,15`. In RTL terms, the insn order pre-reorg might already be: bne, andi, li a2,15, sll. That would mean sched2 placed the andi right after the branch (in the fall-through). Then reorg's delay slot fill: the thread copy would take the andi (first insn after the branch)! That's "fill_slots_from_thread". So the andi was scheduled into the fall-through by sched2 (because it was independent and sched2 hoisted/sunk it). Then reorg copies the andi (safe) instead of the sll.

If that's the case, the andi's position after the branch is a sched2 choice. In the target (with the launder), no andi exists, so the sll is copied.

So I need to prevent sched2 from putting the andi right after the branch. Hmm.

What if the andi is placed at the *launder position* (before the sx division) — that's b4, and sched2 moved it down. What if I place it even earlier (right after the vol division)? Same.

What if the mask is *dependent* on something after the branch? E.g., `vol = (vol | 0) & 0xFFFF` — fold removes.

Hmm, what about making the second set's insn be one that sched2 won't move after the branch: e.g., a `sw`/`lw` (memory ops are less movable). But we can't add memory ops.

Alternatively: accept a small extra but get score 0? Score 0 requires byte-identical (237 insns, same mnemonics). So no extra.

New idea: What if the second set of vol is achieved by a *narrower type* that causes a SUBREG copy which is zero-cost? E.g., declare `s16 vol`? Then the division result (int) assigned to s16 → subreg. The uses of vol promote back. Might be zero-cost if the uses are narrow... but the target uses vol as a full 32-bit value in the OR and the call. So a subreg would add sign-extension insns.

What about `u16 vol`? The division would be unsigned → different magic. No.

Hmm, let me look at this from a completely different angle: maybe the launder can be replaced by a *reordering* that makes the birth boost irrelevant. The launder exists because sched1/sched2 hoists the pan multiply. What if the source computes the pan BEFORE vol in a way that the compiler still emits vol first? No.

Actually — maybe a simpler C change: swap the two computations' source order. Currently vol first, then pan. Without the launder, the compiler emits pan first (wrong). What if the source order were pan first, then vol? Then maybe the compiler emits vol first? No — with the birth boost, pan is always hoisted.

Wait, let's re-examine: in b4 the final order is vol first (matching). So the mask DID fix the order. Good. The only residual is the delay slot.

So: keep b4's mask but prevent reorg from stealing it. What if the andi's result is used in a way that makes it NOT safe to execute on the branch-taken path? It's always executed before the branch anyway, so it's safe.

What if the andi is placed *after* the sll in source but is *dependent* on the sll (so it can't move before it)? `vol = (vol | 0) & 0xFFFF` isn't dependent on sx. But I could write `vol = vol & (0xFFFF | (sx & 0))`? fold removes sx&0.

What if the mask depends on sx in a way that folds to a constant? E.g. `vol = vol & (sx ? 0xFFFF : 0xFFFF)` — that's a branch. No.

What about `vol = vol & ~(sx >> 31)`? Not equivalent.

Hmm.

Alternative: make the second set be an insn that's a *jump target label* boundary. What if I put the mask after a `if` that creates a label right before it? E.g.:

```
vol = ((0xA0-av)*0x7F)/0xA0;
if (vol >= 0) { vol = vol & 0xFFFF; }
sx = ...
```
This adds a branch (`bltz`/`bgez`) — +1 or +2 insns. But wait: combine/flow may prove vol >= 0? vol = (0xA0-av)*0x7F/0xA0 where av <= 0xA0... gcc can't prove. So a real branch. +1 insn (plus maybe a delay nop). No good.

Hmm, unless the branch folds: `if (vol != 0)`? no.

What about using `&&`/`||` folds? No.

OK, radical idea: maybe the second set doesn't need to be in this function's tail at all. reg_n_sets is per pseudo. What if I make `vol` the SAME variable as one that's already set multiple times elsewhere? E.g., merge `vol` with `sx`! In the target, vol is in $a1 and sx in $a2. If they were the same C variable, they'd share a hard reg — no.

What if vol is the same variable as `t`? t is set twice (func_8004787C, func_80047948) and lives across those calls in $a? Let me look at the target's regs: t = func_8004787C result, used in sp30.x; then t = func_80047948. In the target disassembly, which reg holds t? Let me check. If t is in a register that dies before the tail block, reusing it as vol could work with no extra insns — the div would be the 3rd set. But the live range and allocation would change: vol would be allocated to t's reg, not $a1. Bad.

What about `d` (block-local in the two ifs)? Each `s32 d` is a separate block-scoped variable — two different pseudos. Reusing one as vol... vol is in a later block; the if-blocks' d dies at their end. If vol were the same C variable as d (declared at function scope), then vol's live range would start earlier and it'd be set multiple times. The register allocator might give it a different reg. Risky.

Hmm, hold on. Let me reconsider the c1 approach. c1's problem: cse forwarded so vol had 1 set. What if I make the second set *not* forwardable by putting a function call or a memory barrier between? No.

What if the second set is a *store to a local* through vol? no.

OK, let me try a slightly different c-variant: make the call use `(vol & 0xFFFF)` but assign vol first with a real 2nd set that cse can't forward because the *value differs*:

```
vol = vol | (0x3000 | sx);     // set 2
func_8002D4C8(0xA9B, vol & 0xFFFF);   // uses vol, masks
```
That's e-ish (e4 was 245). Hmm, 245 is way off — maybe because vol's live range changed allocation.

Wait, why would e1 be 245? Let me look at e1's diff to understand. Actually, maybe the +8 is because the `vol` variable became live across... no, it's the same.

Hmm, 245 = 237 + 8. Suspicious: 8 extra could be a different frame/reg allocation. Let me look at e1's diff quickly.
