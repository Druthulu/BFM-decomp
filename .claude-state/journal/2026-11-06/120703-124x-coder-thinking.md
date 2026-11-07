---
ts: 2026-11-06T19:07:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q2kj6nT6cT3zV6NY2S7n
---
h049's asm:
```
la $7, D_8011FD10     ← matches target (lui a3)
move $3, $7           ← matches target (move v1,a3)
...
$L5:
addu $3,$3,104        ← target: addiu a3,a3,104
addu $7,$7,104        ← target: addiu v1,v1,104
addu $6,$6,1
slt $2,$6,20
bne ...
addu $5,$5,104
```

So the ONLY diff: the two increments are in the order (v1, a7) instead of (a7, v1).

The target:
```
addiu a3,a3,104
addiu v1,v1,104
addiu a2,a2,1
slti v0,a2,20
bnez ...
addiu a1,a1,104
```

So I need to swap the two increments' order. Since sched1 preserves the RTL order, I need the RTL order a7-first with the cse canonical staying a7 (the init correct).

The cse canonical choice: in h049 (v1-first increments), cse kept the symbol in a7 (good). In w1 (a7-first), cse canonicalized onto v1 (bad init).

What's the difference for cse? cse's `reg_eqv` canonical is chosen by `max_reg`/`reg_next_eqv`... In cse.c, `make_regs_eqv (dest, src)`: it makes the reg with the LOWER "canonical" number the representative? Let me look at cse.c's make_regs_eqv.

Actually, the cse's choice might depend on `reg_n_refs` or the order of the uses encountered during the cse scan. Since cse scans the insns in order, it processes the copy `v1 = a7` and records the equivalence; later, when it sees a use of one of them, it substitutes the canonical.

The canonical is determined by `reg_eqv`/`make_regs_eqv`: it links the two and the "canonical" is the one with... let me read cse.c.
