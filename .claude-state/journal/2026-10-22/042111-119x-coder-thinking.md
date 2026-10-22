---
ts: 2026-10-22T10:21:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_nGFc4oHCVAroCwXeRWVC
---
The target:
```
19: li   v1,-1664     (x)
20: li   a1,-3712     (y)
21: li   a0,-848      (z)
22: li   v0,104       (0x68)
23: lui  at; sh v0,0(at)   (D_80192CF0 = 0x68)
...
42: li   v0,573
43: lui  at
44: sw   v1,0(at)     (D_80192CE0 = x)   ← x in v1 ✓
```
So the target materializes x in v1, y in a1, z in a0 at the assignment point (19-21) and keeps them.

Ours (lever-free): x → v0 at the first use (insn 39), y → v1.

Interesting: in the target, x is in v1 and y in a1 — and z in a0 (pinned). Hmm, the launder's asm outputs were allocated v1, a1, a0.

Now: how to get the constants materialized early (at the assignment) lever-free?

Key: cse forwards the constant to the uses, so the pseudo is born at the first use. To keep the pseudo born at the assignment, the assignment must not be foldable — i.e. the variable must be SET AGAIN later (per §195-I: any second SET of the pseudo kills the fold).

Hmm! But a second set of x with the same value is an identity statement → not allowed as a crack.

Hmm, what if x is set again with a DIFFERENT value that's equivalent? No.

Hmm, what if the constants were computed rather than literal? E.g. `x = -0x680;` → the value is a constant; cse folds it. But what if x were computed from a runtime value in a way that yields the same constant? Not possible without a lever.

Hmm, what about the *pin* on z: `register s32 z asm("a0")` — that's allowed to stay (other rows' levers). Hmm! And the notes say the pin on z stays. So z is in a0 ✓ (both).

Hmm, so for x and y we need them materialized early in v1 and a1.

Hmm, what determines that they're materialized early? Their pseudo must be born at the assignment.

IDEA: What if x and y are *live across the call* `func_8001C2C4(v)`? Then they'd be in callee-saved regs ✗ (the target has them in v1/a1).

IDEA: What if the assignments happened BEFORE the call `func_8001C2C4(v)`? The notes say "the assignment must stay after func_8001C2C4(v)" — because the values depend on the call? Hmm, x = -0x680 is a constant — it doesn't depend on the call! Hmm, but maybe the decompiler placed it there for a reason (the original source's order).

Hmm! If the assignments were moved BEFORE the call, then the constants would be materialized before the call → in the asm they'd appear before the jal ✗ (the target has them after the call at 19-21).

Hmm, wait: the target's order is: [14: jal func_8001C2C4?][16: lui s0][17: addiu s0][18: move s1,zero][19-21: the three li's][22: li v0,104]...

So the three li's come after the call and after "move s1,zero" ✓ = the source order (the assignments come after `s1 = 0;`).

So the source order is right; the issue is only that the constants are materialized at their first USE instead of at the assignment.

Hmm, so how do we make gcc materialize a constant at the assignment point?!

Hmm! What if the constant is used by a *store* that comes right after the assignment? I.e. reorder the stores so that the x-store comes first? But the target's store order is: CF0, CF2, CF4, CF6, D00, D14, D16, then CE0=x, CE4=y, CE8=z, CEC=x, CFC=0, D04=x, D08=y, D0C=z, D10=x, D18, D1A, D20, D1C, D24.

Hmm, so the x-store is the 8th store. If we reordered the stores, the asm order changes ✗.

Hmm, BUT: what if the *materialization* is forced early by the value being used in a way that's early? Hmm.

Alternatively: what if the constants were assigned to variables that are ALSO used earlier (e.g. in a dead computation)? no.

Hmm, hmm. Let me think about cse's forwarding rule again: cse forwards a constant into a use when the reg's class head is the constant. The pseudo for x is set once (`(set (reg x) (const -1664))`) and used 4 times. cse's "qty_const" mechanism records the constant and then `equiv_constant` substitutes it into uses → the uses become the constant directly → the pseudo dies → the li is emitted at the use.

For the pseudo to survive, its set must not be a simple constant set... per §195-I, a SECOND SET of the pseudo kills the fold (the reg_tick++ invalidation).

Hmm! But here's a thought: what if the second set is *legitimate*? E.g. what if the original source assigned x twice with the same value in different branches? Hmm.

Hmm, what about the `do { } while` loop — the loop's variables get copied (loop.c copies the loop init values into the loop registers)? Hmm.

Hmm, let me look at the target's loop asm to see if there's anything.

