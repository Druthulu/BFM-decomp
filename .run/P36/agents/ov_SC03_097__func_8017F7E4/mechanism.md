# func_8017F7E4 (ov_SC03_097) — score 0, ZERO levers (agent e37, P36 S104)

(a) Residual (free body, 19, COUNT 103 vs 108): (1) the target keeps `&D_80126B58` in `a1` from the PROLOGUE and reads
    `lh a0,6(a1)` in case 3's second half, mine folds it to an absolute `lui/lh D_80126B58+6`; (2) the target RE-LOADS the
    state (`lh v0,0x70(s0); sll; lh v0,D_8019AE46(v0)`) for the table index there, mine folds `D_8019AE46[3]` to an absolute
    load (cse knows the state == 3 on that path). The tree's levers: a `launder` on `p` and a `"memory"` barrier.

(b) Pass + decision. Both levers fake ONE fact: that cse1 does NOT reach case 3's second block with the path's
    equivalences. cse follows a conditional jump only into a label with exactly ONE use preceded by a BARRIER
    (`cse.c:8102-8118`), or SKIPS a branch-around block when no label lies between the jump and its target
    (`cse.c:8149-8170`). In the tree's goto spelling, `if (A) { if (B) goto SUCCESS; }` then the block is
    `beqz A -> L1; …; bnez B -> SUCCESS; L1:` — L1 has one use and nothing between, so cse skips into it with `p` ==
    `&D_80126B58` and `mem(0x70)` == 3 in its table (`record_jump_equiv`), folds `p[3]` (`find_best_addr`, `cse.c:2622`)
    and `D_8019AE46[3]`. Also `p` then has exactly 2 refs and `update_equiv_regs` (`local-alloc.c:1076-1116`) replaces
    its single use with the constant and deletes the init — that is why the prologue `lui a1/addiu a1` vanishes.

(c) The move — the STRUCTURED spelling (S104 d17: a `switch`), which is what the decision tree in the bytes IS
    (`beq 2 / slti 3; bnez / beq 3 / bltz -> default` = `emit_case_nodes` for cases 0,1 | 2 | 3):
        switch (state) { case 0: case 1: if (pz < z && z + T44[state] < pz) flag = 1; break;
                         case 2: if (pz > z && pz < z + K48) flag = 1; break;
                         case 3: if (py > y && py < y + K4A) flag = 1;
                                 else if (p[3] < x && x + T46[state] < p[3]) flag = 1; break; }
    `if (A && B) flag = 1; else if (C && D) flag = 1;` expands to `beqz A -> L1; beqz B -> L1; flag = 1; j END; L1: …`:
    L1 now has TWO uses at cse1 time, so cse neither follows nor skips into it — the block starts with an empty table,
    `p[3]` stays `(mem (plus p 6))` (`p` keeps 3 refs: set + two reads, so `update_equiv_regs` leaves it, and it lives
    from the prologue in `a1`), and `state` is re-read from memory. The post-reload cross-jump (`jump.c:2371`) then merges
    the three `slt; beqz -> TAIL; li a2,1` tails into the one CHECK/SUCCESS the bytes show, turning case 3's
    `j SUCCESS` into `bnez B -> SUCCESS` — after cse has already run. `D_80126B66`/`D_80126B62` are read BY NAME (via
    `p[7]`/`p[5]` they compile to the same instructions but relocate against `D_80126B58+14/+10`: score 6, identical
    only after linking — the parked class; the by-name spelling is byte-identical in the object).

(d) GENERATOR PROPOSAL: when a `launder` on a constant pointer and/or a `"memory"` barrier sit in a goto-chain body
    whose dispatch is `== k / < k / == k / < 0`, rewrite it as a `switch` with per-case `if (A && B) flag = 1;` /
    `else if` — the second-use label gains a use and cse1 stops folding; more generally, a "value cse should not know"
    residual is a LABEL-USE-COUNT question (`cse.c:8106`), not a memory question.

(e) Did NOT work (bytes): all reads through `p` (vA 25, vB 6 — relocation addends only).

(f) Method: METHOD step 14 ("if your body has goto/labels, try the structured spelling EARLY") was the whole answer; the
    cse dumps (`;; Processing block from 2 to 273`) confirmed the tree and the free body follow the same paths.

(g) Structs: yes, and it is the natural spelling. `p` is the player position block (`s16 x,y,z` at +6/+0xA/+0xE of
    D_80126B58) and `a0` the actor (`s16 x/y/z` at 6/0xA/0xE, `s16 state` at 0x70, `s16 +0xFE`). With `Player *p` the
    `p->x` read is the same `(mem (plus p 6))`; it changes nothing in cse's decision (which is about label uses), so the
    struct is a readability gain with zero byte risk here.

Copies (same structure, symbols mapped by position — all score 0; scratch/copies/LIST.tsv):
  func_8017EE6C  src/ov_SC03_096/ov_SC03_096_jr_8017BEBC.c
  func_8017D960  src/ov_SC03_095/ov_SC03_095_jr_8017BEBC.c
  func_8017F398  src/ov_SC03_093/ov_SC03_093_jr_8017D898.c
