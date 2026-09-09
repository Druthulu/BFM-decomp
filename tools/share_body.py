#!/usr/bin/env python3
"""share_body.py — give a byte-identical function class ONE source (Phase 35 T5): the permanent successor of dedup_propagate +
dedup_extend for the include-at-site form.

    tools/share_body.py --plan                             # the buckets: extend (registered-incomplete) / new (unregistered same-vram)
    tools/share_body.py --apply --bucket extend            # bucket 0: the registered classes whose members are not all sharing
    tools/share_body.py --apply --bucket new --batch 120 --limit N   # the unregistered same-vram classes, largest reach first
    tools/share_body.py --apply ... --only <h_exact>       # one class (the R37 probe)

WHAT ONE SHARE IS. A class = one h_exact (the raw instruction bytes) at one vram, with >=2 instances across the fleet, some of which
are still PRIVATE COPIES (a definition in that binary's own TU). Sharing it: the class's ONE body goes to (or already is) a plain-C
header under src/shared/<space>/ (macro_to_header's naming: func_<VRAM>[__h8].h, keyed by the class — R48), every private copy becomes
`#include "../shared/<space>/<header>"` at the SAME position (the copy's definition lines, nothing else — the TU keeps its own
declarations), and the registry gains the group (shorthand form, appended by text) or the members (dedup_extend.add_members_surgical).

THE EXEMPLAR (for an unregistered class) — printed with every share: the copy whose normalized text the MOST copies share; a tie goes
to a pin-free copy; a further tie to the shortest. A body defined under an asm-label alias (aF<ADDR>) gets its own binding
(macro_to_header.bind_alias_header). 91% of the backlog's classes have identical text in every copy (the census), so the exemplar is
usually every copy; the 9% with differing texts are where the gate earns its keep.

THE GATE, per batch: every private copy's edits applied bottom-up per TU (line numbers stay valid), then for every touched binary
(a twin's primary counts for the twin too): the objects snapshotted before, `make check BINARY=<b> -j16` (exit code), every object
compared. A red binary is BISECTED: its TUs restored, the batch's classes re-applied one at a time, the culprit's members in that
binary stay private and the class is LEDGERED in config/dedup_exceptions.tsv with the compiler's line (TU-CONFLICT / GATE-REJECT);
the class is registered with the members that passed. "shared" is printed only from the gate's success (R66). The clean fleet run
after the batch is the caller's (R22). Never `yaml.safe_dump` the registry (H5).
"""
import argparse
import collections
import json
import os
import pathlib
import re
import subprocess
import sys
import time

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import share_census as sc            # noqa: E402
import macro_to_header as m2h        # noqa: E402 — Oracles (naming, spaces, sigs), bind_alias_header, include_line, banner
import dedup_extend as de            # noqa: E402 — add_members_surgical (the registry's surgical text edit)

LEDGER = REPO / "config/dedup_exceptions.tsv"
RUN = REPO / ".run/P35/share"


def log(msg):
    print(msg, flush=True)


# ----------------------------------------------------------------------------------------------------------------------------
def census(jobs):
    aliases, dirs = sc.fleet_and_dirs()
    spaces = sc.vram_bases()
    twins = sc.twin_sets(aliases)
    twin_of = sc.twin_of_map()
    sigs = {a: sc.sig_rows(a) for a in aliases}
    forms, notes = sc.build_forms(aliases, dirs, jobs, use_cache=True)
    groups = sc.load_groups()
    exceptions = sc.load_exceptions("config/dedup_exceptions.tsv")
    verb = sc.verbatim_instances()
    classes, cov = sc.classify(sigs, forms, groups, spaces, dirs, twins, twin_of, verb, exceptions, keep_instances=True)
    if cov["unaccounted"] or notes["multi_form"]:
        sys.exit(f"share_body: the census has {len(cov['unaccounted'])} unaccounted / {len(notes['multi_form'])} multi-form instances — fix "
                 f"the census first (R32)")
    return dict(aliases=aliases, dirs=dirs, spaces=spaces, twins=twins, twin_of=twin_of, forms=forms, groups=groups,
                exceptions=exceptions, classes=classes)


def candidates(cen):
    """(extend, new): the classes this tool shares. Same-vram only; twin-covered and excepted classes are satisfied already."""
    extend, new = [], []
    for c in cen["classes"]:
        if c["verdict"] == "A" or "E" in c["flags"] or "F" in c["flags"] or "TWIN-COVERED" in c["flags"] or c["excepted"]:
            continue
        priv = [i for i in c["insts"] if i["form"] == "def"]
        if c["verdict"] == "B":
            extend.append(c)
        elif priv:
            new.append(c)
    new.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    extend.sort(key=lambda c: (-c["instances"], -c["nins"], c["h"]))
    return extend, new


