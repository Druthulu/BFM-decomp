#!/usr/bin/env python3
"""Phase-26 §8 (overlay ×134): set up the jtbl-rodata carve for an overlay's matched jr-functions.

An overlay's gcc switch jump tables sit in one contiguous `.rodata` island at the TAIL of the flat
blob. Matching a jr-function makes its C emit that jtbl into `.rodata` (floated to the FRONT by
section_order) while the raw copy stays in the data tail -> duplicate + wrong address. This tool
carves each named jr-function's jtbl(s) out of the `[…, data, tail]` region into a dotted
`[.rodata, <code-subseg>]` subseg (spimdisasm migrates it into the fn's object), splitting the data
tail into the surrounding `data` subsegs, and sets the `<ov>_JTBL_INTERLEAVE` var in
config/overlays.mk so `make extract` runs `ld_interleave --order` (the address-ordered
data->rodata->data->…->data sandwich; cookbook §8/§8a).

Per-sibling: the SAME function is at the same vram across overlays but its jtbl is at a DIFFERENT
address in each (the island floats with the overlay's size), so the carve is recomputed per overlay.

MULTI-jtbl (Phase-26 session 3): the carve is ADDITIVE and regenerated from the current config —
each `--func` call re-derives the FULL address-ordered set of {data pieces, existing .rodata carves,
the new jtbl(s)} and re-emits the region + an `--order` interleave list. So banking a 2nd matched
jr-function into an overlay that already has one (the ×134 accumulation case) Just Works. A single
code object contributes at most ONE contiguous .rodata run, so two matched jr-functions in the SAME
code subseg (non-adjacent jtbls in the island) are UNSATISFIABLE -> this tool fails loud, and the
caller must first isolate one into its own code subseg (the whale `_o0b` precedent).

Usage:  jtbl_carve.py <ov> --func func_XXXX [--func ...]   # add these matched jr-fns to the carve set
        jtbl_carve.py <ov> --revert                        # restore the config from git (drop carves)
Idempotent: re-running with the same (accumulated) funcs reproduces the same config.
"""
import argparse
import glob
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

PIECE_RE = re.compile(r"^(\s*)- \[(0x[0-9A-Fa-f]+),\s*([.\w]+),\s*(\w+)\]")
EOF_RE = re.compile(r"^\s*- \[(0x[0-9A-Fa-f]+)\]\s*(?:#.*)?$")


def cfg_path(ov):
    return os.path.join(REPO, f"config/splat.{ov}.yaml")


def overlay_vram_base(ov):
    """The overlay's load vram (all location overlays share the 0x80128158 slot, but read it)."""
    txt = open(cfg_path(ov)).read()
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", txt)
    if not m:
        sys.exit(f"jtbl_carve: no vram in {cfg_path(ov)}")
    return int(m.group(1), 16)


def code_pieces(ov):
    """[(vram, subseg)] for every `- [off, c, name]` code piece in the config, ascending."""
    base = overlay_vram_base(ov)
    out = []
    for ln in open(cfg_path(ov)):
        m = re.match(r'\s*- \[(0x[0-9A-Fa-f]+),\s*c,\s*(\w+)\]', ln)
        if m:
            out.append((base + int(m.group(1), 16), m.group(2)))
    return sorted(out)


def func_subseg(ov, func):
    """The code subseg that owns `func`, derived from the CONFIG (address -> containing code piece).

    NOT from the asm tree: `make extract` does not prune stale subseg directories, so after a §8b
    isolation BOTH `nonmatchings/<ov>_after/<func>.s` (stale) and `nonmatchings/<ov>_jr_<ADDR>/<func>.s`
    (current) exist on disk, and an `os.listdir` scan can return the STALE owner — silently
    re-creating the same-subseg NON-CONTIGUOUS collision the isolation just removed. The config is
    authoritative and stale-proof."""
    addr = int(func[len("func_"):], 16)
    owner = None
    for vram, name in code_pieces(ov):
        if vram <= addr:
            owner = name
        else:
            break
    if owner is None:
        sys.exit(f"jtbl_carve: {func} (0x{addr:08x}) precedes every code piece in {cfg_path(ov)}")
    return owner


def func_jtbls(ov, func):
    """(subseg, [jtbl_hex,...]) that `func` references (from its .s %hi(jtbl_...))."""
    sub = func_subseg(ov, func)
    s = open(os.path.join(REPO, "asm", ov, "nonmatchings", sub, f"{func}.s")).read()
    return sub, sorted(set(re.findall(r"jtbl_([0-9A-Fa-f]{8})", s)))


