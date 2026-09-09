"""The wave gate driver — the S49 practice, paid for in two incidents (cookbook §169 law 3).

Usage: tools/gate_lane.py <wavedir> <slate-or-confirmed.json> [results.json]
Accepts either shape (`name` or `fn` per record) and takes an explicit `draft` path when present.

The contract, and why each clause exists:
  - group drafts by (binary, destination split .c)
  - gate_stage --no-propagate --commit, NO outer timeout (the tool owns its own)
  - revert any residue between groups; abort loudly if the tree is dirty at entry
  - propagate PER FUNCTION afterwards, committing each
Usage: gate_lane.py <wavedir> <slate.json> [results.json]"""
import json, os, shutil, subprocess, sys, collections, glob
sys.path.insert(0,'tools'); import corpus
wavedir, slate = sys.argv[1], sys.argv[2]
outp = sys.argv[3] if len(sys.argv)>3 else '.run/gate_lane_results.json'
raw=[c for c in json.load(open(slate)) if isinstance(c,dict) and (c.get('name') or c.get('fn'))]
cards=[dict(c, name=c.get('name') or c.get('fn')) for c in raw]     # accept slate OR confirmed shape
if not cards: sys.exit(f"R32: {slate} yielded 0 usable records — wrong shape?")
def dirty(): return subprocess.run("git status --porcelain -- src/ config/",shell=True,
                                   capture_output=True,text=True).stdout.strip()
def writers(): return subprocess.run("pgrep -af 'dedup_propagate|gate_stage|harvest_verify'",
                                     shell=True,capture_output=True,text=True).stdout
if dirty(): sys.exit("TREE DIRTY at entry — resolve before gating:\n"+dirty()[:400])

# The stub's HOME .c, DERIVED from the corpus oracle (R33) rather than re-globbed. The old
# `glob("src/<binary>/*.c")` was structurally blind to `main`, whose sources live at src/*.c —
# every main draft grouped under src=None (R36: a consumer silently ignoring a real binary).
# corpus.stubs() already carries the answer on each record: Stub.path.
_HOME={}
def _home(binary, fn):
    if binary not in _HOME:
        _HOME[binary]={st.symbol: st.path for st in corpus.stubs(binary).values()}
    return _HOME[binary].get(fn)

groups=collections.defaultdict(list)
for c in cards:
    p=c.get('draft') or f"{wavedir}/{c['name']}/{c['name']}.c"   # explicit path wins (agents use per-binary dirs)
    if not os.path.isfile(p): continue
    src=_home(c['binary'], c['name'])
    groups[(c['binary'],src)].append((c['name'],p))
n_g=sum(len(v) for v in groups.values())
missing=[c['name'] for c in cards if not os.path.isfile(c.get('draft') or f"{wavedir}/{c['name']}/{c['name']}.c")]
if n_g != len(cards):   # R32: a silent skip is a DEFECT, not a no-op
    print(f"R32 COVERAGE: {len(cards)} records -> {n_g} gateable; {len(missing)} missing drafts: {missing[:8]}", flush=True)
    if n_g == 0: sys.exit("R32: nothing gateable — refusing to report 0 as a result")
print(f"gating {n_g} drafts in {len(groups)} groups", flush=True)
banked=[]; res={}; crashed=[]
for (b,src),items in sorted(groups.items()):
    if dirty():
        subprocess.run("git checkout -- src/ config/",shell=True); print("  (reverted residue)",flush=True)
    d=f".run/gate_lane/{b}__{os.path.basename(src or 'x')}"
    shutil.rmtree(d,ignore_errors=True); os.makedirs(d,exist_ok=True)
    for n,p in items: shutil.copy(p,f"{d}/{n}.c")
    sub=os.path.dirname(corpus.asm_path(b,items[0][0]) or "")
    cmd=[".venv/bin/python","tools/gate_stage.py","--drafts",d,"--binary",b,"--no-propagate","--commit"]
    if src: cmd+=["--src",src,"--src-file",src]
    if sub: cmd+=["--asm-subdir",sub]
    r=subprocess.run(cmd,capture_output=True,text=True)          # NO outer timeout (§169 law 3)
    js=[l for l in (r.stdout+r.stderr).splitlines() if l.startswith('{')]
    # A CRASH IS NOT A RESULT. Without this, an unhandled gate_stage exception (e.g.
    # corpus.CorpusError) left js empty -> v={} -> "0 banked", INDISTINGUISHABLE from an honest
    # empty gate. That cost two cycles in P31. Surface stderr and label the group CRASH.
    if r.returncode != 0 or not js:
        tail="\n".join((r.stderr or r.stdout or "").strip().splitlines()[-12:])
        v={'CRASH':True,'returncode':r.returncode,'stderr_tail':tail,'verified':[]}
        crashed.append(f"{b}:{src}")
        print(f"  {b:14} {os.path.basename(src or ''):34} {len(items)}d -> ‼ CRASH rc={r.returncode} "
              f"(NOT an empty result)\n{tail}", flush=True)
    else:
        v=json.loads(js[-1])
        got=v.get('verified',[])
        print(f"  {b:14} {os.path.basename(src or ''):34} {len(items)}d -> {len(got)} banked", flush=True)
    banked+=v.get('verified',[])
    res[f"{b}:{src}"]=v
    json.dump(res,open(outp,'w'),indent=1)
if dirty(): subprocess.run("git checkout -- src/ config/",shell=True)
print(f"\nBANKED {len(banked)}: {banked}", flush=True)
if crashed:
    print(f"‼ {len(crashed)} GATE GROUP(S) CRASHED and were NEVER GATED: {crashed}\n"
          f"  Their drafts are unjudged — re-run those groups after fixing the cause "
          f"(run tools/gate_stage.py directly for the full traceback).", flush=True)
json.dump(banked,open(outp.replace('.json','_banked.json'),'w'))
# propagate per function
for fn in banked:
    addr="0x"+fn.split("_")[1].lower()
    r=subprocess.run([".venv/bin/python","tools/share_body.py","--apply","--bucket","new","--batches","1"],   # P35 T6
                     capture_output=True,text=True)
    if dirty():
        tag=os.environ.get("GATE_PHASE","decomp")   # P31 T1: was hardcoded "phase-30 S49"
        subprocess.run("git add src/ config/",shell=True)
        # S59: never stage main's TUs from an overlay propagate — one writer (gate_main),
        # one committer (main_lane). See ox_campaign.unstage_main_tus.
        subprocess.run("git reset -q -- src/*.c",shell=True)
        subprocess.run(f'git commit -q -m "feat({tag}): propagate {fn} (gate lane)"',shell=True)
        print(f"  prop {fn}: committed", flush=True)
print("DONE", flush=True)
if crashed: sys.exit(f"EXIT NON-ZERO: {len(crashed)} gate group(s) crashed — output above is INCOMPLETE.")
