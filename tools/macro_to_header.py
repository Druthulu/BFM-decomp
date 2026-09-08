#!/usr/bin/env python3
"""macro_to_header.py — Phase 35 T4 (ONE-OFF): every `DEFINE_func_X()` macro body of src/shared/engine_core.h becomes a plain-C
header under src/shared/<space>/ that is `#include`d at each member's site; the three legacy macro headers (clearTbl40.h,
ov_setters.h) are converted the same way; func_80144B9C.h (already the target form) moves under ov/; the registry's `source:` /
`func:` lines are text-edited; engine_core.h is deleted last.

    tools/macro_to_header.py --plan                       # the census of what would happen; touches nothing
    tools/macro_to_header.py --apply --binaries a,b,…     # convert these binaries' TUs (headers written on first use)
    tools/macro_to_header.py --finalize                   # legacy headers, the whale's move, the registry, engine_core.h deleted
    tools/macro_to_header.py --verify                     # 0 macro sites, no macro header, every registry source DEFINES its func

WHY IT IS BYTE-NEUTRAL BY CONSTRUCTION. A macro instantiated at a site and a header included at that site put the SAME text at the
SAME point of the SAME translation unit (the body's `extern`s become file-scope declarations at that line either way); cc1 emits
one extra `.file` directive that `as` consumes. Measured (Probe P1, then all 34 TUs of ov_SC06_033 at T0): byte-identical objects.
Still gated: `make check BINARY=<b>` per converted binary (the L0 object A/B ledger is the caller's), the clean fleet run at the end.

RULES OF THE CONVERSION
  * the LAST definition of a twice-defined macro is the body (cpp keeps the last; 1,631 twins, 4 divergent — asserted);
  * a directive audit first: engine_core.h must contain exactly its define lines + the 8 known directives, so the prelude
    (common.h + engine_types.h + ENGINE_SHB) is provably everything the header contributed besides bodies (R32);
  * the header's name is keyed by the h_exact CLASS, never by a bare name (R48): `func_<VRAM>` + `__<h8>` iff (space, vram) hosts
    more than one h_exact class fleet-wide (an immutable property of the ROM, so names are stable under later additions) —
    the space directory is `ov` (the overlay slot) or `slot_<BASE>` (a module slot base) or `main` / `resident`;
  * a macro with >=2 sites is a shared body -> a header; with 1 site -> a header iff its h_exact class has >=2 instances fleet-wide
    (T5 shares the other instances), else the body is written INLINE at its site as plain C; with 0 sites -> dropped, listed;
  * the body text is the macro's text with continuations stripped and the generator's 4-space indent removed, asserted to carry the
    SAME TOKENS; every extern, alias, comment and register pin is kept verbatim (pins are Phase 36's; declarations the types phase's);
  * pure fragments: no include guard (a second include of a fixed-name header must be the loud duplicate-definition error), no
    includes of their own (the prelude comes from the TU — sotn's contract);
  * the registry is TEXT-EDITED by group id, never `yaml.safe_dump` (dedup_extend's H5 lesson);
  * anything it cannot map is a refusal (R43): an unknown site shape, a header that would be written twice with different text
    (a collision the naming rule missed), a member set that spans address spaces.
"""
import argparse
import collections
import json
import os
import pathlib
import re
import shutil
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import share_census as sc          # noqa: E402 — the one reader of the header form (header_defs), the sig/space oracles

ECH = REPO / "src/shared/engine_core.h"
PRELUDE = REPO / "src/shared/engine_prelude.h"
OV_BASE = 0x80128158
SITE = re.compile(r"^(\s*)DEFINE_(func_[0-9A-Fa-f]{8})\(\)\s*(/\*.*?\*/)?\s*$")
DEFLINE = re.compile(r"^#define (DEFINE_func_[0-9A-Fa-f]{8})\(\)(.*)$")
DIVERGENT = {"DEFINE_func_8013FFD8", "DEFINE_func_8013F350", "DEFINE_func_80181538", "DEFINE_func_801808C4"}
KNOWN_DIRECTIVES = 8                 # #ifndef SHARED_ENGINE_CORE_H, #define it, #include common.h, #include engine_types.h,
                                     # #ifndef ENGINE_SHB, #define ENGINE_SHB(x), #endif, #endif


