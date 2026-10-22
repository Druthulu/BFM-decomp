---
ts: 2026-10-22T07:08:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Ca4My0dfXxe0WiLU6AdS
---
Item 4: func_80190D70 — a big function (192 ins). The launder is:

```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            /* sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder
            sx = (sx + 0xA0) / 0x14;
```

The launder on `vol` gives vol a 2nd SET → kills the sched1 birthing boost → the PAN multiply (sx's) is not hoisted ahead of the vol multiply.

Note: `vol` is NOT pinned (no register var). The pins here: `register void *r4 __asm__("$4")` and `register s32 av __asm__("$5")`.

The G11 recipe: a compound assign gives a REAL 2nd SET: e.g. `vol &= 0xFFFFFFFF;`? Hmm, but vol is a plain local.

Better: per the moves.md G11 entry: "launder: pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost; plain pv = pv & mask (a new temp) does NOT".

So here: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then `vol &= 0xFFFFFFFF;`? That's a no-op compound assign → gcc folds `x & -1` → x? For an s32, `x & 0xFFFFFFFF` → -1 → folded to x. Hmm.

What about `vol = vol % 0x100000000`? no.

Hmm, we need a real 2nd SET of vol. Options:
- `vol |= 0;` → folded? `x | 0` → x (folded by combine).
- `vol += 0;` → folded.
- `vol = (s32)vol;` → folded.
- `vol = vol;` → removed.

Hmm, but G11's example: `pv &= 0xFF000000` — that's a REAL change of the value (masking), which is why it survives! In G11, the target's own code masked pv, so the C code was `pv = pv & 0xFF000000` written as a compound assign `pv &= 0xFF000000` — the compound form gives the pseudo a 2nd set (the RMW) while the plain form creates a new temp.

So the question here: is there a way to write the vol computation so that vol gets 2 sets while the VALUE stays the same?

`vol = ((0xA0 - av) * 0x7F) / 0xA0;` — the value is a division. What if we write it as a compound assign? E.g. `vol = 0; vol += ((0xA0 - av) * 0x7F) / 0xA0;`? Hmm, that changes the instruction sequence (an extra add/move).

Hmm, what about: `vol = X;` then `vol = vol;`...

Alternative: use the division differently: `vol = (0xA0 - av) * 0x7F / 0xA0;` — the target computes `((0xA0 - av) * 0x7F) / 0xA0` with a magic-multiply division. If I write it as a compound assign `vol = something; vol *= ...` hmm.

Think: the target's instruction sequence for vol is: sub, mult (magic), mult, div → the division by 0xA0. A compound assign form: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` — that's a 2nd set of vol (the /= is an RMW on vol) but the value differs? No: vol = (0xA0-av)*0x7F then vol /= 0xA0 gives the same value ✓ and the instructions would be: mul, then the division sequence (with vol as the dividend). But the target's division might use a different register/insn sequence (e.g. the magic multiply needs a copy of the dividend).

Hmm! The target: `vol = ((0xA0 - av) * 0x7F) / 0xA0;`. Written as `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` — gcc's div-by-const expansion: for `x / 0xA0` with x = the product, gcc computes the magic multiply on x. The compound form `vol /= 0xA0` is an RMW: it needs vol in a register and computes the quotient into it — the same insns but vol's pseudo gets a 2nd set ✓ (the RMW).

But the multiplication: `vol = (0xA0 - av) * 0x7F` then `vol /= 0xA0` → the instruction sequence: `subu` (0xA0 - av), `mult`/`mul`, then the magic-mult division. The target's sequence might be: `subu`, `multu`, `mflo`, `multu` (magic), `mflo`, ... Let me check the target's assembly to see.

Let me look at the target's .s for this function. I can objdump the built object.

This is promising: the compound-divide form gives vol a real 2nd set (the RMW) — exactly the G11 recipe ("compound assign = a REAL 2nd SET").

But the instruction sequence might differ (the division's dividend handling). Let me check the target's code.

Let me set up the item dir and look at the target assembly for the vol computation.

Plan:
1. Copy the def to orig.c (lines 3413-3496 or wherever the function ends).
2. Look at the target's disassembly around the vol computation.
3. Try the compound-divide variant.

Let me find the function's line range: it starts at 3413 and ends at "}" before the comment at ~3497. From the output above, the function ends around line 3496 ("    }" then "}").

Let me extract lines 3413 to the closingbrace.
