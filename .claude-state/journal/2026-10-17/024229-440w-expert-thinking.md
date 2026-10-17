---
ts: 2026-10-17T08:42:29.998Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm looking at the gte-lever rows the census flags as strict failures — these are GTE lever calls like gte_rtv0tr_m appearing in bodies, even though they're already header-level levers per C0517. The resolution needs to clarify whether they should resolve to gte_inline.h spellings or remain as header-level lever references.

I'll test each site by trying to canonicalize the respelling; where the respelling differs, I'll keep the row as a header-level lever with oracle evidence. First I want to check the current strict counts by running the lever census check with strict and residue flags through run.sh.
