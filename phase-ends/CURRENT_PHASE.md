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
  - [x] **libetc** (5 objs, 35 fns) — clean single block at 800-tail; 5/5 byte-verified; dual byte-gate PASS (with+without); LINKED 340→375; no symbols.us.txt change needed. **(progress report #2)**
  - [ ] libgpu · libmcrd · libc2 · libcard · libapi · libspu · libsnd · libgte
- [ ] **T(N+1)** — Deferred-library hard-case documentation (honest stub deferrals, structured comments, worklist notes). *(xHigh)*
- [ ] **T(N+2)** — Game-code harvest (read cookbook+§5.4 first; sig-refresh → difficulty.md regen → cheap non-jtbl game leaves; bank, don't exhaust). *(xHigh; optional breadth)* **→ report #4**
- [ ] **T(N+3)** — Headers (`include/psyq/*.h`) + cookbook §9 flywheel (R16) + SETUP/memory-map refresh (R21). *(xHigh)*
- [ ] **T(N+4)** — Phase 8 close: verify checkboxes (P7) → demo milestone → Drew confirms (gate 2) → PhaseEnd_Phase8.md + archive worklog (R19) + commit + Ghidra push (R20) + plain-English recap (R18) + hard stop (P8). *(Tier-1 Max)*

## Current task pointer
**T4 — Integrate libgpu** (3 contiguous objs EXT/PRIM/SYS @0x80058890, 800b2; split 800b2 into pre+libgpu+post). libetc proved the per-library mechanism end-to-end.

## Progress log
- **2026-06-15 (session A, planning):** Read PROJECT_CONTEXT + all PhaseEnds + effort-map + gen2-roadmap. Byte-grounded the Phase-8 scope (R14): harvest is ~90% library objects; progress.py counts linked libs as stubs; machinery ready (20 `.LIB`s, 14 `.a`, 14 built `.run/obj40/*` dirs). Two owner decisions taken (LINKED category; full ceiling). Plan approved (gate 1). **T0 done** — this file written.
- **2026-06-15 (session A, exec):** Baseline confirmed byte-identical (143dbb89). **T1 done** — `psyq_identify` survey → `docs/psyq-worklist.md` (9 footprint libs / 199 placements ranked; 3 skip). **T2 done** — progress.py LINKED category (340 fns; byte-identical 20.31%; build unchanged). Built the 16-task monitor list. Committed T1+T2 foundation checkpoint.

## Blockers
- None.
