---
ts: 2026-11-06T11:58:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_khl224WWOcGm33PeHOKl
---
p2 residual (8):
1. The `lui a1; addiu a1` (address of D_800AE620) is emitted early in mine (positions 3-4) but later in target (9-11). One insn-count difference? No: mine 93 vs target 94. Hmm, mine is missing one insn.

2. Target has a `nop` at 53 (load-delay) and `sh v0,14(s3)` at 54; mine has sh at 55 and no nop.

So mine is missing a nop (93 vs 94) and has an extra/moved address materialization.

Interesting: with barriers kept (orig), the address materialization `lui a1; addiu a1` is later (target). Removing the barriers lets sched1 hoist it to the top.

So p2 is close: 8. Real-C moves might fix the address hoist and the nop.

The `&D_800AE620` address: `register Blk20 *s __asm__("$5") = &D_800AE620;` — pinned to $5 (a1). The address materialization is lui+addiu. In target it's at 9-11 (after some prologue); in mine at 3-4.

Hmm, in mine the pin $5 forces the address into a1 early. Target also has a1... target:
```
7: lw s2,32(s3)
9: lui a1,0x0
11: addiu a1,a1,0
```
mine:
```
3: lui a1
4: addiu a1
...
10: lw s2,32(s3)
```

So the address materialization is born earlier in mine. This is the sched1 birth order. Real C: move the first Blk20 block later in the source? It's already after obj/ent.

Hmm, the first barrier was between obj and ent, and the second between ent and the Blk20 block. Removing them let sched1 move the address up.

What real-C move could delay it? Declaring `s` later, or making the block conditional... Or using the address in a way that's born later.

Idea: keep the launder (it's the kind we keep for PARTIAL) — the launder is in the block. So we can move the whole block later, e.g. after `ang = ...`? But the block computes blk before RotMatrixZ(ang, &blk). Moving it after `ang = ...` might be fine semantically.

Let me try a few:
- p2a: move `ang = ...` before the first Blk20 block.
- p2b: move the `vec[0..2]` assignments before the block.
- p2c: use a temp for the address: `Blk20 *s = &D_800AE620;` outside the block? The pin is inside.

Since the pin $5 (a1) must stay? Pins are other-kind levers — may stay or go. Let me try without the $5 pin too.

Also the missing nop at 53: after a load, sched1 filled the slot in mine. The target's nop is between two insns around `sh v0,14(s3)`. Let me get more context: target[53:55] = nop, sh v0,14(s3). Mine has sh v0,14(s3) at 55.

Hmm.

Let me try the reorder experiments. ~6 candidates.

Also, maybe removing the launders in a *different* real-C way could work (v0 = 75 is bad; the launder removal loses the `q` temp and s's register). Actually p1 (barriers kept, launders gone) = 69 — the launders matter hugely because the launder forces `s` (the pinned $5/$7 pointer) to be a register.

Wait: the launder `__asm__("" : "=r"(s) : "0"(s))` forces s into its pinned register $5. Without it, the compiler can use the address directly in loads (lui/addiu folded into the lw offset) — hence the code explosion? Actually with `register Blk20 *s __asm__("$5")`, the pin alone should force a1. Hmm, but removing the launder made 109 insns vs 93.

So for a MATCH we'd need to replace the launder's effect. The effect: s is a real register variable holding &D_800AE620, used for 8 loads. Without the launder, gcc's cse/regalloc might merge s with the address computation... but the pin should still hold it in $5. Yet 16 extra insns appeared — maybe because the compiler used the address differently (e.g. each load through a new lui/addiu? no).

Let me look at v1's diff briefly... it's 75 with 110 insns. Given time, the PARTIAL:launder path (p2=8) is more promising.

Let me try the p2 reorder batch.

Item 3 started ~8 min ago. Let's spend ~10 min.
