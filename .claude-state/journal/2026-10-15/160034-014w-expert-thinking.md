---
ts: 2026-10-15T22:00:34.664Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
I'm noticing the hash names have drifted — most T2 hash keys don't appear in the current struct_map, since the census likely named clusters differently than the canonical names defined later in the header. I need to check whether the type names in the residue census actually match these map types.

Since residue_census.json and struct_map were written at different times, they may come from different census runs, so I should just regenerate everything fresh — a full type_census with --check-casts --residue on HEAD, now that T2 is committed, plus tnc_types added.

Looking at T2's calibration for TYPE-UNION: cases with width conflicts or overlap-only conflicts get flagged, but some folded/canonical-looking structs also show big conflicts despite being defined as cf=0 in T2. So the actual binding rule seems to be simply "conflicts → TYPE-UNION," which is a blunt policy but apparently the one being applied.

I need to distinguish sign-only conflicts (same width, different sign) from true width conflicts — sign-only shouldn't trigger a union since that's handled by sign macros, while overlap entries (like a 4-byte field at offset 0 overlapping a 1-byte at offset 3) do need a union, matching how T2 treated 801345F8. So the precise rule is: TYPE-UNION only if a conflict entry is an overlap or involves more than one distinct width, not just a sign mismatch.

Then for ordering the residual checks: size_hint of 0 means TYPE-NO-LAYOUT (as with 57db4d07, which had negative offsets and overlaps but T2 still called it NO-LAYOUT), negative offsets alone signal TYPE-INTERIOR (like b6c7c603), unions come next, and a single field maps to TYPE-SCALAR. I'm testing this against 80130D48 (one field, size 2 → scalar) and 8016B4F8, which has one field but a size of 32, which seems inconsistent with the simple one-field-equals-scalar rule — maybe that field sits at a nonzero offset like 28, which would change the classification.

So I'm refining the rule: SCALAR should mean exactly one field *and* that field sits at offset 0, since a single field at a nonzero offset is really a genuine struct member access rather than a bare scalar pointer. Looking at 50a3f6b4 (size 54, three fields), T2 hand-labeled it NO-LAYOUT seemingly as a special exception rather than from the mechanical rule, and I'm noting that hand-labeled T2 rows already folded in should just be left alone rather than rewritten. Now I'm turning to how to mechanically detect the E1/E2/E3 categories.

For E2, I was thinking about anchoring on shared globals between a non-canonical map type and a canonical one, but then realize that if two clusters shared a global's AT node, union-find would have already merged them into a single cluster within one census — unless the 20-item cap on globals_at is hiding the overlap, which could still make E2 possible in capped cases.

Alternatively, the global's extern declaration type in source headers could flag canonical types directly, though that requires grepping headers rather than relying purely on census data. For E1 lineage, I'm tracing how TNC sites' base types line up with the ledger's S rows recording the canonical ctype for the same base — this seems mechanizable by checking each band type's TNC sites against their enclosing function bodies.

I'm realizing the mismatch between a site's drawn base type and its map type likely stems from name drift: the ledger entry used an older census's type name for the same canonical type, since map types are assigned per census cluster while the ledger retains whatever name was current when it was drawn.

For E3, field-wise copies would need direct evidence like matching assignments across all fields between two bodies, which is hard to generalize mechanically. Given the done-when criteria only requires detecting at least one of E1/E2/E3 rather than implementing all three, I'll focus on E1 (ledger drift) and E2 (global declarations of a canonical type).

For E2, I'm thinking of scanning src/ and include/ with a regex to find globals declared as `extern C D_X;` or `C D_X[n]` where C is a canonical struct type, since that directly tells me the global's real type when it appears as an AT base rather than a pointer.

For E3, field-wise copy detection, I'm considering skipping that implementation entirely and relying only on E1/E2 evidence — folding without strong evidence is riskier than leaving things as defines, so being conservative here seems like the honest default.

Actually the real insight is that union-find already merges any assign or field-level links, so cross-cluster E3 within a census can't really exist independently — it would show up as E1 drift instead. I should record this as a deviation/finding rather than implement separate E3 logic, and think through how name drift manifests when a map type's cluster root matches a canonical type's addressed cluster.

Ledger-based E1 is the real evidence source here — residue_split already loads the ledger latest for all bodies inside type_census, so cost isn't an issue. The simpler path is to use body_base_type.json, which maps body|base pairs to type and sites, rather than trying to derive this from the drawn census map type per base. I'm unsure how many TNC sites E1 will actually capture, so I'll just run it and observe. For the canonical naming scheme using `Unkstruct_<owning addr>`, I need to work out whether the owning address is the lowest function address or some hash-derived name, and for hash-based names, whether the owning address comes from the first global or the lowest function address among candidates.

For hash-named types (like the cb638a45 case representing a 3-function flow cluster), there's no func node directly in the cluster, so I'll derive the owning address from the lowest function address among the bodies containing the type's TNC sites from the census. If no global or function address is available as fallback, I need to decide what to do — possibly disallow hash-based naming entirely in that case and find another fallback scheme.

Collisions against canon_types and other new definitions need suffix handling (_2, _3, etc.). For writing the actual definitions, I need to trace through how `--write-types` renders previews from struct_map into include/struct_types.h, checking the existing restruct.py code around write_types and the related folding logic to understand how T2 originally wrote these definitions.

I'm also realizing that after each batch of defines gets added, the census needs re-resolution — since new header definitions can shift canonical field-union types, band map_type entries might drift and need re-keying by owning address if they go missing. There's also a subtlety about what happens when a define's target already sits in canon_types: the residue_cause through folds would need restamping, though that's likely outside this task's scope and belongs to a later sweep.

Now I'm checking whether adding types and fold rows affects `--check-residue` coverage or the census gate — since both depend only on uncovered counts, ledger stamps and coverage should stay unchanged, and bbt renames should read fine through type_folds. I also want to verify whether check-structs' dup-def detection gets triggered by adding thousands of defs with identical layouts, since new unused defs are dead but allowed until T4/T5, while layout-identical duplicates might get flagged as struct twins.

Mechanized hash-twin overlay copies across many body families could generate lots of identical layouts, which worries me about tripping the "0 dup defs" check — I need to actually read the check-structs predicate rather than assume, so I'll just grep for check_structs in type_census myself instead of delegating.
