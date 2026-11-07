---
ts: 2026-11-06T05:18:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kb48FTvSzfN2u3EwIdXi
---
No frame info in dumps. Let me check the greg dump for the asm and stack. Alternatively, let me search GCC source: `tools/reference/gcc-2.7.2/` for `scratch` and `assign_stack_local`. Actually, maybe the 16-byte frame is `current_function_outgoing_args_size` attributed to vars? No.

Wait, maybe the issue: the `asm` statement is inside a function that's `s32` and... hmm.

Let me try a more faithful minimal probe: add an extern struct array and an asm. Actually, let me test the hypothesis differently: take the nobar body and add a dummy 16-byte local array that is used in a way that survives but doesn't emit code. E.g.:

```
u8 pad[16];
pad[0] = 0;  // would emit a store
```
No.

Alternatively, test if the asm's memory clobber is the cause by using `__asm__("" : : : "memory")` vs `__asm__("")`. The minimal probe with plain `__asm__("" ::: "memory")` gave frame 0. So the memory clobber alone doesn't. So something about the *function* makes the asm create a frame.

Could it be that the asm's source line is inside a block with `extern` declarations...? No.

Hmm, let me test: in the minimal probe, the asm is between two global stores. In func_80175820, the asm is between a store through a pointer (`ptr[2] = ...`) and a load. Still no frame.

Wait — maybe the frame comes from `S_AE7BC_80175820_80175820` being an *incomplete or struct-typed array* and the asm causing... no, nobar has the same.

Let me test the actual hypothesis by compiling the orig body in a *small standalone* TU (not the big includer). The header body has externs to undefined types (S_AE7BC...), which are defined in the includer TU. So standalone won't compile.

Better: use hdump on a different includer TU and see if the frame is also 16. If yes, it's the asm.

Actually, I realize there might be a much simpler explanation: **the asm's memory clobber forces the compiler to consider that the call to `__builtin_...`?** no.

Let me look at GCC 2.7.2 source for asm memory clobber and stack: grep for "scratch" in the reference.