def choose_exemplar(priv):
    by_text = collections.Counter(i["text_hash"] for i in priv)
    best = max(by_text.values())
    pool = [i for i in priv if by_text[i["text_hash"]] == best]
    pool.sort(key=lambda i: (i.get("pins", False), i.get("nlines", 0), i["alias"], i["tu"]))
    reason = "majority text" if best > 1 or len(priv) == 1 else "tie → pin-free, shortest"
    return pool[0], reason, dict(by_text)


def def_text(inst):
    """The definition's lines [line..end] of a private copy, from its TU."""
    tu = REPO / inst["tu"]
    lines = tu.read_text(errors="surrogateescape").split("\n")
    a, b = inst["line"] - 1, inst["end"]
    return "\n".join(lines[a:b]).rstrip("\n") + "\n"


# ----------------------------------------------------------------------------------------------------------------------------
class Batch:
    """Edits for a batch of classes: per TU a list of (start_line, end_line, replacement) applied bottom-up."""

    def __init__(self, orc, cen):
        self.orc, self.cen = orc, cen
        self.edits = collections.defaultdict(list)      # tu_rel -> [(line, end, new_text, h)]
        self.headers = {}                                # header rel -> text
        self.register = []                               # (id, hash, source, func, vram, [binaries])
        self.extend = collections.defaultdict(list)      # group id -> [binaries]
        self.touched = set()                             # binaries
        self.members = collections.defaultdict(list)     # h -> [(alias, tu)]
        self.exemplar_note = {}

    def add_class(self, c):
        h = c["h"]
        vram = int(c["addrs"][0], 16)
        priv = [i for i in c["insts"] if i["form"] == "def"]
        base = self.orc.bases[priv[0]["alias"]] if priv else self.orc.bases[c["insts"][0]["alias"]]
        fn = f"func_{vram:08X}"
        if c["verdict"] == "B":
            g = c["groups"][0]
            hdr = g["source"]
            defined = {n for n, _ in sc.header_defs(REPO / hdr)}
            if g.get("func") not in defined:
                return f"refused: {g['id']}'s source {hdr} does not define {g.get('func')}"
            listed = {b for b, _, _ in m2h.sc_group_members(g)}
            for i in c["insts"]:
                if i["alias"] not in listed:
                    self.extend[g["id"]].append(i["alias"])
            self.exemplar_note[h] = f"extend {g['id']} (+{len(self.extend.get(g['id'], []))} members, {len(priv)} private sites → include)"
        else:
            ex, reason, texts = choose_exemplar(priv)
            hdr = self.orc.header_rel(base, vram, h)
            if (REPO / hdr).exists():
                defined = {n for n, _ in sc.header_defs(REPO / hdr)}
                if fn not in defined:
                    return f"refused: {hdr} exists and does not define {fn} (defines {sorted(defined)[:3]})"
            else:
                body = def_text(ex)
                space_name = "overlay slot" if base == m2h.OV_BASE else self.orc.space_dir(base)
                text = m2h.banner(fn, base, h, space_name) + body
                text, _ = m2h.bind_alias_header(text, fn)
                self.headers[hdr] = text
            self.register.append((f"S_{fn}", h, hdr, fn, vram, sorted({i["alias"] for i in c["insts"]})))
            self.exemplar_note[h] = f"exemplar {ex['tu']}:{ex['line']} ({reason}; texts {len(texts)}), {len(priv)} private sites → include"
        for i in priv:
            inc = m2h.include_line(i["tu"], hdr)
            self.edits[i["tu"]].append((i["line"], i["end"], inc, h))
            self.touched.add(i["alias"])
            self.members[h].append((i["alias"], i["tu"]))
        for i in c["insts"]:
            self.touched.add(i["alias"])                 # twins of a touched primary are gated too (their objects change)
        return None

    def apply_edits(self, only_tus=None):
        n = 0
        for tu, eds in self.edits.items():
            if only_tus is not None and tu not in only_tus:
                continue
            p = REPO / tu
            lines = p.read_text(errors="surrogateescape").split("\n")
            for line, end, new, _ in sorted(eds, key=lambda e: -e[0]):
                lines[line - 1:end] = [new]
                n += 1
            p.write_text("\n".join(lines))
        return n

    def write_headers(self):
        for hdr, text in self.headers.items():
            p = REPO / hdr
            if p.exists():
                if p.read_text(errors="surrogateescape") != text:
                    sys.exit(f"share_body: {hdr} exists with different text — the naming rule missed a collision (R43)")
                continue
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(text)


# ----------------------------------------------------------------------------------------------------------------------------
def objdir(alias):
    return REPO / ("build/src" if alias == "main" else f"build/src/{alias}")


