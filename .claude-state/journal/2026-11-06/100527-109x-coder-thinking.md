---
ts: 2026-11-06T17:05:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PHHLUmRe8F45svdPXLO7
---
Cleaned up. Now let me do a final verification that everything is in place:
- results.tsv: 4 rows ✓
- moves.md: 4 lines ✓
- win.c for 3 MATCH items scoring 0 ✓
- item 1: WALL, best c38.c ✓
- log written ✓

No commit (the brief says no git/commit).

Let me do a final sanity check on the win.c files' lever-freeness for the row kinds:
- Item 2 (launder): win.c has no `__asm__` except the pins. The pins are `register ... __asm__` — these are register-asm pins, kind=pin, allowed (row kind is launder). ✓
- Item 3 (pin): win.c has NO asm/register at all (I verified grep rc=1). ✓
- Item 4 (keepalive,launder): win.c has only the a0 pin (kind=pin, allowed). ✓

Wait, for item 2, the win.c keeps the ang and pv pins, which are `register __asm__` — the row kind is "launder" only, so pins are other-kind and may stay. But the brief's PARTIAL rule says "the expert diffs orig.c -> win.c lever lines". The expert will see the pins remain; since pins are not in the row kinds, that's fine.

For item 4, the win.c keeps the a0 pin ($16) — same.

One concern: for item 3, the row kind is "pin", so ALL pins must be gone. win.c has none. ✓

For item 1 (WALL), no win.c needed.

Now, one more check: the brief says "MATCH = the kinds in <dir>/kinds gone". For item 2, the launder `__asm__("" : "=r"(pv))` is gone ✓. For item 4, both the keepalive and both launders are gone ✓.

Also the "no new lever of any kind" — did I add any? 
- Item 2: added `pv = pv & 0xFF000000;` (a real statement, not a lever). ✓
- Item 3: added `v0b` variable, `s16 a0r`, `v1 <<= 16; v1 >>= 16;` — real C. ✓
- Item 4: added `do{}while(0)` with the !FAKE marker (allowed), a struct assignment, `q = 0` dead reset (real C). ✓

Good. Let me also double check the do-while marker in item 4's win.c.

Actually I already grepped: only line 3 (the a0 pin) has asm. The do-while marker is there.

Let me write the final report. The RETURN format: final message starts with the bare word done, then ≤10 lines: per item dir result best wall; nothing else.

Format:
done
- func_800D1E9C: WALL, best 5, jump2-crossjump-arms
- func_8018AB20: MATCH, best 0, -
- func_8017F200: MATCH, best 0, -
- func_801888F4: MATCH, best 0, -
No commit (brief: no git/commit). results.tsv 4 rows; moves.md 4 lines; log phase-ends/current/logs/T11.cW47.md.

The instruction says "+ ≤ 10 lines: per item dir result best wall; nothing else." So I should keep it minimal. But I should mention the no-commit. Hmm, "nothing else" — I'll keep it to the 4 lines plus maybe one line. Let me follow strictly: 4 item lines.

Actually the report contract says "starts with one plain word, done... then says what changed and the commit." But this task says no commit. I'll add one short line "no commit (brief: scratch-only)". That's within 10 lines.
