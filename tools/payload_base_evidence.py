#!/usr/bin/env python3
"""payload_base_evidence.py — static, controls-gated base evidence for a never-onboarded disc payload (P32 T2a).

A module's own bytes constrain WHERE it loads in three ways, none of which the S45 shape-scans used together:
  * absolute pointers (its header fn-ptr table / data pointers) must land INSIDE the module at its base;
  * `jal` targets that are self-calls must land ON the module's own function prologues at its base (a
    module that calls itself even once pins its base exactly — MAIN/7 lands 9/9 at 0x800CEDF8, MAIN/9
    fits exactly one base, 0x800CD348);
  * `lui` hi-halves of its address materialisations must be able to reach [base, base+size).
The candidate list is BOUNDED, never searched: the five §S44 module slots, every DESTPTR the IDXTAB map
recorded (`.run/idxtab_map.json`, 134 distinct), and the jal->prologue vote's top bases. Each candidate is
scored and ranked; the byte gate (`tools/new_binary.sh` first build) remains the arbiter (P9).

R39 controls (`--controls`): the byte-proven bases of seven banked modules must come out TOP-RANKED from
their payloads alone, or the tool exits 2 and emits nothing. R43: a payload with NO self-reference at any
candidate (no internal pointers, no internal jals, no reachable lui) is REFUSED as base-independent — its
bytes cannot discriminate a base, and the gate cannot either; say so, do not guess.

  tools/payload_base_evidence.py --controls
  tools/payload_base_evidence.py extracted/retail/MAIN.CD.dir/FILE_007 [--text-lo 0x34] [--json out.json]
"""
import argparse, json, os, struct, sys, collections

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SLOTS = {0x800CEDF8: "boot/resident slot", 0x800CAE08: "slot A (md_MAIN_013..041)", 0x800CCB1C: "slot B (md_MAIN_042..047)",
         0x801A00D8: "SC07 slot", 0x801EF468: "script slot (ov_SC03_001 DESTPTR)"}
# byte-proven bases (config/splat.<alias>.yaml vram + the yaml's first `c` offset) — the R39 control set
CONTROLS = [("md_MAIN_008", "extracted/retail/MAIN.CD.dir/FILE_008.dir/1.1", 0x800CEDF8, 0x4),
            ("md_MAIN_011", "extracted/retail/MAIN.CD.dir/FILE_011.dir/1.1", 0x800CEDF8, 0x7C),
            ("md_MAIN_013", "extracted/retail/MAIN.CD.dir/FILE_013.dir/1.1", 0x800CAE08, 0x4),
            ("md_MAIN_042", "extracted/retail/MAIN.CD.dir/FILE_042.dir/0.1", 0x800CCB1C, 0x4),
            ("md_SC03_073", "extracted/retail/SC03.CD.dir/FILE_073.dir/2.1", 0x801EF468, 0x14),
            ("md_SC02_009", "extracted/retail/SC02.CD.dir/FILE_009.dir/0.1", 0x801E4C60, 0x4),
            ("md_SC07_004", "extracted/retail/SC07.CD.dir/FILE_004.dir/1.1", 0x801A00D8, 0x158)]


def destptrs():
    p = os.path.join(REPO, ".run/idxtab_map.json")
    if not os.path.exists(p):
        return {}
    m = json.load(open(p))
    out = {}
    for b in m.get("binaries", []):
        for d in b.get("destptrs") or []:
            v = d.get("dest")
            if isinstance(v, int):
                out.setdefault(v, []).append(b["alias"])
    return out


def words(b):
    return [struct.unpack_from("<I", b, i)[0] for i in range(0, len(b) - 3, 4)]


