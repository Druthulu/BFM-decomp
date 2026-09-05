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
      **IN PROGRESS — checkpointed 2026-09-05 09:30 MDT (see the 🛑 block): 31/47 launched, 10 BANKED (1,063 ins, commits `commit:3923`..`commit:3931`), 10 more MATCH verified in the real TU awaiting the gate (1,049 ins) + 1 leaf-exact behind a TU decl, 9 NEAR at exact length, 17 Haiku rows still queued; the launching coordinator overflowed its context at 07:07Z. Census 44 stubs / 5,313 ins (`.run/P32/frontier_t3_checkpoint.json`).** Original brief:
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
- 2026-09-05 (successor session, later) — **Session-start protocol rewritten at Drew's direction (R64 candidate):** `phase-ends/DIGEST.md` created (every phase synopsis + every rule in full + the PROJECT_CONTEXT corrections + the doc map); CLAUDE.md load order = PROJECT_CONTEXT → DIGEST → the three most recent PhaseEnds → CURRENT_PHASE, ≈100k tokens, the 🛑 block replayed VERBATIM; Phase Boundary step 3b maintains the digest (P7); `phase-ends/README.md` + SETUP §7 updated; the two memories (`checkpoint-current-phase-before-pause`, `session-start-list-rules-in-full`) + MEMORY.md updated; `.run/P32/t3/PROMPT_TEMPLATE.md` saved (verbatim agent prompts). The 🛑 block below was REFRESHED to the verbatim-replay standard and SUPERSEDES the 09:30 block. Ratify R64 at PhaseEnd_Phase32.
- 2026-09-05 09:30 MDT — **T3 CHECKPOINT by the successor session (Max, Fable 5.1) after the launching session died.** The T3 coordinator (session c6a5fb71) banked 10 functions in 9 commits (T3 (1)–(9), 01:01–01:07 MDT) and then hit "Prompt is too long" at 01:07 MDT; 22 agent completions (07:07Z–08:04Z) arrived into a dead session. Recovered via the recorded route: `agent_verdicts.py` over the 31 task transcripts → `.run/P32/t3/verdicts.jsonl` (20 MATCH / 9 NEAR / 2 FAIL); every unbanked draft re-verified with `rtu_match` in its real TU (10 MATCH confirmed). **Instrument incident (R48 class):** one agent's tidy-up (`find .run/P32/t3/opus -maxdepth 1 -type f ! -name func_800CD674.c -exec mv {} _scratch/`, 07:52Z) had swept 11 sibling Opus deliverables — found in `_scratch/`, moved back, byte-verified at the reported closeness; `tools/agent_drafts_restore.py` (NEW — transcript replay) written as the fallback; `.gitignore` allowlist for `.run/P32/**` so the drafts/ledger/census are committed (R20). Harvest written IN-SESSION (R16/R30): cookbook **§500** (10 banked closers, 10 MATCH closers, 9 NEAR classes, two NEW mechanisms — the pinned-base alias basin and `#line`-equalised ASM_OPERANDS — and the process defects); `docs/wave-playbook.md` §S80 addendum-2 (per-function work dirs, JSON-only final message, the 20-agent cap, the recovery tools); `docs/accelerators.md` P32 T3; `docs/decision-log.md` P32 S82 (R31); SETUP row (R21). Read-only T4 pre-check results from the dead session preserved in the 🛑 block. Effort: this checkpoint at Max; **T3 resumes at xHigh** (R27).
- 2026-09-05 — gate 1 approved; T0 opened at HEAD `commit:3900`.
- 2026-09-05 — **T3 LAUNCHED** (xHigh): 47 targets = census 54 − 7 pinned walls (`.run/P32/t3/targets.json`, 5,288 ins); packs built (`claude_wave_packs`, 47/47 neighbours, 10 journals); brief `.run/P32/t3/BRIEF.md`. **20 Agent-tool drafters running** (16 Opus: the 11 old near/far rows + resident func_800D06E8 + the 4 largest new bodies · 3 Sonnet · 1 Haiku); **27 Haiku queued** behind the harness's 20-concurrent cap (`.run/P32/t3/pending_launch.txt`, launched one per freed slot). Recovery + per-result route: `.run/P32/t3/LAUNCHED.md`.
- 2026-09-05 — **T2c DONE (R22 218/218 rc 0) · T2d not needed.** Twenty of the 56 new stubs fell to twin remaps and constant flips (0 tokens); the rest (36, all ≤50 ins but one, never drafted) join T3 on the model ladder. Session limit reset here (Drew); effort now xHigh via `/model` (the T3 orchestration level, R27 satisfied). Settings-file JSON defect fixed (a trailing comma).
- 2026-09-05 — **T2b DONE — the parked ledger is EMPTY: all five payloads onboarded byte-identical (MAIN/7 → md_MAIN_007 @0x800CEDF8; MAIN/9 → md_MAIN_009 @0x800CD348; SC03/53, /54 → md_SC03_053/054 @0x801EF468; SC03/56 → md_SC03_056 @0x801CBB50).** Every base came from T2a's static alignment (self-calls / fn-ptr-table entries on the module's own function starts; controls 7/7), NOT from the byte check — two negative controls showed the first build is base-lenient (fine offsets) and only catches gross errors. Two tool refinements en route (combined STRONG rule; outward-explained vote bases). The 100% claim loses its last asterisk once the new stubs are banked or ledgered (T2c/T3).
- 2026-09-05 — **T1b + T1c DONE (R22 213/213 rc 0 for the batch) · T2a DONE.** Both banks were ZERO-token: T1b's body came from `family_remap` of the d=2 twin (+ four TU spellings), T1c's from a stored S72 body the census had mis-keyed (R48) — the journals (R38) named both. Census 21 → **18 stubs** (resident 1 · main 12 · md_MAIN_003 1 · ov_SC03_105 2 · ov_SC06_022 1 · ov_SC07_002 1). T2a's instrument gives every parked payload a bounded probe list; two are STRONG.
- 2026-09-05 — **T1a DONE — `resident:func_800D128C` BANKED (243 ins, byte-identical 8e17e02f, R22 213/213).** The stored S71 closeness-0 draft was byte-correct all along; the whole task was three instrument defects the resident (the fleet's one `common.h`-only, `--pre`-sandwich binary) exposed in overlay-only assumptions: (1) `jr_isolate_all` dropped a file-local typedef whose name engine_types.h also defines (§496 — fixed: provided types derived from the TU's own includes); (2) `jtbl_carve` regenerated `JTBL_INTERLEAVE` without the `--pre hdr.rodata.o` clause → extract refused → the gate linked a stale script and booked the byte-correct draft as DIFF; `harvest_verify` ignored that extract's rc (§498 — both fixed, R49/R61); (3) `interleave_check` read a `--pre` line as n=0 (false DRIFT; fixed). R38 then found two more stored MATCH bodies for T1b/T1c (see their rows). Effort stayed Max.
- 2026-09-05 — **T0 DONE.** Baseline reads all green (`.run/P32/t0_baseline.log`): `verbatim_check --strict` 5 bodies == 5 rows; `exclude_audit --assert-fresh` 8 entries, 8 WALL, 0 stale; `frontier_classify` → 21 rows = the S80 census exactly; `make tools-health` OK (sigs fresh, corpus(+resident), cdecl, audit-binaries 213/213, report lint+dedup, cookbook-index, split_indicator 213 OK); `make check-all` 213 passed / 0 failed, rc 0. Harness task list #1–#11 built (R28). NEXT = T1a.

