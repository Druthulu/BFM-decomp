---
ts: 2026-10-15T22:04:53.995Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
The job has five parts. First, freeze the TNC band from a fresh census so it matches residue_census exactly. Second, make the fold/residual/define decisions mechanically from struct_map facts and the rung-S ledger, using the brief's rule order: fold only on detected evidence, otherwise residual with the four layout classes, otherwise define `Unkstruct_<owner>`. Third, add a narrow restamp variant that rewrites NO-EDIT entries only when their map type has a `residual` fold row. Fourth, add a zero-work exit to the cycle. I'll reuse `tc.residue_split` and the type_census cutoff loop instead of reimplementing either one, so the band can't drift from the census. Decisions only append and are dry-run by default, so nothing in src/ or include/ changes in this task. I'm starting the census first because it is the long pole.
