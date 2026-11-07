---
ts: 2026-11-06T16:51:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BoW4i8vcwanb3xJqB3qJ
---
Key difference: no_fp has 10 global regs (extra 225 and 85) and dispositions:
- 86 in 17 (s1) — same
- 135 in 18 (s2) — same
- 82 in 19 (s3)
- 84 in 20 (s4)
- 85 in 21 (s5)
- 81 in 23 (s7)
- 134 in 22 (s6)
- 225 → ? (not in the list? dispositions list doesn't show 225 — maybe it got a0-a3 or v? Actually 10 regs to allocate but dispositions show only 8 of them; 225 and 117 might be in call-clobbered regs.)

In pinned: fp=16 (s0); 86 in 17, 135 in 18, 84 in 19, 82 in 20, 134 in 21, 81 in 22.
In no_fp: 86 in 17, 135 in 18, 82 in 19, 84 in 20, 85 in 21, 134 in 22, 81 in 23.

So removing the fp pin: fp's pseudo changed from 16 to ... 225/85? The extra pseudos 85 and 225 appear — probably because without the pin, the fp expression `(s8*)prim + 0x22` is computed differently (split into two pseudos), and one of them (85) takes s5, pushing 134 to s6 and 81 to s7 → the extra save and frame.

Target (pinned) needs fp in s0. To get that lever-free, the pseudo must be allocated s0. In no_fp, s0 is allocated to... none of the globals (16 not in dispositions). So s0 is used by a block-local pseudo (91 in 16!). Register 91 in 16 (s0) is a block-local pointer in block 0 — the &D_800AF648 or &D_8019E164. Since local-alloc gives block-local pseudos their regs first (before global alloc), s0 is taken by a block-local pseudo in block0. But s0 can be reused across blocks by global alloc if the block-local dies... The global alloc pass sees hard reg 16 used in block0 (by reg 91) — that creates a conflict only if the global's live range overlaps. Global pseudos live across blocks; if a hard reg is used anywhere in their live range, it conflicts.

In the pinned version, fp is forced to s0 despite 91 in 16? That would conflict... unless the pin makes the register allocator ignore? A pinned register var (asm) is a fixed hard reg; the allocator treats it as always available? Hmm, but 91 in 16 (block 0) and fp in 16 (loop) don't overlap in liveness (block 0 is before the loop), so global-alloc can give fp s0 if it considers 91 dead by then.

In no_fp, global-alloc *could* give fp s0 too, but fp's priority ordering placed it after others? No: s0 would be assigned to the highest-priority global that doesn't conflict with 16. Let me see the conflict lists: 135 conflicts include "16" (hard reg s0) — in pinned, "135 conflicts: ... 16 ..." too. Hmm, both have 16 in the conflict lists of 81,82,84,86,134,135. Wait in no_fp, conflicts list for 135 includes 16? "135 conflicts: 81 82 84 85 86 134 135 225 2 3 4 5 29" — no 16! In pinned: "135 conflicts: ... 2 3 4 5 16 29" — includes 16.

So in the pinned version, the global pseudos conflict with s0 (16) — that's because fp is pinned to s0 and is live across them, so they can't use s0. In no_fp, nobody conflicts with 16 except... 91 (block-local) uses it.

So in no_fp, s0 is free for the globals, yet none got it. Why? The global allocator's ordering: it allocates the highest-priority first, choosing the cheapest register. Maybe s0 is more expensive for the qty class? All are GR_REGS. find_free_reg scans regs in order of cost; for GR_REGS, s0..s7 all cost 1? Hmm.

Wait — maybe global-alloc assigns s0 to a pseudo that then got coalesced away, or s0 is used by the *fixed* pin? No pins now.

Hmm, 10 regs to allocate; dispositions list shows 8 in s-regs and 2 (117, 225) in call-clobbered. So s0 (16) wasn't used by any global; s1..s7 used. That means the allocator skipped s0! Why? Because s0 is "used" in block0 by 91 and the allocator's conflict computation might mark s0 as conflicting with everything live at entry? The global allocno live ranges that include block0 (e.g., buf lives from block2 to the end, not block0).

Actually: reg 86 (s1), 135 (s2), 82 (s3), 84 (s4), 85 (s5), 134 (s6), 81 (s7). So 7 globals got s1-s7, and s0 unused. That suggests the allocator started at s1 because s0 was considered used/conflicting for all of them. Which global could conflict with s0? The one live in block0 — 117 (in 2 = v0) or 74 (in 8 = t0). Hmm.

Maybe the block-local 91 in 16 (s0) spans into a later block? No, "in block 0".

Alternatively, global-alloc's find_free_reg starts from a "preferred" reg based on the order of hard regs by cost; for a qty that crosses calls, callee-saved regs cost less. The scan order might be s1, s2, ... (s0 excluded because it's a fixed/return-address? No, s0=16 is a normal callee-saved).

