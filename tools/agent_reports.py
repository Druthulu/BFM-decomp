#!/usr/bin/env python3
"""agent_reports.py — save each Agent-tool subagent's FINAL message (its full prose report) to a file (P32 T3, 2026-09-05).

`agent_verdicts.py` extracts only the one-line JSON verdict. The agent's final message also carries the evidence a
successor needs to route a NEAR or bank a MATCH — the levers that closed it, the levers measured INERT, the residual's
mechanism, TU-plumbing warnings ("do NOT hoist this extern"). Those lived only inside the transcript JSONL (never cat
one into a session) until this tool: it writes one Markdown file per agent, named by the function and arm.

    python3 tools/agent_reports.py <subagents-dir> --out <dir>
    # -> <dir>/<fn>__<arm>__<agentId>.md  (header: model, start/end, target; body: the final assistant message)

Agents whose prompt names no function are written as UNKNOWN__… (R32: nothing silently skipped).
"""
import argparse, glob, json, os, re


def parse(tp):
    first = last = model = None; prompt = ""; final = ""
    for line in open(tp, errors="replace"):
        try:
            o = json.loads(line)
        except Exception:
            continue
        ts = o.get("timestamp")
        if ts:
            first = first or ts; last = ts
        t = o.get("type"); m = o.get("message") or {}
        if t == "user" and not prompt:
            c = m.get("content")
            if isinstance(c, str):
                prompt = c
            elif isinstance(c, list):
                prompt = " ".join(x.get("text", "") for x in c if isinstance(x, dict) and x.get("type") == "text")
        if t == "assistant":
            model = model or m.get("model")
            for x in m.get("content") or []:
                if x.get("type") == "text" and x["text"].strip():
                    final = x["text"]
    fn = re.findall(r"func_[0-9A-Fa-f]{8}", prompt)
    arm = re.search(r"\bArm:\s*(\w+)", prompt)
    binm = re.search(r"in binary (\S+)", prompt)
    return dict(model=model, start=first, end=last, fn=fn[0] if fn else "UNKNOWN",
                arm=(arm.group(1) if arm else "unknown"), binary=(binm.group(1) if binm else "?"),
                prompt=prompt, final=final)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("subagents_dir"); ap.add_argument("--out", required=True)
    a = ap.parse_args(); os.makedirs(a.out, exist_ok=True); n = 0
    for tp in sorted(glob.glob(os.path.join(a.subagents_dir, "agent-*.jsonl"))):
        tag = os.path.basename(tp)[len("agent-"):-len(".jsonl")]
        r = parse(tp)
        outp = os.path.join(a.out, f"{r['fn']}__{r['arm']}__{tag}.md")
        with open(outp, "w") as f:
            f.write(f"# {r['binary']}:{r['fn']} — arm {r['arm']} — model {r['model']}\n")
            f.write(f"agent {tag} · start {r['start']} · end {r['end']} · transcript {tp}\n\n")
            f.write("## Task prompt (first 600 chars)\n\n" + r["prompt"][:600] + "\n\n## Final report (verbatim)\n\n" + r["final"] + "\n")
        n += 1
        print(f"{r['binary']:13} {r['fn']:14} {r['arm']:7} -> {outp}")
    print(f"agents={n} -> {a.out}")


if __name__ == "__main__":
    main()
