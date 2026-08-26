#!/usr/bin/env python3
"""mk_write.py — the ONLY safe way to rewrite config/overlays.mk.

WHY THIS EXISTS (P31 S60 — it cost the campaign two registry wipes in one day).

config/overlays.mk is the generated registry that defines all 141 overlay binaries: EXE paths,
VRAM bases, ASM_DIR/SRC_DIR roots, symbol files, and every §8e JTBL_PADS spec. Four separate code
paths rewrote it with

    open(mk, "w").write(txt)

which truncates the file to ZERO first and only then writes. Three ways that loses the registry:

  * the process dies between truncate and write -> an EMPTY file;
  * another process reads it inside that window -> it sees an empty or partial registry;
  * two writers interleave -> a partial line lands after the last good one. The morning's wipe
    left exactly that fingerprint: a stray `uto.txt` fragment after the final entry.

The blast radius is total and silent. With no binaries registered, main's object glob (which
prunes siblings via `$(<bin>_ASM_DIR)`) sweeps every overlay's nonmatchings/*.s into MAIN's OBJS
and assembles them standalone; main cannot build, the main lane correctly refuses to gate against
a RED baseline, and EVERY overlay gate rejects EVERY draft because no overlay can build. Measured
twice: waves dn/do banked 0 of 224 and 0 of 236, and waves ei..em banked 2 of ~1,100 with 675
backlog rows reading "match_one MATCH but the whole-binary gate rejected" — the local oracle
proving the drafts were byte-correct while the tree could not build them.

WHAT THIS GUARANTEES
  1. ATOMIC. Write a sibling tmp file, fsync, then os.replace() — a rename on the same filesystem
     is atomic, so no reader ever observes a partial registry and a crash leaves the original
     untouched.
  2. REFUSES A COLLAPSE. A rewrite that would drop below `min_ratio` of the current line count is
     refused loudly (R43: refuse, never mishandle). A carve edits a line or two; it never removes
     20% of the file, so this cannot fire on legitimate work.
  3. SERIALIZED. An flock so two concurrent carves cannot interleave their writes.

WHAT IT DOES NOT FIX, stated honestly: callers still READ outside the lock, so two carves can each
read, edit, and write, and the second silently drops the first's line. That is a LOST UPDATE — a
missing line, not a wiped file — and it is caught downstream by the fleet check and jtbl_pads_fix.
Closing it properly means holding the lock across read-modify-write in every caller.
"""
import fcntl
import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MK = os.path.join(REPO, "config", "overlays.mk")
LOCK = os.path.join(REPO, ".run", "auto", "overlays_mk.lock")
FLOOR = 100          # a healthy registry is ~5,000 lines; below this it is already broken


def write_overlays_mk(txt, path=MK, min_ratio=0.8):
    # R43 (S61): refuse a text that would kill make at PARSE time — one mangled target-variable
    # line ("...o: JTBL_PADS : JTBL_PADS := ...") fails EVERY build of EVERY binary with
    # "target pattern contains no '%'", which is strictly worse than any wipe this guard's line-count
    # floor was built for. A second colon before the ':=' on an armed-object line is never legal.
    for _ln in txt.splitlines():
        if _ln.startswith("build/") and _ln.count(":") >= 2 and ":=" in _ln:
            _head = _ln.split(":=", 1)[0]
            if _head.count(":") >= 2:
                raise SystemExit("mk_write: REFUSING a parse-poisoned registry line: %r" % _ln[:120])
    """Replace overlays.mk atomically, refusing any rewrite that collapses it.

    Returns the number of lines written. Raises RuntimeError on a refused collapse — callers
    should let that propagate: a carve that cannot safely record its spec must fail loudly, not
    continue with an unrecorded one.
    """
    new_lines = txt.count("\n")
    try:
        with open(path, errors="replace") as fh:
            old_lines = sum(1 for _ in fh)
    except OSError:
        old_lines = 0

    os.makedirs(os.path.dirname(LOCK), exist_ok=True)
    with open(LOCK, "w") as lk:
        fcntl.flock(lk, fcntl.LOCK_EX)
        # AN ALREADY-EMPTY REGISTRY IS NOT A LICENCE TO WRITE (P31 S60, learned the hard way: my
        # own verification control clobbered a registry that a carve had truncated seconds
        # earlier, because the collapse check was skipped when old_lines was 0). A healthy file is
        # ~5,000 lines; anything under FLOOR means the registry is ALREADY broken and the right
        # move is to refuse and let a human restore it from git, not to layer another write on top.
        if old_lines < FLOOR:
            raise RuntimeError(
                f"mk_write: {path} currently has {old_lines} lines — the registry is already "
                f"broken (healthy is ~5,000). REFUSING to write over it; restore it with "
                f"`git checkout HEAD -- config/overlays.mk` first. Nothing was written.")
        if old_lines and new_lines < old_lines * min_ratio:
            raise RuntimeError(
                f"mk_write: REFUSING to write {path} with {new_lines} lines — it currently has "
                f"{old_lines}. A carve edits a line or two; this would drop "
                f"{100 * (1 - new_lines / max(old_lines, 1)):.0f}% of the registry. "
                f"Nothing was written.")
        tmp = path + ".tmp"
        with open(tmp, "w") as fh:
            fh.write(txt)
            fh.flush()
            os.fsync(fh.fileno())
        os.replace(tmp, path)
    return new_lines
