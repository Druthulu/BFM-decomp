---
ts: 2026-11-07T00:51:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VNSy5Uhn3W8d4pNPJ5qU
---
Score 6: mine has `move a0,s0` where the target has `addiu a0,s0,24`. So cse folded `mb + 0x18` into mb (with s0 = &D_800AF630 + 0x18, i.e., the base already includes +24), so the arg is a plain move.

So in mine, `mb = (u8*)&D_800AF630; ... mb + 0x18` — cse computed `mb+0x18` once and kept it in s0 across the calls, so the argument is `move a0,s0`.

The target: s0 = &D_800AF630 (no +24), and each call gets `addiu a0,s0,24`.

So I need cse to NOT merge the two `mb + 0x18` computations, and to keep the base (not the sum) in s0.

Real-C moves:
1. Make `mb`'s value unknown after the first call so the second `mb + 0x18` must be recomputed: that's what the launder does.
2. Alternatively, make the *source* not use mb+0x18 twice but keep the base: e.g., write `func_8004914C(mb + 0x18); func_800491AC(mb + 0x18);` — that's what it is.
3. Use a different variable for the second call: `mb2 = (u8 *)&D_800AF630;` — cse would equate the constants.

Hmm, the note says cse unifies via the *constant value* class of `(const (plus D_800AF630 24))`. Interesting: so cse replaced `mb + 0x18` with the constant address `D_800AF630+24`, and then s0 holds that constant.

What if `mb` is loaded from memory rather than being a constant? E.g., if the source used a global pointer variable: `mb = D_800AF630_ptr;`? Then cse would have a MEM expression, not a constant, and the call would invalidate it (memory), forcing a reload → but the target keeps s0 across the call (s0 = &D_800AF630 is a callee-saved reg, loaded once).

Hmm, in the target, s0 = the address of D_800AF630 (constant, held in a callee-saved reg across calls). Each call: addiu a0,s0,24.

In mine, s0 = &D_800AF630 + 24 and the arg is a move.

So the difference: which value cse decides to keep. The target keeps the *base*; mine keeps the *sum*.

Real-C ideas:
- Make the two uses have different offsets that happen to be equal? No.
- Make the first use `mb + 0x18` and the second `(mb + 0x18)` computed from a *different* base expression, e.g. the second uses `&D_800AF630 + 0x18` spelled directly: `func_800491AC((u8 *)&D_800AF630 + 0x18);` — cse still equates.

Hmm. What breaks the cse constant class? The comment says: "an unknown value after the first call keeps two adds off one call-crossing base". So the launder makes mb's value unknown (the asm output constraint "=r" gives mb a new unknown value), so `mb + 0x18` can't be folded to a constant.

Real-C equivalent: a 2nd set of mb with an unknown value that's actually the same. E.g.:

```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630;   /* 2nd set, same value */
func_800491AC(mb + 0x18);
```
cse would fold the second assignment to the same constant and merge. Since it's a constant, cse sees them as equal.

Unless the 2nd set is not a constant: e.g., `mb = mb;`? identity.

Hmm, what about deriving mb from something the compiler can't fold: e.g., `mb = (u8 *)((s32)mb);` — identity cast, folded.

What about `mb = (u8 *)((u32)param_2 & 0) + (u32)&D_800AF630;`? That's an identity launder (banned).

Hmm. What about a *legit* real computation: the base could be computed from a variable that holds the same address at runtime. E.g., is there a global variable holding &D_800AF630? Not that we know.

Alternative approach: change the *shape* so cse can't fold: e.g., pass `mb + 0x18` where mb is re-loaded from a local variable that cse treats as memory? 

Hmm, what about the "struct-member" trick: read the base through a struct member so the value is a MEM load:
```
u8 **pp = &D_800AF630_ptr; ...
```
No such symbol.

OK, what about a different approach entirely: the target keeps s0 = base and two addiu. What if we write the source so the *compiler* naturally does that: e.g., use a local `u8 *base = (u8 *)&D_800AF630;` and then two calls with `base + 0x18`. cse folds the sum into a constant and keeps that.

What if we use `mb[0x18]`... no, we pass a pointer.

What if the two calls use different expressions that are equal at runtime but not foldable: e.g., `mb + 0x18` and `mb + (0x10 + 8)`? Folds.

Hmm, what about `func_8004914C(mb + 0x18); func_800491AC(&mb[0x18]);`? Same RTL.

Hmm.

Let me look at the cse comment in the source: "cse unifies the second `mb + 0x18` through the class of its constant value `(const (plus D_800AF630 24))`, cse.c:6766-6850 + :7195-7225".

So cse substitutes the *constant* (the address) for the expression. The constant is in cse's table as an equivalent constant.

Real-C ways to prevent cse from knowing mb's value:
(a) make mb's value come from a non-constant source (a load from memory or a function call result).

Idea: what if `mb` is loaded from a *global* pointer variable that exists? Let me check what symbols exist: `D_800AF630` is `u8[]`. Is there a global that holds &D_800AF630? Let me search the TU/src for a pointer to D_800AF630.

Hmm, that's speculative.

Idea (b): use a *different* variable for the second call, initialized from a call's return value? No.

