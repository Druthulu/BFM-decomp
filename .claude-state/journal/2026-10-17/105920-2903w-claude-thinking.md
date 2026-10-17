---
ts: 2026-10-17T16:59:20.910Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: a929cb8c-c58d-4431-838f-471430491695
---
I'm weighing whether "unk_" is the right prefix here, since "Unk"/"unk" is already conventionally used elsewhere for fully unknown fields, so this naming might collide and need a more distinct marker like "guess_" or "maybe_" instead.

Actually, I think the tiered approach works: `func_8001234` for nothing known, `unk_MutateHp` for a guess, and `MutateHp` once confirmed by evidence, paired with a names ledger tracking confidence and basis so promotion requires proof and agents know to treat unk_ names as hypotheses rather than fact, guarding against anchoring bias. Since correct types do influence codegen, better-informed guesses could plausibly help cracking, and renaming is cheap once tooling exists. I want to flag whether this changes the broader naming policy too, and note adding a wiki page on starting a new decomp project that documents this convention.
