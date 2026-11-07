---
ts: 2026-11-06T15:35:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GFsrQJIZFBy1TCre7yZt
---
All score 6, same. So cse/combine still folds. Hmm. All six produce the same code presumably (s0=base+24, move).

Let me check one disassembly to confirm. Also think harder.

The launder's role: it's an asm with "=r"(mb) : "0"(mb). This tells gcc: mb is copied to a register, then that register is "used" and a new value (same register) is produced with unknown value. So after the asm, mb is unknown. Then `mb + 0x18` cannot be constant-folded; it must be addiu from the register holding mb.

In C, to make a value unknown: assign from a non-constant. But we need the base address.

Alternative: use a local array/pointer whose address is only known at runtime? No.

Wait — maybe the trick is not to make mb unknown, but to make the *base* itself a variable that is set to the address of the symbol, and the +24 done on a register. The launder-free target requires: s0 = &D_800AF630 (base), then addiu a0,s0,24 twice. That means the sum is NOT held in a register across the call; the base is.

In c1, the sum is computed once (s0=base+24) and both calls use move. Why does cse prefer the sum? Because both uses are the same expression (plus sym 24), cse computes it once before the first call and reuses after the call (s0 callee-saved).

To force per-use adds, we need the two uses to not be the same cse expression. The launder achieves that by making mb unknown after the first call. But plain C can't easily.

Unless... use a different variable for the second call whose value cse sees as a *different* expression but which combine folds to the same address? For instance:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
Here the second use is the literal constant expression again — cse sees the same hash entry and reuses the register. Same.

What if we make the second use `mb + 0x10 + 8`? Constant-folded to the same.

What if the second use involves a variable with unknown offset that sums to 24? Not possible.

Hmm, what about the C0414 dead-reset used differently: reset mb to 0 AFTER the first call, then recompute mb for the second call *from a non-constant* expression that yields the address. But there is no non-constant source.

Wait — maybe we can make the base come from an opaque source: e.g. `extern u8 *D_800AF630_ptr;` no, changes the object.

Hmm. What about using the address through an array index with a variable that's provably 0 at runtime but opaque to cse? That's an identity launder — not allowed.

Let me reconsider. Maybe the target doesn't need the base in s0 for all three sites; the diff shows 6 replacements: two per site: move->addiu at 107,109; 212,214; 317,319. So yes, all three sites: target has addiu per call, mine has move.

Could we instead keep mb as base by doing the +24 on separate variables and making the *sum* not live across the call? E.g.:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
What if the first call's arg is computed as `mb + 0x18` into a variable `a` and the second as `mb + 0x18` into variable `b`? Still same expression.

Think about cse's invalidation: cse's hash entry for the constant address `(plus (symbol_ref D_800AF630) (const_int 24))` — how is it represented? Actually for a symbol address, gcc may keep it as a constant, and each use is an insn with a CONST operand, which cse's `insert` would hash. The register form arises when the address must be materialized. cse's `cse_insn` for a `set (reg) (symbol_ref+const)` creates a register equivalence. For a *use* inside an add (`set (a0) (plus (reg mb) 24)`) where mb's value is the symbol constant, combine/cse may forward.

Actually the folding from `mb + 24` to a constant happened in cse1: `mb = (u8*)&D_800AF630` makes mb's reg_equiv a constant. Then `mb + 24` is simplified to the constant address `&D_800AF630 + 24`. Then both call args become that constant; cse materializes once.

To prevent cse from knowing mb's constant value, we need mb's assignment to not be a simple constant. If we could load the address from a table... but the symbol is fixed.

Idea: make mb = (u8 *)&D_800AF630 via a pointer arithmetic chain that cse doesn't constant-fold at the tree level but combine folds later? E.g. `mb = (u8 *)((s32)&D_800AF630);` — cast, same. `mb = (u8 *)&D_800AF630; mb = mb + 0;`? identity.

Hmm, maybe use `param_4` or `param_3` to compute the address? No.

Alternative: split the call argument through a struct field access:
```
mb = (u8 *)&D_800AF630;
func_8004914C(&((S_AF630 *)mb)->f18);   /* struct field at 0x18 */
```
Still same.

Wait — what if we make the *base* variable the result of a call or of an opaque pointer, but at runtime equals D_800AF630? No.

Hmm, maybe the answer is different: maybe we can make the target's shape by NOT having mb at all but using two separate constants? Target literally: lui s0,%hi; addiu s0,%lo; then addiu a0,s0,24 twice. The base in s0 comes from one materialization of the symbol. If we write:
```
func_8004914C((u8 *)&D_800AF630 + 0x18);
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
gcc materializes &D_800AF630 in s0 and does addiu a0,s0,24 for each — exactly target! Because the sum is not a "constant" it can hold across the call cheaply? Hmm, actually it may still compute s0 = &sym+24 once. Let's test: no mb variable, direct array expressions.

Wait, but c1 already effectively does this via mb. Let's test direct without mb:
```
    func_8004914C((u8 *)&D_800AF630 + 0x18);
    func_800491AC((u8 *)&D_800AF630 + 0x18);
```
That's variant g. Also:
```
    func_8004914C((u8 *)D_800AF630 + 0x18);
```
D_800AF630 is declared `extern u8 D_800AF630[]` so `(u8 *)D_800AF630 + 0x18`. Let me generate.

Also try passing `D_800AF630 + 0x18` (array decay) directly.

Let me add variants g,h,i:
g: drop mb entirely; both calls with `(u8 *)&D_800AF630 + 0x18`.
h: first `(u8 *)D_800AF630 + 0x18`, second `(u8 *)&D_800AF630 + 0x18` (different spellings).
i: `func_8004914C(D_800AF630 + 0x18); func_800491AC(D_800AF630 + 0x18);`

Also j: mb = D_800AF630; calls mb+0x18 — D_800AF630 decays to pointer; same as before probably.

Let me test g,h,i.
