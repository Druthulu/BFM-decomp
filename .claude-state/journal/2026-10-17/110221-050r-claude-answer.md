---
ts: 2026-10-17T17:02:21.881Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 167a1437-716c-4f11-bdec-4bb4f7c76a16
usage: {input: 16, cacheRead: 824032, cacheWrite: 5122, output: 3463}
---

Best-guess naming with the `guess_` prefix is now the project's rule.

- **The standard.** I've amended rule 1 in `docs/gen3-standards.md`. A name without evidence is now allowed as a best guess under `guess_`, such as `guess_MutateHp`, `guess_PlayerState` or a field `guess_hp`. Each guess gets a names-ledger row giving its basis and confidence. `guess_` always means "our best guess so far". `unk`, `Unkstruct_` and `func_` keep meaning "nothing known". A guess drops the prefix only once there's recorded evidence, and it can be renamed freely before then.
- **The generation plan.** 3.42's rename tools and names ledger now carry the guess tier. 3.43 is now "Evidence and best-guess names". Confirmed names need a citation row and guesses need a basis row, and the 3.42 scanner checks both. `no-evidence` is now only for names where not even a guess has a basis.
- **The kit docs.** Two docs for new projects still say "unnamed beats wrong": `decomp-architect/decomp-architect.md` and `decomp-architect/intake.decomp.md`. T14 updates them along with the wiki pages.

The rule changes are committed as fe8028d960 and the link check is clean. Both commits I made earlier today also took in the journal and T11's coder logs, which is harmless.

None of this affects T11.
