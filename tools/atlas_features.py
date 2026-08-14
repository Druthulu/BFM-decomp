#!/usr/bin/env python3
"""P31 T4 — per-function feature extractor for the Frontier Atlas (cookbook §168+, plan T4).

WHAT: one deterministic feature record per function across ALL 213 registry binaries, written to
`.run/feat.<bin>.jsonl` (one row per sig row, keyed (addr, h_exact)) with the body-level features
memoized per distinct `h_exact` in `.run/feat_memo.json` — a feature is a PURE FUNCTION of the
instruction bytes (position-independence argued below), so ~91k distinct bodies cover ~363k rows.

WHY: the atlas (T5) groups the remaining stubs into crack groups by tiers looser than h_seq; these
features are the bucketing keys, the §172b static tells, and the li-normalized skeleton that kills
the measured dominant drift class (li 16-bit-boundary expansion — cookbook §168: 25/86 near-pairs).

POSITION-INDEPENDENCE (why the h_exact memo is valid): branches are pc-relative (in-fn-ness shifts
with pc, identical for identical bytes); `jal`/`j` targets are absolute AND byte-identical for
identical bytes, and are treated as CALLS, never CFG edges; the call-stability test uses FIXED
ranges (main + resident vram), never the instance's own window. No feature reads the placement.

SCOPE: binaries from `dup_report.BINARIES` (the registry — raw sig globs pick up proto/demo strays,
agent-verified). MAIN override: the registry's main sig stays the Ghidra one (it feeds the
provisional MAIN weighted metric); the atlas layer reads the splat-true `.run/sig.main.jsonl`
(made by `make sig-main`, word-cross-checked 2,002/2,002) — this extractor does the same.

R32: per binary, rows must be 1:1 with sig rows on (addr, h_exact) — asserted at write time.
`--verify` re-derives a random sample of memoized bodies and compares (determinism proof) and
cross-checks `mid_jr` against `family_hseq`'s independent implementation on family exemplars.

The §172b tell detectors (extpair / dupselect / sign_mix / magic_div) live HERE as importable
functions — `len_tells.py` (T8) imports them; one implementation (R33).
"""
import argparse, collections, hashlib, json, os, sys, random

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import family_remap as FR
import family_cousins as FC
import sig_image

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MEMO_PATH = ".run/feat_memo.json"

# Fixed location-stable call ranges (the two universally-resident code regions; derived once from
# the same sources the build reads — main: splat.us.exe.yaml via FR.vram_of + t_size 0x64800;
# resident: its splat vram + the ELF-verified text end 0x800D3408).
MAIN_LO, MAIN_HI = 0x80010000, 0x80074800
RES_LO, RES_HI = 0x800CEDFC, 0x800D3408

TINY, SUBSTANTIAL = 16, 80          # family_hseq band constants (kept in lockstep)
O0_PROLOGUE = 0x03A0F021            # addu $fp,$sp,$zero — the -O0 prologue tell (cookbook §116)

_SAVE_REGS = {16, 17, 18, 19, 20, 21, 22, 23, 30, 31}   # $s0..$s7, $fp, $ra

# 16-bucket opcode-class histogram (fixed order; index = bucket)
_BUCKETS = ["load", "store", "strength", "addr", "branch", "jal", "jr", "lui",
            "nop", "gte", "slt", "logic", "shift", "hilo", "regimm", "other"]
_LOADS = {"lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr"}
_STORES = {"sb", "sh", "sw", "swl", "swr"}
_STRENGTH = {"mult", "multu", "div", "divu"}
_ADDR = {"addu", "addiu", "add", "addi", "subu", "sub", "ori"}
_BR = {"beq", "bne", "blez", "bgtz", "bltz", "bgez", "bltzal", "bgezal", "b", "beqz", "bnez",
       "beql", "bnel", "j"}
_SLT = {"slt", "sltu", "slti", "sltiu"}
_LOGIC = {"and", "or", "xor", "nor", "andi", "xori"}
_SHIFT = {"sll", "srl", "sra", "sllv", "srlv", "srav"}
_HILO = {"mfhi", "mflo", "mthi", "mtlo"}


