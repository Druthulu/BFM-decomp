# func_801AB54C (md_SC07_004) — P36 S104 agent e8 — score 11 (lever-free) -> 0 with ZERO levers (was 1 `$0` pin + a dead `frame_pad[4]` keepalive)

(a) Residual: 32 vs 34 ins, twice the same shape: the target loads the s16 field (`lh v0`), COPIES it (`move v1,v0`), tests
the original (`slti v0,v0,K` — the test result overwrites it) and adds from the copy (`addiu v0,v1,ADD` in the beqz slot).
Lever-free, `c = v + 0` is folded, so there is no copy and the test/sum both read one register.

(b) Pass and decision (dumps `scratch/dumps_good/`, `scratch/dumps_H/`):
- A source copy `c = v` never survives: cse makes the two one class (`make_regs_eqv`, `cse.c:846-862`) and deletes it.
  Hiding it from cse as `c = (s16)v` (sweep `H_*`, score 2) survives cse, becomes a reg-reg copy in combine (sign-bit
  copies, `combine.c:7926-7942`), and then local-alloc's `optimize_reg_copy_1` (`local-alloc.c:700`, call site
  `:1004-1007`) rewrites the slt to read the COPY (`.greg` insn 45 reads v1) — exactly cookbook §162j1's mechanism.
- The close: the natural compound `if (F < K) F += ADD;` on the s16 field. Expand gives the field ONE HImode load
  (`reg:HI 77`), the test reads its sign extension (reg 78, shifts), the `+=` reads `(subreg:SI (reg:HI 77))`. combine
  folds the load into the extension (`78 = lh`, `extendhisi2_internal`) and rewrites 77's set as
  `(set (reg:HI 77) (subreg:HI (reg:SI 78) 0))` (good_combine.txt insn 37). Its SET_SRC is a SUBREG, so
  `optimize_reg_copy_1` is never called (`local-alloc.c:1004-1006` requires `GET_CODE (SET_SRC (set)) == REG`) and the slt
  keeps reading 78 (dies there, v0) while the add reads 77 (v1); movhi prints the subreg copy as `move`. Proven on bytes.
- Frame: the tree's `s32 frame_pad[4]; (void)&frame_pad;` faked 16 bytes of frame. In the close, combine leaves the two
  dead shift temps as `(use (reg:SI 79))` / `(use (reg:SI 88))` (good_lreg.txt insns 83/84); they get no hard register
  (`.greg` dispositions omit 79/88, "ST_REGS or none") and reload gives each a stack slot (`.greg` shows the uses rewritten
  to `(mem (plus sp ...))`). That is where the target's frame of 40 comes from — no pad needed (d10's "count the dead
  pseudos against the frame", proven: frame 40 with no pad).

(c) Moves (proven, score 0 — body.c):
1. `if (*(s16 *)(P + 0x18) < 0x600) { *(s16 *)(P + 0x18) += 0x100; }` for the load/copy/test/store sequence (both groups);
2. `v`, `c`, the `$0` pin, `frame_pad` and its `(void)&` keepalive deleted;
3. `p` either inlined (body.c — no locals at all) or one local per group (`body_twop.c`, also 0). A single `p` reused by
   both groups scores 10 (register swap: the reused pseudo "dies in 2 places" and goes global, `p` lands in `$v1`).
   `+= ADD` and `= F + ADD`, `s16`/`u16` store all score 0 (48-body sweep, `scratch/sweep_L.py`: 24 zeros).

(d) GENERATOR PROPOSAL: when a `$0` pin makes a copy `c = v + zr` of a value just loaded from a 16-bit field, with the test
reading `v` and a store back to the SAME field reading `c`, rewrite the group as `if (FIELD < K) FIELD += ADD;` (test the
memory, compound-assign it) and delete the temps — the HImode subreg copy combine makes is invisible to
`optimize_reg_copy_1`; also delete any dead `pad[N]` + keepalive first and let the dump decide the frame.

(e) Did NOT work: widths alone on `v`/`c` (78-body sweep, best 6/7: a same-mode copy is folded by cse; an s16 `c` makes
cse substitute the subreg or re-load with `lhu`); `c = (s16)v` = 2 (optimize_reg_copy_1 re-routes the test to the copy);
the pad was never needed (keep/no-keep identical in every width variant).

(f) Method gap: the brief's `$0`-pin advice (delete the temp / width) was the wrong family here — the answer was cookbook
§164's "test the memory and re-read it inside the arm" (a re-read cse commons into a copy), not in the METHOD list. The
tree's temps (`v`, `c`) were decompiler artefacts of a compound assignment; no generator rewrites `v = F; if (v<K) F = v+A`
back to `if (F<K) F += A`. Also: two `--try` COMPILE-ERRORs (`At top level:`) on text that scored 0 on the next three runs.

(g) Structs: NO for the lever — the decision is combine's HImode subreg copy vs `optimize_reg_copy_1`, not a memory
ordering question. Typing `a0` as a struct (0x1C s32 counter, 0x20 pointer to a sub-object whose 0x18/0x1A are s16 scales)
would read better: `if (a0->sub->sx < 0x600) a0->sub->sx += 0x100;` — plausibly byte-identical (a COMPONENT_REF gives the
same HImode MEM), not tested on bytes.

(h) Joint check (e8): all four e8 body.c files spliced into one copy of the tree TU (`md_SC07_004__func_801AB78C/scratch/splice4.py` -> `scratch/tu_all4.c`): each of the four scores 0, and the whole object is sha1-identical to the baseline per section (.text ad583f4dfb0c, .rodata, .data/.sdata/.bss) with .rel.text identical.
