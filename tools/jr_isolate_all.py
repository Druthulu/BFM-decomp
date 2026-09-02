#!/usr/bin/env python3
"""Phase-26 §8b: isolate every jr (switch) function in an overlay into its OWN code
subseg — the one-shot multi-cut resegment that unblocks the Stage-2 heavy-jr-core
harvest (each isolated jr carves its jtbl independently, so banking any core is a
clean fill with no same-subseg collision; cookbook §8/§8b, the whale `_o0b` precedent
generalized).

For each -O2 code object that contains jr-functions, the object is cut right BEFORE
each jr vram:  [gap0][jr1 + trailing non-jr][jr2 + ...] ...  . The leading gap keeps
the object's name; each jr-led region becomes `<ov>_jr_<addr>`. Source is repartitioned
(overlay_src_split, H5) and INCLUDE_ASM stub paths repointed to the new subseg. The 2
already-banked jr (their real-C is PRESERVED) have their `.rodata` carve repointed to
their new `_jr_<addr>` subseg (config piece + overlays.mk --order) — no un-banking, no
metric churn. -O0 objects (`*_o0`, `*_o0b`) are skipped (their new subsegs would lose
the Makefile -O0 flag; the heavy Stage-2 cores are all -O2).

Byte-neutral by construction: the split only reorganizes .text into more objects placed
contiguously in address order (the existing -O0 multi-object precedent), and the carve
bytes are unchanged (only the owning object's NAME changes). `make build` (SHA1) is the
sole arbiter (G3/P9/R22).

    jr_isolate_all.py <ov> [--only func_X,func_Y] [--dry-run]
"""
import collections
import argparse
import glob
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import overlay_src_split as oss
import mk_write as MKW    # atomic, collapse-refusing overlays.mk writer (P31 S60)

REPO = oss.REPO
O0_SUFFIX = ("_o0", "_o0b")


def sh(cmd):
    return subprocess.run(cmd, shell=True, cwd=REPO, capture_output=True, text=True)


def oss_vram(ov):
    txt = open(os.path.join(REPO, f"config/splat.{ov}.yaml")).read()
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", txt)
    if not m:
        sys.exit(f"jr_isolate_all: no vram in config for {ov}")
    return int(m.group(1), 16)


def code_objects(cfg_lines):
    """[(line_idx, indent, off, name)] for every `- [off, c, name]` code piece, in order."""
    objs = []
    for i, ln in enumerate(cfg_lines):
        m = re.match(r'^(\s*)- \[(0x[0-9A-Fa-f]+),\s*c,\s*(\w+)\]', ln)
        if m:
            objs.append((i, m.group(1), int(m.group(2), 16), m.group(3)))
    return objs


def rodata_carves(cfg_lines, ov=None):
    """[(line_idx, off, subseg)] for every `.rodata` CARVE piece.

    A carve is a jump table jtbl_carve.py lifted out of the data tail so its owning object can
    emit it. The §154-A LEADING ISLAND — `- [0x0, .rodata, <alias>]`, the module's own rodata blob
    of INCLUDE_RODATA data plus every stub's still-migrated table — is NOT one: it has no single
    owner, so jr_inventory's "every carve resolves to exactly one banked function" check (R32)
    aborted on it and md_* could not be isolated at all.

    The discriminator is structural: a carve is a table LIFTED OUT OF THE DATA TAIL, so it can
    never sit at the segment's own offset 0 — offset 0 is where the module-id header (md_*) or the
    first function (ov_*) lives. Verified across all 213 splat configs: every `.rodata` piece at
    offset 0 is an md_* leading island; ov_*/main configs have none, so passing `ov` is a no-op
    for them. The discriminator used to ALSO require the subseg to be the binary's own alias, but
    that conjunct broke the moment a leading island was legitimately RENAMED to the code subseg
    where its emitters live (S68 md_MAIN_003 → md_MAIN_003_jr_800D12D0: spimdisasm rodata-migration
    is same-subseg-only, cookbook §371), which made jr_inventory read the island as an UNOWNED
    carve and R32-abort every further carve on the binary. Offset 0 alone is the honest key;
    negative-controlled over all 184 configs with `.rodata` pieces (only md_MAIN_003's verdict
    moved, abort → OK)."""
    out = []
    for i, ln in enumerate(cfg_lines):
        m = re.match(r'^\s*- \[(0x[0-9A-Fa-f]+),\s*\.rodata,\s*(\w+)\]', ln)
        if m:
            off, sub = int(m.group(1), 16), m.group(2)
            if ov is not None and off == 0:
                continue                                   # the leading island (possibly renamed), not a carve
            out.append((i, off, sub))
    return out


