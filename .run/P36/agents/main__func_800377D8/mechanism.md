# func_800377D8 (src/800_c.c) — P36 S104 agent e27 — score 42 (lever-free; sweep best 19) -> 0, ZERO levers (was 1 `$2` pin + 3 `__asm__ volatile("")` barriers)

(a) Residual: COUNT 314 vs 316 with three separate defects (diffed on whole normalised listings, `scratch/free.m` vs `target.m`):
1. case 1's counter block: `lhu`/`lw D_80076228` in swapped order and `$v0`/`$v1` swapped (8 rows + the compare);
2. case 1's `D_80076243 = 1` arm (`sb a0; j tail`) is merged into case 3's identical arm (-2 ins; case 1's `& 0x2000` test
   becomes `bnez` to case 3 + `j`);
3. the shared tail: the two zero stores (`sb zero,D_80076298`, `sh zero,D_80076240`) sink below the `D_80076294`/`D_80076244[]`
   loads; the target keeps source order with an unfilled load-delay `nop` after `lw D_80076294`.

(b) Pass and decision (dumps `scratch/dumps_{free,v1,m1,w1,y1,z6}/`; the `.sched` ready-list trace settled 1 and 3):
1. sched1 (`sched.c`): `priority()` is the distance from the block START (max over LOG_LINKS of pred priority + cost - 1,
   `sched.c:1425` priority()), nearly flat here, so `adjust_priority` decides: an insn with no REG_DEAD that BIRTHS a register set
   once (`birthing_insn_p`, `sched.c:2469-2490`, `reg_n_sets[i] == 1` at `:2490`) is lifted to the ready list's max priority
   (`adjust_priority`, `sched.c:2507`, the birthing case `:2539-2544`). `nxt = gD_80076228 + 0x800` made the add a birthing insn (w1 trace: insn 128 at `7f000001`), so in the
   backward pass it was taken before the counter store and the loads swapped; local-alloc then gave `$v0` to the first-born
   (the counter) — this last step inferred, not dumped. Written `nxt = gD_80076228; nxt += 0x800;`, `nxt` is set twice, neither insn births (z6 trace: insn 129 stays
   at priority 2), and the scheduler keeps `lw`, `lhu`, `add`, `add`, `sh`, …, `sw` — the target. (The `sw 228` / `sh 0(a0)` pair
   must also stay in source order: in sched2 the `sh` goes through the hard `$a0`, `canon_rtx` no longer knows its value, and
   `memrefs_conflict_p` returns 1, `sched.c:614-662` — so the gD store stays textually after the counter store.)
2+3. ONE move fixes both: the two zero stores are written inside EACH arm of the `& 0x2000` if/else (both cases).
   - sched1: the stores are now in the arm blocks and the `D_80076244[]` loads in the join block, so nothing can interleave
     them — the target's source-order tail (`z6.i.sched`: 232/235, 248/251, 553/556, 569/572 in the arm blocks).
   - jump2: case 3's `= 1` arm cross-jumps its `sb zero; sh zero` tail onto the `= 2` arm's copy; `do_cross_jump` finds no label
     before those stores and `get_label_before` makes a NEW one (`find_cross_jump` `jump.c:2371`, `do_cross_jump` `:2537`, `get_label_before` `:2589`): `code_label 741`, above the
     `.greg` max uid 730 (`z6.i.jump2` line 1113). Case 1's arms merge into case 3's the same way, and BOTH `= 1` arms end as
     `j 741`. The "try each other jump to this label" loop is guarded by `INSN_UID (JUMP_LABEL (insn)) < max_uid`
     (`jump.c:1985`), so the two `sb a0; j 741` arms are never compared and stay apart — e21's func_800359B0 mechanism.
     With the stores after the join instead, the tail label is an original label and the arms merge (defect 2).
All three proven on bytes (`--try` 0, 316/316) and on dumps (the trace lines, the new label 741, the block membership).

(c) Moves (body.c = scratch/z/z6.c, score 0):
1. case 1: `{ s32 rnxt, rcnt; … }` block deleted; `pCnt = &hD_80076240; nxt = gD_80076228; nxt += 0x800; (*pCnt)++;
   gD_80076228 = nxt; if ((s16)*pCnt != 0xE) return;` (the pin deleted; the unused `cnt` local deleted);
