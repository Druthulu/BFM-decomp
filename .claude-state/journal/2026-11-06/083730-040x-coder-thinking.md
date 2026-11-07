---
ts: 2026-11-06T15:37:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_riSM9HkbwOyxiylVYMJJ
---
Look at lines 5615-5616: `{ void *r4; r4 = &D_800AF648; func_8004914C(r4); }` — using a scoped block and a different variable per call! And 5808-5809 same with D_800AF648_b. These are other functions' idioms. But those pass &D_800AF648 directly, not +0x18.

Hmm, in our function, could the "intended" source be two separate scoped variables:
```
{ u8 *r4 = (u8 *)&D_800AF630 + 0x18; func_8004914C(r4); }
{ u8 *r5 = (u8 *)&D_800AF630 + 0x18; func_800491AC(r5); }
```
Would gcc still cse the two constants? The variables are block-local, each set once. cse would fold each to the constant &sym+24 and share. Probably still 6.

What about using the pattern from 6199-6200: `func_8004914C(&D_800AF648); func_800491AC(&D_800AF648);` — two direct calls with the same address. That function presumably matches without a launder! So how does that produce two materializations? Let's check that function (func_8018B3D0 at 6177). It calls with &D_800AF648 (no +0x18). Maybe the target there has a single materialization? Let me check by extracting and looking at disassembly? It's not our item. But it suggests the idiom: two direct &sym calls may or may not share.

