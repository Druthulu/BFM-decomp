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
- [ ] **T3 — one bounded crack pass, Opus agents, one per function** (xHigh orchestration — prompt R27):
      **IN PROGRESS — 47/47 drafted, 38 BANKED (10 in the launching session + 28 in S83 = 2,111 + ~2,800 ins; commits `commit:3923`..`commit:3931`, `commit:3935`..`commit:3946`), 9 NEAR ledgered in the backlog, 0 FAIL outstanding; the 17 queued Haiku rows went 17/17 MATCH (S83). Census 16 stubs / 3,827 ins = 7 pinned walls + 9 NEAR (`.run/P32/frontier_t3s3_haiku.json`); md_SC03_053/054/056 100% C; resident 145/145. Remaining in T3: step 8 (bounded NEAR tail: permuter_ils ×2 + one Opus look) and the close (step 9). Earlier checkpoints: 09:30 / 10:01 MDT (the launching coordinator overflowed at 07:07Z; the S82 successor recovered 22 verdicts).** Original brief:
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
- [ ] **T4 — the walls' FINAL verdicts** (xHigh; no drafting): the 8 pinned rows — confirm each citation current
      + instrument exonerated (R40), PROVED vs CANDIDATE, ledger best-draft → an existing real-TU-clean C file (R62:
      `func_80011380` → `.run/m3/opus/func_80011380.c`; `func_801834A4` → `.run/S71_gate14/ov_SC03_105*/`),
      `exclude_audit --write`, `backlog.py render`; a T3 idiom naming a wall's mechanism re-opens that row
      (bounded: one attempt, permuter first). Wall table into this file; cookbook §496+; decision log; accelerators.
- [ ] **T5 — PhaseEnd** (Max, Tier 1 — prompt R27): P7 checkbox walk; milestone demo (R22 fleet N/N, tools-health,
      `verbatim_check --strict`, final census, wall ledger, parked-5 dispositions via `make audit-disc`,
      `make report` all three metrics + main `143dbb89…` with/without SDK dirs, corrected denominators); **WAIT
      for gate 2**; `PhaseEnd_Phase32.md` (+ Roadmap delta + Plain-English Recap); `git mv` this file →
      `phase-ends/logs/Phase32.md` (R19); R23 MCP stop if it ran; leave both uncommitted for Drew (R6); 🛑 (P8).

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

## 🛑 SESSION CHECKPOINT — T3 STEPS 0–7 DONE, STEP 8 NEXT (2026-09-05 11:30 MDT; written by session 491895ad "S83"; SUPERSEDES the 10:01 block)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase29/30/31.md` and this
file, and nothing else (CLAUDE.md protocol, R64 candidate). Replay this block verbatim into your chat, state phase / done /
NEXT / effort, list the rules from the digest, then WAIT for Drew. When he confirms, follow §4 in order. **Effort: xHigh
for the rest of T3 and for T4** (R27 — Drew sets it; if the status line does not say xHigh, prompt before the first
command); **Max only for T5.** Fable only if a wall class the codegen map lacks appears — STOP and prompt Drew first. No
Workflow / Ultracode: one Agent-tool subagent per function where an agent is used at all.

