#!/usr/bin/env python3
"""P31 T5 — the Frontier Atlas: every open stub in exactly one crack group, lever-labeled.

WHAT: joins the whole grouping ladder into ONE partition-asserted work queue over ALL open
functions (main included — the family/cousin maps exclude main by scope; the atlas attaches it
here, per the plan's Q4 decision, without widening those tools' consumers):

  T0  h_exact             (identical bytes — dedup territory, already banked machinery)
  T1  h_seq families      (.run/family_hseq.json — exact mnemonic skeleton)
  T2  cousin units @0.85  (.run/family_cousins.json — the S49 similarity tier)
  T1.5 h_seqn exact (NEW) — li-normalized skeletons (atlas_features.li_norm_toks) merge units
                            split only by constant-materialization length drift
  T3  seed sweep    (NEW) — every open skeleton vs the ~2.7k distinct MATCHED skeletons
                            (raw + normalized), best seed recorded ≥ SEED_FLOOR
  T4  warm tier     (NEW) — cold + main-only skeletons, feature-bucketed, in-bucket normalized
                            ratio, merged at THRESH_WARM (frozen by --calibrate, measured basis)
  T5  kNN graph     (NEW) — top-K open neighbors + top matched neighbors per open skeleton:
                            the "crack one, look around" layer the campaign walks after a bank
  tiny-direct             — nins<8 (shingle-blind by construction): exact-key groups only

plus the EVIDENCE joins (c294 audit + backlog + classified ledgers + cards) and a LEVER label
per group with confidence ∈ measured > ledger > tell > default > UNKNOWN (UNKNOWN is honest and
counted — never silently defaulted).

ARBITER NOTE: groups are ADVISORY — the whole-binary byte-gate stays the sole arbiter (G3/P9).
A warm-tier merge wastes at most an exemplar crack; it can never bank a wrong byte.

R32/R35: the atlas derives its OPEN SET from corpus.stubs (the oracle), asserts the partition,
asserts evidence accounting (unparsable = fatal), and stamps HEADs. Stale family/cousin maps are
tolerated ONLY in the banked-since direction (they can list already-banked members, which simply
have no open instances; an OPEN skeleton missing from the maps is fatal) — `make atlas` regenerates
the chain first so the normal path is always fresh.

  calibrate:  tools/atlas.py --calibrate          -> .run/atlas_calibration.json (+ table)
  survey:     tools/atlas.py                      -> .run/atlas.json + docs/frontier-atlas.md
  targets:    tools/atlas.py --targets 40 [--lever L] [--cat C] -> .run/atlas_targets.json
"""
import argparse, collections, glob, hashlib, json, os, random, re, subprocess, sys
from difflib import SequenceMatcher

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import family_remap as FR
import family_cousins as FC
from atlas_features import li_norm_toks

SEED_FLOOR = 0.55
K_SEED = 6            # candidate shingles for the seed sweep (looser than FC's K=8)
K_WARM = 5            # candidate shingles inside warm buckets
CAP = 400
CAL_PATH = ".run/atlas_calibration.json"
TINY = 8


def git_head():
    return subprocess.run(["git", "rev-parse", "--short=9", "HEAD"],
                          capture_output=True, text=True).stdout.strip()


def registry():
    import dup_report
    return sorted(dup_report.BINARIES)


# ------------------------------------------------------------------ open set (corpus-derived)

_MAIN_OPEN = None


def main_open_stubs():
    """Main's OPEN game-code set: corpus.stubs('main') minus the LINKED PsyQ-subseg stubs and
    minus progress's data BLOBS (INCLUDE_ASM-shaped data placeholders — not crackable code).
    Derived from the same oracles progress.py counts with (R33), and RECONCILED against its
    classify() buckets: open == stubs + nonmatching, exactly."""
    global _MAIN_OPEN
    if _MAIN_OPEN is not None:
        return _MAIN_OPEN
    import progress
    progress.set_binary("main")
    real, empty, nonmatching, stubs_l, blobs, linked_l = progress.classify()
    linked = set(progress.LINKED_SEGS)
    blob_names = set(blobs)
    out = {}
    for a, s in corpus.stubs("main").items():
        seg = s.asm_dir.rsplit("/", 1)[-1]
        if seg in linked or s.symbol in blob_names:
            continue
        out[a] = s
    want = len(stubs_l) + len(nonmatching)
    assert len(out) == want, (f"main open reconcile: filtered {len(out)} != "
                              f"classify stubs {len(stubs_l)} + NM {len(nonmatching)} (R32)")
    _MAIN_OPEN = out
    return out


