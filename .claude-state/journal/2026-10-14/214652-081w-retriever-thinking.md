---
ts: 2026-10-15T03:46:52.092Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab979db8361de1187
model: claude-haiku-5-5[1m]
effort: medium
turnId: 243a97c8-7e46-4136-94de-b425c226ce82
---
I'm finding solid evidence in lever_residue rows 149 and 153 for those two functions, pointing to missing-parameter causes, plus a dedup conflict row for func_8016BF50. I still want to verify a few specifics, like the exact content of lever_residue line 149 and the T10/T9 references.

Looking further, I'm tracing the compile-error attempts in Phase37 for t4_sig9/t4_sig10 around lines 617 and 619, and the return-type lies case that seems parked without a clear attempt outcome. I need to grep for the specific function names across Phase37 logs to pin down which TUs are involved in the same-address copies and return-type lies issues, and check whether PhaseEnd_Phase3.38 even has matching T7 entries before moving on.
