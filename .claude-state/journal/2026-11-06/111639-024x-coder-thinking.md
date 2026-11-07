---
ts: 2026-11-06T18:16:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lYXtopXbf5KQuwpetGD6
---
Let me get a dump. Approach: copy the TU to a scratch file with the body replaced, then run cc1_dumps_tu.sh on it with DUMP_ROOT under my shard dir.

Actually simpler: delever_search --try with --keep prints the candidate object path and keeps scratch. But the scratch is under .run somewhere shared? The brief says "--keep scratch is removed after use". Let me instead make my own TU copy: take the src TU and replace the function body with my candidate. That's what delever_search does internally.

Hmm, for the dump I need a .c TU file containing my body. I can create one: copy src TU (it's big, ~8000 lines) — that's heavy but fine (a copy under my shard dir). Actually the src TU is huge; copying is cheap.

Wait, but maybe simpler: use delever_search --try --keep to get the scratch TU path, then dump that. Let me try.

Actually, before diving into dumps, let me test cheap candidates. Time is limited (3 items, 20-30 min each).

Let me think about the global-alloc priority angle for item 3. v0 and v1 are both global (live across blocks). Priorities:
- v0: refs? v0 = D_80078EB1 (load), then used in 2 slt (refs 2 more?), then set to 1 or 2 in branches (2 sets), then used in store. Hmm, v0 is a single pseudo reused for many values? In the source, v0 is one variable. Its live range is long; refs ~6. pri = floor_log2(6)*6*4/live... 
- v1: refs 3 (two defs, one use), live shorter.

In global-alloc, the allocation order is by pri; for each allocno, find_reg tries hard regs in `reg_alloc_order`. Global-alloc's find_reg tries call-clobbered regs first ($2,$3,...). It also uses "copy preferences" (allocno_pref) and "conflicting" info. The result v0=$2, v1=$4 suggests: maybe v1 was allocated FIRST (higher priority) and $2 was taken by... no, v0=$2.

Hmm, if v1 allocated first with $2 free, it would take $2 (lowest free). Then v0 would take $3. But we see v1=$4, v0=$2. So v0 allocated first (took $2), then v1: $3 free but $4 also free; it took $4 — why not $3? Copy preference! v1's def is `lw` from a0; no copy. Hmm, but global-alloc might have a preference from the *argument* a0? There's `REG_LIVE_LENGTH`...

Actually maybe $3 is NOT free: $3 could be used by something else in the function... in block B? The function is tiny. $3 is the target's v1. In our build, is $3 used by another pseudo (like a1)? a1 is a parameter ($5). a2 = $6. v0=$2. Hmm.

Wait, in our build the mismatches are only the three v1 refs. So everything else matches, meaning $3 is not used elsewhere in our build.

Unless... global-alloc's find_reg checks `regs_live_at`/conflicts; $3 might conflict with a call-clobbered... no calls.

So why $4 over $3? Possibly `allocno_pref` copy preference from the *store*: `sw v0,176(v1)` — no. Or from `lw v1,204(a0)`: the load's address base a0 is a hard reg; global-alloc's `record_reg_classes` may add a preference for a0 (like local-alloc's suggestion). Yes! In global-alloc.c there's similar logic: `record_reg_classes` calls `record_one_conflict`/preferences; for a memory operand with a base reg, it may add a preference to use the base reg ("preferred or nothing"). In global-alloc there's the function `record_reg_classes` which for operand constraints 'm'/'o' does nothing, but for the "SET_SRC is memory" ... Hmm.

Actually in global-alloc.c 2.7.2, there's `reg_pref` handling with "copy" preferences computed in `global_alloc` from `regs_set`... The preferences come from `REG_NOTE REG_EQUIV`? No: global-alloc computes preferences in `find_reg` from `allocno_pref` arrays filled by `record_reg_classes` — where an operand constraint 'r' that can also be a memory... 

Let me just grep global-alloc.c for "pref".

But maybe more productive: try to change the value flow so v1 is not live from a block into the join, e.g., make the store duplicated in each branch (like the source already duplicates the else). If v1 becomes block-local, local-alloc handles it; then the suggestion $4 mechanism may apply (as analyzed). Hmm, that would give $4 again (as in block C). Unless block-local gives $2/$3.

Wait: our current build's v1 IS live across blocks (from d24 to d38). Target's v1 is also live across blocks (same structure). So the difference is in global-alloc.

Let me look at the .greg dump to see the order and preferences. That's the decisive tool. Let me get the dump.

Plan: create a scratch TU with my body (w1) spliced, run cc1_dumps_tu.sh with DUMP_ROOT=.run/P40/T11/W48x/dumps_item3, then run alloc_table.py on the tag. But cc1_dumps_tu.sh takes a .c file or a work dir with <fn>/t.c. It compiles the whole TU — fine.

How to splice? Use delever_search --try --keep, which prints the candidate object path; maybe the scratch dir contains t.c. Let me try.
