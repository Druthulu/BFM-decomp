---
ts: 2026-10-15T21:25:28.032Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: f343d920-17a1-4fc5-8d01-815d88dd1268
usage: {input: 6, cacheRead: 237948, cacheWrite: 2854, output: 794}
---

The revised 3.40 plan is in the plan view. It keeps T1 and T2 done and leaves the lever tasks exactly as you approved them. Three of the planner's own choices are worth a look before you approve:

1. **The tail's reason is named "TYPE-BELOW-BAND".** The tooling assigns it by rule, never by hand. It's capped at the size of the tail, so a struct inside the band can't quietly slide into the tail later.
2. **The band is a frozen list,** `config/tnc_band.tsv`. T3 builds it once from today's census, so it stays exactly the 6,676 types you agreed to. A threshold rule would land on a different count.
3. **New safeguards:**
   - The restruct cycle now stops when a batch has nothing left to do, which fixes T2's stall.
   - The final gate now checks the residue breakdown directly, because the old exit code ignored it.
   - The ledger-backup task (now T15) checks each public copy for disassembly itself and keeps it under 50 MB.

One loose end is outside this plan. The 3.40 entry in `GENERATION_PLAN.md` still has the older wording. That wording doesn't mention not-canonical residue, so nothing contradicts the change, but I can bring it in line after you approve.

Nothing starts until you approve.
