# func_8017FEA0 (ov_SC03_097) — score 0, ZERO levers (agent e37, P36 S104)

(a) Residual (free body, 16, REG-caller): in the first if-block the `t0` chain (`li 1`, `&D_8019AEB4`, `lw 0xC4 … ori 2 … sw`,
    `lhu 0x72 … ori 0x1000 … sh`) sits in `v1` and the `0x14`/index pair in `v0`; the target has them the other way round
    (`t0` in `v0`, `0x14` + `lh 0x70` + `sll` in `v1`). The tree's lever: `register s32 t0 __asm__("$2")`.

(b) Pass + decision. The reused `t0` dies 4 times, so it is global (`.lreg`: "dies in 4 places"; `local-alloc.c:472`),
    and the target ORDER depends on that reuse (the anti/output dependences on one pseudo keep `lw 0xC4` under `sw 0xBC`
    and `lhu 0x72` under `sw 0xC4`; every split spelling lets sched1 hoist the loads to the block top — vA/vB/vE, 10–17).
    Local-alloc runs first and hands `v0` (first in `reg_alloc_order`) to the block-local temps that overlap `t0`'s
    lifetimes — the `0x14` holder (r79), the index (r73) and the `sll` result (r88) — so global finds `v0` in r78's
    `hard_reg_conflicts` (`.greg`: `78 conflicts: … 2 …`) and `find_reg` (`global.c:945-990`) gives it `v1`.
    With the pin the pseudo IS `$2`, the locals see it live and step to `v1`.

(c) The move — S103 c18's MERGE, applied to the OTHER register: make the `v1` side one variable too, so NO block-local
    temp exists to take `v0` before global runs:
        v1 = 0x14; *(u8 *)(s1 + 0x75) = v1;      (the 0x14 holder merged into the index variable)
        v1 = *(s16 *)(s1 + 0x70); …
        v1 = v1 << 2;                             (the shift result merged too)
        func_80029178(*(s32 *)((u8 *)D_8019AEF4 + v1))
    Now both `t0` (r78, 12 refs/15 insns, priority 24000) and `v1` (3 deaths) are global; `allocno_compare` orders
    `t0` first → `v0`, `v1` → `v1`; the ior results stay in the same variables (`t0 |= 2`, `t0 |= 0x1000`), and sched2
    can then lift the `sll v1` into the `lhu` load-delay slot (in vG, where the sll result was a fresh local in `v0`,
    the anti-dependence on `v0` pinned the sll after the `sh`, score 6).
    Merging only the 0x14 holder (vD, 16) leaves the sll temp local → it takes `v0`; merging only the sll (not tried
    alone) leaves the 0x14 temp local → same. Both merges are needed (a JOINT edit, METHOD step 5).
    `v1 *= 4` does NOT work (16): expand_mult goes through a fresh pseudo and the copy is what local-alloc sees;
    `v1 = v1 << 2` (or `<<=`) is the spelling.

(d) GENERATOR PROPOSAL: when a pinned `$2`/`$3` temp is reused for N values and the residual is a pure v0<->v1 swap
    against the OTHER short temps of the same block, merge those short temps (a constant holder, an index, its shifted
    copy) into ONE second variable — including `idx = idx << k` with the array access rewritten as a byte offset — so the
    block has zero local quantities and global's priority order decides both registers.

(e) Did NOT work (bytes): split temps (10), fresh ior results with the merged v1 (vF 17, vG 6), the enumeration of
    96 combinations of {reuse/inline/split} × {flags,u16,0x14} (best 6 = vG), `v1 *= 4` (16).

(f) Method: the 96-way sweep found nothing the reading did not; the dumps (.sched launch log, .lreg deaths) were what
    showed that the ORDER needs the reuse and the REGISTER needs zero locals.

(g) Structs: partially. `s1` is the actor (`u8 +0x75`, `s16 +0x70`, `u16 +0x72`, `s32 +0xB4/+0xBC/+0xC4`, `u8 +0xC0/+0xC1`).
    Field accesses would not change this decision: the loads hoist on `memrefs_conflict_p` (same base, disjoint offsets)
    whether or not `MEM_IN_STRUCT_P` is set (`sched.c:817`), so the reuse is still what orders them; and the allocation is
    decided by which pseudos are block-local, which struct typing does not touch. What a struct WOULD buy: the
    `D_8019AEF4[v1]` byte-offset cast could become `D_8019AEF4[idx]` only if the index were a `u8 *`-typed pointer walk,
    not a field.

Copies (same text, `D_` symbols renamed, function renamed — all score 0; scratch/copies/LIST.tsv):
  func_80181EDC  src/ov_SC02_028/ov_SC02_028_jr_8017D898.c
  func_80180400  src/ov_SC03_101/ov_SC03_101_jr_8017CA80.c
  func_8018383C  src/ov_SC03_104/ov_SC03_104_jr_80182038.c
