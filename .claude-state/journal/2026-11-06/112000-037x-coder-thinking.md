---
ts: 2026-11-06T18:20:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NhZDh3CUSrVg2QydvPSx
---
expand_preferences: for an insn that sets allocno dest and has a REG_DEAD of another allocno: if XEXP(link) == SET_SRC (a copy), merge copy prefs; and merge normal prefs regardless.

Insn 32: `(set (reg 76) (mem (plus (reg 72) 204)))` with REG_DEAD(reg 72). dest allocno 76, dead 72; they don't conflict → merge prefs of 72 into 76 and vice versa. 72's preferences = {4} (copy from a0). So 76 gets pref 4! That's the mechanism.

So to remove the preference, either:
(a) make 72 and 76 conflict (then no merge), or
(b) remove 72's preference for a0 (the param copy), or
(c) make 72 not a global allocno (allocated locally) — e.g., if 72's life is block-local... but it's used in 3 blocks, so global.

Option (b): 72 = the param copy `(set (reg 72) (reg 4 a0))` — wait, why is there a copy at all? Because `void *a0` is used via cast `((Unkstruct*)a0)->unkCC` — expander copies the param to a pseudo? Actually the param `a0` in the RTL is a copy from hard reg a0 into pseudo 72 (that's the standard "parameter copy" — the function's a0 param is loaded into a pseudo when the variable's address is taken or when needed? Normally the param stays as a hard reg with a REG_DEAD). The copy exists because the source uses `a0` as a variable of type `void *` (movsi_internal2). Hmm, in the target's RTL (the pinned version), is there a copy? The target's a0 is used as base directly; the pin version has `register s32 v1 __asm__("$3")`, and a0 is the param.

The copy `(set (reg 72) (reg 4 a0))` is emitted by expand for a parameter that is used multiple times? In GCC 2.7.2, the parameter is copied into a pseudo if it's used more than once (to avoid the hard reg being clobbered). Yes: `assign_parms` copies params used more than once into pseudos.

So 72's preference for $4 comes from the copy. To kill it: make a0 used only once? No, it's used 3 times (3 loads). Hmm.

Wait, but the pinned version has the same structure and the pin forces v1=$3. So the preference exists there too, but the pin overrides it.

Option (a): make 72 and 76 conflict. How? If the load's result 76 were live at the same time as 72's next use... The three loads each use 72 and set 76; between them 72 stays live (72's life spans all 3 blocks: "dies in 3 places"). 76's life: born in block 1, dies at the store (block 4). Actually 76 is live from block 1 to the join. 72 is live from entry to block 3's load. They overlap: in blocks 1 and 2 both 72 and 76 are live (76 defined in block 1 and used in block 4). Hmm, but do they conflict? The conflict list says 72 conflicts: 72 74 75 2 5 6 29 — no 76. Why not? Because 76 is not live at the points where 72 is live... 76 is defined in block 1, then block 2 uses 72 and sets 76 (a redefinition). At block 2, both 72 and 76 are live-in? 76 from block 1 is dead (redefined). So the live ranges don't overlap in a conflicting way: 76's live range in block 1 is [load32, end of block1]; 72 is live through block 1. Hmm, that should conflict... unless 76's definition in block 1 is dead (only the block-3 definition reaches the store)? Flow: block 1 (d24: lw v1; j d38) → 76 flows to the store. Block 2 (d30? no)...

Wait the RTL blocks: 
- Block A: insn 29 (v0=1), 32 (76=load), j 45.
- Block B: label 36: 40 (76=load), 43 (v0=2).
- Block C: label 49: 53 (76=load), 56 (v0=2).
- Block D: label 58: 61 (store).
All three set 76. Since all definitions reach the store, 76 is live from each definition to the store. In block A: 76 live from 32 to end. 72 live through block A (it's used again in block B/C). So at insn 32 and after, both 72 and 76 live → they should conflict! But the dump says no conflict between 72 and 76.

Hmm, why? Because 76 is a *global* allocno and 72 too. Conflicts are recorded when a pseudo becomes live: `record_one_conflict` for pseudo sets. At insn 32, 72 is used (live), 76 is set → conflict recorded? mark_reg_store(76) marks 76 live and records conflict with all currently live, including 72. So there SHOULD be a conflict. Unless flow's data says 72 dies at insn 32 (REG_DEAD) and the conflict is not recorded because the death is processed first? In global.c's scan (`record_conflicts`), for each insn it processes deaths before stores? Let me check: in global.c, `record_conflicts` scans insns and for each: "mark_reg_store" then "mark_reg_death"? If the death of 72 is processed before the store of 76 at the same insn, no conflict is recorded (they'd be considered non-overlapping — a dying reg can share the reg with the value born in the same insn). That's the standard "death in same insn" allowance.

At insn 32, 72 has REG_DEAD? 72 is used in blocks B and C too, so 72 dies at insn 53 (the last use). At insn 32 there's no REG_DEAD for 72. Hmm, then the conflict should be recorded...

Unless the conflict is not recorded because 76's live range... Let me look at the .lreg table (local-alloc) — the "72 conflicts: ... " list. Hmm, actually the allocno conflicts list from the dump is global's. Let me not over-theorize.

The key question: what real-C change removes the a0 preference from 76? Options:

(b) Remove 72's preference: 72 prefers a0 because of the param copy `(set (reg 72) (reg 4 a0))`. If the param a0 were used as a hard reg directly (no copy), 72 wouldn't exist. When does expand avoid the copy? `assign_parms` creates the copy for params used more than once... Let me check function.c: in 2.7.2, "If the parameter is used more than once, copy it into a pseudo". Actually the condition: `if (reg_parm_stack_space ...)`? Let me look.

Alternatively, reduce a0's uses to 1 by using a different variable for the loads... e.g., load the pointer from a single expression. Hmm, a0 is used 3 times.

But wait — the target itself has the same 3 uses of a0 and the same param copy, and it worked because of the pin. For a lever-free crack we need another route.

Option (c): make 72 block-local? Impossible (3 blocks).

Option (d): make 76 conflict with 72 so expand_preferences won't merge. E.g., if 76 were live from an earlier point... it's born at the load.

Option (e): give 76 a *copy* preference for $3? A copy suggestion only counts if there's a reg-reg copy involving 76. What if we add `v1 = (s32)v1;`? no.

Option (f): Make 76's preference irrelevant by making $4 unavailable at allocation time: if $4 is in 76's conflicts. 76 conflicts: 75 76 29 (and hard regs from...). $4 would be in 76's conflicts if a0 were live across 76's live range. a0 (hard reg 4) is live at entry through 72's last use (insn 53, block C). 76's live range spans blocks A-C to the store. Hard reg 4 is live until insn 53. So does 76 conflict with hard reg 4? In global.c, hard reg conflicts are recorded when a hard reg becomes live: `record_one_conflict(4)` at the entry? For hard regs: "When a hard register becomes live, record conflicts with live pseudo regs". At function entry, hard reg 4 is live (param) → conflicts with all live pseudos... but pseudos born later? Hmm, hard_regs_live is updated as the scan proceeds; a hard reg that is live from entry conflicts with allocnos live at entry only. The conflict list for 76 doesn't include 4 because at 76's birth (insn 32), hard reg 4 is... live? a0 is live at insn 32 (used there). So 76 should conflict with hard reg 4!

But the dump says 76 conflicts: 75 76 29 — no 4. Hmm. Wait, the conflicts line lists allocnos (pseudos) and then hard regs 0..FIRST_PSEUDO_REGISTER. "76 conflicts: 75 76 29": 75 is an allocno; 76 is itself; 29 = sp. No 4. So hard reg 4 does NOT conflict with 76 in global's model.

That's because at insn 32, the load `set (reg 76) (mem (plus (reg 72) 204))` — the base is pseudo 72 (which is in $4), not hard reg 4. Hard reg 4 is only live during insn 4 (the copy to 72) and dies immediately (REG_DEAD at insn 4). Right! The param copy kills a0 at entry. So hard reg 4 is free afterwards; only pseudo 72 (→$4) occupies it. And 72 is NOT in conflict with 76 per the dump. Hmm, but if 72 is allocated $4 and 76 also $4, both live simultaneously in block A (76 born at insn 32 while 72 still needed in block B)... that would be a real conflict. But global says they don't conflict, so it must be that 72's live range ends at insn 32? No — 72 is used at insns 40 and 53 too.

Hold on: maybe the allocnos' conflict list is computed with live ranges; 72 "dies in 3 places". Its live range is the union. At insn 32, 72 is live (used) and 76 is born. Unless the conflict isn't recorded because 76's value at insn 32 is *not used* before being redefined? No, block A's 76 reaches the store.

Hmm, wait: is block A's 76 live at the store? Block A jumps to label 45 (block B's end), then falls to block D. Block A: 29,32,jump 45. label 45 is after block B (insn 43). So block A's jump goes to label 45 which is block B's end → then label 58 → store. So yes 76 from block A reaches the store.

Unless... hmm, `(jump_insn 34 32 35 (set (pc) (label_ref 45)))` — jump to 45, and label 45 is `(code_label 45 43 47)`. So block A jumps to block B's tail. So 76 (block A def) is live at 45 → store. Yes.

I'm confused about why 72 and 76 don't conflict. Let me look at the .lreg dump for the actual local-alloc behavior — local-alloc runs after global-alloc and might have its own view. But the register assignment is global (76 is a global allocno).

Actually maybe the conflict IS absent because of how global.c scans: at insn 32, 72's use is in the *address*; `mark_reg_store` for 76 records conflicts with `hard_regs_live`; but pseudo 72 might not be marked live at insn 32 because... no.

Let me look at the actual allocno conflict computation in global.c: `record_conflicts` processes insns: for each insn, first `note_stores (PATTERN (insn), mark_reg_store)` (marking stores, recording conflicts), then for each REG_DEAD `mark_reg_death`, and for each reg in the insn's operands `mark_reg_live`. Order matters: maybe uses are marked AFTER stores, so at insn 32: mark_reg_store(76) records conflict with currently live (not including 72 since 72's liveness was established at its last use... but liveness is a scan forward: they use REG_LIVE notes?).

Let me read record_conflicts in global.c (around line 610-770).
