# func_80181C84 — e32 (P36 S104) — CLOSED at 0, zero levers

`body.c` (= `scratch/g2.c`): `--try` score 0 (359/359). Levers before: 2 pins (`i` `$18`, `q` `$3`). After: 0.
Also one `goto lShared` label removed (structured C).

(a) Residual (lever-free 96): two independent register defects.
 1. The entity (`s1`, the parameter copy) and the loop counter `i` swap `$s1`/`$s2` everywhere (81 rows).
 2. In both div loops `q = 0x1C0 / n` takes `$a1` instead of `$v1` (8 rows), plus the two `lhu 10/6(s0)` swapped.

(b) Passes (both read off the dumps, `tools/alloc_table.py`, `scratch/dumps_*`):
 1. global.c `allocno_compare` (`global.c:594-607`): the entity r73 is 6*69/249 = 16626 and `i` r78 is 4*29/69 =
    16811 — `i` is allocated first and takes the first callee-saved (`$s1`, `find_reg` pass 1 in reg_alloc_order), the
    entity gets `$s2`. The target needs the entity > `i` > `n` (12800). Giving the entity refs does it: the tail shared by
    case 7 (`goto lShared`) and case 8 written ONCE PER CASE adds 6 entity refs (75 refs / 258 live = 17441 > 16811,
    PROVEN in `scratch/dumps_g2`), and the post-reload cross-jump (`toplev.c:3142` → `find_cross_jump`,
    `jump.c:2371`) re-merges the two identical tails AFTER allocation, so the bytes keep one copy (the S103 c6 mechanism).
 2. `q` is shared by the case 3 and case 4 loops → it dies in 2 places → a GLOBAL allocno; local-alloc has already put
    the REG_UNUSED remainder of `0x1C0 / n`'s `divmodsi4` (r140, born with `q` at the same insn) in `$v1`, so `q`
    conflicts with v0/v1/a0 and takes `$a1`. Declared inside each `if (p != 0)` block, `q` is block-local, ranked by
    local-alloc with the div's other quantities, and lands in `$v1` (S104 d7/d22: a per-arm local instead of a shared
    one; `flow.c:2058-2061` marks the shared one global). The `lhu` order follows with it. PROVEN: `scratch/c1.c` (only
    this move) clears all non-`s1/s2` rows (96 → 82); `scratch/g3.c` (only move 1) leaves exactly the 8 `a1->v1` rows (16).

(c) Moves:
 1. `goto lShared` / `lShared:` → case 7 `if (… < 0) { tail }` and case 8 `if (… > 0) { tail }`, each with its own copy
    of the 5-statement tail (`t34b`, 0x1C, 0x102, 0xE0, 0x34).
 2. `s32 q;` moved from function scope into each `if (p != 0) { s32 q; … }` block.
 3. The stale "LOAD-BEARING pins" comment replaced with one naming these two facts. Both moves are needed jointly
    (82 with 2 only, 16 with 1 only).

(d) GENERATOR PROPOSAL: when a callee-saved permutation puts a long-lived pointer BELOW a counter and the tree has a
`goto L` into a shared tail that uses the pointer, inline the tail at each goto site (drop the label) and check
`floor_log2(refs)*refs/live` against the rival; when a local shared by two loops/cases lands one register off in each
(`$a1` vs `$v1`), declare it block-local in each arm.

(e) Did not work: moving `i = 0` anywhere between the `func_80184604` call and the loop (sched1 sinks it to the block
end, live stays 69 — `pos0..pos9`); before the call (`d2`): live 94 → `i` drops below `n` (s2/s3 swap, 35); a separate
counter per loop (`f1`–`f3`): the entity still loses; deleting the `s1 = a0` copy (`e1`): no change; an extra `s1`
argument to the K&R `func_801843DC()` adds a `move` (97).

(f) Method: the answer was S103 c6 (a shared goto tail, one copy per site, re-merged by cross-jump) — listed in METHOD but
as a CALL tail; it applies to any tail whose refs a losing allocno needs. The alloc table's arithmetic (need +1 ref)
told me what to look for; the residual alone would not.

(g) Structs: no. Neither defect is a memory access question; both are allocation priorities/liveness of registers.
A struct type for the entity (field accesses instead of `*(u16 *)(s1 + 0x34)`) would not change the entity's ref count.
