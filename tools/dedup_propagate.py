#!/usr/bin/env python3
"""dedup_propagate.py — match once, share many across the overlay fleet (Phase 15, cookbook §14).

The overlay fleet is position-locked at vram 0x80128158, so a shared engine function has the
SAME vaddr (hence the same `func_<ADDR>` symbol) and BYTE-IDENTICAL body in every overlay that
contains it. This tool takes a function already matched in ONE overlay and propagates that single
matched C body to every onboarded overlay whose signature shows the same `h_exact` at that addr:

  1. extract the matched body from the source overlay's .c  (externs + the function def)
  2. author it ONCE as a `DEFINE_func_<ADDR>()` macro in src/shared/<header>.h  (idempotent)
  3. at each member overlay, replace that function's INCLUDE_ASM stub (or, in the source overlay,
     its inline def) in place with `DEFINE_func_<ADDR>()` — address order preserved
  4. BYTE-GATE every touched overlay (`make build BINARY=<ov>` == its check.sha); on ANY miss,
     restore every file from an in-memory snapshot and abort (fail-closed; nothing wrong can land)
  5. register the group in config/dedup.us.yaml (the byte-honesty registry, validated by
     tools/dedup_integrate.py --check)

Everything is keyed by the integer address: the sig uses lowercase hex ("0x80144b9c"), splat emits
the uppercase symbol ("func_80144B9C") — never compare the strings, always the int.

Lead with h_exact (guaranteed byte-identity). The per-overlay `make check` is the sole arbiter
(G3/P9): a wrong propagation cannot pass it.

Usage:
  tools/dedup_propagate.py --addr 0x8013xxxx[,0x...] [--source-overlay ov_SC01_077]
  tools/dedup_propagate.py --auto-from ov_SC01_077 [--min-reach 2] [--limit N]
  tools/dedup_propagate.py ... --check-only         # dry run: print the plan, touch nothing
Options:
  --header src/shared/engine_core.h   target cluster header (created/appended)
  --tier h_exact|h_norm               default h_exact (h_norm requires the byte-gate to pass on ALL)
  --binaries a,b,c                    restrict members to these onboarded overlays (default: all that share)
  --no-gate                           skip the per-overlay build gate (CI / batch re-gate later)
"""
import argparse, json, pathlib, re, subprocess, sys

ROOT = pathlib.Path(__file__).resolve().parent.parent


# ---------------------------------------------------------------- fleet / sig helpers
def onboarded_overlays():
    mk = (ROOT / "config/overlays.mk").read_text()
    m = re.search(r"^OVERLAY_BINARIES\s*:=\s*(.*)$", mk, re.M)
    return m.group(1).split() if m else []


def sig_path(ov):
    return ROOT / f".run/sig.{ov}.jsonl"


def load_sig(ov):
    """addr(int) -> {h_exact, h_norm, nins, ...}; {} if absent."""
    p = sig_path(ov)
    if not p.exists():
        return {}
    out = {}
    for ln in p.read_text().splitlines():
        ln = ln.strip()
        if ln:
            r = json.loads(ln)
            out[int(r["addr"], 16)] = r
    return out


def sym(addr):
    return f"func_{addr:08X}"  # splat convention: uppercase 8-hex


def c_path(ov):
    return ROOT / f"src/{ov}/{ov}.c"


def stub_line(ov, addr):
    return f'INCLUDE_ASM("asm/{ov}/nonmatchings/{ov}", {sym(addr)});'


