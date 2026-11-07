---
ts: 2026-11-06T22:37:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wak6MlA0ZyOsviiDRcNz
---
The priority formula: floor_log2(n_refs)*n_refs/live * 10000 * size. No loop depth. So the do-while raises priority only by increasing n_refs (or shortening live length).

For s1ang: 2 refs, live 7 → floor_log2(2)=1, 1*2/7*10000 = 2857.
To reach 10000: need floor_log2(n)*n/live ≥ 1. E.g., n=3: floor_log2(3)=1, 3/live ≥1 → live ≤3. Hmm, 3 refs over 3 insns. Or n=4: 2*4/live ≥1 → live ≤8. So 4 refs over ≤8 insns gives 10000.

A do-while on the load could add refs. How did the div do-while lift d from 5185 to 12222? 12222 > cap 10000... wait, the cap isn't in the formula! pri can exceed 10000. The table showed 10000 for d, but the notes say 12222. Maybe the table caps display. Anyway.

For d: 9 refs/27 → 3.17*9/27*10000 = 10570. The notes said 5185 before the do-while — hmm, that suggests d had 5 refs/27? floor_log2(5)=2, 2*5/27*10000=3703. Not 5185. Whatever.

Let me instead directly test: add a do-while around the s1ang load and see the alloc table.

Candidate w5:
```
do { s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12); } while (0);
```
Let me test and dump.

Actually, C0535 says do{}while(0) splits cse1 EBB. The loop body is the load. The loop structure: block with the load, then a test/jump back? For `do { X; } while (0);`, gcc generates a loop with a note; the body executes once, then the condition 0 exits. Since the condition is constant, the loop is removed by loop.c? The C0535 technique presumably keeps it as an EBB split via NOTE_INSN_LOOP_BEG/END without actual branch instructions.

Let me test w5 and inspect.
