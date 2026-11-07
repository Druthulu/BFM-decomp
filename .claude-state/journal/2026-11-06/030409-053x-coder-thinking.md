---
ts: 2026-11-06T10:04:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NCQ8Zed3ivMPXhcAKdDq
---
The dispositions: r75 in 2 (v0), r78 in 5 (a1), r79 in 2 (v0), etc. And r74 in 2? Line 448 says "Register 74 in 2." Hmm — that would put r74 in v0 too? But then t (r74) and tb (r75) both in v0 — impossible unless they don't overlap.

Wait line 79: r75 in 2 (v0); line 448: r74 in 2 (v0). Let me look at the context — these "in N" lines might be in different dump sections (the lreg file has the whole TU with multiple functions; line 448 might be a different function).

Let me be careful. Let me extract the func_800CD314 section and look at the disposition lines within it. The awk started at ";; Function func_800CD314" and line 448 is relative to that section. So within the function, r74 in 2? That contradicts.

Hmm, but maybe line 448 is from the SECOND occurrence (the function might appear twice? or a note). Let me print around line 440-460 of the section.
