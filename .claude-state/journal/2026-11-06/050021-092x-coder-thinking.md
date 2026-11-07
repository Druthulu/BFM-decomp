---
ts: 2026-11-06T12:00:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xMvEqHHHS2Lf54AXkb59
---
Still 8 best. The residual is the hoisted address materialization (and the missing nop).

Wait — maybe the hoist isn't the real problem; the score is 8 and the diff showed a delete of 2 insns at the top and an insert at 9. That's a 3-instruction displacement = 6 mismatches? plus the nop.

Let me reconsider: could the missing nop be the key? mine 93 vs target 94: target has a nop at 53.

Hmm, since p2 keeps the launders, the launders' asm insns are real scheduling barriers (asm can't move). Removing the memory barriers (5 of them) changed only the address hoist.

Real C move to stop the address hoist: hmm, what if we make the address computation textually *inside* the first statement that uses it, e.g. `((Blk20 *)&D_800AE620)->w[0]`? That's what the source would be without s. But s is needed.

What if `s` is declared with the pin at function scope and assigned right before the block (h) = 41 (worse).

What if the obj/ent loads are made "more important" by using them immediately? E.g. use obj in a computation before the block: the code uses obj only at the end. 

Honestly, this looks like another wall: `sched1-birth-order` / address hoist.

Given the time (item 3 ~25 min), I need to satisfy ≥30 tries for a WALL. Current tries for item 3: v0, v1, p1, p2, p2a-d (4), gen6 (9) = 16. Need ~14 more.

Let me run one more batch of ~16 lever-free (v0/v1-based) variants to be thorough, then record WALL with best = 75? Wait — best lever-free is v0/v1 = 75. Hmm, that's the WALL best.

Hmm, but hold on: is v0 really "lever-free"? Yes (barriers+launders gone, pins kept). Score 75.

Hmm, that's a poor best. Let me reconsider whether the launder can be replaced by real C. The 16 extra insns = 8 loads × 2 address-materialization insns. If I can force s into a register with real C:

Idea: use a volatile pointer? `Blk20 *volatile s = &D_800AE620;` — volatile forces the variable to be stored/loaded (extra stack traffic) — probably worse.

Idea: make s a *parameter-like* local modified: 
```
Blk20 *s;
s = &D_800AE620;
```
Same.

Idea: use the pointer in an opaque way: `s = &D_800AE620; if (s == 0) ...`? adds a branch.

Idea: `Blk20 *s = (Blk20 *)&D_800AE620; s->w[0]...` with `s` also used in a call: `func(s)`? no.

Hmm, what if the loads go through a struct copy: `blk = D_800AE620;` — a single struct assignment! That would emit 8 loads + 8 stores in one go (like the target's 8 loads + 8 stores). The target does exactly that: 8 lw from a1, 8 sw to the stack, in order w[0..7]! That's what `blk = D_800AE620;` would generate.

But the target's code uses t0,t1,t2 rotation (lw v0/v1/a0; sw) — a struct copy! Yes: `lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); sw v0,32(sp); sw v1,36(sp); sw a0,40(sp); ...` — that's a block copy with 3 registers.

So the real C could be `blk = D_800AE620;` — and the second block `blk = D_800AE620;` again. The t0/t1/t2 rotation is the compiler's copy idiom.

Let me test that! v2 = v0 (no barriers/launders) with `blk = D_800AE620;` instead of the 8-load loop, in both places. This is a real C move (struct assignment, pointer reuse).

Also test with the pins removed (the pins $5/$7/$6 are on s/t2 which wouldn't exist).

Let me write v2.c with struct copies.
