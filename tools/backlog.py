#!/usr/bin/env python3
"""backlog.py — Phase 21 near-miss ledger for the automation manager.

The automation's headline DELIVERABLE: every function the worker/grinder got *close* on but
did NOT byte-match is logged here, ranked for Drew's hand-sessions. The byte-gate
(harvest_verify) is the sole arbiter (G3/P9): a byte-MATCH banks and does NOT appear here;
only genuine near-misses/blockers do. Honest by construction.

Two faces:
  .run/backlog.jsonl   append-only machine log (one record per logged attempt; history kept)
  docs/backlog.md      ranked human table (best record per addr; rows that are now matched are dropped)

Record: {ts, addr, name, reach, klass, nins, status, closeness, where_stuck, best_draft, source}
  status   : near | failed | capped | stub      (near = match_one near-miss; capped = matched-but-
             propagation-blocked; stub = loose-typing/irreducible wall; failed = won't compile/gate)
  closeness: int (match_one mismatch count; lower = closer) or None
  where_stuck: the residual class / blocker (e.g. "regalloc-order", "store-vs-load sched",
               "propagation: undeclared callee func_X", "loose-typing arity")
  best_draft : .run/backlog_drafts/<name>.c (saved best draft, so Drew resumes where it stuck)
  source     : worker | grinder | manual

Ranking (hand-session priority): reach desc (x134 leverage), then closeness asc, then nins asc.

Usage:
  tools/backlog.py log --addr 0x.. --name func_.. --reach 134 --class PINS --nins 80 \
      --status near --closeness 6 --where regalloc-order --source worker [--draft path.c]
  tools/backlog.py render        # regenerate docs/backlog.md from .run/backlog.jsonl
  tools/backlog.py show [-n 40]  # print the top N to stdout
Importable: append_record(dict), render(), save_draft(name, text)->path.
"""
import argparse, glob, json, os, re, shutil, time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
JSONL = os.path.join(REPO, ".run/backlog.jsonl")
MD = os.path.join(REPO, "docs/backlog.md")
DRAFTS = os.path.join(REPO, ".run/backlog_drafts")
SRC_GLOB = os.path.join(REPO, "src/ov_SC01_077/ov_SC01_077*.c")
STUB_RE = re.compile(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)")
FIELDS = ("ts", "addr", "name", "reach", "klass", "nins", "status",
          "closeness", "where_stuck", "best_draft", "binary", "source",
          # Phase-29 Task-12: structured failure telemetry for the permuter-autopsy loop.
          # residual = masked_diff.structured_diff()[:cap] — [(idx, mine, target), ...]; the WHAT/WHERE
          # of the residual (reg-alloc swap / scheduled-order flip / extra-absent insn). passes_tried =
          # the permuter perm_* passes exercised (from permuter_weights) before the plateau — so the
          # autopsy can tell "the right lever was tried and failed" (wall) from "the lever was never
          # tried" (missing-transform → extend the ILS). Both optional; absent on legacy records.
          "residual", "passes_tried")


_NAME_ADDR_RE = re.compile(r"^func_([0-9A-Fa-f]{6,8})$")


def addr_of(rec):
    """The record's address, DERIVED from `name` when the caller omitted `addr` (R33).

    WHY (Phase 29 SESSION-20, the ledger defect): `addr` was null for 1,501 of 1,622 live entries
    (93%) because most callers log only `name`. Every consumer that keys on `addr` therefore
    silently processed 7% of the ledger and reported a confident answer about the other 93% —
    the exact silent-skip shape R32 exists for, and I fell into it twice in one session. The
    address is never actually missing: `func_80174CB0` states it. Derive it, never re-ask.
    Returns None only when neither field carries an address (a genuinely unusable record)."""
    a = rec.get("addr")
    if a:
        try:
            return int(str(a).replace("0x", ""), 16)
        except ValueError:
            pass
    m = _NAME_ADDR_RE.match(str(rec.get("name") or ""))
    return int(m.group(1), 16) if m else None


def assert_addr_coverage(records, what="backlog"):
    """R32: a consumer keying on address must FAIL on the rows it cannot key, not skip them."""
    blind = [r for r in records if addr_of(r) is None]
    if blind:
        raise SystemExit(
            f"{what}: {len(blind)} record(s) carry NO derivable address (neither `addr` nor a "
            f"func_<hex> `name`) — keying on address would silently drop them:\n  "
            + "\n  ".join(json.dumps(r)[:110] for r in blind[:5]))
    return len(records)