def jr_inventory(ov):
    """Return (all_jr:{vram:src_kind}, banked:{vram:func_name}). src_kind in {'asm','banked'}.

    jr = still-unmatched switch functions (INCLUDE_ASM `.s` referencing a jtbl_) + the
    already-banked jr (whose jtbl became a committed `.rodata` carve).

    `banked` is DERIVED FROM THE IMAGE — never from a roster (R33). The old code filtered
    real-C defs by an EPHEMERAL, gitignored `.run/banked_func_*.json` set: a `rm -rf .run`
    / fresh clone made all banked jr invisible at once, and a cross-address sibling (whose
    roster file is named after the exemplar) was structurally missing. Two proven invariants
    answer it instead: (1) the committed splat config lists every `.rodata` carve; (2) a
    real-C function OWNS a carve iff it references that carve's address — `family_remap.
    reloc_targets` reads the extracted image and says so. So a real-C def/define fn is a
    banked jr iff it references a committed carve offset. Cross-address- and
    curated-name-immune, and it finds NON-LEADER banked jr (carve in the object's own
    subseg, not a `_jr_` leader) that a subseg-name model would miss. Every carve MUST
    resolve to exactly one owner or the run aborts (R32) — a stranded/duplicated carve is
    the func_801734BC incident (§8b) and must never be silent.

    Cost: ~6s -> ~0.1s by reading the overlay image ONCE and passing it to reloc_targets."""
    import family_remap
    base = oss_vram(ov)
    syms = oss.load_ov_syms(ov)

    # still-unmatched jr: an INCLUDE_ASM fn whose .s references a jtbl_. Resolve the .s
    # basename through the symbol table (addr_of) so a CURATED name (e.g. listCdBuffer) is
    # not dropped by a func_-shape fullmatch (§26-A LOW finding).
    asm_jr = {}
    for p in glob.glob(os.path.join(REPO, f"asm/{ov}/nonmatchings/*/*.s")):
        if re.search(r'jtbl_[0-9A-Fa-f]{8}', open(p).read()):
            nm = os.path.basename(p)[:-2]
            a = oss.addr_of(nm, syms)
            if a is not None:
                asm_jr[a] = nm

    # already-banked jr: every real-C def/define fn that references a committed carve
    # offset in the IMAGE (read once, passed to reloc_targets).
    cfg_lines = open(os.path.join(REPO, f"config/splat.{ov}.yaml")).read().splitlines()
    carve_offs = {off for _li, off, _sub in rodata_carves(cfg_lines, ov)}
    img = open(family_remap.img_path(ov), "rb").read()
    banked, owners = {}, {}                              # owners: carve_off -> [names]
    for cf in glob.glob(os.path.join(REPO, f"src/{ov}/*.c")):
        _, items = oss.parse_overlay_c(open(cf).read(), syms)
        for addr, name, kind, _ in items:
            if kind not in ("def", "define") or not name or addr is None:
                continue
            try:
                targets = family_remap.reloc_targets(ov, addr, data=img)
            except Exception:
                continue
            hits = {t - base for k, t in targets if k == "data" and (t - base) in carve_offs}
            if hits:
                banked[addr] = name
                for off in hits:
                    owners.setdefault(off, []).append(name)

    # R32: every committed carve resolves to EXACTLY ONE owner, or abort loud.
    #
    # OWNERSHIP HAS TWO MORE SOURCES THAN THE RELOC SCAN ABOVE (P31 S70). The scan finds an owner
    # only among the overlay's OWN real-C definitions, and it was aborting on 36 carves across 8
    # binaries — every one of which is BYTE-GREEN (R22 213/213), i.e. the config is right and the
    # MODEL was blind (R34). The two blind spots, measured:
    #
    #   1. THE SUBSEG NAME IS THE OWNERSHIP RECORD (32 of 36 = 89%). The isolate convention writes
    #      the owner into the name: a carve in `<ov>_jr_<ADDR>` belongs to `func_<ADDR>`. Several of
    #      those owners are RESIDENT-range functions (0x80135D20, 0x8015C32C …) instantiated in the
    #      overlay through a shared macro, so they are not overlay-local definitions and
    #      `parse_overlay_c` cannot see them at all. Reading the name is R33 — derive from the
    #      invariant instead of re-deriving it by scanning relocations.
    #   2. A CARVE FOR A STILL-STUBBED FUNCTION IS PENDING, NOT STRANDED (the remaining 4). The
    #      carve is committed and the function has simply not banked yet; `func_8016AB6C` in
    #      ov_SC07_010 references its carve at 0x801A6460 from an INCLUDE_ASM stub.
    #
    # A carve with NONE of the three is still a hard abort — that is the real corruption this
    # assertion exists to catch (§8b func_801734BC class).
    _named = re.compile(r"^%s_jr_([0-9A-Fa-f]{8})$" % re.escape(ov))
    named_owner = {off for _li, off, sub in rodata_carves(cfg_lines, ov)
                   if _named.match(str(sub or ""))}
    pending = set()
    try:
        import corpus as _corpus
        _stub_addrs = list(_corpus.stubs(ov))
    except Exception:
        _stub_addrs = []          # the stub oracle refusing is not this assertion's business
    for _a in _stub_addrs:
        try:
            _t = family_remap.reloc_targets(ov, int(_a), data=img)
        except Exception:
            continue
        pending |= {x - base for k, x in _t if k == "data" and (x - base) in carve_offs}
    accounted = set(owners) | named_owner | pending
    problems = [("UNOWNED", hex(base + o)) for o in sorted(carve_offs - accounted)]
    problems += [("MULTI", hex(base + o), owners[o]) for o in sorted(owners) if len(owners[o]) > 1]
    if problems:
        sys.exit(f"jr_inventory({ov}): committed .rodata carve ownership is not 1:1 (R32/R33) — "
                 f"a stranded/duplicated carve (§8b func_801734BC class): {problems}")

    alljr = dict(asm_jr)
    alljr.update({a: "banked" for a in banked})         # marker; name in `banked`
    return alljr, banked


def plan(ov, only=None):
    """Compute the resegment plan without touching disk. Returns a dict."""
    base = oss_vram(ov)
    cfg_lines = open(os.path.join(REPO, f"config/splat.{ov}.yaml")).read().splitlines()
    objs = code_objects(cfg_lines)
    obj_ranges = []                                    # (start_vram, end_vram, name, line_idx, indent)
    for k, (li, ind, off, nm) in enumerate(objs):
        end = objs[k + 1][2] if k + 1 < len(objs) else None
        obj_ranges.append((base + off, (base + end) if end is not None else None, nm, li, ind))

    def obj_of(vram):
        for s, e, nm, li, ind in obj_ranges:
            if s <= vram and (e is None or vram < e):
                return nm
        return None

    alljr, banked = jr_inventory(ov)
    if only:
        only_addrs = {int(x[5:], 16) for x in only if re.fullmatch(r'func_[0-9A-Fa-f]{8}', x)}
        # A region may host AT MOST ONE `.rodata` carve, because an object's `.rodata` is a single
        # CONTIGUOUS section. So every ALREADY-BANKED jr in an object we are cutting must be cut too:
        # otherwise it shares a region with the new core, and that one object has to emit both jump
        # tables — which sit far apart in the island — into one `.rodata`. Byte-proven: isolating
        # func_8015AE2C (jtbl 0x801D8B54) alone left the banked func_801734BC (jtbl 0x801D8C68) inside
        # its region, and the object emitted a 0x34 `.rodata` spanning BOTH tables (image +33 B).
        # Cutting at each banked jr gives every one its own region → exactly one carve per object.
        # (This is what cookbook §8b's "bank same-subseg families ASCENDING" note was warning about;
        # it is now enforced by construction rather than left to discipline.)
        touched = {obj_of(a) for a in only_addrs}
        only_addrs |= {a for a in banked if obj_of(a) in touched}
        alljr = {a: v for a, v in alljr.items() if a in only_addrs}
        # NB `banked` itself is deliberately NOT filtered — every banked carve must stay trackable.

    # group jr by their -O2 object (skip -O0 objects + objects with no jr)
    skipped_o0 = []
    per_obj = {}
    for a in sorted(alljr):
        nm = obj_of(a)
        if nm is None:
            continue
        if nm.endswith(O0_SUFFIX):
            skipped_o0.append(a)
            continue
        per_obj.setdefault(nm, []).append(a)

    # banked jr -> its object (for carve repoint)
    banked_obj = {banked[a]: obj_of(a) for a in banked}
    return {
        "base": base, "cfg_lines": cfg_lines, "obj_ranges": obj_ranges,
        "per_obj": per_obj, "banked": banked, "banked_obj": banked_obj,
        "skipped_o0": skipped_o0,
    }


def subseg_name(ov, vram):
    return f"{ov}_jr_{vram:08X}"          # uppercase hex, matching the func_XXXXXXXX convention


