---
ts: 2026-10-22T21:38:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UALdmzEOFkVXfSSulU7u
---
All score 2. Let me look at sched2's dump to understand the hazard rule and find the lever. Dump the candidate TU.

Actually first, let me check whether the sw ra position is the only difference in all of them (likely).

Let me dump sched2 for the lever-free body and look at the block's scheduling decision. Maybe there's a simpler observation: the target has sw ra right after move s0,a0 — that's the natural expand order (prologue). sched2 moved it down in mine.

sched2's `rank_for_schedule`: insns that are "potentially hazardous" get scheduled first? The gcc comment (from the source note in src): "sched2 finds no memory dependence and its potential_hazard rule promotes the prologue sw $ra over the ALU candidates, sinking it to just above the branch".

Hmm: "promotes sw $ra over the ALU candidates" — that means in the ready list, sw ra is chosen over ALU insns, so it's scheduled EARLY... but it ends up late? Actually if it's promoted early it'd be first. The note says it sinks to just above the branch. Confusing.

Let me just look at the sched2 dump: which insns are in the block and the order.

Actually, a more direct lever: what if the dead stores were NOT dead — e.g. make sp10 actually used (e.g. passed to a call)? That changes insns.

What about the number of insns before the branch? In the target the block is:
addiu sp; sw s0; move s0; sw ra; lui; lw; li -64; sh; li 10; bne; sh zero (delay).

In mine: addiu sp; sw s0; move s0; lui; lw; li -64; sh; li 10; sw ra; bne; sh zero.

So sw ra moved from slot 3 to slot 8, just before the branch.

What in the block could pin it? If the sw ra had a dependence on something... e.g. if the compiler thought ra was needed. Plain C can't touch ra.

sched2 hazard rule: in gcc 2.7.2 sched.c, `rank_for_schedule` compares:
- if one insn is a memory reference that "may be a hazard" ... there's `potential_hazard(insn)` used in `schedule_insns`:
```
      /* We have two insns... */
      if (potential_hazard (insn) ... )
```
Actually there's this in sched.c:
```
static int
rank_for_schedule (x, y)
{
  ...
  /* We prefer the insn that has a larger number of insns depending on it */
  ...
  /* Prefer memory insns over non-memory if there's a potential hazard */
```
Hmm.

Since all my variants give 2, and the sw ra movement is a sched2 decision that the asm barrier forced, this looks like the classic WALL. But maybe there's a trick: make the block's *first* memory insn the sw ra... no.

Think: what makes sched2 keep sw ra early? If sw ra were dependent on the preceding insns. The preceding insn is `move s0,a0` (ALU). No dep.

Alternatively: if there were a call in the block? no.

Alternative idea: the target's `sw ra` is at slot 3 — maybe in the ROM it's there because the *expand order* put it there and sched2 didn't move it. sched2 moves insns only when it can improve; the schedule order is by priority. Both mine and the target have the same insns.

What if I make the block's insn count before the branch smaller/larger? no.

What if the dead stores are the key: in mine they are `sh v0,18(sp)` and `sh zero,16(sp)`. In the target the same. Hmm.

Honest thought: this is the sched2 potential_hazard wall — no plain C. But before declaring, let me look at the sched2 dump to see if there's an available difference (e.g. the two sh stores are in the same block and sched2 orders them; if I make one of them a "potential hazard" MEM (non-constant address), maybe sw ra stays).

a2/a3 (pointer p = sp10) still gave 2 — but did they change the address to a register? Let me check a2's disassembly: if `p` got folded back to sp+16, then no change.

Let me check the sched2 dump of a2.

Actually, time. Let me try a couple more targeted variants:
b1: make the load address non-constant: `s32 *g = D_801270C8; if (*g == 0xA)`. Then `lw v1,0(v1)` becomes `lw` through a pseudo → maybe still folded to a constant symbol.
b2: `if (D_801270C8[0] == 0xA)` → `if (D_801270C8[0] - 0xA == 0)`? folds.
b3: change the ORDER of the stores vs the load: put the stores after the if? changes layout.
b4: declare sp10 as `s16 sp10[2] = {0, -0x40};` (init at decl) — the stores would be emitted in the prologue... maybe they'd be moved.
b5: `sp10[0] = 0;` where 0 comes from a variable that's 0.

Hmm. Let me look at the sched2 dump first — 2 minutes of reading might reveal the lever.

Let me dump the win.c TU.
