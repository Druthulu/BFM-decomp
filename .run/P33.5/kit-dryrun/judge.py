#!/usr/bin/env python3
"""judge.py — the main session's independent judgment of one dry-run (P33.5 task 13; scratch, not tracked).
Compares the produced manifest's (ACTION path) SET against expected-manifest.txt (cookbook name normalised, markers ignored),
runs the kit's Step-10 placeholder audit and the check-ignore probes inside the throwaway, counts G rules and memory seeds,
checks the commits are trailer-free, and diffs the BEFORE/AFTER guardrail values. Prints every count with its denominator."""
import json, os, pathlib, re, subprocess, sys
D = pathlib.Path(__file__).resolve().parent; R = pathlib.Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else D / "repo"
def sh(cmd, cwd=None): return subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True)
ok = True
def check(name, cond, detail=""):
    global ok; ok &= bool(cond); print(f"  [{'OK' if cond else 'FAIL'}] {name}{(' — ' + detail) if detail else ''}")
# 1. manifest set
def norm(lines):
    out = set()
    for ln in lines:
        ln = ln.strip()
        if not ln or ln.startswith('#'): continue
        m = re.match(r'(CREATED|APPENDED|SKIPPED)\s+(\S+)', ln)
        if not m: out.add(('UNPARSED', ln)); continue
        act, path = m.group(1), m.group(2)
        if re.search(r'docs/[^/]*cookbook[^/]*\.md$', path): path = 'docs/COOKBOOK.md'
        out.add((act, path))
    return out
exp = norm((D/'expected-manifest.txt').read_text().splitlines())
got = norm((D/'manifest.txt').read_text().splitlines()) if (D/'manifest.txt').exists() else set()
print(f"manifest: expected {len(exp)} entries, produced {len(got)}")
for e in sorted(exp - got): print("   missing:", e)
for e in sorted(got - exp): print("   extra:  ", e)
check("manifest set equal", exp == got)
# 2. placeholder audit (SETUP Step 10.1)
r = sh("command grep -rln '{{' --include='*.md' --include='*.txt' --include='*.sh' --include='*.py' --include='*.yml' --include='*.json' --include='*.mk' --include='Makefile' . | grep -vE '^\\./(decomp-architect|project-architect-2\\.0)/' | sort", cwd=R)
allowed = {'./docs/project-architect.md', './phase-ends/CURRENT_PHASE.template.md', './phase-ends/PhaseEnd.template.md'}
hits = set(r.stdout.split())
check("leftover placeholders only in PA's allowed files", hits <= allowed, f"hits={sorted(hits - allowed)}")
# 3. check-ignore probes
pos = ["disks/x.bin","asm/x.s","extracted/x","dumps/x.bin","ghidra/x","tools/psyq/x",".claude-state/transcripts/x",".run/scratch/x","decomp-architect/x"]
neg = ["src/main.c","config/x.yaml","extracted/retail/manifest.jsonl",".run/README.md",".claude-state/memory/MEMORY.md"]
pf = [p for p in pos if sh(f"git -C '{R}' check-ignore -q '{p}'").returncode != 0]
nf = [p for p in neg if sh(f"git -C '{R}' check-ignore -q '{p}'").returncode == 0]
check(f"check-ignore positive {len(pos)-len(pf)}/{len(pos)}", not pf, str(pf)); check(f"check-ignore negative {len(neg)-len(nf)}/{len(neg)}", not nf, str(nf))
# 4. registry, memory, commits, audit
g = len(re.findall(r'^### G\d+ ', (R/'RULES_REGISTRY.md').read_text(), re.M)) if (R/'RULES_REGISTRY.md').exists() else -1
check("registry G rules == 67", g == 67, f"got {g}")
mem = [p for p in (R/'.claude-state/memory').glob('*.md') if p.name != 'MEMORY.md'] if (R/'.claude-state/memory').exists() else []
check("memory seeds == 34", len(mem) == 34, f"got {len(mem)}")
idx = (R/'.claude-state/memory/MEMORY.md').read_text() if (R/'.claude-state/memory/MEMORY.md').exists() else ''
links = re.findall(r'\]\(([^)]+\.md)\)', idx); dangling = [l for l in links if not (R/'.claude-state/memory'/l).exists()]
check(f"MEMORY.md links resolve {len(links)-len(dangling)}/{len(links)}", not dangling, str(dangling[:5]))
log = sh(f"git -C '{R}' log --format='%s%n%b'").stdout
check("commits trailer-free", 'co-authored-by' not in log.lower())
subjects = sh(f"git -C '{R}' log --format=%s").stdout.strip().splitlines()
print("  commits:", subjects)
aud = sh("python3 tools/audit_public.py", cwd=R); check("kit audit_public exits 0 in the throwaway", aud.returncode == 0, aud.stdout.strip().splitlines()[-1] if aud.stdout.strip() else aud.stderr.strip()[-200:])
check("PhaseEnd_Phase0.5.md exists", (R/'phase-ends/PhaseEnd_Phase0.5.md').exists()); check("PhaseLog_0.5.md archived", (R/'phase-ends/logs/PhaseLog_0.5.md').exists())
check("CURRENT_PHASE.md absent after close", not (R/'phase-ends/CURRENT_PHASE.md').exists())
st = sh(f"git -C '{R}' status --porcelain").stdout.strip().splitlines(); check(f"throwaway tree clean ({len(st)} dirty)", not st, str(st[:5]))
# 5. guardrails: BEFORE vs AFTER
before = {}
for l in (D/'before.txt').read_text().splitlines():   # run 5: an EMPTY dirty set is a one-token line — never crash the reader on it
    if l.strip():
        parts = l.split(None, 1); before[parts[0]] = parts[1] if len(parts) > 1 else ''
H = os.path.expanduser('~')
after = {
 'settings_sha1': sh(f"sha1sum {H}/.claude/settings.json | cut -c1-40").stdout.strip(),
 'statusline_sha1': sh(f"sha1sum {H}/.claude/statusline.sh | cut -c1-40").stdout.strip(),
 'memory_files': sh(f"ls {H}/.claude/projects/-home-musashi-bfm-decomp/memory | wc -l").stdout.strip(),
 'dirty_paths': ','.join(sorted(l[3:] for l in sh("git -C /home/musashi/bfm-decomp status --porcelain").stdout.splitlines() if not l[3:].startswith('.run/P33.5/'))),
 'ghidra_entries': sh("ls /home/musashi/bfm-decomp/ghidra | wc -l").stdout.strip(),
 'dumps_bin': sh("ls /home/musashi/bfm-decomp/dumps/*.bin | wc -l").stdout.strip(),
 'home_claude_entries': sh(f"ls -A {H}/.claude | wc -l").stdout.strip(),
}
(D/'after.txt').write_text(''.join(f"{k} {v}\n" for k, v in after.items()))
for k in before: check(f"guardrail {k} unchanged", before[k] == after.get(k), f"{before[k]} -> {after.get(k)}")
print("JUDGE:", "PASS" if ok else "FAIL"); sys.exit(0 if ok else 1)
