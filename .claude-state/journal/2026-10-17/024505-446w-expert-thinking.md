---
ts: 2026-10-17T08:45:05.359Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
These macros embed inline asm launders directly, making them body-level constructs. The cleanest fix is swapping the raw inline-asm launder for the shared ENGINE_SHB macro from the prelude, so the macro no longer registers as asm-bearing and can be handled consistently by the delever logic.

But I realize if an outer macro wraps ENGINE_SHB internally, the textual census would miss it entirely since census scanning is purely textual -- that's effectively hiding the launder, which isn't acceptable. So for structuring macros, I should expand them inline at their use sites instead, making the lever visible and countable per (file, func, kind), then run delever removal tests on each site individually.

For the 136-file SHB case with 259 uses, raw inline expansion is less legible than a named launder, so consolidating into a header-level ENGINE_SHB replacement seems like the better path forward.

I need to test via the oracle whether volatile versions of the asm produce byte-identical output across all 133 non-volatile uses -- if GCC can delete or reschedule non-volatile asm with unused outputs, that changes things. If they're all identical, I can collapse everything into one shared header-level definition; otherwise I need a separate ENGINE_SHB_NV variant in the prelude. Either way, the prelude definition row stays as the counted launder site, keeping the census honest even after consolidating 157 rows down to roughly 2.

I should also verify that all 136 SHB translation units actually include engine_prelude.h, and check whether any TU defines SHB independently if the prelude doesn't -- tracing the include chain through common.h to confirm.
