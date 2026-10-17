---
ts: 2026-10-17T08:44:15.274Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm checking whether macro-based SHB uses already get counted as launder sites in their call bodies, which would make the per-translation-unit macro definition an extra redundant fail. To eliminate this duplication, I'm thinking about moving the SHB definition into a shared header instead so it's ledgered once rather than per use.

I need to check whether the census's strict mode already skips macro definitions from shared headers (it seems only the GTE header gets this exemption), and whether the existing ENGINE_SHB definition in the prelude is itself counted as a single row. I also want to verify whether all the current SHB definitions are textually identical across files, or if there are variants like volatile vs non-volatile asm, since that affects whether I can simply swap SHB(x) calls for the existing ENGINE_SHB(x) macro.

Consolidating the 136 duplicate definitions into one shared definition mirrors how C0517 handled the GTE header, and since the actual uses are already ledgered per-call-site, this seems legitimate rather than concealment -- it would shrink the per-TU definition count substantially while leaving use-site rows untouched. The open question is whether the prelude's shared ENGINE_SHB definition should be exempted from the census the same way the GTE header is, since it isn't really "per-TU" anymore once consolidated, and that's something I'd need to scope within tools rather than touch src/include directly.
