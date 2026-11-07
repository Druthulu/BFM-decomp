---
ts: 2026-11-06T16:49:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DyvVBwM75HaAb0zZYSkC
---
Here cse2 shows: insn 153 sets pseudo 86 = symbol_ref D_8018E2DC, then uses pseudo 86 for a1. So cse kept the symbol_ref in a pseudo (reg/v:SI 86). That pseudo is used in multiple places across calls → global alloc gives it a callee-saved register (s2). The launder forced a fresh pseudo each time (asm clobbers).

In the target, each call materializes the symbol fresh. So the original's RTL had separate constants per call.

What makes cse create a shared pseudo for the constant? In cse.c, when it sees a constant that's "expensive", it may allocate a pseudo and record it in the constant table (see `cse_insn` handling of CONST / SYMBOL_REF: "if (const_cost > 2, put in register"). There's a known GCC behavior: cse puts a symbol address into a register once and reuses it if used more than once (to save lui/addiu pairs). Actually the code: in cse.c, `record_reg_vals` / `hash_rtx`. Let me look for "cost" and constant.

If cse decides the constant is "expensive" (2 insns) it can put it in a register. The number of uses matters. With the asm, the constant at each site is a separate value.

Real-C trick to stop cse from merging: make each address expression *not identical*. The identity address spellings don't count as a crack — but maybe the original used genuinely different expressions, e.g. `D_8018E2DC` vs `D_8018E2DC + 0` — no, identity.

Hmm wait, what if the original source is a LOOP over an array of these constants, and the target's unrolled code comes from... no, GCC 2.7.2 doesn't unroll.

Alternatively, maybe the original passes `&D_8018E2DC[0]` and `D_8018E2E8` etc., and cse still merges identical ones.

Let me reconsider: maybe the key is that in the target, the calls' arguments come from a *different* source structure: the m values are loaded from a global pointer array! Look: target emits `lui a1,0; addiu a1,a1,0` — that's the address of D_8018E2DC, not a load. So no.

Hmm, let me look at the cse dump for the ORIG (with asm) to see the difference. In orig, each laundered call has `(reg/v:SI m)` set from the symbol and the asm clobbers it, so cse can't propagate across. The non-laundered ones (group B etc.) still share pseudos? In the target, ALL calls materialize fresh. So even the non-laundered group B calls materialize fresh — because... group B's m = D_8018E2DC etc. are the same constants as group A. If cse merged them, they'd share a pseudo. Target doesn't. So in target's source, even group B's constants were distinct from group A's.

Wait, maybe the target's source used *different symbol spellings* for the same address: e.g. group A used `D_8018E2DC` and group B used `D_8018E2DC`... same. Unless the symbols are actually different arrays! Let me check: group A m = D_8018E2DC, E2E8, E2F4. Group B m = D_8018E2DC, E2E8, E2F4. Same symbols. And target materializes each fresh.

So how did the original avoid cse merging? Maybe the original source had a *variable* assigned before each call, e.g.:

```
u8 *src;
...
src = D_8018E2DC;
func_8017D8A4(..., src, src + 0x30, 0, 1);
...
src = D_8018E2DC;
func_8017D8A4(..., src, src + 0x30, 0, 1);
```
cse would still merge the constants (they're the same value).

Unless the variable is `volatile`? A volatile pointer load would emit a load. No.

Hmm, wait. Let me reconsider the target: does it really materialize the address fresh, or is it `lui a1,0` for a different reason? 
```
7180: lui a1,0  (R_MIPS_HI16 D_8018E2DC)
7184: addiu a1,a1,0 (R_MIPS_LO16 D_8018E2DC)
7188: addiu a2,a1,48
```
Yes, fresh.

So in the target's RTL each of these is a separate constant expression not merged by cse. Since the symbols repeat, cse must not have merged them. Why? Because cse only keeps a constant in a register if it's "cheap enough" or if... Let me read cse.c's constant handling to understand when it makes a pseudo.

Actually — maybe the difference is the ORDER: in target, D_8018E2DC appears in group A (call 1) and group B (call 4). If cse's constant table expires entries... cse processes basic blocks and invalidates the table at calls? The constant table isn't invalidated by calls (constants don't change). Hmm.

Let me look at cse.c's handling of constants: search for "CONST" and "expense".