### 1. Where we are
**Phase 32 — the last 21 + the parked 5 (short, kill-gated).** Gate 1 approved 2026-09-05 (Drew, plan mode, Max, Fable 5.1);
R44–R63 ratified then; R64 is a candidate (DIGEST §3). Tasks: **T0 ✓** `commit:3901` · **T1a ✓** `commit:3902` `commit:3904` ·
**T1b ✓** `commit:3903` `commit:3906` `commit:3907` · **T1c ✓** `commit:3908` · **T2a ✓** `commit:3909` · **T2b ✓** `commit:3911`
`commit:3912` `commit:3913` `commit:3914` (fleet 213 → 218) · **T2c ✓** `commit:3917` `commit:3918` `commit:3919` `commit:3920`, close
`commit:3921` · **T2d not needed** · **T3 steps 0–7 ✓** (launch `commit:3922`; banks 1–9 `commit:3923` `commit:3924` `commit:3925`
`commit:3926` `commit:3927` `commit:3928` `commit:3929` `commit:3930` `commit:3931`; S82 checkpoints `commit:3932` `commit:3933` `commit:3934`;
S83 banks 10–37: `commit:3935` `commit:3936` `commit:3937` `commit:3938` `commit:3939`(plumbing) `commit:3940` `commit:3941` `commit:3942`
`commit:3943` `commit:3944` `commit:3945` `commit:3946`; the S83 checkpoint commit = HEAD) · **T3 step 8 (bounded NEAR tail) and
step 9 (close) pending · T4, T5 pending.** Harness task list #1–#12 exists (#6 §5.5 and #8 §5.7 in_progress at this writing;
#9 = step 8 next). Fleet **218 binaries** (main + resident + 138 `ov_*` + 78 `md_*`). **Last full R22: 218 passed / 0 failed,
exits 0/0/0 at 10:46 MDT** (`.run/P32/t3s3/r22_full.log`, BEFORE the 17 Haiku banks); **post-batch R22 (after all 28 S83
banks): **217+main extracted, 218 passed / 0 failed, exits 0/0/0 at 11:09 MDT**** (`.run/P32/t3s3/r22b_full.log`). tools-health OK at 10:57 (`.run/P32/t3s3/tools_health.log`).
Non-ghidra tree clean at HEAD; the `ghidra/` churn (`db.*.gbf`, `~index.*`, `*.prp`) is R23 restart-noise — never stage it.
Claude commits, Drew pushes (R6; ~45 unpushed at this writing).

