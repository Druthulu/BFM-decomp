---
ts: 2026-10-17T17:09:37.475Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 16d5b8ea-f552-421d-89cb-c6a3a79d628e
---
The prefix ladder idea has a flaw: tying confidence to a name prefix like guess_/maybe_/likely_ means every confidence bump forces a rename across many files, creating diff noise, and it conflates confidence with a separate conflict axis. Better to keep a single neutral prefix (guess_) in the name itself and track confidence level and evidence type in a ledger instead.

On comments: it's worth having agents add "why" comments when understanding clicks — explaining odd spellings, function purpose, workarounds — rather than attempting a blanket pass over the whole codebase without real understanding, since uninformed comments tend to be noise or wrong. Comments don't affect bytes but do add source churn, and overrides can just rely on git history rather than date-tagging.

Transcripts aren't worth mining either; most are archived, and what they'd yield is mechanics reasoning rather than semantic insight, and ledgers already capture the useful facts (walls, guesses). So the plan is: skip a transcript-mining phase, fold commenting into the naming milestone instead — whoever names a function writes a short header comment with its basis, plus a cheap mechanical pass that projects ledger facts (walls, guesses) straight into comments. I should bring this to the picker as an addition to the naming task plus a day-one rule, and separately acknowledge the naming milestone is already done since he confirmed it.

For the prefix question, I'll just queue a second picker sequentially rather than trying to combine it with the comments decision — two pickers run one after another is fine.
