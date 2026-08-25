# main lane fix — why 737 drafts banked zero (P31 S59)

**Status: DIAGNOSED, FIXED, BYTE-PROVEN.** The proof section carries the measurement commands and
SHA lines. Companion docs: `main-gate-defects.md`, `docs/automation-runbook.md`, cookbook §236
(integration-failure taxonomy), R40/R42/R43.

## 0. The verdict, in one paragraph

The main lane's drafts were fine and its gate was fine; **the committed baseline was RED**. From
14:57:01 to 18:43:23 on 2026-08-24, HEAD's `src/800.c` carried at least one byte-wrong body
(adopted by auto-commit `commit:2693`), so `make build BINARY=main` produced
`307aa45dc2aff265043a60c9ad2f6b30777852b1` against the expected
`143dbb89f34491258bbc27810d0a12ec8b43a8dd` **with no draft substituted at all**. Every batch
gated in that window was doomed before its first draft was judged: four 200-card draft rounds
(m00–m03 card cycles, ~737 drafts produced, 160 slated after the reloc filter) banked **zero**,
~50 clean EXE rebuilds were burned bisecting innocent slates, and every rejection in the lane's
log was a false verdict. This is R40's exact scenario — the instrument (the tree), not the
subject (the drafts), was broken — and R43's: nothing refused loudly.

## 1. The measurement that establishes it (do this first, always)

Holding `.run/auto/gate.main.lock`, with `pgrep -f 'tools/gate_mai[n]\.py'` empty and top-level
`src/*.c` clean:

    rm -f build/us/SLUS_007.26 && make extract BINARY=main && make build BINARY=main

* At `commit:2711` (HEAD during the failures): rc=2, binary produced,
  `307aa45d…` — **RED**. The build log also always carries
  `src/800.c:479: warning: previous implicit declaration of 'func_800143AC'`
  (line 479 calls it before its decl at 559 — harmless, but load-bearing below).
* With `src/800.c`+`src/800c.c` restored from `commit:2692` (the last lane-verified-green main
  commit, m00baaa 14:56:47): rc=0, `143dbb89…` **BYTE-IDENTICAL** — so those two files carried
  the entire breakage.
* With the files from `commit:2693` (14:57:01): RED at **exactly HEAD's wrong SHA** — `commit:2693`
  is the breaking commit, and the two later adopters (`commit:2694`, `commit:2706`) are byte-neutral
  (their adopted bodies were correct; only never verified).

## 2. Root cause: adoption-during-gate (a TOCTOU race, not a bad tool)

`commit:2693` is ox_campaign's gate-entry auto-commit ("commit in-tree banked work before the next
gate"). Its main-source carve-out (from `commit:2638`, same morning) DID run — it reverted the dirty
main TUs — but a `gate_main` bisect chunk was live at that moment (the commit landed 14 s after
m00baaa banked, exactly one chunk cadence), and gate_main's `substitute()` re-wrote `src/800.c`
between the carve-out's `git checkout` and the site's `git add -A src/`. The add swept the
mid-flight, unverified substitution into the commit; the chunk then FAILED its byte-gate and
gate_main "reverted" — to the newly poisoned HEAD. Two unverified bodies (`func_8002992C`,
`func_80038698`, at least one byte-wrong) became the permanent baseline.

Three separate adopters could do this (all blanket-add `src/`): ox_campaign's gate-entry commit,
its pre-main-batch overlay commit ("Committed before the main batch…", which adopted five more
bodies at 16:50 `commit:2706` and — luckily — the *investigation's own green checkout* at 18:43
`commit:2712`, which is what restored the baseline), and `maintenance.sh`. `gate_stage`
(`git add -u src/`), `gate_lane`, and `idiom_serial` had the same latent hazard.

## 3. The amplifier: why the gate LIED about why batches failed

`make build BINARY=main` runs the SHA check itself, so on a byte MISMATCH it exits nonzero with
the binary present. `gate_main.clean_build` treated any nonzero rc as "no binary" → every
mismatch entered the compile-failure analysis → its conflict regex (which accepted `warning:`
forms) matched the baseline's ever-present `func_800143AC` implicit-decl warning → every m04
chunk died with `COMPILE conflict on func_800143AC … drafts declaring it: []` — a symbol no
draft mentioned. m03's batches (whose rebuilds didn't recompile 800.c, so no warning in the log)
fell through to bisection instead and burned the full `MAX_STEPS=24` rejecting innocents one by
one: `BANKED 0 of 36 … STILL MISMATCHED`.

