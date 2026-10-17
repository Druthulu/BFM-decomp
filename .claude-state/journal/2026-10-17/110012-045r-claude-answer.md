---
ts: 2026-10-17T17:00:12.481Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: a929cb8c-c58d-4431-838f-471430491695
usage: {input: 14, cacheRead: 669838, cacheWrite: 5809, output: 3746}
---

I agree, and your naming idea is better than the rule I gave you. "Don't name until sure" does leave a late-stage decomp full of `func_8001234` and `unk10`. A marked best guess carries real information and doesn't claim more than it knows.

**It's written down.** I've added all three rules to T14. They go into the wiki pages "Start a new decomp project" and "How to AI decomp", and into the bootstrap guide, as rules for any new project using our workflow:
1. **Structs as you go.** Before writing any raw cast, an agent looks up the existing struct and extends it.
2. **Pure C by default.** A lever is allowed only with its compiler wall, and what was tried first, recorded when the function is matched.
3. **Best-guess names from the start**, under a guess prefix, promoted to a plain name once there's evidence.

Each rule cites what skipping it cost us in Phases 3.35 to 3.40. The change goes in at the next task boundary. I've also noted your naming preference on the card (`HOW_WE_WORK.md`), so later planners see it.

**What I'd add to make the naming rule work:**
- **A distinct prefix.** Decomp convention already uses `unk` for "nothing known": `unk10` fields, `Unkstruct_80126B58`, and so on. If `unk_MutateHp` meant "best guess", the two meanings would blur. A separate marker like `guess_MutateHp`, or `maybe_`, keeps three clear tiers: placeholder, guess and confirmed. Whichever prefix you pick, the important thing is that it means one thing only.
- **A names ledger.** Each guessed name gets one row saying why: "writes the player HP field, called from the damage handler". Promoting a guess to a plain name then means adding evidence to its row. Without the row, a guess that has survived long enough starts to look like a fact. The ledger also guards against the one real risk, a wrong guess steering later agents. Agents are told that guessed names are guesses, and the ledger shows how weak each one is.
- **Cheap renames.** 3.42 already builds the tool that proves every reference to a renamed symbol was rewritten, so changing a guess later costs very little.

**On helping the cracking: yes, but indirectly.** The compiler ignores names, so a name never changes the bytes. What helps is the agent's understanding. An agent that knows it's touching `guess_PlayerState.hp` rather than `*(s16*)(a0+0x4C)` picks the right types and widths sooner, and those do change the code the compiler generates. That's the same reason structs as you go helps.

**For this project.** 3.43 is still planned as "unnamed beats wrong": only names with evidence, and everything else stays a placeholder. Your idea would change that phase's milestone, so it's your call. I recommend adopting it with a distinct prefix and the ledger. 3.43 would then name far more than its top 500, and every guess would still be marked as one. Pick an option in the picker.
