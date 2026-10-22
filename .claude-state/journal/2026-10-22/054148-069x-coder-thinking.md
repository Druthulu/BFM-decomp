---
ts: 2026-10-22T11:41:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0t3hjoqfy3264akpXGWq
---
Now I can see the RTL:

```
(code_label 459 ...)      <- the join block (after the bgez)
(insn 462: set 201 = 160)
(insn 464: set 200 = 201 - a1)
(insn 467: set 203 = 200 << 7)
(insn 469: set 204 = 203 - 200)
(insn 471: set 206 = 1717986919)    <- the magic constant (0x66666667)!  1717986919 = 0x66666667
(insn 472: set 205 = highpart(204 * 206))
```

So the magic constant (pseudo 206) is set at insn 471, AFTER the vol chain's arithmetic (462-469) and right before the mult.

And the FINAL code has the constant at the TOP of the block (index 198 = lui, before li v0,160 at 200).

So in the FINAL code, the constant's lui/ori is scheduled BEFORE `li v0,160` (insn 462) even though in the RTL it comes after (insn 471).

So the SCHEDULER moved the constant's definition from position 471 to position 462 (earlier)! That's the "2 uses → high priority → scheduled early" behavior.

And in the candidate w4, the scheduler did NOT move it.

**WHY?** Because in the candidate, the constant has only ONE use at sched time! The second use (the sx division) must be a DIFFERENT pseudo (207 or whatever) at sched time, and CSE/reload merges them later.

Hmm, but in the original, the constant 206 is used by insn 472 (the vol mult). Where's the sx division's magic? Let's look further in the RTL. Let me read more.

Actually, the sx division `sx = (sx + 0xA0) / 0x14` uses the same magic 0x66666667 but with a different shift (3). GCC's expansion creates a separate pseudo (e.g. 210) set to the same constant. Then CSE merges 206 and 210.

In the ORIGINAL, the asm (the launder) sits between the two divisions. The asm is a barrier → CSE can't merge across it? No — CSE merges CONSTANTS (same value) regardless of position.

Hmm. But the point is: at SCHED time, is the constant pseudo shared (2 uses) or not?

In the original: the asm's presence... hmm.

**AH, WAIT!** Look at the RTL: `insn 471: set 206 = 1717986919` — the magic constant is a PSEUDO set to a CONST_INT. In the original, this pseudo 206 has 1 set (insn 471) and 2 uses (the vol mult and the sx mult).

The scheduler moved it EARLY (to the top of the block). Why? Because it has 2 uses → priority 2 → scheduled early.

In the candidate w4: the constant also has 2 uses → should also be scheduled early. But it wasn't!

Hmm, so the difference must be elsewhere. Let me look at the candidate's RTL around the same place to compare.

Let me dump the same region in w4d.

Let me find the corresponding line. Let me grep for "1717986919" in w4d.