def load_open():
    """{(b, addr) -> {name, nins, h_exact, h_seq, feat}} for every open instance, all binaries."""
    inst = {}
    for b in registry():
        st = main_open_stubs() if b == "main" else corpus.stubs(b)
        if not st:
            continue
        if b == "main":
            sigrows = {int(r["addr"], 16): r
                       for r in (json.loads(l) for l in open(".run/sig.main.jsonl")) }
        else:
            sigrows = corpus.sig(b)
        feats = {}
        fp = f".run/feat.{b}.jsonl"
        if not os.path.exists(fp):
            raise SystemExit(f"atlas: no {fp} — run atlas_features first (R32)")
        for l in open(fp):
            r = json.loads(l)
            feats[int(r["addr"], 16)] = r
        for a, s in sorted(st.items()):
            row = sigrows.get(a)
            f = feats.get(a)
            if row is None or f is None:
                raise SystemExit(f"atlas: open stub {b}:{a:#x} missing from sig/feat (R32)")
            inst[(b, a)] = {"name": s.symbol, "nins": row["nins"], "h_exact": row["h_exact"],
                            "h_seq": row["h_seq"], "feat": f}
    return inst


def skeletons(inst):
    """h_seq -> {'ex': (b,a,nins), 'members': [(b,a)], 'nins': int} over OPEN instances.
    Exemplar preference: ov_SC01_077 (the mother overlay, richest tooling) else first."""
    sk = {}
    for (b, a), v in sorted(inst.items()):
        hs = v["h_seq"]
        d = sk.setdefault(hs, {"ex": None, "members": [], "nins": v["nins"]})
        d["members"].append((b, a))
        if d["ex"] is None or (b == "ov_SC01_077" and d["ex"][0] != "ov_SC01_077"):
            d["ex"] = (b, a, v["nins"])
    return sk


# ------------------------------------------------------------------ streams + local shingles

def stream_pair(b, a, n):
    ws = FR.stream_words(b, a, n)
    if ws is None:
        raise SystemExit(f"atlas: no stream for {b}:{a:#x} (R32)")
    return tuple(FC.tok(w) for w in ws), tuple(li_norm_toks(ws))


def shingle(streams, k):
    ix = collections.defaultdict(list)
    for key in sorted(streams):
        s = streams[key]
        if len(s) < k:
            continue
        seen = set()
        for i in range(len(s) - k + 1):
            h = hash(s[i:i + k])
            if h not in seen:
                seen.add(h)
                ix[h].append(key)
    return {h: v for h, v in ix.items() if len(v) <= CAP}


def candidates(s, index, k, self_key=None, topn=12):
    if len(s) < k:
        return []
    cnt = collections.Counter()
    for i in range(len(s) - k + 1):
        for key in index.get(hash(s[i:i + k]), ()):
            if key != self_key:
                cnt[key] += 1
    return [key for key, _ in cnt.most_common(topn)]


def ratio(a, b):
    return SequenceMatcher(None, a, b, autojunk=False).ratio()


# ------------------------------------------------------------------ calibration