def carve_owners(ov, banked, base, carve_offs):
    """{carve_offset: func_name} — which already-banked jr owns each existing `.rodata` carve.

    Resolved from the EXTRACTED IMAGE (`family_remap.reloc_targets` reads each function's lui/%lo
    address operands), NOT from splat `.s`: splat emits **no `.s` for a MATCHED function** (its `.c`
    carries real C), so an asm scan finds nothing and every banked carve silently goes untracked —
    which is precisely how func_801734BC's carve got stranded. A banked jr owns a carve iff it
    references that carve's address."""
    import family_remap
    owners = {}
    for addr, fn in banked.items():
        try:
            targets = family_remap.reloc_targets(ov, addr)
        except Exception:
            continue
        for kind, t in targets:
            if kind == "data" and (t - base) in carve_offs:
                owners[t - base] = fn
    return owners


def build_new_config(ov, p):
    """Return (new_cfg_lines, new_files:{path:content}, carve_renames:{old_sub:new_sub})."""
    base = p["base"]
    cfg_lines = list(p["cfg_lines"])
    syms = oss.load_ov_syms(ov)

    # 1) source repartition + the config code-region replacement (per object, bottom-up so
    #    line indices stay valid).
    new_files = {}
    replacements = []            # (line_idx, [new config lines])
    carve_moves = {}             # carve OFFSET (jtbl vram - base) -> the subseg that now hosts its fn
    carve_renames = {}           # old code-subseg -> new subseg (derived; for the overlays.mk --order)
    carve_offs = {int(m.group(1), 16) for m in
                  (re.match(r'^\s*- \[(0x[0-9A-Fa-f]+),\s*\.rodata,\s*\w+\]', ln) for ln in cfg_lines)
                  if m}
    owners = carve_owners(ov, p["banked"], base, carve_offs)      # {carve_off: fn}
    fn_carves = {}
    for _off, _fn in owners.items():
        fn_carves.setdefault(_fn, []).append(_off)
    banked_by_obj = {}
    for fn, obj in p["banked_obj"].items():
        banked_by_obj.setdefault(obj, []).append(fn)

    for s, e, nm, li, ind in p["obj_ranges"]:
        if nm not in p["per_obj"]:
            continue
        cuts = p["per_obj"][nm]                                # jr vrams in this object
        # A jr function that IS the object's first function (the object is already named after it,
        # e.g. ov_SC06_029_jr_8017C954) yields a cut at the object start -> an empty region 0 at the
        # same offset -> "code subseg … out of order" at config time (P31 S62). Such a cut is a no-op.
        cuts = [c for c in cuts if c != s]
        if not cuts:
            continue
        srcpath = os.path.join(REPO, f"src/{ov}/{nm}.c")
        header, regions = _partition(srcpath, cuts, syms)
        # region 0 (lo=None) keeps the object name; each jr-led region -> _jr_<lo>. Regions are
        # processed in address order, accumulating this object's file-scope decls as `ambient` so
        # each region carries the decl context it had in the original single object.
        cfg_block = []
        ambient = []
        for (lo, hi, items) in regions:
            # EMPTY region 0: the object's first item IS the first cut (an already-isolated region
            # whose leading jr is being cut again, e.g. cutting func_80178D40 out of
            # ov_SC01_000_jr_801734BC — the leader 0x801734BC is a cut too, per the banked-jr rule).
            # Emitting it would duplicate region 1's line exactly (same offset, and subseg_name(lo)
            # == nm when the object is already named _jr_<leader>) → splat "segments out of order".
            if lo is None and not items:
                continue
            sub = nm if lo is None else subseg_name(ov, lo)
            off = (s if lo is None else lo) - base
            cfg_block.append(f"{ind}- [{hex(off)}, c, {sub}]")
            body = _render_region(header, items, old_sub=nm, new_sub=sub, ambient=ambient,
                                  syms=syms, obj_start=s)
            new_files[os.path.join(REPO, f"src/{ov}/{sub}.c")] = body
            ambient = ambient + _file_scope_decls(items)      # context for later regions
            # EVERY already-banked jr that now falls in this region must have its `.rodata` carve
            # repointed to `sub` — not just one that LEADS it. A cut placed BELOW an already-banked jr
            # MOVES that jr into the new region, so its C-emitted jump table is linked into the new
            # object while the config still names the old subseg → the carve piece under-fills and every
            # later symbol shifts (byte-proven: isolating func_8015AE2C at 0x8015AE2C moved the banked
            # func_801734BC @0x801734BC, whose 20-B table then landed in the new object's .rodata,
            # bloating it 0x1C→0x34 and lengthening the image). This stayed hidden because both earlier
            # single-core isolations cut ABOVE func_801734BC, and the full isolate-all gave every jr its
            # own leading region. Carves are keyed by OFFSET (the jtbl vram), since two banked jr of one
            # object can now land in DIFFERENT regions. (Cookbook §8b's "bank ASCENDING" note is exactly
            # this hazard — now handled instead of merely warned about.)
            for fn in banked_by_obj.get(nm, []):
                a = int(fn[len("func_"):], 16)
                if (lo is None or a >= lo) and (hi is None or a < hi):
                    for _o in fn_carves.get(fn, []):
                        carve_moves[_o] = sub
        replacements.append((li, cfg_block))

    # apply config code-region replacements bottom-up
    for li, block in sorted(replacements, reverse=True):
        cfg_lines[li:li + 1] = block

    # 2) repoint each .rodata carve piece — matched by OFFSET, not by subseg name, because two banked
    #    jr of one object can now land in DIFFERENT regions.
    for i, ln in enumerate(cfg_lines):
        m = re.match(r'^(\s*- \[)(0x[0-9A-Fa-f]+)(,\s*\.rodata,\s*)(\w+)(\].*)$', ln)
        if not m:
            continue
        off, cur = int(m.group(2), 16), m.group(4)
        new = carve_moves.get(off)
        if new and new != cur:
            carve_renames[cur] = new          # for the overlays.mk --order (jtbl_carve re-emits it anyway)
            cfg_lines[i] = m.group(1) + m.group(2) + m.group(3) + new + m.group(5)

    return cfg_lines, new_files, carve_renames


