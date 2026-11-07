---
ts: 2026-11-06T05:21:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3Hiaf9TnfNf8CdTDUKYr
---
The `(mem:BLK (scratch))` is `(mem:BLK (scratch:VOID))`, not a SCRATCH expression itself. Let me search for how a clobber of a MEM is treated in `local-alloc`/`sched`. Hmm.

Actually, let me search for "BLKmode" in local-alloc or reload for stack temp allocation. Or check `sched.c` for `mem:BLK`.

Honestly, the mechanism detail isn't needed for the result. What I need is: can pure C produce the same? Let me test the hypothesis that the frame difference is *unavoidable* by checking whether ANY of the 5 items can score 0 without asm. Given time, let me run a candidate generator.

But before investing 2 hours, let me reconsider the shard's purpose. The shard is "singleton crack shard G21x (scratch-only)". The expert expects some items to crack and some to wall. The evidence in moves.md is rich with cracked barrier items. But these 5 items are all headers with `h_exact` barriers added in P36 rung B ("NEEDED DIFFERS"). The comment says "!FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)". So the barrier was added *because* the source needs it to match — i.e., these are known to need the barrier. Our job is to find a real-C alternative.

Given the frame artifacts, I suspect these are walls, but the exact artifact might be crackable by a real C construct that produces a stack temp of the same size. For 75820, the target frame is 16 bytes of vars with NO access — that's a temp slot that was allocated and freed (like `assign_stack_temp` with free_temp_slots). What C construct allocates a temp during expansion without emitting code? **A function call's outgoing argument area**? No. **A struct-typed function argument passed by value**? The call to an opaque function with a struct arg allocates a temp.

Hmm! In the family, the source has no calls. But maybe the original code had something.

Wait, actually, let me reconsider: maybe the 16-byte frame is `current_function_outgoing_args_size` from the *asm being treated as a call*. The .frame comment says args=0, but maybe the MIPS .frame comment's "vars" includes outgoing args? Let me check the mips.h FRAME_... Actually, the `.frame` comment format: `vars=%d, regs=%d/%d, args=%d, extra=%d` — vars = get_frame_size(), args = current_function_outgoing_args_size. It said vars=16, args=0. Hmm.

OK here's another thought: maybe `get_frame_size()` includes the temp slots allocated by `expand_asm_operands` for *the memory clobber*: `(clobber (mem:BLK (scratch)))` — in `reload`, `find_reloads` for a MEM clobber with BLKmode... Let me look at `reload1.c` around `mem:BLK`. Actually let me grep for `MEM_IN_STRUCT_P` in reload or `assign_stack_temp` in reload.
