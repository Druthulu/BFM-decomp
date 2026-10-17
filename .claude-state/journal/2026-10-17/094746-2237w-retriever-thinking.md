---
ts: 2026-10-17T15:47:46.347Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6d6d42b9ac5d5847
model: claude-haiku-5-5[1m]
effort: medium
turnId: f7b4ad10-361a-44d3-9321-c1d2b4e8cebf
---
I'm tracking down the callers of func_80026514 and func_800268D0, which show up in 800.c through casted function pointers around lines 13993-14017. For func_800CBA44, the callers are in md_MAIN_027.c at lines 502 and 512, with no other references found elsewhere in src or include.

Now I need to pin down the declarations and definitions: 800.c has K&R-empty declarations around 13917-13918 and definitions at 15079 and 15166, while md_MAIN_027.c has a K&R-empty extern at 434 and a definition at 525. I still need to locate the unbacked CAST_NONSTRUCT site, but the census grep for .run/P37 returned no matches, so I'm not sure if that directory even exists. I'll check the type_census file around a few line ranges, look at the restruct rows near 1251, and pull the git log for T8.c4 to piece this together.
