# func_80037EA0 (src/800_c.c) — P36 S104 agent e21 — score 33 -> 0, ZERO levers (the `$16` pin removed)

## (a) The residual
COUNT 44 vs 39 + a frame 8 bytes larger: the lever-free do-while walks TWO pointers (`$s1` = p, `$s0` = p-74, both
`addiu …,96` per iteration) plus `$s3` for the mask, where the target walks ONE (`$s0` = D_800C6E2E, every access at
-4/-1/0/-74 off it). The pin forced `p` into `$s0` and so hid the second walked register.

## (b) The pass decision (read on `-dL` dumps, `scratch/dumps_free/` vs `scratch/dumps_c1/`)
- In the tree text `p` is a BIV (`p += 0x60`). loop.c records `p-4`, `p-1`, `p-74`, `p-74` as DEST_ADDR givs, combines them
  onto the textually last one (`combine_givs`, loop.c:5494; list prepended by `record_giv`, loop.c:4341) and reduces them
  into a NEW register (`giv at 49 reduced to (reg:SI 85)`). But `p[0]` addresses the biv ITSELF: find_mem_givs refuses a
  DEST_ADDR giv with mult 1 add 0 (loop.c:4196-4197), so `maybe_eliminate_biv_1` hits the bare REG (loop.c:6022-6024):
  `.loop` "Cannot eliminate biv 72: biv used in insn 32." -> two walked pointers.
- Written as `p = &D_800C6E2E[i * 0x60]` inside a counted loop, `p` is a DEST_REG giv of the counter biv
  (`Insn 29: giv reg 72 src reg 73 … mult 96 add (reg 79)`), reduced to ONE register (`giv at 29 reduced to (reg:SI 91)`),
  and every `p[K]` read uses that register with a displacement. The counter biv stays (it is the call argument).
- Prologue order (score 4 with `mask = …; for (i = 0; …)`): the loop invariant `0xFFF9FFFF` must be materialised after
  `i = 0`; written inline (`&= ~0x60000`) loop.c hoists it into the preheader after the init — proven on bytes only.
Proven on bytes: `--try` 0 (39/39). Proven on dumps: the biv/giv lines above.

## (c) The move that closed it
The walked pointer `p += 0x60` deleted; `p` recomputed from the counter at the top of a `for` loop, mask inlined:

    for (i = 0; i < 0x10; i++) {
        p = &D_800C6E2E[i * 0x60];
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= ~0x60000;
            p[0] = 0;
        }
    }

Also 0: the same with `u32 mask` kept, if `i = 0;` is written BEFORE `mask = …` (scratch/b1.c do-while, b2.c, b3.c).

## (d) GENERATOR PROPOSAL
When a pinned walked pointer `p += K` feeds both `p[0]` and `p[±c]` accesses and the lever-free text grows a second walked
register (`addiu sB,sA,-c` + two `addiu …,K` per iteration), replace the walk with `p = &BASE[i * K];` at the top of the
counted loop (delete `p += K` and its initialiser): a direct `(mem (reg biv))` is never a giv (loop.c:4196), so the biv
cannot be eliminated, whereas a DEST_REG giv of the counter reduces to one register.

## (e) What did not work (bytes)
- Every access indexed directly (`D_800C6E2E[i*0x60 - 4]`, a1/c2): 45 — the multiply givs are reduced separately (54 ins).
- The same through D_800C6DD0 + field offsets (a3): 45.
- `mask = …;` then `for (i = 0; …)` (a2): 4 — prologue order only; `for (mask = …, i = 0; …)` (b4): 4.

## (f) Where the method fell short
related.txt had only func_80037D98 (same global, index-walked) — the shape hint was there (`D_800C6E2E[offset]`); no
generator rewrites a walked pointer into a counter-derived one. The S103 c2 / d16 note ("index by the counter") is the
right family but is phrased for a SECOND pointer `q = p + k`; here the defect is `p[0]` itself blocking biv elimination.
func_80037FC4 (same TU, src/800_c.c:2382) carries the SAME two loops with the same `$16` pin. With this body's loop
and func_80037F3C's body.c loop spliced in, its pin goes and it scores 0 (118/118): `scratch/fc4.c` (not my assignment,
scored read-only).

## (g) Structs question
Plausibly yes, and the struct is the natural reading: D_800C6DD0 is an array of 16 x 0x60-byte channel records (fields
+0x14 u32 flags, +0x5A, +0x5D, +0x5E u8; func_80037F3C/func_8003916C/func_8003A0E4 index the same record). `rec[i].f5E`
etc. is exactly the counter-derived address that closed this (a DEST_REG giv of `i`), and it is MEM_IN_STRUCT_P. But
the target's relocation is D_800C6E2E (= D_800C6DD0 + 0x5E), so a struct over D_800C6DD0 would be identical only after
LINKING at best; the closing text keeps D_800C6E2E. TESTED (scratch/s1.c, body-local `struct Chan` over D_800C6DD0,
`ch = &((struct Chan *)D_800C6DD0)[i]`): score 8 — same 39 instructions and schedule, but the reduced register is the
record START (`lbu 90(s0)`, `lw 20(s0)`) where the target's is the +0x5E field (`lbu -4(s0)`, `lw -74(s0)`): the giv
combine base follows the pointer the source names, so a struct version must still take `&rec[i].f5E` as its walker.
