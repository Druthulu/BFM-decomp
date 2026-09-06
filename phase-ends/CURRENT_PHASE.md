# CURRENT_PHASE — Phase 32: the last 21 + the parked 5 (short, kill-gated)

> **Gate 1 approved 2026-09-05 (Drew, plan mode, Max, Fable 5.1).** Rules R44–R63 ratified at gate 1 (binding).
> The approved plan (full text): `~/.claude/plans/plan-mode-enabled-max-iterative-ember.md` — its substance is
> this file. Jumping-off document: `docs/frontier-p32.md`. Roadmap: `docs/roadmap-to-100.md` v2 §3 (P32 as
> written is consumed; P32 is this census) + `PhaseEnd_Phase31.md` Roadmap delta.
> **Baseline HEAD at open: `commit:3900`** (Phase-31 close + post-close docs; no `src/`/`config/` change since the
> S80 census — verified `git diff commit:3898..HEAD -- src config Makefile` empty).

## Milestone (gate 2)
Every one of the 21 census rows is **BANKED** or carries a **FINAL verdict** (PROVED wall / candidate wall with a
gcc-mechanism citation + a bounded-attempt record / deferred with its cost stated); each of the 5 parked payloads
is **onboarded byte-identical at a byte-proven base** (its stubs then join the census and are banked or ledgered
the same way) **or** carries a documented exclusion with the static + runtime evidence; the fleet is byte-identical
(R22) at every banked batch; the PhaseEnd carries the final wall ledger, the corrected denominators (main game-code
41,556 — the 22-ins Ghidra-boundary gap), all three metrics, and the roadmap delta (P33 = verify + flip).

**Kill gate:** a session that banks nothing and produces no new verdict ends the crack work (T3); the parked-5 work
is bounded to the static candidate list + one static-RE session; no forced banks, no redefinition (P9).
Scale estimate: 3–5 sessions.

## Effort / model (R7/R26/R27 — every transition is PROMPTED, never assumed)
- **Max** through T0–T2 (T2 is non-obvious static RE; T0/T1 are settled-design and would be fine at xHigh).
- Prompt to drop to **xHigh** for T3 (orchestration) and T4 (ledgering); prompt back to **Max** for T5 (PhaseEnd).
- Models: T1c one **Sonnet** agent (123 ins); T3 **Opus** for all 11 targets (escalation tier — Sonnet plateaued on
  the ≤120-ins rows in S79); **Fable only if an agent names a wall class the codegen map lacks** — STOP and prompt
  Drew first. **No Ultracode / Workflow:** one-page census → the S80 one-agent-per-function shape
  (`docs/wave-playbook.md` §S80 addendum, Agent-tool subagents; `tools/agent_verdicts.py` for any that outlive a
  session).

## Adjustments vs `frontier-p32.md` §4 (approved)
1. The parked 5 (T2) run BEFORE the crack pass (T3): the static header probe (2026-09-05) gave every payload a
   deterministic candidate base, so T2 is a set of ~0-token `new_binary.sh` byte-gate probes, and any stubs they
   add ride the same single bounded agent pass.
2. Tooling-first split into three tasks, one commit each (P4/R42/R60).
3. No MCP dependency for the parked 5 (static evidence + our own matched C); MCP only as a fallback (R29 prompt).
4. Walls get a ledger task (T4), not drafting — incl. fixing two dangling best-draft paths (R62).

## Tasks (strict order; one commit per task after this file is updated; count banks from the SOURCE)

- [x] **T0 — Phase open** (Max) — DONE 2026-09-05: verbatim 5==5 · exclude 8/8 fresh · census 21 (B-CARVE 4 / D-NEAR 10 / F-FAR 7, `.run/P32/frontier_p32_open.json`) · tools-health OK · check-all 213/213 rc 0 (`.run/P32/t0_baseline.log`): this file; harness task list (R28); baseline reads — `verbatim_check --strict`
      (5==5), `exclude_audit --assert-fresh`, `frontier_classify --json .run/P32/frontier_p32_open.json` (21),
      `make tools-health` OK, `make check-all` 213/213 (read of the on-disk S80 artifacts); commit.
- [x] **T1a — resident: split the code subseg, bank `func_800D128C` (243)** — DONE 2026-09-05: BANKED byte-identical `8e17e02f…` (commits `commit:3902` split + `commit:3904` bank); **R22 after the bank: check-all 213 passed / 0 failed, rc 0** (`.run/P32/t1a/r22.log`); resident stubs 2 → 1; THREE instrument fixes on the way (cookbook §496 carrier provided-types, §498 carve `--pre` drop + gate ignoring the extract rc + interleave_check false DRIFT); twin_rescan: 20 open, nothing newly free. Original brief:
      `jr_isolate_all resident --only func_800D128C` (dry-run CLEAN 2026-09-05: 3 region files, carve repoint
      `resident → resident_jr_800D00E4`, `--order` + `JTBL_PADS`) → `make extract BINARY=resident && make build
      BINARY=resident -j8` (EXIT CODE, R53; byte-neutral split) → commit carve state alone (R60) → `rtu_match` the
      closeness-0 draft `.run/S71_gate14/resident/func_800D128C.c` in the new region TU → `parallel_gate --r22`
      (carves `jtbl_80113FB8` + `jtbl_80114198`; `pads_audit` after) → in-tree build exit code → commit →
      `twin_rescan`. TU refusal → §376/§378 chain as a byte-neutral plumbing commit BEFORE re-gating.
- [x] **T1b — ov_SC02_017: split + remap the twin, bank `func_80186C64` (209)** — DONE 2026-09-05: BANKED byte-identical `c0253499…` (`commit:3903` carrier §497 fix — NO source rename needed · `commit:3906` split · `commit:3907` bank); 0 drafting tokens; four §376 TU spellings + one TU-provided typedef stripped. Original brief (Max/xHigh): byte-neutral tag rename in `src/ov_SC02_017/ov_SC02_017_jr_8017DF34.c` (:4314/:4319; keep the
      typedef name) → build sha-unchanged → commit → `jr_isolate_all ov_SC02_017 --only func_80186C64` (dry-run
      REFUSED on the conflict 2026-09-05; expect CLEAN after the rename) → extract/build byte-neutral → commit carve
      state → `family_remap --addr 0x801810C8 --from ov_SC02_016 --to ov_SC02_017 --to-addr 0x80186C64` (d=2
      RELOC-ONLY twin; source `src/ov_SC02_016/ov_SC02_016_jr_801810C8.c:2839`) → strip typedefs the TU already
      defines (§491 gap 2) → `rtu_match` → `parallel_gate --r22` → commit → `twin_rescan`.
