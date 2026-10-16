---
ts: 2026-10-15T22:02:31.333Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
Residual-row types already resolve to TYPE-NOT-CANONICAL at the base level, so their body verdict is covered under DONE_VERDICTS, with the site cause coming separately from residue_cause as TYPE-BELOW-BAND. That means I don't need a new verdict name — TYPE-BELOW-BAND belongs at the site-cause level, not the body level.

For T3, I'm now thinking the mechanised approach should write generated definitions directly into struct_types.h, bounded by markers similar to how head_types.py handled T2, keeping the generated region clearly demarcated inside a hand-edited file. For rendering, I'm weighing reuse of head_types.py's max-site layout logic against sl.entries_from_layout/render_struct from write_types, leaning toward reusing head_types' approach for consistency with T2, with render_struct as fallback.

I'm sketching out a `restruct.py --decide-band` mode, starting with a `--freeze-band` step that reads tnc_types from residue_census.json and writes a one-time config/tnc_band.tsv file, refusing to overwrite an existing one and including header metadata about source commit and sort order.

The band itself is determined by finding the minimal cumulative prefix that reaches 95% coverage, same loop structure as the types_to_cover_pct calculation, and I need this to match the census figure of 6676 types — if a fresh census differs, I'll flag that explicitly.

Then `--decide-band --ranks A-B` processes band rows lacking existing type_folds entries: resolving each against struct_map (reporting missing ones), making the decision, appending generated rows to type_folds.tsv, and rendering definitions into the struct_types.h generated block. A `--tail` flag handles the roughly 6,066 residual TYPE-BELOW-BAND types with no existing row, growing type_folds.tsv to about 12.7k rows total, which seems fine. I'll also have the mode print per-action/class counts, and I'll handle sampling verification myself afterward with a separate scratch script checking against struct_map.json rather than building that into the mode itself.

For the tail types, I'm noting that even though they don't change now, a tail map name could still drift later since it's keyed on names — if that happens it reverts to a TNC-type cause, which is really a T4/T5 restamping concern I should flag separately. I also need to resolve how E1/E2 fold targets behave when those targets are themselves map types that get folded or defined — the fold target needs to resolve to a canonical type name, which seems workable. On naming and collision handling, I'm digging into whether the owning address for Unkstruct names is derived from the lowest function address in the cluster or from a global address reference, since the example shown uses a global AT:D address alongside a function address, so I need to clarify this address-derivation rule for hash-based names too.

Now I'm working through whether a defined target name can equal an address-named map name, concluding it's fine unless it collides with existing identifiers in src, including possible local typedefs from other hash sources, which the collision check should catch with suffixes like _2 or _3. I'm also laying out the ordered residual classification rules — zero size hint means no layout, negative offsets mean interior type, overlapping or multi-width conflict entries mean union type, and single-field-at-offset-zero cases get their own designation.

5. If the renderer refuses or nothing survives, it falls back to no-layout; otherwise it's defined, with folding checked before residual classification and residual checked before defining. I'm second-guessing rule 3 though, since real structs with big width conflicts (like the 800D3888 example) would get pushed into the union residual bucket under this policy, which could shift a large share of sites out of being defined — I want to quantify this against struct_map before committing, approximating the class distribution over current struct_map sites weighted by site count since I don't have the full per-type census yet.
