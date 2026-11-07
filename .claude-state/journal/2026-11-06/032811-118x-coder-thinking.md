---
ts: 2026-11-06T10:28:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OWuIGP27tshpT4SGrEIj
---
src/, include/, config/, tools/ are clean (no changes). My shard files are untracked (gitignored presumably) — .run is gitignored, so they don't show. moves.md is also under .run (ignored). The log file is untracked (new).

Wait — `.run/P40/T11/moves.md` is under .run (gitignored), so my append won't be committed (no commit anyway).

Everything is in order. No commit per the brief.

Now let me reconsider the deliverable one final time before writing the report. The brief's RETURN: "your final message starts with the bare word done (or blocked) as its very first word, nothing before it; + ≤ 10 lines: per item dir result best wall; nothing else."

So my report:
```
done
func_8017F1F0__ov_SC03_001_jr_8017AE2C  WALL  best 15  expand-void-return
func_80180AC4__ov_SC03_028_jr_8017DF98  WALL  best 23  expand-void-return
func_801803D0__ov_SC03_096_jr_8017BEBC  WALL  best 28  expand-void-return
func_80180E64__ov_SC03_121_jr_8017E1D0  WALL  best 7   greg-ref-count
```

Hmm, the brief says "per item dir result best wall; nothing else". But the system prompt's coder report contract says: "starts with one plain word, done, question or blocked, then what changed and the commit." Since no commit (scratch-only), I'll note that.

But wait — I should double-check whether the task really expects no MATCH. Let me reconsider item 4 once more, since it's the only one with a plausible crack. The residual is a single register swap (f vs giv). I tried ~39 variants. The G26 parent had a similar wall (func_8017DD04 greg-ref-count, 36 tries). So 39 tries and a WALL is in line.

However, let me reconsider: maybe the target's f=v1 could be achieved by making the giv *not* strength-reduced, i.e., removing the giv entirely and computing `D_801AECD8[i1]` each iteration. Then the address computation would use i1 directly. Would the code match? The target HAS the giv (addiu a1,a1,4). So no.

Or making the loop index a pointer: `for (p = D_801AECD8; p < D_801AECD8+5; p++)` — that's the d9 variant (12).

OK, WALL it is.

Hmm, one more: the brief says "Budget 20-30 min wall per item (date at start/end)". I have `date` at start (02:54) and now (03:26). Item 4 started ~03:00, so ~26 min. Good. Items 1-3 also ≥26 min.

Actually, let me get the current date for the record.

Also, I should update the log with the final try counts (item 1: 34, item 2: 32). Let me fix the log's try counts to match results.tsv:
- Item 1: "35 tries" → "34 tries"
- Item 2: "31 tries" → "32 tries"

Let me edit the log.
