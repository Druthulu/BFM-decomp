---
ts: 2026-10-22T00:15:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Rb3zNmWCLzBXmVZMKHUs
---
Close! 11 mismatches, all register transpositions: the target uses a2 where mine uses a0 (and v1 vs a0). The instruction count matches (177 = 177).

The difference: in the target, the address base (D_800A651C) is in a2, and the loaded value in a0; in mine, the base is in a0 and the value in v1.

The launder's removal changed the register allocation of the "bidx * 20" address computation.

The pattern: target: lui a2,0x0; addiu a2,a2,0; lhu a0,0(a2); lw v1,0(s1); lui a0,0xff00 ... hmm, wait the target at 130 is "lw v1,0(s1)" then 131 sll v0,a0,0x2, 132 addu v0,v0,a0.

So in the target, the address base is a2 and the lhu result is a0 (which is then masked with 0xff00 → a0 = bidx*20?). Hmm: "lhu a0,0(a2)" then "lui a0,0xff00"?? That overwrites a0. Let me re-read the target lines:

125 lui a2,0x0
126 addiu a2,a2,0
127 (equal, not shown)
129 lhu a0,0(a2)
130 lw v1,0(s1)
131 sll v0,a0,0x2
132 addu v0,v0,a0
133 (equal)
137 lui a0,0xff00
138 (equal)
139 and v1,v1,a0
143 lhu v1,0(a2)
154 and v0,v0,a0
157 lhu v0,0(a2)

Hmm, so a2 = the address of D_800A651C (lui a2,0x0; addiu a2,a2,0 → the symbol address), a0 = lhu result (bidx) initially, then reused for the 0xff00 mask constant. v1 = the loaded value from s1 (pv).

Mine:
125 lui a0,0x0
126 addiu a0,a0,0
129 lhu v1,0(a0)
130 lui a2,0xff00
131 sll v0,v1,0x2
132 addu v0,v0,v1
137 lw v1,0(s1)
139 and v1,v1,a2
143 lhu v1,0(a0)
154 and v0,v0,a2
157 lhu v0,0(a0)

So the difference: the symbol address base is in a0 (mine) vs a2 (target); the lhu result in v1 (mine) vs a0 (target); the 0xff00 mask const in a2 (mine) vs a0 (target).

So it's a local-alloc qty/priority difference: in the target the *address base* (long live range) gets a2, and in mine a0. Hmm, actually in the target the base is a2 and in mine a0. Both are "the same pseudo" with different reg.

The mask constant 0xff00: in the target it's a0 (reused after the lhu result), in mine a2.

So a0 ↔ a2 swapped, and the lhu result v1 ↔ a0.

This is the local-alloc ordering. The launder affected the priority of these pseudos (it changed REF counts / the birth boost).

Hmm. The launder here is out-only on pv: `__asm__ __volatile__("" : "=r"(pv));` — creates a 2nd set of pv (dead) that "kills the sched1 birthing boost".

