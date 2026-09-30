### P33 B3 (S86, 2026-09-06) — `tools/bootstrap.sh` / `make bootstrap`: the fresh-clone setup
- **`tools/bootstrap.sh`** (idempotent, never sudo): apt packages of §4.5 checked with `dpkg -s` and the missing ones printed
  as ONE `sudo apt-get install` line (never run); `.venv` created from `requirements-python.txt` (pinned; a no-op when
  satisfied); `git submodule update --init`; `sha256sum --check tools/bin/CHECKSUMS.sha256` then each cc1 tarball extracted
  into its own `tools/bin/gcc-2.7.2-{psx,cdk}/` unless `cc1` already exists; finally `make check-env` (its exit status is
  the script's). `make bootstrap` is the alias. Idempotent run on a set-up tree: 1.4 s.
- `make check-env` additions: 4b) the other three submodules populated (WARN — matching tooling, not build inputs),
  4c) the four tracked splat preset headers present (FAIL), 8) `[INFO] extracted payloads present: N / 218 binaries`
  (the census of the fleet's inputs; the hint names `make disc-extract`).
- The **fresh-clone proof** (the "stranger with their own dump" criterion, gen2-roadmap Phase-14 milestone (b)): `git clone
  --no-local` → `tools/bootstrap.sh` → `ln -s <your disks> disks` → `make disc-extract && make extract-all && make
  check-all` → `check-all: 218 passed, 0 failed of 218`. Recorded in `phase-ends/CURRENT_PHASE.md` (B3) with timings.

