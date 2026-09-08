#!/usr/bin/env python3
"""shared_lock.py — one reader/writer lock over the FLEET-SHARED source state.

Stage 1 of docs/concurrency-design.md.

WHAT IT PROTECTS
    src/shared/** (the shared bodies — engine_core.h until Phase 35 T4, the per-function headers after — and
    engine_types.h), config/overlays.mk,
    config/dedup.us.yaml, and the per-overlay .c files that propagation rewrites.
    These are the only files whose writers span binaries; every per-binary resource
    (build/<bin>/**, src/<bin>/*.c, asm/<bin>/**) is already isolated and is guarded by
    gate_stage's existing per-binary flock.

WHY
    A gate that merely READS the shared header can safely run beside other such gates —
    that is the parallel lane bulk_harvest wants. But a writer (dedup_propagate,
    fix_arity_callers --apply) racing a reader can let a gate compute a verdict against a
    TRANSIENT tree state that never exists again ("verdict decay", design §2.2b). That
    cannot false-bank — the gate compares against config/check.<bin>.sha, which no stage
    writes, and INCLUDE_ASM pastes the original bytes — but it mints banks whose C is not
    byte-correct against the state actually committed, and the R22 then fails on a batch
    that "all gated green".

MODES
    shared()     readers  — parallel gates that do not write shared state
    exclusive()  writers  — dedup_propagate, fix_arity_callers --apply, serial-lane gates

NESTING
    gate_stage SPAWNS both writers as subprocesses. A child re-acquiring exclusively while
    the parent holds the lock would deadlock, so the parent exports BFM_SHARED_LOCK_HELD=1
    and children treat the lock as already held. The parent is responsible for taking the
    correct mode for what it is about to do (EX if it will propagate or run the arity
    pre-pass, SH otherwise) — see gate_stage.run_gate.
"""
import contextlib
import fcntl
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOCK = os.path.join(REPO, ".run/auto/shared_state.lock")
ENV = "BFM_SHARED_LOCK_HELD"


@contextlib.contextmanager
def hold(exclusive, nonblocking=False, announce=None):
    """Hold the shared-state lock. No-op if an ancestor already holds it (see NESTING)."""
    if os.environ.get(ENV):
        yield "inherited"
        return
    os.makedirs(os.path.dirname(LOCK), exist_ok=True)
    fh = open(LOCK, "w")
    mode = fcntl.LOCK_EX if exclusive else fcntl.LOCK_SH
    if nonblocking:
        mode |= fcntl.LOCK_NB
    try:
        fcntl.flock(fh, mode)
    except OSError:
        fh.close()
        raise SystemExit(
            f"[shared-lock] REFUSED: another process holds {os.path.relpath(LOCK, REPO)}"
            + (f" ({announce})" if announce else "")
            + ".\n  A fleet-shared writer may not run while gates are reading shared state"
            " (docs/concurrency-design.md §2.2b). Wait for it, or re-run without --nb.")
    prev = os.environ.get(ENV)
    os.environ[ENV] = "1"
    try:
        yield "exclusive" if exclusive else "shared"
    finally:
        if prev is None:
            os.environ.pop(ENV, None)
        else:
            os.environ[ENV] = prev
        fcntl.flock(fh, fcntl.LOCK_UN)
        fh.close()


def held_by_ancestor():
    return bool(os.environ.get(ENV))


if __name__ == "__main__":
    # Test helper: hold the lock for N seconds so a negative control can observe a refusal.
    #   python3 tools/shared_lock.py shared 30
    import time
    mode = (sys.argv[1] if len(sys.argv) > 1 else "shared").lower()
    secs = float(sys.argv[2]) if len(sys.argv) > 2 else 5.0
    os.environ.pop(ENV, None)
    with hold(exclusive=(mode == "exclusive")) as m:
        print(f"[shared-lock] holding {m} for {secs}s (pid {os.getpid()})", flush=True)
        time.sleep(secs)
    print("[shared-lock] released", flush=True)
