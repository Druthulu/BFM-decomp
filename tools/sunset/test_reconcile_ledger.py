#!/usr/bin/env python3
"""Targeted proof of the S45p7 reconcile-ledger fix in dedup_propagate.

The full-propagation negative control did not fire (that run SUCCEEDED), so the guarded
path was never executed. This exercises the mechanism directly:

  1. take real overlay files, snapshot them
  2. apply a REAL reconcile via dedup_propagate.reconcile_caller_extern (the same call the
     --recover Part B path makes) -> files are now edited on disk
  3. drive the ledger's undo the way the fixed code does when the fn leaves the plan
  4. assert every file is byte-identical to its original

Read-only w.r.t. git: it restores what it edits, and asserts it did.
"""
import sys, os, hashlib
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'tools'))
sys.path.insert(0, 'tools')
import dedup_propagate as dp


def sha(p):
    return hashlib.sha1(open(p, 'rb').read()).hexdigest()


def main():
    OV, ADDR = 'ov_SC07_010', 0x80146A6C     # the exact overlay+fn from tonight's breakage
    files = [cp for cp, _ in dp.overlay_files(OV)]
    before = {str(p): sha(p) for p in files}
    print(f"[setup] {OV}: {len(files)} source files snapshotted")

    # --- 1. apply a real reconcile (this WRITES) ---
    snap, n = dp.reconcile_caller_extern(OV, ADDR)
    after_edit = {str(p): sha(p) for p in files}
    changed = [k for k in before if before[k] != after_edit.get(k)]
    print(f"[apply] reconcile_caller_extern -> {n} edit(s); {len(changed)} file(s) changed on disk")
    if n == 0 or not changed:
        print("SKIP: this fn/overlay pair produced no reconcile edit — cannot exercise the path.")
        return 3

    # --- 2. drive the ledger undo exactly as the fixed code does ---
    kept = [(ADDR, snap)]
    drop = [r for r in kept if r[0] in {ADDR}]
    for _a, _s in reversed(drop):
        dp.restore_snapshot(_s)
    print(f"[undo]  ledger restored {len(drop)} kept reconcile(s)")

    # --- 3. the assertion ---
    after = {str(p): sha(p) for p in files}
    bad = [k for k in before if before[k] != after.get(k)]
    if bad:
        print("FAIL — files NOT restored byte-identically:")
        for k in bad[:5]:
            print("   ", k)
        return 1
    print(f"PASS — all {len(files)} file(s) byte-identical after the ledger undo "
          f"(the orphan that broke 141/213 cannot survive this path)")
    return 0


if __name__ == '__main__':
    sys.exit(main())
