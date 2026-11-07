---
ts: 2026-11-06T05:19:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M6IPP0G95l7O6Mky0bin
---
No stack. So where does vars=16 come from?

Hmm — `free_temp_slots()` at the end. Not relevant.

Let me look at the actual .s prologue of the *orig* more carefully. `.frame $sp,16,$31 # vars= 16, regs= 0/0, args= 0, extra= 0`. Maybe the .frame comment is emitted by the assembler macro based on... no, GCC emits it.

Wait — maybe the 16 bytes come from **`current_function_outgoing_args_size`** which is counted in "args" not "vars". It says args=0.

Hmm, let me look for a `(mem:BLK (scratch))` in the final .s? It's gone.

Alternative: let me just check the nobar vs orig `.frame` across the other family members to see if this pattern is consistent (all have the asm). If every barrier body gets +16 vars, then it's the asm. Let me check func_80150170: orig frame vs nobar frame.

Actually, I realize I should check the *target* (build) object's frame, since the target is what we must match. The target = orig (score 0). For func_80175820, target frame is 16 (from the object disassembly: addiu sp,sp,-16 mid-function). So yes.

Now: is there any C construct that makes GCC 2.7.2 allocate 16 bytes of *unused* stack? Let me think about `assign_stack_temp` with `free_temp_slots`: if a temp is allocated during expansion but the slots are freed, the *frame size* is still counted (get_frame_size counts all stack slots ever assigned, even freed ones!). YES! That's it: `free_temp_slots` frees the slot for reuse but `get_frame_size` returns the max frame size including temp slots? Let me check.

In GCC, `assign_stack_temp` allocates a stack slot; `free_temp_slots` marks them free but the slot remains allocated in the frame (stack_slot_list). Actually `get_frame_size` returns `frame_size` computed from `stack_slot_list`, which is the list of all stack slots allocated (not freed). Hmm, freed temp slots are added to `temp_slot_list` for reuse but still counted.

So a C construct that allocates a 16-byte temp during expansion (then discarded) would give vars=16 without any access. What C construct does that? 
- Passing a struct by value to a function (call) — creates a temp.
- An `asm` with an "m" operand (assign_stack_temp).
- Returning a struct.
- A `({ ... })` statement expression?
- `__builtin_memcpy` with a constant size might use a temp? No.

But the asm here has no operands. Hmm.

Wait — maybe the 16 bytes come from the asm being expanded in a *block with a declaration*: the body declares `extern ... D_800AE7BC[]` etc. No.

Hmm, actually, maybe the memory clobber causes a `assign_stack_temp` in `expand_asm_operands` via `force_const_mem`? Line 1568: `force_const_mem` for inputs that don't allow regs. No inputs.

Let me look at line 1477 and 1578 — assign_stack_temp for output operands. No outputs.

So the asm itself allocates nothing. Then vars=16 must come from elsewhere... but nobar has vars=0 with the same code! The ONLY difference is the asm lines. Unless the line numbers shift something (debug info doesn't affect frame).

Hmm wait, let me double check that the orig.s .frame I read is really the function's. Line 4105 `func_80175820:` and 4106 `.frame $sp,16,$31 # vars= 16`. And nobar line 4106 `.frame $sp,0`. Both from the same includer TU. So yes, the asm causes 16 bytes.

Could it be `current_function_has_computed_jump`? no.

Let me look at the `-dg` (greg) dump around the asm in orig to see if a stack slot pseudo exists. Let me find the function in greg and look for `(mem:BLK (scratch))`.