In the target, `lw v1,0(s1)` is the load of pv (s1 = p? no, s1 is a saved register; pv is pinned to $3! Hmm: `register u32 pv __asm__("$3")` — pv is pinned to $3 = v1! So "lw v1,0(s1)" loads pv from memory into v1 = $3. Yes.

OK so in the target, pv (v1=$3) is loaded at 130 (after the lhu), while in mine it's at 137. Hmm.

The register difference for the address base: target a2 ($6), mine a0 ($4). The address base is a pseudo with a long live range (used at 129, 143, 157). In mine it got a0, in the target a2.

local-alloc assigns by qty (number of references) and life. Hmm, in the target the base has 3 refs (129, 143, 157) → a2; in mine the base also has 3 refs but got a0.

Wait, maybe the difference: in the target, a0 is used for the lhu result and later for the 0xff00 constant, so a0 has a short live range, while a2 holds the base. In mine, a0 holds the base and a2 holds the mask constant.

local-alloc in gcc 2.7 allocates to $2,$3,$4,... in order of priority: the highest-priority pseudo gets $2, etc. Actually gcc 2.7's local_alloc allocates hard regs starting from the highest ($7 = a3?) Hmm.

The upshot: the priority order of the pseudos in the block differs between mine and the target. The launder affected it.

How can I nudge this? Options:
- Change the source so the priority order matches: e.g. the order of the statements, or splitting an expression into temps (which changes ref counts).

The relevant expressions:
```
    bidx = (u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C + (*bidx * 20)), 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
Note `bidx` is `volatile u16 *` → the load `*bidx` is volatile, so it can't be CSE'd → two separate lhu loads (at 129 and 143). Good, that matches the target (two lhu).

The base address `&D_800A651C` appears twice (in the first store and in `ot = ...`). The compiler CSEs them into one pseudo (3 uses).

Now, with my split (`pv = pv & 0xFF000000;`), the code changed shape enough to alter the allocation. Maybe a different split would preserve the allocation. E.g. instead of splitting pv, split the *other* operand:

```
    *(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
where X = CAST_NONSTRUCT(...). Splitting X:
```
    t = CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C + (*bidx * 20)), 0x40);
    *(u32 *)p = (pv & 0xFF000000) | (t & 0xFFFFFF);
```
Hmm, but the "real 2nd set" was needed for pv specifically (to kill the birthing boost of pv).

Hmm, wait. Which pseudo's birthing boost matters? The comment says the out-only launder on pv "kills the sched1 birthing boost". The launder's output is a new pseudo (dead) — this creates a 2nd set of pv...

Hmm, in the target vs mine, the difference is in the allocation of the address base and the mask constant, NOT pv (pv is pinned to $3).

Let me think about the "birthing boost" more concretely: sched1 boosts the insn that *births* a pseudo (the first definition). The launder's output pseudo is born at the launder (the last insn of the function) — that kills the boost of... hmm.

Since the launder is at the END of the function (after the last call), its effect on the earlier scheduling seems odd. Unless the out-only launder's output pseudo (dead) affects the *last* set of pv (the load) — the boost of the "lw v1,0(s1)" insn (which births pv). The launder adds a 2nd set of pv (the asm output) — hmm, but the asm output is a *different* pseudo, not pv.

Hmm: `__asm__ __volatile__("" : "=r"(pv));` — the output is tied to pv (the "=r" output with the same variable). GCC creates a new reg for the output and ties it to pv's reg. So the "2nd set" of pv is the tie: pv's reg has 2 sets (the load and the asm output).

Effect: the load `lw v1,0(s1)` is no longer the *only* set of pv's register; the asm output is a second set (at the end of the function). This changes the live range of pv's reg: it now extends to the end of the function → the reg's live range is longer → in local-alloc, pv's qty/life changes. But pv is pinned ($3) so it doesn't matter for allocation... but it DOES matter for the *other* pseudos: a longer-lived pinned reg? no.

Hmm, but the observed difference is in the address base's register. Since the base (a2 in target) has 3 uses spread out, its live range is long; the local-alloc priority is by qty then life.

In mine, the base got a0 and the mask const a2. In the target, the base got a2 and the mask a0. So the relative priority of the base vs the mask constant flipped. The mask constant (0xff00) has 1-2 uses (short life); the base has 3 uses (long life). In gcc's local-alloc, higher qty (more refs) wins the earlier register. The base should win → it should get a0 (allocated first?) hmm, in the target the base got a2 ($6) and the mask a0 ($4). So in the target the *mask* won the earlier register, meaning the mask has HIGHER priority than the base in the target. In mine, the base won.

Hmm, that suggests the target's order is the opposite of what I'd expect. Whatever.

Practical approach: try a few source variants for this item and see which one scores 0. Variants:
(a) split pv (current) → 11
(b) split the other operand (X) instead of pv
(c) both
(d) different placement of the split (before/after the store)

Note the target's own structure: I should look at what the target code does with pv: "lw v1,0(s1)" at 130 — the load of pv happens at 130, i.e. AFTER "lhu a0,0(a2)" (129) and before the sll. In mine, "lw v1,0(s1)" is at 137 — after the lui a2,0xff00 (130). So the ORDER of the load differs too: in the target, pv's load is early (right after the lhu), in mine it's later.

Hmm, in the target, at 137 there's "lui a0,0xff00" — so the mask constant is materialized AFTER the pv load. In mine, at 130 "lui a2,0xff00" (early) and 137 "lw v1,0(s1)".

So the target's schedule: [base address] [lhu bidx] [lw pv] [sll/addu] [lui 0xff00] [and] ...
Mine: [base address] [lhu bidx] [lui 0xff00] [sll/addu] [lw pv] [and]...

So in the target, the pv load comes before the mask constant; in mine, after. This is the "birthing boost" thing: the lw (pv's birth) is boosted in the target? Hmm, no: in the target the lw comes FIRST (before the lui 0xff00), in mine the lui comes first. The comment says the launder "kills the sched1 birthing boost" — so without the launder (in mine), the boost is alive and the lui (0xff00) is boosted up. With the launder, the boost is killed so the lw stays earlier.

Hmm, so with the launder the *lw* wins; without it, the *lui* wins. The 0xff00 constant is the "match_scratch"/constant pseudo — a local-alloc constant. The moves.md wall tag "sched1-birth-boost: birthing-insn priority boost against a local-alloc constant" — exactly this!

So the fix must kill the birthing boost of the 0xff00 constant in plain C. The 0xff00 constant is a local-alloc constant (a pseudo with 1-2 uses). The birthing boost: the insn that births the constant pseudo (lui a2,0xff00) gets a scheduling boost.

How to kill it in plain C? By giving the constant a second set! E.g. if the constant 0xff00 is used in two places, or if it's assigned to a variable twice.

Hmm, in the source: `(pv & 0xFF000000) | (X & 0xFFFFFF)` and `(*(u32 *)(ot + 0x40) & 0xFF000000) | ...`. There are two 0xFF000000 masks! The first is on pv, the second on *(u32*)(ot+0x40). So the constant 0xFF000000 is used twice → gcc materializes it once (a pseudo with 2 refs) → the "lui" births it.

And 0xFFFFFF is another constant (used twice as well).

Hmm, so the constants have 2 uses each.

In the target, the order is: lhu, lw(pv), sll, addu, lui 0xff00, and... So the 0xff00 constant (the AND mask) is materialized after. In mine, before.

Hmm wait, "lui a0,0xff00" — the mask 0xFF00? The source has 0xFF000000 and 0xFFFFFF. 0xff00 = 0xFF000000 >> 16. So gcc materialized the constant 0xFF000000 as "lui 0xff00" (the high part) + "and"? Hmm, "lui a0,0xff00" then "and v1,v1,a0" — that's a 16-bit AND with 0xFF00?! That doesn't match `pv & 0xFF000000`.

Hmm: "and v1,v1,a0" where v1 = lw v1,0(s1) = pv and a0 = 0xff00 → result = pv & 0xFF00?? But the source says pv & 0xFF000000. Hmm, that means the 32-bit constant 0xFF000000 is materialized as lui 0xff00 (giving 0xFF000000) and the AND is a 32-bit and with a0 = 0xFF000000. Yes! lui a0,0xff00 → a0 = 0xFF000000. Right, lui loads the upper 16 bits into bits 31-16: 0xff00 << 16 = 0xFF000000.

So the constant pseudo = 0xFF000000, used twice (at 139 and 154).

In the target, the "lui a0,0xff00" comes at 137 (after the lw pv at 130) and in mine at 130 (before the lw at 137).

So I need the lui to be scheduled after the lw. The launder killed the "birthing boost" of the constant.

How to kill the boost in plain C? Give the constant a second *set* so that the birth is not the only one? Hmm, the boost is on the *birthing insn* (the first definition of the pseudo). If the constant has 2 sets, the first set is still a birth...

Alternatively: make the constant a *variable* with 2 sets:
```
u32 mask = 0xFF000000;
...
*(u32 *)p = (pv & mask) | ...;
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & mask) | ...;
```
Hmm, that gives the mask 1 set (the init) with 2 uses. The init is at the top of the function → the "lui" would be hoisted to the top → worse.

What if the mask is assigned twice:
```
mask = 0xFF000000;
... first use ...
mask = 0xFF000000;
... second use ...
```
That would emit 2 luis (2 insns) → count mismatch.

Hmm. What about the *order* of the two uses: the first use is at the first store, the second at the second store. If the constant's birth is boosted, it's hoisted to the top of the block.

Wait — what if we express the two masks differently so that they DON'T share a constant pseudo? E.g. write the second mask as `(*(u32 *)(ot + 0x40) & 0xFF000000)` and the first as `(pv & 0xFF000000)` — they share. If I write one of them as `~(x & 0x00FFFFFF)` (complement form) — different code.

Hmm. Alternatively: give the constant pseudo a 2nd set in a *real* way:
```
u32 mask = 0xFF000000;
mask = 0xFF000000;   /* no */
```

What about making the AND's operand a variable that is assigned from the constant:
```
u32 m = 0xFF000000;
*(u32 *)p = (pv & m) | ...;
```
Same.

Hmm, what about the *birth* being a different insn: e.g. if the constant is produced by a computation with 2 sets (like `m = 0xFF000000; m = m;`)... no.

Alternatively: maybe the launder's role here isn't about the constant's boost but about pv's. Let me re-read the comment: "zero-byte 2nd SET: kills the sched1 birthing boost". And the moves.md entry (G09's func_80184174 etc.): "launder->pv = *p; pv &= 0xFF000000 split (real 2nd set); pv $3 pin dropped; ang $4 pin kept (not row kind), pin-free 4".

In those cases the recipe was: `pv = *p; pv &= 0xFF000000;` — exactly my split (a) but with the order: first the load, then the mask. That's what I did. And it gave 11 here.

Hmm, but in those cases the "real 2nd set" was of the *masked* value: `pv = *p; pv &= 0xFF000000;` — the mask split creates a 2nd set of pv (the masked value) and the *store* uses pv directly. In my case I did exactly that: `pv = pv & 0xFF000000; *(u32*)p = pv | (...)`.

Hmm, but in the moves.md case, the load was `pv = *p;` (a load) and the mask `pv &= 0xFF000000;`, so pv has 2 sets: the load and the mask. In my case, pv = *(u32*)p (load), then pv = pv & 0xFF000000 (mask) → also 2 sets. Same.

And the result: 11 mismatches (register transpositions). The other shards' crack had "pin-free 4" as the best (i.e. they also had residual mismatches — the pin removal wasn't part of it). Hmm, in their case the row kind was "launder,pin" and the MATCH came from removing both.

For us, only the launder must go. The residual 11 is register transpositions: a0 vs a2 and v1 vs a0.

Let me look at the target vs mine more carefully:

Target:
125 lui a2,0x0
126 addiu a2,a2,0
129 lhu a0,0(a2)      ; bidx
130 lw v1,0(s1)       ; pv (pinned $3 = v1)
131 sll v0,a0,0x2
132 addu v0,v0,a0
137 lui a0,0xff00     ; mask
139 and v1,v1,a0      ; pv & mask
143 lhu v1,0(a2)      ; bidx again (volatile)
154 and v0,v0,a0
157 lhu v0,0(a2)

Mine:
125 lui a0,0x0
126 addiu a0,a0,0
129 lhu v1,0(a0)      ; bidx in v1
130 lui a2,0xff00     ; mask
131 sll v0,v1,0x2
132 addu v0,v0,v1
137 lw v1,0(s1)       ; pv
139 and v1,v1,a2
143 lhu v1,0(a0)
154 and v0,v0,a2
157 lhu v0,0(a0)

So the difference is: the address base pseudo got a0 (mine) vs a2 (target); the bidx load result got v1 (mine) vs a0 (target); the mask got a2 (mine) vs a0 (target).

Interesting: in the target, a0 is used for the bidx result AND later the mask constant; the base is a2. In mine, a0 = base, v1 = bidx, a2 = mask.

So the target's allocation: base → a2, bidx-result → a0, mask → a0 (reused). Mine: base → a0, bidx → v1, mask → a2.

Both use 3 regs. The target prefers a0 for the *short-lived* bidx result and a2 for the long-lived base. Mine gives a0 (the first/lowest?) to the base.

gcc's local-alloc: it allocates the pseudo with the highest priority to the first available hard reg. Priority = qty (number of refs) primarily, then life.

Target: bidx-result has 3 uses (129, 131, 132) — hmm, that's 3 refs, more than the base (3 uses: 129, 143, 157). Both 3.

Hmm, actually the base is used at 129, 143, 157 = 3 refs; the bidx value: 129 (dest), 131, 132 = 2 uses + 1 set.

The mask: 2 uses (139, 154).

In the target: bidx-result → a0 ($4); base → a2 ($6); mask → a0 (reused after bidx dies).
In mine: base → a0; bidx → v1 ($3!); mask → a2.

Hmm, wait: v1 is $3 — but pv is pinned to $3! So $3 is taken by pv. So the bidx result can't use v1 in the target; it uses a0 instead. In mine, the bidx result got v1 — conflicting with pv's pin? But pv's live range in mine starts at 137 (the lw) whereas the bidx result at 129-132 is dead by then. So in mine, v1 is free at 129-132 and gets reused for bidx, then pv takes v1 at 137.

In the target, the pv load is at 130 (early) so v1 is occupied from 130 on; hence the bidx result couldn't use v1 and took a0.

So the difference: the position of the pv load (130 vs 137) → which cascades into the register choices. And the pv load's position is the "birthing boost" thing.

So: the key is to make the lw (pv's load) come early — right after the lhu — without the launder.

The boost: "kills the sched1 birthing boost" — so without the launder, the *lui 0xff00* (the constant's birth) is boosted, hoisting it above the lw. With the launder, the boost is killed.

Hmm, why would the launder kill the constant's birth boost? Because the launder creates a new pseudo (the output) whose birth is the asm — and maybe the boost mechanism applies to "the pseudo born in this block" and the launder's output takes that slot? Hmm.

In gcc 2.7's sched1 (reorder), the priority function `init_priority` computes for each insn a priority based on:
- REG_N_REFS of the operands,
- whether the insn is the birth of a pseudo (in `rts_prio`),
Specifically, in gcc's `sched.c`, there's a notion: "an insn that sets a pseudo which is not live anywhere else gets a higher priority" — the "birth boost".

So: without the launder, the constant pseudo (0xFF000000) is born by the "lui" and the birth boost makes the lui early. With the launder, the launder's output pseudo is born at the end... hmm, that wouldn't kill the constant's boost.

Alternatively: with the launder, the *pv* pseudo has 2 sets (the load and the asm output) → the load is no longer a "birth" (the pseudo's live range starts earlier?) → the load isn't boosted → the load stays later?? But the target has the load EARLY (130). Hmm, so the load IS boosted in the target.

Confusing. Let me flip it: maybe the boost applies to the *lui* in mine because the constant pseudo is born there and the boost raises the lui above the lw. In the target, the launder's presence means the constant pseudo... hmm.

Whatever the mechanism, what matters: how to reproduce the target's order in plain C?

Target order: lhu(bidx) → lw(pv) → sll/addu → lui(mask) → and...
Mine: lhu(bidx) → lui(mask) → sll/addu → lw(pv) → and...

Wait, in the target, is the lw really at 130? The diff said:
```
  replace mine[125:127] target[125:127]
      125  lui	a0,0x0                         | lui	a2,0x0
      126  addiu	a0,a0,0                      | addiu	a2,a2,0
  replace mine[129:133] target[129:133]
      129  lhu	v1,0(a0)                       | lhu	a0,0(a2)
      130  lui	a2,0xff00                      | lw	v1,0(s1)
      131  sll	v0,v1,0x2                      | sll	v0,a0,0x2
      132  addu	v0,v0,a1                      | addu	v0,v0,a0
  replace mine[137:138] target[137:138]
      137  lw	v1,0(s1)                        | lui	a0,0xff00
```
So target[129]=lhu a0,0(a2); target[130]=lw v1,0(s1); target[131]=sll v0,a0,0x2; target[132]=addu v0,v0,a0; target[137]=lui a0,0xff00.

Yes: the target has the lw right after the lhu.

Hmm OK. So how do I get the lw early? The lw is `pv = *(u32 *)p;` — a load from p. The scheduling: the load is independent of the lhu (both from different addresses). The scheduler placed the lui(mask) before the lw in mine.

To move the lw earlier, I could make the lw *depend* on the lhu... no. Or make the mask constant's birth NOT boosted: give the mask constant a 2nd set! E.g.:

```
u32 mask;
mask = 0xFF000000;
*(u32 *)p = (pv & mask) | ...;
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & mask) | ...;
```
Here mask has 1 set (the init). gcc would CSE the init into one lui — same as now.

Alternatively, express the second mask differently so that the two masks don't share a pseudo:
```
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
This is the second use. If I write the FIRST mask as `pv & 0xFF000000` and the second as `*(u32*)(ot+0x40) & 0xFF000000` — they share the constant (CSE). To break the sharing, I could write the second one as `(*(u32 *)(ot + 0x40) & ~0x00FFFFFF)`. That's a different constant (0xFF000000 computed as ~0x00FFFFFF → probably materialized as "nor" or a different lui) → extra instructions? `x & ~0xFFFFFF`: gcc would compute ~0x00FFFFFF = 0xFF000000 as a constant — gcc's CSE would still merge it with the other 0xFF000000 (they're the same value). Hmm.

OK, different approach: what if the *order* of the two mask uses is swapped in the source? I.e. use the mask in the second store first? That changes semantics (the second store uses ot which is computed later). No.

Hmm. What about the *first* use: `(pv & 0xFF000000)`. If we split it as `pv = pv & 0xFF000000;` (my split) then the masked pv is used in the store. The mask constant is then used at the split point and at the second store. Its birth is at the split point, which is *before* the store but *after* the `ot = ...` computation? Hmm, in my source order:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;      <- mask birth here
*(u32 *)p = pv | (X & 0xFFFFFF);
ot = ...;
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ...;
```
The mask is born at the split (early) — same as before.

What if I move the split AFTER the first store? Not possible (pv is used in the store).

Hmm. What if the split is on the SECOND use instead:
```
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
ot = ...;
m2 = *(u32 *)(ot + 0x40);
m2 = m2 & 0xFF000000;      <- 2nd set of m2
*(u32 *)(ot + 0x40) = m2 | ((u32)p & 0xFFFFFF);
```
This gives the second masked value a 2nd set. But the launder was on pv, not on the second value. Hmm. But maybe the *effect* we need (killing the boost) can come from anywhere.

Hmm, wait. Let me reconsider. What if the launder's effect is: it makes the *pv load* NOT the birth of a pseudo? I.e. with the launder, pv's reg has 2 sets (the load and the asm output) → the load is not a "birth" → no birth boost on the load → the load is NOT boosted → it stays where the source order puts it... and in the target the load is EARLY (130) which is its source position (the load statement is before the store statement)!

And in mine, the load is LATE (137) — meaning it was *sunk* or the other insns were hoisted above it.

Hmm, so with the launder, the load stays in its source position (early), and without it, the load gets pushed down (137) while the lui (130) is hoisted.

Hmm, "kills the sched1 birthing boost" — the birth boost would push the *lui* (the constant's birth) up. But the comment says the launder kills a boost, and the launder is on pv...

You know what? Both readings are consistent with: with the launder, the *constant's* birth boost is killed (the lui stays late at 137); without it, the constant's birth boost pushes the lui up to 130, pushing the lw down to 137.

So the launder kills the CONSTANT's birth boost. How? The launder's output pseudo is born at the end of the function... Hmm, in gcc 2.7's sched1, the "birth boost" might be implemented as: an insn that sets a pseudo which is *not used before* gets +1 priority... no.

Let me look at gcc 2.7's source. The project's tools may include the gcc source (docs/gcc-2.7.2-map/sched.md was mentioned). Let me check for the scheduler docs: docs/gcc-2.7.2-map/sched.md. That would tell me the priority rules. Let me grep it for "birth".

That's a good idea — the cookbook/docs may explain the birth boost precisely.

Let me look.
