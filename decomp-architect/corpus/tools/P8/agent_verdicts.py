#!/usr/bin/env python3
"""agent_verdicts.py — pull the FINAL JSON verdict out of Agent-tool subagent transcripts (P31 S79 #9 handoff).

The drafting agents of task #9 were Agent-tool subagents (not a Workflow), so their results live only in
the harness transcript files (JSONL, one message per line; huge — never cat them into a session). Each
agent's last assistant text ends with one JSON object {"fn","binary","arm","status","closeness","compiles",
"draft_path","note"}. This prints those objects (one per file, as JSONL) and appends them to a ledger.

    python3 tools/agent_verdicts.py <transcript.output> [...] [--append .run/S79w/verdicts/verdicts.jsonl]
    python3 tools/agent_verdicts.py /tmp/claude-1000/-home-musashi-bfm-decomp/<session>/tasks/*.output --append ...
A file with no verdict prints {"file":..., "status":"NO-VERDICT"} so nothing is silently skipped (R32).
"""
import json, re, sys

def texts(path):
    out = []
    for ln in open(path, errors="replace"):
        ln = ln.strip()
        if not ln:
            continue
        try:
            j = json.loads(ln)
        except Exception:
            out.append(ln); continue
        def walk(x):
            if isinstance(x, str): out.append(x)
            elif isinstance(x, dict):
                for v in x.values(): walk(v)
            elif isinstance(x, list):
                for v in x: walk(v)
        walk(j)
    return out

def verdict(path):
    pat = re.compile(r'\{"fn"\s*:\s*"func_[0-9A-Fa-f]+".*?"note"\s*:\s*".*?"\s*\}', re.S)
    best = None
    for t in texts(path):
        for m in pat.finditer(t):
            try:
                best = json.loads(m.group(0))
            except Exception:
                try: best = json.loads(m.group(0).encode().decode("unicode_escape"))
                except Exception: pass
    return best

def main():
    args = sys.argv[1:]
    app = None
    if "--append" in args:
        i = args.index("--append"); app = args[i + 1]; del args[i:i + 2]
    rows = []
    for p in args:
        v = verdict(p) or {"file": p, "status": "NO-VERDICT"}
        v.setdefault("file", p); rows.append(v)
        print(json.dumps(v)[:600])
    if app:
        with open(app, "a") as f:
            for v in rows: f.write(json.dumps(v) + "\n")
        print(f"appended {len(rows)} row(s) -> {app}")

if __name__ == "__main__":
    main()
