# T7 §G — levers harvested this session (formalize into cookbook §36/§31 at batch close, R30)

> **[A23] SOURCE-VERSION AUDIT (2026-07-28).** 30 claims re-derived against `tools/reference/gcc-2.7.2/`;
> 2 REFUTED raised. **Provenance here is MIXED, not uniformly contaminated** — some cites are already
> 2.7.2-correct (e.g. `sched.c:2469 [2.7.2]` = the true `birthing_insn_p` line) while others came from the
> 2.8.1 `gcc-papermario` tree. So check each citation individually rather than assuming a uniform
> offset. This is a session harvest log, not a primary reference: where it disagrees with
> `sched.md` / `regalloc.md` / `cse_expr.md` (all audited the same day), those files win.

## TOOL FIX (flywheel) — permuter comment-strip (tools/p16_permute.py make_base_c)
A draft's header comment (long, non-ASCII —/§, prose that trips a prep regex) lost its closing
`*/` in base.c → `cpp -P -nostdinc` died "unterminated comment" → decomp-permuter no-op'd SILENTLY
at preprocess ("no match (0s)"). Had been masking the permuter on EVERY commented giant draft.
Fix: `strip_c_comments()` in make_base_c before the other passes. Immediately cracked func_801571C4
(SCHEDULE, 11→0 in ~40s). **Cookbook: always sanity-check a permuter "no match (0s)" = preprocess death.**

## func_801571C4 (198, SCHEDULE) — MATCH, banked ×1 (permuter)
- Residual was pure prologue position ripple (the `local_40=a2` save at idx5-6 vs target idx14-15).
- Permuter winner: proved `local_40 == a2`, substituted `a2` at the use, kept the dead
  `__asm__("":"=r"(local_40))` as a pure schedule wedge (semantically-equiv, byte-exact).
- BANK wrinkle (main-split giant): caller forward-decl `extern void func_801571C4` at ov_SC01_077.c:4721
  conflicts with the `u32` def. Widen `void`→`u32` (byte-neutral; func_80157158 ignores the return) =
  §35-step-1 caller-extern reconcile. gate_stage's sig_unify REGRESSED the standalone match (198→190);
  the winning stage was canon+cast+reconcile (`-cn-cast-rc`). **Bank giants with --no-propagate; the
  `extern void`→canonical-return reconcile is the recurring main-split def-side wall.**

## func_8014EA4C (183) — agent CLOSE=6 (count-exact); permuter exhausted → FABLE5 CANDIDATE
- **NEW §31/§36 LEVER (headline): a `%hi/%lo`-read value-symbol MUST be a scalar, not `[]`.**
  `extern u8 D_80126720[]` made `D_80126720 - a1[0] >= 0` POINTER arithmetic → gcc folds static-array
  ptr ≥0 to constant-TRUE → DELETES both sign-test blocks (−17 ins). Declaring `extern s16 D_80126720`
  (scalar) → real integer subtraction → `bltz` survives, +17 ins exact. **Diagnostic tell: a large
  instruction SHORTFALL concentrated in sign-test/branch blocks → suspect a value-symbol mis-declared
  as array.** Fixing it also auto-restored the `$s` regalloc order (ref-counts) — confirms §32#1.
- Residual 6 = C1 (idx69-71, §31 S4 load-gap-filler: `sw D_801150D8`=pre-call low-LUID wins the
  `lw a0` load-delay slot over the a1 call-arg load) + C2 (idx135-137, expand_abs `move $3,$2;negu $3`
  vs target in-place `negu $2`; local-alloc coalesce).