def snapshot(aliases):
    snap = {}
    for a in aliases:
        d = objdir(a)
        snap[a] = {p.name: p.read_bytes() for p in d.glob("*.o")} if d.exists() else {}
    return snap


def gate(alias, snap):
    """(ok, detail): make check by exit code, then every object compared with the snapshot."""
    log_p = RUN / f"check_{alias}.log"
    with open(log_p, "w") as f:
        r = subprocess.run(["make", "check", f"BINARY={alias}", "-j16"], cwd=REPO, stdout=f, stderr=subprocess.STDOUT)
    if r.returncode != 0:
        txt = log_p.read_text(errors="replace")
        err = [ln for ln in txt.splitlines() if "error" in ln.lower() or "conflicting" in ln.lower()]
        return False, (err[0] if err else txt.splitlines()[-1] if txt.strip() else "make check failed")[:200]
    d = objdir(alias)
    same = diff = 0
    for name, data in snap.get(alias, {}).items():
        q = d / name
        if q.exists() and q.read_bytes() == data:
            same += 1
        else:
            diff += 1
    if diff:
        return False, f"object A/B: {same}/{same + diff} — {diff} object(s) differ"
    return True, f"BYTE-IDENTICAL, obj A/B {same}/{same + diff}"


def restore(tus):
    if tus:
        subprocess.run(["git", "checkout", "--"] + sorted(tus), cwd=REPO, check=True)


def ledger_row(h, reason, nins, instances, note):
    with open(LEDGER, "a") as f:
        f.write(f"{h}\t{reason}\t{nins}\t{instances}\t{note}\n")


def registry_append(entries):
    """Append shorthand groups by text at the end of config/dedup.us.yaml (never a yaml dump — H5)."""
    p = REPO / "config/dedup.us.yaml"
    t = p.read_text()
    if not t.endswith("\n"):
        t += "\n"
    out = []
    for gid, h, src, fn, vram, bins in entries:
        out.append(f"  - id: {gid}\n    tier: h_exact\n    hash: {h}\n    source: {src}\n    func: {fn}\n    vram: 0x{vram:08X}\n"
                   f"    binaries: [{', '.join(bins)}]\n")
    p.write_text(t + "".join(out))


def run_batch(orc, cen, classes, label):
    b = Batch(orc, cen)
    refused = []
    for c in classes:
        why = b.add_class(c)
        if why:
            refused.append((c["h"], why))
    for h, why in refused:
        log(f"  refuse {h[:10]}: {why}")
    twins_of = collections.defaultdict(list)
    for t, prim in cen["twin_of"].items():
        twins_of[prim].append(t)
    gated = sorted(b.touched | {t for a in b.touched for t in twins_of.get(a, [])})
    snap = snapshot(gated)
    b.write_headers()
    b.apply_edits()
    log(f"  [{label}] {len(classes) - len(refused)} classes · {sum(len(v) for v in b.edits.values())} sites in {len(b.edits)} TUs · "
        f"{len(b.headers)} new headers · gating {len(gated)} binaries")
    failed_classes = set()
    results = {}
    for a in gated:
        ok, detail = gate(a, snap)
        results[a] = (ok, detail)
        if ok:
            continue
        # BISECT this binary: restore its TUs, re-apply the batch's classes one at a time
        my_tus = {tu for tu in b.edits if tu.startswith(cen["dirs"][a] + "/") or (a == "main" and tu.count("/") == 1)}
        prim = cen["twin_of"].get(a)
        if prim:
            my_tus = {tu for tu in b.edits if tu.startswith(cen["dirs"][prim] + "/")}
        restore(my_tus)
        by_class = collections.defaultdict(lambda: collections.defaultdict(list))
        for tu in my_tus:
            for e in b.edits[tu]:
                by_class[e[3]][tu].append(e)
        good = []
        for h, tus in sorted(by_class.items(), key=lambda kv: kv[0]):
            restore(my_tus)
            for hh in good + [h]:
                for tu, eds in by_class[hh].items():
                    p = REPO / tu
                    lines = p.read_text(errors="surrogateescape").split("\n")
                    for line, end, new, _ in sorted(eds, key=lambda e: -e[0]):
                        lines[line - 1:end] = [new]
                    p.write_text("\n".join(lines))
            ok2, det2 = gate(a, snap)
            if ok2:
                good.append(h)
            else:
                failed_classes.add(h)
                log(f"  [{label}] {a}: class {h[:10]} REJECTED — {det2}")
                # leave the good ones applied
                restore(my_tus)
                for hh in good:
                    for tu, eds in by_class[hh].items():
                        p = REPO / tu
                        lines = p.read_text(errors="surrogateescape").split("\n")
                        for line, end, new, _ in sorted(eds, key=lambda e: -e[0]):
                            lines[line - 1:end] = [new]
                        p.write_text("\n".join(lines))
        ok3, det3 = gate(a, snap)
        results[a] = (ok3, det3 + f" (after bisect: {len(good)} classes kept, {len(by_class) - len(good)} rejected)")
        if not ok3:
            sys.exit(f"share_body: {a} still red after the bisect ({det3}) — stopping (R43)")
    # register: new groups with the members that passed; extensions likewise; ledger the rejected
    reg_entries = []
    for gid, h, src, fn, vram, bins in b.register:
        if h in failed_classes:
            # members that passed = private sites whose binary gated green with this class kept... a class rejected in ANY
            # binary is registered with the others only when its header exists and at least 2 members share it
            kept = [a for a in bins if a not in {al for al, tu in b.members[h] if not results.get(al, (True,))[0]}]
            # conservative: a rejected class is ledgered whole; its passing members keep the include, the group lists them
            passing = [a for a in bins if results.get(a, (True,))[0] and a not in rejected_in(b, h, cen)]
            if len(passing) >= 2:
                reg_entries.append((gid, h, src, fn, vram, passing))
            c = next(x for x in classes if x["h"] == h)
            ledger_row(h, "TU-CONFLICT", c["nins"], c["instances"],
                       f"share_body {label}: rejected in {sorted(rejected_in(b, h, cen))}; registered for {len(passing)}")
        else:
            reg_entries.append((gid, h, src, fn, vram, bins))
    if reg_entries:
        registry_append(reg_entries)
    ext = {gid: bins for gid, bins in b.extend.items()}
    n_ext = de.add_members_surgical(ext) if ext else 0
    ok_n = sum(1 for a in gated if results[a][0])
    log(f"  [{label}] gated {ok_n}/{len(gated)} binaries green · registered {len(reg_entries)} groups · extended {n_ext} members · "
        f"rejected classes {len(failed_classes)}")
    (RUN / f"batch_{label}.json").write_text(json.dumps(dict(classes=[c["h"] for c in classes], refused=refused,
                                                                results=results, registered=[e[0] for e in reg_entries],
                                                                extended=ext, rejected=sorted(failed_classes),
                                                                exemplars=b.exemplar_note), indent=1) + "\n")
    return len(failed_classes) == 0 and all(results[a][0] for a in gated)


