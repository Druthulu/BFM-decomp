---
ts: 2026-10-17T16:06:57.803Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: ee7fbc65-97b8-4a8a-8e3c-c7327a9054ea
---
I'm figuring out the actual hand cracking numbers — around 394 singleton functions in T11 with roughly 258 expected cracks, versus T20's ~864 rows which is tagging, not cracking. The hand cracking itself was done by Claude coders rather than the developer directly, so I need to clarify that distinction, and I'm also noting that api_agent.py exists to give an API model the same tool access.

On the GLM bake-off idea, the harness was built for shape-matching rather than lever-free cracking, so plugging it into T11 mid-wave would clash with the existing coder shards and banker — better to run a cheap, isolated bake-off on ~20 survivor rows after T11 finishes, scratch-only with no banking, to compare crack rates at roughly $0.03-0.08 per function. This would require proposing a scope addition rather than a plan change, but since T11 still has 14 hours to run and this wouldn't block it, I can just raise it in conversation rather than treating it as a formal hold.
