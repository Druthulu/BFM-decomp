# func_80133784 (ov_SC04_011) — mechanism (WORK IN PROGRESS)

Best so far: **score 19** (from 21; mechanical best was 12 — but that was a different family, see below).
Best text: `PACK/scratch/v/J.c` (= `PACK/body.c`).

## (a) The residual in one sentence
The lever-free body is 2 instructions SHORT of the target (201 vs 203): two register-to-register
copies that the target keeps (`sltiu v0,v0,1` + `move s2,v0`, and `move v1,v0` after the call) are
coalesced away in mine — and, before the two moves are even reachable, mine hoists the call
argument's sign-extension `sll` OUT of the loop and swaps two callee-saved registers.

## (b) The pass and the decision, read from the compiler's own source
**loop.c — `scan_loop` / `invariant_p` (the `sll` hoist).** `loop_optimize` only sees a loop when the
RTL carries `NOTE_INSN_LOOP_BEG`/`NOTE_INSN_LOOP_END`, and those notes are emitted only by the
`while`/`for`/`do` statement expanders (`stmt.c: expand_start_loop`). Written as `while (1) { … }`,
the body's first call argument `(ashift (reg arg0s) 16)` is loop-invariant
(`tools/reference/gcc-2.7.2/loop.c:2745-2751`, `invariant_p` case REG returns
`n_times_set[REGNO] == 0`), so `scan_loop` records it as a movable
(`loop.c:645-710`) and `move_movables` hoists it into the preheader
(`loop.c:1631` — `threshold * savings * m->lifetime >= insn_count`, and with a call in the loop
`threshold = 1 * (1 + n_non_fixed_regs)` is ~60, so the test always passes).
Written as a **label + `goto`**, no loop notes exist, `loop_optimize` never sees a loop, and the
`sll` stays where the target has it (at the branch target, re-executed every iteration).
PROVEN on bytes: the `sll a0,s5,0x10` / `sra a0,a0,0x10` pair and the `arg0s`/flag register swap
all disappear from the diff the moment the `while (1)` becomes `loop: … goto loop;`.

**global.c — `allocno_compare` (the `$s3`/`$s4` swap).** With the loop fixed, the counter and the
accumulator are two 4-reference global allocnos whose priorities
`floor(log2 refs) * refs / live_length * 1e4` differ by ~2%: measured with
`tools/alloc_table.py`, source order `s3 = 0; s4 = 0;` gives counter 8/89 = 898.9 and accumulator
8/87 = 919.5, so the accumulator is allocated first and takes `$s3`. Exchanging the two
initialisers moves the counter to 8/86 = 930.2 ahead of the accumulator's 8/90 = 888.9 and the
two registers come out as the target has them. PROVEN on bytes (score 22 -> 19).

## (c) Source moves so far
1. `while (1) { … }` -> `loop: { … if (oldc < 5) goto loop; }` — kills the loop-invariant hoist.
2. `s3 = 0; s4 = 0;` -> `s4 = 0; s3 = 0;` — flips `allocno_compare` so the counter gets `$s3`.

## (d) Generator proposal
(placeholder — see the final version)

## (e) Not yet closed
- The two surviving copies (`move s2,v0`, `move v1,v0`).
- The prologue emission order of the two zero-initialisers (a side effect of move 2).
