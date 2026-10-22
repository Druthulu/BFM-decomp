---
ts: 2026-10-22T12:44:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yoT4SjqSskGaYjbUwwNN
---
Interesting! My candidate:
```
lui a0, hi(D_80120194)
addiu a0, a0, 25996   ; LO16 D_80120194 with addend 0x658C -> address D_80120194+0x658C
j 4190
nop
4188: j 41bc ; delay move v0,v1
418c: move v0,v1   <- wait, the order: 4188 is `j 41bc` and 418c is the delay slot `move v0,v1`
4190: lui v1, hi(D_801202A0); addiu v1,v1,lo
4198: beq a0,v1
```
Target:
```
4178: lui v1, hi(D_80120194)
417c: addiu v1,v1,lo(D_80120194)
4180: j 4190 ; delay: addiu a0,v1,25996
4184: addiu a0,v1,25996
4188: j 41bc ; delay move v0,v1
418c: move v0,v1
4190: lui v1, hi(D_801202A0) ...
4198: beq v1,a0
```

So in the target, the address D_80120194 is materialized in v1 and p = v1 + 0x658C in a0. In mine, the whole thing folded to a0 = D_80120194+0x658C and the `return it` used v1 — but v1 holds... wait mine has `move v0,v1` at 418c, so v1 must hold &D_80120194. But where is v1 set in mine? It's not in the listing! Hmm, the listing shows lui a0/addiu a0 at 4178-417c and no v1 setup. But `move v0,v1` at 418c implies v1 = &D_80120194.

Ah I see — the "return it" at the copy label: `it` at that point is the pseudo holding &D_80120194... but wait, in the target, `copy: return it;` — `it` here refers to the value at the copy point which is the loop's it (D_801202A0 + k*0x10C)? No wait.

Hold on. Let's re-read the source:

```c
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
    return it;     // it = D_80120194 (the first value!) since `it` is reassigned at test:
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```

Hmm, at `copy`, `it` has been reassigned to D_801202A0 and incremented in the loop. So `return it` returns the loop pointer, not D_80120194. But GCC's register allocation: at copy, the live value of `it` is the loop counter (v1 at 41a0..41b4 uses v1 as the pointer). But at 418c, `move v0,v1` — v1 must hold the value of `it` at the copy point.

Wait, the control flow: body → if (*it == 0) goto copy (4188). At that point v1 = the current `it` (the pointer being tested). So v1 at 418c = current it. And the target's 417c `addiu v1,v1,lo(D_80120194)` sets v1 = &D_80120194 at entry — that's the FIRST it value, which is only used for p = it + 0x658C.

Hmm, so v1 is used for two different things: entry it (=&D_80120194) and the loop pointer. But at 418c, `move v0,v1` — v1 there must be the loop pointer value.

Hmm wait, at 418c (the copy block), the value of `it` — the copy block is reached from 41a8's beqz (i.e. *it == 0). At that point v1 = the pointer. So `move v0,v1` returns the pointer. But also the entry path: 4178 sets v1 = &D_80120194, and 4184 computes a0 = v1+0x658C, then jumps to 4190 which sets v1 = &D_801202A0. So the v1 at 418c on the entry path is irrelevant (entry doesn't reach copy).

But actually, GCC allocated the same reg v1 to two different pseudos (the first `it` = &D_80120194 and the loop `it`), since their live ranges don't overlap. Good.

So in the target, the "first it" pseudo is in v1 and p = v1 + 0x658C (not folded). In mine, the first `it` pseudo got folded into a0 = &D_80120194+0x658C, and the copy-block `it` (the loop one) is in v1. So the difference: GCC's constant folding merged the first it into p.

So to match: prevent the fold of (const address + 0x658C).

Now: what if the source were:
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
but GCC folded because `it` is a constant. In the original compile, GCC did NOT fold. What could differ? Maybe in the original, D_80120194's address was not directly usable because the original code had something like:

```c
it = (s32)(u32)D_80120194;
```
no.

OR the original had the two symbols as an ARRAY of pointers? Hmm.

OR the original source computed the base differently: e.g.

```c
s32 base = (s32)D_80120194;
```
Same.

Hmm, think about GCC 2.7.2's cse: `find_best_addr` handles `reg + const` where reg holds a symbol address: it can find the base reg and use (reg + const) instead of rematerializing. The moves.md entry for func_80183098 says exactly: "cse: find_best_addr rematerialises the +4 address for cam->y (lui+addiu) instead of the base reg; only an opaque (asm) base keeps lh 4(s1)".

