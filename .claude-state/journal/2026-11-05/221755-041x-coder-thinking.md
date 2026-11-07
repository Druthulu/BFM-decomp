---
ts: 2026-11-06T05:17:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dR5lyuS2J1so87y4om6d
---
The asm with `(clobber (mem:BLK (scratch)))`. In GCC 2.7.2, `(mem:BLK (scratch))` — the `scratch` is a `const_int 0`? It's a special address. Hmm, but why would it allocate 16 bytes of vars?

Maybe the `(mem:BLK (scratch))` is handled in `find_reg_note`/`assign_stack_local`? Unlikely.

Alternatively: `vars=16` could be `current_function_pretend_args_size`? No.

Wait — maybe the asm insn is *not* the cause; maybe it's a `struct` return temp. The function returns s32, no.

Hmm, let me directly compare the nobar RTL's frame-related info. Let me grep both RTL dumps for "stack" or "frame" and the function's prologue insns. Actually, the frame size is in the .s .frame comment. Let me instead look at the `lreg` or `greg` dump for a stack slot. Or, simplest: dump `-dS` (sched) and look for `(set (reg:SI 29)` (sp) adjustments.

Actually, the simplest explanation test: the minimal probe with an *extern struct array* might reproduce. But more likely: the asm's memory clobber forces the *address* of a global to be re-materialized, increasing register pressure → spill. But vars=16 with no loads/stores... Hmm, in the orig asm I saw `lw $5,D_800AE7BC($2)` — that's a global load. The nobar uses `lw a2,0(at)` with `lui at`. Different addressing, no spill.

Let me look for `(mem:SI (plus:SI (reg:SI 29)` in the orig RTL function region — that would be a stack access.