# ----------------------------------------------------------------------------------------------------------------------------
# the macro header
# ----------------------------------------------------------------------------------------------------------------------------
def parse_header():
    text = ECH.read_text(errors="surrogateescape")
    lines = text.split("\n")
    macros, count, twice = {}, 0, collections.Counter()
    i = 0
    while i < len(lines):
        m = DEFLINE.match(lines[i])
        if not m:
            i += 1
            continue
        name = m.group(1)
        if m.group(2).strip() != "\\":
            sys.exit(f"macro_to_header: unexpected text after the define of {name}: {m.group(2)!r} (R43)")
        body = []
        i += 1
        while i < len(lines) and lines[i].endswith("\\"):
            body.append(lines[i][:-1].rstrip())
            i += 1
        if i < len(lines):
            body.append(lines[i].rstrip())
            i += 1
        count += 1
        twice[name] += 1
        macros[name] = [ln[4:] if ln.startswith("    ") else ln for ln in body]      # the generator's 4-space indent
    directives = [ln for ln in lines if ln.startswith("#") and not DEFLINE.match(ln)]
    shb = [ln for ln in directives if ln.startswith("#define ENGINE_SHB(")]
    if len(directives) != KNOWN_DIRECTIVES or len(shb) != 1:
        sys.exit(f"macro_to_header: engine_core.h carries {len(directives)} non-DEFINE directives (expected {KNOWN_DIRECTIVES}) — "
                 f"the prelude would not be provably complete (R32): {directives[:10]}")
    div = {n for n, c in twice.items() if c > 1 and n in DIVERGENT}
    if div != DIVERGENT:
        sys.exit(f"macro_to_header: the divergent-twin set changed: {sorted(div)} vs the known {sorted(DIVERGENT)} (R32)")
    for name, body in macros.items():
        if any(ln.endswith("\\") for ln in body):
            sys.exit(f"macro_to_header: {name}: a continuation survived the strip (R43)")
    return macros, dict(define_lines=count, distinct=len(macros), twice=sum(1 for c in twice.values() if c > 1), shb=shb[0])


def tokens(lines):
    return " ".join(" ".join(l.split()) for l in lines).split()


# ----------------------------------------------------------------------------------------------------------------------------
# the oracles: fleet, spaces, sigs, the collision map
# ----------------------------------------------------------------------------------------------------------------------------
class Oracles:
    def __init__(self):
        self.aliases, self.dirs = sc.fleet_and_dirs()
        self.bases = sc.vram_bases()
        self.sigs = {a: {addr: (h, nins) for addr, nins, h, _ in sc.sig_rows(a)} for a in self.aliases}
        self.by_space = collections.defaultdict(lambda: collections.defaultdict(set))    # (base, vram) -> {h}
        for a in self.aliases:
            b = self.bases[a]
            for addr, (h, _) in self.sigs[a].items():
                self.by_space[(b, addr)][h].add(a)
        self.instances = collections.Counter()                                          # h -> instances fleet-wide
        for a in self.aliases:
            for addr, (h, _) in self.sigs[a].items():
                self.instances[h] += 1

    def space_dir(self, base):
        if base == OV_BASE:
            return "ov"
        if base == self.bases["main"]:
            return "main"
        if base == self.bases["resident"]:
            return "resident"
        return f"slot_{base:08X}"

    def header_rel(self, base, vram, h):
        classes = self.by_space[(base, vram)]
        suffix = f"__{h[:8]}" if len(classes) > 1 else ""
        return f"src/shared/{self.space_dir(base)}/func_{vram:08X}{suffix}.h"

    def class_of(self, alias, vram):
        row = self.sigs[alias].get(vram)
        if row is None:
            sys.exit(f"macro_to_header: {alias}:0x{vram:08X} has no sig row — cannot key its class (R32)")
        return row[0]


def include_line(tu_rel, header_rel):
    tu_dir = os.path.dirname(tu_rel)
    rel = os.path.relpath(header_rel, tu_dir)
    return f'#include "{rel}"'