def all_data_labels(ov):
    """All (jtbl_|D_) dlabel vrams across every asm/<ov>/data/*.data.s, sorted ascending."""
    labels = set()
    for p in glob.glob(os.path.join(REPO, "asm", ov, "data", "*.data.s")):
        for ln in open(p):
            m = re.match(r"\s*(?:dlabel|glabel)\s+(?:jtbl_|D_)([0-9A-Fa-f]{8})", ln)
            if m:
                labels.add(int(m.group(1), 16))
    return sorted(labels)


def jtbl_words(ov, jtbl_hex):
    """The raw `.word` values under `dlabel jtbl_<hex>`, in order."""
    pat = re.compile(rf"dlabel\s+jtbl_{jtbl_hex}\b", re.I)
    for p in glob.glob(os.path.join(REPO, "asm", ov, "data", "*.data.s")):
        lines = open(p).read().split("\n")
        for i, ln in enumerate(lines):
            if pat.search(ln):
                out = []
                for ln2 in lines[i + 1:]:
                    m = re.search(r"\.word\s+(0x[0-9A-Fa-f]+)", ln2)
                    if m:
                        out.append(int(m.group(1), 16))
                        continue
                    if re.search(r"\b(?:dlabel|glabel|enddlabel)\b", ln2):
                        break
                return out
    return []


def jtbl_range(ov, jtbl_hex, labels, region_end_vram):
    """(start_vram, end_vram) of a RAW jtbl_<hex>: end = the next data dlabel, MINUS any trailing
    zero words.

    A trailing `.word 0x00000000` under a jtbl dlabel is NOT a table entry — it is the original TU's
    intra-rdata **`.align 3` padding** (a jtbl whose entries end ≡4 mod 8, with another jtbl of the
    same TU following, gets one zero word of alignment fill). It cannot be an entry: 0x00000000 is
    not a jump target, and the function's `sltiu <n>` range check names the true entry count
    (byte-confirmed: `func_8015AE2C` → `sltiu 0x7` = 7 entries, yet the raw dlabel spans 8 words).

    This matters because **maspsx drops `.align`**, so a C-emitted jump table can never reproduce the
    pad. Carving to the next dlabel would reserve 8 words while the compiled object supplies only 7 —
    under-filling the `.rodata` piece by 4 bytes and shifting every later symbol (the same +4 image
    corruption class as §41d). Trimming leaves the pad where it belongs: in the raw post-carve data
    piece. This also retroactively explains the §8a `func_80159C84` "5 words vs the real 6"
    false-MATCH."""
    start = int(jtbl_hex, 16)
    if start not in labels:
        sys.exit(f"jtbl_carve: jtbl_{jtbl_hex} not found in the raw data asm "
                 f"(asm/{ov}/data/*.data.s) — already carved / stale asm? re-extract or --revert first")
    nxt = next((a for a in labels if a > start), None)
    end = nxt if nxt is not None else region_end_vram
    words = jtbl_words(ov, jtbl_hex)
    if words:
        n = len(words)
        while n > 0 and words[n - 1] == 0:
            n -= 1
        trimmed = start + n * 4
        if trimmed < end:
            print(f"jtbl_carve: jtbl_{jtbl_hex}: trimmed {(end - trimmed) // 4} trailing .align pad "
                  f"word(s) — {n} real entries")
            end = trimmed
    return start, end


