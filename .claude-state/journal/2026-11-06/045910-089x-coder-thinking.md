---
ts: 2026-11-06T11:59:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZsiS71JaHsCOmH12nrih
---
No change. The swap persists. This is a local-alloc register choice. Let me check walls.txt: `lreg-qty-priority local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo (G22)`. And `lreg-hardreg-live-end`. 

Hmm. Let me think about how to make two get v1 instead of v0. 

In local-alloc, within a basic block, registers are allocated by qty priority. The first pseudo allocated gets the lowest-numbered free reg (v0). To give two v1, p must be allocated first (get v0). p is born at the lw (before two's li). So p should be first... but it isn't.

Wait — maybe local-alloc doesn't allocate in birth order; it sorts by `qty_compare` (priority). Let me check qty_compare in local-alloc.c. Priority = refs * something / live_length. p: 4 refs, two: 2 refs. Higher refs → higher priority → allocated first → gets v0. So p should get v0. But mine gives two v0.

Unless `two` has higher priority because of the REG_EQUAL constant (constants might get a boost). Or because `two`'s live range is shorter... priority = (refs * refs * ...) / live_length. A short live range with few refs can have high priority.

Let me look at local-alloc.c qty_compare. Actually, this is the lreg-qty-priority wall. To flip, I need to change the qty priority. Options:
- Increase p's refs (it has 4). 
- Decrease two's refs (it has 2).
- Change live lengths.

Hmm. Or make `two` a copy of a register that's already in v1.

Alternatively, maybe I can make `two` share a register with something already in v1. E.g., if `p` is in v0 and `two` is a copy of a value in v1... 

Wait — actually, the target has `lw v0,32(s0)` (p=v0) and `li v1,2` (two=v1). What if `two` is the SAME pseudo as `v` (the later variable)? No.

Let me think differently: what if I reorder so that `p` is used MORE or `two` is used less, changing the priority. `two` is used twice (li + sh). If I use `two` only once (store the literal 2), then it's not a variable. That's nopin (still two in v0). 

Hmm, in nopin, `unk2 = 2` — the constant 2 goes to v0. So even as a literal, it gets v0. 

What if I make the constant NOT a simple li? E.g., store `a0->unk2 = (s16)2` — same. 

What if I store a value that's in v1 naturally? Like the low half of p? No.

Let me look at the register allocation more carefully. The target's `li v1,2` — maybe the pin forced $3=v1. Without it, gcc picks v0. To force v1, I need a real-C reason for v1.

What if `two` is assigned from a computation that uses v1? E.g., `two = (s32)(p != 0) + 1;`? That would use v0/v1 and add insns.

What if `two` is a copy of `p`'s low bits? No.

Hmm. This is the lreg-qty-priority wall. Combined with the store sink (sched-store-sink). Two walls.

Let me try to crack the store sink at least (maybe it's easier), and see if the score drops.

For the store sink: the barrier prevented the store from sinking past the li a0. Let me try adding a dependence: make the store value depend on something computed after the li. But v is computed before. 

Alternatively, reorder the source so the store is the LAST thing in the middle block, then the barrier... without the barrier, sched still sinks.

Hmm. Let me look at what the barrier does: it's a `__asm__ __volatile__("")` at the end of the middle block, right after the store. It prevents sched2 from moving insns across it. Without it, the `li a0,2432` (from the final call) hoists above the store.

Real C: if the store and the li are in the same basic block and independent, sched reorders them. To prevent, add a dependence. The li a0 is the call arg. If the store's address or value depended on a0... it does (a0+0x10). But the li a0=0x980 overwrites a0! Wait — a0 is the function parameter (the struct pointer). But the final call sets a0=0x980. So a0 is reassigned. The store `*(a0+0x10) = v` uses the OLD a0 (the struct pointer, in s0 after `move s0,a0`). Actually a0 was moved to s0 at entry, so the struct accesses use s0, not a0. And the final call's a0=0x980 is a new value.

So the store `sw v0,16(s0)` uses s0. The li a0=0x980 is independent. Sched can reorder.

To force the store before the li: hmm. Maybe reorder the source so the final call's argument setup happens later. But the compiler schedules it.

This is a sched-store-sink wall. 

So item 4 has two walls: lreg-qty-priority (register swap) and sched-store-sink (store position). Both are in walls.txt.

Hmm, but let me not give up. Let me try a few more:
- For the store: make the store depend on a value loaded after? No.
- For the register: try `two` as a `s32` read from a global that's 2? No.

Actually, let me reconsider the register swap. The pin was `register s32 two __asm__("$3")`. $3 = v1. The target has two in v1. If I could make gcc put the value 2 in v1 via a real-C mechanism... 

What if `two` is the result of `func`? No.

What if I use a `register` variable without asm? The brief says "no `register` vars". So no.

What if I make `two` a parameter-like value? No.

Hmm. Let me check if the swap is actually a lreg-qty issue by looking at what qty priority gcc gives. Actually, let me try increasing p's usage or decreasing two's to flip.

two has 2 refs. If I store the literal 2 (nopin), two is a constant with 1 use. Still v0. 

What if p is used 5+ times? It's used 4 (lw + 3 sh). Adding a 4th sh? No, changes code.

What if `two` is a copy of `p`'s value masked? No.

Let me try: assign `two` from `v`? v is computed later. No.

Let me try making `two` a `char` (u8/s8) — maybe HImode/QImode changes the allocation. v_two_u16 was 8. Let me try s8/u8.

Also, let me try `((...)a0)->unk2 = 2;` but with the store BEFORE the p load (p = ... after unk2). v_p_after_unk2 = 8 (no change).

Hmm.

Let me step back. Two independent walls (register priority + store sink). The best is 8 (44 ins, target 44). That's actually quite close (only 6 register-pair mismatches + 1 store position). But not 0.

Given the budget (20-30 min), let me spend ~20 min on item 4 trying. It's 04:58 now, item 4 started ~04:56. Let me continue.

Let me try more variants:
1. v_two_s8 / v_two_u8.
2. v_two_from_p: `two = (p != 0) ? 2 : 2;`? adds compare.
3. v_two_shift: `two = 1 << 1;` folds to 2.
4. v_two_add: `two = 1 + 1;` folds.
5. v_two_cast: `two = (s32)2u;` folds.
6. v_p_before: ensure p's def is before two's (already).
7. v_use_two_twice: use two in a second store to give it more refs? Would change code.

Hmm. The register swap is stubborn. Let me look at local-alloc.c to understand qty priority and whether I can influence it with real C.

Actually, maybe the swap isn't local-alloc but the front-end's REG_EQUAL constant. When `two = 2` and then `unk2 = two`, gcc may fold two into the store (making it `sh v0,2(s0)` with v0=li 2). The register for the constant is chosen by local-alloc/reload. 

Let me look at the actual RTL? That's deep. Let me instead try a bunch of spellings empirically.

Let me also reconsider: maybe the register swap and the store sink are BOTH fixed by a single move: a `do-while` or a different structure. Let me try wrapping the first block in a do-while, or the whole function.

Let me generate a bigger batch:
- v_two_s8, v_two_u8
- v_block_dw: wrap the first block in do-while
- v_whole_dw: wrap the whole function in do-while
- v_two_dw: two var + do-while around the unk2 store

Let me test.

Actually, the register swap: let me look at the target once more. Target: `lw v0,32(s0); li v1,2; sh v1,2(s0); sh zero,52(s0); sh zero,20(v0)...`. So p=v0, two=v1. Mine: `lw v1,32(s0); li v0,2; sh v0,2(s0); ... sh zero,20(v1)`. 

What if the order of the stores matters? Target stores unk2 (sh v1,2) then unk34 (sh zero,52) then p stores. Mine same order. So only the regs swap.

Let me try making `p` a variable that's born at the SAME time as two or later, but with more refs. 

Actually — what if I make `p` used in the `two` computation, creating a dependence that forces p into v0 first? E.g., `two = p ? 2 : 2`? adds compare. No.

What if `two` is derived from p's low byte? Wrong value.

Hmm.

Let me just try the batch and see.

Actually, let me reconsider whether the register swap is worth cracking. If I can't, item 4 is a WALL. The best is 8. That's fine for a WALL.

But let me give it a solid 20 min. Let me test the batch.
