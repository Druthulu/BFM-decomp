---
ts: 2026-10-22T00:10:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9eEsjsCYgUFRCLWNJmC4
---
Not present in gcc 2.7.2's fold-const.c. So the swap is elsewhere (combine.c or local-alloc.c's combine_regs).

Let me grep local-alloc.c for "swap".

Hmm, actually, let me stop this rabbit hole. Time check: I've been at this a long time. The item is at score 1 (one insn).

Let me make a decision: I'll try TWO more cheap dials, then record the result.

Dial A: the "pointer reuse" catalog move — hmm.
Dial B: change the `+ 4` to be part of a different expression: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` → hmm.

Hmm, what about the ORDER of the two ADDEND expressions in the C: since C requires ptr+int, what if the pointer is the SECOND operand via a cast of the whole sum? Hmm:
`D_801270C8 = *(s16 *)((u8 *)(off + (u32)p) + 4);` — hmm, off + (u32)p is an integer add: the tree = (PLUS (CONVERT off) (CONVERT p))?? hmm, the operands would be (off, p) → p second ✗ (that's mine's order).

Hmm! Interesting: so writing the sum as an INTEGER addition with the index first would give the index-first tree = mine's order. And the ptr+int form gives p first = the target's order. But gcc flips the ptr+int form to index-first. Hmm, so the integer form might stay index-first ✗.

Hmm, unless gcc flips the integer form to p-first (by the same canonicalization) ✓!! Hmm, if the canonicalization is "put the cheaper operand first" and the index (a shift) is more expensive than p (a reg)... hmm, then the ptr+int form (p first, p cheaper) would stay p first ✗.

I'm going in circles. Let me just try the integer-add spelling:
`D_801270C8 = *(s16 *)((u8 *)((u32)p + (u32)off) + 4);`

Hmm, hmm, but (u32)p — the cast of a pointer to u32 on a 32-bit target: gcc would emit a conversion insn? For a register, the conversion Pmode→SImode is a no-op (same size) → no insn ✓.

Let me try it. And also try the variant with the +4 inside: `*(s16 *)((u8 *)((u32)p + (u32)off + 4))`.

Let me do one test with the integer spelling. If it fails → WALL with best=1.

Hmm, hold on. Before that, let me reconsider something: what if the swap is decided by the ORDER OF THE STATEMENTS (the LUIDs) and the "dying pseudo" tie? Specifically: the index is loaded at 79 (late) and used at 84-85; p is materialized at 69-70 and used at 85. Hmm.

What if p's materialization were LATER (e.g. the p assignment moved into the if-block)? Then the tree might flip. But the materialization's position would change ✗ (the target has it at 69-70, and 69-70 is BEFORE the newval load at 71-73).

Hmm, hmm. Wait, actually — is 69-70 really before the newval load? The listing order: 69 lui a1, 70 addiu a1, 71 lui at, 72 addu at,at,v0, 73 lh v0,0(at). Yes, 69-70 before 71-73.

Hmm, but the p variable's assignment in the source is BEFORE the newval load ✓ (in the current C: `D_80195AF6_t *p = D_80195AF6;` then `s16 newval = D_80195AF6[...].f0;`). ✓

So both mine and the target have p's materialization early.

OK, let me try the integer-add spelling and then wrap up this item.
