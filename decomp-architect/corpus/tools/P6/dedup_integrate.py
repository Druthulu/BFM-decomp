#!/usr/bin/env python3
"""Cross-binary code-share registry validator (Phase 11, G7 "match once, share").

Validates config/dedup.us.yaml — the registry of functions matched ONCE and shared across >=2
duplicate sites/binaries via a source-level body (a macro in src/shared/), instantiated at each
member site so the same bytes land at each member vram.

WHAT THE REGISTRY CLAIMS, AND HOW EACH CLAIM IS CHECKED  (Phase 26-A tooling audit; R32/R33)
--------------------------------------------------------------------------------------------
C1  EQUIVALENCE — "these member vrams hold the same code IN THE ORIGINAL BINARY."
    Checked against .run/sig.<bin>.jsonl, which signs the ORIGINAL bytes. A genuine EXTERNAL
    oracle: it catches a group registered with a wrong hash, or a member vram whose original
    bytes are not in the claimed equivalence class.
    It does NOT — and cannot — detect SOURCE drift: a sig is a property of the ROM, so it is
    immutable with respect to src/. (The pre-audit docstring claimed it did. Source drift is
    caught by the BUILD, `make check`, which is the real byte-gate. P9.)

C2  BANK — "the body is matched once in `source` (named `func`) and INSTANTIATED at every member."
    DERIVED from the build invariant rather than re-parsed (R33): the fleet builds byte-identical,
    and INCLUDE_ASM pastes the ORIGINAL assembly — therefore a member site NOT wrapped in
    INCLUDE_ASM is byte-exact, and one that IS wrapped is NOT banked, whatever the registry says.
      C2a  the `func` token must actually occur in `source`   (no group may name a macro nobody wrote)
      C2b  no member may still be an INCLUDE_ASM stub          (no group may claim work never done)

COVERAGE (R32) — the run reports found-vs-candidates and REFUSES to print a green it did not earn.
    A member whose binary has no signature file is UNVALIDATED for C1, and the run FAILS unless
    --allow-unsigned. Pre-audit this printed [WARN] and still exited 0 — so on a fresh clone, where
    .run/sig.*.jsonl does not exist at all, the gate validated NOTHING and passed.

WHY THIS TOOL IS AUDITED FIRST
------------------------------
It is the last line of `make report` and is fail-closed by design, so a silent skip here is a FALSE
GREEN FROM A GATE and nothing downstream can catch it. The audit found three:
  * C2a was greenlighting 7 groups whose `DEFINE_func_*` macro was never written (1808 claimed,
    1801 defined) — hiding 532 member-instances of real, unbanked work in 4 functions that are
    matched in ov_SC01_077 and still INCLUDE_ASM in the other 133 overlays;
  * a missing sig file degraded silently to "0 validated, 0 failed" and exit 0;
  * the bank claim itself was never checked at all.

This is NOT a fork of psyq_integrate's object-swap: that works only for separate library SUBSEGMENT
stubs; game-code functions are interior to one object per binary, so the linker cannot swap them —
sharing is source-level. The .ld interpose stays the library mechanism.

Usage: tools/dedup_integrate.py [--check] [--binary <alias>] [--allow-unsigned]
                                [--dedup config/dedup.us.yaml]
"""
import argparse, json, os, pathlib, re, sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from dup_report import BINARIES  # single source of truth for per-binary .run/sig.<bin>.jsonl paths

TIERS = ("h_exact", "h_norm", "h_text")   # h_text (Phase 35 T5b): one TEXT at one address whose bytes vary per binary — C1 per member

# OVER-APPROXIMATING by design (R32): any C identifier, not just func_<hex> — a curated symbol
# (e.g. listCdBuffer) is a stub too, and a `func_`-only pattern silently misses it.
INCLUDE_ASM_RE = re.compile(r'INCLUDE_ASM\([^)]*,\s*([A-Za-z_]\w*)\s*\)')
PARAM_FUNC_RE = re.compile(r'^SHARED_FN$')   # the parameterized include form's `func` token (P35; the macro forms are gone)
SYMBOL_LINE_RE = re.compile(r'^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;')


