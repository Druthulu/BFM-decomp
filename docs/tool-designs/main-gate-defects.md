# main gate — two defects found by the P31 S58 probe (2026-08-24)

Probe: 8 main drafts from `.run/main_queue/an.json` through `tools/gate_main.py --apply`.
Outcome: **killed after 38 minutes without a verdict.** Neither defect is about the drafts.

## 1. The compile-error shortcut missed the error gcc actually printed  — FIXED

`gate_main` documents "A COMPILE error names its own culprit -- read it instead of bisecting.
Bisection here costs a FULL CLEAN REBUILD per step (~2-4 min), so it is worst-case hours."
Its matcher recognised only `previous declaration of`. gcc printed:

    src/800.c:3018: warning: type mismatch with previous implicit declaration
    src/800.c:2910: warning: previous implicit declaration of `func_80017930'

so the batch fell through to bisection to rediscover a symbol already named in the first build.
Fixed: the matcher now also accepts `previous implicit declaration of` and `conflicting types for`.

An IMPLICIT declaration comes from a CALL SITE with no prototype, which is also why
`resolve_conflicts` reported `8 -> 8 compatible, 0 dropped` — it compares draft-vs-draft and
draft-vs-explicit-decl, and is structurally blind to this class. That pre-check gap is NOT fixed.

## 2. The typedef-hoist repair is NOT IDEMPOTENT — NOT FIXED

Every bisect round emitted:

    hoisted 2 typedef(s) to the top of src/800.c: Poly12Obj, Poly12Pt

**150 times**, and the working-tree diff at kill time was a DUPLICATED marker comment:

    /* hoisted by gate_main so drafts above can reuse them (§181) */
    +/* hoisted by gate_main so drafts above can reuse them (§181) */

The repair does not detect that it has already run, so it re-hoists, rebuilds, fails identically,
and repeats — it cannot converge. This is why the probe never produced a verdict.

**Before main is gated again:** make the hoist idempotent (detect the marker / the existing typedef)
and bound the bisect by iteration count so a non-converging repair fails loudly instead of spinning.