def analyse(path, text_lo=None, extra_bases=()):
    b = open(path, "rb").read(); n = len(b); w = words(b)
    pro = [i * 4 for i, x in enumerate(w) if (x >> 16) == 0x27BD and (x & 0x8000)]
    jr = [i * 4 for i, x in enumerate(w) if x == 0x03E00008]
    if text_lo is None:
        text_lo = pro[0] if pro else 0
    code_end = min(n, jr[-1] + 8) if jr else n      # last `jr $ra` + its delay slot (byte offsets)
    ptrs = [(i * 4, x) for i, x in enumerate(w) if 0x80010000 <= x < 0x80200000]
    lui = collections.Counter(); jals = []
    for i in range(text_lo // 4, code_end // 4):
        x = w[i]; op = x >> 26
        if op == 0x0F:
            lui[x & 0xFFFF] += 1
        elif op == 0x03:
            jals.append(0x80000000 | ((x & 0x3FFFFFF) << 2))
    # FUNCTION STARTS = frame prologues + the word after every `jr $ra`+delay-slot pair inside the code span
    # (leaf functions have NO prologue — S45's lesson; a self-call into a leaf would otherwise read as a MISS)
    starts = set(pro) | {j + 8 for j in jr if text_lo <= j + 8 < code_end} | {text_lo}
    proset = starts
    # jal -> prologue vote: every (target - prologue) pair is a candidate base; >=2 hits = a self-calling module
    vote = collections.Counter()
    for t in set(jals):
        for q in starts:
            base = t - q
            if 0x80000000 <= base < 0x80200000 and base % 4 == 0:
                vote[base] += 1
    vote_top = [(bse, c) for bse, c in vote.most_common(6) if c >= 2]
    dp = destptrs()
    cands = set(SLOTS) | set(dp) | {bse for bse, _ in vote_top} | set(extra_bases)
    rows = []
    for base in sorted(cands):
        lo, hi = base, base + n
        in_ptrs = [x for _, x in ptrs if lo <= x < hi]
        in_ptrs_on_pro = sum(1 for x in in_ptrs if (x - base) in proset)
        ij = [t for t in jals if lo <= t < hi]
        ij_on_pro = sum(1 for t in ij if (t - base) in proset)
        # lui hi-halves that can reach [lo,hi) with a signed lo16
        reach = sum(c for h, c in lui.items() if (h << 16) - 0x8000 < hi and (h << 16) + 0x7FFF >= lo)
        self_ref = bool(in_ptrs) or bool(ij) or reach > 0
        if ij and ij_on_pro == len(ij):
            verdict = "STRONG" if ij_on_pro >= 2 else "CONSISTENT"
        elif ij and ij_on_pro < len(ij):
            verdict = "INCONSISTENT"      # an internal jal that misses every prologue: not this base
        elif in_ptrs or reach:
            verdict = "CONSISTENT"
        else:
            verdict = "NO-EVIDENCE"
        score = (ij_on_pro * 100) - (len(ij) - ij_on_pro) * 1000 + in_ptrs_on_pro * 10 + len(in_ptrs) + (1 if reach else 0)
        rows.append({"base": base, "label": SLOTS.get(base) or ("DESTPTR of " + ",".join(dp.get(base, [])[:3])) if (base in SLOTS or base in dp) else "jal-vote",
                     "internal_ptrs": len(in_ptrs), "internal_ptrs_on_prologue": in_ptrs_on_pro,
                     "internal_jals": len(ij), "internal_jals_on_prologue": ij_on_pro, "lui_reach": reach,
                     "verdict": verdict, "score": score, "self_ref": self_ref})
    rows.sort(key=lambda r: -r["score"])
    any_self = any(r["self_ref"] for r in rows)
    return {"payload": os.path.relpath(path, REPO), "size": n, "id_word": w[0], "text_lo": text_lo, "code_end": code_end,
            "n_prologues": len(pro), "n_jr_ra": len(jr), "n_abs_ptrs": len(ptrs),
            "lui_top": [(hex(h), c) for h, c in lui.most_common(6)], "jal_vote_top": [(hex(b_), c) for b_, c in vote_top],
            "base_independent": not any_self, "candidates": rows[:12]}


def render(r):
    print(f"{r['payload']}: size 0x{r['size']:X} id=0x{r['id_word']:X} TEXT_LO=0x{r['text_lo']:X} prologues={r['n_prologues']} "
          f"jr_ra={r['n_jr_ra']} abs_ptrs={r['n_abs_ptrs']} lui_top={r['lui_top'][:4]} jal_vote={r['jal_vote_top']}")
    if r["base_independent"]:
        print("  !! REFUSED: no self-reference at any candidate base — the bytes are base-independent; the gate cannot discriminate (R43)")
        return
    top_v = r["candidates"][0]["verdict"] if r["candidates"] else None
    ties = [c for c in r["candidates"] if c["verdict"] == top_v]
    if top_v != "STRONG" and len(ties) > 1:
        print(f"  ~~ AMBIGUOUS: {len(ties)} candidates share the top verdict {top_v} — probe each with the byte gate, in this order")
    for c in r["candidates"][:5]:
        print(f"  0x{c['base']:08X} {c['verdict']:<12} ptrs_in={c['internal_ptrs']:<4}(on_pro {c['internal_ptrs_on_prologue']:<3}) "
              f"jals_in={c['internal_jals']:<3}(on_pro {c['internal_jals_on_prologue']:<3}) lui_reach={c['lui_reach']:<4} score={c['score']:<6} {c['label']}")


def run_controls():
    bad = 0
    for alias, path, true_base, tlo in CONTROLS:
        p = os.path.join(REPO, path)
        if not os.path.exists(p):
            print(f"[controls] {alias}: payload missing — {path}"); bad += 1; continue
        r = analyse(p, text_lo=None, extra_bases=(true_base,))
        rank = {"STRONG": 3, "CONSISTENT": 2, "NO-EVIDENCE": 1, "INCONSISTENT": 0}
        me = next((c for c in r["candidates"] if c["base"] == true_base), None)
        tl_ok = (r["text_lo"] == tlo)
        if me is None or r["base_independent"]:
            ok, why = False, "true base absent from the candidate rows / payload read as base-independent"
        else:
            rivals = [c for c in r["candidates"] if c["base"] != true_base and rank[c["verdict"]] > rank[me["verdict"]]]
            ok = (me["verdict"] in ("STRONG", "CONSISTENT")) and not rivals
            why = f"true={me['verdict']} score {me['score']}" + (f"; STRONGER rivals: {[(hex(c['base']), c['verdict']) for c in rivals[:3]]}" if rivals else "")
        top = r["candidates"][0]
        print(f"[controls] {alias}: true 0x{true_base:08X} {'OK  ' if ok else 'FAIL'} | top 0x{top['base']:08X} {top['verdict']} | {why} | TEXT_LO est 0x{r['text_lo']:X} vs yaml 0x{tlo:X} {'ok' if tl_ok else 'DIFFERS (header table; pass --text-lo)'}")
        if not ok:
            for c in r["candidates"][:4]:
                print(f"      0x{c['base']:08X} {c['verdict']:<12} ptrs_in={c['internal_ptrs']} jals_in={c['internal_jals']} on_start={c['internal_jals_on_prologue']} lui={c['lui_reach']} score={c['score']} {c['label']}")
        bad += 0 if ok else 1
    print(f"[controls] {len(CONTROLS) - bad}/{len(CONTROLS)} true bases top-ranked")
    return bad == 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("payloads", nargs="*")
    ap.add_argument("--text-lo", type=lambda s: int(s, 0), default=None)
    ap.add_argument("--base", action="append", type=lambda s: int(s, 0), default=[], help="extra candidate base(s)")
    ap.add_argument("--controls", action="store_true", help="run the R39 controls (also run before any emission)")
    ap.add_argument("--json", default=None)
    a = ap.parse_args()
    if not run_controls():
        sys.exit("payload_base_evidence: CONTROLS FAILED — refusing to emit (R39/R35)")
    if a.controls and not a.payloads:
        return
    out = []
    for p in a.payloads:
        r = analyse(os.path.join(REPO, p) if not os.path.isabs(p) else p, a.text_lo, a.base)
        render(r); out.append(r)
    if a.json:
        json.dump(out, open(a.json, "w"), indent=1); print("->", a.json)


if __name__ == "__main__":
    main()