def _addr(v):
    """Accept a YAML int (0x.. parsed) or a hex string ('0x..' / bare hex) -> int."""
    return v if isinstance(v, int) else int(str(v), 16)


def group_members(g):
    """Yield (binary, vram_int, name) for a group in EITHER form (Phase 15):
       verbose   -> members: [{binary, vram, name}, ...]
       shorthand -> vram: 0xADDR + binaries: [a, b, ...]  (position-locked: same vram/name everywhere;
                    ~20x smaller for fleet-wide shares where every member sits at the identical vaddr)."""
    if g.get("members"):
        for m in g["members"]:
            a = _addr(m["vram"])
            yield m.get("binary"), a, m.get("name", f"func_{a:08X}")
    elif g.get("binaries") is not None and g.get("vram") is not None:
        a = _addr(g["vram"]); nm = f"func_{a:08X}"
        for b in g["binaries"]:
            yield b, a, nm


def _src_paths(binary):
    """The .c files that make up a binary's source — through the Makefile oracle (corpus.src_files: a twin's files are its
    primary's, Phase 35 T2/T3), never a hand-built src/<binary> path (R33)."""
    sys.path.insert(0, str(ROOT / "tools"))
    import corpus
    return [pathlib.Path(p) for p in corpus.src_files(binary)]


def _curated_syms(binary):
    """curated name -> addr, from the symbol files that can name this binary's symbols."""
    out = {}
    for cand in (f"symbols.{binary}.txt", "symbols.resident.txt", "symbols.us.txt"):
        p = ROOT / "config" / cand
        if not p.exists():
            continue
        for line in p.read_text().splitlines():
            m = SYMBOL_LINE_RE.match(line)
            if m:
                out.setdefault(m.group(1), int(m.group(2), 16))
    return out


_STUB_CACHE = {}


def stub_addrs(binary):
    """C2b's oracle: the set of vram addresses this binary still ships as INCLUDE_ASM.

    Resolves ANY C identifier, not just func_<hex> — a curated stub name (listCdBuffer) is a stub.
    An unresolvable stub symbol is a COVERAGE FAILURE, not a shrug: it means this oracle cannot
    answer "is this member banked?" for that address, so we fail loud rather than guess 'banked'."""
    if binary in _STUB_CACHE:
        return _STUB_CACHE[binary]
    paths = _src_paths(binary)
    if not paths:
        sys.exit(f"dedup-check: binary {binary!r} has no source under src/ — cannot verify its bank claims")
    syms = _curated_syms(binary)
    addrs, unresolved = set(), []
    for p in paths:
        for m in INCLUDE_ASM_RE.finditer(p.read_text()):
            nm = m.group(1)
            if re.fullmatch(r'func_[0-9A-Fa-f]{8}', nm):
                addrs.add(int(nm[5:], 16))
            elif nm in syms:
                addrs.add(syms[nm])
            else:
                unresolved.append(f"{p.relative_to(ROOT)}: {nm}")
    if unresolved:
        sys.exit(f"dedup-check: {len(unresolved)} INCLUDE_ASM symbol(s) in {binary} resolve to no "
                 f"address — the bank oracle is blind to them:\n  " + "\n  ".join(unresolved[:10]))
    _STUB_CACHE[binary] = addrs
    return addrs


def _load_sig_index(rel):
    """addr(int) -> sig row for .run/sig.<bin>.jsonl, or None if the file is absent."""
    p = ROOT / rel
    if not p.exists():
        return None
    idx = {}
    for line in p.read_text().splitlines():
        line = line.strip()
        if line:
            r = json.loads(line)
            idx[int(r["addr"], 16)] = r
    return idx