# ---------------------------------------------------------------- body extraction
def find_site(text, ov, addr):
    """Locate this function in ov's .c. Returns (kind, start, end, body_lines):
       kind 'stub'   -> the INCLUDE_ASM line (start==end, body_lines None)
       kind 'def'    -> an inline definition block (preceding contiguous externs .. closing brace)
       kind 'macro'  -> already a DEFINE_func_<ADDR>() instantiation (already propagated)
       None          -> not present / matched in some other form."""
    lines = text.splitlines()
    s = sym(addr)
    stub = stub_line(ov, addr)
    for i, l in enumerate(lines):
        if l.strip() == stub:
            return ("stub", i, i, None)
    for i, l in enumerate(lines):
        if l.strip() == f"DEFINE_{s}()" or l.strip().startswith(f"DEFINE_{s}()"):
            return ("macro", i, i, None)
    # inline definition: "<type> func_XXXX(...) {" at column 0, brace on the same line
    defre = re.compile(rf"^[A-Za-z_][\w \*]*\b{s}\s*\([^;]*\)\s*\{{")
    for i, l in enumerate(lines):
        if defre.match(l):
            # brace-match forward to the closing '}'
            depth = 0
            end = None
            for j in range(i, len(lines)):
                depth += lines[j].count("{") - lines[j].count("}")
                if depth <= 0:
                    end = j
                    break
            if end is None:
                return None
            # collect contiguous preceding extern declarations (skip blank lines)
            start = i
            k = i - 1
            while k >= 0 and lines[k].strip() == "":
                k -= 1
            while k >= 0 and re.match(r"^\s*extern\b.*;\s*$", lines[k]):
                start = k
                k -= 1
                while k >= 0 and lines[k].strip() == "":
                    k -= 1
            body = [ln for ln in lines[start:end + 1] if ln.strip() != ""]
            return ("def", start, end, body)
    return None


def make_macro(addr, body_lines):
    """Turn an extracted body (externs + def) into a `#define DEFINE_func_<ADDR>() \\`-continued macro.
       Fails loud on constructs that don't survive line-continuation (// comments, trailing backslash)."""
    s = sym(addr)
    for ln in body_lines:
        if "//" in ln:
            raise SystemExit(f"[refuse] {s}: body has a // comment — not macro-safe (handle manually)")
        if ln.rstrip().endswith("\\"):
            raise SystemExit(f"[refuse] {s}: body line ends with backslash — not macro-safe")
    out = [f"#define DEFINE_{s}() \\"]
    for idx, ln in enumerate(body_lines):
        cont = " \\" if idx < len(body_lines) - 1 else ""
        out.append("    " + ln.rstrip() + cont)
    return "\n".join(out) + "\n"


# ---------------------------------------------------------------- file edits (in memory)
INCLUDE_RE = re.compile(r'^#include\s+"\.\./shared/')


def ensure_include(text, header):
    rel = f'#include "../shared/{pathlib.Path(header).name}"'
    if rel in text:
        return text
    lines = text.splitlines(keepends=True)
    for i, l in enumerate(lines):
        if l.strip() == '#include "common.h"':
            lines.insert(i + 1, rel + "\n")
            return "".join(lines)
    return rel + "\n" + text  # fallback: prepend


def replace_site(text, ov, addr, kind, start, end):
    lines = text.splitlines(keepends=True)
    repl = f"DEFINE_{sym(addr)}()  /* dedup: shared engine-core @0x{addr:08X} (src/shared) */\n"
    lines[start:end + 1] = [repl]
    return "".join(lines)


# ---------------------------------------------------------------- dedup.us.yaml registration
def append_groups(groups):
    """Append new groups textually (preserve the file's header comments). Idempotent by id."""
    path = ROOT / "config/dedup.us.yaml"
    text = path.read_text()
    blocks = []
    for g in groups:
        if re.search(rf"^\s*-\s*id:\s*{re.escape(g['id'])}\s*$", text, re.M):
            continue  # already present
        mem = "\n".join(
            f"      - {{ binary: {m['binary']}, vram: 0x{m['vram']:08X}, name: {m['name']} }}"
            for m in g["members"])
        blocks.append(
            f"  - id: {g['id']}\n"
            f"    tier: {g['tier']}\n"
            f"    hash: {g['hash']}\n"
            f"    source: {g['source']}\n"
            f"    func: DEFINE_{sym(g['addr'])}\n"
            f"    members:\n{mem}")
    if not blocks:
        return 0
    if not text.endswith("\n"):
        text += "\n"
    path.write_text(text + "\n".join(blocks) + "\n")
    return len(blocks)


