---
ts: 2026-10-17T11:51:50.000Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm noticing the constant whose uses interleave with another constant should get the longer lifetime, so -160 should come first to get v1 early — ordering as x0=-160, x1=160, x2=-160, x3=160 matches the natural setXY4 sequence of x0,y0,x1,y1,x2...
