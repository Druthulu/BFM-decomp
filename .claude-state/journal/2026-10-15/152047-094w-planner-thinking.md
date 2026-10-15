---
ts: 2026-10-15T21:20:47.993Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab5a3773d37dd2401
model: claude-opus-5-5[1m]
effort: high
turnId: 5357bd4a-9af8-47c8-b7d6-78b8d0e3eabd
---
With no AUDIT.md and no new rules, I'll keep the existing triage line as is while I wait for the retrievers, and refine the milestone so every residue item from 3.39's ledgers is either genuinely fixed or still clearly marked with its pass, instrument, and cause.

The verification runs type_census.py checking casts and residue, requiring TYPE-NOT-CANONICAL to be zero for all 6,676 types within the 95% band, with the tail below that band folded into RESIDUAL rows under a single new rule-defined cause whose count is stated — leaving the by-cause line entirely free of TNC. I'm now considering naming that new cause something like TYPE-BELOW-BAND, tied to a rule about single-use or below-band types.

But I'm worried about stability — the band membership needs to be frozen mechanically rather than redefined each census run, since hash names for map types can drift between runs and break membership if it's keyed by name. A threshold-based rule, like sites ≤ some small number, seems more robust against drift than a frozen rank-based list, so I'm trying to work out what site-count threshold would land near the 95% cutoff given the tail's roughly 6,066 types and ~7k sites, averaging about 1.15 sites per type.

The band is whatever's needed for cumulative sites to hit 95% of post-T2 census. I'm realizing hash drift is a deeper problem: since type_folds.tsv keys off hash names that can shift when new bodies appear, this same instability already affects the fold decisions, not just the band. The residue ledger stamps the cause at the time it's recorded, so if the hash drifts afterward there's a mismatch to account for.

I think the cleanest fix is a stable, census-independent rule like a per-type threshold on site/body counts, rather than something tied to the exact 95% band, since that band shifts as census changes. The developer wants the tail (~7k sites) to carry its own named residual cause determined by a tool-applied rule, not manual judgment — so I'll leave the exact threshold to the T3 expert but flag that whatever rule they pick needs to be robust against hash drift.

I'm defining the cause name as `TYPE-BELOW-BAND`, fixed for clarity in milestone wording, with a deterministic rule: a frozen band list in `config/tnc_band.tsv`, generated once from the post-T2 census (closed at commit 63fc7e8bf6), sorted by site count, body count, then name, cumulative up to 95% of the 139,520 TNC sites — any map type that's not canonical, not in type_folds, and absent from that frozen list gets tagged with this cause.

I'm uncertain whether a census re-run after respelling bodies could shift struct_map clusters, since those are inferred from casts that may disappear once things are respelled to members — this is a real drift risk, so I'll flag it under Risks and require T3 to confirm the band list stays stable across a re-census, falling back to a drift-proof key like an address anchor if it doesn't.

For the milestone check, I want the frozen 95% list to remain the fixed rule rather than something recomputed from sites or bodies, so stability must be verified rather than assumed. The instrument should show a by-cause residue line with zero TYPE-NOT-CANONICAL and a bounded TYPE-BELOW-BAND count consistent with the stated ~7.0k sites over roughly 6,066 types.

Since the band list is frozen, band types can't shift into the below-band category, so I can add a sanity check that band-list types carry zero TYPE-BELOW-BAND by construction. I'm also noting the TNC-zero requirement applies per layout class, that there's a NO-EDIT restamp variant around 9.6k sites, and that T3 needs a zero-work exit path for restruct_cycle.sh to avoid a stalled redraw.

Since restruct_cycle.sh is a project tool rather than harness code, adding that exit is a legitimate project change requiring wiring and doc updates. I'm settling the T3/T4/T5 split so T3 handles decision tooling, band decisions, and header batches, while the later tasks do the re-sweeps.

T3 defines types for the band and the below-band cause rule, plus the restamp variant for tooling, then T4 sweeps ov and T5 sweeps md/main/shared, stamping TYPE-BELOW-BAND rows afterward. I'm weighing whether the restamp of below-band/NO-EDIT rows belongs in T3 since it's a ledger rewrite rather than a body respell — but if T3 restamps everything before T4/T5 finish sweeping, band types' sites would get stamped with a stale cause before the sweep happens.

So restamping needs to happen per segment in T4/T5 after their sweep completes. T3 should cover tooling, decisions, headers, and the below-band rule with a selftest on a sample; T4/T5 handle sweep, residue, restamp, and check-residue, with explicit done-when criteria about TNC and TYPE-BELOW-BAND counts. I'm also checking that check-structs tolerates dead names until T4/T5, since defining band types in T3 creates defs with no users until the sweep marks them.

For T3's workload, T2 was the judgment-heavy step, so T3 is now mostly mechanized medium-effort work — fold detection via E1/E2/E3 tooling. Sizing-wise, after removing the 75 already done, the band computation spans the remaining 12,742 types, giving roughly 6,676 band types across ~132.5k sites, which maps to about 4.5k new defs in struct_types.h, processed in batches of 216 → 1,834 → 6,676.

