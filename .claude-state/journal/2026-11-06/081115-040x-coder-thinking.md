---
ts: 2026-11-06T15:11:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gldMQGIypKpG8AQqpyna
---
Time: 08:10. Item started 08:00. So only 10 minutes elapsed! Great — I have more time than I thought (the clock is the wall time; my earlier reasoning about 30 min was wrong).

So I have ~20 more minutes on item 1.

h1 compile error: probably declaring `s32 vol = ...` mid-block after statements is fine in gnu89... The error message truncated. Whatever.

Let me think again with fresh eyes, since I have time.

The structure: target's fall-through block starts with the sll (speculated). Mine's starts with the andi.

reorg.c fill_simple_delay_slots: it scans insns after the branch. For each candidate it checks `eligible_for_delay`, and importantly it stops at the first insn that is not eligible OR that is "needed before the next label". Actually the algorithm: it looks at `next_trial` insns in order; a candidate must be `eligible_for_delay (insn, ...)` and `! insn_references_resource_p` conflicts, and the insn must not be "used" on the path.

Key: reorg fills the delay slot with the insn *immediately after* the branch if eligible, else tries others. Mine's insn immediately after the branch (in the fall-through block) is the andi — meaning sched1 placed the andi first in that block!

Why would sched1 place the andi first in the fall-through block? Because the fall-through block (the ==16 path) is: `li a2,15; sll a2,a2,0x8` — that's tiny. The andi can't be in it.

Unless... the block structure is different: maybe the andi IS in the branch block (before the branch) and reorg moved it into the delay slot as part of "fill from the branch's own block" — reorg does have code to move an insn from before a branch into its delay slot when the branch is a forward branch and the insn is not needed on the path... Yes! reorg.c `fill_simple_delay_slots` has a section for "the delay slot is filled by an insn before the jump" — it's `fill_eager_delay_slots`? Actually, in reorg.c, for a conditional jump, `fill_simple_delay_slots` fills from the fall-through. But there's also `optimize_skip`... Hmm.

There's a known reorg feature: if the branch is a "conditional return" or the jump is at the end of a block, reorg may move an insn from *before* the jump into the delay slot if that insn is not needed on the branch-taken path ("fill from the block"). That's `fill_slots_from_thread`.

If so, moving the andi from before the branch into the delay slot requires it to be dead on the taken path — but vol is used on both paths (in the call). Hmm, no: the andi result (vol) IS used later on both paths, so it can't be moved... unless reorg duplicates it (it does "steal" insns and re-inserts them on the other path).

Given the listing: mine 4b84 andi (delay), 4b8c sll. There's no second andi later except the final mask. So the andi was moved from before the branch into the delay slot — which is fine because the delay slot is executed on both paths.

