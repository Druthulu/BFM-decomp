---
ts: 2026-11-06T21:21:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tRkqfLcywhuGH1feSAb6
---
Score 3: mine has `move a0,s0` at 27 instead of 24, and uses s0 for the store base at 29.

So sched1 still sinks the move. The keepalive asm was the barrier that kept it early.

How to make the move early with real C? Ideas:
1. Make `a` (a copy of arg0) used in an expression that is *born earlier*, e.g., use it in the `if` condition? No, that changes semantics.

2. Change the *store order*: put `*(u16 *)((u8 *)arg0 + 0xb8) = 1;` BEFORE `*(u16 *)((u8 *)q + 0x10) = 0xc00;`. Then the move (needed for the store base) would be born before the li v0,3072. Let's see what target has: li v0,3072; sh v0,16(v1); li v0,1; jal; sh v0,184(a0). The store to 0xb8 is in the jal delay slot (last). Hmm, if we swap the C order, sched1/sched2 might still reorder them (the sh to 184(a0) has no deps on the others). Worth a try.

3. Use `a` in the condition: `if (*(s16 *)((u8 *)q + 0x10) < 0xc00)` → maybe compute `a = arg0` inside a condition expression like `if (a = arg0, *(s16*)...)`? A comma expression in the condition: `if ((a = arg0, *(s16 *)((u8 *)q + 0x10)) < 0xc00)`. Hmm, then the assignment is evaluated before the condition — the move would be before the lh/slti, not in the delay slot. Target has it in the delay slot (after slti). But sched1 could move it. Hmm, risky.

4. Use the value `a` in the *slti* comparison? No.

5. Make the copy necessary before the branch by using it in the branch condition: e.g., `if (*(s16 *)((u8 *)(a = arg0) + 0x10) < 0xc00)`? That uses `a` as the base of the load in the condition — but the target loads from q (q is a separate load from arg0+0x20). q = *(arg0+0x20), and a = arg0. Different pointers.

6. Hmm, what about making the store `*(u16 *)((u8 *)a + 0xb8) = 1` use a variable `a` that is *also* used in the `p`/`q` computation, so it's live earlier? E.g., `q = *(s32 *)((u8 *)a + 0x20);` using a instead of arg0! Then `a` is used at the q load (68a8 region), so the copy would be needed earlier... but the target has `lw v1,32(s0)` using s0, not a0. Hmm, in the target, at 68a8 `lw v1,32(s0)` — s0. So q is loaded from s0.

Hmm.

7. What if we place `a = arg0;` at the very start of the function (before the outer if)? Then a is live throughout, and the copy would be at the prologue — target has it at 68c0. No.

Let me reconsider: the target's `move a0,s0` is in the delay slot of the inner-if branch. The instructions after the branch are: li v0,3072; sh v0,16(v1); li v0,1; jal; sh v0,184(a0).

Interesting: the `sh v0,184(a0)` is in the jal's delay slot and uses a0. So a0 must be set before the jal. The move at 68c0 is placed early (in the beqz delay slot) rather than just before the jal.

For reorg to pick the move for the beqz delay slot, the move must be the first insn after the branch in the scheduled stream. sched1 must emit the move before `li v0,3072`.

Why would sched1 do that? sched1 sorts by priority; the move has a long live range (a0 needed at the last store) — maybe higher priority. In mine, sched1 put the li first.

What makes the move higher priority? Its dependence chain: the move feeds the store `sh v0,184(a0)` which is in the jal delay. Hmm.

Maybe the difference: with the asm keepalive, `a` was live at the asm (right after the move), giving the move an earlier "need".

Let me try variant 2 (swap the store order) and a few others. Let me also try using `a` for the q load: `q = *(s32 *)((u8 *)a + 0x20);` — hmm, that changes the load's base to a0; target uses s0.

Let me try:
- w3: swap the two stores in the then-block.
- w4: use `a` for the q load: no.
- w5: put `a = arg0;` right after `q = *(s32*)...` (before the inner if) — i.e., hoist the copy out of the then-block:
```
q = *(s32 *)((u8 *)arg0 + 0x20);
a = arg0;
if (*(s16 *)((u8 *)q + 0x10) < 0xc00) { ... }
```
Then the move is before the lh/slti/branch. The target has it after the branch (in the delay slot). sched1 might move it down into the delay slot? Maybe.

- w6: `a = arg0;` before the inner if but after the q load.
- w7: use a as the base for the store to q? no.

Let me test these.
