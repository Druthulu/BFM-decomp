# func_80156044 (ov_SC04_011) — score 0, MATCH, lever-free

Pack: `.run/P36/agents/ov_SC04_011__func_80156044`
Body: `PACK/body.c` — verified `score 0 … MATCH` by
`.venv/bin/python tools/delever_search.py --try src/ov_SC04_011/ov_SC04_011_jr_80154C24.c func_80156044 PACK/body.c --body`.
Levers removed: both `register … __asm__` pins (`$2` on `puVar2` @1027, `$3` on `iVar3` @1028). No asm, no added
`volatile`, no `__builtin_*`, no `register`.

## (a) The residual, in one sentence

The lever-free draft computed the row address as two cross-block variables — a base `puVar2` and an offset `iVar3`
added at the merge point — and got the two caller-saved colours the wrong way round in every arm
(`andi v1 / sll v0 / addu v0 / la a1` instead of the target's `andi v0 / sll v1 / addu v1 / la v0`), plus, with the
`s32 puVar2` spelling, two extra `addu`s that `reorg` stole into the two `j` delay slots (score 18, COUNT).

## (b) The passes and the decisions I read (byte-proven where marked)

Two independent decisions, both keyed on the base pointer being a **cross-block** value:

1. **`local_alloc` / `block_alloc` — the 2-quantity vs 3-quantity fork.** PROVEN on bytes and in `.lreg`.
   `local-alloc.c:472` only makes a quantity for a pseudo local to one block with one death, and
   `local-alloc.c:517` resets `next_qty` per block. With `puVar2` a cross-block variable, each arm holds exactly
   **two** quantities — the masked index `t` (3 refs, life 3) and the tied `sll/addu` chain (4 refs, life 3) —
   priority `floor_log2(refs)*refs*size/(death-birth)` (`qty_compare`, `local-alloc.c:1578-1596`) makes the chain
   26666 vs the index's 10000. `next_qty == 2` takes the unrolled `case 2` at `local-alloc.c:1499-1502`: ONE
   comparison, one exchange, chain allocated first, chain = `$2`, index = `$3` — the residual.
   With the base scoped **into the arm** it becomes a third local quantity, `next_qty == 3`, and the unrolled
   `case 3` at `local-alloc.c:1491-1496` **falls through into `case 2`**, so `qty_compare(0,1)` is applied a
   second time and undoes its own exchange. Order becomes base, chain, index → base `$2`, chain `$3`, index `$2`
   (reusing the dead index's colour) — the target exactly.
   Checked in the `.lreg` dump of the winning body: block 1 holds `78` (index), `80/81/82` (one chain qty) and
   `83` (base); dispositions `78 in 2, 80/81/82 in 3, 83 in 2`.
   Negative control: a plain `{ … }` block around the same statement changes nothing (score stays 18) — it is the
   quantity count, not the C scope.

2. **`global_alloc` — the `$a1` preference the base inherited from `puVar4`.** PROVEN in the `.greg` dump.
   While the base is a global allocno it is coloured by `global.c`. `puVar4` is copied into `a1` for
   `func_80156848`/`func_80156A88`, so `set_preference` (`global.c:1535+`) gives it a copy preference for `$5`;
   `expand_preferences` (`global.c:781-825`) then merges that preference into every non-conflicting allocno that
   dies at `puVar4`'s defining `addu` — i.e. into the base. `find_reg` picks `$2` first-fit in pass 0 and is then
   **overridden by the preference** at `global.c:1034-1067`, giving the base `$5`. The `.greg` dump of the
   `puVar2` drafts shows exactly this: `;; 74 preferences: 5` and `74 in 5`.
   `prune_preferences` (`global.c:834-882`) cannot save it: it drops a lower-priority conflicter's preference from
   `regs_someone_prefers` whenever *we* prefer it too (equal size), so `$5` is never excluded in pass 0.
   Scoping the base into the arm removes it from `global.c` altogether and the whole preference chain with it.

The count half of the original residual (`s32 puVar2`, 76 vs 74 ins) is `reorg`'s `fill_slots_from_thread`
stealing the merge point's `addu` into both `j` delay slots and retargeting the jumps past it — it disappears as
soon as the arm's last real insn is an insn of the arm itself (the final `sll`), which the pointer-typed spellings
already give.

## (c) The move that closed it

**Scope the base pointer into the arm: drop the `puVar2`/`iVar3` pair and give each arm the whole address
expression, `puVar4 = &D_xxxx + (((u32)param_2) & 0xffff) * 0x14;`.**

Two variables removed, three statements become three, nothing else changes. The three identical trailing
`addu s0,v1,v0`s are re-merged at the join by cross-jumping after allocation, which is why the target still shows
one `addu` at a shared label with the jumps landing on it.

All four spellings of the same move reach 0 (`&D + n*0x14`, `n*0x14 + &D`, and both `(u8 *)((s32)&D + …)` casts) —
the move is robust to operand order and to the cast.

## (d) GENERATOR PROPOSAL

*When the residual is REG-only (or REG+COUNT with the extra insns sitting in `j` delay slots) and the diff shows a
`$2`/`$3` swap inside every arm of an if/else chain whose arms each set a variable that is only consumed by ONE
expression after the merge point, rewrite that expression into each arm — i.e. sink the merge-point statement into
the arms and delete the now-dead variable — then let cross-jumping re-merge the tail.*

A cheaper, more general form of the same dial for the `$2`/`$3`-inside-a-block class: **make the contested block
hold exactly three local quantities.** Two is the unrolled `case 2` (higher-density qty first); three is the
`case 3`→`case 2` fall-through that reverses that pair; four or more is `qsort` (higher-density first again). So
`next_qty == 3` is the only setting that hands `$2` to the *lower*-density quantity, and any move that adds or
removes one block-local, single-death pseudo in the arm flips the colours. Generators the engine already has that
change the count by one: R12 width on a variable set in the block (a narrow local adds an extend temp — this is
what the mechanical search found: `u16 puVar2` reached score 1, one `andi` short), and declaration scope
(function-scope → per-arm), which is this crack's move.

## (e) What did NOT work, with byte evidence

| attempt | score | why |
|---|---|---|
| `s32 puVar2` (the `body_free.c` start) | 18, 76 ins | `reorg` steals the join's `addu` into both delay slots (+2) |
| `u8 *puVar2` (pointer type) | 18, 74 ins | count fixed; pure `$2`/`$3` swap remains — the 2-qty fork |
| all 24 permutations of the four declarations | 18 each | quantity order is birth order inside the block, not declaration order |
| `(u16)param_2`, `param_2 & 0xffff` without the `u32` cast, `u32 iVar3`, `(x*5)<<2`, `&puVar2[iVar3]`, `iVar3 + puVar2` | 18 each | none of them changes the RTL shape of the arm |
| `u16 puVar2` (what the mechanical search found) | 1, 75 ins | gives the 3rd quantity (an SImode holder + a HImode truncate) and breaks the `$a1` preference — but pays one `andi` at the join to zero-extend, and is semantically wrong |
| per-arm `u16` holder for the address | 2, 75 ins | same trade |
| function-scope temp for the mask (`uVar5 = …; iVar3 = uVar5 * 0x14;`) | 23, 76 ins | 3 arms ⇒ 3 deaths ⇒ a global allocno and an extra register |
| `puVar2 = &D;` **before** the multiply in the arm | 22, 67 ins | the three multiply tails become identical and cross-jumping merges them |
| `do { … } while (0)` around the mask's own assignment (per-arm temp) | **7**, 74 ins | works as a ref-count dial (`flow.c:2067`, `depth = 1` at `flow.c:434`, +1 inside the loop) — index refs 3→4 ties the two densities so `case 2` no longer exchanges, fixing `$2`/`$3`; the `$a1` preference on the base survives, so the three `la`s stay in `a1`. A plain `{ }` (score 18) is the negative control that isolates the LOOP note |
| accumulate into the offset (`iVar3 += (s32)puVar2; puVar4 = (u8 *)iVar3;`) | **4**, 74 ins | the `addu`'s dest now conflicts with the base, so `expand_preferences` skips the merge and the base finally gets `$2` — but `iVar3` and `puVar4` coalesce into one pseudo, so the arms' last `sll` writes `s0` |
| putting one arm's `la` first to force a base/`a1` conflict | 9, 74 ins | it also makes the base conflict with `$2` and `$3` |

## (f) Where the method fell short

- **`history.txt` was a local optimum that hid the answer.** Twelve one-move children all scored 1 on top of the
  `u16` narrowing, so the trace read "one instruction away". The `u16` move is a *symptom-level* imitation of the
  real fix (it manufactures the third quantity by accident); the search had no move that deletes a variable, so it
  could never leave that basin. Reading the residual first and asking *which pass* — rather than hill-climbing from
  the best-scoring child — is what found it.
- **The class label pointed at registers; the fix was a variable.** `REG-caller` invites register-shaped moves
  (swap, pin, inline a temp). The actual lever was "this variable should not exist", which no register-shaped
  generator can express. Suggested engine addition: a **sink-the-join-statement** move for if/else chains, and its
  inverse (hoist), keyed on "every arm sets X, X is read once after the merge".
- **`residual_moves.md` 1a rank 3 (declaration SCOPE) is the row that wins here, but it is written for temps.**
  It should say explicitly that scoping a value into a block changes *two* things at once — it moves the value from
  `global.c` (where copy preferences propagate through `expand_preferences`) into `block_alloc`, and it changes the
  block's `next_qty`, which is a *discontinuous* dial (2 / 3 / ≥4 give three different orderings). The `next_qty == 3`
  double-comparison quirk at `local-alloc.c:1491-1502` is worth its own row: it is the only configuration in which
  the lower-density quantity gets the lower register.
- **What I could not settle from the source:** the exact `REG_NOTES` order at the join `addu` (it decides whether
  the base inherits `{5}` alone or `{3,5}`); I inferred it from the `.greg` preference lines rather than from
  `flow.c`.
