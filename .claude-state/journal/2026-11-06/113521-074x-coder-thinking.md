---
ts: 2026-11-06T18:35:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Is5haMOiAwoAnmMr7gNv
---
The priority in the ready list is the insn's INSN_PRIORITY (0x7f000001 = LAUNCH_PRIORITY assigned to the currently-executing insn in the backward pass). In the trace at T-18: "52 (1) 55 (7f000001)" — 55 is the currently executing insn (the one being scheduled at T-18), so its priority was set to LAUNCH_PRIORITY. That's just the trace artifact, not a property of 55.

OK, so the difference is the *order* in which insns become ready in the backward pass. The backward scheduler starts from the block's end and walks backward. Insns become ready when all their successors have been scheduled.

In the orig, 55 (a1 symbol) is scheduled at T-18 (5th from the start). In w1, the equivalent is insn 94 (the call arg), scheduled at T-8ish (12th).

Hmm, why? In the orig, the RTL has the asm at 57 and the call arg copy at 96. Insn 55 feeds both the asm (57) and the call arg (96). The asm is a barrier: sched1 won't move memory insns across it, and the asm itself must be scheduled at its position. The asm (57) uses 77 (from 55) — the asm is scheduled at T-17 (right after 55). Because the asm is a barrier, sched1 must schedule all memory insns (stores 88, 91, etc.) on the correct side. The asm's position in the block forces the a1 materialization before it.

So the asm barrier is doing the work. A real-C equivalent would be a memory barrier that sched1 must respect. What creates a memory barrier in real C? A volatile store or a call. Our code has stores (the unk14/unk2/unk58 stores) but those are at their source positions; sched1 can move them within the block (it treats memory refs with alias analysis; since they may alias, it preserves their relative order but can move them relative to non-memory insns).

