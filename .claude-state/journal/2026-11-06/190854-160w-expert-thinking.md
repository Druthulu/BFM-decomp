---
ts: 2026-11-07T02:08:54.584Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: e0c8644d-6ef7-4f4d-ab7b-71dcf29b7e37
---
I've got the decompiled function for func_80184440 now, but --update always keeps the ov_* rows, so the leftover GONE entry has to come out by hand. Since config/ is hand-edited, I'll remove that object from the JSON with a short Python script that cuts the text between the matching opening and closing lines, keeping the rest of the formatting intact. I still need to deal with the header text as well.

I'm leaving the func_80184440 mention in the header line as it is, since it's a historical note. I also want to check whether the JSON has its own count fields that would need updating after the removal.