def banner(fn, base, h, space_name):
    return (f"/* {fn} — shared body ({space_name} 0x{base:08X}, h_exact {h[:8]}). ONE source: instantiated by #include at each\n"
            f" * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */\n")


def write_header(path, text, ledger):
    p = REPO / path
    if p.exists():
        old = p.read_text(errors="surrogateescape")
        if old != text:
            sys.exit(f"macro_to_header: {path} exists with DIFFERENT text — a collision the naming rule missed (R43)")
        return False
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(text)
    ledger["headers_written"] += 1
    return True


def prelude_text(shb_line):
    return ("/* src/shared/engine_prelude.h — Phase 35: what every overlay/module TU needs from the shared tree BEFORE its first shared\n"
            " * body: the shared engine types and the ENGINE_SHB barrier. It replaces the engine_core.h include (the bodies now live as\n"
            " * per-function headers under src/shared/<space>/, included at each member's site — sotn's shape). */\n"
            "#ifndef SHARED_ENGINE_PRELUDE_H\n#define SHARED_ENGINE_PRELUDE_H\n"
            '#include "common.h"\n#include "engine_types.h"\n'
            "#ifndef ENGINE_SHB\n" + shb_line + "\n#endif\n#endif\n")


# ----------------------------------------------------------------------------------------------------------------------------
# the site index
# ----------------------------------------------------------------------------------------------------------------------------
def site_index(orc, aliases):
    """{alias: [(tu_rel, lineno, fn, indent)]} + the set of TUs that include engine_core.h."""
    import compile_only
    sites, includers = {}, set()
    for a in aliases:
        if sc.twin_of_map().get(a):
            continue                                  # a twin has no TUs of its own
        per = []
        for p in compile_only.tus_of(a, orc.dirs):
            rel = p.relative_to(REPO).as_posix()
            text = p.read_text(errors="surrogateescape")
            if re.search(r'^#include "(\.\./)?shared/engine_core\.h"', text, re.M):
                includers.add(rel)
            masked = sc.mask_text(text)                   # comments blanked (a DEFINE_ mention in prose is not a site), lines kept
            for i, ln in enumerate(masked.split("\n"), 1):
                if "DEFINE_func_" not in ln:
                    continue
                m = SITE.match(ln)
                if m:
                    per.append((rel, i, m.group(2), m.group(1)))
                elif ln.lstrip().startswith("DEFINE_func_"):
                    sys.exit(f"macro_to_header: {rel}:{i}: unrecognized site shape (R43): {ln!r}")
        sites[a] = per
    return sites, includers


def plan(orc, macros):
    sites, includers = site_index(orc, orc.aliases)
    use = collections.defaultdict(list)             # macro -> [(alias, tu, line)]
    for a, per in sites.items():
        for rel, i, fn, _ in per:
            use["DEFINE_" + fn].append((a, rel, i))
    shared = {m: u for m, u in use.items() if len(u) >= 2}
    single = {m: u for m, u in use.items() if len(u) == 1}
    dead = sorted(m for m in macros if m not in use)
    missing = sorted(m for m in use if m not in macros)
    if missing:
        sys.exit(f"macro_to_header: {len(missing)} instantiated macro(s) have no definition: {missing[:5]} (R43)")
    single_header, single_inline = {}, {}
    for m, u in single.items():
        a, rel, i = u[0]
        vram = int(m[len("DEFINE_func_"):], 16)
        h = orc.class_of(a, vram)
        (single_header if orc.instances[h] >= 2 else single_inline)[m] = u
    return dict(sites=sites, includers=includers, shared=shared, single_header=single_header, single_inline=single_inline, dead=dead)


