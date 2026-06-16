# CURRENT_PHASE — Phase 13: Representative location overlays (end-to-end + fleet runbook)

> Gen2 phase 6 (8→9→10→11→12→**13**→14→15). Effort: **Max** (template/first overlay). Plan approved by Drew 2026-06-16 (gate 1). Full plan: `~/.claude/plans/plan-mode-enabled-max-hazy-hamming.md`.
> **Crash-recovery task log (P3/P5).** Update after every task. The PhaseEnd absorbs+archives this at close (R19).

## Owner decisions (this session)
- **Scope = "Representative + credit"** — match SC01/077 end-to-end, collapse dup pair SC01/005≡006, add free-roam SC03/001, ship the fleet runbook. Bank the shared bodies SC01/077 *exercises*; full 134-sweep is Phase 15.
- **Import the representative overlays into Ghidra** (decompiler assist for unique fns); Ghidra-free for the eventual fleet.

## Invariants (never regress)
- main `143dbb89f34491258bbc27810d0a12ec8b43a8dd` + resident `8e17e02ff8954d07c979449198f7e1645046b353` stay BYTE-IDENTICAL through every task.
- Byte-checks from a CLEAN rebuild (R22). Default build links no non-matching C (G4). MCP verified before any RE (G2). Stop+verify Ghidra before any DB commit (R23).

## Representative overlays (byte facts, verified R14)
| Alias | `0.4.dec` path (extracted/retail/) | Size | SHA1 |
|---|---|---|---|
| ov_SC01_077 | SC01.CD.dir/FILE_077.dir | 731,607 | d19c9580a02dc63ba1f0e7e0c770f3b10de35635 |
| ov_SC01_005 | SC01.CD.dir/FILE_005.dir | 679,689 | 56760dbec7757f12d18d7e40242a0b05280ff444 |
| ov_SC01_006 | SC01.CD.dir/FILE_006.dir | 679,689 | 56760dbec7757f12d18d7e40242a0b05280ff444 |
| ov_SC03_001 | SC03.CD.dir/FILE_001.dir | 815,887 | f8fd92f59c6871577c61cb626cb9ddb0db5ba884 |

All load @ vram 0x80128158. SC01/077 starts with CODE at offset 0x0 (no leading data word).

## Tasks
- [x] **T0** — Overlay splat template (`config/splat.us.overlay.template.yaml`) + Makefile `-include config/overlays.mk` indirection. ✅ GATE: clean rebuild main `143dbb89…` + resident `8e17e02f…` BYTE-IDENTICAL (indirection proven a no-op; `overlays.mk` absent → silent `-include` → `BINARIES` unchanged).
- [~] **T1** — SC01/077 end-to-end. ✅ T1a scaffold (overlays.mk + splat.ov_SC01_077.yaml + check.sha + symbols + 4 Python dicts w/ sentinel) · ✅ T1b all-asm byte-match `d19c9580…` BYTE-IDENTICAL (milestone; main+resident unregressed) · ☐ T1c seed boundaries + Ghidra import · ☐ T1d dedup-credit · ☐ T1e unique-remainder harvest (Ultracode §12 — prompt R26).
  - **Reusable finding (→ cookbook §13 + PhaseEnd):** non-word-aligned overlays (≈75% of fleet) need 3 template/Makefile additions: (1) a `[<word_floor>, bin, trailing]` carve for the final 1-3 bytes spimdisasm's data path drops; (2) a `build/assets/%.o` incbin rule (+ `--set-section-alignment .data=1`) wiring splat `bin` assets (scoped `asset_path: assets/<alias>`); (3) an objcopy end-align **trim** (shrink-only, ≤3 B) removing the splat `.ld`'s `. = ALIGN(., 4)` segment-end pad. EXE/resident are 4-aligned so untouched.
- [ ] **T2** — Dup-pair collapse SC01/005≡006 (both `56760dbe…` from one shared source).
- [ ] **T3** — Free-roam SC03/001 (`f8fd92f5…`); recipe scales to a large overlay.
- [ ] **T4** — `tools/new_overlay.sh` one-command onboarding (gen `overlays.mk`; sentinel-insert 4 dicts; idempotent). GATE: onboard a fresh overlay in one command.
- [ ] **T5** — `make build-all`/`check-all` (recursive `$(MAKE) BINARY=<b>`, aggregate PASS/FAIL).
- [ ] **T6** — Docs (cookbook §13 runbook, SETUP R21, gen2-roadmap status, per-ov digests) + PhaseEnd (Tier-1).

## Current task
→ **T1** (in progress). T0 done (template + indirection no-op proven). Next: T1a scaffold `ov_SC01_077` (instantiate the template; `overlays.mk` block; 4 Python dicts; check.sha=`d19c9580…`; empty symbols), then T1b iterate the code/data split to byte-identical.

Harness task list built (T0–T6; T0 completed, T1 in_progress) for Drew's monitoring — new standing preference saved to memory (`build-tasklist-after-plan-approval`).

## Blockers
(none)