def parse_config(ov):
    """Parse the flat-overlay config's tail data region.

    Returns (lines, indent, region_lo_idx, region_hi_idx, tail_start, region_end, trailing_present,
             existing_carves) where:
      - lines: the config file split into lines.
      - region_lo_idx..region_hi_idx: the [inclusive, exclusive) line range of the `- [...]` data/
        rodata PIECE lines to replace (the `bin,trailing` + EOF lines stay).
      - tail_start / region_end: file offsets bounding the regenerated data region.
      - trailing_present: whether a `[off, bin, trailing]` piece caps the region.
      - existing_carves: [(start_off, end_off, subseg), ...] for the `.rodata` carves already present.
    """
    lines = open(cfg_path(ov)).read().splitlines()
    pieces = []   # (idx, indent, off, kind, name)
    eof_off = None
    for i, ln in enumerate(lines):
        m = PIECE_RE.match(ln)
        if m:
            pieces.append((i, m.group(1), int(m.group(2), 16), m.group(3), m.group(4)))
            continue
        e = EOF_RE.match(ln)
        if e:
            eof_off = int(e.group(1), 16)
    # The data region = the trailing run of {data, .rodata} pieces after the last `c` piece.
    data_pieces = [p for p in pieces if p[3] in ("data", ".rodata")]
    if not data_pieces:
        sys.exit(f"jtbl_carve: no data-tail region in {cfg_path(ov)}")
    region_lo_idx = data_pieces[0][0]
    indent = data_pieces[0][1]
    tail_start = data_pieces[0][2]
    # Where the regenerated pieces stop: the trailing bin piece, else the EOF marker.
    trailing = [p for p in pieces if p[3] == "bin" and p[4] == "trailing"]
    if trailing:
        region_hi_idx = trailing[0][0]
        region_end = trailing[0][2]
        trailing_present = True
    else:
        if eof_off is None:
            sys.exit(f"jtbl_carve: no trailing bin and no EOF marker in {cfg_path(ov)}")
        # region_hi_idx = the EOF marker line index
        region_hi_idx = next(i for i, ln in enumerate(lines) if EOF_RE.match(ln))
        region_end = eof_off
        trailing_present = False
    # Existing .rodata carves: end = the following piece's off (or region_end for the last).
    region = [p for p in data_pieces if region_lo_idx <= p[0] < region_hi_idx]
    existing = []
    for j, (_, _, off, kind, name) in enumerate(region):
        if kind == ".rodata":
            end = region[j + 1][2] if j + 1 < len(region) else region_end
            existing.append((off, end, name))
    return lines, indent, region_lo_idx, region_hi_idx, tail_start, region_end, trailing_present, existing


def build_carve(ov, funcs):
    """Return (region_lines, order_arg): the regenerated data-region `- [...]` piece lines and the
    `ld_interleave --order` object list, for the accumulated carve set (existing + the new funcs)."""
    base = overlay_vram_base(ov)
    (_, indent, _, _, tail_start, region_end, trailing_present, existing) = parse_config(ov)
    region_end_vram = base + region_end

    # carves: (start_off, end_off, subseg). Existing ones come from the config (already migrated).
    carves = list(existing)
    have = {c[0] for c in carves}
    # A new jtbl's end is bounded by the next RAW data dlabel OR the next EXISTING carve start
    # (an already-carved adjacent jtbl is gone from the data asm, so the raw dlabels alone would
    # over-extend the new jtbl past it — the merge would then see an overlap, not an abutment).
    labels = sorted(set(all_data_labels(ov)) | {base + c[0] for c in existing})
    for f in funcs:
        sub, js = func_jtbls(ov, f)
        if not js:
            sys.exit(f"jtbl_carve: {f} references no jtbl_ (not a jr/switch function?)")
        for jh in js:
            s_vram, e_vram = jtbl_range(ov, jh, labels, region_end_vram)
            s_off, e_off = s_vram - base, e_vram - base
            if s_off in have:
                continue                       # idempotent: already carved
            carves.append((s_off, e_off, sub))
            have.add(s_off)
    carves.sort()

    # A code object emits its jtbls CONTIGUOUS in .rodata (gcc source order). So two carves in the
    # SAME subseg are byte-correct only if ADJACENT in the island (no unmatched jtbl between) -> merge
    # them into one spanning .rodata piece. NON-adjacent same-subseg is unsatisfiable (a single object
    # can't leave a gap for the raw jtbl between) -> isolate one fn into its own subseg (jr_isolate.py).
    merged = []
    for s_off, e_off, sub in carves:
        if merged and merged[-1][2] == sub and merged[-1][1] == s_off:
            merged[-1] = (merged[-1][0], e_off, sub)      # extend the contiguous same-subseg run
        else:
            merged.append((s_off, e_off, sub))
    seen_subsegs = {}
    for s_off, _, sub in merged:
        if sub in seen_subsegs:
            sys.exit(
                f"jtbl_carve: subseg '{sub}' would host NON-CONTIGUOUS .rodata carves "
                f"(0x{seen_subsegs[sub]:x} and 0x{s_off:x}) — a single object can't leave a gap for the "
                f"unmatched jtbl between them. Isolate one matched jr-function into its own code subseg "
                f"first (tools/jr_isolate.py, the whale `_o0b` precedent), then re-carve.")
        seen_subsegs[sub] = s_off
    carves = merged

    # Walk the region [tail_start, region_end), emitting a `data` piece before each carve.
    pieces = []          # (off, kind, name)
    order = []           # object leaves for --order, in address order
    cursor = tail_start
    n_data = 0
    def data_name():
        nonlocal n_data
        n_data += 1
        return "tail" if n_data == 1 else f"tail{n_data}"
    for s_off, e_off, sub in carves:
        if cursor < s_off:
            nm = data_name()
            pieces.append((cursor, "data", nm))
            order.append(f"{nm}.data.o")
        pieces.append((s_off, ".rodata", sub))
        order.append(f"{sub}.o")
        cursor = e_off
    if cursor < region_end:
        nm = data_name()
        pieces.append((cursor, "data", nm))
        order.append(f"{nm}.data.o")
    if trailing_present:
        order.append("trailing.o")

    region_lines = []
    for off, kind, name in pieces:
        comment = "  # Phase-26 §8 jtbl-rodata carve (jtbl_carve.py)" if kind == ".rodata" else ""
        region_lines.append(f"{indent}- [{hex(off)}, {kind}, {name}]{comment}")
    return region_lines, "--order " + ",".join(order)


