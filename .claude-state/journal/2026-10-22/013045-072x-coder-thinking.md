---
ts: 2026-10-22T07:30:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_I3Nac1WSWQuAkESyhevi
---
**cand27 = SCORE 0! MATCH!**

cand27:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            vol = vol | 0x3000;                     /* the real 2nd SET of vol (the launder's role) */
            func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
i.e. the launder replaced by `vol = vol | 0x3000;` placed just before the call.

Score 0, 192 ins = target ✓ MATCH!

Let me verify with dt.sh (the score 0 line) and then save it as win.c, write the notes, and record the results row.

Let me confirm the score and check that no lever remains:
- No pins added (the existing $4/$5 pins stay).
- No asm, no launder, no barrier, no keepalive.
- The `vol = vol | 0x3000;` is a plain C compound-ish statement: a real 2nd SET of vol's pseudo (the G11 recipe: a compound/real 2nd set). And the value is preserved because the call argument masks with 0xFFFF and ORs 0x3000 again ✓.

Wait, is the value really preserved? Original: arg = (vol | (0x3000 | sx)) & 0xFFFF. New: vol' = vol | 0x3000; arg = (vol' | (0x3000 | sx)) & 0xFFFF = (vol | 0x3000 | 0x3000 | sx) & 0xFFFF = (vol | 0x3000 | sx) & 0xFFFF ✓ identical.

Let me double check the diff tool's score 0 means byte-identical. Yes, score 0 = MATCH.

Let me now:
1. Copy cand27 to win.c.
2. Verify with dt.sh.
3. Write notes.md.
4. Append the results.tsv row.
5. Append to moves.md.

Also I should double check the "fresh" requirement: diff orig.c against the current src def — I extracted orig.c from the current src ✓ (just now).

Let me also check: does the body still contain the other pins (r4 $4 and av $5)? Yes — those are "pin" levers of a kind not in the row (launder) — allowed to stay ✓.

Let me proceed.
