---
ts: 2026-10-16T16:52:28.789Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6262df0e8a0d472a
model: claude-opus-5-5[1m]
effort: medium
turnId: 7850ba3c-c3b4-45a3-a86f-0ae36df32364
---
I'm realizing that --fold-class would merge an entire class onto one canonical, which is too strong since it could fold genuinely separate entities and violate the per-type rule. I need to only merge the specific components that actually share objects, not the whole class, so I'm checking whether the tool even supports that kind of subset folding, then estimating how many of the 241 classes actually have shared-component names worth folding.

Then there's the tier complication: opaque members get renamed and need access respelling, while tier-2 placeholder members might just differ in naming convention (unk0 vs f0) without needing deeper fixes. Given the scale and ambiguity, I'm weighing whether to pause and ask a clarifying question versus just measuring the actual numbers first, and I also want to check why this didn't surface back at T3 — maybe the SHARED classification logic didn't exist yet in struct_twins at that point.

Checking the restruct history, at T3 bodies were identical with no struct name bindings at all, so there was no sharing signal. It was restruct (T4/T5) that converted raw casts into named member accesses per overlay, picking different struct names per translation unit for the same underlying routine — that's what created the artificial "shared" identity. So the honest fix is to fold those names per component, respelling the casts in minority copies to match the majority name since the layout is the same.

Before: dup_classes=170, twins_stale=3894 per check_structs.txt. After regen: 241 — that's fine. Now I want to actually compute the components, so I'm writing a quick scratch script under .run/P40/t5/.

I'll measure the fold scope first, identifying for each SHARED class the connected components of names linked by shared objects—since only those need folding, while other names remain separate twins per G62.
