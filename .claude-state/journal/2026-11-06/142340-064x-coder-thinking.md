---
ts: 2026-11-06T21:23:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2SWwF4uARN8kS6dfrjuw
---
The includer is src/ov_MAIN_012/... and includes "../shared/ov/func_80160C28.h". If I copy the includer to a scratch dir with the same relative structure (scratch/ov_MAIN_012/x.c and scratch/shared/ov/func_80160C28.h), then `#include "../shared/ov/..."` resolves relative to the includer's directory → scratch/shared/ov/... 

So: create .run/P40/T11/W49x/item3/dump/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.c (copy) and .run/P40/T11/W49x/item3/dump/shared/ov/func_80160C28.h (modified). Then run cc1_dumps_tu.sh on the copied .c. The script adds -Iinclude -I(dirname) -Isrc/shared -Isrc, so "common.h" resolves via -Iinclude. Good.

Then inspect .sched/.sched2/.dbr.

But is this worth it? Let me think about whether I can crack item 3 by reasoning.

The difference: after the inner-if branch, sched1 emits `li v0,3072` before `move a0,s0`; target has the reverse.

With the keepalive asm (current src), it matches. The asm barrier blocks sched1 from moving the move down past the asm... wait, actually the asm is AFTER the move in the C, so sched1 can't move the move below the asm, but it could move the li above the asm? No — the asm is volatile, so sched1 won't move other insns across it? A volatile asm is a full scheduling barrier in sched1? In GCC 2.7.2, `volatile asm` sets `insn_sched` barriers via `find_basic_blocks` / `sched_analyze` treating it as a barrier. Yes, an asm volatile acts as a scheduling barrier (it's marked as such in sched.c: `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS && MEM_VOLATILE_P (PATTERN (insn)))` → barrier).

So the asm splits the block into two scheduling regions: before the asm (move) and after (li, sh, li, jal, sh). The move is alone in the first region → it stays first. Without the asm, one region, and sched1 reorders.

To replicate without asm, I need a real barrier between the move and the li. A real C construct that's a scheduling barrier but emits no code... There isn't one (a call emits jal).

Hmm, but wait: what about a *function call* that is already there? No.

What about a `volatile` local variable? A volatile read/write emits code.

So the keepalive is genuinely load-bearing for the scheduling. WALL? Let me check the moves.md for similar cases: "keepalive | func_8016432C | WALL sched1-argcopy-hoist — without the volatile-asm barrier sched1 puts the a0=s0 arg copy before the 0x188 store, local-alloc rewrites its base; best 2 (G25x)". That's exactly our shape (though the other way round).

And "keepalive | func_80184D28 | MATCH — keepalive replaced by return v0". 

So for item 3, maybe the wall tag is `sched1-argcopy-hoist` or similar. Let me check walls.txt for relevant tags.

But before declaring a wall, let me try more variants:
1. Drop the pin too (w2) — score 3 (move at 27, store uses s0).
2. Keep pin, remove keepalive (w1) — score 2 (move one slot late).
3. Try to make the move first by changing the C order/declarations.
4. Try `a` declared as `void *a` (no pin) + `a = arg0` and use a for both stores/call: w2 did that (score 3).
5. Try using a as the q-load base: changes the load register.
6. Try `p`/`q` reuse to shorten code.

Let me also consider: what if we remove the `a` variable and instead call `func_80146CA0(arg0)` with the store using arg0 (w2) — score 3. The residual: move at 27 and `sh v0,184(s0)` instead of (a0).

Hmm, what if we force a0 for the store by making the store's base a *cast*: `*(u16 *)((u8 *)arg0 + 0xb8) = 1;` uses s0. To use a0, the C would need the value in a0.

OK let me try a few scheduling tricks:
- Put the `a = arg0;` assignment *after* the two stores but before the call (so the move is born right before the call):
```
*(u16 *)((u8 *)q + 0x10) = 0xc00;
*(u16 *)((u8 *)arg0 + 0xb8) = 1;
a = arg0;
func_80146CA0(a);
```
Then the move would be right before the jal — probably scheduled into the jal delay slot, not the beqz. Target has it at the beqz delay. Hmm.

- What about `a = arg0` before the inner if *and* used in the condition? 

Let me look at the sched1 dump to understand the priority. Let me set up the dump; it's worth 5 minutes.

Actually, maybe a simpler experiment: change the `if` condition to use a different form that changes the branch scheduling. E.g., `if (*(s16 *)((u8 *)q + 0x10) < 0xc00)` → `if (*(s16 *)((u8 *)q + 0x10) < 3072)`. Same.

Let me look at the sched dump. I'll create the mirrored scratch.

Actually, wait. Before that, let me reconsider the goal: the kinds are {keepalive}. The pin ($4) may stay. Our best lever-free-of-keepalive is score 2 (w1). If we can't get 0, it's a WALL with best 2 (or a PARTIAL if we can score 0 keeping only the keepalive — i.e., dropping the pin? The pin is not a row kind, so keeping it is allowed; dropping it is also allowed. PARTIAL is about *row kinds* still kept. Since the row kind is keepalive, PARTIAL:keepalive = keeping the keepalive (score 0). Hmm, but that's just the current src body (which keeps both). If we keep the keepalive but drop the pin and score 0, that's PARTIAL:keepalive.

Let me test: keepalive kept, pin removed. Does it score 0? The keepalive's asm with `a` not pinned: `a = arg0; asm(r(a))`. The asm forces a into a register; the store uses a. The move might not be emitted at all (a coalesces with s0) → the code would differ. Let me test.

Actually, let me test both PARTIAL options quickly, then decide whether to invest in a crack.

Time: it's ~14:25. Item 2's wall needs its end time ~14:30. I'm now working on item 3, which is fine (the wall time is wall-clock from start; I'll note 14:09-14:30).

Let me test the keepalive-only body for item 3.
