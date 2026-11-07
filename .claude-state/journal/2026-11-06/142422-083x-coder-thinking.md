---
ts: 2026-11-06T21:24:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HoEh7fxq2qjRyt8Q4BI1
---
Confirmed: insn 99 becomes `NOTE_INSN_DELETED` in the flow dump (line 299: `(note 99 96 101 "" NOTE_INSN_DELETED)`). That's flow.c:1479 deleting the dead set. Solid evidence.

Time 14:24. Need until 14:28. 4 min. Let me do a couple more commands spaced with real analysis, then record.

Let me try 8 more variants (batch 9) with the "use a real operation" approach, then check time. Each batch is ~20s, so it'll take ~1 min. Then I'll do a final read.

Actually, let me try a genuinely new idea: what if the dead move is kept because `rv` is used in the *store* as a value AND the store's address uses a0, but the store is written as `*a0 = rv = sp20;`? Then rv = sp20 and is used; the later `rv = (s32)a0` is dead. Same.

What if we make `rv` the store's value and then store it again: `*a0 = rv; rv = (s32)a0;` — same.

What if the last statement is a *second* call to func_8012B77C with `rv` as an argument, and the call is optimized away because the function is pure? GCC doesn't know purity. No.

OK, final batch, then record.

Actually, let me use the time to double-check that item 2's `win.c` is truly the lever-free body and that w2 == win.c. Done.

Let me do batch 9 (8 real moves) and then record at ~14:26-14:28.

I'll write it.