## 4. What changed (all landed this session)

**`tools/gate_main.py`**
* `clean_build`: binary-present + rc≠0 now returns the real hash (an honest mismatch), never
  "BUILD FAILED (no binary produced)".
* **Baseline-red control (the R40 guard):** on any batch failure, one `try_batch([])` control
  rebuild runs first. If HEAD itself is red, the gate prints `*** BASELINE RED — HEAD builds to
  X, want Y, with NO draft substituted`, leaves the slate untouched, and exits 3. No bisect, no
  false rejects, ~one rebuild of cost only on the failure path.
* Conflict shortcut: fires only on a TRUE compile failure, only on error-shaped lines (never
  `warning:`), and only when a draft in the slate actually names the symbol; otherwise it says
  so and falls through to the honest error report + bisect.
* `--assert-baseline` mode: no slate; clean-builds the committed tree with nothing substituted;
  exit 0 green / 3 red. Runs under the same gate lock.
* Every revert narrowed from `git checkout -- src/` to **top-level `src/*.c` only** (`main_tus()`)
  — a main gate can no longer destroy overlay lanes' in-flight work (the S58 61-bank incident
  class is closed structurally, not by commit-ordering discipline).

**`tools/main_lane.py`**
* Every cycle begins with `gate_main --assert-baseline` — the lane refuses to spend tokens or
  rebuilds against a red baseline (R43), raising `BaselineRed`: parks nothing, bumps no tries,
  writes `.run/main_lane.BASELINE_RED`, logs the fix-path, and re-checks every 30 min. The
  sentinel clears itself when the baseline is green again.
* `BASELINE RED` in gate output mid-cycle raises the same way (belt and braces: the pre-cycle
  assert can go stale mid-cycle).

**The adopters** (`ox_campaign.py` ×3 incl. `unstage_main_tus()`, `maintenance.sh`,
`gate_stage.py`, `gate_lane.py`, `idiom_serial.py` ×2)
* **main's TUs (top-level `src/*.c`) are never staged by any overlay/maintenance lane, and never
  reverted by one either.** One writer (`gate_main`), one committer (`main_lane`, after the
  whole-EXE SHA re-checks green). The old carve-out's revert is gone — it was the losing half of
  the TOCTOU — replaced by unstaging after the blanket add, which is race-free: a re-write after
  the reset simply stays unstaged.

**Recovery**
* `.run/main_queue/s59_recovery.json`: the 56 unique falsely-rejected drafts from the m00–m04
  slates (tries reset — their strikes were false verdicts) plus the 7 byte-correct bodies
  (`func_8001D70C`, `func_800291A0/B4/C8/DC`, `func_8003A0D0`, `SYS_OBJ_E34`) that `commit:2712`'s
  sweep re-stubbed, re-extracted from `commit:2694`/`commit:2706` into
  `.run/s59_mainfix/recovered/`.

## 5. Proof

* Baseline at current HEAD (`commit:2712`), measured under the lock, no gate alive, clean sources:
  rc=0, `143dbb89f34491258bbc27810d0a12ec8b43a8dd  build/us/SLUS_007.26` — **BYTE-IDENTICAL**.
* Proof run: one `main_lane.py --once` cycle through the fixed machinery over the recovery queue
  (result appended below).

## 6. The laws this re-proves

* **R40**: the first question about a 0% yield is never "why are the drafts bad" — it is "is the
  instrument green". A null result against 737 drafts IS the instrument's confession.
* **Silently narrowed tool scope / R32**: `_stub_removals` counted honestly; what nothing
  asserted was the denominator's denominator — the tree those diffs were taken against.
* **New (S59): a shared mutable file needs ONE writer and ONE committer.** Any "commit whatever
  is dirty" pass over a file another process substitutes into WILL eventually commit an
  unverified intermediate state, no matter what pre-check it runs — the check and the add are
  two reads of a file someone else is writing. Exclude by construction, not by inspection.
