---
ts: 2026-10-22T12:58:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_qG1rZMiBhtEGemlXry8E
---
As expected: without the launder, GCC rematerializes the address for EVERY load (lui + lw each time) — 6 extra instructions (6 lui pairs).

The target (with the launder) keeps the address in $5 (the pinned `src`) and does `lw t0, 0($5)` etc.

So for item 1, the launder's purpose: keep `src` (the address) in ONE register instead of rematerializing. The pin `register int *src __asm__("$5")` alone is NOT enough (because the address is a constant → GCC rematerializes it at each use; the pin only says WHICH register, but GCC still rematerializes the constant into $5 each time!).

Interesting: so with the pin but no launder, GCC rematerializes. With the launder, the value is opaque → kept in $5.

Hmm, so the fix: make the address's value opaque... same problem as item 2.

BUT: here the address is used 8 times! So if the value were opaque, GCC would keep it in one register. How can we make it opaque in plain C?

Since the address is used 8 times, maybe there's another way: **use the address as a MEM base in a way that forces a register** — the second-symbol case in C2D0 stayed in a register when used as a MEM base! Here `src[0]`, `src[1]`, ... are MEM accesses with (reg src) + offset. The MEM address (reg src + const offset) → if GCC substituted the constant, the MEM would be (plus (symbol_ref) const) → a constant address → the backend emits lui+lw per access (that's what we see).

So the MEM use does NOT force a register. Hmm! But in C2D0, D_801202A0's MEM use DID keep it in a register... because it also had a compare use.

OK so the rule stands: a COMPARE use forces the value into a register.

**SO THE TRICK FOR ITEM 1: make the address participate in a compare!**

Hmm, in item 1, the source is:
```c
src = (int *)&D_800AE620;
t0 = src[0]; t1 = src[1]; t2 = src[2]; m[0] = t0; ...
```
Semantically, the code copies 8 ints from D_800AE620 into the local array m. What if the original source was:

```c
int *src = (int *)&D_800AE620;
```
Hmm.

What if we write the copy as a LOOP?
```c
for (i = 0; i < 8; i++) m[i] = src[i];
```
That would change the code completely (the target has the unrolled copy) ✗.

Hmm, but WAIT: what if the original source was:

```c
    src = (int *)&D_800AE620;
    t0 = src[0]; ...
```
and the game's compiler kept the address in a register because...

Hmm, in the target, the address is in $5 (the pinned reg) — a PINNED register! The decompiler added the pin `register int *src __asm__("$5")`. Was there a pin in the ORIGINAL? The original source couldn't have had `register __asm__` (that's a GCC extension the decompiler uses). Hmm, but the original could have had a plain `register int *src;` — but the game source is unlikely to use `register` for that.

