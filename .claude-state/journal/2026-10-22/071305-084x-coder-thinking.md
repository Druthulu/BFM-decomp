---
ts: 2026-10-22T13:13:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_W85EGRX559s0V6ekuI4X
---
Item 3: best 4 ✓, tries now 33 ✓.

Now let me write everything up:
1. notes.md per item (in the item dir).
2. results.tsv rows (4 rows).
3. moves.md lines (4 lines).
4. The log phase-ends/current/logs/T11.cG16.md.

Wait — the brief says "no git, no commit" for this task? Let me re-read: "CONSTRAINTS: ... write only under .run/P40/T11/G16/ plus appends to .run/P40/T11/moves.md (never src/, include/, config/, tools/, build/, other shards, shared helpers); no make, no git, no commit".

So: NO COMMIT for this task. But the system prompt says to commit when green... The brief explicitly says no commit (it's a scratch-only shard: "singleton crack shard G16 (scratch-only)"). The brief overrides (it's the task spec). Hmm, but the log must be written: "LOG: phase-ends/current/logs/T11.cG16.md". The brief says to write only under .run/P40/T11/G16/ plus moves.md... but it also says to write the log at phase-ends/current/logs/T11.cG16.md. So the log is allowed (it's explicitly requested).

And "no commit" — so I should NOT commit. The task is "scratch-only". I'll note that in my report. Hmm, the system prompt says "When green: commit with tools/commit_task.sh..." but the brief says no git/no commit. The brief is the task spec and it explicitly forbids commits (scratch-only shard). I'll follow the brief and not commit; I'll state that in the report.

Hmm, tricky. The expert's brief says "no make, no git, no commit" — that's an explicit constraint from the expert. I'll respect it.

Now, the results.tsv format: `dir file func kinds result best tries wall evidence` (tabs).
- dir: the item dir name
- file: the TU file (src/shared/ov/func_....h)
- func: the function name
- kinds: launder
- result: MATCH | PARTIAL:<kinds> | WALL
- best: the best score
- tries: the number of scored tries
- wall: for a WALL/PARTIAL, a tag from walls.txt or a new `<pass>-<what>`; for MATCH, "-"
- evidence: "gcc pass + mechanism ≤ 140 chars"

Let me now write the results. But first — should I record the best bodies? The brief says "each MATCH/PARTIAL has its win.c scoring 0" — for a WALL, no win.c is required, but it's good practice to save the best body. I'll save the best body as `best.c` in each item dir (hmm, the brief mentions win.c for MATCH/PARTIAL; for a WALL I'll save best.c).

Hmm, wait. Let me reconsider the results for items 2 and 3 once more. Their best is 4 with the plain no-launder body. Hmm, "best = the lowest score of a lever-free body" ✓ = 4.

For item 1: best 20.
For item 4: best 4 (the n1/q3 body).

Hmm, for item 4, is a score of 4 really a WALL? Let me reconsider: the row would be "WALL" with the tag. The evidence: "gcc pass + mechanism".

Let me now define the wall tags:
- Items 1, 2, 3: `cse-const-addr` (an existing tag in walls.txt) — the mechanism: cse substitutes the constant address into the use; only an opaque (asm) base keeps the base in a register.
- Item 4: a new tag. The mechanism: the ax/by re-tie's second set must be free; a plain-C second set on a widened (u32) var emits an `andi` (the zero-extension) that the asm re-tie does not, and a 16-bit var's second set is folded → no free second set. The pass: hmm. The `andi` comes from expand/combine; the scheduling effect from sched1. Let me name it `expand-secondset-andi`? Hmm, the tag should be `<pass>-<what>`. Let me use `sched1-free-secondset` — hmm, but the andi is the blocker, not sched1.

Let me name it: `expand-secondset-andi` — "a plain-C second set on a widened var costs an andi (the zero-extension of the truncation); the asm re-tie is free".

Hmm, alternatively `reload-secondset-andi`. I'll go with `expand-secondset-andi` and define it in the evidence.

Hmm, also for item 4, the residual also includes the ay+117 sink. I'll mention both.

Now the evidence field (≤140 chars): "gcc pass + mechanism". The gcc pass = the command that produced the score, e.g. "delever_search --try src/shared/ov/func_8012C2D0.h func_8012C2D0 gen_base.c --body → score 4". Hmm, that's already ~80 chars. Let me keep it tight.

Let me write the evidence strings:
- Item 1: "dt.sh gen_base.c: score 20 (90 vs 84 ins); cse substitutes &D_800AE620 into every load -> 6 rematerialised lui pairs; only an opaque base keeps $5"
  Hmm, ≤140 chars. Let me count: roughly 135 ✓.
- Item 2: "dt.sh gen_base.c: score 4 (19 ins); cse folds (plus &D_80120194 0x658C) into one address; the target keeps the base in $23 -> addiu a0,v1,25996"
- Item 3: same as item 2.
- Item 4: "dt.sh gen_n1.c: score 4 (208 vs 207); a plain-C 2nd set on a widened var costs an andi; the asm re-tie is free; ay+117 also sinks late"

Now the tries counts:
- Item 1: 31 scored tries.
- Item 2: let me count: w1, n2, n3, b1-b5 (5), x1, + 28 variants = 1+1+1+5+1+28 = 37. Let me say 37.
- Item 3: 23 + 6 (z) + 4 (y) = 33. Hmm, the earlier ones: I scored gen_* for item 3 = 23, z = 6, y = 4 → 33 ✓.
- Item 4: w1, w2, v6, v7, v8 (5), g1-g5 (5), h1,h2,h6,h7,h8 (5), m1,m2,m3 (3), n1,n2 (2), o1-o4 (4), q1,q2,q3 (3), gen_id_axby, plus0_axby, keep_op_only, id_ax, id_by (5) = 32 ✓.

The wall time: the brief says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`" — that's the TAG column, not a time. Hmm, but the column name is "wall" — in the INTERFACES: "results.tsv row (tabs) `dir file func kinds result best tries wall evidence`; result MATCH ... | WALL (best = lowest score of a lever-free body); wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". So the "wall" column holds the TAG ✓.

OK. Now let me write the files. Also the moves.md lines: `kind | func | MATCH: move / WALL tag — mechanism (G16)`.

And the log: phase-ends/current/logs/T11.cG16.md with the timeline per item (start/end times, minutes, tries).

Let me get the times. I started at ~06:37. Item 1: 06:37-07:00ish; item 2: 06:41-07:35; item 3: 07:35-08:10; item 4: 08:10-09:50. Hmm, I don't have exact per-item timestamps. Let me record approximate times from the commands I ran:
- The baseline scoring ran at ~06:38.
- The item-2 variants were generated/scored at ~07:05-07:20.
- Item 3's variants at ~07:25-07:35.
- Item 4's variants at ~08:15-09:45.

Let me be honest: I'll record the times I actually observed (from the `date` outputs I saw): 06:41:42 (the item-2 first score), 06:47:57-06:50:31 (the item-2 sweep). And the final date now.

Let me capture the current date and compute the timeline approximately. I'll note the approximate per-item windows honestly.

Let me write the files now. First, the per-item notes.md and the best bodies.

Also: the brief says the disk is capped and the cc1 dumps must be deleted. Let me remove the dumps dir (.run/P40/T11/G16/dumps) ✓ and check the shard dir size.

Let me also verify the FRESH requirement: "at each item's start diff <dir>/orig.c against the def in the current src file (src moves as earlier batches bank); if it differs, regenerate orig.c/nopin.c from src and say so in notes.md". I extracted orig.c from the current src at the start ✓ (all 4 were extracted from src at the beginning). Let me re-verify now (at the end) that the src hasn't changed since (i.e. orig.c still matches src) — a quick diff. If src changed, my results would be stale.

Let me do that check now, then write up.
