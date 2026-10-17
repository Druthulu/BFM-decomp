---
ts: 2026-10-17T08:43:45.637Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm noting that the gte-clobber-steer rows are already header-level levers per C0517, so resolution likely means testing whether the canonical form matches the current spelling—if so, respell it; if not, keep it as a lever with the oracle evidence recorded, still flagged as a strict failure in the residue ledger.

Now turning to SHB, the per-TU launder macro defined in 136 files: I need to figure out whether resolution means removing the macro along with its uses where that holds, or ledgering each remaining use individually as a launder site with oracle DIFFERS. My plan is to test removal of each use separately, then for ones that can't be removed, move the definition into a shared header so those uses become ordinary launder sites in function bodies, ledgered per use. I want to check how the lever census currently classifies uses of a header-defined macro like this, so I'm going to grep through the census logic for how it handles macro definitions versus their call sites.
