#!/usr/bin/env python3
"""work_evidence.py — assertions that a tool ACTUALLY DID the work it reports (P31 S70).

WHY THIS EXISTS
---------------
`make tools-health` audits DATA integrity (corpus, cdecl, binaries, digest, text). Nothing audited
TOOL BEHAVIOUR — and in one session four tools reported success while doing nothing or doing harm:

  * `parallel_gate` ran `gate_stage` with `cwd=<worktree>` and a RELATIVE `--drafts` path, so the
    directory did not exist there: 0 drafts found, banked 0, **rc=0**, 1-2s per binary. The same
    drafts gated in-tree banked 15/16. (§402)
  * `harvest_verify` reported `verified 1 / VERIFIED: func_8002B0B4`, SHA byte-identical, and left
    the `INCLUDE_ASM` stub in place — it verifies, it does not bank. A bank was REPORTED that never
    existed. (§404)
  * both undo-journals printed full success and left the file corrupted. (§403)
  * `gater_lane` ledgered drafts as gated that the gate never examined.

THE COMMON SIGNATURE, and the reason a code review would not have found them: **a wrong instrument
returns a plausible NUMBER, not an error.** Every one of these was caught by behaviour — an impossible
runtime, a diff after a claimed-success undo, an arithmetic reconciliation that refused to close.

So the assertions here are about OBSERVABLE CONSEQUENCE, not about internal state:

  assert_inputs  a job with zero readable inputs is a DEFECT, not a zero-yield result (R32/R43).
                 "0 of 0 failed" and "0 of 57 failed" are indistinguishable downstream, and the
                 second is a fact about the drafts while the first is a fact about the harness.
  assert_floor   work that claims to have compiled/gated cannot finish faster than a compile. The
                 ONLY tell on the pgate defect was a 1-2s wall clock; every other signal said success.
  assert_effect  a tool claiming N successes must show a PERSISTENT effect. Verification is not
                 banking; a green report with an unchanged tree is the §404 class.

USAGE — call these where the tool already knows the facts, e.g.

    import work_evidence as we
    we.assert_inputs("gate_stage", n_drafts, drafts_dir,
                     hint="a 0-draft gate would report 'banked 0' as if the drafts had failed")
    we.assert_floor("pgate/%s" % binary, elapsed, floor=10.0, claimed="a full binary build+check")
    we.assert_effect("bank", claimed=len(verified), before=stubs_before, after=stubs_after)

Each raises `WorkEvidenceError`. Callers that must not abort can pass `strict=False` to get a loud
stderr warning and a False return instead — but note R54: a guard that is not running is not a guard,
and a warning nobody reads is the same as silence. Prefer the raise.

Self-test (R39 negative control — every assertion must PASS the good case AND FAIL the bad one):
    python3 tools/work_evidence.py --selftest
"""
import os
import sys

FLOOR_BUILD = 10.0   # seconds. Nothing that compiles + links + sha1s a PS1 binary finishes faster.


class WorkEvidenceError(RuntimeError):
    pass


def _fail(msg, strict):
    if strict:
        raise WorkEvidenceError(msg)
    print("[work-evidence] WARNING: %s" % msg, file=sys.stderr)
    return False


def assert_inputs(what, n_inputs, where, hint="", strict=True):
    """A job that found ZERO inputs did not do the work — it never started it.

    The distinction that matters downstream: "processed 0 of 0" is a statement about the HARNESS,
    "processed 0 of 57" is a statement about the SUBJECT. Reporting the first as the second is how a
    35-binary batch read as 57 failed drafts (§402)."""
    if n_inputs and n_inputs > 0:
        return True
    return _fail("%s: ZERO readable inputs at %r — refusing to report a zero-yield RESULT for what is "
                 "an empty INPUT.%s" % (what, where, (" " + hint) if hint else ""), strict)


def assert_floor(what, elapsed, floor=FLOOR_BUILD, claimed="", strict=True):
    """Work that claims a compile/gate cannot beat physics.

    This is the assertion that would have caught §402 on its own: 35 binaries each 'gated' in 1-2s
    while a real gate takes 60-120s. Everything else about that run looked like success."""
    if elapsed is None:
        return True
    if elapsed >= floor:
        return True
    return _fail("%s: finished in %.1fs, below the %.1fs floor for %s — that is faster than the work "
                 "it claims to have done, so it did not do it." % (what, elapsed, floor,
                                                                   claimed or "this operation"), strict)


def assert_effect(what, claimed, before=None, after=None, effect=None, hint="", strict=True):
    """A claim of N successes must have a PERSISTENT consequence.

    Pass either a before/after measurement (e.g. the stub set) or an explicit `effect` boolean. When
    `claimed` is 0 there is nothing to prove and this is a no-op. §404: `verified 1` with the stub
    still present is exactly the shape this refuses."""
    if not claimed:
        return True
    if effect is None and before is not None and after is not None:
        try:
            effect = len(before) != len(after)
        except TypeError:
            effect = before != after
    if effect:
        return True
    return _fail("%s: claims %d success(es) but the tree shows NO persistent effect — a verification "
                 "is not a bank.%s" % (what, claimed, (" " + hint) if hint else ""), strict)


def selftest():
    """R39: each assertion must PASS the already-succeeded case and FAIL the known-bad one."""
    ok = True

    def expect(name, fn, should_raise):
        nonlocal ok
        try:
            fn()
            raised = False
        except WorkEvidenceError:
            raised = True
        good = raised == should_raise
        ok &= good
        print("  [%s] %-42s %s" % ("PASS" if good else "FAIL", name,
                                   "raised" if raised else "no raise"))

    expect("inputs: 57 drafts -> accept",
           lambda: assert_inputs("t", 57, "/d"), False)
    expect("inputs: 0 drafts -> REFUSE",
           lambda: assert_inputs("t", 0, "/d"), True)
    expect("inputs: None -> REFUSE",
           lambda: assert_inputs("t", None, "/d"), True)

    expect("floor: 102s build -> accept",
           lambda: assert_floor("t", 102.0), False)
    expect("floor: 1.4s 'build' -> REFUSE (the §402 tell)",
           lambda: assert_floor("t", 1.4), True)
    expect("floor: elapsed unknown -> accept",
           lambda: assert_floor("t", None), False)

    expect("effect: claimed 0 -> accept (nothing to prove)",
           lambda: assert_effect("t", 0, before={1, 2}, after={1, 2}), False)
    expect("effect: claimed 1, stub set SHRANK -> accept",
           lambda: assert_effect("t", 1, before={1, 2}, after={2}), False)
    expect("effect: claimed 1, tree UNCHANGED -> REFUSE (the §404 tell)",
           lambda: assert_effect("t", 1, before={1, 2}, after={1, 2}), True)
    expect("effect: explicit effect=True -> accept",
           lambda: assert_effect("t", 3, effect=True), False)

    # non-strict must WARN and return False, never raise
    quiet = assert_inputs("t", 0, "/d", strict=False)
    ok &= (quiet is False)
    print("  [%s] non-strict returns False instead of raising" % ("PASS" if quiet is False else "FAIL"))

    print("work_evidence selftest: %s" % ("OK" if ok else "FAILED"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(selftest() if "--selftest" in sys.argv else selftest())
