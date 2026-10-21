---
ts: 2026-10-21T20:03:16.416Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 1529e2d0-471c-49f0-8029-9de319a33b12
usage: {input: 4, cacheRead: 122108, cacheWrite: 571, output: 610}
---

Adding a model is a setup you run yourself, in a normal terminal. Don't run it through `!` here: it asks for your key with hidden typing, and anything typed in this chat stays in the conversation log.

The steps:
1. **Create a key** at openrouter.ai and give it a credit limit. If the new model's best host differs from DeepSeek's, use a new key just for this model, because a key's guardrail covers every model on it.
2. **Run the setup** in a WSL terminal, since the project runs in WSL:
   `sh ~/.claude/pa3-src/project-architect-3.0/setup-external.sh`
   It asks for:
   - the URL: press Enter for OpenRouter;
   - a name for the config, for example `openrouter-<model>`;
   - the key;
   - the model id, copied from the model's OpenRouter page in the form `vendor/model`.

   It tests the model and saves nothing if the test fails.
3. **Add the guardrail.** The setup lists the model's hosts, best first, and names the recommended one. Add a guardrail on the key at openrouter.ai that allows only that host.

Your next message here will bring me the setup's result. I'll run the connection check then, and we'll decide what the new model is for. Today all function cracking goes to DeepSeek, so the new model could replace it, split the batches with it for a comparison, or wait for a later wave.

Which model is it? If you tell me now, I can look up what PA3's tests or OpenRouter's page say about its price and its hosts while you run the setup. T11 is still stopped.
