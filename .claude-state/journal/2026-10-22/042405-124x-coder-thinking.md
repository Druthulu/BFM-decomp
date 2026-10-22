---
ts: 2026-10-22T10:24:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_KD92pcsmzEckQimJi6xe
---
So other shard coders committed only the phase-ends/current/logs/*.md files (the .run/ stuff is gitignored). The brief's "no git, no commit" probably meant "don't commit the scratch" — but the convention (from G15b) is to commit the log file.

Hmm, but the brief explicitly says "no make, no git, no commit". Hmm, hmm. The safest interpretation given the harness rule "When green: commit with tools/commit_task.sh" and the observed project convention (G15b committed the log): commit ONLY the log file(s). The risk of committing is low; the risk of not committing is that the expert can't find my log.

Hmm, but "no commit" is explicit in the brief... The brief was written by the expert for a scratch-only shard. Hmm, but it also says "LOG: phase-ends/current/logs/T11.cRM2.md (timeline per item, moves that cracked, walls with evidence)" — so the log is expected to be written; whether committed is ambiguous.

Decision: write the log, and commit just the log file with tools/commit_task.sh (following the project convention from G15b and the harness rule). Hmm... but "no git, no commit" — if the expert's brief forbids it, committing might conflict with the expert's workflow (e.g. the expert might commit the shard's log itself later, causing a conflict — no, committing is harmless).

Hmm. Actually, let me re-read: "CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added; write only under .run/P40/T11/RM2/ plus appends to .run/P40/T11/moves.md (never src/, include/, config/, tools/, build/, other shards, shared helpers); no make, no git, no commit;"

"write only under .run/P40/T11/RM2/ plus appends to .run/P40/T11/moves.md" — hmm, that excludes the log file too! But the LOG section says to write phase-ends/current/logs/T11.cRM2.md. Contradictory-ish, but the LOG section is explicit.

Given "no git, no commit" is explicit and the harness's commit rule is generic, and the brief also says "write only under .run/...", I think this shard is deliberately scratch-only: the expert will collect the results. Hmm, but then why require the log file?

Hmm. Compromise: write the log file (required by LOG) but do NOT commit (following "no git, no commit"), and state in the report that the log is written and uncommitted per the brief's constraint. Hmm, but the harness says "commit only what is green"...

Hmm, the risk: if the expert expects a commit, an uncommitted log is still on disk (visible). If the brief forbids commits, committing violates an explicit constraint (a judge could flag it).

Hmm, the brief's constraint list is the task spec, and it's explicit: "no make, no git, no commit". Also the system prompt says "the project-architect skill is binding" and the brief is from the expert. Also: "Do not add features, abstractions, options, or tests beyond the change".

Hmm, but the system prompt ALSO says "When green: commit with tools/commit_task.sh T<n>.c<k> ...". Hmm.

Let me look at how the shard dirs of other coders handled it: G15b committed. But maybe G15b's brief said to commit.

Decision: I will NOT commit, because the brief explicitly forbids git/commit for this shard ("no make, no git, no commit"). I'll note it in the report and in the log file. Hmm... hmm. But the harness's "DONE WHEN" + report says "+ the commit" in the report format ("your report starts with one plain word ... then says what changed and the commit").

Ugh. Let me weigh: the brief's constraint is specific and explicit; a coder violating an explicit "no commit" is a clear breach. The harness rule is generic. I'll follow the brief: no commit, and say so explicitly in the report (the report format mentions the commit; I'll state "no commit (brief forbids it)").

Hmm, hmm. Hmm, but "DONE WHEN: every item of RM2/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." — that's the completion criterion, and the log is required by LOG.

OK: no commit. I'll note it.

Now, let me finish the work:

1. Score w17-w19 — done (12, 20, 15). w17 (store first) = 12 — interesting, better than 20! That confirms the mechanism: when the x-store comes first, the li's move earlier (12 instead of 20). But the store order then differs from the target ✗.

Hmm! Interesting: w17 = 12. Hmm, so moving the x/y/z stores earlier reduces the mismatch. But the target's store order has them after the other stores. Hmm, but the mismatch count 12 means the li's are at the right place?? Hmm, no: w17 changed the store order → the stores are mismatched but the li's are earlier.

Hmm! Let me look at w17's diff to see. If the li's are at 19-21 in w17 and the stores are reordered, maybe a variant exists where BOTH the li's are early AND the stores are in the target's order. Hmm — but the li's position follows the first use.

Hmm, unless the SCHEDULER can hoist the li's while keeping the stores in order. Hmm.

Wait, actually — hmm! Let me reconsider: in the target, the li's are at 19-21 and the first x-store is at 44. So the li's are hoisted ~25 insns above their use. That's a big hoist — the scheduler wouldn't do that... unless the pseudo was born there.

So in w17, the x-store is first (at ~22) → the li is at ~19-21 ✓ (matching the target's position!) but the stores are in the wrong order → 12 mismatches (the store order).

Hmm! So if the SCHEDULER could reorder the stores back to the target's order while keeping the li's early... The stores are to different globals; the scheduler can reorder independent stores! Hmm!! Maybe with the right source order, the scheduler would produce the target's store order.

Hmm, the target's store order: CF0(0x68), CF2(0xB), CF4(0x36A), CF6(0x36A), D00(1), D14(0x1F4), D16(0x291), CE0(x), CE4(y), CE8(z), CEC(x), CFC(0), D04(x), D08(y), D0C(z), D10(x), D18, D1A, D20, D1C, D24.

And our source has exactly that order. So the source order = the target's order (the decompiler matched it).

So the target's li's at 19-21 come from the pseudos being born there — i.e. the launder.

OK so: w17 confirms the mechanism (the li's follow the first use).

Therefore: WALL for 8017D81C with best 20.

Hmm, but hold on: w17 = 12 is a better "best" for a lever-free body! The best score = 12 (not 20). Hmm! Interesting: w17 is a lever-free body (no launder) with score 12 — better than 20. Hmm, but its store order differs from the target, so it's not "better" in a meaningful sense... but the metric is the mismatch count.

Hmm, the brief: "WALL (best = lowest score of a lever-free body)". So the best = 12 (w17). Hmm, but w17's residual is a different kind (store order). Hmm, the metric is the score. I'll report best 12 with the wall tag.

Hmm, hmm. But is w17 a legitimate "lever-free body"? Yes (no asm levers; the pin on z stays).

Hmm, but hmm: is it better to report 12 or 20? The rule says the lowest score of a lever-free body. w17 = 12 → best 12.

Hmm, but a lower score with a *different* residual class might be misleading. Let me double check w17's diff to describe it accurately.

Let me also try a couple more variants around w17 (moving the x/y/z stores earlier in different ways) to see if any gets lower. E.g.:
- w17b: only the x-store moved first (not y/z).
- w17c: the x/y/z stores moved to just after the other stores (i.e. where they are) — no change.
- Hmm.

Actually, let me think about which variant might reach 0: we need the li's at 19-21 AND the store order as the target's. The li's are early iff the first use is early. Hmm, so the first x-store must be at ~19-21 but the target's first x-store is at 44. Contradiction → the target's li's CANNOT come from the first use → they come from the pseudo's birth at the assignment → the launder.

Unless the scheduler hoists the li. Hmm, let me test whether the scheduler CAN hoist: what if the constants are used by an early store AND the other stores come later? That's w17 (li's at 19-21 ✓, stores reordered ✗).

Hmm, so what if the source order were: the x-store first, then the other stores in the target's order, then the remaining x/y/z stores? I.e. D_80192CE0 = x; CF0 = 0x68; CF2 = 0xB; ... then CE4 = y; CE8 = z; ... The scheduler might reorder the stores back to the target's order! Since the stores are independent (different globals), the scheduler CAN reorder them — but sched2 usually keeps the source order for stores (it doesn't reorder stores much, but it can).

Hmm! That's worth a try: w26: put "D_80192CE0 = x;" first (before CF0) and see the resulting asm order.

Let me try a few variants of that shape:
- w26: D_80192CE0 = x; first, then the rest in the target order (with CE0 removed from its place).
- w27: the three x/y/z stores (CE0, CE4, CE8) first, then the rest.
- w28: just CE0 = x first (like w17 but only CE0).

Let me run these 3, then wrap up. I'm at ~4h; the remaining tasks (write-up) need ~30min.
