---
ts: 2026-11-06T21:22:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0lRPuP4ZhbpjpmiY4Mp3
---
w5 (a = arg0 before the inner if) still puts the move at 27 — sched1 sinks it. So the copy's placement is determined by sched1, not by the C order.

What makes sched1 keep the move early? The keepalive asm is a scheduling barrier: it stops sched1 from moving the move below the asm. Since the asm is right after the move, the move can't sink past it. But the li v0,3072 is after the asm too, so the move stays first.

Without a barrier, sched1 sinks the copy to just before its first use (the store).

How to keep the copy early without an asm? Make the copy's *first use* early. Its uses: `*(u16*)((u8*)a+0xb8) = 1` and `func_80146CA0(a)`. If we reorder the C so the store using `a` comes first (w3), sched1 put `sh v0,184(s0)` first — using s0, not a0 (coalesced), and the move at 27. Hmm, in w3 the store uses s0 directly (coalesced with arg0) — no copy needed until the call.

The fundamental issue: `a = arg0` coalesces with arg0 (s0) unless it must be in a0 (call arg) — the call needs a0 at the jal. So the copy is only needed at the call, and sched1 sinks it to just before the jal... but in the target it's at the beqz delay slot (much earlier).

Wait, why is the target's move in the beqz delay slot? Because reorg's delay-slot filling took the first insn after the branch — and sched1/sched2 had put the move first. With the asm barrier, the move was pinned early.

Hmm, what if we make the move needed earlier by a real use that doesn't add an instruction? E.g., use `a` as the base for a store that already exists. The store `*(u16 *)((u8 *)q + 0x10) = 0xc00` uses q. What if we use `a` as the base for the *0xb8 store* and place it before the q store (w3) — sched1 coalesced it to s0 (no copy needed since a=arg0 and arg0 is s0, and the store just uses s0).

To prevent coalescing of `a` with arg0, we need arg0 to stay live after the copy (so they can't share). arg0 (s0) IS live throughout (used at 6880-68a8). So the copy a=arg0 can't coalesce with s0? Wait, but coalescing means a and arg0 share s0 — that's allowed if the copy is removed (a and arg0 have the same value; sharing is fine as long as the live ranges overlap... they do overlap, and that's exactly why coalescing works: a's live range is a subset of arg0's). So `a` can just BE s0. Then no copy is needed except where a0 is required (the call).

So the move is only needed for the call. The target's move at the beqz delay slot is a scheduling choice.

How to force the call-argument move earlier? If the call's argument setup is scheduled early... In mine (w2), the move is at 27, which is... let me see the mine order: 
mine: 24 = ?, 25..26, 27 = move a0,s0, 29 = sh v0,184(s0). 

Target: 24 move, 25 li, 26 sh, 27 li, 28 jal, 29 sh v0,184(a0).

Mine (w2): probably 24 li v0,3072; 25 sh v0,16(v1); 26 li v0,1; 27 move a0,s0; 28 jal; 29 sh v0,184(s0).

So mine has the move just before the jal; target has it in the delay slot of the beqz (24), and the jal's delay slot is filled by `sh v0,184(a0)`.

Hmm, so in the target, the move is hoisted 3 slots earlier, and the store to 184 uses a0.

What would make sched1 emit the move first? A barrier or a dependency. 

Idea: make the store `*(u16 *)((u8 *)a + 0xb8) = 1;` come *first* and depend on `a` (not coalesced). If `a` were a *different* value than arg0 (e.g., a pointer computed from arg0), the copy would be a real computation. But target's move is a pure copy.

Hmm, what if the C uses a *volatile* pointer? no.

Let me look at this from the "what did the original source look like" angle. The keepalive was added by a previous agent to fake the ordering. The real source probably had `a = arg0` and the compiler happened to schedule it early — but our compiler build/source produces the sink. So the wall may be genuine.

