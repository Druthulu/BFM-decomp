# phase-ends/DIGEST.md — the session-start digest (every PhaseEnd in one page + every rule in full)

> **Purpose (R64 candidate, Drew 2026-09-05).** The Session Start Protocol used to read all 32 PhaseEnd files (~510 KB,
> ~150k tokens) before any work. This digest replaces that read: it carries **every rule's full text** (the rules
> acknowledgment is transcribed from here) and a **synopsis of every phase**, so a session reads `PROJECT_CONTEXT.md`
> → this file → the **three most recent** `PhaseEnd_*.md` in full → `CURRENT_PHASE.md` (and replays its 🛑 block
> verbatim into the chat). Budget: the whole protocol ≈ 100k tokens + the verbatim checkpoint. The PhaseEnd files are
> still the durable record (never deleted, R19) — read an older one on demand when a synopsis is not enough.
> **Maintenance:** at every PhaseEnd, append that phase's synopsis and its ratified rules here (a P7 checkbox).
> This file is DERIVED from the PhaseEnds and may be corrected; PROJECT_CONTEXT.md is never edited (P1).

## 0. Where the project stands (at the latest PhaseEnd — the live state is in CURRENT_PHASE.md)
Brave Fencer Musashi (SLUS-00726) matching decomp. **Phase 33 closed 2026-09-07 (v1.32.0) on a RE-CHARTERED milestone: everything
before the public flip is done.** The 100% contract was re-proven as one recorded run (218/218 from a clean rebuild; `sdk-dual` both legs;
every oracle green; fleet 363,214 / 13,492,113 / 5,820,205 all 100%; main game-code **45,150 / 45,150** — the build-derived denominator,
3,616 words above Ghidra's) on a tree a stranger can build (`make disc-extract`, `make bootstrap`, the fresh-clone proof, the Ghidra
database regenerable from `config/ghidra/`). The whole history was rewritten with git-filter-repo (4,031 commits verified pair by pair,
`docs/commit-map.tsv`), force-pushed IN PLACE, `.git` 93 MB; the publishing surface (README with generated numbers, AGPL for tools/docs,
no license asserted over `src/`, NOTICE, THIRD_PARTY, badges, ROM-free CI), the releases (gcc-2.7.2 map, xsig, the permuter driver —
offered upstream and declined, the drafter write-up, the decomp.me preset proven through decomp.me's own toolchain), the outreach notes,
story, retrospective, wiki (13 pages) + how-to (13 chapters), and the **Gen3 charter** (`docs/gen3-handoff.md`, `docs/gen3-standards.md`)
are written. **The repository went PUBLIC on 2026-09-08 (Phase 34 task 1, Drew)** after the purge probe passed twice — 2026-09-07 and
again immediately before the flip (33 of 33 sampled old hashes gone; Support ticket #4736982 had done its work) — with the `protect-main`
ruleset (no force-push, no deletion) guarding the published history. **Phase 33.5 CLOSED 2026-09-08 (v1.32.1; `PhaseEnd_Phase33.5.md`):** the docs sub-phase before the flip — the wiki is the single
source of truth (six new pages incl. the Reference index and the Archive index; 59 documents and 34 tools retired into indexed sunset
folders; `doc_links` with six checks), the tracked `.run/` is flip-ready (1,086 → 868 + the phase's own evidence; the two ROM listings
untracked under an audit-only rule + a content check), the memory store reconciled (80 == 80; an 18-file seed), and **the day-one decomp
kit `decomp-architect/`** (a Phase-0.5 overlay on ProjectArchitect 2.0; 436 files) built and dry-run installed five times: the intake
with the 11-phase ladder, G1–G67, DK-1–DK-81, **three verbatim dictionaries** (the tools by need, the cookbook, the record — `make
kit-corpus`, asserted equal in tools-health), `tools/kit_coverage.py` (every rule and every accelerator entry cited or dispositioned —
its first run found 26 + 21 uncited, three genuine gaps), and the worklog mining pass (777 candidates / 634 banked / 143 new → DK-69–80).
R74–R83 ratified at its gate 1; candidates (i)–(xii) proposed for Phase 34 gate 1. **Phase 34's gate is OPEN: the purge probe PASSED
2026-09-07.** **Phase 34 = the flip + the outward actions + C11 + the v2.0.0 PhaseEnd = Gen2 EXIT** (`docs/phase34-seed.md`).
**Phase 34 CLOSED 2026-09-08 (v2.0.0 = GEN2 EXIT; `PhaseEnd_Phase34.md`):** one session (S93), 24 commits — the flip after the probe
passed before and after (33/33 gone); the `protect-main` ruleset, description/topics/homepage; decomp.dev (100.00% / 100.00%); the wiki
(32 pages, three syncs); the decomp.me preset request (decompme/decomp.me#2106) on a 100% scratch, after the pasted target's form was
fixed and proven through decomp.me's own `as` (`verbatim_target_s.py --gas`, replica steps D/E); the Archipelago note (#1); the xsig
topics; the tool announcement, Drew's `#ai` reply and two Decompedia rows; the aftercare (~9 GB of scratch pruned, the record updated,
`docs/outreach/` and `docs/sunset/` out of the tree on the owner's decision, `tools/sunset/` kept, the timeline in the README); three
instrument findings fixed (cdecl's scratch dir, two wiki citations, kit_coverage → DK-81 + twelve dispositions); tools-health OK on run 5.
**Pending by name:** the preset's creation by decomp.me's maintainers, a reply from Archipelago, frogress. Candidates (a)–(d) proposed. **Gen3 opens at Phase 35** — its seed now includes the S91-b types doctrine (R95, the canonical
type layer).

**Phase 35 CLOSED 2026-09-08 (v2.1.0; `PhaseEnd_Phase35.md`) — Gen3's first phase, the DEDUP phase: "one source per unique function."**
Three sessions (S94–S96) / 48 commits: every shared body one plain-C header under `src/shared/` included at each site (3,175 headers, the
8.8 MB macro header gone), the five twins from one source directory, the same-address backlog 1,099 classes / 4,755 copies → 51 ledgered
/ 160, a new `h_text` registry tier for 38 byte-variant functions, S1 a tools-health gate with a second oracle, 14 macro-era tools frozen +
4 retired behind a guard, the published counts corrected (+459 functions; REAL 360,744 → 350,533 with EMPTY up the same). R96–R99 ratified;
candidates (a)–(g) proposed. **Gen3 continues at Phase 36 — pins off** (Drew's order dedup → pins → structs → names). The open paragraph:
*Phase 35 OPEN (2026-09-08, S94; gate 1 in plan mode at Max)*
Drew set the Gen3 order dedup → pins → structs → names (one phase each, planned one at a time). The phase converts the 3,516 distinct
`DEFINE_func_` macro bodies (5,147 define lines) into per-function plain-C headers under `src/shared/<space>/` included at each member's
site (sotn's shape, verified from its tree), collapses the five identical-payload twin overlays onto one source directory each, shares
the same-address duplicate backlog (~11,289 copies; ~70% in the twins), censuses and DEFERS the 3,697 cross-address classes to the
names phase, freezes the macro-era tools with a loud refusal, and wires the S1 invariant into `make tools-health`. R96–R99 ratified at
gate 1. The live state is `phase-ends/CURRENT_PHASE.md`; closes at v2.1.0.

## 1. Corrections and supersessions of PROJECT_CONTEXT.md recorded in PhaseEnds (P1: the constitution is never edited)
- **Session start** reads this digest + the last three PhaseEnds, not every PhaseEnd (R64 candidate, Drew 2026-09-05).
- **P8 "absorb and delete CURRENT_PHASE.md"** → **R19**: `git mv` it to `phase-ends/logs/Phase<N>.md`, out of the load
  order; consult a log only when researching a past mechanism.
- **Commit cadence:** P4 per-task → R8 one-commit-at-phase-end (P2) → per-session checkpoint commits (P7) and R20
  backups → today: **one commit per completed task after CURRENT_PHASE.md is updated; a bank commits the moment it
  exists (R42)**. Claude commits; **Drew pushes** (R6); the PhaseEnd + archived log are left uncommitted for Drew's
  milestone-close commit; no `Co-Authored-By` (R5).
- **H1** was relaxed while private (R1, 2026-06-10 → 2026-09-06) and is **IN FORCE again since Phase 33 C3 (2026-09-06)**: the ROM-derived and proprietary paths left the index and were purged from the whole history before the public flip (`docs/public-flip-runbook.md`); R1 is historical. **The flip itself happened on 2026-09-08 (Phase 34 task 1).** **R20's backup home** is now the text export `config/ghidra/` (+ `tools/ghidra_rebuild.sh --proof`), `dumps/CHECKSUMS.sha1`, `tools/psyq_CHECKSUMS.sha256`, and the private archive repo `Druthulu/BFM-decomp-archive` (the pre-rewrite history); **never `git clean -x`** (CLAUDE.md fail-safe).
- **Environment:** all-in-WSL (R2); Ghidra runs **headless** (MCP server via `tools/ghidra_mcp_start.sh` / the
  SessionStart hook; symbols persist only via `tools/ghidra_apply_symbols.sh`, MCP renames do not); PCSX-Redux is
  Windows-native bridged over the web API (R11); no `/tmp`, scratch under `.run/` (R12).
- **Roadmap:** the constitution's Gen1 roadmap ended at Phase 7 (Gen1 EXIT confirmed 2026-06-15); Gen2 phases 8–32 are
  governed by `docs/gen2-roadmap.md` → `docs/roadmap-to-100.md` v2 (both archived under `docs/sunset/` at Phase 33.5; the
  outcomes are in the PhaseEnds); **Phase 14 (public flip) became P33** — executed as an
  IN-PLACE flip with the full rewritten history (not gen2-roadmap's two-repo mirror; decision log P33 S86), 2026-09-06/07.
- **Effort doctrine (Drew 2026-07-04, `docs/effort-map.md` governs):** xHigh for most tasks, Max for deep tasks (phase
  plans, PhaseEnds, non-obvious debugging), Ultracode for breadth; plan mode always Max; every transition is prompted
  (R27). Model ladder for drafters: Haiku ≤~50 ins → Sonnet ~50–120 → Opus ≥120 → Fable only for a NEW wall class.
- **Compiler triple pinned** (P6, SETUP §5.4): `gcc-2.7.2-psx cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float
  -fgnu-linker` → `maspsx --aspsx-version=2.56 --expand-div` → `mipsel-as -march=r3000 -mtune=r3000 -no-pad-sections
  -O1 -G0`; per-file `-O0` modules exist (boot, the `_o0` splits).

## 2. Phase synopses (what each phase delivered, its key finding, the rules it added)
**P1 (2026-06-13, v1.1.0) Repo governance + WSL RE stack.** Ghidra 12.1 + GhidrAssistMCP + ghidra_psx_ldr installed
headless; `SLUS_007.26` imported (1,726 fns, PsyQ 4.0.0), PsyQ types imported; the LZSS decompressor at 0x80018730
decompiled via MCP. Rules R1–R6.
**P2 (2026-06-13, v1.2.0) Deterministic extraction.** `tools/bfm_extract` walks the disc/.CD/PAC/LZSS into 1,801
manifest-tracked artifacts, byte-validated against CUE's `brave` (138/138 type-4). `docs/effort-map.md`. Rules R7, R8.
**P3 (2026-06-14, v1.3.0) File-loader & overlay map.** The loader is a hand-rolled CdControl reader driven by
`cdFileLocTable` (LIST.CD) + `resourceIdMap`; LZSS staging 0x80079A70; PCSX-Redux runtime oracle; resident blob
@0x800CEDF8 and location overlays @0x80128158 byte-proven against live RAM; 13 area-states; player state verified.
Rules R9–R12.
**P3.5 (2026-06-14, v1.3.1) Prototype spike — NO-GO.** Neither US prototype carries symbols; Sep-8 = retail minus 3
functions; protos kept only as assets. Rules R13, R14.
**P4 (2026-06-14, v1.4.0) Build toolchain.** binutils-mipsel 2.42, splat64 0.41.0, pinned submodules
(maspsx/asm-differ/m2c/decomp-permuter), gcc-2.7.2-psx/cdk cc1 (i386 static); `make check-env`. No rules.
**P5 (2026-06-14, v1.5.0) All-asm byte-identical EXE** (`143dbb89…`) from the splat config; `-G0`; binutils 2.42
byte-clean. Rule R15.
**P6 (2026-06-14, v1.6.0) Compiler pinned + first matches.** The triple above (`--expand-div` required); 14 matches;
`docs/matching-cookbook.md` and the permuter harness created. Rule R16.
**P7 (2026-06-15, v1.7.0) Gen1 EXIT.** Reports (progress/difficulty/dup); the `-O0` boot module; **real PsyQ library
objects linked byte-identical** (libcd + libgs); LZSS matched; 43 REAL. Rules R17–R19.
**P8 (2026-06-15, v1.8.0)** Eight more PsyQ libraries linked; EXE 50.24% byte-identical-from-source. Rule R22.
**P9 (2026-06-15, v1.9.0)** Binary-agnostic toolchain (`make build BINARY=<alias>`, required `--vram-base/--exe`). Rule R23.
**P10 (2026-06-15, v1.10.0)** The resident engine blob is the 2nd byte-identical binary (`8e17e02f…`, flat-blob
recipe); it detects PsyQ 4.7. Rules R24, R25.
**P11 (2026-06-16, v1.11.0)** Cross-binary dedup pipeline (`sig_image.py`, `dup_report --cross`, `config/dedup.us.yaml`,
`src/shared/`); all 134 overlays signed — 9,366 cross-binary groups. No rules.
**P12 (2026-06-16, v1.12.0)** Resident harvest 1.4% → 85.6% via the Ultracode parallel-draft + whole-binary byte-gate
(`harvest_verify.py`, `match_one.py`); the "script VM" is compiled-MIPS dispatch tables; save format documented. Rule R26.
**P13 (2026-06-16, v1.13.0)** Representative overlays; 6 binaries; `tools/new_overlay.sh`; non-4-aligned overlay
handling; dup-pair collapse. Rules R27–R29.
**P15 (2026-06-18, v1.14.0)** All 134 overlays onboarded (136 binaries); `dedup_propagate` + `engine_core.h` (match once
→ ×134); fleet 3.82% → 54.48%; `sig_unify`. No rules. (P14 public flip deferred.)
**P16 (2026-06-19, v1.15.0) PIVOT.** m2c + permuter cannot crack the loose-typed engine core (~3%); `docs/struct-core-pivot.md`.
**P17 (2026-06-20, v1.16.0)** Canonical-sig layer; the wall is the compiler's codegen, not signatures/types; 55.51%.
**P18 (2026-06-20, v1.17.0)** Compiler-quirk research → the register-pin toolkit (cookbook §17); waves 33% → 56% → 90%
close-rate; 56.64%.
**P19 (2026-06-20, v1.18.0)** Scaled waves (88/92% match_one); `canon_resident_calls`, `fix_arity_callers`; propagation
is the cap; 58.00%.
**P20 (2026-06-21, v1.19.0)** `cast_call_sites` cap tool; typedef type-lift; the `%lo`-fold class cracked; 58.82%. Rule R30.
**P21 (2026-06-26, v1.20.0)** The automation manager (`gate_stage`, `worker_wave`, `grinder`, `orchestrator`, backlog
ledger, `idiom_loop`); 63.18%; automated ceiling byte-proven; a 5-scout sweep found no external shortcut.
**P22 (2026-06-29, v1.21.0)** Tractable giants banked ×134; 63.66%; pivot to the local LLM tier.
**P23 (2026-07-02, v1.22.0) THE BREAKTHROUGH.** Local 7B tier saturates ≤15-ins ($0); **Fable reading the gcc-2.7.2
source cracks "unsteerable" classes** → the §31 codegen map (`docs/gcc-2.7.2-map/`); 64.86%; `gcc-papermario` is
gcc 2.8.1 — vanilla 2.7.2 staged under `tools/reference/`.
**P24 (2026-07-08, v1.23.0)** Permuter overhaul (masked scorer, §31 class weights, ILS); integration-recovery tools;
every matched giant ×134 (incl. the 770-ins whale, the 400-ins flagship); 66.02%; the h_norm structural-family reframe.
**P25 (2026-07-11, v1.24.0)** Family engine (`family_remap`/`family_sweep`, `canon_sig_reconcile` v3.2, `rtu_match`);
giant endgame complete; 74.6% fn / 58.2% instr / 30.3% distinct; the h_seq reframe → `family-endgame-megaplan.md`. Rule R31.
**P26 (2026-07-15, v1.25.0)** Family engine + the **26-A tooling-integrity audit** (`corpus.py`, `cdecl.py`,
`audit-corpus` — the tools WERE several walls) + the §52 discovery flywheel; 68.9% instr / 49.2% distinct; mechanical
harvest exhausted. Rules R32–R34.
**P27 (2026-07-15, v1.26.0)** Instruments fixed (fail-closed Makefile, one typedef-strip primitive, second oracle on
resident); disc audit 136 → 140 + 39 type-1 modules found; the pin-crash "wall" was a tool bug; 67.0% (denominator
correction). Rule R35.
**P28 (2026-07-16, v1.27.0)** Instrument repair; B2 LIVES (its 0/8 was a missing carve); SC07 pool wired via
`dedup_extend` (6,174 members); resident 90%; 68.9%. Rule R36.
**P29 (2026-07-30, v1.28.0) THE FAMILY CAMPAIGN.** 25 sessions / 552 commits; 68.9 → 87.5% instr, 49.5 → 78.0% distinct;
`diff_regions.py` resolved the swing number (tooling); integration, not idioms, is the wave bottleneck; roadmap v2.
Rule R37 proposed.
**P30 (2026-08-14, v1.29.0)** Recovery & concentration; 87.5 → 95.3% instr; fleet 140 → 213 (disc audit + module
onboarding); the zero-token mechanical pipeline (`aprop_autodraft`, `symfix`, `prechecks`, `gate_lane`); the §172 wall
model. R37 operated as binding; R38–R39 proposed.
**P31 (2026-09-05, v1.30.0) THE FRONTIER ATLAS & WIDE-TOLERANCE CAMPAIGN.** 30 sessions / ~1,660 commits; the atlas
(`atlas.py`), 6,000-ins waves, autonomous lanes, a completion sprint; stubs 12,059 → 21; fleet 95.3 → 100.0% instr;
main 1,041 → 12 open; libpad 4.2.1 + RTL 4.2 archive linked (twelve "walls" were Sony objects); the verbatim `__asm__`
class censused to 5 PERMANENT rows; `gate_main` (main gates only by clean rebuild). R37–R39 ratified; R40–R43 + R61
accepted; R44–R60, R62–R63 proposed → **all ratified at P32 gate 1 (2026-09-05)**.
**P32 (2026-09-06, v1.31.0) THE FRONTIER EMPTIED.** 5 sessions (S81–S85) / 111 commits. The five parked disc payloads
onboarded on their first static-derived bases (fleet 213 → 218, UNCLAIMED 0 of 220); 77 functions banked — 3 tooling-first,
20 free, 39 by a one-agent-per-function pass, 13 in T4b (Drew's directive: everything short of Sony's objects and the original
hand-asm must be C — 11 by a Fable pass reading pass dumps, 2 by hand), 2 in T4c (the "PROVED"/"PLATEAU" main rows) — every
final bank pin-free. Two written verdicts fell to producers missing from their censuses: combine's self-update bookkeeping
gap that mints a no-traffic frame slot (§501-Q) and loop.c's user-variable rule + cse's later-mention canonicalization
(§501-R: three inline temps merged by `combine_movables`, `u16` as a cse firewall, the allocation order IS the callee-saved
bank). Census 0 stubs; fleet 100.00 / 100.0 / 100.0; main 2,091 / 2,091. `phase-ends/DIGEST.md` created (R64). Rules: R44–R63
ratified at gate 1; **R64 ratified**; candidates (i)–(ix) recorded. Instruments: `payload_base_evidence.py`, `ghost_census.py`,
`agent_drafts_restore.py`, `cc1_dumps_tu.sh`, `alloc_table.py`, `bank.sh`.
**P33 (2026-09-07, v1.32.0) VERIFIED, REWRITTEN, PUBLISHED-READY (re-chartered close).** 4 sessions (S86–S89) / 59 commits. Block A:
instruments fixed (build-derived `sig-main`: main game-code 45,150 not 41,534; `NO_SDK` + `make sdk-dual`) and THE RECORDED RUN
(`tools/verify_contract.sh`, `docs/verification.md`, 218/218). Block B: the public build path (`make disc-extract`, portable includes,
`tools/bootstrap.sh` + the fresh-clone proof 218/218 in 4 m 18 s, `tools/fetch_psyq.sh`, Ghidra export/import/rebuild `--proof`,
`dumps/CHECKSUMS.sha1`, the ROM-free CI with `audit_public.py` + `compile_only.py`). Block C: `tools/public_rewrite/` — two trial rewrites
caught two corrupting defects; the real rewrite 4,032 → 4,031 commits / 0 old hashes / 4,031 pairs verified; adoption, `commit-map.tsv`,
C8 R22, Drew's force-push, gc (12 stale worktrees pinned 12 GB), `.git` 1.5 GB → 93 MB. Block D: README/LICENSE/NOTICE/THIRD_PARTY,
badges + objdiff + frogress, SETUP public-clean, `doc_links`. Block E: gcc-map README + `gccmap_cites`, `tools/xsig/` + `Druthulu/xsig`
(public), the permuter PR (#213/#214 **closed unmerged** — the maintainer keeps the wildcard, prefers symbol renames in the asm, and
read the model-drafted text as LLM-written → Drew's rule: outward text in a developer's voice, no AI acknowledgement), the drafter
write-up, `decompme-preset.md` + `tools/decompme_replica.sh` (decomp.me = old-gcc 0.13 + maspsx 86ccd7d8, rebuilt locally, 26/26 words),
`outreach/archipelago.md` (+ four memory-map corrections from reading their addresses against our source). Block F: `timeline.py` +
story, `mine_hindsight.py` + retrospective, the wiki + how-to + `wiki_render`/`wiki_sync`. Block G: `gen3-handoff.md`, `gen3-standards.md`,
`phase34-seed.md`. Findings: GitHub's Activity view publishes every pre-force-push tip (the flip must wait for the purge); the probe was
a writer (R57). Rules: R65–R73 ratified at gate 1; candidates (a)–(j) proposed for P34 gate 1.
**P34 (2026-09-08, v2.0.0) THE FLIP — GEN2 EXIT.** One session (S93) / 24 commits. Gate 1 (plan mode, Max) ratified R84–R95 and added
metadata, a ruleset and a Release; the preflight found (and Drew deleted) a Phase-1 relic clone of the old history. The probe PASSed
before and after the flip; Drew made the repository public; Claude set description/7 topics/homepage and the `protect-main` ruleset
(no force-push, no deletion, no bypass). Outward, all the same day: decomp.dev registered and verified (100.00% / 100.00%, hero image);
the wiki pushed three times on one-off R6 waivers (32 pages); the decomp.me scratch at 100% + the preset request #2106 + the manual
search closing ledger row 14 — after the first paste FAILED (`invalid operands 'li a2,2'`: the doc named the word-oracle listing, never
assembled anywhere) and the tools were fixed: `verbatim_target_s.py --gas`, `decompme_replica.sh` steps D (the paste through decomp.me's
`as`, 26/26) and E (the bundle); the Archipelago issue #1; xsig topics + homepage; the tools post, Drew's `#ai` reply, two Decompedia
rows; frogress skipped on measurement. C11: no other clone; ~9 GB of untracked scratch pruned (46 → 37 GB); `.run/public_rewrite/` kept
to the probe's inputs; DIGEST/decision-log/accelerators/SETUP/wiki updated; the generated timeline in the README; `docs/outreach/` and
`docs/sunset/` untracked on Drew's decisions (the Archive index is the record; `tools/sunset/` kept for the index). The close chain went
red three times on the day's own edits — cdecl's probe dir under the pruned tree (a refusal misgraded as four defects), two wiki
citations of untracked paths, R84–R95 + the new accelerators entry uncited in the kit (→ DK-81 + twelve map rows) — and was OK on run 5;
one commit claimed "green" from a masked exit code and was named in the next. Rules: R84–R95 ratified; candidates (a)–(d) proposed.
**P33.5 (2026-09-08, v1.32.1) THE WIKI AS SOURCE OF TRUTH + THE DAY-ONE DECOMP KIT (sub-phase).** 3 sessions (S90–S92) / 26 commits.
Six wiki pages (conventions, the ROM firewall with the copyable `.gitignore` fence, the Reference index — the only wiki→`docs/` link site —,
the direction page, Start-a-new-decomp-project, the Archive index); six documents folded into the wiki/how-to; 59 docs + 34 tools sunset
by `git mv` with review tables; `doc_links` rewritten (links + pending, the archive refusal, wiki-first, coverage ⊆, TRACKED/UNTRACKED
citations) + render reachability + `timeline` wired + `gitignore_template_check` + `audit_public` check 4 (disassembly-shaped runs ≥ 64) +
the audit-only `untracked_after_rewrite.txt`; tracked `.run/` 1,086 → 868; the memory store reconciled. **The kit:** intake (11-phase
ladder, the six inversions), SETUP (Step 0–10, derived verify lines), the methodology, 19 templates, G1–G67, DK-1–DK-81, the three
dictionaries (`tool_census` + `config/tool_dictionary.tsv` → `docs/tool-index.md`, the kit's MANIFEST, `corpus/tools` 302+28, `corpus/cookbook`,
`corpus/record` 57 files incl. the health chain), `kit_lint`, `kit_coverage` (+ `config/kit_coverage_map.tsv`), 18 memory seeds; five
dry-runs in a throwaway judged by script (run 5 PASS 20/20). Findings: the kit had been distilled from summaries only (57/83 rules,
40/53 accelerators, 0 PhaseEnds/logs cited) → the coverage check + the record + the worklog pass (143 of 777 candidates banked nowhere);
the S91-b types hindsight (a banking + width lever → the canonical type layer at Phase 6, DK-65/G62); a typed verify figure wrong twice;
four false judge flags in five runs, all the instrument's. Rules: R74–R83 ratified at gate 1; candidates (i)–(xii) proposed.

**P35 (2026-09-08, v2.1.0) GEN3 OPENS — THE DEDUP PHASE.** 3 sessions (S94–S96) / 48 commits. Gate 1 reversed the 2026-09-02 "leave the
backlog" decision on sotn's tree (it shares once, by an include). T1 `share_census` (362,389 instances, 0 unaccounted, 10,180 classes);
T2 the health chain learns the include + twin forms; T3 five twin pairs → one source dir (166 files deleted); T4 `macro_to_header`: 246,347
sites → 2,215 headers, 213/213 binaries and 4,121/4,121 objects byte-identical, `engine_core.h` deleted; T5 `share_body` (bucket 0 183 →
135 shared / 48 ledgered; bucket new 915 → 914 / 3; a re-exemplar), the S94 death at 91 % and the S95 transcript recovery, four tool
defects fixed at their cause; T5b the `h_text` tier (38 classes / 2,030 sites); T6 14 frozen / 4 retired / the guard; T7 S1 strict + C2c/C2d
in tools-health, the digest corrected; T8 the record (wiki, cookbook §453, decision log). Close: R22 218/218; S1 10,180/10,180, 0
violations; fleet clean-run 157 s → 84–90 s. Rules: R96–R99 ratified; candidates (a)–(g).

## 3. Every rule, in full (transcribe these at session start; P/G/H/X are in PROJECT_CONTEXT.md)
- **R1 — H1 relaxed while private.** ROM-derived content (`asm/`, `assets/`, `extracted/`, decompressed `.CD`) MAY be
  committed while the repo is private; accidental inclusion is not a violation. The raw multi-GB disc dump stays ignored
  regardless. Compliance before going public = history scrub + a rom→decoder regeneration tool.
- **R2 — All-in-WSL (H2 restatement).** One ext4 clone at `~/bfm-decomp`; no Windows/WSL split, no second clone, no
  `/mnt` builds; MCP is loopback `127.0.0.1:8080`.
- **R3 — All tooling under `tools/`.** Including `tools/bin` (compilers), `tools/psyq*`, `tools/ghidra_scripts`.
- **R4 — Plan mode every phase.** Present the task-by-task plan and get approval before executing (the Phase Start gate).
- **R5 — No `Co-Authored-By` trailer on commits.**
- **R6 — Git workflow = Claude commits in WSL, Drew pushes.** Never `git push` from the WSL CLI. Phase-boundary
  exception: Claude writes `PhaseEnd_PhaseN.md` and archives `CURRENT_PHASE.md` but leaves them uncommitted; Drew
  commits AND pushes the milestone close.
- **R7 — Effort-map check.** Before each Phase Start, state the recommended effort for planning that phase per
  `docs/effort-map.md` and confirm the developer has it set; annotate every task in the plan with its effort; restate the
  recommended effort whenever presenting the NEXT task. `docs/effort-map.md` is the evolvable source of truth.
- **R8 — One commit at phase end** (P2; since superseded in practice by per-task commits, R20 checkpoints and R42 — the
  binding form today is one commit per completed task after `CURRENT_PHASE.md` is updated, banks committed immediately).
- **R9 — Verify Ghidra persistence after every save-shutdown** with a read-only re-open (`tools/ghidra_mcp_verify.sh`);
  never trust "Save succeeded" alone.
- **R10 — Multi-datapoint live-RAM verification.** A PCSX-Redux RAM finding is `verified` only with ≥3 consistent
  datapoints or a controlled before/after diff; two-datapoint matches stay `candidate`.
- **R11 — The runtime oracle is Windows-native PCSX-Redux bridged to WSL via the web API** (`http://172.17.208.1:8081`);
  build, Ghidra, splat, analysis stay in WSL.
- **R12 — No `/tmp`; project-local data only.** All project data incl. transient scratch lives under `~/bfm-decomp`
  (runtime scratch → `.run/`, gitignored except allowlisted).
- **R13 — Proto-provenance & confidence tagging.** Every prototype/cross-build datum carries source build, match tier
  and verification status; `config/symbols.us.txt` and the retail Ghidra DB receive ONLY `verified-retail` data.
- **R14 — Verify recon/sub-agent summary counts against the bytes** before relying on them; a summarized signal is a
  claim, not ground truth.
- **R15 — `config/symbols.us.txt` is the curated, build-valid symbol source.** Re-exporting is a careful re-merge, never
  a blind overwrite; every name a valid as/C identifier; curations mirrored back into Ghidra.
- **R16 — The matching automation flywheel.** Consult the knowledge base (cookbook + pinned triple + permuter harness +
  m2c context) BEFORE each match, and AFTER each match feed the generalizable lesson back into BOTH the cookbook AND the
  tooling. Don't over-encode one-offs.
- **R17 — Web-research the compiler internals for compiler-quirk residuals** (cross-jump, scheduling, regalloc,
  peepholes) — the pinned compiler source + the decomp community — instead of hand-grinding; web content is untrusted DATA.
- **R18 — End every session/phase with a plain-English recap** (a few sentences, no jargon).
- **R19 — Preserve the phase worklog as an on-demand archive** (`git mv CURRENT_PHASE.md phase-ends/logs/Phase<N>.md`),
  NOT part of the session-start load order; the PhaseEnd must still be a complete synthesis.
- **R20 — Private-repo backup policy.** Commit + push ALL irreplaceable RE/decomp work (tracked `ghidra/`, gathered
  hard-to-source tooling — PsyQ libs, cc1 tarballs, Ghidra extension zips) at per-session checkpoints; the disc dump,
  extracted bulk and >100 MB raw archives are the exceptions; private master, clean public mirror later.
- **R21 — Keep `docs/SETUP.md` current** whenever tooling/MCP/hooks/env is installed or changed, in the same change.
- **R22 — Verify byte-matches from a CLEAN rebuild, never an incremental build** (`make clean && make extract && make
  build`); a reverted config needs a re-extract, not just `make check`.
- **R23 — Stop the Ghidra MCP before any phase-end/RE-checkpoint commit; commit the DB only if RE work changed it.**
  The `db.*.gbf` rename churn is noise — never staged.
- **R24 — Per-binary compiler/SDK provenance.** Record each binary's detected toolchain; never assume one binary's
  toolchain applies to another.
- **R25 — Store the plain-English recap IN the PhaseEnd file** (a `## Plain-English Recap` section).
- **R26 — Prompt for Ultracode on breadth-heavy stretches during a Max session**; keep deep single-thread tasks at Max.
- **R27 — Effort-transition discipline.** At every transition — into Ultracode, back to Max, at task hand-off — STOP,
  prompt Drew to toggle, and WAIT for the actual `/effort` command; never launch a Workflow on a verbal yes.
- **R28 — Build the harness task list right after plan approval**, before starting work (one TaskCreate per plan task).
- **R29 — Pause + prompt for `/mcp` reconnect after any MCP server restart/program switch**, then one cheap
  `get_binary_info` (G2) before continuing.
- **R30 — Capture context-dependent knowledge artifacts DURING the producing session**, before any fresh-session handoff;
  defer only mechanical/continuable work.
- **R31 — Capture the WHY behind strategic pivots in `docs/decision-log.md` while fresh**: context+belief → what failed →
  the pivot → the measurement-grounded why → a hindsight "better path".
- **R32 — Assert your COVERAGE.** A corpus scanner compares what it found against an over-approximating candidate set
  and fails on the gap; a silent skip is a defect, and a loud failure nobody counts is exactly as invisible.
- **R33 — Derive, don't re-derive.** Where a proven invariant answers the question, derive from it rather than re-parse
  the source; the best outcome is a DELETED scanner.
- **R34 — A second, DISAGREEING oracle — not a better assertion** — when an oracle is structurally blind to an error class.
- **R35 — Fix the measuring instrument before trusting its measurement; a probe from a broken tool is not evidence.**
  Tool-integrity is a precondition of a measurement, not a parallel concern.
- **R36 — A newly-discovered binary is not real until every consumer knows it** (sig set, family map, dedup registry,
  shared-header include, reports) — asserted by a gate (`make audit-binaries`), not remembered.
- **R37 — Probe before costing.** Ground every estimate/attribution on ONE instance; derive counts from `corpus.stubs`;
  diff the artifact to prove an edit actually ran before judging the lever it carried.
- **R38 — Read the recorded failure verdicts before designing an experiment** (`.run/harvest_failed.*.classified.txt`,
  gate results, journals) — the answer is frequently already recorded.
- **R39 — Negative-control every new refusal-check against the already-succeeded population**; zero false positives
  before it ships.
- **R40 — Exonerate the instrument before attributing a failure to its subject** (truncation, fences, rate limits, tool
  faults first; ~a third of P31's "walls" were tooling).
- **R41 — Every cost/rate/yield/effort number ships with its denominator.**
- **R42 — Commit banked work the moment it exists**, before the next command that can touch `src/` (a gate IS one);
  never blind-revert a dirty `src/`; count banks from the SOURCE.
- **R43 — A tool must refuse an input it cannot handle, never process it wrongly.**
- **R44 — A card may not name a lever the knowledge base does not contain.**
- **R45 — Draw-time bankability: never draw a card the pipeline cannot bank.**
- **R46 — A budget is part of the harness, not a constant.**
- **R47 — Consume every verdict layer** (a stage reading one bit of one oracle staged garbage forever).
- **R48 — Never key by bare function name** (scratch dirs, ledgers, drafts — collisions destroy work).
- **R49 — A soft error inside a success envelope is still that error** (a 200 carrying code 429; `rc≠0` read as "no binary").
- **R50 — Periodic whole-fleet verification** (a byte gate is silent about every binary it did not build).
- **R51 — A derived property stored as config will go stale and take a binary with it**; derive it or give it a
  byte-proven self-repair.
- **R52 — A blanket committer must not adopt a collapsed file** (right for `src/`, wrong for config).
- **R53 — Verify a build from its exit code, not its output file** (a failed build leaves the previous binary in place).
- **R54 — A guard downstream of the failure is not a guard, and a guard that is not running is not a guard.**
- **R55 — A lane that runs unattended must leave evidence** (progress logs; empty log + no ps hits = never started).
- **R56 — A gate verdict measures the draft only while the binary's baseline is green**; check the baseline first.
- **R57 — An instrument's own write path is part of the instrument.**
- **R58 — A session-close "clean" must quote the fleet's green count** (tree-clean ≠ fleet-green).
- **R59 — A blanket commit of another lane's mid-gate tree is a race, not a backup.**
- **R60 — `config/overlays.mk` and the splat yamls are CARVE STATE**: a gate commit carries only its own binary's lines;
  any blanket restore/commit is followed by `interleave_check` + `pads_audit` on every touched binary.
- **R61 — A tool must distinguish "judged and failed" from "not judged", and a judging tool must model what the gate
  does to the draft** (a loop tool that reports "unchanged" for N cycles must prove it iterated).
- **R62 — A ledger's best draft may never be an `__asm__` body, and a bank whose body is `__asm__` is a verbatim, not a
  bank** (`verbatim_check --strict` in the per-bank close).
- **R63 — A permuter/waypoint score is not a closeness until its diff is read.**
- **R64 (RATIFIED at PhaseEnd_Phase32, 2026-09-06; Drew-directed 2026-09-05) — Session start reads PROJECT_CONTEXT.md →
  `phase-ends/DIGEST.md` → the three most recent PhaseEnds → `CURRENT_PHASE.md`, then replays the 🛑 SESSION CHECKPOINT
  block VERBATIM into the chat; the protocol costs ≈100k tokens + the checkpoint. Every PhaseEnd appends its synopsis
  and rules to the digest (P7). A checkpoint is written to be replayed: self-sufficient, verbose, every path/command/hash
  explicit (see `checkpoint-current-phase-before-pause` memory).**
(R40–R43 and R61 were accepted mid-P31; their long forms are in `phase-ends/logs/Phase31.md` — the one-liners above are
the binding text. R44–R63 one-liners are the P31 table, ratified at P32 gate 1.)
**R65–R73 — RATIFIED at Phase 33 gate 1 (Drew, 2026-09-06; the PhaseEnd_Phase32 candidates (i)–(ix), operated all of P32):**
- **R65 — A wall verdict must be PASS-attributed with a dump line** (R40 extended: exonerate the instrument, then NAME the
  compiler pass, quoting the dump line that shows it). Six of the seven P32 T4 wall citations named the wrong pass; each crack
  came from one dump line (§501).
- **R66 — Write "banked" only from the tool's printed success line** (`gate_main`'s BANKED line, `bank.sh`'s sha == config
  line); never from the intent to bank. Two S83 ledger messages claimed banks that had not happened (a helper no-op on an
  empty list; a wrong draft dir).
- **R67 — Agents write their deliverables early** (draft file first, verdict JSON last); every agent lost to a usage limit
  had to be resumed, and the one that had written its draft first banked from the dead run.
- **R68 — A helper must refuse an empty work list** (R43 restated for helpers): `bank.sh` built the unchanged tree and exited
  0 on an empty function list.
- **R69 — A residual gets a PRODUCER CENSUS from the compiler source before any spelling sweep, and "PROVED" means every
  producer on a NAMED list was refuted on the bytes** — a verdict says what it was proved against. §501-M/O were right about
  their lists; §501-Q/R were the producers missing from them.
- **R70 — A ledger's tie-break is part of the instrument.** `backlog.py` kept the earliest record at equal closeness, so a
  re-verdict could never render (S84).
- **R71 — When a same-family sibling is banked, port its SPELLING before touching a dial on the draft** (§501-N first try;
  §501-P first try after 3,360 sweep variants).
- **R72 — A similarity score is not a shape oracle:** a hand pass opens with a grep for the idiom's literal constants across
  `src/` and an objdump of each hit's window against the target (the atlas scored the exact sibling 0.55, §501-P).
- **R73 — Build the 1-second reproducer battery for a mechanism BEFORE probing the real function, and read the allocation
  ORDER (`tools/alloc_table.py`) before any register lever** (§501-Q from 18 five-line reproducers after two sessions of
  real-function probes; §501-R from an 8-variant reproducer sweep; every pin then came off — accelerators (15)/(16)).
**R74–R83 — RATIFIED at Phase 33.5 gate 1 (Drew, 2026-09-07; the PhaseEnd_Phase33 candidates (a)–(j), operated through P33):**
- **R74 — No ROM-derived bytes in ANY published artifact** — test fixtures, JSON, badges, reports, wiki pages and tracked scratch
  included. The xsig fixture was built from our own C at two link addresses for exactly this reason; the regenerated target `.s`
  stays under the ignored `.run/`. (Phase 33.5 found one tracked residue — two `fable_cd4` disassembly listings — and untracks it.)
- **R75 — Published numbers are generated, never typed** (R51 applied to documents). `docs/progress.json`, the README block, the
  badges, the timeline: every hand-typed number in the old README was stale. A number that must appear in prose is a dated snapshot
  that carries the command that produced it.
- **R76 — Rehearse every irreversible repository operation on a scratch copy and prove it pair by pair with POSITIVE assertions.**
  Trial rewrite #1 exposed the empty-blob strip-list defect and the unchanged-commit case; the real run had 0 failures.
- **R77 — A linked worktree's HEAD is a ref — audit `git worktree list` before any gc or purge.** 12 stale worktrees (12 GB) pinned
  3,729 old commits through the gc.
- **R78 — R20 amendment: the text export + checksums + the archive repository are the backup; never `git clean -x`.** The purged
  paths are ignored-but-present; a `-x` clean deletes the RE database (CLAUDE.md fail-safe since C3).
- **R79 — `pkill -f` never with a literal the calling shell's own command line contains.** S87 killed its own shell twice (exit 144).
- **R80 — A checker that widens its document set must classify a missing promised page as PENDING, never BROKEN.** `doc_links` +
  `doc_links_pending.txt`: 10 planned pages mid-F3, 0 false failures; the pending list must be EMPTY at a PhaseEnd (`--strict`).
- **R81 — A probe or guard must never write into the repository it guards** — a "read-only" check that fetches, clones or builds does
  so in a throwaway (R57 exemplar). The purge probe re-imported 5.97 GiB of the purged history on every run.
- **R82 — A rewritten history is not private until the objects are gone from the HOST** — its Activity view publishes every
  pre-force-push tip; gate a flip on the probe (or recreate the repository), never on a clean tree. 157 activity rows to 2026-06-11;
  the old tip still served the EXE, the dumps and the archive.
- **R83 — Outward text to third parties is written by Drew the way a developer writes** — short, plain, few or no code spans, no
  bullet walls, no evidence scaffolding — rewritten from the facts, never a model draft with the tells removed; **no AI
  acknowledgement**; the target project's AI-contribution policy is read first. The permuter maintainer closed #213/#214 and named
  the LLM-looking text as the reason he minded; sotn-decomp forbids autonomous-tool PRs outright.
**R84–R95 — RATIFIED at Phase 34 gate 1 (Drew, 2026-09-08; the PhaseEnd_Phase33.5 candidates (i)–(xii), operated through P33.5):**
- **R84 — An ignore file's directory-form rule is a wall no later block can climb — write the by-contents form first.**
  ProjectArchitect's `.run/` defeated every re-include beneath it; dry-run 1 stopped on it (DK-67, accelerators S91 (1)).
- **R85 — A check compares two DERIVED figures; a typed figure in a verify line is wrong the day the derived side moves.** Run 4
  stopped on `321 != 293`; the kernel count was typed `= 64` the day it became 65.
- **R86 — A dry-run judge is an instrument — negative-control it against a known-PASS run before believing a FAIL.** Four of its
  flags across five runs were its own (scope, count vs set, a stripped porcelain line, an empty value).
- **R87 — A tool ships with its dictionary row, or the health check fails.** 91 of 326 tools had no consumer and no way to be found
  by need; the census + the dictionary made the index and the corpus (G66).
- **R88 — Re-run `doc_links --strict` after ANY untrack or archive move, not only after a docs edit.** Task 10 found tools-health red
  on the docs side since task 8's untrack; the claim had been carried from task 7.
- **R89 — An unattended installer's manifest is specified as a derivable SET.** Two honest agents produced 57 and 46 entries from the
  same words (run 3).
- **R90 — A governance system that keeps transcripts in the repository needs the firewall's class-7 line.** A decomp's transcripts
  quote the target's disassembly; the source project purged ~260,000 lines of `.s` from its own archive.
- **R91 — A foreign project's path is named in prose, never as a backticked `docs/…` citation.** The checker reads every such
  citation as this repository's (tasks 7 and 14 both hit it).
- **R92 — A distillation ships with a coverage check against the populations it claims to distil.** `kit_coverage`'s first run: 26
  uncited rules, 21 uncited entries, three genuine gaps → DK-66/67/68.
- **R93 — The worklogs get one final read at the end of the project, with an "already banked?" grep per candidate.** 777
  candidates, 143 banked nowhere; the missing fifth was fixed-but-never-generalised.
- **R94 — A snapshot instrument never `.strip()`s a porcelain listing.** The run-5 false flag: the first line's status space eaten,
  a deletion under the dry-run's own directory read as foreign.
- **R95 — Types are a banking lever and a width lever, not a codegen lever: a canonical type file from the first bank, widths
  proven by the bytes at bank time, no duplicate definition or raw address cast banked** (the S91-b doctrine; the binding Gen3 type
  rule). Phase 17 measured the codegen half (0/10/2, identical bytes) and the project underweighted the other: 1,232 definitions,
  143 raw casts, a reconcile ladder built to repair what the discipline prevents.
**Phase 34 proposed candidates (a)–(d) for Phase 35 gate 1** (the table in `PhaseEnd_Phase34.md` §Rules: a scratch prune is an
instrument change — re-run every tool that writes under it; "green" is read from a check's EXIT CODE with `pipefail` in every chain,
never from its last line; a step that hands a file to a third party is proven through that party's own toolchain on the file itself
before the owner's browser session, and the proving tool writes the paste; what a public tree carries is decided before the flip, and a
retired document gets its Archive-index row and is deleted in the same commit).

**R96–R99 — RATIFIED at Phase 35 gate 1 (Drew, 2026-09-08; the PhaseEnd_Phase34 candidates (a)–(d), operated through P34):**
- **R96 — A scratch prune is an instrument change:** every tool that writes under a pruned tree is re-run before the prune is called
  done. `cdecl --audit` wrote its probe under the pruned `.run/audit/`; the refusal read as four parser defects (P34 run 1 of the close chain).
- **R97 — "Green" is read from a check's EXIT CODE, never from its last line; every chain sets `pipefail`.** Commit `81ec81945` claimed
  "kit_coverage green" while three rows were refused — a `tail` masked the status.
- **R98 — A step that hands a file to a third party is proven through that party's own toolchain, on the file itself, before the
  owner's browser session — and the proving tool writes the paste.** The decomp.me listing failed to assemble on the first try; the
  replica had proven the compile, not the paste (DK-81).
- **R99 — What a public tree carries is decided before the flip, and a retired document gets its Archive-index row and is deleted in
  the same commit — history keeps it.** Two folders left the tree within hours of going public; the paths-never-links rule made it
  harmless, the timing cost two commits on a public history.

## 4. Where things live (the doc map a session needs)
**The wiki is the source of truth for documentation (Phase 33.5):** `docs/wiki/Reference-index.md` lists every live reference and
generated file with how to read it — start there; `docs/wiki/Docs-and-scratch-conventions.md` says where each kind of knowledge goes;
`docs/wiki/The-ROM-firewall.md` is the no-ROM policy; `docs/wiki/Archive-index.md` records every document retired at Phase 33.5
(the archive folder itself left the tree at Phase 34, 2026-09-08 — the rows are the record; nothing ever linked into it). The files a session touches most: `docs/SETUP.md` (environment, every tool's
row, commands) · `docs/matching-cookbook.md` §1–§500 (idioms; 3.5 MB — grep by §, never read whole) + `docs/cookbook-index.md`
(symptom-keyed, derived, 566 KB — grep) · `docs/gcc-2.7.2-map/` (the compiler map) · `docs/wave-playbook.md` (THE wave procedure;
the OpenRouter-era `automation-runbook.md` is archived) · `docs/effort-map.md` · `docs/phase34-seed.md` (the next phase's seed;
`roadmap-to-100.md` v2 and `frontier-p32.md` are archived — their outcomes are in the PhaseEnds) · `docs/decision-log.md` (R31) ·
`docs/accelerators.md` · `docs/memory-map.md` (addresses, provenance) · `docs/formats.md` · `docs/disc-completeness.md` +
`docs/disc-ledger.md` · `docs/backlog.md` (near-miss ledger) · `docs/gen3-handoff.md` + `docs/gen3-standards.md` (Gen3) ·
`docs/tool-index.md` (every tool keyed by
the need it answers; generated) · **Phase 35:** `docs/wiki/The-dedup-engine.md` (the shared-source model), `tools/share_census.py` (the S1
census and gate), `tools/share_body.py` (the share tool), `config/dedup_exceptions.tsv` (the ledger), cookbook §453 · **`decomp-architect/`** (the day-one kit: three dictionaries, DK-1–81, G1–67; its wiki page
`docs/wiki/Start-a-new-decomp-project.md`; `make kit-corpus` regenerates, tools-health asserts) · `config/wave_exclude.txt` (pinned walls) · `config/verbatim_manifest.json` · `phase-ends/logs/` (on demand only, R19) · `.run/`
(scratch; allowlisted subtrees are tracked — e.g. `.run/P32/t3/` drafts/ledger; the rules are on the conventions page).
