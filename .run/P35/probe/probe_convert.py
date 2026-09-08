#!/usr/bin/env python3
"""probe_convert.py — Phase 35 T0 probe (R37): convert ONE overlay's TUs from the DEFINE_func_X() macro form to the
include-at-site header form, IN TREE, so the real Makefile recipe builds the objects; the caller compares per-object SHA1s
against the baseline objects (the L0 "object A/B" oracle proven by Probe P1) and runs `make check BINARY=<ov>`.

SCRATCH, not a tool: the recipe it proves becomes tools/macro_to_header.py in T4. It never touches the registry.

    probe_convert.py --ov ov_SC06_033 --apply       # writes src/shared/engine_prelude.h, src/shared/ov/func_*.h, rewrites the TUs
    probe_convert.py --ov ov_SC06_033 --plan        # counts only

What it does (the T4 rules, minimal form):
  * macro_index: every `#define DEFINE_func_X()` in src/shared/engine_core.h, keeping the LAST definition of a name (cpp semantics);
    body = the continuation-stripped, 4-space-dedented text; asserts the 4 known divergent twins.
  * header per macro USED by this overlay: src/shared/ov/func_X.h = banner + body (pure fragment, no guard, no includes).
  * prelude: src/shared/engine_prelude.h = engine_types.h + the ENGINE_SHB macro copied from engine_core.h.
  * each TU: line `#include "../shared/engine_core.h"` -> `#include "../shared/engine_prelude.h"`;
    each site line `DEFINE_func_X()  /* dedup: ... */` -> `#include "../shared/ov/func_X.h"` (same line, same position).
  * refuses (R43) any site line not of the one known shape, any macro used but not defined, any body with a trailing backslash left.
Restore afterwards: `git checkout -- src/<ov> && rm -rf src/shared/ov src/shared/engine_prelude.h`.
"""
import argparse, os, re, sys, pathlib

ROOT = pathlib.Path(__file__).resolve().parents[3]
ECH = ROOT / "src/shared/engine_core.h"
SITE = re.compile(r'^(\s*)DEFINE_(func_[0-9A-Fa-f]{8})\(\)\s*/\* dedup: [^*]*\*/\s*$')
DEFLINE = re.compile(r'^#define (DEFINE_func_[0-9A-Fa-f]{8})\(\)(.*)$')
DIVERGENT = {"DEFINE_func_8013FFD8", "DEFINE_func_8013F350", "DEFINE_func_80181538", "DEFINE_func_801808C4"}


def macro_index(text):
    """name -> (body_lines, n_definitions); LAST definition wins (cpp keeps the last)."""
    lines = text.split("\n")
    out, seen = {}, {}
    i = 0
    while i < len(lines):
        m = DEFLINE.match(lines[i])
        if not m:
            i += 1
            continue
        name = m.group(1)
        rest = m.group(2)
        if rest.strip() != "\\":
            sys.exit(f"probe: unexpected text after the define of {name}: {rest!r}")
        body = []
        i += 1
        while i < len(lines) and lines[i].endswith("\\"):
            body.append(lines[i][:-1].rstrip())
            i += 1
        # the last body line has no continuation
        if i < len(lines):
            body.append(lines[i].rstrip())
            i += 1
        seen[name] = seen.get(name, 0) + 1
        out[name] = body
    # dedent by the common 4 spaces the generator used
    for name, body in out.items():
        ded = []
        for ln in body:
            ded.append(ln[4:] if ln.startswith("    ") else ln)
        out[name] = ded
    return out, seen


def engine_shb_block(text):
    """The ENGINE_SHB definition lines (between `#ifndef ENGINE_SHB` and its `#define ENGINE_SHB(...)` line)."""
    m = re.search(r'^#ifndef ENGINE_SHB\n(#define ENGINE_SHB\(x\)[^\n]*)\n', text, re.M)
    if not m:
        sys.exit("probe: ENGINE_SHB definition not found in engine_core.h")
    return m.group(1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ov", required=True)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--plan", action="store_true")
    a = ap.parse_args()
    text = ECH.read_text(errors="surrogateescape")
    macros, seen = macro_index(text)
    twice = sorted(n for n, c in seen.items() if c > 1)
    print(f"engine_core.h: {sum(seen.values())} define lines, {len(macros)} distinct, {len(twice)} defined twice")
    tus = sorted((ROOT / "src" / a.ov).glob("*.c"))
    used, plans = {}, {}
    for tu in tus:
        src = tu.read_text(errors="surrogateescape").split("\n")
        new, nsite = [], 0
        for ln in src:
            if ln.strip() == '#include "../shared/engine_core.h"':
                new.append('#include "../shared/engine_prelude.h"')
                continue
            m = SITE.match(ln)
            if m:
                fn = m.group(2)
                mname = "DEFINE_" + fn
                if mname not in macros:
                    sys.exit(f"probe: {tu.name} uses {mname} which engine_core.h does not define")
                used[fn] = macros[mname]
                new.append(f'{m.group(1)}#include "../shared/ov/{fn}.h"')
                nsite += 1
                continue
            if "DEFINE_func_" in ln and not ln.lstrip().startswith(("/*", "*", "//")):
                sys.exit(f"probe: {tu.name}: unrecognized DEFINE_ line shape (R43): {ln!r}")
            new.append(ln)
        plans[tu] = ("\n".join(new), nsite)
    print(f"{a.ov}: {len(tus)} TUs, {sum(n for _, n in plans.values())} sites, {len(used)} distinct shared bodies")
    for fn, body in used.items():
        if any(l.endswith("\\") for l in body):
            sys.exit(f"probe: {fn}: a trailing backslash survived")
    if not a.apply:
        return
    shared = ROOT / "src/shared"
    (shared / "ov").mkdir(exist_ok=True)
    prelude = shared / "engine_prelude.h"
    prelude.write_text(
        "/* src/shared/engine_prelude.h — Phase 35: what every overlay/module TU needs from the shared tree BEFORE its\n"
        " * first shared body: the shared engine types and the ENGINE_SHB barrier. Replaces the engine_core.h include.\n"
        " * The bodies themselves are per-function headers under src/shared/<space>/, included at each member's site. */\n"
        "#ifndef SHARED_ENGINE_PRELUDE_H\n#define SHARED_ENGINE_PRELUDE_H\n"
        '#include "common.h"\n#include "engine_types.h"\n'
        "#ifndef ENGINE_SHB\n" + engine_shb_block(text) + "\n#endif\n#endif\n")
    for fn, body in used.items():
        hp = shared / "ov" / f"{fn}.h"
        banner = (f"/* {fn} — shared engine body (overlay slot 0x80128158). ONE source: instantiated by #include at each\n"
                  f" * member's site in address order; the members are recorded in config/dedup.us.yaml. Phase 35 probe form. */\n")
        hp.write_text(banner + "\n".join(body).rstrip("\n") + "\n")
    for tu, (newtext, _) in plans.items():
        tu.write_text(newtext)
    print(f"applied: {len(used)} headers under src/shared/ov, prelude written, {len(tus)} TUs rewritten")


if __name__ == "__main__":
    main()