def apply(ov, funcs):
    region_lines, order_arg = build_carve(ov, funcs)
    lines, indent, lo, hi, *_ = parse_config(ov)
    new_lines = lines[:lo] + region_lines + lines[hi:]
    open(cfg_path(ov), "w").write("\n".join(new_lines) + "\n")
    set_overlays_var(ov, order_arg)
    print(f"jtbl_carve {ov}: carve set = {len(region_lines)} pieces; JTBL_INTERLEAVE = {order_arg}")


def set_overlays_var(ov, args):
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    var = f"{ov}_JTBL_INTERLEAVE := {args}  # Phase-26 §8 jtbl-rodata carve"
    if re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE\b", txt, re.M):
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", var, txt, count=1, flags=re.M)
    else:
        # insert right after the overlay's SPLAT_YAML line
        anchor = f"{ov}_SPLAT_YAML := config/splat.{ov}.yaml"
        if anchor not in txt:
            sys.exit(f"jtbl_carve: no {anchor} anchor in overlays.mk")
        txt = txt.replace(anchor, anchor + "\n" + var, 1)
    open(mk, "w").write(txt)


def revert(ov):
    """Restore this overlay's carve state to the COMMITTED one.

    `<ov>_JTBL_INTERLEAVE` must be restored to its committed VALUE, not deleted: every overlay now
    carries a committed carve (134/134 since func_8012ACE0 / func_801734BC banked ×134), so an
    unconditional drop would destroy a banked carve on any failed sweep. And `overlays.mk` is SHARED
    by all 134 overlays, so a blunt `git checkout` of it would wipe the OTHER siblings' in-flight
    vars mid-sweep — hence the surgical, per-overlay line splice."""
    subprocess.check_call(["git", "-C", REPO, "checkout", "--", cfg_path(ov)])
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    committed = subprocess.run(["git", "-C", REPO, "show", "HEAD:config/overlays.mk"],
                               capture_output=True, text=True).stdout
    m = re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", committed, re.M)
    has_now = re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE\b", txt, re.M)
    if m and has_now:
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", lambda _: m.group(0), txt,
                     count=1, flags=re.M)
    elif m:                                   # committed var was dropped -> put it back
        anchor = f"{ov}_SPLAT_YAML := config/splat.{ov}.yaml"
        if anchor not in txt:
            sys.exit(f"jtbl_carve: no {anchor} anchor in overlays.mk")
        txt = txt.replace(anchor, anchor + "\n" + m.group(0), 1)
    else:                                     # no committed carve -> drop ours
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*\n", "", txt, flags=re.M)
    open(mk, "w").write(txt)
    print(f"jtbl_carve {ov}: reverted config + JTBL_INTERLEAVE restored to committed"
          f"{'' if m else ' (none)'}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--func", action="append", default=[], help="matched jr-function to carve (repeatable)")
    ap.add_argument("--revert", action="store_true", help="restore config from git + drop the var")
    a = ap.parse_args()
    if a.revert:
        revert(a.ov)
    elif a.func:
        apply(a.ov, a.func)
    else:
        ap.error("give --func <fn> (repeatable) or --revert")


if __name__ == "__main__":
    main()
