---
ts: 2026-10-15T22:54:17.331Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I'm thinking through how to build a canonical "twin" lookup index for decide_band—I need a helper that walks canonical headers using the existing worker, computing a hash/signature per definition so I can resolve names consistently, likely reusing tc's existing Resolver class for this.

Since name_sig and sig_of are inner functions in run_census and not importable, I'd need to duplicate the signature regex rather than modify type_census.py, citing the source lines in a comment for traceability—acceptable duplication given the constraint that file must stay untouched. For rendered defs, I can parse snippet text through walk_file and build a Resolver scoped to canonical globals plus the local def, since rendered fields are only scalar types so the resolver's needs are minimal; the canonical index itself maps each location hash to its set of meaningful signatures and names, letting me apply the tier-1 opacity rule by comparing against those sets.

I'm working out how to generalize the tier classification: combine existing meaningful sigs with the new def's sig, and if the resulting set has at most one element, it's a tier-1 twin, with the canonical name chosen as the minimum name among matching defs (or minimum existing name if the match comes only from the new def being opaque). I also need to decide whether the index should include defs from the same batch or an existing T3 block already present in struct_types.h.

Since struct_types.h is a canonical header, those defs are already indexed as opaque, so two new opaque defs in the same batch would just be tier 2. I should also check whether the canonical index needs to cover non-canonical .c file defs too, since the census pulls from defs_all — I'll check the CANON_HEADERS list to see what's actually covered, and confirm the layout hash handles the packed attributes correctly.

For the twin check, since it has to run before any name allocation happens, I need to render the text using a placeholder name — the layout hash and signature don't depend on naming anyway, and the existing t3_residual function already returns rendered text keyed by map name.

For the --write behavior appending new define targets to the "Dead kept" section of the docs file, I need to figure out where that section actually lives in the document — whether it's always the last section or something else — so the insertion stays deterministic and idempotent.

Since struct_twins --write only regenerates the "## Twins" section, Dead kept stays untouched. Now I need to handle the third item: for UNBOUND names that are define targets in type_folds.tsv, I should add U evidence pulled from census sites of the relevant map types, which means digging into struct_twins's collect/uses/has_addr/write functions more closely.
