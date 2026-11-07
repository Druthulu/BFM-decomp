---
ts: 2026-11-07T01:01:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RjxdKrbwzF6e3VAkXK5m
---
There's an existing tag `callee-saved-order` explicitly for func_80177940: "global-alloc; callee-saved order needs a return-type/signature change (T10 S07 func_80177940)". That fits. But the brief says a WALL needs best = lowest score of a lever-free body. Our best is 43.

Time: item 1 started 17:57ish, now 18:00:40. Wait, that's only ~4 minutes? The `date` at session start was 17:54:12. Now 18:00:40. Hmm, so only 6.5 min elapsed. The "20 min" requirement per WALL... The brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". We have 35 tries but only ~7 min. So I need to spend more time, or at least more tries? The rule: "Budget 20-30 min wall per item; past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item".

So I need to keep working on item 1 until ≥20 min. Let me continue with more meaningful attempts — there may be a crack I haven't found.

Let me think harder about the two artifacts, since fixing them might actually be possible with the right real-C construct, and the register order too.

Reconsider: is the score 43 mostly register mismatches? The diff showed many instructions differing due to regs. If the registers were right, the score would be ~2 (the two missing copies). So both must be fixed.

The register order: p must be last. What if p is not the parameter pseudo at all? E.g., copy p to a local at entry and use the local everywhere:

```
void func_80177940(u32 *p0, u32 a, u32 b, u32 c)
{
  u32 *p = p0;
  ...
}
```
Then p0 has 1 ref (the copy) and p has the uses. If the copy is coalesced (reg_may_share), same allocno. If not coalesced, p0 gets a hard reg (a0, param) and p gets... still 11 refs. No change.

What if we split the pointer into two pseudos with disjoint live ranges so they DON'T share an allocno and each has ~5 refs? E.g.:
- pA for the pre-loop stores (refs ~5, live ~12)
- pB = pA + 5 for the loop/tail (refs ~6, live ~20)

Then global alloc: pA priority = 3*5/12*10000 = 12500; pB = 2*6/20 = 6000. Both high. Hmm, pA > b.

But wait — if pA and pB don't conflict (pA dies when pB is born), they can share an allocno (reg_may_share via the copy) → summed refs 11. Hmm.

What if pB is computed not by a copy but by an expression, so no may-share? `q = p + 5;` — still a copy-like set (reg_may_share applies to copies between pseudos? Let me check global.c: it uses `reg_may_share` from copy insns found in the RTL (set of a reg to another reg). p+5 is an add, not a copy, so no share.)

So:
```
  p[0] = ...; p[2] = ...; p[1] = ...; p[3] = ...;
  q = p + 5;     // p's last use
  ...
  p = q;         // p's def (dead-ish)
  r = p;
```
p's refs: 4 stores + p-5 + 1 (q = p+5) + 1 (p = q) = 7; live ~29.
q's refs: loop uses.
Priority p = floor_log2(7)*7/29*10000 = 2*7/29*10000 = 4827. Still > b 3333.
p refs 6: floor_log2(6)=2, 12/29 = 4137.
p refs 5: 2*5/29 = 3448 — still > 3333 (barely).
p refs 4: 2*4/29 = 2758 < 3333! 

So if p's refs drop to 4 and live stays 29, p falls below b. Then order: b(3333) > p(2758) > a(1944) > c(1666) → b=s0, p=s1, a=s2, c=s3. Target wants b=s0, c=s1, a=s2, p=s3. Not right: p would take s1, c s3.

To get p to s3, p must be below c (1666): refs 3 → 1034. And a must be below c: a 1944 → need <1666, e.g. live 13.

So: p refs ≤3, a live ≥13.

p refs ≤3: p's uses would have to be almost all on other pseudos. E.g., p used only in `q = p + 5` (1 ref) and `p = q` (1 ref) = 2 refs. The stores go through a different pseudo z (z = p at entry). Then z has the store refs and would compete for s0! z refs ~5, live ~12 → 12500, top. z would take s0, not b. Unless z's live/refs... z does the 4 stores + p-5: refs 5, live from entry to the 4th store (~12 ins). Priority 2*5/12*10000 = 8333 > b. So z takes s0. Bad.

Hmm. Unless z is block-local and local-alloc'd... The stores are in the entry block, which also contains the call. Local-alloc can't keep a value across a call in a caller-saved reg, but z is dead after the stores (no crossing). Wait, z is live from entry (z = p) to the last store; the call to func_80029504 is BEFORE the stores (v = func_80029504() comes first). So z is born after the call → local-alloc can put z in a caller-saved reg (a0/a1...) if its live range is within one basic block and doesn't cross a call. Hmm! But local-alloc's qty: z would be local-alloc'd (not a global allocno) if reg_n_calls_crossed == 0 and its uses are in one block.