def rejected_in(b, h, cen):
    """The binaries in which class h was rejected (their private sites restored by the bisect)."""
    out = set()
    for alias, tu in b.members[h]:
        p = REPO / tu
        text = p.read_text(errors="surrogateescape")
        hdr_inc = [e[2] for e in b.edits[tu] if e[3] == h]
        if hdr_inc and hdr_inc[0] not in text:
            out.add(alias)
    return out


# ----------------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--plan", action="store_true")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--bucket", choices=["extend", "new"], default="new")
    ap.add_argument("--batch", type=int, default=120)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--only", default="")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    RUN.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    cen = census(a.jobs)
    orc = m2h.Oracles()
    extend, new = candidates(cen)
    log(f"share_body: census {time.time() - t0:.0f} s · extend (registered-incomplete) {len(extend)} classes · new (unregistered same-vram) "
        f"{len(new)} classes / {sum(len([i for i in c['insts'] if i['form'] == 'def']) for c in new):,} private sites")
    if a.plan:
        bands = collections.Counter(c["band"] for c in new)
        log(f"  new by band: {dict(bands)}; differing-text classes {sum(1 for c in new if c['verdict'] == 'D')}; "
            f"with pins {sum(1 for c in new if 'PINS' in c['flags'])}; alias-form {sum(1 for c in new if 'ALIAS' in c['flags'])}")
        for c in new[:8]:
            log(f"    {c['verdict']} {','.join(c['flags']) or '-':14s} {c['instances']:4d} inst x {c['nins']:5d} ins {c['addrs'][0]} private {c['copies']}")
        return
    if not a.apply:
        return
    pool = extend if a.bucket == "extend" else new
    if a.only:
        pool = [c for c in pool if c["h"].startswith(a.only)]
    if a.limit:
        pool = pool[:a.limit]
    all_ok = True
    for k in range(0, len(pool), a.batch):
        chunk = pool[k:k + a.batch]
        ok = run_batch(orc, cen, chunk, f"{a.bucket}{k // a.batch + 1}")
        all_ok = all_ok and ok
    log(f"share_body: done — {len(pool)} classes in {(len(pool) + a.batch - 1) // a.batch} batch(es); {'all green' if all_ok else 'see the ledger'}; "
        f"{time.time() - t0:.0f} s")


if __name__ == "__main__":
    main()