So in cse, when we have `x = reg + const` where reg is a pseudo holding symbol address S, cse's find_best_addr(cst, want) tries to find a register whose value is S - const... i.e. it can replace (S + c) with the base reg + c (base-relative). Here the opposite happened: we got the folded constant, not the base-relative. So it wasn't find_best_addr but rather the front-end/cse constant propagation: the pseudo `it` was recognized as a constant (CONST) and `it + 0x658C` folded into a new constant.

In the original compile, `it` was NOT a constant. Why? Because of the launder! The asm output "=r"(it) forces `it` into a register — a REG (not CONST). So the value &D_80120194 is in a REG.

So to reproduce without asm, we need `it` to be a register value in GCC's view. Ways:
1. The address must be loaded from memory at runtime (not available).
2. Something prevents the front end from treating it as a constant...

Hmm! What about the *order*: in the target, the materialization `lui v1; addiu v1` is a REG containing the symbol address. GCC 2.7.2 does that when a symbol address's value is needed in a register and can't be folded into the use — e.g. when the address is used with a variable offset or when the pseudo is "address-taken" etc.

Idea: use `p = it + 0x658C` where the addition is done in a way GCC can't fold because `it` has a *different* type/precision. E.g. if `it` were a `u32` and the offset added... no.

Idea: what if the address is obtained via a cast that GCC treats as non-foldable in the RTL but folds in the front end? Everything folds in the front end at -O2 with constant addresses.

Idea: what if `it` is assigned from a *volatile* read of a global pointer? Not available.

Idea: use the address of a *static* local variable initialized to the address? Folded.

Idea: use `&&label`? no.

Hmm, but wait: maybe there's a completely different source formulation that produces the same code! E.g., maybe the original was:

```c
s32 it;
it = (s32)D_80120194;
p = it + 0x658C;
```
with `D_80120194` declared as `extern u8 D_80120194[];` — hmm.

What if the original code had the loop walking with a *pointer* variable and the base was loaded from an array of pointers? 

Alternatively — what if the original source was:

```c
it = (s32)&D_80120194[0];
```
no.

New thought: maybe the trick is that GCC folds only when the constant is a "CONST" of a specific kind. If the symbol address is used in a context requiring a *non-constant* (e.g. passed to a function that takes its address — "address taken" → the pseudo becomes an address, not a value) — e.g.:

```c
s32 *ip = &it;   /* address taken */
```
That makes `it` a MEM, not a REG. Different code.

Alternatively, the front end folds `it = (s32)D_80120194` into a CONST because D_80120194 is a link-time constant address. GCC 2.7.2 with -O2: `expand_expr` for `&array` gives a SYMBOL_REF; in a cast to s32, it becomes a CONST (symbol_ref) in a reg. Then `it + 0x658C` → cse/constant-prop folds.

BUT: if the symbol is declared `extern` and the address is taken in a context where "targetm.c" `mips_move_imm` etc... Hmm.

What if the address is of a symbol in a different section such that the HI16/LO16 pair is generated? Both cases use HI16/LO16.

OK here's another thought: what if we avoid the fold by making the offset non-constant in the source but constant in the target? E.g.:

```c
p = it + 0x658C;
```
target: `addiu a0, v1, 25996`. The offset 25996 = 0x658C. If the source had `p = it + 0x658C` and it folded, we'd get lui/addiu with addend. So we need GCC to emit base+offset.

What if `it` is `u32` and `p = it + 0x658C` where `it` is assigned `(u32)D_80120194`? Same fold.

Idea: Use a union:
```c
union { s32 i; u8 *p; } u;
u.p = D_80120194;
it = u.i;
```
GCC would fold that too (union of pointer and int, type-punning a constant → folded at -O2? probably folded).

Idea: use a struct with a pointer member and memcpy? no.

Idea: compute the address as `it = (s32)(char *)D_80120194;`? Folded.

Hmm. What about making the *base* not the symbol but a computed value that equals it? E.g.:

```c
it = (s32)D_80120194 + 0;   /* folded */
```

What about a pointer difference between two symbols: `(s32)((u8*)D_801202A0 - 0x10C)` → folds to D_80120194.

Everything folds. The only non-folding sources of an address in C: reading a pointer from memory, or a function call result, or a register.

