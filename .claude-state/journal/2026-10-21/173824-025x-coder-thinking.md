---
ts: 2026-10-21T23:38:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3SGI7u7FIM2qF2blCGFN
---
No other shard has them. Let me check the T10 worked example and the R3.40-013 helpers. Also let me check the "held.tsv" / "parked.tsv" in T11.

Actually, let me focus. Let me try to understand the launder's effect by dumping RTL. Let me look at tools/cc1_dumps_tu.sh and alloc_table.py.

Actually, maybe a much simpler idea works: what if the SECOND call's argument is written as `sp10 + 4` but the FIRST call's second argument is written as a *different* array-index form that yields a different rtx but the same address — specifically using a **pointer to u16 with a different base**: e.g., the first call's args could be `p0` and `p1` where p1 = sp10+4 computed from a *byte* pointer: `p1 = (u16 *)((u8 *)sp10 + 8)`. Then the rtx for p1's value is (plus (symbol_ref) (const 8)) — same as sp10+4. gcc will unify.

Hmm, in gcc, does `(u8*)sp10 + 8` produce the same rtx as `sp10 + 4`? The base is symbol_ref (a MEM address); pointer arithmetic in bytes: (plus (symbol_ref) (const 8)). For u16*: (plus (symbol_ref) (const 8)) too (byte offset 8). So identical.

What if the base is a *pointer variable* holding sp10?
```
u16 *base = sp10;
func_800D20C0(base, base + 4, 1);
func_800D23D0(base + 4);
```
Now base's value is (symbol_ref sp10) held in a pseudo; base+4 is (plus (pseudo_base) (const 8)). Both uses of base+4 → cse unifies → one pseudo → s0. Same.

Hmm. But what if base is *modified* between the calls? Then base+4 differs. But the target shows the same address sp+24 both times, so the value must be the same but the rtx different.

AH WAIT. Here's an idea: what if the two uses are the same *value* but spelled through DIFFERENT base variables that hold the same address:
```
u16 *b1 = sp10;
u16 *b2 = sp10;
func_800D20C0(b1, b1 + 4, 1);
func_800D23D0(b2 + 4);
```
Now b1 and b2 are two different pseudos both holding (symbol_ref sp10). cse would unify them (both are the same constant) → b1 == b2 → then base+4 identical → unified. Hmm. Unless the unification of b1 and b2 happens but then b1+4 vs b2+4 are the same rtx.

Unless we make b2's value different at RTL but same address:
```
u16 *b2 = &sp10[0];
```
same.

Hmm.

New angle: maybe use a **struct** with two members at different offsets but the SAME address via a union... no.

New angle 2: maybe use `__builtin_frame_address`? Not available/portable, and it's a different thing.

New angle 3: Maybe the fix isn't about breaking CSE at all, but about making gcc's *scheduling* place the addiu differently. Hmm no — the insn count differs by 1 and register allocation differs.

New angle 4: Let's look at the problem from the "what does gcc do with `sp10 + 4` twice" question. gcc creates a pseudo P = sp+24 at the first use, uses P for a1. Then at the second use, cse finds the same expression and reuses P (P is live across the call → needs callee-saved reg → s0).

To make gcc recompute, the second use must not be recognized as the same expression.

What if the second use goes through a **volatile** access? No.

What if the second use's address is computed from a *different but equivalent* base that gcc treats as a different symbol: e.g. `sp10` is `u16 sp10[6]` and we add a second reference `&sp10[0]` via a **function parameter**? No.

What if the array is declared as `u16 sp10[6]` and we also declare `u16 *sp10p = sp10;` then use `sp10p + 4` for one call and `sp10 + 4` for the other? cse: sp10p's value = (symbol_ref) — if sp10p is a local var, local-alloc may keep it in a register → (plus (reg) (const 8)) ≠ (plus (symbol_ref) (const 8)) → NOT unified by cse! But then the first use would be `addiu a0,a1,8`? No wait, if sp10p is in a register r, then sp10p+4 needs `addiu t,r,8` — 1 insn, then a1 = t → `move a1,t`? That's 2 insns. Target has just `addiu a1,sp,24`. So the register holding sp10p would be sp itself! If sp10p is assigned sp10 and gcc keeps it in a register, the register would be... $sp? gcc can use the frame pointer register for a frame address. Hmm! Then `sp10p + 4` = (plus (reg sp) (const 8)) → `addiu a1,sp,24` — exactly the target!

And the second use `sp10 + 4` = (plus (symbol_ref) (const 8)) → also `addiu a0,sp,24` but as a different rtx, so no CSE unification → gcc computes twice!

Hmm, but would gcc actually keep sp10p in $sp? Unlikely; it'd be a general reg.

Hmm, but wait: for a local variable whose value is the address of another local, gcc's local-alloc would likely give it a register (like s0). Hmm.

OK, let me try a completely different approach: EMPIRICAL. Let me try ~10 candidate spellings and see which gives 0. Each score takes maybe 15s. That's fine.

But first, let me look at the "R3.40-013 helpers" — maybe delever_search has a --moves/beam search I can use with lever-free seeds. The brief says "delever_search.py --try <TU> <fn> <file> --body (score 0 = MATCH; compares with the function in build/); R3.40-013 helpers." And POINTERS mention .run/P40/T10/tryinc.py and hdump.sh (for header items). We have no header items here.

Let me look at the T10 worked example notes for how a similar launder was cracked, and check the R-rules (R2/R3/R4...) mentioned in the completed item's notes: "delever R2/R3/R4/R6/R9/R12/R27 sweep over the lever-free body: best 7". So there's a moves catalog R1..R40 somewhere. Let me find it.