# ----------------------------------------------------------------------------------------------------------------------------
# apply
# ----------------------------------------------------------------------------------------------------------------------------
def apply(orc, macros, info, aliases, ledger, dry=False):
    pre = prelude_text(info["shb"])
    if not dry:
        if PRELUDE.exists() and PRELUDE.read_text() != pre:
            sys.exit("macro_to_header: engine_prelude.h exists with different text (R43)")
        PRELUDE.write_text(pre)
    pl = plan(orc, macros)
    inline_set = set(pl["single_inline"])
    for a in aliases:
        if a not in pl["sites"]:
            continue
        base = orc.bases[a]
        space_name = "overlay slot" if base == OV_BASE else "module slot" if orc.space_dir(base).startswith("slot_") else orc.space_dir(base)
        by_tu = collections.defaultdict(list)
        for rel, i, fn, indent in pl["sites"][a]:
            by_tu[rel].append((i, fn, indent))
        # this binary's TUs: under its source dir — for main (dir `src`) ONLY the top-level files, never everything beneath src/
        # (the first run swapped 3,818 includers from "main" and converted no site: a prefix test on `src/` matched the fleet)
        if a == "main":
            mine = {t for t in pl["includers"] if t.count("/") == 1}
        else:
            mine = {t for t in pl["includers"] if t.startswith(orc.dirs[a] + "/")}
        tus = set(by_tu) | mine
        for rel in sorted(tus):
            p = REPO / rel
            lines = p.read_text(errors="surrogateescape").split("\n")
            changed = 0
            for k, ln in enumerate(lines):
                if re.match(r'^#include "(\.\./)?shared/engine_core\.h"\s*$', ln):
                    lines[k] = include_line(rel, "src/shared/engine_prelude.h")
                    changed += 1
            for i, fn, indent in by_tu.get(rel, []):
                ln = lines[i - 1]
                if not SITE.match(ln) or SITE.match(ln).group(2) != fn:
                    sys.exit(f"macro_to_header: {rel}:{i} no longer holds the expected site for {fn} (R43)")
                mname = "DEFINE_" + fn
                vram = int(fn[5:], 16)
                h = orc.class_of(a, vram)
                body = macros[mname]
                if mname in inline_set:
                    lines[i - 1] = "\n".join(body)            # plain C at the site; nothing shared
                    ledger["inlined"] += 1
                else:
                    hdr = orc.header_rel(base, vram, h)
                    text = banner(fn, base, h, space_name) + "\n".join(body).rstrip("\n") + "\n"
                    if tokens(body) != tokens(text.split("\n")[2:]):
                        sys.exit(f"macro_to_header: {fn}: the header text does not carry the macro's tokens (R32)")
                    if not dry:
                        write_header(hdr, text, ledger)
                    lines[i - 1] = include_line(rel, hdr)
                    ledger["sites"] += 1
                changed += 1
            if changed and not dry:
                p.write_text("\n".join(lines))
            ledger["tus"] += 1 if changed else 0
    ledger["dead"] = len(pl["dead"])
    return pl


# ----------------------------------------------------------------------------------------------------------------------------
# finalize: the legacy headers, the whale, the registry, the deletion
# ----------------------------------------------------------------------------------------------------------------------------
SETTER_SITE = re.compile(r"^\s*SETTER\(\s*(func_[0-9A-Fa-f]{8})\s*,\s*([^,]+?)\s*,\s*([^)]+?)\s*\)\s*(/\*.*?\*/)?\s*$")
RETCONST_SITE = re.compile(r"^\s*RETCONST\(\s*(func_[0-9A-Fa-f]{8})\s*,\s*([^)]+?)\s*\)\s*(/\*.*?\*/)?\s*$")
CLEAR_SITE = re.compile(r"^\s*CLEAR_TBL40\(\s*(func_[0-9A-Fa-f]{8})\s*\)\s*(/\*.*?\*/)?\s*$")


