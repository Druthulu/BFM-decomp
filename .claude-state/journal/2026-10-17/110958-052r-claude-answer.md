---
ts: 2026-10-17T17:09:58.783Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 16d5b8ea-f552-421d-89cb-c6a3a79d628e
usage: {input: 6, cacheRead: 243749, cacheWrite: 3452, output: 2563}
---

The 3.43 milestone change is already in. I made it in my last message, committed as fe8028d960.

**Prefixes: I'd keep one in the name and put the rest in the ledger.** You're right that confidence has levels, and knowing how we worked something out matters. But the name is the wrong place for it, for three reasons:
- **Every step becomes a rename.** If `guess_` becomes `likely_`, every file that uses the name changes. With hundreds of names moving up over time, the code history fills with renames that change no meaning.
- **"Maybe" is a different question.** It means "the evidence conflicts", not "less sure than likely". Squeezing both into one prefix ladder blurs them.
- **Readers can't tell the levels apart.** Someone reading `maybe_` next to `likely_` can't say how much more sure one is than the other. A ledger row can.

So the code shows only the one thing a reader must know: `guess_` (not confirmed) or a plain name (confirmed). The ledger row holds the detail:
- **Confidence:** low, medium or high.
- **Evidence kind:** inferred from the code, string, cross-reference chain, debug menu, live-RAM observation, or a community label.
- **A conflict flag** for your "maybe" case, naming the contradicting evidence.
- **Name history**, so we know what it was called before.

A tool can list "all guesses with conflicts" or "all high-confidence guesses ready to confirm" whenever we want. If you'd still rather have the levels in the name, it works. It just costs more renames. I put it in the first picker.

**Comments as you go, from day 1: yes, strongly.** It's the same lesson as structs and names. Understanding is cheapest to record at the moment an agent has it. An agent that has just matched a function knows what it does, why an odd spelling is there and what it tried. Two lines of comment then cost almost nothing, while recovering that later costs a full agent run. Comments don't change the compiled bytes, so the 218/218 check is unaffected.

You're right that older comments may be wrong. That's fine: comments get edited freely, and git keeps the old versions. I'd only ask that a guess in a comment says it's a guess, the same way names do.

**Going back now: no whole-codebase comment pass, and no transcript-mining phase.** My reasons:
- **A comment pass would mostly produce noise.** An agent that reads code only to comment it, without the understanding that comes from working on it, writes "loops over the array" style comments. Many would be confidently wrong.
- **The transcripts are the wrong source.** Most of the reasoning in them is about how to match the compiler: register pins, compiler pass quirks, permuter runs. Hardly any is about what the game code means. The parts that matter are already distilled: the cookbook, the restruct ledger, each lever's recorded wall, and the `!FAKE` notes. Reading them would also cost a great many tokens, on a scale like this whole phase, for a little value.

**What I'd do for this project instead:**
1. **Write comments as part of naming in 3.43.** Whoever names a function or field also writes a short header comment: what it does, how sure we are, the basis. That's when the understanding actually exists.
2. **A cheap ledger-to-comment pass.** A small tool copies what the ledgers already know into the code: each surviving lever gets a one-line comment naming its compiler wall, and each guessed name points to its ledger row. That's mechanical, nearly free, and puts the reasoning where a reader will see it.
3. **Day 1 for new projects:** add "comment as you go" to T14's guide, next to structs as you go, pure C and guess names.

Both choices are in the pickers.
