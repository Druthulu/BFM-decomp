---
ts: 2026-10-22T10:20:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yG1Hpoq9sqkfye5qLoJl
---
The three constants x, y, z are assigned after `func_8001C2C4(v)` and used in the stores below.

Target: the three `li`s are at insns 18-20, right after "move s1,zero" (17) — i.e. at the assignment point, in $v1 (x), $a1 (y), $a0 (z, pinned).

Wait, the notes say: "`li v1,-1664` (x), `li a1,-3712` (y), `li a0,-848` (z)".

Hmm, x = -0x680 = -1664 ✓, y = -0xE80 = -3712 ✓, z = -0x350 = -848 ✓.

Ours (lever-free): the constants are materialized at their first use: x into $v0, y into $v1 (insns 39-40).

The difference: the materialization POSITION (early vs at first use) and the REGISTERS.

Since the pin on z ($a0) stays, z is in a0 in both.

For x and y: the target has them in v1 and a1 (materialized early); ours has them in v0/v1 at the first use.

Hmm, the register difference (v1 vs v0 for x) is interesting: in the target, x is in $v1 — and $a1 for y. Hmm, why $a1 for y? Because the asm's outputs (the launder's "=r"(y)) were allocated to v1, a1, a0 — hmm, the asm with 3 outputs: x→v1? y→a1? z→a0?

Hmm, the notes say the launder's asm outputs were "$v1, $a1, $a0" — the target's registers. With the asm, gcc assigns the outputs to specific regs.

Without the asm, x and y are materialized at their first use in whatever regs are free.

Hmm, so cracking this requires:
1. The constants materialized at the assignment point (not at the first use) — requires the pseudo to be born at the assignment → cse must not forward the constant → the pseudo must have 2+ sets (per §195-I) or the assignment must not be foldable.

Hmm! Since x/y/z are assigned once and used 4/3/3 times, cse forwards the constant to the uses (that's the "lone use" hmm, actually with multiple uses cse can still forward).

Hmm, what if the constants were used in a way that requires a register EARLY? E.g. if the first use of x were before the call... no.

Hmm, what about the ORDER of the assignments: `x = -0x680; y = -0xE80; z = -0x350;` — the assignments are consecutive. gcc's cse folds each constant into its uses → the pseudos are born at the uses.

BUT: what if the *first* use of x came right after the assignment? Then the materialization would be at the first use = right after the assignment ≈ the same position! Hmm! But the stores of x are at D_80192CE0 = x (after 8 other stores).

Hmm, so the ORDER of the stores matters: if the x-store came FIRST (right after the assignments), then the materialization of x would be at that point — earlier. But the target has ALL THREE constants materialized at insns 18-20 (consecutively, before the first store "li v0,104" at 21).

Hmm! So in the target, the three li's are grouped at the assignment point. In ours, each is materialized at its own first use (x at 39, y at 40 — consecutive!, z somewhere).

Hmm, ours: "ours materialises x into $v0 and y into $v1 at their FIRST USE (insns 39-40, just before `D_80192CE0 = x`)". So x and y are materialized at 39-40 — consecutive (because their uses are consecutive: D_80192CE0 = x; D_80192CE4 = y). And z at 41 maybe.

So in ours the constants are materialized at their first use (consecutively) but LATE (after 8 other stores).

In the target they're at the assignment point (early).

So the difference is WHERE the constants are materialized. If the source's stores of x/y/z came FIRST (right after the assignments), the materialization would be at that point — but then the ORDER of the stores would change ✗ (the target's store order is fixed: D_80192CF0 = 0x68 first, etc.).

Hmm! Unless... the materialization happens at the assignment because the pseudo is born there. Which requires the "second set" trick (§195-I) or...

Hmm, hold on: what about the *do-while loop* and the loop's "copy" of variables? Hmm.

Hmm, what about this: the target's "li v1,-1664" at 18 — is it really the materialization of x? The notes say so.

Let me look at the target's asm 1-30 to understand the structure.

Let me dump it.
