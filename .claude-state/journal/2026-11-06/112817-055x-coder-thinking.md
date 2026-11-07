---
ts: 2026-11-06T18:28:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3E2iZl4ARUqAe18GsFE7
---
w14 compile error because the sed swapped both lines to the same? Let me check: w1 has "s32 v0;" then "s32 v1;". sed 's/    s32 v0;/    s32 v1;/' turns line1 into v1; then 's/    s32 v1;/    s32 v0;/' turns BOTH lines into v0 (line 1 and line 2 both "s32 v1" now). Oops. Not important — one more try: a proper decl-order swap. Actually decl order in GCC 2.7.2 doesn't matter for RTL (pseudos are created on first use). Skip.

Time: 11:28:11 → 17.1 min. Need 20 min. Let me do 2 more meaningful tries and let a bit of time pass. 

One more idea: **make the two loads in the arms be of different C expressions but the same value**: e.g., arm A: `v1 = ((Unk*)a0)->unkCC;` and arm B: `v1 = *(s32 *)((char*)a0 + 0xCC);` — same RTL.

Another: **make the load result used in the condition**: no.

Another: **make 76's live range longer by placing the store after a dummy statement that's folded**: e.g., `if (v0 == 1) {}` — flow deletes.

Hmm, what about adding a `do{}while(0)` around the store? That might change the block structure. Let me try:
w16: do{}while(0) around the store.
w17: put the store inside an if that's always true? e.g., `if (v1 != 0) *(s32*)(v1+0xB0) = v0;` — adds a test (target has none).

Let me try w16 and also a variant where the arms' loads use a temp that cse keeps (w3 showed it merges).

Actually, let me look at whether the *order* of global allocnos can be changed by the sched1 pass reordering insns (live lengths are computed post-sched?). Live lengths come from the final RTL before global-alloc. Statement order affects sched1 which can reorder loads/uses. The sweep showed no change.

I'll do one final try: `if (!(v0 < a1) && (v0 < a2)) { ... } else { ... }` with the store written as `((Unkstruct_80184B70 *)v1)->unkB0 = v0;` (struct store) — maybe the store's addressing changes nothing.

Then record the WALL at ~20 min.
