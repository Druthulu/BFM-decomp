---
ts: 2026-10-17T13:19:15.406Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a68ccc2589980bbb7
model: claude-opus-5-5[1m]
effort: medium
turnId: 03eed4ba-949a-478f-9f08-7d9a9121a969
---
I'm comparing abs vs __builtin_abs usage and wondering if that distinction actually matters here—in older GCC, abs() with the stdlib prototype typically gets treated as a builtin anyway unless -fno-builtin is set, so I'm checking whether this project defines abs as its own macro instead.

My simplest plan is to take the win.c function, rename the relevant symbols, and apply that body directly to the header, checking first whether the needed struct types are visible in the header's includers before trying it.
