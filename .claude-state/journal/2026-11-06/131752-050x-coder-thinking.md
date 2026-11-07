---
ts: 2026-11-06T20:17:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tY1jPHhCWKUL8Vr4UXnR
---
`birthing_insn_p`: a SET whose dest pseudo has reg_n_sets == 1 and is not live before. So the boost is per-pseudo (REGNO), and reg_n_sets is per pseudo. The launder's second set is a *different pseudo* (a new set of the variable pv creates a new pseudo). So how does it kill the boost on the first pseudo?

Hmm, unless cse/flow treats the variable as one... In gcc, each SET to a variable creates a new pseudo only if the variable is not live at that point; otherwise it reuses. At the end of the function, pv's first pseudo is dead, so the asm's output gets a new pseudo. Then reg_n_sets of the first pseudo is still 1.

Wait, but maybe the effect is different: the asm makes the *variable* have 2 sets, and since the asm is opaque, the compiler may allocate the first pseudo... Hmm.

Actually maybe the launder's effect is: the asm's output pseudo is allocated the SAME register as the first pv pseudo (since pv is pinned to $3, both are $3? No—the pin is on the variable, so ALL pseudos of pv are $3!). Ah, that's the thing: `register u32 pv __asm__("$3")` means every assignment to pv writes hard reg $3. So `pv = *(u32*)p;` writes $3 directly (no pseudo). And the launder asm's output is also $3.

Then birthing_insn_p checks REGNO = 3 (hard reg) — reg_n_sets[3]? For hard regs, reg_n_sets is maintained too. With 2 sets, reg_n_sets[3] = 2 ≠ 1 → no boost. THAT's the mechanism: with the pin, pv's sets are to hard reg $3, and the boost condition `reg_n_sets[i] == 1` refers to $3; the launder adds a second set of $3, so the boost is killed.

So the launder is a "hard-reg 2nd set" trick: it kills the birthing boost on the $3 load.

Now, lever-free: we must keep the pin ($3) — it's an existing lever of another kind and may stay. We need a real C second set of pv (=$3) that survives.

Since pv is a hard reg, a second *dead* C assignment `pv = 0;` would emit `li $3,0` (1 insn) unless deleted. delete_dead_from_cse deletes insns setting a register that's dead... but does it delete a set to a HARD register? Hard regs are never "dead" in the usual sense — delete_dead_from_cse works on pseudos (regno >= FIRST_PSEUDO_REGISTER)? Let me check delete_dead_from_cse.

If it only deletes pseudo sets, then `pv = 0;` at the end (setting hard $3) would SURVIVE as `li $3,0` — one extra insn. Not matching.

Hmm, but wait: maybe a *conditional* or otherwise-eliminated set. We need a second set of $3 with no instruction.

Alternatively, kill the boost differently: the boost requires the dest reg to be live before? No: `if (bb_live_regs[offset] & bit) return (reg_n_sets[i] == 1); return 0;` — boost if the reg is LIVE BEFORE the insn and has 1 set. Wait: "if live before, return reg_n_sets==1". So a birthing insn is one where the reg is live before (in bb_live_regs at block start) and has exactly one set in the function.

For hard $3: bb_live_regs includes $3 if it's live at block entry. reg_n_sets[3] = 1 (just the pv load) → boost. With the launder, reg_n_sets[3] = 2 → no boost.

So we need a second set of hard $3 that doesn't emit an insn.