Honestly, let me consider the simplest possibility: maybe a different declaration/assignment structure keeps the pseudo alive. E.g.:
- Declare x, y, z at the top and assign them at the assignment point: that's what we have (they're declared at the top of the function and assigned in the middle) ✓.
- v2 (init at declaration) → 19 but the frame grows.

Hmm, what if only x and y are initialized at the declaration (and z assigned later)? The frame grows for x/y (callee-saved) ✗.

Hmm, what if the constants are assigned to variables that are *not* modified and have a single use? no.

OK, let me think about the mechanism differently: in the target, the li's are at 19-21 and the stores use v1/a1/a0. The li's are consecutive → they were born together → the three pseudos were born at the same point (the assignment point).

In ours, x is born at its first use (v0) and y at its first use (v1).

Hmm, so in the target, the pseudos x/y/z are all born at the assignment point. That's exactly what the launder's asm does (it reads them there).

What else could make a pseudo be born at the assignment? If the pseudo were USED at the assignment point. Hmm!

What if x were used in a way that requires its value at the assignment point but produces no code? E.g. `x = x;`? identity (not allowed).

Hmm, what about the ORDER: `x = -0x680;` — hmm.

What if the assignment were a *compound* expression: `x = -0x680 + 0;`? Folded.

Hmm, what if x's value were assigned via a variable that's read: e.g.
```c
s32 t = -0x680;
x = t;
```
→ then x's pseudo is born at the copy... and the constant is materialized for t. Hmm! Then the constant's pseudo (t) is born at its assignment (the first use of the constant) and x's copy at the assignment of x. Hmm, but the li would be at t's assignment ✓ EARLY!

Hmm! That's interesting: a *copy* through another variable keeps the materialization at the assignment point (because the copy's source is a pseudo, not a constant... but cse would forward the constant again ✗).

Hmm, unless the copy kills the fold per §195-I ("§145(b)'s `p = r;` copy" kills the fold!). YES: §195-I says a `p = r;` copy (a second set in the equivalence chain) kills the fold!

So:
```c
s32 t;
...
t = -0x680;
x = t;      /* the copy kills cse's fold → the pseudo survives → the li is at t's assignment */
```
Hmm, but the li's position: t's pseudo is born at t's assignment → the li is emitted there ✓ EARLY.

Hmm, but would the copy `x = t` produce an extra "move" instruction? In the target, x's value is in v1 — the copy would be a move (v1 ← v0) ✗ (extra insn). Hmm, unless the copy is coalesced (the two pseudos get the same register) → then the li is in v1 and no move ✓.

Hmm! Coalescing: if t and x are both pseudos with the same value and the copy is coalesced, the li would be in x's register (v1) ✓.

So the plan:
```c
s32 t1, t2;   /* or reuse */
...
t1 = -0x680;
x = t1;
t2 = -0xE80;
y = t2;
```
Hmm, but cse's fold is killed only if the copy survives to cse... The front end would fold `x = t1` where t1's value is a constant → the front end's constant propagation might fold it entirely (x = -0x680) → back to square one.

Hmm! The front end's fold: does gcc's front end propagate a constant from a local variable to another local? In gcc 2.7's c-type.c, the front end's expand_expr for a VAR_DECL with a constant initializer — I believe the front end does NOT fold uses of a variable (it only folds constant expressions). But EXPAND does (the pseudo substitution).

Hmm, and expand's substitution: the pseudo for t1 is set to the constant → expand substitutes the constant into t1's uses → `x = t1` becomes `x = -0x680` → x's pseudo is born at the assignment with the constant → the li at the first use ✗.

Hmm!! Unless the substitution is what we're fighting.

Hmm, but the §195-I note says a `p = r;` copy kills the fold — meaning the copy DOES survive to cse in some contexts (the pointer-bump case). So the copy does survive expand's substitution in some cases.

Hmm, in the pointer-bump case: `r = p + K; ... p = r;` — the copy `p = r` — expand wouldn't fold r's value (it's not a constant) ✓. So the note's case isn't about constants.

For OUR case (a constant), the copy would be folded by expand.

Hmm. OK.

So what makes the target's constants be born at the assignment point?

Hmm, hold on. Let me reconsider: maybe in the target, the constants are NOT born at the assignment but the SCHEDULER hoisted them. The three li's at 19-21 are consecutive and before the first store. Hmm, in ours, the li's are at 39-41 (at the first use). The scheduler could hoist a constant's materialization if beneficial... but the constant's pseudo is born at the use, so the scheduler can't hoist it before its use? Actually sched can move instructions within a block as long as dependencies allow — the li (a constant materialization) has no dependencies and could be hoisted to the top of the block ✓. But gcc's scheduler generally doesn't hoist a "birthed" instruction far from its use... Hmm, actually sched2 CAN hoist.

In ours, the li's stayed at the first use. In the target, they're at the top.

Hmm, what if the difference is that in the target, the three constants' pseudos were born at the top (so the li's are there), and in ours they're born at the use.

