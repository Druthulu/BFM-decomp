#!/usr/bin/env python3
"""inject_capped_externs.py — free the reach>=N inline matches that dedup_propagate skips as
"not self-contained" because they reference callees/data declared only at FILE scope (Phase-20
backlog "macro-extern-injection", cookbook §28/§28c).

A function matched INLINE in the canonical source (ov_SC01_077) builds byte-identically there
because the .c declares every callee/data symbol at file scope. But dedup_propagate lifts only the
function DEF (find_site captures the def + *contiguous* preceding externs, not the file-scope ones),
so in every OTHER overlay the lifted macro body has undeclared `func_X`/`D_X` -> compiles_standalone
fails -> the match stays ov_SC01_077-LOCAL (no x reach). These are NOT a codegen wall — the bytes are
already correct; the only barrier is declaration plumbing.

This tool, for each such capped function, sources the EXACT file-scope `extern ...;` line the overlay
already declares for every symbol the body references, and injects those externs BLOCK-scope (just
inside the body's opening brace) so the lifted macro is self-contained with the correct types. Block
vs file scope is codegen-neutral, so the source overlay stays byte-identical (the gate proves it);
then `dedup_propagate --auto-from` propagates each x reach.

Fail-safe (P9/G3): a function is rewritten ONLY if the injected body then `compiles_standalone`
(common.h + engine_types.h). Ones still blocked (a data extern whose struct type isn't yet in
engine_types.h -> needs build_engine_types.py §28b; an inline-defined type; a parse-resistant body)
are reported and left untouched. The whole-binary byte-gate remains the sole arbiter downstream.

Usage:
  tools/inject_capped_externs.py [--overlay ov_SC01_077] [--src-file src/ov_SC01_077/ov_SC01_077.c]
                                 [--min-reach 2] [--apply]
  (default = dry run: print the plan, touch nothing)
"""
import argparse, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dedup_propagate as dp

SYM_RE = re.compile(r'\b(func_[0-9A-Fa-f]{6,8}|D_[0-9A-Fa-f]{6,8})\b')


def def_span(text, name):
    """Return (start, end) char span of `name`'s top-level definition in text, or None."""
    m = re.search(r'\n([A-Za-z_][^\n;]*\b%s\s*\([^;{]*\)\s*\{)' % re.escape(name), text)
    if not m:
        return None
    start = m.start(1)
    i = text.index('{', start)
    depth, j = 0, i
    while j < len(text):
        if text[j] == '{':
            depth += 1
        elif text[j] == '}':
            depth -= 1
            if depth == 0:
                return start, j + 1
        j += 1
    return None


def file_scope_externs(text):
    """Map symbol -> its file-scope `extern ...;` declaration line (first occurrence)."""
    out = {}
    for m in re.finditer(r'^[ \t]*(extern[^\n;]*;)[ \t]*$', text, re.M):
        line = m.group(1).strip()
        sm = SYM_RE.search(line)
        if sm and sm.group(1) not in out:
            out[sm.group(1)] = line
    return out


def inject(defblock, name, ext_map):
    """Return (injected_block, missing_syms). Inject block-scope externs for every referenced
    func_/D_ symbol (except `name` itself) that the file declares."""
    syms = sorted(set(SYM_RE.findall(defblock)) - {name})
    lines, missing = [], []
    for s in syms:
        if s in ext_map:
            lines.append("    " + ext_map[s])
        else:
            missing.append(s)
    brace = defblock.index('{')
    injected = defblock[:brace + 1] + "\n" + "\n".join(lines) + "\n" + defblock[brace + 1:]
    return injected, missing


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--overlay", default="ov_SC01_077")
    ap.add_argument("--src-file", default="src/ov_SC01_077/ov_SC01_077.c")
    ap.add_argument("--min-reach", type=int, default=2)
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()

    src = a.overlay
    srcfile = dp.ROOT / a.src_file
    text = srcfile.read_text()
    ext_map = file_scope_externs(text)

    pool = dp.onboarded_overlays()
    sigs = {ov: dp.load_sig(ov) for ov in pool}
    ssig = sigs[src]
    reg = dp.registered_addrs()
    ctext = dp.source_text(src)

    applied, skipped = [], []
    edits = []  # (start, end, new_text)
    for addr in sorted(ssig):
        if addr in reg:
            continue
        site = dp.find_site(ctext, src, addr)
        if not site or site[0] != "def":
            continue
        h = ssig[addr].get("h_exact")
        reach = sum(1 for ov in pool if sigs[ov].get(addr, {}).get("h_exact") == h)
        if reach < a.min_reach:
            continue
        # already self-contained? then dedup_propagate handles it directly — skip
        if dp.compiles_standalone(site[3]):
            continue
        name = f"func_{addr:08X}"
        span = def_span(text, name)
        if not span:
            skipped.append((addr, reach, "def not in this file (split _a/_o0?)"))
            continue
        defblock = text[span[0]:span[1]]
        # an inline-defined named type needs the §28b type-lift, not extern injection
        if re.search(r'(\b(struct|union)\s+\w+\s*\{)|(\btypedef\b)', defblock):
            skipped.append((addr, reach, "inline type def -> build_engine_types.py (§28b)"))
            continue
        injected, missing = inject(defblock, name, ext_map)
        if not dp.compiles_standalone(injected.split("\n")):
            reason = ("missing extern: " + ",".join(missing)) if missing else "type/other wall"
            skipped.append((addr, reach, reason))
            continue
        edits.append(span + (injected,))
        applied.append((addr, reach))

    print(f"== inject_capped_externs: {src} ({a.src_file}), min-reach {a.min_reach} ==")
    print(f"   will inject + free: {len(applied)}   |   left for other levers: {len(skipped)}")
    for addr, reach in applied:
        print(f"   FREE  0x{addr:08X}  reach={reach}")
    for addr, reach, why in skipped:
        print(f"   skip  0x{addr:08X}  reach={reach}  ({why})")

    if a.apply and edits:
        for start, end, new in sorted(edits, reverse=True):  # apply from end -> spans stay valid
            text = text[:start] + new + text[end:]
        srcfile.write_text(text)
        print(f"\n[apply] wrote {len(edits)} injected defs to {a.src_file}")
        print("[next] make build BINARY=%s  (must stay byte-identical) -> dedup_propagate --auto-from %s --min-reach %d"
              % (src, src, a.min_reach))
    elif not a.apply:
        print("\n(dry run: pass --apply to write)")


if __name__ == "__main__":
    main()
