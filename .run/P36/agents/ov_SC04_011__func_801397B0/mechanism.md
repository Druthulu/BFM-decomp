# ov_SC04_011:func_801397B0 — T7 agent c21 re-draw (IN PROGRESS — preliminary, rewritten as work lands)

Earlier agent's files: `scratch/prev_body.c`, `scratch/prev_mechanism.md` (S102 a3, score 2 ORDER).

Current best: score 2 (ORDER) — `body.c` unchanged from a3 (zero store moved above `off = …`).

Working reading (to be proven/refuted below):
- local-alloc quantity priorities (qty level, `scratch/qsim.py` simulates block_alloc tying + `qty_compare`):
  chain {r85 lbu, r86 addiu, r74 off, r76 b1A8} = 10 refs / len 44 → 6818; t2 {r78, r98, r100} = 7 refs / len 20 → 7000.
  t2 goes first and takes $4. Target needs chain > t2.