# ---------------------------------------------------------------- byte gate
def byte_gate(ov):
    r = subprocess.run(["make", "build", f"BINARY={ov}"], cwd=ROOT,
                       capture_output=True, text=True)
    return r.returncode == 0, r.stdout + r.stderr


# ---------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", help="comma-separated target vaddrs (hex)")
    ap.add_argument("--auto-from", help="propagate every matched+shared function of this overlay")
    ap.add_argument("--source-overlay", help="overlay to extract the matched body from (default: auto)")
    ap.add_argument("--min-reach", type=int, default=2, help="min #overlays sharing (auto mode; default 2)")
    ap.add_argument("--limit", type=int, default=0, help="cap #functions (auto mode; 0 = no cap)")
    ap.add_argument("--header", default="src/shared/engine_core.h")
    ap.add_argument("--tier", default="h_exact", choices=("h_exact", "h_norm"))
    ap.add_argument("--binaries", help="restrict members to these onboarded overlays (comma list)")
    ap.add_argument("--check-only", action="store_true", help="dry run: print the plan, touch nothing")
    ap.add_argument("--no-gate", action="store_true")
    a = ap.parse_args()

    onb = onboarded_overlays()
    restrict = set(a.binaries.split(",")) if a.binaries else None
    pool = [ov for ov in onb if (restrict is None or ov in restrict)]
    sigs = {ov: load_sig(ov) for ov in pool}

    # ---- choose target addresses + source overlay per target
    targets = []  # list of (addr, source_overlay)
    if a.auto_from:
        src = a.auto_from
        ssig = load_sig(src)
        ctext = c_path(src).read_text()
        for addr in sorted(ssig):
            site = find_site(ctext, src, addr)
            if not site or site[0] != "def":   # only functions matched (inline def) in the source
                continue
            h = ssig[addr].get(a.tier)
            reach = sum(1 for ov in pool if sigs[ov].get(addr, {}).get(a.tier) == h)
            if reach >= a.min_reach:
                targets.append((addr, src))
        targets.sort(key=lambda t: ssig[t[0]]["nins"])
        if a.limit:
            targets = targets[:a.limit]
    elif a.addr:
        for tok in a.addr.split(","):
            addr = int(tok, 16)
            src = a.source_overlay
            if not src:  # auto: an onboarded overlay where it is an inline def
                for ov in pool:
                    site = find_site(c_path(ov).read_text(), ov, addr)
                    if site and site[0] == "def":
                        src = ov
                        break
            if not src:
                sys.exit(f"[error] 0x{addr:08X}: no source overlay has it matched — give --source-overlay")
            targets.append((addr, src))
    else:
        sys.exit("give --addr or --auto-from")

    # ---- build the per-target plan (members + body + hash)
    plan = []
    for addr, src in targets:
        ssig = load_sig(src)
        if addr not in ssig:
            print(f"[skip] 0x{addr:08X}: not signed in {src}"); continue
        h = ssig[addr].get(a.tier)
        site = find_site(c_path(src).read_text(), src, addr)
        if not site or site[0] != "def":
            print(f"[skip] 0x{addr:08X}: not an inline def in source {src}"); continue
        body = site[3]
        members = [ov for ov in pool if sigs[ov].get(addr, {}).get(a.tier) == h]
        if len(members) < 2:
            print(f"[skip] 0x{addr:08X}: reach {len(members)} < 2"); continue
        plan.append(dict(addr=addr, src=src, hash=h, body=body, members=members))

    if not plan:
        sys.exit("[error] nothing to propagate")

    print(f"== plan: {len(plan)} function(s), tier={a.tier}, header={a.header} ==")
    for p in plan:
        print(f"  0x{p['addr']:08X}  body={len(p['body'])}L  members={len(p['members'])}  "
              f"[{','.join(m.replace('ov_','') for m in p['members'][:6])}{'…' if len(p['members'])>6 else ''}]")
    if a.check_only:
        print("(--check-only: no files touched)")
        return

    # ---- apply (in-memory snapshot of every file we touch, for fail-closed restore)
    header_path = ROOT / a.header
    touched = {}  # path -> original text (None if newly created)

    def edit(path, newtext):
        if path not in touched:
            touched[path] = path.read_text() if path.exists() else None
        path.write_text(newtext)

    # author macros
    htext = header_path.read_text() if header_path.exists() else \
        ("/* src/shared/engine_core.h — Phase 15 shared engine-core bodies (cross-overlay dedup, §14).\n"
         " * Each DEFINE_func_XXXX() expands to the WHOLE matched body once; instantiated in place at the\n"
         " * func_XXXX site in every overlay that shares it (address order preserved). Registry +\n"
         " * byte-honesty: config/dedup.us.yaml + tools/dedup_integrate.py. Tool-generated; do not hand-edit. */\n"
         "#ifndef SHARED_ENGINE_CORE_H\n#define SHARED_ENGINE_CORE_H\n#include \"common.h\"\n\n#endif\n")
    for p in plan:
        if f"DEFINE_{sym(p['addr'])}()" not in htext:
            macro = make_macro(p["addr"], p["body"])
            htext = htext.replace("\n#endif\n", "\n" + macro + "\n#endif\n")
    edit(header_path, htext)

    # edit each member overlay
    for p in plan:
        for ov in p["members"]:
            cp = c_path(ov)
            t = cp.read_text()  # accumulated on-disk text (edit() preserves the original for restore)
            t = ensure_include(t, a.header)
            site = find_site(t, ov, p["addr"])
            if not site:
                print(f"[warn] {ov}: 0x{p['addr']:08X} site not found — skipping in this overlay")
                continue
            if site[0] == "macro":
                edit(cp, t)  # already instantiated (idempotent)
                continue
            t = replace_site(t, ov, p["addr"], *site[:3])
            edit(cp, t)

    # ---- byte-gate every touched overlay
    def restore():
        for path, orig in touched.items():
            if orig is None:
                path.unlink(missing_ok=True)
            else:
                path.write_text(orig)

    # structural check the byte-gate CANNOT catch: a leftover INCLUDE_ASM stub is itself
    # byte-identical, so `make check` would pass even if a function wasn't actually converted.
    for p in plan:
        for ov in p["members"]:
            t = c_path(ov).read_text()
            if f"DEFINE_{sym(p['addr'])}()" not in t:
                restore(); sys.exit(f"[FAIL] {ov}: 0x{p['addr']:08X} not instantiated after edit — REVERTED")
            if stub_line(ov, p["addr"]) in t:
                restore(); sys.exit(f"[FAIL] {ov}: 0x{p['addr']:08X} stub still present — REVERTED")

    gate_ovs = sorted({ov for p in plan for ov in p["members"]})
    if not a.no_gate:
        for ov in gate_ovs:
            ok, log = byte_gate(ov)
            if not ok:
                tail = "\n".join(log.splitlines()[-12:])
                print(f"[FAIL] {ov} not byte-identical after propagation — REVERTING ALL.\n{tail}")
                restore()
                sys.exit(1)
            print(f"[ OK ] {ov} byte-identical")

    # ---- register groups
    groups = [dict(id=f"E_{sym(p['addr'])}", tier=a.tier, hash=p["hash"],
                   source=a.header, addr=p["addr"],
                   members=[dict(binary=ov, vram=p["addr"], name=sym(p["addr"])) for ov in p["members"]])
              for p in plan]
    n = append_groups(groups)
    print(f"== propagated {len(plan)} function(s) across {len(gate_ovs)} overlays; "
          f"registered {n} new group(s) in config/dedup.us.yaml ==")


if __name__ == "__main__":
    main()