The difference: +0x18. For `&D_800AF648`, the address is the symbol itself — gcc may materialize it once in s0 and both calls use move a0,s0 (matching that function's target presumably). For our target, it's addiu per call.

Hmm so the target explicitly adds per call, meaning the base is held and the add done twice. The launder is what does it.

Let me look at how the launder works more precisely in gcc 2.7.2. The asm `__asm__("" : "=r"(mb) : "0"(mb))`: output operand is a register (new value), input tied to same. This creates an insn with a SET of a new pseudo (or the same?) to an asm_operands. The value is unknown. So after it, `mb` (the variable) is in a register with unknown value. gcc has to compute mb+24 = addiu.

In plain C, to get "unknown value in a register but actually the address", we can... hmm, what if we use a *union* to reinterpret? No.

What about making mb a `u32` variable? `u32 m = (u32)&D_800AF630;` then `(u8*)m + 0x18`? cse folds the cast/constant. Same.

What about the address of a global through a variable index known to be 0? Identity launder, disallowed.

Hmm. Let me reconsider: maybe we don't need to replicate the launder's effect exactly; maybe another real-C restructuring produces the same target code. The target: base in s0, two addiu. Perhaps if the base pointer is *also used* as a base for something else after the calls (making the base live), gcc keeps the base and computes sums per use. Let's test: add a use of mb after the second call, e.g. `func_8004914C(mb + 0x18); func_800491AC(mb + 0x18); mb[0] = mb[0];` — but that's extra code (changes insns). Target has 397 ins = mine 397; adding code would break count unless it replaces something.

Actually wait — maybe the target's base in s0 IS used for other things elsewhere? The diff is only 6 insns (2 per site), so the rest matches. So the only difference is the add. So any restructuring must produce exactly that.

Think about cse's constant handling again. When `mb = &D_800AF630` and `mb+24` used twice, cse computes a register holding &sym (mb) then... why does the *sum* end up in s0 rather than base? Because cse replaced both `mb+24` uses with a single register holding the sum (computed once before the first call). So cse materializes the sum.

If the base were used (mb itself) somewhere else in between, cse would keep the base in a register and then the sums would be computed per use? Not necessarily.

Hmm — what if we make the first call use `mb` (base) and the second `mb+0x18`? No, target has both addiu.

Let me try: use a *second* base variable that's live: 
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
func_80017254(mb);   // extra use
```
This adds a call (changes insns). No.

OK, different approach: maybe there's a way to get cse to not fold `mb+0x18` into a constant: make mb's declared type different such that the addition isn't a constant fold? E.g. `u8 (*mb)[]`? no.

Wait, maybe use pointer arithmetic on a *different-sized* type: `func_8004914C((u8 *)mb + 0x18)` vs `func_8004914C(mb + 0x18)` where mb is `u8*` — same.

Hmm, let me look at the actual RTL. Maybe use hdump to see cse behavior. But time budget: 20-30 min per item. We're maybe 10 min into item 2.

Let me check the actual target for the FIRST pair of calls in the function (lines 6048-6049): `func_8004914C((void*)(((s32*)param_1)[8] + 0x34)); func_800491AC((void*)(((s32*)param_1)[8] + 0x34));` — this pair is at the function start. Does it match (it's in the 397 ins and score 0 diff only at the 3 sites)? Yes, no diff at those. So for param_1-based address, gcc does two adds (since param_1[8] is a load, runtime value) — good.

So the difference is purely the constant symbol.

Idea: express &D_800AF630 + 0x18 through a *runtime* value that cse can't fold but that equals the address — e.g., use the address of the array's element: `&D_800AF630[0x18]` — same constant.

What about using a pointer to a struct with a flexible member? Same.

Hmm, what if we declare `mb` as `void *` and use `(u8 *)mb + 0x18`? Same.

Let me examine how the launder-free c1 is compiled and whether cse's sum register is really s0 across calls. Yes.

Could the dead reset work if placed BEFORE the second call but the second call uses mb? Like:
```
mb = &D_800AF630;
f(mb + 0x18);
mb = 0;
mb = &D_800AF630;    // re-set
g(mb + 0x18);
```
Tested variant d → 6.

What if the dead reset is `mb = 0;` then second call uses a *different* variable mb2 assigned &D_800AF630 — tested c? c was mb = base+0x18. Let me try:
```
mb = &D_800AF630;
f(mb + 0x18);
mb = 0;
mb2 = &D_800AF630;
g(mb2 + 0x18);
```
Hmm the cse hash entry for (plus sym 24) persists regardless of the variable.

Let me think about cse internals: cse's hash table entry for `(plus (symbol_ref) (const_int 24))` — when it first sees `mb + 24` (with mb's reg_equiv being the constant sym), it folds to the constant expression and inserts it. On second occurrence, lookup finds the entry. The entry's register is s0. It stays valid across the call because s0 is callee-saved... but cse's validity is about whether the register has been modified. The call doesn't modify s0 (callee-saved), so valid.

The launder's asm writes mb's register with unknown value → but wait, the asm output is the SAME register as input ("0"). So the register holding &sym is overwritten with an unknown value → the hash entry's register is invalidated → second `mb+24` cannot reuse it → recompute addiu. But the physical register still holds the base... because the asm is empty, it doesn't change it. So the target has s0 still holding base.

For plain C: we need to convince cse that the register's value changed, without changing it. That's exactly what the dead-reset does for non-constant values, but here cse has folded the sum into a constant, so the "register" is the sum's register.

Hmm! Wait. If we dead-reset mb after the first call, cse invalidates mb's equivalence, but the sum's register (s0) holds the sum — no. Let me reconsider what s0 holds in c1: s0 = &sym+24. The two call args are move a0,s0. cse merged the two `mb+24` into one register. The base &sym was never in a register.

With launder: mb is unknown, so `mb+24` is a register add computed per call, and mb's register (s0) holds the base.

So to get plain C to keep the base in a register and add per call, we need cse to not fold `mb+24` to the constant. That requires mb's value not be known as the constant at the time of the additions. Since `mb = &D_800AF630` is a constant assignment, cse will know.

Unless we make the assignment happen in a way cse can't see: e.g., assign mb inside a loop? cse handles loops (it's per-EBB, and this is one EBB). 

What about assigning mb through a pointer-to-pointer local? Adds loads.

What about `mb = (u8 *)&D_800AF630;` where D_800AF630 is declared as a *local extern array* vs file-scope? Same.

Could we use a *different* symbol that the linker resolves to the same address? Like an alias `extern u8 D_800AF630_alias[] __asm__("D_800AF630");` — the symbol_ref would be the same string → same symbol_ref rtx? GCC creates SYMBOL_REF by name with a shared hash; so same.

Hmm what if the base is the address of a *structure member* computed as `&((S*)&D_800AF630)->f18`? Same constant fold.

OK here's another angle: maybe cse's constant folding of `mb+24` happens because mb's reg_equiv is a constant and `plus` simplification is done by cse's `simplify_rtx`? Actually cse folds `(plus (reg) const)` only if the reg is equivalent to a constant. To prevent the reg_equiv from being a constant, the assignment must not be a simple constant. 

What if we assign `mb = (u8 *)&D_800AF630;` and then modify it in a way that's real C but doesn't change the value? That's an identity launder — disallowed.

What if the C uses a struct copy that gcc lowers to address+offset but cse doesn't see as constant? Hmm.

Let me look at other similar launder cracks in moves for the same mechanism ("cse unifies the second ... through the class of its constant value"). Search moves for "constant value" or "two adds".
