#!/usr/bin/env python3
"""main_diff_locate.py -- turn a RED whole-binary gate into a NAMED list of divergent symbols.

WHY THIS EXISTS (P31 S72). A main gate's entire output is two hashes:

    [FAIL] build/us/SLUS_007.26
           got  817987d141d07ced0cc74e8bb0f8bb33eb41cfd1
           want 143dbb89f34491258bbc27810d0a12ec8b43a8dd

That is a correctness oracle with ZERO diagnostic content, and the campaign has been paying for
it. S71 substituted 11 main drafts one at a time, watched 7 of them come back with a different
hash, and recorded all 11 as "PROVEN gate-rejects -- §376 in its purest form". But a hash says
only THAT the image moved, never WHERE: a draft whose own body is byte-perfect still moves the
image if the substitution perturbed a CALLER (the classic §376 shape -- the TU keeps a stale
`extern void f(void*)` forward declaration while the new definition is `void f(s32)`, so every
call site's argument codegen changes). Attributing that to the drafted function is the R40
failure mode: blaming the subject for a harness effect, with no instrument that could tell them
apart.

WHAT IT DOES
  diff the built image against the retail reference, coalesce the differing bytes into runs, and
  name the symbol each run lands in using the linker map. The answer that matters is one line:
  is the divergence INSIDE the function you drafted, or somewhere else?

    * diff inside the drafted function only  -> BODY REJECT. A real one.
    * diff only in `.rodata`                 -> TABLE REJECT (§405-A). The `.text` is perfect and
      the JUMP TABLE is wrong. `match_one` compares .text only and cannot see this; gcc emits case
      BODIES in source order while entry *i* points at case *i*, so case value and case order are
      independent and only the order is pinned by .text. Fix the case values/order, never respell
      the body. (This class was mislabelled PLUMBING until `func_800316F8` produced it.)
    * diff elsewhere in CODE                 -> PLUMBING REJECT, not a body reject. Route to
      the §376/§378 chain (fix_arity_callers -> cast_self_callers -> --sync-decls), re-gate.
    * diff in more than one of those         -> MIXED; the body verdict is unproven until the
      others are fixed and it is re-gated.

DERIVED, NOT HARDCODED (R33). The file-offset mapping comes from the map's own
`load address 0x...` on each output section, not from the PS-X EXE's 0x800 header constant, so a
resegmentation cannot silently skew every reported address by a fixed amount.

NEGATIVE CONTROL (R39, and `check-against-a-known-true-case`). `--self-test` flips one byte at a
caller-supplied address in a copy of the reference and asserts the tool names the containing
symbol, then asserts a byte-identical pair reports zero. A localizer that cannot be shown to
finger a KNOWN perturbation is not evidence about an unknown one.

Usage:
  tools/main_diff_locate.py                                  # build/ vs extracted/retail, table
  tools/main_diff_locate.py --focus func_8001A114            # verdict relative to one function
  tools/main_diff_locate.py --json                           # machine-readable
  tools/main_diff_locate.py --self-test 0x8001a114
"""
import argparse, bisect, functools, json, os, re, sys

print = functools.partial(print, flush=True)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILT = 'build/us/SLUS_007.26'
REF = 'extracted/retail/SLUS_007.26'
MAP = 'build/us/SLUS_007.26.map'

# ld prints an output section as  `.main    0x80010000  0x64800 load address 0x00000800`, and the
# LMA is the only statement in the whole toolchain of where a vaddr lands in the FILE. Reading it
# beats restating the 0x800 PS-X header here (R33) -- and it is per-section, which a constant is not.
SECTION = re.compile(r'^(\.\S+)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+load address 0x([0-9a-fA-F]+)')
# A symbol line is an address and a name, indented, nothing else on the line. The `\S+$` anchor is
# what keeps input-section lines (`.text  0x80010000  0x23f0 build/src/boot.o`) out: those carry a
# size column, so they never reduce to one trailing token after the address.
SYMBOL = re.compile(r'^\s+0x([0-9a-fA-F]+)\s{2,}(\S+)$')
INPUT_SEC = re.compile(r'^\s(\.\S+)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+(\S+)$')


