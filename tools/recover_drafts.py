#!/usr/bin/env python3
"""Recover agent-written draft files from a workflow run's TRANSCRIPTS. (P30 S48)

WHY THIS EXISTS. A 28-agent wave wrote its drafts into one shared directory, and later agents
deleted earlier agents' files while tidying. 21 adversarially-VERIFIED cracks looked destroyed and
were written off; a 5M-token re-crack wave was launched before Drew asked the right question —
"can you just analyse the workflow results to get those back?"

They were all recoverable. Every agent tool call is recorded in the run transcript WITH ITS CONTENT,
so the transcript is the backup for anything an agent produced. Recovery is deterministic and costs
zero agent tokens.

THE METHOD, and why the two obvious shortcuts fail:
  * Taking each `Write` record's content recovers only the drafts that were written once — agents
    REFINE. (Measured: 8 of 21.)
  * Taking each `Edit`'s `new_string` as a file is worse: it is a FRAGMENT, not a file.
  So: replay the mutation history per (agent, file_path) — `Write` sets the content, `Edit` applies
  old->new to the current content — and snapshot after EVERY mutation. The wanted file state is one
  of those snapshots, usually but not always the last (an agent may end on a failed experiment).
  (Measured: 20 of 21.)
  * The last file never used Write/Edit at all — it was written by a shell heredoc. So also scan
  `Bash` commands for `<<'EOF' … EOF` bodies. (Measured: 21 of 21.)

Snapshots are emitted newest-first so a caller can gate them in order and stop at the first MATCH;
`--gate` does exactly that when given the per-function asm subdir map.

    tools/recover_drafts.py <run_dir> --names func_A,func_B --out .run/recover
    tools/recover_drafts.py <run_dir> --names-json lost.json --out .run/recover \
        --gate targets.json     # [{"name":..., "sub":...}] -> runs match_one, writes recovered.json
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEREDOC_RE = re.compile(r"<<\s*'?(\w+)'?\s*\n(.*?)\n\1", re.S)


def _tool_blocks(obj, out):
    """Every {name, input} tool-use block anywhere in a transcript record."""
    if isinstance(obj, dict):
        if isinstance(obj.get("input"), dict) and obj.get("name"):
            out.append((obj["name"], obj["input"]))
        for v in obj.values():
            _tool_blocks(v, out)
    elif isinstance(obj, list):
        for v in obj:
            _tool_blocks(v, out)


def snapshots(run_dir, names):
    """{fn: [content, ...]} newest-first, deduped, from every agent transcript in `run_dir`."""
    want = set(names)
    per_fn = {n: [] for n in want}
    for path in sorted(glob.glob(os.path.join(run_dir, "agent-*.jsonl"))):
        state = {}                                  # file_path -> current content, PER AGENT
        for line in open(path, errors="ignore"):
            if not any(t in line for t in ('"Write"', '"Edit"', '"Bash"')):
                continue
            try:
                rec = json.loads(line)
            except Exception:
                continue
            ops = []
            _tool_blocks(rec, ops)
            for name, inp in ops:
                if name == "Bash":                  # heredoc-written files
                    cmd = inp.get("command", "") or ""
                    for _tag, body in HEREDOC_RE.findall(cmd):
                        for fn in want:
                            if fn in body and "{" in body:
                                per_fn[fn].append(body)
                    continue
                fp = inp.get("file_path", "") or ""
                if not fp.endswith(".c"):
                    continue
                fn = os.path.basename(fp)[:-2]
                if fn not in want:
                    continue
                if name == "Write":
                    state[fp] = inp.get("content", "")
                else:
                    cur = state.get(fp)
                    if cur is None:
                        continue                    # an Edit to a file this agent never wrote
                    old, new = inp.get("old_string", ""), inp.get("new_string", "")
                    if not old or old not in cur:
                        continue                    # stale/failed edit — keep the prior state
                    state[fp] = cur.replace(old, new) if inp.get("replace_all") else cur.replace(old, new, 1)
                per_fn[fn].append(state[fp])
    out = {}
    for fn, versions in per_fn.items():
        seen, uniq = set(), []
        for c in reversed(versions):                # newest first
            h = hash(c)
            if h in seen:
                continue
            seen.add(h)
            uniq.append(c)
        if uniq:
            out[fn] = uniq
    return out


def gate(fn, path, sub):
    r = subprocess.run(f"python3 tools/match_one.py {fn} --c {path} --asm-subdir {sub}",
                       shell=True, cwd=REPO, capture_output=True, text=True, timeout=600)
    first = (r.stdout or "").strip().split("\n")[0]
    return first.startswith("MATCH"), first[:80]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("run_dir", help="the workflow run's transcript dir (…/subagents/workflows/wf_…)")
    ap.add_argument("--names", help="comma-separated func_XXXXXXXX to recover")
    ap.add_argument("--names-json", help="JSON list of {'fn':…} or bare names")
    ap.add_argument("--out", default=".run/recover")
    ap.add_argument("--gate", metavar="TARGETS_JSON",
                    help="[{name, sub}] — gate snapshots newest-first, keep the first MATCH")
    a = ap.parse_args()

    names = set()
    if a.names:
        names |= {x.strip() for x in a.names.split(",") if x.strip()}
    if a.names_json:
        for r in json.load(open(a.names_json)):
            names.add(r["fn"] if isinstance(r, dict) else r)
    if not names:
        ap.error("give --names or --names-json")

    snaps = snapshots(a.run_dir, names)
    outdir = os.path.join(REPO, a.out)
    for fn, versions in snaps.items():
        d = os.path.join(outdir, fn)
        os.makedirs(d, exist_ok=True)
        for i, c in enumerate(versions):
            open(os.path.join(d, f"v{i:02d}.c"), "w").write(c)
    missing = sorted(names - set(snaps))
    print(f"recover_drafts: {len(snaps)}/{len(names)} functions have snapshots "
          f"({sum(len(v) for v in snaps.values())} versions) -> {a.out}"
          + (f"; NO RECORD: {missing}" if missing else ""))

    if not a.gate:
        return 0
    subs = {t["name"]: t["sub"] for t in json.load(open(a.gate))}
    hits = {}
    for fn, versions in sorted(snaps.items()):
        sub = subs.get(fn)
        if not sub:
            print(f"  {fn}: no asm subdir given — skipped"); continue
        for i, _c in enumerate(versions):
            p = os.path.join(a.out, fn, f"v{i:02d}.c")
            ok, line = gate(fn, p, sub)
            if ok:
                hits[fn] = p
                print(f"  MATCH {fn} <- v{i:02d}.c")
                break
        else:
            print(f"  no version matches: {fn} ({len(versions)} tried)")
    json.dump(hits, open(os.path.join(REPO, a.out, "recovered.json"), "w"), indent=1)
    print(f"recover_drafts: {len(hits)}/{len(snaps)} gated MATCH -> {a.out}/recovered.json")
    return 0


if __name__ == "__main__":
    sys.exit(main())
