---
ts: 2026-10-17T12:45:51.321Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm thinking through union mode sizes—whether a plain union with a pointer and double becomes DImode across two registers, and considering whether a union containing a byte array would force BLK mode into memory instead. I'm also exploring the reverse case, where the pointer field is narrower than the union's full width, making a store to it a partial subreg write.

Tracing through what happens when setting the pointer field inside a DImode union pseudo: register allocation still treats the whole pseudo as live, so it gets paired into two registers and saved in the prologue even though only the low word is ever written—meaning the high word's liveness doesn't actually narrow the allocation. I'm now considering checking cse.c to see how REG_EQUAL notes get removed.
