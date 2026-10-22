---
ts: 2026-10-22T12:51:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QwySFqCZ95hYf1EV2LXg
---
This is the classic "REG_EQUAL note" mechanism: when a pseudo is set once to a constant, cse adds a REG_EQUAL note on the insn, and the register allocator/reload uses that note to substitute the constant at the use. That's the fold.

So to defeat it, the pseudo must have more than one set (n_sets != 1) — but the pseudo here is the *load* pseudo (from the frame slot), not the variable.

Hmm, wait. Let me reconsider: in GCC 2.x, local variables live in memory. But hold on — is that true for gcc 2.7.2? Let me check `expand_start_function`/`start_function` in function.c: I recall "local variables" are allocated in the frame, and there's an optimization in `expand_end_function`... Actually no! I now recall clearly: GCC 2.x had a "pseudo variable" optimization: in `start_function`, local variables are allocated frame slots; but the front end's `expand_expr` for a VAR_DECL returns a MEM. Then `cse` eliminates the store/load pairs at the RTL level, creating pseudos.

So the sequence for `it = (s32)D_80120194; p = it + 0x658C;`:
RTL: (set (mem slot) (symbol_ref D_80120194)); (set p (plus (reg tmp) (const 25996))) where tmp = the load of the slot.

cse: the load (mem slot) is replaced by the value of the store → the load pseudo gets REG_EQUAL(symbol_ref) → then in the insn (plus tmp const), cse's `equiv_constant(tmp)` returns symbol_ref → the plus becomes (plus symbol_ref const) → folded to an address → the mips backend emits lui/addiu with the addend.

To defeat: the pseudo must not have a REG_EQUAL note → i.e. the load must not be cse-merged with a single preceding store, or the pseudo must have 2+ sets.

My dead-reset test (n2/n3) didn't help. Why? Because in n2 (store 0; store addr; load) — the load is after the addr store, so cse merges it with the addr store → REG_EQUAL(note) → still folded. The dead store BEFORE doesn't matter (cse looks at the last store).

In n3 (store addr; load; store 0) — the load is still merged with the addr store. The later dead store doesn't affect the load's REG_EQUAL.

So the dead store must be BETWEEN the store and the load? No... The load's value is the address regardless.

Hmm! So how can we prevent the load from being cse-merged with the address store? We need the load to NOT be a simple load of the slot, or the slot to be modified between the store and the load... but any modification changes the value.

Alternatively: prevent the *variable* from being in memory. How? By making it a `register` variable (register vars in GCC 2.x are allocated to a pseudo directly, not memory!). But "no register vars" per the constraints. Hmm, but the constraint says "no `register` vars, no `__asm__`" — in the context of "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". The `register int obj __asm__("$16")` pins are "register vars" and they're allowed to stay (they're existing pins). But adding a NEW `register` var (without an asm pin) is a new lever of kind "pin"? The pin kind is "register-asm/`__asm__` reg steer" per the brief: "no pin (register-asm/`__asm__` reg steer)". So a bare `register s32 it;` — is that a "pin"? It's not a reg steer (no hard reg specified). Hmm, but it does change the allocation.

Hmm, GCC 2.7.2: `register int x;` — the variable is still in memory! In GCC 2.x, `register` only affects allocation hints for locals in memory (they can be in a frame slot but "preallocated" to a register if possible). Actually in GCC 2.x, ALL local variables are in memory (frame slots); `register` variables are just marked so the register allocator can try to keep them in a register — but the RTL still has MEMs and the reload pass may keep the slot. Hmm, in GCC 2.x, `register` variables are handled by `allocate_variable` in function.c: they're put in the frame but "hard reg" candidates.

Hmm, in GCC 2.7 the front end's `expand_start_function` → for a register variable, `allocate_variable` creates a "pseudo" via `gen_rtx_...`? Let me check: in GCC 2.x, `expand_start_function` → `allocate_variable (decl, 0, 0)` → the variable gets a frame slot. But there's the "REGISTER_VARIABLE" handling in `start_function`? I recall that in GCC 2.x, register variables ARE kept in pseudo registers: `function.c`'s `start_function` has:

```c
  /* Make a new global hard_reg for each register variable ... */
```
Hmm.

Actually YES: I'm now fairly confident: in GCC 2.x, a variable declared `register` whose address is never taken is allocated a *pseudo register* by the front end (`expand_start_function` → `allocate_variable` → for register vars, `reg` is set). Let me verify in the source: function.c, `allocate_variable`:

Let me grep.
