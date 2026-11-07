---
ts: 2026-11-06T04:36:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xwASkvItqkVXhXe6xhnh
---
Tie-break: (1) priority, (2) class relative to the last scheduled insn (data-dependent > anti/output > independent), (3) INSN_LUID (original order; stable, minimizes movement).

So after scheduling the last chain insn (sll at 4940), the next candidates: addiu (data-dependent on the sll, class 1) and lw p (independent of the sll, class 3, OR anti-dependent on the addu). Class 1 (addiu) beats class 3 (lw p) → addiu scheduled first. That's why!

In the TARGET, the lw p came before the addiu. For that, the lw p must be data-dependent on the last scheduled insn (the sll) — impossible — OR the addiu must not be data-dependent (e.g., the addiu depends on something else / is scheduled elsewhere).

Hmm. So the target's order (lw, addiu) suggests that after the sll, the lw p was data-dependent on the last insn (sll). The lw p's address is a0 (s1), independent. Unless the last scheduled insn before the lw was NOT the sll but something else.

Target order: 4938 sll; 493c addu; 4940 sll; 4944 lw; 4948 addiu; 494c sh. After the sll at 4940, the addiu is data-dependent (class 1) and the lw is independent (class 3). By rank, addiu should be first. But the target has lw first! So the target's lw p must be data-dependent on the sll at 4940, i.e., the lw's ADDRESS depends on the sll result?! That can't be (address a0).

OR the sll at 4940 is not the last scheduled insn before the lw; maybe the lw was scheduled at a different T with the sll... Hmm.

Wait, maybe in the target, the p load's priority is HIGHER than the addiu's. Priority: addiu → sh = 2 (sh is the only dependent). lw → sh = 2. Equal. Unless the p load also feeds something else (e.g., p is used twice). In the target, p at 4944 is used only by the sh at 494c. So priority 2.

Hmm, but maybe the target's `sh` at 494c is in the SAME basic block as the arm (no label between), so both are in-block and the priorities are 2. And the class: after the sll, addiu class 1, lw class 3 → addiu first. Still.

Unless the scheduler scheduled the lw BEFORE the sll: e.g., order sll(4938), addu(493c), lw(4944), sll(4940)? No, the final order is sll, addu, sll, lw.

Maybe the scheduler scheduled: sll, addu, then at the next cycle the lw (independent, class 3) and the sll (data-dependent on addu, class 1)... it should pick the sll. Hmm.

I'm clearly missing something about the target's schedule. Let me check whether the target's p load is actually `lw v1,32(s1)` — yes.

Given the time (21:36), and that I have 40+ tries, let me check the 20-min rule: item 4 started at ~21:22 (after item 3). It's 21:36 → 14 min. Need 20 → until 21:42. Let me continue a bit.

Actually, maybe I should reconsider: is item 4's start really 21:22? The date at the first item-4 command was after item 3's notes. Item 3's end: I didn't print a date. Item 2's end ~21:16 (date 21:09 during item 2, then ~7 min). Item 3 was quick (~5 min) → ~21:22. Item 4 started ~21:22. Now 21:36 → 14 min. Need ~6 more min.

Let me try a few more variants around z8 to fix the lw/addiu order:
- z11: give the p load a higher priority by using p twice after: e.g., the store `((Unk*)p)->unk18 = v;` uses p once. Add a dead use? 
- z12: make the addiu not data-dependent on the sll: compute `v = v + 0x600` BEFORE the chain? e.g., `v = 0x600; ...` no.
- z13: make the addiu depend on the p load: e.g., `v = v + 0x600;` where 0x600 is loaded via p? no.

Alternatively, make the lw p data-dependent on the last chain insn by making p's address depend on v — fake.

Hmm, what if the p load and the addiu are in a different order because the addiu's birth is LATER than the lw's in the target? The tie-break by LUID (original order) applies when class is equal. If both were class 3 (independent of the last insn), the LUID order would decide. The lw's LUID vs addiu's: in the target's RTL, if the lw was born before the addiu, the lw wins. In z8, the source is p then add → lw born before addiu. But the class difference (addiu class 1) overrides. To make the addiu class 3 (independent of the last sll), the addiu must not depend on the sll. But it does (v+0x600).

What if we compute the +0x600 as part of the multiply chain differently so the final chain insn is the addiu? E.g., `v = (p * 3 * 32) + 0x600;` — the final insn is addiu, and the lw p is independent. Target order: sll, addu, sll, lw, addiu. If the chain is sll, addu, sll, addiu (all data-dependent), the scheduler would do the whole chain first, then the lw. That gives sll, addu, sll, addiu, lw — not target (lw before addiu). Hmm.

