---
ts: 2026-11-06T05:26:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ffTFjO5mIMETNjqlEDwB
---
So the memory clobber in the middle creates a 16-byte frame; at the end it doesn't. This is bizarre but reproducible. The clobber must force a temp allocation for something that's live across it.

Actually! Now I get it: the memory clobber forces values that are in *memory* (the struct array element?) to be reloaded. But the 16-byte temp could be from `assign_stack_temp` for the *struct member* `D_800AE7BC[*q].f0`? No.

Hmm, wait: maybe the 16 bytes are a **spill slot**? No, spills are reload's job and use `assign_stack_local` in reload1.c (line 2352/2384). A spilled pseudo would produce stack accesses though. Unless the spill slot is allocated and then the pseudo gets a register anyway... no.

Actually, reload1.c:663 `assign_stack_local (BLKmode, 0, 0)` — that's for the `-fstack-check`? Let me look. Line 2352: `assign_stack_local (GET_MODE (regno_reg_rtx[i]), total_size, -1)` — this is for *callee-saved register spills*. A 16-byte slot for spilling callee-saved regs? But no callee-saved regs are used.

Let me look at reload1.c:2352 context.
