---
ts: 2026-11-06T06:33:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NZwdzgjK4swoCeJycNbN
---
In w0, the compiler hoisted the `lw a2,0(a2)` (D_800A5E60 load) BEFORE the division (mine[70-72] vs target[88]). That's the key: the launder forces the load after the div.

Wait, mine has `lw a2,0(a2)` at 71 then `lw a1,20(sp)` at 72 — the load of D_800A5E60 happens before the div. So the compiler moved `pkt = D_800A5E60` before `mulc = mulc/(g.otz*4)`.

Hmm, but the *source* order has the division first. Why would gcc hoist the load? Because `g.otz` is a stack variable and D_800A5E60 is a global; no aliasing issue (stack vs global). The scheduler (sched1) might hoist it.

Actually, in the target, `lw a3,0(a3)` is after the div (6d3c). In mine, `lw a2` is before. So the difference is scheduling.

To fix in real C: make the load depend on mulc? Hmm, e.g. `pkt = D_800A5E60 + (mulc & 0)`? That adds insns.

Or make the division's result feed into the address? No.

Hmm, the launder's memory output on D_800A5E60 prevents the load from moving above it (a store to the same location must precede the load). That's the mechanism: the asm *writes* D_800A5E60, so the load can't be hoisted above the write.

Real-C equivalent: a real store to D_800A5E60 before the load that is dead (overwritten by the later store). E.g.:

```
D_800A5E60 = D_800A5E60;   /* dead store? */
```
That's a load+store: 2 insns, and the load would be hoisted... The store would be `sw` to D_800A5E60 — an extra insn. Target doesn't have it.

Hmm, what about writing `D_800A5E60 = pkt + 0x28;` where pkt is loaded... that's the existing store, which comes after.

Hmm, what about the C0414 dead-reset: `pkt = 0;` — a dead store to the *local* pkt, deleted by cse; doesn't affect D_800A5E60.

What about making the division's denominator and the pkt load interact: e.g. 
```
mulc = mulc / (g.otz * 4);
pkt = D_800A5E60;
```
The load is already after. The scheduler hoists it. What if we make the load depend on mulc? e.g. `pkt = D_800A5E60 + (mulc & 0);`? adds andi.

Hmm, what if we make the division's *result* an input to the address: no.

OK, this item is harder. Let me first look at what else is wrong: the register pairs a0->v1 x7, v1->t1 x4, v1->a0 x4 — lots of register differences, plus missing 5 insns.

Hmm, the missing insns: mine[67:68] target[67:86] — the whole mulc computation block (19 insns) is MISSING in mine at that point and appears later at 103-123. So it's a *scheduling/order* difference (the mulc chain moved).

This is a big residual. 96 ins but 68 score. Hmm.

Wait — that's because the launder also anchors the mulc computation: the asm's "r"(mulc) input forces mulc to be computed and in a register right there. Without it, the mulc computation sinks below the packet stores.

Real-C move: make mulc used earlier... e.g. `w = mulc;` — but the source has `w = mulc` after the packet stores.

Hmm. What if the division were computed later in the source? No, we need the same insns.

This is the classic "sched1-birth-boost"/"sched1 sinks the chain" problem. The moves.md has "sched1-birth-boost" walls.

Let me think: the target computes mulc (div etc.) right after the flag test, then the packet stores, then uses mulc at `w = mulc` (move a2,a1 at 6dc8).

In w0, the compiler sinks the whole mulc chain to after the packet stores. To keep it up, we need something that uses mulc early.

Real C: assign mulc to another variable early? That's a copy.

Hmm, what if `w = mulc;` is moved earlier in the source? Then w would be assigned early — the target has `move a2,a1` at 6dc8 (in the beqz delay slot) which is the `w = mulc` copy. So w is assigned late in the target.

Hmm.

What if the division is written differently so it can't sink? E.g. use the result in the packet stores... no.

OK, this item looks hard too. Let me consider: maybe there's a systematic crack. Let me look at the *other* items first to see if they share the pattern — the two 307/308 items are in ov_SC06_018 (same TU as each other).

Hmm, but time. Let me spend a bit more on this one since it's smaller.

Actually, let me try the simplest real-C replacements for the launder first and see the scores:

