---
ts: 2026-10-15T03:51:07.397Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 6fc7430e-a08e-4f8d-bfd0-045c00b69643
---
I should give a plain, direct answer: MIT is permissive and allows closed-source use as long as the notice is kept, while AGPL-3.0 is copyleft and requires derivatives—including network-run services—to stay AGPL with source shared. If their code derives from AGPL-licensed tools or docs, relicensing it as MIT wouldn't be allowed; and since our src/ carries no license, it defaults to all rights reserved, complicated further by the fact it's decompiled code from a copyrighted game.

They claim they copied none of our actual code, only the memory layout and symbol names, which are likely uncopyrightable facts rather than protected expression, and those live in config rather than the tools. So this probably isn't an issue unless they lifted actual AGPL tool code — their own tooling seems independently written. The unlicensed src also cuts both ways, technically restricting anyone from copying it, which is worth considering if we want to make the source more permissively reusable going forward.
