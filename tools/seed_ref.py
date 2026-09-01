#!/usr/bin/env python3
"""seed_ref.py — for an open stub, the ALREADY-BANKED body that matches it. (P31 S67)

WHY THIS EXISTS — 102,193 opus tokens, one function.
`ov_SC03_107:func_8013DD68` was drafted from scratch by an opus agent, which reported:
"Card wrongly said NO banked twin — func_8013DD68 is banked verbatim in ~20 sibling overlays."
It was right. The body sits in `ov_MAIN_012` at the same address, and SIX overlays still hold it
open. The agent re-derived it, matched 187/187, and the whole exercise was avoidable.

THE THREE-PART FAILURE, each part true on its own:
  1. `twin_sweep` DID find the pair — `candidates("both")` returns it, tier `norm`. But a previous
     sweep's MECHANICAL remap was gate-refused, so it went into `.run/twin_refused.json`
     (`ov_SC03_107:0x8013dd68<-ov_MAIN_012:0x8013dd68`) and is skipped FOREVER without
     `--retry-refused`. The ledger is right that the remap failed; it is wrong to conclude the
     FUNCTION is spent, because an agent can fix the integration blocker a symbol substitution
     cannot.
  2. `t5_cards.py` does not build `seed_ref` ("needs the atlas knn"), so the card asserts
     "no banked twin — derive from the .s" and its docstring calls that TRUE. It is true of the
     CARD and false of the WORLD — the card's own claim is what sent the agent to the .s.
  3. Nothing joined those two facts, so a refusal in one tool became a false negative in another.

WHAT THIS DOES INSTEAD. Joins open stubs to banked bodies on the SIGNATURE HASHES the corpus
already computes — no atlas, no knn, ~2 s fleet-wide:
    h_exact : identical instruction bytes modulo relocation fields   (measured 88.5% remap rate)
    h_norm  : identical after masking the relocation fields          (measured ~76-80%)
h_seq is NOT used — Phase 26 refuted it at 0%.

COVERAGE IS FLEET-WIDE ON PURPOSE (R32). `twin_sweep` reads `family_sweep.load_sigs()`, which
covers **141 of 213 binaries** — `main`, `resident` and every `md_MAIN_*` are absent, so every twin
in them is structurally invisible to it. This reads `corpus.sig`/`corpus.matched` over all 213.
(`twin_sweep` has a second, separate hole: it builds its open-set with
`int(s.symbol[5:], 16)` inside a bare `except Exception: pass`, so ONE curated symbol name silently
disables an ENTIRE binary — measured: `main`, where 765 of 1048 stubs carry curated names.)

    tools/seed_ref.py --binary ov_SC03_107 --fn func_8013DD68
    tools/seed_ref.py --all --json .run/seed_refs.json

NEAR TIER (P31 S69 Fable audit — venv-only, see the block below `for_stub`):
    .venv/bin/python tools/seed_ref.py --near [--max-d 5] [--json PATH]
    .venv/bin/python tools/seed_ref.py --near-control

CONTAINED TIER (P31 S69 Fable-2 audit — venv-only, see the block above `contained_scan`):
banked twins 1..4 whole statement-blocks away at ANY gap size (the near tier's cap conflates a
46-ins inserted block with "far"). Advisory seeding only — deletion-direction rows are
mechanically decidable, insertion-direction rows carry the block's exact asm for a seeded crack.
    .venv/bin/python tools/seed_ref.py --contained [--min-cover 0.8] [--json PATH]
    .venv/bin/python tools/seed_ref.py --contained-control
"""
import argparse
import collections
import functools
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import corpus     # noqa: E402
import progress   # noqa: E402

REFUSED_LEDGER = os.path.join(REPO, ".run/twin_refused.json")


@functools.lru_cache(maxsize=1)
def _linked_segs():
    """{binary: {subseg, ...}} whose INCLUDE_ASM is DEAD TEXT — a draft there banks a FALSE match.

    Measured P31 S68 (R45 — never offer a target the pipeline cannot honestly bank). `--all` used to
    report "87 open stubs have a banked twin"; **43 of them were main stubs in LINKED subsegs**, i.e.
    the 49 subsegs whose TUs the linker script never references because the bytes come from linked
    PsyQ SDK objects. `Makefile:595` still globs every `src/*.c` into OBJS, so ANY C written into one
    of those TUs compiles, links, and leaves the SHA1 green **whether or not it is correct**. A
    mechanical twin-remap lane fed from that list would have minted up to 43 gate-green FALSE matches
    that the whole-binary byte gate is structurally unable to catch (R34).

    `draw_waves.py` has refused these since S66; this oracle did not, and the wave playbook cites
    THIS tool as "the fleet-wide answer" — so the hole lived in the tool the playbook trusts most.
    Fleet-wide today only `main` has any (49); computed per binary anyway, because a newly onboarded
    binary must be seen by every consumer (R36). ~0.4 s for all 213.
    """
    out = {}
    for b in progress.BINARIES:
        try:
            progress.set_binary(b)
            segs = set(progress.LINKED_SEGS or ())
        except Exception:
            segs = set()
        if segs:
            out[b] = segs
    return out


def is_linked_stub(binary, stub):
    """True when this open stub's INCLUDE_ASM is dead text (see _linked_segs)."""
    return getattr(stub, "region", None) in _linked_segs().get(binary, ())