def check(groups, binary_filter=None, allow_unsigned=False):
    """Validate every group's C1 (equivalence, vs the original bytes) and C2 (bank, vs the build
    invariant). Returns the failure count (0 = every claim honest AND fully covered)."""
    sigcache = {}

    def sig_for(binary):
        if binary not in sigcache:
            cfg = BINARIES.get(binary)
            sigcache[binary] = _load_sig_index(cfg["sig"]) if cfg else None
        return sigcache[binary]

    src_cache = {}

    def source_text(rel):
        if rel not in src_cache:
            p = ROOT / rel
            src_cache[rel] = p.read_text() if p.exists() else None
        return src_cache[rel]

    failures = unvalidated = validated = 0
    members_seen = members_c1 = 0
    # C2d (Phase 35 T7): the per-instance source FORMS from the census (one scan per TU, cached by mtime/size) — a member's site must
    # be an include of THIS group's source; a surviving private copy is the registry running ahead of the source.
    _forms = {}

    def site_form(binary, vram):
        if not _forms:
            sys.path.insert(0, str(ROOT / "tools"))
            import share_census as _sc
            aliases, dirs = _sc.fleet_and_dirs()
            f, _notes = _sc.build_forms(aliases, dirs, os.cpu_count() or 4, use_cache=True)
            _forms.update(f)
            _forms.setdefault("__loaded__", {})
        return _forms.get(binary, {}).get(vram)

    for g in groups:
        gid = g.get("id", "?")
        members = list(group_members(g))
        if binary_filter and not any(b == binary_filter for b, _, _ in members):
            continue
        if g.get("tier") not in TIERS:
            print(f"[FAIL] {gid}: tier must be one of {TIERS} (got {g.get('tier')!r})"); failures += 1; continue
        if len(members) < 2:
            print(f"[FAIL] {gid}: a share needs >=2 members (got {len(members)})"); failures += 1; continue
        src = g.get("source")
        txt = source_text(src) if src else None
        if txt is None:
            print(f"[FAIL] {gid}: shared source {src!r} missing"); failures += 1; continue

        # ---- C2a: the shared body this group names must actually EXIST in `source` ---------------
        fn = g.get("func")
        if not fn:
            print(f"[FAIL] {gid}: no `func` (the group must name the shared body it claims)")
            failures += 1; continue
        if not re.search(rf'\b{re.escape(fn)}\b', txt):
            print(f"[FAIL] {gid}: `func: {fn}` does NOT occur in {src} — the group claims a shared "
                  f"body that was never written (the share was registered but never propagated)")
            failures += 1; continue
        # ---- C2a′ (Phase 35 T2): a PLAIN-C header source must DEFINE `func` (a token occurrence is not a body) --------
        # The parameterized form (SHARED_FN) defines through cpp and keeps the token check above; every other source is a
        # plain-C header read by share_census.header_defs — the one reader of that form (R33).
        sys.path.insert(0, str(ROOT / "tools"))
        import share_census
        defined = {n for n, _ in share_census.header_defs(ROOT / src)}
        if not PARAM_FUNC_RE.match(fn) and fn not in defined:
            print(f"[FAIL] {gid}: `func: {fn}` occurs in {src} but that header does not DEFINE it "
                  f"(defines: {sorted(defined)[:4]}) — a declaration is not a shared body")
            failures += 1; continue
        # ---- C2c (Phase 35 T7): ONE source, under src/shared/, defining exactly ONE function — the token the group names ----------
        if not src.startswith("src/shared/"):
            print(f"[FAIL] {gid}: source {src} is not under src/shared/ — a shared body has its one source there (S1)")
            failures += 1; continue
        if len(defined) != 1:
            print(f"[FAIL] {gid}: {src} defines {len(defined)} functions {sorted(defined)[:4]} — a shared header defines exactly one (C2c)")
            failures += 1; continue

        tier, want = g["tier"], g.get("hash")
        if not want:
            print(f"[FAIL] {gid}: no recorded hash"); failures += 1; continue
        # h_text (Phase 35 T5b): the group hash is the normalized TEXT; every member carries its OWN h_exact (the bytes differ per
        # binary through the TU's declarations) — C1 compares each member against its recorded byte hash, never the group's
        member_hash = {}
        if tier == "h_text":
            for m in g.get("members") or []:
                if not m.get("h_exact"):
                    print(f"[FAIL] {gid}: h_text member {m.get('binary')}:{m.get('vram')} carries no h_exact"); failures += 1
                member_hash[(m.get("binary"), _addr(m["vram"]))] = m.get("h_exact")
            if len(member_hash) != len(list(group_members(g))):
                continue

        ok = True
        for (b, vram, name) in members:
            members_seen += 1

            # ---- C2b: DERIVED from the build invariant — a member still stubbed is NOT banked ----
            if vram in stub_addrs(b):
                print(f"[FAIL] {gid}: {b}:0x{vram:08x} ({name}) is claimed MATCHED but is still an "
                      f"INCLUDE_ASM stub — the registry is claiming work that was never done")
                failures += 1; ok = False; continue

            # ---- C2d (Phase 35 T7): the member's SITE includes this group's source — no private copy survives ----------------
            rec = site_form(b, vram)
            if rec is None:
                print(f"[FAIL] {gid}: {b}:0x{vram:08x} ({name}) has no source form in the census (coverage, R32)")
                failures += 1; ok = False; continue
            if rec.get("form") not in ("include", "param-include"):
                print(f"[FAIL] {gid}: {b}:0x{vram:08x} ({name}) is listed as a member but its site is a {rec.get('form')} in {rec.get('tu')} — "
                      f"the registry runs ahead of the source (C2d)")
                failures += 1; ok = False; continue
            if rec.get("header") and rec["header"] != src:
                print(f"[FAIL] {gid}: {b}:0x{vram:08x} ({name}) includes {rec['header']}, not this group's source {src} (C2d)")
                failures += 1; ok = False; continue
            # ---- C1: equivalence, against the ORIGINAL bytes ------------------------------------
            idx = sig_for(b)
            if idx is None:
                unvalidated += 1; ok = False
                continue
            row = idx.get(vram)
            if row is None:
                print(f"[FAIL] {gid}: {b}:0x{vram:08x} ({name}) not found in {b} signature")
                failures += 1; ok = False; continue
            want_m = member_hash.get((b, vram), want) if tier == "h_text" else want
            got = row.get("h_exact" if tier == "h_text" else tier)
            if got != want_m:
                print(f"[FAIL] {gid}: {b}:0x{vram:08x} ({name}) {'h_exact' if tier == 'h_text' else tier}={got} != recorded {want_m} — SHARE DRIFTED")
                failures += 1; ok = False; continue
            members_c1 += 1

        if ok:
            validated += 1
            uniq = sorted({b for b, _, _ in members})
            disp = ",".join(uniq) if len(uniq) <= 6 else f"{len(uniq)} binaries"
            print(f"[ OK ] {gid}: {len(members)} members [{disp}] share {tier} {want[:12]}… (source {src})")

    # ---- COVERAGE (R32): never print a green this run did not earn ------------------------------
    print(f"dedup-check: {validated} validated, {failures} failed  "
          f"| C1 coverage {members_c1}/{members_seen} members signed")
    if unvalidated:
        msg = (f"dedup-check: {unvalidated} member(s) UNVALIDATED — their binary has no "
               f".run/sig.<bin>.jsonl, so the equivalence claim could not be checked at all. "
               f"Run `make sig-overlays` (or pass --allow-unsigned to accept an unverified registry).")
        if allow_unsigned:
            print(f"[WARN] {msg}")
        else:
            print(f"[FAIL] {msg}")
            failures += unvalidated
    return failures


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dedup", default="config/dedup.us.yaml")
    ap.add_argument("--binary", default=None, help="validate only groups with a member in this binary")
    ap.add_argument("--check", action="store_true", help="validate (default mode)")
    ap.add_argument("--allow-unsigned", action="store_true",
                    help="downgrade 'member has no sig file' from FAIL to WARN (fresh clone / pre-sig-refresh)")
    ap.add_argument("--apply", action="store_true", help="reserved (shares are source-level; validates only)")
    a = ap.parse_args()

    path = ROOT / a.dedup
    if not path.exists():
        print(f"dedup-check: {a.dedup} absent — no shares registered (build uses INCLUDE_ASM stubs).")
        return
    import yaml  # PyYAML (venv; splat dependency)
    data = yaml.safe_load(path.read_text()) or {}
    groups = data.get("groups") or []
    if a.apply:
        print("dedup_integrate --apply: shares are SOURCE-LEVEL (authored in src/shared/, instantiated "
              "per site); no build-time action — validating instead.")
    if check(groups, a.binary, a.allow_unsigned):
        sys.exit(1)


if __name__ == "__main__":
    main()