What if the +0x600 is applied via an addiu whose operand is a *separate* temp? e.g., `s32 w = v + 0x600;` then store w. Same.

The target's lw-before-addiu is unusual. Let me look at the target's dependency: 4940 sll v0,v0,0x5; 4944 lw v1,32(s1); 4948 addiu v0,v0,1536; 494c sh v0,24(v1). The addiu depends on the sll (data). The lw is independent. By rank, the addiu should be scheduled at 4944 (class 1) and the lw at 4948 (class 3). But the target has the reverse! Unless the scheduler's class computation: the "last_scheduled_insn" at that point is the sll; the addiu is data-dependent → class 1; the lw → class 3. Rank prefers the HIGHEST class number! Let me re-read: "Choose the insn from the highest numbered class if different." Class 3 > class 1! So independent insns (class 3) are preferred over data-dependent (class 1) when priorities are equal! 

Wait, that means the scheduler prefers to fill with independent insns (to avoid stalls) — class 3 wins. So the lw (class 3) should be scheduled BEFORE the addiu (class 1) — matching the TARGET! But z8 got addiu first. So in z8, the lw must NOT be class 3; it must be class 2 (anti/output dependent) — because of the p reuse! The p reload has an anti-dependency (write p) with the previous p value used by the addu (last scheduled? no, the last scheduled is the sll). Hmm, the lw p writes p; the last scheduled insn (sll) doesn't read p. So class 3.

Unless the lw p's priority is LOWER than the addiu's. Priority: addiu → sh = 2; lw → sh = 2. Equal. Hmm.

Wait, maybe in z8 the lw p's priority is 1 because the sh is in a different block (the label between). Then addiu (priority 2) wins. In the target, the sh is in the same block (no label at sched1 time), so the lw's priority is 2 and class 3 beats class 1 → lw before addiu. THAT's the difference!

So the key: at sched1 time, the merge store `sh` must be in the SAME basic block as the `<0x11` arm, with no label between. In our build, there's a label at the merge (from the other arms' jumps). In the target's original, the label at 494c must have been created AFTER sched1 (by jump2/reorg), meaning at sched1 the merge store was in the same block as the `<0x11` arm.

How to make the merge store in the same block as the `<0x11` arm at sched1? The label exists because other arms jump to the merge store. If the merge store were reached only by fall-through from the `<0x11` arm, and the other arms had their own copies of the store, then no label. But the target has ONE shared store (494c) with jumps to it. Hmm, but those jumps could be created by jump2's cross-jump from duplicated stores! The comment in the source says: "This arm writes its own 0x18 store and skips the shared tail; in the target it lands on the opposite register pair (`sh $v1,0x18($v0)`), which is precisely why cross_jump could not fold it into .L8018121C." — so the decomp author knows cross-jump behavior.

Maybe the ORIGINAL C had the 0x18 store duplicated in each arm (not a shared merge), and jump2/cross-jump merged some of them into the shared 494c, but NOT the else arm (different registers). If each arm has its own store, then at sched1 there's no shared label; each arm's store is at the end of its block. Then the `<0x11` arm's p load and store are in the same block → priority 2, class 3 → lw before addiu! That matches!

But the target shows the other arms' stores at 48bc, 48d4, 48fc (in the delay slots of jumps to 494c) and the shared store at 494c. So at sched1, each arm's store was separate, and jump2 cross-jumped them into 494c. The `<0x11` arm's store (494c) is the "merged" one (the fall-through), and the other arms' stores were moved into their jump delay slots by reorg.

So the original C likely had the store duplicated in each arm! Let me restructure: give EVERY arm its own `((Unk*)p)->unk18 = v;` and remove the shared merge store. Then:
- n<8 arm: v=n*3*128; p=model; store 0x1A; store 0x18.
- n<0x16: v=0xC00; p=model; store 0x1A; store 0x18.
- ==0: store 0x1A raw; p=model; v=0x1200; store 0x18.
- <0x11: store 0x1A raw; p=obj->1C... (with the p reuse); v=...; p=model; store 0x18.
- else: store 0x1A; store 0x18; goto call (or fall through).

Then jump2 cross-jumps the identical stores. Let me try! This is a real restructure and plausible as the original C.

Let me build from z8 (which has the p reuse in `<0x11`). I'll add the store to each arm and remove the shared one.

z8 structure (lines):
- 31-39: n<8 arm
- 40-43: n<0x16 arm
- 44-52: ==0 arm
- 53-63: <0x11 arm
- 64-70: else arm
- 71: shared store
- 72: call label

Let me view z8 fully to edit precisely.
