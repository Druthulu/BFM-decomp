---
ts: 2026-10-22T12:51:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_BfvnKcxrlvXapG673FsQ
---
Same as w1: the address is folded into a0 with the addend, and the delay slot is nop.

The target: base in v1 (materialized plainly), p = v1 + 0x658C in a0 in the delay slot.

So I need the base to be a REG.

Since the dead store doesn't help, the fold happens elsewhere. Let me figure out WHERE. Let me use the cc1 dump to see the RTL. tools/cc1_dumps_tu.sh — let me check its usage.

Actually, let me think about it from the "reload" angle: reload is what turns the frame-slot load into a pseudo. In GCC 2.7, local variables ARE in memory. So `it = (s32)D_80120194` → store the constant to the slot; `p = it + 0x658C` → load the slot into a pseudo + add const.

Hmm wait, but GCC 2.7's front end for a local variable that's never address-taken: I believe GCC 2.x does keep locals in memory. Then the optimizer's `cse` pass eliminates the store/load pair (cse handles MEMs) → the load becomes a pseudo set to the constant → then reload's reg_equiv → the pseudo is rematerialized as a constant → the plus becomes (plus symbol_ref const) → the mips backend folds the address → lui/addiu with addend.

Now, the ASM: `__asm__("" : "=r"(it) : "0"(it))` — here `it` is used as an asm OUTPUT, so the front end must put `it` in a REGISTER (the asm output). GCC's expand for an asm with a register output on a local variable: the variable's MEM is loaded into a reg (pseudo), the asm writes to the pseudo, and the pseudo is stored back to the slot? Actually for `=r` outputs, GCC expands the asm with the output being a pseudo, and if the variable is in memory, it emits the asm with a temp reg and then stores it back to the slot. But then the *load* of `it` before the asm would be folded with the constant by cse → the pseudo = constant → then the asm's input "0"(it) = the same reg...

Hmm, but the asm forces the value into a REG: the pseudo's value is the constant symbol_ref, and the asm input operand is that pseudo. In reload, the pseudo (with a constant value) — hmm, for an asm input, reload can't rematerialize a constant into a register? Actually reload CAN rematerialize constants into registers for asm inputs (it materializes the constant into a reg: `reload_reg` with a constant → it emits the constant into the reg). Hmm, but for a symbol_ref address constant, materializing means lui/addiu into the reg → that's the `lui v1; addiu v1` we see!

So: the asm input forces the address into a real register (v1), and then `p = it + 0x658C` uses that reg → addiu a0, v1, 25996.

So the crux: GCC will keep a constant in a register only if the context demands a register (asm operand) or if the reg is needed multiple times.

So: to reproduce without asm, we need the address in a register. The context that demands a register: a MEM with a *variable* offset? No... a MEM with a constant offset also uses a reg for the base, but the base of a MEM can be a constant address (folded).

Hmm! So how did the ORIGINAL (the game's source) get this? The original compiler was gcc 2.7.2 for PSX with the same flags presumably. The original source must have had the address in a register for another reason.

**IDEA**: What if the original source's `it` was a *pointer to a struct* and the code did something like `p = (s32)(it + 0x658C)` where `it` is `u8 *`? Then `it + 0x658C` is pointer arithmetic → the front end's plus_expansion: base = a variable (MEM load) → reg + const → same.

**IDEA 2**: What if the original source had the base address used as the base of a MEM somewhere (e.g. `*(u16*)it`)? In C2D0 the base is NOT dereferenced.

Hmm, but hold on! What if the original source was structured as a LOOP over the base with an index, and the decompiler's version differs? The target code is what it is; we must reproduce it. The target has: base in v1 (used once for p). GCC's choice to keep it in a reg despite a single use... 

With GCC's global-alloc, if the pseudo were a REG with a single use, it might still get a register (the cost of a lui/addiu pair vs. folding). Actually here's the thing: the *fold* (relocating the constant into the use) happens in the reload pass (rematerialization) or in cse. If the fold happens, we get the "lui a0/addiu a0,addend" form. The target has the unfolded form.

So which pass folds? If it's reload's rematerialization, then giving the pseudo a second set might prevent it... but my dead-reset test didn't help. Hmm, maybe because cse already folded it (cse runs before reload).

Let me look at cse.c for the code that replaces a register with its constant value. In cse.c, `cse_basic_block` has:

```c
	  /* If we have a constant, and the register is not modified... */
```
Let me grep for "equiv_constant" (declared at line 653).

`equiv_constant (x)`: "If X is a constant, return the constant; if X is a reg equivalent to a constant, return it." That's used in cse's `cse_basic_block` to replace operands!

Let me look at where equiv_constant is used.