def _partition(srcpath, cuts, syms):
    """overlay_src_split.partition but taking a preloaded syms dict."""
    header, items = oss.parse_overlay_c(open(srcpath).read(), syms)
    # A trailing chunk with real content (kind="tail") is unaddressable only POSITIONALLY —
    # no anchor follows it for the parser to attach it to. Its content still HAS addresses:
    # a §265 verbatim `__asm__` body names its symbol in `.globl`/`.ent`, and
    # INCLUDE_ASM/INCLUDE_RODATA name theirs. When every symbol the chunk DEFINES resolves
    # at/after the LAST cut, the chunk belongs — in file order and address order alike — at
    # the end of the LAST region, exactly where the split leaves it; attaching it there
    # preserves per-region file order and is byte-neutral by the same argument as the split
    # itself. Anything else keeps the hard refusal (R32 spirit: never rewrite a TU minus
    # content you cannot place). First hit: md_MAIN_003's trailing verbatim-asm pair
    # func_800D3204/func_800D3234 blocking the 0x800D0D6C -O0 carve (P31 S68).
    tail = [it for it in items if it[0] is None and it[2] == "tail"]
    if tail:
        last_cut = max(cuts) if cuts else None
        for it in tail:
            # .globl/.ent live inside C string literals, so the separator can be a literal
            # two-char escape (`\t`, `\n`) or a quote boundary, not just whitespace.
            defined = set(re.findall(
                r'\.(?:globl|ent)(?:\s|\\[nt]|")+([A-Za-z_]\w*)', it[3])) | \
                set(re.findall(r'INCLUDE_(?:ASM|RODATA)\("[^"]*",\s*(\w+)\)', it[3]))
            addrs = {nm: oss.addr_of(nm, syms) for nm in defined}
            bad = sorted(nm for nm, a in addrs.items()
                         if a is None or last_cut is None or a < last_cut)
            if not defined or bad:
                sys.exit(f"jr_isolate_all: unaddressable content in {srcpath} — trailing "
                         f"chunk defines {bad if defined else '(nothing resolvable)'} "
                         f"which does not resolve at/after the last cut "
                         f"({hex(last_cut) if last_cut is not None else None}); refusing "
                         f"to attach it to the last region (R32)")
    footer = [it for it in items if it[2] == "footer"]
    # R32 COVERAGE — the same guard as overlay_src_split.partition, and for the same reason:
    # `addressed` silently discards any construct whose vram did not resolve, so this function
    # rewrote the TU WITHOUT it. Measured P30 S38: one carve of ov_SC02_028 deleted the two
    # definition-side asm-label-alias definitions emitting func_80183AF8 and func_80184268 (their
    # C identifiers are aF*, which matched neither `func_<hex>` nor `syms`), and the overlay then
    # failed to link. Six wave-6 drafts were written off against that. Fail loud instead.
    lost = [it for it in items if it[0] is None and it[2] not in ("tail", "footer")]
    # FILE-LOCAL `static` DEFINITIONS HAVE NO ADDRESS BY CONSTRUCTION, AND THAT IS NOT A DEFECT
    # (P31 S71). A `static inline` helper (§82.1) emits NOTHING of its own — it exists to shape the
    # code of the function that calls it — so it carries no symbol and `addr_of` cannot resolve it.
    # The R32 guard above is right to refuse an UNPLACEABLE construct, but it was refusing these
    # too, which blocked the isolate on 4 of the 6 overlays whose CARVE-REFUSED functions the
    # isolate is the named remedy for (`bandsetup` on ov_SC03_010/013/092, `setup_80188D90` on
    # ov_SC06_029). Place them instead: a file-local definition belongs with the region that USES
    # it, and if two regions use it we REFUSE rather than duplicate (two copies of a used static
    # are two different objects' code — a byte change, R43).
    local_defs, unplaceable = [], []
    for it in lost:
        if (it[2] == "def" and it[1]
                and re.search(r'^\s*static\b[^;{]*\b%s\b' % re.escape(it[1]),
                              it[3] or '', re.M)):
            local_defs.append(it)
        else:
            unplaceable.append(it)
    if unplaceable:
        sys.exit(f"jr_isolate_all: {srcpath} has {len(unplaceable)} construct(s) with no resolvable "
                 f"address — refusing to rewrite the file without them (R32):\n" +
                 "\n".join(f"  kind={it[2]} name={it[1]} :: {it[3].strip()[:110]}"
                            for it in unplaceable[:6]))
    addressed = [it for it in items if it[0] is not None]
    cuts = sorted(set(cuts))
    bounds = [None] + cuts + [None]
    regions = []
    for lo, hi in zip(bounds[:-1], bounds[1:]):
        sel = sorted((it for it in addressed
                      if (lo is None or it[0] >= lo) and (hi is None or it[0] < hi)),
                     key=lambda it: it[0])
        regions.append((lo, hi, sel))
    if tail or footer:                  # tail = guarded last-region content (see above);
        lo, hi, sel = regions[-1]       # footer = comment/blank-only trailing chunk
        regions[-1] = (lo, hi, sel + tail + footer)
    # Place each file-local `static` definition with the ONE region that references it.
    for it in local_defs:
        name = it[1]
        users = [i for i, (lo, hi, sel) in enumerate(regions)
                 if any(re.search(r'\b%s\b' % re.escape(name), o[3] or '') for o in sel
                        if o is not it)]
        if len(users) > 1:
            sys.exit(f"jr_isolate_all: file-local {name!r} is used by {len(users)} of the new "
                     f"regions; carrying it into each would emit two copies of the same static "
                     f"(a byte change). Isolate a different jr-function, or hoist {name!r} to a "
                     f"shared header first (R43).")
        idx = users[0] if users else 0
        lo, hi, sel = regions[idx]
        # the definition must precede its callers inside the region (C89 needs the declaration)
        regions[idx] = (lo, hi, [it] + sel)
    return header, regions


# a hoistable declaration line: an `extern` decl, or a func/data prototype ending in `;`
# with no `{` body. These are legal to REPEAT in C (unlike typedef/struct/enum), so we hoist a
# deduped copy to the region top — every symbol is then declared before any body uses it (a cut can
# strand a use above its in-region decl; the source redundantly re-declares externs per fn-group).
_HOIST_RE = re.compile(
    r'^\s*(?:extern\b.*;'
    r'|[A-Za-z_][\w\*\s]*\b(?:func_[0-9A-Fa-f]{8}|D_[0-9A-Fa-f]{8})\b[^{]*;)\s*(?:/\*.*\*/)?\s*$')