def finalize(orc, ledger):
    import yaml
    import compile_only
    reg = REPO / "config/dedup.us.yaml"
    groups = yaml.safe_load(reg.read_text())["groups"]
    ginfo = {}
    for g in groups:
        bins = sorted({b for b, _, _ in sc_group_members(g)})
        vrams = sorted({v for _, v, _ in sc_group_members(g)})
        ginfo[g["id"]] = dict(hash=g["hash"], source=g["source"], func=g.get("func"), bins=bins, vrams=vrams)
    # 1. the legacy sites: SETTER/RETCONST (src/ov_SC01_005) and CLEAR_TBL40 (main)
    new_paths = {}                                    # group id -> (source rel, func token)
    for a in orc.aliases:
        if sc.twin_of_map().get(a):
            continue
        for p in compile_only.tus_of(a, orc.dirs):
            rel = p.relative_to(REPO).as_posix()
            text = p.read_text(errors="surrogateescape")
            if not any(k in text for k in ("SETTER(", "RETCONST(", "CLEAR_TBL40(", "shared/ov_setters.h", "shared/clearTbl40.h")):
                continue
            lines = text.split("\n")
            out, changed = [], 0
            for ln in lines:
                if re.match(r'^#include "(\.\./)?shared/(ov_setters|clearTbl40)\.h"', ln):
                    changed += 1
                    continue                          # the macro header include goes; the bodies arrive at their sites
                m = SETTER_SITE.match(ln)
                if m:
                    fn, off, ty = m.group(1), m.group(2), m.group(3)
                    vram = int(fn[5:], 16); h = orc.class_of(a, vram); base = orc.bases[a]
                    body = [f"void {fn}(void *p, {ty} v) {{", f"    *({ty} *)((s32)p + ({off})) = v;", "}"]
                    hdr = orc.header_rel(base, vram, h)
                    write_header(hdr, banner(fn, base, h, "overlay slot") + "\n".join(body) + "\n", ledger)
                    out.append(include_line(rel, hdr)); changed += 1; ledger["legacy_sites"] += 1
                    for gid, gi in ginfo.items():
                        if gi["source"].endswith("ov_setters.h") and vram in gi["vrams"]:
                            new_paths[gid] = (hdr, fn)
                    continue
                m = RETCONST_SITE.match(ln)
                if m:
                    fn, val = m.group(1), m.group(2)
                    vram = int(fn[5:], 16); h = orc.class_of(a, vram); base = orc.bases[a]
                    body = [f"s32 {fn}(void) {{", f"    return ({val});", "}"]
                    hdr = orc.header_rel(base, vram, h)
                    write_header(hdr, banner(fn, base, h, "overlay slot") + "\n".join(body) + "\n", ledger)
                    out.append(include_line(rel, hdr)); changed += 1; ledger["legacy_sites"] += 1
                    for gid, gi in ginfo.items():
                        if gi["source"].endswith("ov_setters.h") and vram in gi["vrams"]:
                            new_paths[gid] = (hdr, fn)
                    continue
                m = CLEAR_SITE.match(ln)
                if m:
                    fn = m.group(1); vram = int(fn[5:], 16); h = orc.class_of(a, vram); base = orc.bases[a]
                    gi = ginfo["I0_clearTbl40"]
                    hdr = orc.header_rel(base, min(gi["vrams"]), h)           # one header for the pair, keyed by the class
                    body = ["extern u8 D_80076251;", "", "void SHARED_FN(void) {", "    s32 i;",
                            "    for (i = 0x40; i >= 0; i -= 0x10) {", "        (&D_80076251)[i] = 0;", "    }", "}"]
                    write_header(hdr, (f"/* the clearTbl40 pair — ONE body at two addresses of main (h_exact {h[:8]}): the name-parameterized\n"
                                       f" * include form — the site defines SHARED_FN, includes this, undefines it (Phase 35; the worked example\n"
                                       f" * for the deferred cross-address classes). Members: config/dedup.us.yaml I0_clearTbl40. */\n")
                                 + "\n".join(body) + "\n", ledger)
                    out.append(f"#define SHARED_FN {fn}"); out.append(include_line(rel, hdr)); out.append("#undef SHARED_FN")
                    changed += 1; ledger["legacy_sites"] += 1
                    new_paths["I0_clearTbl40"] = (hdr, "SHARED_FN")
                    continue
                out.append(ln)
            if changed:
                p.write_text("\n".join(out))
    # 2. the whale: src/shared/func_80144B9C.h -> src/shared/ov/func_80144B9C.h (guard removed), its includers rewritten
    old = REPO / "src/shared/func_80144B9C.h"
    if old.exists():
        h = orc.class_of("ov_SC01_077", 0x80144B9C)
        hdr = orc.header_rel(OV_BASE, 0x80144B9C, h)
        text = old.read_text(errors="surrogateescape")
        text = re.sub(r"^#ifndef func_80144B9C_H\n#define func_80144B9C_H\n", "", text, count=1, flags=re.M)
        text = re.sub(r"\n#endif[^\n]*\n?\s*$", "\n", text, count=1)
        (REPO / hdr).parent.mkdir(parents=True, exist_ok=True)
        (REPO / hdr).write_text(text)
        subprocess.run(["git", "rm", "-q", "--cached", str(old.relative_to(REPO))], cwd=REPO, check=False)
        old.unlink()
        n = 0
        for p in REPO.glob("src/*/*_o0b.c"):
            rel = p.relative_to(REPO).as_posix()
            t = p.read_text(errors="surrogateescape")
            t2 = t.replace('#include "../shared/func_80144B9C.h"', include_line(rel, hdr))
            if t2 != t:
                p.write_text(t2); n += 1
        ledger["whale_includers"] = n
        new_paths["E_func_80144B9C"] = (hdr, "func_80144B9C")
    # 3. the registry: source/func for every engine_core group, the legacy groups, the whale
    for gid, gi in ginfo.items():
        if gi["source"].endswith("engine_core.h"):
            fn = gi["func"]
            if not fn.startswith("DEFINE_"):
                sys.exit(f"macro_to_header: {gid}: an engine_core group whose func is not a DEFINE_ macro: {fn} (R43)")
            fn = fn[len("DEFINE_"):]
            bases = {orc.bases[b] for b in gi["bins"]}
            if len(bases) != 1 or len(gi["vrams"]) != 1:
                sys.exit(f"macro_to_header: {gid}: members span {len(bases)} spaces / {len(gi['vrams'])} vrams — not the position-locked form (R43)")
            new_paths[gid] = (orc.header_rel(bases.pop(), gi["vrams"][0], gi["hash"]), fn)
    lines = reg.read_text().split("\n")
    cur, n = None, 0
    for k, ln in enumerate(lines):
        m = re.match(r"^\s*-\s*id:\s*(\S+)\s*$", ln)
        if m:
            cur = m.group(1); continue
        if cur in new_paths:
            hdr, fn = new_paths[cur]
            if re.match(r"^\s*source:\s", ln):
                lines[k] = re.sub(r"(source:\s*)\S+", lambda mm: mm.group(1) + hdr, ln); n += 1
            elif re.match(r"^\s*func:\s", ln):
                lines[k] = re.sub(r"(func:\s*)\S+", lambda mm: mm.group(1) + fn, ln); n += 1
    reg.write_text("\n".join(lines))
    ledger["registry_lines"] = n
    # every rewritten source must DEFINE its func (C2a′)
    for gid, (hdr, fn) in new_paths.items():
        defined = {nm for nm, _ in sc.header_defs(REPO / hdr)}
        if fn not in defined:
            sys.exit(f"macro_to_header: {gid}: {hdr} does not define {fn} (defines {sorted(defined)[:3]}) (R32)")
    # 3b. non-shared headers that include a macro header (src/800_shared.h -> clearTbl40.h; two per-overlay _shared.h ->
    #     engine_core.h): the engine_core include becomes the prelude include, the legacy includes go (both carry no code)
    for p in sorted(REPO.glob("src/**/*.h")):
        rel = p.relative_to(REPO).as_posix()
        if rel.startswith("src/shared/"):
            continue
        t = p.read_text(errors="surrogateescape")
        lines, out, changed = t.split("\n"), [], 0
        for ln in lines:
            if re.match(r'^#include "(\.\./)?shared/engine_core\.h"', ln):
                out.append(include_line(rel, "src/shared/engine_prelude.h")); changed += 1
            elif re.match(r'^#include "(\.\./)?shared/(ov_setters|clearTbl40)\.h"', ln):
                changed += 1
            else:
                out.append(ln)
        if changed:
            p.write_text("\n".join(out)); ledger["aux_headers"] += 1
    # 4. the macro headers go
    for rel in ("src/shared/engine_core.h", "src/shared/ov_setters.h", "src/shared/clearTbl40.h"):
        p = REPO / rel
        if p.exists():
            subprocess.run(["git", "rm", "-q", "--cached", rel], cwd=REPO, check=False)
            p.unlink(); ledger["deleted"] += 1


