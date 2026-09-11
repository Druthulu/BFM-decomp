# func_801A5094 (md_SC07_004) — P36 S104 agent e8 — score 4 (lever-free) -> 0 in plain C ONLY with a SYMBOL change; minimum-lever body at 0 with the tree's 1 barrier (1 -> 1)

(a) Residual: same 64 instructions; the word load `lui v1; lw v1,D_801F8744` is scheduled ABOVE `li v0,1; sb v0,D_801F8747`
where the target keeps it BELOW the byte store (right before `li v0,6`). Count equal — a pure ORDER residual.

(b) Pass and decision (read in the dumps, `scratch/dumps_free/free.i.sched` and `.sched2`):
- sched1 keeps the source order (sb 134, lw 139, li 144, sh 146, sw 141). The reorder is **sched2** (post-reload), block 1:
  T-1 sw, T-2 sh, T-3 the lw is blocked by the memory unit (`schedule_select`, `sched.c:2640-2650`) so `li v0,6` goes; at T-4
  the ready list is {sb 134, lw 139}, both priority 2 (every insn after the call anti-depends on it); rank_for_schedule puts
  the lw first (class 3 vs 2, `sched.c:2398-2422`) but `schedule_select` takes the insn with the greater
  `potential_hazard` (`sched.c:1318-1350`, `:2655-2670`) — the STORE — and the lw, blocked again at T-5, floats to the top.
- It can only do that because the two MEMs are INDEPENDENT: `true_dependence` (`sched.c:817-839`) ->
  `memrefs_conflict_p` (`sched.c:614`): both addresses are bare `symbol_ref`s (the `$at` form is the assembler's macro), so
  they reach `CONSTANT_P (x)` (`sched.c:753-778`) and conflict only if `rtx_equal_for_memref_p` — same symbol. "D_801F8747" and
  "D_801F8744" are different SYMBOL_REFs -> 0 -> no dependence. With a true dependence lw->sb, the sb is not ready at T-4
  and the target order falls out.
- The two symbols are ONE object: `undefined_syms_auto.txt:67` `D_801F8747 = 0x801F8747` = D_801F8744 + 3, and the word the
  body reads at 0x801F8744 CONTAINS that byte. `func_801A6FD4` (tu line 4773-4774) shows the same object: `D_801F8747[0] = 1;`
  then passes `D_801F8747 - 3` (= &D_801F8744) to `func_8017D7D4`. It is a 4-byte {r,g,b,cd}-shaped record (PsyQ CVECTOR shape)
  whose 4th byte the symbolizer gave its own name.

(c) Moves (all proven on bytes):
1. `D_801F8744[3] = 1;` for `D_801F8747[0] = 1;` (body_symbol.c): the ORDER closes — `memrefs_conflict_p` recurses
   `(const (plus sym744 3))` vs `sym744` with c = -3, size 4 -> conflict. Score 2: the only remaining diff is the
   relocation, `sb v0,3(at)` R_MIPS_LO16 D_801F8744 vs the baseline's `sb v0,0(at)` D_801F8747 — the LINKED bytes are
   identical (0x801F8744 + 3 = 0x801F8747), the object's .text word and reloc symbol are not.
2. Same with a body-local struct alias `extern struct { u8 r, g, b, cd; } cv __asm__("D_801F8744"); cv.cd = 1;
   ... = *(s32 *)&cv;` (scratch/b.c): score 2, identical residual (the reloc only) — the struct spelling works.
3. Keeping D_801F8747 on the store and reading `*(s32 *)(D_801F8747 - 3)` (scratch/c.c): order closes, score 2 with the
   reloc mismatch moved to the lw (`lw v1,-3(v1)` vs `0(v1)` D_801F8744). No spelling keeps BOTH baseline reloc symbols AND a
   dependence: the two symbol names are exactly what makes sched call the accesses independent.
DELIVERED: `body.c` = the minimum-lever body, score 0 under `--try --body`: the tree's one `__asm__ __volatile__("")` barrier,
re-marked with the pass (count 1 -> 1). `body_symbol.c` = the zero-lever plain-C close (`D_801F8744[3] = 1;`), linked-binary
identical but NOT object-identical — it needs the symbol decision (retire D_801F8747 in favour of D_801F8744+3 / a struct
field, in both functions 3516 and 4773-4774, which re-symbolizes the baseline object's relocs). PARKED for the structs phase.

(d) GENERATOR PROPOSAL: when a barrier sits between a store to symbol A and a load from symbol B and `addr(A)` lies inside
`[addr(B), addr(B)+sizeof(load))` (read from undefined_syms_auto.txt / the map), rewrite the store as `B[addr(A)-addr(B)]`
(or a field of a struct at B) and score with a RELOC-NORMALISED comparison (symbol value + addend), since the plain object
compare will always report the reloc name.

(e) Did NOT work / cannot work: the free sweep's 183 compiles (R6/R7/R8/R9/R12) all stay at 4 — none creates a memory
dependence. Priorities cannot separate the pair (all post-call insns get priority 2 through the call's anti-dependence,
`sched.c:1488`), and the store always wins `potential_hazard` over the load on the one "memory" unit (mips.md:153-161), so
with independent MEMs sched2 always hoists the lw. MEM_IN_STRUCT flags are irrelevant here: `memrefs_conflict_p` returns 0
before the in-struct clauses of `true_dependence` are consulted.

(f) Method gap: the residual reads as a scheduling tie; the cause is a SYMBOLIZATION split (two names for one object), visible
only by checking the two symbols' ADDRESSES (`build/<tu>/undefined_syms_auto.txt`, the .map). A pre-check "are the barrier's
two neighbouring MEMs within sizeof of each other in address space?" would have named it at once. Also: the scorer compares
reloc symbol names, so a linked-identical close reads as score 2 — the method has no reloc-normalised verdict.

(g) Structs: YES — this is the textbook case. Type D_801F8744 as a 4-byte struct `{ u8 r, g, b, cd; }` (CVECTOR shape; the
word read at +0 copies it, the byte at +3 is the flag `cd`), write `D_801F8744.cd = 1;` here and in func_801A6FD4 (whose
`D_801F8747 - 3` becomes `&D_801F8744`), and drop D_801F8747. The channel is not `expr.c:4568` in-struct marking but alias
analysis on the SYMBOL: one object = one SYMBOL_REF = `memrefs_conflict_p` sees the overlap. Proven on bytes with a
body-local struct alias (score 2 = reloc name only).

(h) Joint check (e8): all four e8 body.c files spliced into one copy of the tree TU (`md_SC07_004__func_801AB78C/scratch/splice4.py` -> `scratch/tu_all4.c`): each of the four scores 0, and the whole object is sha1-identical to the baseline per section (.text ad583f4dfb0c, .rodata, .data/.sdata/.bss) with .rel.text identical.
