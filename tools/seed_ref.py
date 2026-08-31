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
"""
import argparse
import functools
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import corpus     # noqa: E402
import progress   # noqa: E402

REFUSED_LEDGER = os.path.join(REPO, ".run/twin_refused.json")


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


def for_stub(binary, fn):
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


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary")
    ap.add_argument("--fn")
    ap.add_argument("--all", action="store_true", help="every open stub fleet-wide")
    ap.add_argument("--json")
    a = ap.parse_args()

    if a.all:
        out, scanned = [], 0
        for b in progress.BINARIES:
            try:
                stubs = corpus.stubs(b)
            except Exception as e:
                print("  oracle refused %s: %r" % (b, e), file=sys.stderr)
                continue
            for s in stubs.values():
                scanned += 1
                sr = for_stub(b, s.symbol)
                if sr:
                    out.append(sr)
        ref = sum(1 for x in out if x["mechanical_remap_refused"])
        print("open stubs scanned: %d · WITH a banked twin: %d (h_exact %d / h_norm %d) · "
              "of those, %d were already mechanically refused"
              % (scanned, len(out),
                 sum(1 for x in out if x["tier"] == "exact"),
                 sum(1 for x in out if x["tier"] == "norm"), ref))
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