Real C ideas:
- `pv = pv;` — a self-copy: gcc would emit `move $3,$3`? or delete it. If it survives as a self-move, it might be deleted by cse1 or reorg (redundant move). Worth trying: `pv = pv;` at the end.
- An assignment that cse1 deletes but that still counts reg_n_sets at sched time? No—if deleted, reg_n_sets updated? delete_dead_from_cse... reg_n_sets is recomputed by reg_scan before sched? sched1 uses reg_n_sets from... `reg_scan` is called before sched (toplev: `reg_scan` in schedule_insns? sched.c calls `reg_scan` itself? Let me check: sched.c line 110 comment. `schedule_insns` calls `reg_scan (insns, max_reg_num(), 0)`? Let me check.

Actually if sched1 recomputes reg_n_sets from the RTL it sees, then only surviving sets count. So a deleted assignment doesn't help.

- A set of $3 inside a dead branch: no.
- A set that combine/sched removes later but sched1 sees... sched1 is the target pass; the set must exist at sched1.

What about assigning pv a value via a construct that folds into an existing insn? E.g., `pv = p;` where p is s1 → `move $3,$s1` (1 insn). No.

What about making the *first* set not count: e.g., if pv is set twice before sched1 in a way where one is the actual load. Hmm.

Wait — maybe we don't need the boost killed if we can achieve the same schedule another way. The score is 11 with three clusters:
1. bidx register: a0 in mine vs a2 in target (6 pairs a0->a2).
2. The `lw v1,0(s1)` position: mine at 137, target at 130 (in the lhu's delay slot).
3. `lui a0,0xff00`: mine at 130, target at 137.
4. `and v1,v1,a2` vs `and v1,v1,a0` (follows from bidx reg).

If pv's load is scheduled into the delay slot, the ordering fixes itself and the bidx reg may follow. The notes say both edits are needed and neither works alone: (1) kill the boost, (2) pin pv to $3. We keep the pin. So we need to kill the boost lever-free.

Idea: make pv's load NOT a birthing insn by making $3 live before the load with reg_n_sets==1... it IS. Alternatively make reg_n_sets[3] != 1 by having another set of $3 *earlier* in the function. E.g., set pv earlier: `pv = 0;` at the top → `li $3,0` (extra insn, but maybe it can be deleted?). Hmm, 178 insns.

What if the earlier set is *combined* into another instruction? e.g., `pv = (u32)p & 0xFFFFFF` used in the second half... 

Wait! Look at the target: in the second half, `and s1,s1,a3` computes `p & 0xFFFFFF` in s1 (clobbering p). The first half uses `and v1,v1,a0` (pv & 0xFF000000). If we wrote the second half using pv... no.

Alternative: write the first half so that pv is set twice *in the C source* in one expression? e.g., `pv = *(u32 *)p, *(u32 *)p = ...` no.

Hmm, what about using the same variable for both halves' read-modify-write, but keeping the target registers? The second half in target loads ot->unk40 into v0. If we write `pv = ((Unk*)ot)->unk40;` then pv is $3=v1 → the load would be `lw v1,0x40(v1)`?? No: ot is v1 in target's second half (`lw v1,0(at)` then `lw v0,64(v1)`). If pv is pinned to $3 and ot is in v1=$3, conflict.

Let me look at the full mine vs target tail to see registers. Target second half: v1 = ot (loaded), v0 = ot->unk40, s1 = p&0xFFFFFF. Mine? The diff only shows up to line 157. Let me see the full diff.

Actually the diff showed only ~8 mismatches in the tail; the rest matches. So mine's second half matches target exactly (ot in v1 etc.). Only the bidx register and the schedule differ.

So mine (lever-free): bidx in a0, and pv load late. Target: bidx in a2, pv load in delay slot.

Hmm, so the launder changed both the schedule and the bidx allocation. How? Because the launder extends... no, the launder is at the very end. It changes reg_n_sets[$3] and thus sched1's boost; the different schedule then changes... the bidx allocation? The bidx local is `volatile u16 *bidx` — a pointer pseudo. Its allocation (a0 vs a2) is a local-alloc/global-alloc decision, probably influenced by the sched1 order (sched1 assigns priorities that affect local-alloc).

The notes say: with the boost dead, "sched1 emits the target order exactly"; and with the pin, the index is pushed to $a0. Wait — the note says "With pv in $v1 the index is pushed to $a0" — the index IS a0 in the target! And bidx (the pointer to D_800B9A02) is in a2.

The diff: mine `lui a0,0x0; addiu a0,a0,0; lhu v1,0(a0)` vs target `lui a2,0x0; addiu a2,a2,0; lhu a0,0(a2)`. So in mine, the bidx *pointer* is in a0 and the loaded index in v1; in target, the pointer is a2 and the index in a0.

So mine has bidx-pointer=a0, index=v1; target has bidx-pointer=a2, index=a0.

Since the pointer is `volatile u16 *bidx = &D_800B9A02;`, it's a pseudo used 3 times (three lhu). The loaded value (u16) is used once per site.

Target allocates the pointer to a2 and the first index value to a0. Mine: pointer a0, index v1.

Hmm, this is a local-alloc difference caused by the sched1 order (the notes say sched2 re-applies rule 5(b) without the pin; here the pin is kept).

Let me try the obvious real-C launder replacements and score:
1. `pv = pv;` at the end.
2. `pv = (u32)pv;` (a cast, identity) — not allowed as an identity launder? "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". A self-assignment is an identity launder → banned.
3. `pv = 0;` at the end (dead reset, C0414). If it survives as `li $3,0` → +1 insn. Let me test; maybe it gets deleted (if delete_dead_from_cse handles hard regs). Actually for a hard reg, is the set dead? reg_n_sets... The set is to $3; if $3 is not live after (dead), flow marks it dead. `delete_dead_from_cse` deletes insns setting a register that is dead — including hard regs? Let me check the function.

Let me read delete_dead_from_cse.
