---
ts: 2026-11-06T15:50:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KKCiNqD3PpG3lyTlQSOW
---
The crack:
```
void *q = &sp18;
void *q2;
call1(..., q);
q = 0;
q2 = &sp18;
call2(q2, arg1);
```
Here `&sp18` is a stack address. The dead-reset `q = 0` empties cse's class; `q2 = &sp18` then re-materializes the address (addiu a0,sp,24) rather than a move from a held register.

Note: the target has `addiu a0,sp,24` for call2 — a *fresh addiu off sp*, not a register. In our case, the target has `addiu a0,s0,24` off the base register.

For our case, the analogous crack: q = mb (base), call1(q + 0x18)... hmm, the structure differs: in func_80149374, the address is the whole argument.

Our C: `func_8004914C(mb + 0x18)` — the argument is base+24. The target computes it as `addiu a0,s0,24` where s0 = base. So cse keeps mb (the base) in s0 across the calls and recomputes +24.

In func_80149374, the argument is the address itself (no offset); the target re-materializes it with addiu a0,sp,24 (sp-relative).

For our item, maybe the crack is:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = 0;
mb2 = (u8 *)&D_800AF630;
call2(mb2 + 0x18);
```
This is what b1 did (score 6). Hmm, but b1 had the dead-reset. Let me check b1's asm — maybe it produced `addiu a0,s0,24` for the second call but the first still `move a0,s0`? Score 6 = 6 diffs = all 3 sites × 2 calls. So no.

Let me actually look at b1's output. Quick check of the diff.

Actually, maybe the problem: `mb2 = (u8 *)&D_800AF630` gives a *known constant*, so `mb2 + 0x18` folds to the const and cse finds the const's table entry → 140. In func_80149374, `q2 = &sp18` — the address is also a constant (sp+24)! Yet it re-materialized... because the address is a *virtual stack slot* address, materialized as addiu a0,sp,24 each time (sp-relative), and the cse table entry for `(plus sp 24)` was invalidated by the dead-reset? Hmm, `q = 0` invalidates q's qty; `(plus sp 24)` doesn't mention q...

Whatever. Let me try to make the second base a genuinely different, unknown value: use `mb2 = mb + 0;`? folds.

Hmm, what about making mb's second set come from a *computation* on the first base that changes the value but is compensated:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = mb + 0x18;      // mb = base+24
call2(mb);
mb = mb - 0x18;      // restore? not needed if reassigned next face
```
d1 did exactly this and cse folded because `(plus 82 24)` was already known as 140.

What if the offset variable is a *different constant expression*, e.g. `mb = mb + 0x18;` vs the first `mb + 0x18`... same.

What if I reverse: first call uses `mb + 0x18`, then `mb = mb - 0x18` (mb = base-24?) no.

OK here's another idea: make the *base* a stack-relative or non-constant value. No.

What about the "identity address spelling" prohibition: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". So I must avoid those anyway.

Let me look at the target's RTL more carefully: maybe the target's two pluses are actually the SAME expression but the *allocator* split them because the second one is in a different block! Let me check: the three faces — are they in separate basic blocks? The `if (oz > 0 ...)` between faces creates blocks. So the first call and second call of a face are in the same block (no branch between). Yes, same block.

Hmm. But wait — the calls themselves don't split blocks in cse (calls are insns).

Let me try yet another approach: the "real 2nd set" of mb with a *different value that's still correct at the use*. E.g.:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = (u8 *)((s32)mb + 0x18);   // mb = base+24
call2(mb);
```
same as d1.

What if instead: keep `mb` as the base but write the second call as `func_800491AC(mb + 0x18)` and insert a statement that makes cse's `(plus 82 24)` entry invalid by modifying the *reg 140*'s pseudo. We can't name it... but we can if we write the first call's arg through a variable:
```
u8 *a = mb + 0x18;    // a = 140
call1(a);
a = 0;                // dead-reset on a!
call2(mb + 0x18);
```
The dead-reset `a = 0` invalidates reg 140's value → the table entry `(plus 82 24) → 140` is removed! Then the second `(plus 82 24)` is a fresh computation → addiu a0,s0,24 (with 82 in s0, since it's live across the calls).

And `a = 0` is a dead store (a not used after) → removed by flow. This is EXACTLY the C0414 dead-reset, applied to the *temporary* holding the address!

Let me test:
```
mb = (u8 *)&D_800AF630;
a = mb + 0x18;
func_8004914C(a);
a = 0;
func_800491AC(mb + 0x18);
```
Wait, but the first call's argument: the target has `addiu a0,s0,24` — the arg computed at the call. With `a = mb + 0x18; call1(a);`, a is computed (addiu) then moved to a0 → maybe coalesced to a0 directly.

Hmm, also the base mb must be live across the calls for the second use — yes.

Let me test this (e1). Also a variant where a is reused for the second call:
```
a = mb + 0x18;
call1(a);
a = 0;
a = mb + 0x18;
call2(a);
```
The second `a = mb+0x18` is a real 2nd set; cse: after `a = 0` invalidates, the new plus is fresh.

Let me test both.
