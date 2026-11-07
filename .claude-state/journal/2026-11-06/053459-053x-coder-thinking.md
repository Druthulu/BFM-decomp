---
ts: 2026-11-06T12:34:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5XfrTjE6DYn3pwkiZiWG
---
No REG_ALLOC_ORDER defined in mips config (only the files that reference it), so reg order is numeric: 0=zero,1=at,2=v0,3=v1,4=a0...

But wait — `used1` excludes fixed regs and (if calls crossed) call_used regs; also `IOR_COMPL_HARD_REG_SET(used1, reg_class_contents[class])` restricts to the preferred class. For a pseudo, `reg_preferred_class` may be ALL_REGS or a specific class. With `used = used1 | regs_used_so_far` complement... In pass 0, `used` includes the complement of regs_used_so_far (so only regs not yet used by any allocno), and regs_someone_prefers.

So the allocno that is allocated FIRST (highest priority) picks the lowest-numbered free register. But v0 (2) is lower than a0 (4)... unless v0 is in `no_global_alloc_regs` or the class excludes it, or v0 is `regs_someone_prefers`.

Hmm, but wait: there's `no_global_alloc_regs` — for MIPS, maybe v0 is excluded? Hmm. Also `reg_class_contents[class]` where class = reg_preferred_class(pseudo). For a pseudo used in a `return`, maybe the preferred class is... 

Alternatively, maybe the reason mine used a0: some other allocno with higher priority took v0. Which one? In mine, at the STORE: `sh v0,2(s1)` requires a move from a0 to v0 → so v0 is free at that point. But during the arm (li v0,N), v0 might be taken by another pseudo with a longer range... no: if v0 were occupied at the li's def point, ret couldn't get it. But the allocator considers conflicts over the whole live range; some other allocno holding v0 across the arms would conflict.

Hmm, in the target, v0 is used for lots of things (it's the call result reg). Since v0 is call-clobbered, using it for a pseudo live across a call is impossible. Is ret live across a call anywhere in the target? The arms: `ret = 7; goto STORE` — not across a call. But the last part: `ret = CAST_SIGN(u16, param_1, 2) + 1;` after MoveImage calls. Also not across.

Hmm, but the whole function: ret is defined in arms, used at STORE. Each live range is def→STORE with no intervening call. So v0 is fine.

So why a0 in mine? Priority ordering: some other allocno got v0 first. Since `used` in pass 0 = regs not yet used by anyone... Actually the loop: for each allocno in priority order, find_reg with `used1` = fixed + (call_used if calls crossed) + complement of class; then `used = used1 | complement(regs_used_so_far)` — in pass 0 they avoid regs already used by previously allocated allocnos; if none, pass 1 ignores that.

Since v0 < a0 numerically, and if v0 were free, ret would get v0 in pass 0. So v0 must be taken by an earlier (higher-priority) allocno, or v0 conflicts (hard_reg_conflicts), or v0 is in regs_someone_prefers (a register some other pseudo prefers).

`regs_someone_prefers`: computed in prune_preferences from the *preferences* of all allocnos — "a bitmask of the hard registers that some allocno prefers". Pass 0 avoids those. If some other pseudo prefers v0 (e.g. via copy preferences), ret wouldn't get v0 in pass 0, but pass 1 would still try in numeric order... unless it found a0 in pass 0. Right! Pass 0: ret skips v0 (someone prefers it) and takes a0 (4). So ret gets a0.

In the target, ret gets v0 — so either ret has a copy preference for v0 (the `v0 = ret` copy at the return! → copy preference), or nobody else prefers v0.

`hard_reg_copy_preferences` comes from copy insns: `set A = B` gives both A and B a copy preference for each other's registers. But `v0 = ret` where v0 is a hard reg — does that create a copy preference for ret toward v0? In global.c, preferences are built in `global_conflicts`? Let's see: `hard_reg_preferences` is initialized from... line 516-518 only clears eliminable. Let me look at where hard_reg_copy_preferences gets filled — search for "IOR_HARD_REG_SET (hard_reg_copy_preferences" occurrences: line 809 (expand_preferences merging) and in local-alloc.c it writes `reg_pref`. Let me grep in local-alloc.c.