def append_record(rec):
    """Normalize + append one record to .run/backlog.jsonl (adds ts if absent).

    Fills BOTH directions of the name<->addr pair so no downstream consumer has to guess: a
    caller that logs only `name` (the common case) still produces a row an addr-keyed reader
    can use. See addr_of() for why this was costing 93% of the ledger."""
    r = {k: rec.get(k) for k in FIELDS}
    if not r.get("ts"):
        r["ts"] = time.strftime("%Y-%m-%d %H:%M:%S")
    if r.get("addr") and not r.get("name"):
        r["name"] = "func_" + r["addr"].lower().replace("0x", "").upper()
    if not r.get("addr"):
        a = addr_of(r)
        if a is not None:
            r["addr"] = "0x%08x" % a
    os.makedirs(os.path.dirname(JSONL), exist_ok=True)
    with open(JSONL, "a") as f:
        f.write(json.dumps(r) + "\n")
    return r


def save_draft(name, text):
    """Persist a best-draft .c so the human picks up where the machine stuck. Returns rel path."""
    os.makedirs(DRAFTS, exist_ok=True)
    p = os.path.join(DRAFTS, f"{name}.c")
    open(p, "w").write(text)
    return os.path.relpath(p, REPO)


_STUB_CACHE = {}


def _open_stubs(binary):
    """INCLUDE_ASM stub names still OPEN in <binary>'s source (main + any _a/_o0 split). Fleet-aware:
    a fn matched in ov_SC01_077 but propagation-stuck stays OPEN in the other overlays (the Phase-19/20
    cap), so the grinder must judge open-ness against the record's OWN binary, not just 077."""
    if binary not in _STUB_CACHE:
        s = set()
        for p in glob.glob(os.path.join(REPO, f"src/{binary}/{binary}*.c")):
            s |= set(STUB_RE.findall(open(p).read()))
        _STUB_CACHE[binary] = s
    return _STUB_CACHE[binary]


def load_best():
    """Best (lowest closeness, latest ts) record per addr, restricted to fns still OPEN in their OWN
    binary (rec['binary']; legacy records default ov_SC01_077). Fleet-aware so a 077-matched-but-
    stuck-local fn surfaces via its overlay record — the grinder must SEE it to grind it (P9 honesty:
    a fn banked in its own binary since logged is dropped)."""
    if not os.path.exists(JSONL):
        return []
    _STUB_CACHE.clear()
    best = {}
    for line in open(JSONL):
        line = line.strip()
        if not line:
            continue
        r = json.loads(line)
        nm = r.get("name")
        binary = r.get("binary") or "ov_SC01_077"
        if nm and nm not in _open_stubs(binary):   # banked in ITS binary since logged -> drop (P9)
            continue
        # Key on the DERIVED address (addr_of), never on `addr or name`: 93% of rows carry only
        # `name`, so the old key split one function into TWO "best" records whenever it had been
        # logged both ways — the same silent-skip class as the null-addr defect itself.
        a = addr_of(r)
        key = a if a is not None else nm
        cur = best.get(key)
        c = r.get("closeness")
        cscore = c if isinstance(c, int) else 10 ** 9
        if cur is None or (cscore, r.get("ts", "")) <= (cur[0], cur[1]):
            best[key] = (cscore, r.get("ts", ""), r)
    return [v[2] for v in best.values()]


def _rank_key(r):
    return (-(r.get("reach") or 1),
            r.get("closeness") if isinstance(r.get("closeness"), int) else 10 ** 9,
            r.get("nins") or 10 ** 9)