I keep coming back to: the pseudo must be born at the assignment.

Hmm, let me look at this from the "what does the launder do" angle again: `__asm__ __volatile__("" : "=r"(x) : "0"(x));` — this asm reads x and writes x. The asm forces x into a register at that point → the pseudo is born there ✓.

Without the asm: x = -0x680 is a constant → gcc materializes it where used.

So the lever is essential for this shape... unless the value is used early.

Hmm! IDEA: what if the value is used EARLY in a way that produces the target's asm? E.g. what if the FIRST store of x were... no, the store order is fixed.

IDEA 2: What if the constants were assigned to variables that are ALSO used by the do-while loop? no.

IDEA 3: What if x/y/z were declared as `volatile`? Not allowed.

IDEA 4: What if the assignments were moved into a nested block so the pseudos' lifetimes change? Hmm: the constants' uses are all after the block, so they must be live across the block ✗.

IDEA 5: What if the values were computed by an expression involving a runtime value that cancels out? e.g. `x = -0x680 - 0;` folded.

Hmm, IDEA 6: what if x's value were assigned from a *global* that holds -0x680? no.

IDEA 7: What if the constants were assigned to variables of a *different type* (e.g. u16)? Hmm, -0x680 doesn't fit in u16.

IDEA 8: What if we use the do-while loop's `s1` trick? no.

IDEA 9: What if the constants were assigned to the *same* variable in a way that... hmm.

IDEA 10 (promising!): What if the three constants are stored into variables whose VALUES are then used in a way that forces them into registers early — e.g. the STORE order! Hmm.

Hmm, wait. Actually, let me reconsider the problem. In ours, the constants are materialized at their first use: x at insn 39 (just before "D_80192CE0 = x"), y at 40, z at 41. The score is 20 — 20 mismatched insns out of 89. Hmm, that's a lot: the 3 li's misplaced (3) + the stores using the wrong registers (each store's "sw v1,0(at)" vs ours "sw v0,0(at)" — the register difference counts as a mismatch) — 10 stores × 2 (the li + the store) ≈ 20 ✓.

So if we could get the constants materialized early in the right registers, we'd score 0.

Hmm, what if we make the constants' first use EARLY by reordering the STORES? The store order is fixed by the target... but WAIT: is it? The target's store order: CF0=0x68, CF2=0xB, CF4=0x36A, CF6=0x36A, D00=1, D14=0x1F4, D16=0x291, CE0=x, CE4=y, CE8=z, CEC=x, CFC=0, D04=x, D08=y, D0C=z, D10=x, D18, D1A, D20, D1C, D24.

Our source has that exact order ✓. So no reordering.

Hmm, so the only way is to have the pseudos born at the assignment.

Hmm hmm. What if the constants are assigned to variables that are *read* by the do-while loop or later... no, that's later.

What if we introduce a use of x right at the assignment that produces no code? E.g. `x = -0x680; if (x == -0x680) { }` → the front end folds the comparison → no use remains ✗.

Hmm, what about `x = -0x680; x = x;`? identity → not allowed.

OK, so item 8017D81C is likely a genuine wall (cse-const-holder). Let me do a batch of tries to reach 30 and record it.

Batch ideas (cheap):
1. x/y/z as u32/s16 types.
2. The assignments as separate statements with an intermediate variable.
3. The assignments moved before/after the `s1 = 0`.
4. The constants spelled as decimal.
5. The constants assigned in a different order (z, y, x).
6. x/y/z declared as locals in the inner block.
7. The constants as `0x680` negated: `x = 0 - 0x680;`
8. `x = -1664;`
9. The li's target: `li v1,-1664` — the value -1664 = -0x680 ✓. Note: gcc materializes "li v1,-1664" (one instruction) ✓.
10. The assignment as a cast: `x = (s32)(-0x680);`
11. y and z assigned via `z = -0x350;` ✓ already.
12. Swap the roles: make x's first use the z-store? no.

Also, since the target has the li's at 19-21 in the order x,y,z, and the assignment order in the source is x,y,z ✓.

Hmm, let me think about the do-while loop: the loop's "s1" is incremented; the loop is at the end. The loop.c pass might copy values into the loop's registers — the loop's induction variable s1 is in s1 ✓.

Hmm, what about the possibility that in the target, the constants' pseudos were born at the assignment because the ORIGINAL source had the constants assigned to variables that were ALSO used in the loop or later in a way that kept them alive... they're used in the stores ✓ (4 uses for x).

Hmm, so x has 4 uses and the pseudo still died (folded) in ours.

Hmm, hmm. What if the stores were written to use the *address* of the variable? no.

OK, let me think about the *pin*: z is pinned to a0 (allowed to stay). The pin forces z into a0 — a hard reg — so z's pseudo is NOT folded (the pin's asm-like constraint keeps it). Indeed in ours, z is presumably materialized early too (in a0) ✓ (the notes say "The $a0-pinned z is early in ours too (insn 18)").