Hmm, actually sched1 DOES keep memory operations in order (it's a "memory dependence" model: stores may alias, so their order is preserved). The a1 symbol_ref is not memory, so it can move freely.

The target's a1 is early because the asm (a memory barrier) forced it.

Real C: what if we make the a1 value used by a *store*? E.g., if the first store used a1 as the stored value... no.

Hmm, what about the *source order* of the stores and the a1 assignment? The target's order: a1 load (22), v0 const (24), s0=4 (25), store unk14 (26)... The source order is the same. sched1 reordered.

Let me think about the scheduler's backward pass: it starts with the last insn (107 = the call func_8002D4C8?) and walks backward, scheduling insns as they become ready. The order of the final schedule is determined by which insns become ready when. The a1 symbol (55) is ready only when its uses are scheduled: the asm (57) and the call arg (96). In the orig, the asm 57 is scheduled at T-17 (late in the backward pass = early in the final order) because the asm is a barrier that must be placed... hmm.

In w1 (no asm), 55 is deleted (folded into 94). Insn 94 (the call arg) becomes ready only after its use (the call 100) is scheduled. The call 100 is scheduled at T-3 (3rd from the end). So 94 becomes ready around T-4..T-8 and is scheduled at T-8 (after 86, 89 which have hazards). 

To make 94 early, it must become ready early in the backward pass — i.e., the call must be scheduled early in the backward pass? No: the backward pass starts at the END. The call is near the end (T-3). Insns ready right after the call are its predecessors: the arg copies (94,96,98) and the memory ops.

Hmm, the target's 94 is scheduled at position 5 from the start — in the backward pass that's T-18 (near the END of the backward pass). Wait, I need to be careful: the trace's T-1 is the last insn scheduled in the backward pass = the FIRST insn of the block (the block head). So T-22 (orig) is the first scheduled in the backward pass = the LAST insn of the block. So the final order = reverse of the T sequence: T-22 is the last insn, T-1 is the first.

Orig final order: T-22=45? Hmm, T-22 "45 (1)" — the trace at T-22 lists "45 (1)" as the ready list before scheduling... and "now 45". So the insn scheduled at T-22 is 45, which is the block head (43 is the block head, 45 is the first insn). So the final order starts with 45. Yes: T-22 = position 1, T-1 = position 22.

So the orig order: 45,47,49,52,55,57,60,63,66,69,72,74,77,79,88,91,96,98,100,102,106,107.
- 55 = a1 at position 5. ✓ (target 22-23 after 4 insns: 52, 92?? hmm, where's 92 in the orig? The orig's block has 96,98,100 as the call args and no 92? Let me see: in the orig, the two moves: 52 (a0 = s0, the pin) and... the call arg a0 copy might be folded into the call (a0 is a hard reg; `(set (reg 4 a0) (reg 4 a0))` gets deleted by cse/combine?). In the orig's asm, there are two moves a0,s0. Hmm, in the orig's sched block 3 list: 45,47,49,52,55,57,60,63,66,69,72,74,77,79,88,91,96,98,100,102,106,107 — no 92. So the second move (92 in w1) doesn't exist in the orig? But the target asm has two moves.

Wait, in the orig the pin a0 is `register s32 a0 __asm__("$4")`. The keepalive asm `__asm__ __volatile__("" :: "r"(a1))` doesn't involve a0. Hmm, where does the second move come from? Let me look at the orig's RTL around insn 52 and the call. Actually maybe in the orig the call arg a0 copy is insn 92 but it was deleted as a self-copy after the pin... but the target asm shows `move a0,s0` twice at 8014 and 8018. Let me check the orig's final asm: dump to.s.

Actually, the target.s shows:
```
8010: jal func_8012B1B4
8014: move a0,s0      <- delay slot
8018: move a0,s0
801c: lui a1
```
And in the orig's schedule, position 4 is 52 = `a0 = s0` (the pin) and position 5 is 55 = a1. Hmm, so where's the second move? Maybe insn 52 in the orig's RTL is already the *pair*? Let me look at the orig's .rtl: insn 52 = `(set (reg/v:SI 4 a0) (reg/v:SI 73))` (pin a0 = s0) and insn 92 = `(set (reg:SI 4 a0) (reg/v:SI 4 a0))`. In the orig's .rtl, maybe the second one is absent because a0's value is already in $4 and the call's arg copy is a no-op that flow deletes? But the target's asm has it.

Hmm, wait: in the orig's dump the block 3 has 45,47,49,52,55,57,... — where's the call arg a0? The call insn 102's args: 96 (a1), 98 (a2), 100 (a3) — and a0 is used directly (hard reg). So the call's a0 arg copy is gone in the orig, but the target asm shows two moves.

Hold on, the target asm at 8014 (delay slot) and 8018 — maybe 8014 is insn 52 (the pin assignment) placed in the delay slot by reorg, and 8018 is... another copy? Let me look at the orig's final .s.

Let me just compare the orig's final asm to the target's. The orig scores 0, so they're identical. The two moves: one is the pin assignment `a0 = s0` (insn 52), and the other might be the *call arg* copy which exists in the orig's RTL. Let me look at the orig's .rtl dump for insn 92.

Hmm, I'm spending a lot on this. Let me step back and think about what real-C change could make the a1 materialization early.

Since the keepalive's asm was a *barrier* that pinned the schedule, a real-C equivalent is hard. But maybe there's another way: make the a1 symbol_ref insn *not foldable* and *dependent* on an early insn.

Idea: compute a1 from `a0`? e.g., `a1 = (s32)&D_801A15AC;` — no dependency. What if we write `a1 = (s32)&D_801A15AC + (s32)(s0 - s0)`? launder.

Idea: use a *variable* for the address so it's a load from memory: `a1 = *(s32*)&D_801A15AC;`? That changes the code (a load instead of lui/addiu).

Idea: make a1's value used by the *first* store: e.g., `((Unkstruct*)a0)->unk14 = v0;` — what if the store's address is `a1 + something`? no.

Hmm, let me look at the problem from the target's perspective: maybe the target's source had the keepalive (the pin+keepalive were added by a previous agent as a workaround for a *different* natural layout). The task is to find a real-C body that scores 0 without the asm. Given the scheduling dependence on the asm barrier, maybe the answer is a different statement order that makes sched1 naturally produce the target's order.

Let me think about sched1's backward pass more carefully:
- The block (43..107 in orig, 43..105 in w1).
- The backward pass schedules the last insn first. The last insn of block 3 is the call func_8002D4C8 (or the branch?). In w1, the block is 43..105 (the branch_equality at 105). The call func_8002D4C8 (118) is in block 5.
- The a1 arg insn (94) becomes ready when the call (100) is scheduled. The call 100 is scheduled at T-3 (third from the block end? no, T-3 means 3rd from the *first* scheduled = near the block end). The final order position of 100 is T-3 → position 20 of 22. So the call is near the end. Then 94 becomes ready and is scheduled at T-8 → position 15.

To get 94 at position 5 (orig), it must become ready much earlier in the backward pass, i.e., the call must be scheduled much earlier (T-18). But the call is near the block's end...

Hmm, that suggests in the orig, the call insn 100/102 is scheduled at T-19? The orig's trace: T-19: "52 (1), now 52"; T-18: "52 (1) 55 (7f000001), now 55 52". Hmm, the call 102 is scheduled at T-3. So how did 55 become ready at T-18 if its use (the call arg 96) is scheduled at T-5?

Because 55 is also used by the asm (57), which is scheduled at T-17! The asm 57 is scheduled at T-17 (position 6). The asm becomes ready when its successors are scheduled — the asm is a barrier with deps on the memory insns after it. So the asm is scheduled late in the backward pass (T-17), making 55 ready at T-18.

So the key is the ASM's position in the backward schedule: it's placed at position 6 (early in the final order).

A real-C barrier: the asm is volatile and uses/defines memory (sched_analyze sets memory deps). Real C stores are also memory barriers of sorts. The block's memory insns: 64 (store unk14), 86 (store unk2), 89 (store unk58), 57 (the asm), and the call 100 (memory). sched1 preserves the order of potentially-aliasing memory refs: 57 (asm) is between 55 and 60 in the source... 

In the target's final order: 55 (a1), 58 (v0), 60?, 63?, 66?, 69?, 72?, 74?, 77?, 79?, 88?, 91? Hmm, I'm conflating the orig's insn numbers with the target's asm.

OK, let me take a completely different approach: brute-force a sweep of statement orders (like the moves.md's "statement-order permutation sweep") with the real statements: 
- a0 = s0;
- a1 = &D_801A15AC;
- v0 = 0xFFF60000;
- s0 = 4;
- unk14 = v0;
- v0 = &D_801A1474; v1 = 0x40000000; v0 |= v1; v1 = 0x20000000; v0 |= v1;
- a2 = &D_801A15B4;
- a3 = 0x20;
- unk2 = s0;
- unk58 = v0;
- if (call) ...
- call

The dependencies constrain many orders. Let me permute a few independent groups:
1. Position of `a1 = ...` among the early statements.
2. Position of `a2/a3` and the stores.

But sched1 reorders anyway, so source order may not matter much... though the RTL order affects the ready-list order.

Given time (item 1 started 11:30, now 11:37), I should do a moderate sweep. Let me generate permutations of the independent statements in the body after the call func_8012B1B4, respecting data deps, and score them.

Independent groups:
- A: a0 = s0 (must precede the stores)
- B: a1 = &D_801A15AC
- C: v0 = 0xFFF60000; s0 = 4; unk14 = v0 (the store needs v0 and a0)
- D: v0 = &D_801A1474; v1 = 0x40000000; v0 |= v1; v1 = 0x20000000; v0 |= v1 (the or chain)
- E: a2 = &D_801A15B4; a3 = 0x20
- F: unk2 = s0 (needs a0, s0)
- G: unk58 = v0 (needs a0, v0 from D)

The target's order: A, B, C, D, E, F, G, call.

If I permute the source order of the groups, sched1 might produce the target order. Let me sweep permutations of the group order (A,B,C,D,E,F,G) subject to deps: C before F? F needs s0 from C (s0=4), so C before F. D before G. A before C/F/G (a0). So valid orders: A, B, C, D, E, F, G in various interleavings.

That's a lot (7! / constraints). Let me limit: keep C's internal order, D's internal order; permute the group order among {B, C, D, E, F, G} after A, with F after C, G after D. That's manageable (~60 orders). Each compile ~1.5s → 90s. OK.

Actually, the moves.md says the target order is exactly the source order, and sched1 preserves it in the target because of the barrier. Without the barrier, sched1 reorders. Statement order permutations might or might not change sched1's output. But the sched1 order depends on the RTL order (the backward pass starts at the block end and the ready-list order depends on the RTL positions). So permutations are worth trying.

Let me write the sweep script.
