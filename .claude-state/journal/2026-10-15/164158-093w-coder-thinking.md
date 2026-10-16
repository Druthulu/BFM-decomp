---
ts: 2026-10-15T22:41:58.143Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a27f5e99cd45ba1f7
model: claude-opus-5-5[1m]
effort: medium
turnId: 93fc0445-54f4-44e8-8ad6-986fd7c917ec
---
While I wait, I consider a possible fix on the restruct side: since struct_twins needs an address in bound objects, layout-identical dead defs might instead be collapsed by having restruct emit one definition plus a typedef alias for the other.

Since a typedef alias isn't a struct body, it wouldn't trigger duplicate-class detection, and since alias typedefs aren't added to canon_defs, the aliased name wouldn't count toward the dead set—effectively making the live name reachable through the alias line instead. That's a real rule change to decide/render, which the brief permits, but it brushes up against the deeper question of whether folding new defs into existing canonical types based purely on layout identity is actually safe, especially given several of the 65 twin-bound classes mix brand-new names with pre-existing ones like SubEnt8018B390 and Unkstruct_8015D380.

Aliasing effectively conflates distinct map types by layout alone, which directly violates the policy that layout twins without evidence must stay separate—G62 is scoped per type, not per layout, so this is a call for the domain expert, not something I should resolve unilaterally. The dup_classes mechanism also requires an addressed cause via owner address or def comment, which falls outside the allowed fix scope, and the 14 affected classes have unbound, unused names that are genuinely dead. This looks like a genuine wall where the prescribed process can't cleanly resolve check-structs, so I'm leaning toward reverting the batch-1 writes rather than leaving anything half-applied, and returning a question with the supporting evidence.

The 14 refused classes are identical-layout groups of new T3 defs with no live names, so struct_twins can't cite an address—that logic lives in struct_twins.py (outside the restruct.py decide/render fix scope). I'll wait for check-structs to finish before proceeding.
