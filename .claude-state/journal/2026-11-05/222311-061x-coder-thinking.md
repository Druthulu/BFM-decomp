---
ts: 2026-11-06T05:23:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iHA6l1D2ONL7bHVa5t68
---
So frame_size = -frame_offset. frame_offset decreases with each assign_stack_local. A temp slot alloc increases frame_offset; freeing doesn't decrease it. So a 16-byte temp allocated during expansion → frame 16.

What in the real function allocates a 16-byte temp only when the asm is present? Hmm... `expand_asm_operands` calls `free_temp_slots()` at the end. `assign_stack_temp` with keep=0... 

Wait — maybe the temp is from the *first* call site... no calls.

Let me look at `expand_asm_operands` line 1477: `output_rtx[i] = assign_stack_temp (BLKmode, ...)` for output operands that don't allow regs. No outputs here.

Line 1578: input operands that don't allow regs. No inputs.

Hmm, so the asm itself doesn't allocate. Unless the `(clobber (mem:BLK (scratch)))` is processed by `expand_expr` for the `__asm__` with a memory clobber... no.

Let me look for `assign_stack_temp` calls in expr.c/stmt.c that might be triggered. Maybe the `(mem:BLK (scratch))` clobber is emitted via `gen_rtx (MEM, BLKmode, gen_rtx (SCRATCH,...))` and something calls `assign_stack_temp` for BLKmode scratch. Let me grep for "BLKmode" in stmt.c/expr.c near asm.

Alternatively — maybe the 16 bytes come from the **`!FAKE` barrier being inside a conditional that also has a `__builtin_memcpy`**? For func_80150170, yes, but 75820 has no memcpy.

Hmm, wait. Let me reconsider: maybe the frame is not from the asm but from the **`#include` context**: hdump replaces the include line with the body. The nobar body has 2 fewer lines, so line numbers shift, but that shouldn't matter.

Let me directly bisect the real body: orig with the asm removed → frame 0. orig with asm kept → 16. So the asm causes it. Let me now bisect the *function*: make a minimal version that still has the asm and reproduces frame 16. My probe didn't. Differences: real body has `extern S_AE7BC_80175820_80175820 D_800AE7BC[];` where the struct type may be defined as a union/array; and `p + *q * 4 + 0x20`; and `D_800AF634[*q].g0` with `s32 acc`, `s32 t`, and a `>> 2`.

Maybe the 16-byte temp comes from a *struct-typed array indexing with a variable index* — `D_800AF634[*q].g0` where the struct might be large; the compiler may need a temp for the struct? Hmm.

Let me check the actual struct definitions in the includer TU. grep S_AE7BC_80175820_80175820 in src.
