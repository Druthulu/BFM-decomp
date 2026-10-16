---
ts: 2026-10-16T14:47:16.891Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aede67d56d4362411
model: claude-opus-5-5[1m]
effort: medium
turnId: 25ddd874-0949-491c-a87c-0e1a6c0ee67b
usage: {input: 14, cacheRead: 363133, cacheWrite: 10596, output: 5971}
---

**Project Architect 3.28.7 is installed and loaded. Ready to continue work.**

I answered T4's question myself, because it stays inside the milestone. T4 can now close.

**What T4 did.** It finished re-sweeping the overlays (the binaries loaded per scene or room) onto the new canonical struct types. That took 24 batches, every one byte-identical at 218/218 and committed. In all, 55,583 casts became plain struct member accesses. Raw pointer casts fell from about 175,000 to 120,000. Inside the 95% band, the overlays now have no "type not canonical" residue left. TNC (that "not canonical" label) fell from 139,520 to 23,630 sites overall, and the rest of that belongs to T5.

**What it hit.** 7,128 overlay sites still read TNC, spread over 652 struct types. These types aren't in the frozen band list or in the tail. They are new placeholder types, formed when the census regrouped the raw casts the sweep left behind. Some are big: one has 768 sites. The expert rightly declined to relabel them as "below band", because that would have stretched the term to make the check pass.

**What I decided:**
- **New task after T5.** It decides these leftover types for all the binaries in one pass, by the same rules as T3. First it tries tracing each one back to an existing type and merging it into that type. If that fails, it records a layout reason; otherwise it gives the type a proper definition. Then it runs one sweep of the bodies it touched.
- **No "below band" for leftovers.** Even single-site leftovers can't go there. The milestone caps that label at the roughly 7,000 tail sites frozen with the band, and the overlays alone already use 5,009 of them.
- **Asks before creating one-off structs.** If the task would create more than 500 single-site structs, it stops and asks first, because you didn't want structs that exist only to satisfy the counter.
- **T4 and T5 amended.** Their "no TNC left" check now covers the band and tail types only. The new task owns the check across all binaries, so the milestone itself doesn't change.

These changes go in at the next task boundary, so T5 runs as planned and then hands its leftovers to the new task.

T4's summary is in `/home/musashi/bfm-decomp/phase-ends/current/tasks/T4.md`.
