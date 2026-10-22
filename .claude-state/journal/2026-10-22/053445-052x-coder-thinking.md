---
ts: 2026-10-22T11:34:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_I8xGYo7JQeUERKQXepqR
---
The constant is materialized in reload (after sched1), so it's not visible in the RTL dumps before that. The `li $4,0x66660000` at line 11907/12386 — two occurrences in the .s? Hmm, those are in different functions maybe. Actually the .s is the whole TU. Let's find func_801832A8's section.

Anyway — since the constant is created by reload, the POSITION of the lui/ori is decided by reload, which runs after sched1. Reload places the constant's definition at the point of the pseudo's set in the RTL.

So: in the ORIGINAL, the pseudo for the constant is SET at the top of the join block (before the vol chain), and in w4 it's set just before the mult.

Hmm, but reload happens after sched, so the pseudo's SET insn position was decided by sched1 in both cases.

Hmm, but the RTL dumps don't show 0x66666667 — because the pseudo is set by a `lui`/`ori` pair with the constant in a "split" form, or the constant is stored as `(const_int 1717960703)` in a SET. Let me grep for 1717960703 in the dumps.

1717960703 = 0x66666667. Let me grep.