Hmm, in the pinned version, all globals conflict with 16 because fp pinned there. So s0 was excluded there too.

Let me look at the actual reg ordering: maybe the allocator sorts by hard reg number but starts with the ones not used by block-local allocs in *other* blocks? 

This is deep. Alternative: force the fp pseudo to be born in block0? If fp's live range starts at entry, it might conflict with s0's block-local use (91) and thus not use s0. No good.

Alternative: eliminate the block-local 91 in s0 so s0 is free and the allocator picks it. What is 91? It's a pointer in block0: probably `&D_800AF648` (used for the two calls) or `&D_8019E164` (RotTransSV arg). In the target, s0 is used for &D_800AF648 (lui s0) and later reused for fp. So the target DOES have a block-0 use of s0.

Hmm, so in the target, the &D_800AF648 pseudo is s0 (block0) AND fp is s0 (later). Both use s0 at different times. Global-alloc gave fp s0 despite the block0 use — meaning fp does NOT conflict with 91's use (non-overlapping live ranges). But then why didn't no_fp's fp get s0?

Maybe because in no_fp, fp's pseudo is different (85 and 225 split) and their live ranges DO overlap block0? No.

Let me look at no_fp's greg conflicts: does any global conflict with 16? No. So s0 is free for all of them, but they took s1-s7. That means the allocation order assigned s1 first to the highest priority... i.e., the allocator's register scan starts at s1, not s0! Why? Perhaps because s0 is *fixed*? No.

Hmm, in the pinned version, the dispositions: 86 in 17 (s1), 135 in 18, 84 in 19, 82 in 20, 134 in 21, 81 in 22 — also s1-s6! And fp=16 (s0) pinned. So in BOTH cases the allocator uses s1, s2, ... in order, skipping s0. That suggests the global allocator assigns s0 only to a pinned/fixed reg, or s0 is the *lowest priority* register in its ordering (maybe because s0 is "used" by block0 locals?).

Wait, actually, maybe it's because in the target, fp got s0 via the pin; the other globals got s1+. In no_fp, the allocator gave the 7 highest-priority globals s1..s7 (never s0). If s0 were available, the first would get s0. So s0 must be excluded. Why? Possibly because reg 91 (block-local in s0) is live at the function entry and the global allocs' conflict sets include hard reg 16 via the *entry* block? Only pseudos live at entry would conflict.

Which globals are live at entry? None (they're born later).

Hmm, alternatively, global-alloc marks a hard reg as used if ANY block uses it and the allocno's live range *includes* that block. The `&D_800AF648` (91) is in block0; globals born later don't include block0.

Let me look at the alloc order: maybe global-alloc assigns in priority order and the first free register scan starts from a per-qty preferred class order that puts s0 last due to `reg_alloc_order` (REG_ALLOC_ORDER macro in the mips machine description!). In gcc, find_free_reg scans `reg_alloc_order[]` which is machine-specific. The MIPS REG_ALLOC_ORDER might be: 4..7, 8..15, 16..23, ... i.e., s0..s7 in order. Hmm.

Actually, maybe s0 is at the END of the allocation order because it's the frame pointer candidate. Let me check the mips.h REG_ALLOC_ORDER.
