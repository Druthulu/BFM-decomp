---
ts: 2026-11-06T05:25:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OhSw1zIAp8awTb47ZeUY
---
So the memory clobber creates `(mem:BLK (scratch))` with no stack. So where's the 16 bytes?

Let me test whether the 16-byte frame requires the *whole body* or just the asm in a function with certain variables. Let me bisect using the probe (now working). Variants:
1. body with `__asm__("" ::: "memory")` → frame 16 (confirmed).
2. body with `__asm__("")` → ?
3. body without asm → ?
4. body with asm but remove the `{ s32 acc ... }` block → ?
5. body with asm but remove `p2 = ...` block → ?

Let me write a probe runner script that generates variants and greps the frame. That's efficient.

Actually, the key question for the task: can a *lever-free* body produce the frame? If the frame is tied to the asm, no. Let me verify variant 2 and 3 (which we already know from the real TU: noasmclob and nobar both score 30 with 49 ins and presumably frame 0). So the frame is tied to the memory clobber. Since the clobber is a lever (barrier), and it's the only thing producing the frame, no lever-free body can match → WALL.

But wait: maybe a lever-free body can produce a 16-byte temp frame via a struct copy or a call. E.g., `__builtin_memcpy`? That's a builtin call; for a 16-byte constant copy GCC might emit inline code, not a temp. Hmm.

The target frame is 16 bytes of *unused* vars. What C construct allocates a stack temp and frees it (unused)? A **struct assignment/copy through a temp**: `struct S x = D_800AF634[*q];` would allocate a temp and copy — emits code though. Hmm, but if the copy is optimized away... 

Actually, `assign_stack_temp` with keep=0 followed by `free_temp_slots`: the classic case is `expand_call`'s outgoing arguments (not a temp slot) or `store_expr` for a struct return.

Hmm, what about a **compound literal** or **function call with a struct argument**: `f(D_800AF634[*q])` allocates a temp for the argument. But there's no call.

What about a **`__builtin_memcpy` with a 16-byte struct**? It emits inline copies.

Honestly, the frame is an artifact of the clobber. Let me find WHY: the 16 bytes could be from `assign_stack_temp (BLKmode, 16, 0)` in `expand_asm_operands`... but there are no operands.

Wait, maybe it's not the clobber but the `asm` statement's *volatile* behavior? Let me check variant 2 (`__asm__("")` no clobber) in the probe. Let me write a variant runner.