def _op_bucket(mnem, word):
    if word == 0:
        return "nop"
    if (word >> 26) in (0x12,):          # COP2 / GTE
        return "gte"
    m = mnem.lower()
    if m in _LOADS: return "load"
    if m in _STORES: return "store"
    if m in _STRENGTH: return "strength"
    if m in _HILO: return "hilo"
    if m == "lui": return "lui"
    if m in _ADDR: return "addr"
    if m in _BR: return "branch"
    if m in ("jal", "jalr"): return "jal"
    if m == "jr": return "jr"
    if m in _SLT: return "slt"
    if m in _LOGIC: return "logic"
    if m in _SHIFT: return "shift"
    if (word >> 26) == 1: return "regimm"
    return "other"


# ---------------------------------------------------------------- §172b tell detectors (shared)

def extpair_count(words):
    """`sll r,x,16 … sra r,r,16` (or 24/24) same-dest pairs ≤2 apart — the §172b-1 'extend' tell
    (register-held short promotion). Byte-level: R-type funct 0x00 (sll) / 0x03 (sra)."""
    n = 0
    for i, w in enumerate(words):
        if (w >> 26) == 0 and (w & 0x3F) == 0x00 and w != 0:          # sll (nop excluded)
            sa = (w >> 6) & 0x1F
            rd = (w >> 11) & 0x1F
            if sa in (16, 24):
                for j in range(i + 1, min(i + 4, len(words))):
                    w2 = words[j]
                    if (w2 >> 26) == 0 and (w2 & 0x3F) == 0x03:       # sra
                        if ((w2 >> 6) & 0x1F) == sa and ((w2 >> 16) & 0x1F) == rd:
                            n += 1
                            break
    return n


def dupselect_count(words):
    """Repeated register-identical (slt*, branch) bigram within a 16-ins window — the §172b-2
    'swaprepeat' tell (a textually repeated compare with swapped select arms re-emits its own
    slt+branch structure). Bigram key = (slt word, branch word masked of its displacement)."""
    seen = {}
    n = 0
    for i, w in enumerate(words):
        op = w >> 26
        is_slt = (op == 0 and (w & 0x3F) in (0x2A, 0x2B)) or op in (0x0A, 0x0B)
        if not is_slt:
            continue
        for j in range(i + 1, min(i + 3, len(words))):
            b = words[j]
            if (b >> 26) in (0x04, 0x05):                              # beq/bne
                key = (w, b & 0xFFFF0000)
                if key in seen and i - seen[key] <= 16:
                    n += 1
                seen[key] = i
                break
    return n


def sign_mix(words, mnems):
    """(lh AND lhu present, lb AND lbu present) — the §172a sign-load tell."""
    s = set(mnems)
    return int("lh" in s and "lhu" in s), int("lb" in s and "lbu" in s)


def magic_div_count(words, mnems, reloc_idx):
    """lui(non-anchor const) + mult/multu + mfhi + sra within a 10-ins window — the s16/K
    magic-multiply division tell (§172b-4)."""
    n = 0
    for i, m in enumerate(mnems):
        if m == "lui" and i not in reloc_idx:
            window = mnems[i + 1:i + 10]
            if any(x in ("mult", "multu") for x in window) and "mfhi" in window \
               and any(x == "sra" for x in window):
                n += 1
    return n


# ---------------------------------------------------------------- body features (memo per h_exact)

