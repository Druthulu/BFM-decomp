# gcc-2.7.2 residual→C-lever map: CSE + expression emission + `/s` aliasing + stack layout
**Pass-group:** `cse.c` (8989) + `expr.c` (12077) + `function.c` (6321), with targeted reads of
`calls.c` / `stmt.c` / `local-alloc.c` / `sched.c` where they consume this group's decisions.
All source cites are `tools/reference/gcc-papermario/<file>:<line>` — **[A23] which is gcc 2.8.1, NOT
our 2.7.2; see the audit block below before following any line number.** All byte-proofs ran through
`tools/match_one.py` (pinned triple, relocation-masked byte equality). Proof C files:
`.run/gccmap/proofs/`. Date: 2026-07-02, Phase 23.

**Headline: the §10/§20 hoist-vs-remat class is STEERABLE (was "CONFIRMED unsteerable" since
Phase 20). Both canonical stub exemplars now MATCH** (`func_80149374` 23 ins, `func_801493D0`
23 ins — reach-134 fns, ready for whole-binary integration). Lever = §2 below.

> ## ⚠️ SOURCE-VERSION AUDIT (Phase 29 SESSION-23, 2026-07-28) — THIS FILE HAD THE MOST ERRORS
> The cites above say `gcc-papermario`, **which is gcc 2.8.1, not our 2.7.2** (vanilla 2.7.2 is at
> `tools/reference/gcc-2.7.2/`). All 74 claims here were re-derived against the real source by
> parallel agents, each REFUTED claim then adversarially re-checked by an independent agent told to
> uphold the map by default. **17 REFUTED raised; the highest error density of any map file.**
> Line numbers drift −20 to −220 (cse.c), −960 to −1180 (expr.c), −230 to −520 (function.c) — enough
> to land inside a different function. **`grep -n '^sym ('` before citing.**
>
> ### [A23-1] THE 1000-INSN CSE FLUSH DOES NOT EXIST IN gcc 2.7.2 — it is 2.8.1-only
> `grep -n num_insns tools/reference/gcc-2.7.2/cse.c` → **no hits**; no `flush_hash_table`, no
> "quadratic", no "Perhaps for 2.9" anywhere in the 8,779-line file. It was added in 2.8.1
> (`gcc-papermario/cse.c:8621-8644 [2.8.1 pm]`). **In our compiler a CSE class NEVER expires by instruction
> count.** This invalidates THREE places below — §1's table row, §6's "long straight-line giant"
> tell, and §7's "check `num_insns` distance / shift ±insns across the 1000 boundary" bullet — i.e.
> **a lever aimed at a counter our compiler does not have, in exactly the giants this map is
> consulted for.** All three are struck inline.
>
> ### [A23-2] §2's "kill THE class reg" is SINGULAR AND WRONG — and this is why §2 can fail
> A CSE class routinely holds **several** registers, and the extra ones have **no C-level name**, so
> the output-only asm kill can only ever name one of them. Byte-reproduced with the pinned cc1 during
> the audit: adding one line `v[1] = v[0];` to a working case defeats the recipe completely (working:
> frame 56 / 2 saved regs / `addiu` remat at site 2 → broken: frame 64 / 3 saved regs / `addu
> $16,$sp,16` hoist / both sites `move $aN,$16`). **Mechanism:** `config/mips/mips.c:2350-2351 [2.7.2]`
> (`expand_block_move`) calls `copy_addr_to_reg` on **BOTH** aggregate addresses, creating
> `(set (reg:SI 77) (plus:SI (reg:SI 30 $fp) 16))`; cse substitutes reg 77 into the FIRST call's
> arg-load, so by the time the asm kill fires it invalidates a register **already out of the chain**
> and reg 77 sails on into `$16`.
> **Two remedies, both byte-proven in the audit:** (a) spell the aggregate copy **field-by-field**
> (returns to frame 56 / 2 regs / remat), or (b) force a **real join CODE_LABEL** between the block
> move and the calls. **Caveat before reaching for (a):** if the TARGET's own bytes contain the
> unaligned `lwl/lwr…swl/swr` block move, spelling it field-by-field changes bytes you need — in that
> case the s32/remat route is simply closed and you should keep the narrower-typed draft.
> *(This is the documented explanation of a live 47→40-mismatch wall hit the same day on
> `func_80132F40`; ladder preserved at `.run/near6/f132F40_v1..v6.c`.)*
>
> ### The other upheld corrections (each struck or annotated at its site)
> - **§1's "complete list" of class killers is NOT complete** (upheld narrowly — the word "complete"
>   fails). Notably a **volatile SET's dest is invalidated** via `do_not_record` (`cse.c:7110-7114 [2.7.2]`),
>   which is the source line for §2's own lever — as written, §1 says that lever cannot exist.
> - **§4a: `assign_temp` does not exist in gcc 2.7.2** (added in 2.8; `grep -rn assign_temp` → 0 hits)
>   and **2.7.2's `assign_stack_temp` does NO `/s` reset**, so a **RECYCLED slot INHERITS `/s` and
>   `RTX_UNCHANGING_P` from its previous occupant** — the opposite of what §4a claims, and it
>   interacts directly with §5's own slot-recycling text.
> - **There is NO `BUILT_IN_MEMSET`/`BZERO` in 2.7.2's `expand_builtin`.** `memset` is always an
>   ordinary library CALL (which flushes the whole cse memory table), never an inline `/s` BLKmode
>   block move. The "memcpy/memset/strcpy" trio is really **memcpy/strcpy** sharing one path.
> - **§6's "recompute right after a join is NORMAL — never a residual" is FALSE at -O2**, where
>   `flag_cse_follow_jumps` and `flag_cse_skip_blocks` are both set (`toplev.c:3389-3390 [2.7.2]`) and
>   `cse_end_of_basic_block` extends the table across a join (TAKEN `cse.c:8118 [2.7.2]`, AROUND `:8150`).
>   As written, that row would have blocked §H.1's own antidote.
> - **§5's "`frame_offset` starts at 0 (= sp+0x10 at runtime)"** — only the parenthetical is wrong.
>   `STARTING_FRAME_OFFSET` is `current_function_outgoing_args_size`, which is **0 for a leaf with no
>   calls**, so a leaf's first local sits at **sp+0**, not sp+0x10. The rest of the claim stands.
> - **§H's "no bank (5 permuter-shaped clusters)" verdict is SUPERSEDED** — byte-refuted the same day:
>   4 of the 5 clusters proved steerable from C (`func_80176734` 217 → **13**, count exact 371/371).
>   Only two coupled ties survive. §H's own two mechanisms both CONFIRMED, with one correction: the
>   diamond antidote's barrier-preceded label is the **ELSE** label, not the merge label (the merge
>   label works because it is neither followable nor skip-block-able, so `new_basic_block()`
>   (`cse.c:8430 [2.7.2]`) clears the table).
> - **§H's `update_equiv_regs` live-length doubling is exactly ×2 on global priority**
>   (`local-alloc.c:1064 [2.7.2]`, and `allocno_live_length` is the DENOMINATOR — `global.c:594-597 [2.7.2]`); the
>   rest of the informal "~×4" comes from the `floor_log2(n_refs)*n_refs` numerator. It applies only
>   to pseudos carrying a REG_EQUIV note, and `CONSTANT_P` (`rtl.h:237-240 [2.7.2]`) **excludes a bare PLUS**
>   — so a frame address never qualifies (same correction as `regalloc.md` RC-7).

