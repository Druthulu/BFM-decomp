---
ts: 2026-11-06T05:18:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_A6qrRqaRcM2XZnfRUmN5
---
Let me look at how `(mem:BLK (scratch))` is handled in the machine description — the MIPS pattern for asm clobber might need a stack? Hmm.

Actually, I wonder if the frame comes from the *`__asm__` being inside a conditional block with declarations*... no.

Let me try a different angle: maybe the frame isn't from the asm at all but from the **line number** of the asm: the asm's source is a different `.file` (the header). No.

OK, practical approach: rather than fully explaining, empirically test whether a *pure C* body can reproduce the 16-byte frame. What C construct yields vars=16 with no stack access? An uninitialized local array whose address is taken but which is never read/written, e.g.:

```
u8 pad[16];
sink = pad;   // store of the address to a global? that emits code
```
No.

What about a local array passed to a function call that's optimized? Calls emit code.

What about `__builtin_alloca`? That changes sp.

What about a large local array that gets scalarized/eliminated? Eliminated → no frame.

What about a *volatile* local? Would emit accesses.

Hmm, what about a local struct assigned to a global? Emits stores.

The target frame is 16 bytes *unused*. There's no C way to allocate an unused 16-byte frame. So this is likely `no-c-spelling` — the asm's frame artifact.

But wait — hold on. Let me reconsider: maybe the 16 bytes are for the asm because GCC's `expand_asm_insn` with clobbers calls `emit_insn` and the memory clobber `(mem:BLK (scratch))` gets `find_reloads`... and reload might allocate a stack slot for an address? Hmm, `(scratch)` is `(const_int 0)` in the address, which is not a valid address; MIPS `movstr`? The clobber is a PARALLEL with the asm. The `(mem:BLK (scratch))` in a clobber should never be reloaded (clobbers aren't real). 

Hmm, unless the MIPS backend's `print_operand`... no, frame size is decided before.

Let me just check GCC source: `assign_stack_local` calls in `expand_asm_insn`? Let me grep expand_asm_insn in stmt.c.
