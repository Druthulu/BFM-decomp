---
ts: 2026-11-06T10:14:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BW5FcZwIxSoiqS6X4hYo
---
Interesting: at index 31-32, target has `subu v0,s4,v0; move s4,v0` — that's the `y = t2 + zr` copy (move s4,v0 = y = t2). Mine has `subu s4,s4,v0` (fused). So target has an extra `move` here. And at index 14, target has `move s4,a0` (y = t copy). Mine fuses.

So the 2 missing instructions ARE the two `+ zr` copies. The target's y is a separate pseudo (s4) and t is a0 (caller-saved), so the copies are real moves.

To reproduce lever-free, we need y as a distinct pseudo from the expression. The target: `y = t + zr` where t is in a0 and y in s4. Without zr, `y = t` lets cse merge → no move.

How to keep y distinct without a lever? One real-C way: make t die before y is used... no, the merge is because y and t are copies.

Hmm, but actually the difference is deeper: in the target, t is in a0 (caller-saved) and y in s4 (callee-saved). If y were merged with t, both in a0, and later `(s16)t` used... The target keeps them separate because of the asm operand.

Real C that forces a copy: use `y` in a context that requires it to be a different value at a different time — e.g., `t` is modified. Or use a struct copy.

What if I write `y = t;` and then `t += 0;`? folds.

Hmm. What if I compute y with a cast that changes the mode: `y = (s32)(u16)t;`? That changes the value (truncation) — no.

What if `y` is assigned before `t` is used but `t` is redefined later: e.g. move the `t2 = y - ...` computation and reassign t? Not matching.

Given the count mismatch is structural (the lever itself creates the 2 instructions), a lever-free body fundamentally can't reproduce them. That's a WALL (no-c-spelling? or a wall tag). The 2 copies exist only because of the $0 operand — that's a "pin" mechanism. The wall tag could be `no-c-spelling` (instruction with no C form) or a new tag.

But wait — the target has 188, mine 186. Could a real C move add exactly 2 instructions that match the target's? The target's 2 extra are `move s4,a0` and `move s4,v0` — copies y=t and y=t2. Real C: if we can force y to be a distinct pseudo, we'd get these. 

Idea: make `t` a `volatile`? no (lever).
Idea: use a function call or memory round-trip? changes code.

What about declaring `y` and assigning through a different-typed intermediate that requires a copy but is free? E.g.:
```
s32 t;
s32 y;
...
y = t;
```
cse merges.

What if y is assigned via a pointer: `s32 *yp = &y; *yp = t;`? That's a memory store (extra insns).

What if we use `y = t; y = y + 0;`? folds.

Honestly, the only way to keep y distinct from t is a real redefinition of t between. In the target, after `y = t`, t is used in `D_8012718C - (s16)t`, then in the branch `D_8012718C - t`. t is not redefined.

Hmm, unless cse merges because y=t AND the target's y is callee-saved. Actually cse wouldn't merge y and t if t is in a caller-saved reg and y needs to survive a call. But cse operates on pseudos, not regs. The copy `y = t` — cse's make_regs_eqv replaces one with the other unless both are live across different... 

Actually, GCC's cse merges y and t, then register allocation sees one pseudo. The target's asm operand $0 prevented the merge? The `+ zr` is `plus(t, reg$0)`; cse sees the $0 operand as a hard reg, so it can't canonicalize y to t (different regs). Hence the copy survives.

Lever-free, cse merges. So it's a genuine no-c-spelling-ish wall.

But hold on — maybe I can prevent the merge by making t and y have different MODES or by making the assignment not a simple copy. For example:
```
y = t;
```
→
```
y = D_80127190 - 0x128;   // recompute instead of copy
```
Then y is a separate computation (loads D_80127190 again). That adds instructions (a load), not matching.

What if:
```
t = D_80127190 - 0x128;
y = D_80127190 - 0x128;
```
Two computations, cse would merge the loads into one and produce two... actually cse would compute once and copy. Could emit `addiu t,v1,-296; move y,t`? Hmm, maybe. But the target loads D_80127190 once (v1) then computes.

This is worth a try! `y = D_80127190 - 0x128;` after `t = ...` — cse sees the same expression, computes once and copies. That might produce exactly the target's `addiu a0,v1,-296; move s4,a0`? But then t would be a0 and y s4. Hmm, the target's move is y=t.

Wait, but t must still exist for `(s16)t`. If I write both, t and y both = D_80127190-0x128. cse merges the computation, leaving one addiu and one copy. 

But which gets the addiu and which the copy? The target: `addiu a0,v1,-296` (t in a0), `move s4,a0` (y in s4). If I write t first then y, likely addiu t; move y,t. That's the target!

Similarly for t2/y: `t2 = y - (rand() & ...); y = t2;` → write `y = t2;` as recompute? t2 = y - (...); y = y - (...) would need the rand value again. Hmm, t2 is used in the comparison `(s16)t2 < ...`. So write:
```
t2 = y - (rand() & (...));
y = t2;
```
→
```
t2 = y - (rand() & (...));
y = y - (rand() & (...));   // recompute
```
That calls rand() twice — different code. No.

Alternative: keep `y = t2;` — cse merges, losing the move. Hmm.

Maybe use `y = t2 + 0`? folds.

Hmm.

Actually, maybe a simpler idea: the copies are `addu dst,src,$0`. In C, an `addu` with $0 is a plain copy. What real C construct emits a copy that cse won't eliminate? A copy where the source is redefined later, or where source and dest have different register classes/uses.

For `y = t2`: after this, t2 is used in `(s16)t2 < ...`. So t2 is live after y=t2. If cse merges, it uses t2 for both. To force a copy, make y used where t2 can't be (e.g., after t2 is redefined). t2 isn't redefined.

Alternatively, make y a different type: `s16 y`? Then `y = t2` truncates → extra sll/sra, not a copy.

Hmm.

OK, this item is a WALL. The mechanism: the `$0` operand prevents cse's copy-merge; without it cse merges y with t/t2 and the two `addu r,r,$0` copies (and the register shift) disappear. Tag: `no-c-spelling`? The instruction `addu y,t,$0` has a C form (a copy) but cse removes it. Maybe a new tag `cse-copy-merge` (exists in walls.txt: "cse-copy-merge cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0 (W04)"). That's exactly it! `cse-copy-merge`.

Best score 65 (nopin). But let me try a few variants to see if I can get the copies back, and to reach 30 tries.

Variants:
1. y = D_80127190 - 0x128 (recompute).
2. t2 recompute variants.
3. reorder.
4. widths.

Let me generate ~30 variants and score. Time check: ~03:20. Item 2 started 03:13. Budget 20-30 min → until ~03:40.

Let me write a generator.
