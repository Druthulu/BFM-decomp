---
ts: 2026-11-06T13:43:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_z6BDoj9GX1eRf9hMFIHc
---
Target head:
```
8e50: addiu sp,sp,-24
8e54: move t1,a1        (su = x)
8e58: lui a1,0x80
8e5c: ori a1,a1,0x8080  (rgb)
8e60: move t2,t1        (sv = y? no)
8e64: lw t5,40(sp)      (cy?)
8e68: move t3,a2
8e6c: sw s0,16(sp)
8e70: lw s0,52(sp)      (tp)
8e74: lw t9,56(sp)      (zoff)
8e78: lbu t6,44(sp)     (w)
8e7c: lbu t7,48(sp)     (h)
8e80: lui t0, D_800A5E60
8e84: lw t0,0(t0)
...
```
So the target loads all the parameters early (index 8 = lbu t6 at 8e78, index 9 = lbu t7 at 8e7c), then the D_800A5E60 load.

Mine (barrier A removed): lbu t7 at index 13 instead of 11. So mine sinks the lbu h by 2 (after the D_800A5E60 load and maybe more).

Let me see mine's listing head.