So z works because of the pin (a lever of another row). For x and y, we need a similar effect without a pin.

Hmm! What if x and y were pinned to $v1 and $a1 with `register`?? That's a PIN — a lever of the "pin" kind, which is NOT in this row's kinds ("launder")! Hmm!! Wait: the kinds file for this item says "launder" only. The constraint says: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

"never added" — so I can't ADD a pin. The def already has a pin on z (allowed to stay). But adding a pin on x/y would be "adding a lever" ✗.

Hmm. But hold on: is that really forbidden? The brief says: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

Hmm, the first clause says "no pin" — but the kinds are "launder" only. The second clause: "no new lever of any kind" — so adding a pin = adding a lever ✗. And CONSTRAINTS: "levers of other kinds the def already had (pins under other causes) may stay, never added".

So: no new pins. The existing z pin stays.

OK so we need x and y materialized early without any lever.

Hmm, what makes the pinned z early? The pin's register variable means z's pseudo is allocated a0 and the value is materialized there at the assignment ✓.

Hmm, is there any *non-lever* way to force a variable into a register early? Hmm: what if x and y were used in the `do-while` loop... no.

What if x and y were used in an EARLIER store? The store order is fixed.

Hmm, what if x and y were *declared* earlier and assigned earlier (before the call)? Then they'd be materialized before the call ✗ (the target has them after the call).

Hmm, wait — actually, would they? If x = -0x680 is before the call `func_8001C2C4(v)`, then the constant's pseudo is born at... the first use (the stores, after the call) ✗ — the pseudo is born at the use regardless of where the assignment is! The assignment position doesn't matter for cse's forwarding.

Hmm, right: cse forwards the constant to the uses regardless of the assignment's position. So the position of the assignment doesn't matter at all — only the uses' positions.

So the ONLY way to get the li's early is to have a USE of x/y early (before the stores). The uses are the stores.

Hmm! Unless... the li's are hoisted by the scheduler. Hmm, in the target they're at 19-21 — right after the "move s1,zero". Could the scheduler have hoisted them there? The first use of x is at insn 44 (the store). Hoisting the li from 44 to 19 is a big move. sched2 does hoist "free" instructions sometimes.

Hmm, but in ours, the li's are at 39-41 (just before their uses) — hmm, wait, ours materializes x at insn 39 = just before the store. So the li's are adjacent to the uses.

So the target's early li's = the pseudo was born early = the launder's effect.

CONCLUSION: this is a genuine wall (cse-const-holder).

Hmm, but hold on! What if the constants were used EARLY in a way that produces the SAME asm? E.g. what if the first use of x were a store that the target also has... no.

Hmm, what about the possibility of making the li's hoist by using a *different* form: e.g. `x = -0x680;` vs `x = 0xFFFFF980;` (the unsigned spelling)? Same constant.

Hmm, what if the three constants were assigned to variables in a way that they're live across the do-while loop? They're used before the loop ✗.

OK. Let me now run a batch of ~16 tries for this item (to satisfy ≥30 tries) and then write everything up.

Ideas for the batch:
1. x/y/z types: s32 (current), u32, s16?
2. The assignment order: z, y, x
3. The constants as decimal (-1664, -3712, -848)
4. `x = 0 - 0x680;`
5. `x = (s32)-0x680;`
6. The assignments moved before `s1 = 0;`
7. The assignments moved after `p = D_80192D28;`
8. x/y/z declared at the top vs inside the block
9. The first store using x moved? (no)
10. `x = -0x680; y = -0xE80; z = -0x350;` → `x = -0x680; z = -0x350; y = -0xE80;`
11. The stores: `D_80192CE0 = x;` → `D_80192CE0 = x + 0;`? (identity, but let's see the effect)
12. The values used via a temp: `D_80192CE0 = x;` hmm.
13. x/y/z as `s32` but assigned via a temp: `s32 t = -0x680; x = t;`
14. The do-while loop changed to a for loop.
15. The declarations reordered (x, y, z before v, s1, p).

Let me write and run.
