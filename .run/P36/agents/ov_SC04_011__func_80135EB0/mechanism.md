# func_80135EB0 (src/ov_SC04_011/ov_SC04_011_jr_80135D20.c): T7 agent c15, S103 — WORK IN PROGRESS

Current best lever-free: **score 18** (`body.c`, REG-callee only; 289 = 289 ins). Start was 64 (COUNT, 276 vs 289);
the mechanical best was 52. The 18 is one register swap: `arg1` sits in `$s2` and `m2` in `$s3`, the target has
them the other way round.

## (a) The residual in one sentence
Thirteen missing instructions were two things: jump2's cross-jump folding case 1 and case 2 into case 6's second-call
tail (11 ins), and sched1/sched2 hoisting the next coordinate group's `lhu` over the previous group's stores in the
`(m1|m2)==0` block (2 nops); the register residual is `allocno_compare` ranking `arg1` (12 refs / 175 live) above
`m2` (6 refs / 141 live).

(details and the generator proposals are written below as each is proved)
