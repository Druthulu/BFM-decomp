---
ts: 2026-10-22T10:16:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SNBVGWbGMIOHA8uT4zpk
---
The residual involves the division sequence and the register allocation (a0 vs v0 for the magic).

Target:
```
120: lui a0,0x6666
121: ori a0,a0,0x6667     (the magic in a0)
...
125: subu v1,v1,v0
126: mult v1,a0
...
128: addiu v0,a2,160
...
130: mult v0,a0
131: sra v1,v1,0x1f
132: subu a1,a0,v1
133: sra v0,v0,0x1f
...
136: sra v1,a2,0x3
137: subu a2,v1,v0
```
Ours:
```
123: subu a1,v1,v0
124: lui v0,0x6666
125: ori v0,v0,0x6667
126: mult a1,v0
128: addiu v1,a2,160
130: mult v1,v0
131: --
132: sra v0,a1,0x1f
133: subu a1,a0,v0
134: sra v1,v1,0x1f
136: sra v0,a2,0x3
137: subu a2,v0,v1
```

So two differences:
(a) The magic constant is materialized early in the target (at the top: lui a0/ori a0) vs late in ours (next to the mult).
(b) The register assignment differs: the target uses a0 for the magic, ours uses v0; and the v0/v1 swap in the final part.

Both stem from the magic constant's position: in the target, the magic is materialized at the "tail top" (before the division sequence) into a0 — and being in a0 (an argument register!) it's live across... hmm.

Interesting: the target's magic is in $a0 — that's the *first argument register*. Hmm! In the target's asm, the magic constant is loaded into a0 — suggesting that in the original source, the division's magic was computed into a0 because... hmm.

The launder `__asm__("" : "=r"(vol) : "0"(vol));` — the launder's output operand forces vol into a register, and the asm's priority anchors it.

Hmm, what does the launder do here? It re-ties vol to itself. In the target, maybe the division result was in a register that was later used.

Honestly, for this item, the lever-free best is 14 and the residual is about the magic constant's placement and the register swap.

Ideas to try:
1. Split the division differently: `vol = (0xA0 - ax) * 0x7F; vol = vol / 0xA0;` (c1 = 14).
2. `vol = (0xA0 - ax) * 0x7F / 0xA0;` (one expression) — probably the same as the orig.
3. Hoist the numerator: `s32 num = (0xA0 - ax) * 0x7F; vol = num / 0xA0;`
4. Use an unsigned division: `vol = (u32)((0xA0 - ax) * 0x7F) / 0xA0;` → different magic (0xCCCCCCCD) ✗.
5. Divide by a variable: `s32 d = 0xA0; vol = num / d;` → the magic would be computed at runtime? gcc would emit a division by a variable ✗.
6. Use `vol = num * (1.0f/0xA0)`? no.
7. Make the division's magic appear at the top by computing something else first that uses the same constant? Hmm — the target has "lui a0; ori a0,a0" at 120, which is at the "tail top" (the start of the tail block).

Hmm, what does "the tail top" mean? The tail block of the function (after the last call). The target materializes the magic at the top of the tail block. In ours, it's materialized right before its use.

