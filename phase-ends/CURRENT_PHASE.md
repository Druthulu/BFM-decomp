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
- [ ] **T4b — crack and bank the final 15 (ADDED 2026-09-05 by Drew's directive, supersedes the kill gate: "anything that isn't the original hand-written asm or the PsyQ libs needs to be cracked and banked before we finish"; "before you spawn Fable agents, hand crack each and figure out the blocker to fix it")** (xHigh→Max recommended; Fable agents authorised AFTER the hand pass): for each of the 15 rows (8 NEAR + 7 walls) the coordinator hand-cracks — read the diff + the recorded mechanism, read the compiler (dumps + source), find the lever the record did not try, measure, bank through the verified chain (rtu in the real TU → bank.sh / gate_main) — and only then hands the leftovers to one Fable agent each (brief `.run/P32/t5x/BRIEF.md`). Plumbing landed first: `src/800_c.c` decl/extern edits byte-neutral (this commit). Work dirs `.run/P32/t4b/<fn>/`. **Hand pass DONE 2026-09-05 (S83): all 15 rows read against their diffs and the compiler; 22 spellings measured (all regressions), 0 banks; every row's blocker refined to a named mechanism with the untried lever written in `.run/P32/t4b/<fn>/NOTES.md` (func_80032A74: the transient caller-save area — reload1.c order proven; func_8017DF28: the block-move pseudo reuse vs reorg's branch-target hoist; func_80011380: the target's assignment shape; func_801834A4: sign-hoist vs const-hoist thresholds; …). TU plumbing for func_80039DEC/func_800391D4 committed byte-neutral (`commit:3953`). 15 Fable agents launched ~13:05 MDT (two usage-limit outages, resumed each time via SendMessage). **T4b (1): `main:func_800391D4` BANKED 143dbb89 (`commit:3956`) — a pinned wall: explicit promotion + insn_count pads 7→9 (§501); pin dropped. **T4b (2): `main:func_80039DEC` BANKED 143dbb89 (`commit:3959`) — a pinned wall: the natural switch with duplicated tails, so a2's raw copy keeps 4 refs and wins $a3 (§501-B); pins 7 → 5. **T4b (3): `md_MAIN_009:func_800CD674` BANKED d270f695 (`commit:3964`) — the $a3↔$t1 plateau: a 2-death pseudo is excluded from local_alloc; a fresh single-death pseudo for prim 4 + a zero-byte asm set on prim 3's copy against sched1's birthing boost (§501-C).** Remaining 12 in flight.**
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

## 🛑 SESSION CHECKPOINT — T4b IN FLIGHT: 15 Fable agents cracking the final 15 (2026-09-05 13:40 MDT; written by session 491895ad "S83"; SUPERSEDES the 12:45 block)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase29/30/31.md` and this
file, and nothing else (CLAUDE.md protocol, R64 candidate). Replay this block verbatim into your chat, state phase / done /
NEXT / effort, list the rules from the digest, then WAIT for Drew. **NEXT is T4b (Drew's directive 2026-09-05: every function
that is not original hand-asm or a PsyQ object must be cracked and banked before the phase closes; hand-crack first, Fable
agents after) — 15 Fable agents were launched at ~13:05 MDT by session 491895ad and may have finished into a dead session.**
Effort: xHigh (orchestration; Max for any hand-crack you do yourself — R27 prompt). RECOVERY ROUTE if the launching session
died: (1) `ls .run/P32/t5x/fable/` (the deliverables) + `.run/P32/t5x/reports/` (the evidence); (2) `.venv/bin/python
tools/agent_verdicts.py /tmp/claude-1000/-home-musashi-bfm-decomp/491895ad-3c84-4037-b04f-bf7e5ee16a0c/tasks/a*.output
--append .run/P32/t5x/verdicts.jsonl` (pass ONLY `a*.output` — 17 of those are the S83 Haiku agents, already banked; the 15
Fable rows are the ones whose `fn` is in `.run/P32/t5x/targets.json`); (3) re-verify every MATCH with `rtu_match` in the
CURRENT real TU and bank with `.run/P32/t3s3/bank.sh` (overlays/modules) or a `gate_main` slate (main), one commit per bank
(R42); (4) NEAR rows → backlog with cost; then T5. No Workflow / Ultracode.

### 1. Where we are
**Phase 32 — the last 21 + the parked 5 (short, kill-gated).** Gate 1 approved 2026-09-05 (Drew, plan mode, Max, Fable 5.1);
R44–R63 ratified then; R64 is a candidate (DIGEST §3). Tasks: **T0 ✓** `commit:3901` · **T1a ✓** `commit:3902` `commit:3904` ·
**T1b ✓** `commit:3903` `commit:3906` `commit:3907` · **T1c ✓** `commit:3908` · **T2a ✓** `commit:3909` · **T2b ✓** `commit:3911`
`commit:3912` `commit:3913` `commit:3914` (fleet 213 → 218) · **T2c ✓** `commit:3917` `commit:3918` `commit:3919` `commit:3920`, close
`commit:3921` · **T2d not needed** · **T3 ✓ CLOSED 2026-09-05 12:40 MDT** (launch `commit:3922`; banks 1–9 `commit:3923`..`commit:3931`;
S82 checkpoints `commit:3932` `commit:3933` `commit:3934`; S83 banks 10–38 `commit:3935`..`commit:3946` + `commit:3948`; S83 checkpoint
`commit:3947`; Makefile guard `commit:3949`; §500-G `commit:3950`; the T3-close commit = HEAD) · **T4 ✓ DONE 12:45 MDT** (`commit:3952`) · **T4b IN FLIGHT** (added by Drew's directive; plumbing `commit:3953`, hand pass
`commit:3954` — all 15 rows analysed, 22 spellings measured, 0 banks, blockers in `.run/P32/t4b/<fn>/NOTES.md`; 15 Fable agents
launched ~13:05 MDT from `.run/P32/t5x/BRIEF.md` + `packs/` + the NOTES; harness #13) · **T5 after T4b.** Fleet **218 binaries** (main + resident + 138 `ov_*` + 78
`md_*`). **Fleet R22 at the T3 close (after ALL S83 banks + the Makefile guard): **217+main extracted, 218 passed / 0 failed, exits 0/0/0 at 12:00 MDT**** (`.run/P32/t3s3/r22c_full.log`);
earlier S83 R22s 218/218 at 10:46 and 11:09. `make report` at the close: **instr 13,484,739 / 13,488,497 = 100.0% · distinct
5,812,831 / 5,816,589 = 99.9% (90,975 / 90,984 unique fns) · fn-count 363,199 / 363,214 = 100.00% · INCLUDE_ASM 15**; main:
REAL 783 · LINKED 1,256 · VERBATIM 3 · stubs 6 · byte-identical 2,085 / 2,091 = 99.71% · sha `143dbb89…`. Non-ghidra tree
clean at HEAD; the `ghidra/` churn (`db.*.gbf`, `~index.*`, `*.prp`) is R23 restart-noise — never stage it. Claude commits,
Drew pushes (R6; ~50 unpushed at this writing).

### 2. What S83 did (session 491895ad, 2026-09-05 10:10 → 12:40 MDT, xHigh, Fable 5.1) — T3 steps 0–9
**Banks: 29** (the 11 S82 MATCH rows, the 17 queued Haiku rows — 17/17 MATCH first pass — and `func_8001BC6C` cracked 6 → 0);
**census 44 → 15 stubs / 3,758 ins** (7 pinned walls + 8 NEAR); md_SC03_053/054/056 → 100% C; main 9 → 6 open. **Steps 0–7:**
preflight R22 218/218 → the 11 S82 rows banked (md_SC03_053 ×2; main ×2 via `gate_main`; md_SC03_054 `func_801EF6D8` 604 +
7 jump tables via the §303 derive stage, NO carve; md_MAIN_007 ×6 after the byte-neutral `func_800CF3B0` no-proto decl) →
R22 218/218 → the 9 NEAR ledgered → 17 Haiku agents launched at once from staged prompts, every verdict re-verified in the
CURRENT TU and banked by `bank.sh` (md_MAIN_007 ×6, md_MAIN_009 ×8, md_SC03_054 ×2, md_SC03_056 ×1) → R22 218/218 → checkpoint
`commit:3947`. **Step 8 (bounded tail):** `permuter_ils` 8×150 s -j3 on both REGALLOC-PERM seeds — `func_800CD674` plateau
(same `$a3↔$t1` pair, ledgered), `func_8001BC6C` masked 1 → R63 read → the `& 0xFF` width mutation dropped, the two sound
levers (idx after color; early `tag`/`k` birth) re-spelled well-defined `k = 0; tag = (a1 << 8) | k;` → rtu MATCH → `gate_main`
BANKED `143dbb89` (`commit:3948`). `gate_main`'s first rebuild died on a concurrent agent's `src/.masked_diff_probe.<pid>.c` →
Makefile `C_SRCS` find `-not -name '.*'` (`commit:3949`, byte-neutral, controlled). One bounded Opus second look at
`func_800CF3E8` (245k tokens, 29 min, ~16k compiles): 27 HOLDS; §500-D1's mechanism corrected to `cse.c find_best_addr`
(fold_rtx MEM; COST pseudo 0 vs hard reg 1), the alias lever refuted 5/5, a new zero-byte pinned-pointer launder found
(79 @ 470, structurally closer) — cookbook §500-H, backlog row updated with cost. **Step 9:** `make report`, `make report
BINARY=main`, census `.run/P32/frontier_t3_close.json`, `twin_rescan` 0 free, cookbook §500-F/G/H + index, this file.
**Kill gate:** 29 banks + 3 new verdicts this session; the tail's three bounded attempts are spent → T3 closes on the evidence.
**Integration classes learned (§500-F):** two drafts of one TU can each MATCH alone and fail together (same-symbol
spellings, §304 self-defining rodata ×3, a prototype a sibling bank introduced) — the BUILD is the batch verdict; re-verify
in the CURRENT TU right before splicing. **Nothing under `config/` changed this session; `src/` changed only by the banks.**

### 3. Census — 15 stubs / 3,758 ins (`.run/P32/frontier_t3_close.json`; 7 pinned walls + 8 NEAR, 0 undrafted)
| binary | stubs · ins | rows |
|---|---|---|
| main | 6 · 1,381 | **NEAR (backlog):** func_80039308 518 → 17 (`.run/P32/t3/opus/func_80039308.c`, TU `src/800_c.c`; sched2 + cross-block regalloc + 11 rows of one alias fact) · **WALLS (pinned, `config/wave_exclude.txt`, T4):** func_80011380 192 (boot −O0; `.run/m3/opus/func_80011380.c` DIFF 6) · func_80032A74 422 (800_b_2; the S79w draft is a CC1 FAIL in the TU — §376 re-probe first; the census prints closeness 1 from a stored masked diff) · func_80020DA4 100 (`.run/S79w/sonnet/func_80020DA4.c` DIFF 2) · func_80039DEC 74 (S79w drafts CC1 FAIL — def-side decl, §495) · func_800391D4 75 (S79w sonnet draft CC1 FAIL `conflicting types for D_80073140`) |
| md_MAIN_009 | 2 · 421 | NEAR func_800CD674 174 → 2 REGALLOC-PERM `$a3↔$t1` (permuter plateau S83; `…/opus/func_800CD674.c`) · func_800CD92C 247 → 15 §S7 prologue weave (`…/opus/func_800CD92C.c`) |
| md_MAIN_007 | 2 · 427 | NEAR func_800CF408 178 → 49 [permuter] 3 hunks · func_800CF6D0 249 → 137 sched1 class tie (`…/opus/`) |
| md_MAIN_003 | 1 · 469 | NEAR func_800CF3E8 469 → 27 — §500-H: `cse.c find_best_addr` basin; the alias lever REFUTED; the pinned-pointer launder gets 79 @ 470; a CANDIDATE wall unless a new idiom places the freed load at slot 380 (`…/opus/func_800CF3E8.c` = `…_s83.c`) |
| ov_SC03_105 | 2 · 595 | NEAR func_80185810 489 → 35 [permuter] 4 emission windows (`…/opus/func_80185810.c`) · WALL (pinned) func_801834A4 106 (`.run/S71_gate14/ov_SC03_105*/func_801834A4.c` DIFF 6) |
| ov_SC06_022 | 1 · 119 | WALL (pinned) func_8017DF28 119 (`.run/S79w/sonnet/func_8017DF28.c` DIFF 2) |
| ov_SC07_002 | 1 · 346 | NEAR func_8017DC80 346 → 46 reload-slot frame + `la $a0` slot (`…/opus/func_8017DC80.c`) |

Modules at 100% C after S83: resident (145/145), md_SC03_053, md_SC03_054, md_SC03_056. **The 39 T3 banks:** the 10 of the
launching session (§500-A) + S83's 29 (`git log --oneline commit:3934..HEAD`). Backlog: `docs/backlog.md` 14 open near-misses
(every NEAR row carries class · closeness · best draft · cost, R41). `verdicts.jsonl`: 50 rows.

### 4. NEXT — T4b results, then T5
0. **Preflight:** `git status --short | grep -v ghidra/` (empty) · `verbatim_check --strict` (5 == 5) · `make check-all` (218/218) —
   and the RECOVERY ROUTE in §0 if the Fable agents finished into a dead session.
1. **Per Fable result (never in bulk):** `grep -c '\.ent\|\.word\|__asm__' <draft>` (an `__asm__` body is a verbatim, R62 — zero-byte
   launders/fences/pins are fine) → your OWN `rtu_match` in the CURRENT real TU (main rows: `--tu src/<sub>.c`; boot: `--o0`) →
   overlays/modules: `.run/P32/t3s3/bank.sh <binary> <tu> <asmdir> fable "<title>" <fn>` (it refuses on red) · main: a
   `gate_main` slate with the ABSOLUTE draft path, `--apply`, read the BANKED/BYTE-IDENTICAL line → `git add <tu>` + commit
   (R42) → `twin_rescan`. A MATCH whose draft depends on the TU's declarations is fine; a `CC1 FAIL` names a spelling to adopt.
2. **NEAR results:** `tools/backlog.py log … --closeness N --source "P32-T4b Fable agent <cost>"` with the mechanism; if a row is
   pinned in `config/wave_exclude.txt`, update its comment line; `exclude_audit --assert-fresh config/wave_exclude.txt`.
3. **Harvest (R16/R30):** every new idiom → cookbook §501 (T4b) + index regen; `docs/accelerators.md`; decision-log (R31) if the
   finish-line doctrine changes; `make report`; census `frontier_classify --json .run/P32/frontier_t4b_close.json`; fleet R22
   after the banks (`make clean && make extract-all && make check-all`, quote the count); refresh this block; commit.
4. **Then T5 — the PhaseEnd (Max, Tier 1: prompt R27 and WAIT for `/effort`):** P7 walk (T0–T4b) → milestone demo → **WAIT for
   gate 2** → `PhaseEnd_Phase32.md` (Build Log · Deviations incl. the T4b directive and its outcome · Commit Message · Rules
   Added — R64 to RATIFY + candidates · Changelog v1.30.0 → v1.31.0 · Roadmap delta: P33 = verify + public flip · Plain-English
   Recap · believed/failed/sooner · 🛑) → DIGEST.md §2/§3 (step 3b) → `git mv phase-ends/CURRENT_PHASE.md phase-ends/logs/Phase32.md`
   (R19) → R23 → leave both uncommitted for Drew (R6) → "PhaseEnd file created. Commit the file and start a new Claude Code
   session for the next phase." → HARD STOP (P8). If any of the 15 remain open at T5, the PhaseEnd says so (P9) with each
   row's mechanism, cost and best draft — never redefined.

### 5. Files, tools, exact invocations, gotchas
- **`.run/P32/t4b/<fn>/`** (S83 hand pass; tracked `*.md`, `*.c`): `NOTES.md`/`HYPOTHESIS.md` per row (mechanism + measured spellings + the
  untried lever) and the variant drafts measured. **`.run/P32/t5x/`** (the Fable pass; tracked BRIEF.md, targets.json, `fable/func_*.c`,
  `reports/*.md`; untracked packs/ work/ rtu/): one agent per row, budget ~2 h each, final message = the JSON line.
- **`.run/P32/t3s3/` (S83; tracked: `*.sh *.py *.log *.txt prompts/ gate/*.json gate/*.log`; untracked: `verify*/` compile
  dirs):** `splice.py <tu> <asmdir> <fn> <draft>` (asserts the INCLUDE_ASM line occurs once, replaces it with the draft) ·
  `bank.sh <binary> <tu> <asmdir> <arm> "<commit title>" fn…` (the per-TU bank chain; refuses on `__asm__`/`.word` in a
  draft, any rtu non-MATCH, build rc≠0 or sha mismatch, and never commits on red — the tree is left for diagnosis) ·
  `backlog_near.sh` (the 9 rows, re-runnable) · `prompts/<fn>.txt` (the 17 launched prompts) · `gate/slate_main{2,3}.json` +
  `gate/gate_main{2,3}.log` · `ils_func_*.log` (the two permuter runs) · `p1bc6c/` (the 11 func_8001BC6C spellings) · `r22_*.log` / `r22b_*.log` / `r22c_*.log` / `report_close.log` / `report_main_close.log` / `tools_health.log` / `build_*.log` / `bank_*.log` / `twin_rescan*.log`.
- **`.run/P32/t3/`:** `verdicts.jsonl` now 48 rows (31 + 17; the S83 rows carry `"session": "491895ad"`) · `haiku/` 28 drafts
  (all banked) · `opus/` 14 (banked S83: func_80015B6C, func_8002FDE8, func_801EF6D8, func_8001BC6C_s83; 8 NEAR incl. func_800CF3E8_s83 == the prior best) · `sonnet/` 4 (all
  banked) · `reports/` (the 31 S82 reports + 3 Haiku reports) · `pending_launch.txt` (EMPTY — all 17 launched 10:57) ·
  `BRIEF.md` (amended: §304 + exact-TU-spelling) · `PROMPT_TEMPLATE.md` · `harvest_notes.md`.
- **Transcripts of the 17 S83 agents:** `~/.claude/projects/-home-musashi-bfm-decomp/491895ad-3c84-4037-b04f-bf7e5ee16a0c/subagents/agent-<id>.jsonl`
  (`/tmp/claude-1000/-home-musashi-bfm-decomp/491895ad-3c84-4037-b04f-bf7e5ee16a0c/tasks/a*.output` are symlinks; the
  `b*.output` there are this session's Bash jobs). All 17 verdicts are already in `verdicts.jsonl`; `agent_verdicts.py
  <tasks>/a*.output` rebuilds them; `agent_reports.py` saves the full reports.
- **`rtu_match`:** `--split <sub> --source <binary> --c <draft> --asm-subdir <asmdir> --work <dir>`; **main adds `--tu
  src/<sub>.c`**; verdict line `MATCH (N ins)` / `DIFF` / `CC1 FAIL` (compile-only: BLIND to link-time §304 and to cross-draft
  same-TU conflicts — the BUILD is the batch verdict). **Build check:** `make build BINARY=<b> -j8`, read the EXIT CODE (R53;
  a failed build leaves the OLD binary in place — the printed sha is then stale). **`gate_main`:** the ONLY way to gate main
  (slate JSON of `{fn, draft(ABSOLUTE)}`, `--apply`). **Carves:** for `md_*` island tables do NOT carve (§303 — the derive
  stage prints the pad spec in the build log); for overlays `jtbl_carve.py <b> --func <fn>` → `make extract` (rc) → build →
  `pads_audit`/`interleave_check` (R60).
- **Gotchas that bit today:** two drafts of one TU can each MATCH alone and fail together (spelling / §304 / a prototype a
  sibling bank introduced) — always rtu in the CURRENT TU right before splicing (bank.sh does) · `backlog.py`/`corpus.stubs`
  raise `CorpusError … NO .s on disk` while `make extract-all` is running (the instrument's environment, not a defect — R40)
  · census `nins` counts `.s` lines incl. rodata `.word`s · agents read `asm/` — never launch them while a `make clean &&
  make extract-all` is in flight · the harness cap is 20 concurrent subagents · never `cd` inside a compound command ·
  `set -o pipefail` + `grep -c` exits 1 on zero matches.

### 6. Carried context for T5 (T4 is DONE — its ledger is the table above this block)
**T4 (xHigh, no drafting) — the dead session's read-only pre-check (07:00Z) still stands (re-run each in the CURRENT TU first — S83 changed src/800.c and src/800_b_2.c):** `exclude_audit --assert-fresh`: 7
entries, 7 WALL, 0 stale. Best drafts in their REAL TU: `main:func_80011380` `.run/m3/opus/func_80011380.c` DIFF 6 (the
ledger's `.run/backlog_drafts/func_80011380.c` is MISSING — R62 path fix) · `main:func_80032A74` `.run/S79w/opus/
func_80032A74.c` **CC1 FAIL** (`redefinition of struct Slot`/`Slot`, `conflicting types for A12`/`B12` vs
`src/800_shared.h:68/95` — §376 plumbing, re-probe before a final verdict, R40; the census prints closeness 1 for it from a
stored masked diff) · `main:func_80020DA4` `.run/S79w/sonnet/func_80020DA4.c` DIFF 2 · `main:func_80039DEC` both
`.run/S79w/{permuter,sonnet}/func_80039DEC.c` **CC1 FAIL** (`conflicting types for func_80039DEC` — def-side declaration,
§495: fix the TU's own decl first) · `main:func_800391D4` `.run/S79w/sonnet/func_800391D4.c` **CC1 FAIL** (`conflicting
types for D_80073140` at t.c:3310 vs :2622) · `ov_SC06_022:func_8017DF28` DIFF 2 · `ov_SC03_105:func_801834A4` S71_gate14
variants DIFF 6 (ledger `.run/backlog_drafts/func_801834A4.c` MISSING). Deliverables: each of the 7 rows PROVED vs
CANDIDATE with a current citation + an instrument-exonerated bounded attempt (R40 — the three CC1-FAIL rows get their §376
plumbing fixed byte-neutrally and are re-probed BEFORE any verdict), `exclude_audit --write`, `backlog.py render`, the wall
table into this file, cookbook §501 if a verdict changes, decision-log, accelerators. A T3 idiom naming a wall's mechanism
re-opens that row (one bounded attempt, permuter first).
**T5 (Max, Tier 1 — prompt R27; WAIT for gate 2):** P7 checkbox walk over every task above; milestone demo = R22 fleet
218/218 · `make tools-health` OK · `verbatim_check --strict` 5==5 · the final census (`tools/frontier_classify.py --json`) ·
the wall ledger · parked-5 dispositions via `make audit-disc` (UNCLAIMED 0 of 220 at T2c) · `make report` all three metrics +
main `143dbb89…` WITH and WITHOUT the SDK object dirs (`.run/obj40`, `.run/obj42`; fresh-extract fallback) · corrected
denominators (main game-code 41,556 — the 22-ins Ghidra-boundary gap; the fleet denominator grew by the five modules' ~2,600
ins at T2b). Then `PhaseEnd_Phase32.md` (+ Roadmap delta: P33 = verify + flip; + Plain-English Recap; + the rules table incl.
R64) → **append the P32 synopsis + rules to `phase-ends/DIGEST.md` (step 3b)** → `git mv CURRENT_PHASE.md
phase-ends/logs/Phase32.md` (R19) → R23 MCP stop if it ran → leave both uncommitted for Drew (R6) → 🛑.

### 7. Environment
Fleet 218; shas: main `143dbb89f34491258bbc27810d0a12ec8b43a8dd` · resident `8e17e02ff8954d07c979449198f7e1645046b353` ·
md_SC03_053 `c0848f308342e499e2bd8c2db86f6225a29e1592` · md_SC03_054 `06bd73dfbdb10748adcbac7093ead5d76131206a` · md_MAIN_007
`2ff702b605ab5cfc18474c464c4c07e5f8ffd48c` · md_MAIN_009 `d270f695b793b5c03db159b7aabcc066daa87eda` · md_SC03_056
`bc768a6b7baa911e0a0cb9175b33550851d6c1eb` (`config/check.<b>.sha` is authoritative). Toolchain unchanged (SETUP §5.4). The
SessionStart hook launches a headless Ghidra MCP (`.run/ghidra-mcp.log`); this session's MCP failed to connect and nothing
needed it — T4/T5 do not either (R23: never stage `ghidra/`). Harness: 20 concurrent Agent-tool subagents max. Metrics:
regenerate with `make report` at the T3 close (218 binaries; last published = P31 close, 213 binaries: instr 100.0% ·
distinct 99.9% · fn 99.99%).

### 8. Standing reminders (the rules that bite now)
Every bank commits before the next command that can touch `src/` (R42) · count banks from the SOURCE and quote the fleet's
green count at every close (R58) · verify a build from its exit code (R53) · a masked/permuter score is not a closeness until
its diff is read (R63) · an `__asm__` body is a verbatim, not a bank (R62) · fix the TU by a byte-neutral plumbing commit
BEFORE any gate (S77 law) · re-verify in the CURRENT TU before splicing (§500-F) · rules check every 4 tasks (P6) · harvest
idioms into the cookbook before the next drafting step (R16/R30) · no `Co-Authored-By` (R5) · never stage `ghidra/` (R23).

**Plain-English recap (R18).** This session finished the crack pass. Twenty-nine functions were banked byte-for-byte: the
ten exact matches the overnight agents had produced, seventeen small functions drafted by seventeen cheap agents launched
together (all seventeen exact on the first try), and one stubborn near-miss that the brute-force polisher found the key
to — after we threw away the part of its answer that was actually wrong. Three code modules are now fully rebuilt from C,
and every rebuild of all 218 files stayed identical. Of the sixteen leftovers, one careful second look confirmed a
near-miss really is stuck (and corrected our explanation of why), and the rest are the seven long-standing "walls" plus
seven near-misses with their causes written down. Next: the walls get their final written verdicts, then the phase closes.