# a col-0 decl whose base type is a BUILTIN / include-provided type is safe to hoist as-is; one
# naming a FILE-LOCAL type is only safe once that type is carried too — which `file_scope_types()`
# now does, so such decls ride along after their typedef (types are emitted before decls).
#
# ^ THAT COMMENT DESCRIBED A FIX THAT WAS NEVER APPLIED TO THE CODE (Phase 26-A audit, HIGH).
# The predicate only ever whitelisted builtins, so a decl naming a carried file-local type was matched
# by _HOIST_RE and then SILENTLY DROPPED. Measured: 4,040 dropped col-0 decls — 3,357 DATA externs and
# **683 function PROTOTYPES**. The data drops are loud (undeclared identifier -> compile error, someone
# notices). The prototype drops are NOT: in C89 an undeclared function is implicitly `int f()`, so the
# TU still COMPILES — with the wrong return type and lost pointer-ness. And this project has BYTE-PROVEN
# that the return type drives codegen (cookbook: "schedule — delay-slot fill via void return type";
# ov_SC01_077_after.c carries an `extern int` -> `extern void` flip described as byte-neutral precisely
# because the return type moves the delay slot). So a dropped prototype is a SILENT BYTE-CHANGER, armed
# to fire on the NEXT carve. Today's split is green only because the source redundantly re-declares
# externs per fn-group, so most items carry their own decl. That is luck, not design.
#
# Two of the dropped base types are not even file-local: `uint` (139 drops) and `code_fn` (21) are
# DEFINED IN src/shared/engine_types.h, which engine_core.h pulls into every region — the predicate was
# rejecting INCLUDE-PROVIDED types it had no reason to reject. And `volatile` (3 drops) fell off because
# the qualifier group has `const` but not `volatile`.
_SAFE_TYPE = re.compile(
    r'^\s*(?:extern\s+)?(?:(?:const|volatile)\s+)*(?:(?:un)?signed\s+)?'
    r'(?:void|char|short|int|long|float|double'
    r'|[su](?:8|16|32|64)|M2C_UNK|MNC_UNK)\b')

# the base type of a col-0 decl (after extern/qualifiers/struct-union-enum), for the carried-type test
_BASE_TYPE = re.compile(
    r'^\s*(?:extern\s+)?(?:(?:const|volatile)\s+)*(?:struct\s+|union\s+|enum\s+)?([A-Za-z_]\w*)')

_ENGINE_TYPES = None


def _engine_types():
    """Every type name the SHARED headers provide (engine_types.h / common.h). These are include-provided
    in every region — a decl naming one is safe to hoist with no carried typedef at all."""
    global _ENGINE_TYPES
    if _ENGINE_TYPES is None:
        names = set()
        for h in ("src/shared/engine_types.h", "include/common.h"):
            p = os.path.join(REPO, h)
            if not os.path.exists(p):
                continue
            t = open(p, errors="replace").read()
            names |= set(re.findall(r'\}\s*([A-Za-z_]\w*)\s*;', t))              # typedef struct {...} X;
            # `} __attribute__((packed, aligned(1))) X;` — the lifted Block4/Blk4_E960 shape (P31 S62): the
            # attribute sits between the brace and the name, so the pattern above never saw them.
            names |= set(re.findall(r'\}\s*__attribute__\s*\(\(.*?\)\)\s*([A-Za-z_]\w*)\s*;', t))
            names |= set(re.findall(r'^\s*typedef\s+[^;{}]*?\b([A-Za-z_]\w*)\s*;', t, re.M))
            names |= set(re.findall(r'^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*;', t, re.M))
            # ...and the same TAGS defined WITH A BODY (`struct PW8017E6D8 { int w; };`). The
            # forward-decl pattern above only catches `struct X;`, and the `}\s*X;` pattern above
            # catches `typedef struct {...} X;` — a plain tagged definition matches NEITHER, so its
            # tag was absent from _ENGINE_TYPES and any `extern struct X D_…;` failed the
            # carried-type test. Phase 29 SESSION-19: that is what blocked the func_8017C954 carve
            # (`extern struct PW8017E6D8 D_801E1EC4;`, and PW8017E6D8 sits at engine_types.h:658).
            # Measured blast radius: 77 such tags in engine_types.h were invisible to this check.
            names |= set(re.findall(r'^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*\{', t, re.M))
            # fn-ptr typedefs — the name sits INSIDE the parens (`typedef void (*ActorFn)(void);`), so
            # every name-before-';' pattern above misses it. Measured: exactly the 5 residual drops
            # (ActorFn, FuncPtr, DispatchFn, VoidFn, code_fn). Without this the coverage assertion below
            # would fire on legitimate input.
            names |= set(re.findall(r'typedef\s+[^;{}]*?\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\([^;]*\)\s*;', t))
        _ENGINE_TYPES = names
    return _ENGINE_TYPES



# `} __attribute__((packed, aligned(1))) Blk4_9B4;` — the ATTRIBUTE SITS BETWEEN THE BRACE AND THE
# NAME (P31 S71, §323 blocker 2). Every type-name scan here matched `\}\s*(\w+)\s*;`, which reads
# `__attribute__` as the name, fails on the following `((`, and yields NOTHING — so a packed
# file-local typedef never entered `carried`, every decl naming it read as "unknown type", and
# jr_isolate_all REFUSED the whole overlay. That is the entire §323 carve blocker 2, on
# ov_SC07_000 (`Blk4_9B4`, `Blk4`) and ov_SC03_029 (`Block8_80181600`). Strip attributes first.
_ATTR = re.compile(r'__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)')


def _strip_attrs(block):
    return _ATTR.sub(' ', block)


