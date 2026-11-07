---
ts: 2026-11-06T10:03:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FNrSLQD8PhFM6YEURNZJ
---
The function name in the .s may be mangled per includer (the header body has a name from the original? Actually the header defines func_8012BA10, so it should appear). But the grep didn't find it — maybe the assembler output uses the address label. Hmm, the .ent labels are func_80128218 etc. The header is instantiated at "each member's site in address order" — the function may be renamed via #define before inclusion. Let me search for "func_8012BA10" case-insensitively or check how the header is included. Actually the header defines `s32 func_8012BA10(...)`. But maybe the includer does `#define func_8012BA10 func_8012XXXX` before the include. Then the .s label differs.

This is a rabbit hole. Let me step back and use the delever_search --explain residual as the guide, and try candidate C bodies empirically. The score is fast.

Let me write 3-4 variants and score them with sc.sh (one line each). sc.sh uses includer 0 (dt.sh's recs[0]).

Variants for item 2:
V1 (nopin.c as written).
V2: s1ang load moved after u5 (so it's after the call).
V3: `s16 d` declared instead of s32.
V4: reorder declarations (d after s1ang).

Actually, a more promising idea based on the alloc analysis: s1ang is local-alloc'd to s0 because it's born and dies in block 0. If I move the *use* of s1ang (u6) into a different basic block, s1ang becomes global. How? Put `u6 = s1ang & 0xFFF;` after a branch... but the target has it right after the call.

Alternatively, define s1ang in a different block: e.g., 
```
if (1) { s1ang = ...; }
```
adds a branch. No.

Hmm, what about moving the s1ang *load* earlier into a conditional? no.

Let me reconsider the local-alloc priority. In gcc 2.7.2 local-alloc, `local_alloc` sorts qtys by `qty_n_refs` descending? If s1ang has refs 2 and there are other local qtys with more refs that also need callee-saved... but those others (u5, etc.) don't cross calls, so they'd take caller-saved first.

Actually, wait. Let me look at the local-alloc code for how it picks the hard reg. It iterates `for (i = 0; i < nregs; i++)` over reg_alloc_order? The first available reg in `reg_alloc_order` for the qty's class. The order for GR_REGS is: 2 3 4 5 6 7 ... 16 17 ... So caller-saved first, then callee-saved. For a qty that crosses a call, caller-saved regs are excluded (they're clobbered), so it picks 16 (s0) first.

To make it pick 17 (s1), s0 must be unavailable. If another pseudo (local, crossing the call, higher priority) takes s0 first. Is there another variable crossing the call? `arg0` is used before the call only (in the address computations) — after the call, arg0 isn't used. So arg0 doesn't cross. Only d and s1ang cross.

d is global (multi-block). So s1ang is the only local one crossing the call → gets s0.

Therefore, to flip, we need d to be local too, or s1ang to be global, or another local pseudo crossing the call with higher priority than s1ang.

Hmm, what if we make d local-alloc-able by making all its uses in the same basic block as its definition? The divisions are in blocks 7 and 9 (the if/else arms). Can't.

What if we restructure so that d is defined *inside* each division block? e.g., 
```
q = iVar4 / (s16)arg1;   // in each branch
```
Then arg1 is used directly (no d variable). But then the `move s0,a1` prologue copy wouldn't exist; instead each div would use a1... but a1 is caller-saved and clobbered by the call! So arg1 must be copied to a callee-saved reg before the call. The copy `move s0,a1` is in the prologue. If we write `d = arg1;` and use d in the divisions, that's the current shape.

What if we write `s16 d = arg1;` — same.

Hmm, what if the *copy* to the callee-saved reg is done by the compiler for a variable that's also used before the call? E.g., if d were used before the call too, its live range starts earlier and it might become global.

Alternatively: what if we make s1ang global by using it in a later block. For example, use s1ang in the `if (u6 == u5)` comparison but compute u6 in a nested block? no.

Hmm, wait. Let me reconsider the possibility that in the original, s1ang's load is AFTER the call, and the target's `lh s1,18(v0)` before the jal is due to *dbr* (delayed branch) moving it? No, the jal isn't a branch with a delay slot filled by a load from the same block... Actually `jal` HAS a delay slot. The instruction in the delay slot is `subu a1,v1,a1` (computed from v1=D_80126B5E loaded before). The `lh s1,18(v0)` is 2 instructions before the jal.

If the source had the load after the call, sched1 would not move it before the call (memory clobber). So the load is genuinely before.

BUT — what if the source had the load in a *different* order such that it's before the call but s1ang is used in a later block? Hmm.

Let me try yet another angle: what if the original used `u6 = s1ang & 0xFFF` where s1ang is a *function argument* or something. no.

OK, empirical. Let me try variants and see the alloc table changes. Actually, the alloc table is the fastest way to see if a variant flips s1ang to global. But each hdump run takes a few seconds. Let me just try C variants with sc.sh and look at scores; if a variant changes the register assignment favorably, the score drops.

Let me think about what would make d win s0:

Option X: Make d's live range start before s1ang's, or make s1ang's qty not need a callee-saved reg.

Option Y: Reduce the number of callee-saved regs available? no.

Option Z: Use a *different* variable for the divisor that is defined in the same block as the divisions but reads a saved arg. Hmm.

Wait — here's an idea: what if we assign `d = (s16)arg1` in the prologue (combining the copy and sign extension), so d's def is the sign-extended value, and the sign extension happens at the prologue? The target has sll/sra at 3904/3910 (after the call), so no.

Option W: What if `s1ang` is declared *after* the call in the source, but its load is hoisted by... no.

Hmm, let me look at the actual original target more carefully. The `lh s1,18(v0)` loads from `*(arg0+0x20)+0x12`. In the source, `s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);` — note `*(s32 *)(arg0 + 0x20)` is loaded into v0 at 38e0 (`lw v0,32(v0)`), then `lh s1,18(v0)`. 

Now, the u5 computation uses arg0's fields 0xE and 0x6 and globals. The `lw v0,32(v0)` happens at 38e0, before `lh s1,18(v0)` at 38f0.

If the source were:
```
u5 = ratan2(...);
u6 = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;
```
then the load would be after the call. But maybe sched1 hoists `lw v0,32(v0)` and `lh s1,18(v0)` before the call because... hmm, the call clobbers memory, so no.

Actually, WAIT. Does gcc 2.7.2 consider a call to clobber memory by default? In gcc, `init_call_insns` sets `(clobber (mem:BLK (scratch)))` for calls. Yes, memory is clobbered. So loads can't move across.

Unless `ratan2` is declared with `const`? No.

So the load is before the call in source order. Confirmed.

OK, let me try the empirical approach now. Write variants:

V2: `s32 d; s32 s1ang;` but move the `d = arg1;` assignment AFTER the s1ang load and u5 computation (so d is defined after the call). Then d doesn't cross the call → d gets a caller-saved reg? But the target has d in s0 across the call. So no.

V3: Swap: `s1ang` assigned after `d = (s16)d`. no.

Hmm, let me think about what makes s1ang global: if the load is in block 0 and the use in block 1 (after a branch). What if we write:

```
if (u5 == u6) return 0;  // uses u6 before
```
No, u6 is computed before that.

What if we compute u6 lazily inside the if? no.

Alternatively, make s1ang's *use* be in the divisions (later blocks) rather than before. E.g.:
```
if ((s1ang & 0xFFF) == u5) return 0;
iVar4 = u5 - (s1ang & 0xFFF);
...
```
Then s1ang is used in the entry block (the comparison) — still block 0.

Hmm.

Let me look at this from the other side: maybe the target's s1ang is NOT local-alloc'd; maybe it IS global with a priority higher than d's, and in the target the order is s1ang then d? But then s1ang would get s0 (wrong; target has s1ang in s1).

Unless the register allocation order in the target has d first. d pri 5185 > s1ang 2857 → d first → s0. Yes, that's what I computed. So IF s1ang were global, the target allocation results. So the question remains: how to make s1ang global?

In gcc, a pseudo is "local" if it is born and dies within one basic block. s1ang's def (lh) and use (andi) are both in the entry block (block 0), which spans the call. So it's local.

BUT: is the call a basic block boundary? In gcc, `NOTE_INSN_FUNCTION_BEG`, calls don't split blocks. However! There's a subtlety: `flow.c` splits blocks at calls? No.

Hmm, but what about the `if (u6 == u5) return 0;` — that's after the use. The use (andi) is before the branch.

Wait, maybe in the original source, u6 was computed inside the `if` condition, e.g.:
```
if ((s1ang & 0xFFF) == u5) return 0;
```
Then the load and the andi are in block 0, and the branch follows. Still block 0.

Hmm.

Let me reconsider: maybe the target was produced with s1ang NOT crossing the call — i.e., the `lh s1` is a *hoisted* load and the `andi s1` is... no.

Alternatively, maybe s1ang doesn't cross the call because the load is a *separate* pseudo that dies before the call, and the *andi* uses a different value? No: `andi s1,s1,0xfff` reads s1 which was loaded before the call. So it crosses.

Hmm, unless there's a `move` in between. No.

Let me look at the actual target .greg-equivalent: I can't easily get the original's RTL.

New idea: maybe the difference is that in the original, `d` is NOT global either, and the s0/s1 assignment came from local-alloc assigning d to s0 (local!) and s1ang to s1. For d to be local, its uses must be in its def block. Not possible.

Hmm hold on, maybe the *whole* d variable is a single qty that local-alloc handles because gcc's local-alloc handles multi-block pseudos when `-f...`? Let me actually check: local-alloc processes pseudos whose live range is within a block, but ALSO `local-alloc` assigns regs for pseudos that are live across blocks if... no, those go to global.

Let me look at the local-alloc code to see how it decides. Actually, let me check the alloc table's "blk" column: r75 has blk 0 (local). r74 blk None (global). Yes.

So: to make s1ang global, its use must be in a different block from its def. Can I introduce a block boundary between the load and the use *without changing the target code*? A block boundary can come from a branch. The target has a `bne` after the andi — so the andi is in the block before the branch. If the andi were moved to AFTER the bne (i.e., in a later block), the code order would change: bne first, then andi. Target has andi before bne. Hmm.

But wait — could the andi be in a block that's after the call but before the branch, where the block boundary is the *call*? If gcc treats calls as block boundaries in some mode... Let me check gcc 2.7.2 flow.c: `find_basic_blocks` — it ends a basic block at any insn that is a `JUMP_INSN`, `CALL_INSN`, or `CODE_LABEL`. Let me check! In old gcc, calls DO end basic blocks? Hmm, I recall basic block boundaries at labels, jumps, and calls (because calls can throw / for exception handling). Let me grep flow.c.
