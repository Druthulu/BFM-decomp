---
ts: 2026-10-22T12:46:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mFT5WbsBAdHr0dbMC2SW
---
This is the reassociation of plus/minus. Not the fold of a pseudo into a constant.

The fold likely happens in the front end or in `jump`/`reload`? Let's look at where the pseudo `it` gets folded. Actually! I bet it's in `combine` or in `reload` (reload.c's `reload_cse`?) Hmm.

Alternatively, the fold could be at the FRONT END: expand_assign for `it = (s32)D_80120194` → since D_80120194 is a global array, `&D_80120194` is an ADDR_EXPR → in expand_expr, `ADDR_EXPR` of a DECL with a constant address → the result is a CONST (symbol_ref) → then `expand_assign` with a constant RHS and LHS a MEM (pseudo's stack slot? no, `it` is a local → its address is a MEM in the frame!). Hmm! `it` is a local variable → in the front end, `it = <const>` → expand_assign → the LHS is a MEM (frame slot). GCC's expand_assign: if the RHS is a constant and the LHS is a MEM, it might just store the constant to the memory slot. Then the load of `it` later is a MEM load → reload pass → the value is loaded from the stack... but with -O2 and the variable not address-taken, GCC promotes it to a register (SRA / local-alloc). GCC 2.7 doesn't have SRA; it relies on the front end keeping locals in "expand" pseudos? In GCC 2.7, local variables are memory (frame slots) unless the optimizer promotes them. Actually GCC 2.x has "local_alloc" and the front end does create a pseudo for a local variable when it's not address-taken? No: in GCC 2.x, all local variables live in memory (the frame), and the reload pass creates pseudos.

Hmm, but there's an optimization in expand_assign: `if (MEM_P (lhs) && GET_MODE...)`. Also `store_expr`...

Hmm, but GCC 2.x has a front-end optimization where a local variable that is never address-taken can be kept in a pseudo? I don't think so in 2.7; that came with the "local variables in registers" work in GCC 3.x? No, GCC 2.x did have that: expand_end_function / the "pseudo variable" mechanism? Hmm, in GCC 2.x, `expand_start_function` creates a frame and locals go to the stack. But there's `cse`/`reload` promoting.

Wait, but for -O2 with GCC 2.7.2, the local `it` is in a stack slot and the reload pass loads it. But the target code has no stack frame for this function (no sw sp). So `it` was promoted to a register.

Actually GCC 2.7.2 does have "local variables in registers" — the front end creates a pseudo for each local variable in `start_function`? I recall GCC 2.x: variables whose address is never taken are allocated to "local variables" which are actually memory, but the RTL optimizer (reload) can eliminate the stores/loads if the variable is not address-taken... no, that's SSA.

Hmm, in GCC 2.7.2, `expand_end_function`... Honestly, GCC 2.x does have `note_var_usage` and the "register" handling: `declare_function`? Let me instead check empirically: the candidate's code has no stack traffic for `it`, so it was promoted.

OK, empirical approach. Let me try several C spellings quickly and observe. Since each score takes ~1s, I can try many.

Spellings to try for item 2 (keeping semantics):
(a) `it = (s32)D_80120194;` → `p = it + 0x658C;` (current, folds)
(b) `p = (s32)(D_80120194 + 0x658C);` — hmm, that's not valid C for arrays; `D_80120194 + 0x658C` is pointer arithmetic on u8* → gives u8* → cast to s32. GCC folds to a constant address. The target needs base+offset form.
(c) Make `it` a `u32`: `it = (u32)D_80120194; p = it + 0x658C;`
(d) Use a separate variable for the base and make the address computed via a "cast chain": `it = (s32)(long)D_80120194;`
(e) Use `volatile`? not allowed (new lever).
(f) Use a function-like identity: e.g. `it = (s32)D_80120194;` then `p = it + 0x658C;` but insert `it = it;`? That's an identity statement launder → doesn't count.

Hmm, hold on! Wait. What about the OTHER direction: maybe I don't need to prevent the fold — maybe I need the fold to produce the TARGET's form! The target has:
```
lui v1, hi(D_80120194)
addiu v1, v1, lo(D_80120194)
addiu a0, v1, 25996
```
This is base+offset where the base is a materialized register. The alternative plain-C way to get this exact instruction sequence: what if `p` is computed as `base + 0x658C` where base is loaded from a *global pointer variable*? Not available.

What if the source computed p as `(s32)D_80120194 + 0x658C` where GCC folds to lui/addiu with addend → 2 instructions but different reloc addend. The target's 3 instructions (lui, addiu, addiu) require the base in a reg.

Hmm, unless the target's first two instructions come from a DIFFERENT source construct: e.g. `it = (s32)D_80120194;` where `it` is used LATER (not folded), and `p` is computed as `it + 0x658C` where the offset comes from a *variable*!

Idea: `p = it + off;` where `off` is a local `s32` initialized to 0x658C. Front end: off is a local → its value is in memory/reg; the front end doesn't know it. So `p = it + off` → plus(reg it, reg off) → then RTL: it = symbol_ref (const), off = 25996 (const). The fold of it+off into a constant requires cse to substitute both constants — possible in cse (both regs have constant values in the hash table).

Hmm, but the front end: for `off` (a local variable initialized to a constant), GCC 2.7's expand would emit `set off, 25996` (a pseudo with a constant) — and then `p = plus(it, off)`. Then cse might fold. But note: in GCC 2.7, local variables ARE in memory, so `off` would be a stack slot and `p = it + off` would be a load + add → reload pass would give a pseudo with the constant 25996 → then the add is reg+const → `addiu`. And `it` — the symbol address — the front end's expand_assign stores the const into the stack slot? Then `it` would be loaded from memory → reload → the load of a constant from a stack slot that was just stored → reload_cse might fold it to the constant. Hmm.

Wait, but the target has NO stack frame at all (no sw sp). So all locals were promoted to registers. So GCC 2.7.2 does promote locals to registers... yes! GCC 2.x does have "local variables in registers" via the `expand` "pseudo variable" mechanism? Hmm, actually I recall in GCC 2.x, `start_function` creates a "local vars" frame but the RTL optimizer's `reload` can keep them in registers only if their address is never taken — that's exactly what `cse`/`reload` do NOT do in 2.x...

OK, empirics beat theory. Let me look at the actual generated RTL! We have cc1 dumps tools. tools/cc1_dumps_tu.sh — dump the TU's cc1 RTL. That will tell me exactly what the front end produced and where the fold happened. The pointer says: ".run/P40/T10/hdump.sh (header pass dumps), tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps)".

Let me use cc1_dumps_tu.sh on the header TU to see the RTL for both orig and candidate. That's the fastest path to understanding.

But hmm, the header TU compile goes through the includer (ov_MAIN_012). Let me check tools/cc1_dumps_tu.sh usage.

Actually, let me first try the cheap experiments (a few C spellings), since each is 1s. Then use dumps if needed.

Let me create a batch script that tries several candidates and prints scores.

Candidate spellings for item 2:

s1: `it = (s32)D_80120194; p = it + 0x658C;` — baseline fold.
s2: same but `it` is `u32`: `it = (u32)D_80120194; p = it + 0x658C;`
s3: `it = (s32)D_80120194; p = it + (s32)0x658C;`
s4: use pointer type: `u8 *b = D_80120194; p = (s32)(b + 0x658C);`
s5: `it = (s32)D_80120194; p = it; p += 0x658C;`
s6: keep the base alive: `it = (s32)D_80120194; p = it + 0x658C;` where `it` is also compared somewhere? changes semantics.
s7: `it = (s32)(u32)D_80120194;`
s8: `it = (s32)D_80120194; p = it + 0x658C;` with `it` declared as `unsigned long`? (32-bit target; long = 32 bits)

Hmm, all of these are likely folded.

Radically different idea: maybe the real original source computed p from a *different* base that's naturally in a register. For instance:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
vs
```c
p = (s32)D_801202A0 + 0x6480;   /* same value 0x80126720 */
```
folded → lui/addiu with addend 0x6480 → the target has 25996=0x658C with base D_80120194. Not matching.

Hmm OK. So what if the target's `lui v1; addiu v1` is NOT the address of D_80120194 but something else that coincidentally... no, the relocs say D_80120194 HI16/LO16.

So GCC materialized &D_80120194 into a register and added 0x658C.

Think about GCC 2.7.2's `reload`: when a local variable holds a constant address and is used in an address context (plus const), the reload pass creates a pseudo for the address and adds the offset. In GCC 2.x, address arithmetic like `p = it + 0x658C` where it is a pointer to a global: the front end computes the address `&D_80120194 + 0x658C` as an ADDR_EXPR+offset → the front end generates a MEM with that address → the reload pass creates the address in a register (pseudo) → `lui/addiu` with the constant folded in the address → then `load`/`add`? Hmm, but then we'd get the folded form (my version).

For the target to have the base in a register with a separate addiu, the front end must have produced `p = it + 0x658C` where `it` is a *variable* (not an address expression) — i.e. `it` holds a pointer value loaded from somewhere. Then the front end: `it` is a local var of type s32 → it's a MEM load. But the target has no memory traffic for it! So `it` must have been a *pseudo* holding the address.

Hmm, so in the target, `it` was a register pseudo holding &D_80120194 — meaning the front end did NOT put the constant into the frame slot. Which happens when the local variable is "register-allocated" by the front end? In GCC 2.x there IS such a mechanism for variables whose address is never taken: `expand_start_function` → `alloca`... hmm, no.

WAIT. I remember now: GCC 2.x has the "LOCAL_VARIABLE" mechanism? Let me check gcc 2.7.2's function.c: `start_function` sets up the frame; local vars are allocated in the frame by `assign_parms`/`expand_start_function`. But there's `note_var_usage` and in `expand_end_function`...

But the key: in GCC 2.x, `expand_assign` to a local variable MEM: the value is stored to the frame slot. Then reading it is a load. The RTL optimizer (reload) then eliminates the store/load pair via "reload_cse"? In GCC 2.x, `reload` has `cse_basic_block` merging the store and load if the frame slot isn't otherwise used → the load gets the constant value → the pseudo holds the constant.

So `it` as a pseudo = constant symbol_ref. Then `it + 0x658C` → the front end's expand of `it + 0x658C`: since `it` is a variable (MEM), the front end computes MEM(it) + 0x658C → expand → the load gives a reg, then plus const → RTL: plus(reg, const). Then cse: the reg's value = symbol_ref (a constant) → cse substitutes → the address becomes (plus symbol_ref const) → and then the final address materialization folds the addend into the lui/addiu → my version.

The launder prevented this by making `it` a REG (the asm output), so the pseudo's value is a REG, not a constant. Then `it + 0x658C` stays plus(reg, const) → `addiu a0, v1, 25996`. And the address materialization `lui v1; addiu v1` came from the asm's input copy (the constant was materialized into a reg because the asm needs a register operand).

So: to reproduce, we need a REG (not CONST) holding &D_80120194.

How to make GCC materialize a symbol address into a register in plain C? Answer: **use it as a value in a context that requires a register, e.g. store it into memory or pass it to a function**. Hmm.

Or: **make the address non-constant**.

Hmm, hold on! What about `&D_80120194` where D_80120194 is declared as `extern u8 D_80120194[];` — what if we take the address of a *local* struct? no.

IDEA: What about the *order of the two assignments*? The target materializes &D_80120194 in v1 and then &D_801202A0 in v1 again at 4190. If in the source the second assignment came first... no.

IDEA 2: **The loop structure.** What if we restructure so the base address is used as a loop bound or something? Semantics must stay.

IDEA 3: **Use an unsigned/signed trick**: `it = (s32)(u32)D_80120194;` — the front end: cast to u32 then to s32 → no-op → still const.

IDEA 4: What if we do the addition in the *pointer* domain with a type whose size differs, so GCC computes base + 0x658C as a scaled index? e.g. `p = (s32)(D_80120194 + 0x658C/4)` with u32* type → the byte offset would be 0x658C anyway (0x658C/4 = 0x6593 truncated → 0x6593*4 = 0x664C ≠ 0x658C). Not exact.

IDEA 5: The "identity-statement launder" note says `w = (w>>16<<16)|x` doesn't count. Hmm, that hints that some agents tried such tricks.

IDEA 6: What about making the address come from a *struct member of a global* — e.g., if D_80120194 were part of a larger global array, then `&arr[0]` vs `&arr[k]`: GCC folds both.

Hmm, so how do real decompilers handle this? They use `register` + asm, or they accept the difference. But the project wants plain C.

Hmm, hold on. Maybe there IS a plain-C spelling: what if the offset 0x658C is applied to a variable that GCC can't fold because the variable is *volatile*? Not allowed.

What if the variable is read via a pointer to it (address taken)? Then it lives in memory and the load is a real load → the target has no such load.

Hmm, what about this: the target's `addiu a0, v1, 25996` — what if in the source, p is computed as `it + 0x658C` where `it` is a *pointer to a struct* and 0x658C is a *field offset*? Same RTL.

OK OK. Let me reconsider: maybe the fold isn't cse but the FRONT END, and the front end's behavior depends on the *type* of the assignment. In particular:

In GCC 2.x's expand_assign, there's an optimization:
```c
  /* If the RHS is a constant, and the LHS is a MEM that is not volatile... */
```
Hmm, that stores to memory.

But there's ALSO in expand_expr for ADDR_EXPR: `ADDR_EXPR` of a DECL → `expand_addr` → if the decl's address is constant → `x = constant` → the result is a CONST node (symbol_ref). Then in `expand_assign` for `it = CONST`, since `it` is a local variable MEM, GCC might do `store_expr`... The front end then has MEM = CONST.

Then the reload pass: the load from the slot gets the constant → pseudo = constant.

Hmm, so the question is whether GCC's reload/cse can *keep* the pseudo as a REG holding the address. There IS such a case: if the value must be in a register because it's used in a way that requires a register (e.g. as the base of a MEM with a variable offset, or as an operand of an arithmetic op). In our case `it + 0x658C` → the front end does: load it (pseudo), then plus with const → the reload pass creates a pseudo for the address? Let's think about the front end's expansion of `it + 0x658C` where `it` is `s32`:

expand_expr(BINARY_PLUS): expands the LHS `it` → a MEM load (reg), then the RHS const → then emits `plus(reg, const)`. RTL: (set p (plus (reg it_load) (const_int 25996))).

Now, cse: `it_load`'s value = symbol_ref (const). cse's `simplify_gen_binary` → `fold` on (plus (reg) (const)) → no fold (the reg isn't a constant at RTL level; only cse knows its value). But cse.c has a step: in `cse_basic_block`, for each insn it calls `cse_record` etc. But the substitution of a register with a constant happens in `cse.cse_basic_block` via:

```c
	  /* If we are looking at a constant, ... */
```
Hmm, actually I recall cse.c's `cse_basic_block` has this:

```c
	      /* If this insn is a copy of a constant, ... */
```

The function `cse_const` in cse.c:
```c
/* Record that X is the value of a constant ... */
static void
cse_const (x, cse_data)
```
Let me grep it. Earlier grep for "cse_const" found nothing in cse.c! So the fold isn't cse.

So where does the register get replaced by its constant value? That's `reload`? No... It's probably in the FRONT END after all: in GCC 2.x, `expand_assign` has:

```c
  /* If the RHS is a constant and the LHS is a register or a local variable
     that is not address-taken... */
```

Hmm. Actually! I recall in GCC 2.x's `expand_end_function`... no. But I DO recall: in GCC 2.x, the front end's `expand_expr` for a variable that's a local: `expand_expr` on a VAR_DECL returns a MEM. But before that, there's the pass in `cse`/`jump`...

Alternatively: **the front end folds at the "store" level**: `it = (s32)D_80120194` → expand_assign with RHS = CONST(symbol_ref) and LHS = MEM(frame slot). GCC 2.7's expand_assign:

```c
  if (TREE_CODE (lhs) == VAR_DECL ...) 
  ...
  /* If the value is a constant, store it directly? */
```
It emits `set (mem) (symbol_ref)`. Then the load `it` later reads the mem. In the reload pass, the store to the slot and the load from the slot: reload's `cse` (reload_cse) merges them → the load's value = symbol_ref constant → reload creates a pseudo with that constant... Actually reload would create a pseudo and set it to the constant (reg = symbol_ref) and then the plus uses the pseudo.

Then the fold: in reload, when the pseudo's value is a constant and it's used in an address or arithmetic, GCC 2.x's reload might substitute the constant into the insn, making the address (plus symbol_ref const) → and then the address gets folded into the lui/addiu with addend → my version. That's the "reload-rematerialise" wall in moves.md! Yes: "launder | func_80185380 | WALL reload-rematerialise — reload: unk6C via char* keeps 111 ins exact but &D_80190048 is rematerialised into at instead of held in v1".

So reload rematerializes constant addresses. The launder (asm) makes the value a REG so reload can't rematerialize.

So the question: how to get a REG holding the address in plain C?

In GCC, a pseudo whose value is a constant gets "rematerialized" by reload only if it's cheaper. But if the pseudo is used in a context where a constant isn't allowed (e.g. as the base of a MEM with a *variable* offset), reload must keep it in a reg.

Hmm! In our target, the base is used as `reg + const` (an arithmetic op, not a memory address). The load would be from the frame slot. Hmm.

Wait, actually, hold on. Let me re-examine: maybe the target's `lui v1; addiu v1` is NOT a rematerialized constant but the result of `it` being *promoted* differently.

New idea: what if the source's `it` is NOT a local variable but a *parameter* or has `register`? We're told "no register vars" for new code, but the def already has none here.

Hmm, let me look at this from a completely different angle: what if the original source used a DIFFERENT expression for the base, e.g.:

```c
it = (s32)&D_80120194[0];
```
no.

What about the *second* symbol: `it = (s32)D_801202A0;` — the target materializes that one plainly too (lui v1; addiu v1) and it IS used in a MEM (`lhu v0,0(v1)`) and in a compare. In MY candidate, that one is also materialized plainly (lui v1; addiu v1) — because it's used as a memory base, so it must be a reg.

So the difference is only for the first address, used once in an arithmetic op.

So the fix: make the first address be used as a MEM base or otherwise force a reg. But semantics...

IDEA: What if we express the loop bound differently so that the first address is used as a memory base? E.g.:

The loop: it starts at D_801202A0, increments by 0x10C until it == p (p = D_80120194+0x658C).

Alternative formulation: iterate over the array from D_80120194 with an index? The semantics: the function returns the address of the first zero u16 entry scanning from D_801202A0 up to p. Hmm, wait: it starts at D_801202A0 and goes up by 0x10C to p = D_80126720. And D_801202A0 = D_80120194 + 0x10C. So the scan starts one entry after the base and ends at base + 0x659 entries (0x658C/0x10C = 0x64 = 100 entries).

Alternative formulation: `it` starts at base+0x10C and the loop condition is `it != p`. If we rewrote it as a loop over an index from 1 to 100: `for (i = 1; i <= 100; i++) { e = base + i*0x10C; ... }` — that changes the code completely. No.

OK so we need: `p = base_reg + 0x658C` where base_reg holds &D_80120194.

Since the address is a compile-time constant, GCC will always fold it... unless the pseudo is forced to be a reg.

**KEY INSIGHT attempt**: In GCC 2.7.2's reload pass, a pseudo whose value is a constant CAN be kept in a register if the register is cheaper or if it's used in a context requiring a reg. Specifically, reload has "rematerialization" for constants: `reload` will rematerialize a constant into the register each time it's needed. But for a constant that's a SYMBOL_REF address, the cost might be high, so reload keeps it in a reg.

In my candidate, the pseudo for `it` was rematerialized as (plus symbol_ref const) → folded into the address operand of the addiu.

Hmm, what if the offset were applied to a *variable*? e.g.

```c
s32 off;
it = (s32)D_80120194;
off = 0x658C;
p = it + off;
```
Front end: off is a local → MEM → load → the load's value = 25996 (constant). RTL: plus(reg_it, reg_off). Then cse/reload: reg_off is a constant → reload rematerializes it as 25996 → plus(reg, const) → addiu. And reg_it is a constant address → reload rematerializes it as (symbol_ref) → then plus(symbol_ref, const) → folded address → the SAME as now, probably.

Hmm. Unless reload can't rematerialize `it` because it's used... only once. Ugh.

**Different approach**: maybe I should look at what the ORIGINAL source was, from the ROM's perspective. The project may have a "recovered original" or the target was compiled from the actual game source (which we don't have). The target's code was compiled by the ORIGINAL PSX gcc 2.7.2 with the original source. So the original source's spelling produced this code. Our job: find a spelling that reproduces it.

The original source probably looked like:
```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
}
```
Hmm, but that folds for us...

UNLESS: in the original, `D_80120194` was declared differently, e.g. as a `static` array or with a different type, or the original had `extern u32 D_80120194[];`... The address is the same regardless.

Hmm, but wait: what if in the original the pointer arithmetic was on a *pointer* variable:
```c
u8 *it;
it = D_80120194;
p = (s32)(it + 0x658C);
```
Front end: `it + 0x658C` where it is a pointer variable → the front end expands to (plus (reg load_it) (const 25996))? Or does the front end compute the address as an ADDR_EXPR? For pointer arithmetic on a variable, the front end emits a load + plus. Then reload rematerializes the load as the constant address → plus(symbol_ref, 25996) → folded → lui/addiu with addend. Same.

Hmm, so how did the ORIGINAL get base+offset?

Unless the original had TWO separate statements:
```c
it = (s32)D_80120194;   /* used again later */
p = it + 0x658C;
```
where `it` was ALSO used later so it needed a reg! But in the current source, `it` is reassigned to D_801202A0 before any later use.

What if the original source had TWO variables:
```c
s32 base;
s32 it;
base = (s32)D_80120194;
p = base + 0x658C;
it = (s32)D_801202A0;
...
```
Then `base` is used once (still folded). Hmm, unless `base` is used in the loop bound!

AH WAIT. Look at func_8012C750 (the sibling!):
```c
s32 base = (s32)D_80120194;
p = base + 0x6480;
if (p != base) { do { ... p -= 0x10C; } while (p != base); }
```
Here `base` is used TWICE: once for p = base + 0x6480 and once in the comparison `p != base` / `while (p != base)`. THAT's why the base stays in a register! And note: in C750, the target presumably has `lui v1, hi(D_80120194); addiu v1,v1,lo; addiu a0,v1,0x6480` — base in a reg!

So for C750, the base IS used twice → GCC keeps it in a reg → no launder needed?! But C750's current source has launders on `it` (the D_80120194 value in the else branch) — where the base is used only once (p = it + 0x658C) → folded.

Hmm interesting. So in C750's else branch, the same structure as C2D0.

But in C2D0, `it` (the first one) is used only once.

Hmm, so how did the original C2D0 keep it? Let me look at the target of C2D0 again:

```
4178: lui v1, hi(D_80120194)
417c: addiu v1,v1,lo
4180: j 4190
4184: addiu a0,v1,25996
```

What if the original source was:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
where `it` is ALSO used in the loop as the *upper bound*?! Wait: the loop is:
```
test: it = (s32)D_801202A0; if (it == p) goto zero;
body: if (*(u16*)it == 0) goto copy; it += 0x10C; if (it != p) goto body;
```
So p is the bound and `it` walks. The first `it` (=D_80120194) is used only for p.

Hmm, unless the original was:
```c
it = (s32)D_80120194;
p = it + 0x658C;
...
test:
    it = (s32)D_801202A0;
```
Hmm.

Wait wait wait. What if the original source was:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
BUT with `it` being a *pointer* and `p` a pointer, and the *comparison* `if (it == p)` where `it` is later reassigned...

Honestly, the empirical route: since in C750 the base is used twice (in the `if (p != base)` test), maybe in C2D0's original the base was used twice too, e.g.:

```c
s32 base;
base = (s32)D_80120194;
p = base + 0x658C;
...
```
with base used once → folds.

Hmm. What if the original source of C2D0 was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
...
```
and GCC 2.7.2 (the ORIGINAL PSX compiler) did NOT fold it because the original build used different flags? The project's build uses `-O2 -G0 -mips1 -mcpu=3000`. Hmm, the original might have been compiled with different flags, but the project reproduced the rest of the ROM with these flags, so probably the same.

Hmm, but here's a thought: the "P36 rung B headers1" comment suggests these headers were converted to a shared body and the levers were re-added artificially. The original per-member sources (before dedup) may have had the launder... The phase's goal is to find plain C.

Let me look at how another shard cracked a similar "cse-const-addr" case — moves.md: "launder | func_80183098 | WALL cse-const-addr — cse: find_best_addr rematerialises the +4 address for cam->y (lui+addiu) instead of the base reg; only an opaque (asm) base keeps lh 4(s1) (G14)" — a WALL. And "pin | func_80180C04 | MATCH: $0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse".

Hmm! "flag declared s16: HImode flag=1 test not folded by cse" — interesting trick: using a narrow type to escape cse's folding.

So maybe for our case: if the base variable is declared with a narrower type, the constant isn't folded the same way? E.g. `it` is s32 holding an address; if we declared a `u16`/`s16` temp... no, addresses don't fit.

Hmm, what about this: the HImode trick works because a copy of a value into a narrow type is a SUBREG/zero-extension that cse doesn't fold. Here, the address is 32-bit; a narrow type can't hold it.

What about a *float*? `it = (s32)(float)D_80120194;` — no, precision.

Hmm, what about the reverse: keep `p` in a narrow... no.

Let's think about reload's rematerialization more concretely. In GCC 2.7.2's reload.c, `reload()` decides whether to put a value in a register or rematerialize it. For a pseudo whose value is a constant (from the cse/reg-load of the frame slot), reload checks `reg_equiv_contain_p` and `reload_cse`. There's a specific optimization: "cse_basic_block" in reload merges the store and load.

Then, when the pseudo's value is a constant, the RTL is `(set (pseudo) (symbol_ref))`. Then the use `(plus (pseudo) (const 25996))`. Then reload processes the insn: the pseudo is in the "reg_equiv" class; reload may substitute the constant directly into the insn (reload's `reload_reg` with `reg_equiv`) → giving `(plus (symbol_ref) (const 25996))` → then the address/arith simplification folds → the final form is a MEM-style address or a constant → the mips backend emits lui/addiu with the addend.

To prevent this, the pseudo must NOT be in reg_equiv (i.e., its value must not be a constant). This happens if the value is set by a *non-constant* insn.

So: **what if the address is computed by an arithmetic operation on a constant that GCC can't fold into a single symbol?** For example:

```c
it = (s32)D_80120194 + 0;  /* folded */
```

What about:
```c
it = (s32)(D_80120194 - 0x10C) + 0x10C;   /* front-end folds */
```
The front end folds constant arithmetic on constants. Since &D_80120194 is a constant (ADDR_EXPR of a decl with a constant address → constant), any arithmetic folds.

**Unless the decl's address is not constant!** When is a global's address not a compile-time constant? Never for a normal global. But for a *local static*? Also constant.

**What if the address is of a function?** `extern void f();` → the address of a function is a symbol too.

**What if the array is declared `extern u8 D_80120194[];` and we take `&D_80120194[N]` with a runtime N?** Then the address is (symbol_ref + N*size) — not constant! E.g.:

```c
it = (s32)&D_80120194[1] - 1;  /* folds */
```

Hmm. But what if we use a runtime index? We have no runtime value available... except the function's own data. Hmm, but adding a runtime-dependent term changes semantics.

OK, radically different: **maybe the target's base reg v1 is not a "kept constant" but rather GCC's own choice, and the fold can be avoided by making the FIRST address be used in a MEM context** — e.g., by rewriting the loop so the first address is dereferenced? Semantics forbid.

Hmm, hold on. Let me revisit the possibility that the ORIGINAL source for C2D0 differs from our current source in a bigger way. The current source was auto-generated by the decomp pipeline (a "shared body"), with the launder added to make it byte-match. The original ROM code came from the game's source. The game's source for this function might be:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```

Hmm, but how did the game's compiler keep the base in a reg?

AH WAIT!!! What if the original code was:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
where `it` is declared as a POINTER and the addition `it + 0x658C` is done in *pointer* arithmetic... and GCC's front end for pointer + constant generates a MEM address (not a plus in a reg):

`p = (s32)(D_80120194 + 0x658C)` → the front end: ADDR_EXPR + offset → this is a "constant address" → the whole thing folds to a single address constant → lui/addiu with addend → my version.

vs `it` being a VARIABLE → the load → plus.

Hmm, so in the target, the plus is in a reg: `addiu a0, v1, 25996` where v1 is the base. So the front end DID produce a plus of a register and a constant, and the register was NOT substituted with the constant.

The only way: the register's value was not known to be a constant at RTL level. Which happens if the register is set by an insn whose value isn't a constant... The asm launder does that. Or if the front end put the constant in a reg via `force_operand`/`emit_move_insn` with a REG_DEST (i.e., the assignment `it = (s32)D_80120194` where `it` is a local var that GCC keeps in a register rather than memory!).

**In GCC 2.x, local variables CAN be kept in registers if declared `register`!** YES! `register s32 it;` → GCC 2.x keeps it in a pseudo (a "register variable" is allocated a pseudo register, not a stack slot). Then `it = (s32)D_80120194` → expand_assign: the LHS is a pseudo REG → the front end emits `set (pseudo) (symbol_ref)` — the pseudo's value IS the constant symbol_ref, but as a REG_DEST. Then in the reload pass, the pseudo is a "reg_equiv" → could still be substituted with the constant...

Hmm, but here's the thing: for a register variable, GCC 2.x creates the pseudo at function entry with the value in a "reg" and the assignment `it = const` sets the pseudo. Then `p = it + 0x658C` → plus(pseudo, const). Then cse/reload: the pseudo's value = symbol_ref constant. In reload, `reload_reg` for a pseudo with a constant value: it might keep the constant in the register (since reload of a constant is cheap: it's rematerialized) → the pseudo becomes the constant → then the plus folds.

Hmm, but there's a subtlety: in GCC, when the value of a register variable is a constant, the front end's `set (pseudo) (const)` and reload's `reg_equiv` handling: reload would replace the pseudo's uses with the constant → fold.

BUT: the moves.md entry "pin | func_80180C04 | MATCH: $0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse" and "launder | func_80184174 | MATCH: launder->pv = *p; pv &= 0xFF000000 split (real 2nd set); $3 pin dropped; $4 ang pin kept (non-row kind), pin-free 4" show that the "real 2nd set" (a second assignment to the same variable) is a powerful trick: it makes the variable's value NOT a single constant (2 sets → the pseudo isn't reg_equiv to a constant).

**So: give `it` a SECOND set!** In the target, the first `it` value (&D_80120194) is in v1 and later `it` is set to &D_801202A0 — those are already 2 sets of the source variable `it`! But GCC splits them into 2 pseudos, and the FIRST pseudo has a single constant set → substituted.

Hmm, so how do we make the first pseudo's value not a constant? Give it two sets: e.g.

```c
it = (s32)D_80120194;
it = it;         /* identity — but that's an identity launder, doesn't count */
```

Hmm. What about a value-preserving second set that isn't an identity? E.g. `it = (s32)D_80120194; it = it + 0;`? That's identity too (and might be flagged as an identity launder). Hmm, "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack" — so `it = it + 0` would be an identity statement → doesn't count as a crack. Hmm. But `it = it + 0` gives `it` a second SET — is it an "identity statement launder"? Yes, it is literally an identity statement.

But hold on: the trick used in G14/G15 ("real 2nd set") was e.g. `v = (s16)v;` — a cast, value-preserving, NOT an identity statement in the "w = (w>>16<<16)|x" sense... Hmm, `v = (s16)v` IS an identity in value but a real conversion (HImode) that escapes cse. The note in the brief says: "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". So a cast that changes the mode is acceptable (it's a "real 2nd set" per G14), but a pure identity like `w = (w>>16<<16)|x` or `x = x + 0` does not count.

Hmm, so what would be a legitimate "real 2nd set" for `it`?

Wait, maybe I don't need a 2nd set at all. Let me reconsider: the first pseudo's value is the constant symbol_ref. If the pseudo has 2 sets, it's not a single constant → not reg_equiv → stays a reg.

But how do we give the FIRST it a second set without changing semantics? Hmm: `it` is later reassigned to D_801202A0 — but that's a different pseudo (different set).

Hmm, what if we introduce a new variable that holds the base and is used twice:
```c
s32 base = (s32)D_80120194;   /* hmm, used once */
```

What if we restructure so that the base address is used twice — e.g., compute p from the base AND compare the base?

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
The only use of `it` is in p.

Restructure idea: express the loop bound as `p` and ALSO the start as base+0x10C:
```c
base = (s32)D_80120194;
p = base + 0x658C;
it = base + 0x10C;   /* = D_801202A0 */
```
Then base is used twice → base stays in a reg (v1) and `it = base + 0x10C` → hmm, but then the target's second materialization `lui v1, hi(D_801202A0); addiu v1,v1,lo(D_801202A0)` would become `addiu v1, v1, 0x10C` — NOT matching the target (which materializes D_801202A0 with lui/addiu).

So no.

OK, let me now think about the *reload* mechanism concretely and find a spelling where the pseudo is not reg_equiv.

Honestly, the most promising: make the first `it` value have TWO sets. What if we write:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
as
```c
it = (s32)D_80120194;
it = (s32)D_80120194;   /* second set, same value */
p = it + 0x658C;
```
That's a redundant re-assignment — an "identity statement"? It's a duplicate assignment of the same constant. Hmm, it's a "dead reset"-ish trick. G15 used "DEAD-RESET CSE-BREAKER (§373): pb=&buf; call(pb); pb=0; before every site" — a dead reset! So the project has a cookbook entry §373 about dead resets breaking cse's address class.

But here the second set of the SAME value doesn't create a new pseudo — GCC would just have one pseudo with 2 sets → not reg_equiv → the pseudo keeps a register! That's exactly the "real 2nd set" trick from G14/G15 ("the vol 2nd set that restores the multiply order (u16 cast = 1 andi)"). They used a cast to make it a real 2nd set.

But here the second set would be a *dead* assignment (the value is the same). Would the judge consider it an "identity statement launder"? The brief says: "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". A dead duplicate assignment `it = (s32)D_80120194;` twice — hmm, "identity address spellings" might cover exactly this ("it = &D_80120194" written twice = an identity address spelling). Risky.

Let me think about what the ORIGINAL source most likely was, since the target must be reproducible from a natural source. Let me reconsider...

AH WAIT!!! I think I've got it. What if the original source was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
```
where the ORIGINAL declared `D_80120194` as something whose address is NOT a link-time constant...

Hmm, actually, hold on! What if in the original, the *base* was not `D_80120194` but a pointer stored in a global? Look: `D_80120194` and `D_801202A0` are 0x10C apart, and the loop steps by 0x10C. So D_80120194 is an array of 0x10C-sized entries (like a linked-list node array?). The function scans from D_801202A0 to D_80120194+0x658C.

In C750, the same base appears: `s32 base = (s32)D_80120194; p = base + 0x6480; if (p != base) {...}`. So the base is used twice in C750 → kept in a reg → no fold. That's consistent with my theory!

And in C750's ELSE branch (the laundered one), the code is the C2D0 pattern (base used once) → the launder is needed there.

Hmm, so in the ORIGINAL source, C2D0's base was used once and yet kept in a reg. So the original must have had something else.

Unless the original C2D0 was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    ...
```

Hmm, what if the original had `p` computed BEFORE... no.

Let me look at the target's structure once more:

```
4178: lui v1, hi(D_80120194)
417c: addiu v1,v1,lo(D_80120194)
4180: j 4190
4184: addiu a0,v1,25996       <- delay slot of the j
4188: j 41bc
418c: move v0,v1
4190: lui v1, hi(D_801202A0)
4194: addiu v1,v1,lo(D_801202A0)
4198: beq v1,a0,41bc
419c: move v0,zero
```

Note the `j 4190` at 4180 with the delay slot `addiu a0,v1,25996`. This is the "goto test" jump. The delay slot computation of p is filled by sched.

Now compare with C750's target (which has the same base pattern in the else branch, but there the base IS used twice → maybe no launder needed there?). Let me dump C750's target and see whether the else-branch base is in a reg.

Actually! Important: in C750 the else branch is:
```c
it = (s32)D_80120194;
[launder]
p = it + 0x658C;
```
base used once → same problem. But in the IF branch:
```c
s32 base = (s32)D_80120194;
p = base + 0x6480;
if (p != base) { do {...} while (p != base); }
```
base used 3 times → reg.

Hmm, so in C750 the IF branch has no launder (consistent with "used twice → reg") and the ELSE branch needs one.

Now, what if in the ORIGINAL source, C2D0's structure was such that the base was used twice? For instance:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16*)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    return 0;
}
```

Hmm, here's a thought: what if the original was written with a *pointer* type and pointer comparison:

```c
u8 *it;
u8 *p;
it = D_80120194;
p = it + 0x658C;
```
The front end: `it + 0x658C` where it is a pointer VAR → load + plus(const). Then reload: the load's value is the constant &D_80120194 → hmm same.

Hmm, but here's a subtle difference: for a POINTER variable, the front end might do address arithmetic differently: `expand_expr` for `it + 0x658C` → `plus_expansion` → it computes the address as a MEM? Specifically, in GCC 2.x, `plus_expansion` handles the case where the base is an ADDR_EXPR: it folds into a MEM address (a constant address). But if the base is a variable (a load), it does reg + const.

So both are the same in our case.

OK, let me now consider: maybe the answer is that the ORIGINAL source had the base used twice, e.g.:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
Wait!!! What if the ORIGINAL source reused `it` for the base in the LOOP too? I.e., what if the loop was:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
    it += 0x10C;   /* from the base! */
```
Hmm: the loop goes from D_801202A0 to p. What if the original was:

```c
    it = (s32)D_80120194;    /* base */
    p = it + 0x658C;         /* end */
    it += 0x10C;             /* it = base + 0x10C = D_801202A0 */
    goto test;
test:
    if (it == p) goto zero;
body:
    if (*(u16*)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```

Then the base `it` is used twice: `p = it + 0x658C` and `it += 0x10C` → so `it` (the base pseudo) is live across... hmm, but `it` is reassigned by `it += 0x10C` — that's a different set of the same variable. GCC creates a new pseudo for the incremented value; the base pseudo is still used twice (in p = base + 0x658C and in it_new = base + 0x10C) → the base pseudo has 2 uses → GCC must materialize it in a register? Hmm, with 2 uses, reload's reg_equiv substitution could still substitute the constant into both uses (both are plus-with-const) → folding into a single address each. Hmm, but reload would then produce two lui/addiu pairs (2 materializations) instead of one. Hmm, but reload's reg_equiv substitution has a cost heuristic: if the constant is used multiple times, it's cheaper to keep it in a register! Yes — reload's `reload_cse`/reg_equiv: if a pseudo is set to a constant and used more than once, reload keeps it in a register (the cost of rematerializing twice > the cost of a register).

But hold on: in the target, the second materialization is `lui v1; addiu v1` for D_801202A0 (a different symbol), so the base pseudo is used only ONCE in the target (for the addiu a0,v1,25996). Hmm, so the base's second use (it += 0x10C) doesn't exist in the target's code — the target's `it` at 4190 = &D_801202A0 materialized with lui/addiu. So in the target, the value D_801202A0 is materialized as a constant address, NOT derived from the base.

So the original source did `it = (s32)D_801202A0` directly (a separate constant). And the base &D_80120194 was materialized once (lui v1, addiu v1) and used once (addiu a0,v1,25996).

So the base pseudo has ONE use, and GCC kept it in a register. That contradicts the "fold" theory... unless the base pseudo was NOT a constant in the original!

WAIT. What if in the original, the base was NOT &D_80120194 directly but something computed at runtime? Look at the target: `lui v1, hi(D_80120194); addiu v1,v1,lo(D_80120194)` — that IS the constant address materialized in a register. This is exactly what GCC does when a *pseudo* holds a symbol_ref and is used in an arithmetic op (not an address). I.e., the pseudo's value is a constant, but GCC keeps it in a reg because... the use is `plus(pseudo, const)`.

In MY compile, the pseudo was substituted with the constant and the whole thing became a constant address (plus symbol_ref const) which the backend materialized as lui/addiu with the addend.

So the difference is whether reload/cse substitutes the constant into the plus. reload's reg_equiv substitution happens when the pseudo's value is a constant AND the pseudo is "cheap to rematerialize". The decision is in reload.c: `reload_reg` → if `reg_equiv_contain_p` and the value is a constant, reload can either rematerialize or keep the reg. There's a heuristic based on the number of references and the cost.

Hmm, in my compile the substitution happened. In the original compile it didn't. What could differ? THE FRONT END: whether the pseudo's value was a constant at all.

**IDEA**: What if the original code assigned the base via a *pointer-typed* variable that GCC 2.7.2 keeps in a register?? no...

**BETTER IDEA**: What if the original source was:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
where the compiler was NOT folding because the *order* of the expansion differs: the front end expands `p = it + 0x658C` where `it` is a MEM → the front end's expand_expr(BINARY_PLUS) → expand the LHS (a load) → then `plus_expansion` → it might convert the load into an address computation: since `it` is a variable of type s32, `it + 0x658C` is just an integer add: reg + const.

OK. Empirical: let me look at the cc1 RTL dump for the candidate to see exactly where the constant gets substituted. tools/cc1_dumps_tu.sh dumps the TU's cc1 RTL (for a header: through an includer). Let's check what it produces.

Actually, maybe simpler: let me look at the original PSX source style. The game is PSX (Psychonauts? no — 0x8012xxxx addresses, D_800AE620 Mat32, RotMatrixX — this is PSX "Lemmings"? or "Rhythm Jack"? Actually 8012xxxx with GsSortLine → PlayStation game). The original source style for such functions (from the game's SDK) might be:

```c
s32 func_8012C2D0() {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```

Hmm.

Let me try the "2 uses" idea concretely and see what GCC produces. Even if it doesn't match exactly, it tells me about reload's behavior. Actually, better: let me test the hypothesis directly with a tiny experiment: does GCC keep a constant in a reg when the pseudo is used twice in plus-operations? If yes, then I need a formulation where the base has 2 uses — but any second use changes the code...

Hmm, unless the second use is DEAD (like the §373 DEAD-RESET trick): e.g.
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
Hmm, a dead reset would be `it = 0;` after the use — but that kills the value for later uses... The base has no later uses.

Hmm! But wait: maybe a dead reset BEFORE the use:
```c
it = 0;              /* dead */
it = (s32)D_80120194;
p = it + 0x658C;
```
This gives the pseudo 2 sets: the first is dead (constant 0). Then the pseudo's value isn't a single constant → reg_equiv doesn't apply → the pseudo stays in a reg → GCC materializes &D_80120194 into v1 and does addiu a0,v1,25996!! That's exactly the §373 DEAD-RESET trick from G15!

And it's not an "identity statement launder" — it's a dead store, a known project technique (cookbook §373). But is it "a new lever"? It's a real C move (the brief's catalog mentions "statement order, init at decl, temps..."). The §373 dead-reset was used in a MATCH by G15 ("launder | func_8018A180 | MATCH — DEAD-RESET CSE-BREAKER (§373)"). So it's an accepted technique!

Hmm, but here the dead reset is *before* the assignment, so it doesn't break the cse address class of the SECOND set... Actually the point is to give the pseudo 2 sets so it's not reg_equiv to a constant.

Hmm, but will GCC's cse then fold the plus? Let's test! Quick experiment.

Let me write candidate w2.c:

```c
s32 func_8012C2D0(void)
{
    s32 p;
    s32 it;
    it = 0;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```

Hmm, but `it = 0;` then `it = (s32)D_80120194;` — GCC's front end: the first store is dead? The front end might eliminate it. But at the RTL level, the pseudo has 2 sets → not reg_equiv → stays.

Hmm, but actually if the pseudo is a local variable in MEM (frame slot), the front end stores 0 then the address; reload's cse merges the loads. The load after the 2nd store → the value is the address constant → and the reload's `reg_equiv` for the pseudo... the pseudo has 2 sets → `reg_equiv_contain_p` returns the last value but reload checks the number of sets? In reload.c, `reg_equiv_contain_p` walks the reg_equiv list and finds a single equivalent; if there are multiple conflicting values, the pseudo is NOT reg_equiv → it gets a real register.

Let me just test it. Also test the alternative: `it = (s32)D_80120194; it = it;` etc.

Let me create a batch of candidates and score them.

Actually, wait. Before that, let me reconsider the "dead reset" placement. If I write:
```c
it = 0;
it = (s32)D_80120194;
```
The dead store `it = 0` might be removed by the front end? GCC 2.7 doesn't do dead store elimination at the front end (no SSA). At the RTL level, cse might remove the first store as dead (cse does eliminate stores to a pseudo that are overwritten before any read? cse.c does have "cse.cse_basic_block" removing a set that is dead — yes, cse removes redundant/dead sets for pseudos). Hmm, if cse removes the dead store, we're back to 1 set.

But the trick in §373 (per moves.md) was: "pb=&buf; call(pb); pb=0; before every site; cse's &buf address class breaks". So the dead reset AFTER a use breaks the address class. In our case, the base's use is `p = it + 0x658C`. If we put a dead reset AFTER that use:
```c
it = (s32)D_80120194;
p = it + 0x658C;
it = 0;    /* dead reset */
```
Then the pseudo has 2 sets: the address and 0. But the use of `it` (the address) happens between them → the pseudo is live at that point → the value at the use is the address constant → cse could still fold the plus (the reg_equiv for the load of `it` after the 1st store is the constant address...). Hmm, but with a later set, the pseudo is not reg_equiv overall → the load must be materialized in a reg → the pseudo holds the address in a reg → `addiu a0, v1, 25996`.

Wait, but does the later dead store prevent the reg_equiv? In reload.c, `reg_equiv_contain_p (reg, mode, &value)` looks up reg_equiv[reg] — a list of (pseudo, equiv_expr). It's populated by cse when a set's value is a constant... The list can have multiple entries with different values, and `reg_equiv_contain_p` requires that ALL entries have the same value? Let me look at the source: in reload.c:

```c
int
reg_equiv_contain_p (reg, mode, value)
{
  ...
  for (p = reg_equiv[reg]; p; p = p->next_equiv)
    if (GET_MODE(p->equiv_expr) == mode)
      {
        if (value)
          *value = p->equiv_expr;
        return 1;
      }
  return 0;
}
```
Hmm, it returns the FIRST match. So with 2 conflicting entries, it might return the wrong one. But also, cse adds to reg_equiv only when the pseudo is set once? In cse.c:

```c
      /* If this insn is a set of a pseudo to a constant, ... */
      if (GET_CODE (x) == SET && ... )
```
There's a check: "if (REGNO (SET_DEST (x)) is a pseudo and the value is a constant) and the pseudo has only one set" — cse has `record_equiv`?

In cse.c, the function `record_jump_equiv` and:
```c
/* Record that X is the value of REG ... */
static void
record_equiv (dest, equiv)
```
which is called when a pseudo is set to a constant, and there's a check `if (reg_equiv_contain_p (dest, GET_MODE (dest), NULL))` → skip (don't add a conflicting entry)? I recall:

```c
static void
record_equiv (dest, equiv)
     rtx dest, equiv;
{
  rtx gen;
  int i;
  ...
  /* If we have a REG_EQUIV, we must not add another one */
```
Let me actually read cse.c's record_equiv.

Let me grep.
