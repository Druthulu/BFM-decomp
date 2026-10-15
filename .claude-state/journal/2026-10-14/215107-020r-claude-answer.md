---
ts: 2026-10-15T03:51:07.469Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 6fc7430e-a08e-4f8d-bfd0-045c00b69643
usage: {input: 4, cacheRead: 51289, cacheWrite: 664, output: 997}
---

Most likely there's no issue. The question is only whether anything they copied from us was AGPL-covered.

**MIT (theirs)** is a "do what you like" license. Anyone can copy, change, sell or fold the code into closed-source software, as long as they keep the copyright notice. It asks nothing back.

**AGPL-3.0 (our `tools/` and `docs/`)** is a "share-alike" license, and the strictest common one. Anyone may use and change our tools, but anything they build from them and distribute must also be AGPL, with full source. The "A" adds that this applies even when the software only runs on a server for others to use. The point is that improvements to our work stay open.

**Where it could clash:** if they had copied one of our AGPL tools or docs and released it as MIT, that would break our license, because AGPL code can't be relicensed as permissive. From what the retriever saw, they haven't done that. They say they contain none of our code, and what they took is the splat layout and symbol names. Those are essentially facts about the game's binary (addresses, sizes, labels) and live in our config, not in `tools/` or `docs/`. Their own tools look self-written. So I see no actual conflict, though I haven't checked their files line by line.

**The one real point is our `src/`, which has no license.** With no license, the default is "all rights reserved", so strictly nobody may reuse our decompiled C. (The C also comes from Square's game, so whose rights cover it is murky anyway, which is common for decomp projects.) That matters later: if they want our typed structs and named code in 3.43 and beyond, they technically have no permission to take them.

My recommendation is to do nothing now. When you want others to build on the legible source, put an explicit license on `src/`. Pick a permissive one like MIT or CC0 if you want ports to use it freely, or AGPL if you want their changes to stay open. That's your call and not urgent. This is a plain reading of the licenses, not legal advice.

The planner is still drafting 3.40. I'll bring you the draft when it's ready.
