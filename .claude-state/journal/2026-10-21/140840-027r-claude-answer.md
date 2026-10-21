---
ts: 2026-10-21T20:08:40.089Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 462d9afa-5514-4bae-9432-c9b418b23f87
usage: {input: 12, cacheRead: 620384, cacheWrite: 2829, output: 2172}
---

MiniMax is set up and now does the crack-wave coding. DeepSeek is out. Nothing else changed: Opus coders bank, nothing escalates, and walls are held for you.

**The setup worked.** The connection check passes for all four configs:

| Config | Check |
|---|---|
| openrouter-minimax | connected (minimax ok) |
| openrouter-deepseek | connected, but no longer used here |
| openrouter-glm | connected, not used |
| openrouter-qwen | connected, not used |

**What I changed:**
- **Project settings.** MiniMax gets 4 lanes, and DeepSeek's lanes are set to 0. Effort stays at the default, high. Committed.
- **The card.** It now reads "Func cracking: openrouter-minimax/minimax (high) only."
- **The plan.** I've queued a line for its change log that swaps DeepSeek for MiniMax in the cracking rule. The rest of the rule stays.

**One thing you should know first.** The model id the setup saved is `minimax/minimax-m3.1-flash:free`, the free variant. Two catches come with free models on OpenRouter:
- **Rate limits.** Free variants get a small number of requests per minute and per day. A cracking coder makes hundreds of calls per function, so 4 coders will probably hit the limit. Runs may then fail with 429 errors and pile up on your held list, even though the model could have cracked those functions. PA3 also hasn't tested MiniMax, so I have no crack rate to compare it with.
- **Prompt logging.** Free endpoints typically log prompts and may train on them. A coder's prompts include our source and the game's disassembly from `asm/`, which is ROM-derived and which we deliberately keep out of the public repo.

If you meant the paid version, run the setup again with the id without `:free`. Then the credit limit caps the spending, as before. If the free variant is deliberate, it works as configured. Expect slow or failing runs under load, and watch the held list early.

T11 is still stopped. Say go and I'll resume it with MiniMax doing the cracking.
