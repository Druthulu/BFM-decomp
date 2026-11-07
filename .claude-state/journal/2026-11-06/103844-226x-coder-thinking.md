---
ts: 2026-11-06T17:38:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kSuBL08FHXVniCOpZRuc
---
Time 12.9 min. i4 accidentally became a duplicate of the original structure (7).

Let me try a couple more, then start the WALL at 20 min (I still need ~7 min). Let me pick more meaningful experiments:

j1: change the `r[0x49] == 5` comparison to `r[0x49] != 5` with swapped bodies (e5, 7).
j2: use `sh16 = (s32)(angle * 0x10000);` (d3, 7).
j3: make sh16's first def in the *join* block by using a ternary: 
```
sh16 = (r[0x49] == 5) ? (angle << 16) : (p[0x79] << 16);
```
with the call/goto before:
```
if (r[0x49] != 5 && func_8014CB7C() == 0) goto LAB;
sh16 = (r[0x49] == 5) ? (angle << 16) : (p[0x79] << 16);
```
This changes the CFG: the call would be evaluated in the guard. The target has the call only in the else path. The code would differ (the call is evaluated when r[0x49]!=5 — same condition). Actually the CFG is equivalent: `if (r[0x49] != 5 && func()==0) goto LAB;` — the call happens only when r[0x49] != 5. The target's CFG: `if (r[0x49]==5) then else {if (func()==0) goto;}` — equivalent. But the generated code order may differ (the target's beq then call). With the && form, gcc would emit: beq (r[0x49]==5) skip; jal func; beqz goto; ... This is similar! And the ternary would compute sh16 after the merge → sh16 local!

The instruction order would be: beq; jal; beqz; sll... The target's order: beq; sll (delay slot); jal; beqz; lhu; sll. Hmm, the target's then arm computes sh16 in the delay slot of the beq. In the ternary version, the sll would come after the call block. Different bytes.

Still, worth a try.

j4: `sh16 = (r[0x49] == 5) ? (angle << 16) : (p[0x79] << 16);` after the guard.

Let me test j3/j4.
