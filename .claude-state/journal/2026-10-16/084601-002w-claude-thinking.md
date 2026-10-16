---
ts: 2026-10-16T14:46:01.012Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aede67d56d4362411
model: claude-opus-5-5[1m]
effort: medium
turnId: 25ddd874-0949-491c-a87c-0e1a6c0ee67b
---
I'm checking whether this touches the milestone requirement that no TYPE-NOT-CANONICAL drift remains anywhere, including inside the frozen 95% band and tail — meaning any proposed new task needs to resolve these drift types, particularly ones with multiple sites.

I'm worried that pushing drift singletons into TYPE-BELOW-BAND could exceed the frozen tail cap, since the overflow tail is already at 5,009 and more sites will be added. I'll add a done-when condition that keeps the BELOW-BAND count within the cap, stopping to ask if it can't be satisfied, which keeps the task scoped to the milestone — now I need to check the task list for the right ID and the syntax for adding to the plan.
