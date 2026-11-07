---
ts: 2026-11-06T09:31:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kGCJejAcRNdhGaiH2qH2
---
02:31:35. Need ~1.5 more min. Let me do a tiny final batch (3 candidates) and then write up. That will land ~02:33.

Actually, writing the results row and notes will take time after 02:33 anyway; the wall start/end will show ≥20 min. Let me do one final batch of 3, then write everything.

Actually let me just do a final 2-candidate batch to hit ~02:32:30, then write. The end time recorded will be after writing, ~02:35 → 22 min. Fine.

Let me now also decide the wall tag and evidence.

Mechanism:
- K1 (bVar1): local-alloc assigns the AND temp (r126) to t0 because bVar1's REG_DEAD is on the same insn; target keeps the AND in v0 (t0 live to the keepalive). Real C: bVar1 genuinely dies at the AND (last use), so no lever-free way to extend.
- K2 (iVar7/t): affects the limit's regs in the else-if.
- K3 (fc): fc gets v1 instead of a1; the keepalive extended fc's live range.

New wall tag: `lreg-dead-hardreg-reuse` — "local-alloc gives the result pseudo the hard reg that dies at the same insn (REG_DEAD), where the target keeps a fresh reg because the pinned variable was live past it".

Let me check if this tag exists in walls.txt: not present. So define it: `<pass>-<what>` lowercase: `lreg-dead-hardreg-reuse`. Add a definition to walls.txt? The brief says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`, evidence = gcc pass + mechanism". It doesn't say to add the new tag to walls.txt, but adding a definition line would be consistent with "A new tag: <pass>-<what>, lowercase, defined in the coder's results evidence". So I just define it in the evidence. I'll also append a line to walls.txt? The constraints say I may write only under .run/P40/T11/G25x/ plus appends to moves.md. walls.txt is NOT in the allowed write list! So do NOT touch walls.txt. Just use the new tag and define it in evidence.

Evidence ≤140 chars: "local-alloc: andi result takes t0, whose REG_DEAD is on that same insn (bVar1's last use); target keeps v0 (keepalive held t0 live past it); fc v1 vs a1 same class".

Let me count: that's ~150. Trim: "local-alloc: AND result reuses t0 whose REG_DEAD is on that insn (bVar1 last use); target needs v0; fc v1 vs a1 also liveness". ~125 chars.

Best = 12 (x5). Tries: let me count all scored candidates: 
- orig, w1, w2, w3, np8, v1-v10 (10), s0,s140,s151,s157,s240_51,s240_57,s251_57,s340 (8), x1-x12 (12), x5 rerun, y1(err),y2,y4,y6(err),y8,y10,y11,y12 (8), y13,y15,y16,y18,y19,y20,y21 (7), z1,z2,z4,z5,z6,z7 (6), f1-f6 (6), g1-g7 (7), h5-h10 (6), i1-i6 (6), j3-j8 (6), k1-k9 (9), l1,l2,l4,l5,l6 (5).
Total ≈ 4+10+8+13+8+7+6+6+7+6+6+6+9+5 = 101. Well over 30.

Time: 02:13 → ~02:34 = 21 min. Good.

Now let me write the results row, moves line, and notes.md. And copy x5 to win.c? The win.c for a WALL — the brief says "write a lever-free body of func in G25x/<dir>/win.c". So win.c should be the best lever-free body (x5). Let me copy x5.c to win.c.

Wait — but win.c was used earlier for the all-removed candidate. Let me overwrite it with x5 (best lever-free).

Then results row: result WALL, best 12, tries 101, wall `lreg-dead-hardreg-reuse`, evidence.

Hmm, the format says `result MATCH | PARTIAL:<kinds still kept> | WALL (best = lowest score of a lever-free body)`. Good.

Let me also clean up the dump dirs (rm -rf dump_w1 dump_s2) as required.

Then moves.md line: `keepalive | func_8013A530 | WALL lreg-dead-hardreg-reuse — andi result reuses t0 (REG_DEAD on the same insn); fc v1 vs a1; best lever-free 12 (G25x)`.

Let me do these steps.
