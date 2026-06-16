# CURRENT PHASE — Phase 8: Finish the EXE — remaining PsyQ libraries + final harvest

> **Gen2, Phase 8** (first Gen2 phase). **Plan APPROVED by Drew 2026-06-15** (gate 1 passed).
> Full plan: `/home/musashi/.claude/plans/plan-mode-enabled-max-wobbly-manatee.md` (mirrored here as the in-repo crash-recovery log, P3).
> **Execution effort:** xHigh default; conditional Max if a library fights past cookbook §9; Max for the PhaseEnd.
> **Owner decisions (2026-06-15):** progress metric = **add a LINKED category to progress.py**; exit bar = **full matching ceiling** (link every footprint-confirmed library; defer any that fight as honest documented stubs).
> **Commit cadence:** per-session/per-task checkpoints, commit + (Drew) push irreplaceable work (R20, loosens R8).

## Goal / milestone (byte-checkable gate)
1. `make clean && extract && build && check` → SHA1 `143dbb89…` byte-identical **with** all newly-linked SDK objects AND **without** them (`.run/obj40/` absent → stub fallback) — both green.
2. `make report` shows REAL / **LINKED** / NON_MATCHING / stubs; LINKED grown by the newly-linked objects, stubs reduced accordingly, REAL up by the harvested game leaves; deterministic.
3. **0 NON_MATCHING in the default build** preserved (G4).
4. Every footprint-confirmed library is linked OR documented as an honest deferral (`docs/psyq-worklist.md`) — no silent gaps (P9).
5. `git status` shows zero ROM-derived/generated bulk staged.

