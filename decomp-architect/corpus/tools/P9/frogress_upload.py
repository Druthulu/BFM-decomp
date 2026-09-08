#!/usr/bin/env python3
"""frogress_upload.py — push docs/progress.json to a frogress instance (progress.deco.mp) (P33 D3).

    tools/frogress_upload.py                       # --dry-run is the default: prints the payload, sends nothing
    tools/frogress_upload.py --push --project bfm --version us     # needs FROGRESS_API_SECRET in the environment

frogress projects are created by the frogress maintainers (a slug + an API key are issued to the project owner);
the upload is `POST https://progress.deco.mp/data/<project>/<version>/` with a JSON body
`{"api_key": …, "entries": [{"git_hash": …, "timestamp": …, "categories": {"default": {measure: value, …}}}]}`
(schema as documented by decomp.me's frogress; treat the endpoint's answer as data, X2). Measures sent, every one with
its denominator (R41): functions / instructions / distinct code / main game code matched and total, binaries
byte-identical and total. Stdlib only. The secret is never written anywhere; a missing secret with --push is an error.
"""
import argparse
import json
import os
import pathlib
import subprocess
import sys
import urllib.request

REPO = pathlib.Path(__file__).resolve().parent.parent


def payload(d, git_hash, ts, key):
    f, c = d["fleet"], d["counts"]
    ok_bins = sum(1 for r in d["per_binary"] if r["matchable"] and r["byte_identical"] == r["matchable"])
    m = {
        "fns_matched": f["fn_count"]["matched"], "fns_total": f["fn_count"]["total"],
        "instr_matched": f["instr_weighted"]["matched"] if f["instr_weighted"] else 0,
        "instr_total": f["instr_weighted"]["total"] if f["instr_weighted"] else 0,
        "distinct_matched": f["distinct_code"]["matched"] if f["distinct_code"] else 0,
        "distinct_total": f["distinct_code"]["total"] if f["distinct_code"] else 0,
        "main_matched": f["main_game_code"]["matched"] if f["main_game_code"] else 0,
        "main_total": f["main_game_code"]["total"] if f["main_game_code"] else 0,
        "binaries_ok": ok_bins, "binaries_total": d["binaries"],
        "linked_sony_functions": c["linked_psyq_objects"], "verbatim_asm_bodies": c["verbatim_asm_bodies"],
    }
    return {"api_key": key, "entries": [{"git_hash": git_hash, "timestamp": ts, "categories": {"default": m}}]}


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--push", action="store_true", help="actually POST (default: dry run)")
    ap.add_argument("--project", default="bfm")
    ap.add_argument("--version", default="us")
    ap.add_argument("--url", default="https://progress.deco.mp")
    ap.add_argument("--in", dest="inp", default=str(REPO / "docs/progress.json"))
    a = ap.parse_args(argv)
    d = json.loads(pathlib.Path(a.inp).read_text(encoding="utf-8"))
    git_hash = subprocess.run(["git", "-C", str(REPO), "rev-parse", "HEAD"], capture_output=True, text=True).stdout.strip()
    ts = int(subprocess.run(["git", "-C", str(REPO), "log", "-1", "--format=%ct"], capture_output=True, text=True).stdout.strip() or 0)
    key = os.environ.get("FROGRESS_API_SECRET", "")
    body = payload(d, git_hash, ts, key if a.push else "<FROGRESS_API_SECRET>")
    endpoint = f"{a.url.rstrip('/')}/data/{a.project}/{a.version}/"
    if not a.push:
        print(f"frogress_upload: DRY RUN — would POST to {endpoint}:")
        print(json.dumps(body, indent=1))
        return 0
    if not key:
        sys.exit("frogress_upload: --push needs FROGRESS_API_SECRET in the environment (never in a file)")
    req = urllib.request.Request(endpoint, data=json.dumps(body).encode(), headers={"Content-Type": "application/json"}, method="POST")
    with urllib.request.urlopen(req, timeout=60) as resp:
        text = resp.read().decode("utf-8", "replace")
        print(f"frogress_upload: HTTP {resp.status} {text[:300]}")
        return 0 if 200 <= resp.status < 300 else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
