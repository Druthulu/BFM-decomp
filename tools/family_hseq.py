#!/usr/bin/env python3
"""Phase-26 T1: the ranked h_seq FAMILY survey — the finish-the-decomp target map.

The Phase-25 close (R14): the "unique tail" is a strict-`h_norm` artifact. Re-cluster the unmatched frontier
by the looser `h_seq` (mnemonic skeleton — same instruction sequence, ignoring registers/immediates/relocs)
and ~90% collapses into per-location FAMILIES: the same engine fn recurring across ~120 overlays, differing
only in per-overlay symbols (RELOC, §40) + a few immediates (IMM, §46/T2a). This groups ALL unmatched overlay
instances by h_seq and, per family, classifies every member against an exemplar via the shared word-diff
classifier (family_remap.classify_member) into PURE (reloc-only, mechanically bankable now) / IMM (needs the
T2a immediate engine) / STRUCT (register-alloc drift or an h_seq collision — NOT templatable, excluded).

Matched-vs-unmatched = per-overlay INCLUDE_ASM stubs in that overlay's own src (ground truth; reproduces
progress.py's 74.8% fn / 58.2% instr / 30.3% distinct exactly). Exemplar pick, most-useful first: a MATCHED
member (its C exists → template for ~0 tokens; prefer ov_SC01_077) ▸ an unmatched ov_SC01_077 member (cached
Ghidra-C for drafting) ▸ the member at the family's modal address. The whole-binary byte-gate stays the sole
arbiter (G3/P9): this survey RANKS and CLASSES; it never asserts a match.

  .venv/bin/python tools/family_hseq.py
  -> .run/family_hseq.json (full, ranked by templatable byte-weight) + docs/family-hseq.md (digest, committed)

Ground truth = the sigs (`make sig-overlays`) + src stubs. Companion to tools/family_manifest.py (h_norm).
"""
import os, sys, json, glob, re, collections, subprocess
sys.path.insert(0, "tools")
import family_remap as FR

SUBSTANTIAL = 80          # nins >= this is the campaign band (below = mid/tiny, collision-prone)
TINY = 16                 # nins < this is the coincidental-h_seq-collision band (report, don't campaign)
EX_OV = "ov_SC01_077"     # the canonical drafting overlay (cached Ghidra-C)


sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus   # the derived corpus oracle (Phase 26-A)


def load():
    """-> instances[(ov, addr, nins, h_exact, h_norm, h_seq, matched)], and nins/matched maps."""
    # DERIVED from tools/corpus.py (Phase 26-A). The old scan globbed every .c correctly but its
    # regex only matched `func_<hex>` symbols — so the 100 CURATED-name stubs (listCdBuffer) were
    # invisible, and family_hseq therefore labelled 3 still-stubbed functions as MATCHED exemplars.
    # A phantom exemplar is re-nominated by every sweep, produces nothing, and books a silent skip.
    # P30 S44: widened from src/ov_* + sig.ov_* to EVERY non-main binary — the resident and the
    # md_* modules carry shareable engine functions too, and their absence here is why the R36
    # gate's family-map check (CHECK 4) could never see them. main stays excluded (structurally
    # barren — zero h_exact overlap, checked twice, S39).
    stubs = {b: set(corpus.stubs(b)) for b in
             (d.split("/")[-1] for d in sorted(glob.glob("src/ov_*")) + sorted(glob.glob("src/md_*")))}
    if os.path.isdir("src/resident"):
        stubs["resident"] = set(corpus.stubs("resident"))
    inst = []
    for p in sorted(glob.glob(".run/sig.ov_*.jsonl")) + sorted(glob.glob(".run/sig.md_*.jsonl")) \
             + sorted(glob.glob(".run/sig.resident.jsonl")):
        base = os.path.basename(p)[len("sig."):-len(".jsonl")]
        ov = base
        st = stubs.get(ov)
        if st is None:
            continue
        for line in open(p):
            line = line.strip()
            if not line:
                continue
            d = json.loads(line)
            a = int(d["addr"], 16)
            inst.append((ov, a, d["nins"], d["h_exact"], d["h_norm"], d["h_seq"], a not in st))
    return inst


