---
ts: 2026-10-17T14:02:58.830Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
The function signature matches with these specific parameter types, so I'm checking whether that's lever-free given that other translation units only have extern declarations with generic s32 parameters — since those are separate compilation units, there's no actual conflict, but I need to verify how callers in those other files handle the type casts.

Only the in-TU extern declaration needs to change since the in-TU callers already cast the function pointer explicitly, making them unaffected by the signature difference. The remaining concern is whether a stricter `--body` check would flag the extern declaration at line 676 as conflicting with the definition, which could break the byte-for-byte equality requirement.

I should test `--body` against the sg3 definition to see if the older compiler tolerates this mismatch; if not, I'll stick with keeping the fuller file as proof and treat win.c purely as the definition plus a note about the needed extern tweak. I also notice there are similar residue entries for the sibling TUs (MAIN_012 and SC04_011) that aren't strictly required but could be worth trying as a quick bonus win.
