# func_80183ADC (ov_SC02_027) — agent e18, P36 T7 S104 — score 0, ZERO levers

(a) Residual: score 4 (COUNT, 59 vs 58) — mine copies the call result into `$a0` right after `jal func_8012C1B8`
(`move a0,v0` before the `bnez`) and leaves the `jal func_8001C214` delay slot empty; the target keeps the value in `$v0`
across the branch and does the `move a0,v0` in that delay slot. The tree faked it with a launder
`__asm__("" : "=r"(v0) : "0"(v0))` before the call.

(b) Pass and decision (proved on dumps: `scratch/dumps_free/` vs `scratch/dumps_close/`, `tools/alloc_table.py`):
- The decompiler's chain `if ((*(s32 *)(a0 + 0x20) = v0 = f()) == 0)` expands to TWO pseudos: r75 = the call value
  (block-local, used by the store and the test, tied to `$v0` by local-alloc) and the variable r73 = a COPY of r75
  (insn 15), live into the next block. r73 is born while r75 lives in `$v0`, so it conflicts with `$v0`; global.c's
  `find_reg` then takes its remaining copy preference, `$a0` from the argument copy (global.c:1001-1010; preferences
  recorded at :1589/:1608). `alloc_table`: free r73 "conflicts v0,sp prefers a0".
- Written as three statements (`v0 = f(); *(p) = v0; if (v0 == 0)`) there is ONE pseudo, set straight from the hard
  `$v0`: r73 priority 20000, "conflicts sp, prefers v0,a0" → `$v0`, and the arg copy becomes the target's delay-slot
  `move a0,v0`. Proved on bytes (`--try` 0).

(c) Move: split the assignment chain in the `if` condition into `v0 = call(); store = v0; if (v0 == 0)` (the shape of the
lever-free siblings func_80144A98, func_801320D8), delete the launder and its `§67` comment (it describes the lever).

(d) GENERATOR PROPOSAL: when a body tests an assignment CHAIN `if ((M = v = CALL()) == 0)` and `v` is used after the
branch, rewrite it as `v = CALL(); M = v; if (v == 0)` — the chain's value temp is a second pseudo that pushes `v` off
`$v0` (a new "R-split-chain" rule; the sweep's R7/R8/R9/R10/R14 families all mutate around the chain, never split it).

(e) Tried: nothing else was needed; the sweep's best was 2 (R14 param width + R9 swap) — compensating, not the mechanism.

(f) Method note: `alloc_table.py` on the free body answered it in one read ("conflicts v0 … prefers a0" on the variable
and a block-local r75 in `$v0` before it) — step 4 was the whole crack; `DUMP_ROOT` must be the PARENT of `dumps_<tag>`
for alloc_table (passing the dumps dir itself prints "NO DUMP").

(g) Structs: no. The lever is a pseudo split by the C expression shape; a struct type on `a0` would not change it.

Copies closed with the same move (the only three `chain + launder` sites in src/, scanned):
- src/ov_SC02_027 func_80182868 (agent e18's third pack, score 0)
- src/ov_SC02_028/ov_SC02_028_jr_8017D898.c func_80180970 (score 0; .run/P36/agents/ov_SC02_027__func_80182868/scratch/copy_SC02_028_func_80180970.c)