@functools.lru_cache(maxsize=1)
def _refused():
    """{(to_bin, to_addr, from_bin, from_addr)} the mechanical remap already failed on.

    Keys look like `ov_SC03_107:0x8013dd68<-ov_MAIN_012:0x8013dd68`, with LOWERCASE hex — a search
    by the uppercase SYMBOL name finds nothing, which is how this ledger stayed invisible while it
    was suppressing the very twin an agent was paying to re-derive.
    """
    out = set()
    try:
        with open(REFUSED_LEDGER) as fh:
            for k in json.load(fh):
                try:
                    lhs, rhs = k.split("<-")
                    tb, ta = lhs.split(":")
                    fb, fa = rhs.split(":")
                    out.add((tb, int(ta, 16), fb, int(fa, 16)))
                except ValueError:
                    continue
    except (OSError, ValueError):
        pass
    return out


@functools.lru_cache(maxsize=1)
def _banked_index():
    """({h_exact: [(bin, addr, name, nins)]}, {h_norm: [...]}) over ALL binaries."""
    ex, no = {}, {}
    for b in progress.BINARIES:
        try:
            rows = corpus.matched(b)
        except Exception:
            continue                      # a binary whose oracle refuses is REPORTED by callers
        for addr, r in rows.items():
            item = (b, addr, r.get("name"), r.get("nins"))
            if r.get("h_exact"):
                ex.setdefault(r["h_exact"], []).append(item)
            if r.get("h_norm"):
                no.setdefault(r["h_norm"], []).append(item)
    return ex, no


def for_stub(binary, fn, include_linked=False):
    """The best banked twin for one open stub, or None.

    Prefers h_exact over h_norm (a stricter twin is a safer remap) and, within a tier, a
    SAME-ADDRESS exemplar (the same engine function in a sibling overlay), because that remap is a
    pure symbol substitution.
    """
    try:
        sig = corpus.sig(binary)
        st = next((s for s in corpus.stubs(binary).values() if s.symbol == fn), None)
    except Exception:
        return None
    if st is None:
        return None
    if not include_linked and is_linked_stub(binary, st):
        # DEAD TEXT (R45): a draft here gates GREEN while wrong, so this is not a bankable target
        # and offering its twin is worse than offering nothing. Callers that want the raw join
        # anyway pass include_linked=True and get the row tagged, never silently.
        return None
    row = sig.get(st.addr)
    if not row:
        return None
    ex, no = _banked_index()
    for tier, idx, key in (("exact", ex, row.get("h_exact")), ("norm", no, row.get("h_norm"))):
        pool = idx.get(key) if key else None
        if not pool:
            continue
        pool = sorted(pool, key=lambda x: (x[1] != st.addr, x[0]))
        fb, fa, fname, fnins = pool[0]
        try:
            src = corpus.stubs(fb) and None
        except Exception:
            src = None
        # SCHEMA NOTE: `binary`/`fn` are the EXEMPLAR's, because that is what api_agent's card
        # renderer greps for ("grep(pattern=sr['fn'], path='src/'+sr['binary'])"). Naming them after
        # the TARGET would send every agent grepping for its own function in its own source — a
        # silent no-op that looks like a rendered hint. The target is kept as target_binary/target_fn.
        return {
            "binary": fb, "fn": fname, "nins": fnins, "tier": tier,
            "target_binary": binary, "target_fn": fn,
            "exemplar_addr": "0x%08x" % fa, "same_addr": fa == st.addr,
            # THE FLAG THAT MATTERS TO AN AGENT: the mechanical remap was already tried and the
            # gate refused it, so copy the BODY but expect a declaration/integration blocker —
            # do not assume a plain symbol substitution will bank.
            "mechanical_remap_refused": (binary, st.addr, fb, fa) in _refused(),
            "others_open": sum(1 for x in pool if x[1] == fa),
        }
    return None


# --------------------------------------------------------------------------------------------
# NEAR TIER (P31 S69 Fable audit, 2026-09-01) — banked twins at edit distance 1..K, not only
# hash equality.
# --------------------------------------------------------------------------------------------
# WHY (byte-witnessed; full audit in .run/S69_fable/report.md). `h_norm`'s hi/lo tracker
# (sig_image.norm_stream) DISCARDS the pending lui-hi when an R-type intervenes, so the
# indexed-global triad
#       lui $at, %hi(arr);  addu $at, $at, idx;  lw $r, %lo(arr)($at)
# keeps its %lo IMMEDIATE unmasked in the hash. Two per-overlay copies of the same function
# whose only difference is that array's ADDRESS therefore hash to DIFFERENT h_norm, and every
# h_norm-keyed consumer (for_stub above, twin_sweep, dup_report, the family maps' structural
# tier, config/dedup.us.yaml) reads them as unrelated singletons. Measured 2026-09-01 over the
# 360 reachable open stubs: 22 had a d=0 (hash) twin, and 36 MORE had a banked twin at distance
# 1..5 — 31 of them RELOC-ONLY (every differing word an address-reloc slot under
# family_remap.reloc_indices, which DOES propagate hi through add/addu — the wider, proven
# model behind the 76-88% mechanical-remap rates). Example: `func_80185F6C` is banked in
# ov_SC06_033 and its body serves FIVE open 94-ins copies whose single differing word is
# `lw $a1, %lo(D_xxxx)($at)` — one extern rename each.
#
# THE METRIC: banded Levenshtein over norm_stream 32-bit tokens (registers and true immediates
# KEPT), so d==0 IS h_norm equality — asserted against for_stub on every run (R34/R39: the near
# tier must reproduce every d=0 the hash oracle finds, or die). Prefilters are SOUND lower
# bounds (|dnins| <= K; opclass-histogram L1 <= 2K; token-multiset L1 <= 2K): no true d<=K pair
# can be excluded by them (R32). h_norm ITSELF is deliberately left unchanged — every stored
# map, ledger and calibration keys on it; this tier widens the JOIN, not the hash.
#
# Verdicts per row: RELOC-ONLY (mechanical-remap candidate — route to family_remap; expect the
# h_norm-class 76-88% rate, minus jtbl carve blockers) vs NEAR-COUSIN (real code drift <= K —
# seeded-crack card fuel: copy the twin's C, expect exactly the listed words to differ).

