#!/usr/bin/env python3
"""tools/claude_wave_packs.py — build the per-function PACKS a Claude-subagent wave drafts from (P31 S62 T4).

The pack is EXACTLY what tools/api_agent.py sends a paid model: api_agent.user_msg(target, card) +
prior_draft (law-1c filtered: symbols must overlap the target .s) + gate_feedback, plus api_agent.SYS
written once. Identical packs are what made the T4 arms comparable; keep it that way.

Usage: claude_wave_packs.py <targets.json> <out_dir> [--cards cards.json]
CARDS ARE KEYED BY (binary, fn), NEVER BY BARE NAME (R48; byte-measured P31 S63). Overlays share
function NAMES at equal addresses, and a K-class target has never been carded, so a name-keyed
lookup over `.run/wave_*_cards.json` returns SOME OTHER overlay's same-named function every time:
in wave t5a it mis-carded 48 of 48 targets, and nine agents independently reported "the pack's
warm-start/twin/decl hints were a different function". A card whose binary does not match the
target is DROPPED and counted, never silently substituted (R32/R43).
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

PY = '.venv/bin/python'
A_NO_RESIDUAL = False    # --no-residual: skip measuring prior drafts (one compile each)

def _residual_block(t, where):
    """MEASURE the prior draft instead of merely handing it over (P31 S65).

    A pack used to say only "the gate did not accept it, so it is wrong somewhere". That throws away
    the one datum that decides how the agent should spend its budget. Measured on the two t5u seeds:
    func_8017F234 was 3 mismatched of 202 (a schedule swap + one `andi` reading the copy instead of
    the pre-copy value) and func_8017E7E8 was 11 of 66 (an inverted branch + a cast written back into
    the variable rather than a temp). Told THAT, an agent edits one use site; told "it is wrong
    somewhere", it re-derives 202 instructions.

    A prior draft that measures MATCH in isolation is not a drafting job at all — the refusal is
    integration, and the pack says so and names the $0 probe instead of burning a wave slot.
    """
    import subprocess
    draft = os.path.join(REPO, where) if not os.path.isabs(where) else where
    if not os.path.exists(draft):
        return ""
    try:
        r = subprocess.run([PY, 'tools/match_one.py', t['name'], '--c', draft,
                            '--asm-subdir', t['sub'], '--json'],
                           capture_output=True, text=True, timeout=600, cwd=REPO)
        j = json.loads(r.stdout.strip().splitlines()[-1])
    except Exception as e:                 # never let the measurement break pack generation
        return "\n\n(residual not measured: %s)\n" % str(e)[:120]
    st, cl = j.get('status'), j.get('closeness')
    if st and st.endswith('-fail'):        # P31 S66: the prior draft does not even BUILD in isolation
        # `match_one --json` now answers in JSON for a toolchain failure too (it used to print bare
        # `CC1 FAIL\n<stderr>`, which json.loads swallowed as "residual not measured"). The compiler's
        # own message IS the lever — 3 of the 4 swallowed t5/r1 drafts were a decl conflict the
        # card's `decl_prior` block already answers.
        return ("\n\n================================================================================\n"
                "MEASURED: this prior draft **does not compile** (%s). The compiler said:\n\n%s\n"
                "Fix THAT first — it is usually a declaration disagreement (see the decl_prior block\n"
                "above), not a codegen problem. Re-run match_one before submitting.\n"
                "================================================================================\n"
                % (st, (j.get('error') or '').strip()[-1200:]))
    if st == 'match':
        return ("\n\n================================================================================\n"
                "MEASURED: this prior draft is **MATCH (closeness 0) in isolation** — its body is\n"
                "byte-correct. The whole-binary gate refused it for an INTEGRATION reason, not a\n"
                "codegen one, so do NOT redraft it. Run, before anything else:\n"
                "  .venv/bin/python tools/recover_integration.py --draft-dir <dir> --binary %s \\\n"
                "      --no-propagate --probe-only        # $0, names the blocker\n"
                "If the probe also says MATCH, the residual is outside the function (rodata/jump-table\n"
                "placement — the §8e JTBL_PADS class), which no C edit reaches.\n"
                "================================================================================\n"
                % t['binary'])
    # RETRIEVAL IS PUSHED, NOT PULLED (P31 S66 — measured).
    # SYS.md already says "START AT docs/cookbook-index.md — it is symptom-keyed"; agents skip it and
    # grind instead. Round-3 harvest caught two transcripts (func_800CDBA8, func_800CB00C) that
    # RE-DERIVED banked laws — the §165-19/§162d1/§30#3 birthing-boost dial and the §135-1/§165-28
    # unsigned-switch-selector rule — with an EMPTY cookbook_refs_used. That is a retrieval defect,
    # not missing knowledge, and the book's own guidance says fix RETRIEVAL rather than write more
    # prose. So when we have already MEASURED the residual and know its klass, paste the matching
    # symptom bucket into the pack instead of hoping the agent greps for it.
    def _index_bucket(klass):
        buckets = {
            'REGALLOC-PERM': 'register allocation & pins', 'REGALLOC-LOCAL': 'register allocation & pins',
            'SCHEDULE-REORDER': 'instruction scheduling', 'OPCODE-MIXED': 'instruction scheduling',
            'DELAY-SLOT': 'delay slots & branches', 'BRANCH-POLARITY': 'delay slots & branches',
            'WIDTH': 'types, signedness & load/store width', 'IMM-VALUE': 'types, signedness & load/store width',
            'IMM-OFFSET': 'types, signedness & load/store width', 'ADDRESSING': 'CSE / redundancy / rematerialization',
            'LENGTH-DRIFT': 'instruction scheduling', 'CC1-FAIL': 'declarations, prototypes & K&R',
        }
        name = buckets.get((klass or '').split('/')[0].upper())
        if not name:
            return ''
        try:
            idx = open(os.path.join(REPO, 'docs/cookbook-index.md'), errors='replace').read().splitlines()
        except Exception:
            return ''
        out, on = [], False
        for line in idx:
            if line.startswith('### '):
                if on:
                    break
                on = name in line
                if on:
                    out.append(line)
                continue
            if on and line.strip():
                out.append(line)
        if len(out) < 2:
            return ''
        head, rows = out[0], out[1:]
        shown = rows[:40]
        more = ('\n  … %d more in docs/cookbook-index.md under "%s"' % (len(rows) - len(shown), name)) if len(rows) > len(shown) else ''
        return ("\n\nTHE COOKBOOK BUCKET FOR THIS RESIDUAL CLASS (pasted so you do not have to find it;\n"
                "these are the laws that already exist for what your diff shows — READ BEFORE GRINDING):\n%s\n%s%s\n"
                % (head, "\n".join(shown), more))

    resid = j.get('residual') or []
    if st != 'near' or not resid:
        return ""
    sig = (j.get('verdict') or {}).get('sig') or ''
    klass = (j.get('verdict') or {}).get('klass') or sig
    rows = "\n".join("  idx %-4s mine %-32s tgt %s" % (e[0], e[1], e[2]) for e in resid[:16])
    more = "\n  … %d more" % (len(resid) - 16) if len(resid) > 16 else ""
    return ("\n\n================================================================================\n"
            "MEASURED RESIDUAL — this draft is **%s instruction(s)** from MATCH\n"
            "================================================================================\n"
            "`match_one` on the body above: status=near closeness=%s nins=%s  %s\n"
            "%s the length is already exact — do NOT rewrite the function; the residual is:\n\n%s%s\n\n"
            "Read the pairs before editing: two adjacent rows holding the SAME instructions in the\n"
            "opposite order are a SCHEDULE swap, not a wrong instruction; a row whose only difference\n"
            "is the register says the value came from the wrong PLACE (often: the copy instead of the\n"
            "pre-copy value); a beqz/bnez row means INVERT the test and swap the arms (their constants\n"
            "swap with them). Fix the smallest cause, then re-run match_one before submitting.\n"
            "================================================================================\n%s"
            % (cl, cl, j.get('nins'), sig,
               "Note:" if j.get('nins') else "", rows, more, _index_bucket(klass)))


_NEIGHBOR_HEADING = "## ALREADY-MATCHED NEIGHBOURS — READ THESE FIRST"


def _src_name(tu_path, name, addr):
    """The neighbour's name AS THE SOURCE SPELLS IT (P31 S77).

    `neighbor_ref` reports the symbol-table name, which for an unnamed function is Ghidra's
    `FUN_8003a0e4` — and that string appears NOWHERE in src/*.c, where the same function is
    `func_8003A0E4`. A pack that tells an agent to read `FUN_8003a0e4` sends it to grep for a name
    that does not exist, it finds nothing, and it concludes there is no neighbour — silently
    defeating the ~20x lever this block exists to supply. Resolve against the TU text and fall back
    to the address, which is never ambiguous. (R61: the pack asserted a name true of the symbol
    table and false of the world the agent works in.)"""
    try:
        txt = open(tu_path, errors='replace').read()
    except OSError:
        return name
    if name and name in txt:
        return name
    try:
        cand = "func_%08X" % int(str(addr), 16)
    except (TypeError, ValueError):
        return name
    return cand if cand in txt else name


def _render_neighbors(r):
    """The ranked worked examples, as pack markdown. SAME-TU first because it shares the decl
    environment and the carve, and its header comment usually records the levers it needed."""
    L = ["\n\n" + _NEIGHBOR_HEADING, ""]
    L.append("A neighbour is a WORKED EXAMPLE TO READ, never a body to copy — cousin-remap measured "
             "0/26 (§168 law 1). SAME-TU beats everything; an opt-level mismatch actively misleads "
             "(an -O2 example against an -O0 target, §116).")
    L.append("")
    L.append("TU `%s` — %d matched function(s) in it, %d in the binary.%s"
             % (r.get("tu"), r.get("matched_in_tu", 0), r.get("matched_in_binary", 0),
                "  **THIS TARGET IS -O0.**" if r.get("o0") else ""))
    for n in r["neighbors"]:
        L.append("")
        _nm = _src_name(r.get("tu"), n["name"], n["addr"])
        L.append("* **%s** @ %s — %d ins, score %s%s%s"
                 % (_nm, n["addr"], n["nins"], n["score"],
                    "  **<< SAME TU**" if n["same_tu"] else "",
                    ("  (symbol table calls it `%s`)" % n["name"]) if _nm != n["name"] else ""))
        L.append("  * why: %s" % "; ".join(n["why"]))
        if n.get("header"):
            L.append("  * its header comment (often names the levers it needed):")
            L.append("    ```")
            for line in n["header"].splitlines():
                L.append("    " + line)
            L.append("    ```")
    return "\n".join(L) + "\n"


def main():
    global A_NO_RESIDUAL
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    A_NO_RESIDUAL = '--no-residual' in sys.argv
    targets = json.load(open(sys.argv[1])); out = sys.argv[2]
    dup = [n for n, c in __import__('collections').Counter(t['name'] for t in targets).items() if c > 1]
    if dup:   # packs are keyed by bare fn name; two binaries' same-named fns would overwrite (R43/R48)
        sys.exit('REFUSED: %d duplicate fn name(s) in one wave (packs are name-keyed): %s' % (len(dup), ' '.join(dup)))
    cards, wrong_bin = {}, 0
    def add(e):
        nonlocal wrong_bin
        if not (isinstance(e, dict) and e.get('fn')):
            return
        b = e.get('binary') or e.get('b')
        if not b:                      # a card that cannot prove its binary cannot be trusted to a target
            wrong_bin += 1; return
        cards[(b, e['fn'])] = e
    if '--cards' in sys.argv:
        for c in json.load(open(sys.argv[sys.argv.index('--cards') + 1])): add(c)
    else:   # newest per-(binary,fn) card across every wave card file
        for f in sorted(glob.glob('.run/wave_*_cards.json'), key=os.path.getmtime):
            try:
                for e in json.load(open(f)): add(e)
            except Exception:
                pass
    os.makedirs(os.path.join(out, 'packs'), exist_ok=True)
    open(os.path.join(out, 'SYS.md'), 'w').write(A.SYS)
    n = 0
    for t in targets:
        um = A.user_msg(t, cards.get((t['binary'], t['name'])))
        pd, where = A.prior_draft(t)
        if pd:
            um += ("\n\nA PREVIOUS ATTEMPT on this exact function left this body behind (%s). The whole-binary "
                   "byte-gate did NOT accept it, so it is wrong somewhere — but it is usually wrong in ONE place; "
                   "keep what matches the .s, fix what does not. Discard it if it is a different function's body."
                   "\n\n```c\n" % where) + pd.strip() + "\n```\n"
        if pd and not A_NO_RESIDUAL:
            um += _residual_block(t, where)
        gf = A.gate_feedback(t)
        if gf:
            um += '\n\n' + gf + '\n'
        open(os.path.join(out, 'packs', t['name'] + '.md'), 'w').write(um); n += 1
    hit = sum(1 for t in targets if (t['binary'], t['name']) in cards)
    byname = sum(1 for t in targets if any(k[1] == t['name'] for k in cards))
    # PAST-ATTEMPT FUEL (P31 S71, cookbook §409/§411). Every drafting agent already wrote a
    # note per target into its workflow journal; until S71 nothing read them back, so each
    # wave re-derived the dead ends the last one paid for. Measured on the S71 wave: 38/39
    # MATCH (vs S70's 124/131 on an easier pool), 29/39 agents citing a prior attempt, and
    # 4/39 banking by RECOVERING a body that already matched. It is a pack step, not an audit.
    try:
        import journal_notes as _jn
        _idx = _jn.load()
        _hit = _add = 0
        for _t in targets:
            _fn = _t.get('name') or _t.get('fn')
            _p = os.path.join(out, "packs", "%s.md" % _fn)
            if not os.path.exists(_p):
                continue
            _rows = _jn.notes_for(_idx, _t.get('binary'), _fn)
            if not _rows:
                continue
            _hit += 1
            if _jn.HEADING in open(_p, errors='replace').read():
                continue
            open(_p, 'a').write(_jn.render(_rows))
            _add += 1
        print('past-attempt notes: %d/%d target(s) have journal history; appended to %d pack(s)'
              % (_hit, len(targets), _add))
    except Exception as _e:            # fuel is additive — never fail a wave over it
        print('past-attempt notes SKIPPED: %s: %s' % (type(_e).__name__, _e))

    # WORKED-EXAMPLE FUEL (P31 S77, playbook §2b). `neighbor_ref` answers the question that is
    # weaker than seed_ref's "is there a byte-identical twin?" and FAR more often answerable:
    # "which already-MATCHED function should this agent READ first?". S68 measured a ~20x token
    # swing on exactly that variable — every cheap large match came from an agent finding a matched
    # neighbour, and the ones with none cost 200-350k each. It has been a MANUAL per-card step in
    # the playbook ever since, wired into nothing, so in practice it ran for approximately no cards.
    # A lever the pack does not carry is a lever nobody pulls (§478's shape: enumerate the
    # consumers). Same additive, never-fail-the-wave contract as the past-attempt notes above.
    try:
        import neighbor_ref as _nr
        _nhit = _nadd = 0
        for _t in targets:
            _fn = _t.get('name') or _t.get('fn')
            _p = os.path.join(out, "packs", "%s.md" % _fn)
            if not os.path.exists(_p):
                continue
            _r = _nr.neighbors(_t.get('binary'), _fn, 5)
            if _r.get('error') or not _r.get('neighbors'):
                continue
            _nhit += 1
            if _NEIGHBOR_HEADING in open(_p, errors='replace').read():
                continue
            open(_p, 'a').write(_render_neighbors(_r))
            _nadd += 1
        print('worked-example neighbours: %d/%d target(s) have a matched neighbour; appended to %d pack(s)'
              % (_nhit, len(targets), _nadd))
    except Exception as _e:            # fuel is additive — never fail a wave over it
        print('worked-example neighbours SKIPPED: %s: %s' % (type(_e).__name__, _e))

    print('packs: %d written to %s' % (n, out))
    print('cards: %d/%d matched on (binary, fn); %d target(s) have a same-named card in ANOTHER binary '
          '(DROPPED, not substituted — R48); %d card(s) skipped for carrying no binary'
          % (hit, len(targets), byname - hit, wrong_bin))

if __name__ == '__main__':
    main()
