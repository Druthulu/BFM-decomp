---
ts: 2026-11-06T09:36:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9txI2cOGGcNBilFVKo4x
---
B4's replace chain is messy: TAIL.replace("rv = sp20;", "rv = sp20;\n    sp20 = rv;") then .replace("sp20 = rv;\n    *a0 = rv;", "*a0 = rv;") — that would cancel itself out. Let me simplify: B4 = reorder to `*a0 = sp20; rv = sp20;`? That changes semantics? *a0 = sp20 directly is equivalent (rv=sp20 then *a0=rv). Let me make B4: `*a0 = sp20; rv = sp20;` — real C move (remove the intermediate). Hmm, but then rv is only used by the asm... there's no asm in lever-free; rv's last set is rv=(s32)a0.

Let me rewrite B4 cleanly.
