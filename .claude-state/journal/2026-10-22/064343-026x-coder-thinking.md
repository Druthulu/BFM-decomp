---
ts: 2026-10-22T12:43:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hDUYcUuwuyp35Uxw2NFP
---
Now the target:

```
lui v1, %hi(D_80120194)
addiu v1, v1, %lo(D_80120194)
j 4190        (delay slot: addiu a0, v1, 0x658C)
...
4190: lui v1, %hi(D_801202A0)
      addiu v1, v1, %lo(D_801202A0)
      beq v1, a0, 41bc
      move v0, zero   (delay slot)
41a0: lhu v0, 0(v1)
      nop
41a8: beqz v0, 4188
      nop
41b0: addiu v1, v1, 0x10C
41b4: bne v1, a0, 41a0
      move v0, zero (delay slot)
```

Interesting: at 418c there's `move v0,v1` — the copy: label, `return it` → v0 = v1 (it). But wait, the "copy:" block returns `it` and v0 = v1 = it at that point. Hmm but v1 has been incremented by 0x10C in the loop; at 4188 the jump comes from 41a8's beqz (i.e. *it == 0), and 418c is `move v0,v1` (the copy block), and at 4188 `j 41bc` with delay `addiu a0,v1,25996`?? Wait no.

Order of blocks: 4178-4184 is the entry: lui/addiu v1 = D_80120194; j 4190 with delay slot addiu a0,v1,0x658C. Then 4188: j 41bc with delay slot 418c: move v0,v1 → so the "copy" block is at 4188-418c (returns it). Then 4190 = "test" block.

So:
- entry: v1 = &D_80120194; a0 = v1 + 0x658C (p); jump to test.
- copy: v0 = v1 (it); j 41bc (return it).
- test: v1 = &D_801202A0; if (v1 == a0) goto zero; body...
- body: v0 = *(u16*)v1; if (v0 == 0) goto copy; v1 += 0x10C; if (v1 != a0) goto body.
- zero: return 0.

So `it` (v1) is a callee-saved-ish register reused: v1 is used for both D_80120194 and D_801202A0 addresses and the loop counter. Note the loop uses v1 for the pointer and v0 for the loaded u16.

Now the source:
```c
it = (s32)D_80120194;
asm launder(it);
p = it + 0x658C;
goto test;
copy: return it;
test: it = (s32)D_801202A0; asm launder(it); if (it == p) goto zero;
body: if (*(u16*)it == 0) goto copy; it += 0x10C; if (it != p) goto body;
zero: return 0;
```

Without the launder, gcc computed: lui a0, D_80120194; addiu a0; (then addiu a0,a0,0x658C folded) — i.e. it folded p = &D_80120194 + 0x658C into one address, and used a0 for the address, then compared `it == p` as beq a0,v1.

The target keeps the base address in v1 and computes p = v1 + 0x658C. The launder prevents the "copy" from being folded: the asm creates a new pseudo for it, so `it` = copy of the address pseudo; then p = it + 0x658C can't fold into the address materialization because `it` is a separate reg.

Wait — but in the target, v1 IS the address of D_80120194 at entry, and `it` in the source after the launder is a copy. So the copy pseudo got v1 and the original address pseudo got... hmm, both are v1? The launder's output "=r"(it) with input "0"(it) — GCC creates a copy of the input reg into the output reg, both "it". So actually in the RTL: the address is materialized into reg X (from `it = (s32)D_80120194`), then the asm copies X into reg Y (it). Then p = Y + 0x658C. Then copy: return it → v0 = Y.

