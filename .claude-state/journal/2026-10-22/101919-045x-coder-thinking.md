---
ts: 2026-10-22T16:19:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sbCa11zRtyCq5RuQ8uFR
---
In the .combine dump (after combine, before cse1), the EQ is already (72, 73) = (p, it). So the swap happens in `combine` or earlier (jump optimization). The .rtl had NE(73,72) = (it,p); after combine it's EQ(72,73) = (p,it) — inverted AND swapped.

So `invert_jump` (in jump.c) swaps the operands when inverting? Let's see: NE(it,p) inverted to EQ(p,it). That's a swap, not a straight inversion. Why? `invert_jump_1` for a comparison uses `gen_rtx_fmt_ee (reversed_comparison_code, ...)` with the same operands → EQ(it,p). Hmm, but we see EQ(p,it).

Maybe `combine`'s `simplify_comparison` swaps to put... Actually `simplify_comparison` in combine.c has:
```
  /* If the first operand is a register and the second is a constant... */
```
Not for two regs.

Hmm, maybe the swap is in `fold_rtx` (cse) — but .combine already shows it, and .combine comes after combine but also after cse? The pass order: rtl → jump → cse → ... Actually `-dc` (combine) dump is after combine, which runs after cse1. Let me check the .cse dump — it also shows (72,73). The .cse dump is after cse1 which runs after jump1. So the swap happened in jump1 or cse1.

The .rtl dump is before all passes. So jump1 or cse1 swapped. If jump1's invert swaps operands, then any `if (x == y)` becomes `if (y != x)`... 

Let's test the hypothesis: the *first* pass that sees `NE(it,p) goto body; goto zero` inverts the branch to jump to zero and swaps. Why swap? Because `invert_jump` in GCC 2.7.2's jump.c:
```
  if (condjump)
    {
      ...
      /* Invert the condition */
      ...
      if (GET_CODE (SET_SRC (SET_PATTERN)) == IF_THEN_ELSE)
        ...
```
Maybe it uses `swap_condition` which for NE returns EQ and then `XEXP (SET_SRC, 0)` operands are swapped by `gen_rtx_fmt_ee (code, VOIDmode, XEXP (x, 1), XEXP (x, 0))`? Possibly to keep the "canonical" order.

Whatever the mechanism, the target's compiler ended with EQ(it,p) = (v1,a0). Our compiler ends with EQ(p,it) = (a0,v1). So the target's C must have started with the *opposite* order so that after the swap it lands as (it,p). That means the target's C wrote `if (p == it) goto zero;` → expand NE(p,it) → invert+swap → EQ(it,p) = beq v1,a0 = target!

But q14 (which is exactly `if (p == it) goto zero;`) scored 1 with beq a0,v1. Hmm! Unless q14's swap went the other way: NE(p,it) → EQ(p,it)? Let me check q14's dump... 

Wait, maybe I have the swap direction backwards. In q9, C = `it == p` → RTL NE(it,p) → after invert: EQ(p,it). So the invert swaps. For q14, C = `p == it` → RTL NE(p,it) → after invert: EQ(it,p) → beq v1,a0 = target. But q14 scored 1 with beq a0,v1 — the *same* as q9. So either q14's RTL differs, or the final order isn't from the invert.

Let me check q14's final RTL/s. Maybe q14's `p == it` produced a different expand (e.g., EQ directly without inversion). Let me dump q14 quickly and check the .rtl and .combine EQ order.

Alternatively, maybe the expand of `if (p == it) goto zero;` (with zero after body) produces NE(p,it) → invert → EQ(it,p)... but the score says otherwise. Let me verify empirically with a dump.

Actually — maybe the swap is in `combine`'s `simplify_comparison` which canonicalizes by *register number*: it swaps so the lower-numbered pseudo is first. In q9, p=72, it=73 → (72,73). If I could make it have the lower number (declare it first) → (it,p) = target. But r1 (declare it first) still scored 1! Hmm. Maybe the declaration order doesn't determine the pseudo numbers; GCC numbers pseudos in order of first use. In q9, the first use is `it = A` (it gets 73?) and p gets 72? The cse2 shows p=72, it=73. If it is used first, why is it 73? Maybe because `p` is declared first → pseudo 72. In r1 (`s32 it; s32 p;`), p would be 73 and it 72 → the canonical order (72,73) = (it,p) → target. But r1 scored 1, same diff. So the swap isn't by pseudo number, or r1's numbering didn't change.

Let me check r1's dump to see the EQ order and pseudo numbers. Actually, maybe the pseudo numbering is by *first use in the RTL*: `it = A` first (it=72?), then p. In q9 the cse2 shows p=72, it=73 — so p got the lower number despite being used second. That suggests declaration order determines numbering (p declared first). In r1, it declared first → it=72, p=73. Then the EQ after canonicalization would be (72,73) = (it,p) = target. But r1 scored 1 with beq a0,v1 — maybe the swap isn't canonical-by-number and the *registers* changed instead? Let me dump r1 and check.

Let me do that: build a dump for r1 and grep the EQ + the .s.