def calibrate(sk, streams_norm, unit_of, sample=4000):
    """Freeze THRESH_WARM/KNN_FLOOR from measured distributions: positives = skeleton pairs the
    cousin tier merged at >=0.85 RAW (ground truth of same-source kinship), negatives = size-matched
    random cross-unit pairs. Deterministic (seeded RNG)."""
    rng = random.Random(31)
    by_unit = collections.defaultdict(list)
    for hs, u in unit_of.items():
        if hs in streams_norm:
            by_unit[u].append(hs)
    pos_pairs = []
    for u, hss in by_unit.items():
        if len(hss) >= 2:
            hss = hss[:6]
            pos_pairs += [(x, y) for i, x in enumerate(hss) for y in hss[i + 1:]]
    rng.shuffle(pos_pairs)
    pos_pairs = pos_pairs[:sample]
    keys = sorted(streams_norm)
    by_size = collections.defaultdict(list)
    for hs in keys:
        by_size[len(streams_norm[hs]) // 16].append(hs)
    neg_pairs = []
    tries = 0
    while len(neg_pairs) < min(sample, 4000) and tries < sample * 20:
        tries += 1
        bucket = by_size[rng.choice(list(by_size))]
        if len(bucket) < 2:
            continue
        x, y = rng.sample(bucket, 2)
        if unit_of.get(x) != unit_of.get(y):
            neg_pairs.append((x, y))
    pos = sorted(ratio(streams_norm[x], streams_norm[y]) for x, y in pos_pairs)
    neg = sorted(ratio(streams_norm[x], streams_norm[y]) for x, y in neg_pairs)
    import bisect
    table = []
    best = None
    for t10 in range(50, 96):
        t = t10 / 100
        rec = 1 - bisect.bisect_left(pos, t) / max(1, len(pos))
        acc = 1 - bisect.bisect_left(neg, t) / max(1, len(neg))
        table.append({"t": t, "pos_recall": round(rec, 4), "neg_accept": round(acc, 4)})
        # a false warm-merge wastes an exemplar crack, a missed one only costs a cheaper tier —
        # so optimize for LOW false-accept first (<=0.2%), then recall (>=0.95).
        if rec >= 0.95 and acc <= 0.002 and best is None:
            best = t
    thresh = best if best is not None else 0.72
    cal = {"head": git_head(), "n_pos": len(pos), "n_neg": len(neg),
           "thresh_warm": thresh, "knn_floor": 0.55,
           "note": "thresh = smallest t with pos_recall>=0.95 and neg_accept<=0.002 "
                   "(false merges waste exemplar cracks; misses only route to a cheaper tier)",
           "table": [r for r in table if r["t"] in (0.55, 0.6, 0.65, 0.7, thresh, 0.75, 0.8, 0.85)]}
    json.dump(cal, open(CAL_PATH, "w"), indent=1)
    print(f"calibrate: pos={len(pos)} neg={len(neg)} -> THRESH_WARM={thresh} (table in {CAL_PATH})")
    for r in cal["table"]:
        print(f"  t={r['t']:.2f}  pos_recall={r['pos_recall']:.3f}  neg_accept={r['neg_accept']:.4f}")
    return cal


# ------------------------------------------------------------------ evidence

LEDGER_RE = re.compile(r"failed\.(?P<bin>[A-Za-z0-9_]+?)(?:\.\d+)?\.classified\.txt$")


def addr_of_name(name):
    m = re.search(r"_?([0-9A-Fa-f]{8})$", name or "")
    return int(m.group(1), 16) if m and m.group(1)[0] == "8" else None


def load_evidence(inst):
    """Per-member evidence + accounting. Every record: joined | gone (banked/not-open) |
    unparsable (FATAL)."""
    ev = collections.defaultdict(dict)          # (b,a) -> {source: value}
    acct = {}
    unparsable = []

    # c294 audit (freshest classified near-miss pile)
    p = ".run/c294/audit_results.json"
    joined = gone = 0
    if os.path.exists(p):
        for r in json.load(open(p)):
            a = addr_of_name(r.get("fn"))
            if a is None:
                unparsable.append(("audit", r.get("fn")))
                continue
            k = (r.get("binary"), a)
            if k in inst:
                ev[k]["audit"] = {"verdict": r["verdict"], "cls": r.get("cls"),
                                  "detail": r.get("detail", "")}
                joined += 1
            else:
                gone += 1
    acct["audit"] = {"joined": joined, "gone": gone}

    # backlog best-records
    joined = gone = 0
    try:
        import backlog as BL
        best = BL.load_best()
    except Exception:
        best = []
    for r in best:
        a = addr_of_name(r.get("name"))
        if a is None:
            unparsable.append(("backlog", r.get("name")))
            continue
        k = (r.get("binary"), a)
        if k in inst:
            ev[k]["backlog"] = {"closeness": r.get("closeness"), "status": r.get("status"),
                                "best_draft": r.get("best_draft")}
            joined += 1
        else:
            gone += 1
    acct["backlog"] = {"joined": joined, "gone": gone}

    # classified ledgers: newest mtime per (binary, fn)
    newest = {}
    files = glob.glob(".run/*failed*.classified.txt") + glob.glob(".run/c294/*failed*.classified.txt")
    for f in files:
        m = LEDGER_RE.search(os.path.basename(f))
        if not m:
            continue
        b = m.group("bin")
        mt = os.path.getmtime(f)
        for ln in open(f, errors="replace"):
            if "\t" not in ln:
                continue
            fn, verdict = ln.rstrip("\n").split("\t", 1)
            k2 = (b, fn)
            if k2 not in newest or newest[k2][0] < mt:
                newest[k2] = (mt, verdict)
    joined = gone = 0
    for (b, fn), (mt, verdict) in newest.items():
        a = addr_of_name(fn)
        if a is None:
            unparsable.append(("ledger", f"{b}:{fn}"))
            continue
        k = (b, a)
        if k in inst:
            ev[k]["ledger"] = verdict.split(":")[0].strip()
            ev[k]["ledger_detail"] = verdict[:160]
            joined += 1
        else:
            gone += 1
    acct["ledgers"] = {"files": len(files), "joined": joined, "gone": gone}

    # cards (lane annotations)
    for path, tag in ((".run/adapt_cards.json", "adapt_card"), (".run/aprop_cards.json", "aprop_card")):
        joined = gone = 0
        if os.path.exists(path):
            data = json.load(open(path))
            rows = data if isinstance(data, list) else []
            for r in rows:
                if tag == "adapt_card":
                    k = (r.get("binary"), r.get("addr") if isinstance(r.get("addr"), int)
                         else addr_of_name(r.get("name")))
                    if k in inst:
                        ev[k][tag] = r.get("klass")
                        joined += 1
                    else:
                        gone += 1
                else:
                    for mrow in r.get("members", []):
                        k = (mrow.get("binary"), mrow.get("addr") if isinstance(mrow.get("addr"), int)
                             else addr_of_name(mrow.get("name")))
                        if k in inst:
                            ev[k][tag] = r.get("cls")
                            joined += 1
                        else:
                            gone += 1
        acct[tag] = {"joined": joined, "gone": gone}

    # residuals: join only if fresher than its named-defect vintage
    p = ".run/autopsy/residuals.jsonl"
    if os.path.exists(p) and os.path.getmtime(p) > os.path.getmtime(".run/c294/audit_results.json"):
        joined = gone = 0
        for ln in open(p):
            r = json.loads(ln)
            a = addr_of_name(r.get("name"))
            k = (r.get("binary"), a)
            if a and k in inst:
                ev[k]["residual"] = {"bucket": r.get("bucket"), "klass": r.get("klass")}
                joined += 1
            else:
                gone += 1
        acct["residuals"] = {"state": "joined", "joined": joined, "gone": gone}
    else:
        acct["residuals"] = {"state": "EXCLUDED-STALE"}

    if unparsable:
        for src, name in unparsable[:10]:
            print(f"  UNPARSABLE {src}: {name}")
        raise SystemExit(f"atlas: {len(unparsable)} unparsable evidence records (R32)")
    return ev, acct


LEN_RE = re.compile(r"mine=(\d+) ins, target=(\d+) ins")


def member_lever(k, v, ev):
    """(lever, confidence) for one member; precedence measured > ledger > tell > default."""
    e = ev.get(k, {})
    a = e.get("audit")
    if a:
        cls = a.get("cls") or ""
        if a["verdict"] == "MATCH":
            return "integration", "measured"
        if a["verdict"] == "CC1":
            return "cc1", "measured"
        m = LEN_RE.search(a.get("detail", ""))
        if cls.startswith("LEN") and m:
            mine, tgt = int(m.group(1)), int(m.group(2))
            frac = abs(tgt - mine) / max(1, tgt)
            if frac > 0.35:
                return "redraft", "measured"
            return "len-vein", "measured"
        if cls.startswith("FRAME"):
            return "frame-172", "measured"
        if cls.startswith("SIGNLOAD"):
            return "signload", "measured"
        return "needs-autopsy", "measured"
    r = e.get("residual")
    if r and r.get("bucket"):
        return {"integration": "integration", "permuter": "permuter",
                "structural": "redraft", "redraft": "redraft"}.get(r["bucket"], "needs-autopsy"), "measured"
    # A "PURE" A-PROP CARD OUTRANKS A BARE LEDGER STRING (P31 S56, found by the 611-ins autopsy).
    #
    # `aprop_card` was collected at line ~324 and then NEVER READ -- `grep -n aprop tools/atlas.py`
    # returned exactly one hit, the loader. Meanwhile a bare `DIFF` token from a ledger promoted the
    # member to `needs-autopsy` at confidence "ledger" and the ladder returned there.
    #
    # Measured cost of that ordering: the func_801898E4 family (4 members x 611 ins = 2,444
    # instructions) carries `aprop_card: PURE` AND `seed: {sim 1.0, ref ov_SC04_018:0x80186E24}` --
    # i.e. a banked byte-identical twin and a relocation-only delta -- yet was labelled
    # needs-autopsy, so no sweep ever selected it. All four members matched from the twin with no
    # logic edits once anyone looked.
    #
    # PURE means the member differs from its seed only in per-location relocations; that is the
    # definition of a remap, and it is FRESH structural evidence. A ledger token is one historical
    # attempt with no draft path, no residual and no timestamp.
    ap = e.get("aprop_card")
    if isinstance(ap, str) and ap.upper() == "PURE":
        return "remap", "aprop-pure"

    led = e.get("ledger")
    if led:
        # PROVENANCE GATE. A ledger verdict is evidence about the draft that produced it, not about
        # the member. func_801898E4's DIFF came from .run/s34/.../func_801898E4.c dated 2026-08-04 --
        # SIX DAYS BEFORE its seed was banked (commit:1541, 2026-08-10). A 607-instruction hand-draft
        # that predates the 611-instruction twin cannot be evidence that remapping the twin fails.
        # When the record carries no usable provenance, say so in the confidence string rather than
        # presenting a stale token as a measurement (R35: fix the instrument before trusting it).
        conf = "ledger" if e.get("ledger_detail") else "ledger-bare"
        return {"PLUMBING": "plumbing", "CC1-FAIL": "cc1", "CC1-FAIL(no-diagnostic)": "cc1",
                "CARVE-REFUSED": "carve", "DIFF": "needs-autopsy"}.get(led, "needs-autopsy"), conf
    bl = e.get("backlog")
    if bl and isinstance(bl.get("closeness"), int) and bl["closeness"] <= 2:
        return "near-crack", "measured"
    f = v["feat"]
    if f.get("mid_jr"):
        return "jtbl-carve", "tell"
    if f.get("o0"):
        return "o0-lane", "tell"
    if f.get("extpair"):
        return "extend-tell", "tell"
    if f.get("dupselect"):
        return "swaprepeat-tell", "tell"
    if f.get("magic_div"):
        return "s16-div-tell", "tell"
    return None, None


_LEVER_RANK = ["integration", "plumbing", "near-crack", "len-vein", "frame-172", "signload",
               "carve", "cc1", "permuter", "jtbl-carve", "o0-lane", "extend-tell",
               "swaprepeat-tell", "s16-div-tell", "needs-autopsy", "redraft"]
_CONF_RANK = {"measured": 0, "ledger": 1, "tell": 2, "default": 3, "none": 4}


# ------------------------------------------------------------------ the survey

def survey(args):
    head = git_head()
    inst = load_open()
    sk = skeletons(inst)
    print(f"atlas: open instances={len(inst)} skeletons={len(sk)} (HEAD {head})")

    # cousin units (non-main baseline)
    fc = json.load(open(".run/family_cousins.json"))
    unit_of = {}
    unit_cat = {}
    for i, u in enumerate(fc["units"]):
        for s in u["skels"]:
            unit_of[s["hs"]] = i
        unit_cat[i] = u["cat"]
    missing = [hs for hs in sk if hs not in unit_of
               and not all(b == "main" for b, _ in sk[hs]["members"])]
    if missing:
        raise SystemExit(f"atlas: {len(missing)} open non-main skeletons missing from the cousin map "
                         f"— regenerate (make atlas runs the chain) (R32/R35)")

    # union-find over group nodes: cousin units + main-only skeleton nodes
    parent = {}

    def find(x):
        while parent.get(x, x) != x:
            parent[x] = parent.get(parent[x], parent[x])
            x = parent[x]
        return x

    def union(x, y):
        rx, ry = find(x), find(y)
        if rx != ry:
            parent[ry] = rx

    node_of = {}          # hs -> node key
    for hs in sk:
        if hs in unit_of:
            node_of[hs] = ("u", unit_of[hs])
        else:
            node_of[hs] = ("m", hs)      # main-only skeleton
        parent.setdefault(node_of[hs], node_of[hs])

    # main exact h_seq attach (hs equality with a fleet unit) is implicit: same hs string ->
    # unit_of hit above. (Measured at plan time: 38 main skeletons attach this way.)

    # T1.5: merge nodes sharing a member h_seqn
    by_seqn = collections.defaultdict(set)
    for (b, a), v in inst.items():
        by_seqn[v["feat"]["h_seqn"]].add(node_of[v["h_seq"]])
    t15_merges = 0
    for nodes in by_seqn.values():
        nodes = sorted(nodes)
        for other in nodes[1:]:
            if find(nodes[0]) != find(other):
                union(nodes[0], other)
                t15_merges += 1

    # streams for open skeleton exemplars (raw + norm)
    streams_raw, streams_norm = {}, {}
    for hs, d in sk.items():
        b, a, n = d["ex"]
        raw, norm = stream_pair(b, a, n)
        streams_raw[hs] = raw
        streams_norm[hs] = norm

    # calibration (already-frozen file, or freeze now with --calibrate)
    if args.calibrate or not os.path.exists(CAL_PATH):
        cal = calibrate(sk, streams_norm, unit_of)
        if args.calibrate:
            return
    else:
        cal = json.load(open(CAL_PATH))
    thresh_warm = cal["thresh_warm"]
    knn_floor = cal["knn_floor"]

    # T3 seed sweep: matched pool (non-main), dedup by h_seq
    pool = {}
    for b in registry():
        if b == "main":
            continue
        st = set(corpus.stubs(b))
        for a, r in corpus.sig(b).items():
            if a in st:
                continue
            hs = r["h_seq"]
            if hs not in pool or (b == "ov_SC01_077" and pool[hs][0] != "ov_SC01_077"):
                pool[hs] = (b, a, r["nins"])
    m_raw, m_norm = {}, {}
    for hs, (b, a, n) in pool.items():
        raw, norm = stream_pair(b, a, n)
        m_raw[hs] = raw
        m_norm[hs] = norm
    ix_m_raw = shingle(m_raw, K_SEED)
    ix_m_norm = shingle(m_norm, K_SEED)
    seed_best = {}
    for hs in sk:
        best = {"raw": (0.0, None), "norm": (0.0, None)}
        for tag, s, ix, streams in (("raw", streams_raw[hs], ix_m_raw, m_raw),
                                    ("norm", streams_norm[hs], ix_m_norm, m_norm)):
            for c in candidates(s, ix, K_SEED, topn=8):
                r = ratio(s, streams[c])
                if r > best[tag][0]:
                    best[tag] = (r, c)
        if best["raw"][0] >= SEED_FLOOR or best["norm"][0] >= SEED_FLOOR:
            seed_best[hs] = {t: {"sim": round(b_[0], 4),
                                 "ref": list(pool[b_[1]]) if b_[1] else None}
                             for t, b_ in best.items() if b_[0] >= SEED_FLOOR}

    # T4 warm tier over cold/main-only skeletons (tiny excluded)
    def node_cat(n):
        return unit_cat.get(n[1], "main-only") if n[0] == "u" else "main-only"

    warm_pool = [hs for hs in sk
                 if sk[hs]["nins"] >= TINY and node_cat(node_of[hs]) in ("cold", "main-only")]
    def bucket_key(hs):
        f = inst[sk[hs]["ex"][0], sk[hs]["ex"][1]]["feat"]
        return (f["band"], min(f["nblk"] // 4, 10), int(f["nback"] > 0),
                f["mid_jr"], f["o0"], min(f["frame"] // 32, 6))
    buckets = collections.defaultdict(list)
    for hs in warm_pool:
        buckets[bucket_key(hs)].append(hs)
    warm_merges = 0
    warm_ratio_calls = 0
    for bk, hss in buckets.items():
        if len(hss) < 2:
            continue
        if len(hss) > 200:
            sub = collections.defaultdict(list)
            for hs in hss:
                sub[sk[hs]["nins"] // 16].append(hs)
            groups = list(sub.values())
        else:
            groups = [hss]
        for grp in groups:
            if len(grp) < 2:
                continue
            local = {hs: streams_norm[hs] for hs in grp}
            ix = shingle(local, K_WARM)
            for hs in grp:
                s = streams_norm[hs]
                for c in candidates(s, ix, K_WARM, self_key=hs, topn=12):
                    if find(node_of[hs]) == find(node_of[c]):
                        continue
                    sm = SequenceMatcher(None, s, local[c], autojunk=False)
                    if sm.quick_ratio() < thresh_warm - 0.05:
                        continue
                    warm_ratio_calls += 1
                    if sm.ratio() >= thresh_warm:
                        union(node_of[hs], node_of[c])
                        warm_merges += 1

    # T5 kNN over all open skeletons (norm streams) + matched top-3
    ix_open = shingle({hs: streams_norm[hs] for hs in sk if len(streams_norm[hs]) >= K_WARM}, K_WARM)
    knn = {}
    for hs, d in sk.items():
        s = streams_norm[hs]
        neigh = []
        for c in candidates(s, ix_open, K_WARM, self_key=hs, topn=14):
            r = ratio(s, streams_norm[c])
            if r >= knn_floor:
                eb, ea, _ = sk[c]["ex"]
                neigh.append([f"{eb}:{ea:08x}", round(r, 3)])
        neigh.sort(key=lambda x: -x[1])
        matched_n = []
        sb = seed_best.get(hs, {})
        for t in ("norm", "raw"):
            if t in sb and sb[t]["ref"]:
                mb, ma, _ = sb[t]["ref"]
                matched_n.append([f"M:{mb}:{ma:08x}", sb[t]["sim"]])
        eb, ea, _ = d["ex"]
        knn[f"{eb}:{ea:08x}"] = neigh[:8] + matched_n[:3]

    # evidence + levers
    ev, acct = load_evidence(inst)

    # assemble groups
    comp = collections.defaultdict(list)
    for hs in sk:
        comp[find(node_of[hs])].append(hs)
    groups = []
    covered = 0
    for root, hss in comp.items():
        members = []
        cats = set()
        tiers = set()
        for hs in hss:
            n = node_of[hs]
            cats.add(node_cat(n))
            members += [(b, a, hs) for b, a in sk[hs]["members"]]
        if len(hss) > 1:
            tiers.add("hseqn/warm")
        covered += len(members)
        inst_rows = []
        lever_votes = []
        ins_total = 0
        tiny_all = all(inst[(b, a)]["nins"] < TINY for b, a, _ in members)
        for b, a, hs in members:
            v = inst[(b, a)]
            ins_total += v["nins"]
            lv, cf = member_lever((b, a), v, ev)
            if lv:
                lever_votes.append((lv, cf))
            e = ev.get((b, a), {})
            inst_rows.append({"b": b, "a": f"0x{a:08x}", "name": v["name"], "hs": hs[:12],
                              "nins": v["nins"],
                              **({"ev": {k2: e[k2] for k2 in e}} if e else {})})
        # cat precedence
        cat = ("A-prop" if "A-prop" in cats else
               "seeded" if "seeded" in cats else
               "tiny" if tiny_all else
               "cousin-multi" if (len(members) >= 2) else
               "cold" if "cold" in cats else "main-only")
        # group lever = best-ranked member vote; default by cat when no vote
        if lever_votes:
            lever_votes.sort(key=lambda x: (_CONF_RANK[x[1]], _LEVER_RANK.index(x[0])
                                            if x[0] in _LEVER_RANK else 99))
            lever, conf = lever_votes[0]
            alts = sorted({lv for lv, _ in lever_votes[1:]})
        else:
            lever, conf, alts = {"A-prop": ("family-sweep", "default"),
                                 "seeded": ("seeded-crack", "default"),
                                 "cousin-multi": ("head-crack", "default"),
                                 "tiny": ("tiny-direct", "default")}.get(
                cat, ("UNKNOWN", "none"))[0:2] + ([],)
            if isinstance(conf, tuple):
                lever, conf = conf
        exm = max(members, key=lambda m: inst[(m[0], m[1])]["nins"])
        ex_hs = exm[2]
        seed = seed_best.get(ex_hs)
        groups.append({
            "gid": hashlib.sha1(("|".join(sorted(f"{b}:{a:x}" for b, a, _ in members))).encode()
                                ).hexdigest()[:12],
            "cat": cat, "n_skel": len(hss), "inst": len(members), "ins": ins_total,
            "lever": lever, "confidence": conf, "lever_alts": alts,
            "exemplar": {"b": exm[0], "a": f"0x{exm[1]:08x}",
                         "name": inst[(exm[0], exm[1])]["name"],
                         "nins": inst[(exm[0], exm[1])]["nins"]},
            "seed": seed,
            "members": inst_rows,
        })
    groups.sort(key=lambda g: -g["ins"])

    # ---------------- assertions
    assert covered == len(inst), f"partition: covered {covered} != open {len(inst)} (R32)"
    seen_i = collections.Counter()
    for g in groups:
        for m in g["members"]:
            seen_i[(m["b"], m["a"])] += 1
    dup = [k for k, c in seen_i.items() if c > 1]
    assert not dup, f"partition: {len(dup)} instances in >1 group: {dup[:3]}"
    n_main = sum(1 for (b, _) in inst if b == "main")
    exp_main = len(main_open_stubs())
    assert n_main == exp_main, f"main reconcile: atlas {n_main} != corpus-filtered {exp_main}"

    by_cat = collections.defaultdict(lambda: [0, 0, 0])
    by_lever = collections.defaultdict(lambda: [0, 0, 0])
    for g in groups:
        for d, key in ((by_cat, g["cat"]), (by_lever, (g["lever"], g["confidence"]))):
            d[key][0] += 1
            d[key][1] += g["inst"]
            d[key][2] += g["ins"]

    out = {
        "head": head,
        "inputs": {"family_hseq": fc.get("head"), "cousins": fc.get("head"),
                   "calibration": {"thresh_warm": thresh_warm, "knn_floor": knn_floor},
                   "evidence": acct},
        "scope": {"binaries": len(registry()), "main": "atlas-layer join (family maps stay non-main)",
                  "open_instances": len(inst), "open_skeletons": len(sk),
                  "main_open": n_main},
        "tiers": {"t15_merges": t15_merges, "warm_merges": warm_merges,
                  "warm_ratio_calls": warm_ratio_calls,
                  "seeded_skeletons": len(seed_best), "matched_pool": len(pool)},
        "totals": {"groups": len(groups),
                   "by_cat": {k: v for k, v in sorted(by_cat.items())},
                   "by_lever": {f"{k[0]}[{k[1]}]": v for k, v in sorted(by_lever.items())}},
        "groups": groups,
        "knn": knn,
    }
    json.dump(out, open(".run/atlas.json", "w"))
    render(out)
    print(f"atlas: {len(groups)} groups / {len(inst)} instances / "
          f"{sum(g['ins'] for g in groups)} ins; t1.5 merges={t15_merges} warm merges={warm_merges}; "
          f"seeded {len(seed_best)}/{len(sk)} skeletons; UNKNOWN groups="
          f"{sum(1 for g in groups if g['lever'] == 'UNKNOWN')}")
    print("atlas: wrote .run/atlas.json + docs/frontier-atlas.md — all assertions green")


def render(out):
    L = []
    L.append(f"# The Frontier Atlas (P31 T5)\n")
    L.append(f"> Generated at HEAD `{out['head']}` by `tools/atlas.py` — REGENERATE, never edit. "
             f"Groups are ADVISORY (the byte-gate is the arbiter). Calibration: warm merge at "
             f"norm-ratio ≥ {out['inputs']['calibration']['thresh_warm']}, kNN floor "
             f"{out['inputs']['calibration']['knn_floor']}.\n")
    s = out["scope"]
    t = out["tiers"]
    L.append(f"**Scope:** {s['open_instances']} open instances / {s['open_skeletons']} skeletons "
             f"across {s['binaries']} binaries (main: {s['main_open']} — {s['main']}).  ")
    L.append(f"**Tiers:** T1.5 h_seqn merges {t['t15_merges']} · warm merges {t['warm_merges']} "
             f"(from {t['warm_ratio_calls']} ratio calls) · seed sweep: {t['seeded_skeletons']} "
             f"skeletons carry a ≥{SEED_FLOOR} seed from the {t['matched_pool']}-skeleton matched pool.\n")
    L.append("## Groups by category\n")
    L.append("| cat | groups | instances | ins |")
    L.append("|---|--:|--:|--:|")
    for k, v in out["totals"]["by_cat"].items():
        L.append(f"| {k} | {v[0]} | {v[1]} | {v[2]} |")
    L.append("\n## Groups by lever (confidence)\n")
    L.append("| lever | groups | instances | ins |")
    L.append("|---|--:|--:|--:|")
    for k, v in sorted(out["totals"]["by_lever"].items(), key=lambda kv: -kv[1][2]):
        L.append(f"| {k} | {v[0]} | {v[1]} | {v[2]} |")
    L.append("\n## Top 40 groups by open instructions\n")
    L.append("| gid | cat | lever | inst | ins | exemplar | seed |")
    L.append("|---|---|---|--:|--:|---|---|")
    for g in out["groups"][:40]:
        e = g["exemplar"]
        sd = ""
        if g.get("seed"):
            best = max(g["seed"].values(), key=lambda x: x["sim"])
            sd = f"{best['sim']:.2f}"
        L.append(f"| {g['gid']} | {g['cat']} | {g['lever']}[{g['confidence']}] | {g['inst']} | "
                 f"{g['ins']} | {e['b']}:{e['name']} ({e['nins']}) | {sd} |")
    L.append("")
    open("docs/frontier-atlas.md", "w").write("\n".join(L))


def targets(args):
    out = json.load(open(".run/atlas.json"))
    rows = []
    for g in out["groups"]:
        if args.lever and g["lever"] != args.lever:
            continue
        if args.cat and g["cat"] != args.cat:
            continue
        e = g["exemplar"]
        nins = e["nins"]
        model = "v3" if nins <= 15 else ("haiku" if nins <= 50 else
                                         "sonnet" if nins <= 120 else "opus")
        rows.append({"fn": e["name"], "binary": e["b"], "addr": e["a"], "nins": nins,
                     "cat": g["cat"], "tier_model": model, "lever": g["lever"],
                     "confidence": g["confidence"], "inst": g["inst"], "ins": g["ins"],
                     "seed": g.get("seed"), "gid": g["gid"],
                     "sub": FC.resolve_asm(e["b"], int(e["a"], 16)),
                     "knn": out["knn"].get(f"{e['b']}:{e['a'][2:]}", [])[:5]})
        if len(rows) >= args.targets:
            break
    json.dump(rows, open(".run/atlas_targets.json", "w"), indent=1)
    nosub = sum(1 for r in rows if not r["sub"])
    print(f"atlas targets: {len(rows)} rows -> .run/atlas_targets.json (unresolved .s: {nosub})")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--calibrate", action="store_true")
    ap.add_argument("--targets", type=int, default=0)
    ap.add_argument("--lever", default=None)
    ap.add_argument("--cat", default=None)
    a = ap.parse_args()
    if a.targets:
        targets(a)
    else:
        survey(a)


if __name__ == "__main__":
    main()