def _file_scope_decls(items):
    """[(line, [syms])] for every decl that stood at FILE SCOPE in the original TU, in item
    order. TWO sources — the second is the §8b scoping-wall fix:

      (1) COL-0 extern/proto lines in the `.c` text, with a builtin base type (a file-local
          type would be a parse error if hoisted above its typedef — see _SAFE_TYPE).
      (2) The LEADING EXTERNS of every `DEFINE_func_*()` macro the region invokes. The macro
          expands at file scope to `extern <type> <sym>; ... <def>`, so those externs ARE part
          of the TU's file-scope decl environment — but they live in engine_core.h, so no col-0
          scan of the `.c` can see them. This is what stranded `func_801734BC` from
          `extern s16 D_80126B3E;` (declared only inside DEFINE_func_80173460). Their types come
          from engine_types.h/common.h — included by engine_core.h at every region top — so they
          need no _SAFE_TYPE guard. (Externs *inside* macro bodies are block-scope shadows: they
          expand with the invocation and are never hoisted.)
      (3) The PROTOTYPE IMPLIED BY EVERY FUNCTION DEFINITION (`def` items and the `DEFINE_func_*`
          / SETTER / RETCONST macros' own definitions). In ONE translation unit a file-scope
          definition declares its function for all code below it — so a cut that moves the
          definition into an earlier region strands every later caller that took its address
          (`func_8012B2CC undeclared`). Every overlay def has external linkage (no `static`), so
          re-declaring it in a later region is always legal.
      (4) The col-0 TYPE definitions, so a carried prototype naming a file-local type
          (`Vec3s *a0`) still parses. Returned flagged so the renderer emits types FIRST.

    Returns [(text, is_type)] in item order."""
    # Collect the types this layer CARRIES first, so a decl naming one can ride along after its typedef
    # (which is exactly what the _SAFE_TYPE comment has always claimed, and never did).
    carried = set()
    for _, _, _kind, text in items:
        for block in oss.file_scope_types(text):
            block = _strip_attrs(block)
            for a, b in re.findall(r'\}\s*([A-Za-z_]\w*)\s*;|\b(?:struct|union|enum)\s+([A-Za-z_]\w*)', block):
                carried.add(a or b)
            carried |= set(re.findall(r'typedef\s+[^;{}]*?\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\([^;]*\)\s*;', block))
    known = carried | _engine_types()

    out, dropped = [], []
    # A CARRIED TYPE MAY BE EMITTED ONCE PER REGION, NOT ONCE PER ITEM (P31 S67, cookbook §321).
    # `file_scope_types` is called per item and the carried layer is the union over every item that
    # feeds this region, so a tag several of them each define at file scope — legal while they were
    # separate TUs — arrives here as N copies of one definition. At file scope in ONE TU that is
    # fatal: measured on ov_SC02_000, the isolation emitted `struct sprite8` FOUR times into
    # `ov_SC02_000_jr_80187B40.c` and cc1 rejected the region with `redefinition of struct sprite8`,
    # taking the whole overlay's build down (and, because the previous object was still on disk, the
    # SHA1 read GREEN afterwards — R53).
    # Dedupe by NAME, comparing bodies with comments and whitespace normalised away, because the
    # copies differ only in their hand-written field comments. Two DIFFERENT bodies under one name
    # are a real conflict that a rename must resolve, so those are refused loudly (R43), never
    # silently merged — picking either one would change what the region compiles to.
    seen_types, type_conflicts = {}, []

    def _type_names(block):
        block = _strip_attrs(block)
        names = {a or b for a, b in
                 re.findall(r'\}\s*([A-Za-z_]\w*)\s*;|\b(?:struct|union|enum)\s+([A-Za-z_]\w*)', block)}
        names |= set(re.findall(r'typedef\s+[^;{}]*?\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\([^;]*\)\s*;', block))
        return {n for n in names if n}

    def _norm_body(block):
        return re.sub(r'\s+', ' ', re.sub(r'/\*.*?\*/|//[^\n]*', '', block, flags=re.S)).strip()

    for _, _, kind, text in items:
        for block in oss.file_scope_types(text):        # (4) types first-class
            names = _type_names(block)
            if not names:
                # Anonymous — §321: two identically-spelled anonymous struct typedefs are DISTINCT
                # types, so there is nothing safe to dedupe against. Emit as-is.
                out.append((block, True))
                continue
            # ...AND NEVER RE-EMIT ONE THE SHARED HEADERS ALREADY DEFINE. Every region `#include`s
            # engine_core.h -> engine_types.h at its top, so carrying a definition of a type that
            # lives there is an unconditional `redefinition of struct X`. Measured on ov_SC02_000:
            # `struct sprite8` is engine_types.h:417, and the carry emitted it again into
            # ov_SC02_000_jr_80187B40.c. _engine_types() already recognises body-defined tags (the
            # SESSION-19 PW8017E6D8 fix); nothing was ever consulting it on this path.
            if names <= _engine_types():
                continue
            key = tuple(sorted(names))
            body = _norm_body(block)
            # A BARE TAG FORWARD DECL (`struct X;` — no typedef, no body) is not a body at
            # all: C89 lets it repeat and coexist with the later definition in one TU, so it
            # must neither register as the tag's body nor conflict with one. Emit it in
            # place, in original order. (P31 S68: md_MAIN_003 carries `struct S_D2394;`
            # ahead of pointer uses and the full `typedef struct S_D2394 {...}` later; the
            # body-compare refused that legal pair as R43-conflicting.) Typedef forward
            # forms (`typedef struct X X;`) stay on the dedupe path — repeating a typedef
            # IS a C89 redefinition error, so those must still collapse or refuse.
            if re.match(r'^(?:struct|union|enum)\s+\w+\s*;$', body):
                out.append((block, True))
                continue
            if key not in seen_types:
                seen_types[key] = body
                out.append((block, True))
            elif seen_types[key] != body:
                type_conflicts.append((key, seen_types[key], body))
        for line in text.split("\n"):
            if not line or line[0].isspace():           # col-0 only (block-scope stays put)
                continue
            if "{" in line or "}" in line:
                continue
            if not _HOIST_RE.match(line):
                continue
            # A col-0 line may GLUE code-emitting macro invocations onto a declaration
            # (`extern s32 aF…(…) __asm__(""); DEFINE_func_8014C4AC() DEFINE_func_8014C568() …`,
            # ov_SC03_107 S62). Carrying it whole re-instantiated the shared bodies inside the new
            # region (duplicate, name-mangled definitions -> `.globl` with no name). Carry only the
            # `;`-terminated declaration segments; for each glued DEFINE_ invocation carry its
            # implied prototype + macro externs instead (a dropped prototype is a silent byte-changer).
            glued = re.findall(r'\bDEFINE_\w+\s*\(\s*\)', re.sub(r'/\*.*?\*/|//.*$', '', line))
            if glued:
                code = re.sub(r'/\*.*?\*/|//.*$', '', line)          # comments may hold `;` — strip first
                decls = [x.strip() + ';' for x in code.split(';')[:-1] if x.strip() and 'DEFINE_' not in x]
                for inv in glued:
                    for ml in oss.macro_externs(inv):
                        out.append((ml, False))
                    mp = oss.macro_proto(inv)
                    if mp:
                        out.append((mp, False))
            else:
                decls = [line.rstrip()]                 # the original whole-line behaviour
            for d in decls:
                base = _BASE_TYPE.match(d)
                if _SAFE_TYPE.match(d) or (base and base.group(1) in known):
                    out.append((d.rstrip(), False))
                else:
                    dropped.append(d.rstrip())          # REPORTED, never silently dropped (R32)
        proto = None
        if kind == "define":                            # (2) macro-injected file-scope externs
            for line in oss.macro_externs(text):
                out.append((line, False))
            proto = oss.macro_proto(text)
        elif kind == "def":
            proto = oss.def_proto(text)
        if proto:                                       # (3) the definition's implied declaration
            out.append((proto, False))

    # A NAME CARRYING TWO DIFFERENT BODIES IS NOT DEDUPABLE (R43). Emitting either one silently
    # decides which definition the region compiles against; refuse and name the tag instead.
    if type_conflicts:
        sys.exit("[jr_isolate_all] %d carried type name(s) have CONFLICTING bodies — a rename is "
                 "needed, not a dedupe (R43):\n%s" % (
                     len(type_conflicts),
                     "\n".join("  %s\n    A: %s\n    B: %s" % ("/".join(k), a[:150], b[:150])
                               for k, a, b in type_conflicts[:5])))

    # COVERAGE ASSERTION (R32). A line _HOIST_RE recognised as hoistable but that we could not place is
    # a BUG, never a silent no-op. Print the base-type histogram so the cause is named, not guessed —
    # this single check would have surfaced all 4,040 drops the day the first split shipped.
    if dropped:
        hist = collections.Counter()
        for l in dropped:
            m = _BASE_TYPE.match(l)
            hist[m.group(1) if m else "?"] += 1
        protos = sum(1 for l in dropped if re.search(r'\bfunc_[0-9A-Fa-f]{8}\s*\(', l))
        sys.exit(
            f"[jr_isolate_all] {len(dropped)} file-scope decl(s) matched _HOIST_RE but could not be "
            f"placed — REFUSING to emit a region that silently omits them.\n"
            f"  {protos} are function PROTOTYPES: in C89 an undeclared function is implicitly `int f()`, "
            f"so the TU still COMPILES with the WRONG RETURN TYPE — and return type drives delay-slot "
            f"fill in this codebase. A dropped prototype is a SILENT BYTE-CHANGER.\n"
            f"  base types: {dict(hist.most_common(12))}\n"
            f"  e.g. {dropped[:3]}\n"
            f"  Fix: carry the naming type (file_scope_types) or add it to src/shared/engine_types.h.")
    # FINAL PASS (P31 S62): NO carried line may contain a code-emitting `DEFINE_…()` invocation,
    # whichever branch produced it (a one-line `extern …; DEFINE_func_X() DEFINE_func_Y()` item
    # reaches here both as a col-0 decl and as a `define` item's macro_externs text). Keep the
    # `;`-terminated declaration segments, and carry each glued macro's implied prototype instead.
    cleaned = []
    for line, is_block in out:
        if is_block or not re.search(r'\bDEFINE_\w+\s*\(\s*\)', line):
            cleaned.append((line, is_block)); continue
        code = re.sub(r'/\*.*?\*/|//.*$', '', line)
        for x in code.split(';')[:-1]:
            x = x.strip()
            if x and 'DEFINE_' not in x:
                cleaned.append((x + ';', False))
        for inv in re.findall(r'\bDEFINE_\w+\s*\(\s*\)', code):
            mp = oss.macro_proto(inv)
            if mp and (mp, False) not in cleaned:
                cleaned.append((mp, False))
    return cleaned


