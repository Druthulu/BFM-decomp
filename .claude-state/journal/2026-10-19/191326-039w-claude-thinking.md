---
ts: 2026-10-20T01:13:26.642Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 279f4a59-e9bd-43fe-b6f4-cb544d688d68
---
I'm uncertain about p39-census since it's just a baseline reference, so I'll flag it to ask rather than decide. For the wave_* directories and loose json files from the Aug–Sep era, those can be deleted now that everything's matched, and the ox_campaign note about keeping drafts for recovery no longer applies since all functions are accounted for.

Now I'm being more careful about the t* directories — my grep shows several (t4, t5, t5a, and others like c294, wave4, resolver, autopsy) are actually still referenced by tools despite the retriever's suggestion to delete them. I'll compute the precise delete list programmatically: taking the candidate set by pattern and subtracting anything referenced in tools, Makefile, or config greps, plus anything still tracked, to make sure I don't remove something still in use.
