---
ts: 2026-10-22T21:54:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pjgk2HoQB4zlEmDtR2qL
---
In the base (with the barrier), the barrier insn (insn 67, ref_count 17, priority 3) is present. Note insn 67 has ref_count 17 — that's probably the asm insn with many deps.

The key: in the base, the order launched (bottom-up) is: ..., 72 (T-18), 70 (T-19), 67 (T-20), 65 (T-21), 58, 57, 55, 52...

So insn 67 (the barrier) sits between 70 and 65 — meaning the stores (55,57,58) are launched at T-22..T-24, i.e. earlier in time (later in program order... no wait).

Bottom-up: launched at higher T = placed earlier in the block. Order of placement (program order) = reverse launch order:
36 (T-32) first, 39 (T-31), 41 (T-30), 42 (T-29), 44 (T-28), 47 (T-27), 52 (T-26), 55 (T-25), 57 (T-23), 58 (T-22), 65 (T-21), 67 (T-20), 70 (T-19), 72 (T-18), 79, 84, 89, 95, 92, 102, 107, 109, 110, 117, 120, 123, 125, 127.

So the barrier (67) is between 65 and 70. And the stores 55, 57, 58 are BEFORE 65 (the lh) in program order!

Hmm, that means in the base the stores are before the lh?? But the target has them after the lhu...

Wait, maybe I have the insn numbering wrong. Let me identify the insns. Insn 47 ref_count 13 — hmm.

Let me look at the .sched dump's insn bodies. The -dS dump lists insns with their patterns? The .sched file has the per-block scheduling but the insn bodies are in the .rtl/.lreg dumps.

Rather than decode, note the structural difference: in the base there are 2 more insns (67 barrier, and something else) and the ready-list dynamics differ.

Let me try a different approach: compare the *final* asm of base vs target — they match (score 0 in tree). So the base's sched1 output is the target's.

In the base, insn 67 = the barrier. Its position: after 65 and before 70.

Hmm OK. So the barrier sits in the middle. The stores 55/57/58 are before the barrier and before 65.

I'm not going to decode this reliably in reasonable time.

Alternative plan: think about what plain C creates a "blocking" insn like the barrier at that position. The barrier is a zero-width insn with no outputs but many deps (ref_count 17). 

Hmm, in gcc 2.7.2, `__asm__("")` without operands becomes `(insn (asm_input ("")))`? A zero-width asm is kept as an insn.

Plain C has nothing like it.

Let me try yet another angle: maybe the -0x60 store group is placed after the lhu if the group has a *memory dependence* on the table load. The table load is `D_801944F4[...].f6` — a load from the table (a global symbol). If the stores wrote through a pointer that could alias D_801944F4, sched1 would order them.

Idea: declare a pointer `s16 *p = (s16 *)D_801944F4;` and store via `p[...]`? changes the asm.

Hmm, what if the stores are written with the value read from the table? no.

Let me look at this from a different perspective: what if I make the -0x60 group come after the -0x80 group AND rely on the LAW-1c style reversal... no.

Time to consider the cost/benefit. It's 15:55, item 4 at 7 min. I've done 31 tries. I could WALL now with best 15, or invest 10 more minutes.

Let me try a few more creative variants:

p1: Use a `do { } while (0)` around the -0x60 group (loop shape) — might make sched1 treat it differently. It's a plain C move (loop shape). Requires the !FAKE comment? That rule is about the src tree's fakes. I'll include the comment for clarity. But is it a "lever"? `do{}while(0)` is listed as acceptable in prior moves ("do { } while (0)" used in T10 examples as a real C move). Let me try it.

p2: Put the -0x60 group in an `if (v1 >= 0 || v1 < 0)` — adds insns.

p3: Reverse: make the -0x60 stores the LAST statements (after the v1 stores and the Blk8 copy) — j2 (26).

p4: make the -0x60 group use the same li as... 

p5: Write the -0x60 group with `D_80126976 = -0x60, *(s16 *)&D_80126970 = -0x60;` comma — same.

p6: Write the stores as `*(s16 *)&D_80126976 = -0x60;` and `*(s16 *)&D_80126970 = -0x60;` where both are u16 globals → 2 lis? The comment says casting the lvalue avoids a second li.

Let me try p1 (do-while) and a couple more, then decide.

Actually — here's a much better idea! The barrier's role: it pins the table read + index arithmetic ABOVE the stores. What if I make the index arithmetic *depend on a value produced after* the stores... no.

Alternatively: what if I make the -0x60 stores depend on the *Blk8 copy's* load? The Blk8 copy reads D_801944F4[...] too. If the -0x60 stores came after it, the schedule would differ (j2=26).

