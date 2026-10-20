---
ts: 2026-10-17T17:35:07.684Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm working through register scheduling order, figuring out which values get allocated first based on lifetime - the merged pseudo gets a later slot since it's long-lived, while shorter-lived quantities like e1b and m24 need to be placed earlier, checking their load/store positions in the dump.

But I keep looping on why m24's lui gets scheduled late in the target without pins. It might come down to how luid values are assigned to split instructions during backward scheduling, which determines tie-breaking priority among ready instructions.

Splitting order puts e1a before e1b before m24, so with no pins the m24 lui always gets hoisted to the top since backward scheduling picks the lowest luid last. For target to differ, m24's lui must carry a dependency — possibly because reusing pseudo r03 merges lifetimes and raises its priority, though local-alloc can't split a single pseudo's lifetime. I'm wondering if e1b and m24 actually land in the same hard register through combine, creating an implicit ordering constraint.

Another possibility: m24 reuses the pseudo for variable w, whose last use (the D+w+4 computation) sits earlier — that would force m24's lui after that point via a WAR dependency, merging w's early lifetime with m24's late one into one low-priority pseudo. I'm tracing where target assigns w (looks like a1) to see which register m24 would end up sharing.

Then I consider whether e1b and e1a could overlap through shared registers, but they're in different regs (v1 vs t0), so no match there — t0 seems to be where m24 and e1b actually coincide. That suggests the scheduler hoists m24's lui ahead of e1b's death unless some dependency blocks it, so I want to check how instruction LUIDs are assigned after splitting in sched.c to see if my ordering assumption is wrong.
