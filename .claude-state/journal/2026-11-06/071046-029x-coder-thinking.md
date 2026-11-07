---
ts: 2026-11-06T14:10:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jRSz8sItxaDf42JNrD6b
---
Now clear:
- reg 160 = i
- reg 161 = src
- reg 162 = dst
- reg 159 = n

And:
- insn 307: i = 0 (reg 160)
- insn 310: src = mem (reg 161)
- insn 312: asm(src) uses reg 161
- insn 316/318: dst = src + n*2 (reg 162)
- ...
- insn 329: asm(i) uses reg 160 (the i keepalive) — scheduled late among the mults
- ...
- insn 397: i++ (reg 160 +1)
- insn 400: src++ (reg 161 +2)
- insn 394: dst++ (reg 162 +2)
- insn 406: slt i, n

Register refs from the table:
- Register 159 used 9 times (n)
- Register 160 used 14 times (i)
- Register 161 used 15 times (src)
- Register 162 used 11 times (dst)

Wait, let me confirm the table:
```
Register 159 used 9 times across 42 insns; dies in 0 places; GR_REGS or none.
Register 160 used 14 times across 41 insns; dies in 0 places; GR_REGS or none.
Register 161 used 15 times across 40 insns; dies in 0 places; GR_REGS or none; pointer.
Register 162 used 11 times across 37 insns; dies in 0 places; GR_REGS or none; pointer.
```

So i (160) has 14 refs, dst (162) has 11 refs. Wait, that's with the keepalive (the +refs). The keepalive on i added refs. With the asm removed, i would have 14 - X refs and src 15 - Y refs.

The comment: "+3 refs on i (depth-3)" and "+2 refs on src (depth-2)". So without asm: i = 14-3 = 11? dst = 11. src = 15-2 = 13. Hmm i and dst would tie at 11. Then lifetime/size breaks the tie; and the result is dst gets t2, i gets t3 (as observed).

With asm: i=14, dst=11 -> i wins t2.

So to crack: I need i's real ref count > dst's, without asm. Options:
(a) Raise i refs by ≥1 real use.
(b) Lower dst refs by ≥1 real use.

Both must not change the emitted code (which is fixed by the target). Since target code is the same as with keepalive, the real-C version must produce the identical instruction sequence AND have i's priority > dst's.

Key insight: refs count comes from RTL occurrences. If I can write real C where i appears in one more RTL insn that would be generated anyway (i.e., the code already exists but attributed to a different pseudo, or a copy is folded), then refs increase without changing code.

Hmm. Alternatively, note that local-alloc priority also uses lifetime (`qty_size`, shorter-lived higher priority) and `qty_compare_1`. Let me read qty_compare_1 to see the exact comparison.
