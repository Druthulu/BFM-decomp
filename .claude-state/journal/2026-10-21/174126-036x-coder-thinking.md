---
ts: 2026-10-21T23:41:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_skedmafD9o2VuxRzZdpc
---
Now it's crystal clear. In mine:
- s1 = param_1 (target's s0)
- s0 = sp+24 (target's s1 = loop counter)
- target's s1 = loop counter `move s1,zero`, `addiu v0,s1,1`.

In mine, s0 = sp+24, and the loop counter is in... mine[26] `move s0,zero` — so mine uses s0 for the loop counter! And s1 = param_1.

So mine: s0 = sp+24 initially, but later s0 is REUSED for the loop counter (after the address is dead). And s1 = param_1.

Target: s0 = param_1, s1 = loop counter.

So in mine, param_1 is in s1 and the loop counter in s0; in target, param_1 in s0 and counter in s1. Plus the address.

So the register allocation differs: in the target, s0 = param_1 (the only callee-saved besides the counter). In mine, s1 = param_1 (so s0 was taken by the address).

So it's ALL caused by the sp+24 pseudo taking s0. If we remove that, mine would have s0 = param_1, s1 = counter — matching the target exactly!

So: 28 of the 29 mismatches are just the s0/s1 swap. If I fix the address issue, the score should drop to ~1 (the `move a0,s0` vs `addiu a0,sp,24`).

So the single fix: prevent gcc from putting sp+24 in a callee-saved register.

How? Options:
(a) Break the CSE so gcc computes the address twice, each time directly into an argument register.
(b) Make the address's live range not cross a call.

For (b): the address is used at insn 4 (a1 for call 1) and insn 15 (a0 for call 2). The call at insn 12 is between them. So the value IS live across a call → needs callee-saved.

For (a): break the CSE.

Now, how does the ASM do it? `__asm__("" : "=r"(p1) : "0"(p1))` — the asm forces p1 into a register. Then gcc's value for p1 is the asm output (a hard reg). Hmm, but then p1's value is in a hard register which must survive the call at 12 — a hard reg can't be callee-saved... gcc would move it to a callee-saved reg. Hmm.

Wait, no. The asm is BEFORE the call. The asm output reg p1 is used at the call (a1). Then p1 is dead. So the asm output doesn't live across the call. And the SECOND use (sp10+4 for call 2) is a separate expression → separately computed. But then why doesn't gcc CSE the asm's p1 value with sp10+4? Because the asm output is a hard register (not a cse-able pseudo) — cse can't rewrite the asm's operands.

Hmm, but then p1's value in the asm input is "0"(p1) which is the address; gcc allocates a reg for it: e.g. $a1, and the address is materialized by `addiu a1,sp,24` right before the asm? Then the asm is a no-op, and the `addiu a1,sp,24` is the materialization. Then a1 = p1 already.

So with the asm, gcc computes the address into the argument register directly, and there's no shared pseudo → no s0. And for the second use, `sp10+4` → another addiu.

So the crux: gcc must not create a shared pseudo for the two identical address expressions.

In real C, how? We need the two expressions to differ in RTL. Since both are the address of the same stack slot + 8, the RTL must differ. Options:
- Different base *objects* at the same address: a UNION! `union { u16 a[6]; u16 b[6]; } sp10;` — the address of sp10.b[4] is (plus (symbol_ref sp10) (const 8)) — same. Hmm.

Unless... the union member is accessed as a MEM with MEM_IN_STRUCT_P. When you take the ADDRESS of a union member, the rtx is (plus (symbol_ref) (const 8)). Same.

- What if the two expressions use different *pointer variables* that are separately assigned but whose values are NOT CSE-unifiable because the assignments are in different blocks? cse is global.

Hmm, hold on. What if the value of one of them is loaded from memory? E.g., what if the ORIGINAL source stored sp10+4 into a local pointer variable, and the variable lives in a stack slot? Then the use would be `lw`. No.

What if the second use is `p1` where p1 was assigned `sp10 + 4` and the first use is `sp10 + 4` — and the ASSIGNMENT `p1 = sp10 + 4` creates a second set of the *address pseudo*? Hmm: `p1 = sp10+4` creates a copy; the address pseudo gets set once; p1 gets set to it. Then `func_800D20C0(sp10, sp10+4, 1)` and `func_800D23D0(p1)`. cse: the address pseudo has 1 set; p1's value = the pseudo. cse substitutes → the two uses refer to the same pseudo → live across the call → s0. That's c1 (29).

What if the order is: `func_800D20C0(sp10, p1, 1)` where p1 = sp10+4 assigned BEFORE, and `func_800D23D0(sp10+4)`? That's b1-like (29).

Hmm.

What about making the address NOT a frame address but something gcc computes differently — e.g. what if the array is accessed via a pointer to a pointer?

RADICAL IDEA: What if we give the compiler a *different* but equivalent way to compute sp+24 — e.g. `sp10 + 4` where sp10 is `u16 *` pointing to a heap/stack array? no.

KEY INSIGHT ATTEMPT: gcc's CSE unifies two expressions if they're structurally equal after simplification. But if one of them is a **MEM with MEM_IN_STRUCT_P** and the other is a plain **MEM**, cse may keep them separate (different rtx: MEM vs MEM with MEM_IN_STRUCT_P flag). Let's think: for a local array `u16 sp10[6]`, `sp10 + 4` as a pointer value = (plus (symbol_ref sp10) (const 8)). If instead we have a struct local:
```
struct { u16 x[6]; } s;
```
`s.x` is a MEM (with MEM_IN_STRUCT_P) at offset 0 of s. `&s.x[4]` = (plus (symbol_ref s) (const 8)). Same.

What if the pointer expression is derived from a MEM value rather than a symbol_ref? E.g.:
```
u16 *base = &sp10[0];
... base + 4 ...
```
base's value in a register → (plus (reg) (const 8)). The other use `sp10+4` = (plus (symbol_ref) (const 8)). NOT structurally equal → cse won't unify!! But then base must live in a register across the call → base would be in a callee-saved reg → same problem (s0 = base = sp+16, then `addiu a1,base,8`).

Unless gcc recognizes base == sp+16 and uses the frame pointer... Actually! gcc often optimizes `u16 *base = &sp10[0];` — the local `base` is a copy of the frame address; gcc's local-alloc may fold it back to the symbol_ref. If it folds, then base+4 == sp10+4 and CSE unifies.

Hmm, hmm. But if gcc DOESN'T fold, we'd get an extra register.

OK, ANOTHER ANGLE: what if the difference is not about the address at all but about how the *frame* is laid out? Look: target has `addiu a0,sp,16` and `addiu a1,sp,24` — and the sp10 array at sp+16. But what if in the target's original source, the array was NOT declared as an array but as THREE separate u16 variables?! E.g.:

```
u16 w0, w1, w2, ...;
```
Hmm, but the target stores `sh zero,20(sp); sh zero,18(sp); sh zero,16(sp)` and loads `lhu v0,26(sp)`. With separate variables at sp+16,18,20 and something at sp+24,26.

AH, THIS IS INTERESTING! What if the original source had:
```
u16 a;  // sp+16
u16 b;  // sp+18
u16 c;  // sp+20
u16 d;  // sp+22
u16 e;  // sp+24
u16 f;  // sp+26
```
and the code was:
```
a = 0; b = 0; c = 0;   // hmm, order: target does sh zero,20(sp); sh zero,18(sp); sh zero,16(sp) → c,b,a
func_800D20C0(&a, &e, 1);
func_800D23D0(&e);
D_801C7540 = f - 0x400;
```
Then `&e` = (symbol_ref) + 4 or (plus (symbol_ref) (const 4))? For a scalar local, the address is (symbol_ref) with a frame offset, and `&e` would be (plus (frame_pointer) (const 20))? In gcc, `&e` for a local scalar = (symbol_ref e) → but in RTL it's (plus (reg sp) (const 20)) — the address of a local is a frame offset constant, computed as (plus (reg sp) (const 20))? Actually gcc represents local addresses as (symbol_ref) with a frame offset attribute, and in the RTL after reload it becomes (plus (reg sp) (const N)) or (reg sp) with offset. Hmm.

Key: two DIFFERENT scalar variables at different offsets → &a and &e are different addresses. But we need &e twice.

Hmm, what about: `func_800D20C0(&a, &e, 1)` and `func_800D23D0(&e)` — same &e twice → CSE → same problem.

BUT: what if the second call's argument is a DIFFERENT variable that happens to be at the same address? Impossible.

Hmm, but what if the original was:
```
u16 *p = &e;
func_800D20C0(&a, p, 1);
func_800D23D0(&e);
```
Now `p` is a copy of &e, and `&e` is a separate expression. cse: p's value = (&e) and the second use is &e → CSE unifies → p's pseudo = &e's pseudo. Same problem. Hmm! Unless the asm...

Hmm OK, what if the original was:
```
u16 *p = &e;
p = p;  // no
```

Let me look at this from the "how would the target's compiler have produced it" angle: the target was compiled by the ORIGINAL game compiler (not gcc). It produced `addiu a0,sp,16; addiu a1,sp,24` and `addiu a0,sp,24`. A naive compiler that doesn't CSE across a call would produce exactly this. So the original C was likely:

```
func_800D20C0(sp10, sp10 + 4, 1);
func_800D23D0(sp10 + 4);
```

and our gcc CSEs. The lever (launder) was added by the decompiler to force gcc to match. Our job: find a real-C way.

Since the same address is needed twice with a call in between, the ONLY way to prevent gcc from sharing is to have the two expressions be different rtx. The classic trick: make the second one depend on a value that gcc can't fold, but the result is the same address. E.g.:

```
u16 *p = sp10 + 4;
u16 *q = p;    // copy
func_800D20C0(sp10, p, 1);
func_800D23D0(q);
```
cse: q = p (copy) → q's value = p's value = the address pseudo. Then uses of p and q both → the same pseudo. Still shared.

Hmm, unless the copy `q = p` happens and then gcc's local-alloc gives p and q separate registers, both holding the address → then two registers → 2 addiu? No, it'd be `move`s.

OK, think about C0505: "A named derived pointer `q = p - k` that cse keeps as a REGISTER address (find_best_addr, cse.c:2656-2721) — the `la` lever."

Hmm — "the `la` lever" means: the ORIGINAL had `la` (load address) macros? No, "la" as in load-address pseudo.

Hmm, and: "A twice-set pointer `p = &D; p += x;` as one expression (R36 — the frame-only residual: combine leaves the ref count, reload gives a slot, combine.c:2305-2337, reload1.c:2327-2352)."

Interesting: "A twice-set pointer p = &D; p += x; as ONE expression". So `p = &D; p += x;` written as one expression `(p = &D) + x`? Hmm, R36 is about combining.

OK, let me try yet another approach: what if we make the SECOND use of the address come from a *different* source that is genuinely different but equal — e.g. compute the address of the array END and subtract:

```
u16 *p1 = &sp10[6];   // sp+28
...
func_800D20C0(sp10, p1 - 2, 1);
func_800D23D0(sp10 + 4);
```
p1-2 = (plus (symbol_ref) (const 8)) after folding → same. gcc folds pointer arithmetic on frame addresses. Yeah.

Hmm hm. What if the base is not a frame address but a **pointer to a static**? no.

NEW STRATEGY: maybe instead of preventing the CSE, we can *use* the CSE but make the register allocation match. I.e., accept that sp+24 lives in a register, but arrange for the register to be the one the target uses... no, the target has no register holding it.

ALTERNATIVE STRATEGY: change the *frame layout* so that the address doesn't need a register. E.g., if sp10 were at sp+24 instead of sp+16... no, the target's offsets are fixed.

Hmm, WAIT. What about this: the target's `addiu a1,sp,24` and `addiu a0,sp,24` are both rematerializations of the SAME pseudo — gcc CAN rematerialize a pseudo if the pseudo is "rematerializable"! In gcc, a pseudo assigned a constant (like a frame address) can be rematerialized by the register allocator (reload.c: `reload_remat`), producing `addiu a0,sp,24` twice!

So maybe the issue is just that our gcc's local-alloc decided the pseudo is NOT rematerializable but kept it in s0, whereas the original game compiler did rematerialize.

Why would gcc not remat? Because the pseudo came from a local VARIABLE assignment (p1 = sp10+4) or from a MEM.

Hmm — but b1.c (no variables, direct sp10+4) also produced s0. So even a pure constant address expression was kept in s0.

Hmm! Interesting. So gcc created a pseudo for `sp10+4` (used twice) and allocated it to s0 rather than rematerializing. Because rematerialization in gcc happens in `reload` only for pseudos that are `reg_equiv` to a constant — and a frame-address plus constant is NOT a simple constant, it's an expression involving the frame pointer. gcc's `reload_remat` requires the reg_equiv to be a constant or a "reg" ... Actually `find_reg_uses`/`reload` handles `CONSTANT_P (reg_equiv)` — a plus expression isn't a constant.

But `local-alloc`'s "address giv" handling: gcc's local-alloc has special handling for addresses (the `la` pseudo). And there's `find_best_addr` in cse.c which finds a better address expression.

Hmm — so how do we get gcc to emit `addiu a0,sp,24` twice? We need the address pseudo to be *rematerializable* or to have 2 sets.

The cookbook §349 says: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY to make `n_times_set > 1` — that kills both loop.c's INVARIANT HOIST and the ADDRESS GIV, reproducing a REMATERIALISED `addiu $aN,$sp,K`".

So: making n_times_set > 1 for the address pseudo → the ADDRESS GIV is killed → the value gets rematerialized. But in our case, a "base pointer" would be a variable holding a base address; the GIV would be that variable.

So: introduce a base pointer variable!
```
u16 *base = sp10;   // base holds the address of sp10
u16 *p1 = base + 4;
```
Hmm, then p1 = (plus (reg base) (const 8)).

Hmm, but what does the TARGET need? `addiu a1,sp,24` — the addend is sp+24 directly, so the base is $sp. If base is a variable holding sp+16 in a register r, then p1 = r+8 → `addiu a1,r,8` — not matching.

BUT: if base is a variable whose value is the frame address and gcc rematerializes base itself as sp+16... then p1 = sp+16+8 = sp+24. gcc's arithmetic: (plus (plus (reg sp) (const 16)) (const 8)) → (plus (reg sp) (const 24)) — the ADD_RANGE/ADDR_EXPR folding could combine. Actually if base is a pseudo holding (plus (reg sp) (const 16)) and p1 = base + 8, then RTL is (plus (pseudo_base) (const 8)). To emit `addiu a1,sp,24` gcc would need to know pseudo_base = sp+16 and fold. gcc's `simplify_rtx` can do this if the reg_equiv is known: `lookup_reg(base)` → (plus (reg sp) (const 16)), then simplify (plus (plus (reg sp)(const 16)) (const 8)) → (plus (reg sp) (const 24)) → `addiu a1,sp,24`!!

That's promising! If base is a local variable that gcc keeps as a pseudo with reg_equiv = (plus (reg sp) (const 16)) (i.e. the address of the local), then base+4 folds to (plus (reg sp) (const 24)) and gcc emits `addiu a1,sp,24` — and if the pseudo for that expression is used twice, cse would still unify it into one pseudo... and then it'd be in s0. Hmm. BUT if it folds to a constant expression at the RTL level, then it's not a pseudo at all but a literal expression evaluated at each use → two `addiu`s!

Hmm, but cse would create a pseudo for the shared expression anyway (cse creates pseudos for expressions used more than once, unless rematerializable).

Hmm. But if the expression is (plus (reg sp) (const 24)), gcc's cse might treat it as rematerializable since it's "cheap". Actually gcc's cse has `record_cse` and it does create a pseudo for any non-constant expression used ≥2 times, BUT the "birth" of the pseudo happens in cse's `cse_record`... Actually gcc's cse does create pseudos for common subexpressions. However, if the expression is a simple `plus` of a register and a constant, gcc's `cse` has a special case: `cse.c` `record_cse` → `if (GET_MODE... )`. Hmm, I recall gcc's cse does NOT create a pseudo for a `plus` of a reg and a constant when the value is in a register that is cheap to recompute? Not sure.

But the target shows it recomputed twice, so *something* allowed it.

ALTERNATIVE MUCH SIMPLER IDEA: What if the pseudo holding sp+24 has 2 SETS in the original? Then cse won't unify the two uses (per §145(b): a second set kills the equivalence chain) → each use is computed separately → two addiu's! And the value never needs a register!

So: give the address pseudo two sets. E.g.:
```
u16 *p1;
p1 = sp10 + 4;
... 
p1 = sp10 + 4;   // second set
```
But that's an identity assignment (banned-ish).

BUT §145(b) says a second set via "in-place `p += K`" or "`p = r;` copy". So a *copy* `p1 = p2` where p2 holds the same address would give p1 two sets! And a copy is a legitimate "pointer reuse" move (in the C0505 catalog: "pointer reuse").

Hmm, but `p2 = p1; p1 = p2;`? Silly.

Hmm, what about the natural restructure: the original source might have had a single pointer variable p that is used for both calls, and p got a second set naturally. E.g.:

```
u16 *p = sp10 + 4;
func_800D20C0(sp10, p, 1);
p = p;   // no
```

What about: the first call uses p, and between the calls p is re-assigned to the same value via a different route:
```
p = sp10 + 4;
func_800D20C0(sp10, p, 1);
p = &sp10[4];
func_800D23D0(p);
```
Hmm, `&sp10[4]` and `sp10+4` are the same rtx, so p's two sets have the same value → gcc's cse: p has 2 sets, each with the same value. The uses: use1 reads set1, use2 reads set2 → NOT unified! So gcc emits:
- use1: addiu a1,sp,24 (from set1)
- use2: addiu a0,sp,24 (from set2)
And no pseudo is live across the call!!!

But is `p = &sp10[4]` an "identity address spelling"? It's the second set of the pointer. Hmm. The concern in the brief: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". I read "identity address spellings" as: spelling the SAME address two different ways to fake a launder (e.g. `p = (u8*)&D` vs `p = &D`). That is exactly what I'd be doing. Hmm. Risky.

But hmm, is there a *legitimate* structure? Consider: what if the pointer is re-assigned in a way that reflects the program flow? E.g.:

```
u16 *p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
u16 *p2 = p1;   // hmm
```

Hmm, what about the SECOND call using a pointer that was set earlier for a different purpose? E.g.:

```
u16 *p = sp10;      // p = base
func_800D20C0(p, p + 4, 1);
p += 4;              // ← real bump! second set
func_800D23D0(p);
```
This is a genuine pointer-bump (not an identity). And §145(b) says a second set kills the cse fold → each use computed separately.

But the values: use1 = p+4 where p = sp+16 → (plus (pseudo_p) (const 8)); use2 = p (after bump) = (plus (pseudo_p) (const 8)). Hmm, the bump `p += 4` makes p's value = (plus (pseudo_p) (const 8)) where pseudo_p = sp+16 in a register. So use1 = (plus (pseudo_p) (const 8)) and use2 = same → cse might unify them still (same rtx!). Hmm, but the second set of p means p's value is a NEW pseudo, not the folded constant. So use2 = (plus (new_pseudo_p) (const 8))? and use1 = (plus (old_pseudo_p) (const 8))? These are different rtx (different pseudos) → NOT unified → two separate computations!

But then gcc needs pseudo_p in a register (holding sp+16) → an extra register and `addiu a1,reg,8` instead of `addiu a1,sp,24`. Unless pseudo_p's reg_equiv is (plus (reg sp) (const 16)) and it folds.

Hmm, this is really deep in the weeds. Let me just EXPERIMENT with several spellings. Empiricism beats theory here.

Let me create a batch of candidates:

d1: p1 = sp10+4; call1 uses p1; then p1 = &sp10[4]; call2 uses p1.  (second set)
d2: p = sp10; call1(p, p+4, 1); p += 4; call2(p);
d3: p1 = sp10+4; call1 uses sp10+4 (raw); p1 = sp10+4; call2 uses p1.
d4: base pointer: u16 *base = sp10; u16 *p1 = base + 4; call1(base, p1, 1); call2(p1);
d5: u16 *base = sp10; call1(base, base+4, 1); call2(base+4);
d6: reorder: assign p1 = sp10+4 AFTER the first call? i.e. call1 uses sp10+4 raw and p1 assigned after.

Let me write d1..d6 and score them one by one. Each score call ~20-30s. 6 candidates = 6 calls. OK.

Actually, let me think about which is most likely to work given the target:
target: `addiu a0,sp,16` (a0 = sp10), `addiu a1,sp,24` (a1 = sp10+4), `addiu a0,sp,24` (call2 arg).

For d5 (base pointer variable): the base var holds sp+16; if gcc rematerializes it as (plus (reg sp)(const 16)) then base+4 → (plus (reg sp) (const 24)) → `addiu a1,sp,24`. And the second use base+4 → same expression → cse unifies → pseudo... but if the pseudo's reg_equiv is the constant expression, gcc might rematerialize → 2 addiu. Worth trying!

Hmm, but a "base pointer variable" holding a local array's address — gcc will likely just fold it back to the symbol_ref (since the address of a local is a compile-time constant), giving exactly the b1 situation.

Let me think about d2 (pointer bump):
```
p = sp10;            // p = sp+16
func_800D20C0(p, p + 4, 1);
p += 4;              // p = sp+24
func_800D23D0(p);
```
Here p+4 for call1: (plus (pseudo_p) (const 8)) with pseudo_p's reg_equiv = (plus (reg sp) (const 16)). simplify_rtx with lookup_reg → (plus (plus (reg sp)(const 16)) (const 8)) → (plus (reg sp) (const 24)). Then `addiu a1,sp,24` ✓ (if the fold happens in the frontend/expand). And after `p += 4`, p's value = (plus (pseudo_p) (const 8)) → same expression → the uses might be unified by cse (same rtx!). Hmm, but p's *value* at the second use is a new set.

Hmm, honestly: if the frontend folds p+4 to sp+24 at the RTL level, then both uses are the same expression and cse unifies → 1 pseudo → s0 again.

The ONLY reliable way to prevent unification is a genuine 2-set with different rtx.

Hmm, so what about: make the two uses have DIFFERENT rtx by having one of them be a "MEM" style and the other a plain pointer? Like:
call1's second arg: `&sp10[4]` → rtx (plus (symbol_ref) (const 8)).
call2's arg: `(u16 *)((u8 *)sp10 + 8)` → rtx: (plus (symbol_ref) (const 8)) — the same after simplification, but BEFORE simplification, the tree is (plus (convert (symbol_ref)) ...)? No: (u8*)sp10 is a NOP cast (same address), so (u8*)sp10 + 8 = (plus (symbol_ref) (const 8)). Identical.

What about `(u16 *)(&sp10[0] + 8)`? same.

What about using a **char array** and casting? `u8 raw[12]; u16 *sp10 = (u16 *)raw;` — then sp10 is a pointer variable; the address of raw = sp+16; (u16*)raw + 4 → (plus (symbol_ref raw) (const 8))? The cast (u16*)raw is a no-op pointer cast, so raw+8 in bytes = (plus (symbol_ref raw)(const 8)). Same rtx as (plus (symbol_ref raw)(const 8)) for sp10+4 → but sp10 is a VARIABLE, so sp10+4 = (plus (pseudo_sp10) (const 8)).

So with `u8 raw[12]; u16 *sp10 = (u16 *)raw;`:
- call1(sp10, sp10+4, 1): a0 = pseudo_sp10 (a register!), a1 = pseudo_sp10+8.
- call2(sp10+4): same.
Unified again.

OK. Completely different: what if the two uses are in *different scopes* such that gcc creates two pseudos? Like one in a block and one outside? cse is global regardless.

Hmm, hold on. What about cse's behavior with a value that's live across a CALL? cse's `cse.c` has a rule: a pseudo that is live across a call can't be CSE'd across the call? No, that's not it either.

NEW IDEA — maybe the answer is much simpler and I'm overcomplicating. What if we change the ORDER of the two calls' arguments or use a **different function**? No.

NEW IDEA: what if the `p0` argument (a0 = sp+16) is the key? In the target, a0 = sp+16 is computed at insn 3, a1 = sp+24 at insn 4. In mine, a0 = sp+16 presumably also at 3. So the first call is fine; the issue is only the second use of sp+24.

What if we could make the SECOND use of the address happen at a point where the value can be recomputed? The value sp+24 is a compile-time constant + frame. gcc's register allocator chose to keep it in s0 because it was live across a call and gcc's "address giv" logic (find_best_addr) decided the pseudo holds a "good address".

§349: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY to make n_times_set > 1 — that kills both loop.c's INVARIANT HOIST and the ADDRESS GIV, reproducing a REMATERIALISED addiu $aN,$sp,K".

KEY: "the ADDRESS GIV". A "GIV" (GIMPLE/rtl GIMPLE IV) in local-alloc is a "general IV" — a pseudo holding an induction variable or an address. local-alloc's "address giv" is a pseudo whose value is an address, used to compute other addresses. If n_times_set > 1, local-alloc can't treat it as a GIV.

So: make the pseudo holding sp+24 have 2 sets. Ways:
1. `p1 = sp10 + 4;` ... `p1 = sp10 + 4;` (2 sets, same value) → then local-alloc sees n_times_set=2 → doesn't make it an address GIV → it gets rematerialized!

Hmm! And this is EXACTLY §349's mechanism. And is it an "identity-statement launder"? It's a re-assignment of a pointer to the same value. Hmm. The brief's ban: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". The example `w = (w>>16<<16)|x` is a *value* launder that pretends to break cse. Our `p1 = sp10+4; p1 = sp10+4;` is an *address* re-assignment that pretends to break the address GIV. I think this would be judged as an identity statement launder — risky.

Let me find a NON-identity version: the second set must have the same final value but be a different statement.

What about:
```
p1 = sp10 + 4;
p1 = p1 + 0;   // hmm, folds
```

What about making the pointer's value pass through a real computation that ends at the same place? e.g.
```
p1 = sp10 + 2;
p1 += 2;
```
Then p1's value = (plus (pseudo) (const 4)) after the bump; the fold to (plus (symbol_ref)(const 8)) would be killed by the second set (per §145(b): the bump's addiu is saved by cse only if there's a second set; here there IS a second set, so cse can't fold the bump back). So p1's value stays as (plus (pseudo_p1) (const 4)) where pseudo_p1 = sp+20.

Then call1's a1 = p1 → needs pseudo_p1 in a register → `addiu r,sp,20` then `addiu a1,r,4`. NOT `addiu a1,sp,24`. ✗.

Hmm. Unless gcc folds (plus (reg sp)(const 20)) + 4 → (plus (reg sp)(const 24)) via lookup_reg + simplify. Then it'd be `addiu a1,sp,24` — and pseudo_p1 is rematerializable (it's a frame address). Hmm! That could work. And it's a genuine restructure (not an identity): the pointer is built in two steps.

