---
ts: 2026-10-15T03:53:11.410Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 4a69dac3-8f69-47f0-893f-56ae92deece1
usage: {input: 4, cacheRead: 51953, cacheWrite: 1060, output: 1117}
---

One correction first: AGPL doesn't stop anyone selling. No standard open-source license does, and MIT, GPL and AGPL all allow selling. AGPL only forces anyone who sells a derived work to release its full source under AGPL too. To rule out selling you need a **non-commercial** license, which by the usual definition is "source-available" rather than open source.

**What fits what you want** ("free community mods fine, selling not"):
- **CC BY-NC-SA 4.0** is the best-known one. Reuse is free with credit, nothing commercial is allowed, and derivatives must use the same terms. It's widely used for docs and data, and some decomp projects use it for source.
- **PolyForm Noncommercial 1.0** is written for software and bans commercial use. It doesn't force derivatives to stay under the same terms.

My recommendation is CC BY-NC-SA 4.0 for `src/` and `docs/`, the project's real value. Leave `tools/` on AGPL unless you also mind someone selling the tooling itself. The vendored `tools/brave-CUE/` is someone else's GPL code and can't be relicensed.

**Limits to keep in mind:**
- **Their own code stays theirs.** You can't change the MIT on code Blizz127 wrote. A new license only covers what you publish, and only from now on.
- **Facts aren't covered.** Addresses and splat layouts probably aren't protected by any license.
- **Selling is already blocked.** A paid BFM port would infringe Square Enix's rights to the game no matter what our license says. A non-commercial license mainly makes your intent explicit and covers future reuse of our structs and names.
- **You need to be the copyright holder.** You can relicense only if you are the only human contributor. Anything someone else contributed needs their consent.

If you want to go ahead, I'd make it a small task of its own, outside 3.40, so the plan stays as it is: add a `LICENSE` for `src/` and `docs/`, update the README's license section and the existing AGPL headers, and run `audit_public.py`. I can do that alongside the planner if you confirm the license choice and that all contributions are yours.
