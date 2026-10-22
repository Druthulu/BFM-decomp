---
ts: 2026-10-21T23:42:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Lx8hbLrtkwcRiXTsgCFf
---
Now the diff is crystal clear. Differences:

1. Target: `move a0,s2` and `addiu a1,s0,12` appear EARLIER (before `sb v0,18(s0)` / `sb v0,26(s0)`), and `li v1,-160` is hoisted to that region. Mine has a `nop` there instead of `move a0,s2` (so mine has an extra nop = the 91st instruction), and the `move a0,s2`/`addiu a1,s0,12` come later.

2. Target: the -160 constant is in v1 and hoisted early; mine keeps it in v0 late.

3. Target: byte-12 load in a2, store `sb a2,42(s0)` at the same place as mine's `sb v1,42(s0)`.

So essentially: in the target, the scheduler hoisted `move a0,s2`, `addiu a1,s0,12`, `li v1,-160` earlier; and used a2 for byte-12.

The nop in mine at that slot: in the target, that slot has `move a0,s2`. So the difference is the scheduler's filling of the delay slot (the `lw v0,28(s1)` has a nop in its delay slot; in the target, the delay slot of that lw contains `move a0,s2`!). Look: target:
```
lw v0,28(s1)
move a0,s2     <- delay slot filled
sb v0,18(s0)
```
Mine:
```
lw v0,28(s1)
nop
sb v0,18(s0)
```
So the target's scheduler filled the delay slot with `move a0,s2` (the a0 setup for the AddPrim call, moved up). In mine, the a0 setup came later, leaving a nop.

So the target has these 3 insns hoisted into the byte-group area: `move a0,s2`, `addiu a1,s0,12`, `li v1,-160`.

Why would `move a0,s2` be hoisted? Because a0 (the call arg) is set early: in the target, a0=s2 is the first arg of the AddPrim(ot, p+0xC) call, and a1 = s0+12. These are call-argument setups that the scheduler hoists early (they're independent of the memory ops). In mine, the same setup happens but is scheduled later (after the byte group) because of a scheduling conflict (a0/a1 in use?).

Hmm! In mine, at the same region we have `move a0,s2` and `addiu a1,s0,12` — they ARE there, just 2 slots later. So the difference is subtle scheduling.

What blocks the hoist in mine? The register pressure: a0/a1 are call args; the scheduler's "sched1" has a limit on how far it can hoist. Hmm.

Alternatively, the whole thing might hinge on `li v1,-160` being hoisted: in the target, the li is early. In mine, it's late. Both `move a0,s2`/`addiu a1,s0,12` and `li -160` are hoisted in the target but not in mine. This suggests a general "the scheduler could not hoist these because of a dependency/pressure" in mine.

What differs? In mine, c1 is a pseudo (v0) that conflicts with the byte-12 pseudo (v1). The scheduler, when it considers hoisting `li -160` (pseudo c1), must check register conflicts: c1's live range overlaps byte-12's → they can't share a reg; the scheduler's "sched1" in gcc 2.7 uses `no_insns_scheduled`? Hmm, gcc 2.7's sched1 computes "deps" and also tries to avoid increasing register pressure.

Alternatively the hoisting of `move a0,s2` is blocked by a different conflict in mine: a0 is a hard reg ($4) in both. Hmm, but in mine a0 is used by the call `func_8005A600(p, 0, 0, tp, 0)` (a0 = s0 at 2680) — the same in both.

Wait: in the target, `move a0,s2` is at position ~55 (in the byte group) — before the `jal func_8005A600`? No, the jal func_8005A600 is at 2690, much earlier. So a0 is free after that.

The difference in hoisting `move a0,s2` might be a knock-on effect: in mine, the byte-12 load is `lw v1,28(s1)` vs target `lw a2,28(s1)`. The scheduler's decisions about a2 vs v1...

Honestly, this is a "one-thing-changed" puzzle: the whole tail region differs. The root cause is likely the c1 register: in the target c1=$3 (hard, from the pin). The pin affects the ENTIRE scheduling because c1's pseudo/hard-reg status changes the scheduler's choices (the target's `li $3,-160` can be hoisted, and the resulting freedom changes the rest).

So to match, I need the compiler to produce the same allocation AND scheduling. Without a pin, I need the pseudo c1 to be allocated $3 and to be hoistable.

Alternative idea: what if I make c1 a hard register by... no, that's a pin (not allowed).

What if c1 is eliminated entirely and the -160 is materialized as a constant in a way that the scheduler handles like a hard-reg constant? E.g. write the literal twice: `*(s16*)(p+0x14) = -0xA0;` — GCC would generate `li $N,-160` for each; cse would then merge them into one `li` + reuse. In gcc 2.7's cse, two identical constant sets in different regs... the second `li` would be replaced by a copy or the first's reg reused. Then the pseudo would be the same as c1's.

Hmm, but there's another route: what if the -160 constant is loaded as part of a bigger constant that cse/other passes keep? No, the target has `li v1,-160` exactly.

Let me think about the priority formula again: pri = floor_log2(n_refs) * n_refs * size / (death - birth). Shorter live range → higher priority. Also, "If this insn introduces a 'constant' register, decrease the priority of that register" — in update_equiv_regs, for a pseudo set once from a constant, the priority is decreased (reg_live_length *= 2 and there's more). Let me read that part to see exactly how the priority of constant pseudos is decreased, and how that interacts.

Let me read lines 1080-1200 of local-alloc.c.
