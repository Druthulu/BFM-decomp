#!/usr/bin/env python3
"""P30 S49: the COUSIN-UNIT survey — similarity clustering over the open frontier.

WHY (the S49 finding, byte-verified): `h_seq` is an EXACT hash of the mnemonic skeleton, so one
inserted instruction makes two functions total strangers — and per-location compilation inserts
instructions constantly (a constant crossing the 16-bit `li` boundary becomes `lui+ori`, a bigger
jump table adds a case, a dropped flag test deletes one). Probed on the full frontier: 86/120
near-pairs in the 0.85-0.99 band differ by PURE insertion/deletion (25 with `lui` in the inserted
block — the li-expansion tell). The "4,513 unique singletons" picture was therefore substantially a
grouping artifact: e.g. ov_SC06_010:0x8017bebc (753 ins, "singleton") is 98.7% identical to a
MATCHED function in the same binary.

WHAT: group the distinct open skeletons (one per h_seq class, ×N copies collapsed first) by
mnemonic-stream SIMILARITY (difflib ratio over per-word mnemonic-class tokens — register/imm-blind
like h_seq, but comparable at <100% identity), union-find at >= SIM_MERGE, and attach the best
MATCHED skeleton seed to every unit. Categories:
  A-prop       — the unit contains a lane-A skeleton (matched sibling in-family): family_sweep work
  seeded       — best matched-skeleton similarity >= SIM_MERGE: crack by EDITING a proven C body
  cousin-multi — no seed, but >= 2 open instances in the unit: one crack seeds the rest
  cold         — genuinely alone at SIM_MERGE: the real unique tail
A unit is a CANDIDATE grouping for wave targeting: this survey RANKS and SEEDS; it never asserts a
match — the whole-binary byte-gate stays the sole arbiter (G3/P9). Skeleton drift means a cousin
needs a per-member recompile (a seeded CRACK), never a family_sweep remap.

HONEST LIMITS (encode, don't hide): short functions inflate similarity ratios (shared prologue
boilerplate), so consumers should discount seeds on small nins — the digest and targets carry nins
and seed similarity separately. SIM_WEAK..SIM_MERGE matches are annotated `weak_seed`, never merged.

  .venv/bin/python tools/family_cousins.py                 # survey -> .run/family_cousins.json + docs/family-cousins.md
  .venv/bin/python tools/family_cousins.py --targets 40    # wave slate (crack_wave.js arg shape) -> stdout JSON

R32: coverage-asserted BOTH ways — the open-instance total is re-derived from sigs+stubs
independently of the family map and must agree with it exactly (a stale map fails loud), and every
open h_seq class must land in exactly one unit. R33: stubs/matched derive from `corpus`, streams
from `family_remap.stream_words` — no private re-parsers.
"""
import argparse, collections, glob, json, os, re, subprocess, sys
from difflib import SequenceMatcher

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import family_remap as FR

FAMILY_MAP = ".run/family_hseq.json"
OUT_JSON = ".run/family_cousins.json"
OUT_MD = "docs/family-cousins.md"
SIM_MERGE = 0.85   # union-find + seed threshold (measured: this band is 72% pure-indel drift)
SIM_WEAK = 0.70    # annotate-only band
K = 8              # shingle length (mnemonic tokens)
CAP = 400          # drop shingles with posting lists longer than this (boilerplate)
TOPN_M, TOPN_O = 4, 3


def tok(w):
    """Mnemonic-CLASS token for one instruction word: opcode plus the fields that select the
    mnemonic (SPECIAL funct, REGIMM rt, coprocessor sub-op). Registers and immediates excluded —
    the same granularity family h_seq hashes, but kept as a sequence so ratios exist below 1.0."""
    op = w >> 26
    if op == 0:
        return (0, w & 0x3F)
    if op == 1:
        return (1, (w >> 16) & 0x1F)
    if op in (0x10, 0x11, 0x12, 0x13):
        return (op, (w >> 21) & 0x1F, w & 0x3F)
    return (op,)


def load_corpus():
    """-> (sigs, stubs) for every non-main binary with a src dir, sorted for determinism."""
    sigs, stubs = {}, {}
    for p in sorted(glob.glob(".run/sig.*.jsonl")):
        b = os.path.basename(p)[4:-6]
        if not (b.startswith("ov_") or b.startswith("md_") or b == "resident"):
            continue
        if not os.path.isdir("src/" + b):
            continue
        sigs[b] = {int(d["addr"], 16): d for d in map(json.loads, filter(str.strip, open(p)))}
        stubs[b] = set(corpus.stubs(b))
    return sigs, stubs


