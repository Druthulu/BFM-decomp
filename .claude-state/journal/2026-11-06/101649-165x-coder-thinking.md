---
ts: 2026-11-06T17:16:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f5IlNq1S3a7z1KnirGQX
---
Still 21. Time: 10 min. Let me try the "reorder the packets" idea, which changes which constant competes:

g1: move the p2 block (0x8E) to the END (after p5). The instruction order changes → the target's bytes are in p0..p5 order, so this won't match even if the mask gets t6. But if it fixes the mask and breaks only the order, the score would be much higher. Not useful.

Better: reorder the *statements within* the p2 block so the constant store moves later/earlier. The target's instruction order is fixed; sched1 reorders anyway.

Alternative: change the mask's *use* to the second operand position in the and? The target has `and v0,v0,t6` (mask second). Mine has `and v0,v0,t7`. Same position.

Hmm.

Let me try: make the mask constant have a different value that requires the same insns but... no.

What about giving the mask a *type* that makes qty_size 8? no.

At this point, let me check one more hypothesis: maybe the mask gets t7 because t6 is occupied by the 0x8E constant *at the mask's birth in the chain*, and the allocation order is actually by *chain position* (not priority) for qtys that are "born" during the allocation scan? local_alloc does a pre-pass `block_alloc` per block, which scans insns and allocates on the fly? Let me read local-alloc.c's block_alloc: it collects qtys in `reg_qty` via `reg_is_born` as it scans, then after scanning the block sorts by priority and allocates. The priority is qty_n_refs etc.

Hmm, but maybe there's a special rule: `qty_phys_copy_sugg` for constants? Let me look at how constants are handled in local-alloc: there's `qty_const` — `if (reg_equiv_constant[regno]) ... qty_const[qty] = ...`. Registers that are equivalent to constants are marked `qty_const` and local-alloc does NOT allocate them (they're rematerialized at reload). But our mask IS allocated (it appears as a real lui/ori in the output, which is the rematerialization!). Wait — maybe the mask is NOT allocated a register at all; it's rematerialized at each use? No, it's materialized once and reused (and v0,v0,t7 12 times).

Hmm, but if the mask were `qty_const`, reload would rematerialize it at each use (12 lui/ori pairs) — not the case.

OK, let me look at this from the "what did the original source look like" angle. The comment says the pin was added because "the 0xFFFFFF mask lands in $t7 and the 0xE100008E constant in $t6 -- the target has them the other way round". So the previous decomp author faced exactly this and pinned. The task now asks for a lever-free crack. Maybe there IS one, but it's hard.

One idea: make the 0xE100008E constant *not* a pseudo by using a different store type: e.g., `*(u32 *)(p2 + 4) = 0xE100008E;` vs the current `*q2 = 0xE100008E;` where q2 is a u32*. Same.

What if we write the constant store as two 16-bit stores? Changes bytes.

What if the constant is stored via a *memory-to-memory*? no.

Let me try: make the six constants *not hoistable* by giving each a second use that's free. For 0x8E: `*q2 = 0xE100008E;` — what if we also use 0xE100008E elsewhere where it's free? Nowhere.

Alternatively, make the 0x8E constant's store happen *before* the mask's birth in the chain... it does (the store is at UID 170, before the mask's def at 571), but the mask's live range starts at 429 (the first and). Hmm, the constant's use at 170 is before 429, so they DON'T conflict in UID terms! Then the mask could take t6 (free after 170) — but it didn't.

Unless the mask's live range actually starts at its def (571) and the ands at 429 are... wait, the ands at 429-549 use the mask BEFORE its def (571)? That's impossible in the chain unless sched1 moved the def earlier. The chain order after sched1 has the def before the ands; the UIDs are stale. The lreg dump prints the RTL in chain order with UID numbers. So the mask's def is in the chain before the ands, and the constant's store is also before.

Then their live ranges in *chain order*: constant def (chain pos ~5), store (chain pos ~76); mask def (chain pos 16), ands (146+). They overlap? The constant's live range ends at 76, the mask's starts at 16 — overlap 16-76. So they conflict.

If the constant were materialized closer to its use (after 76), no conflict. sched1 hoists it.

What if we make the constant's use *immediately* after its materialization by putting the store in a position where sched1 can't hoist? Hard.

Alternatively, make the mask materialize *after* the constant's death (after insn 76) — but sched1 hoists it to 16.

Hmm! What if the mask's definition is placed such that sched1 cannot hoist it above insn 76? E.g., make the mask's computation depend on something that's defined late. Like `m24 = (u32)(*ot | 0xFFFFFF);`? That changes the value/instructions.

What about `m24 = 0xFFFFFF & ~0;`? folds.

What if m24 is computed from `ot`: `m24 = (u32)ot & 0xFFFFFF;`? Wrong value.

I'll stop. Let me record a WALL for item 3 (best 21). But I need ≥20 min and ≥30 tries. Currently ~10.5 min and ~30 tries (let me count: orig, nopin, a1(×2), a2,a3,a5,a6,a7,a8,a10,b1,b2,c1,c2,c3,c4,d1,d2,d8,d9,f1,f2 = ~24). Let me do 10 more minutes of tries.

Let me try a broader random-ish set of C changes around the tail and the mask:
- Use `u32 m24` but assign via `m24 = 0xFFFFFFUL;`
- Split the tail into two halves with the mask re-assigned in between (2 pseudos with 6 refs each).
- Reorder the 12 tail statements (interleave unk0 and *ot differently).
- Compute the mask as `0xFFFFFFFF >> 8`.
- Use `m24` in the `& 0xFF000000` too? no.

Actually, here's an idea I haven't tried: the mask could be declared as a *static/global* const? no.

Another: make the mask's uses go through a *pointer*: `u32 *pm = &m24;` then `& *pm`? extra.

Let me try the two-halves idea (g3) and a couple more.
