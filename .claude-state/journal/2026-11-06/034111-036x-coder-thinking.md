---
ts: 2026-11-06T10:41:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nvAHeSDTGDJV9WUwHO1R
---
Now only the `sw v1,88(s0)` (unk58 store) is moved: target has it at 31 (right after the lui/addiu of &D_801907C4), mine has it at 34 (after ori/sw of unkC4).

Target order:
```
28 lw v0,196
29 lui v1,D_801907C4
30 addiu v1
31 sw v1,88(s0)
32 ori v0,v0,2
33 sw v0,196
```
Mine:
```
29 lui v0? ... 
```
Wait, with the do-while the regs might be right now (no pairs reported). Mine has: lui/addiu (v1) then ori/sw (v0) then sw v1,88. So the store to unk58 was sunk below the unkC4 read-modify-write. The C order is:
```
t = unkC4;      (do-while block)
unk58 = &D_801907C4;
unkC4 = t | 2;
```
Target: store unk58 before the ori/sw. Mine: store after.

Why is the store sunk? sched1 reorders. The store to 88 and the load/store of 196 don't alias. sched1 could put the store anywhere. Target has it early.

Fix ideas: include the unk58 store inside the do-while block? `do { t = unkC4; unk58 = &D_801907C4; } while (0);` — then both are in the split block, and the ori/sw outside. Let's try that. Also maybe wrap all three.

Let me test both:
- v_dw2: do { t = unkC4; unk58 = &D_801907C4; } while(0); then unkC4 = t|2;
- v_dw3: do { t = unkC4; unk58 = ...; unkC4 = t|2; } while(0);

Try both.
