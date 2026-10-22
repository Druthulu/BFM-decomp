---
ts: 2026-10-21T23:55:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_iNLTxpJRsE4DPzwjqpXD
---
Item 4's ROM asm (40 ins):
```
 0 addiu sp,sp,-40
 1 sw   s0,32(sp)
 2 move s0,a0
 3 addiu a1,sp,16
 4 move a2,a1
 5 li   v0,7
 6 sw   ra,36(sp)
 7 sh   zero,16(sp)
 8 sh   zero,18(sp)
 9 jal  func_80149290
10 sh   v0,20(sp)      ; buf1[2] = 7 (v0 = 7 from ins 5)
11 move a0,s0
12 addiu s0,sp,24
13 move a1,s0
14 move a2,s0
15 li   v0,-24
16 sh   zero,24(sp)
17 sh   zero,26(sp)
18 jal  func_80149290
19 sh   v0,28(sp)      ; buf2[2] = -24
20 li   a0,1
21 addiu a1,sp,16
22 jal  func_80133784
23 move a2,s0
24 move v1,v0         ; ret = v0 → v1
25 beqz v1,a4fc       ; if ret == 0 → +0x88
26 andi v1,v1,0x8000
27 beqz v1,a500       ; if (ret & 0x8000) == 0 → +0x8c (return 0)
28 move v0,zero       ; result = 0
29 lbu v0,30(sp)      ; buf2[3] (offset 6)
30 nop
31 xori v0,v0,0x15
32 j a500             ; +0x8c
33 sltiu v0,v0,1      ; result = (buf2[3] != 0x15)
34 move v0,zero       ; +0x88: result = 0
35 lw ra,36(sp)
36 lw s0,32(sp)
37 addiu sp,sp,40
```
So the ROM: the return value is in $2 (v0) naturally. The pin on `result` ($2) forces $2.

Note: ins 24 `move v1,v0` — the call result is copied to v1 ($3) for the test. Then ins 25 `beqz v1` — so the ret value lives in $3, and $2 is free for the result ✓.

Interesting: the source's `ret` variable is used twice (the != 0 test and the & 0x8000 test) → kept in $3 (v1) ✓.

The `result` variable: set to 0 in two places (ins 28, 34) and to the comparison (ins 33). Without the pin, gcc would compute the return value in $2 anyway (the return reg) — probably identical! The pin might be redundant here.

Let me test: the lever-free version = the same body without the `register int result __asm__("$2")` line (result becomes a normal int).

Note the source has the odd `if (ret != 0) { result = 0; if (...) result = ...; } else { result = 0; }` — the "result = 0" in both branches.

Let me write the lever-free candidate (nopin.c) and score it. Likely 0 → MATCH!

Let me writeit.