Hmm.

What about making the whole store group depend on `v1` via the `at` register... no.

Let me try p1 (do-while), p7 (an `if (v1 == v1)` wrapper?), p8 (reorder the two -0x60 stores with the -0x80 group in a way that keeps the asm order but changes RTL order: 76, 70, 7A, 74 is current; try 70, 76, 74, 7A — the LAW-1c reversal trick!).

The LAW 1c note says: gcc emits the PAIR of `sh $v1` stores in REVERSE source order, so the source must be 62 then 6A. Maybe the same applies to other pairs. Let me try source order 70, 76 (reverse of 76, 70) — m2 tried that (15, same).

OK let me try p1 and then WALL.

Actually, wait. Let me reconsider the problem: the target's insn order after the lhu is: li -96, lui, sh, lui, sh, li -128, lui, sh, lui, sh, lui, sh v1, lui, sh v1, then the second lh chain.

In mine: lh, li -96, lui, sh, lui, sh, sll, addu, sll, lui at, addu at, lhu, li -128, ...

So the -0x60 group is placed BEFORE the index chain. Since sched1 is bottom-up, placing an insn "before the index chain" means it was launched LATER (higher T) than the index chain.

For it to be launched earlier (placed after the chain), its priority must be higher or it must be ready earlier.

The index chain insns (sll/addu/sll) have priority 2-3 and depend on the lh (which is blocked by the load delay). The store group has priority 2-3 too.

Idea: raise the store group's priority by increasing its ref_count? Priority in sched1 = length of the longest path to the end of the block. The stores are near the end of the block already (priority 2-3).

Hmm, actually: priority = the critical path length. The stores' path to the block end is short. The index chain's path to the end is longer (it feeds the lhu and then the v1 stores).

In the target, the stores ended up after the lhu — i.e. the scheduler put them at the point where they were ready and the higher-priority insns (index chain) went first.

So if the store group had a LOWER priority (shorter path), it'd be deferred. Their priority is already low.

OK so why does mine put them right after the lh? Because at that moment the index chain was blocked (load delay) and the scheduler had to fill the slot with something — the li -96.

In the target, the barrier prevented the stores from being available at that point at all.

So: I need to make the store group unavailable early. The only way in plain C: a dependence on something scheduled late.

What if the stores depend on the `lhu` result (v1)? The v1 stores already do (they're after). If the -0x60 stores also depended on v1, they'd be forced after the lhu.

Value-preserving dependence on v1 that the compiler can't fold... Hmm.

What about a *memory* dependence: make the -0x60 store address depend on a load? no.

What if the -0x60 value came from `(s16)(v1 * 0x0 - 0x60)`? Folds at tree level? `v1 * 0` → 0. gcc 2.7.2's fold does this.

What about `(s16)((v1 & 0x80000000) >> 31) * -0x60`? no, that's not -0x60.

Hmm, what about a division/multiplication that the folder can't prove? Like `(s16)(0x100000000LL...` no.

What if I use a function of v1 that is constant but not foldable, e.g. `v1 == v1 ? -0x60 : -0x60`? folds.

OK. What about a *type-punning* dependence: store to a union whose other member was read from the table? 

Actually, here's one that might work: make the stores' ADDRESS depend on the table read. E.g.:
```
s16 *p = (s16 *)((u8 *)D_80126970 + (v1 & 0));
```
`v1 & 0` folds to 0.

Everything folds.

Hmm, what about using the `at`-clobber idea at the RTL level: the address is `(mem (symbol_ref))`. Two stores to different symbols can't be reordered across... they're independent.

Let me just try the do-while and a couple of wild ones, then WALL. Time: 15:56.

Actually, let me reconsider the "structural" trick from item 3: init at decl. No decl here.

Hmm — what about making the -0x60 group part of a *compound literal* assignment? e.g.
```
*(struct { s16 a, b; } *)&D_80126970 = (struct {...}){-0x60, -0x60};
```
That would emit a copy — different asm (2 sh from a temp). Hmm, actually it could emit exactly `li v0,-96; sh v0,0(at); sh v0,2(at)` — but the target has separate symbols for 70 and 76 (different lui at each). So no.

Let me do the last batch: p1 do-while, p2 reorder with the v1 stores first (j8=15), p3 `if (1)`? no.

I'll do p1 and then WALL.

Actually, one more idea worth a shot: put the -0x60 group BEFORE the `v1 = ...` read but AFTER the barrier position... there's no barrier. If the stores come before the table read in source, sched1 might place them before the lh — the target has them after. No.

Let me try p1.