def body_features(words, vram):
    """The pure-function-of-bytes feature dict for one body (vram = any instance's placement;
    used only for pc-relative branch decode, which is placement-invariant — see module docstring)."""
    nins = len(words)
    insns = [sig_image.make_insn(w, vram + 4 * i) for i, w in enumerate(words)]
    mnems = [i.getOpcodeName().lower() if i.isValid() else "?" for i in insns]
    reloc_idx = FR.reloc_indices(words)

    lo, hi = vram, vram + 4 * nins
    leaders = {vram}
    ncond = nback = ret_n = jalr_n = 0
    mid_jr = False
    calls = []
    for i, (w, ins, m) in enumerate(zip(words, insns, mnems)):
        pc = vram + 4 * i
        if not ins.isValid():
            continue
        if m == "jr":
            if ((w >> 21) & 0x1F) == 31:
                ret_n += 1
            else:
                mid_jr = True
        elif m == "jalr":
            jalr_n += 1
        elif m == "jal":
            calls.append(ins.getInstrIndexAsVram())
        elif ins.isBranch():
            t = ins.getBranchVramGeneric()
            ncond += 1 if m not in ("b", "j") else 0
            if lo <= t < hi:
                leaders.add(t)
                if t <= pc:
                    nback += 1
            if pc + 8 < hi:
                leaders.add(pc + 8)
        elif m == "j":
            t = ins.getInstrIndexAsVram()
            if lo <= t < hi:
                leaders.add(t)
                if t <= pc:
                    nback += 1

    stable = [t for t in calls if MAIN_LO <= t < MAIN_HI or RES_LO <= t < RES_HI]
    rk_seq = []
    for i in sorted(reloc_idx):
        if mnems[i] == "jal":
            rk_seq.append("C")
        elif mnems[i] == "lui":
            rk_seq.append("D")
    hist = collections.Counter(_op_bucket(m, w) for m, w in zip(mnems, words))

    # prologue: frame + ordered callee-saved stores in the pre-branch window
    frame = 0
    saves = []
    for i, (w, m) in enumerate(zip(words, mnems)):
        if i >= 12 or m in _BR or m in ("jal", "jr", "jalr"):
            break
        if m == "addiu" and ((w >> 21) & 0x1F) == 29 and ((w >> 16) & 0x1F) == 29 and frame == 0:
            imm = w & 0xFFFF
            if imm >= 0x8000:
                frame = 0x10000 - imm
        if m == "sw" and ((w >> 21) & 0x1F) == 29:
            rt = (w >> 16) & 0x1F
            if rt in _SAVE_REGS:
                saves.append(rt)

    # li-normalized skeleton: tok stream with non-anchor lui dropped and ori→addiu class (§168)
    toks = []
    for i, w in enumerate(words):
        t = FC.tok(w)
        if mnems[i] == "lui" and i not in reloc_idx:
            continue
        if (w >> 26) == 0x0D:                                          # ori → addiu class
            t = (0x09,)
        toks.append(t)
    h_seqn = hashlib.sha1(repr(toks).encode()).hexdigest()

    sm_h, sm_b = sign_mix(words, mnems)
    return {
        "nins": nins,
        "band": "tiny" if nins < TINY else ("substantial" if nins >= SUBSTANTIAL else "mid"),
        "o0": int(any(w == O0_PROLOGUE for w in words[:4])),
        "frame": frame,
        "saves": "".join(f"{r:02d}" for r in saves),
        "fp": int(any(m in ("sw", "lw") and ((w >> 21) & 0x1F) == 30
                      for m, w in zip(mnems, words))),
        "nblk": len(leaders),
        "ncond": ncond,
        "nback": nback,
        "ret_n": ret_n,
        "mid_jr": int(mid_jr),
        "jalr_n": jalr_n,
        "res_calls_h": hashlib.sha1(" ".join(f"{t:08x}" for t in stable).encode()).hexdigest()[:16],
        "res_n": len(stable),
        "loc_n": len(calls) - len(stable),
        "rk_seq_h": hashlib.sha1("".join(rk_seq).encode()).hexdigest()[:16],
        "nrel_call": rk_seq.count("C"),
        "nrel_data": rk_seq.count("D"),
        "ophist": [hist.get(b, 0) for b in _BUCKETS],
        "extpair": extpair_count(words),
        "dupselect": dupselect_count(words),
        "sign_lh": sm_h, "sign_lb": sm_b,
        "magic_div": magic_div_count(words, mnems, reloc_idx),
        "h_seqn": h_seqn,
        "nins_n": len(toks),
    }


# ---------------------------------------------------------------- the fleet run

def registry_binaries():
    import dup_report
    return sorted(dup_report.BINARIES)