def load_open_units(sigs, stubs):
    """Open skeleton exemplars from the family map, R32-checked against an independent recount."""
    fam = json.load(open(FAMILY_MAP))
    open_ex = {}
    map_inst = 0
    for f in fam["families"]:
        if f["n_members"] == 0:
            continue
        lane = "A" if f["n_matched"] >= 1 else ("B" if f["n_members"] >= 2 else "C")
        e = f["exemplar"]
        b, a = e["ov"], int(e["addr"], 16)
        if b not in sigs or a not in sigs[b]:
            b, a = f["members"][0][0], int(f["members"][0][1], 16)
        open_ex[f["h_seq"]] = dict(b=b, a=a, nins=f["nins"], lane=lane,
                                   mem=f["n_members"], ins=f["n_members"] * f["nins"],
                                   jr=f["has_mid_jr"], members=f["members"])
        map_inst += f["n_members"]
    # R32: the over-approximating candidate set, derived WITHOUT the map.
    true_inst = sum(1 for b, m in sigs.items() for a in m if a in stubs[b])
    if true_inst != map_inst:
        sys.exit(f"R32: family map is STALE — sigs+stubs count {true_inst} open instances, "
                 f"the map holds {map_inst}. Regen first: make sig-overlays && make sig-modules "
                 f"&& make sig-resident && tools/family_hseq.py")
    return open_ex


def load_matched(sigs, stubs):
    """One representative per matched h_seq (same h_seq => same token stream, so any member do)."""
    matched = {}
    for b in sorted(sigs):
        st = stubs[b]
        for a in sorted(sigs[b]):
            d = sigs[b][a]
            if a not in st and d["h_seq"] not in matched:
                matched[d["h_seq"]] = (b, a, d["nins"])
    return matched


def streams_of(exmap):
    out = {}
    for hs in exmap:
        v = exmap[hs]
        b, a, n = (v["b"], v["a"], v["nins"]) if isinstance(v, dict) else v
        ws = FR.stream_words(b, a, n)
        if ws is None:
            sys.exit(f"R32: no image stream for {b}:{a:#x} — img_path/splat drift")
        out[hs] = tuple(tok(w) for w in ws)
    return out


def shingle_index(streams):
    ix = collections.defaultdict(list)
    for hs in sorted(streams):
        s = streams[hs]
        if len(s) < K:
            continue
        seen = set()
        for i in range(len(s) - K + 1):
            h = hash(s[i:i + K])
            if h not in seen:
                seen.add(h)
                ix[h].append(hs)
    return {h: v for h, v in ix.items() if len(v) <= CAP}


def best_match(s, index, streams, self_hs=None, topn=4):
    if len(s) < K:
        return 0.0, None
    cnt = collections.Counter()
    for i in range(len(s) - K + 1):
        for hs in index.get(hash(s[i:i + K]), ()):
            if hs != self_hs:
                cnt[hs] += 1
    best = (0.0, None)
    for hs, _ in cnt.most_common(topn):
        r = SequenceMatcher(None, s, streams[hs], autojunk=False).ratio()
        if r > best[0]:
            best = (r, hs)
    return best


