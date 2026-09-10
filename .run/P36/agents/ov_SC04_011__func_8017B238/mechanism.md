# ov_SC04_011 / func_8017B238 — MATCH (score 0), levers removed

`.venv/bin/python tools/delever_search.py --try src/ov_SC04_011/ov_SC04_011_jr_8017AE2C.c func_8017B238 PACK/body.c --body`
→ `score 0 (OTHER; mine 76 ins, target 76) — MATCH`

Levers removed: the `register u8 *src __asm__("$16")` pin (line 2775) and the `__asm__` launder (line 2776),
both marked NEEDED. No pin, no asm, no added `volatile`, no `__builtin_*`.

---

## (a) The residual in one sentence

`body_free.c` scored 7 (COUNT/ORDER): the parameter's copy `move s0,a1` had been hoisted **above** the compare
(`sltiu v0,s0,11` instead of `sltiu v0,a1,11`, `sll s0,s0,0x4` instead of `sll s0,a1,0x4`, and the branch's delay
slot took `sw ra` instead of `sw s0`) — i.e. `param_2` and the if-arm's `src` had been **coalesced into one
$s0-lived pseudo** instead of `param_2` staying in `$a1` with a separate `$s0` born inside the arm.

## (b) The passes and the decisions read (all `tools/reference/gcc-2.7.2/`)

Three decisions chain, and all three had to be turned at once.

1. **cse deletes the arm's copy** — `make_regs_eqv` `cse.c:826`, head rule `cse.c:840-857`.
   `body_free.c`'s RTL really does contain the copy: `.jump` dump has `(insn 19 (set (reg/v:SI 75) (reg/v:SI 73)))`,
   and `.cse` has it gone with the two `movstrsi` insns reading `(reg/v:SI 73)` directly. `insert_regs`
   (`cse.c:1017-1032`) joins the two SImode regs and `make_regs_eqv` keeps the *parameter* as `qty_first_reg`,
   because the copy's destination only becomes the canonical head when
   `uid_cuid[regno_last_uid[new]] > cse_basic_block_end || uid_cuid[regno_first_uid[new]] < cse_basic_block_start`
   (`:853-855`) **and** `uid_cuid[regno_last_uid[new]] > uid_cuid[regno_last_uid[firstr]]` (`:856-857`).
   A local `src` whose life is confined to the arm fails both, so `canon_reg` rewrites its uses back to `param_2`
   and the copy dies — which keeps `param_2` live across the two `movstrsi` insns, whose four
   `(clobber (scratch:SI))` become `$v0/$v1/$a0/$a1`, so `param_2` **conflicts with `$a1`** and can never keep it.

2. **The pointer's register comes from a hard-reg PREFERENCE, not from its own live range** —
   `set_preference` `global.c:1535`, called for every SET at `global.c:1348`, preference applied over the pass-0
   pick at `global.c:1000-1071` (and pass 0 itself at `global.c:951-956`: `IOR_COMPL(used, regs_used_so_far)`).
   MIPS defines no `REG_ALLOC_ORDER`, so a *block-local* qty always takes the lowest free regno (`$v0`) and a
   *global* allocno crossing no call would take the lowest already-used non-conflicting one (`$a2`).
   The one thing that reaches `$s0` is the preference: `set_preference` strips one level of RTX
   (`if (GET_RTX_FORMAT (GET_CODE (src))[0] == 'e') src = XEXP (src, 0), copy = 0;`), so an **arithmetic** set
   counts too, and the branch at `global.c:1601-1618` gives a global dest a preference for whatever hard reg the
   *source operand* already got from local-alloc.

