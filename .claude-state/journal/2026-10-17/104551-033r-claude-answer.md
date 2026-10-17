---
ts: 2026-10-17T16:45:51.335Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: c90cef9c-89b2-40cc-9526-e8d1886c0067
usage: {input: 6, cacheRead: 195524, cacheWrite: 2486, output: 1042}
---

I've had T11's expert start the Haiku test, rather than spawning the agent myself. The expert owns T11's worklist and its committer, so a coder I started separately could grab functions the wave is already working on, or commit outside its checks.

What the expert will do:
- **The test.** One extra coder on Haiku 5.5 at medium effort tries 10 functions, with a mix of lever kinds and sizes. None of the 10 overlap with what the Opus coders or the external models are working on.
- **Same rules as the rest.** It gets the same instructions and the same 30-minute limit per function, and works in scratch only. Anything it cracks goes through the same committer and the 218/218 check.
- **Inside your cap.** It takes one of the 4 coder slots, starting with the next one that frees up.
- **The comparison.** T11's summary gets a Haiku row in the comparison table, next to Opus, DeepSeek and GLM. It covers attempts, tokens, minutes per function and what it cracked.

The pilot gives the bar Haiku has to clear. Opus cracked about 60% at about 40k tokens per function. If Haiku gets anywhere near that, it would make the rest of the work much cheaper, and a 10-function sample will at least show whether it's worth a bigger trial.