## Tasks
- [x] **T0** — Write this `CURRENT_PHASE.md` (kickoff). *(Tier-3)*
- [x] **T1** — Library placement survey + worklist → `docs/psyq-worklist.md`. **DONE:** 9 footprint libs (libgpu/libetc/libmcrd/libc2/libcard/libapi/libspu/libsnd/libgte = 199 placements) ranked ascending-difficulty; 3 SKIP (libmath/libc/libsn = 0 footprint); key findings: libgs "gaps" gsgap1/2/4/5 are libgte; heavy interleaving (800=game+libspu+libsnd+libetc, 800b≈libgte, 800b2=game+libgpu/libc2/libapi/libmcrd/libcard); cross-lib aliases (C112, UT_RON/S_IH, S_R/S_W).
- [x] **T2** — `progress.py` LINKED category. **DONE:** linked subsegs sourced from the Makefile's `psyq_integrate` calls (single source of truth, auto-updates per integration); libcd+libgs **340** stubs→LINKED; byte-identical/matchable now **425/2093 = 20.31%**; build unchanged (143dbb89).
- [~] **T3…N** — Per-library integrate, ascending difficulty (resegment splat → trim src → Makefile gated psyq_integrate + `-T` syms → dual byte-gate → report → commit). *(xHigh; Max-escalate if a lib fights)* **→ report #2 after first lib lands; #3 when last placed lib done**
  - [x] **libetc** (5 objs, 35 fns) — clean single block at 800-tail; 5/5 byte-verified; dual byte-gate PASS; LINKED 340→375. **(progress report #2)**
  - [x] **libgpu** (EXT+PRIM, 2 objs / +49 fns; curated `libgpu_used`) — dual byte-gate PASS; LINKED 375→424. **SYS.o EXCLUDED** = scattered-`.bss` §9.1 (GS_001 class), documented in worklist, stays a stub in 800c. Split 800b2→[800b2][libgpu][800c]. First hard case handled.
  - [x] **libmcrd** (2 objs / +104 fns) — clean (27 `.bss` commons all recovered); 2 non-adjacent blocks (libmcrd1/libmcrd2) splitting 800c; dual byte-gate PASS; LINKED 424→528.
  - [x] **libc2** (17 objs / +62 fns) — C stdlib, 2 blocks (16-obj main libc2_1 + STRCAT libc2_2; PRNT jtbl OK). Hit + fixed the **boundary gotcha**: SETJMP.o `.text`=0x80 (8-align pad) not 0x78 → 800c3 boundary was 8 low → +8 global shift; fixed to 0x5CE18. Lesson recorded in worklist. dual byte-gate PASS; LINKED 528→590.
  - [x] **libgte** (53/58 objs / +120 fns; 22 blocks) — reordered value-first. Built `tools/gen_lib_subsegs.py` (generates multi-block subseg lines w/ section-size boundaries) + integrate window. progress.py now resolves `$(VAR)` stub lists. 5 libgs-gap objects DEFERRED. dual byte-gate PASS; LINKED 590→710, byte-identical **37.93%**.
  - [x] **libspu+libsnd COMBINED sound region** (60/70 objs / +225 fns; 9 blocks) — the two libs interleave so linked as ONE region. New `tools/make_snd_used.py` (alias dedup by byte-match + exclude-by-address). 4 addresses excluded (scattered-`.bss`/false-pos: S_R/S_GRMDT/S_IH/VM_F), SSGM deferred. All matched C preserved (trim kept 732 < 0x3A444). dual byte-gate PASS; LINKED 710→935, byte-identical **48.66%**.
  - [x] **libapi+libcard COMBINED 800c2 region** (22 objs / +24 fns; 4 blocks; `tools/make_apicard_used.py`, 0 exclusions) — dual byte-gate PASS; LINKED 935→959, byte-identical **49.81%**. libapi's 800c3 remnant (~22 objs) DEFERRED.
  - **LIBRARY CEILING REACHED** — 8 libs linked (959 LINKED fns); remaining are documented low-value deferrals (worklist).
- [ ] **T(N+1)** — Deferred-library hard-case documentation (honest stub deferrals, structured comments, worklist notes). *(xHigh)*
- [ ] **T(N+2)** — Game-code harvest (read cookbook+§5.4 first; sig-refresh → difficulty.md regen → cheap non-jtbl game leaves; bank, don't exhaust). *(xHigh; optional breadth)* **→ report #4**
- [ ] **T(N+3)** — Headers (`include/psyq/*.h`) + cookbook §9 flywheel (R16) + SETUP/memory-map refresh (R21). *(xHigh)*
- [ ] **T(N+4)** — Phase 8 close: verify checkboxes (P7) → demo milestone → Drew confirms (gate 2) → PhaseEnd_Phase8.md + archive worklog (R19) + commit + Ghidra push (R20) + plain-English recap (R18) + hard stop (P8). *(Tier-1 Max)*

## Current task pointer
**T14 — cookbook flywheel** (update §9 with Phase-8 lessons: gen_lib_subsegs + section-size boundary gotcha, combined-region for interleaved libs, scattered-`.bss` cross-object exclusion, the incremental-`.ld` clean-rebuild gotcha). Then **T15 — present the Phase 8 milestone to Drew (gate 2)**; PhaseEnd only after Drew confirms.

**T13 game-code harvest DONE:** 9 trivial game-code accessors matched (func_8002AEF8/AF08/AF60, func_8002D4B8/D7FC/D834, func_8002F648, func_80037358/37CC8 — getters/setters of D_* globals, byte-verified). REAL 43→52. (Gotcha found: matching changes need `make clean` rebuild — the incremental psyq_integrate `.ld` rewrite can go stale.) sig-refresh deferred (needs Ghidra stopped; difficulty.md regenerates next session).

## Progress log
- **2026-06-15 (session A, planning):** Read PROJECT_CONTEXT + all PhaseEnds + effort-map + gen2-roadmap. Byte-grounded the Phase-8 scope (R14): harvest is ~90% library objects; progress.py counts linked libs as stubs; machinery ready (20 `.LIB`s, 14 `.a`, 14 built `.run/obj40/*` dirs). Two owner decisions taken (LINKED category; full ceiling). Plan approved (gate 1). **T0 done** — this file written.
- **2026-06-15 (session A, exec):** Baseline confirmed byte-identical (143dbb89). **T1 done** — `psyq_identify` survey → `docs/psyq-worklist.md` (9 footprint libs / 199 placements ranked; 3 skip). **T2 done** — progress.py LINKED category (340 fns; byte-identical 20.31%; build unchanged). Built the 16-task monitor list. Committed T1+T2 foundation checkpoint.

## Blockers
- None.
