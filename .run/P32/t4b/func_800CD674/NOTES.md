# func_800CD674 (md_MAIN_009, 174 ins) — S83 hand probes
Residual: prim 4's masked-p (`and`, idx 156 / `or` 164) $a3 vs target $t1 (= m24's pinned register $9, dying at that `and`).
P2 variants — A: inline `*ot = (otv & mff) | ((u32)p & m24)` (175 ins, 44); B: block-scoped `pm3` before the `otv` load
(174, 31); C: block-scoped `pm3` after the load (175, 44). All regress: a fresh pseudo for prim 4 displaces the hoisted
constants (the report's "+1 pseudo" finding reproduced). The tie needs m24's qty_phys_sugg to reach the and's result WITHOUT a
new declared pseudo: i.e. the SAME `pm2` variable but with m24 dying at prim 4's `and` in a way local-alloc credits — or the
shared pm2 must be born at prim 4 (prim 3 using a different spelling). Untested: swap roles — prim 3 inline, prim 4 = pm2
(so pm2's birth is at prim 4's `and`, where m24 dies); permuter_ils plateaued at the same pair (S83).
