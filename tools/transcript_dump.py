#!/usr/bin/env python3
"""transcript_dump.py — condense a Claude Code session transcript (JSONL) into readable text (P32 T3 recovery, 2026-09-05).

WHY. When a session dies without a checkpoint (context overflow mid-wave), the successor must reconstruct what it did
from `~/.claude/projects/<proj>/<session>.jsonl` — 6 MB of JSON that cannot be read raw. This prints, in order, every
assistant text/thinking, every tool call (Bash commands in full, Edit/Write/Agent inputs abbreviated) and every tool
result truncated (agent verdicts kept longer), with timestamps, so a successor can read the session in ~150 KB and find
the last checkpoint write, the commits, and what was in flight.

    python3 tools/transcript_dump.py <session.jsonl> <out.txt>
Then `grep -n` the output for the last checkpoint/commit and read from there. Pair with tools/agent_verdicts.py,
tools/agent_reports.py and tools/agent_drafts_restore.py for the subagents.
"""
import json,sys,re
f=sys.argv[1]; out=open(sys.argv[2],'w')
def trunc(s,n):
    s=s if isinstance(s,str) else json.dumps(s)
    return s if len(s)<=n else s[:n]+f' …[+{len(s)-n} chars]'
msgs=[]
for line in open(f):
    try: o=json.loads(line)
    except: continue
    t=o.get('type')
    if t not in ('user','assistant','system'): continue
    msgs.append(o)
for o in msgs:
    ts=(o.get('timestamp') or '')[11:19]
    t=o['type']
    m=o.get('message') or {}
    content=m.get('content') if isinstance(m,dict) else m
    if t=='system':
        out.write(f"\n[{ts}] SYSTEM: {trunc(o.get('content') or json.dumps(m),400)}\n"); continue
    if isinstance(content,str):
        if t=='user':
            out.write(f"\n[{ts}] USER: {trunc(content,3000)}\n")
        else:
            out.write(f"\n[{ts}] ASSISTANT: {content}\n")
        continue
    for c in content or []:
        ct=c.get('type')
        if ct=='text':
            if t=='user':
                txt=c['text']
                if txt.startswith('<system-reminder>') or txt.startswith('<local-command'):
                    out.write(f"\n[{ts}] USER(sys): {trunc(txt,300)}\n")
                else:
                    out.write(f"\n[{ts}] USER: {trunc(txt,3000)}\n")
            else:
                out.write(f"\n[{ts}] ASSISTANT: {c['text']}\n")
        elif ct=='thinking':
            out.write(f"\n[{ts}] THINKING: {trunc(c.get('thinking',''),1200)}\n")
        elif ct=='tool_use':
            name=c.get('name'); inp=c.get('input') or {}
            if name=='Bash':
                out.write(f"\n[{ts}] TOOL Bash: {trunc(inp.get('command',''),2500)}\n   # {inp.get('description','')}\n")
            elif name in ('Edit',):
                out.write(f"\n[{ts}] TOOL Edit {inp.get('file_path')}:\n   OLD: {trunc(inp.get('old_string',''),400)}\n   NEW: {trunc(inp.get('new_string',''),1200)}\n")
            elif name=='Write':
                out.write(f"\n[{ts}] TOOL Write {inp.get('file_path')} ({len(inp.get('content',''))} chars):\n{trunc(inp.get('content',''),1500)}\n")
            elif name=='Agent':
                out.write(f"\n[{ts}] TOOL Agent model={inp.get('model')} type={inp.get('subagent_type')} desc={inp.get('description')}\n   PROMPT: {trunc(inp.get('prompt',''),700)}\n")
            elif name=='Read':
                out.write(f"\n[{ts}] TOOL Read {inp.get('file_path')} off={inp.get('offset')} lim={inp.get('limit')}\n")
            else:
                out.write(f"\n[{ts}] TOOL {name}: {trunc(inp,800)}\n")
        elif ct=='tool_result':
            rc=c.get('content')
            if isinstance(rc,list):
                rc=' '.join(x.get('text','') for x in rc if isinstance(x,dict))
            rc=rc or ''
            lim=1800
            if 'verdict' in rc.lower() and '{' in rc: lim=6000
            out.write(f"\n[{ts}] RESULT: {trunc(rc,lim)}\n")
out.close()