def survey():
    sigs, stubs = load_corpus()
    open_ex = load_open_units(sigs, stubs)
    matched_ex = load_matched(sigs, stubs)
    S_open = streams_of(open_ex)
    S_m = streams_of(matched_ex)
    idx_m = shingle_index(S_m)
    idx_o = shingle_index(S_open)

    seed = {hs: best_match(S_open[hs], idx_m, S_m, topn=TOPN_M) for hs in sorted(S_open)}

    parent = {hs: hs for hs in S_open}
    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    for hs in sorted(S_open):
        r, other = best_match(S_open[hs], idx_o, S_open, self_hs=hs, topn=TOPN_O)
        if other and r >= SIM_MERGE:
            ra, rb = find(hs), find(other)
            if ra != rb:
                parent[ra] = rb

    clusters = collections.defaultdict(list)
    for hs in sorted(S_open):
        clusters[find(hs)].append(hs)

    units = []
    for root in sorted(clusters):
        members = clusters[root]
        lanes = {open_ex[hs]["lane"] for hs in members}
        inst = sum(open_ex[hs]["mem"] for hs in members)
        ins = sum(open_ex[hs]["ins"] for hs in members)
        bs_hs = max(members, key=lambda hs: seed[hs][0])
        bs, bref = seed[bs_hs]
        if "A" in lanes:
            cat = "A-prop"
        elif bs >= SIM_MERGE:
            cat = "seeded"
        elif inst >= 2:
            cat = "cousin-multi"
        else:
            cat = "cold"
        units.append(dict(
            cat=cat, n_skel=len(members), inst=inst, ins=ins,
            best_seed=round(bs, 3),
            weak_seed=bool(SIM_WEAK <= bs < SIM_MERGE),
            seed_ref=(list(matched_ex[bref][:2]) + [matched_ex[bref][2]]) if bref else None,
            skels=[dict(hs=hs, b=open_ex[hs]["b"], a=f'0x{open_ex[hs]["a"]:08x}',
                        nins=open_ex[hs]["nins"], lane=open_ex[hs]["lane"],
                        mem=open_ex[hs]["mem"], jr=open_ex[hs]["jr"],
                        seed_sim=round(seed[hs][0], 3)) for hs in members],
        ))
    units.sort(key=lambda u: -u["ins"])

    # R32 the other way: every open skeleton in exactly one unit; instance total exact.
    placed = [sk["hs"] for u in units for sk in u["skels"]]
    if len(placed) != len(set(placed)) or set(placed) != set(open_ex):
        sys.exit("R32: unit partition defect — an open skeleton is missing or double-placed")
    if sum(u["inst"] for u in units) != sum(v["mem"] for v in open_ex.values()):
        sys.exit("R32: unit instance total disagrees with the family map")

    head = subprocess.run(["git", "rev-parse", "--short", "HEAD"],
                          capture_output=True, text=True).stdout.strip()
    out = dict(sim_merge=SIM_MERGE, sim_weak=SIM_WEAK, k=K, head=head,
               n_units=len(units),
               totals={c: dict(units=sum(1 for u in units if u["cat"] == c),
                               inst=sum(u["inst"] for u in units if u["cat"] == c),
                               ins=sum(u["ins"] for u in units if u["cat"] == c))
                       for c in ("A-prop", "seeded", "cousin-multi", "cold")},
               units=units)
    json.dump(out, open(OUT_JSON, "w"))
    write_digest(out)
    t = out["totals"]
    print(f"units {len(units)} (of {len(open_ex)} skeletons) @>= {SIM_MERGE}: "
          + " · ".join(f'{c} {t[c]["units"]}u/{t[c]["inst"]}fn/{t[c]["ins"]}ins'
                       for c in ("A-prop", "seeded", "cousin-multi", "cold")))
    print(f"-> {OUT_JSON} + {OUT_MD}")
    return out


def write_digest(out):
    t = out["totals"]
    L = []
    L.append("# P30 S49 — cousin-unit survey (similarity tier over the open frontier)\n")
    L.append(f"> Generated by `tools/family_cousins.py` at HEAD `{out['head']}` from "
             f"`.run/family_hseq.json` + the binary sigs (R32-checked against an independent "
             f"stub recount — a stale map fails loud). Compare digests only at the same HEAD.\n>")
    L.append("> **A unit is a CANDIDATE grouping** — same-source cousins split by skeleton drift "
             "(insertion/deletion; the li-expansion class). Cousins need a per-member seeded CRACK, "
             "never a `family_sweep` remap. The whole-binary byte-gate stays the sole arbiter.\n")
    L.append(f"**Merge/seed threshold {out['sim_merge']}** (measured: 72% of this band is pure "
             f"indel drift) · weak-seed band {out['sim_weak']}–{out['sim_merge']} annotated, never "
             f"merged · short-nins seeds inflate — consumers discount below ~40 ins.\n")
    L.append("| category | units | open fns | open ins | lever |")
    L.append("|---|--:|--:|--:|---|")
    lever = {"A-prop": "family_sweep (propagation)",
             "seeded": "seeded crack — edit a >=0.85-similar MATCHED body",
             "cousin-multi": "1 crack seeds the unit's other members",
             "cold": "full-price crack (the honest unique tail)"}
    for c in ("A-prop", "seeded", "cousin-multi", "cold"):
        L.append(f'| {c} | {t[c]["units"]} | {t[c]["inst"]} | {t[c]["ins"]} | {lever[c]} |')
    L.append(f'| **total** | **{out["n_units"]}** | '
             f'**{sum(t[c]["inst"] for c in t)}** | **{sum(t[c]["ins"] for c in t)}** | |')
    L.append("\n## Top units by open instructions (whole-cluster weight)\n")
    L.append("| # | cat | ins | fns | skels | seed | seed ref | head skeleton |")
    L.append("|--:|---|--:|--:|--:|--:|---|---|")
    for i, u in enumerate(out["units"][:40], 1):
        hd = max(u["skels"], key=lambda s: s["mem"] * s["nins"])
        ref = f'`{u["seed_ref"][0]}:{u["seed_ref"][1]:#x}`' if u["seed_ref"] and u["best_seed"] >= out["sim_merge"] else "·"
        L.append(f'| {i} | {u["cat"]} | {u["ins"]} | {u["inst"]} | {u["n_skel"]} | '
                 f'{u["best_seed"] if u["best_seed"] >= out["sim_weak"] else "·"} | {ref} | '
                 f'`{hd["b"]}:{hd["a"]}` ({hd["nins"]} ins ×{hd["mem"]}{" jr" if hd["jr"] else ""}) |')
    open(OUT_MD, "w").write("\n".join(L) + "\n")


