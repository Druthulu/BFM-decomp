---
ts: 2026-10-21T23:40:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jv1B55DB4PKWwe1exDI2
---
c1: 29. Same.

Let me think differently. The key must be to make gcc NOT put the address in a callee-saved register.

Observation: gcc keeps the address in s0 because it's live across the call at insn 12. What if the value is NOT live across the call because we restructure so that the *second* use is computed from something else?

What if the array `sp10` is a **static/global**? No — it must be on the stack (target has sp-relative).

Hmm, what about: what if the second call's argument is `sp10 + 4` but the FIRST call's args are `sp10` and `sp10 + 4` — same. What if the first call's second arg is `&sp10[4]` and second call's arg is `sp10 + 4`? Same rtx.

OK, radical: what if we make the array a **struct with a union** so that the two addresses are computed from different MEMs:

```
struct S { u16 a[6]; };
struct S sp10;
```
`sp10.a` → (plus (symbol_ref) (const 0))? For a struct local, `sp10.a` is a MEM with MEM_IN_STRUCT_P, and its address is (symbol_ref sp10). `&sp10.a[4]` → (plus (symbol_ref) (const 8)). Same as array.

Hmm.

TOTALLY DIFFERENT ANGLE: maybe the launder isn't what makes the difference; maybe the difference is that the launder asm prevents gcc from *knowing* that the pointer is a constant, so gcc must allocate a register for it, and then... no wait, the target has NO register.

Hmm hold on, let me re-examine. Maybe the real difference is elsewhere entirely and the s0 thing is a red herring. Let me look at the full diff of b1 to see all 29 mismatches. Let me run with head -120.

Actually, let me reconsider: score 29 with 120 vs 119 ins. The diff tool aligns. Let me view the whole diff. It's worth 100 lines.

Actually, let me first check something cheap and potentially decisive: what if I make the whole thing use a **different but equivalent** structure for the first call: `func_800D20C0(sp10, sp10 + 4, 1)` where sp10 is passed as `sp10` (decays to u16*). Target: a0 = sp+16 ✓.

Let me now consider: what if the *first* call's args are computed from a pointer variable that gcc keeps in a register, and the SECOND call uses the raw array expression? Then gcc would have to keep the pointer in a reg → extra insns. No.

Let me look at the full diff now. It's the most informative next step.