I'm weighing whether T3 should split into tooling, decisions, and headers, but it's sizeable yet coder-driven, so I'll keep it intact. Similarly, T4's sweep runs ~9.9 hours at 4.48 min/1k, but since one expert task can handle multiple batches with handoffs, I'll leave the structure as approved rather than splitting it further.

I also need to account for the --restamp variant tooling built in T3 but executed in T4/T5, plus the one-time run covering the 9.6k sites in the TYPE-NO-MEMBER types from T2.

T3 also needs to handle the zero-work exit gotcha for cycles, wiring the fix into restruct_cycle.sh via R127 so a cycle on a set with no drawable sites exits cleanly after one zero batch. For T13's verification, I'm stuck on how to express "no TNC in by-cause" through a return code alone, since type_census.py's check-casts rc ignores by-cause — meaning "no TNC" and "lying 0" have to be confirmed by reading the text output rather than relying on exit status, which may require adding a dedicated check script or band-check flag to T3.

Refining the grep pattern to match digit-only occurrences so a zero count doesn't trigger a false failure, and chaining the commands with `&&` to preserve the return code properly, plus adding a mkdir step to ensure the output directory exists.

I'm now drafting the milestone wording itself — stating that every residue item from 3.39's ledgers is either fixed or still tagged with its pass, instrument and cause, with TYPE-NOT-CANONICAL eliminated across the 95% band (6,676 types frozen at the post-T2 census).

The tail below the band falls under RESIDUAL rows with the single cause TYPE-BELOW-BAND covering roughly 7.0k sites, so the by-cause tally drops both TYPE-NOT-CANONICAL and the lying count to zero. I'm also listing the other checks that must pass clean: the restructuring rung check, the structs check for duplicate defs and dead names, and the lever census check against the literal gate derived from 3,528 sites across 2,433 residue rows.

I'm settling on TYPE-BELOW-BAND as the cause name since naming is my own engineering call, not something the developer dictated. But I'm worried about drift — if the frozen band list is keyed by hashes that can drift, the "not in band list" rule could misclassify a drifted band type as below-band and inflate the count dishonestly. So I want to add a safeguard to the milestone's done-when criteria: TYPE-BELOW-BAND's count must stay at or below the roughly 7.0k-site tail measured at freeze time, since any excess signals a band type that drifted rather than a genuine below-band case.

I'm also checking that T3's frozen tail count and every TYPE-BELOW-BAND type's absence from the band list get verified by a stability control — rerunning the census to confirm all band-list names still resolve, falling back to anchor-based keys if any go missing. And I need to pin down exactly which census T3 freezes from: it should match the post-T2 census state (139,520 TNC / 12,742 types) since T12 only snapshots without changing source, so T3's verification should align with that close-of-T2 tree.

I'm also considering task ordering — whether T6 (which depends on T1 and modifies source signatures) could run before T3 and cause census drift, since tasks seem to execute serially per the file order rather than in parallel. If T3's recorded figures (6,676 types / ~132.5k) differ even slightly from T2's milestone numbers, that discrepancy needs to be flagged explicitly rather than silently reconciled.

For the TNC residue census, TYPE-BELOW-BAND gets stamped by residue_cause at write time, and the restamp step covers tail types even though they have no definition body to sweep — meaning the drawable set must explicitly exclude them to avoid shrinking incorrectly. I'm now checking whether by_cause type_census entries need separate registration.

I'm revising the T4 done-when condition: since tail sites get restamped to TYPE-BELOW-BAND, the "no site keeps TYPE-NOT-CANONICAL" criterion still holds, so I just need to add the restamp steps and a NO-EDIT variant. For T5, the check-casts residue condition also stays valid once the tail is renamed, so I'm phrasing the done-whens as TNC being zero within the band while the tail is stamped as TYPE-BELOW-BAND with a count no greater than the frozen tail, leaving by-cause free of TYPE-NOT-CANONICAL.

Now I'm going through the bullets that need updating: line 8 needs post-T2 figures for TNC concentration, line 9's anomaly gets resolved by T1/T2, and line 11's stale "about 6 min" fan-out figure should become 51 seconds. The rationale and risks sections need the planner's judgment swapped for the developer's actual decision, and I should check whether the open items (cap of 4 coders, ledger durability) were already settled at the 2026-10-14 approval so I can record them as resolved in Developer decides.

For the Changes section, I think it's best left untouched since plan_edit writes those lines directly and a REPLAN redraft doesn't need manual edits there. The header's Approved/Planner/Plan-hash fields should reset to dashes for the mod to fill in during approval, consistent with how a replan resets that state.

Now I'm thinking through T15's ledger backup placement relative to T14's docs task — whether T14 should depend on T15 so the documentation can reference the backup, or whether they stay independent since the REPLAN only specifies T15 comes after T13.

I'm weighing the size of the gzipped ledger snapshots against GitHub's 100 MB file limit, since the stripped JSON for later phases could compress to tens of megabytes and each phase's public copy accumulates in repo history.

I'll add a done-when guard requiring each public gz to stay under 50 MB — GitHub's warning threshold — with a blocked return if any copy exceeds that, since a push failure would be worse. I've also noted R3.40-005 applies to T3's state reconstruction loop, and now I'm waiting on the retrievers before closing out this turn.
