---
ts: 2026-11-06T05:22:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RYjtiVVWMJperO9vMYDN
---
`var_size = MIPS_STACK_ALIGN(size)` where size = `get_frame_size()`. So frame=16 means get_frame_size()=16 (or rounded). get_frame_size() = frame_size set in function.c.

frame_size is incremented by `assign_stack_local_1`. Let me check `get_frame_size` and where frame_size is set: also `assign_stack_temp`. If a temp slot was allocated and freed, `get_frame_size` might still count it? Let me look at function.c: `get_frame_size()` returns `frame_size`. `assign_stack_local_1` sets `frame_size = align + size`. `free_temp_slots` doesn't reduce frame_size. So a freed temp slot still counts!

So: the asm's memory clobber causes a *temp slot* allocation (16 bytes) during expansion, which is then freed but still counted in the frame. What allocates a 16-byte temp in `expand_asm_operands`? `force_const_mem`? No.

Hmm, but my probe with the same construct didn't. Let me look at what's special: maybe it's `S_AE7BC_80175820_80175820` — a struct with a *union* or an array member? `D_800AE7BC[*q].f0` — the struct member access. No temp.

Wait — maybe the temp is from `(clobber (mem:BLK (scratch)))` in **local-alloc**: line 1134 "Counter to prevent allocating more SCRATCHes than can be stored in SCRATCH_LIST". The `(mem:BLK (scratch))` is a MEM with SCRATCH inside. In local-alloc, `GET_CODE (recog_operand[i]) == SCRATCH` — not this. Hmm.

Let me check `function.c` for `frame_size` and `assign_stack_temp` with `BLKmode`. Actually, let me grep `get_frame_size`.