def _near_mods():
    """Lazy venv-only deps (sig_image needs rabbitizer). Imported here, not at module top, so
    the card pipeline's plain-python3 `import seed_ref` keeps working; --near under the wrong
    interpreter refuses loudly instead of degrading the metric (R43)."""
    try:
        import sig_image
    except ModuleNotFoundError as e:
        raise SystemExit("seed_ref --near needs rabbitizer (via sig_image): run under "
                         ".venv/bin/python. Refusing rather than degrading (R43).") from e
    import family_remap
    return sig_image, family_remap


def _norm_tokens(SI, words):
    raw = struct.pack("<%dI" % len(words), *words)
    nb = SI.norm_stream(raw)
    return struct.unpack("<%dI" % (len(nb) // 4), nb)


def _words_of(FR, b, a, n):
    data = FR._img(b)
    off = a - FR.vram_of(b)
    if off < 0 or off + 4 * n > len(data):
        return None
    return list(struct.unpack_from("<%dI" % n, data, off))


def _opclass_hist(words):
    h = collections.Counter()
    for w in words:
        op = w >> 26
        h[(op, w & 0x3F if op == 0 else ((w >> 16) & 0x1F if op == 1 else 0))] += 1
    return h


def _l1(c1, c2):
    d = 0
    for k, v in c1.items():
        d += abs(v - c2.get(k, 0))
    for k, v in c2.items():
        if k not in c1:
            d += v
    return d


def _mid_jr(words):
    return any((w >> 26) == 0 and (w & 0x3F) == 0x08 and ((w >> 21) & 0x1F) != 31 for w in words)


def _lev(a, b, cut):
    """Levenshtein over token sequences, capped: returns min(d, cut+1). Common-affix trim +
    banded DP with an early bail when a whole band row exceeds the cap."""
    la, lb = len(a), len(b)
    if abs(la - lb) > cut:
        return cut + 1
    i = 0
    while i < la and i < lb and a[i] == b[i]:
        i += 1
    j = 0
    while j < la - i and j < lb - i and a[la - 1 - j] == b[lb - 1 - j]:
        j += 1
    a = a[i:la - j]; b = b[i:lb - j]
    la, lb = len(a), len(b)
    if la == 0:
        return lb
    if lb == 0:
        return la
    if la > lb:
        a, b, la, lb = b, a, lb, la
    INF = cut + 1
    prev = list(range(la + 1))
    for jj in range(1, lb + 1):
        lo = max(1, jj - cut); hi = min(la, jj + cut)
        cur = [INF] * (la + 1)
        if lo == 1:
            cur[0] = jj if jj <= cut else INF
        bj = b[jj - 1]; best = INF
        for ii in range(lo, hi + 1):
            c = prev[ii] + 1
            if cur[ii - 1] + 1 < c:
                c = cur[ii - 1] + 1
            c3 = prev[ii - 1] + (a[ii - 1] != bj)
            if c3 < c:
                c = c3
            cur[ii] = c
            if c < best:
                best = c
        if best > cut:
            return cut + 1
        prev = cur
    return prev[la] if prev[la] <= cut else cut + 1


def _classify_pair(FR, wo, wb, to, tb, show=6):
    """RELOC-ONLY iff every differing token sits in an address-reloc slot on BOTH sides under
    family_remap.reloc_indices (the addu-propagating model); else NEAR-COUSIN."""
    import difflib
    ro, rb = FR.reloc_indices(wo), FR.reloc_indices(wb)
    sm = difflib.SequenceMatcher(a=to, b=tb, autojunk=False)
    reloc_only, detail = True, []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == "equal":
            continue
        if op != "replace" or (i2 - i1) != (j2 - j1):
            reloc_only = False
            detail.append("%s open[%d:%d] twin[%d:%d]" % (op, i1, i2, j1, j2))
            continue
        for k in range(i2 - i1):
            io, ib = i1 + k, j1 + k
            if io in ro and ib in rb:
                detail.append("reloc@%d" % io)
            else:
                reloc_only = False
                detail.append("code@%d:%08x<->%08x" % (io, wo[io], wb[ib]))
    return ("RELOC-ONLY" if reloc_only else "NEAR-COUSIN"), detail[:show]


def _main_splat_sig():
    """main's splat-true sig rows ({addr: row}) — the registry sig for main is the (older)
    Ghidra dump; .run/sig.main.jsonl carries splat-seeded slices for everything that was still
    a stub when `make sig-main` last ran, which includes every CURRENT stub (stubs only shrink)."""
    out = {}
    p = os.path.join(REPO, ".run/sig.main.jsonl")
    if os.path.exists(p):
        for ln in open(p):
            ln = ln.strip()
            if ln:
                r = json.loads(ln)
                out[int(r["addr"], 16)] = r
    return out


def _pool_and_open(include_linked=False, caller="near_scan"):
    """The shared population + banked pool (one pass per binary; R32 buckets).
    Returns (open_rows, banked, linked_n): open_rows = every reachable open stub with its sig
    row; banked = {h_exact: (nins, [(bin, addr)])} over every non-IMPORTED matched body (main:
    splat-true sig.main rows first, then registry non-stub rows). Extracted verbatim from
    near_scan for the --contained tier (S69 Fable-2); the two tiers MUST share one denominator."""
    open_rows, linked_n, oracle_refused = [], 0, []
    banked = {}

    def _add(h, n, bb, aa):
        e = banked.setdefault(h, (n, []))
        if len(e[1]) < 3:
            e[1].append((bb, aa))

    msig = _main_splat_sig()
    for b in progress.BINARIES:
        try:
            stubs = corpus.stubs(b)
        except Exception as e:
            oracle_refused.append((b, repr(e)[:90]))
            continue
        st_addrs = set(stubs)
        if b == "main":
            seen = set()
            for a2, r in msig.items():
                if a2 in st_addrs:
                    continue
                _add(r["h_exact"], r["nins"], "main", a2); seen.add(a2)
            for a2, r in corpus.sig("main").items():
                if a2 in st_addrs or a2 in seen or r.get("src") == "IMPORTED":
                    continue
                _add(r["h_exact"], r["nins"], "main", a2)
        else:
            for a2, r in corpus.matched(b).items():
                if r.get("src") == "IMPORTED":
                    continue
                _add(r["h_exact"], r["nins"], b, a2)
        for s in stubs.values():
            if not include_linked and is_linked_stub(b, s):
                linked_n += 1
                continue
            row = msig.get(s.addr) if b == "main" else corpus.sig(b).get(s.addr)
            if row is None:
                raise SystemExit("%s: open stub %s:%s missing from its sig — refusing to "
                                 "scan a population I cannot stream (R32)." % (caller, b, s.symbol))
            open_rows.append(dict(binary=b, addr=s.addr, symbol=s.symbol, nins=row["nins"],
                                  h_exact=row["h_exact"]))
    if oracle_refused:
        raise SystemExit("%s: corpus oracle refused %s — the denominator would be wrong "
                         "(R32/R41)." % (caller, oracle_refused))
    return open_rows, banked, linked_n


def near_scan(max_d=5, include_linked=False):
    """Fleet-wide near-twin scan. Returns {rows, clusters, stats}; every reachable open stub
    appears in exactly one row (R32 — the arithmetic is asserted), with its minimum distance to
    any banked body (None if > max_d) and, at d<=max_d, the twin + RELOC-ONLY/NEAR-COUSIN
    verdict. `clusters` are the open-open connected components at d<=max_d (crack-one-unlock-k)."""
    SI, FR = _near_mods()
    open_rows, banked, linked_n = _pool_and_open(include_linked, "near_scan")

    # ---- streams + histograms ----
    by_len = collections.defaultdict(list)
    bw, unstreamable = {}, 0
    for h, (n, locs) in banked.items():
        for (bb, aa) in locs:
            ws = _words_of(FR, bb, aa, n)
            if ws is not None:
                bw[h] = ws
                by_len[n].append(h)
                break
        else:
            unstreamable += 1
    ow = {}
    for o in open_rows:
        if o["h_exact"] not in ow:
            ws = _words_of(FR, o["binary"], o["addr"], o["nins"])
            if ws is None:
                raise SystemExit("near_scan: cannot stream open stub %s:%s (R32)."
                                 % (o["binary"], o["symbol"]))
            ow[o["h_exact"]] = ws
    bh = {h: _opclass_hist(w) for h, w in bw.items()}
    oh = {h: _opclass_hist(w) for h, w in ow.items()}

    # ---- sound prefilter -> candidates ----
    cand = {}
    for o in open_rows:
        n, hx = o["nins"], o["h_exact"]
        ho = oh[hx]
        cs = [h for m in range(max(1, n - max_d), n + max_d + 1) for h in by_len.get(m, ())
              if _l1(ho, bh[h]) <= 2 * max_d]
        cand[(o["binary"], o["addr"])] = cs

    need = set(h for cs in cand.values() for h in cs)
    tok = {h: _norm_tokens(SI, bw[h]) for h in need}
    for hx, ws in ow.items():
        tok[hx] = _norm_tokens(SI, ws)
    cnt = {h: collections.Counter(t) for h, t in tok.items()}

    drawn = set()
    dp = os.path.join(REPO, ".run/t5/drawn.json")
    if os.path.exists(dp):
        try:
            drawn = {tuple(k.split(":", 1)) for k in json.load(open(dp))}
        except (OSError, ValueError):
            pass

    # ---- open vs banked ----
    rows = []
    for o in open_rows:
        hx = o["h_exact"]
        to, co = tok[hx], cnt[hx]
        best, bhx = max_d + 1, None
        for h in cand[(o["binary"], o["addr"])]:
            if _l1(co, cnt[h]) > 2 * max_d:
                continue
            d = _lev(to, tok[h], best - 1 if best <= max_d else max_d)
            if d < best:
                best, bhx = d, h
                if best == 0:
                    break
        rec = dict(binary=o["binary"], fn=o["symbol"], addr="0x%08x" % o["addr"],
                   nins=o["nins"], d=(best if best <= max_d else None),
                   jtbl=_mid_jr(ow[hx]), drawn=(o["binary"], o["symbol"]) in drawn)
        if bhx is not None:
            tb, ta = banked[bhx][1][0]
            rec["twin"] = "%s:0x%08x" % (tb, ta)
            rec["twin_nins"] = banked[bhx][0]
            if best > 0:
                cls, detail = _classify_pair(FR, ow[hx], bw[bhx], to, tok[bhx])
                rec["cls"], rec["diff"] = cls, detail
            else:
                rec["cls"] = "HASH-TWIN"
        rows.append(rec)

    # ---- open vs open clusters ----
    prs = []
    for i in range(len(open_rows)):
        o1 = open_rows[i]
        for j in range(i + 1, len(open_rows)):
            o2 = open_rows[j]
            if abs(o1["nins"] - o2["nins"]) > max_d:
                continue
            h1, h2 = o1["h_exact"], o2["h_exact"]
            if h1 == h2:
                prs.append((0, i, j)); continue
            if _l1(cnt[h1], cnt[h2]) > 2 * max_d:
                continue
            d = _lev(tok[h1], tok[h2], max_d)
            if d <= max_d:
                prs.append((d, i, j))
    par = list(range(len(open_rows)))

    def find(x):
        while par[x] != x:
            par[x] = par[par[x]]; x = par[x]
        return x
    for d, i, j in prs:
        par[find(i)] = find(j)
    comp = collections.defaultdict(list)
    for i in range(len(open_rows)):
        comp[find(i)].append("%s:%s" % (open_rows[i]["binary"], open_rows[i]["symbol"]))
    clusters = sorted((v for v in comp.values() if len(v) > 1), key=len, reverse=True)

    # ---- R34/R39: the near tier must reproduce every d=0 the hash oracle (for_stub) finds ----
    mism, unverifiable = [], []
    dmap = {(r["binary"], r["fn"]): r for r in rows}
    for o in open_rows:
        sr = for_stub(o["binary"], o["symbol"], include_linked=include_linked)
        if not sr:
            continue
        r = dmap[(o["binary"], o["symbol"])]
        if r["d"] == 0:
            continue
        tb, ta = sr["binary"], int(sr["exemplar_addr"], 16)
        ws = _words_of(FR, tb, ta, sr["nins"] or 0) if sr.get("nins") else None
        if ws is None:
            unverifiable.append((o["binary"], o["symbol"], "twin unstreamable"))
            continue
        mism.append((o["binary"], o["symbol"], sr["tier"], r["d"]))
    if mism:
        raise SystemExit("near_scan FAILED its hash-oracle cross-check (R34/R39): for_stub finds "
                         "a d=0 twin the near tier does not: %s" % mism[:5])

    n_d0 = sum(1 for r in rows if r["d"] == 0)
    n_near = sum(1 for r in rows if r["d"] is not None and r["d"] > 0)
    stats = dict(reachable=len(rows), linked_skipped=linked_n, max_d=max_d,
                 d0=n_d0, near=n_near,
                 reloc_only=sum(1 for r in rows if r.get("cls") == "RELOC-ONLY"),
                 near_cousin=sum(1 for r in rows if r.get("cls") == "NEAR-COUSIN"),
                 no_twin=sum(1 for r in rows if r["d"] is None),
                 clusters=len(clusters),
                 cluster_stubs=sum(len(c) for c in clusters),
                 banked_pool=len(banked), banked_unstreamable=unstreamable,
                 cross_check="OK (%d hash twins reproduced)" % n_d0,
                 cross_check_unverifiable=unverifiable)
    assert stats["d0"] + stats["near"] + stats["no_twin"] == stats["reachable"], "R32 arithmetic"
    return dict(rows=rows, clusters=clusters, stats=stats)


def near_control(max_d=5, n_pairs=4000, n_pos=200):
    """R39 controls for the near tier.
    POSITIVE (must be perfect): pairs of banked bodies with EQUAL h_norm but different h_exact
    — the class the hash remap already banks — must all measure d=0. Any other answer means the
    metric would refuse work that previously succeeded: FAIL.
    BASE RATE (context): random size-matched banked pairs, P(d<=max_d) per size band — how often
    the metric fires on arbitrary same-size functions. (The banked corpus contains TRUE twin
    families, so this over-states the false-positive rate; treat it as an upper bound.)

    SCOPE: the positive control pairs only rows from sig_is_independent binaries. main's registry
    h_norm is GHIDRA's normToken — a different normalizer (sig_image's docstring says so) — so an
    equal-Ghidra-h_norm main pair may legitimately measure d>0 here; pairing across hash MODELS
    measured the models' disagreement, not this metric (found by this control's own first run:
    2/200 failures, both main, e.g. main:0x80011818 vs 0x80011b7c, Ghidra-equal, sig_image d=6)."""
    import random
    SI, FR = _near_mods()
    random.seed(42)
    groups = collections.defaultdict(list)      # h_norm -> [(b, addr, nins, h_exact)]
    for b in progress.BINARIES:
        if not corpus.sig_is_independent(b):
            continue                             # h_norm there is Ghidra's model, not norm_stream's
        try:
            for a2, r in corpus.matched(b).items():
                if r.get("src") == "IMPORTED" or not r.get("h_norm"):
                    continue
                groups[r["h_norm"]].append((b, a2, r["nins"], r["h_exact"]))
        except Exception:
            continue
    pos = 0; posn = 0
    for hn, mem in groups.items():
        if posn >= n_pos:
            break
        hexs = {}
        for m in mem:
            hexs.setdefault(m[3], m)
        if len(hexs) < 2:
            continue
        (b1, a1, n1, _), (b2, a2, n2, _) = list(hexs.values())[:2]
        w1, w2 = _words_of(FR, b1, a1, n1), _words_of(FR, b2, a2, n2)
        if w1 is None or w2 is None:
            continue
        posn += 1
        d = _lev(_norm_tokens(SI, w1), _norm_tokens(SI, w2), max_d)
        if d == 0:
            pos += 1
    print("POSITIVE control (h_norm-equal, h_exact-different banked pairs): %d/%d at d=0"
          % (pos, posn))
    if pos != posn:
        raise SystemExit("near_control FAILED: %d previously-succeeding twin pairs measure d>0 "
                         "(R39 zero-false-refusal broken)." % (posn - pos))

    flat = [m for mem in groups.values() for m in mem]
    by_len = collections.defaultdict(list)
    for m in flat:
        by_len[m[2]].append(m)
    band = lambda n: "tiny(<16)" if n < 16 else "small(16-49)" if n < 50 else \
        "mid(50-119)" if n < 120 else "big(>=120)"
    ctr = collections.Counter()
    tries = 0
    while tries < n_pairs:
        m1 = random.choice(flat)
        cs = [m for k in range(max(1, m1[2] - max_d), m1[2] + max_d + 1)
              for m in by_len.get(k, ()) if m[3] != m1[3]]
        if not cs:
            continue
        m2 = random.choice(cs)
        w1, w2 = _words_of(FR, m1[0], m1[1], m1[2]), _words_of(FR, m2[0], m2[1], m2[2])
        if w1 is None or w2 is None:
            continue
        tries += 1
        d = _lev(_norm_tokens(SI, w1), _norm_tokens(SI, w2), max_d)
        ctr[(band(m1[2]), d <= max_d)] += 1
    print("BASE RATE (random size-matched banked pairs, P(d<=%d)) — an UPPER bound on false "
          "positives (true twin families inflate it):" % max_d)
    for bd in ("tiny(<16)", "small(16-49)", "mid(50-119)", "big(>=120)"):
        hit, tot = ctr[(bd, True)], ctr[(bd, True)] + ctr[(bd, False)]
        print("  %-13s %4d/%4d = %5.2f%%" % (bd, hit, tot, 100.0 * hit / max(tot, 1)))


# --------------------------------------------------------------------------------------------
# CONTAINED TIER (P31 S69 Fable-2 audit, 2026-09-01) — banked twins one-to-four whole BLOCKS
# away, at ANY total gap size (the near tier's edit-distance cap conflates a 46-ins inserted
# block with "far"; this tier has no cap on gap, only on drift OUTSIDE the blocks).
# --------------------------------------------------------------------------------------------
# WHY (measured; full audit in .run/S69_fable2/report.md). Levenshtein-K misses the pair
#   open = banked body + one contiguous inserted/deleted statement block of >K instructions
# even when EVERYTHING else matches — e.g. ov_SC07_000:func_8017F69C (108 ins) is banked
# func_8017f59c (64 ins) plus a 46-ins state-dispatch preamble, byte-identical elsewhere; it sat
# in the "no twin within 25" pile. Measured 2026-09-01 over 352 reachable stubs / 51,760 banked
# bodies >=25 ins: 8 opens have a contained twin at cover>=0.8 — 3 with no near-tier twin at
# all, and for 2 more the contained twin is STRICTLY BETTER work than their near twin
# (ov_SC01_077:func_80184D50's d=5 substitution twin vs ov_SC03_007 minus ONE C statement,
# resid 0). Law: minimum edit DISTANCE is not minimum WORK — a resid-0 one-block twin beats a
# closer substitution twin.
#
# THE METRIC: difflib alignment over BRANCH-MASKED norm_stream tokens (branch imm16 zeroed —
# a branch that jumps ACROSS an inserted block differs in offset while the C is identical, so
# unmasked branch offsets veto exactly the pairs this tier exists to find; C-level insertion
# regenerates the offsets). Verdict: 1..4 indel regions, <=2 substituted tokens total (as
# equal-length replaces of <=2), and equal-token cover >= min_cover of the SHORTER side.
# min_side=25 on both functions: below that, prologue+epilogue boilerplate alone passes any
# containment test (measured: 173 raw hits at min 12 collapse to 9 real at min 25).
# Candidates via prefix-8 OR suffix-8 reg_fields-skeleton buckets (a gap at one edge still
# leaves the other edge's skeleton intact; a gap at BOTH edges is invisible to this tier —
# stated limitation, not silent).
#
# The verdict is ADVISORY seeding (copy the twin's C; insert/delete exactly the listed block):
# the deletion direction (twin longer) is mechanically decidable — delete the C statements the
# block compiles from and the byte-gate arbitrates; the insertion direction still needs the
# block's C authored, but the card carries its exact disassembly. Nothing here banks by itself.

_BR_OPS_MASK = frozenset((1, 4, 5, 6, 7))


def _tok_brmask(SI, words):
    """norm_stream tokens with branch immediates masked (see the block comment above)."""
    ts = _norm_tokens(SI, words)
    return [t & 0xFFFF0000 if (t >> 26) in _BR_OPS_MASK else t for t in ts]


def _contained_verdict(to, tt, max_k=4, max_sub=2):
    """difflib classification of one token-stream pair -> dict(k, gap, nsub, m_equal, regions)
    or None. k = indel regions (1..max_k); substitutions allowed only as equal-length replaces
    of <=2 tokens, <=max_sub total; regions carry (tag, open_span, twin_span) for the card."""
    import difflib
    ops = difflib.SequenceMatcher(a=to, b=tt, autojunk=False).get_opcodes()
    k = nsub = gap = m_equal = 0
    regions = []
    for tag, i1, i2, j1, j2 in ops:
        if tag == "equal":
            m_equal += i2 - i1
            continue
        if tag == "replace":
            if (i2 - i1) == (j2 - j1) and (i2 - i1) <= 2:
                nsub += i2 - i1
                regions.append(("sub", (i1, i2), (j1, j2)))
                continue
            return None
        k += 1
        gap += max(i2 - i1, j2 - j1)
        regions.append(("indel", (i1, i2), (j1, j2)))
    if k == 0 or k > max_k or nsub > max_sub:
        return None
    return dict(k=k, gap=gap, nsub=nsub, m_equal=m_equal, regions=regions)


def contained_scan(min_cover=0.8, min_side=25, include_linked=False):
    """Fleet-wide contained-twin scan. Returns {rows, stats}; one row per open stub that has a
    contained twin (best = fewest nsub+k, then highest cover), with `d0_twin` marking stubs the
    hash tier already serves (a contained twin there is a downgrade — consumers should prefer
    the hash/near row). R32: the population is _pool_and_open's, arithmetic asserted."""
    SI, FR = _near_mods()
    open_rows, banked, linked_n = _pool_and_open(include_linked, "contained_scan")

    pre_idx, suf_idx, binfo = {}, {}, {}
    for h, (n, locs) in banked.items():
        if n < min_side:
            continue
        w = None
        for (bb, aa) in locs:
            w = _words_of(FR, bb, aa, n)
            if w is not None:
                break
        if w is None:
            continue
        kp = tuple(FR.reg_fields(x) for x in w[:8])
        ks = tuple(FR.reg_fields(x) for x in w[-8:])
        pre_idx.setdefault(kp, []).append(h)
        suf_idx.setdefault(ks, []).append(h)
        binfo[h] = (n, locs[0][0], locs[0][1], w)

    tokc = {}

    def T(h):
        if h not in tokc:
            tokc[h] = _tok_brmask(SI, binfo[h][3])
        return tokc[h]

    rows, n_scanned, seen_hx = [], 0, {}
    for o in open_rows:
        if o["nins"] < min_side:
            continue
        n_scanned += 1
        hx = o["h_exact"]
        if hx in seen_hx:                       # h_exact-equal opens share the verdict
            if seen_hx[hx] is not None:
                rows.append(dict(seen_hx[hx], open="%s:%s" % (o["binary"], o["symbol"]),
                                 addr="0x%08x" % o["addr"]))
            continue
        wo = _words_of(FR, o["binary"], o["addr"], o["nins"])
        if wo is None:
            raise SystemExit("contained_scan: cannot stream %s:%s (R32)."
                             % (o["binary"], o["symbol"]))
        cset = set(pre_idx.get(tuple(FR.reg_fields(x) for x in wo[:8]), ())) | \
               set(suf_idx.get(tuple(FR.reg_fields(x) for x in wo[-8:]), ()))
        to = _tok_brmask(SI, wo)
        best = None
        for h in cset:
            n, bb, aa, wt = binfo[h]
            if n == o["nins"]:
                continue                         # same length = the hash/near tiers' territory
            tt = T(h)
            m = min(len(to), len(tt))
            lcp = 0
            while lcp < m and to[lcp] == tt[lcp]:
                lcp += 1
            lcs = 0
            while lcs < m - lcp and to[-1 - lcs] == tt[-1 - lcs]:
                lcs += 1
            if lcp + lcs < 14:                   # cheap gate; full verdict below is authoritative
                continue
            v = _contained_verdict(to, tt)
            if v is None or v["m_equal"] < min_cover * m:
                continue
            row = dict(open="%s:%s" % (o["binary"], o["symbol"]), addr="0x%08x" % o["addr"],
                       nins=o["nins"], twin="%s:0x%08x" % (bb, aa), twin_nins=n,
                       side=("open" if o["nins"] > n else "twin"),
                       cover=round(v["m_equal"] / m, 2), **v)
            if best is None or (row["nsub"] + row["k"], -row["cover"]) < \
                               (best["nsub"] + best["k"], -best["cover"]):
                best = row
        seen_hx[hx] = best
        if best is not None:
            best["d0_twin"] = for_stub(o["binary"], o["symbol"],
                                       include_linked=include_linked) is not None
            rows.append(best)

    stats = dict(scanned=n_scanned, of_reachable=len(open_rows), linked_skipped=linked_n,
                 min_cover=min_cover, min_side=min_side, banked_pool=len(binfo),
                 hits=len(rows))
    assert all(r["cover"] >= min_cover and r["k"] >= 1 for r in rows), "verdict invariant"
    return dict(rows=rows, stats=stats)


def contained_control(n_pos=60, n_neg=400, min_side=25):
    """R39 controls for the contained tier, self-contained so they never go stale.
    POSITIVE (must be perfect): plant the pair by construction — take a random banked body of
    >=min_side+10 ins, DELETE a random contiguous 5..30-token mid-block, and the classifier
    must report k=1, nsub=0, cover 1.0. Any other answer means the tier would refuse a
    textbook one-block twin: FAIL.
    NEGATIVE (base rate, context): random banked pairs sharing a prefix-8 OR suffix-8 skeleton
    bucket with different lengths — how often ARBITRARY same-shape pairs pass the verdict.
    True contained families inflate it; treat as an upper bound."""
    import random
    SI, FR = _near_mods()
    random.seed(42)
    _, banked, _ = _pool_and_open(False, "contained_control")
    pool = []
    for h, (n, locs) in banked.items():
        if n >= min_side + 10:
            w = _words_of(FR, locs[0][0], locs[0][1], n)
            if w is not None:
                pool.append(w)
        if len(pool) >= 4000:
            break
    ok = 0
    for i in range(n_pos):
        w = random.choice(pool)
        t = _tok_brmask(SI, w)
        glen = random.randint(5, min(30, len(t) - min_side))
        at = random.randint(4, len(t) - glen - 4)
        t2 = t[:at] + t[at + glen:]
        v = _contained_verdict(t, t2)
        if v and v["k"] == 1 and v["nsub"] == 0 and v["m_equal"] == len(t2):
            ok += 1
    print("POSITIVE control (planted one-block deletions): %d/%d classified k=1 sub=0 full-cover"
          % (ok, n_pos))
    if ok != n_pos:
        raise SystemExit("contained_control FAILED: the classifier refuses planted one-block "
                         "twins (R39).")
    hit = tot = 0
    for i in range(n_neg):
        w1, w2 = random.choice(pool), random.choice(pool)
        if len(w1) == len(w2):
            continue
        t1, t2 = _tok_brmask(SI, w1), _tok_brmask(SI, w2)
        m = min(len(t1), len(t2))
        v = _contained_verdict(t1, t2)
        tot += 1
        if v and v["m_equal"] >= 0.8 * m:
            hit += 1
    print("BASE RATE (random banked pairs, different lengths): %d/%d = %.2f%% pass "
          "cover>=0.8 — an UPPER bound (true contained families inflate it)"
          % (hit, tot, 100.0 * hit / max(tot, 1)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary")
    ap.add_argument("--fn")
    ap.add_argument("--all", action="store_true", help="every open stub fleet-wide")
    ap.add_argument("--json")
    ap.add_argument("--include-linked", action="store_true",
                    help="do NOT refuse targets in LINKED subsegs (dead text; see _linked_segs)")
    ap.add_argument("--near", action="store_true",
                    help="near tier: banked twins at edit distance 1..K too (venv-only)")
    ap.add_argument("--max-d", type=int, default=5, help="near tier distance cap K (default 5)")
    ap.add_argument("--near-control", action="store_true",
                    help="R39 controls for the near tier (positive + base rate)")
    ap.add_argument("--contained", action="store_true",
                    help="contained tier: banked twins 1..4 whole blocks away, any gap size "
                         "(venv-only)")
    ap.add_argument("--min-cover", type=float, default=0.8,
                    help="contained tier: equal-token cover floor over the shorter side")
    ap.add_argument("--contained-control", action="store_true",
                    help="R39 controls for the contained tier (planted positives + base rate)")
    a = ap.parse_args()

    if a.near_control:
        near_control(max_d=a.max_d)
        return 0

    if a.contained_control:
        contained_control()
        return 0

    if a.contained:
        out = contained_scan(min_cover=a.min_cover)
        s = out["stats"]
        print("contained tier: %d/%d stubs >=%d ins scanned (of %d reachable; +%d LINKED "
              "skipped) vs %d banked bodies · %d contained-twin rows (cover>=%.2f)"
              % (s["scanned"], s["scanned"], s["min_side"], s["of_reachable"],
                 s["linked_skipped"], s["banked_pool"], s["hits"], s["min_cover"]))
        for r in sorted(out["rows"], key=lambda r: (r["d0_twin"], r["gap"])):
            print("  %-30s %3d ins <- %-26s %3d  k=%d gap=%3d sub=%d cover=%.2f side=%s%s"
                  % (r["open"], r["nins"], r["twin"], r["twin_nins"], r["k"], r["gap"],
                     r["nsub"], r["cover"], r["side"],
                     "  [has d0 hash twin — prefer that]" if r["d0_twin"] else ""))
        if a.json:
            with open(a.json, "w") as fh:
                json.dump(out, fh, indent=1)
            print("wrote %s" % a.json)
        return 0

    if a.near:
        out = near_scan(max_d=a.max_d, include_linked=a.include_linked)
        s = out["stats"]
        print("near tier (K=%d): %d reachable open stubs (+%d LINKED skipped) · d=0 %d · "
              "d 1..%d %d (RELOC-ONLY %d / NEAR-COUSIN %d) · no twin %d · open-open clusters "
              "%d covering %d · cross-check %s"
              % (s["max_d"], s["reachable"], s["linked_skipped"], s["d0"], s["max_d"], s["near"],
                 s["reloc_only"], s["near_cousin"], s["no_twin"], s["clusters"],
                 s["cluster_stubs"], s["cross_check"]))
        for r in sorted((r for r in out["rows"] if r["d"]), key=lambda r: (r["d"], -r["nins"])):
            print("  d=%d %-11s %s:%s (%d ins)%s <- %s  %s"
                  % (r["d"], r.get("cls", ""), r["binary"], r["fn"], r["nins"],
                     " [jtbl]" if r["jtbl"] else "", r.get("twin", "?"),
                     "; ".join(r.get("diff", []))[:70]))
        if a.json:
            with open(a.json, "w") as fh:
                json.dump(out, fh, indent=1)
            print("wrote %s" % a.json)
        return 0

    if a.all:
        out, scanned, dead = [], 0, 0
        dead_by_bin = {}
        for b in progress.BINARIES:
            try:
                stubs = corpus.stubs(b)
            except Exception as e:
                print("  oracle refused %s: %r" % (b, e), file=sys.stderr)
                continue
            for s in stubs.values():
                scanned += 1
                if not a.include_linked and is_linked_stub(b, s):
                    # counted, never silent: a skipped population nobody counts is invisible (R32)
                    if for_stub(b, s.symbol, include_linked=True):
                        dead += 1
                        dead_by_bin[b] = dead_by_bin.get(b, 0) + 1
                    continue
                sr = for_stub(b, s.symbol, include_linked=a.include_linked)
                if sr:
                    out.append(sr)
        ref = sum(1 for x in out if x["mechanical_remap_refused"])
        print("open stubs scanned: %d · WITH a banked twin: %d (h_exact %d / h_norm %d) · "
              "of those, %d were already mechanically refused"
              % (scanned, len(out),
                 sum(1 for x in out if x["tier"] == "exact"),
                 sum(1 for x in out if x["tier"] == "norm"), ref))
        if dead:
            print("REFUSED %d twin(s) whose TARGET is a LINKED subseg — dead text, a draft there "
                  "gates GREEN while wrong (%s). Pass --include-linked to see them anyway."
                  % (dead, ", ".join("%s:%d" % kv for kv in sorted(dead_by_bin.items()))))
        if a.json:
            with open(a.json, "w") as fh:
                json.dump(out, fh, indent=1)
            print("wrote %s" % a.json)
        return 0

    if not (a.binary and a.fn):
        ap.error("give --binary/--fn or --all")
    sr = for_stub(a.binary, a.fn)
    print(json.dumps(sr, indent=1) if sr else "no banked twin")
    return 0


if __name__ == "__main__":
    sys.exit(main())