---

## §0 The diagnostic loop: RTL dumps from the pinned cc1

`cc1` accepts `-da` → per-pass dumps (`t.i.rtl` = expand, `.jump`, `.cse`, `.loop`, `.cse2`,
`.flow`, `.combine`, `.sched`, `.lreg`, `.greg`, `.sched2`, `.dbr`). This turns "which pass did
that?" from guesswork into a 10-second lookup:

```sh
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 \
  -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C t.c > wd/t.i
cd wd && <repo>/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas \
  -msoft-float -fgnu-linker -da t.i -o t.s
```

Reading the dumps: ~~pseudos start ≈ reg 70 (MIPS: 0-31 GPR, 32-63 FPR, 64-66 hi/lo/fpsw,
67-70 virtuals).~~ **[A23] corrected — `FIRST_PSEUDO_REGISTER` is 68** (`config/mips/mips.h:1179 [2.7.2]`),
so the four virtuals are **68-71** and **the first pseudo is 72**, not ~70. (The headline
`(reg:SI 69)` below is still right: virtual-stack-vars is the 2nd virtual.) `(reg:SI 69)` in `.rtl`
= **virtual-stack-vars** (frame base, = first local's address). In `.cse` and later, frame addresses appear as `(plus (reg 30 $fp) k)` — `$fp` is
eliminated to `$sp` only at reload, so grep for `$fp` pre-reload, `sp` post. Triage rule:
- residual visible in `.cse` → this file, §1-§3 below;
- appears first in `.lreg/.greg` → regalloc (pins / §30 recipes);
- appears first in `.sched/.sched2/.dbr` → scheduler/delay-slot group.

---

## §1 The CSE machine (cse.c) — what survives what

CSE keeps a hash table of equivalence classes {expr, regs...} per **extended basic block** and
replaces any src whose class holds a cheaper valid reg. Everything about "why did gcc reuse /
not reuse that value" reduces to whether the class was still valid at the second occurrence.

**Class killers (complete list for MIPS):**

| Event | Effect on classes | Source |
|---|---|---|
| reg SET again | that reg leaves its class; `reg_tick[reg]++` stales every EXPR containing it | `cse.c:7418-7441 [2.8.1 pm]` (cse_insn tail), `invalidate` |
| CALL_INSN | `invalidate_for_call`: **hard call-clobbered regs only. Pseudos + their exprs SURVIVE calls** | `cse.c:1756 [2.8.1 pm]` |
| CALL_INSN | `invalidate_memory(everything)`: ALL `MEM` entries die (non-const calls) | `cse.c:7409-7415 [2.8.1 pm]` |
| memory store | selective MEM-entry kill via `note_mem_written` — see §4 aliasing table | `cse.c:7709 [2.8.1 pm]`, `1732` |
| CODE_LABEL | **total flush** (`new_basic_block`) — every class dies at every label | `cse.c:797 [2.7.2], 8614` |
| ~~1000 insns~~ | ~~**total flush** mid-block ("extreme quadratic behavior" kludge)~~ **[A23-1] DOES NOT EXIST IN 2.7.2** — 2.8.1-only; no `num_insns` in our `cse.c`. A class never expires by insn count. | ~~`cse.c:8626 [2.8.1 pm]`~~ |
| volatile asm | **NOTHING** (no reg-class invalidation; a `"memory"` clobber kills only MEM entries via BLKmode→`all=1`) | `cse.c:6340-6355 [2.8.1 pm]` |

Consequences you will see in diffs:
- **Pseudo-held subexpressions get reused ACROSS CALLS** (the phantom-$s-reg §30 class and the
  address-caching §2 class). Hard-reg-held ones don't (killed at the call).
- **A memory-clobber barrier `__asm__ volatile("":::"memory")` CANNOT stop reg-class reuse** —
  that's why every Phase-20 "barrier" attempt on this class failed. It only kills cached LOADS.
- **Recomputation after any label/join is NORMAL** (table flushed) — never chase a "missed CSE"
  across a branch target; conversely you cannot make gcc REUSE a value into a label'd block.
- With `-fcse-follow-jumps` (in `-O2`) the EBB follows the TAKEN path of a conditional
  (`cse.c:8647-8667 [2.8.1 pm]`, `invalidate_skipped_block` handles the not-taken side) — so reuse INTO
  the fall-through-only path may differ from the taken path.

---

## §2 RESIDUAL: cross-call ADDRESS caching — hoist-vs-remat (§10/§20) — **STEERABLE, byte-proven**

**Symptom (the §20 wording):** target rematerializes `addiu $aN,$sp,K` at each call site;
ours computes it once into a freed callee-saved reg (`addiu $s0,$sp,K` + `move $aN,$s0` per
use). +1 insn, one extra $s-reg touched, cascades into the schedule.

**Mechanism (three cooperating decision points):**
1. `calls.c:1632-1650 [2.8.1 pm]` — every register-parameter value is precomputed by
   `expand_expr(..., NULL_RTX, ...)`; for `&local` at frame offset ≠ 0 this **forces a fresh
   pseudo** `rN = (plus vsv K)` per call site (`memory_address`/`force_reg`). Offset-0 locals
   are the exception: `&first_local` IS `virtual-stack-vars` (already a reg) → no pseudo →
   the arg-load `(set $aN vsv)` is later rewritten IN PLACE by `instantiate_virtual_regs`
   (function.c) into `(set $aN (plus sp K))` — a **hard-dest** addiu per site.
2. `cse.c` unifies the second site's pseudo with the first (`(plus $fp K)` class holds a valid
   pseudo — calls don't kill pseudos, §1) → one pseudo now live across the call.
3. `global.c` happily gives that call-crossing pseudo a callee-saved reg (free if one is
   already saved) → the cached form. (`local-alloc.c:1007 [2.7.2] update_equiv_regs` does NOT rescue:
   it only REG_EQUIVs CONSTANT_P notes / unchanging MEMs, and only moves REG_N_REFS==2
   pseudos — an address used at 2 call sites has 3 refs.)

**Why the target remats:** the first-use pseudo's class must have NO valid reg when the second
site is scanned. The zero-offset local gets this for free (hard-dest class dies at the call —
that is why `&sp10` remats naturally in the same function). For any other offset you must kill
the class reg yourself.

**THE LEVER (byte-proven):** name the first use through a pointer local in a nested block, and
**redefine it AFTER the call with a volatile OUTPUT-ONLY asm**; later sites use the bare `&buf`:

```c
/* BEFORE (cached, +1 insn):                    AFTER (remat, MATCH): */
f2(t, &sp10, &sp18);                            {
f3(&sp18, arg1);                                    void *q = &sp18;      /* (plus fp K) lands in q's pseudo */
                                                    f2(t, &sp10, q);
                                                    __asm__ __volatile__("" : "=r"(q));  /* kill: re-SET q, 0 bytes */
                                                }
                                                f3(&sp18, arg1);          /* class has no valid reg -> fresh addiu */
```

- `func_80149374` (ov_SC04_005 …/func_80149374.s): 24 ins/11 mism → **MATCH (23 ins)**.
  Proof: `.run/gccmap/proofs/func_80149374_remat.c`.
- `func_801493D0` (ov_SC03_099): same recipe on `u8 buf[8]` locals → **MATCH (23 ins)**.
  Proof: `.run/gccmap/proofs/func_801493D0_remat.c`.
- Verify cmd: `tools/match_one.py <fn> --c <proof.c> --asm-subdir asm/<ov>/nonmatchings/<ov>`.

**Boundary conditions (each byte-probed — violating any one loses the match):**
1. **Output-only** `"=r"(q)` — the familiar re-tie `"=r"(q):"0"(q)` KEEPS q live across the
   call → callee-saved → 26 ins (proof `..._NEG_input_tied.c`). Output-only leaves garbage in
   q, so q must be dead after the call — it always is in this pattern.
2. **volatile** — a non-volatile asm whose output is dead gets deleted by flow before it can
   matter (it still kills the CSE class — cse runs first — but keep volatile so the intent
   survives; it emits zero bytes either way).
3. **Placement:** q's init must not itself cross a call (declare in a nested block right at
   its call statement; a function-top `void *q = &buf;` init crosses earlier calls → 29 ins,
   proof `..._NEG_top_decl.c`). The kill-asm goes AFTER the call, never between the address
   computation and the call (an asm inside the pre-call chain deepens that chain and the
   scheduler then hoists the addiu above the other arg setups — 2-off order flip; observed
   with statement-expr and pre-call re-tie variants).
