---
ts: 2026-10-15T21:19:44.435Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8db926a6adc5bbd5
model: claude-haiku-5-5[1m]
effort: medium
turnId: 71f49971-3fa1-4ac7-ba61-10ef592c67d9
---
I need to track down the residue_census function signature and its call site in main, figure out how the cause dictionary is keyed and populated, and check where residue cause lists like RESIDUE_SEGMENTS or a whitelist are defined—also looking at type_census for similar cause-string whitelisting and the struct_twins documentation.

Now I also want to check struct_map_join and twin_rescan for related logic, and grep type_census for the E1/E2/E3 evidence keys plus the TYPE-UNION cause whitelist to understand how evidence feeds into cause classification.
