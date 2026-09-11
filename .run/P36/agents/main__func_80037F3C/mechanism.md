# func_80037F3C (src/800_c.c) — P36 S104 agent e21 — score 15 -> 0, ZERO levers (the `$16` pin removed)

## (a) The residual
COUNT 38 vs 34 + a frame 8 bytes larger: the lever-free text walks THREE registers per iteration (`$s2` base, `$s3` = p,
`$s0` = p-1) where the target walks TWO (`$s2` = D_800C6DD0, `$s0` = `$s2`+94, every field at -4/-1/0/-74 off `$s0`).

## (b) The pass decision (read on `-dL` dumps, `scratch/dumps_free/` vs `scratch/dumps_b2/`)
- Tree text: `p` and `base` are two BIVs (`p += 0x60; base += 0x60`). loop.c combines p's DEST_ADDR givs (p-4, p-1,
  p-74, p-1) onto the textually last `p-1` (`combine_givs`, loop.c:5494; `record_giv` prepends, loop.c:4341) and reduces
  them into a new register (`giv at 46 reduced to (reg:SI 82)`), but `p[0]` is the biv itself — no DEST_ADDR giv for
  mult 1 add 0 (loop.c:4196-4197), `maybe_eliminate_biv_1` REG case (loop.c:6022-6024) -> "Cannot eliminate biv 72: biv
  used in insn 49." -> base + p + the reduced giv = three walked registers.
- Closing text: ONE pointer biv `base`; every field is `base[K]`, a DEST_ADDR giv with add 90/93/20/93/94, all combined
  onto the last (`+94`) and reduced to one register initialised `base + 94` (`addiu s0,s2,94`, the target's). The biv
  `base` survives only because the call argument `base + 0x10` is a DEST_REG giv "not worth while, 0 vs 17" (loop.c:3828)
  — the target's `addiu a1,s2,16` + `addiu s2,s2,96`.
Proven on bytes: `--try` 0 (34/34). Proven on dumps: the `.loop` lines quoted.

## (c) The move that closed it
The second pointer `p = base + 0x5E` deleted; every access written as a field offset of the one walked record pointer,
the walk moved into the `for` header:

    base = D_800C6DD0;
    for (i = 0; i < 0x10; i++, base += 0x60) {
        if (base[0x5A] != 0 && base[0x5D] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(base + 0x14) = 0;
            base[0x5D] = 0;
            base[0x5E] = 0;
        }
    }

Also 0: the do-while with `p = base + 0x5E;` recomputed at the top of the body and `p += 0x60` deleted (scratch/b3.c).

## (d) GENERATOR PROPOSAL
When two walked pointers step by the same K (`p = base + c; … p += K; base += K;`) and the lever-free text carries a third
walked register, delete the derived pointer `p` and rewrite its accesses as `base[c + off]` (or recompute `p = base + c` at
the top of the body): one biv whose fields are all DEST_ADDR givs reduces to one register, while a second biv read at
offset 0 can never be eliminated (loop.c:4196, :6022).

## (e) What did not work (bytes)
- `p = &D_800C6DD0[i*0x60]` + `p[0x5A]…` (a1), and base/p both derived from `i` (a2): 17 — one register only, the target
  keeps two (the call argument keeps the biv alive only when `base` is itself walked).
- `p = &D_800C6E2E[i*0x60]` + walked `base` (a3): 5 — `p` loads its own `lui D_800C6E2E` and the increments reorder.
- `base = …; p = base + 0x5E` in a `for` whose `base += 0x60` is the body's last statement (b1): 2 (ORDER).

## (f) Where the method fell short
Same as func_80037EA0: no generator deletes a walked pointer or re-derives it from the other biv. related.txt's
func_8003A0E4 (`a2 = D_800C6DD0 + i * 0x60; a2[0x5D] …`) already shows the record-offset spelling.

## (g) Structs question
Yes, the natural spelling: D_800C6DD0 is `struct Chan { …; u32 f14; …; u8 f5A, …, f5D, f5E; …; } [16]` (0x60 bytes;
func_80037EA0, func_8003916C, func_8003A0E4 touch the same fields). `for (…, ch++) if (ch->f5A && ch->f5D) { f(i, &ch->f10);
ch->f14 = 0; ch->f5D = 0; ch->f5E = 0; }` is this closing text with names (the same giv structure: a biv pointer and field
displacements). TESTED on bytes with a body-local struct (scratch/s1.c: `struct Chan { u8 pad00[0x10]; u8 f10[4]; u32 f14;
u8 pad18[0x42]; u8 f5A, f5B, f5C, f5D, f5E, f5F; } *ch = (struct Chan *)D_800C6DD0; for (…; i++, ch++)`): score 0 as well.
So the struct spelling closes it too; body.c keeps the field-offset text because the TU has no such type yet (structs phase).