- [x] **T1c — md_MAIN_034: bank `func_800CB00C` (123)** — DONE 2026-09-05: BANKED byte-identical `46153c06…` (`commit:3908`) from the STORED S72 body `.run/O21/opus/func_800CB00C.c` (rtu MATCH 123/123; the census's best_draft was a name-collided WRONG file, R48/R38) — NO agent; WALL pin dropped (exclude 8→7); backlog 18→17. **R22 after the T1b+T1c batch: check-all 213 passed / 0 failed, rc 0** (`.run/P32/t1b/r22.log`). Original brief: pack via
      `claude_wave_packs` (the stored 174-ins draft is WRONG, not a seed; §494 jtbl idioms) → verbatim grep →
      `rtu_match --split md_MAIN_034 --source md_MAIN_034` → `parallel_gate` (island pads derive at build, §303)
      → commit → `twin_rescan`; drop the `md_MAIN_034:func_800CB00C` pin (`exclude_audit --write`).
      **Progress report to Drew after T1c.**
- [ ] **T2 — the parked 5** (Max):
  - [x] **T2a** — DONE 2026-09-05 (`commit:3909`): controls 7/7 (5 STRONG, 2 CONSISTENT; TEXT_LO estimates == yaml); the five: MAIN/7 STRONG 0x800CEDF8 · MAIN/9 STRONG 0x800CD348 · SC03/53, /54 CONSISTENT top 0x801EF468 (12-way tie) · SC03/56 SPLIT (jal vote 0x80178C8C vs ptrs/lui ~0x801CBB50); memory-map §S45 p7; SETUP row. Brief: `tools/payload_base_evidence.py` (id word, first prologue → TEXT_LO, abs-pointer window, lui
        hi-half histogram, `jal` self-consistency per candidate base, DESTPTR lookup in the window from
        `.run/idxtab_map.json`) — R39 controls: must re-derive md_MAIN_008/011 (0x800CEDF8), md_MAIN_042
        (0x800CCB1C), md_MAIN_013 (0x800CAE08), md_SC03_073 (0x801EF468) from their payloads alone; refuses a
        payload with no self-reference (base-independent bytes — say so, never guess). SETUP row (R21);
        evidence rows → `docs/memory-map.md` §S45 p7 (G5 `static-derived`, US). Commit.
  - [x] **T2b** — DONE 2026-09-05: **ALL FIVE onboarded on their first candidate**, byte-identical first builds — md_MAIN_007 @0x800CEDF8 (`commit:3911`, 19 stubs, A4 applied) · md_MAIN_009 @0x800CD348 (`commit:3912`, 11) · md_SC03_053 + md_SC03_054 @0x801EF468 (`commit:3913`, 15 + 7) · md_SC03_056 @0x801CBB50 (`commit:3914`, 4). Fleet 213 → **218**; +56 stubs (~2,600 ins). **Instrument findings (R34/R35):** the all-INCLUDE_ASM first build is a NULL oracle for FINE base errors (+8 builds byte-identical; +0x1000 fails the link) — bases are static-derived STRONG, byte-proven by the first internal-call C bank; a jal-vote base whose targets are shared-engine function starts is OUTWARD-EXPLAINED (SC03/56's false 0x80178C8C). Close chain (sig-modules → tools-health → audit-disc → R22 of 218) running: `.run/P32/t2b/close.log`. Original brief: onboard probes, one payload per commit, top candidate first (the module-class law: the FIRST
        build's byte-identity is the arbiter; a miss → next candidate; none → stays parked with the evidence):
        `md_MAIN_007 extracted/retail/MAIN.CD.dir/FILE_007 0x800CEDF8 0x34` (9/9 internal jals on its own
        prologues at that base; omit `symbols.resident.txt`, A4 law) ·
        `md_MAIN_009 …/FILE_009.dir/0.1 0x800CD348 0x3C` (the unique base fitting both in-region jals; then
        0x800CAE08, 0x800CCB1C) · `md_SC03_053 …/SC03.CD.dir/FILE_053.dir/0.1 0x801EF468 0x4` ·
        `md_SC03_054 …/FILE_054.dir/0.1 0x801EF468 0xF0` · `md_SC03_056 …/FILE_056.dir/0.1 0x801CBB50 0x4`
        (then 0x801CBD90, 0x801CC6E0). After each success: `make sig-modules`, `make tools-health` (R36),
        `make audit-disc` (UNCLAIMED 5 → 5−N), commit.
  - [x] **T2c** — DONE 2026-09-05: **20 free banks** in the five new modules for 0 drafting tokens (`commit:3918` 8 · `commit:3919` 5 · `commit:3920` 7): 7 d=0 hash twins + 3 RELOC-ONLY via `family_remap`, 9 constant-only NEAR-COUSINs (each constant named by the real-TU diff), 2 hand pass-throughs (main's `func_80014128` shape); `dedup_extend` 0 (no macro-group members); `split_indicator` population fix (`commit:3917`, was a stale 213 list — R51). **R22 after the batch: check-all 218 passed / 0 failed, rc 0** (`.run/P32/t2c/r22.log`). Census: **54 stubs / 6,376 ins** (`.run/P32/frontier_t2c_close.json`: main 12 · md_MAIN_007 15 · md_MAIN_009 10 · md_SC03_053 6 · md_SC03_054 4 · md_SC03_056 1 · ov_SC03_105 2 · resident 1 · md_MAIN_003 1 · ov_SC06_022 1 · ov_SC07_002 1). `make audit-disc` UNCLAIMED 0 of 220; disc-completeness.md P32 section written; cookbook §499 + decision-log S81 (R31). Brief: free banks + census: `twin_rescan` / `dedup_extend` for h_exact twins of the new stubs; regenerate
        the census; leftovers join T3. Update `docs/disc-completeness.md` (+ ledger regen), decision log (R31).
  - [x] **T2d** — NOT NEEDED (both MAIN/7 and MAIN/9 onboarded on their first candidate). Brief: (only if MAIN/7 or MAIN/9 refuse every candidate): one bounded static-RE pass over our own C
        (`src/800.c`, `src/boot.c`, `src/resident/resident.c`: `loadDestPtrTable`, `D_800D3764`/`D_800D384C`,
        the `resourceIdMap` sites) for a route producing global index 7 or 9; MCP (R29) only if the C is
        insufficient. Outcome: a base, or the strengthened exclusion evidence. **Progress report after T2.**
- [x] **T3 — one bounded crack pass, Opus agents, one per function** (xHigh orchestration — prompt R27):
      **DONE 2026-09-05 (S83): 47/47 drafted, 39 BANKED (10 in the launching session + 29 in S83: the 11 S82 MATCH rows, the 17 queued Haiku rows 17/17 MATCH, and func_8001BC6C cracked 6 -> 0 by permuter_ils + an R63 read), 8 NEAR ledgered in the backlog with cost, 0 FAIL, 0 walls found. Census 15 stubs / 3,758 ins = 7 pinned walls + 8 NEAR (`.run/P32/frontier_t3_close.json`); md_SC03_053/054/056 100% C; resident 145/145; main 6 open (5 walls + func_80039308 NEAR 17). Fleet (make report): instr 13,484,739 / 13,488,497 = 100.0% · distinct 5,812,831 / 5,816,589 = 99.9% (90,975 / 90,984 unique) · fn-count 363,199 / 363,214 = 100.00% · INCLUDE_ASM 15. Step 8 (bounded tail): func_8001BC6C BANKED; func_800CD674 permuter plateau at the same $a3<->$t1 pair; func_800CF3E8 Opus second look NO GAIN at 27 but the §500-D1 mechanism corrected (cse find_best_addr) and its lever refuted (§500-H). Harvest: cookbook §500-F/G/H, BRIEF.md, jtbl_carve probe text, Makefile C_SRCS dotfile guard (a masked_diff probe broke a gate_main rebuild). Fleet R22 218/218 at 10:46, 11:09 and **217+main extracted, 218 passed / 0 failed, exits 0/0/0 at 12:00 MDT** (S83).** Original brief:
      targets = `main:func_80023BF0` 11 · `func_80038698` 11 · `func_80039B20` 7 · `func_80039308` 34 ·
      `func_80015B6C` 40 · `func_8002FDE8` 35 · `func_8001BC6C` 28 · `ov_SC03_105:func_80185810` 37 ·
      `md_MAIN_003:func_800CF3E8` 54 · `ov_SC07_002:func_8017DC80` 84 · `resident:func_800D06E8` 344 (after a
      byte-neutral fix of the `Struct80078E78` typedef clash) + any T2c leftovers. Cheap second looks first:
      `func_80023BF0` (VERIFY the S80 permuter waypoint's semantics before seeding) and `func_80039B20`.
      Packs: `claude_wave_packs` (S79 verdict incl. INERT list, exact-length best draft, matched same-TU neighbour,
      §494/§495 laws, the fixed permuter recipe `permuter_ils … --cycles 8 --secs 150 --j 3`); brief =
      `.run/S79w/SYS.md`. Per result, never in bulk: verbatim grep → `rtu_match` (main: `--tu src/<TU>.c`) → gate
      (`parallel_gate --r22` / main: `gate_main <slate> --apply`, read the BODY/TABLE/PLUMBING/MIXED line) →
      commit per bank (R42) → `twin_rescan`; plateaus → `backlog.py log` with attempt + cost (R41).
      Expected 1–4 banks (S79: 3/11 on the Opus F/G tier), ~0.6–1.4M tokens. **Progress report after T3.**
- [x] **T4 — the walls' FINAL verdicts** — DONE 2026-09-05 (S83, xHigh, no drafting): all 7 pinned rows re-probed IN TU CONTEXT (`rtu_match` in the real TU; the three CC1-FAIL rows via a sandbox TU copy under `.run/P32/t4/tu/` — every CC1 FAIL was plumbing, R40) and every one reproduced its recorded residual: **1 PROVED** (`main:func_80011380` §474, DIFF 6) · **6 CANDIDATE** with current citations (`func_80032A74` 1 · `func_80020DA4` 2 · `func_80039DEC` 2 · `func_800391D4` 3 · `ov_SC06_022:func_8017DF28` 2 · `ov_SC03_105:func_801834A4` 6). No verdict changed. Deliverables: the wall table below; `config/wave_exclude.txt` annotated per row, `exclude_audit --assert-fresh` 7/7; backlog rows for all 7 (the two path-less rows given existing drafts, R62; `func_80032A74` got a TU-clean synced draft `.run/P32/t4/drafts/func_80032A74_tuclean.c`); cookbook **§500-I**; `docs/accelerators.md` (8); decision-log (the final wall doctrine, R31). Original brief: the 8 pinned rows — confirm each citation current
      + instrument exonerated (R40), PROVED vs CANDIDATE, ledger best-draft → an existing real-TU-clean C file (R62:
      `func_80011380` → `.run/m3/opus/func_80011380.c`; `func_801834A4` → `.run/S71_gate14/ov_SC03_105*/`),
      `exclude_audit --write`, `backlog.py render`; a T3 idiom naming a wall's mechanism re-opens that row
      (bounded: one attempt, permuter first). Wall table into this file; cookbook §496+; decision log; accelerators.
- [~] **T4b — crack and bank the final 15 (ADDED 2026-09-05 by Drew's directive; supersedes the kill gate: "anything that isn't the original hand-written asm or the PsyQ libs needs to be cracked and banked before we finish")** — **FIRST PASS COMPLETE 2026-09-05 (S83): 11 of 15 BANKED byte-identical, 4 carried to the NEXT session's HAND pass (Drew: no second agent round; hand-crack the remaining ones).** Hand pass first (22 spellings, 0 banks, every blocker refined to a mechanism in `.run/P32/t4b/<fn>/NOTES.md`), then one Fable agent per row (permission, not requirement — Drew), resumed 3-at-a-time through three usage-limit outages. Banked (each: coordinator `rtu_match` in the CURRENT real TU → `gate_main` / `bank.sh` byte-identical → one commit; pins dropped by `exclude_audit --write`; mechanism in cookbook §501–§501-L): `main:func_800391D4` `commit:3956` · `main:func_80039DEC` `commit:3959` · `md_MAIN_009:func_800CD674` `commit:3964` · `ov_SC06_022:func_8017DF28` `commit:3966` · `main:func_80020DA4` `commit:3969` · `ov_SC03_105:func_801834A4` `commit:3972` · `md_MAIN_003:func_800CF3E8` `commit:3976` · `md_MAIN_009:func_800CD92C` `commit:3979` · `ov_SC07_002:func_8017DC80` `commit:3983` · `main:func_80011380` `commit:3990` (the §474 "PROVED" wall) · `md_MAIN_007:func_800CF6D0` `commit:3992`. Ten of the eleven were T4 "walls" or long-standing NEARs. **HAND PASS S84 (2026-09-06, Fable Max, no agents): row (a) `main:func_80032A74` → PROVED at 1 (§501-M producer census: the 0x48 slot can only be a combine-minted ghost, which needs an `lh`/`lb`; the pin stays with its final verdict; ledger + `tools/ghost_census.py` + `cc1_dumps.sh` repair; rows (b)(c)(d) next).** Carried (4, all exact length, in `docs/backlog.md` with next levers): `main:func_80032A74` 1 (the last pin; ghost pseudo — near-proved) · `md_MAIN_007:func_800CF408` 3 · `main:func_80039308` 4 · `ov_SC03_105:func_80185810` 13. Close: fleet R22 **218 passed / 0 failed, exits 0/0/0** (23:33–23:36 MDT, `.run/P32/t4b/r22_full.log`); `make report`: instr 13,486,890 / 13,488,497 = 100.0% · distinct 5,814,982 / 5,816,589 = 100.0% (90,982 / 90,984 unique) · fn-count 363,210 / 363,214 = 100.00% · **INCLUDE_ASM 4**; main REAL 787 · LINKED 1,256 · VERBATIM 3 · stubs 2 · 2,089 / 2,091 = 99.90% · `143dbb89…`; census `.run/P32/frontier_t4b_close.json` 4 stubs / 1,607 ins; decision-log P32 S83 T4b (R31); accelerators (10)–(11); tools-health OK (`.run/P32/t4b/tools_health.log`).
- [ ] **T5 — PhaseEnd** (Max, Tier 1 — prompt R27): P7 checkbox walk; milestone demo (R22 fleet N/N, tools-health,
      `verbatim_check --strict`, final census, wall ledger, parked-5 dispositions via `make audit-disc`,
      `make report` all three metrics + main `143dbb89…` with/without SDK dirs, corrected denominators); **WAIT
      for gate 2**; `PhaseEnd_Phase32.md` (+ Roadmap delta + Plain-English Recap); `git mv` this file →
      `phase-ends/logs/Phase32.md` (R19); R23 MCP stop if it ran; leave both uncommitted for Drew (R6); 🛑 (P8).

## T4 — the walls' FINAL ledger (S83, 2026-09-05; every row re-probed in TU context; `config/wave_exclude.txt` carries the same lines)
| row | ins | class | closeness leaf / real-TU (S83) | mechanism · citation | bounded attempt record | verdict | best draft |
|---|---|---|---|---|---|---|---|
| main:func_80011380 (boot, −O0) | 192 | C-level floor | 6 / 6 (`rtu --o0`) | fold-const.c:882 `split_tree` merges MULT(MULT(i,2),2); the two escapes each cost one insn (stupid.c:497 adjacency / expand_decl use-brackets) — cookbook §474, §388 −O0 colouring oracle | 20 spellings + statement-expression + `(t=i*2)*2` register form (S76 proof); pinned S79 #8 | **PROVED** | `.run/m3/opus/func_80011380.c` |
| main:func_80032A74 (800_b_2) | 422 | FRAME/WIDTH | 1 / 1 (synced draft) | sole residual idx 244 `lh` vs `lhu`: extendhisi2 is a force_not_mem EXPAND (an orphan frame slot is minted only at an `lh`); the target's +8 frame bytes = §172 producer 3 (caller-save area, reload1.c:1445) | ~200 byte-probes + 100-variant retyping sweep (S79 Opus) + permuter_ils 8×150 s null (S80); S83: CC1 FAIL was 7 header typedefs + 4 decl spellings → synced copy DIFF 1 | CANDIDATE | `.run/P32/t4/drafts/func_80032A74_tuclean.c` |
| main:func_80020DA4 (800) | 100 | REGALLOC-PERM | 2 / 2 | phantom 16-byte frame reproduced (address-taken `frame_pad[3]`); residual = `mflo` destination `$t0` vs `$a2`; pinning regresses to 79 | 5 attempts 51→20→14→8→2 (S7x/S79) + permuter_ils null (S80); S83 rtu DIFF 2 | CANDIDATE | `.run/S79w/sonnet/func_80020DA4.c` |
| main:func_80039DEC (800_c) | 74 | REGALLOC (K&R) | 2 / 2 (sandbox TU, no-proto decl) | the `$a3↔$t0` swap of the two K&R raw-preserve parameter copies is fixed by ARGUMENT POSITION in gcc-2.7.2 narrow-parameter promotion (2nd → `$a3`, 3rd → `$t0`) before global-alloc; every pin regresses to 60–75 (cookbook §376/§495 K&R laws, lines ~1320/1508) | 3 attempts (S7x/S79 Sonnet 9) + permuter_ils 9→2 (S80); S83: CC1 FAIL = the TU's narrow prototype at 800_c.c:3496 vs the K&R def | CANDIDATE | `.run/S79w/permuter/func_80039DEC.c` |
| main:func_800391D4 (800_c) | 75 | SCHED (loop) | 3 / 3 (sandbox TU, `[][1]` externs) | 3-insn SCHEDULE-REORDER (`off` init vs arg1's `sll/sra`): `move_movables` splices hoisted invariants after any pre-existing preheader flow code (loop.c 2.7.2:1529; map loop.md L4) | 4 prior + S79 Sonnet 64→3 (`i=$7` pin kills combine_givs, `D_80073140[][1]` decl, 7 `asm("")` pads) + permuter_ils null (S80); S83: the `[][1]` spelling is load-bearing (TU-compatible forms → 65 @ 76) | CANDIDATE | `.run/S79w/sonnet/func_800391D4.c` |
| ov_SC06_022:func_8017DF28 (jr_8017BEBC) | 119 | SCHED (slot) | 2 / 2 | `expand_block_move` `copy_addr_to_reg` pseudo cse-reused for both later `&mtx` args (map cse_expr.md [A23-2]/§H); `addiu $s2,sp,0x10` in the jal delay slot vs the target's bnez slot | five RTL-verified attempts (S71/S79); permuter_ils "1" was a divergent rewrite (S80, R63); S83 rtu DIFF 2 | CANDIDATE | `.run/S79w/sonnet/func_8017DF28.c` |
| ov_SC03_105:func_801834A4 (jr_80181C84) | 106 | SCHED (loop) | 6 / 6 (×3 variants) | loop.c movable ordering (S71) | S71 gate14 resolver variants cn-cast / -rc / -rc-sd all DIFF 6; S83 rtu DIFF 6 ×3 | CANDIDATE | `.run/S71_gate14/ov_SC03_105-cn-cast-rc-sd/func_801834A4.c` |
| *(unpinned)* md_MAIN_003:func_800CF3E8 | 469 | ALIAS-BASIN | 27 / 27 | cse.c `find_best_addr` (fold_rtx MEM; COST pseudo 0 vs hard reg 1) swaps the bare-REG tag-load address to a pseudo; the alias lever refuted 5/5; the pinned-pointer launder frees the load but lands it 4 slots late (79 @ 470) — §500-H | S79/S82 Opus + S83 Opus second look (245k tokens, ~16k compiles) | CANDIDATE (backlog, not pinned) | `.run/P32/t3/opus/func_800CF3E8.c` |

The other 7 NEAR rows (`func_80039308` 17, `func_800CD674` 2, `func_800CD92C` 15, `func_800CF408` 49, `func_800CF6D0` 137, `func_80185810` 35, `func_8017DC80` 46) are DEFERRED WITH COST in `docs/backlog.md` (class · closeness · best draft · agent/permuter cost), per the milestone's third disposition.

## Standing procedure (every task)
Fix the TU by a byte-neutral plumbing commit BEFORE any gate (S77 law) · commit banked work before the next
command that can touch `src/` (R42) · after any bank: `twin_rescan`, `verbatim_check --strict` (R62) · after a
carve/merge touching a yaml/`.mk`: `make extract BINARY=<b>` before building; `pads_audit`/`interleave_check` on
every touched carve binary (R60) · fleet verify after every banked batch: `make clean && make extract-all && make
check-all` — read EXIT CODES (R53), quote the green count at every close (R58); `make tools-health` · log each
task here + refresh the 🛑 checkpoint before any pause · rules check every 4 tasks (P6) · harvest idioms into the
cookbook before the next drafting step (R16/R30) · no `Co-Authored-By` trailer (R5); keep the `Claude-Session:` line.

## Blockers
- 2026-09-05 09:xx: the successor session's SessionStart hook launched a headless Ghidra MCP server (`.run/ghidra-mcp.log`); T3/T4 do not use it; no RE writes → never stage the `ghidra/` churn (R23).
- Ghidra MCP not running at open (clean stop in the log; the SessionStart hook's server did not persist). Not
  needed for T0–T2b; if T2d needs it: `tools/ghidra_mcp_start.sh` → pause → Drew runs `/mcp` (R29) → G2 ping.

## Log
- 2026-09-06 (S84, session 72d8b4b1, Max, Fable 5.1) — **T4b hand pass, row (a) `main:func_80032A74` CLOSED: PROVED at 1 (verdict, not a bank).** Preflight: tree clean, `verbatim_check --strict` 5==5, `make check-all` 218 passed / 0 failed rc 0 (`.run/P32/t4c/check_all_preflight.log`). Re-verified in the real TU (`rtu_match … --tu src/800_b_2.c --asm-subdir asm/nonmatchings/800_b_2`): the `s16 u18` draft DIFF 1 (idx 244 `lh` vs `lhu`, frame exact); the `u16 u18` TU-clean variant DIFF 22 = the 22 frame rows only (422/422 code). The residual is ONE reload-time slot at sp+0x48. Instead of a spelling sweep, enumerated every post-parameter stack-slot producer from the 2.7.2 source (reload1.c:658 ghost `alter_reg` · caller-save.c:249 area · reload1.c:879 invalid-equiv address · reload1.c:3499 `spill_stack_slot`) and refuted each on the bytes/dumps: combine's `newi2pat` ghosts re-derive a narrow load (`lh`/`lb`) and the site is `lhu` with no `lb`/double load; a save area without `sw/lw` needs sched.c:4962 staleness and no register-only insn shares a block with any of the 7 calls; unallocated single-block equiv pseudos cannot exist; `$t0` holds no pseudo (`order_regs_for_reload`) and LO mult results retry into `GR_REGS`. Found and measured a NEW ghost producer — `local-alloc.c optimize_reg_copy_2` on `tmp = x; tmp op= c; x = tmp;` (P13 refs 5, P14 refs 1) — which cannot slot because it is minted after regclass (class `GR_REGS`, no conflicts → allocated, vars=0). 18 isolated reproducers, 0 draft variants. Deliverables: cookbook **§501-M**, `tools/ghost_census.py` (new) + `tools/cc1_dumps.sh` (repaired: frame line + census, the under-counting `(use)` grep gone) + SETUP rows (R21), accelerators (12), backlog row (WALL-PROVED) + `tools/backlog.py` tie-break repair (kept the EARLIEST record at equal closeness — the S84 row never rendered), `config/wave_exclude.txt` annotated (`exclude_audit --assert-fresh` 1/1), notes `.run/P32/t4c/func_80032A74/NOTES.md`. NEXT = row (b) `md_MAIN_007:func_800CF408` (3).
- 2026-09-05 13:05–23:40 MDT (S83, continued) — **T4b first pass COMPLETE: 11 of 15 banked, 4 carried.** Fifteen Fable agents launched from `.run/P32/t5x/` (BRIEF + packs + the hand-pass NOTES); three usage-limit outages killed every run (resumed each time via SendMessage with context intact; "write deliverables early" saved one crack from a dead run); from the second outage on, resumed 3 at a time (Drew). Verdicts: 11 MATCH (each re-verified by the coordinator in the CURRENT real TU and banked byte-identical — main rows via `gate_main` slates, overlays/modules via `SPLIT=… DRAFT_DIR=.run/P32/t5x/fable bank.sh`), 4 NEAR at exact length (1 / 3 / 4 / 13) with pass-attributed residuals and next levers ledgered. Every crack came from READING a pass dump against the 2.7.2 source; cookbook §501–§501-L (12 new laws: cascades, cross-jump-after-alloc, dying-input vs birthing boost, hard-reg sets count, pins forbid retry regs, CSE-quantity split, three-passes-three-dials, constants as floaters, manufactured orphans, a proved tree wall is not an RTL wall, sched2's /s exemption, coupled dials); decision-log P32 S83 T4b; accelerators (10)–(11). Instrument defects: bank.sh (empty fn list → built the unchanged tree, exit 0; `_jr_` TU split; draft dir) hardened, and two premature "banked" ledger messages corrected in the next commit (memory: write the message from the tool's output). Pins 7 → 1. Fleet R22 218/218 at the close; `make report` fleet 100.0/100.0/100.00, 4 stubs. **Drew: no second agent round; hand-crack the remaining four next session.** NEXT = the hand pass on the four (see the 🛑 block), then T5.
- 2026-09-05 12:05–12:40 MDT (S83, continued) — **T4 DONE.** Preflight: tree clean, verbatim 5==5, R22 218/218 (12:00), `exclude_audit --assert-fresh` 7/7. Every pinned wall's best draft re-run with `rtu_match` in its CURRENT real TU: `func_80011380` DIFF 6 (`--o0`), `func_80020DA4` DIFF 2, `func_8017DF28` DIFF 2, `func_801834A4` DIFF 6 ×3 variants; the three CC1-FAIL rows re-probed after their plumbing was understood — `func_80032A74` (7 TU-provided typedefs + 4 decl spellings → `cdecl.strip_provided_typedefs` + the TU's lines → DIFF 1 in the real TU), `func_80039DEC` and `func_800391D4` (a sandbox TU copy under `.run/P32/t4/tu/` with the declaration edited THERE → DIFF 2 / DIFF 3) — no `src/` edit, no byte-neutral commit spent on rows that will not bank. Leaf `match_one` re-measured all three (1 / 2 (permuter) / 3). **No verdict changed: 1 PROVED (§474) + 6 CANDIDATE**, citations current (§474, §172 reload1.c:1445, loop.md L4 2.7.2:1529, cse_expr.md [A23-2], the K&R promotion laws). Deliverables: the wall table (above), `config/wave_exclude.txt` per-row S83 lines, backlog rows for all 7 (+ the two path-less rows fixed, R62; `docs/backlog.md` 16 open), cookbook §500-I, accelerators (8), decision-log. NEXT = **T5 (Max, Tier 1 — prompt R27, WAIT for gate 2)**.
- 2026-09-05 11:30–12:30 MDT (S83, continued) — **T3 steps 8–9 DONE → T3 CLOSED.** Step 8: `permuter_ils` 8×150 s -j3 on the two REGALLOC-PERM seeds — `func_800CD674` plateau (best waypoint = the same 2-row `$a3↔$t1` pair; ledgered with cost), `func_8001BC6C` reached masked 1; the R63 read showed three mutations, one of them a WRONG-WIDTH `& 0xFF` (lhu→lbu); the two sound ones (idx after color; an early `tag`/`k` birth) = leaf MATCH, re-spelled well-defined as `k = 0; tag = (a1 << 8) | k;` (11 spellings measured), rtu MATCH in src/800.c, **gate_main BANKED 143dbb89** (`commit:3948`) — main 7 → 6 open. gate_main's first rebuild died on a concurrent agent's `src/.masked_diff_probe.<pid>.c` (present at parse, gone at compile) → **Makefile `C_SRCS` find now `-not -name '.*'`** (`commit:3949`, byte-neutral, control on `make -pn`). One bounded Opus second look at `func_800CF3E8` (245k tokens, 29 min): 27 holds; §500-D1's mechanism corrected to `cse.c find_best_addr` (fold_rtx MEM; COST pseudo 0 vs hard reg 1), the alias lever refuted 5/5, a new zero-byte pinned-pointer launder found (79 @ 470, structurally closer) — cookbook **§500-H**, backlog row updated. Step 9: `make report` (fleet instr 100.0% · distinct 99.9% · fn 100.00% · 15 stubs), `make report BINARY=main`, census `.run/P32/frontier_t3_close.json` (15 / 3,758), twin_rescan 0 free, cookbook §500-G/H + index, this file; R22 → see the 🛑 block. **Kill gate:** the session banked 29 and produced 3 new verdicts; the tail's three bounded attempts are spent — T3 closes on the evidence. NEXT = T4.
- 2026-09-05 10:10–11:25 MDT (S83, session 491895ad, xHigh, Fable 5.1) — **T3 steps 0–7 DONE: 28 banks, fleet R22 218/218 twice.** Preflight R22 218/218 rc 0 (`.run/P32/t3s3/r22_check.log`) → the 11 S82 MATCH rows banked: md_SC03_053 ×2 (`commit:3935` `commit:3936`, 100% C) · main ×2 via gate_main (`commit:3937`: "slate 2 -> 2 compatible … BANKED 2 … 143dbb89 BYTE-IDENTICAL") · md_SC03_054 func_801EF6D8 604+7 jtbls (`commit:3938`; `jtbl_carve --probe` refused the tail carve → §303 derive stage reproduced the island pads `0,0t1,0t1,0t1,0t1,0t1,0` with NO carve state change) · md_MAIN_007 ×6 after the byte-neutral func_800CF3B0 no-proto decl commit (`commit:3939`, `commit:3940`) — two integration classes on the way (same-TU s16/u16 spelling of D_800B99E8; §304 self-defining rodata D_800CEDFC). twin_rescan 33 open / 0 free; verbatim 5==5; **R22 `make clean && make extract-all && make check-all` → 217+main extracted, 218 passed / 0 failed, exits 0/0/0** (`.run/P32/t3s3/r22_full.log`, 10:41–10:46); tools-health OK. The 9 NEAR rows ledgered (`backlog_near.sh`; docs/backlog.md 15 open). **17 Haiku agents launched 10:57 from staged prompts (`.run/P32/t3s3/prompts/`), 17/17 MATCH by 11:15**, each re-verified with rtu_match in the CURRENT TU and banked by `bank.sh` (verbatim grep → rtu → splice → one build → sha → commit-on-green): md_MAIN_007 ×6 (`commit:3941` `commit:3942`), md_MAIN_009 ×8 (`commit:3943` `commit:3946` — func_800CD520 needed a §376 re-spell after a sibling bank added the file-scope prototype), md_SC03_054 ×2 (`commit:3944`, 100% C), md_SC03_056 ×1 (`commit:3945`, 100% C). twin_rescan 16 open / 0 free. Harvest: cookbook **§500-F** (the four integration classes), BRIEF.md §304 sentence, `jtbl_carve --probe` text, harvest_notes. Post-batch R22 (after all 28 banks): 217+main extracted, **218 passed / 0 failed, exits 0/0/0** (`.run/P32/t3s3/r22b_full.log`, 11:04–11:09).
- 2026-09-05 (successor session, later) — **Session-start protocol rewritten at Drew's direction (R64 candidate):** `phase-ends/DIGEST.md` created (every phase synopsis + every rule in full + the PROJECT_CONTEXT corrections + the doc map); CLAUDE.md load order = PROJECT_CONTEXT → DIGEST → the three most recent PhaseEnds → CURRENT_PHASE, ≈100k tokens, the 🛑 block replayed VERBATIM; Phase Boundary step 3b maintains the digest (P7); `phase-ends/README.md` + SETUP §7 updated; the two memories (`checkpoint-current-phase-before-pause`, `session-start-list-rules-in-full`) + MEMORY.md updated; `.run/P32/t3/PROMPT_TEMPLATE.md` saved (verbatim agent prompts). The 🛑 block below was REFRESHED to the verbatim-replay standard and SUPERSEDES the 09:30 block. Ratify R64 at PhaseEnd_Phase32.
- 2026-09-05 09:30 MDT — **T3 CHECKPOINT by the successor session (Max, Fable 5.1) after the launching session died.** The T3 coordinator (session c6a5fb71) banked 10 functions in 9 commits (T3 (1)–(9), 01:01–01:07 MDT) and then hit "Prompt is too long" at 01:07 MDT; 22 agent completions (07:07Z–08:04Z) arrived into a dead session. Recovered via the recorded route: `agent_verdicts.py` over the 31 task transcripts → `.run/P32/t3/verdicts.jsonl` (20 MATCH / 9 NEAR / 2 FAIL); every unbanked draft re-verified with `rtu_match` in its real TU (10 MATCH confirmed). **Instrument incident (R48 class):** one agent's tidy-up (`find .run/P32/t3/opus -maxdepth 1 -type f ! -name func_800CD674.c -exec mv {} _scratch/`, 07:52Z) had swept 11 sibling Opus deliverables — found in `_scratch/`, moved back, byte-verified at the reported closeness; `tools/agent_drafts_restore.py` (NEW — transcript replay) written as the fallback; `.gitignore` allowlist for `.run/P32/**` so the drafts/ledger/census are committed (R20). Harvest written IN-SESSION (R16/R30): cookbook **§500** (10 banked closers, 10 MATCH closers, 9 NEAR classes, two NEW mechanisms — the pinned-base alias basin and `#line`-equalised ASM_OPERANDS — and the process defects); `docs/wave-playbook.md` §S80 addendum-2 (per-function work dirs, JSON-only final message, the 20-agent cap, the recovery tools); `docs/accelerators.md` P32 T3; `docs/decision-log.md` P32 S82 (R31); SETUP row (R21). Read-only T4 pre-check results from the dead session preserved in the 🛑 block. Effort: this checkpoint at Max; **T3 resumes at xHigh** (R27).
- 2026-09-05 — gate 1 approved; T0 opened at HEAD `commit:3900`.
- 2026-09-05 — **T3 LAUNCHED** (xHigh): 47 targets = census 54 − 7 pinned walls (`.run/P32/t3/targets.json`, 5,288 ins); packs built (`claude_wave_packs`, 47/47 neighbours, 10 journals); brief `.run/P32/t3/BRIEF.md`. **20 Agent-tool drafters running** (16 Opus: the 11 old near/far rows + resident func_800D06E8 + the 4 largest new bodies · 3 Sonnet · 1 Haiku); **27 Haiku queued** behind the harness's 20-concurrent cap (`.run/P32/t3/pending_launch.txt`, launched one per freed slot). Recovery + per-result route: `.run/P32/t3/LAUNCHED.md`.
- 2026-09-05 — **T2c DONE (R22 218/218 rc 0) · T2d not needed.** Twenty of the 56 new stubs fell to twin remaps and constant flips (0 tokens); the rest (36, all ≤50 ins but one, never drafted) join T3 on the model ladder. Session limit reset here (Drew); effort now xHigh via `/model` (the T3 orchestration level, R27 satisfied). Settings-file JSON defect fixed (a trailing comma).
- 2026-09-05 — **T2b DONE — the parked ledger is EMPTY: all five payloads onboarded byte-identical (MAIN/7 → md_MAIN_007 @0x800CEDF8; MAIN/9 → md_MAIN_009 @0x800CD348; SC03/53, /54 → md_SC03_053/054 @0x801EF468; SC03/56 → md_SC03_056 @0x801CBB50).** Every base came from T2a's static alignment (self-calls / fn-ptr-table entries on the module's own function starts; controls 7/7), NOT from the byte check — two negative controls showed the first build is base-lenient (fine offsets) and only catches gross errors. Two tool refinements en route (combined STRONG rule; outward-explained vote bases). The 100% claim loses its last asterisk once the new stubs are banked or ledgered (T2c/T3).
- 2026-09-05 — **T1b + T1c DONE (R22 213/213 rc 0 for the batch) · T2a DONE.** Both banks were ZERO-token: T1b's body came from `family_remap` of the d=2 twin (+ four TU spellings), T1c's from a stored S72 body the census had mis-keyed (R48) — the journals (R38) named both. Census 21 → **18 stubs** (resident 1 · main 12 · md_MAIN_003 1 · ov_SC03_105 2 · ov_SC06_022 1 · ov_SC07_002 1). T2a's instrument gives every parked payload a bounded probe list; two are STRONG.
- 2026-09-05 — **T1a DONE — `resident:func_800D128C` BANKED (243 ins, byte-identical 8e17e02f, R22 213/213).** The stored S71 closeness-0 draft was byte-correct all along; the whole task was three instrument defects the resident (the fleet's one `common.h`-only, `--pre`-sandwich binary) exposed in overlay-only assumptions: (1) `jr_isolate_all` dropped a file-local typedef whose name engine_types.h also defines (§496 — fixed: provided types derived from the TU's own includes); (2) `jtbl_carve` regenerated `JTBL_INTERLEAVE` without the `--pre hdr.rodata.o` clause → extract refused → the gate linked a stale script and booked the byte-correct draft as DIFF; `harvest_verify` ignored that extract's rc (§498 — both fixed, R49/R61); (3) `interleave_check` read a `--pre` line as n=0 (false DRIFT; fixed). R38 then found two more stored MATCH bodies for T1b/T1c (see their rows). Effort stayed Max.
- 2026-09-05 — **T0 DONE.** Baseline reads all green (`.run/P32/t0_baseline.log`): `verbatim_check --strict` 5 bodies == 5 rows; `exclude_audit --assert-fresh` 8 entries, 8 WALL, 0 stale; `frontier_classify` → 21 rows = the S80 census exactly; `make tools-health` OK (sigs fresh, corpus(+resident), cdecl, audit-binaries 213/213, report lint+dedup, cookbook-index, split_indicator 213 OK); `make check-all` 213 passed / 0 failed, rc 0. Harness task list #1–#11 built (R28). NEXT = T1a.

## 🛑 SESSION CHECKPOINT — T4b HAND PASS IN PROGRESS: row (a) PROVED at 1, rows (b)(c)(d) NEXT, then T5 (2026-09-06 ~12:00 MDT; written by session 72d8b4b1 "S84"; SUPERSEDES the 2026-09-05 23:45 block)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase29/30/31.md` and this file, and
nothing else (CLAUDE.md protocol, R64 candidate). Replay this block verbatim into your chat, state phase / done / NEXT / effort,
list the rules from the digest, then WAIT for Drew. **NEXT is the HAND pass on rows (b) → (c) → (d) — Drew (2026-09-05 23:2x MDT):
"we will hand crack the remaining ones next session instead of using agents."** Non-obvious root-cause work: recommend
**effort: Max** (R7/R27 — prompt and wait for the `/effort`). No Agent tool, no Workflow. After the three (banked or honestly
ledgered), T5 = the PhaseEnd (Tier 1, Max, WAIT for gate 2).

### 1. Where we are
**Phase 32 — the last 21 + the parked 5 (short, kill-gated) — extended by Drew's T4b directive: every function that is not original
hand-asm or a PsyQ object must be cracked and banked before the phase closes.** Gate 1 approved 2026-09-05; R44–R63 ratified then;
R64 candidate. Tasks: **T0 ✓ T1a ✓ T1b ✓ T1c ✓ T2a–c ✓ (T2d not needed) T3 ✓ T4 ✓ T4b first pass ✓ (11 of 15 banked)** ·
**T4b hand pass IN PROGRESS: row (a) `main:func_80032A74` CLOSED as PROVED at 1 (S84, a verdict — nothing banked this session);
rows (b)(c)(d) open** · **T5 pending.** Harness tasks #1–#13 (#13 = T4b in_progress).
Fleet **218 binaries**. **No `src/`, `config/` (except `wave_exclude.txt` annotation) or carve state changed in S84.** Last fleet R22:
`make clean && make extract-all && make check-all` → 217+main extracted, **218 passed / 0 failed, exits 0/0/0 at 2026-09-05 23:36 MDT**
(`.run/P32/t4b/r22_full.log`); S84 preflight `make check-all` → **218 passed / 0 failed, EXIT=0** (`.run/P32/t4c/check_all_preflight.log`).
`make report` (S83 close, still current): **instr 13,486,890 / 13,488,497 = 100.0% · distinct 5,814,982 / 5,816,589 = 100.0% (90,982 /
90,984 unique fns) · fn-count 363,210 / 363,214 = 100.00% · INCLUDE_ASM 4**; main REAL 787 · LINKED 1,256 · VERBATIM 3 · stubs 2 ·
byte-identical 2,089 / 2,091 = 99.90% · sha `143dbb89…`. `verbatim_check --strict` 5 == 5 (S84). `config/wave_exclude.txt`: **1 entry**
(`main:func_80032A74`, now carrying its S84 PROVED verdict), `exclude_audit --assert-fresh` 1/1 OK (S84). Census
`.run/P32/frontier_t4b_close.json`: **4 stubs / 1,607 ins**. `make tools-health` → OK at the S83 close (`.run/P32/t4b/tools_health.log`);
`cookbook_index.py --check` OK (S84). Non-ghidra tree clean at HEAD after the S84 commit; the `ghidra/` churn is R23 restart-noise —
never stage it. Claude commits, Drew pushes (R6; ~100 unpushed). 100% C: resident, md_SC03_053/054/056, md_MAIN_003, md_MAIN_009,
ov_SC06_022, ov_SC07_002.

### 2. What S84 did (session 72d8b4b1, 2026-09-06, Max, Fable 5.1, no agents)
Row (a) only. Re-verified both best drafts in the real TU; then, instead of a spelling sweep, read every post-parameter stack-slot
producer out of `tools/reference/gcc-2.7.2` and refuted each on the bytes/dumps — the producer census is cookbook **§501-M** and
`.run/P32/t4c/func_80032A74/NOTES.md`. Found a NEW ghost producer (`local-alloc.c optimize_reg_copy_2`) and measured why it cannot
slot (post-regclass → allocatable). Tooling: **`tools/ghost_census.py`** (new; ghosts with stale refs and their class), **`tools/cc1_dumps.sh`
repaired** (prints the `.frame` line + ins count + spill lines + the census; its `(use)` grep under-counted), **`tools/backlog.py`
tie-break repaired** (kept the EARLIEST record at equal closeness — the S84 PROVED row never rendered), SETUP rows (R21), accelerators
(12), backlog row `WALL-PROVED`, the pin annotated. 18 isolated reproducers (`.run/P32/t4c/func_80032A74/p1..p18.c`), 0 draft
variants. **Verdict for (a): PROVED at 1** — the honest final disposition the plan allows for this row (P9; nothing redefined).

### 3. THE THREE REMAINING ROWS — the hand-crack briefs (all at EXACT length, all rtu-clean; unchanged from the 23:45 block)
Verify any draft with `rtu_match` in the REAL TU (main: `--tu src/<sub>.c --asm-subdir asm/nonmatchings/<sub>`; overlays/modules:
`--split <tu-basename> --source <binary>`); bank via `gate_main` (main) or `SPLIT=<tu-basename> DRAFT_DIR=<dir> .run/P32/t3s3/bank.sh
<binary> <tu> <asmdir> <arm> "<title>" <fn>` (it refuses on red). RTL dumps: `tools/cc1_dumps.sh <self-contained draft> <tag>` →
`.run/c294/dumps_<tag>/<tag>.i.{rtl,jump,cse,loop,flow,combine,sched,lreg,greg}` + the `.frame`/ins/spill/ghost summary (the draft
must carry its own typedefs/externs; add `-O0` by editing the script's cc1 line for boot). Each row's Fable report
(`.run/P32/t5x/reports/<fn>.md`) carries the dump citations and the measured-inert list — READ IT FIRST, do not repeat its sweeps.
**Do the producer census BEFORE any spelling probe (§501-M, accelerators (12)): name the pass and the dump line that owns the residual.**

**(a) `main:func_80032A74` — CLOSED: PROVED at 1 (S84).** Best drafts: `.run/P32/t4/drafts/func_80032A74_tuclean.c` (`s16 u18`, rtu
DIFF 1 = idx 244 `lh` vs `lhu`, frame exact) and `.run/P32/t4c/func_80032A74/lhu_tuclean.c` (`u16 u18`, 422/422 code, DIFF 22 = the
frame rows: vars 56 vs 64). Proof: the residual is one reload-time slot at sp+0x48; its only zero-code producer is a combine-minted
ghost (`newi2pat` split, combine.c:1887/1963 → reload1.c:658), which re-derives a narrow signed load; the site is `lhu`, the function
has no `lb` and no double load, all nine `lh` are single-use. Caller-save area (caller-save.c:249) needs sched.c:4962 staleness and no
register-only insn shares a block with any call; reload1.c:879 needs an unallocated single-block equiv pseudo; `spill_stack_slot`
needs a pseudo in `$t0` (impossible: `lw $t0` param reloads) or a failed LO retry (mult results have alternate `GR_REGS`).
`optimize_reg_copy_2` ghosts are post-regclass and allocatable (P14 vars=0). Do NOT reopen without a new producer.

**(b) `md_MAIN_007:func_800CF408` — 178 ins, closeness 3, zero pins.** TU `src/md_MAIN_007/md_MAIN_007.c`, sub `md_MAIN_007`, asm
`asm/md_MAIN_007/nonmatchings/md_MAIN_007/`. Draft `.run/P32/t5x/fable/func_800CF408.c`; report `.run/P32/t5x/reports/func_800CF408.md`;
probes/dumps `.run/P32/t5x/work/func_800CF408/`. **Residual idx 10–12** (`ori $s5,0x96` below `sw $s0` / `li $s0,5`): §501-H's floater
mechanism — the unboosted tag load lingers up block 1's store stream, is `blocking` one cycle behind the tpage `sw` at T-139, and the
empty cycle consumes the highest-LUID floater — COUPLED to the `$t2/$t3` `qty_compare` contest (ob vs 0xFF000000: 2389 vs 2400, one
ref apart): mhi's `li` UID above the index `sll` cures the floater but moves mhi's birth one slot later and flips the contest (18);
`ob` after the index fixes the contest but opens a bubble in the OT-chain `lhu` gap that eats the same floater (13). The target fills
that gap with `and $a3,$v0,$t1` = an UNBOOSTED `p & m24`; a 2-set `a3` is re-merged by combine (`reg_n_sets--`, combine.c:2309 → 36),
an asm launder there is a sched2 delay-slot phantom nop (179 ins). **Next lever (§501-L):** a filler for that gap that combine cannot
re-merge and that changes neither count — a different-mode temp (`u16`/HImode view of `p & m24`), a `volatile` temp, or moving the
contest margin by one `ob` reference in a block that does not touch the tag load. 135-variant sweep floor 3 (×24) — do not repeat.

**(c) `main:func_80039308` — 518 ins, closeness 4.** TU `src/800_c.c` (which now spells `extern s32 D_80073140[][1]`), sub `800_c`,
asm `asm/nonmatchings/800_c/`. Draft `.run/P32/t5x/fable/func_80039308.c`; report `.run/P32/t5x/reports/func_80039308.md`. **Residual =
two causes:** rows 49/50 — the hoisted constant `2` vs the pinned `vbase` preheader order (move_movables splices after source
preheader code; unpinning/moving vbase → 515/495; a named `cst2` → 520/286); rows 412/415 — `lhu $s7` is reload's SPILL REGISTER:
storing `arg1` directly spills the HImode parameter and reproduces `sh $a1 / lhu $s7` exactly, but the target frame is [arg1 spill
@0][8-byte slot with NO traffic @8][cnt @0x10] and the phantom slot could not be induced (frame 0x38 vs 0x40). **Next lever:** run the
§501-M producer census on THIS frame first — the phantom slot sits BETWEEN the arg1 spill (regno-lowest) and `cnt`, i.e. it is an
`alter_reg` slot of a pseudo numbered between them (or a `spill_stack_slot`): read the `.greg` "Spilling reg N" / "now on stack" lines
and the `.lreg` headers (`tools/ghost_census.py`) before any spelling; the S83 hypotheses (a hard-reg `spill_stack_slot` on LO or `$s7`
during `retry_global_alloc`, or a ghost as in (a)) are now testable with the census; cf. §501-E. Corrected law from this row: at an
equal-priority load/store tie sched2 issues the STORE via `potential_hazard`, not LUID (sched.c:2616–2680).

**(d) `ov_SC03_105:func_80185810` — 489 ins, closeness 13.** TU `src/ov_SC03_105/ov_SC03_105_jr_80181C84.c`, sub
`ov_SC03_105_jr_80181C84`, asm `asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_80181C84/`. Draft `.run/P32/t5x/fable/func_80185810.c`;
report `.run/P32/t5x/reports/func_80185810.md`; harness `.run/P32/t5x/work/func_80185810/`. Three of four windows closed (P_TAG
bitfield OT link + integer add `(otz<<2)+(u32)ob` for the addu operand order; sched1 `flush_pending_lists` at the 33rd memory op
explains the load order → HI temps t20/t22 with tp loaded between loads and stores; pins uu `$4` / mode `$5` / ot16 `$6` — a hard-reg
destination is NOT birthing-boosted, so the LUID tie-break gives the load order; shf pinned `$3`). **Residual ONE cause, idx
363–380:** `cl &= 0xFFFF` is an unboosted 2nd set whose anti-deps hold the w-chain's two `cl` reads — the zero-byte fence after
`p[7] |=` is needed (without it the reads float to the block head and take `$a0/$a1`: 43/51) yet it forbids sched2's fillers (`sll $a2`,
`andi $a3`, `li/subu`) from crossing into the tpage/code window. A fresh single-set `clx` is boosted but combine folds the `andi` via
`nonzero_bits(cl)` into any same-block consumer (59); 2-set `clx` unboosted (49/39/42); an arm-duplicated store does not cross-jump
(490 ins); a launder asm is a real move for block_alloc. **Next lever:** make `cl` single-set with its high half cleared at birth
(`cl = *(u16 *)…` or a shift form) so no fence is needed, or give the two reads a fresh copy combine cannot fold (a HImode/subreg
temp defeats `nonzero_bits`). 3,360-variant region-2 sweep best 14 — do not repeat.

### 4. NEXT — in order
0. **Preflight:** `git status --short | grep -v ghidra/` (empty) · `verbatim_check --strict` (5 == 5) · `make check-all` → 218/218 (R56 baseline). Prompt `/effort max` (R27) and WAIT.
1. **The hand pass on (b) → (c) → (d), one row at a time:** read the report, reproduce the residual with `rtu_match`, dump the RTL
   (`cc1_dumps.sh`), run the producer census where the residual is a frame/slot (§501-M), attribute the residual to a PASS and a dump
   line before the first probe (§501, accelerators (11)/(12)), then the row's next lever; ≤ ~10 draft probes per row before writing the
   verdict. A MATCH → bank + commit + `backlog.py render` + cookbook §501-N…; a plateau → `backlog.py log` (closeness, class, best draft,
   cost) — write "banked" only from the tool's printed success line; a PROVED verdict names the pass and the refuted producers (P9).
2. **T4b close:** `make clean && make extract-all && make check-all` (quote 218/218) · `make report` + `make report BINARY=main` ·
   `frontier_classify --json .run/P32/frontier_t4b_final.json` · refresh this block · commit · harness #13 done.
3. **T5 (Max, Tier 1 — prompt R27; WAIT for gate 2):** P7 walk (T0–T4b) → milestone demo (R22 218/218 · tools-health · verbatim 5==5 ·
   the final census · the wall ledger — ONE pin, PROVED · `make audit-disc` UNCLAIMED 0 of 220 · `make report` ×3 metrics + main
   `143dbb89…` WITH and WITHOUT the SDK object dirs · denominators) → WAIT → `PhaseEnd_Phase32.md` (Build Log · Deviations incl.
   the T4b directive and the remainder stated plainly · Commit Message · Rules Added — R64 to RATIFY + the S83/S84 candidates
   below · Changelog v1.30.0 → v1.31.0 · Roadmap delta: P33 = verify + public flip · Plain-English Recap · believed/failed/sooner ·
   🛑) → DIGEST.md §2/§3 (step 3b) → `git mv phase-ends/CURRENT_PHASE.md phase-ends/logs/Phase32.md` (R19) → R23 → leave both
   uncommitted for Drew (R6) → "PhaseEnd file created. Commit the file and start a new Claude Code session for the next phase." →
   HARD STOP (P8). **Rule candidates for the PhaseEnd table:** (i) a wall verdict must be PASS-attributed with a dump line
   (R40 → "exonerate the instrument, then name the pass"); (ii) write "banked" only from the tool's printed success line; (iii) agents
   write deliverables early (a dead run's draft banked); (iv) a helper must refuse an empty work list (R43 restated); **(v) S84: a
   residual gets a PRODUCER CENSUS from the compiler source before a spelling sweep, and "PROVED" means every producer refuted on the
   bytes (accelerators (12)); (vi) S84: a ledger's tie-break is part of the instrument — a re-verdict that cannot surface is a silent
   skip (backlog.py kept the earliest record at equal closeness; R43/R61 family).**

### 5. Files, tools, exact invocations, gotchas
- **`.run/P32/t4c/`** (S84, tracked: `dump.sh` (private dump + census, writes `dumps_<tag>/` under t4c), `check_all_preflight.log`,
  `func_80032A74/{NOTES.md,lhu_tuclean.c,p1..p18.c}`; ignored: `dumps_*/`, `rtu/`). **`.run/P32/t5x/`** (tracked: BRIEF.md, targets.json,
  `fable/func_*.c` (15), `reports/*.md` (15), `verdicts.jsonl`; untracked: packs/, work/, rtu/). **`.run/P32/t4b/`** (tracked:
  `<fn>/NOTES.md|HYPOTHESIS.md`, `<fn>/*.c`, `*.log`). **`.run/P32/t3s3/`**: `bank.sh` (env `SPLIT=`, `DRAFT_DIR=`), `splice.py`, logs.
  **`.run/c294/dumps_*`**: `cc1_dumps.sh` output (regenerable).
- **`tools/ghost_census.py <tag>.i.lreg`** — headers with no occurrence in the post-sched stream: `ST_REGS or none` ⇒ an 8-byte slot
  (combine-minted); `GR_REGS …` ⇒ allocatable, no slot. `tools/cc1_dumps.sh` runs it and prints `vars=` (the arbiter).
- **Gotchas that bit in S84:** `rtu_match` on a MAIN function needs `--asm-subdir asm/nonmatchings/<sub>` (its default is the overlay
  layout: "No such file … asm/ov_SC01_077/nonmatchings/…") · `.run/P32/t4b/func_80032A74/lhu.c` carries the TU-provided typedefs
  (`Rec14`, `Slot54` …) and FAILS cc1 in the real TU — use the `*_tuclean.c` drafts (`cdecl.strip_provided_typedefs`) · a mechanism probe
  must keep the temp's LAST mention after the variable's (cse `make_regs_eqv` canonicalizes the shorter-lived reg away) and sched can
  sink a protecting store below a copy · `backlog.py` ties are now latest-wins (repaired) · the cookbook index does not index the bold
  `§501-x` sub-entries (only `## §` headings) — `--check` stays green after appending one.
- **Gotchas from S83 (still live):** `gate_main --assert-baseline --allow-dirty` RESTORES the working tree's TUs before building (use an
  in-tree `make extract BINARY=main && make build BINARY=main` for an uncommitted TU edit) · `make extract BINARY=main` rewrites main's
  `asm/` — never while something reads those `.s` files · a bank helper called with no function name built the unchanged tree and
  exited 0 (fixed, R43) · backticks inside a double-quoted `--where` argument are command substitution (use single quotes) ·
  `.run/P32/**` allowlists are per-subdir — an ignored path silently breaks a `git add … &&` chain · an agent's masked_diff probe in
  `src/` is build input (Makefile guard `commit:3949`).

### 6. Environment
Fleet 218; shas: main `143dbb89f34491258bbc27810d0a12ec8b43a8dd` · md_MAIN_007 `2ff702b605ab5cfc18474c464c4c07e5f8ffd48c` · ov_SC03_105
`d305ff6da199b52d0d44023766643a8b661ed524` (`config/check.<b>.sha` is authoritative). Toolchain unchanged (SETUP §5.4). The SessionStart
hook launches a headless Ghidra MCP (`.run/ghidra-mcp.log`); nothing in T4b/T5 uses it (R23: never stage `ghidra/`). Claude commits,
Drew pushes.

### 7. Standing reminders
Every bank commits before the next command that can touch `src/` (R42) · count banks from the SOURCE and quote the fleet's green count
at every close (R58) · verify a build from its exit code (R53) · a masked/permuter score is not a closeness until its diff is read
(R63) · an `__asm__` body that reproduces instructions is a verbatim, not a bank (R62; zero-byte fences/launders are dials) · re-verify in
the CURRENT TU before splicing (§500-F) · attribute a residual to a PASS before sweeping levers (§501, accelerators (11)) · census the
PRODUCERS of a frame residual before any spelling (§501-M, accelerators (12)) · write "banked" only from the tool's printed success
line · rules check every 4 tasks (P6) · harvest into the cookbook before the next drafting step (R16/R30) · no `Co-Authored-By` (R5) ·
never stage `ghidra/` (R23).

**Plain-English recap (R18).** This session took the first of the four leftover functions — the one that was a single instruction
away — and, instead of trying more rewordings, listed every way the 1995 compiler can leave an unused slot in a function's stack
frame and struck each off against the bytes. The only way that could produce this slot at zero cost needs a signed 16-bit load, and
the original uses an unsigned one, so the function is now recorded as proved-unreachable by re-spelling, with the compiler pass named.
Along the way a genuinely new compiler quirk was found and measured (a temporary copied in and out of a variable leaves a ghost
register behind), a small measuring tool was written, an old one repaired, and a ledger bug fixed that had been hiding updated
verdicts. Three functions remain, each with its cause written down; nothing in the game's rebuilt code changed.
