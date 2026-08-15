#!/usr/bin/env python3
"""P31 T9 — the permuter/grinder FEEDER: warm-start drafts from banked exemplars + routed fuel.

WHY: the grinder's own audit (Phase-22) showed 92% of its CPU went where the permuter provably
cannot win; its targeting fix admits autopsy `bucket=="permuter"` and — deliberately — KEEPS
unclassified records ("unknown is not a reason to skip", R32). So a feeder that enqueues ONLY
pre-verified permuter-shaped work needs NO grinder patch: it appends backlog near-records
(source=warmstart) whose drafts are remapped PROVEN sibling bodies, and the daemon picks them up.

Modes:
  --from-banked fn[,fn…] --binary B   for each newly-banked exemplar: walk its h_seq family's
      still-open members (the atlas group's mechanical remainder); for each, build the remapped
      seed draft (family_remap.symbol_map — refuses on reloc-count mismatch) and STREAM-CLASSIFY
      member-vs-seed with ZERO compiles (both are ground-truth bytes); enqueue only
      bucket==permuter or LENGTH-DRIFT |Δ|<=2.
  --lenmiss   ingest .run/lenmiss/permuter.json (T8's |Δ|<=2 clean-drift route, drafts already
      on disk) as warmstart backlog records.

The whole-binary byte-gate remains the arbiter; a wrong enqueue costs grinder CPU, never a byte.
"""
import argparse, json, os, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog
import corpus
import family_remap as FR
import family_cousins as FC
import aprop_autodraft as APD
import residual_class
import sig_image


def stream_dicts(words, vram=0x80100000):
    """words -> masked_diff-shaped [{word, mnem, reloc_kind, reloc_op}] for classify_streams
    (zero compiles: both sides are ground-truth bytes)."""
    rel = FR.reloc_indices(words)
    out = []
    pending_hi = set()
    for k, w in enumerate(words):
        ins = sig_image.make_insn(w, vram + 4 * k)
        mnem = ins.getOpcodeName().lower() if ins.isValid() else "?"
        kind = None
        if k in rel:
            op = w >> 26
            if op in (2, 3):
                kind = "R_MIPS_26"
            elif op == 0x0F:
                kind = "R_MIPS_HI16"
                pending_hi.add((w >> 16) & 31)
            else:
                kind = "R_MIPS_LO16"
        out.append({"word": w, "mnem": mnem, "reloc_kind": kind, "reloc_op": None})
    return out


def classify_pair(seed_words, member_words):
    """-> verdict dict from residual_class over the two byte-truth streams."""
    return residual_class.classify_streams(stream_dicts(seed_words), stream_dicts(member_words))


def enqueue(rec, dry):
    if dry:
        print("  would enqueue:", rec["binary"], rec["name"], rec.get("klass"))
        return
    backlog.append_record(rec)


def from_banked(fns, binary, outdir, dry):
    fam = json.load(open(".run/family_hseq.json"))["families"]
    by_hs = {}
    sig = corpus.sig(binary)
    n_enq = n_ref = 0
    for fn in fns:
        addr = int(fn.split("_")[1], 16)
        row = sig.get(addr)
        if row is None:
            print(f"  {fn}: not in {binary}'s sig — skipped")
            continue
        hs = row["h_seq"]
        f = next((x for x in fam if x["h_seq"] == hs), None)
        if f is None:
            print(f"  {fn}: no family for its h_seq — ×1 bank, nothing to seed")
            continue
        seed_words = FR.stream_words(binary, addr, row["nins"])
        body_ref = FC.seed_body_ref(binary, addr)
        if not body_ref or body_ref.get("kind") == "unresolved":
            print(f"  {fn}: seed body unresolved — skipped")
            continue
        body, seed_text, _kind = APD.seed_body(body_ref, fn)
        if body is None:
            print(f"  {fn}: seed body unreadable — skipped")
            continue
        for m in f["members"]:
            mb, ma = m[0], (m[1] if isinstance(m[1], int) else int(str(m[1]), 16))
            if mb == binary and ma == addr:
                continue
            st = corpus.stubs(mb)
            if ma not in st:
                continue                                   # already banked
            member_words = FR.stream_words(mb, ma, f["nins"])
            if member_words is None:
                continue
            v = classify_pair(seed_words, member_words)
            klass = v.get("klass")
            delta = len(member_words) - len(seed_words)
            ok = (v.get("bucket") == "permuter") or (klass == "LENGTH-DRIFT" and abs(delta) <= 2)
            if not ok:
                n_ref += 1
                continue
            mfn = st[ma].symbol
            try:
                renames, sm_err = FR.symbol_map(addr, binary, mb, to_addr=ma)
            except Exception as e:
                renames, sm_err = None, repr(e)[:60]
            if renames is None:
                print(f"  {mfn}: symbol_map refused ({sm_err})")
                n_ref += 1
                continue
            draft, skip = APD.build_draft(body, fn, mfn, renames, seed_text, "")
            if draft is None:
                print(f"  {mfn}: build_draft skipped ({skip})")
                n_ref += 1
                continue
            os.makedirs(f"{outdir}/{mb}", exist_ok=True)
            p = f"{outdir}/{mb}/{mfn}.c"
            open(p, "w").write(draft)
            enqueue({"name": mfn, "binary": mb, "status": "near", "source": "warmstart",
                     "klass": v.get("profile") or klass, "closeness": v.get("closeness"),
                     "best_draft": p, "where_stuck": f"warmstart from {binary}:{fn}"}, dry)
            n_enq += 1
    print(f"warmstart --from-banked: enqueued {n_enq}, refused {n_ref}")


def from_lenmiss(dry):
    rows = json.load(open(".run/lenmiss/permuter.json"))
    n = 0
    for r in rows:
        enqueue({"name": r["fn"], "binary": r["binary"], "status": "near",
                 "source": "warmstart", "klass": "LENGTH-DRIFT",
                 "closeness": abs(r.get("delta") or 0),
                 "best_draft": r["draft"],
                 "where_stuck": "lenmiss permuter-length route"}, dry)
        n += 1
    print(f"warmstart --lenmiss: enqueued {n}")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--from-banked", default=None, help="comma-separated banked fn names")
    ap.add_argument("--binary", default=None)
    ap.add_argument("--lenmiss", action="store_true")
    ap.add_argument("--outdir", default=".run/warmstart")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    if a.lenmiss:
        from_lenmiss(a.dry_run)
    if a.from_banked:
        if not a.binary:
            sys.exit("--from-banked needs --binary")
        from_banked([x.strip() for x in a.from_banked.split(",") if x.strip()],
                    a.binary, a.outdir, a.dry_run)
    if not a.lenmiss and not a.from_banked:
        sys.exit("nothing to do: pass --lenmiss and/or --from-banked")


if __name__ == "__main__":
    main()
