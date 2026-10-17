---
ts: 2026-10-17T08:49:31.296Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
I'm seeing 440 targets against a brief that expected roughly 443, which seems fine since headers are excluded in this mode — the 8 missing ones are just headers that would need the --headers flag. The 133 extras look like duplicate function names with sites, and rerunning with --rejudge should be harmless since they'd only get banked if identical, though their ledger rows would update either way.

Since `--only` works as OR not AND, I can't restrict to avoid both issues at once, so the ~25% overhead from extras seems acceptable as harmless rework. I'm checking whether any extras have pending non-trivial states — but since the ladder judges against current text and only identical removals bank, re-judging should just reconfirm the same verdicts. With 551 files covering 565 bodies and each body taking roughly 8 seconds single-threaded, I want to prototype on a small set first — so I'm figuring out which target names have an exact match count between drawn and target with no extras, then writing a quick filter to list those candidates for a 2-3 item test run.
