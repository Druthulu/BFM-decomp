---
ts: 2026-10-22T01:10:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rSctwnBZTfbQYGPpMVye
---
Interesting! The alloc table for my P1 body:
- r73: pri 10000, refs 3, live 3, prefers v0 — no hard reg assigned (it's a pseudo with no hard reg = the RESULT_DECL? It has no hard → it stayed a pseudo? Hmm, "hard -" means no hard reg assigned).
- r79, r82, r84: pri 10000, refs 2, live 2, block 1/2 — "prefer v0"?

Hmm, the table shows the .lreg table (local allocation) with preferences.

Hmm, the RESULT_DECL would be r73 (pri 10000, refs 3 = 3 returns ✓, live 3, prefers v0 ✓).

So the RESULT_DECL (r73) has pri 10000 and refs 3, live 3 → pri = 3*10000/3 = 10000 ✓.

And r79/r82/r84 have pri 10000 too (refs 2, live 2 → 2*10000/2 = 10000) — TIE with r73 and the lower allocno wins (global.c:607). r73 has the LOWEST allocno (73 < 79) → r73 should win the tie!

Hmm, but r73 has no hard reg in the table. The table's "hard" column shows the assigned hard reg: r73 = "-" (none assigned). Hmm, so r73 was NOT allocated a hard reg?

Hmm, maybe the alloc table lists the local-alloc table (.lreg) — pseudos that got hard regs in the local allocation. r73 has none — hmm.

Let me compare with the ORIGINAL (pinned) body to see the difference. Let me dump the pinned header body too and compare the tables. That tells me what the pin changes.

Let me create tu_dump2.c with the pinned body (register int result __asm__("$2")) and dump it.

Actually, more useful: dump the TARGET's structure. The target = the pinned body (orig.c). So let me dump orig.c's body and compare the alloc tables. The difference will show what the pin does.

Let me do that.