Actually hold on, hold on. Simpler: what if we just write the pointer arithmetic so that the address is computed from the frame in a way that gcc's local-alloc treats as a GIV with 2 sets, e.g.:

```
u16 *p1 = sp10 + 4;
p1 = p1;   // no, identity
```

Hmm.

OK, let me look at this from yet another angle: what if we avoid the problem entirely by changing WHICH call gets which argument? I.e., what if the first call's second argument is `sp10 + 4` and the second call's argument is `sp10 + 4`, but we introduce a THIRD use in between that forces a different structure? No.

What if we make the array smaller/different so that the address sp+24 is not a "nice" frame slot? The offsets are fixed by the target: sp+16..sp+27 for the array, s0 at sp+32. The frame is 56 bytes. gcc chose that layout. If I change the declaration (e.g. `u16 sp10[6]` → `u16 sp10[6]` same), layout stays.

Hmm, but what if I add another local to force a different layout? No — the layout must match the target exactly.

Hmm OK, let me look at the problem from the "what's the actual C the game used" angle once more. The decompiler wrote:
```
p0 = sp10;
p1 = sp10 + 4;
__asm__("" : "=r"(p0) : "0"(p0));
__asm__("" : "=r"(p1) : "0"(p1));
func_800D20C0(p0, p1, 1);
func_800D23D0(sp10 + 4);
```
The decompiler added the launder to p0 AND p1 — both! Even p0, whose use is unique (a0 = sp+16). Why would p0 need a launder? Because with the launder on p0, gcc can't fold the address... hmm, but the target's a0 = sp+16 is a plain addiu.