def _rewrite_includes(text, old_sub, new_sub, syms, obj_start):
    """Address-aware INCLUDE_ASM/INCLUDE_RODATA path repoint (P31 S68).

    `rewrite_asm_subseg` repointed EVERY `/nonmatchings/<old_sub>"` occurrence in the item
    text — including a glued §154-A LEADING-ISLAND reference. But splat regenerates a
    piece-owned rodata symbol's `.s` under the subseg that owns its ADDRESS: after the
    md_MAIN_003 3-way carve, `D_800CEDF8.s` (island, vram 0x800CEDF8 < the object's code
    start 0x800CEED0) stayed at `nonmatchings/md_MAIN_003/` while the repointed include
    named `nonmatchings/md_MAIN_003_jr_800D12D0/` — `can't open ... for reading` at
    assembly (loud, thankfully). A symbol BELOW the object's code start is exactly the
    leading-island case, so its include keeps its original path; everything else — function
    stubs, in-code data words (D_800D3200), migrated tail tables (addr beyond the object)
    — keeps the proven blanket-rewrite behavior, unresolvable names included."""
    out = []
    inc_re = re.compile(r'\s*INCLUDE_(?:ASM|RODATA)\("[^"]*/nonmatchings/'
                        + re.escape(old_sub) + r'",\s*(\w+)\)')
    for line in text.split("\n"):
        m = inc_re.match(line)
        if m:
            a = oss.addr_of(m.group(1), syms)
            if a is not None and obj_start is not None and a < obj_start:
                out.append(line)                    # piece-owned island content: path unchanged
                continue
        out.append(oss.rewrite_asm_subseg(line, old_sub, new_sub))
    return "\n".join(out)


def _render_region(header, items, old_sub, new_sub, ambient, syms=None, obj_start=None):
    """Region .c = header + AMBIENT file-scope decls (from earlier regions of this object, in
    original order, deduped by symbol) + the region's items unchanged.

    WHY THIS IS BYTE-NEUTRAL AND CONFLICT-FREE BY CONSTRUCTION: `ambient` reproduces the
    original TU's file-scope decl environment, carried strictly FORWARD (regions are in address
    order and file order == address order, so every ambient source textually preceded every item
    of this region in the original). Therefore (a) every carried decl already coexisted with
    every definition in the one original TU, so no NEW `conflicting types` can arise; (b) decl
    compatibility is order-symmetric, so hoisting a decl earlier is safe; (c) decls emit no code.
    The loose-typing shadows — e.g. `func_80173544`, defined at file scope as
    `s32 f(void *)` yet declared `extern void f(void);` *inside* func_801734BC's body — live in
    bodies, travel with their item, and are never hoisted, so the split never creates the clash a
    naive "declare every used symbol" completion would. `make build` (SHA1) remains the sole
    arbiter (G3/P9/R22)."""
    if new_sub != old_sub:
        items = [(a, n, k, _rewrite_includes(t, old_sub, new_sub, syms, obj_start))
                 for a, n, k, t in items]
    # Dedup by EXACT decl text, not by symbol: this codebase is loosely typed, so one symbol can
    # legally carry several distinct (even mutually-warning) file-scope decls — the baseline build
    # emits 87 `type mismatch with previous external decl` warnings and is still byte-identical.
    # Collapsing them to the first would drop a decl the original TU had (e.g. hide a definition's
    # own signature behind an earlier, differently-typed canonical extern). Emitting every distinct
    # decl in original order reproduces the original sequence exactly.
    types, decls, seen = [], [], set()
    for text, is_type in ambient:
        key = re.sub(r'\s+', ' ', text.strip())
        if key in seen:
            continue
        seen.add(key)
        (types if is_type else decls).append(text)
    parts = [header]
    if types or decls:
        # NB the trailing END MARKER is load-bearing, not decoration: family_remap.extract_unit walks
        # BACKWARD from a definition absorbing every preceding extern/comment/blank line as the fn's
        # "preamble". Without a stop, the first item of a region swallows this whole carried layer —
        # which then gets templated into every sibling (dragging ~140 unrelated externs, some naming
        # types the sibling's TU lacks) and the gate fails. The marker bounds the layer.
        parts.append("/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) "
                     "===================\n"
                     " * The file-scope decl environment from earlier code regions of this object —\n"
                     " * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier\n"
                     " * definition's implied prototype (types first, then decls in original order).\n"
                     " * Decls emit no code => byte-neutral. See cookbook §8c. */\n"
                     + "\n".join(types + decls)
                     + "\n/* ==== end §8b carried decl layer ==== */")
    parts.extend(t for _, _, _, t in items)
    return "\n".join(parts) + "\n"


