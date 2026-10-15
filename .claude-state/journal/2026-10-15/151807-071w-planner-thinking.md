---
ts: 2026-10-15T21:18:07.057Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab5a3773d37dd2401
model: claude-opus-5-5[1m]
effort: high
turnId: 5357bd4a-9af8-47c8-b7d6-78b8d0e3eabd
---
I'm checking whether R3.40-005 exists and what tooling restruct.py already offers for computing bands and mechanized decisions, since T3 needs decision tooling built around type_folds.tsv, the restamp interface, and the residue_cause fold path. I should pull a retriever report on the shape of config/type_folds.tsv and the relevant functions like type_folds(), fold_type(), and the new residue_cause logic.

I also want to understand where residual causes like TYPE-UNION originate, how the residue_census tnc block works, and whether a new cause such as TYPE-BELOW-BAND could plug into residue_cause without touching other levers. I should verify whether tools/ledger_backup.py actually exists, check the residue.pairs field in the restruct ledger, look at the audit_public tool and the tools-edit-kit-corpus rule/skill, and confirm restruct_cycle.sh's zero-work exit behavior.

I also need to check if there's a queued add-task sitting in .run or a mod queue -- I'll grep for "ledger_backup" to find out. And I should consider whether a REPLAN is allowed to amend the milestone header, since DECIDED implies yes, and whether the generation plan's phase 3.40 entry needs the same amendment, which I'll flag in the report rather than fix myself. Time to run these quick checks before spawning retrievers.