That means reorg "stole" the andi from the branch block into the delay slot. Target instead stole the sll (from after the branch, since target's branch target is 4b90 = after the shift).

In target, the taken path jumps to 4b90 — i.e. the branch's target skips the sll at 4b84... but the delay slot executes, so the sll is applied on both paths. Good.

In mine, the branch target 4b8c = the sll, so the shift happens on the taken path there, and the delay slot holds the andi.

So: if the andi were NOT stealable (e.g. it's needed in the branch block itself, or it's a "sets_cc0" / uses a resource), reorg would instead steal the sll.

What makes an insn ineligible for a delay slot in reorg.c? `eligible_for_delay`: not a jump, not `sets_cc0_p`, not using a register that the branch target needs... Also insns that "may_trap_p", or that are `use`/`clobber` insns, or `JUMP_INSN`, or `asm` (asm insns are ineligible for delay slots in gcc 2.7.2! `if (GET_CODE (insn) == INSN && ... asm_noperands (PATTERN (insn)) < 0`).

AH HA — that's why the launder asm could not be stolen, and it stayed in the block. But the launder is zero-width so it emits nothing.

So a 2nd set that is an `asm`... not allowed (that's the launder).

What plain-C insn is ineligible for a delay slot? A load into a register? No, loads are fine on MIPS (with the load-delay handled by `eligible_for_delay` checking `dbr_sequence_length` and the load delay...). In gcc 2.7.2 reorg, `eligible_for_delay` for MIPS: an insn that sets a register which is used by the next insn (load delay) is not eligible... Hmm.

Alternatively: make the 2nd set an insn that conflicts with the branch's operands. The branch is `bne a2,v0` — uses a2 and v0. If our extra insn *sets a2* or *sets v0*... it wouldn't be safe.

Hmm! What if the vol 2nd set writes to a register that the branch uses? Can't control.

Another angle: what if the extra insn is a *store*? Stores are eligible on MIPS (with proper addressing).

What if the extra insn is `mfhi`? mfhi/mflo can't be in a delay slot (hilo hazard) — reorg checks `hilo_delay`? Hmm.

What if the extra insn is a `mult`? A mult in a delay slot is legal on R1000? The target has a `mult` in... no.

OK, different approach: make the andi's *result* needed before the branch (so it can't be stolen). I.e. use vol between the cast and the branch. E.g.:

```
vol = (u16)vol;
if ((sx == 0x10) && vol >= 0) { ... }   -- changes semantics? vol >= 0 always true. Hmm, adding a condition changes the CFG.
```

What about: `if (sx == 0x10) sx = 0xF;` → make the condition use vol in a no-op way: `if ((sx ^ (vol & 0)) == 0x10)`? That's an identity launder-ish (not allowed).

What about ordering: compute vol's cast, then use vol in a statement before the branch that doesn't change semantics... e.g. move the call arg computation? No.

Hmm, what about: make the branch condition depend on vol in a value-preserving way that's natural? Not natural.

New approach: make the extra insn the *first* insn after the branch so it's stolen anyway... no.

What if the extra insn is `sll a2,a2,0x8` itself?! I.e. give the pan shift a 2nd set: `sx = sx << 8;` already; what if we write `sx = sx << 4; sx = sx << 4;`? That's 2 shifts, and target has 2 slls... but target's 2 slls are the same shift duplicated by reorg.

Interesting: if I write `sx = sx << 4; sx = sx << 4;` the code has 2 slls (8 insns total +2 = 239). Hmm no.

OK, think about it from the allocation side: maybe I don't need the extra insn at all if I can get sched1 to order vol's mult first by another means. The plain drop has pan first. What determines it? Both mults are independent; sched1 picks by priority. The vol chain: subu v0,v0,a1 (0xA0-av) → sll v1 → subu v1 → mult. The pan chain: addiu v0,a2,160 → mult.

In the target, the vol mult comes first. In plain drop, the pan mult comes first (at 201) and vol's at 207.

Note in plain drop, mine had `addiu a0,a3,160` at 200 and `mult a0,a2` at 201 — so the pan mult directly after. And vol's `mult v1,a2` at 207.

What if I make the pan chain start EARLIER in source (compute sx first) — then it'd be even more likely first. Reverse: make vol's chain shorter so it's ready sooner? 

What if I move the `vol = ...` computation BEFORE the `av` computation? Can't (needs av).

What if I compute the numerator earlier:
```
s32 num = (0xA0 - av) * 0x7F;   /* after av */
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
vol = num / 0xA0;
```
Hmm, that moves vol's division after the pan — probably pan first again.

Alternatively make the vol chain the only long one... 

What if `av` is computed without the branch (using abs)? That changes insns.

Hmm, what about the ordering of the two mults being driven by the "match_scratch" sharing? Both divisions by constants use the same scratch? The comment says "Both magic-multiplies write the same match_scratch". The magic 0x66666667 in a0 is shared.

In target, the lui/ori (magic) is at 4b34-4b38 BEFORE both mults, then vol's mult, then pan's. In plain drop: lui/ori at 198-199, pan mult at 201, vol mult at 207.

What if the magic is materialised per-use (two lui/ori pairs)? That'd be +2 insns.

OK here's another thought experiment: the launder asm is a use+def of vol at a point between the vol computation and the pan computation in the *instruction stream*. sched1 must schedule the asm insn; asm insns have HIGH priority in sched1 (they're treated as having a large priority / they're "SCHED_GROUP"?). In gcc's sched.c, `priority()` gives insns in a `asm` a boost? Actually there's special handling: `if (GET_CODE (insn) == INSN && asm_noperands(...))` — hmm.

Since the asm can't be moved past the pan computation? Actually it CAN (independent).

Since the asm must be scheduled somewhere and sched1 places high-priority insns early, placing the asm early forces vol's computation before it. That's the mechanism: the asm has high priority.

Plain C: is there any statement with an inherently high sched1 priority? An insn whose "depth" to the end of the block is long. The vol chain's end (the asm) had a long path to the block end (through the call? no, the call is in a later block?).

Hmm, what if the cast is placed such that the andi's path to the block end is long, i.e. it's used by the call... it is (vol used in the call arg, which is in the same block? The call is after the if — different block).

Alternatively: make the vol value needed *before* the branch by the branch itself? 

What if I restructure so the `if (sx == 0x10)` comes AFTER the call? No, semantics.

What about computing `sx << 8` BEFORE the if and adjusting the if's constant:
```
sx = (sx + 0xA0) / 0x14;
sx = sx << 8;
if (sx == 0x1000) { sx = 0xF00; }
```
Now the branch is on the shifted value; the delay slot could be filled by the call setup. Target's insns: `li v0,16; bne a2,v0` — the compare is against 16 (unshifted). With this rewrite the compare would be against 0x1000 and the sll before it. That changes the instruction sequence. Probably not matching.

I think I should look at how similar launder items were cracked: moves.md line 187 (func_8018CDEC): "the launder tied-output on sc -> empty do { } while (0)". Line 189: "launder (tied output + m(pad)) -> do { } while (0) + v0 = (s16)v0 (a real 2nd set)".

For this item, maybe the equivalent is: `do { } while (0)` somewhere that splits the EBB so sched1 keeps vol's mult first, AND something to restore the 237th insn.

Let me check what c_dw (empty do-while at the launder position) looked like: 236, score 16. Its diff might reveal a near-miss structure. And what if I combine do-while + a 2nd set elsewhere?

Actually! Key: 236 vs 237. The target's extra insn is the duplicated sll (reorg speculation). If the delay slot is filled by the sll (speculated), we get +1. In c_dw (empty do-while), maybe the schedule is right but reorg doesn't speculate.

Let me look at c_dw's diff.

Time: 08:12. OK.

Let me dump c_dw's tail via --keep... that costs a compile. Instead, run dt with tail 400 and read.

Let me look at c_dw and c_f1 diffs.