Idea (c): make the base `mb` be computed from `param_1` or another runtime value that equals the constant... no.

Hmm, wait. Let me reconsider: maybe the real-C fix is not about mb at all but about the ORDER/shape: the target has `addiu a0,s0,24` in the *delay slot* of the jal. Mine has `move a0,s0`. So mine passes the constant sum.

What if I write the calls with an explicit intermediate:
```
func_8004914C((u8 *)&D_800AF630 + 0x18);
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
Same.

What if the *first* call uses `mb + 0x18` and the second uses `mb + 0x18` where mb was re-assigned between from a *runtime* source that's still the same address... 

Ooh — here's a thought: what about `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); mb = (u8 *)&D_800AF630; func_800491AC(mb + 0x18);` — cse folds both to constants. No good.

What about making the base an *unknown* value at RTL that is nonetheless the address: e.g., passing `&D_800AF630` through a function call? No.

Hmm, what about the "dead reset" C0414 applied to mb: `mb = (u8*)&D_800AF630; ...; mb = 0; ... mb = (u8*)&D_800AF630;` — the middle `mb = 0` is dead and deleted by flow. But cse: after `mb = 0`, the equivalence `mb == &D_800AF630` dies; then the re-assignment sets it again — and cse would again know the constant. So the second `mb + 0x18` folds to the same constant. No good.

Unless... hmm.

OK, different idea: **use the two calls with different base variables that cse can't equate because they're loaded from memory**. For instance, if `mb` were a `u8 *` stored in a local variable and read back... locals are registers.

What about a global? If the TU has a global pointer to D_800AF630, we could use it. Let me grep for D_800AF630 in src/.

Actually, wait. Let me reconsider the problem: maybe the target's shape arises when the two `+0x18` are computed *at the call sites* (not folded), which happens if cse doesn't have the constant. But another way: if the *argument* is computed from a base that lives in a register (s0) — e.g., if the source is:

```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
The compiler could either (a) keep mb in s0 and do addiu twice, or (b) keep mb+0x18 in s0 and move. The target does (a).

Which one the compiler picks is cse's choice: it substitutes the constant expression.

Hmm, what if the two calls are given *different* expressions like `mb + 0x18` and `mb + 0x1C - 4`? Folds.

What about using a different offset type, e.g., `(u8 *)((u32 *)mb + 6)`? Folds to +24.

What if the base is accessed as `&D_800AF630[0x18]`? Folds.

OK, what about the "2nd set" with a genuinely different value that is later restored? E.g.:

```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)(param_1 + 0);   /* a real 2nd set with a runtime value */
mb = (u8 *)&D_800AF630;     /* restore */
func_800491AC(mb + 0x18);
```
The intermediate assignment changes mb to a runtime value, but then it's restored to the constant, so cse knows the constant again at the second use. No.

Hmm.

What if the second call's base is derived from the *result* of a real computation that the compiler can't fold, e.g.:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC((u8 *)((u32)mb + (0x18 & 0x1F)));   /* identity? */
```
That's an identity launder — banned.

Hmm.

Let me look at this from a different angle: what does the *real original C* look like? This is a decompiled game function. The launder was added by the decomp author because plain C didn't match. The original C probably was:

```
func_8004914C(&D_800AF630[0x18]);
func_800491AC(&D_800AF630[0x18]);
```
or with a local. And the ORIGINAL compiler produced the target from it. So the target IS reproducible from plain C — the launder is just a workaround for a different issue (maybe the decomp author's C differs).

Hmm, but if the target came from the original compiler with the original C, then some plain C reproduces it.

Let me think about what determines "addiu a0,s0,24" vs "move a0,s0": the constant s0 holds. If cse doesn't fold `mb + 0x18` to a constant, the compiler would keep mb (the base) in s0 and compute the sum at each call.

When does cse fold `(plus (reg mb) (const 24))` into a constant? When mb's value is known as a constant. `mb = (u8*)&D_800AF630` → known.

But note: mb is a *local* variable assigned once. If the source didn't have the local at all, e.g.:
```
func_8004914C(&D_800AF630[0x18]);
...
func_800491AC(&D_800AF630[0x18]);
```
Then the expression is `(plus (symbol_ref) 24)` — a constant address directly. The compiler would materialize the address once (in s0) and... hmm, the target shows s0 = D_800AF630 base and addiu +24 twice. That suggests the compiler kept the SYMBOL (not the sum) in s0.

Interesting! When the address is `(symbol_ref D_800AF630 + 24)`, MIPS's `lui/addiu` expansion produces `lui s0, %hi(D_800AF630); addiu s0, s0, %lo(...)`. For the address D_800AF630+24, the expansion is `lui s0,%hi(D_800AF630); addiu s0,s0,%lo(D_800AF630)` (the +24 folded into the LO16!) — that would give `lui s0, hi(D_800AF630+24); addiu s0,s0,lo(...)`, i.e., a different base value.

Hmm, the target shows: `lui s0,0x0 (D_800AF630)` and `addiu s0,s0,0 (D_800AF630)`? Let me check the actual instructions around c6b8-c6d4 in the target.

Let me look at the target listing around that region.