Then z gets a caller-saved reg like a1/a2/a3 (whatever local-alloc picks), NOT s0. And global alloc only sees p, a, b, c. Then p's refs 2, live 29 → priority 1*2/29*10000 = 689 → p takes s3 (if it gets an s reg at all). But wait, p is only used in q = p+5 and p = q — both dead-ish. Hmm, if p is only used there, p might be local too.

But the target's stores use s3! If z is local-alloc'd to a caller-saved reg, the stores use a caller-saved reg, not s3. Mismatch.

So the target really has the store pointer in a global allocno that ranks last. Its refs are 8+.

I think this confirms: lever-free impossible. The target's allocation is pin-driven.

BUT WAIT. Maybe I should double check the priority numbers with the actual tool. The prior agent's numbers (11379 etc.) might be from a slightly different body. Let me use alloc_table.py to get ground truth for the current base body? That requires a TU dump. The brief mentions `tools/cc1_dumps_tu.sh` + `tools/alloc_table.py`. That's for the whole TU. Might be worth one look to confirm the wall evidence precisely (needed for the evidence field anyway).

Given the evidence field needs "gcc pass + mechanism ≤ 140 chars", I can cite: global-alloc allocno_compare priority: p (n_refs 11/live 29 → 11379) vs b (3/9 → 3333); p takes $s0. That's from the prior agent's analysis; I should verify at least roughly.

Let me check alloc_table.py usage.

Actually, let me do something more productive with the remaining ~13 min: try a few more genuinely different structures (splitting the pointer, local pointer for stores, etc.) to see if any score drops below 43. If none, wall.

Candidates y:
- y00: stores through z = p; then q = p + 5 (p's refs drop).
- y01: z = p - 5 for the first store value.
- y02: p[0] with a temp `u32 m = (u32)p;` and `p[0] = ((m - 20) & 0xffffff) | 0x3000000;`
- y03: `q = p + 5;` instead of p += 5 (w20 was 72 — it had `q = p + 5` with p_adv and no p+=5... scored 72).
- y04: both z stores and q = p + 5.
- y05: p[0] = ((u32)(p-5) & ...) with the p-5 hoisted to a temp.
- y06: use `a` as a pointer-free counter? no.
- y07: `p[3]` uses cl instead of the expression? The target computes the p[3] value as sll/ori/sll/ori (v<<6|0x4016)<<16 | 0x3850, and cl = ((v<<6)|0x4016)<<16. So p[3] = cl | 0x3850! Let me check: target: sll v1,v0,6; ori v1,v1,0x4016; sll v1,v1,0x10; ori v1,v1,0x3850 → yes = ((v<<6|0x4016)<<16) | 0x3850 = cl | 0x3850. And the cl computation: sll v0,v0,6; ori v0,v0,0x4016; sll t2,v0,0x10 → cl = ((v<<6)|0x4016)<<16 (no ori). So the source's p[3] expression is `(((v<<6)|0x4016)<<16) | 0x3850` and cl is `((v<<6)|0x4016)<<16`. They share the subexpression ((v<<6)|0x4016) but NOT the shifted value.

In r4.c, p[3] = (((v << 6) | 0x4016) << 16) | 0x3850 and cl = ((((s16) v) << 6) | 0x4016) << 16. The (s16) cast makes the cl expression different from p[3]'s inner, so cse can't fold. Good — the target indeed computes two separate sll/ori pairs.

Wait, does the target compute (v<<6)|0x4016 twice? Yes: sll v1,v0,6; ori v1,v1,0x4016 for p[3]; sll v0,v0,6; ori v0,v0,0x4016 for cl. Two separate computations. So the (s16) trick works to force it. 

Now the ORDER: target computes p[3]'s value (v1) BEFORE the cl value (v0)? Let's look: after `sw v1,0(s3)` (p[0]), `addiu v1,s0,15; andi v1,v1,0xffff; or v1,s1,v1; sw v1,8(s3)` (p[2]), then `sll v1,v0,0x6; ori v1,v1,0x4016; sll v1,v1,0x10; ori v1,v1,0x3850; sw a1,4(s3); sw v1,12(s3); addiu s3,s3,20; move a0,s3; sll v0,v0,0x6; ori v0,v0,0x4016; sll t2,v0,0x10`.

So p[3]'s computation happens BEFORE the cl computation (which happens after p += 5). Interesting — the target's cl computation is after the pointer advance. That's sched1 reordering.

OK. Let me just run a few more structural candidates and then wall.

Let me write gen3.py with the pointer-split ideas.
