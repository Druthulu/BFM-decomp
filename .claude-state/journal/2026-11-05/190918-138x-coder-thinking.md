---
ts: 2026-11-06T02:09:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mclnkfv3EiTIOjdNkIP9
---
The backtrace shows delete_jump called from jump_optimize at 0x80f31f5. UID 368, JUMP_INSN. But is it OUR function? The UIDs collide per function, so this could be another function's insn 368. The compile is in progress; the current function at that point... The bt doesn't tell. The .jump dump for our function showed no jump 368; if this hit is our function, then jump_optimize deleted it via delete_jump.

Which jump_optimize call site is at 0x80f31f5? Let me disassemble around there and map to source lines (no debug info, but we can find the call address relative to known functions). Alternatively, use the fact that delete_jump is called only at 4 places: lines 667, 1130, 1299, 1733. Line 667 is the condjump-to-next; 1733 is condjump-over-jump. 1130/1299 are x=a/b condjump transforms. All require a conditional jump!

But our jump is a simple jump to the epilogue. Hmm, unless redirect_jump(insn, NULL_RTX) converted it to a RETURN, and delete_jump was later called on it — delete_jump checks `single_set(insn)`; a RETURN pattern is not a SET → no delete. So not.

So this hit is likely a different function's jump. UIDs collide! I need the function name. Let me print `current_function_decl` and its DECL_NAME. The tree structures: DECL_NAME at some offset. Hard.

Alternative: print the insn's address and compare against the .jump dump? The dump prints UIDs, not addresses.

Alternative: run the compile on a TU containing ONLY our function. We can create a small TU that includes common.h and the function + all its externs. The function references externs declared in the TU; we can copy the def and its extern decls into a small file with `#include "common.h"`. The function uses Unkstruct_800B5CB8 (from engine_types.h via common.h), CAST_WIDTH, etc. Let's try: create a mini TU with just our function (from orig.c) and include common.h. Then compile with the same cc1 flags; the UIDs will match the .rtl dump of the full TU only if the function is compiled in isolation... UIDs are per function, so they should be identical! Actually UIDs are assigned per function starting fresh? Let me check: the dumps show each function starting at note 2. Yes, per function.

So a mini TU with just our function will have the same UIDs. Then gdb hits will be only our function's. 

But the mini TU must compile to the same code: the function body references file-scope externs and types. Let me build it: take the src TU's extern declarations needed. Simpler: extract from the src TU the lines from `#include "common.h"` through our function? The src TU has `#include "common.h"` then extern decls then the function. Let me look at the region around 4183-4200 (the externs right before our function) and construct a mini file: common.h include + those externs + the orig function.

The function uses: Unkstruct_800B5CB8, CAST_WIDTH, func_80185DD8, func_80185B48, func_8012A828, D_8018C750, D_8018C700, func_8012BD3C, func_80185D3C, func_8012B8E4, func_8012B178, func_8012CBA4, func_8012B200. The externs at 4183+ cover some. Let me check lines 4183-4200.
