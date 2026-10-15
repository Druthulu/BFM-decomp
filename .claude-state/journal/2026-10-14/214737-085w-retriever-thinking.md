---
ts: 2026-10-15T03:47:37.526Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab979db8361de1187
model: claude-haiku-5-5[1m]
effort: medium
turnId: 243a97c8-7e46-4136-94de-b425c226ce82
---
I have enough to write the report now. I'll keep the handback message dense and within the 40-line cap while saving the fuller detail to the pending file, using a slug like "3-40-residue-lane-planning-inputs".

The global rule against writing summary files doesn't apply here since this pending file is input to the digest tool rather than a standalone report — so I'll write it following the path convention under pending/ with a retriever-digest filename.

I should flag several discrepancies in the file: the milestone line position mismatch (P3.39:4 vs 5), conflicting replan dates for "reading A" between the milestone and lever gate notes, the TNC coverage numbers appearing inconsistent between T10 and T9 (281,252 vs 291,819), and a mismatch in struct-map type counts between T3 and T4.

I'm also tracking the cause breakdown rows (2,433 rows across 3,528 sites, split by head-class, singleton, missing-parameter, etc.), noting that no by-pass/instrument breakdown exists in the files, and pulling carry-forward items from T12 and D1 along with the recap verification details and the two "(none)" rules entries from PhaseEnd_Phase3.

I'm locating rules R123-R126, with R124 and R126 defining how raw-cast residue and asm-macro rows get covered, and gathering the next-task carry items for 3.40 scattered across T3, T4, T8, T9, T10, plus the lying-count discrepancy between P3.39 (11 ledgered) and P3.38 (229 over 24 callees). Now I'm looking at the legacy T7 status for func_801A1E94/func_801A5C44, where the cause is a zero-argument caller passing its own $a0 register, documented in PhaseEnd_Phase37 and the corresponding logs.

I'm also going through the attempted signature fixes for t4_sig9/t4_sig10 that produced compile errors for too few arguments, now parked but still open and ledgered as residue in 3.39. Then I move through the same-address copy cases (func_80185578, func_80188DF4, func_8017FC5C, func_80183CC4) and their parked status in Phase36, noting the brace-wrap issue flagged in T8, and finally the five return-type lies where functions declared void are actually used as returning values across multiple callers, with step (b) held pending step (d).

Checking config/lying_exceptions.tsv for these five function names against the broader lying census, I find no match, so their status against that census remains unverified. I also work through func_8016BF50's conflicting declarations across overlapping headers and TUs, confirming its kept, residue status from a prior K&R-marking pass.

I note that both 3.37 and 3.38 PhaseEnd docs restrict the T7 residue lane to agent-only handling under the user's cap, that LEGACY_INDEX has no T7 entries, and that 3.39's T7 was superseded by T7.1 — all details to fold into the pending file before drafting a capped, ~40-line handback summary that points to the fuller writeup.