- **FRAME KNIFE-EDGE unsteerable sub-class:** frame 0x60 comes ONLY from the OOB `buf[16]+memcpy(buf+16,a2,8)`
  construction; ANY added local / register-asm dummy → 0x68 (+1 insn). So the §34 toolkit is unavailable
  → needs gdb-on-cc1 (shipped cc1's .sched/.greg dumps are empty). Permuter also can't (small space).

## func_801412A8 (198) — agent CLOSE=80 (count-exact, pin-clean); permuter exhausted → FABLE5 CANDIDATE
- Refutes the old "S11 CONFIRMED-INTRINSIC" flag: 110 diffs = 48 pure-schedule + 62 register; the 62
  register ARE steerable. gdb-on-cc1 (`find_free_reg`): masks/bases are LOCAL-alloc qtys in block 7
  ("9 regs to allocate" globally = the local-vs-global tell). **RC-3 pin on the highest-priority mask
  (`M24=0xffffff→$a3`) cascades 0xff000000→$t0 + code→$t0: 110→91; +4 more pins → 80.**
  **NEW cookbook: for addPrim/GPU-builder giants with NIL $s pressure (all caller-saved $t), the
  mask/base register choice is a LOCAL first-fit window (not global density) — steerable pin-clean;
  one pin on the top mask cascades the coalesce chain.**
- Residual 80 = 48 schedule + 32 schedule-coupled: sched1 backward-list ⊗ load-priority (S3) — the 8
  addPrim loads give chains priority+1, dominating LUID tie-break; cheap consts/subtracts float. "C
  cannot lower a load-fed priority." Needs Fable5 source-structure (like §36 bitfield decoupler did AF20).
- **§36 COUNTER-CASE (record):** bitfield-store P_TAG → 181 here (folds the dest-read; target KEEPS the
  read because addPrim's dest `*param_1`==word0 just set to 0x3000000 → user-mask is correct, NOT bitfield).

## func_801770E0 (152) — agent CLOSE=47 (count-exact, RC-6 exemplar); permuter (REGALLOC) failed → FABLE5 CANDIDATE
- 53→49: S2 birthing-boost via fresh single-set save vars (`void *u4,*u5`) — save sinks below arg-setup
  to just before the jal → dbr slots it, `li $a1,4` hoists (sched.md §S2, reproduced).
- **NEW §36 lever (49→47):** compute a high-ref const's CONSUMER into a block-local temp before a
  competing low-ref const's store, to force the high-ref const to materialize first (no added pseudo):
  `{ u32 v0m=((u32)(puVar3-5)&0xffffff)|0x3000000; puVar3[1]=0x6055ff00; *puVar3=v0m; }` pulls the 3-ref
  0xffffff mask's first-use ahead of 0x6055ff00 → mask (top allocno pri) materializes first (idx73-74).
  Generalizable to any high-pressure block where a high-ref 2-insn const must precede a low-ref one.
- Residual 47 = RC-6 pressure-lock (regalloc.md named exemplar) ⊗ S3. "every small edit moves 20+ insns"
  (the RC-6 tell). Agent route: permuter w/ `register u32 param_2 __asm__("$18")` anchor. My REGALLOC
  permuter (no anchor) failed. → Fable5 or anchored-permuter.

## func_80176D94 (152) — agent CLOSE=52 (count-exact); permuter failed → FABLE5(-source) CANDIDATE
- Root cause (byte-proven via `cc1 -dS` priority dumps): all 52 cascade from ONE schedule decision —
  the `lhu D_8011F82C ×0x50e6 magic → sw puVar3[3]` chain lands early (target) or sinks (mine).
  `flush_pending_lists` bars mem crossing a call → both tail reloads take REG_DEP_ANTI on the last
  `jal func_801777BC` → inherit pri 3; r3000 load-latency-2 makes the magic STORES pri 4 vs plain pri 3;
  the BACKWARD list scheduler emits highest-pri first (block bottom) → magic chains sink.
- **MUTUAL-EXCLUSION wall:** target needs the magic load LATE (fresh into $a0 in the tail, not crossing
  the calls → no 7th callee-save) but the store EARLY (pri 3, plain group); under gcc-2.7.2
  `store_pri == load_pri+1` with BOTH positions derived from that one number → source can't express both.
  9 variants floor at 52 or regress. NOT global-array-hoist ($s0–$s5 param/local-derived, alloc solved).
- **NEW levers:** (1) `const` on a post-call-reloaded global = RTX_UNCHANGING **priority PROBE** — strips
  the anti-call dep, drops the magic-store pri by 1; use to TEST if an S3 residual is a chain-sink (it
  byte-reproduced the target store order `[1],[2],[3],[5],[10],[6],[7],[b],[c],[8],[d]`, isolating the
  cause), even when not a usable fix. (2) **`/s` scalar-store sharpened:** `*ptr` (INDIRECT_REF) is
  non-`/s` and aliases global-symbol loads (spurious mem-dep); `ptr[0]` folds back to `*ptr` (still non-`/s`);
  only a struct-member `((struct{u32 w0;}*)ptr)->w0` (COMPONENT_REF @off 0) sets `/s`. Right tool for
  "global load stuck below a bare `*ptr` store."

## func_801372B0 (207) — agent CLOSE=8 (count-exact, ALL regs correct); → FABLE5 (schedule-wall) candidate
Drove 173→8. NOT global-hoist-class (D_800AF630→$s7, D_800A6518→$s5 hoists + 100% regalloc SOLVED);
residual = 8 insns, pure sched1/sched2 S3/S11 live-range ordering. Agent: permuter is low-ROI here
(fence-heavy pinned draft = tiny permutable space, matches perm 0/N record) → Fable5-source for the
sched1 live-range-shortening decision.
- **NEW levers (transfer to region-a siblings):**
  1. **Cross-BB base-offset split (173→81):** a hoisted `$sN` global base + small `+OFF` applied in a
     LATER BB stays a separate `addiu` (gcc-2.7.2 no cross-BB CSE): `register u8 *mat __asm__("$23")=D_x;
     if(...){ mat += 0x18; }`. **Tell: count-exact-MINUS-1 + huge mismatch = a folded base-offset on a
     hoisted $sN global base** (target keeps the `addiu` separate).
  2. **Pin post-`jal` struct-output loads to the target's exact scratch regs (81→35):** pinning
     `out.vx→$a3`, `out.vy→$v1/$v0` cascaded the throwaway store-constant rotation (0x78/0x10/-0x5A→$t0
     not $a3) FOR FREE — "scratch alloc follows the load allocation." **Tell: a systematic $a3↔$t0
     offset on store-constants is downstream of ONE mis-allocated post-call load sharing a scratch.**
  3. **§34 zero-byte identity-asm boost-defeat on store-value arith (35→9):** `{ s16 t=vx+K;
     __asm__("":"=r"(t):"0"(t)); prim.f=t; }` makes `t` multi-set → kills the birthing boost → the
     `vx+K` add stays at source position (before the call-arg chain) instead of sinking past it.
  4. **Boost-defeated call-arg local before an in-place last-use (9→8):** `GLINE *op=(GLINE*)&...;
     __asm__("":"=r"(op):"0"(op));` before `ay+=K` floats the a1-chain above the last-use.

## func_80178004 (165) — agent CLOSE=37 (count-exact, idx0-110 byte-exact); → FABLE5 candidate
Not §35 hard class ($s param/local-derived). Residual 37 = loop const-hoist⊗regalloc: the loop's two
2-insn invariant consts (0x74808080, 0x6d164000) each get a hoisted hard reg (ONE more persistent
const reg than the target) → shifts the whole $t-file. Target hoists only the split hi-half 0x6d160000→$t6
(ori 0x4000 folded in-loop) + RECOMPUTES 0x74808080 inline as a reorg.c branch-merge-duplicated lui
pair (delay-slot lui + fallthrough lui + shared ori), gated by exactly 0 free regs. Needs gdb-on-cc1 on
move_movables/reorg.c.
- **NEW levers:** (1) **`s16` (HImode) biv, NOT `s32`, when the counter is used only as `(short)x`** —
  an all-`(short)`-used SImode biv triggers gcc's shifted-biv substitution (`iVar4<<16`, cast→1 sra,
  in-place incr = 163 ins / 2 short); a HImode counter keeps it unshifted with per-use `sll;sra` + the
  2-insn opaque-copy increment (`addiu v0,a3,1; addu a3,v0,$0`) = exact. Clean cookbook entry, the
  "count-exact-minus-2 on a counter-derived loop" tell. (2) **prologue CSE-const pins in DECL order
  (73→38):** mips has NO REG_ALLOC_ORDER (numeric first-fit); 1-ref short-live 4th-word consts have
  HIGHER local-alloc density (`fl2(nrefs)*nrefs/live_len`) than a 6-ref mask → steal $a0. Pin the
  invariants low + materialize the short-live const FIRST (register-var initializer order = entry emit
  order) → reproduces the target reg order, cascades the rest. (3) puVar3→$a0 + q→$a1 pins collapse 3
  q-stores onto one base (−8/−4/0), kills the giv-split (§35 dest-off-base). (4) $0-add opaque copies (§36).

## func_80148094 (213) — agent CLOSE=72 (count-exact); PERMUTER-REACHABLE (iterated local search) → 36
Mixed verdict: Fable5-class as a HAND-wall (no C construct forces global `fac` pseudo-79 to win $a0 over
the local `param2c` load in local-alloc — local-alloc runs BEFORE global-alloc so the local wins first-fit
$a0; target is reverse), but NOT a hard wall — **permuter-REACHABLE** (72→36 descending).
- **HEADLINE NEW LEVER — PERMUTER ITERATED LOCAL SEARCH (build as a tool):** a single COLD `run_masked`
  plateaus at base (72) over ~10k iters, but **warm-restarting base.c from the best byte-waypoint each
  cycle (fresh `-j12`, `--klass regalloc`) descends 72→62→53→49→45→36 over ~8 restarts.** Big drops come
  from FRESH restarts, not continuing a plateaued run. Reusable for ANY count-exact regalloc/schedule
  residual where cold-permuter stalls (i.e. most of this batch). ⚠ waypoints can be SEMANTICALLY
  DIVERGENT (permuter drops/rewrites stores for byte-proximity) — only a score-0 hit is a valid bank.
- **gdb-on-cc1 register forensics:** break `global_alloc`,`finish`; deref `*(short**)0x082d4330`
  (`reg_renumber`) + read `.greg` `;; N conflicts:` sets → pinpoints WHICH pseudo stole your target reg
  (here 183=$a0 blocks 79). "Who took the register I wanted" in minutes.
- **Negative results (don't re-try):** `register __asm__("$4")` on fac (+7), §34 density dummy (+7),
  §36 $0-opaque (folds), decoy-qty (0), keepalive (0), block-layout reorder to target bnez/slti shape
  (+3 — layout is NOT the lever), explicit param2c temp (+6 over-holds).

## 🐋 func_80144B9C WHALE (770) — agent CLOSE=2 (768/770); ⚠ IT'S -O0, NOT -O2 — special track
**CRITICAL STRUCTURAL FINDING:** func_80144B9C is an **-O0** function (prologue sig `21F0A003` = `$fp`
frame pointer; same-slot triple-reloads; unfilled load-delay nops). -O0 compile → **768/770 (close=2)**;
-O2 match_one → only 458/770 (proves -O0). It sits at 0x80144B9C, ABOVE the known -O0 cluster
(`ov_SC01_077_o0.c` 0x8013B568..0x8013C98C) → a **SECOND -O0 region stranded in the -O2 "after" segment.**
- **BANK BLOCKER (orchestrator action, mine):** `ov_SC01_077` needs a **second per-file -O0 split** for
  the 0x80144B9C region (same Makefile `CC1FLAGS := -O0` mechanism as `ov_SC01_077_o0.o`). Standard
  match_one (-O2) CANNOT verify/bank it. Agent built an -O0 match clone: `.run/t7b/work/func_80144B9C/match_o0.py`
  (reusable for any -O0 fn in this region). Deliverable draft: `.run/t7b/close/func_80144B9C.c`.
- **RESIDUAL (2 insns):** `func_8005C324` **IS memcpy** (`config/symbols.proto-sep8.txt: memcpy=0x8005C324`).
  target precomputes `dst→$v1`,`src→$v0` then `addu $a0,$v1 / addu $a1,$v0`; mine emits direct (`la;lw`).
  gcc-2.7.2 -O0 arg-precompute in **`calls.c` — NOT in `tools/reference/gcc-2.7.2/` (only 2.8.1 there)**;
  resolving needs that source (FETCH gcc-2.7.2 calls.c). Exhaustively not C-form-reproducible.
- **NEW -O0 IDIOM SET (cookbook — first -O0 giant idioms):**
  1. **-O0 detection:** prologue `21F0A003` + same-slot triple-reloads + unfilled nops ⇒ compile -O0.
  2. **Struct-member fold (860→91):** at -O0 `struct->field` folds to `lw off(reg)`, but `*(T*)(base+const)`
     AND array `b[k]` each materialize an extra `addu` → ALL bases must be struct pointers w/ exact-offset
     padded structs; a pointer-to-struct field (`p10->f20->f12`) where a double-deref folds.
  3. **Far-global $s0 base:** `register u8 *p = D_800AF630;` held across calls (boot.c precedent);
     `*(s16*)(p+0xA3D8)` auto-splits `+0x10000/-0x5Cxx`.
  4. **`i++` not `i=i+1`** for the loop counter (91→29): `i++` emits the target's extra `addu $v0,$v1,$zero`
     copy before `sh`; `i=i+1` omits it.
  5. **Branch polarity off the opcode** (full-init in the fall-through arm → `bnez ...,else`).
  6. **Chained multi-store** `a->x=a->y=a->z=SRC;` = the -O0 one-load/three-store camera-setup blocks.
- **-O0 SPLIT SCOPING (2026-07-07 recon):** whale span = **0x80144B9C..0x801457A4** (0xC08). Mechanism =
  splat subsegment (`config/splat.ov_SC01_077.yaml:53-62`) + Makefile per-file `CC1FLAGS := -O0` on the
  `_o0` .o (`Makefile:442-445`). ⚠ **RISK/DELICACY:** the whale sits in the `[0x14834, c, ov_SC01_077]`
  -O2-"after" subseg which ALREADY holds banked C (func_801571C4 def + many `DEFINE_` macros). Carving an
  -O0 subseg out of it re-splits that file → must NOT lose the banked C (splat regen behavior on existing
  hand-edited .c needs verifying; commit first). Also -O0 fns are SCATTERED here (80140958, whale, 801457A4,
  8014DD8C, 8014E284 — verify each's `addu $fp,$sp,$zero`), so future -O0 banks need more subsegs. For the
  whale ALONE: one -O0 subseg [0x1CA44..0x1D64C] with the rest staying INCLUDE_ASM (opt-agnostic). Fetch
  gcc-2.7.2 `calls.c` (ftp.gnu.org reachable; find the correct release path — .tar.gz 404'd). **DEDICATED
  focused task — do NOT rush inside the Fable5-chain juggle.**

## ✅ func_8014EA4C — FABLE5 MATCH (183 ins), banked ×1 (2026-07-07) — the 1st Fable5 crack
Zero pins, pure source structure. **METHOD UPGRADES (fold into cookbook + all future Fable5):**
- **SIBLING-GREP shortcut:** the pre-call idiom was already solved in banked `DEFINE_func_8014EE14`
  (engine_core.h:24926 [repo]). Grep src/ for the idiom (symbol+callee) BEFORE cc1. C1+C2 fell in 1 edit each.
- **⚠ RTL DUMPS ARE NOT STRIPPED** (§34 correction): pinned cc1 with `-dr -dj -dc -dl -dg` emits full
  `.rtl/.jump/.combine/.lreg/.greg` — readable ground truth before gdb. Upgrades every future run.
- **LEVER — C1 `/s`-flag COMPONENT_REF arg read:** an arg/operand load with a ZERO pointer offset that
  must cross a fixed-symbol store needs `((struct{s32 w;}*)q)->w` (COMPONENT_REF → `/s`=MEM_IN_STRUCT_P →
  `sched.c:817 [2.7.2] true_dependence` lets it hoist); `q[0]` front-end-folds the +0 → plain MEM → spurious
  true-dep → pinned below the store. NONZERO offsets cross free. This is the LOAD-side mirror of
  func_80176D94's store-side `/s` lever — same flag, both directions proven. (`expr.c:4568 [2.7.2]` case INDIRECT_REF.)
- **LEVER — C2 s32-abs, `(s16)` cast at the USE:** `s32 t=..; if(t<0)t=-t; if(0x800<(s16)t)` → `negu $2,$2`
  in place; a NARROW `s16 t` gives `move $3,$2; negu $3` (HImode neg into a fresh pseudo + subreg truncate).
  Rule: `negu rX,rX` in place = word-sized abs var + narrowing cast at the use; move+negu pair = narrow var.
- **LEVER (headline) — PHANTOM-SLOT PARITY:** frame-parity residuals on s16-heavy fns = uncounted stack
  slots from label-headed orphaned extend-intermediates (`combine.c:10829 [2.7.2]` parks a REG_DEAD note on a bare
  `(use (reg))` at a CODE_LABEL → regclass sees no constraint → `alter_reg` gives a stack slot: +8 bytes,
  0 insns). **Count `(use (reg:SI` in `.combine`.** Locals size = declared aggregates + 8×phantom-count.
  The §34 toolkit ISN'T unavailable on such fns — trade a phantom for 8 buffer bytes freely (`buf[16]→buf[24]`
  repaid the −8 from switching s16→s32). Corrects the close-draft's "OOB memcpy is the only 0x60" belief.
- Bank note: reconcile `D_80126720` → canonical `extern u8 D_80126720[]` + `*(s16*)` read (reconcile_decls
  did it; byte-identical). Sibling macro ⇒ possible engine-core dedup candidate.

## ✅ func_801372B0 — FABLE5 MATCH (207), banked ×1 (asm-label-alias bank) — 3rd crack
- **Lever A (S2-kill on single-set PINNED vars):** `birthing_insn_p` (sched.c:2469 [2.7.2]) boosts single-set REG
  dests INCLUDING register-asm hard regs (corrects the "non-boosted pinned const" briefing). A post-use
  re-tie `__asm__("":"=r"(v):"0"(v))` → `reg_n_sets==2` → no boost → source order. In an in-place-update
  pinned pair (`ax=ay+K; … ay+=K'`) the fresh single-set half boost-glues above the in-place half; the
  re-tie restores source order. 8→2.
- **Lever B (NEW CLASS — S2 fire-tick via CONSUMER STORE ORDER):** a boosted const lands directly above
  its last-backward-picked consumer; among equal-pri independent stores the backward cascade picks
  highest-LUID first. Reorder the consumer stores to shift the const's fire-tick (`[attr,r,g,b,x0,y0]` vs
  `[x0,attr,…]` slips the 255-`li` slot). sched2 re-normalizes the final store layout identically → the
  only byte effect is the boosted li's slot. 2→0.
- **METHOD (key refinement): "model to close=2 by hand, THEN directed-permuter the tiny residual."** The
  permuter found Lever B at iteration 291 on the close=2 draft; the "permuter low-ROI" verdict was only
  true at close=8. Apply to the rest of the chain.
- **BANKING INSIGHT — ASM-LABEL ALIAS (flywheel / reconcile_decls-fix candidate):** a `_a`-split giant's
  externs can conflict with SIBLING `DEFINE_` macro decls in the same TU (here `GsSortLine`/`func_80137030`/
  `D_800B9A02`, the last a signedness `short`-vs-`u16` mismatch). reconcile's `*(u16*)&D_x` cast avoids the
  conflict but the ADDRESS-OF perturbs regalloc (aliasing → `$s6↔$fp` swap, 13-off). **Fix: an asm-label
  alias — a distinct identifier of the NEEDED type bound to the linker symbol:** `extern u16 aD800B9A02
  __asm__("D_800B9A02");` + use `aD800B9A02` (direct `lhu`, no address-of, no conflict); same for proto
  conflicts (`extern void aGsSortLine(...) __asm__("GsSortLine");`). Banked 372B0 byte-identical. →
  **reconcile_decls should emit asm-label aliases for signedness/proto conflicts, not perturbing casts.**

## ⛔ func_80178004 — FABLE5 CLOSE=7 (from 37), NOT a match — genuine biv-init wall; stays INCLUDE_ASM
Drove 37→7 (count-exact, ALL registers correct); last 7 = a compiler-internal biv-init EMIT-ORDER
barrier: the two-base store split (puVar3=$a0 off-0; q=$a1 off 4/8/12 as −8/−4/0) forces q a separate
biv, and "separate base AND late init" is not co-reachable from C — q pinned → init is an early-LUID
source stmt (emits before the movables); q as giv → the −8/−4/0 offsets fold into the `sw` so
`emit_iv_add_mult` gets ELIMINATED (benefit→0, loop.c:3803 [2.7.2]/3823) → one base, −1 insn. Permuter plateaus
at 5 via semantically-divergent waypoints. → INCLUDE_ASM (or a per-fn `_o0`-style split TU to host a
scheduling hack — heavy, declined for now). Draft `.run/t7b/close/func_80178004.c`.
- **LEVER 1 (NEW, headline, BANKABLE, broadly applicable → §36):** the **coalescable-copy insn_count
  bump.** When the whole `$t`-file is shifted by ONE extra-hoisted loop const, `move_movables`' hoist
  threshold `2*(1+n_non_fixed_regs)` (decays −3/hoist, loop.c:1717 [2.7.2]/1904) is sitting at its `>=` boundary
  (`43>=43` TRUE → the 6th const grabs a persistent reg). Nudge `insn_count +1` with ONE coalescable copy
  `{ u32 m2 = uVar6; q[-1] = m2 | …; }` → `43>=44` FALSE → hoist REFUSED (gdb: reg "not desirable"), and
  combine/regalloc coalesce `m2`→$s0 = **zero final bytes**. This is the FUNCTION-LOCAL, BANKABLE
  equivalent of a global-register-var (which works but is TU-wide → NEVER bankable in a shared overlay TU).
  **Rule: whole-$t-file shifted by one hoisted const ⇒ move_movables threshold at its `>=` boundary ⇒
  a coalescable copy refuses the hoist.**
- Lever 2 (hi hoist-reg via live-length: assign the hi-half at loop TOP so allocno_compare sorts it
  longest-lived → first-fit target reg; split `hi | (x|0x4000)` with the ori folded in-loop). Lever 3
  (uVar2 delay-slot copy via raw/copy split `u32 s=srl; uVar2=s+zr; if(s!=0||…)` — compare reads raw, +zr
  fills the branch delay).

## ✅ func_801770E0 — FABLE5 MATCH (152), banked ×1 — the RC-6 EXEMPLAR DOWNGRADED (47→0, no permuter/gdb)
**Meta (updates the §31 map):** the "RC-6 pressure-lock ⊗ S3" 47-residual was a **missing memory-dependence
LATTICE (a wrong dep GRAPH), not an unsteerable allocation.** Restore the lattice → all register "mirrors"
resolve themselves + every edit becomes local/monotone. The "every edit moves 20+ insns" tell was ~40
dep-free insns re-floating. **Audit "RC-6 unsteerable" verdicts — check the dep graph first.**
- **LEVER (headline, structural, 47→12; zero bytes) — the `/s`-LOAD DEP LATTICE:** `expr.c` marks
  INDIRECT_REF-of-PLUS as `MEM_IN_STRUCT_P` — `p[k]` (k≠0) stores are `mem/s`, bare `*p` is not.
  `sched.c:829-907 [2.7.2]` DROPS a store↔load conflict when one side is /s+varying(+!QI) and the other
  non-/s+fixed → plain `lhu D_global` never orders against `puVar3[k]` stores → global loads float, tail
  schedule collapses. **Fix: load the global as a struct-member-at-offset-0** —
  `((struct { u16 h; } *)&D_8011F830)->h` — COMPONENT_REF sets `/s` on the LOAD → both exception clauses
  fail → every store↔load pair conflicts → **tail order becomes source statement order partitioned around
  the loads.** The **load-side DUAL of 76D94's store-side `/s`** — apply DIRECTLY to 76D94. Tell: *a global
  scalar load sits far from its source position, crossing pointer stores, 20+ placement diffs.*
- **LEVER — the const-register PIN cascades store order:** "one const's register + one store's position
  wrong, schedule levers cascade" ⇒ store order is DOWNSTREAM of the const's register via sched2 hard-reg
  anti-webs → pin the const to the target's reg (`register u32 c __asm__("$6")=…`) → the stores re-place free.
- **LEVER — CSE-dodge WITHOUT a barrier:** head `(u16)param_2` (zero_extend RTL) vs tail `param_2 & 0xffff`
  (AND RTL) hash differently in cse → no cross-call CSE → no 7th callee-save. **Replaces volatile-asm re-ties**
  — which per sched.c ASM_OPERANDS are a FULL scheduling barrier (they were warping the tail). Prefer this.
- Multi-set load var (both `lhu`s in one 2-set `u32 dl` → kills the birthing boost → loads stay at source
  pos); decl-order LUID (C89 decl-init order = emission order → materialize below the pinned lui/ori).

## ✅ func_80176D94 — FABLE5 MATCH (152), banked ×1 — ONE-SHOT via SIBLING-ISOMORPHISM (~15 min)
- **ISOMORPHIC-SIBLING LAW (headline; MANDATORY step-0 for every remaining giant):** 76D94 is
  instruction-isomorphic to the banked **770E0** — a mnemonic diff of the two target `.s` shows ONLY 11
  immediate/symbol differences. Ported 770E0's banked source verbatim + the 11 substitutions → one-shot
  MATCH. GPU-packet/addPrim builders come in FAMILIES. Before deep work: `grep -oP '\*/\s+\K\S+' target.s`
  → diff the mnemonic sequence vs already-MATCHED siblings; an immediates-only diff ⇒ port + constant-swap.
- **"Mutual-exclusion" is a TELL, not a verdict** (confirmed): "X early AND late, coupled through one
  priority number" = a MISSING dep edge (the /s lattice) — real only in the broken graph. Store-side (76D94)
  and load-side (770E0) presentations, one fix.
- **gcc-2.7.2 scheduler algebra (byte-relevant):** `priority = max over deps of (priority(dep)+insn_cost(dep)−1)`;
  **`insn_cost` is DEP-KIND-BLIND in 2.7.2** (no REG_DEP_ANTI zero-case, unlike ≥2.8) → an anti-dep of a
  latency-2 load gets +1 priority → restoring `/s` anti edges RE-GROUPS downstream stores up one priority level.
- **BANKING INSIGHT (isomorphic siblings → gate_stage/reconcile-fix candidate):** a ported sibling shares
  its helper struct + canonical callee decls with the already-banked original. TWO collisions to fix by hand
  (gate_stage returned all-zero / harvest failed): **(a) canonical call-cast** — the callee is already
  declared 4-arg in the TU from the first bank → declare it canonically + cast the call site
  `((void*(*)(void*,s32,s32))func_80177784)(…)`, don't re-declare it 3-arg; **(b) anonymize the shared
  `/s`-cast struct** — `struct hs { u16 h; };` collides with the first bank's def → inline it
  `((struct { u16 h; } *)&D_x)->h`. Banked byte-identical. (Same family as the 372B0 asm-label-alias fix.)

## ⛔ func_801412A8 — FABLE5 CLOSE=29 (from 80), NOT a match — allocation placement knot; stays INCLUDE_ASM
Drove 80→29 (count-exact). Residual 29 = ONE placement knot (window-1's pm-and + copy float to idx 43-45;
no dependence ceiling exists, boost unavailable reg_n_sets[$3]=5). Finish needs a pin-free reconstruction
with the complete reuse-set (~10-20 more joint byte-gated experiments after dropping the pins) — deferred.
Permuter reached 26 only via an ILLEGAL mutation (reads a pin before its set) — not bankable. Draft
`.run/t7b/close/func_801412A8.c`; 48 experiments + gdb qty traces in `.run/t7b/fable/412A8/`.
- **LEVER — the qty_compare 2500-TIE is the real root of "S3 walls" (-39):** gdb `find_free_reg`: two
  temps at EXACTLY equal `qty_compare` priority (link {3 refs/len 12}=2500 vs and-temp {2 refs/len 8}=2500)
  → tie broken by qty NUMBER = block-scan order → the loser cascades the whole $t-file rotation + store
  order. A window-temp pin (or inline reuse taking a dying reg via `qty_phys_sugg`) flips the tie → dozens
  of diffs collapse. **Audit "schedule" residuals for an equal-priority qty tie FIRST (gdb find_free_reg).**
- **LEVER — multi-death block-var law (`local-alloc.c:472 [2.7.2]`):** a block-local with `reg_n_deaths != 1` is
  REJECTED by local-alloc → becomes a GLOBAL allocno → alloc chaos. Use one-statement fresh-per-window
  single-death locals (`o = OTLINK; o[2]=…` = 4 deaths → split them).
- **LEVER — dead-variable reuse = the register oracle:** the target's "impossible" register choices are
  Ghidra-style variable REUSE through the global-allocno path (e.g. `iVar1=(u16)*idxp` through the dead
  divisor puts the lhu in $a0), NOT pins — unreachable by local-alloc steering; reconstruct the reuse.
- **LEVER — new RC-5 channel (pin-set float):** an UNBOOSTED pin-set with ancient inputs (hard-regno
  multi-set → birthing_insn_p fails) floats to block top → its hard-reg range crosses disjoint globals →
  `hard_reg_conflicts` EVICTION. Corollary: input-only asm dummies (no dependents) go to block END —
  can't fence from below in a big block (matches 78004's finding).
- **SCOPE NOTE — the `/s`-dep-lattice lever is INAPPLICABLE when all mem ops are register-addressed:**
  `sched.c:820-865 [2.7.2]` drop clause needs one side /s+varying AND the other **non-/s + FIXED-address**; if
  every mem op is register-addressed (varying), all edges already exist → /s changes nothing. (770E0/76D94
  had FIXED-address `D_global` loads; 412A8 does not.)

## ✅ func_80148094 — FABLE5 MATCH (213), banked ×1 — cracked from RTL dumps alone (no gdb, no permuter)
Root cause (corrects the close-draft): NOT local-alloc first-fit — a global-alloc **`allocno_compare`
NEAR-TIE** (`global.c:588 [2.7.2]`: `pri = floor_log2(refs)*refs/live_length*10000*size`): fac (pseudo-79, 7refs/33)
= 4242 vs the arm-local p2c (pseudo-183, 3refs/7) = 4285 → 183 allocated first, its preferences {4,5}
(`set_preference` unwrap rule) pref-take $a0, push fac→$a1. **Preference beats first-fit** — explains the
target's "impossible" `lw $a1,0x2C` skipping free $v1.
- **L1 (NEW §36) — allocno-priority ref-boost, placement-critical:** `__asm__("" :: "r"(v));` at the TOP of
  a block where `v` is ALREADY live-through → +1 flow-time ref, ZERO live-range extension, zero bytes; refs
  7→8 crosses the `floor_log2` step (2→3) → priority 4242→~7058 > 4285 → v wins the reg. **Rule: when a
  long-lived global loses a reg to a short block temp, compute both `floor_log2(refs)*refs/length` products
  from `.lreg`'s "used N times across L insns" rows — one dummy ref usually crosses a log2 step.** (The prior
  agent's "+7 failure" was def-site placement + L2's effect, not live-range blowup — placement is critical.)