But wait — the kind here is keepalive only; the pin $4 is allowed to stay. With the pin, `a` is hard a0. Then `a = arg0` is a move from s0 to a0, and since a is a hard register, sched1 treats it as... hmm, with the pin, the move is required at that point (a0 is a fixed reg; the value must be there). Does sched1 still sink it? Our w1 (pin kept, keepalive removed) scored 2: the move was at 25 instead of 24 — a one-slot difference. So the pin keeps the move but reorg picks a different delay-slot filler.

So with the pin: mine has the move at 25, target 24. Mine's 24 is presumably `li v0,3072` and the move at 25. So the delay slot is filled with the li in mine, move in target.

Reorg's delay-slot choice depends on the instruction order after the branch. With the pin, the move is at some position; the li is before it in mine.

Hmm, can I get the move before the li? The C order in the then-block is: `a = arg0; store q; store a; call(a)`. The `li v0,3072` comes from the store `*(u16*)((u8*)q+0x10) = 0xc00`. So the li is generated before the store. The move `a = arg0` is generated before both.

So in the *unscheduled* stream: move a0,s0; li v0,3072; sh; li v0,1; jal; sh. That's the target order! And sched1 reorders to li first? In w1, mine has move at 25 (after something at 24). What's at 24? Probably `li v0,3072`.

Hmm, so sched1 moved the li before the move. Why? Because the move (a0=s0) is a "copy" and sched1 might sink copies.

What if we add a dependence: make the store `*(u16*)((u8*)a+0xb8)=1` use the result of the li? No.

Alternatively, make `a` used in the *li/store*: e.g., `*(u16 *)((u8 *)a + 0xb8) = 1;` — the store's base is a. If sched1 sinks the copy, the store's base would be s0 (coalesced). With the pin, a is a0 hard, so the store must use a0 → the copy must precede the store. The store is scheduled... in the target, the store is in the jal delay slot (last). So the copy could be anywhere before it.

Hmm, what if we make the `a` store come *before* the q store in the C? Then the copy must precede the a-store; if the a-store is scheduled first... but sched1 reorders.

I tried w3 (swap) without the pin → 7. Let me try the swap *with* the pin.

Also, another idea: use `a` in the *condition* of the inner if: `if (*(s16 *)((u8 *)q + 0x10) < 0xc00)` — no.

What about `if (a == arg0 && ...)`? Extra comparison.

Hmm, what about making the store to 0xb8 a *different* pointer computation that requires a: e.g., `((u16 *)a)[0x5c] = 1;` — same.

Let me try with the pin:
- w6: pin kept, store order swapped.
- w7: pin kept, a used for the q load? `q = *(s32 *)((u8 *)a + 0x20);` — target uses s0 for that load... but wait, if a is a0 (pinned), then q's load would use a0. Target has `lw v1,32(s0)`. Mismatch.

Let me think about reorg's delay slot selection: `reorg.c` fills a branch delay slot with an insn from after the branch if it's "safe" and the insn is the first in the stream (it uses `fill_slots_from_thread` scanning the insns after the jump). It takes the first eligible insn. So the order after the branch matters: sched1's output.

In mine (w1, pin kept), the stream after the beqz is: li v0,3072; move a0,s0; sh v0,16(v1); li v0,1; jal; sh. So sched1 put the li before the move. In the target: move; li; sh; li; jal; sh.

Why would sched1 order the move first? The move (a0=s0) has a dependence: s0 must be live; the li has none. sched1 uses priorities: an insn that unblocks more gets scheduled first. Hmm.

What if the move's destination a0 is needed soon (the store in the delay slot)? In target, the store `sh v0,184(a0)` is the last. 

Honestly, the asm barrier was doing this. Without it, sched1 picks differently.

Could a real-C change alter sched1's priorities? For example, making the move's result used by an insn that is scheduled early. E.g., if the *first* then-block statement were the a-store, the move would be needed early. w3 did that without the pin: sched1 scheduled `sh v0,184(s0)` first (using s0, no move needed). With the pin, the store must use a0, so the move is needed before it. Let me test w6 = w3 + pin.

Let me also test w8 = pin + `a` used for the q load in the *then* block? no.

Let me run w6.
