---
ts: 2026-10-22T21:41:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ROlWX3E6ZZBmSD3Rvqbl
---
Same class as item 2: `sw ra` sunk one slot. Target: sw ra at slot 3, mine at slot 4.

Let me try the same family of moves: init at decl for `loc`? The body stores into `loc.a.raw[0]`, `loc.a.raw[2]`, and `loc.b` = D_801E2DD8.

Try: make the first memory op appear before the load... What's in the block? Let me see the disassembly of mine and target around the prologue.