def parse_map(path):
    """-> (sections, syms) where sections is [(vma, size, lma)] and syms is sorted [(addr, name, obj)].

    Two map facts this has to survive:
      * splat emits `func_X.NON_MATCHING` and `func_X` at the SAME address for every stubbed
        function. Keeping both doubles every row of the report and makes an attribution look
        ambiguous when it is not, so the `.NON_MATCHING` alias is dropped in favour of the real
        name whenever both sit on one address.
      * `ld` has no per-symbol size here. A symbol's extent is [its address, the next DISTINCT
        address) -- the next-address rule is the only end marker available, and it is exact for
        contiguous code.
    """
    sections, raw, obj_of, cur_obj = [], {}, {}, None
    for line in open(path, errors='replace'):
        line = line.rstrip('\n')
        m = SECTION.match(line)
        if m:
            sections.append((int(m.group(2), 16), int(m.group(3), 16), int(m.group(4), 16)))
            continue
        m = INPUT_SEC.match(line)
        if m:
            cur_obj = '%s(%s)' % (m.group(4), m.group(1))
            continue
        m = SYMBOL.match(line)
        if m:
            addr, name = int(m.group(1), 16), m.group(2)
            if name.endswith('= .') or '=' in name:
                continue
            prev = raw.get(addr)
            # prefer the real name over splat's `.NON_MATCHING` alias at the same address
            if prev is None or (prev.endswith('.NON_MATCHING') and not name.endswith('.NON_MATCHING')):
                raw[addr] = name
                obj_of[addr] = cur_obj
    syms = sorted((a, n, obj_of.get(a)) for a, n in raw.items())
    return sections, syms


def off_to_addr(sections, off):
    """Map a file offset back to a RAM address, preferring the SMALLEST containing section.

    The output sections OVERLAP in file offsets here: `.main` spans 0x800..0x65000 and every
    linked PsyQ library block sits inside that range with its own `load address`. Both mappings
    agree today (the libs are contiguous inside .main), but "first match wins" would silently
    depend on map ordering the day they stop agreeing, so the tightest section wins."""
    best = None
    for vma, size, lma in sections:
        if lma <= off < lma + size and (best is None or size < best[1]):
            best = (vma, size, lma)
    return None if best is None else best[0] + (off - best[2])


def addr_to_sym(syms, addrs, addr):
    """Name the symbol containing `addr`, or None before the first symbol."""
    i = bisect.bisect_right(addrs, addr) - 1
    if i < 0:
        return None, None
    return syms[i][1], syms[i][2]


def diff_runs(a, b, gap=64):
    """Differing byte offsets, coalesced into runs separated by more than `gap` identical bytes.

    Regalloc drift scatters single differing WORDS across a whole function; emitting one run per
    word buries the answer in hundreds of rows. Merging across a small gap groups them back into
    the one region a human (or a router) actually reasons about, while `nbytes` keeps the honest
    count of bytes that actually differ (R41 -- the run count is not the magnitude)."""
    n = min(len(a), len(b))
    runs, start, last, ndiff = [], None, None, 0
    for i in range(n):
        if a[i] != b[i]:
            ndiff += 1
            if start is None:
                start, last = i, i
            elif i - last > gap:
                runs.append((start, last + 1))
                start = i
            last = i
    if start is not None:
        runs.append((start, last + 1))
    return runs, ndiff, (len(a) != len(b))


def attribute(built, ref, sections, syms, gap=64):
    """-> (per_symbol, total_diff_bytes, size_mismatch).

    Attribution is PER BYTE, not per run: a run that straddles two functions is credited to both
    in the right proportion. Crediting a whole run to the symbol its first byte lands in is how a
    one-byte spill into the next function gets reported as "two functions diverged"."""
    addrs = [s[0] for s in syms]
    runs, ndiff, size_mismatch = diff_runs(built, ref, gap)
    per = {}
    for lo, hi in runs:
        for off in range(lo, hi):
            if built[off] == ref[off]:
                continue
            addr = off_to_addr(sections, off)
            if addr is None:
                key, obj = '<outside any output section>', None
            else:
                name, obj = addr_to_sym(syms, addrs, addr)
                key = name or '<before first symbol>'
            e = per.setdefault(key, {'symbol': key, 'obj': obj, 'bytes': 0,
                                     'first_off': off, 'first_addr': addr, 'last_addr': addr})
            e['bytes'] += 1
            e['last_addr'] = addr
    return per, ndiff, size_mismatch


