---
ts: 2026-11-06T10:08:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1rqiNV1l9sX89qDrIg8r
---
Key: "Don't already know about SREG, so tie it to UREG if this is the last use of UREG". So for `(set (reg 77) (and (reg 75) 0xFFF))`, sreg=77 (u6), ureg=75 (s1ang). If s1ang dies at this insn (REG_DEAD), they'd be tied! But the dump shows them separate. Why? Because `reg_qty[sreg] >= -1` — if sreg (u6) already has a qty (because it's used in multiple blocks, it was assigned a qty earlier), then no tie. Right: u6 is used in later blocks, so when the entry block is processed, u6 might already have a qty from... no, blocks are processed in order.

Hmm, the order of block processing in local-alloc: it processes blocks in order 0,1,2,...  In block 0, the andi `(set 77 (and 75 ...))` — sreg=77. Has 77 been assigned a qty? `reg_qty[77]` is -2 (unborn) or -1. If it's a global (multi-block) register, reg_qty is set to -1 by the "global" marking? Let me check: in `local_alloc`, for each pseudo, if it's local (reg_qty >= 0) it's processed; globals get reg_qty = -1? 

Actually, the comment says "If UREG is a pseudo-register that hasn't already been assigned a quantity number, it means that it is not local to this block or dies more than once." So globals have reg_qty < 0 (probably -1). Then `reg_qty[sreg] >= -1` (line 1859) → true for -1 → return 0, no tie. So u6 (global, reg_qty=-1) can't be tied to s1ang. That's why they're separate.

So s1ang is local (reg_qty>=0) and gets s0.

Now, what if s1ang were GLOBAL? Then local-alloc wouldn't assign it; global-alloc would. Its priority (refs 2, live 7) = 2857 < d's 5185. So d gets s0, s1ang gets s1! That's the target.

So the fix is to make s1ang GLOBAL. How? Its live range must span basic blocks. Currently def (lh) and use (andi) are both in block 0.

Idea: make the andi happen in a different block. The target's andi is in block 0 (before the first bne). Hmm.

BUT WAIT: what if s1ang is used in a LATER block too (in addition), making it global, while the andi stays in block 0? That would add a use. Unless the extra use replaces something.

Hmm, what if s1ang's *definition* is in a different block? E.g., load it in a block before... no.

Alternatively: what if `s1ang` is used in the `if (u6 == u5)` and ALSO the code after uses it — but the target doesn't.

Hmm. Alternatively, make s1ang's live range span a block boundary by placing the load before a branch. The only branch is `if (u6 == u5) return 0;`. If the load were before that branch and the use after... but the load is already before.

Wait, what if the source computes u6 BEFORE the call? No, s1ang is loaded before the call.

Hmm, hold on: what if the LOAD is in block 0 and the ANDI in block 0, but the block boundary is created by the `if (u6 == u5) return 0;` — the branch. The andi is before the branch, so block 0.

What if we restructure so the andi is AFTER the branch? The target has andi before bne. But wait — is the andi really before the bne in the target? 
```
3904: sll s0,s0,0x10
3908: andi s1,s1,0xfff
390c: bne s1,a0,391c
3910: sra s0,s0,0x10    (delay slot)
```
Yes, andi before bne.

Hmm. So s1ang's def and use are in block 0 in the target too. So s1ang is LOCAL in the target too! Then local-alloc gave it s1 — contradicting my analysis.

Unless in the target, local-alloc gave s1ang s1 because s0 was taken by another local qty crossing the call. Which one? The target saves s0 and s1 in the prologue, so both are used by callee-saved variables. d is global. Is there another local-crossing qty? 

What about the `d` sign-extension intermediate? insn 55: `(set (reg/v:SI 74) (sign_extend:SI (subreg:HI (reg/v:SI 74) 0)))` — this is a *second set of the same pseudo r74*. Hmm, that's d being reassigned. It's the same pseudo.

What about `u5` (r76)? Born at the call result (r99 → r76 via andi). u5 is used after the call in blocks 1,2,3. It's global. It doesn't cross the call (born after). Actually, r76 is global (multi-block) and gets... the order 78 80 79 77 76 74 — r76 is 5th. In the nopin, r76 (u5) got a caller-saved reg (v0/a0) because its live range doesn't cross a call. In the target, u5 is in a0 (after the call). Fine.

Hmm, so in the target, what took s0? If s1ang is local and the only local-crossing qty, it should get s0. But the target has it in s1. Contradiction!

Unless... the target's local-alloc assigned s0 to a local qty that does NOT cross the call but has a *copy preference* for s0, and that qty's live range overlaps s1ang's, making s0 unavailable for s1ang. Then s1ang gets s1. Which local qty could prefer s0? A qty copied from/to s0. Hmm, the prologue `move s0,a1` — the copy is `d = arg1` where d is the pseudo r74 and arg1 is hard reg a1 (5). That's a copy preference for a1 (5), not s0.

Hmm, what about the `sw s0,16(sp)` — that's the save of s0, no.

Wait, maybe the target's local-alloc assigned s1ang s0 first, and then the *global* d got s1... but the target has d in s0. Ugh.

Let me re-examine the target asm to be 100% sure which is which:
```
38c4: move s0,a1        # s0 = arg1 → this is d (the divisor, set at prologue)
...
38f0: lh s1,18(v0)      # s1 = s1ang
3904: sll s0,s0,0x10    # d = (s16)d
3908: andi s1,s1,0xfff  # u6 = s1ang & 0xFFF
390c: bne s1,a0,...     # if (u6 == u5)
...
394c: div zero,v1,s0    # iVar4 / d
```
Yes: d=s0, s1ang=u6=s1.

So in the target, d got s0 and s1ang s1. Given my analysis (s1ang local → s0), the target must have had a different RTL. 

OH! Maybe in the ORIGINAL, s1ang was loaded and used in a way that made it GLOBAL. What if the original source had `s1ang` used in the `if (u6 == u5) return 0;` condition *and* the return value computation? No.

OR maybe the original had the load in block 0 but the andi in a LATER block. Let me reconsider the target: what if the `andi s1,s1,0xfff` at 3908 was hoisted by sched1 from a later block? No, sched1 works within a block.

Hmm, wait — what if the andi is in the *delay slot* of the bne? No, the delay slot is 3910 `sra s0,s0,0x10`.

What if the block boundary is at the `jal`? Only with nonlocal labels. `ratan2` — could it be declared with a setjmp-like property? No.

Hmm, let me reconsider: maybe the ORIGINAL source didn't have `s1ang` as a variable at all; instead `u6 = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;` computed AFTER the call, and the target's `lh s1,18(v0)` before the call is a *different* load — maybe `lw v0,32(v0)` + `lh s1,18(v0)` were hoisted by sched1 because the call `ratan2` is a *const* function (pure)? If ratan2 were declared `const`, gcc would know it doesn't read memory → loads can be hoisted. Is ratan2 declared const anywhere? The extern is `extern s32 ratan2(s32 a0, s32 a1);`. No const.

Hmm, but gcc 2.7.2's sched1 might not track memory dependencies at all! Let me check: does sched1 in 2.7.2 model memory dependencies? Old gcc sched.c: `sched_analyze_2` for MEM adds `add_dependence` via `true_dependence`? Let me check. If sched1 does NOT model memory dependencies (only register deps), then loads CAN be hoisted above calls! That's a well-known behavior of old gcc: it schedules aggressively without memory deps? Actually, gcc's scheduler has always had memory dependency tracking via `sched_analyze_2`/`memrefs`. Let me verify in the reference source.

Let me grep sched.c for "mem" dependency tracking.
