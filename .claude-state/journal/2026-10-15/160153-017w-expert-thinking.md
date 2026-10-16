---
ts: 2026-10-15T22:01:53.538Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
I notice the hash names in the struct_map have drifted heavily between census times — what was 1230 sites before is now showing as a different hash with only 10 sites. Since the band list is keyed off these census map names which shift after header batches, I need to re-resolve the mapping rather than relying on the frozen names.

But thinking through when a cluster's structure would actually change: sites already in P-cast form (not yet respelled to canonical types) should have unchanged cluster structure regardless of header edits, since our generated definitions only use scalar fields. So header-only additions likely cause minimal drift, and the cluster naming (via lowest func addr or sha1 of root) should stay deterministic as long as the union-find ordering is consistent.

At scale, with roughly 6,676 band types yielding maybe 4-5k new struct definitions added to the header, that pushes the file toward 1.5MB, which could slow compilation across thousands of translation units by maybe 30 seconds total — acceptable but worth noting. I don't think these typedefs affect codegen or byte-matching, though I should watch for naming collisions between generated `Unkstruct_<addr>` names and anything else.

Importantly, collisions could be worse than cosmetic: if a .c file already has its own local typedef with that exact same canonical name, defining it again in the header would cause a C89 redefinition error. So I need to scan src and include for existing `Unkstruct_` identifiers before generating definitions, and apply a suffix like `_2` when a collision is found.

For the actual rendering of definitions, I'm using the struct renderer keyed on the target name, and classifying failures consistently: when rendering refuses with a negative offset, that's an INTERIOR-type issue, otherwise it's a NO-LAYOUT case.

I'm checking whether pointee typing is needed here but decide to keep the flat max-site layout approach that T2 used, referencing its header comment around those lines. I'm also working out the batching strategy across the three band ranks, confirming decision rows get written for every band type first, then definitions get written in those banded batches afterward — any residue rows pointing to non-canonical targets before the header defs exist should just resolve harmlessly as before.

Thinking through the self-contained batch design: each batch decides fresh census names, writes rows plus headers, runs R22, commits, and re-censuses to check against the next range's ranks, since frozen names from one batch can drift and need re-keying before the next batch starts.

For re-keying a missing frozen name, I'd want to find the owning address from the census sites rather than add an extra `owner` column to tnc_band.tsv, since the spec only lists rank, map_type, sites, bodies, and cumulative %. I'll avoid over-engineering and only build the re-keying logic if the missing count is actually nonzero, then move on to figuring out what the ledger and global decl types require for folds E1 and E2.

For E1, I'm defining the fold: for a band type T, gather its TNC census sites, check each site's body for the latest ledger row with the same base and a MEMBER verdict, then see if the drawn type C accounts for at least 50% of T's sites and dominates at 90%+ of matches to justify folding T into C with an E1-lineage evidence tag.

I'm uncertain which ledger field actually names the drawn struct type for a base — that's something the coder will need to locate through the retriever, since I only have a rough example from the T2 log showing a case where most TNC sites sit in bodies whose rung-S rows drew the base as a particular unknown struct. I'm also considering an alternative, simpler signal: whether census sites with declared canonical bases versus remaining cast sites with mismatched map types reveal the same pattern without needing that ledger field.

I'll just describe the semantics for the coder: the base's drawn/declared type in a body should be read as whatever the latest rung-S ledger row (MEMBER entries) lists for it, not necessarily what the census map records. Then I need to note a fourth binding — the TYPE-BELOW-BAND rule — and decide whether restruct.py's verdict list at line 401 needs to explicitly mark it as settled.

Body-level verdicts and site-level causes are distinct; TYPE-BELOW-BAND shows up as a per-site RESIDUAL cause via a residual fold row, so I need to check how a residual fold for a type translates into the body's overall verdict, drawing from the per_base status logic around lines 841-855 and 1351. Let me scan lines 830-860 to pin this down.