def classify(per, focus, ndiff):
    """-> (verdict, message) for a drafted function. The three ways a main draft can be red.

    THE THIRD CLASS EXISTS BECAUSE THE FIRST TWO MISLABELLED IT (P31 S72). `func_800316F8`'s
    `.text` was byte-identical and all 18 differing bytes sat in its OWN jump table, and the tool
    called it a PLUMBING REJECT and routed it to the §376/§378 declaration chain — advice that
    would never have fixed it. A `.rodata` divergence is §405-A: `match_one` compares `.text`
    ONLY, so a draft sits at closeness 0 while emitting a wrong table. gcc emits case BODIES in
    source order while entry *i* points at case *i*, so case VALUE and case ORDER are independent
    and only the order is pinned by `.text`.

    Note the attribution reads one symbol LOW for a cc1-emitted table: once a function is C its
    table is a `$L` label, not a `jtbl_` data symbol, so the differing bytes land inside the
    PRECEDING table's extent. The object name is what identifies it, not the symbol name."""
    inside = per.get(focus, {}).get('bytes', 0)
    outside = ndiff - inside
    # TABLE bytes live in whatever section THIS BINARY puts its jump tables in — not always
    # `.rodata` (P31 S75). main's `section_order` is [.rodata, .text, .data, .bss], so its rodata
    # sits BELOW .text at 0x80010000-0x800123F0 and its jump tables land in `.data` objects
    # (`build/asm/data/63C4C.data.o(.data)`). Keying on the literal string `(.rodata)` therefore
    # made TABLE REJECT UNREACHABLE for main, and `SaveLoadRoutine` — 1,165 ins, the largest
    # function left in the project — was labelled a PLUMBING REJECT and routed to the §376
    # declaration chain. Measured split: 3,787 of 3,989 bytes (94.9%) in `.data` jump tables,
    # 202 (5.1%) in real `.text`. The chain was run twice and fixed nothing, because it addresses
    # the 5%.
    tbl = sum(e['bytes'] for k, e in per.items()
              if k != focus and any(t in (e.get('obj') or '') for t in ('(.rodata)', '(.data)')))
    # DOMINANCE, not purity. The old test demanded `ro == outside`, so a few bytes of perturbed
    # code defeated it entirely and the verdict silently fell through to the wrong advice. Report
    # the SPLIT and lead with the class that owns most of the damage.
    if outside and tbl and tbl >= 0.6 * outside and tbl != outside:
        return ('TABLE REJECT (MIXED)',
                f"{focus}'s .text is BYTE-IDENTICAL, and {tbl} of {outside} differing bytes "
                f"({100.0*tbl/outside:.1f}%) are JUMP TABLES / data — a carve-extent problem "
                f"(§446: check the built image SIZE against retail, and the carve extent against "
                f"4 x sltiu). The remaining {outside-tbl} byte(s) are perturbed code and are the "
                f"§376 declaration part. FIX THE TABLES FIRST — the declaration chain cannot "
                f"touch the {100.0*tbl/outside:.0f}% that is data.")
    ro = tbl
    if outside and ro == outside:
        return ('TABLE REJECT',
                f"{focus}'s .text is BYTE-IDENTICAL; all {outside} differing bytes are in "
                f".rodata — its own jump table (§405-A). match_one cannot see this. Check the "
                f"case VALUES and their ORDER against the table's entry order in the .s; do NOT "
                f"respell the body and do NOT route this to the §376 declaration chain.")
    if inside and not outside:
        return ('BODY REJECT',
                f"divergence is CONFINED TO {focus} ({inside} bytes) — a real body reject.")
    if outside and not inside:
        return ('PLUMBING REJECT',
                f"{focus} is BYTE-IDENTICAL; all {outside} differing bytes are ELSEWHERE in "
                f"CODE. The substitution perturbed other functions (§376 — a stale forward "
                f"declaration changes caller codegen). Route to fix_arity_callers -> "
                f"cast_self_callers -> re-gate.")
    if inside and outside:
        return ('MIXED',
                f"{inside} bytes inside {focus}, {outside} elsewhere"
                + (f" (of which {ro} in .rodata — see §405-A)" if ro else "")
                + ". The body verdict is UNPROVEN until the outside bytes are fixed.")
    return ('NOT FOUND',
            f"{focus} is not among the divergent symbols — check the name against the linker map.")


