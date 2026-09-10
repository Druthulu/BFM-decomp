# func_80130D48 (ov_SC04_011_jr_8012ACE0.c), T7 agent c6, S103

**Result: score 0, no levers left.** The function is byte-identical to the target, relocations included
(`objdump -drz` of the function diffs empty), and the whole scratch object `scratch/final.o` has the same `.text`
disassembly and the same `.rodata`/`.data` as the baseline object (md5 equal). No register pin, no asm, no volatile added,
no invented zero term. `body.c` is the final text.

## (a) The residual in one sentence
A pure two-register swap, 266 against 266 instructions, nothing missing: the parameter `pa` (arg0) sat in `$s3` and the
struct pointer `p = D_80078E78` sat in `$s2`. The target has them the other way round. The 3-instruction "insert" at the head
is only the prologue scheduler moving the save of whichever register receives `a0` (`sw s2; move s2,a0` in the target,
`sw s3; move s3,a0` in mine). It goes away once the swap is fixed.

## (b) The pass and the decision (read, then proved on bytes)
- **Global allocation order**, `global.c:594-607` `allocno_compare`: priority = `floor_log2(refs)*refs/live*10000`,
  highest first, and ties go to the lower allocno number. Both pseudos cross calls, so `find_reg` gives them callee-saved
  registers in allocation order. `tbl` took `$s0` and `val` took `$s1`, so whichever of the two came next took `$s2`.
- Allocation table of the lever-free body (`tools/alloc_table.py free`, dumps in `scratch/dumps_free/`):
  `p` = r75, 8 refs / 198 live, **priority 1212.1**. `pa` = r74, 4 refs / 208 live, **priority 384.6**.
  The order line ends `... 75 74`, so `p` is allocated first and gets `$s2`.
- Doing the arithmetic rules out every small move. Declaration order cannot change the result because the priorities are
  distinct and priority is compared first (`global.c:602`). To get `pa` above 1212, `pa` needs 9 or more refs at about
  208 live, or `p` needs 3 or fewer refs. `p`'s seven base-register uses are all in the target bytes, so the refs had to
  come to `pa`.
- **The fingerprint that gave the source shape** was in the target's tail, not in the residual hunks. Six case stubs are
  `j 6448; li a0,K`, landing on a common `move a1,zero; jal func_8012C658; move a2,s2`. The two computed cases jump to
  `644c`, which is the middle of that sequence and skips the `move a1,zero`. Compilers emit this shape when the shared
  suffixes of N separate call sequences are merged by **cross-jumping**: `jump.c:1969` (the simplejump case) and
  `find_cross_jump` at `jump.c:2371`. It runs only in the post-reload jump pass, `toplev.c:3142`
  `jump_optimize (insns, 1, 1, 0)`, which comes after global_alloc (`toplev.c:3077`) and after sched2 (`toplev.c:3117`).
  So the original had **one call per case**, and global allocation saw every one of them: `global.c:421`
  `allocno_n_refs[allocno] += reg_n_refs[i]` counts arg0 once per call site.
- **Proved on dumps** (`scratch/dumps_c9/`, the final body): arg0 is now r72, **11 refs** (1 set + 2 loads + 8 call args)
  / 208 live, **priority 1586.5**, which is above `p` (r74, still 1212.1). The order line ends `... 72 123 150 74`.
  The `.greg` and `.sched2` dumps still hold **8** `func_8012C658` call_insns and the final `.s` holds **1**, so the merge
  happens in jump2 after allocation, as the reading predicted.

## (c) The source moves that closed it
1. (The whole close.) De-merge the shared call tail. Replace the `call_a0 = K; call_a1 = 0; goto do_call;` sites and
   the `do_call:` label with one call per case, `ret = func_8012C658(K, 0, arg0); break;`, and an `if (... == 0xB) ...
   else switch` in place of the early goto. The null check on `ret` stays shared after the switch. This scored 0 on its
   **first `--try`** (`scratch/c1.c`).
2. Readability changes, each re-proved at 0:
   - the lever-residue blocks `{ s32 v1; s8 *bp; ... }` become `tbl = D_8019083C + val;` (c2);
   - `ret` becomes `s32`, the callee's real return type, which removes the casts (c3);
   - the `pa = arg0` copy is dropped (c4);
   - `if (rr >= *tbl) do tbl += 3; while (...)` becomes `while (rr >= *tbl) tbl += 3;` (c5);
   - the two goto counting loops become `for (i = 0; i < 3; i++, tbl++) { if (r < *tbl) break; }` (c8);
   - the variables are renamed (`s1v`→`val`, `cnt`→`i`, `call_a1`→`j`), and `id` is scoped to case 0x60000 (c9 = body.c).

## (d) Generator proposal
When a callee-saved swap involves a pseudo that is a call argument at a **shared `goto do_call` tail** (the target shows
`j L; li a0,K` stubs, and some of them jump into the MIDDLE of a common call sequence), emit one call per goto site
(`args...; goto do_call;` becomes `ret = f(args); break;`) and let jump2's cross-jump re-merge them at zero byte cost. This
multiplies the shared argument's refs in `global.c:421`, which raises its `allocno_compare` priority. A tool can check the
move by arithmetic before compiling: new refs = old refs + (call sites − 1), and the priority must pass the rival
allocno's.

The same fingerprint says the tree's `do_call:` gotos were never the original shape. Any residual-free function with a
`goto do_call`-style tail is a candidate for this readability rewrite.

## (e) What did not work, or was not needed
- The mechanical search (history.txt: 6 runs, up to 2342 compiles, best 18) could not reach this. Every move it has
  (R7 block/do-while, R8 temp/hoist/base, R9 swap-stmts) keeps the single call. By the arithmetic above, no
  single-statement move can make up a 384 → 1212 priority gap.
- `while (r >= *tbl) { ...; if (++i >= 3) break; }` (c6) and a `do { if (r < *tbl) break; ... } while (i < 3)` (c7)
  both scored 56 (274 instructions against 266, 8 more instructions). The `for` form (c8) and the original goto form both
  score 0.
- Not tried: the pins on `$3` that `sites.txt` marks NEEDED. The lever-free start never showed a `$v1`/`$v0` residual,
  so there was nothing to fix there.

## (f) Where the method fell short / notes for the next agent
- The residual and the allocation table said exactly **what** was wrong (priority 384.6 against 1212.1) and proved that no
  small move could close it. They could not say **how** the original earned the refs. The answer was in the target's
  whole-function dump (METHOD step 1): cross-jump stubs jumping into the middle of a shared call. The hunk view never
  shows the tail because the tail is identical. **Proposed method step:** when the table shows a priority gap too large for
  a local move, read the target for merge fingerprints (cross-jump stubs, delay-slot constants before a common `jal`)
  and count how many source sites the merged code stands for.
- `neighbours.txt` recorded this function's LEVERS in English ("pin pa=$s2 p=$s3") but not a mechanism. A lever
  recipe is not a crack.
- Side finding (naming evidence, not used): `D_80078EB2` and `D_80078EB4` are `D_80078E78 + 0x3A` and `+ 0x3C`, the same
  struct that `p` walks (case 1 reads `p + 0x3A`/`p + 0x3C`). In case 0x10000 the target reaches them by absolute
  `lui/lhu` rather than through `$s3`, so the original also wrote those two reads as direct global accesses.

Paths: `body.c`, `mechanism.md`, candidates `scratch/c1.c`…`scratch/c9.c`, dumps `scratch/dumps_free/`, `scratch/dumps_c9/`.
