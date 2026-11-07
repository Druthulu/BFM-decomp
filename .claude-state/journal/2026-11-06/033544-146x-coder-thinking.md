---
ts: 2026-11-06T10:35:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VrJrJP71Kiql5MdsbTn3
---
Both orig.c score 0 (confirming they're the current src def, no drift).

Everything is in place:
- 4 results.tsv rows (WALL)
- win.c best bodies (1, 21, 5, 11)
- notes.md per dir
- orig.c per dir (score 0)
- moves.md appended
- log written
- dumps cleaned

I did not commit (the brief says "no make, no git, no commit").

Let me do a final summary of what changed and return the report. The report must start with `done` or `blocked`. Since all items have rows (the DONE WHEN is satisfied: every item has exactly one row; no MATCH/PARTIAL to verify), I'll return `done`.

Wait — the DONE WHEN says "every item of G27x/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." I have 4 WALL rows, no MATCH/PARTIAL. So done.

But hmm — the task's CHANGE says "write a lever-free body of func ... that scores 0". I produced 0 MATCHes. Is that acceptable? The brief's INTERFACES explicitly defines WALL as a result, and other shards are mostly WALLs. So yes, the shard is complete with WALLs.

Let me write the final report: per item dir result best wall, ≤10 lines.

Final message must start with the bare word done.

Let me also mention no commit (the brief says no git/commit).

Let me format:
done
4 items, all WALL (no MATCH); no src/ writes, no commit (brief forbids git).
- func_8017E8D8 (ov_SC06_014) WALL best 1 lreg-copy-pref-dying-base
- func_8012BA10 (hdr) WALL best 21 lreg-qty-priority
- func_8012BB3C (hdr) WALL best 5 sched1-birth-order (do-while(0) cracked the $16 pin)
- func_801535F4 (hdr) WALL best 11 global-hardreg-reserve
rows in .run/P40/T11/G27x/results.tsv; win.c = best lever-free per dir; log phase-ends/current/logs/T11.cG27x.md.

That's 7 lines. Good.
