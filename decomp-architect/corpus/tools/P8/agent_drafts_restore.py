#!/usr/bin/env python3
"""agent_drafts_restore.py — rebuild a subagent's FINAL deliverable draft from its transcript (P32 T3, 2026-09-05).

WHY. Agent-tool drafters write their deliverable to a shared scratch dir. In the T3 wave one agent's tidy-up
(`find <dir> -maxdepth 1 -type f ! -name <mine> -exec mv {} _scratch/`) swept eleven sibling deliverables away;
two of them were MATCHes. The transcript (`~/.claude/projects/<proj>/<session>/subagents/agent-*.jsonl`) still holds
every Write/Edit the agent made, so the file can be REPLAYED: apply each Write/Edit/heredoc/cp/mv in order and keep
the last state of every path that looks like a deliverable.

    python3 tools/agent_drafts_restore.py <subagents-dir> --out <dir> [--pattern REGEX]

Prints one line per agent: the deliverable path(s) rebuilt, the op count, and the number of Edit ops whose old_string
was NOT found (an edit applied to a file the agent had changed via sed/python in between — a replay that reports
misses > 0 may be STALE; verify it with rtu_match and prefer an on-disk copy if one exists). An agent with no
deliverable prints NO-DELIVERABLE so nothing is silently skipped (R32). Replay is a RECOVERY route, never the primary:
verify every rebuilt draft against the real TU before believing its verdict.
"""
import argparse, glob, json, os, re

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__))) + "/"


def norm(p):
    if not p:
        return p
    p = p.replace(REPO, "")
    return p[2:] if p.startswith("./") else p


def replay(tp, pattern):
    files, ops = {}, []
    for line in open(tp, errors="replace"):
        try:
            o = json.loads(line)
        except Exception:
            continue
        if o.get("type") != "assistant":
            continue
        for c in (o.get("message") or {}).get("content") or []:
            if c.get("type") != "tool_use":
                continue
            n, i = c.get("name"), c.get("input") or {}
            if n == "Write":
                p = norm(i.get("file_path")); files[p] = i.get("content", ""); ops.append(("W", p))
            elif n == "Edit":
                p = norm(i.get("file_path"))
                if p not in files:
                    ops.append(("EDIT-UNKNOWN", p)); continue
                old, new = i.get("old_string", ""), i.get("new_string", "")
                if i.get("replace_all"):
                    files[p] = files[p].replace(old, new); ops.append(("E", p))
                elif old in files[p]:
                    files[p] = files[p].replace(old, new, 1); ops.append(("E", p))
                else:
                    ops.append(("EDIT-MISS", p))
            elif n == "Bash":
                cmd = i.get("command", "")
                for m in re.finditer(r"\b(cp|mv)\s+(?:-\w+\s+)*(\S+)\s+(\S+\.c)\b", cmd):
                    src, dst = norm(m.group(2)), norm(m.group(3))
                    if src in files:
                        files[dst] = files[src]; ops.append((m.group(1), src, dst))
                    elif os.path.exists(REPO + src):
                        files[dst] = open(REPO + src, errors="replace").read(); ops.append((m.group(1) + "-disk", src, dst))
                    else:
                        ops.append((m.group(1) + "-UNKNOWN", src, dst))
                for m in re.finditer(r"cat\s*>\s*(\S+\.c)\s*<<\s*'?(\w+)'?\n(.*?)\n\2\b", cmd, re.S):
                    p = norm(m.group(1)); files[p] = m.group(3) + "\n"; ops.append(("HEREDOC", p))
    deliv = [p for p in files if p and re.search(pattern, p)]
    return files, ops, deliv


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("subagents_dir")
    ap.add_argument("--out", required=True)
    ap.add_argument("--pattern", default=r"/(opus|sonnet|haiku)/func_[0-9A-Fa-f]{8}\.c$",
                    help="regex a path must match to count as a deliverable")
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    n_agents = n_files = 0
    for tp in sorted(glob.glob(os.path.join(a.subagents_dir, "agent-*.jsonl"))):
        n_agents += 1
        tag = os.path.basename(tp)[len("agent-"):-len(".jsonl")]
        files, ops, deliv = replay(tp, a.pattern)
        misses = sum(1 for x in ops if "MISS" in x[0] or "UNKNOWN" in x[0])
        if not deliv:
            print(f"{tag}: NO-DELIVERABLE ops={len(ops)}")
            continue
        for p in deliv:
            arm = p.split("/")[-2]; fn = os.path.basename(p)[:-2]
            outp = os.path.join(a.out, f"{arm}__{fn}__{tag}.c")
            open(outp, "w").write(files[p]); n_files += 1
            flag = "" if misses == 0 else f"  ** {misses} unreplayable op(s): VERIFY, prefer an on-disk copy"
            print(f"{tag} {arm} {fn} -> {outp} ({len(files[p])} chars, ops={len(ops)}){flag}")
    print(f"agents={n_agents} deliverables rebuilt={n_files} -> {a.out}")


if __name__ == "__main__":
    main()
