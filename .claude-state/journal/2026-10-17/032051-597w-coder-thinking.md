---
ts: 2026-10-17T09:20:51.785Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
SHB looks unused in this translation unit, so I need to check whether it's dead across all of them. Since headers show zero real uses, I'll write a script to count genuine occurrences in the .c files, filtering out comments and #define lines, especially for the three volatile symbols with five occurrences each.