Hmm! Wait. What about this: GCC does NOT fold an address+offset if the *offset* is not a compile-time constant... but then the target's addiu wouldn't be constant either. But GCC's RTL would be `plus(reg, reg)` → not addiu. Unless the offset reg is later recognized.

Alternative: what if we give the offset through a variable that GCC constant-propagates at RTL level but not at the front end? E.g.

```c
s32 off = 0x658C;
p = it + off;
```
Front end: `off` is a local with a constant initializer → GCC folds at the front end (constant propagation in the front end for locals? GCC 2.7 does "expand" with the local as a constant only if it's a constant variable... `off` is not const, so the front end emits a set of a constant into a pseudo, then the addition is pseudo + pseudo. Then RTL-level cse/const-prop may fold the copy: `off` pseudo = 25996 → the add becomes reg + 25996 → addiu! And `it` remains a REG holding the symbol address (since the front end set it = symbol_ref, which as a REG...). Hmm, but then the same fold problem for `it`? No! The fold of `it` into p happened because `it` was a CONST in the front end. If it is a REG (because... hmm, `it = (s32)D_80120194` — the front end: expand_expr of &D_80120194 → SYMBOL_REF → converted to a REG by force_operand? The result of an assignment `it = <symbol_ref>`: expand_assign → the RHS is a constant expression → it gets converted to a constant... 

Hmm, in GCC, `x = &foo;` where foo is a global: the RHS is a SYMBOL_REF constant. In expand_assign, if the RHS is a constant, it will try to put the constant directly into the LHS's location. The LHS `it` is a pseudo (local variable) → the constant is stored into the pseudo as a CONST set. So `it` is a pseudo = CONST(symbol_ref). Then use of `it` in `it + 0x658C` reads the pseudo, and cse/const-prop sees the pseudo's value = symbol_ref (a constant) → folds it+0x658C = symbol_ref+0x658C (still a constant but now with an addend, so it can't be a plain symbol) → materialized as lui/addiu with addend 0x658C.

Wait, but then `return it` needs the plain symbol address → materialized separately as lui/addiu with no addend. But in my candidate, only ONE materialization appears (a0 with addend). Where's the plain one for `return it`? Because the copy block's `move v0,v1` — v1 holds &D_80120194... but I don't see any lui v1/addiu v1 for D_80120194 in my candidate!

Look again at my candidate:
```
4178: lui a0, hi(D_80120194)   [R_MIPS_HI16 D_80120194]
417c: addiu a0,a0,25996        [R_MIPS_LO16 D_80120194]
```
The LO16 reloc with addend 25996 → the assembler computes hi(D_80120194)+25996 = D_80120194+0x658C. So a0 = D_80126720.

And at 418c: `move v0,v1` — v1 = ? In the target, at 418c, v1 = the loop pointer. But wait — in MY candidate the loop pointer is also v1 (lhu v0,0(v1); addiu v1,v1,268). So `move v0,v1` at 418c is the loop pointer, NOT &D_80120194!

But the source says `copy: return it;` where `it` at copy = the loop pointer (reassigned at test). Right! I misread earlier. The `it` returned at copy is the loop pointer, i.e. D_801202A0 + k*0x10C. Hmm, but the loop exits when *it == 0, so it returns the address of the zero entry.

Hmm OK. But then what's the role of the first `it = (s32)D_80120194`? Only for p = it + 0x658C. So the first it value is used once. In the target, it's materialized in v1 (a reg) and p = v1+0x658C.

Hmm, so in the target GCC did NOT fold the first `it` into p. Why? Because the first `it` pseudo is a REG (not CONST)? That's what the launder did.

Hmm wait, actually — maybe not. Let's reconsider: maybe in the ORIGINAL source, the first assignment wasn't `it = (s32)D_80120194` but something else. Since v1 in the target holds &D_80120194 and stays live until 4184... but v1 is then reused for the loop pointer at 4190. So the first it's live range is 4178-4184.

Why would GCC keep it in a register instead of folding into the address? Because at 4178-417c we see lui+addiu with NO addend — i.e., the symbol address materialized plainly. That's what GCC does when the value is needed as a register (e.g. used in a context where the constant can't be folded, or the pseudo is a REG).

Consider: what if the source is
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
but with `it` being ALSO used later? No, `it` is reassigned.

What if the source used TWO variables:
```c
s32 base = (s32)D_80120194;
s32 p = base + 0x658C;
```
same thing.

Hmm, what if the original source was:
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
where the compiler was NOT gcc 2.7.2 but something else? The project builds with gcc 2.7.2 (psx). The target bytes came from the actual ROM, compiled by a different compiler (maybe gcc 2.7.2 for PSX too, but different flags/optimization). Actually the project reproduces the ROM with gcc 2.7.2 -O2. So the target should be reproducible... but our source has the launder to force it.

Interesting: the header comment says "h_exact 4516d044" and "!FAKE: launder — NEEDED DIFFERS". So the phase found the plain-C spelling differs and inserted a launder to match. The task now is to find a plain-C spelling that matches without the launder.

So: what plain C spelling keeps the address in a register?

Key insight attempt: GCC 2.7.2's `expand_assign` for `it = (s32)D_80120194` — I believe the front end converts the address to a constant and stores it into the pseudo. Then in `it + 0x658C`, cse.c's `cse.cse_const` / the "fold" would combine. But maybe if the variable `it` is *address-taken* or is of a type with different precision, the front end doesn't do the const store.

Actually here's a cleaner idea: **use a different type for the intermediate so that the front end must use a register**. For example, if `it` is a `float`? no.

Alternative clean idea: **make the offset the one that's constant-folded instead**: i.e., swap which operand is the base:
```c
p = 0x658C + it;   /* commutative; combine puts constant last... */
```
The target's addiu a0,v1,25996 has the base first. combine's simplify_rtx for commutative ops moves the constant to the end → still (reg + const). But the fold into a single symbol+addend happens at the front end/cse when the reg is known constant.

OK so the crux: how do we get GCC to keep the address in a REG?

Option A: Use a pointer variable that is stored to memory and reloaded? e.g.
```c
u8 *tmp;  /* local */
tmp = D_80120194;  /* front end: tmp = constant */
it = (s32)tmp;  /* still constant */
```
No.

Option B: Use `volatile` — that's a lever (and class C/D). The rules: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". Adding volatile = adding a lever of another kind → not allowed. Hmm, but is `volatile` a "lever"? In the lever census, kinds include pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. A volatile cast is class C/D ("byte-needed volatile cast" stays as ordinary C per decision 3 in lever_free_body). Interesting! The docstring said: "A class C/D site the tree still carries (a byte-needed `volatile` cast or bare `register`) STAYS: decision 3 keeps it as ordinary C, unmarked and ledgered, so the search starts from the spelling the original plausibly had rather than paying to remove what the phase does not ask removed".

Hmm, that's about the tree's existing sites. But adding a NEW volatile cast would be "adding a lever of another kind". Risky. The constraint says "no new lever of any kind". A volatile cast is arguably a lever (keepalive/barrier-ish). I'd rather avoid.

Option C: find a way to make the base non-constant using the *existing* declarations. Note `extern u8 D_80120194[];` — an array of unknown size. `&D_80120194[0]` is a constant.

Option D: Change the formulation so the base address is NOT needed as a constant at all: e.g., the target's `addiu a0, v1, 25996` with v1 = &D_80120194 could also be produced by `p = it + 0x658C` where `it` is a *pointer to a struct field*... 

Hmm hold on. Let's revisit: maybe the difference isn't about constants at all! Look at the target again:

```
4178: lui v1, hi(D_80120194)
417c: addiu v1,v1,lo(D_80120194)
4180: j 4190
4184: addiu a0,v1,25996      <- delay slot
```
Note that v1 is *reused* later for the loop pointer (lui v1, hi(D_801202A0) at 4190). And the target's `beq v1,a0` (v1 = &D_801202A0 vs a0 = p).

In MY version:
```
4178: lui a0, hi(D_80120194); 417c: addiu a0,a0,25996 (addend)
4180: j 4190; 4184: nop
4190: lui v1, hi(D_801202A0); 4194: addiu v1,v1,lo
4198: beq a0,v1
```
So GCC chose to fold and use a0 for p, and v1 for the second address.

So in the target, the first address went to v1 (a callee-saved reg!) and p to a0. In mine, the first address (folded) went to a0 and the second address to v1.

Interesting: the register allocation differs. In the target, v1 (s-reg $23) holds the first address. Why a callee-saved reg for a value live only from 4178 to 4184? Because it's live across a call? No calls. Hmm, but GCC's global-alloc assigns to $23 (v1) vs $4 (a0) based on priority/frequency. In mine, the first address got a0 because it's the operand of the compare beq.

So actually the difference in register choice is downstream of the fold.

Let's think about what source change would produce the target:
- The base &D_80120194 materialized plainly in a register (v1), and p = base + 0x658C.

What if we write the source so that GCC has to keep the base in a register for another reason? For instance, if `p` were computed from `it` in a loop or if `it` were used again later.

What if we restructure the source so the base is used twice: e.g.

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
vs
```c
p = (s32)D_80120194 + 0x658C;
```
Both fold.

What if the original source was:
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
and the compiler didn't fold because... the front end didn't fold `it` into a CONST but into a REG. When does GCC keep a symbol address in a reg? In `expand_assign`, if the RHS is a SYMBOL_REF and the LHS is a pseudo, GCC does: `emit_queue` the constant into the LHS. In RTL, `set (reg it) (symbol_ref D_80120194)` — a CONST? No! `(symbol_ref foo)` in RTL IS a CONST (CONST_... hmm, in RTL, symbol_ref is a CONST node (CONST_SYMBOL_REF). So `set reg, const` — the reg is a pseudo whose value is a constant.

Then cse.c's `cse.cse_basic_block` with the "fold_const" logic: for `plus(reg, const)`, it looks up the reg's value in the cse hash table; the reg was set to a constant → the plus folds to a constant (symbol_ref + 0x658C = symbol_ref with addend? In GCC, adding a constant to a symbol_ref gives a new symbol_ref? No! In RTL, (plus (symbol_ref D_80120194) (const_int 25996)) is folded to a symbol_ref with an offset? GCC's fold doesn't create symbol_ref+offset; instead the constant is kept as a separate CONST_INT and the addition becomes an `plus` with a constant → but since symbol_ref is a constant, `fold` returns (plus (const_int 25996) (symbol_ref))? Hmm.

Actually in GCC 2.x, `fold` on (plus (symbol_ref f) (const_int c)) → the result is a CONST node? No: `simplify` in fold-const.c: for PLUS with a constant operand and the other a SYMBOL_REF, it returns... In fold-const.c's fold_binary, for PLUS: if one operand is a constant and the other is a SYMBOL_REF, it returns (PLUS (SYMBOL_REF) (CONST_INT)) unchanged (can't fold a constant+symbol into a new symbol because relocations need the symbol alone). Hmm, but our candidate shows exactly that: `addiu a0, a0, 25996` with HI16/LO16 on D_80120194 and the addend in the instruction (not in the reloc). So the PLUS of a symbol_ref and a const survived to RTL as a memory address operand → the assembler emitted lui/addiu with the addend folded into the immediate (that's a relocation addend, standard).

So in my compile the fold DID happen at the RTL level (the constant was substituted into the plus), and the base pseudo disappeared.

In the target, the base pseudo survived. The difference: cse's constant substitution. cse.cse_basic_block, `case PLUS: ... if (cse_lookup(...))`. Actually the relevant code is in cse.c `cse_record`/`simplify_const`? The key function: cse.c's `cse_basic_block` calls `simplify_gen_binary` which for (PLUS (REG) (CONST)) checks `if (GET_MODE(x) == ...)` hmm.

There's also `cse.cse_const` which does: "if (x is a constant and the mode is not ...) try to replace the register with the constant" — that's cse_const in cse.c: it looks up whether the reg's value equals a known constant, and replaces the reg with the constant. That's the fold we saw.

BUT: cse_const only does this when the reg's value is a *scalar* constant (CONST_INT etc.), NOT a symbol_ref? Actually cse_const handles the case where a register's value equals a constant found in the hash table. Symbol refs are also constants...

Hmm, but in our case, the fold happened even for a symbol ref.

OK, empirical approach is better than theory. Let me just try a bunch of real-C spellings and see. Candidate spellings for keeping the base in a reg:

1. `p = it + 0x658C;` with `it` declared as `s32` — folds (current).
2. Declare `it` as `u32`: `it = (u32)D_80120194; p = it + 0x658C;` — the plus would be unsigned; still folds probably.
3. `it = (s32)D_80120194; p = it + 0x658C;` but with `it` used later: e.g. the copy block returns `it`?? Wait — in the source, at `copy:` the source's `it` is the loop pointer. But what if the ORIGINAL source had a different structure where the first `it` value is also live at the copy point? No.

4. Use a pointer type: `u8 *base = D_80120194; p = (s32)(base + 0x658C);` — pointer arithmetic with a constant offset on a pointer to unknown-size array: GCC folds this too (it computes base+offset as an address constant). Probably the same.

5. Use a *struct* pointer arithmetic: `p = (s32)((u8*)&D_80120194[0] + 0x658C)`.

Hmm.

6. What about making the addition happen in a context where the constant offset can't be merged into the address: e.g. `p = it + 0x658C` where `it` is a `s16`?? no, truncation.

7. What if we compute p as `it + 0x658C` but `it` was set from a *volatile* read? no.

8. What if we never compute `p` from `it` but instead compare differently: the source could be restructured so that p is computed from the SECOND symbol: p = (s32)D_801202A0 + 0x6480? That's a different constant (0x801202A0+0x6480 = 0x80126720 = same value!). Indeed D_80120194 + 0x658C = 0x80126720 and D_801202A0 + 0x6480 = 0x80126720. Same!

But the target's addiu a0, v1, 25996 has v1 = &D_80120194 — base-relative to the FIRST symbol. If we wrote p = D_801202A0 + 0x6480, GCC would fold it to lui/addiu with addend 0x6480 on D_801202A0 → not matching.

Hmm. But what if the source is:
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
and we want GCC to keep `it` in a reg. What if `it` is used in a *later* statement too, so it's not dead? E.g. the loop could be written to compare against the base. Hmm, the semantics: p = end pointer; loop over it from D_801202A0 to p.

9. What about the *order* of the two address materializations? In the target, both D_80120194 and D_801202A0 are materialized with lui+addiu (plain, no addend). The second one (v1 = &D_801202A0) is used as a loop pointer base and in the compare `beq v1,a0` → GCC materialized it plainly because it's a REG used in multiple places (the compare and the lhu). Fine — that already happens in my version too (lui v1/addiu v1 for D_801202A0). So only the FIRST address is the problem: it's used once (for p) so GCC folds it.

So the fix: make the first address used TWICE, so it must be materialized in a register! For instance:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
→ change to something where the base is used again. But semantically we can't change the function's behavior.

Hmm, but the target's v1 IS the base and it is used... only for the addiu. But GCC materialized it in a reg anyway (v1) — because in the target's allocation, v1 is needed anyway for the loop pointer, so materializing the first address into v1 costs no extra register! Global-alloc would prefer to fold though (cse/const-prop happens before reg alloc).

Wait — maybe the order of passes matters: the fold happened in cse (before global-alloc). So the fold is not reg-alloc-dependent.

Unless... the fold is in the FRONT END (expand_assign → the constant is stored into the pseudo, and then the use of the pseudo in `it + 0x658C` is expanded by `expand_expr` which reads the pseudo's value?? No, the front end doesn't know the pseudo's value.

The front end: `it = (s32)D_80120194;` → expand_assign: the RHS is a constant (SYMBOL_REF cast to int) → `emit_insns` of `set it, const`. The pseudo `it` = const symbol_ref.

Then `p = it + 0x658C;` → expand: `p = plus(it, 0x658C)` → set p, (plus (reg it) (const_int)). RTL-wise, `it` is a pseudo with value symbol_ref.

Then at RTL, cse.c's cse_const: it looks for a register whose value is a constant that equals a constant in the hash table. Actually here's the relevant cse code (cse.c, `cse_const`):

```c
static void cse_const (rtx x, struct cse_basic_block_data *cse_data) {
  rtx y;
  if (x == const0_rtx) return;
  y = lookup_case_const (x);
  if (y)
    ...
}
```
Hmm, that's for cases.

The actual folding of a register into a constant use is in `simplify_gen_binary` → `fold` on (PLUS (REG) (CONST)) doesn't look at the reg's value.

But cse.c has `cse.cse_basic_block` → for each insn, `if (...)` and there's `cse_lookup` for the reg. The relevant: in cse.c, `record_jump_equiv` and `find_best_addr`.

And `find_best_addr(cse_data, x, want)`: given x = a constant (like the address), it looks for a register in the equivalence table whose value is `x - want` and returns it if the reg's value is a "good" address (so you can do reg+offset instead of rematerializing). THIS is what the moves.md wall "cse-const-addr" refers to: "cse folds or substitutes a constant/absolute address the target keeps base-relative".

So in cse: we have `set p, (plus (reg it) (const 25996))` — hmm.

Let me look at the actual gcc 2.7.2 source. Is it available in the repo? The project has tools/bin/gcc-2.7.2-psx/ (the compiler binary). Source? "gcc 2.7.2 source" is referenced in delever_search.py comments. Let me check if the source is in the repo (maybe .run/P36 or tools/gcc-src).

Let me look for the cse.c source in the repo.