## 🛑 SESSION CHECKPOINT — T3 MID-WAVE, REFRESHED (2026-09-05 10:01 MDT; written by the successor session e40106e1; SUPERSEDES the 09:30 block)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase29/30/31.md` and this
file, and nothing else (CLAUDE.md protocol, R64 candidate). Replay this block verbatim into your chat, state phase / done /
NEXT / effort, list the rules from the digest, then WAIT for Drew. When he confirms, follow §5 in order. **Effort: xHigh
for T3 and T4** (R27 — Drew sets it; if the status line does not say xHigh, prompt before the first command); **Max only
for T5.** Drafter ladder Haiku ≤50 ins / Sonnet ≤120 / Opus >120; Fable only if an agent names a wall class the codegen
map lacks — STOP and prompt Drew first. No Workflow / Ultracode in T3: one Agent-tool subagent per function.

### 1. Where we are
**Phase 32 — the last 21 + the parked 5 (short, kill-gated).** Gate 1 approved 2026-09-05 (Drew, plan mode, Max,
Fable 5.1); rules R44–R63 ratified then; R64 is a candidate (DIGEST §3). Tasks: **T0 ✓** `commit:3901` · **T1a ✓**
`commit:3902` `commit:3904` · **T1b ✓** `commit:3903` `commit:3906` `commit:3907` · **T1c ✓** `commit:3908` · **T2a ✓** `commit:3909`
· **T2b ✓** `commit:3911` `commit:3912` `commit:3913` `commit:3914` (fleet 213 → 218) · **T2c ✓** `commit:3917` `commit:3918`
`commit:3919` `commit:3920`, close `commit:3921` · **T2d not needed** · **T3 IN PROGRESS** (launch `commit:3922`; banks
`commit:3923` `commit:3924` `commit:3925` `commit:3926` `commit:3927` `commit:3928` `commit:3929` `commit:3930` `commit:3931`; the
successor's checkpoint `commit:3932` + the protocol commit = HEAD) · **T4, T5 pending.** Harness task list #1–#11 exists
(#9 = T3 in_progress). Fleet **218 binaries** (main + resident + 138 `ov_*` + 78 `md_*`). **Last full R22: 218/218 rc 0
at the T2c close** (`.run/P32/t2c/r22.log`); the 10 T3 banks each built byte-identical in their own binary but **no fleet
R22 has run since — §5 step 0 runs one before any new bank.** Non-ghidra tree clean at HEAD; the `ghidra/` churn
(`db.*.gbf`, `~index.*`, `*.prp`) is R23 restart-noise — never stage it. Unpushed commits at this writing: 32
(Drew pushes, R6).

### 2. What happened in the previous session (c6a5fb71, 2026-09-04 22:39 → 2026-09-05 01:07 MDT)
T0–T2c as logged above. T3: census 54 − 7 pinned walls = **47 targets** (`.run/P32/t3/targets.json`); packs built
(`claude_wave_packs`, 47/47 neighbours, 10 journal notes); brief `.run/P32/t3/BRIEF.md`, laws `.run/P32/t3/SYS.md`.
**20 drafters launched 00:53–00:55 MDT** (16 Opus: the 11 old near/far rows + resident `func_800D06E8` + the 4 largest new
bodies; 3 Sonnet; 1 Haiku), **27 Haiku rows queued** behind the harness's 20-concurrent cap; the launch was checkpointed
(`commit:3922`, 00:59). Ten queued rows were launched as slots freed (01:00–01:07). **Ten functions banked in nine commits
01:01–01:07** (list in §4). **At 01:07:15 MDT the coordinator hit "Prompt is too long"** (its context was ~95% full from
the whole day BEFORE the wave); the other **22 completions (01:07–02:04 MDT) arrived as notifications into a dead
session.** At 01:52 MDT one agent (func_800CD674's) tidied the SHARED `.run/P32/t3/opus/` with
`find .run/P32/t3/opus -maxdepth 1 -type f ! -name 'func_800CD674.c' -exec mv {} .run/P32/t3/opus/_scratch/ \;`, moving
**11 sibling deliverables** (the three agents that finished later wrote their finals afterwards and survived). Drew's last
message (09:04): "97% context. checkpoint for fresh session, have next session analyze the completed subagents results".

### 3. What THIS session did (e40106e1, 2026-09-05 09:12 → 10:01 MDT, Max, Fable 5.1)
(a) Dumped the dead session's transcript (`~/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-….jsonl` → condensed text:
assistant text + tool calls + truncated results) and summarised all 31 subagent transcripts. (b) **Rebuilt the verdict
ledger by the recorded route:** `.venv/bin/python tools/agent_verdicts.py /tmp/claude-1000/-home-musashi-bfm-decomp/
7beebba8-05e9-4d18-98ea-ce208f45370f/tasks/a*.output --append .run/P32/t3/verdicts.jsonl` → **31 rows: 20 MATCH / 9 NEAR /
2 FAIL** (pass ONLY `a*.output` — the `b*.output` files there are older sessions' tasks). (c) Found the swept deliverables
in `_scratch/`, moved the 9 missing ones back to `.run/P32/t3/opus/<fn>.c`, and **re-verified EVERY unbanked draft with
`rtu_match` in its real TU — every result equals the agent's verdict** (§4). (d) Wrote `tools/agent_drafts_restore.py`
(transcript replay of Write/Edit/cp/mv/heredoc ops; rebuilt 26/30 exactly — the 4 an agent had edited via shell after its
last Write were stale, so an on-disk copy always wins). (e) **Harvest (R16/R30): cookbook §500** (10 banked closers, 10
MATCH closers, the 9 NEAR classes with their inert-lever lists, two NEW mechanisms — the pinned-base-vs-pseudo-address
alias basin, `#line`-equalised ASM_OPERANDS for cross_jump — and the process defects), `docs/wave-playbook.md` §S80
addendum-2, `docs/accelerators.md` P32 T3, `docs/decision-log.md` P32 S82 (R31), `docs/SETUP.md` tool row (R21),
`docs/cookbook-index.md` regenerated (tools-health's `--check` is green), `.run/P32/t3/BRIEF.md` output contract amended
(final message = the JSON line ONLY; scratch only under `.run/P32/t3/work/<fn>/`; never `find`/`rm`/`mv` in a shared
dir). (f) `.gitignore` allowlist for `.run/P32/**` (drafts, ledger, census jsons, BRIEF/SYS/LAUNCHED/targets/pending/
harvest_notes/PROMPT_TEMPLATE, `restored/sweep_*.py`) → committed **`commit:3932`**. (g) **Drew-directed protocol change:**
`phase-ends/DIGEST.md` created (every phase synopsis, every rule in full, the PROJECT_CONTEXT corrections, the doc map);
CLAUDE.md session-start rewritten (≈100k-token budget: PROJECT_CONTEXT → DIGEST → last 3 PhaseEnds → CURRENT_PHASE; rules in
full from the digest; the 🛑 block replayed VERBATIM); Phase Boundary step 3b (append the phase to the digest, P7);
`phase-ends/README.md`; SETUP §7 pointer; the memories `checkpoint-current-phase-before-pause` and
`session-start-list-rules-in-full` + MEMORY.md; **R64 candidate** — ratify at PhaseEnd_Phase32. (h)
`.run/P32/t3/PROMPT_TEMPLATE.md` — the verbatim agent prompts (Haiku plain / Haiku with a twin hint / the Sonnet
escalation / Opus / Sonnet). (i) Rebuilt the harness task list; wrote this block. **Nothing under `src/` or `config/`
changed this session.**

### 4. Census — 44 stubs / 5,313 ins (`.run/P32/frontier_t3_checkpoint.json`), every row with its state and draft path
| binary | stubs · ins | rows |
|---|---|---|
| main | 9 · 1,643 | **MATCH-unbanked:** func_80015B6C 120 (`.run/P32/t3/opus/func_80015B6C.c`, TU `src/800.c`) · func_8002FDE8 73 (`.run/P32/t3/opus/func_8002FDE8.c`, TU `src/800_b_2.c`) · **NEAR:** func_80039308 518 → 17 (`…/opus/func_80039308.c`, TU `src/800_c.c`) · func_8001BC6C 69 → 6 (`…/opus/func_8001BC6C.c`, TU `src/800.c`) · **WALLS (pinned in `config/wave_exclude.txt`, T4):** func_80011380 192 (boot −O0; `.run/m3/opus/func_80011380.c` 6-off) · func_80032A74 (800_b_2) · func_80020DA4 100 (800; `.run/S79w/sonnet/func_80020DA4.c` 2-off) · func_80039DEC (800_c) · func_800391D4 (800_c) |
| md_MAIN_003 | 1 · 469 | NEAR func_800CF3E8 469 → 27 (`…/opus/func_800CF3E8.c`) |
| md_MAIN_007 | 14 · 701 | **MATCH-unbanked (Haiku, `.run/P32/t3/haiku/<fn>.c`):** func_800CF148 33 · func_800CF2BC 32 · func_800CEEFC 25 · func_800CEF94 25 · func_800CF068 21 · **leaf-exact behind the TU decl:** func_800CF3B0 22 (`src/md_MAIN_007/md_MAIN_007.c:91` = `extern void func_800CF3B0(void *a0, void *a1, void *a2);`, the BANKED `func_800CF390` at `:94` calls it with 3 args; the real signature is `s32 (void)`) · **NEAR:** func_800CF6D0 249 → 137 · func_800CF408 178 → 49 (`…/opus/`) · **QUEUED Haiku:** func_800CF0F4 21 · func_800CF1CC 21 · func_800CF268 21 · func_800CF33C 21 · func_800CF220 19 (twin ov_SC03_001:0x80182860 d=4) · func_800CEFF8 13 (twin ov_SC02_005:0x801865d0 d=3) |
| md_MAIN_009 | 10 · 603 | **NEAR:** func_800CD92C 247 → 15 · func_800CD674 174 → 2 (`…/opus/`) · **QUEUED Haiku:** func_800CD464 25 · func_800CD558 24 · func_800CD408 23 · func_800CD5B8 23 · func_800CD4C8 22 · func_800CD520 22 (twin ov_SC03_011:0x8017dbd8 d=3) · func_800CD614 22 · func_800CD3B8 21 |
| md_SC03_053 | 2 · 116 | **MATCH-unbanked (Sonnet):** func_801EF734 44 (`.run/P32/t3/sonnet/func_801EF734.c`) · func_801EF7E4 72 (`…/sonnet/func_801EF7E4.c`) → the module reaches 100% C |
| md_SC03_054 | 3 · 698 | **MATCH-unbanked:** func_801EF6D8 — targets.json nins 663 = 604 code ins + six jump tables (B-CARVE; `…/opus/func_801EF6D8.c`) · **QUEUED Haiku:** func_801F0048 20 · func_801F00C8 15 (twin md_SC03_053:0x801ef9dc d=5 — `family_remap` refused, reloc-count 1≠2, hand-adapt) |
| md_SC03_056 | 1 · 23 | QUEUED Haiku func_801CBB80 23 (twin ov_SC06_025:0x8017ded8 d=5) |
| ov_SC03_105 | 2 · 595 | NEAR func_80185810 489 → 35 (`…/opus/func_80185810.c`) · WALL (pinned) func_801834A4 106 (`.run/S71_gate14/ov_SC03_105*/func_801834A4.c` 6-off) |
| ov_SC06_022 | 1 · 119 | WALL (pinned) func_8017DF28 119 (`.run/S79w/sonnet/func_8017DF28.c` 2-off) |
| ov_SC07_002 | 1 · 346 | NEAR func_8017DC80 346 → 46 (`…/opus/func_8017DC80.c`) |

**FAIL rows:** haiku func_801EF734 (47 vs 44 — superseded by the Sonnet MATCH); haiku func_800CF3B0 (leaf-exact 22/22; the
TU decl). **The 10 BANKED in T3 so far (1,063 ins):** md_SC03_054 func_801EF558 96 (`commit:3923`, sha `06bd73df…`) ·
md_SC03_053 func_801EF49C 49 (`commit:3924`), func_801EF6B0 33 + func_801EF95C 20 (`commit:3927`), func_801EF624 35
(`commit:3928`) (all `c0848f30…`) · resident func_800D06E8 344 (`commit:3925`, `8e17e02f…` — the resident is 145/145 C; its
`jtbl_80113FA4` carved by `jtbl_carve --func`) · main func_80039B20 79 (`commit:3926`), func_80023BF0 281 (`commit:3930`),
func_80038698 74 (`commit:3931`) (all `143dbb89…` via `gate_main`) · md_MAIN_007 func_800CEE2C 52 (`commit:3929`, `2ff702b6…`).

### 5. NEXT — the T3 resume order (each step's evidence quoted; R42: commit before the next command that can touch src/)
0. **Preflight:** `git status --short | grep -v ghidra/` (empty) · `.venv/bin/python tools/verbatim_check.py --strict` (5 == 5)
   · `make check-all` → **218 passed, 0 failed of 218, exit 0** (R22 baseline before any bank; if any binary is red, fix the
   baseline first — R56) · read cookbook §500-B for each MATCH's plumbing note.
1. **md_SC03_053 ×2 (Sonnet MATCH):** for `func_801EF734` then `func_801EF7E4`: `.venv/bin/python tools/rtu_match.py <fn>
   --split md_SC03_053 --source md_SC03_053 --c .run/P32/t3/sonnet/<fn>.c --asm-subdir asm/md_SC03_053/nonmatchings/md_SC03_053
   --work .run/P32/t3/verify/<fn>` (expect `MATCH (N ins)`) → splice the draft over the one `INCLUDE_ASM("asm/md_SC03_053/
   nonmatchings/md_SC03_053", <fn>);` line (python: assert the line occurs once, replace with the draft text) → `make build
   BINARY=md_SC03_053 -j8` (read `${PIPESTATUS[0]}`, R53) → `sha1sum build/md_SC03_053/md_SC03_053` == `config/check.md_SC03_053.sha`
   (`c0848f30…`) → `git add src/md_SC03_053/md_SC03_053.c` + commit ("T3 (10) …") → **md_SC03_053 is 100% C.**
2. **main ×2 (Opus MATCH):** write `.run/P32/t3/gate/slate_main2.json` = `[{"fn":"func_80015B6C","draft":"/home/musashi/
   bfm-decomp/.run/P32/t3/opus/func_80015B6C.c"},{"fn":"func_8002FDE8","draft":"/home/musashi/bfm-decomp/.run/P32/t3/opus/
   func_8002FDE8.c"}]` (ABSOLUTE paths) → `.venv/bin/python tools/gate_main.py .run/P32/t3/gate/slate_main2.json --apply`
   (a clean main rebuild; read the "slate 2 -> N compatible" and the "BANKED n main functions -- 143dbb89… BYTE-IDENTICAL"
   lines; on a drop, read the BODY/TABLE/PLUMBING/MIXED verdict) → `git add src/800.c src/800_b_2.c` + commit. Keep
   `func_8002FDE8`'s block-scope `extern s16 D_800A46D2;` — the scalar spelling IS the lever (§500-B).
3. **md_SC03_054 `func_801EF6D8` (604 + six jtbls):** `.venv/bin/python tools/jtbl_carve.py md_SC03_054 --func func_801EF6D8`
   (as T3 (3) did for the resident) → `make extract BINARY=md_SC03_054` (EXIT CODE — a failed extract leaves a stale linker
   script, §498) → splice → `make build BINARY=md_SC03_054 -j8` → sha `06bd73df…` → `.venv/bin/python tools/pads_audit.py
   md_SC03_054` + `tools/interleave_check.py md_SC03_054` (R60) → commit the carve state (ONLY this binary's `config/overlays.mk`
   lines + `config/splat.md_SC03_054.yaml`) + the bank. Alternative: `tools/parallel_gate.py … --r22` (it carves). The draft's
   rtu_match MATCH was re-confirmed against the CURRENT TU after `func_801EF558` landed.
4. **md_MAIN_007 (six):** FIRST the byte-neutral plumbing commit (the S77 law): `src/md_MAIN_007/md_MAIN_007.c:91`
   `extern void func_800CF3B0(void *a0, void *a1, void *a2);` → `extern s32 func_800CF3B0();` (no-proto, the §376
   `fix_arity_callers` class — keeps `func_800CF390`'s 3-arg call legal and admits the `s32 (void)` definition) → `make build
   BINARY=md_MAIN_007 -j8` → sha `2ff702b6…` UNCHANGED → commit. (If the sha moves, keep the 3-param decl with `s32` return
   and define `func_800CF3B0` with three unused pointer params instead — the gate decides.) Then `rtu_match` each of
   func_800CEEFC, func_800CEF94, func_800CF068, func_800CF148 (drop its block-scope `s32 func_800CF3B0(void)` redeclaration
   only if cc1 objects), func_800CF2BC, func_800CF3B0 → splice → one build → sha → commit (per bank, or per verified same-TU
   batch).
5. **After 1–4:** `.venv/bin/python tools/twin_rescan.py` (a bank changes the twin graph — the queued md_MAIN_009 rows may
   gain twins; it prints ready `family_remap` command lines) · `verbatim_check --strict` · R22 `make clean && make
   extract-all && make check-all` → quote **218 passed / 0 failed, exit 0** (R58) · `make tools-health` → OK · refresh this
   block + commit. Expected census after 1–4: **33 stubs / ~4,250 ins.**
6. **Ledger the 9 NEAR** in the backlog (`grep -n add_argument tools/backlog.py` first — the dead session's query on keys
   `addr`/`fn` returned nothing for the wall rows, so confirm the row schema; then `tools/backlog.py log …` per row with
   closeness · class · best draft · cost "1 Opus agent, 30–70 min" (R41) · `tools/backlog.py render`): func_800CD674 2
   REGALLOC-PERM `$a3↔$t1` · func_8001BC6C 6 REGALLOC-PERM `$v0↔$v1` (qty_compare one span unit; pinned seed → §494
   `permuter_ils … --cycles 8 --secs 150 --j 3`) · func_800CD92C 15 §S7 prologue weave · func_80039308 17 sched2 +
   cross-block regalloc · func_800CF3E8 27 pinned-base alias basin (§500-D1) · func_80185810 35 [permuter] 4 emission
   windows · func_8017DC80 46 reload-slot frame + `la $a0` slot · func_800CF408 49 [permuter] 3 hunks · func_800CF6D0 137
   sched1 rank_for_schedule class tie.
7. **Launch the 17 queued Haiku rows** from `.run/P32/t3/pending_launch.txt` with the prompts in
   `.run/P32/t3/PROMPT_TEMPLATE.md` (substitute fn / binary / nins / sub / asm / tu / twin; keep the arm; the packs are at
   `.run/P32/t3/packs/<fn>.md` — regenerate with `claude_wave_packs` if missing): **dequeue the row (`sed -i '/^<binary>
   <fn> /d' pending_launch.txt`) BEFORE launching; ≤20 concurrent** ("Concurrent subagent limit reached. … Do not retry" =
   wait for a completion); each agent's final message is now the JSON line only (BRIEF amended). Per result, never in bulk:
   `grep -c '\.ent\|\.word' <draft>` (0) → your OWN `rtu_match` → splice/build/sha → commit → `twin_rescan`. A Haiku FAIL
   whose note names a C-structure residual at near-exact length → escalate to Sonnet with the shape hint (the
   PROMPT_TEMPLATE has the escalation prompt); a TU `conflicting types` → the §376 plumbing commit first.
8. **The NEAR tail (bounded):** permuter on the two REGALLOC-PERM seeds (func_800CD674, func_8001BC6C) via the repaired
   `permuter_ils`; ONE Opus second look only where §500 names an untested lever (func_800CF3E8: an unpinned alias of `p6`
   for the tag load alone). Plateaus stay in the backlog. **Kill gate stands:** a session with no bank and no new verdict
   ends T3.
9. **T3 close:** any new idiom from steps 7–8 → cookbook §500 addendum (R16/R30) + `harvest_notes.md`; regenerate
   `docs/progress.fleet.md` (`make report`); then **T4**.

### 6. Files, tools, exact invocations, gotchas
- **`.run/P32/t3/` (git-tracked unless noted):** `BRIEF.md` (agent brief, amended) · `SYS.md` (the laws) · `targets.json`
  (47 rows: name, binary, nins, sub, asm, tu, klass, closeness, model, twin, twin_d) · `pending_launch.txt` (17 rows
  `binary fn nins [twin=…]`) · `verdicts.jsonl` (31) · `LAUNCHED.md` (recovery route + status) · `harvest_notes.md` ·
  `PROMPT_TEMPLATE.md` · `{opus,sonnet,haiku}/func_*.c` (the deliverables: 12 + 4 + 11) · `restored/sweep_func_80039308.py`
  (the dead-local sweeper an agent wrote — a tool candidate) · untracked: `packs/<fn>.md` (47; regenerable), `verify/` +
  `verify_*.txt` + `gate/slate_*.json` (the coordinator's own checks), `work/` `rtu/` (agent scratch), `opus/_scratch/`
  `opus/x/` `opus/var/` `opus/_h/` `opus/_wk_8017DC80/` `opus/sweep/` (agent leftovers — ignorable), `restored/*.c`
  (transcript replays — inferior to the on-disk finals). Census jsons: `.run/P32/frontier_*.json` (tracked).
- **Transcripts:** `~/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-<id>.jsonl`
  (31; `/tmp/claude-1000/-home-musashi-bfm-decomp/7beebba8-05e9-4d18-98ea-ce208f45370f/tasks/<id>.output` are symlinks to
  them; the id→function map is the `file` field of each `verdicts.jsonl` row). Never cat one; use `agent_verdicts.py` /
  `agent_drafts_restore.py`.
- **`rtu_match`:** `--split <sub> --source <binary> --c <draft> --asm-subdir <asmdir> --work <dir>`; **main adds `--tu
  src/<sub>.c`**; `<sub>`/`<asmdir>`/`<tu>` come from `targets.json` or `corpus.stubs(<binary>)` (`asm_path`, `path`). The
  verdict line starts `MATCH`/`DIFF`/`CC1`. It compiles the WHOLE TU with the draft spliced — the gate predictor.
- **Build check:** `make build BINARY=<b> -j8 2>&1 | grep -v "warning\|In function" | tail -2; rc=${PIPESTATUS[0]}` then
  `sha1sum build/<b>/<b>` vs `config/check.<b>.sha`. R53: exit code, never the file (a failed build leaves the old binary).
- **`gate_main`:** the ONLY way to gate main (incremental builds false-pass/false-diff on main, R43/§S52); slate = JSON list
  of `{fn, draft(ABSOLUTE)}`; `--apply` keeps the splice on success; then `git add` the TU + commit.
- **Carves:** `jtbl_carve.py <b> --func <fn>` → extract (rc) → build; `pads_audit.py <b>`, `interleave_check.py <b>`; a
  DIFF that starts at the first code byte is a stale linker script, never the draft (§498).
- **Gotchas that bit this week:** `set -o pipefail` + `grep -c` exits 1 on zero matches (a "no ghidra staged" guard
  aborted a good commit) · never `cd` inside a compound command (the cwd persists into later calls) · `masked_diff.py`
  leaves `src/.masked_diff_probe.<pid>.c` while running — they are other agents' live probes, never delete them · the
  `.run/P32/t3/<arm>/` dirs are SHARED (agents are now told not to touch siblings) · the SessionStart hook launches a
  headless Ghidra MCP server (`.run/ghidra-mcp.log`) — T3/T4 never use it · `agent_verdicts.py` over a whole `tasks/` dir
  picks up older sessions' outputs — pass `a*.output`.

### 7. Carried context for T4 and T5
**T4 (xHigh, no drafting) — the dead session's read-only pre-check (07:00Z):** `exclude_audit --assert-fresh`: 7 entries,
7 WALL, 0 stale. Best drafts re-run in their REAL TU: `main:func_80011380` `.run/m3/opus/func_80011380.c` DIFF 6 (the
ledger's `.run/backlog_drafts/func_80011380.c` is MISSING — R62 path fix) · `main:func_80032A74` `.run/S79w/opus/
func_80032A74.c` **CC1 FAIL** (`redefinition of struct Slot`/`Slot`, `conflicting types for A12`/`B12` vs
`src/800_shared.h:68/95` — §376 plumbing, re-probe before a final verdict, R40) · `main:func_80020DA4` `.run/S79w/sonnet/
func_80020DA4.c` DIFF 2 · `main:func_80039DEC` both `.run/S79w/{permuter,sonnet}/func_80039DEC.c` **CC1 FAIL**
(`conflicting types for func_80039DEC` — a def-side declaration wall, §495: fix the TU's own decl first) ·
`main:func_800391D4` `.run/S79w/sonnet/func_800391D4.c` **CC1 FAIL** (`conflicting types for D_80073140` at t.c:3310 vs
:2622) · `ov_SC06_022:func_8017DF28` DIFF 2 · `ov_SC03_105:func_801834A4` S71_gate14 variants DIFF 6 (the ledger's
`.run/backlog_drafts/func_801834A4.c` is MISSING). Deliverables: each of the 7 rows PROVED vs CANDIDATE with a current
citation + an instrument-exonerated bounded attempt (R40), `exclude_audit --write`, `backlog.py render`, the wall table
into this file, cookbook §501 if a verdict changes, decision-log, accelerators. A T3 idiom naming a wall's mechanism
re-opens that row (one bounded attempt, permuter first).
**T5 (Max, Tier 1 — prompt R27; WAIT for gate 2):** P7 checkbox walk over every task above; milestone demo = R22 fleet
218/218 · `make tools-health` OK · `verbatim_check --strict` 5==5 · the final census (`tools/frontier_classify.py --json`)
· the wall ledger · parked-5 dispositions via `make audit-disc` (UNCLAIMED 0 of 220 at T2c) · `make report` all three
metrics + main `143dbb89…` WITH and WITHOUT the SDK object dirs (`.run/obj40`, `.run/obj42`; fresh-extract fallback) ·
corrected denominators (main game-code 41,556 — the 22-ins Ghidra-boundary gap; the fleet denominator grew by the five
modules' ~2,600 ins at T2b). Then `PhaseEnd_Phase32.md` (+ Roadmap delta: P33 = verify + flip; + Plain-English Recap; +
the rules table incl. R64) → **append the P32 synopsis + rules to `phase-ends/DIGEST.md` (step 3b)** → `git mv
CURRENT_PHASE.md phase-ends/logs/Phase32.md` (R19) → R23 MCP stop if it ran → leave both uncommitted for Drew (R6) → 🛑.

### 8. Environment
Fleet 218; shas of the binaries T3 touches: main `143dbb89f34491258bbc27810d0a12ec8b43a8dd` · resident
`8e17e02ff8954d07c979449198f7e1645046b353` · md_SC03_053 `c0848f308342e499e2bd8c2db86f6225a29e1592` · md_SC03_054
`06bd73dfbdb10748adcbac7093ead5d76131206a` · md_MAIN_007 `2ff702b605ab5cfc18474c464c4c07e5f8ffd48c` · md_MAIN_009
`d270f695…` · md_SC03_056 `bc768a6b…` (`config/check.<b>.sha` is authoritative). Toolchain unchanged (SETUP §5.4). Harness:
20 concurrent Agent-tool subagents max; an Agent call beyond that returns "Concurrent subagent limit reached" (do not
retry — wait). Claude commits, Drew pushes. Last published metrics (P31 close, 213 binaries): instr 100.0% · distinct
99.9% · fn 99.99% — regenerate with `make report` at the T3 close (218 binaries).

### 9. Standing reminders (the rules that bite in T3)
Every bank commits before the next command that can touch `src/` (R42) · count banks from the SOURCE and quote the
fleet's green count at every close (R58) · verify a build from its exit code (R53) · a masked score is not a closeness
until its diff is read (R63) · an `__asm__` body is a verbatim, not a bank (R62) · fix the TU by a byte-neutral plumbing
commit BEFORE any gate (S77 law) · after a carve/merge touching a yaml/`.mk`: `make extract` before building, then
`pads_audit`/`interleave_check` (R60) · rules check every 4 tasks (P6) · harvest idioms into the cookbook before the next
drafting step (R16/R30) · no `Co-Authored-By` (R5) · never stage `ghidra/` (R23).

**Plain-English recap (R18).** Last night thirty-one AI agents were set on the leftover functions; twenty produced exact
matches, but the coordinator ran out of memory after banking the first ten and one agent accidentally swept the others'
finished files into a side folder. This session read the whole record, pulled every result back out, confirmed each one
byte-for-byte, put the swept files back, wrote the lessons into the cookbook and the playbook, and — at Drew's direction —
made session start cheaper (a one-page digest of all 32 phases instead of reading them all) and made this checkpoint the
complete hand-off the next session replays verbatim. The next session's first jobs: re-verify the fleet, bank the ten
ready matches, then launch the seventeen queued small functions.
