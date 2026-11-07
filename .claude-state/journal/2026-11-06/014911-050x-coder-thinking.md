---
ts: 2026-11-06T08:49:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yY73xah4DNoHb4YZfpHQ
---
18 minutes in. Budget 20-30 min per item. Let me be more systematic and try a batch of plausible real-C variants quickly.

Key hypothesis: we need (a) t3 live across h[0] (its store later or a real later use), and (b) t4→v1.

For (b): what if the fifth load is placed *before* the fourth store (source order: loads t0..t4 then stores)? c2 gave 46 insns. Hmm.

What if we write the fifth load as part of the h computation region? c3/c4 gave score 33/35 (order changed).

Alternative for (b): extend r84's life with a real use of `off` after the fifth load. What real C could use off after the load without adding an instruction? The call: `func_8012C51C(sp10, (s32)a0)` — could we pass something involving off? No, changes semantics.

What about using `off` as the *index* for sp10? Like `h = (u16 *)sp10;` no.

Hmm, wait. Maybe the real C is structurally different: perhaps `sp10` is not an array but five separate locals, or the D_ symbols are an array `D_801A5460[a1]` etc. Let me look at the symbols: D_801A5460, 464, 468, 46C, 470 — consecutive 4-byte globals. The source might be:

```
extern s32 D_801A5460[];
...
off = a1;
t0 = D_801A5460[off]; ...
```
with off = a1 and scaled addressing (a1*4 via sll)? But target computes a1*20 = a1*4*5, i.e., a1*20. With an array index a1*5? Hmm, the target computes sll v0,a1,2; addu v0,v0,a1; sll v0,v0,2 = a1*20. That's (a1*5)*4 — consistent with indexing an array of 5-word structs: `D_801A5460[a1*5 + k]`? Or a struct array.

Maybe the real C is: `off = a1 * 5;` and loads `D_801A5460[off]`, `D_801A5464[off]`... no, those are different symbols.

Actually, more likely: the five globals are declared as an array of 5 structs, e.g. `extern s32 D_801A5460[5][5]`? Hmm.

The original body uses `(char*)&D_801A5460 + off` with off = a1*20. The five symbols are 4 bytes apart, so they're one array of 20 s32? If the TU declares D_801A5460..470 as separate symbols, the C must reference each. So the source likely uses each symbol separately with the byte offset.

OK. Let me try a different tactic: use the "d1" style but keep t3's live range extended too. What if I write:

```
    t3 = *(s32 *)((char *)&D_801A546C + off);
    sp10[0] = t0; sp10[1] = t1; sp10[2] = t2;
    t4 = *(s32 *)((char *)&D_801A5470 + off);
    sp10[3] = t3;
    sp10[4] = t4;
```
This is c1 (46 insns, t3 still a2). Hmm c1 had the same regs as w1.

What if t3's store goes after h[0]? Let's test that (d2), and also after h[1] (d3):

d2:
```
    t0..t3 loads
    sp10[0..2] = t0..t2
    t4 = load
    sp10[4] = t4
    h = sp10
    h[0] = ...
    sp10[3] = t3;
    h[1] = ...
    h[2] = ...
```
Then t3's store is after h[0]; t3's live range extends across the fifth load and h[0]. This gives (a) and possibly (b) if r84's live extends? No, (b) is about the address temp, not t3.

For (b), note that in the target the fifth load is followed by a nop and store; v1 = t0's reg. What if the *source* reuses t0's expression? d1 failed.

Let me try: maybe assign the fifth load to `t1` (a0's reg)? Target's fifth load is v1, not a0. Hmm.

Wait wait. Let me reconsider (b): maybe v1 for t4 is not about the address temp but about the *store order*: `sp10[4] = t4` where sp10[4] is at sp+32. The store could be given a preference? No.

Let me look at the target more carefully: is `lw v1,0(at); nop; sw v1,32(sp)` maybe the result of t4 being loaded into the same pseudo as t0 because the source is:

```
sp10[4] = *(s32 *)((char *)&D_801A5470 + off);
```
and reload chose v1? No, allocation is local-alloc.

Hmm, actually maybe the target's source loads the fifth value BEFORE the stores (loads t0..t4 all first, then stores). Then at local-alloc time (after sched1), the RTL order is target's order anyway. But the pseudo t4's live range would span from its load (insn 56) to its store (59) — same.

Let me just test a batch of variants and see scores. Variants:
d2: t3 store after h[0].
d3: t3 store after h[1].
d4: t3 store after fifth load AND t4 load moved before stores (mix).
d5: loads t0..t4 then stores (c2) but with h early.
d6: reuse t0 for fifth load AND move t3's store after h[1].

Let me write d2-d4 and score.
