# func_8017E830 (ov_SC04_015_jr_8017AE2C.c) — e33, P36 T7 S104 — SCORE 0, ZERO levers

(a) Residual: same 96 instructions; the `u` chain (`andi s4,0x3f; sll; move; addiu 16`) was hoisted above the
`p[3]/p+4/p[7]` stores, so the chain could not reuse `$v0`/`$v1` and took `$v1/$a0/$a1` (score 18). The tree's
`__asm__("")` barrier was faking the target's sched1 order (chain AFTER the three stores).

(b) Pass: sched1 (`sched.c`). Every insn in that stretch has priority 1 (`priority()`, sched.c:1425 — only load latency
raises it), so ties are broken by `schedule_select`'s potential-hazard pick (sched.c:2660-2670): a STORE always beats an
ALU insn of the same priority, so backward list scheduling places ALU insns EARLY unless they are `birthing_insn_p`
(sched.c:2469-2505: dest set exactly once, `reg_n_sets[i] == 1`) and so get `max_priority` (adjust_priority,
sched.c:2540-2548). In `u_hi = …; u_lo = u_hi; u_hi += 0x10;` the u_hi pseudo is set twice → its insns are not
birthing → hoisted. Proven by the `.sched` trace: "insn 107 has a greater potential hazard" at T-33/T-35/T-37/T-38.
Local-alloc then follows sched1 order (the chain overlapping the 0x808080 pseudo and GetTPage's `$v0`).

(c) Move (proven on bytes, --try score 0):
```c
    s32 u;  u8 u_lo;  s32 u_hi;
    u = (s4 & 0x3F) << 2;
    u_lo = u;          /* u8: a QImode SUBREG copy — cse cannot fold it (different mode), so the `move` survives */
    u_hi = u + 0x10;   /* a fresh pseudo, set once */
```
Every pseudo in the chain is now set once → birthing → scheduled (backward) the moment its consumers are, i.e. right
before its stores; local-alloc then gives the chain `$v0`/`$v1` and combine_regs ties `u_hi` to `u` (the in-place
`addiu v0,v0,16`). The width is what keeps the copy: with `s32 u_lo` cse forwards `u` and deletes the copy (score 7,
variant I drops u_lo: 95 ins); with `u8 u_lo, u_hi` the add is folded into one addiu off the copy (score 16).
Variants scored: u8 both 16, s32/u8 16, u8/s32 via in-place 18, **t;u8 u_lo;s32 u_hi = 0**, t;u8;u8 16, t;s32;u8 16;
`p[0x14] = u + 0x10` without u_hi also 0 (variant H). Removing `s32 pad[10]` → 14 (frame 0x50 needs the 0x28 bytes;
0x28 = sizeof(POLY_FT4), so the original probably had a stack POLY_FT4 or similar that the body no longer names).

(d) GENERATOR PROPOSAL: when an ALU chain `v = …; w = v; v += K;` is hoisted above stores it feeds (ORDER residual,
target keeps it after the stores and in `$v0/$v1`), rewrite it as `t = …; u8 w = t; v = t + K;` — one pseudo per value,
and give the COPY the width of its only use (the byte store), so every insn is `birthing_insn_p` and the copy survives cse.

(e) Did not work: the barrier removal alone (18); the sweep's statement swaps (best 5); width moves on x_lo (R12).

(f) Method: the `.sched` trace (the hazard lines + which insns got 7f000001) settled it in one reading; the residual text
suggested a register lever. Rule worth adding to METHOD: "an ALU chain hoisted above stores = the chain is not
birthing; make each pseudo single-set".

(g) Structs: a POLY_FT4 type for `p` would not change this decision (the stores are already `/s` MEM_IN_STRUCT QI
stores with distinct offsets; the hoist is a priority/hazard tie among ALU vs store insns, not a dependence). It would
make the text readable (`p->u0 = u_lo`) and probably explain `pad[10]` (a POLY_FT4 local); not tested.

Copies in other TUs: none found (`grep -rln 'y_hi = Y + 0xF'` → this TU only).
