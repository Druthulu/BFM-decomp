---
ts: 2026-11-06T10:07:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_X2I21SskUCRN7K32kPVr
---
No REG_ALLOC_ORDER in mips.h → uses the default order (0,1,2,...31) filtered by class. So for GR_REGS: 2,3,4,5,6,...,15,16,17,...  First callee-saved = 16 (s0).

Hmm. So s1ang gets s0 unless s0 is taken.

Let me look at find_free_reg to see if there's a "prefer a reg that's dead" logic or copy suggestions.

Actually, let me look at the "preferences" in the nopin .greg: r77 (u6) "preferences: 16". So u6 prefers s0! That's from local-alloc's combine (the andi's output prefers the input's reg? or the reg that s1ang got). Since s1ang got s0, u6 prefers s0 → u6 gets s0. In the target, s1ang got s1, so u6 prefers s1 → u6 gets s1. So the tie propagates.

So the crux is s1ang → s0 vs s1.

Since s1ang is the ONLY local qty crossing the call, and REG_ALLOC_ORDER gives s0 first... the target must have had s0 taken by something.

OH WAIT. Maybe in the original, s0 was taken by a qty that local-alloc assigned s0 and which then died before the call? No, then it'd be free.

Hmm, actually — hold on. Let me reconsider: maybe in the original, `d` was local-alloc'd! What if d's uses in the division blocks don't make it global because the divisions are in the same *extended basic block*? No, local-alloc uses basic blocks.

Alternatively, maybe the original had the divisor stored on the stack? No, target uses s0.

Hmm, let me reconsider the possibility that the target's s1ang is actually the *global* u6 qty and the local s1ang is a different register. Look at target:
```
lh s1,18(v0)       # load into s1
...
andi s1,s1,0xfff   # s1 = s1 & 0xFFF
bne s1,a0,...
subu v1,a0,s1      # uses s1
addiu v0,s1,4096   # uses s1
addiu v0,s1,-4096  # uses s1
```
So s1 holds u6 throughout. And s1ang died at the andi. So s1ang and u6 are in the same register.

If s1ang (local) got s1, u6 (global) prefers s1 and gets it. That's the target.

For s1ang to get s1, s0 must be unavailable during its live range. The only way: another callee-saved reg (s0) is live during s1ang's range. Since s1ang is the only local qty crossing the call, no.

UNLESS: local-alloc assigns s0 to a qty that does NOT cross the call but has a preference for s0 (copy suggestion). E.g., a qty that is copied from/to s0. Hmm, in the target's prologue, `move s0,a1` — the copy d=arg1 where d is in s0! That's a copy between the pseudo d and hard reg a1 (5), not s0. The dest s0 is assigned later.

What about `sw s0,16(sp)` in the prologue — that's the save, not an allocation.

Hmm.

What if the original had `d` local-alloc'd to s0 via a copy preference, and s1ang to s1? But d is global...

Hold on, let me re-examine whether d is truly global in the TARGET. In the target, `move s0,a1` is at insn 3-4 of the prologue. If d were local, the copy would be in block 0, and d used in blocks 6,7,9 → the live range spans blocks → global. So global.

Hmm, unless the target's d is not a variable but the *argument pseudo* itself, which gcc handles specially. When a function argument is used after a call, gcc creates a copy into a callee-saved register in the prologue via `load_register`/`save_call_clobbered_regs`? No, that's reload.

Actually, there's a mechanism: `-fcaller-saves` and the "pseudo live across calls" → global-alloc. Yes.

OK, I'm going in circles. Let me look at the actual sibling `func_8012B8E4.h` and see if it's in the dedup list with a member that's a *non-header* TU where the function might be lever-free. Actually both headers are pinned.

Let me look at this from a completely different angle: maybe there's a way to make s1ang NOT cross the call while keeping the load before the call — impossible.

OR: maybe we can make s1ang's load happen *after* the call in the source, and the target's load-before-call comes from `sched1` hoisting it because... hmm, sched1 CAN move loads above calls if it can prove no aliasing? Let me check: in gcc 2.7.2, `sched_analyze_insn` adds dependencies for memory refs. A CALL_INSN sets `sched_reg_live` and memory. Let me check whether sched1 treats calls as memory barriers.

Actually, in the target, `lh s1,18(v0)` uses v0 = *(arg0+0x20) loaded at 38e0. If the source order were: ratan2 call first, then `lw v0,32(arg0)` and `lh s1,18(v0)`, then sched1 would need to move BOTH the lw and lh above the call. That requires the call to not clobber memory. GCC's `sched_analyze_insn` for a CALL_INSN: it adds `(clobber (mem:BLK (scratch)))`? Let me check.

Let me grep sched.c for CALL_INSN handling.
