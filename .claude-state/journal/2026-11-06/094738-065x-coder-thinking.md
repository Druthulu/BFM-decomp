---
ts: 2026-11-06T16:47:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ELMxC2YZiGdfogZfRl8q
---
Priority = floor_log2(refs) * refs * size / (death - birth), per basic block (local-alloc works block by block). The qty with the highest priority is allocated first, and `find_free_reg` picks... which register? The lowest-numbered free? Actually find_free_reg picks the first free register in the class with a preference ordering.

In the first block (after prologue), the quantities are: v0, v1, a1, at, and the shift temp. The highest priority gets the first free reg (probably $2, since $1 is at? no, at is a real reg $1 = $at, reserved for assembler temp; local-alloc can use $at? In gcc mips, $1 is not allocatable, so the first allocatable is $2).

In the target: v0 gets $2 → v0 has the highest priority in the first block. In mine: the shift temp gets $2 → the shift temp has higher priority than v0.

The shift temp's live range is tiny (birth=death at the sll), so its priority = log2(1)*1*size/1 = high? floor_log2(1)=0 → pri=0! Hmm, floor_log2(1) = 0, so pri=0. That's low. Hmm, maybe refs is 2 (the shift sets and the branch uses it).

Hmm, wait. Maybe the rotation isn't from local-alloc but from global-alloc. The variables are function-scope (global allocnos). The REG-caller class... Actually, `v0` is used in multiple blocks → global allocno. Global-alloc assigns registers in priority order (allocno_compare). The pin forces $2.

The unpinned global assignment: $2 = shift temp (a local pseudo? no, the shift temp is block-local), $3 = v0, ...

Hmm, local-alloc runs first for block-local qtys, then global-alloc for the rest. The shift temp is block-local and gets $2 from local-alloc; then v0 (global) can't get $2 → $3. So the shift temp indeed steals $2.

To fix: make the shift temp share v0's register (tie) or eliminate it. The tie happens via `qty_phys_copy_sugg` (copy preferences) — when an insn is `(set (reg a) (reg b))`, local-alloc suggests the same register. But `sll v0,v0,0x10` is `(set (reg temp) (ashift (reg v0) 16))` — not a copy, no tie.

In the target, why does the shift write into v0? Because... maybe the target's source reused v0: `v0 <<= 16` or the compiler's cse folded the shift into v0 because v0 was dead. Actually, gcc's `cse`/`combine` might transform `(set temp (ashift v0 16))` where v0 dies into `(set v0 (ashift v0 16))` via `reg_dead` substitution? There's an optimization in local-alloc: "if a qty dies at an insn, and the insn sets another qty, tie them" — `qty_phys_copy_sugg`. Let me look for `find_free_reg` and the tie logic in local-alloc.c. There's a function `reg_is_born`, `reg_is_set`, and `update_equiv_regs`.

Actually the relevant: local-alloc.c has code that, when an insn sets REG_A from REG_B and REG_B dies there, it suggests the same register (copy suggestion). But for an ashift, no.

Hmm, but in the target, the sll dest IS v0. Maybe the target's source was different: e.g., `if (v0 << 16 < 0)` where v0 is the u16 value — the compiler could use v0 as the dest because v0 is dead. That's `local-alloc`'s "qty_phys_copy_sugg" only for copies. Alternatively, cse's `cse_insn` might have replaced the temp with v0? No.

Wait, maybe in the target the value loaded is in v0 and the shift is `sll v0,v0,0x10` because the source wrote `v0 = v0 << 16`? But then v0 would be clobbered and recomputed in the branches — which is exactly what the source does! Maybe the original source was:

```
v0 = *(u16 *)at;
v1 = ...;
if (v0 << 16 < 0)  // ...
```

Hmm.

Let me try a different approach: use the *unpinned* body and steer by adding a copy suggestion: `v1 = v0;` before... no.

What about writing the test as `if ((s32)(v0 << 16) < 0)` but assigning the shift to v0 explicitly *without* changing semantics: 
```
v0 = v0 << 16;
if (v0 < 0) { ... }
```
m02 did this and got 66 ins. Let me see why 66. In m02's objdump above, the first block has 67? Let me count... The m02 objdump shows `sll v1,v1,0x10` then `bgez v1`. That's the test using v1 (source v0). And the mapping is still rotated. So the shift temp got merged with v0? In m02, `sll v1,v1,0x10` — yes, the shift dest is the same as v0's register (v1 = source v0). So m02 DID merge the shift into v0! But the rotation persisted: source v0→$v1, source v1→$v0.

So after merging, why is the allocation still rotated? Now v0 (source) has 2 sets... and v1 (source) got $v0. Hmm.

Wait, in m02's first block: `lhu v1,0(at)` (source v0 loaded into $v1), `lhu v0,48(a1)` (source v1 into $v0), `addu v0,v0,v1`, `sll v1,v1,0x10`. So source v1→$v0, source v0→$v1. The shift merged into source v0 ($v1).

So now the priorities: source v1 got $v0. Why? v1's live range in the first block: set at `lhu v0,48(a1)` (birth) to the store `sh v0,48(a1)` (death) — short. v0's: set at the lhu, used at the addu and the shift → dies at the branch. Also short.

The priority formula: log2(refs)*refs*size/live_len. Both size 4 (SImode). If v1 has refs=3 (set, use in add, use in store) and live_len ~5, pri = log2(3)*3*4/5 = 1*12/5 = 2.4. v0 refs=3 (set, add, shift), live_len ~5. Similar. The tie-break might favor v1.

This is getting deep. Let me use tools/localalloc_sim.py if it can take a candidate. Let me check its help.
