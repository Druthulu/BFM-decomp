### P33 A3 (S86, 2026-09-06) — the with/without-SDK dual as a first-class target
- **`NO_SDK=1`** (Makefile knob): `make check BINARY=main NO_SDK=1` skips every `psyq_integrate` rewrite AND the `-T`
  externals fragments, so main links the pristine splat script against its INCLUDE_ASM stub tiles — exactly the link a
  public clone without Sony's objects performs (contract §1.2, the fresh-clone fallback invariant). Until now that leg
  was exercised only by hand (`mv .run/obj40 .run/obj40.off`) and it regressed once unnoticed (`config/symbols.us.txt:248`,
  the `CdReadyCallback` name).
- **`make -j$(nproc) sdk-dual`**: leg 1 extract + check WITH the objects (map must list `build/psyq/libcd/`) → leg 2 extract
  + `rm -rf build/psyq` + check `NO_SDK=1` (map must list `build/src/libcd1.o` and no `build/psyq/`) → leg 3 extract + check
  (the tree back in its default WITH state); both legs against `config/check.us.sha`; maps kept in `.run/P33/verify/`.
  The extracts between legs exist because `psyq_integrate` rewrites `build/us/SLUS_007.26.ld` in place (the incremental
  trap `tools/gate_main.py` documents). REFUSES to run when any of the 11 SDK object dirs is absent (one leg twice is not a
  dual, R32); `tools-health` calls it after `sig-main`, or prints `[skip] sdk-dual: no SDK objects on this machine` — there
  the default build already IS the without leg.

