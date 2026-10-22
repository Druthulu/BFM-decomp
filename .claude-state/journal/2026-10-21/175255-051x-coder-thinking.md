---
ts: 2026-10-21T23:52:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HzsGhlbBjTbmJuLQJO8n
---
Variant A (inline constants) produced the SAME code as nopin (one pseudo for all four constants — gcc reused a single register $2 for the four constants, and the "li v0,9/17/41/10" are all $2). So gcc creates ONE pseudo reused for the constants (because they're all "the constant being compared"), or 4 pseudos sharing $2.

Note: in variant A, gcc has 4 separate pseudos each with 1 set + 1 use, yet they all landed in $2 — so the allocation is NOT qty-based (or the qty of each is 2 but they're still preferred). Hmm, but they all share $2 → they're sequential and gcc reuses.

Hmm, so in variant A, is there ONE pseudo (gcc's "combine" merging) or four? If four pseudos each got $2, then the "1"-pseudo (folded) got nothing, and $2/$3 assignment is free. The result: the constants got $2.

What if I could make the constants get $3 by putting something else in $2 in that block...

AH WAIT. What about the possibility that the mask test's AND result should be in $3 and the constants in... no, the target has the AND result in $2 (ins 17-19: lh v0,174(a1); andi v1,a3,0xffff; and v0,v0,v1 → the AND result in $2, the andi in $3!). Interesting: the target has the `andi v1,a3,0xffff` (arg3 & 0xffff) in $3 and the AND result in $2.

And in mine (nopin), the same head (ins 0..19 match exactly!) — so mine also has the AND result in $2 and the andi in $3 ✓. So the head is identical.

Then at ins 20, the ROM has `bnez v0,+0x90` with the delay slot `li v1,9` — so $3 (v1) is used for the constants AFTER the andi's use of $3 ended ✓ (the andi at ins 18 is dead after ins 19).

In mine: `bnez v0,6ac4` with the delay slot `move v0,zero` — the delay slot fill differs, and the constants get $2.

Why would mine's delay slot be "move v0,zero" while the ROM's is "li v1,9"? Because in mine, the branch at 20 goes to the "return 0" block and gcc filled the delay slot with the "move v0,zero" (setting the return value 0), while in the ROM the branch goes to a block where v0 is set to 0 (ins 36) and the delay slot got the "li v1,9" instead.

Hmm, so in the ROM, the "move v0,zero" is at ins 36 (a separate block), and mine put it in the delay slot. This is a reorg/scheduling difference.

Both are consequences of the block layout, which follows from the register allocation (the const temp's register) and the return structure.

Let me now try the LAST idea I have for item 3, which is to make the "1"-value a REAL pseudo by using it in a comparison with a constant that gcc keeps. Specifically:

```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
```
→ what if instead:
```c
if (arg2 == 9) return 1;
```
i.e. each arm returns the literal → 4 × `li v0,1` → cross-jump merges them into one block → the shared block = `li v0,1; jr $ra`. Hmm, but then the branches go to that block (2 insns) → the chain would be [li v1,9][beq → SHARED][li v1,17][beq → SHARED]... and the SHARED block = `li v0,1; jr $ra`. The ROM has the branches going to +0x94 = `jr $ra` with `li v0,1` in the chain block's delay slot. So the ROM's shared block is JUST the epilogue.

Hmm! But what if the shared block "li v0,1; jr $ra" got its `li v0,1` moved... no.

OK: alternative — what if the arms return the literal 1 and gcc's cross-jump merging produced a shared block that is JUST `jr $ra`, with the `li v0,1` sunk into the delay slot of the branch that reaches it? Hmm, that's not how sched works.

Let me just TEST it: variant with `return 1;` in all four arms. Cheap. Also test `return 1;` in the first arm and `return v0;` in the others.

Let me write both and score. If no luck, I'll wall it and move on.

Actually, let me ALSO try: `if (arg2 == v1) return 1;` where the const temp is used only ONCE (i.e. `if (arg2 == 9) return 1;` — no temp at all!). That's variant A + literal returns. Let me combine: variant H:

```c
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) return 0;
    ...
        if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
            if (arg2 == 9) return 1;
            if (arg2 == 0x11) return 1;
            if (arg2 == 0x29) return 1;
            if (arg2 == 0xA) return 1;
            return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
        }
```
Let me test this and variant I (temp + literal returns).
