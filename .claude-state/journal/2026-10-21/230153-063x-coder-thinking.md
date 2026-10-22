---
ts: 2026-10-22T05:01:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_f0mSFi07S265aibA4Inm
---
The target tail:
```
801537a4: sb v0,222(s0)      <- the u8 decrement store
801537a8: lh a0,6(s0)        <- load temp 1 in a0 ($4)
801537ac: lh v1,160(s0)      <- load temp 2 in v1 ($3)
801537b0: nop
801537b4: bne a0,v1, 801537e4   <- if not equal -> the epilogue (return 1)
801537b8: li v0,1            <- the "r = 1" in v0 ($2) -- in the delay slot!
801537bc: lh a0,10(s0)       <- load temp 3 in a0
801537c0: lh v1,162(s0)      <- load temp 4 in v1
801537c4: nop
801537c8: bne a0,v1,801537e4  <- if not equal -> the epilogue (return 1, v0 still 1)
801537cc: nop
801537d0: lh v0,14(s0)       <- load 5 in v0 ($2)
801537d4: lh v1,164(s0)      <- load 6 in v1 ($3)
801537d8: nop
801537dc: xor v0,v0,v1       <- the compare
801537e0: sltu v0,zero,v0    <- the boolean in v0 ($2)
801537e4: (the epilogue)
```

KEY: `li v0,1` is in the DELAY SLOT of the first `bne` (801537b4), and it's on the "not equal" path (the branch target 801537e4 = the epilogue) → so v0=1 is the "return 1" value ✓.

So the structure: the value `r` = 1 by default, and if both comparisons are equal, r = (load5 != load6).

Crucially: the load temps use a0 ($4) and v1 ($3), and the value uses v0 ($2).

In mine (vV2_direct), the loads use v1/v0 ($3/$2) and the value uses a0 ($4) — i.e. the allocation is shifted.

So we need the RESULT_DECL (or `r`) to take $2 and the load temps to take $4/$3.

The loads: `lh a0,6(s0)` and `lh v1,160(s0)` — the first load in a0, the second in v1. Interesting: the loads alternate a0/v1 — like the mips convention (a0 = first operand, v1 = second?) — this is the "load pair" convention: gcc's mips backend allocates the two operands of a comparison to specific regs? Actually `lh a0` / `lh v1` — hmm.

In mine: `lh v1,6(s0)` and `lh v0,160(s0)` — the same pattern shifted down by one reg.

So the whole allocation is shifted: mine uses ($3,$2) where the target uses ($4,$3). The value: mine $4, the target $2.

Hmm, interesting: in mine, the value (the RESULT_DECL) got a0 ($4) — the lowest free reg? And the loads got v1/v0.

In the target, the value got v0 ($2) and the loads got a0 ($4)/v1 ($3) — leaving $2 for the value.

So the difference is: the RESULT_DECL must get $2 (v0), and the load temps get $4/$3.

Per the notes: the RESULT_DECL (pri 10000) ties with the load temps (pri 10000) and loses the allocno tie-break (the temps have lower allocnos → they win $2).

To win: the RESULT_DECL needs a higher priority than the temps, or a lower allocno.

How to lower the RESULT_DECL's allocno? The RESULT_DECL pseudo is created... in gcc's RTL, the RESULT_DECL's pseudo number is assigned when the function's result decl is created (early, at gimplify). But the notes say "the RESULT_DECL is born at the return" — the copy to the RESULT_DECL happens at the return statement → the pseudo is created at the RTL generation of the return.

Hmm. In gcc 2.7.2, the RESULT_DECL is a DECL created at the start of the function; the RTL pseudo is created when the first "set RESULT_DECL" is expanded (at the return statement). So its pseudo number is high (late).

To lower it: an earlier return statement! E.g., a return earlier in the function → the RESULT_DECL pseudo would be created earlier → a lower allocno → it wins the tie ✓✓✓.

Hmm! Interesting. But the function's early return is `return 0;` inside the `if (q < 0x40 ...)` block:
```
if (q < 0x40 || *(u8 *)(s0 + 0xDE) == 0) {
    func_80015954(s1, s2);
    return 0;
}
```
That `return 0` IS earlier! So the RESULT_DECL should be created there... Hmm, but the notes say it's born at the return (the tail). Hmm, maybe gcc's RTL expansion creates the RESULT_DECL pseudo at the first return → the `return 0` in the middle → its number would be lower than the load temps (which are at the tail) ✓.

Hmm, but the notes say the temps won. Let me get the actual dump for this item and look.

Let me dump the current best candidate (vV2_direct) and read the alloc table. I need to set up a dump work dir for this item (like mkdump.sh but for this item/TU).

The TU for the header: the tool's scratch name will tell. Let me run --keep on vV2_direct to get the scratch dir, then build the dump work dir.

Let me generalize mkdump.sh into a per-item script. I'll write one script under G08b that takes the item dir.

Let me do it.
