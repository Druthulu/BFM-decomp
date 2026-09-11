# func_80037144 (src/800_c.c) — P36 S104 agent e3

**Result.** No levers: `body.c` is byte-identical ONCE LINKED; `--try` scores it **2**, and both points are relocation
naming (`sw v0,4(at)` against `D_80076240` where the baseline has `sw v0,0(at)` against `D_80076244`, and
0x80076240+4 == 0x80076244 per build/us/SLUS_007.26.map). The scheduling is otherwise exact. main banks on the linked
SHA1 (`tools/gate_main.py:220`), and func_80037028, the sibling in the same TU, is already banked with exactly this
`D_80076240+4` relocation form. Fallback: `body_minlever.c` scores **0** at object level with 1 marked lever (the tree's
barrier, re-marked). Levers: 1 -> 0 (body.c), or 1 -> 1 (body_minlever.c).
Best object-level plain-C text: `scratch/best_plainC_objlevel_t1.c`, score 2 (one `li a2,1` out of place, see (e)).

## (a) The residual
Count 123 vs 124 with a permuted head block. Without the barrier, the store `D_80076244[i].unk00 = (s32)D_800BA320`
sinks below the `D_80065438`/`D_800652F0` table loads (sched1). The table value then lands in `v1` rather than `v0`, and the store fills
the load-delay slot the target leaves as a `nop`. That `nop` is the one-instruction count difference, not a missing
operation.

## (b) The pass decision (proven on dumps and bytes)
sched1's dependence builder, `true_dependence` (sched.c:817), calls `memrefs_conflict_p`. Both addresses are
`(plus reg X)`. For the unk00 store X = `(symbol_ref D_80076244)`, which is offset 0. For the load X =
`(symbol_ref D_80065438)`. Neither the registers nor the X terms are equal, so the call reaches `find_symbolic_term`
(sched.c:700). That finds two different symbols and reports "no conflict", so the load does not depend on the store.
Every OTHER slot store has a NON-ZERO offset, `(const (plus sym K))`. `find_symbolic_term` returns 0 on a CONST
(`GET_RTX_CLASS == 'o'`, sched.c:571) and that means "conflict" (sched.c:700-702). So only the offset-0 store is free to
float, and it floats down into the load-latency hole: the `.sched` trace shows it chosen alone at T-6 while the load
stalls. func_80037028's header (src/800_c.c:1649-1661, note 2) records the same law for the same table.
**Proof on dumps:** with the D_80076240 view, the lhu `insn 126` gains `LOG_LINKS insn_list 72` (the unk00 store) in
`scratch/s1.sched`. Without it, it does not.

## (c) The move
`D_80076244[i].unk00 = (s32)D_800BA320;` -> `D_80076240[i].unk04 = (s32)D_800BA320;`. This is the same word, written
through the TU's other declared view of the table (`extern Slot16A D_80076240[]`, 0x80076240, unk04 at +4). The address
becomes `(const (plus D_80076240 4))`, the store conflicts with the loads, and sched1/sched2 reproduce the target order,
including `li a2,1`. Writing all three word fields through D_80076240, the sibling's own convention (scratch/v/s2.c),
gives a byte-identical schedule too, with 5 relocation-only differences (--try 10).

## (d) GENERATOR PROPOSAL
When a zero-offset store `A[i].f0 = …` into a symbol+scaled-index array drifts past later varying loads of OTHER
symbols (ORDER residual, count ±1), and the TU declares an overlapping view `B` of the same memory at a lower address,
rewrite the store through `B[i].<field at +(A-B)>`. Score it on the linked image (reloc-only diff), not on the object.

## (e) What did not work (bytes, --try at object level)
- All 120 orders of the five slot stores (scratch/v/perm_*): 16-19. Order cannot create a memory dependence.
- A marked `do { } while (0)` around every contiguous range of the head statements (55 + 78 files): best 2
  (free_127 from the sweep: `sll a0,a0,1` misplaced).
- **Register anchoring (t1, the best object-level plain C, 2).** Reuse `v` for `&D_800BA320` and for
  `idx | 0x2000` (`v = (s32)D_800BA320; …unk00 = v; … v = idx | 0x2000; …unk04 = v;`). The second set of `v` is an
  anti-dependence that holds the unk00 store above the `ori`. That fixes the whole head block except `li a2,1` (`one`),
  which lands after the `ori` instead of before the store. The cause: `one = 1` is a birthing insn
  (`birthing_insn_p`, sched.c:2465-2488, via `adjust_priority` :2539). sched1 therefore places it directly before its
  only in-block use (the `unk0D` store). sched2's LUID tie-break (`rank_for_schedule`, sched.c:2428) then keeps it
  after the `ori`. I tried `one` as u8/s8/u16/s16, as a literal `1`, and in all 360 orders of the units: all 2 or worse.
  Not a close.
- An unused `v` reuse for `D_800BA320` in the tail too (r2): 40.

## (f) Where the method fell short
neighbours.txt and related.txt were EMPTY, but the answer was spelled out in English in the header of the function 90
lines above (func_80037028, src/800_c.c:1639-1674). related.txt should include same-TU functions that share a GLOBAL,
not only a callee. The scorer compares relocation symbols, so a linked-identical close through an overlapping base is
reported as not matching. A linked-image mode for `--try` (resolve symbol+addend before diffing) would have scored this
body 0.

## (g) Structs question — YES, this is the struct case
The memory at 0x80076228..0x800762A0 is ONE object in the original. This function touches D_80076228, D_8007622C,
D_80076238, D_80076240, D_80076242, D_80076243, the 5x16 slots at D_80076244, D_80076294 and D_8007629C. A single struct
(e.g. `struct { s32 f00; s32 f04[3]; s32 f10; …; u16 f18; u8 f1A, f1B; Slot16 slot[5]; s32 f6C; …; s32 f74; }` at
D_80076228) makes EVERY field access `(const (plus D_80076228 K))` with K != 0, apart from f00. By sched.c:571/700
every slot store then conflicts with every varying table load. That is exactly the dependence the barrier fakes, and the
one func_80037028 fakes with its second base. It also plausibly removes the W8/W32 one-field-struct wrappers
(src/800_c.c:1740-1752) whose only job is to set MEM_IN_STRUCT_P. Tested on bytes only through the D_80076240 view
(body.c, linked-identical). The full struct changes every relocation in the TU's six users of this memory, so it belongs
to the structs phase.
