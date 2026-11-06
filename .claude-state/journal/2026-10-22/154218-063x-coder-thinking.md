---
ts: 2026-10-22T21:42:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UW5XFQr9SEs1kEjb0E6A
---
Entry16 = { S8Blob a; S8Blob b; } — 16 bytes, `a.raw[0..7]`, `b.raw[0..7]`.

The body:
```
*(s16 *)&loc.a.raw[0] = 0;
*(s16 *)&loc.a.raw[2] = -0x40;
*(M8_SC02_005_8017F7CC *)&loc.b.raw[0] = D_801E2DD8;
```
M8_SC02_005_8017F7CC is probably an 8-byte type.

Init-at-decl option: `S16_SC02_005_8017F7CC loc = { {0, 0, -0x40, ...} }` — raw is u8[8], so I can't easily write s16 values. Could do:
`S16_SC02_005_8017F7CC loc = { {{0,0,0xC0,0xFF, 0,0,0,0}}, ... }` — ugly but plain C. Actually the initializer must produce the same insns: `sh zero,16(sp); sh v0,18(sp)` — writing bytes would produce sb's. Not good.

Alternative: keep the stores but move them before... they're already right after the decl (the barrier was between decl and stores; removing the barrier makes them adjacent to the decl).

Hmm, the issue is only the `li v0,-64` being hoisted above `sw ra`.

Alternative approach: make the -0x40 come from a variable so its li is born later? The li is born from the store's constant; sched2 hoists it.

Alternative: what if `loc` is initialized via `= {0}` (all zeros) and then raw[2] set? changes.

Let me think about why the target has sw ra at slot 3: because the barrier (memory clobber) at the top blocks sched2's reordering: everything after the barrier can't move above it, and sw ra... hmm, sw ra is BEFORE the barrier? The barrier is the first statement; the prologue (sw ra) is emitted before the barrier insn. So sw ra can't be moved down past the barrier! That's the mechanism: the asm barrier prevents sched2 from sinking sw ra below it.

So in plain C, I need sw ra to have a scheduling constraint. In item 2 the fix was making the dead stores come earlier (they were the ones being reordered).

Here: the insns are li v0,-64 (ALU) and sw ra (MEM) and sh stores. sched2 picked li before sw ra.

What if I make the first statement a *memory* op that depends on the stack pointer... e.g. the `loc.a.raw[0] = 0` store is a memory op at slot 4 (after li). If the stores came before the li... 

Idea: write the two stores in one statement using a struct assignment? e.g. `loc.a` = a compound literal? That would emit a copy.

Idea: use `s16 v = -0x40;` and assign `*(s16*)&loc.a.raw[2] = v;` — then the li is born at the decl of v... no, at the assignment.

Hmm, what about making `-0x40` come from a *memory load*? no.

Let me look at the sched2 dump to see the ready list for this block — maybe there's a hint. But time.

Cheap experiments (c-series):
c1: swap the two raw stores (raw[2] first, then raw[0]) → order sh v0,18 then sh zero,16. Target has sh zero,16 then sh v0,18. Probably worse.
c2: `s16 m = -0x40;` then `*(s16 *)&loc.a.raw[2] = m;`
c3: declare `loc` as a `u8` array? no.
c4: move the loc.b copy before the raw stores.
c5: make the `iVar2` computation before the stores? changes order.
c6: `S16_SC02_005_8017F7CC loc = {{0}};` then raw[2] = -0x40; → maybe.

Actually, here's a thought experiment: in the target, sw ra is at slot 3 and li at 4. sched2's choice: at T-1 it picks among ready insns. sw ra (MEM, potential hazard) vs li (ALU). The rule "insn has a greater potential hazard" picks the MEM. In mine, the li got picked first — meaning at that point sw ra wasn't ready? or the hazard rule didn't apply.

Hmm, "potential_hazard" in gcc's sched.c:
```
/* Return 1 if the insn is a potential hazard (a memory reference that could
   trap or alias) */
static int
potential_hazard (insn)
{
  ...
  if (GET_CODE (PATTERN (insn)) == ... )
```
Actually in gcc 2.7.2's sched.c there's:

```
/* Return a value based on the number of memory references in INSN ... */
static int
memrefs_conflict_p ...
```

and in rank_for_schedule:
```
  /* Prefer the insn with more memory references if there is a potential hazard */
```

Let me try to see the actual dump. It's worth 2 minutes.

Actually — simplest hypothesis: the number of insns scheduled before the branch determines it, and the difference is one ALU insn. What if I add a *third* dead store (e.g. raw[4] = 0) — no, changes insns.

Let me just run a batch of 6 variants and check.

Actually here's a promising one: **make the `-0x40` store use a `s16` variable declared with init at decl at the top** — no.

**Alternative: reverse the store order so the first store is `sh zero,16(sp)` immediately (no li needed), then the li.** In the target, order is sw ra, li, sh zero, sh v0. In mine: li, sw ra, sh zero, sh v0. So moving the zero store before the li might give sw ra, sh zero, li, sh v0? Not target.

Hmm, what about the reorg delay-slot etc.

Let me look at the sched2 dump quickly for this block.
