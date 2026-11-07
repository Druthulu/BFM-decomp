---
ts: 2026-11-06T23:44:51.491Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ad2f5b165a7f6e91c
model: claude-haiku-5-5
effort: medium
turnId: e4f74c0e-cf1a-45a1-8c3a-3307ee420397
---
I'm treating rung B as the removal of barriers, keepalives and instructions, so the "delever B" lever means removing the barrier at that rung. The 8015444C rows are the file-scope barriers with blank function bodies, and I'm checking where they sit against the end-of-§8b marker.

I'm checking the 8015444C rows against the §8b marker, and the tsv lists the marker at line 1960 while the row cites 1590, so I'll just report the tsv text as written. I also see that the T9 log and task file have no grep hits for these functions, so T9 didn't touch them in scope.

I'm checking the T11 plan: 39 parked rows, made up of 27 instruction-class, 4 family, 5 T10 survivors, and 3 file-scope barriers. T10's notes say to skip the instruction and family rows, and to keep func_80136824 in ov_MAIN_012 and ov_SC04_011 as is. The five survivors sit in parked.tsv rows 14, 15, 33, 38 and 39.

I'm mapping the T10 results to wall tags for the T11 causes: func_8017E98C looks like a sched1-argcopy-hoist case, with the "wall best 1, 25, 7" scores read as three coder-attempt best scores rather than try counts.

I'm working through the T10 wall results now. The numbers after "best" look like comma-separated scores, lower is better, and I don't see a per-function try count recorded for walls, so I won't assume one. The only try count I can confirm is the 847 total across the 20 functions.

I'm reading the T10 wall lines as best score, then tries, then minutes: the S01 entry "best 1, 25, 7" means 25 tries over 7 minutes, and S17 adds about 1440 permutation compiles on top of its 13 tries.

Now I'm working out the wall-function causes from T10, where the cse folds on 801805EC and 8017DFB8 look like the cse-const-addr tag.

I'm now mapping each function to a wall-cause tag, starting with func_80177940, which looks like a callee-saved ordering problem under global allocation, so I'd tag it as callee-saved-order with a best score of 37.

I'm now going through the wall-function causes from T10: func_801805EC looks like a cse-const-addr case with a best score of 11, and func_801831B4 fits sched1-birth-boost with a best of 2 over 13 tries. func_8018EDB0 has no clean existing tag, since its cse merge of two adds off one base across a call doesn't match the copy-merge pattern, so I'm leaning toward proposing a new one. I'm also starting on func_8017E98C.

I'm now going through the family members: the 8015444C rows point to the same macro-named family, and I'm working out which of them T10 never actually attempted, since only 80188C04 was cracked there. The T10 wording about all eleven members sharing the same seven levers reads like a claim across the family rather than per-function results, so I'll keep that distinction in mind.

I'm looking at the SR3_ macro for 8018478C, which is named after its own function and defined in that member's file. Its body is a signed 16-bit read shifted down to 13 bits, and it looks identical across the family files.

I'm going through the remaining parked functions now, checking which ones T10 or T9 never touched in the scope logs. The 80181EBC, 80188C68 and neighboring instruction-class rows have no grep hits, so I'm recording them as not found rather than assigning causes.

I'm checking the remaining instruction-class rows, func_8018C000 among them, and nothing in the scope logs shows they were attempted, so I'm recording them as not found. For the 8015444C barrier rows, I'm tying them to the carried decl-layer end marker in the jr_isolate tool and the rung-B removable set, rather than to any macro I've located.

I'm checking which of the 11 family members actually appear in parked.tsv, since only four rows do, and I want to see whether the other seven turn up anywhere else in the scope logs before I call them not found. I'll run one grep for the SR3_ macro across the source to see if it surfaces them.

I'm going to run a targeted grep for `#define SR3_` across the source tree, since the earlier truncated search may have missed some macro definitions that could reveal the other family member names.
