# func_800391D4 (main/800_c, 75 ins) — S83 hand probes (residual 3: off init BEFORE arg1's hoisted sll/sra; target has it AFTER)
G/G2 `D_800C6DD4[i * 0x60]` giv instead of the hand-kept `off` counter: 78 ins / 69 (the address becomes a base+giv, absolute
addressing lost). H `(s16)i * 0x60`: 75 / 24. T1 explicit `a1v = arg1` before `off = 0`: 18. T2 promotion first: 28. T3 `off = 0`
before `base = …`: 11. All worse than the seed's 3 → the sll/sra pair is NOT a source-visible promotion; it is the loop's
invariant hoist (move_movables) and `off = 0` is preheader source code — the order is compiler-fixed for this shape.
Untested: make `off`'s init ALSO a movable — e.g. `off` assigned inside the loop from an invariant (`off = k;` where k is a
loop-invariant register) so both come out of move_movables in loop order; or drop `off` in favour of the address giv of
`entry` (`&D_800C6DD0[(s16)i * 0x60]` is already a giv — reuse its register for the D_800C6DD4 index via a shared base).
