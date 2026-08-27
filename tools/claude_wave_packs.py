#!/usr/bin/env python3
"""tools/claude_wave_packs.py — build the per-function PACKS a Claude-subagent wave drafts from (P31 S62 T4).

The pack is EXACTLY what tools/api_agent.py sends a paid model: api_agent.user_msg(target, card) +
prior_draft (law-1c filtered: symbols must overlap the target .s) + gate_feedback, plus api_agent.SYS
written once. Identical packs are what made the T4 arms comparable; keep it that way.

Usage: claude_wave_packs.py <targets.json> <out_dir> [--cards cards.json]
  targets.json: [{name, binary, nins, sub, asm, tu}, ...]   (api_agent's target shape; see
                tools/main_queue_rebuild.py / .run/t4/targets.json for how to derive one from corpus)
  out_dir/SYS.md + out_dir/packs/<fn>.md are produced; the workflow script
  tools/workflows/claude_wave_draft.js points its agents at them (edit REPO/paths at the top).
Then: Workflow(scriptPath=tools/workflows/claude_wave_draft.js, args={targets:[{name,binary,nins,sub}...]})
  -> drafts in .run/<wave>/<arm>/<fn>.c -> tools/wave_judge.py <arms...> [--union]  (whole-binary gate,
  banked = removed INCLUDE_ASM lines in git diff; tree reset between arms; --union leaves the best
  cheapest arm's drafts in the tree for the commit). Routing rule measured in T4 (CURRENT_PHASE S62):
  <=50 ins Sonnet (+DeepSeek if funded), 51-120 Sonnet, >120 Opus, Opus on every residue."""
import sys, os, json, glob
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__))); os.chdir(REPO)
sys.path.insert(0, 'tools')
for k, v in (('API_BASE', 'x'), ('API_KEY', 'x'), ('MODEL', 'x'), ('MAXTOK', '8000')):
    os.environ.setdefault(k, v)
import api_agent as A

def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    targets = json.load(open(sys.argv[1])); out = sys.argv[2]
    cards = {}
    if '--cards' in sys.argv:
        for c in json.load(open(sys.argv[sys.argv.index('--cards') + 1])):
            if c.get('fn'): cards[c['fn']] = c
    else:   # newest per-fn card across every wave card file
        for f in sorted(glob.glob('.run/wave_*_cards.json'), key=os.path.getmtime):
            try:
                for e in json.load(open(f)):
                    if isinstance(e, dict) and e.get('fn'): cards[e['fn']] = e
            except Exception:
                pass
    os.makedirs(os.path.join(out, 'packs'), exist_ok=True)
    open(os.path.join(out, 'SYS.md'), 'w').write(A.SYS)
    n = 0
    for t in targets:
        um = A.user_msg(t, cards.get(t['name']))
        pd, where = A.prior_draft(t)
        if pd:
            um += ("\n\nA PREVIOUS ATTEMPT on this exact function left this body behind (%s). The whole-binary "
                   "byte-gate did NOT accept it, so it is wrong somewhere — but it is usually wrong in ONE place; "
                   "keep what matches the .s, fix what does not. Discard it if it is a different function's body."
                   "\n\n```c\n" % where) + pd.strip() + "\n```\n"
        gf = A.gate_feedback(t)
        if gf:
            um += '\n\n' + gf + '\n'
        open(os.path.join(out, 'packs', t['name'] + '.md'), 'w').write(um); n += 1
    print('packs: %d written to %s (cards matched %d/%d)' % (n, out, sum(1 for t in targets if t['name'] in cards), len(targets)))

if __name__ == '__main__':
    main()