def has_mid_jr(words):
    """a `jr` on a non-$ra register = a jump-table dispatch (rodata jtbl → §8 workflow risk)."""
    for w in words:
        if (w >> 26) == 0 and (w & 0x3F) == 0x08 and ((w >> 21) & 0x1F) != 31:
            return True
    return False


def pick_exemplar(members, matched):
    """(ov, addr, kind) — matched(ov077) ▸ matched(any) ▸ unmatched ov077 ▸ modal-addr member."""
    m077 = [m for m in matched if m[0] == EX_OV]
    if m077:
        return (m077[0][0], m077[0][1], "matched-ov077")
    if matched:
        m = min(matched, key=lambda x: (x[0], x[1]))
        return (m[0], m[1], "matched")
    u077 = [m for m in members if m[0] == EX_OV]
    if u077:
        return (u077[0][0], u077[0][1], "draft-ov077")
    modal = collections.Counter(a for _, a in members).most_common(1)[0][0]
    cand = sorted(m for m in members if m[1] == modal)
    return (cand[0][0], cand[0][1], "modal")


def main():
    inst = load()
    nins_of = {(o, a): n for o, a, n, *_ in inst}

    # ---- honest fleet metrics (cross-check vs progress.py --weighted) ----
    tot, tot_i = len(inst), sum(x[2] for x in inst)
    un = [x for x in inst if x[6] is False]
    un_i = sum(x[2] for x in un)
    ue = collections.defaultdict(list)
    for x in inst:
        ue[x[3]].append(x)
    mat_hex = {h for h, v in ue.items() if any(z[6] for z in v)}
    di_tot = sum(v[0][2] for v in ue.values())
    di_mat = sum(v[0][2] for h, v in ue.items() if h in mat_hex)
    metrics = {
        "fn_count_matched_pct": round(100 * (tot - len(un)) / tot, 1),
        "instr_weighted_matched_pct": round(100 * (tot_i - un_i) / tot_i, 1),
        "distinct_matched_pct": round(100 * di_mat / di_tot, 1),
        "unmatched_instances": len(un), "unmatched_ins": un_i,
        "distinct_unmatched_classes": len(ue) - len(mat_hex),
    }

    # ---- tail cross-check (reproduce the Phase-25 close: 663 families / 186 substantial / 1.85M ins) ----
    uncls = {h: v for h, v in ue.items() if h not in mat_hex}
    reach_hn = collections.Counter(v[0][4] for v in uncls.values())
    tail = {h: v for h, v in uncls.items() if reach_hn[v[0][4]] == 1}
    tfam = collections.defaultdict(list)
    for h, v in tail.items():
        tfam[v[0][5]].append(v[0])
    tmulti = {k: v for k, v in tfam.items() if len(v) >= 2}
    tsub = {k: v for k, v in tmulti.items() if v[0][2] >= SUBSTANTIAL}
    tailcheck = {
        "tail_fns": sum(len(v) for v in tail.values()), "tail_ins": sum(v[0][2] for v in tail.values()),
        "hseq_families_ge2": len(tmulti), "substantial_families": len(tsub),
        "substantial_ins": sum(x[2] for v in tsub.values() for x in v),
    }

    # ---- primary survey: ALL unmatched instances grouped by h_seq (the full frontier) ----
    by_seq = collections.defaultdict(lambda: {"members": [], "matched": []})
    for o, a, n, hx, hn, hs, matched in inst:
        (by_seq[hs]["matched"] if matched else by_seq[hs]["members"]).append((o, a))

    families = []
    for hs, g in by_seq.items():
        members, matched = g["members"], g["matched"]
        if not members:                                     # fully matched -> done
            continue
        nins = nins_of[members[0]]
        ex_ov, ex_addr, ex_kind = pick_exemplar(members, matched)
        ex_words = FR.stream_words(ex_ov, ex_addr, nins)
        cnt = {"PURE": 0, "IMM": 0, "STRUCT": 0, "LEN": 0}
        for (o, a) in members:
            if (o, a) == (ex_ov, ex_addr):
                cnt["PURE"] += 1                            # the exemplar vs itself is trivially pure
                continue
            cls, _ = FR.classify_member(ex_words, FR.stream_words(o, a, nins))
            cnt[cls] = cnt.get(cls, 0) + 1
        n_templatable = cnt["PURE"] + cnt["IMM"]
        diff_class = ("PURE" if cnt["IMM"] == 0 and cnt["STRUCT"] == 0 and cnt["LEN"] == 0
                      else "IMM" if cnt["STRUCT"] == 0 and cnt["LEN"] == 0 else "MIXED")
        addrs = {a for _, a in members}
        ovs = {o for o, _ in members}
        tag = ("per-location" if len(addrs) == 1
               else "cross-address" if len(addrs) <= 8 else "scattered")
        band = ("substantial" if nins >= SUBSTANTIAL else "tiny" if nins < TINY else "mid")
        families.append({
            "h_seq": hs, "nins": nins, "band": band,
            "n_members": len(members), "n_matched": len(matched), "n_templatable": n_templatable,
            "n_addrs": len(addrs), "n_ovs": len(ovs), "addr_tag": tag,
            "diff_class": diff_class, "cls_counts": cnt, "has_mid_jr": has_mid_jr(ex_words or []),
            "byte_weight_templatable": n_templatable * nins * 4,
            "byte_weight_all": len(members) * nins * 4,
            "exemplar": {"ov": ex_ov, "addr": f"0x{ex_addr:08x}", "kind": ex_kind},
            "members": [[o, f"0x{a:08x}"] for o, a in sorted(members)],
            "matched_members": [[o, f"0x{a:08x}"] for o, a in sorted(matched)],
        })
    families.sort(key=lambda f: -f["byte_weight_templatable"])

    out = {"metrics": metrics, "tailcheck": tailcheck, "families": families}
    json.dump(out, open(".run/family_hseq.json", "w"))

    # ---- digest ----
    multi = [f for f in families if f["n_members"] >= 2 or f["n_matched"] >= 1]
    singles = [f for f in families if f not in multi]
    subst = [f for f in multi if f["band"] == "substantial"]
    with_matched = [f for f in subst if f["n_matched"] >= 1]
    templ_ins_subst = sum(f["byte_weight_templatable"] for f in subst) // 4
    L = []
    L.append("# Phase 26 — h_seq family survey (T1)\n")
    # R32/R36: report the scope we ACTUALLY scanned, never a hardcoded count. The literal "134" sat
    # here while the tool (correctly, via the src/ov_* + sig.ov_* globs) scanned 138 — a generated
    # doc that misreports its own scope reads exactly like a tool that missed 4 binaries.
    n_sigs = len(glob.glob(".run/sig.ov_*.jsonl")) + len(glob.glob(".run/sig.md_*.jsonl")) \
             + len(glob.glob(".run/sig.resident.jsonl"))   # the SAME globs load() scans — cannot drift
    # P30 T0c: stamp scope + tree state. The "family_hseq 29,961 vs progress 28,296" carried defect
    # was a CROSS-DATE, CROSS-SCOPE misread of two digests (the 07-29 map @ SESSION-25-open vs the
    # 07-30 fleet digest; the delta was exactly the 2,713 banked between). The tools share one
    # oracle (corpus.stubs, line ~42) — same-tree totals agree by construction. The stamp makes a
    # stale or scope-mismatched comparison self-announcing instead of a phantom R32 gap.
    try:
        _head = subprocess.run(["git", "rev-parse", "--short", "HEAD"], capture_output=True,
                               text=True).stdout.strip() or "?"
    except Exception:
        _head = "?"
    L.append(f"> Generated by `tools/family_hseq.py` from the {n_sigs} overlay sigs + per-overlay src stubs. "
             f"Ranked by TEMPLATABLE byte-weight (PURE+IMM members × nins × 4). The byte-gate is the arbiter.\n>\n"
             f"> **Scope: the {n_sigs} OVERLAYS only** (no main, no resident) · generated at HEAD `{_head}` · "
             f"stub set derived from `corpus.stubs` — the same oracle `progress.py` counts, so same-tree "
             f"overlay totals agree by construction; compare digests only at the same HEAD.\n")
    L.append(f"**Fleet (overlays):** {metrics['fn_count_matched_pct']}% fn / "
             f"{metrics['instr_weighted_matched_pct']}% instr / {metrics['distinct_matched_pct']}% distinct-code "
             f"matched. Unmatched: {metrics['unmatched_instances']:,} instances / {metrics['unmatched_ins']:,} ins "
             f"({metrics['distinct_unmatched_classes']:,} distinct classes).\n")
    L.append(f"**Tail cross-check (Phase-25 close):** {tailcheck['tail_fns']:,} tail fns / "
             f"{tailcheck['tail_ins']:,} ins → {tailcheck['hseq_families_ge2']} h_seq families ≥2, "
             f"**{tailcheck['substantial_families']} substantial (nins≥{SUBSTANTIAL}) / "
             f"{tailcheck['substantial_ins']:,} ins**.\n")
    tw = sum(f['cls_counts']['PURE'] for f in subst)
    ti = sum(f['cls_counts']['IMM'] for f in subst)
    ts = sum(f['cls_counts']['STRUCT'] for f in subst)
    L.append(f"**Full frontier (all unmatched by h_seq):** {len(multi)} target families "
             f"(≥2 members or a matched sibling) + {len(singles)} singletons (Step-D residue). "
             f"Substantial: **{len(subst)} families / {templ_ins_subst:,} templatable ins**, "
             f"{len(with_matched)} with a matched sibling (zero-crack). "
             f"Substantial member classes: {tw:,} PURE · {ti:,} IMM · {ts:,} STRUCT-excluded.\n")
    L.append("\n## Top substantial families (by templatable byte-weight)\n")
    L.append("| # | nins | members (P/I/S) | #addr/#ov | tag | class | matched | jr | exemplar | templ. ins |")
    L.append("|--:|--:|--|--|--|--|--:|:-:|--|--:|")
    for i, f in enumerate(subst[:50], 1):
        c = f["cls_counts"]
        L.append(f"| {i} | {f['nins']} | {f['n_members']} ({c['PURE']}/{c['IMM']}/{c['STRUCT']}) | "
                 f"{f['n_addrs']}/{f['n_ovs']} | {f['addr_tag']} | {f['diff_class']} | {f['n_matched']} | "
                 f"{'Y' if f['has_mid_jr'] else '·'} | {f['exemplar']['addr']} {f['exemplar']['kind']} | "
                 f"{f['byte_weight_templatable']//4:,} |")
    open("docs/family-hseq.md", "w").write("\n".join(L) + "\n")

    # OVERLAYS-ONLY, and say so ON STDOUT. load() globs .run/sig.ov_*.jsonl — main and the resident
    # are NOT in these denominators, so every number here runs ~0.3-1.0pp ABOVE the authoritative
    # `make report` / docs/progress.fleet.md fleet numbers. docs/family-hseq.md has always carried
    # the "(overlays)" qualifier; this print did not — and stdout is the channel a session actually
    # reads and transcribes into a checkpoint, which is how a wrong-labelled right number spreads
    # (R35: the measurement was fine, the instrument's LABEL was the defect).
    print(f"fleet (OVERLAYS ONLY — not comparable to `make report`; excludes main + resident): "
          f"{metrics['fn_count_matched_pct']}% fn / {metrics['instr_weighted_matched_pct']}% instr / "
          f"{metrics['distinct_matched_pct']}% distinct")
    print(f"tailcheck: {tailcheck['hseq_families_ge2']} families ≥2, {tailcheck['substantial_families']} "
          f"substantial / {tailcheck['substantial_ins']:,} ins"
          f"   [Task-2 snapshot 2026-07-11: 663 / 186 / 1.85M — this number SHRINKS as banking "
          f"proceeds; it is a point-in-time reference, NOT an invariant to match]")
    print(f"frontier: {len(multi)} target families ({len(subst)} substantial, {len(with_matched)} w/ matched sib) "
          f"+ {len(singles)} singletons")
    print(f"-> .run/family_hseq.json + docs/family-hseq.md")


if __name__ == "__main__":
    main()