Since gcc materializes a constant at its use (unless it's live earlier), the target's magic must be *live* from the top of the tail block → i.e. computed earlier (e.g. before a call) or assigned to a variable that's live across something.

Hmm! In the target, the magic is in $a0 — and $a0 is the first argument register. If the magic were materialized before the call `func_8002D4C8(0xA9B, ...)` — no, the tail comes after.

Hmm, what if in the target, the division was computed BEFORE the call to func_8002D4C8 and the magic was live across the call? Then it'd be in a callee-saved reg (s3), not a0. Hmm, unless the call is a "leaf"...

Hmm, the magic in $a0 suggests the pseudo holding it was allocated a0 — an odd choice for a value live across the tail. So maybe the magic's pseudo is NOT live across anything; it's just allocated a0 by local-alloc (a0 is free at that point).

And "the tail top" — the constant is materialized at the top of the tail block, i.e. right at the start of the block (before the subu/mult sequence).

In ours, the constant is materialized just before the mult (after the subu). So the difference is the SCHEDULING of the constant materialization within the block: the target hoists it to the block's start.

Hmm, sched1's "birth boost" — constants get boosted. In the target, the magic is at the top; in ours, it's next to the mult.

What could make it be born earlier in the target? If the magic's pseudo were created earlier (e.g. the division was computed earlier in the block).

Hmm! What if in the target the division is computed BEFORE the `x = (x + 0xA0) / 0x14;` division? Our source computes vol's division first, then x's division. The target's tail:
```
120: lui a0; ori a0      (magic for /0xA0)
...
125: subu v1,v1,v0
126: mult v1,a0
127: sra?  mfhi?
128: addiu v0,a2,160
129: mult v0,a0
...
```
Hmm, both divisions (by 0xA0 and by 0x14) share the SAME magic? No — the division by 0x14 uses a different magic (0x24924925). Hmm, but the target shows only one magic (0x66666667) at 120-121. Hmm, and 0x14 = 20 → the magic for /20 is 0xCCCCCCCD (unsigned) or 0x99999999 (signed, since 20 = 4*5, the magic is 0x99999999 with a shift). Hmm.

In the target's tail at 128: "addiu v0,a2,160" then "mult v0,a0" — so the SAME a0 (magic 0x66666667) is used for both multiplies! Because both divisions are by 0xA0?? Hmm: our source has `x = (x + 0xA0) / 0x14;` — division by 0x14 = 20. Hmm, but the target's second mult uses the same magic a0 = 0x66666667.

Hmm! 0x66666667 is the magic for dividing by... let me compute: for signed division by d, the magic M = ceil(2^(32+s)/d). For d=160 (0xA0): 2^38/160 = 274877906.9 → hmm. Let's think: 0x66666667 = 1717986919 ≈ 2^31/1.0000... Hmm: 1717986919 * 160 = 274877907040 ≈ 2^38 = 274877906944 — yes! So 0x66666667 is the magic for /160 (0xA0) ✓.

And for /20 (0x14): the magic would be 0x99999999 (since 20 = 4*5, M = ceil(2^34/5)/4...). Hmm, but the target shows "addiu v0,a2,160" before the second mult — a2+160 = x + 0xA0 ✓ (that's the numerator of the second division). So the second division is by 0xA0 too?!

Hmm: our source: `x = (x + 0xA0) / 0x14;` — the numerator is x + 0xA0 ✓ (addiu v0,a2,160 where a2 = x). And the divisor 0x14 = 20 → the magic for /20: M = ceil(2^(32+s)/20); for s=2: 2^34/20 = 858993459.2 → M = 858993460 = 0x33333334 (with a shift of 2). Hmm, that's 0x33333334, not 0x66666667.

Hmm, but the target's second mult uses a0 = 0x66666667 — hmm, 0x66666667 * 20 = 34359738380 ≈ 2^35 = 34359738368 — so 0x66666667 is also a valid magic for /20 with a shift of 3! (2^35/20 = 1717986918.4 → M = 1717986919 = 0x66666667 ✓ with shift 3 ✓ — and indeed the target has "sra v1,a2,0x3" at the end = the shift by 3 ✓).

So the two divisions use DIFFERENT magics in our version (0x66666667 for /160 and 0x33333334 for /20) but the SAME magic 0x66666667 in the target? Hmm, that can't be: the target's second mult uses a0 (0x66666667) — hmm, but wait: maybe the target's second division is by 0xA0 as well? Let me re-read:

target:
```
125: subu v1,v1,v0     ; v1 = 0xA0 - ax
126: mult v1,a0        ; v1 = (0xA0-ax) * 0x66666667
127: (sra/mfhi?)      ; the hi part
128: addiu v0,a2,160   ; v0 = x + 0xA0
129: (mfhi)
130: mult v0,a0        ; v0 = (x+0xA0) * 0x66666667
131: sra v1,v1,0x1f    ; sign
132: subu a1,a0,v1     ; 
133: sra v0,v0,0x1f
134: ...
136: sra v1,a2,0x3     ; the shift by 3
137: subu a2,v1,v0
```
Hmm, "sra v1,a2,0x3" — the shift by 3 of a2 (x). Hmm, so the second division (x + 0xA0)/0x14 uses a shift of 3 and the magic 0x66666667 ✓ (as computed above, 0x66666667 works for /20 with a 3-bit shift).

And the FIRST division (0xA0-ax)*0x7F/0xA0 uses the magic 0x66666667 too (for /160: 0x66666667 * 160 ≈ 2^38, needing a 38-bit product — hmm, with mult/mfhi and a shift of 6?). Hmm.

Anyway: the target uses the SAME magic register a0 for both divisions, while ours materializes two magics (one per division) — hmm, does it? Our asm at 124-126: "lui v0,0x6666; ori v0,v0,0x6667; mult a1,v0" — the first division's magic in v0. And later? The diff only shows a few lines; the second division's magic might also be materialized. Hmm, the target's count is the same (154 = 154) so both have the same number of instructions.

Hmm, the target materializes ONE magic (a0) and uses it twice → saving 2 instructions (lui+ori) — but the counts match, so ours must materialize 2 magics (4 insns) and the target 1 magic (2 insns) + 2 insns elsewhere. Hmm, the diff shows: target has 2 extra insns at 120-121 (the magic) and ours has 2 at 124-125 (the magic) → so both have one magic ✓. OK, so both materialize one magic; the difference is WHERE (early vs late) and the register (a0 vs v0).

So: the target's magic is materialized at the TOP of the tail block into $a0; ours materializes it just before the first mult into $v0.

Ideas:
1. Maybe the ORDER of the two divisions in the source matters: if the x-division came FIRST in the source, the magic would be materialized earlier (at the top) ✓. Let me try swapping the two divisions!
   But careful: the x-division's result is used in the `if (x == 0x10)` etc. The order of the two statements: `vol = ...; x = (x+0xA0)/0x14;`. Swapping them changes the semantics? vol depends on ax (not x) and x's division modifies x. The order swap: `x = (x + 0xA0) / 0x14;` first, then `vol = ...` — vol doesn't depend on x (it uses ax) ✓ semantically equivalent! And the if (x == 0x10) follows.
   Hmm, but the target's order in the asm: the first mult is for (0xA0-ax) and the second for (x+0xA0) — so vol's division is FIRST in the target too. Hmm, but the magic is materialized before both.
   Hmm, so swapping the source order would put x's division first — that might not match.

2. Maybe the magic's early materialization comes from the *launder* (which is the lever): the launder's output "=r"(vol) forces vol into a register, and the asm's position in the block anchors things.

Hmm. But the notes say the residual is "identical to func_801832A8" — a twin function. So the same problem appears elsewhere.

3. What if the division is spelled so that the magic is hoisted: e.g. `vol = num / 0xA0;` where num is a variable → the magic is materialized at the division.

4. What if the *numerator* is computed differently so that the division's magic is materialized earlier?

5. What about `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` — one expression (the orig) → what score? The orig with the launder = 0; without the launder = "the same 30-class residual" (score ~30). c1 (split) = 14. So the split helps.

6. Maybe a different split: `s32 num = (0xA0 - ax) * 0x7F; vol = num / 0xA0;` (with a named numerator) — the numerator's temp might change the scheduling.
7. `vol = (0xA0 - ax) * 0x7F; vol = vol / 0xA0;` (assignment form)
8. `vol /= 0xA0;` (c1) vs `vol = vol / 0xA0;`
9. Split the x-division too: `x = x + 0xA0; x = x / 0x14;`
10. Compute the x-division's numerator in a variable.

Let me try a batch of these.

Also the register difference (a0 vs v0 for the magic, and the v0/v1 swap) may follow from the placement.

Let me write the batch. Base = c1.c (the current best).

Anchors in c1.c:
```
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            vol = (0xA0 - ax) * 0x7F;
            vol /= 0xA0;
            x = (x + 0xA0) / 0x14;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
```
Let me write variants.