# ---------------------------------------------------------------- wave slate
def seed_body_ref(bin_, addr):
    """Where the seed's C body lives: engine_core.h DEFINE_ macro, or the inline def's src file."""
    name = f"func_{addr:08X}"
    core = "src/shared/engine_core.h"
    if os.path.exists(core) and f"DEFINE_{name}(" in open(core).read():
        return dict(kind="macro", path=core, name=name)
    for p in sorted(glob.glob(f"src/{bin_}/*.c")):
        txt = open(p).read()
        if re.search(rf"^[A-Za-z_][^\n=;]*\b{name}\s*\(", txt, re.M) and f"INCLUDE_ASM" not in \
           "".join(l for l in txt.splitlines() if name in l and "INCLUDE_ASM" in l):
            return dict(kind="inline", path=p, name=name)
    for p in sorted(glob.glob(f"src/{bin_}/*.c")):
        if f"DEFINE_{name}()" in open(p).read():
            return dict(kind="macro", path=core, name=name)
    return dict(kind="unresolved", path=None, name=name)


def prior_artifact_counts():
    att = collections.Counter()
    for d in sorted(glob.glob(".run/wave*/")) + [".run/jr48/"]:
        if not os.path.isdir(d):
            continue
        for e in os.listdir(d):
            m = re.fullmatch(r"func_([0-9A-Fa-f]{8})(\.c)?", e)
            if m:
                att["0x" + m.group(1).lower()] += 1
    for p in glob.glob(".run/backlog_drafts/*.c"):
        m = re.fullmatch(r"func_([0-9A-Fa-f]{8})\.c", os.path.basename(p))
        if m:
            att["0x" + m.group(1).lower()] += 1
    return att


def emit_targets(n, wave):
    out = json.load(open(OUT_JSON))
    att = prior_artifact_counts()
    prior_notes = set()
    if os.path.exists(".run/jr48/prior_notes.json"):
        prior_notes = set(json.load(open(".run/jr48/prior_notes.json")))
    targets = []
    for u in out["units"]:
        if u["cat"] == "A-prop":
            continue        # propagation work — family_sweep, not a wave
        hd = max(u["skels"], key=lambda s: s["mem"] * s["nins"])
        b, a = hd["b"], int(hd["a"], 16)
        name = f"func_{a:08X}"
        try:
            sub = os.path.dirname(corpus.asm_path(b, name))
        except Exception:
            sub = None
        seed = None
        if u["best_seed"] >= out["sim_merge"] and u["seed_ref"]:
            sb, sa, snins = u["seed_ref"]
            seed = dict(sim=u["best_seed"], bin=sb, addr=f"0x{sa:08x}", nins=snins,
                        **seed_body_ref(sb, sa))
        model = "haiku" if hd["nins"] <= 30 else ("sonnet" if hd["nins"] <= 120 else "opus")
        targets.append(dict(
            name=name, binary=b, sub=sub, nins=hd["nins"], reach=hd["mem"],
            jr=bool(hd["jr"]), model=model, wave=wave,
            prior=(name in prior_notes),
            prior_artifacts=att.get(hd["a"], 0),
            unit=dict(cat=u["cat"], ins=u["ins"], inst=u["inst"], n_skel=u["n_skel"]),
            seed=seed,
            cousins=[dict(b=s["b"], a=s["a"], nins=s["nins"], mem=s["mem"])
                     for s in u["skels"] if s is not hd][:12],
        ))
        if len(targets) >= n:
            break
    json.dump(targets, sys.stdout, indent=1)
    print(file=sys.stderr)
    seeded = sum(1 for t in targets if t["seed"])
    print(f"{len(targets)} targets · {sum(t['unit']['ins'] for t in targets)} unit ins · "
          f"{seeded} with seeds ({sum(1 for t in targets if t['seed'] and t['seed']['kind']=='unresolved')} "
          f"unresolved seed paths) · {sum(1 for t in targets if t['prior'])} prior-noted", file=sys.stderr)


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--targets", type=int, metavar="N", help="emit top-N wave targets (crack_wave.js shape) to stdout")
    ap.add_argument("--wave", default="wave7", help="wave tag stamped on targets (output dir routing)")
    args = ap.parse_args()
    if args.targets:
        if not os.path.exists(OUT_JSON):
            sys.exit(f"{OUT_JSON} missing — run the survey first")
        emit_targets(args.targets, args.wave)
    else:
        survey()
