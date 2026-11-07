---
ts: 2026-11-06T09:17:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xELyOC9qKb3OxbrRvoCT
---
Worse (13). So pin+keepalive matter.

Let me think again. Perhaps the intended "real C move" is to move a genuine use of bVar1 after the test. Wait — is there a genuine use? Look at the source: `bVar1` is read at line 17 and used at lines 36, 39, 44. What about using bVar1 in the *second* branch (uVar2==1)? No.

Alternatively, maybe restructure the &0x10 test to read bVar1 through a value that's live: e.g., define `u8 b = bVar1;` at the top and use `b` for the last test; b's live range... same.

Hmm, let me reconsider whether the andi destination is really about liveness. Compare w1 mine: `andi t0,t0,0x10` at 65 (early, right after mult). Target: `andi v0,t0,0x10` at 69 (late). The destination and the schedule both differ. With the keepalive, the andi is v0 and scheduled late (at its use). Without, t0 and scheduled early.

Scheduling early: sched1 moved it up because no dependency. With the keepalive, why is it late? Because the asm use of t0 right after... hmm the asm is *after* the andi in source, so t0 is live across the andi; scheduling the andi earlier than the mult would extend v0's live range but that's allowed. sched1 orders by priority; the andi's birth priority maybe lower.

Let me test a candidate: use `if ((bVar1 & 0x10) != 0)` but with a *real* later use of the AND value. For instance:
```
u32 m = bVar1 & 0x10;
if (m) *(s16*)(param_1 + 0xa) = -sVar5;
...
iVar7 = fc + zr;
```
If `m` were used again later, e.g. in the fc block condition... but that changes semantics.

Hmm hold on. Let me reconsider the possibility that the real C keeps bVar1 alive because the compiler *itself* keeps a register variable live to the end of the block. In GCC 2.7.2, a `register` variable declared with an explicit hard register — its pseudo is a "local reg" with the hard reg. Local alloc assigns it. The live range is determined by uses. So no.

Let me look at what the keepalive asm compiles to: empty asm with "r" operand -> in GCC, `asm` with a register operand: the operand is used; an empty template produces no instructions but the USE. It may also prevent the register allocator from reusing t0.

Alternative real-C: could we get the same effect by *ordering* statements so that bVar1's last use is naturally later? What if we reorder the &0x10 test to *after* the `fc` load but before the fc comparisons? Target order: &0x10 test (69-73), then `lh a1,12(a2)` (74), `lh a0,14(a2)` (75). The fc load at 74 comes after the &0x10 store. So source: &0x10 test, then fc = load. bVar1's last use is the &0x10 test. Still dead after.

What if the source computed the +0xa store using a helper expression that also references bVar1 later? E.g.:
```
if ((bVar1 & 0x10) != 0) { *(s16 *)(param_1 + 0xa) = -sVar5; }
```
versus
```
*(s16 *)(param_1 + 0xa) = (bVar1 & 0x10) ? -sVar5 : sVar5;
```
The latter might generate a different sequence (branchless?). Not target.

Hmm, maybe the &0x10 test in the target comes from a different source expression: `if ((bVar1 & 0x10) != 0)` is natural.

Let's consider that maybe bVar1 is not the only thing the keepalive affects: the keepalive's `"r"(bVar1)` also forces bVar1 into a *register* (it is already). The asm operand might create a new pseudo? In GCC, an asm operand "r" on a register variable uses the register.

Alternatively, maybe we can keep t0 live with a genuine *second* use of bVar1 that the target also has: is there any chance the target's `li t1,153` at insn 21 relates? No.

Let me look at the pre-keepalive history: maybe P36 notes recorded what was tried. Search logs? We're told not to read phase-ends/*/logs/. But maybe moves.md has func_8013A530. grep.