3. **The else arm's `$s0` and the else arm's schedule need single-set locals** —
   `combine_regs` `local-alloc.c:1765-1788` (`(sreg >= FIRST_PSEUDO_REGISTER && reg_qty[sreg] == -1)` → refuse:
   a **global** destination cannot be tied to a dying local source) and `birthing_insn_p` `sched.c:2469-2501`
   (`return (reg_n_sets[i] == 1);`) with `adjust_priority` `sched.c:2506-2549` (a birthing insn is raised to
   `max_priority`; gcc 2.7.2 schedules a block backwards, so the boost pushes it to the **bottom** of the block —
   which is how `addu s0,s0,v0` reaches the `jal`'s delay slot). `idx*16` and `a2addr` therefore have to stay
   single-set block-locals: `a2addr` crosses a call → `used = call_used_reg_set` (`global.c:927` /
   `local-alloc.c:2102`) → `$s0`, and `combine_regs` ties `idx*16` to it (`sll s0,a1,0x4` … `addu s0,s0,v0`).

## (c) The move(s) that closed it

**One move, one variable.** Give the if-arm's pointer and the else arm's *first* table address the **same local
`u8 *src`**, declared at function scope:

- if-arm: `src = (u8 *)((u32)param_2);` (was the pinned + laundered `register` in `body_tree.c`)
- else-arm: `src = &D_80193D6C[((u32)param_2) * 0x10];` replaces the old `s32 a1addr` local; the second address
  stays a separate single-set local `s32 a2addr`, and the two calls pass `(s32)src` and `a2addr`.

That single edit turns all three decisions at once:
- `src` is now mentioned in the else arm, so at the copy its `regno_last_uid` is **later** than `param_2`'s and
  **beyond** the cse block's end → it becomes `qty_first_reg` → the copy `move s0,a1` survives → `param_2` dies at
  it, loses the `movstrsi` clobber conflicts, and keeps its copy-preference `$a1` (`.greg`: `73 in 5`, so the
  `(set (reg 73) (reg 5 a1))` prologue copy folds away and the compare reads `a1`).
- `src` is now a **global** allocno, and the else-arm set `(set (reg 74) (plus (reg 82) (reg 83)))` has its source
  operand `reg 82` already renumbered to `$16` by local-alloc, so `set_preference` records
  `;; 74 preferences: 16` (verbatim from the `.greg` dump) → `find_reg` overrides its pass-0 pick with `$s0`.
- `src` is only ever *read* in the else arm (it is the first call's argument), so it crosses **no** call there and
  never collides with `a2addr`'s `$s0`; `idx*16`/`a2addr` stay single-set locals, keeping both `combine_regs`
  (shared `$s0`) and the `birthing_insn_p` boost (the delay-slot `addu s0,s0,v0`) intact.

Final `.greg`: `72 in 17  73 in 5  74 in 16  75 in 2  80 in 16  82 in 16`, `74 conflicts: 74 2 3 4 5 29`,
`74 preferences: 16`.

## (d) GENERATOR PROPOSAL

**One sentence:** when the residual is "an incoming-parameter register is copied into a callee-saved register
*before* the branch, and the target instead compares/uses the raw `$a`-register and does the `move` inside one
arm" (register pair `sN->aM`, count-equal, the delta being a hoisted `move`), rewrite the arm's pointer/index
temp as a **function-scope variable that is also assigned in the other arm to a value derived from an operand
that already lives in a callee-saved register** — i.e. merge the arm-local temp with the *first* single-use
address temp of the sibling arm.

Mechanically checkable pre-conditions (all readable without a compile):
1. the diff's only register pair is `sN -> aM` where `aM` is an argument register, and the extra/moved insn is a
   `move sN,aM`;
2. the function has an `if/else` whose two arms each open with an address/index temp derived from the same
   parameter;
3. the arm-local temp is a **plain copy** of that parameter (so cse folds it).
Rewrite: hoist the arm-local temp's declaration to function scope and replace the *first* (non-call-crossing,
single-use) address temp of the other arm with it, leaving every other temp of that arm untouched.
Guard: never give the shared variable the arm's **call-crossing** temp — that makes it a global destination,
`combine_regs` (`local-alloc.c:1773`) then refuses to tie the scaled index to it and `birthing_insn_p`
(`sched.c:2490`, `reg_n_sets == 1`) loses the boost, which is exactly the score-12 / score-6 near misses below.

## (e) What did NOT work, with byte evidence

| variant | shape | score |
|---|---|---|
| `body_free.c` | arm-local `src` copy | **7** (cse folds the copy; `sll s0,s0,0x4`) |
| a | pointer inlined at both uses, no `src` at all | **7** (identical residual — `src` was never the driver) |
| d | `src` declared+assigned **before** the `if` | **7** (still one cse block; copy still folded) |
| b/c | separate `idx` used only in the else arm | **17** (77 ins: mirror image — `move a2,a1` + `move s0,a2`) |
| e | `src` at function scope + dead `src = 0;` after the join | **17**, 76 ins — **prologue and `move …,a1` position exactly right**; flow deletes the dead store so `src` stays block-local and local-alloc gives it `$v0` (`.lreg`: `Register 74 … in block 1`, `74 in 2`) |
| g | shared `src` = the else arm's **a2addr** (call-crossing) | **12**, 76 ins — if-arm perfect, else arm broken: `src` is global so `combine_regs` refuses the tie and `sll v1,a1,0x4` splits off (`.greg`: `82 in 3`) |
| g5/g6 | shared `src` = the else arm's scaled index only | **26**, **77 ins**, three saved regs (`s0/s1/s2`) — `src` and `a2addr` conflict |
| h1/h2/h4/h5/h6 | `src` holds the index then is re-assigned the a2 address | **6**, 76 ins, **all registers correct** — only the else arm's order differs; `reg_n_sets[src] == 3` kills the `birthing_insn_p` boost (`sched.c:2490`) so `addu s0,s0,v0` leaves the delay slot. Four different spellings all scored 6, which is what identified the cause as the *number of sets*, not the syntax. |
| h3 | same, index assigned inside the call argument | **26** (77 ins) |
| **j1 = `body.c`** | shared `src` = the else arm's **a1addr** (read-only there) | **0 — MATCH** |

## (f) Where the method fell short

- **The pack's scratch collides between agents.** `PROMPT.md` says "never write outside PACK", but the obvious
  scratch dir (`$SCRATCHPAD` from the harness environment) turned out to be **shared with the other ~20 agents**:
  a `t.sh` I had written was overwritten by another agent's copy pointing at `ov_SC04_011_jr_8012ACE0.c:func_801345F8`,
  and I scored two candidates against the wrong function before noticing. Everything then moved to
  `PACK/scratch/`. The brief should say *use PACK for scratch too*, and `--try` should echo the TU/fn it was asked
  for next to the score line (it does — that is the only reason I caught it).
- **`--try` prints only the opcode diff, never the two full listings.** The residual as printed
  (`insert mine[3:3]` / `delete mine[5:8]`) hid the fact that the two sides are the same instruction *multiset*.
  I had to write a 12-line script against `masked_diff.insns_from_object` + the recipe's baseline `.o` to print
  `mine | target` side by side for the whole function; that listing is what made the diagnosis possible in one
  read. A `--try … --full` (or `--context N`) flag would pay for itself immediately.
- **`residual_moves.md` covers this class but points at the wrong knob.** §1b rank 5 ("make or break a call
  crossing") and rank 6 ("scope a temp per block / per arm") are the right neighbourhood, but the actual lever
  here was **hard-reg preference propagated through an arithmetic set from an already-local-allocated operand**
  (`global.c:1535` + `:1601`), which no row names. Worth a new row: *"to move a global allocno into a callee-saved
  register without giving it a call crossing, make it the destination of a set whose first operand is a
  block-local pseudo that local-alloc has already put there."*
- The `.lreg` line `Register N used … in block B` versus its absence is the single most useful fact in the whole
  investigation (local qty vs global allocno) and it is not mentioned in the brief; `tools/alloc_table.py` would
  have shown it faster if I had reached for it first instead of reading `cse.c`.
- Cost: ~24 scored candidates at ~0.7 s each. The four score-6 spellings (h1/h2/h4/h5/h6) were the expensive part
  — they all shared the one defect (`reg_n_sets != 1`) and a tool that reported `reg_n_sets` per candidate
  variable would have collapsed them into one.
