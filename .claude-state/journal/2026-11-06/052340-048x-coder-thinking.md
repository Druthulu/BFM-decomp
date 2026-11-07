---
ts: 2026-11-06T12:23:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jom3kKTLgRDjZKIBNKP3
---
Target order:
```
135 li v0,56        ; q[-7] = 0x38
136 sb v0,-5(a1)     ; q[-7] (a1 = q+2? whatever)
137 lui v0,0x0       ; D_801BB632
138 lhu v0,0(v0)
139 nop
140 addiu v0,v0,1    ; y = D_801BB632 + 1
141 sh v0,-8(a1)     ; *(s16 *)(q - 10) = y
142 lui v1,0x6480    ; *((u32*)(q-0x10)) = 0x64808080
143 ori v1,v1,0x8080
144 lui v0,0x400     ; *((u32*)ot) = 0x4000000
145 sw v0,0(s0)
146 li v0,120        ; q[-8] = 0x78
147 sb v0,-6(a1)
148 li v0,16470      ; *(s16*)(q-6) = 0x4056
149 sw v1,-14(a1)    ; *(u32*)(q-0x10) = 0x64808080
```

So target order of the 4 statements after the y store:
- sh y at 141
- sw 0x64808080 (built at 142-143, stored at 149)
- sw 0x4000000 at 145
- sb 0x78 at 147
- sh 0x4056 at 149 area

Mine: `sh v0,-8(a1)` at 143 instead of 141 → so the y store is 2 slots later.

C source order (lines 77-86):
```
*(s16 *)(q - 10) = y;
<barrier>
*((u32 *)ot) = 0x4000000;
q[-8] = 0x78;
*((u32 *)(q - 0x10)) = 0x64808080;
*(s16 *)(q - 6) = 0x4056;
*(s16 *)(q - 0xC) = ((s32 *)a3p)[2] + ((s32 *)a3p)[3] - 0xD;
*(s16 *)(q - 4) = eight;
*(s16 *)(q - 2) = eight;
```
Without the barrier, the y store at 143 is 2 later. In target it's right after the addiu that computes y.

So sched1 reordered. To fix with real C: reorder the statements so the y store comes earlier relative to the others, or introduce a dependency.

Given the target order: y store (141), then 0x64808080 store (149 — last!), 0x4000000 (145), sb 0x78 (147), sh 0x4056 (149?). Hmm, the target order of the sw's: 145 sw 0x4000000, 149 sw v1 (0x64808080). Both after.

Let me see mine's region to know exactly which moved. Let me get the candidate object for b0.

Cheaper: use --keep and dump 128-150.

Actually, the diff says only ONE insn differs: mine has sh v0,-8(a1) at 143 (target 141), and mine 141 = ? Let me get mine's dump.