def sc_group_members(g):
    from dedup_integrate import group_members
    return list(group_members(g))


# ----------------------------------------------------------------------------------------------------------------------------
def verify(orc):
    bad = []
    for pat in (r"^\s*DEFINE_func_[0-9A-Fa-f]{8}\(\)", r"^\s*(SETTER|RETCONST|CLEAR_TBL40)\("):
        r = subprocess.run(["git", "grep", "-lP", pat, "--", "src"], cwd=REPO, capture_output=True, text=True)
        if r.stdout.strip():
            bad.append(f"macro sites remain ({pat}): {r.stdout.split()[:3]}")
    for rel in ("src/shared/engine_core.h", "src/shared/ov_setters.h", "src/shared/clearTbl40.h", "src/shared/func_80144B9C.h"):
        if (REPO / rel).exists():
            bad.append(f"{rel} still exists")
    if not PRELUDE.exists():
        bad.append("engine_prelude.h missing")
    r = subprocess.run(["git", "grep", "-l", "shared/engine_core.h", "--", "src"], cwd=REPO, capture_output=True, text=True)
    if r.stdout.strip():
        bad.append(f"TUs still include engine_core.h: {r.stdout.split()[:3]}")
    for b in bad:
        print("verify: FAIL —", b)
    print("verify: OK — 0 macro sites, no macro header, the prelude present" if not bad else f"verify: {len(bad)} failure(s)")
    return not bad


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--plan", action="store_true")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--binaries", default="")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--finalize", action="store_true")
    ap.add_argument("--verify", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--ledger", default=".run/P35/convert/ledger.json")
    a = ap.parse_args()
    orc = Oracles()
    if a.verify:
        sys.exit(0 if verify(orc) else 1)
    ledger = collections.Counter()
    if a.finalize:
        finalize(orc, ledger)
        print("finalize:", dict(ledger))
        (REPO / a.ledger).parent.mkdir(parents=True, exist_ok=True)
        (REPO / a.ledger).write_text(json.dumps(dict(ledger), indent=1) + "\n")
        return
    macros, info = parse_header()
    print(f"engine_core.h: {info['define_lines']} define lines, {info['distinct']} distinct, {info['twice']} twice (4 divergent asserted); "
          f"{KNOWN_DIRECTIVES} directives — the prelude is complete")
    pl = plan(orc, macros)
    nsites = sum(len(v) for v in pl["sites"].values())
    print(f"sites {nsites:,} in {sum(1 for v in pl['sites'].values() if v)} binaries · TUs including engine_core.h {len(pl['includers']):,} · "
          f"macros: shared {len(pl['shared']):,} · single-site→header {len(pl['single_header'])} · single-site→inline {len(pl['single_inline'])} · "
          f"dead {len(pl['dead']):,}")
    if a.plan:
        names = collections.Counter()
        for m in pl["shared"]:
            alias, rel, i = pl["shared"][m][0]
            vram = int(m[len("DEFINE_func_"):], 16)
            names["suffixed" if "__" in orc.header_rel(orc.bases[alias], vram, orc.class_of(alias, vram)) else "plain"] += 1
        print(f"naming of the shared headers: {dict(names)}; dead (first 10): {pl['dead'][:10]}")
        return
    if a.apply:
        aliases = orc.aliases if a.all else [x for x in a.binaries.split(",") if x]
        unknown = [x for x in aliases if x not in orc.aliases]
        if unknown:
            sys.exit(f"macro_to_header: unknown binaries {unknown} (R43)")
        apply(orc, macros, info, aliases, ledger, dry=a.dry_run)
        print(("dry-run " if a.dry_run else "") + "apply:", dict(ledger))
        (REPO / a.ledger).parent.mkdir(parents=True, exist_ok=True)
        (REPO / a.ledger).write_text(json.dumps(dict(ledger), indent=1) + "\n")


if __name__ == "__main__":
    main()
