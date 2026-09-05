# The Phase-32 frontier — the last 21 functions, the parked 5 payloads, and the routes (S80 close, 2026-09-05)

> **Purpose.** The jumping-off document for the Phase-32 plan (plan mode reads this FIRST, then
> `docs/roadmap-to-100.md` v2 §3 and `PhaseEnd_Phase31.md`). Every number here comes from an instrument run at
> the S80 close (R14/R41): `tools/frontier_classify.py --json .run/frontier_s80.json`, `.run/backlog.jsonl` /
> `docs/backlog.md`, `.run/S79w/verdicts/verdicts.jsonl`, `config/wave_exclude.txt`, `tools/jtbl_carve.py --probe`,
> `tools/jr_isolate_all.py --dry-run`, `tools/twin_rescan.py`. **Regenerate before planning** — a bank between now
> and then invalidates a row: `make tools-health && python3 tools/frontier_classify.py --json .run/frontier_p32.json`.
>
> **State at the close:** 213 binaries byte-identical (R22 213/213), fleet instr-weighted 100.0% (13,481,386 /
> 13,485,889), distinct-code 99.9%, **21 INCLUDE_ASM stubs = 4,554 instructions**; main REAL 777 · LINKED 1,256 ·
> VERBATIM 3 · stubs 12 · byte-identical 2,079/2,091 = 99.43%; main game-code 39,479 / 41,556 = 95.0% (the published
> 41,534 denominator is 22 short: Ghidra's flow-derived body for `FUN_80023bf0` omits its last 22 instructions —
> use splat's 281, the S79 draft is 281/281). Five PERMANENT verbatim bodies, ratified. Five disc payloads parked.

---

## 1. The 21, by what actually blocks each one

Closeness = masked instruction mismatches of the best draft against the target (0 = match). "Attempts" counts
distinct sessions/agents that left a recorded verdict. Draft paths are the best-known bodies; `.run/S79w/<arm>/`
are the S79 one-agent-per-function drafts, `.run/S79w/permuter/` the S80 permuter waypoints.

### 1a. B-CARVE — a jump-table carve the tooling refuses (3) + one carve-fine F-FAR (1)

| binary:fn | nins | blocker (the tool's own words) | what unblocks it | expected cost |
|---|---|---|---|---|
| `resident:func_800D128C` | 243 | `jtbl_carve --probe`: *subseg 'resident' would host NON-CONTIGUOUS .rodata carves (0x450e0 and 0x451c0) — a single object can't leave a gap for the unmatched jtbl between* | `tools/jr_isolate_all.py resident --only func_800D128C` — the dry run is CLEAN: 3 region `.c` files, carve repointed `resident → resident_jr_800D00E4`, `overlays.mk --order` + `JTBL_PADS` updated. Then gate the **closeness-0 draft** `.run/S71_gate14/resident/func_800D128C.c` (95 drafts exist; `attempts=0` — it was never gated because the carve refused). | tooling ~1 session-hour, then likely a free bank |
| `ov_SC02_017:func_80186C64` | 209 | same refusal in `ov_SC02_017_jr_8017DF34` (carves at 0xc6274 and 0xc62a4); `jtbl_carve` also clamps its table to the 6 entries its `sltiu 6` names | `jr_isolate_all ov_SC02_017 --only func_80186C64` REFUSES today (R43): a carried type name `Rec801806C8_s` has CONFLICTING bodies in the TU (a packed struct definition vs a `typedef struct Rec801806C8_s Rec801806C8;`) — rename one, re-run. **Then it is a REMAP, not a draft:** `twin_rescan` — `ov_SC02_016:0x801810c8` (209 ins) is a d=2 RELOC-ONLY twin (diffs at reloc@12, reloc@144) → `family_remap` + the §378 chain. 105 stored drafts, never gated. | tooling ~1 session-hour, then free |
| `md_MAIN_034:func_800CB00C` | 152 (code 123 + a 29-word table) | `jtbl_carve --probe`: *jtbl_800CAE0C at file 0x4 is BELOW the data region (0x1be0) — it lives in the §154-A leading .rodata island* | The §154-A leading-island prep at gate time (see cookbook §154-A, §491) AND a correct body: the only draft (`.run/wave_g0c/shard30/func_800CB00C.c`, S68) is **wrong-sized — 174 ins vs the 123-ins target** (`rtu_match` DIFF); its S68 "compiler wall" pin in `config/wave_exclude.txt` labels a wrong draft, not a wall (re-probed S79 #6). Redraft from the `.s` (Sonnet-tier, 123 ins, 7 calls, one 29-entry switch). | one agent + the island prep |
| `resident:func_800D06E8` | 344 | carve is fine (*tail — standard §8a carve at gate time*) | The BODY: closeness 292 (`.run/wave_ch/shard62/func_800D06E8.c`, 217 drafts); the last real-TU verdict was `conflicting types for Struct80078E78` (a TU typedef clash, not codegen). A jump-table dispatcher with 11 calls; `docs/resident-dossier.md` §4 names it. Treat as F-FAR: one Opus attempt seeded with the resident's matched dispatcher siblings. | one Opus attempt |

### 1b. D-NEAR, pinned as WALLS (8) — no drafting effort in P32 unless a NEW idiom appears

All in `config/wave_exclude.txt` (8 entries; `tools/exclude_audit.py --assert-fresh` refuses a stale list). One is
PROVED, seven are candidates with a gcc-mechanism citation + a permuter null. The G4 end-state for these is
`INCLUDE_ASM` with the proof in the PhaseEnd ledger.

| binary:fn | nins | close | mechanism (cited) | attempts | best draft |
|---|---|---|---|---|---|
| `main:func_80011380` | 192 | 6 | **PROVED** §474: `fold-const.c:882 split_tree` merges MULT(MULT(i,2),2); the two escapes each cost one instruction (`stupid.c:497` adjacency / `expand_decl` use-brackets); -O0 boot TU (§388 colouring oracle) | S76 proof | `.run/backlog_drafts/func_80011380.c` |
| `main:func_80032A74` | 422 | 1 | idx 244 `lh` vs `lhu`: `extendhisi2` is a force_not_mem EXPAND (an orphan frame slot is minted only at an `lh`); the target's extra 8 frame bytes = §172 producer 3, a caller-save area at `reload1.c:1445`; ~200 probes incl. a 100-variant retyping sweep | S7x + S79 Opus + S80 ILS null | `.run/S79w/opus/func_80032A74.c` (frame 0x78, 27 symbols, every offset exact) |
| `main:func_80020DA4` | 100 | 2 | mflo destination `$t0` vs `$a2` (REGALLOC-PERM); pinning regresses to 79; the phantom 16-byte frame is reproduced by an address-taken `s32 frame_pad[3]` | 51→20→14→8→2 (S7x/S79) + S80 ILS null | `.run/S79w/sonnet/func_80020DA4.c` |
| `main:func_80039DEC` | 74 | 2 | the K&R raw-preserve copy of parameter 2 lands in `$t1`/`$a3` by ARGUMENT POSITION in gcc-2.7.2's narrow-parameter promotion (2nd → `$a3`, 3rd → `$t0`) before the global allocator; every pin on it regresses to 60–75 | 3 corroborating + S80 ILS 9→2 | `.run/S79w/permuter/func_80039DEC.c` (2), `.run/S79w/sonnet/func_80039DEC.c` (9, the K&R-def seed) |
| `main:func_800391D4` | 75 | 3 | a 3-insn SCHEDULE-REORDER: `move_movables` splices hoisted invariants after any pre-existing preheader flow, so `off`'s init cannot follow `arg1`'s hoisted sign-extend from C | 4 prior + S79 (64→3) + S80 ILS null | `.run/S79w/sonnet/func_800391D4.c` — NOTE its `extern s32 D_80073140[][1]` conflicts with the TU's `extern s32 D_80073140[]`: a §200 `__asm__("D_80073140")` alias is needed before any real-TU gate |
| `ov_SC06_022:func_8017DF28` | 119 | 2 | delay-slot fill: `addiu $s2,$sp,0x10` sits in the `jal`'s slot vs the target's `bnez` slot — `expand_block_move`'s `copy_addr_to_reg` pseudo is cse-reused for both later `&mtx` args (`gcc-2.7.2-map/cse_expr.md` [A23-2]/§H); field-wise copy regresses to 117; the §H diamond cse-reset is a no-op here | 5 RTL-verified (S71/S79) + S80 ILS (its "1" was a divergent store rewrite, R14) | `.run/S79w/sonnet/func_8017DF28.c` |
| `ov_SC03_105:func_801834A4` | 106 | 9 | loop.c movable ordering (§148-A/§193-F), closeness 6–9 on four attempts | 4 (S71) | `.run/backlog_drafts/func_801834A4.c` |
| `md_MAIN_034:func_800CB00C` | — | — | **NOT a wall** — see 1a (wrong-sized draft under the S68 pin); drop the pin when the redraft lands | — | — |

### 1c. D-NEAR, not pinned (3) — agent-sized residuals, permuter-confirmed plateaus

| binary:fn | nins | close | residual (from the S79 verdict + the S80 permuter) | best draft |
|---|---|---|---|---|
| `main:func_80023BF0` | 281 | 11 | S79 Opus 90→18 by gdb-on-cc1 allocno arithmetic (every step a computation on `global.c:594`; the levers are in the draft header); the 18 were pure sched2 ORDER provably exclusive with the required pin; the S80 permuter took it to 11 (ADDRESSING: the 0xFFFFFF/0xFF000000 `lui/ori` moved across the `sll`/`bne` — **verify semantics before seeding from it**) | `.run/S79w/permuter/func_80023BF0.c` (11), `.run/S79w/opus/func_80023BF0.c` (18) |
| `main:func_80038698` | 74 | 11 | sched1 DAG priority + local-alloc self-coalesce at three byte-pair sites; §197-C split reproduces 11 (LO-first) or 17; a zero-byte re-tie fixes the load order but costs an `andi` (33–39); the permuter (now able to read its `asm("$7")` pins) confirms 11 | `.run/S79w/sonnet/func_80038698.c` |
| `main:func_80039B20` | 79 | 7 | §461 list-scheduler tie-break: the 7-entry rotation around a redundant `D_80073140[i]` re-read (target schedules it right after the `D_800C7D20` load); four restructurings inert or worse; 17 + 8 + 8 ILS cycles | `.run/S79w/sonnet/func_80039B20.c` |

### 1d. F-FAR (7) — exact-length drafts with a named residual; genuine per-function cracking

| binary:fn | nins | close | where it is stuck (S79 verdict) | best draft / attempts |
|---|---|---|---|---|
| `main:func_80039308` | 518 | 34 | 115→34 by splitting one local shared across both arms of `if (b3)` (−40) + four byte-witnessed spelling laws (§494); residual = 18 register renames + 15 sched-order + 1 imm, no structural difference; the 20-instruction else-mask block resisted 15 spellings | `.run/S79w/opus/func_80039308.c`; 8 drafts, journal 402→34 |
| `ov_SC03_105:func_80185810` | 489 | 37 | compiler C (splat's "Handwritten" banner = cop2 opcodes); identical instruction MULTISET, residual = sched1 ordering in three windows (tpage RMW 363–374, a vertex load-delay slot 421–438, cross-jumped clut branch polarity 443–451); three §194-A fences 80→37; a ~3,600-compile brute force found 37 the floor | `.run/S79w/opus/func_80185810.c`; 6 drafts |
| `md_MAIN_003:func_800CF3E8` | 469 | 54 | all four block sizes exact; fences at prim FIELD boundaries beat pins (262→186→54); residual = p4's `la/addu` chain 5 late (10 rows) + `0xFFFFFF` in `$t2` vs `$a2` (13) + blk1's tag-8C `lui` early (9) + blk2's `lui 0xE100` no longer shared out of the entry delay slot (5) — a local-alloc birth-order tie | `.run/S79w/opus/func_800CF3E8.c`; 135 drafts, journal 377→54 |
| `ov_SC07_002:func_8017DC80` | 346 | 84 | compiler C; the TU's "−33 wall" was the GTE macros UNDEFINED (implicit `jal`s); `true_dependence` struct-vs-scalar interleave 255→109; residual = cse unifying `otz<<2` across a call into pinned `$s1` (~45) + a clamp delay-slot (8) + a late `lui/addiu` pair (~14) | `.run/S79w/opus/func_8017DC80.c`; 40 drafts |
| `main:func_80015B6C` | 120 | 44 (40 last) | two documented walls: a 6-ins `$v0/$v1` swap in the `D_800B9A02*20` index calc (pinning inert) + sched1 hoisting the `xa=x` corner copy one slot across the block1/block2 boundary; per-block pins + opaque-copy barriers 88→44 | `.run/S79w/sonnet/func_80015B6C.c`; 82 drafts, 6 prior attempts |
| `main:func_8002FDE8` | 73 | 35 | OPCODE-MIXED only: gcc caches `&D_800A46D2` in a callee-saved reg across the `func_800419B0` call where the target rematerialises `lui/lo` at both sites (local-alloc priority/rematerialisation, §153); falsified: un-chaining, volatile, a ref-boost asm | `.run/S79w/sonnet/func_8002FDE8.c`; 30 drafts |
| `main:func_8001BC6C` | 69 | 28 | head: sched1 birthing-boost hoists the `a1<<16|0x64000000` colour partial ahead of four `lhu`s regardless of statement order (two mutually exclusive schedules in prior RTL dumps); tail: a val-load/tbl-read/store swap + the `FF000000` mask in `$v1` vs a reused `$a1`; pinning the mask → 60 | `.run/S79w/sonnet/func_8001BC6C.c`; 41 drafts, 3 attempts |

**Per-binary totals:** main 12 (2,077 ins) · resident 2 (587) · md_MAIN_003 1 (469) · md_MAIN_034 1 (152) ·
ov_SC02_017 1 (209) · ov_SC03_105 2 (595) · ov_SC06_022 1 (119) · ov_SC07_002 1 (346).

---

## 2. The parked 5 disc payloads (the 100% claim's explicit exclusion)

`MAIN/7` (a raw file, `FILE_007`, not PAC-wrapped), `MAIN/9`, `SC03/53` (6,616 B), `SC03/54` (8,220 B), `SC03/56`
(3,680 B) — of 220 code-bearing payloads. Evidence so far (`docs/disc-completeness.md` §S45; `docs/memory-map.md`
§S45 part 3): never present in RAM across the L3 debug-menu tour (boot/title/attract/menus/load/opening/endings/
game-over/~15 scene loads); their loaders are individual and condition-gated; jal-vote bases are low-confidence, so
onboarding on a guess is P9 theater. Status: **static-RE targets** — decode each payload's loader path in the EXE /
resident to get its load address, or prove it dead. If any is a live code payload, it is the ONLY place new decomp
work can still appear (its size is bounded: ~19 KB across the three SC03 rows; MAIN/7 and MAIN/9 sizes in
`docs/disc-ledger.md`). If all five are dead or data, the completion claim loses its last asterisk. `make audit-disc`
asserts the residue-0 partition (UNCLAIMED = 5).

---

## 3. Routes and instruments (what a fresh session must know before touching any of the above)

* **Real-TU check before any gate:** `tools/rtu_match.py <fn> --split <TU basename> --source <bin> --c <draft>
  --asm-subdir asm/<bin>/nonmatchings/<subseg>` (main: add `--tu src/<TU>.c`; `--split` still required). A
  standalone `match_one` MATCH is a claim about the body only (§376). Three refusals the S79/S80 banks hit: a
  duplicate typedef already in the TU (strip it); `memcpy(…,12)` → `jal` under the TU's `extern memcpy` (struct-assign
  through an align-1 typedef); the TU's own `extern` for the function being wrong (a def-side declaration wall — §495:
  `extern void f(void)` for a pointer-only callee; a block-scope `struct S *` parameter declaring a block-local tag).
  **Fix the TU by a byte-neutral plumbing commit BEFORE the gate (S77 law).**
* **Gates:** overlays/modules → `tools/parallel_gate.py --plan <plan.json> --workers N` (a FILE, not inline JSON;
  worktrees; then `make extract BINARY=<bin>` if a yaml/`.mk` changed, in-tree `make build BINARY=<bin> -j8` read
  from its EXIT CODE (R53), `pads_audit.py` after a carve). S80 added: a banked-but-not-merged binary prints
  `!! BANKED-BUT-NOT-MERGED` and the run exits 2 — recovery is `rtu_match` MATCH → in-tree splice → build → commit.
  main → `tools/gate_main.py <slate.json> --apply` (clean rebuild; main TUs must be clean; its pre-check names
  decl clashes → `sync_tu_decls` / `cast_self_callers --sync-decls`, committed byte-neutral first). **Commit every
  bank immediately (R42)**, then `tools/twin_rescan.py`.
* **The permuter is now honest on pinned and K&R seeds** (§493 S80 correction, `commit:3890`): `tools/permuter_ils.py
  <fn> --draft <seed> --asm-subdir <dir> --klass REGALLOC|SCHEDULE --cycles 8 --secs 150 --j 3`; it re-hides pins on
  every warm restart, aborts exit-2 on a refusal, and flushes its log. **Read a waypoint's diff (`match_one`) before
  recording its score** — one S80 "1" was a divergent store rewrite. Winners → `tools/p16_permute.winner_to_draft`
  (strip the typedef preamble) → the §493 plumbing route.
* **Verbatim bodies are never banks:** `tools/verbatim_check.py --strict` (in tools-health) diffs the tree against
  `config/verbatim_manifest.json` (5 PERMANENT rows). A ledger `best_draft` that is an `__asm__` body is the S79 #7
  trap (§495). `tools/verbatim_to_stub.py <…> --asm-subdir asm/<bin>/nonmatchings/<subseg> --apply --gate` reverts one.
* **Carves:** `tools/jtbl_carve.py <bin> --func <fn> --probe` (the verdicts above), `tools/jr_isolate_all.py <bin>
  --only <fn> [--dry-run]` (the code-subseg split for NON-CONTIGUOUS carves; works on `resident` — its yaml follows
  the `splat.<bin>.yaml` form), `tools/jtbl_pads_fix.py`, `tools/pads_audit.py`, `tools/interleave_check.py`;
  `config/overlays.mk` + the splat yamls are CARVE STATE (R59/R60: never blanket-add or blanket-restore).
* **Drafting fuel:** `tools/claude_wave_packs.py` packs carry the journal notes (`tools/journal_notes.py`) and a
  matched neighbour; the S79 packs are in `.run/S79w/packs/` with the briefs' laws in `.run/S79w/SYS.md`. Model
  ladder: Haiku ≤50 ins → Sonnet ≤120 → Opus above → Fable only for a NEW wall class (`Agent(model: fable)`).
  Agent-tool drafters outlive a session; harvest their verdicts with `tools/agent_verdicts.py` (never cat a
  transcript).
* **Census / ledgers:** `tools/frontier_classify.py --json <out>` (21 rows), `tools/backlog.py render`
  (`docs/backlog.md`, 18 open near-misses with drafts), `config/wave_exclude.txt` + `tools/exclude_audit.py --write`,
  `.run/S79w/verdicts/verdicts.jsonl` (the full S79 agent notes — the mechanism text per function).
* **Verification:** every banked batch → `make clean && make extract-all && make check-all` (213/213, exit codes) +
  `make tools-health`; count banks from the SOURCE, not a tool's report.

---

## 4. The proposed Phase-32 shape (Drew's steer at S80 close: "a plan to 100%" — the two-gate model supplies the
## stopping rule this tail needs)

**Milestone (proposed):** every one of the 21 is either BANKED or carries a FINAL verdict (PROVED wall / candidate
wall with citation + a bounded-attempt record / deferred-cost with the cost stated), the five parked payloads each
have a load-address answer or a dead-code proof, and the fleet stays 213/213 throughout. Kill gate: a session that
banks nothing and produces no new verdict ends the crack work.

1. **Tooling first, zero drafting tokens (1 session):** the `jr_isolate_all` split for `resident:func_800D128C`
   (dry-run clean) and, after the `Rec801806C8_s` rename, for `ov_SC02_017:func_80186C64`; gate the existing
   closeness-0 draft and the RELOC-ONLY twin remap. Then the §154-A leading-island prep + a Sonnet redraft of
   `md_MAIN_034:func_800CB00C` (123 ins). Expected: 2–3 banks. Drop the S68 pin.
2. **One bounded crack pass on the 10 near/far bodies + `resident:func_800D06E8` (1–2 sessions):** one Opus agent
   each, seeded with its exact-length best draft, its S79 verdict (the INERT list is the most valuable part), the
   §494/§495 idioms and the fixed permuter; Fable only if an agent names a wall class the map lacks. Bank what
   falls; every plateau gets its ledger row updated with the attempt and cost (R41). Candidates for a cheap
   second look first: `func_80023BF0` (11, a permuter-shaped ADDRESSING residual) and `func_80039B20` (7).
3. **The 8 walls get no drafting** — they receive their final verdict (PROVED vs candidate) in the ledger and stay
   `INCLUDE_ASM` under G4, unless step 2 surfaces a new idiom that names one of their mechanisms.
4. **The parked 5 (1 session, static RE — needs the Ghidra MCP, R29):** decode each loader path (memory-map §S45
   part 3 has the decoded leads); onboard any live payload with `tools/new_overlay.sh`, or record the dead-code
   proof in `docs/disc-completeness.md`.
5. **Close with the final ledger** (the PhaseEnd's wall table with proofs) and the corrected denominators (main's
   41,556). Phase 33 = verify + flip (roadmap v2 P33).

**Effort/model:** planning at Max (Tier 1); step 1 xHigh; step 2 xHigh orchestration with Opus agents (no wave —
11 targets, one agent each, `agent_verdicts.py` aggregation); step 4 xHigh + MCP; the PhaseEnd Max.

**What NOT to re-derive:** the walls' mechanisms (above, with citations); the fact that `main()` is C; that the
md_MAIN_003 -O0 cluster is finished; that every S79 "MATCH" that was not one was a verbatim, a TU spelling, or a
gate ladder mutation (§494); that the 1,256 LINKED main functions are Sony's objects, byte-identical by link.
