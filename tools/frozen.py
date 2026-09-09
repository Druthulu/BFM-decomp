#!/usr/bin/env python3
"""frozen.py — the ONE refusal every FROZEN tool prints from its main() (Phase 35 T6, 2026-09-08).

A frozen tool is a matching-era tool that reads or writes the `DEFINE_func_` macro form Phase 35 retired (the shared bodies are
plain-C headers under src/shared/ now, one source per unique function — the S1 invariant). Its code stays in tools/ for the record
and for the libraries other tools import from it; only its command line refuses, so an import never exits (cdecl imports
gen_harvest_targets; eighteen tools import family_remap). The dictionary row carries status FROZEN and the successor.

    import frozen; frozen.refuse("family_sweep.py", "tools/share_body.py", "it rewrites the macro form Phase 35 retired")
"""
import sys


def refuse(tool, successor, why):
    sys.exit(f"{tool}: FROZEN since Phase 35 (2026-09-08) — {why}. Successor: {successor}. The code is kept for the record and its "
             f"library functions still import; the command line does nothing (R43). See docs/SETUP.md and config/tool_dictionary.tsv.")
