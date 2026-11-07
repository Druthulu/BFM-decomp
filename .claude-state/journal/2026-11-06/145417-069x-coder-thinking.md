---
ts: 2026-11-06T21:54:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qoGYwMFnQAWccW6qEUT4
---
Interesting: the branch offsets differ (beqz v0,afc vs b00) — because mine is 709 ins vs 710, one ins shorter, shifting addresses. So there's a missing instruction early on. The `j afc` vs `j b00` differences are just address shifts (same relative structure? mine 0xafc vs target 0xb00 = 4 bytes = 1 ins). So the real difference is one missing insn somewhere before 0xafc, plus the dst bank.

Where's the missing insn? The diff shows "delete"/"replace" hunks; the address shift means mine lacks one insn. Let me find a hunk where mine has fewer lines. Let me grep the diff for hunks with mine range shorter than target.

Also the register pairs: a2->v1 x52 (dst in a2 vs v1), v1->a0 x48, a0->a1 x12, a0->v1 x12, a3->v0 x11, v0->v1 x4. Big bank shift.

This is a huge residual. Cracking it means matching a 710-ins function's allocation exactly. The pin was doing a lot. This might be a WALL too, but the twin (80191C50) is the same body, so a crack helps 2 items.

Let me first find the missing instruction. Look for hunks where mine deletes something. grep "delete".