- **L2 (NEW §36) — cross-jump fall-through law:** `jump.c` cross-jump extends a tail-merge backward only
  while the jumping tail matches the PHYSICAL fall-through predecessor of the exit → order the arms so the
  shared suffix forms the target's `.L` labels (here the `==0x200` arm must be LAST). **Corollary: a correct
  reg-fix that "costs +N ins" may just have un-merged tails the target ALSO keeps separate — pair it with the
  layout lever, don't revert.**
- **L3 — delay-fill store order** (`out[0]=load; out[1]=0;` — sched2 fills the load delay with the zero-store).
- Confirmed **/s SCOPE NOTE** (all mem register-addressed → /s inapplicable). Method: `-da` RTL dumps
  (`.greg` alloc order/conflicts/preferences + `.lreg` refs/length) gave the full mechanism — no gdb.

## ── BATCH-CLOSE PROPAGATION PLAN (dry-run 2026-07-07: 3/5 clean, 2 need self-containment fixes) ──
`dedup_propagate --addr 0x801571C4,0x8014EA4C,0x801372B0,0x801770E0,0x80176D94 --check-only` →
**3 propagate ×134 clean** (571C4, EA4C, 76D94 — each 134 members); **2 skipped "not self-contained
(local types)":**
- **func_801372B0**: local `typedef struct {…} SVEC;` + `typedef struct {…} GLINE;` NOT in engine_types.h
  → dedup_propagate `compiles_standalone` (includes only common.h + engine_types.h) rejects. **FIX: LIFT
  SVEC + GLINE to `src/shared/engine_types.h`** (§28b; they're PsyQ GTE/GPU types future giants reuse) +
  remove the local typedefs from 372B0's def. Byte-neutral → re-verify ov_SC01_077 == d19c9580.
- **func_801770E0**: named `struct hs { u16 h; };` local /s-cast helper → same reject. **FIX: anonymize it**
  (`((struct { u16 h; } *)&D_x)->h`, exactly as 76D94's banked form) OR lift `struct hs`. Byte-neutral.
**AT CLOSE:** apply both fixes → re-verify byte-identical → `dedup_propagate --addr <all matched> --recover`
(the 5 + 48094 if cracked) → clean-verify 136/136 → commit. (Whale is separate: needs its -O0 split first.)

## ── FABLE5 BATCH (Drew authorized full, closest-first sequential + idiom-banking) ──
EA4C(6, C1/C2+frame-knife-edge) · 372B0(8, sched1 live-range) · 80178004(37, const-hoist⊗regalloc) ·
770E0(47, RC-6) · 76D94(52, S3 chain-sink mutual-excl) · 48094(72, local-vs-global $a0 tie / ALSO
permuter-ILS-reachable) · 412A8(80, S3 load-priority). All need gdb-on-cc1 depth (empty shipped
.sched/.greg) — the §34/§36 Fable5-source method. **Parallel cheap attack: warm-restart ILS permuters
on the permuter-reachable ones (48094 proven) while Fable5 works the chain.**
