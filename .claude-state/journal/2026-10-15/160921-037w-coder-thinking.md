---
ts: 2026-10-15T22:09:21.370Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
The census is still running, so I'll start writing the code for task T3 — setting up the frozen TNC band configuration file and defining the directory structure for the fold/residual/define decision process per band type.

I'm defining a `tnc_sites` function that pulls type-not-canonical sites from the census data via a residue split against the ledger's latest state, then a `band_rank` function that counts site types, ranks them by frequency, and determines the band cutoff where cumulative percentage crosses the threshold — mirroring the same accumulation loop used in the census logic.

Now I'm drafting the `freeze_band` function: it refuses to run if the band file already exists, otherwise computes the band and writes out a frozen header documenting the census commit, sort order, cutoff rule, band/tail counts, and totals, followed by a tab-separated table of rank, type, sites, and bodies.

I also need to cross-check the computed values against `residue_census.json`'s tnc sites/types/cutoff percentage, printing a match or mismatch and refusing to write the file if there's a discrepancy, while recording the source commit hash and census head for provenance. Then I'm sketching `load_band()` to parse the frozen file back into row dicts plus the band_n value, and starting to design the pure `decide_band_rows` function that will take rows, the struct map, census data, ledger state, canonical forms, folds, declared types, identifiers, and address mappings to produce per-row decisions, beginning with a lineage-checking component that walks each site for a given type.

Writing lineage inference logic...

After matching declarations, I need to resolve ambiguity when a global has multiple distinct canonical type declarations across files—treating it as unresolved rather than guessing, since full-source scanning could be large so I want to prefilter with a quick substring check before running the full regex match.

I'm also planning to collect `Unkstruct_` identifiers in the same scan pass to check for naming collisions, and I'm sketching logic for classifying a record's residual layout—flagging missing size hints, negative offsets indicating interior placement, and formatting those offsets appropriately for the report.

Working through the union-field detection: checking conflicts for overlaps versus differing field widths (parsed from leading digits in type tags), and distinguishing scalar single-field records from cases where the layout produces no usable entries at all.

Catching render failures as a "layout:refused" fallback, and settling that the no-layout result always wins when nothing else applies, even though the single-field rule stays in place. For the define step, I'm figuring out ownership by taking the minimum function address across non-null bodies, or falling back to the minimum address parsed from global symbol names.

For naming when neither exists, I'm leaning toward falling back to the map type's own name (with a collision suffix) rather than a hash, and tracking collisions against existing identifiers, prior fold targets, and map type names already used in this run, making sure new names never clash with canonical names either.

For rendering, I'm building entries that reuse the write_types layout and comment format showing band rank, TNC sites, and bodies count, but I need to account for the fact that define-targets get rendered under the target name while the residual-class refusal check should be done first using the map's own name, since refusal doesn't depend on the final name—so I'll render once for refusal purposes and then do the final render under the resolved target name.

I'm now mapping out the decision tuple structure (rank, map_type, action, target, evidence, note, facts) with specific note formats for fold/residual/define cases, then working through rank parsing logic to distinguish band rows from tail rows, and handling existing versus missing type_folds entries.

For tail rows I'm deciding whether the missing-from-map check still applies — concluding it does since the band is frozen at census time while live data should show zero missing now. I also decide to compute TNC site counts live at decision time rather than from the frozen band file, since the census could have drifted, and note that the regex-based normalization should be memoized for performance across the large site set before I start writing the append logic.

I'm sketching the output format for type_folds.tsv and the logic for inserting new struct definitions into struct_types.h, making sure new entries get inserted in the correct rank order within the marker block even if batches run out of sequence — I'll need to parse existing definitions to preserve ordering rather than just appending blindly.

I'll keep the dry-run columns simple, stashing rank inside the facts field as "rank=N" rather than adding a separate column, and dump any missing names as commented-out lines. I also need to print per-action/class counts (folds, residuals by cause, defines) plus skipped/missing totals, add a `--restamp-no-edit` flag, and then move on to building synthetic selftest data starting with a band_rank scenario across several site types.

Working out the band-cutoff tie-breaking logic and totals so the 95th-percentile band lands on an interesting boundary for the test fixture.

Let me settle on A35, B20(3 bodies), C20(2 bodies), D20(2 bodies), E3, F2 totaling 100 with cumulative hitting exactly 95 at band_n=4, ordered A through F, which tests both the tie-break on body count and the exact-equality boundary case.

Now I'm shifting to the decide-rules test using synthetic smap records and the `_canon` dict from the selftest fixture, which includes the Unkstruct_TEST canonical entry — I need the decide function to accept this `can` dict as a parameter.

I'm laying out the test cases: E1 checks a type with two TNC sites matching the canonical entry (folding when 2/2 sites agree, falling through at only 1/3), E2 checks anchor-based folding via decl_types, and then there are coverage cases for no-layout, interior offset, and union conflicts with mismatched member-size combinations.

For defining new types, I'm handling naming collisions by deriving the owner from the function address, generating names like Unkstruct_80010000 and suffixing duplicates (_2, _3) when the same owner already has entries. I'm also making the decide function accept an addr_of callable so it doesn't depend on a symbols file, defaulting to the function's own address since func_ names parse directly.

Now I'm adding a case for restamping ledger entries that have a NO-EDIT cause but whose site type is a residual union — these get rewritten to a TYPE-UNION cause with no_edit set to True.

I need the NO-EDIT restamping to use type_folds() for computing the residue cause since the selftest overrides the global folds, not a plain restamp that ignores NO-EDIT entries entirely. I'm also considering whether to write a quick test for the struct_types splice-by-rank function since its ordering logic feels a bit risky, even though the brief doesn't explicitly ask for it — I'll add a small check since it's cheap. Now I'm moving on to wiring things up per the SKILL tools-edit-kit-corpus, so I need to go read that.