def repoint_overlays_mk(carve_renames, dry, ov=None, cfg_lines=None):
    """Repoint both overlays.mk consumers of a renamed carve object: the `--order` leaf AND the
    §8e `JTBL_PADS` target var.

    THE PADS LINE MUST FOLLOW ITS SPAN (P30 S48, the 0b blocker). A multi-table span's pad spec is
    keyed by the OBJECT that emits the tables, so when isolation moves the span's owner into
    `<ov>_jr_<addr>` the spec has to move with it. Leaving it behind fails TWO different ways, both
    observed on ov_SC02_037's 4-table span (spec `0,0,0,0`, tables +0x0,+0x14,+0x34,+0x4c):
      * plain `make build` after a bare isolate -> the stale line arms the pads filter on the
        residual object, which now emits NO jump table:
        `jtbl_rodata_pads: consumed 0 rodata .align(s) but 4 pad spec(s) given` (S47, hard error);
      * the jtbl_family_bank path (isolate -> jtbl_carve) -> `set_pads_vars` regenerates the block
        keyed by the CURRENT subseg names, finds no prior spec under the new name, and the line is
        SILENTLY DROPPED. cc1's natural `.align 3` then pads the span's non-8-aligned interior
        tables (+4 before table 2 here) and the image shifts: `built, bytes differ`.
    Byte-neutral: only the target NAME changes; the spec and its `tables=` record are untouched.

    Fails loud (R32) if the old object still hosts a `.rodata` piece — then the line is ambiguous
    (jtbl_carve's invariant is one contiguous .rodata run per object, so this should be
    unreachable; if it ever fires, the carve set is the thing to fix, not this rename)."""
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    _mk_base = txt
    changed = []
    for old_sub, new_sub in carve_renames.items():
        pat = rf'(--order[^#\n]*?){re.escape(old_sub)}\.o'
        if re.search(pat, txt):
            txt = re.sub(pat, lambda m: m.group(1) + new_sub + ".o", txt, count=1)
            changed.append(f"--order {old_sub}.o -> {new_sub}.o")
        if ov is None:
            continue
        pads_pat = rf'^(build/src/{re.escape(ov)}/){re.escape(old_sub)}(\.o: JTBL_PADS := )'
        if not re.search(pads_pat, txt, re.M):
            continue
        if cfg_lines is not None and any(
                re.match(rf'^\s*- \[0x[0-9A-Fa-f]+,\s*\.rodata,\s*{re.escape(old_sub)}\]', ln)
                for ln in cfg_lines):
            sys.exit(f"jr_isolate_all: {old_sub} has a JTBL_PADS line AND still hosts a .rodata "
                     f"carve after the split — refusing to repoint the spec to {new_sub} (R32). "
                     f"One object must own at most one contiguous .rodata run.")
        txt = re.sub(pads_pat, lambda m: m.group(1) + new_sub + m.group(2), txt, count=1, flags=re.M)
        changed.append(f"JTBL_PADS {old_sub}.o -> {new_sub}.o")
    if not dry:
        MKW.write_overlays_mk(txt, path=mk, base=_mk_base)
    return changed


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--only", help="comma-separated func_XXXX to isolate (default: all -O2 jr)")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    only = set(a.only.split(",")) if a.only else None

    p = plan(a.ov, only)
    n_jr = sum(len(v) for v in p["per_obj"].values())
    print(f"jr_isolate_all {a.ov}: {n_jr} jr in {len(p['per_obj'])} -O2 objects "
          f"{ {k: len(v) for k, v in p['per_obj'].items()} }")
    if p["skipped_o0"]:
        print(f"  SKIPPED {len(p['skipped_o0'])} jr in -O0 objects: {[hex(x) for x in p['skipped_o0']]}")
    if not p["per_obj"]:
        print("  nothing to isolate.")
        return

    cfg_lines, new_files, carve_renames = build_new_config(a.ov, p)
    # FAIL-LOUD VALIDATION (Phase 26 session 8): the code-subseg list must be strictly ascending
    # with unique names, or splat rejects the split ("segments out of order"). The byte-proven
    # corruption path: a failed bank's revert once left an isolation's config lines in place, the
    # committed config gained a DUPLICATE `- [off, c, name]` line (harmless to splat — zero-length),
    # and the NEXT isolation walked the object twice, emitting a reversed duplicate block. Validate
    # BEFORE writing so a corrupt input dies here, not three tools downstream.
    code_re = re.compile(r'^\s*- \[(0x[0-9A-Fa-f]+), c, (\w+)\]')
    seen_off, seen_nm = -1, set()
    for ln in cfg_lines:
        m = code_re.match(ln)
        if not m:
            continue
        off, nm = int(m.group(1), 16), m.group(2)
        if off <= seen_off or nm in seen_nm:
            sys.exit(f"jr_isolate_all: REFUSING to write a corrupt config — code subseg "
                     f"[{hex(off)}, {nm}] is {'out of order' if off <= seen_off else 'a duplicate'} "
                     f"(prev off {hex(seen_off)}). The INPUT config likely carries duplicate/stale "
                     f"subseg lines from an un-reverted isolation — `git diff config/splat.{a.ov}.yaml` "
                     f"and clean it first.")
        seen_off, seen_nm = off, seen_nm | {nm}
    mk_changes = repoint_overlays_mk(carve_renames, dry=True, ov=a.ov, cfg_lines=cfg_lines)
    print(f"  -> {len(new_files)} region .c files; carve repoints: {carve_renames or '(none)'}")
    for c in mk_changes:
        print(f"     overlays.mk: {c}")

    if a.dry_run:
        print("  [dry-run] no files written.")
        return

    # write config, source region files, overlays.mk
    cfg_path = os.path.join(REPO, f"config/splat.{a.ov}.yaml")
    open(cfg_path, "w").write("\n".join(cfg_lines) + "\n")
    # remove the original per-object .c files that were replaced (region 0 rewrites them;
    # extra regions are new — but a stale original with the OLD single-object content would
    # shadow nothing since we overwrite region 0 to the same path). Write all region files:
    for path, content in new_files.items():
        open(path, "w").write(content)
    repoint_overlays_mk(carve_renames, dry=False, ov=a.ov, cfg_lines=cfg_lines)
    print(f"  wrote config + {len(new_files)} region files + overlays.mk. Run `make extract "
          f"BINARY={a.ov} && make build BINARY={a.ov}` to byte-gate (R22).")


if __name__ == "__main__":
    main()