So in the original, the address was in SOME register (the target's $5). Hmm, and the original had 8 uses → GCC would keep it in a register if the value were opaque...

Hmm! But in the original, the value was NOT opaque (it was a constant) → GCC would rematerialize → 8 lui+lw pairs. But the target has ONE materialization!

**=> THE ORIGINAL'S ADDRESS VALUE WAS NOT A CONSTANT!** ⟹ the original got the address from somewhere non-constant!

Hmm!! But the reloc says HI16/LO16 D_800AE620 — that's a constant address materialization.

Hmm, but that's exactly what "rematerialization" looks like: `lui $5, %hi(D_800AE620); addiu $5, $5, %lo(D_800AE620)` — ONE pair. So the original materialized it ONCE and used the register 8 times.

So in the original, GCC decided to keep the address in a register rather than rematerializing 8 times. GCC's reload decides this by cost: rematerializing a constant address = 2 instructions per use (lui+addiu) vs. keeping it in a reg = 2 instructions + a register. With 8 uses, keeping it is cheaper ✓. But in OUR compile, GCC rematerialized! Why?

Because the pseudo was a HARD-REG pseudo ($5)! Hmm, no — GCC's reload for a hard-reg pseudo... hmm, in our compile the address was rematerialized into v0/a0/etc. for each load — it wasn't even kept in $5! So the pin didn't even hold?! Interesting: `register int *src __asm__("$5")` — the pin says src is in $5. But the compiled code doesn't use $5 at all! So GCC ignored the pin (because the variable's value was a constant → rematerialized → the pseudo was never allocated).

Hmm, interesting: with a hard-reg pseudo, GCC would normally do `lui $5; addiu $5` once and then `lw $v0, 0($5)`. But GCC's reload decided to rematerialize the constant at each use instead (since the "register" is a hard reg, rematerialization is allowed).

Hmm, so with the launder, the value is opaque → the pseudo must live in $5 → one materialization.

**SO FOR ITEM 1: without the launder, GCC rematerializes; we need to make the value opaque OR make GCC keep it in $5.**

Hmm! What if the value is used in a COMPARE? E.g., adding a compare of `src` with something... but that's a semantic change.

Hmm, hold on! What about this: the COPY is of 8 ints. What if the original source was:

```c
    src = (int *)&D_800AE620;
    m[0] = src[0]; m[1] = src[1]; ... 
```
vs
```c
    src = (int *)&D_800AE620;
    t0 = src[0]; t1 = src[1]; ...
```
The current source uses temps t0,t1,t2 and assigns m[0]=t0 etc. The temps might be unnecessary: `m[0] = src[0];` — would that change the code? The temps create extra copies (the target has `sw v0,16(sp)` etc. — the loads go to temps then are stored). Hmm, the target's code: `lw v0,0($5); sw v0,16(sp)` — so the load's result goes directly to the stack slot. The temps t0/t1/t2 in the source cause the values to be loaded into temps and then stored — same instructions.

OK, so what C spelling would make GCC keep the address in a register?

**IDEA: make the address the base of a MEM with a VARIABLE offset!** E.g. `m[i] = src[i]` — a loop with a variable index → the address (reg src + reg i) → the base MUST be in a register ✓✓✓! But a loop changes the code shape ✗.

Hmm! But hold on: what about a *partially* unrolled form? The target has 8 explicit loads with constant offsets.

**IDEA: what if the source uses a pointer arithmetic with a variable index ONCE, in a way that doesn't change the code?** E.g.:

```c
    src = (int *)&D_800AE620;
    t0 = src[0]; ...
```
Hmm.

What if we add a dead expression like `if (src == src) {}`? Folded ✗.

Hmm, what about the classic trick: **take the address of the pointer variable** (`&src`) — that forces the pointer to be in MEMORY ✗ (extra store/load).

OK, so how did the ORIGINAL keep the address in one register? GCC's reload would keep a pseudo with 8 uses in a register if the value were... hmm, wait. Actually, let me reconsider: maybe in the original, the address WAS rematerialized but the *pseudo* was a hard-reg pseudo ($5)!

Hmm, and in OUR compile (no launder), the pin didn't take effect because the value was a constant → GCC rematerialized it into whatever reg each load needed.

Hmm! So maybe the fix for item 1 is: keep the pin AND make the value opaque. But the pin alone doesn't work.

Hmm, hmm. But hold on: what if the ORIGINAL source had NO pin, and the address was in $5 because of the register allocator? Then the original's value must have been opaque (or GCC's reload chose to keep it).

**WHY WOULD GCC KEEP A CONSTANT IN A REGISTER?** In reload.c, when a pseudo's value is a constant, GCC can rematerialize it. The decision: `reload_reg` → "if the value is a constant and the register is needed only once, rematerialize; else keep". Actually reload's decision is in `reload.c`'s `reload_reg`:

```c
	  /* If we are loading a constant and the mode is not ... */
```
Hmm, and there's `reg_equiv` handling: `if (reg_equiv_contain_p (reg, mode, &value))` → then reload can either rematerialize the constant into the register or substitute.

The relevant cost model: reload's `reload_reg` → for a "rematerializable" value, the cost of rematerializing is the insn cost; the decision is in `reload.c`'s `reload_reg`:
```c
      /* If we are reusing a reload, ... */
```
Hmm, and there's the "reload_cse" pass.

The key knob: `reload_reg` decides based on `reg_equiv_contain_p` and the number of references (`reg_invalidated`?). In GCC's reload.c, there's a heuristic: "if the value is a constant and it's used more than once, keep it in a register" — I recall `reload.c`'s `reload_reg` has:

```c
	  /* If this is a constant, and we are not able to use it directly, ... */
	  if (GET_CODE (value) == CONST_INT && ...)
```
and in `reload.c` there's the function `reload_reg` with the logic:
```c
      /* ... If the value is a constant, we can rematerialize it. 
	 But if the register is used many times, it may be better to
	 keep the value in the register. */
```
Specifically, GCC 2.x's reload.c has:

```c
  /* If we have a register that is used only once, and the value is a
     constant, rematerialize it. ... */
```
I recall `reload.c`'s `reload_reg`:
```c
	  if (reg_equiv_contain_p (reg, GET_MODE (reg), &value)
	      && GET_CODE (value) == CONST_INT
	      && ! (GET_MODE (reg) == QI && ...))
```
Hmm.

I recall the actual mechanism: **`reload_cse`** and the `reg_equiv` list, plus `reload_reg`'s use of `reg_reload_...`. And the "cost" of rematerializing a CONSTANT vs keeping it in a register: in reload.c:

```c
/* Reload a register that contains a constant... */
static int
reload_reg (...)
{
  ...
  /* If the value is a constant, we can just set the register to it... */
```

OK, I really should stop theorizing and EXPERIMENT. The empirical question for item 1: **what C spelling makes GCC keep the address in ONE register?**

Experiment ideas for item 1:
(a) Use a loop? no.
(b) Use `m[i] = src[i]` for the copy but with the loop unrolled manually? The offsets are constant.
(c) **Use a POINTER VARIABLE for the destination too?** no.
(d) **Assign the address to a variable that is used in a compare**: e.g., `if (src == (int *)&D_800AE620) { ... }` — folded ✗.
(e) **Make `src` a `u8 *` and index with byte offsets**: `t0 = *(int *)(src + 0)` — hmm! With a byte pointer and constant offsets, the MEM address = (reg src + 0), (reg src + 4)... → the base must be in a register! Because the offsets are different per access, GCC can't fold them into one constant address... hmm, actually it could: (plus (symbol_ref D_800AE620) (const 4)) → a constant address → rematerialized ✗.

Hmm, but wait: our current compile DID rematerialize. So GCC's fold handles it.

(f) What if the source uses the address with a variable offset that's constant-folded at the RTL level but not the front end? E.g. `for (i=0;i<8;i++) m[i]=src[i];` → a loop ✗ (different code).

Hmm, what about the possibility that the ORIGINAL source was:

```c
    src = (int *)&D_800AE620;
    m[0] = src[0]; m[1] = src[1]; m[2] = src[2]; m[3] = src[3];
    m[4] = src[4]; m[5] = src[5]; m[6] = src[6]; m[7] = src[7];
```
and GCC kept the address in a register because of the 8 uses — but our compile rematerialized. So something about the ORIGINAL made GCC keep it.

**AH WAIT!!! WHAT IF THE ORIGINAL USED A POINTER VARIABLE OF A DIFFERENT TYPE, e.g. `u8 *src` and `m` as u8[]?** Then `m[i] = src[i]` with byte copies → different code ✗.

**WHAT IF THE ORIGINAL'S COPY WAS DONE VIA A STRUCT ASSIGN?** e.g. `*(Mat32 *)m = *(Mat32 *)&D_800AE620;`? The target copies 8 ints (32 bytes) → a struct copy of 32 bytes might be done as 8 lw/sw pairs ✓✓✓!! And a struct copy's source address... hmm, the MEM would be (mem (symbol_ref D_800AE620)) → the backend would emit lui+lw per word? Hmm.

Hmm, GCC's struct copy: `*(struct A*)m = *(struct A*)&D_800AE620;` → the front end emits a block copy or individual moves. The address of the source is a constant → each MEM would be a constant address → rematerialized ✗ (probably).

OK, let me EXPERIMENT with item 1: I'll try a batch of spellings:
1. `m[0] = src[0];` etc. (no temps)
2. byte-pointer indexing
3. a struct copy
4. `src` used with a variable index in a dead way? no.
5. `int *d = src;` then `d[0]`... (same)

Hmm, hmm. But the KEY question for item 1: the target has the address in $5 (a callee-saved reg). Hmm, $5 = a0! (MIPS: $4=a0, $5=a1). Wait: the pin says `__asm__("$5")` = a1. Hmm, and the target's `lw v0,0(v1)`? Let me look at the target's disassembly for item 1 to see which register holds the address.

Let me dump the target for item 1.
