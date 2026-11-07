---
ts: 2026-11-06T15:30:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ab1uhG9xgeDS2OLZGbs5
---
Baseline orig.c scores 0 with launder. Now I need to remove the launder and still score 0.

The launder:
```c
mp = (u8 *)D_801D0FC0;
__asm__ __volatile__("" : "=r"(mp) : "0"(mp));  // !FAKE: launder — NEEDED DIFFERS
((void(*)(void *, unsigned))func_800233CC)(mp, 0x80);
```

The launder forces mp into a register (a0) probably rather than folding the address. Target likely does:
```
lui a0, %hi(D_801D0FC0)
addiu a0, a0, %lo(D_801D0FC0)
jal func_800233CC
li a1, 0x80
```
without launder, gcc might use `lui a0` then `addiu a0`? Actually it's just passing the address as arg0. The launder is a copy of the pointer into a register... Hmm.

Let me see the actual diff. Run dt.sh with more tail lines to see the diff. The second arg to dt.sh is tail_n which is the tail of the output. Let me run with tail 60.
