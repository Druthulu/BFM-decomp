#!/usr/bin/env python3
"""o0_detect.py — the -O0 prologue tell, in ONE place.  (P31 S67)

Extracted verbatim from match_one.py so other tools can ask the same question without importing
match_one (which parses argv at import time and therefore cannot be imported at all).  A SECOND
hand-written copy of this predicate would be a second oracle that can silently disagree with the
one the drafting path steers by — exactly what R33 forbids.  match_one re-exports it, so its
behaviour is unchanged and there is still only one definition.
"""
import re


def detect_o0(spath):
    """Is the TARGET compiled -O0? Read it off its own prologue (cookbook §6/§18, byte-proven).

    gcc-2.7.2 keeps a frame pointer at -O0 and omits it at -O2, so an -O0 function opens with
    `sw $fp, N($sp)` + `addu $fp, $sp, $zero` (word 21F0A003) inside its first few instructions.
    Requiring BOTH, and requiring them in the PROLOGUE, is what separates the tell from -O2 code
    that merely uses $fp/$s8 as an ordinary allocatable callee-saved register — the distinction that
    makes "$fp occurs in 311 files under asm/" the WRONG population (the real one is 167 files).

    WHY AUTO. Nothing in the drafting path ever passed --o0: api_draft.match_one() (the oracle every
    wave agent iterates against) builds a fixed argv without it. An agent handed an -O0 target was
    therefore shown an -O2 compile of its own C and a mismatch on every instruction — feedback that
    cannot converge, for a reason invisible in the diff. Detecting it from the bytes costs one file
    read and needs no card field, no lane, and no agent instruction (R33: derive it, do not ask).
    """
    try:
        head, started = [], False
        for ln in open(spath):
            # START AT THE FUNCTION, NOT AT THE FILE. A migrated jump table or an .asciz blob is
            # emitted into the same .s ahead of the code (`.section .rodata` first), so a naive
            # "first 8 encoded lines" reads TABLE WORDS as the prologue and calls an -O0 function
            # -O2 (measured on md_MAIN_011/func_800CF28C and func_800D04F4).
            if re.match(r'\s*(glabel|dlabel|\w+:)\s', ln) and 'glabel' in ln:
                started = True
                continue
            if not started:
                continue
            m = re.match(r'\s*/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} ([0-9A-Fa-f]{8}) \*/\s*(\S.*)?', ln)
            if m:
                head.append((m.group(1).upper(), (m.group(2) or '').strip()))
            if len(head) >= 8:
                break
    except OSError:
        return False
    setup = any(w == '21F0A003' or re.match(r'addu\s+\$fp,\s*\$sp,\s*\$zero', t) for w, t in head)
    save = any(re.match(r'sw\s+\$fp,', t) for _w, t in head)
    return setup and save