2. cases 1 and 3: `if (… & 0x2000) { gD_80076243 = 1; D_80076298 = 0; hD_80076240 = 0; } else { gD_80076243 = 2;
   D_80076298 = 0; hD_80076240 = 0; }` then the two `D_80076244[]` copies (all three barriers deleted).
Necessity, each proven on bytes: `nxt = gD + 0x800` single-set = 11 (z2); the arm stores in case 1 only = 40, case 3 only = 48
(z3/z4: 334 ins, the tails no longer match); `*pCnt = *pCnt + 1`, `*pCnt += 1`, `(*pCnt)++`, a `cnt` temp — all 0.
Intermediate: a W8 `D_80076243.v = 1` spelling in case 1's arm (a second SYMBOL_REF string, cross-jump compares names by
pointer) also fixed defect 2 alone (v1.c, 19) — not needed in the final text.

(d) GENERATOR PROPOSALS:
- ORDER residual where two independent loads come out swapped and the first-loaded value takes the other's register: find
  the local set ONCE by `x = LOAD + K` (a birthing insn, `sched.c:2539`) and split it `x = LOAD; x += K;` — a local set twice
  never births (`reg_n_sets == 1`, `sched.c:2490`). (func_800377D8 needed it; the d8 width rule is the SUBREG variant.)
- A `"memory"`/volatile barrier between an if/else's join and the stores that follow it (or one fencing a cross-jump of two
  identical arms): move the statements between the join and the barrier INTO each arm — the join block no longer holds
  them (sched1 cannot interleave), and jump2's tail cross-jump creates a NEW label that `jump.c:1985` hides from the
  arm-vs-arm comparison. Try it on every body whose barrier sits right after an `if/else` that assigns one global per arm.

(e) Did NOT work (bytes): the free sweep (R7/R8/R9/R12/R18, 186 compiles) best 19; 48 width/order spellings of the tree's
`rnxt/rcnt` block (all 19 — the output never changed); the in-place case-2 spelling through `pCnt` (m1: 12 — `sw 228` lands
before the `sh`); the 20 topological orders of {p, n, c, S, T} (12 or 19); the tail stores as in-struct `D_80076240[0].unk00`
(h1: 52) or W32 fields (t/: 42-54); the whole tail duplicated per arm (u1/u2: 87 — cse then forwards `D_80076294` into the
arms and the reload vanishes).

(f) Method gap: the residual hunks read as three unrelated sched/regalloc problems; the deciding fact for two of them was a
BASIC-BLOCK boundary (where the stores sit relative to the join), which no generator moves — they all edit within a statement
list. The `.sched` "ready list at T-n" trace plus `adjust_priority`'s `7f000001` marker named the birthing rule in one read;
METHOD should say "grep the `.sched` trace for `7f000001`: that insn births a register — set its local twice to demote it".
Banking note (unchanged, from the TU header): src/800.c carries a conflicting `extern void func_800377D8(u8 arg0);` — the
§376/§378 fix_arity_callers step precedes the gate; the header's lever notes (3a, 3b, 4) are now stale.

(g) Structs: partly. D_80076228…D_80076298 is plainly ONE loader-state struct (0x28 read ptr, 0x38 SPU addr, 0x3C sector,
0x40 s16 count, 0x42 busy, 0x43 state, 0x44 five 16-byte file records {addr, flags, addr2, done, used}, 0x94 index, 0x98
error). None of the three decisions is an aggregate-vs-scalar alias question (birthing, block membership, a label uid), so a
struct would not have removed a lever here; and a struct over one base symbol changes every relocation (D_80076240+0x54
instead of D_80076294), so it would be identical only after LINKING — a structs-phase rewrite of the whole TU, not testable
body-locally without that parked relocation class. The TU's aliases (gD_/hD_/sD_) stand in for it for now.

(h) Whole-object check (e27): body.c spliced into a copy of src/800_c.c and compiled through the recipe (`scratch/joint.py` -> `scratch/joint/joint.o`): `.text` sha1 157af281674f and `.rodata` identical to the baseline snapshot, relocations and symbol table identical (only the source-path string in `.strtab` differs).
