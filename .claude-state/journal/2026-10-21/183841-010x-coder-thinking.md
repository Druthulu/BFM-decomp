---
ts: 2026-10-22T00:38:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mbwDjihJ6YZTp20NHWW8
---
Now let me create a batch script that extracts all 7 items' orig.c. Item list:
1. func_8018A180__ov_SC06_029_jr_801898CC: src/ov_SC06_029/ov_SC06_029_jr_801898CC.c func_8018A180, launder, 26 lines
2. func_8017FE9C__ov_SC06_030_jr_8017F65C: src/ov_SC06_030/ov_SC06_030_jr_8017F65C.c func_8017FE9C, launder, 52
3. func_8018FB5C__ov_SC06_032_jr_80182890: src/ov_SC06_032/ov_SC06_032_jr_80182890.c func_8018FB5C, launder, 46
4. func_80190D70__ov_SC06_032_jr_801902EC: src/ov_SC06_032/ov_SC06_032_jr_801902EC.c func_80190D70, launder, 93
5. func_8018CD5C__ov_SC06_033_jr_8018C2D8: src/ov_SC06_033/ov_SC06_033_jr_8018C2D8.c func_8018CD5C, launder, 84
6. SCAN__ov_SC06_033_jr_8018D98C: src/ov_SC06_033/ov_SC06_033_jr_8018D98C.c SCAN, launder, 13
7. func_8017E4DC__ov_SC07_001_jr_8017BEBC: src/ov_SC07_001/ov_SC07_001_jr_8017BEBC.c func_8017E4DC, launder, 55

All "launder" kind. Good — all 7 items are launder.

Note: the "lines" column (26, 52, 46, 93, 84, 13, 55) — probably the number of lines in the function? Let me check: item1 function is ~35 lines. Hmm, maybe it's the number of lines of body. Whatever.

Wait — item 4's tu is src/ov_SC06_032/ov_SC06_032_jr_801902EC.c and func func_80190D70. But moves.md has "keepalive,launder | func_801902EC | MATCH" — different function (the jr target). OK.

Also item 7: src/ov_SC07_001/ov_SC07_001_jr_8017BEBC.c — grep didn't show it since I searched src/ov_SC07_001 which exists? The grep included src/ov_SC07_001 as a dir but no results shown for it. Let me check it exists.

Let me write a batch script.