1. Remove the asm entirely: w0 = 68.
2. Replace with `D_800A5E60 = D_800A5E60;` (a real load+store).
3. Replace with `pkt = D_800A5E60; D_800A5E60 = pkt;` then the existing code? That'd be a store.
4. Replace with a do-while(0) around the division.
5. Move the division after the pkt load in the source (reorder) — maybe the scheduler then produces the target order.

Option 5 is interesting: if the compiler sinks the div anyway, writing the source in the sunk order might... no, we need the div BEFORE the stores.

Hmm, what if we write the div *inside* a do-while(0) that also contains... 

Let me look at the target order: div at 6d0c, then the pkt load at 6d3c. In w0: pkt load at 71, div at 106. So gcc moved the pkt load up and the div down — they swapped. 

What if the pkt load were made to *depend* on mulc? For example:
```
pkt = D_800A5E60;
```
→
```
pkt = D_800A5E60 + (mulc - mulc);
```
folds.

What about using mulc in the store: `D_800A5E60 = pkt + 0x28;` — no.

Hmm, what if the division result `mulc` is stored into `g` (a struct) — no.

Let me look at the source again:
```
mulc = D_80126950 * 48;
mulc = mulc / (g.otz * 4);
__asm__ (...);
pkt = D_800A5E60;
D_800A5E60 = pkt + 0x28;
```
Real C alternative that forces the div before the load: 
```
mulc = D_80126950 * 48 / (g.otz * 4);
```
Same.

Hmm, what about making `g.otz` and the load interact: the div reads `g.otz` (a stack slot, 20(sp)). The pkt load reads a global. sched1 hoisted the global load above the div because the div has a long latency? Actually sched1 would schedule to hide latency.

To prevent hoisting: add a dependency. E.g. `pkt = D_800A5E60;` after a store to something that may alias D_800A5E60. The asm's "=m" is exactly that.

Real C: a *store through a pointer* that might alias D_800A5E60. For example, if we write `*(s32 *)&g = mulc;`? That stores to g (a stack slot) — the compiler knows g's address doesn't alias D_800A5E60? Actually a store to `g` (address taken) could alias anything? No — g is a local whose address is taken, but gcc knows it's on the stack... it can alias any *global*? No, stack objects can't alias globals (different address spaces in gcc's alias analysis — actually gcc's alias analysis for a stack slot vs a global symbol: a stack slot's address is &g, which can't equal D_800A5E60's address; gcc uses `alias` sets).

Hmm.

OK, what about a store to `*arg3`? arg3 is a pointer parameter that could alias D_800A5E60! E.g. `*arg3 = i + 1;` at line 24 — that's a store through arg3, and the compiler kept it early.

What if we add a store through a pointer that the compiler can't disambiguate from D_800A5E60, right before `pkt = D_800A5E60;`? But it must be dead-code-free and not add an instruction... it would add an instruction.

Hmm.

OK, so the launder here is a "memory barrier" style lever. The real-C replacement for a memory barrier is... a store. Which costs an insn.

Hmm, but maybe there's a real store already in the code that could be moved: `D_800A5E60 = pkt + 0x28;` — if we swap the order:
```
pkt = D_800A5E60;
D_800A5E60 = pkt + 0x28;
```
already.

What about:
```
D_800A5E60 = D_800A5E60 + 0x28;   /* store first */
pkt = D_800A5E60 - 0x28;          /* load after */
```
That's: lw; addiu; sw; then lw again; addiu — 5 insns vs target's 3 (lw, addiu, sw). No.

Hmm.

OK, let me look at the other items before sinking more time. Actually, let me reconsider the value of a systematic approach: these 5 items are all "launder,pin" from the same rung-B wave (t8_mac1/tus10). The pins and launders were added by the bank because the original bodies didn't match. Removing them requires finding the original structure.

Given the difficulty, maybe all 5 will be WALL/PARTIAL. The brief accepts WALL with evidence. But it also says "Budget 20-30 min wall per item".

Let me be pragmatic: for each item, try the standard replacements for the specific lever kinds, score ~10-30 candidates, and record the best (PARTIAL if a lever subset reaches 0, else WALL).

For item 2, let me try:
1. w0 (both gone) = 68
2. pins only gone (launder kept) — should be 0? Let me check: if the pins are the only problem, keeping the launder might score 0 → PARTIAL:launder. Let me test that first — it's the easiest win.

Let me create p0 = orig with pins removed, launder kept.