### 2. What S83 did (session 491895ad, 2026-09-05 10:10 → 11:30 MDT, xHigh, Fable 5.1)
Followed the 10:01 block's §5 in order. (0) Preflight: tree clean, verbatim 5==5, `make check-all` 218/218 rc 0. (1)–(4) The
11 S82 MATCH rows banked — each re-verified with `rtu_match` in the real TU first: md_SC03_053 `func_801EF734` 44 +
`func_801EF7E4` 72 (→ **100% C**); main `func_80015B6C` 120 + `func_8002FDE8` 73 via `gate_main` ("slate 2 -> 2 compatible,
0 dropped … BANKED 2 main functions -- 143dbb89 BYTE-IDENTICAL", `.run/P32/t3s3/gate/gate_main2.log`); md_SC03_054
`func_801EF6D8` 604 code ins + 7 jump tables — `jtbl_carve --probe` REFUSED the tail carve (tables in the §154-A leading
island 0x4..0xF0) and named §260, but for an `md_*` module **§303 applies: splice + build, the Makefile's `jtbl_rodata_pads
--derive` stage printed `0,0t1,0t1,0t1,0t1,0t1,0` and the sha held with NO carve-state change** (probe text amended);
md_MAIN_007: the byte-neutral no-proto decl commit for `func_800CF3B0` (`commit:3939`, sha unchanged) then six drafts — the
batch exposed two integration classes `rtu_match` cannot see (it splices ONE draft): same-TU `s16`/`u16` spellings of
`D_800B99E8` (fixed to the LOAD's `u16`), and §304 self-defining rodata (`D_800CEDFC` = `.asciz "C:\TIMPACK\OPDEMO0.PAT"`,
defined `const char[]` at file scope at the extern's position, `(void *)` cast at the call). (5) `twin_rescan` 33 open / 0
free; verbatim 5==5; **R22 `make clean && make extract-all && make check-all` → 217+main extracted, 218 passed / 0 failed,
exits 0/0/0**; `make tools-health` OK. (6) The 9 NEAR rows ledgered via `.run/P32/t3s3/backlog_near.sh` (docs/backlog.md 15
open). (7) The 17 queued Haiku rows dequeued, prompts staged (`.run/P32/t3s3/prompts/<fn>.txt` = PROMPT_TEMPLATE + two
integration sentences) and launched at 10:57 as 17 Agent-tool subagents (model haiku); **17/17 MATCH by 11:15** (43–57k
tokens, 46–126 s each); every verdict re-run by the coordinator with `rtu_match` in the CURRENT TU and banked with
`.run/P32/t3s3/bank.sh` (verbatim grep → rtu ×N → splice ×N → ONE build → sha vs `config/check` → commit only on green):
md_MAIN_007 ×6 → 2 open (both NEAR), md_MAIN_009 ×8 → 2 open (both NEAR; `func_800CD520` needed a §376 re-spell of
`func_8001AD38` to the TU's `(const char*)` after a sibling bank added the file-scope prototype), md_SC03_054 ×2 (→ **100%
C**), md_SC03_056 ×1 (→ **100% C**). `twin_rescan` 16 open / 0 free. **Harvest (R16/R30):** cookbook **§500-F** (yield +
the four integration classes), `.run/P32/t3/BRIEF.md` (the §304 sentence + exact-TU-spelling), `.run/P32/t3/harvest_notes.md`,
`tools/jtbl_carve.py` probe text (§303 for `md_*`), `.run/P32/t3/verdicts.jsonl` (+17 rows, `"session": "491895ad"`),
`.gitignore` allowlist for `.run/P32/t3s3/`. **Nothing under `config/` changed this session; `src/` changed only by the
banks listed above.**

### 3. Census — 16 stubs / 3,827 ins (`.run/P32/frontier_t3s3_haiku.json`; 7 pinned walls + 9 NEAR, 0 undrafted)
| binary | stubs · ins | rows |
|---|---|---|
| main | 7 · 1,450 | **NEAR (backlog):** func_80039308 518 → 17 (`.run/P32/t3/opus/func_80039308.c`, TU `src/800_c.c`) · func_8001BC6C 69 → 6 REGALLOC-PERM `$v0↔$v1` (`…/opus/func_8001BC6C.c`, TU `src/800.c`) · **WALLS (pinned, `config/wave_exclude.txt`, T4):** func_80011380 192 (boot −O0; `.run/m3/opus/func_80011380.c` DIFF 6) · func_80032A74 422 (800_b_2; census closeness 1 from a stored draft — the S79w draft is a CC1 FAIL in the TU, §376 re-probe first) · func_80020DA4 100 (`.run/S79w/sonnet/func_80020DA4.c` DIFF 2) · func_80039DEC 74 (S79w drafts CC1 FAIL — def-side decl, §495) · func_800391D4 75 (S79w sonnet draft CC1 FAIL `conflicting types for D_80073140`) |
| md_MAIN_009 | 2 · 421 | NEAR func_800CD674 174 → 2 REGALLOC-PERM `$a3↔$t1` (`…/opus/func_800CD674.c`) · func_800CD92C 247 → 15 §S7 prologue weave (`…/opus/func_800CD92C.c`) |
| md_MAIN_007 | 2 · 427 | NEAR func_800CF408 178 → 49 [permuter] 3 hunks · func_800CF6D0 249 → 137 sched1 class tie (`…/opus/`) |
| md_MAIN_003 | 1 · 469 | NEAR func_800CF3E8 469 → 27 pinned-base alias basin §500-D1 (`…/opus/func_800CF3E8.c`) — the ONE untested lever: an unpinned alias of `p6` for the tag load alone |
| ov_SC03_105 | 2 · 595 | NEAR func_80185810 489 → 35 [permuter] 4 emission windows (`…/opus/func_80185810.c`) · WALL (pinned) func_801834A4 106 (`.run/S71_gate14/ov_SC03_105*/func_801834A4.c` DIFF 6) |
| ov_SC06_022 | 1 · 119 | WALL (pinned) func_8017DF28 119 (`.run/S79w/sonnet/func_8017DF28.c` DIFF 2) |
| ov_SC07_002 | 1 · 346 | NEAR func_8017DC80 346 → 46 reload-slot frame + `la $a0` slot (`…/opus/func_8017DC80.c`) |

Modules at 100% C after S83: resident (145/145), md_SC03_053, md_SC03_054, md_SC03_056. **The 38 T3 banks:** the 10 of the
launching session (§500-A) + S83's 28 (`git log --oneline commit:3934..HEAD`). Backlog: `docs/backlog.md` 15 open near-misses
(the 9 NEAR rows carry class · closeness · best draft · cost "1 Opus agent, 30–70 min", R41).

### 4. NEXT — in order (R42: commit before the next command that can touch src/; a bank that lands goes through bank.sh)
0. **Preflight:** `git status --short | grep -v ghidra/` (empty) · `.venv/bin/python tools/verbatim_check.py --strict` (5 == 5)
   · `make check-all` → **218 passed, 0 failed of 218, exit 0** (the R22 baseline before any bank; if any binary is red, fix the baseline first — R56).
1. **T3 step 8 — the bounded NEAR tail (xHigh; the kill gate stands: no bank + no new verdict ends T3):**
   (a) `permuter_ils` on the two REGALLOC-PERM seeds, §494 recipe, run in the background with logs (R55):
   `.venv/bin/python tools/permuter_ils.py func_800CD674 --draft .run/P32/t3/opus/func_800CD674.c --asm-subdir
   asm/md_MAIN_009/nonmatchings/md_MAIN_009 --klass REGALLOC --cycles 8 --secs 150 --j 3 > .run/P32/t3s3/ils_func_800CD674.log 2>&1`
   and the same for `func_8001BC6C` (`--draft .run/P32/t3/opus/func_8001BC6C.c --asm-subdir asm/nonmatchings/800` — confirm the
   asm dir from `corpus.stubs('main')`/`targets.json` `asm` field before running). **Read every reported score's DIFF before
   calling it a closeness (R63)**; a 0 → `rtu_match` in the real TU → bank.sh (main: gate_main slate instead).
   (b) ONE Opus second look at `func_800CF3E8` (md_MAIN_003, 469 → 27) with the single untested lever named in §500-D1 /
   the backlog row (an unpinned alias of `p6` for the tag load alone); prompt shape = PROMPT_TEMPLATE's Opus row +
   `.run/P32/t3/reports/func_800CF3E8__opus__*.md` as the prior; draft path `.run/P32/t3/opus/func_800CF3E8_s83.c` (never
   overwrite the ledger's best draft); the agent's final message is the JSON line only. Plateaus stay in the backlog
   (`tools/backlog.py log … --closeness N`), each with its cost (R41).
2. **T3 step 9 — close:** any new idiom → cookbook §500-G (R16/R30) + `harvest_notes.md`; `make report` (regenerates
   `docs/progress*.md`, `docs/difficulty.md`); `frontier_classify --json .run/P32/frontier_t3_close.json`; refresh this
   block; commit; **progress report to Drew**; mark harness #8/#9/#10 done.
3. **T4 (xHigh, no drafting)** — §6 below. 4. **T5 (Max, Tier 1 — prompt R27; WAIT for gate 2)** — §6 below.

### 5. Files, tools, exact invocations, gotchas
- **`.run/P32/t3s3/` (S83; tracked: `*.sh *.py *.log *.txt prompts/ gate/*.json gate/*.log`; untracked: `verify*/` compile
  dirs):** `splice.py <tu> <asmdir> <fn> <draft>` (asserts the INCLUDE_ASM line occurs once, replaces it with the draft) ·
  `bank.sh <binary> <tu> <asmdir> <arm> "<commit title>" fn…` (the per-TU bank chain; refuses on `__asm__`/`.word` in a
  draft, any rtu non-MATCH, build rc≠0 or sha mismatch, and never commits on red — the tree is left for diagnosis) ·
  `backlog_near.sh` (the 9 rows, re-runnable) · `prompts/<fn>.txt` (the 17 launched prompts) · `gate/slate_main2.json` +
  `gate/gate_main2.log` · `r22_*.log` / `r22b_*.log` / `tools_health.log` / `build_*.log` / `bank_*.log` / `twin_rescan*.log`.
- **`.run/P32/t3/`:** `verdicts.jsonl` now 48 rows (31 + 17; the S83 rows carry `"session": "491895ad"`) · `haiku/` 28 drafts
  (all banked) · `opus/` 12 (2 banked S83: func_80015B6C, func_8002FDE8, func_801EF6D8 → 3 banked; 9 NEAR) · `sonnet/` 4 (all
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

### 6. Carried context for T4 and T5
**T4 (xHigh, no drafting) — the dead session's read-only pre-check (07:00Z) still stands:** `exclude_audit --assert-fresh`: 7
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

**Plain-English recap (R18).** This session banked twenty-eight functions in about an hour: first the ten exact matches the
overnight agents had already produced (after re-checking each one byte-for-byte), then seventeen small functions drafted by
seventeen cheap agents launched together, every one of which came back exact on the first try. Three of the game's code
modules are now fully rebuilt from C, and the whole 218-file set still rebuilds identically. What is left is sixteen
functions: seven long-standing "walls" that get their final written verdicts next, and nine near-misses that are a few
instructions off, which get one bounded round with the brute-force polisher and one careful second look before the phase
closes.