def sig_rows(binary):
    """Sig rows for the atlas: the registry sig, EXCEPT main -> the splat-true sig-main output."""
    if binary == "main":
        p = ".run/sig.main.jsonl"
        if not os.path.exists(p):
            raise SystemExit("atlas_features: no .run/sig.main.jsonl — run `make sig-main` (R32)")
        return [json.loads(l) for l in open(p) if l.strip()]
    return list(corpus.sig(binary).values())


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--verify", action="store_true",
                    help="re-derive a random memo sample + cross-check mid_jr vs family_hseq")
    ap.add_argument("--sample", type=int, default=200)
    a = ap.parse_args()

    memo = {}
    if os.path.exists(MEMO_PATH):
        memo = json.load(open(MEMO_PATH))

    bins = registry_binaries()
    n_rows = n_new = 0
    for b in bins:
        rows = sig_rows(b)
        out = []
        for r in rows:
            hx = r["h_exact"]
            if hx not in memo:
                addr = int(r["addr"], 16)
                words = FR.stream_words(b, addr, r["nins"])
                if words is None:
                    raise SystemExit(f"atlas_features: stream_words({b},{r['addr']}) None (R32)")
                memo[hx] = body_features(words, addr)
                n_new += 1
            out.append({"addr": r["addr"], "name": r.get("name", ""), "h_exact": hx, **memo[hx]})
        # R32: 1:1 with the sig on (addr, h_exact)
        assert len(out) == len(rows), f"{b}: feat {len(out)} != sig {len(rows)}"
        assert all(o["addr"] == r["addr"] and o["h_exact"] == r["h_exact"]
                   for o, r in zip(out, rows)), f"{b}: (addr,h_exact) join mismatch"
        with open(f".run/feat.{b}.jsonl", "w") as f:
            for o in out:
                f.write(json.dumps(o, separators=(",", ":")) + "\n")
        n_rows += len(out)
    json.dump(memo, open(MEMO_PATH, "w"))
    print(f"atlas_features: {n_rows} rows across {len(bins)} binaries; "
          f"{len(memo)} distinct bodies ({n_new} newly computed)")

    if a.verify:
        # determinism: re-derive a random sample from a fresh pass and compare to the memo
        rng = random.Random(31)
        pairs = []
        for b in rng.sample(bins, min(24, len(bins))):
            rows = sig_rows(b)
            for r in rng.sample(rows, min(10, len(rows))):
                pairs.append((b, r))
        bad = 0
        for b, r in rng.sample(pairs, min(a.sample, len(pairs))):
            words = FR.stream_words(b, int(r["addr"], 16), r["nins"])
            if body_features(words, int(r["addr"], 16)) != memo[r["h_exact"]]:
                bad += 1
                print(f"  DETERMINISM FAIL {b} {r['addr']}")
        print(f"verify determinism: {bad} mismatches")
        # mid_jr cross-check vs family_hseq's independent implementation (exemplar level)
        fh = ".run/family_hseq.json"
        agree = disagree = skipped = 0
        if os.path.exists(fh):
            fam = json.load(open(fh))["families"]
            idx = {}                                   # binary -> {addr:int -> h_exact}
            for f in fam:
                ex = f["exemplar"]
                b2 = ex["ov"]
                ea = ex["addr"] if isinstance(ex["addr"], int) else int(str(ex["addr"]), 16)
                if b2 not in idx:
                    try:
                        idx[b2] = {int(r["addr"], 16): r["h_exact"] for r in sig_rows(b2)}
                    except (SystemExit, corpus.CorpusError):
                        idx[b2] = {}
                hx = idx[b2].get(ea)
                if hx is None or hx not in memo:
                    skipped += 1
                    continue
                got = memo[hx]["mid_jr"]
                if got == int(f["has_mid_jr"]):
                    agree += 1
                else:
                    disagree += 1
                    if disagree <= 5:
                        print(f"  mid_jr DISAGREE {b2} {ea:#x} feat={got} hseq={f['has_mid_jr']}")
            print(f"verify mid_jr vs family_hseq exemplars: {agree} agree / {disagree} disagree / {skipped} skipped")
            if agree == 0:
                sys.exit("R32: the mid_jr cross-check compared ZERO exemplars — the verifier is broken, not the data")
        if bad or disagree:
            sys.exit(1)
        print("atlas_features --verify: PASS")


if __name__ == "__main__":
    main()
