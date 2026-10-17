---
ts: 2026-10-17T16:53:06.153Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 79d8481e-7d87-40f8-87a0-65e068183d9a
usage: {input: 6, cacheRead: 215078, cacheWrite: 914, output: 774}
---

I've told T11's expert to re-deal the batches nobody has started, W08 to W50. The other batches, and any function already handed out, stay where they are:
- **Unchanged:** the 7 batches already running (W01 to W07), the Haiku test and the external-model batches.
- **Grouping:** the batches that haven't started are dealt by lever kind first, then by source file within each kind, with about 8 to 12 functions per batch.
- **Shared notes:** coders keep one shared notes file, `.run/P40/T11/moves.md`. Every coder adds a line after each function, with the move that cracked it or the wall it hit, and reads the file before starting its batch.
- **Same limits:** the same 20 to 30 minutes per function, the same cap of 4 coders, and the same committer.

The summary will also compare the grouped batches with the first 7, in crack rate and tokens per function, so we'll see whether grouping really pays off.
