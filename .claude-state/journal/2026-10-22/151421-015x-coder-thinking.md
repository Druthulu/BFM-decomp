---
ts: 2026-10-22T21:14:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Qa6agMlIExPJQyegSgYQ
---
Now I understand. In the target:

Arm1 (cond1 true): at 1448 `li v0,113` in the branch delay slot (of the beqz at 1444), then 144c: sh v0,32; li v0,1536; sh v0,34; li v0,-80; sh zero,36; sh zero,46; j 14fc; sh v0,48.

So arm1's li -80 IS hoisted to slot 1458, before the sh zero's. So arm1 has the same shape as arm3. Then how does the target have TWO copies?

Wait, in the target, 1448 li v0,113 and 144c sh v0,32 — this is arm1. Then j 14fc with sh v0,48 in delay. Where's arm3? Later at target[49:57] per the diff: at target index 49-56 there's a full body copy. Hmm, the diff indices are insn indices, not addresses. Let me count: target index 0 = 1388. So target[49] = 1388 + 49*4 = 144c. That IS arm1 (144c). And target[56]=1468 sh v0,48.

And the mine[49] region is where mine merged. So the merged arm in mine is arm1 (not arm3!). In mine, at 1444 the test branches `bnez v0,14a0` — arm1's tail jumps to 14a0 which is... a shared block.

Wait, mine 1448 li v0,113, 144c lhu v0,16(sp)... that's cond2's start. So mine's arm1 is skipped via bnez to 14a0. Where's the shared body? Let's see mine fully. Let me read mine from 78 onward.

Hmm, actually mine at 56: `1444: 14400016 bnez v0,14a0` — so if cond1 true, jump to 14a0 (the shared block). Then at 57 `1448: li v0,113` in delay slot... wait that's the delay slot executed regardless. Interesting.

So in mine, arm1's body was merged into a shared block at 14a0 which is arm3's or arm4's? Let me read the rest of mine.

Actually the key point is clear enough: cross-jump merged arm1 with something. The target keeps arm1 at 144c and arm3 elsewhere.

So to defeat cross-jump: make arm1's RTL differ from arm3's. In the target both are: unk20=0x71, unk22=0x600, unk24=0, unk2E=0, unk30=-0x50.

Since the ROM has them separate, the original source must have differed. The most likely difference: in one arm the constant is a variable and in the other it's a literal — but cse would propagate.

Hmm, what makes RTL differ but code identical? The cross-jump in gcc 2.96's jump.c compares the blocks insn by insn with rtx_equal_p, plus it requires the same number of insns. The blocks:

Arm1 (from source): 
sh v0(=113),32; sh v0(=1536),34; sh zero,36; sh zero,46; sh v0(=-80),48

Arm3 same.

If in arm3 I write `unk30 = k;` where k is a *non-constant* variable (e.g., loaded from something, but value known?) — no, then code changes.

Alternative: `unk30 = (s16)(k);` — a SUBREG/truncate of an HImode pseudo. If the pseudo is not propagated (because the cast makes it a distinct pseudo), the RTL store operand is `(subreg:HI (reg:SI k))`. With -mno... hmm, in gcc 2.96 the store of an s16 value into an s16 field: `(mem/s:HI ...)` with operand `(reg:HI ...)`. If k is s16 declared, the pseudo is HImode. Cross-jump sees a reg vs a constant → no merge. And then the code: li v0,-80; sh v0,48. Same insns!

But does cse propagate the constant into k's uses? cse's constant propagation requires a REG_EQUAL note; a local variable assigned once with a constant and never modified gets a REG_EQUAL from... In gcc 2.96, cse does track "reg -> constant" for pseudos assigned from constants (it builds a table). Yes, cse does constant propagation into insns (that's why `k` would be substituted). Hmm. But the current source already has k with the barrier and it worked (score presumably 0 in the tree). Let's check: does the current tree build score 0? Yes, presumably (it's a NEEDED DIFFERS fake, matching).

So in the current tree with the barrier, k remains a register? Well, the barrier is between k's birth and its use, but cse can still propagate... Actually with the asm volatile, cse can't do much but the constant propagation of k into the store is still possible (the asm doesn't reference k). Hmm, but then the store operand would be the constant, and the li would be born at the store, not hoisted. The target has li at 1458, 3 insns before the store at 1464 (in the delay slot).

Hmm. Given both arms have identical instruction sequences, what's actually different in RTL? Let me reconsider: maybe cross-jump doesn't merge arm1 and arm3 but rather arm1's *tail* with arm4's? No, arm4 differs.

Let me look at mine fully to see what got merged. Read mine lines 78-90.
