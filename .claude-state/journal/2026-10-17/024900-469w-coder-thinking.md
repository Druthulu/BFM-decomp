---
ts: 2026-10-17T08:49:00.996Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
I'm worried about replay assigning DIFFERS to non-want sites without actual testing, pulling verdicts from the exemplar's oracle. I need to check rows around 4985-5000 to see what verdict and oracle values the rung-E exemplar actually carries, since if it's RESIDUE with empty oracle, replay's "want" list would come out empty.

For the Rung B greedy test, each site gets judged singly so that part is fine. Now I need to verify whether the census's site list for a body actually includes all the sites with their markers, and figure out how to pick three target bodies to test with --only, since matching by file path pulls in every body in that translation unit while matching by function name pulls in duplicate names across overlays — neither gives an exact match. I'll write a scratch script that imports delever's plan-making logic to compute the target set directly and compare it against what --only with function names would select.