4. The LAST use site takes the bare `&buf` — its fresh pseudo dies at its own call, so it
   coalesces into the arg register (`addiu $aN,$sp,K` direct).
5. ≥3 sites: kill after every site except the last.

**Class verdict:** STEERABLE. Re-test the whole "hoist"/"remat" backlog bucket (~31 verdicts,
§20 router) with this recipe; `func_80149374`/`func_801493D0` are reach-134 and ready to bank
(leaf-proven only — run the whole-binary `gate_stage` per §30's integration note).

---

## §3 RESIDUAL: cross-call VALUE CSE — the phantom extra $s-reg (§30 confirmed, mechanism now sourced)

**Symptom:** a subexpression of a param/global (`param & 0xffff`, a shifted index…) appears in
the first call's args AND again late in the function; gcc computes it once, parks it in an
extra callee-saved reg across all the calls (+1 `sw/lw` pair, 7th $s-reg, count +1).

**Mechanism:** same §1 chain as §2 but for a VALUE: pseudo classes survive calls
(`cse.c:1756 [2.8.1 pm]`), so the tail occurrence is replaced by the pre-call pseudo.

**Lever (byte-proven, cookbook §30 #3 / toolkit `func_80176D94`):** the zero-byte
**input-tied re-tie** `__asm__("" : "=r"(x) : "0"(x));` placed between the two occurrences.
It re-SETS x's pseudo → `reg_tick[x]++` stales every table expr containing x → the tail
recomputes in place (`andi $s2,$s2,0xffff` at its natural position).

**Choosing the re-tie variant (this table is the load-bearing bit):**

| Situation | Variant | Why |
|---|---|---|
| the VARIABLE's value is needed later (kill exprs built FROM it) | `"=r"(x) : "0"(x)` non-volatile | value preserved; liveness unchanged (x was live anyway) |
| a dead-after-call ADDRESS/pointer local (kill the pseudo itself) | `__volatile__ "=r"(q)` output-only | input variant would extend q across the call (§2 probe #1) |

---

## §4 The FULL `/s` (MEM_IN_STRUCT_P) aliasing model — setters, consumers, levers

### 4a. Setter sites (complete for this pass-group)

**Loads/derefs — `expr.c` INDIRECT_REF case (expr.c:5506 [2.8.1 pm], grant at 5535):** `/s` iff
```c
TREE_OPERAND(exp,0) == PLUS_EXPR                      /* top-level pointer sum: q[k], *(q+k) with q TYPED */
|| (SAVE_EXPR && its operand is PLUS_EXPR)            /* same sum reused inside ONE expression */
|| AGGREGATE_TYPE_P(TREE_TYPE(exp))                   /* deref'd TYPE is struct/union/array: *(Blk16*)p */
|| (ADDR_EXPR operand && AGGREGATE_TYPE_P(operand))   /* *&aggregate */
```
New vs cookbook §30/§30a (which only knew arm 1): **a bare `*(struct S*)p` struct COPY gets
`/s` via arm 3 with no PLUS at all**, and a cast-wrapped sum `*(T*)(p+k)` — NOP_EXPR on top —
still gets NO `/s` (§30a stands). Scalar `*p` never gets `/s`.

**Member/array refs — `expr.c:5891 [2.8.1 pm]`** (the COMPONENT_REF/ARRAY_REF/BIT_FIELD_REF bundle after
`get_inner_reference`): **unconditional `/s`**. This is why the anon-struct member cast
`((struct{s32 f;}*)p)->f` is the universal GRANT (§30) — front end emits COMPONENT_REF.

**Store side — `expr.c:4292 [2.8.1 pm]`** (`expand_assignment`, component/array dest): unconditional
`/s` on the dest MEM. An INDIRECT_REF dest reuses the 5535 rule symmetrically. So store-`/s`
is steered by the same syntax choices as loads.

**Temps & locals:**
- `function.c:949 [2.8.1 pm]` — **reusing a temp slot RESETS `/s`=0**, then `assign_temp`
  (`function.c:985 [2.8.1 pm]`) sets `/s = AGGREGATE_TYPE_P(type)`.
- `stmt.c:3646 [2.8.1 pm]` — every memory-resident LOCAL's DECL_RTL gets `/s = AGGREGATE_TYPE_P(decl
  type)`: **an array/struct local's home MEM is `/s`, a scalar local's spill home is not.**
- `function.c:3876 [2.7.2]/4025/4082/4136/4386` — parameter stack homes: `/s = aggregate-ness`.
- `expr.c:9012 [2.8.1 pm]/9029/9097` — memcpy/memset/strcpy builtin block MEMs: `/s = AGGREGATE_TYPE_P`.
- `expr.c:465 [2.8.1 pm]` + emit-rtl `change_address` — derived MEMs COPY the flag.

### 4b. Consumers — where `/s` changes codegen

**Scheduler (sched.c:830 [2.7.2] `true_dependence`, 862 `anti_dependence` — SYMMETRIC):** two memrefs
conflict unless `memrefs_conflict_p` (base+offset window reasoning, sched.c:628 [2.7.2]) proves
disjoint, **except** the escape: a `/s`+varying-address+non-QImode access does NOT conflict
with a non-`/s`+fixed-address access. Because true AND anti dependence share the clause, the
`/s` lever moves loads over stores AND stores over loads (§30's rule, now proven both ways).
`QImode` (u8/s8) accesses NEVER get the escape (ANSI char aliasing) — don't try to float a
byte access over a fixed store by struct-casting; retype to u16/u32 member if the target shows
it floating.

**CSE store-side (cse.c:7709 [2.8.1 pm] `note_mem_written` → 1732 `invalidate_memory`):** what a STORE
kills in the load-cache table:

| Store written | writes flags | Cached loads killed |
|---|---|---|
| fixed symbol `D_x = v` | var=1 | all varying-address (pointer) loads; **fixed-symbol loads survive** (own address killed exactly, `cse.c:7433 [2.8.1 pm]`) |
| `p->f = v`, `p[k] = v` (`/s` or PLUS addr, non-QI) | var+nonscalar | varying + `/s` loads; **fixed-symbol scalar loads SURVIVE** |
| bare `*p = v` (no `/s`, no PLUS, non-QI) | **all=1** | **EVERYTHING** — total memory-table flush |
| any `u8` store through a pointer (QImode) | all=1 | everything |
| BLKmode store (struct copy dest) | all=1 | everything |

Lever reading: if the target RELOADS a global after a pointer store, write the store as a bare
`*p =`; if it KEEPS the pre-store value, write `p->f =` / `p[k] =`. This is the store-side
twin of §30's load rule and explains "why did (only) that global reload" diffs without
touching the scheduler.

### 4c. Grant/deny cheat sheet (steering recipes, §30/§30a + this pass)

- GRANT `/s`: `((struct{s32 f;}*)p)->f` (anon struct — propagation-safe), `q[k]` with typed
  `q`, `*(Blk16*)p` aggregate copy, any real member ref.
- DENY `/s`: bare `*p`, `*(T*)(p + k)` (cast on top of the sum), scalar local spill homes.
- Remember both sides (load and store) and both dependence directions are steered by the
  same syntax.

---

## §5 Stack frame layout (function.c) — offsets, rounding, recycling

**Allocator (`function.c:681 [2.7.2] assign_stack_local`):** MIPS has no FRAME_GROWS_DOWNWARD →
`frame_offset` starts at 0 (= sp+0x10 at runtime: 0x10 arg-save area below) and grows UP in
ALLOCATION ORDER. Alignment: `align=0` → mode alignment (u64 → 8); `align=-1` (all BLKmode:
arrays, structs) → `BIGGEST_ALIGNMENT` = **8 bytes, and size CEIL-rounded to 8**. So:
- locals appear at increasing offsets in DECLARATION (expand) order;
- every array/struct occupies an 8-aligned, 8-rounded slot (`u8 buf[4]` eats 8 bytes);
- a u64/double scalar also 8-aligns; u32 4-aligns — reorder declarations to steer gaps.

**Locals go through the TEMP-SLOT machinery** (`stmt.c:3643 [2.8.1 pm]` → `assign_stack_temp(mode,size,
keep=1)`, `function.c:826 [2.7.2]`): before allocating fresh, it **reuses a free slot of the same
mode+size, else splits the smallest larger free BLKmode slot** (leftover ≥8 becomes a new
free slot). Compiler temps (struct-return staging, block copies `expr.c:5868 [2.8.1 pm]/4170`,
`assign_temp` aggregates) share this pool and are freed at statement end (`free_temp_slots`,
levels pushed around call-arg evaluation by calls.c). **Consequence: a later local can land in
a RECYCLED earlier-temp slot — frame offsets out of declaration order, or a frame ±8 vs the
obvious layout.** This is the mechanical core of the "frame-fragility" class (func_8014EA4C
residue): the fix is never padding hacks; it is reproducing the temp population — i.e. does
the source create a struct copy / u64 intermediate / aggregate arg before that local's block
is entered?

**Diagnosis recipe:** compare the target's `$sp` offsets cluster-by-cluster; each 8-aligned
cluster = one BLKmode object (or a recycled temp). Draft SEPARATE locals per cluster in target
offset order rather than one giant `u8 buf[N]` — a monolithic buffer forces you to guess
internal offsets AND changes `/s` (stmt.c:3646 [2.8.1 pm] gives the array home `/s`) and IV behavior
(§30a #2 single-base rule) in one blob. (This is exactly what's wrong with the current
`func_80132784` draft — see §7.)

---

## §6 Diagnostic tells (residual → class, one line each)

| Tell in the byte-diff | Class | Lever |
|---|---|---|
| `addiu $sN,$sp,K` once + `move $aN,$sN` per call vs target per-site `addiu $aN,$sp,K` | §2 address caching | nested-block ptr local + post-call `volatile "=r"(q)` kill |
| one extra $s-reg saved, count +1, tail uses $sN where target recomputes (`andi` etc. in place) | §3 value CSE across calls | input-tied re-tie `"=r"(x):"0"(x)` between occurrences |
| zero-offset ptr load stuck under a fixed-symbol store; offset/member loads float | §4 `/s` true-dep | grant: anon-struct member ref; deny: bare `*p` (§30) |
| a STORE pinned under/over a load the target orders oppositely | §4 anti-dep (same rule) | same grant/deny on either access |
| target reloads a global after `*p=..` but not after `p->f=..` (or vice versa) | §4b CSE store-flush | choose bare-deref vs member/indexed STORE syntax |
| all pointer-loads reload after ANY u8 store | §4b QImode=total flush | retype the store (u16/u32 member) if target disagrees |
| frame ±8, or a local's offset out of decl order | §5 slot recycling / 8-rounding | reproduce/eliminate the compiler temp; reorder decls |
| every array sits 8-aligned with padding gaps | §5 BLKmode rounding | expected — don't fight it, mimic with decl order |
| value recomputed right after a branch join/label | §1 label flush | NORMAL — never a residual; don't add CSE-defeating hacks |
| long straight-line giant: early value suddenly recomputed mid-function | ~~§1 1000-insn flush~~ **[A23-1] NOT the flush (absent in 2.7.2)** — look for a label/join, a volatile, or a call flushing the memory table instead | ~~expected in giants; position-dependent — see §7~~ **re-triage against §1's real killer list** |
| `lui` above a branch, `ori` duplicated in delay slot + taken path | dbr/reorg territory (delay-slot stealing), NOT cse | route to jump/sched pass-group |

---

## §7 Verdicts, open items, and the giant

- **§2 hoist-vs-remat: STEERABLE** — 2/2 byte-proofs. Re-run the ~31 "hoist" + the remat-shaped
  "regalloc" backlog verdicts with the §2 recipe before any permuter time.
- **§3 phantom-reg: STEERABLE** (was already §30; mechanism now source-anchored).
- **§4 `/s`: STEERABLE both directions** (loads AND stores; QImode is the hard exception —
  intrinsic when the target's byte access truly floats: it can't, so if a diff demands it,
  the draft's TYPE is wrong, not the schedule).
- **§5 layout: STEERABLE** via decl order/typing/temp reproduction; INTRINSIC only in that you
  cannot place two 8-BLKmode objects at 4-mod-8 offsets — that's evidence the original source
  had different object boundaries, not a permuter case.
- ~~**§1 1000-insn flush: INTRINSIC-ish** — you cannot move the counter from C; if a giant's
  residual is a reuse/recompute flip exactly once mid-function, check `num_insns` distance;
  restructuring that shifts ±insns across the 1000 boundary is the only (fragile) lever.
  Document any confirmed case before hand-grinding.~~
  **[A23-1] DELETED — the counter does not exist in gcc 2.7.2** (`grep -n num_insns cse.c` → no hits;
  added in 2.8.1). Do NOT spend a giant's budget measuring distance to a 1000-insn boundary. A
  once-mid-function reuse/recompute flip in OUR compiler is a label/join (§1 + the -O2
  follow-jumps/skip-blocks behaviour), a volatile, or a call — all of which ARE steerable.
- **`func_80132784` (400 ins, `asm/ov_SC01_077/nonmatchings/ov_SC01_077_a/`)** — the draft
  (`.run/backlog_drafts/func_80132784.c`, stuck 240/400) is MULTI-CLASS, in this order:
  (1) §5: single `u8 buf[0xC0]` vs target's separate 8-aligned locals (target arg addresses
  `sp+0x80`, `sp+0xC0` vs draft `sp+0x78`, `sp+0x38`) — redraft with separate locals FIRST;
  (2) §2: the five pre-GTE `addiu $sN,$sp,K` hoists (draft idx166-170) vs target's in-place
  `addiu $s0,$sp,0x80` remat — apply the §2 kill to the GTE pointer locals instead of pinning;
  (3) a `lui/ori` split across a branch with delay-slot duplication (idx111/116/134) — dbr
  (fill_slots_from_thread) + possible condition-shape difference: jump/reorg pass-group;
  (4) the inline-GTE `__asm__` blocks themselves perturb sched chains (§2 boundary #3) —
  keep their operand lists minimal. Expect (1)+(2) to collapse most of the 240.

## §8 Cookbook feed-forward (proposed entries)

1. §30b: "CSE classes survive calls in PSEUDOS only" master rule + the two re-tie variants
   table (§3) — replaces per-function rediscovery of barrier placement.
2. §10 CLOSURE: hoist-vs-remat steerable; recipe + the four boundary conditions (§2).
3. §30a extension: `/s` full setter list (SAVE_EXPR arm, aggregate-deref arm, store-side
   4292, temp-slot reset) + the store-side CSE flush table (§4b).
4. §5-layout: BLKmode 8-align/8-round + temp-slot recycling as the frame-fragility mechanism.

## §H Phase-27 — the CSE address-fold antidote + the fall-through delete (func_80176734, Fable5, 2026-07-15)

Fresh-core pass (`.run/giants/func_80176734.fable.md`, full pass dumps `.run/giants/fable_76734/`) — no bank (5 permuter-shaped clusters), but two byte-proven CSE mechanisms with pure-C antidotes worth reusing:

1. **The cse address-fold pair — killed by a balanced if/else diamond (zero asm).** `find_best_addr`'s cost-ungated qty-const fold + `from_plus` re-association eat reg-based global accesses and derived pointers on *every* cse walk (so a target that recomputes `&g + k` per use, instead of folding, looks unreachable). The pure-C antidote: wrap the merge in a **balanced `if/else` diamond** so its label is **barrier-preceded** → cse starts a FRESH table there → both folds die with no `#APP`. This replaced two asm dials on this function — prefer it to an inline-asm fence whenever the divergence is a cse fold across a join.
2. **`update_equiv_regs` doubles live_length for single-set REG_EQUIV pseudos** (`local-alloc.c:1064 [2.7.2]`) — a **2nd set** of an address pointer forfeits the doubling and ~quadruples its allocno priority, rotating the callee-saved bank. Explains a whole "my zero-byte dial broke the $s-order" class: the dial added a second set. (Companion to regalloc §H; recorded there too.)
3. **`record_jump_equiv` fall-through recording** (`cse.c:7511 [2.7.2]`) deletes a target's provably-dead branch; only an identity-asm 2nd-set re-opaques the value. A recognition **tell**: if the original keeps a branch cse would prove dead, the source had a genuine (non-constant-foldable) second writer.