Hmm! Both launders. Maybe the launder on p0 was needed for a different reason: to prevent gcc from folding the address of sp10 into... hmm.

Actually! Maybe the launder is needed to keep the ARRAY's address from being treated as a constant that gcc folds into the *call* differently. Hmm.

Let me test: what if we remove ONLY the p0 launder and keep the p1 launder? Then a0 = sp+16 might come out differently. And what if we remove only the p1 launder?

Actually, wait. What if the p0 launder is what forces `addiu a0,sp,16`?! Without the p0 launder, gcc might fold sp10's address differently. Hmm, but b1.c (no launders at all) gave... let me check the diff: mine[0..3] matched target[0..3]: `addiu sp,sp,-56; sw s1,36(sp); move s1,a0; addiu a0,sp,16`. So a0 = sp+16 matched. Good — so the p0 launder isn't needed for that.

So only the p1 launder matters. Let me verify: candidate with p0 launder removed but p1 launder kept → should score 0. And p1 launder removed but p0 kept → ?

That's a useful diagnostic but not the goal.

Let me now think about "PARTIAL". The task allows PARTIAL:<kinds still kept> — win.c scores 0 keeping only those levers. But our row kind is ONLY "launder". So PARTIAL would mean keeping the launder → but PARTIAL means "win.c scores 0 keeping only those levers" — i.e. the kinds still kept are listed. If we keep the launder, that's the same as the original → PARTIAL:launder with score 0. Hmm, that's a valid outcome but weak: the original already scores 0, so PARTIAL:launder = orig. That's a legitimate "PARTIAL" answer if the launder can't be removed.

Actually wait, re-read: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So PARTIAL means: the win.c keeps SOME of the row's levers (listed) and still scores 0. Since the row has only one kind (launder), PARTIAL:launder = the original def (launder kept) = trivially 0. That's a valid but weak result. Better to find a full MATCH.

Hmm, but also: PARTIAL could be for a row with multiple kinds where we removed some. Here only one kind.

OK. Let me now run experiments. I'll be systematic but time-boxed (20-30 min per item!).

Let me do a quick decisive experiment first: does the "second set" mechanism work? Test d1:
```
p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
p1 = &sp10[4];
func_800D23D0(p1);
```
If this scores 0, I know the mechanism. Then I can find a non-identity formulation.

Also test e1: p1 = sp10+4; call1(sp10, p1, 1); call2(sp10+4) but with p1's assignment moved after the first call? no.

Let me write d1 and score.

Also, I want a cheaper way to iterate: since scoring takes ~20-30s and I can only run one file per call, let me write several candidates and use a single bash call with `&&` chaining (which worked before: `cd X && grep`).

Let me test whether `A && B` of two delever_search calls is allowed.

Let me write d1, d2, d4 first.