def report(focus=None, as_json=False, built_path=BUILT, ref_path=REF, map_path=MAP, gap=64):
    for p in (built_path, ref_path, map_path):
        if not os.path.exists(p):
            print(f"REFUSED — missing {p}", file=sys.stderr)
            return 2
    built, ref = open(built_path, 'rb').read(), open(ref_path, 'rb').read()
    sections, syms = parse_map(map_path)
    if not sections or not syms:
        print(f"REFUSED — {map_path} yielded {len(sections)} sections / {len(syms)} symbols; "
              f"the map format is not what this tool parses, and a localizer that silently "
              f"attributes nothing is worse than none (R43).", file=sys.stderr)
        return 2
    per, ndiff, size_mismatch = attribute(built, ref, sections, syms, gap)
    rows = sorted(per.values(), key=lambda e: -e['bytes'])

    if as_json:
        print(json.dumps({'diff_bytes': ndiff, 'file_bytes': len(ref),
                          'size_mismatch': size_mismatch, 'focus': focus,
                          'symbols': rows}, indent=1))
        return 0 if ndiff == 0 else 1

    if size_mismatch:
        print(f"!! SIZE MISMATCH — built {len(built)} bytes, reference {len(ref)} bytes. "
              f"Offsets past the shorter file are not compared.")
    if ndiff == 0:
        print(f"IDENTICAL — 0 differing bytes of {len(ref)}.")
        return 0
    print(f"{ndiff} differing bytes of {len(ref)} ({100.0*ndiff/len(ref):.4f}%), "
          f"across {len(rows)} symbol(s):\n")
    print(f"  {'bytes':>7}  {'first addr':>10}  symbol")
    for e in rows[:40]:
        a = f"0x{e['first_addr']:08x}" if e['first_addr'] is not None else f"@{e['first_off']}"
        print(f"  {e['bytes']:>7}  {a:>10}  {e['symbol']}"
              + (f"   [{e['obj']}]" if e['obj'] else ''))
    if len(rows) > 40:
        print(f"  ... and {len(rows)-40} more symbol(s) not listed "
              f"({sum(r['bytes'] for r in rows[40:])} bytes)")

    if focus:
        verdict, msg = classify(per, focus, ndiff)
        print(f"\nVERDICT — {verdict}: {msg}")
    return 1


def self_test(addr_hex, map_path=MAP, ref_path=REF):
    """Flip one byte at a KNOWN address and assert the tool names the containing symbol.

    R39 / `check-against-a-known-true-case`. The identical-pair direction is asserted too: a
    localizer that reports a diff on identical inputs would make every verdict above worthless."""
    addr = int(addr_hex, 16)
    ref = open(ref_path, 'rb').read()
    sections, syms = parse_map(map_path)
    addrs = [s[0] for s in syms]
    want, _ = addr_to_sym(syms, addrs, addr)
    off = None
    for vma, size, lma in sections:
        if vma <= addr < vma + size:
            off = lma + (addr - vma)
    if off is None:
        print(f"SELF-TEST REFUSED — 0x{addr:08x} is in no output section")
        return 2
    ok = True

    # direction 1: identical inputs must report zero
    per, ndiff, _ = attribute(ref, ref, sections, syms)
    print(f"  identical-pair  -> {ndiff} differing bytes, {len(per)} symbols "
          f"{'OK' if ndiff == 0 and not per else 'FAIL'}")
    ok &= (ndiff == 0 and not per)

    # direction 2: a known one-byte perturbation must be attributed to the containing symbol
    mut = bytearray(ref)
    mut[off] ^= 0xFF
    per, ndiff, _ = attribute(bytes(mut), ref, sections, syms)
    got = list(per)
    hit = (ndiff == 1 and got == [want])
    print(f"  1-byte flip at 0x{addr:08x} (file offset {off}) -> {ndiff} byte(s) in {got}; "
          f"expected exactly ['{want}'] {'OK' if hit else 'FAIL'}")
    ok &= hit
    print('SELF-TEST', 'PASS' if ok else 'FAIL')
    return 0 if ok else 1


if __name__ == '__main__':
    os.chdir(REPO)
    ap = argparse.ArgumentParser()
    ap.add_argument('--built', default=BUILT)
    ap.add_argument('--ref', default=REF)
    ap.add_argument('--map', dest='map_path', default=MAP)
    ap.add_argument('--focus', help='the function you substituted; adds an attribution verdict')
    ap.add_argument('--gap', type=int, default=64, help='coalesce runs separated by <= N bytes')
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--self-test', metavar='ADDR',
                    help='negative control: flip one byte at ADDR and assert attribution')
    a = ap.parse_args()
    if a.self_test:
        sys.exit(self_test(a.self_test, a.map_path, a.ref))
    sys.exit(report(a.focus, a.json, a.built, a.ref, a.map_path, a.gap))
