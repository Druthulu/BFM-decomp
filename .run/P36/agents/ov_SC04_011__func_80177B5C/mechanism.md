# func_80177B5C (ov_SC04_011_jr_801734BC.c): T7 agent c46, minimum-lever. Score 0 with ONE lever

Start: c19's plain-C body (`scratch/prev_body.c`, 0 levers, score 2, ORDER class; c19's full reading is in
`scratch/prev_mechanism.md`). Final: **score 0** (147/147, `--try` prints MATCH). `PACK/body.c` has **1 lever**
(the tree carries 23 per copy). The lever is the tree's own launder on `w`, in the tree's position:

```c
    w = c0 | x1;
    __asm__("" : "=r"(w) : "0"(w)); // !FAKE: launder w — a second set of w stops sched1 launching the p[2] `or` at its store (birthing_insn_p, sched.c:2469), so it stays ahead of the cl chain and sched2's equal-priority tie (sched.c:2385) keeps that order; no plain spelling does (S103 c19) (P36 S103 c46 minimum-lever)
    c = v << 6;
    c |= 0x4016;
    cl = c << 16;
    p[2] = w;
```

Nothing else changed from c19's body: the one named temp `w` (`u32 w;`) plus the asm line. The other 22 tree levers
(7 pins, 3 more launders, 3 barriers, 1 keepalive) are replaced by c19's plain-C moves.

## (a) The residual

c19's body: every register is right. The prim-1 p[2] value `or v0,a1,v0` is emitted two slots late, after
`sll v1,t9,6; ori v1,v1,0x4016` where the target has it before them.

## (b) The pass and the decision (proved on this function's own dumps, `scratch/c46/dumps_one` vs `dumps_zero`)

- sched2 (post-reload): the `or` and the `sll`/`ori` of the cl chain are both priority 2 (the `.sched2` dump prints
  them). `rank_for_schedule` (`sched.c:2385`) then breaks the tie by INSN_LUID, which is sched1's output order.
- sched1 output without the lever (`dumps_zero/zero.i.sched`, uids): `80 84 86 64 65 82 91 88`, meaning c0<<=16,
  c=v<<6, c|=0x4016, x1, **w=c0|x1**, store p[2], cl=c<<16. The `or` (82) has one set, and its dest is live when its
  consumer, the store 91, is scheduled backward. `birthing_insn_p` (`sched.c:2469`) is true, so `adjust_priority`
  (`sched.c:2507`) gives it the launch priority and it is placed directly before the store. The cl chain's first two
  insns (c is set twice, so they are not launched) keep source/LUID order and so sit ABOVE the `or`. sched2 inherits
  that order through the tie.
- sched1 output with the launder (`dumps_one/one.i.sched`): `80 64 65 82 84(asm) 86 88 93 90`, meaning x1,
  **w=c0|x1**, the asm, c=v<<6, c|=0x4016, store p[2], cl=c<<16. The asm's `(set w (asm_operands … w))` is a second set
  of w, so `reg_n_sets[w] == 2` and neither w insn is "birthing". Both keep their source position ahead of the c chain,
  so the sched2 tie gives the target's order. Registers are unchanged: the lever-free and the one-lever bodies differ
  only in that order (2 → 0), and local-alloc still ties w to x1 in v0, because w still dies once and so stays a
  local-alloc candidate (`local-alloc.c:472`).

## (c) The single-lever table (each is one lever added to c19's score-2 body; `scratch/c46/v_*.c` / `.out`)

| lever | where | score |
|---|---|---|
| **launder w** | right after `w = c0 \| x1` (the tree's position) | **0** |
| **launder w** | after the cl chain, right before `p[2] = w` | **0** |
| launder c | after `c = v << 6` | 2 |
| launder c0 | after `c0 <<= 16` | 23 |
| launder cl | after `cl = c << 16` | 74 |
| launder x1 | before the c chain | 84 |
| pin c $3 | declaration | 2 |
| pin cl $3 | declaration | 2 |
| pin c0 $5 | declaration | 2 |
| pin yt $4 | declaration | 2 |
| pin v $25 | declaration | 23 |
| pin w $2 | declaration | 69 |
| pin x1 $3 | declaration | 74 |
| pin x1 $2 | declaration | 90 |
| pin c0 $2 | declaration | 115 |
| barrier | after `cl = c << 16` | 105 |
| barrier | after `p[2] = c0 \| x1` (inline) | 72 |
| barrier | after `w = c0 \| x1` / after `c0 <<= 16` | 139 |
| keepalive w | after `p[2] = w` | 2 |
| keepalive w | after `w = c0 \| x1` | 74 |
| (none) | named `w` temp, no lever | 2 |

The smallest set that reaches 0 is one lever, either launder on w. Pins cannot help: a pin changes a register,
and every register here is already right. The only defect is ORDER, and the only thing that fixes it is making the
`or` a non-birthing insn. Barriers (a volatile asm) are worse than no lever: 140 insns and a 16-byte frame instead of 24 (measured). My guess,
NOT proved on dumps, is that the volatile asm stops cse's substitution of the K&R narrow parameters, which c19's shape
relies on.

## (d) Zero levers: not reached. Why it stays shut

To get the target order, sched1 must place the `or` above `c = v << 6; c |= 0x4016` (or the chain must fall between
the `or` and the store). The launch rule puts a single-set `or` immediately before its store, with nothing in between.
If the chain goes after the store instead, it no longer overlaps w's v0 life, and local-alloc gives the c temps v0
(c19, proved). So the `or` itself must be multi-set while still dying once (a local-alloc candidate). Plain C has no
such insn:
- `w = c0; w |= x1` / `w = x1; w |= c0`: cse forwards the copy and flow deletes it, so `reg_n_sets` is 1 again
  (c19, 12 variants, all score 2).
- `x1 |= c0` in place (x1 set twice): x1's zero-extend loses its launch and floats to the top, and x1's qty loses v0
  (`z_x1_inplace*`: 81; c19's searches over every placement: ≥2).
- Reusing an earlier temp for the value (`gg = c0 | x1; p[2] = gg`, a real second value): the temp now dies twice, is
  refused by local-alloc (`local-alloc.c:472`) and goes global, and the c temps take v0 (`z_gg_reuse`: 78). A post-loop
  reuse fails the same way (c19: 70).
- c19's four annealing searches (statement order, including p[2]/p[3] store order, plus spelling options) floor at 2.
The asm launder is exactly the construct that plain C cannot write here: a second set of a register that emits
nothing and survives cse and flow.

## (e) Generator proposal

When a lever-free body's residual is ORDER-only (all registers match) and the misplaced instruction is a single-set
REG def feeding a store that sched1 launched directly before its consumer (`birthing_insn_p`): delever the tree body
down to the plain-C body plus the tree's ONE launder on that def's variable (`x = …; __asm__("" : "=r"(x) : "0"(x));`),
and drop every pin (pins cannot fix order). In `delever_search` terms: for an ORDER-class residual at a small score,
re-add the tree's levers one at a time, launders first, and keep the first that reaches 0.

## (f) Where the method fell short

- c19's plain-C body plus a one-at-a-time lever table found the minimum in one parallel batch (21 variants, about a
  minute). Proposal: a `--minimum-lever` mode that takes the best lever-free body and tries each lever kind of the tree
  body on each variable of the differing hunk.
- The `.sched` uid order of the two bodies, compared side by side, is the whole proof here (`scratch/c46/rtlshow.py`
  prints the Nth..Mth insns of a dump compactly). The residual view alone cannot show sched1's order.