def render():
    # Parallel workers set BACKLOG_NO_RENDER=1 so concurrent gate_stage runs don't race on
    # docs/backlog.md (render is a read-whole-file + rewrite; appends are atomic, render is not).
    # The orchestrator renders ONCE after the wave. Backward-compatible: unset -> render as before.
    if os.environ.get("BACKLOG_NO_RENDER"):
        return
    recs = sorted(load_best(), key=_rank_key)
    by_status, by_class = {}, {}
    for r in recs:
        by_status[r.get("status")] = by_status.get(r.get("status"), 0) + 1
        by_class[r.get("klass")] = by_class.get(r.get("klass"), 0) + 1
    lines = []
    lines.append("# Backlog — automation near-misses for hand-finishing\n")
    lines.append("> Generated by `tools/backlog.py render` from `.run/backlog.jsonl`. "
                 "These are functions the Phase-21 automation got **close** on but did NOT "
                 "byte-match. The whole-binary byte-gate is the sole arbiter (G3/P9): **byte-matches "
                 "bank and are NOT listed here** — only genuine near-misses/blockers are. Ranked by "
                 "hand-session priority: **reach** (×N propagation leverage) → **closeness** "
                 "(match_one mismatch count, lower = closer) → **size**. Each row's `best_draft` is "
                 "the closest C the machine reached — resume from there.\n")
    lines.append(f"**Open near-misses:** {len(recs)}  ·  by status {by_status}  ·  by class {by_class}\n")
    lines.append("| # | addr | reach | class | nins | status | closeness | where it stuck | best draft |")
    lines.append("|--:|------|------:|-------|-----:|--------|----------:|----------------|------------|")
    for i, r in enumerate(recs, 1):
        c = r.get("closeness")
        lines.append("| {} | {} | {} | {} | {} | {} | {} | {} | {} |".format(
            i, r.get("name") or r.get("addr"), r.get("reach"), r.get("klass") or "", r.get("nins"),
            r.get("status") or "", c if c is not None else "", (r.get("where_stuck") or "").replace("|", "/"),
            f"`{r.get('best_draft')}`" if r.get("best_draft") else ""))
    os.makedirs(os.path.dirname(MD), exist_ok=True)
    open(MD, "w").write("\n".join(lines) + "\n")
    return len(recs)


def prune():
    """Compact .run/backlog.jsonl to reality: keep ONE record per addr (the best), and DROP every
    entry whose function is no longer an open stub in its binary (banked since it was logged, P9).

    The raw log is append-only, so it grows without bound and fills with already-banked noise
    (measured 2026-07-24: 6,867 rows, ~98% already banked). `render()`/`load_best()` already filter
    on READ, so docs/backlog.md was correct — but every render re-scanned all 6,867 rows and re-hit
    the stub oracle, and the file itself misrepresented the real open count. prune rewrites the log
    to load_best()'s output so the file matches what the tools already compute.

    Atomic (temp + os.replace) so an interrupt never truncates the log. Idempotent."""
    before = sum(1 for _ in open(JSONL)) if os.path.exists(JSONL) else 0
    kept = load_best()                          # already: drop-now-matched (P9) + best-per-addr
    tmp = JSONL + ".tmp"
    with open(tmp, "w") as f:
        for r in kept:
            f.write(json.dumps({k: r.get(k) for k in FIELDS}) + "\n")
    os.replace(tmp, JSONL)
    print(f"backlog prune: {before} rows -> {len(kept)} open near-misses "
          f"(dropped {before - len(kept)} banked/superseded)")
    return len(kept)


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    lg = sub.add_parser("log")
    for fl in ("addr", "name", "klass", "status", "where", "draft", "source"):
        lg.add_argument(f"--{fl if fl != 'klass' else 'class'}", dest=fl, default=None)
    for fl in ("reach", "nins", "closeness"):
        lg.add_argument(f"--{fl}", type=int, default=None)
    sub.add_parser("render")
    sub.add_parser("prune")
    sh = sub.add_parser("show"); sh.add_argument("-n", type=int, default=40)
    a = ap.parse_args()
    if a.cmd == "log":
        rec = append_record({"addr": a.addr, "name": a.name, "klass": a.klass, "status": a.status,
                             "where_stuck": a.where, "best_draft": a.draft, "source": a.source,
                             "reach": a.reach, "nins": a.nins, "closeness": a.closeness})
        n = render()
        print(f"logged {rec.get('name') or rec.get('addr')}; backlog open={n}")
    elif a.cmd == "render":
        print(f"docs/backlog.md: {render()} open near-misses")
    elif a.cmd == "prune":
        prune(); render()
    elif a.cmd == "show":
        for i, r in enumerate(sorted(load_best(), key=_rank_key)[:a.n], 1):
            print(f"{i:3} {r.get('name'):16} reach={r.get('reach')} {r.get('klass'):7} "
                  f"nins={r.get('nins')} {r.get('status')} close={r.get('closeness')} "
                  f"<{r.get('where_stuck')}>")


if __name__ == "__main__":
    main()