In the target: v1 = address (that's X or Y?), p = v1+0x658C = a0, v0 = v1 at copy. So Y = v1 and X was folded into Y (the move was coalesced). So the launder's real effect was to keep the address in a register instead of folding the +0x658C into the address materialization, i.e., to prevent GCC from computing &D_80120194+0x658C as a single constant address.

Without the launder, GCC computes the constant address &D_80120194 + 0x658C = D_80126720? Wait, D_80120194 + 0x658C = 0x80126720. Hmm but the target's p = v1 + 0x658C (register+offset) because v1 = 0x80120194. So GCC must not fold the constant.

How to prevent the folding in plain C? The value 0x658C is a runtime-ish offset. Options:
- `p = it + 0x658C;` where `it` is not a constant expression. GCC folds because it knows it = (s32)D_80120194.
- Make the address non-constant: e.g. `it = (s32)D_80120194;` where D_80120194 is `extern u8[]` — the address is a link-time constant, so GCC knows it.

Trick: take the address through a pointer that GCC can't see through:
```c
u8 *base = D_80120194;  /* still constant */
```
Hmm.

Another: use a `static` variable initialized with the address? `static u8 *base = D_80120194;` — GCC at -O2 would still constant-propagate it (static const-like init). Actually with `-O2` and a static pointer initialized to a link-time constant, GCC will fold it.

What about `it = (s32)(size_t)D_80120194;`? Same.

What about making the address come through a function call or a volatile? volatile is a lever (new lever, not allowed).

Hmm. But there's another approach: the fold happened for `p` — GCC turned `it + 0x658C` into an address constant. But actually did it? Mine: `lui a0; addiu a0, 0` then `addiu a0,a0,25996`? Let me re-read the diff:

```
replace mine[0:2] target[0:2]
  0  lui a0,0x0 | lui v1,0x0
  1  addiu a0,a0,25996 | addiu v1,v1,0
```
Mine[0]=lui a0, mine[1]=addiu a0,a0,25996. So mine folded the address: lui a0, hi(D_80120194+0x658C); addiu a0, a0, 25996 (reloc HI16/LO16 with addend 0x658C). Target: lui v1, hi(D_80120194); addiu v1, v1, lo; and separately addiu a0, v1, 25996.

And mine[3] = nop where target[3] = addiu a0,v1,25996 (in the delay slot of the j).

So the difference is exactly the folding of the constant address + the register choice.

So the key: GCC must not know that `it` is the constant address D_80120194 when computing `it + 0x658C`.

Real C move ideas:
1. Reorder: compute p differently, e.g. `p = it; p += 0x658C;` — GCC will still fold (it knows it).
2. Make the base come from a different expression that GCC treats as non-constant: e.g. `it = (s32)(u8 *)D_80120194;` no.
3. Use the address of an array element? `&D_80120194[0]` same.
4. Store the address in a global variable that is written elsewhere? e.g. `extern u8 *g; it = (s32)g;` — but we can't add globals to the header (signature/decl change outside body not allowed; and the header is included in 141 TUs, adding an extern decl might be OK? "no signature or decl change outside the body" — adding an extern declaration inside the body is inside the body. But the global must exist somewhere — it's in another TU. We can't rely on undefined symbols (link error).

Hmm! What about using an existing global pointer? Probably not.

5. Trick GCC with a union or a struct member: `it = (s32)&((struct {u8 x[1];}*)D_80120194)->x[0];` — still constant.

The classic decomp trick to hide a constant address from GCC: cast through an integer type that is "unknown"? GCC knows the value regardless.

Hmm, but wait — maybe the fold happens because GCC's cse/constant-propagation knows `it` = the constant. If we instead write:

```c
it = (s32)D_80120194;
```
and then use `it` in a way that forces a register before the add... e.g. `if (it == 0) return 0;`? That's an extra compare — changes code.

Alternatively: could the difference be handled by changing WHICH value is folded? What if instead of `p = it + 0x658C`, we compute `p = (s32)D_801202A0 + 0x658C`? Let's see: the target's p = &D_80120194 + 0x658C = 0x80126720. And D_801202A0 + 0x658C = 0x8012682C. Not the same. But hmm — maybe the original source was:

```c
it = (s32)D_80120194;   // v1
p = it + 0x658C;        // a0 = v1 + 0x658C
```
The compare `if (it == p)` where it = &D_801202A0 vs p = 0x80126720.

Alternatively the original might have been:
```c
p = (s32)D_80120194 + 0x658C;  /* constant folded to 0x80126720 */
```
but the target shows addiu a0,v1,25996 — not folded.

So GCC must not fold. Real C ways to defeat constant folding of an address + offset:
- The address is loaded from memory (a pointer variable in memory). Not available.

Hmm, what about the possibility that the fold is a "cse" artifact (find_best_addr / canonicalization) rather than constant propagation? moves.md mentions "cse-const-addr — cse folds or substitutes a constant/absolute address the target keeps base-relative".

In GCC 2.7.2, cse.c has `find_best_addr` which can transform `x + const` into the base reg... The target keeps base-relative (addiu a0, v1, 25996). So we want cse to NOT substitute.

Since `it` after the launder is a copy (a distinct pseudo), cse sees `it (copy) = X` where X is the address reg; then `p = it + 0x658C` — cse's find_best_addr would find that `it` is a copy of the address constant and could still fold... but the observed target shows it doesn't. So the copy pseudo blocked it.

What real C creates a copy pseudo of a value in GCC 2.7.2?
- A cast that requires a conversion? e.g. `it = (s32)(long)D_80120194;` no.
- Assignment to a variable of different type? e.g. `it = (s32)(u32)D_80120194;` no.
- A conditional expression: `it = cond ? D_80120194 : D_80120194;`
- A function call result?

Hmm! What about the trick used in earlier moves: `u16`/`s16` casts to escape cse equivalence (HImode copies). E.g. `it = (s32)(s16)...` no, that truncates.

What about making the address come from a `unsigned long` arithmetic that GCC treats as non-constant? E.g. `it = (s32)((u32)D_80120194 + 0);` — GCC folds.

Another classic: use the address of a *label*? no.

What about: `it = (s32)D_80120194;` → `it = (s32)(void *)D_80120194;`? no change.

OK, different approach: maybe the target's `v1` is NOT the address of D_80120194 as a constant but rather loaded from... no, it's lui/addiu with HI16/LO16 relocs to D_80120194.

Alternative idea: what if the ordering in the source is different such that GCC computes `p` from a variable that isn't known constant? For example:

```c
s32 p;
s32 it;
it = (s32)D_80120194;
p = it + 0x658C;
```
What if instead:
```c
p = (s32)D_80120194 + 0x658C;   /* folded to constant address */
```
and separately it = D_80120194 → separate materialization. Target has ONE materialization (v1) shared. So the target really has the base in a reg and computes p = base + 0x658C.

Alternatively, maybe the source was:
```c
it = (s32)D_80120194;
p = it;
p += 0x658C;
```
Still folded.

Hmm, what if `it` is a *pointer* type and p is computed as pointer arithmetic with a non-constant index? Like `p = &D_80120194[0x658C/4]`? no.

Think about the launder's role differently: `__asm__ __volatile__("" : "=r"(it) : "0"(it));`. GCC 2.7.2 with this: it creates a REG output and a REG input tied to the same variable. The generated RTL: `set it = X` where X is the address pseudo. Because the output is a "=r" output and the input "0"(it) is a reg, the value gets copied. But GCC's copy propagation usually eliminates such copies... it didn't, presumably because the asm is volatile and the copy is a "pseudo".

Hmm, wait. Actually GCC's asm with "=r" output and "0" input: RTL is (set (reg it) (reg it))? For the same variable used as both input and output with matching constraint, GCC creates a COPY: `set it = it` essentially. That copy gives it a distinct pseudo, and the register allocator then puts the address in v1 and the copy... but the target shows only ONE register (v1) for the address, no copy. So the copy was coalesced but the pseudo split persisted for the address constant handling.

OK. Since we can't use asm, maybe there's a C construct that gives the same effect. What about a "volatile" qualified... no, new lever.

Wait — reconsider. Maybe a different real-C formulation produces the exact target without needing to defeat folding: what if `p` is not `it + 0x658C` but rather the source is:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
What if instead we write:
```c
it = (s32)D_80120194;
p = (s32)((u8 *)it + 0x658C);
```
No.

Hmm, think about what other real-C move could keep the base in a register: make `it` a variable that GCC treats as address-taken or volatile...

Alternative: maybe the trick is to *not* have the address be a compile-time constant in the source, e.g. by using the *difference* between the two symbols? Like the original might have been:

```c
p = (s32)D_801202A0 - 0xC4;  /* == D_80120194 + 0x658C? */
```
D_801202A0 - D_80120194 = 0x10C. So D_80120194 + 0x658C = D_801202A0 + 0x6480. Interesting! And in func_8012C750 we see `p = base + 0x6480;` where base = D_80120194! And the first branch checks `if (p != base)` — where p = base + 0x6480?? Hmm no: in C750, base = D_80120194, p = base + 0x6480, and the loop does p -= 0x10C until p == base. So the end pointer is base = D_80120194 and p starts at base+0x6480.

In C2D0: p = it + 0x658C where it = D_80120194 → p = D_80126720, and the loop `it` starts at D_801202A0 and increments by 0x10C until it == p. Hmm, so the "end" is D_80120194+0x658C.

Whatever. The point is the constant folding.

Let me think about how GCC 2.7.2 decides to fold `X + 0x658C` where X = the address constant. In cse.c, `find_best_addr` (called from cse's `cse_addr`/`record_jump_equiv`?) — the moves.md entry says "cse folds or substitutes a constant/absolute address the target keeps base-relative".

So cse substitutes the constant address. To defeat: make the base value a *pseudo* that isn't a constant.

What if we get the address into a variable via an arithmetic op that GCC can't fold, e.g.:
```c
it = (s32)D_80120194;
```
The `extern u8 D_80120194[];` — a global array. GCC's RTL for its address is a symbol ref (CONST) → folded.

Idea: take the address of a *local* variable and add the difference? no.

Idea: use the address of the array's *second* element and subtract? `it = (s32)&D_80120194[1] - 4;` — GCC folds to the same constant (constant folding in the front end). Yeah.

Idea: use `__builtin`? no.

Idea: use a pointer-to-pointer indirection through an existing global of pointer type? We'd need an existing global pointer whose value is D_80120194 — unlikely.

Hmm, what about using the `&D_80120194` of a *different type* so that GCC creates an address with a different section/alignment and the addiu can't fold? Folding happens on the constant value, independent of type.

Idea: use a struct member of a global object: `it = (s32)&((SomeStruct*)D_80120194)->field;` — the address is base+offset, still a constant, but cse's find_best_addr might behave differently! That's interesting: the "cse-const-addr" wall mentions "find_best_addr rematerialises the +4 address". In cse, find_best_addr looks for a base register whose value is the constant minus the offset. Hmm.

Let me step back and consider: what does the REAL original source look like? This is a decomp project; the target was compiled from some original C. The original probably was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
}
```
and GCC (2.7.2) generated this? But our GCC folds it. Unless the original had something like:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
where D_80120194 was declared differently, e.g. `extern u32 D_80120194;` (not an array)? The address of a scalar global is still constant.

Hmm, but wait: maybe in the original, D_80120194 was a `volatile` or the file had different declarations. Actually! What if the original source declared these as `extern u8 D_80120194[];` but the pointer arithmetic was done as a *pointer* type: `p = (s32)(&D_80120194[0] + 0x658C)`. Same.

Let me look at what the actual difference in the *target* tells us: `lui v1, hi(D_80120194); addiu v1,v1,lo(D_80120194)`. The HI16/LO16 relocs mean the address is materialized as a symbol reference, and `addiu a0, v1, 25996` is a register+offset. So the base IS materialized as a symbol address (not folded with the +0x658C).

So in the original compile, GCC had a pseudo holding the symbol address, and p = pseudo + 0x658C stayed as an addiu.

When does GCC keep a symbol address in a pseudo rather than folding? When the address is loaded as a "symbolic constant" that it can't fold into the use. E.g., if the pseudo is used in multiple places with different offsets, or if the pseudo is loop-invariant and gets a register.

In our compile, GCC folded because cse/constant-prop replaced the use of `it` (a constant) with the constant expression.

What if `it` is used in a way that forces it into a register? Like `it` is modified in the loop (it += 0x10C). But the first `it` value (D_80120194) is separate from the loop's it...

Hmm, hold on! Look again at the target: v1 is used for BOTH D_80120194 (at 4178) and D_801202A0 (at 4190) and the loop counter. The pseudo for `it` at entry = &D_80120194 and later `it` = &D_801202A0. In the source, `it` is assigned twice: first D_80120194, then D_801202A0. So the source's `it` variable is a single variable with 2 sets. GCC would then create 2 pseudos (one per set) — and register allocation gives them the same reg v1.

The first set `it = (s32)D_80120194` → pseudo with the constant address. Its uses: `p = it + 0x658C` and `return it` (at copy). GCC folds the first use into a constant address (lui/addiu with addend) and for the second use (return it) it must keep a register → so GCC materializes the address in a register anyway.

In the target, the address materialization (lui v1; addiu v1) is in v1 and p = v1 + 0x658C. In mine, the address materialization was folded into the p computation (lui a0 with addend 0x658C) and the "return it" needed a separate reg — but there's only ONE materialization in mine too? Let's dump my candidate to see.

Let me dump the candidate object. I need --keep. Let me write a script that scores with --keep and dumps the candidate.

Actually simpler: use delever_search --try with --keep via a modified helper. Let me write my own sc script that prints the candidate disassembly.

Let me create a "dt2.sh" that runs delever_search --try --keep and then objdumps the candidate object.

Actually the --try prints "  --keep: candidate object <path>". Then I can objdump that path. Let me write a wrapper script `cand.sh <itemdir> <bodyfile>` that runs --try --keep, greps the object path, and objdumps the function.

Let me do that.
