#!/usr/bin/env python3
"""api_agent.py — give an OpenAI-compatible API model the SAME HARNESS a Claude agent gets.

WHY THIS EXISTS (P31 S56, measured):
    `api_draft.py` hands a model one enormous single-shot prompt: the whole cookbook inlined,
    the .s, the Ghidra-C, and "reply with one ```c block". A Claude agent doing the same function
    used SIXTEEN TOOL CALLS -- read the .s, locate and read the 0.99-similarity banked seed in its
    own destination TU, GREP the cookbook for the one §31 tell that mattered, three match_one
    iterations, then an objdump relocation audit it ran unprompted to satisfy law 1c -- and matched.

    Those are different experiments. Inlining 22,009 cookbook lines costs ~568k tokens per call
    (~$1.02) and still leaves the model hunting for the relevant section inside a wall of text;
    the agent greps for what it needs and spends ~60k tokens TOTAL. Comparing a single-shot model
    against a tool-using agent measures the HARNESS, not the model.

    This module closes that gap: the same four capabilities the Claude agent actually used, exposed
    as OpenAI-style function tools, driven in a loop, with match_one as the iteration oracle. Then
    "GLM vs Opus" is a question about models.

WHAT IT DELIBERATELY DOES NOT DO:
    * It does not bank. The draft is the deliverable; the whole-binary byte-gate stays the sole
      arbiter (G3/P9), exactly as for an agent-drafted wave card.
    * It does not widen file access beyond the repo's read-only source/asm/docs surface.
    * match_one MASKS jal/HI16/LO16 relocations -- it verifies instruction SHAPE, not symbol
      IDENTITY (§174 law 1c). A MATCH here is a CANDIDATE. The prompt says so, and the caller must
      still run reloc_identity before crediting one.

USAGE
    API_BASE=https://openrouter.ai/api/v1 API_KEY=sk-or-... MODEL=z-ai/glm-5.3 \
    REASON_CAP=6000 .venv/bin/python tools/api_agent.py \
        --targets .run/bakeoff/rung0.json --out .run/bakeoff/glm-agent --max-turns 24
"""
import argparse, glob, http.client, json, os, re, socket, subprocess, sys, time, urllib.request, urllib.error

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import api_draft as AD          # reuse the validated endpoint/match_one/extract plumbing

REPO = AD.REPO

# --- request telemetry (P31 S58) --------------------------------------------------------------
# Every POST appends one line to .run/api_rate.jsonl: when, which model, which pid, and the event.
# WHY: the overnight ox campaign needs a MEASURED requests-per-minute and a MEASURED 429 rate with
# platform-vs-provider attribution (R40/R41). Before this, the only 429 evidence was a flush=True
# print into a block-buffered log file — so "no 429s" and "the buffer has not filled yet" were the
# same observation. A shared append-only JSONL is readable from outside the process at any moment.
_RATE_PATH = os.path.join(REPO, '.run/api_rate.jsonl')


def _rate_log(event, **kw):
    """Append one telemetry record. Never raises: telemetry must not be able to kill a run."""
    try:
        rec = {'t': time.time(), 'pid': os.getpid(), 'model': AD.MODEL, 'ev': event}
        rec.update(kw)
        with open(_RATE_PATH, 'a') as fh:
            fh.write(json.dumps(rec) + chr(10))
    except Exception:
        pass

# Read-only surface. EXTRA_READABLE widens it for a task that genuinely needs more — a
# TOOLING-DESIGN brief must read config/ and tools/, which a decompilation brief must not.
READABLE = tuple(x for x in (('src/', 'asm/', 'docs/', 'include/', '.run/bakeoff/')
                             + tuple(y for d in os.environ.get('EXTRA_READABLE', '').split(',')
                                     if d.strip()
                                     # BOTH forms: 'config/' matches a directory tree, bare
                                     # 'Makefile' matches a single granted FILE (which never
                                     # matches a trailing-slash prefix).
                                     for y in (f'{d.strip().rstrip("/")}/', d.strip().rstrip("/")))))
MAX_BYTES = 60000               # per read_file / grep response, so one call cannot flood context
NUDGE_MAX = int(os.environ.get('NUDGE_MAX', '6'))   # continuations offered when a turn yields no tool call
REPEAT_MAX = int(os.environ.get('REPEAT_MAX', '4'))  # identical consecutive tool calls before the loop is broken
COOKBOOK_FULL = os.environ.get('COOKBOOK_FULL', '0') != '0'   # inline the whole cookbook (big-context models only)

TOOLS = [
    {'type': 'function', 'function': {
        'name': 'grep',
        'description': ("Search the repository with ripgrep-style regex. THIS IS HOW YOU USE THE "
                        "COOKBOOK: docs/matching-cookbook.md is ~22,000 lines and ~450 numbered "
                        "sections -- never ask to read it whole, grep it for the idiom you are "
                        "actually looking at, then read_file the section you hit. Each cookbook "
                        "hit comes back prefixed with the SECTION it lives in (e.g. '§164 | "
                        "docs/...:13446: ...'): cite that §, never the line number after the "
                        "colon -- '§13446' is not a section and nobody can grep it."),
        'parameters': {'type': 'object', 'required': ['pattern'], 'properties': {
            'pattern': {'type': 'string', 'description': 'regex'},
            'path': {'type': 'string', 'description': 'file or dir, default docs/matching-cookbook.md'},
            'max_hits': {'type': 'integer', 'description': 'default 40'}}}}},
    {'type': 'function', 'function': {
        'name': 'read_file',
        'description': 'Read a repo file, optionally a line range. Use after grep to read a section.',
        'parameters': {'type': 'object', 'required': ['path'], 'properties': {
            'path': {'type': 'string'},
            'start_line': {'type': 'integer'},
            'end_line': {'type': 'integer'}}}}},
    {'type': 'function', 'function': {
        'name': 'match_one',
        'description': ("THE ORACLE. Compile your C and diff it against the target instruction by "
                        "instruction. Returns MATCH, or 'near N' with a per-instruction diff "
                        "(idx | MINE | TARGET). Call this as often as you like -- it is free and "
                        "local. NOTE: it masks jal/HI16/LO16 relocations, so it checks instruction "
                        "SHAPE, not symbol IDENTITY: after it says MATCH, re-read the .s and verify "
                        "every symbol you wrote against its own relocation lines."),
        'parameters': {'type': 'object', 'required': ['code'], 'properties': {
            'code': {'type': 'string', 'description': 'the complete C function, no ``` fences'}}}}},
    {'type': 'function', 'function': {
        'name': 'submit',
        'description': 'Submit your final C. Call this when match_one says MATCH, or when you have exhausted your levers.',
        'parameters': {'type': 'object', 'required': ['code'], 'properties': {
            'code': {'type': 'string'},
            'status': {'type': 'string', 'description': 'MATCH | NEAR | IMMOVABLE'},
            'notes': {'type': 'string', 'description': 'residual class, levers tried, what the cookbook did NOT tell you'}}}}},
]


def _safe(path):
    p = os.path.normpath(path).lstrip('/')
    # Compare with a trailing slash appended so a BARE DIRECTORY matches its own allowed root.
    # Every entry in READABLE ends in '/', so `p = '.run/bakeoff'` failed startswith and the agent
    # was refused access to the very directory that was granted to it — measured P31 S58: a tooling
    # brief could not grep the tool sources staged for it under .run/bakeoff/toolwork, and burned
    # its turns on nudges. A refusal that names the granted path as "outside the readable surface"
    # is a harness bug wearing a permissions message (R40).
    probe = p if p.endswith('/') else p + '/'
    if not (probe.startswith(READABLE) or p.startswith(READABLE)) or '..' in p.split(os.sep):
        return None
    full = os.path.join(REPO, p)
    return full if os.path.exists(full) else None


_SEC_CACHE = {}
_SEC_HEAD = re.compile(r'^#+\s*(\u00a7[0-9][\w.\-]*)')


def _section_index(full):
    """[(first_line, label)] for every `## §N` heading in a cookbook-shaped file (cached by mtime)."""
    key = (full, os.path.getmtime(full))
    if key not in _SEC_CACHE:
        # BOTH LEVELS. The corpus nests: `## §164` holds `#### §16Xy`, and the sub-heading is the
        # precise citation while the top-level one is the stable anchor an agent can always find.
        # Emitting only the parent throws away precision; only the child sends the next agent
        # hunting for a heading it cannot place. Emit `§164 > §16Xy` and both are greppable.
        idx, top = [], ''
        with open(full, errors='replace') as fh:
            for i, line in enumerate(fh, 1):
                m = _SEC_HEAD.match(line)
                if not m:
                    continue
                lab = m.group(1)
                if line.startswith('## ') and not line.startswith('### '):
                    top = lab
                    idx.append((i, lab))
                else:
                    idx.append((i, f'{top} > {lab}' if top and top != lab else lab))
        _SEC_CACHE.clear()
        _SEC_CACHE[key] = idx
    return _SEC_CACHE[key]


def _label_sections(full, out):
    """Prefix each cookbook grep hit with the § section that CONTAINS it.

    AGENTS CITE THE GREP LINE NUMBER AS A SECTION NUMBER (P31 S60, measured). The harvested
    notes carry 13 citations to sections that do not exist — `§2329` (x5) is line 2329, inside
    §28; `§13446/13474` are lines inside §164; `§1914` is a line in §20; the corpus stops at
    §273. A citation nobody can grep is worse than none: the next agent reads "covered by
    §2329", finds nothing, and re-derives a lever we already own — and a distill reviewer
    scores the note as covered by a section that was never written.

    The fix is not a warning, it is the right answer in the output (R33): grep hands back the
    containing §, so the number in front of the agent is the one it should cite.
    """
    idx = _section_index(full)
    if not idx:
        return out
    import bisect
    starts = [i for i, _lab in idx]
    lines = []
    for ln in out.splitlines():
        parts = ln.split(':', 2)
        lab = ''
        if len(parts) == 3 and parts[1].isdigit():
            k = bisect.bisect_right(starts, int(parts[1])) - 1
            if k >= 0:
                lab = idx[k][1] + ' | '
        lines.append(lab + ln)
    return '\n'.join(lines)


def run_tool(name, args, target, outdir, state):
    if name == 'grep':
        path = args.get('path') or 'docs/matching-cookbook.md'
        full = _safe(path)
        if not full:
            return f'REFUSED: {path} is outside the readable surface {READABLE}'
        n = int(args.get('max_hits') or 40)
        r = subprocess.run(['grep', '-rn', '-m', str(n), '-E', args['pattern'], full],
                           capture_output=True, text=True, timeout=120)
        out = r.stdout or '(no hits)'
        if full.endswith('matching-cookbook.md') and r.stdout:
            out = _label_sections(full, out)
        return out[:MAX_BYTES]
    if name == 'read_file':
        full = _safe(args['path'])
        if not full:
            return f"REFUSED or missing: {args['path']}"
        if os.path.isdir(full):
            # A DIRECTORY IS A REASONABLE THING TO ASK FOR (P31 S56). The brief itself said
            # "grep src/ov_SC03_099/ for jtbl_", so the model read_file'd the directory -- and the
            # bare open() raised IsADirectoryError, which was unhandled and killed the run at turn 2
            # of 50. Answer the question instead of dying: list it, so the next turn can pick a file.
            try:
                names = sorted(os.listdir(full))[:200]
            except OSError as e:                            # noqa: BLE001 - report, never crash
                return f'cannot list {args["path"]}: {e}'
            return (f'{args["path"]} is a DIRECTORY with {len(names)} entries — read one of these, '
                    f'or grep the directory instead:\n' + '\n'.join('  ' + n for n in names))
        lines = open(full, errors='replace').read().splitlines()
        a = max(1, int(args.get('start_line') or 1))
        b = min(len(lines), int(args.get('end_line') or min(len(lines), a + 400)))
        body = '\n'.join(f'{i}: {lines[i-1]}' for i in range(a, b + 1))
        return body[:MAX_BYTES] + ('' if len(body) <= MAX_BYTES else '\n... (truncated, narrow the range)')
    if name in ('match_one', 'submit'):
        code = args.get('code') or ''
        cfile = os.path.join(outdir, target['name'] + '.c')
        open(cfile, 'w').write(code if code.endswith('\n') else code + '\n')
        status, close, out = AD.match_one(target['name'], cfile, os.path.dirname(target['asm']))
        score = 0 if status == 'match' else (close if status == 'near' else 10 ** 8)
        if score < state['best'][1]:
            state['best'] = (code, score)
        state['calls'] += 1
        if name == 'submit':
            state['submitted'] = {'status': args.get('status'), 'notes': args.get('notes')}
        tag = 'MATCH' if status == 'match' else (f'near {close}' if status == 'near' else 'compile-fail')
        return f'{tag}\n' + '\n'.join(out.splitlines()[:60])
    return f'unknown tool {name}'


def call(messages, tools):
    payload = {'model': AD.MODEL, 'messages': messages, 'tools': tools,
               'max_tokens': AD.MAXTOK, 'temperature': AD.TEMP}
    if AD.REASON_CAP:
        payload['reasoning'] = {'max_tokens': AD.REASON_CAP}
    elif AD.REASON_EFFORT:
        payload['reasoning'] = {'effort': AD.REASON_EFFORT}
    req = urllib.request.Request(AD.API_BASE + '/chat/completions', data=json.dumps(payload).encode(),
                                 headers={'Content-Type': 'application/json',
                                          'Authorization': 'Bearer ' + (AD.API_KEY or 'none')})
    # 429 IS A PACE SIGNAL, NOT A VERDICT (P31 S56). OpenRouter's free tier allows 20 requests per
    # MINUTE (1000/day at >=$10 lifetime credit). A tool loop bursts one request per turn, so two
    # free arms running concurrently trip the per-minute ceiling within a few turns -- and the first
    # version of this function let that kill the run: dots-3-note died at turn 21 and nemotron at
    # turn 3, both at $0.00 with ZERO oracle calls, and both got written down as model failures.
    # The daily budget was barely touched. Back off and continue; only give up after MAX_429 tries.
    # MAX_429 is env-tunable because a PROVIDER burst is not a verdict and not our ceiling.
    # The upstream shared pool saturates and then resumes; the only wrong response is to give
    # up inside the burst. Default 6 tolerates ~6 min of backoff (20+40+80+120+120); the
    # overnight campaign raises it so a long burst costs latency, never a lost function.
    MAX_429, delay = int(os.environ.get('MAX_429', '6')), 20
    for attempt in range(MAX_429):
        _rate_log('POST')
        try:
            # 1800s meant one hung generation parked an agent for THIRTY MINUTES, and from the
            # outside that is indistinguishable from a stall (measured: an agent 1,690s silent
            # while the 429 backoff chain caps at ~14 min, so it was not backoff). At 2,000 agents
            # a 30-minute park is 30 minutes of a worker doing nothing. Env-tunable; the retry loop
            # above already treats a timeout as transient and tries again.
            with urllib.request.urlopen(req, timeout=int(os.environ.get('HTTP_TIMEOUT', '420'))) as r:
                d = json.loads(r.read())
            # A SOFT 429: HTTP 200 WITH A RATE-LIMIT ERROR IN THE BODY (P31 S59, measured).
            # OpenRouter returns the provider's throttle as a 200 whose body carries no `choices`
            # and an `error` of {"message": "Provider returned error", "code": 429}. That never
            # reached the 429 handler below — which keys on HTTPError — so it fell through to the
            # `no choices` raise and KILLED THE AGENT at turn 1 with no draft, no submit, $0.00.
            # Measured on wave cd: 260 of 260 shards "finished cleanly" and 187 produced NOTHING,
            # 186 of them on this exact error. It reads as a completion collapse (28-60% where the
            # fleet used to do 84-89%) and it is really an unretried rate limit. Same treatment as
            # every other transient: back off and carry on.
            _err = (d or {}).get('error') or {}
            if 'choices' not in (d or {}) and (
                    str(_err.get('code')) == '429' or 'rate' in str(_err.get('message', '')).lower()
                    or 'Provider returned error' in str(_err.get('message', ''))):
                if attempt == MAX_429 - 1:
                    raise RuntimeError('soft 429 exhausted: ' + json.dumps(_err)[:300])
                _rate_log('429', src='SOFT-BODY', wait=delay, attempt=attempt + 1)
                print(f'    (soft 429 in a 200 body — waiting {delay}s, '
                      f'retry {attempt + 1}/{MAX_429 - 1})', flush=True)
                time.sleep(delay)
                delay = min(delay * 2, 120)
                continue
            break
        except (http.client.IncompleteRead, http.client.RemoteDisconnected,
                ConnectionError, TimeoutError, socket.timeout) as e:
            # TRANSIENT TRANSPORT FAILURES ARE NOT VERDICTS EITHER (P31 S56). The 429 path below
            # was added first and everything else stayed fatal, so an IncompleteRead at turn 30 --
            # a truncated HTTP body, nothing to do with the model -- ended deepseek's BEST rung-1
            # run (near 17 of 121, 10 turns still unspent) and it was nearly written down as the
            # model's ceiling. Same treatment as a rate limit: back off and carry on.
            if attempt == MAX_429 - 1:
                raise
            print(f'    (transport {type(e).__name__} — waiting {delay}s, '
                  f'retry {attempt + 1}/{MAX_429 - 1})', flush=True)
            time.sleep(delay)
            delay = min(delay * 2, 120)
            continue
        except urllib.error.HTTPError as e:
            # 5xx IS TRANSIENT TRANSPORT, NOT A VERDICT — retry it exactly like a 429.
            # Only 429 was retried, so a single 502/503/504 raised, the caller logged "API error
            # HTTPError", and the function was ABANDONED mid-solve. Measured P31 S58: one shard
            # lost func_801833E8 to a 502 at turn 11 while sitting at "near 19" — two oracle calls
            # of real progress discarded and written down as a model outcome ("near 19, no submit").
            # A gateway hiccup must cost latency, never a function. (R40: exonerate the instrument.)
            if (e.code != 429 and not (500 <= e.code < 600)) or attempt == MAX_429 - 1:
                raise
            if e.code != 429:
                wait = min(delay, 60)
                _rate_log(str(e.code), wait=wait, attempt=attempt + 1)
                print(f'    (HTTP {e.code} — transient, waiting {wait}s, '
                      f'retry {attempt + 1}/{MAX_429 - 1})', flush=True)
                time.sleep(wait)
                delay = min(delay * 2, 120)
                continue
            # A 429 has TWO possible sources and they need different responses:
            #   * PLATFORM  -- OpenRouter's own free-variant caps (20/min, 1000/day at >=$10
            #     lifetime credit) or DDoS protection. Carries X-RateLimit-{Limit,Remaining,Reset}.
            #   * PROVIDER  -- the upstream serving this model is throttling or at capacity.
            #     Carries error.metadata.provider_code; OpenRouter already retried other providers.
            # Report which one fired instead of guessing: the first version of this comment asserted
            # "per-minute ceiling" without reading either signal (R14 -- a cause you did not measure
            # is not a finding).
            hdrs = getattr(e, 'headers', None) or {}
            lim = hdrs.get('X-RateLimit-Limit')
            rem = hdrs.get('X-RateLimit-Remaining')
            rst = hdrs.get('X-RateLimit-Reset')
            ra = hdrs.get('Retry-After')
            pcode = ''
            try:
                body = json.loads(e.read().decode() or '{}')
                md = (body.get('error') or {}).get('metadata') or {}
                # The field is provider_error_code, NOT provider_code -- the first version guessed
                # the name and so every 429 logged UNATTRIBUTED while the body said exactly what
                # was wrong (measured: glm-5.2:free -> provider_name=Decart,
                # limit_source=upstream_provider_shared_pool). limit_source distinguishes an
                # account/platform cap from a provider's shared free pool, which need different
                # remedies: waiting helps the former, only provider routing or a BYOK key helps
                # the latter.
                pcode = md.get('provider_error_code') or md.get('provider_code') or ''
                if md.get('provider_name'):
                    pcode += f" via {md['provider_name']}"
                if md.get('limit_source'):
                    pcode += f" [{md['limit_source']}]"
            except Exception:                              # noqa: BLE001 - diagnostics only
                pass
            src = f'PROVIDER (provider_code={pcode})' if pcode else (
                  f'PLATFORM (limit={lim} remaining={rem} reset={rst})' if lim else 'UNATTRIBUTED')
            wait = delay
            if ra:                                          # honor the server's own hint (docs)
                try:
                    wait = max(1, min(int(float(ra)), 300))
                except ValueError:
                    pass
            _rate_log('429', src=src, wait=wait, attempt=attempt + 1)
            print(f'    (429 {src} — waiting {wait}s, retry {attempt + 1}/{MAX_429 - 1})', flush=True)
            time.sleep(wait)
            delay = min(delay * 2, 120)
    AD._COST[0] += (d.get('usage') or {}).get('cost', 0) or 0
    # A 200 RESPONSE CAN STILL CARRY AN ERROR INSTEAD OF choices (P31 S56). Reading d['choices']
    # blind turned two distinct causes into the same bare `KeyError 'choices'`: nemotron-ultra's
    # provider 502 on reasoning.max_tokens+tools, and a later context-exhaustion failure on the
    # 566k-token cookbook preload. Surface what the body actually said, so the next one is
    # diagnosable from the log instead of needing a reproduction.
    if 'choices' not in d:
        raise RuntimeError('no choices in response: ' + json.dumps(d.get('error') or d)[:400])
    return d['choices'][0]['message'], d['choices'][0].get('finish_reason')


SYS = """You are byte-matching ONE PlayStation function (MIPS, gcc-2.7.2 -O2, PsyQ SDK) in a
decompilation project. Your output must be C that compiles to instructions IDENTICAL to the target.

YOU HAVE TOOLS. Use them the way a careful engineer would:
  * read_file the target .s IN FULL first. The assembly is the ONLY ground truth.
  * START AT docs/cookbook-index.md -- it is symptom-keyed and it is the entry point; grep THAT
    for what you see in the diff, then read the section it names in docs/matching-cookbook.md
    (760+ numbered sections of hard-won gcc-2.7.2 behaviour, far too large to read whole). Search
    for the pass name, the instruction pattern, the C construct. A drafter who does not grep
    re-derives laws the project has held for months.
  * If you cite or read a number like `12479` and grepping `§12479` finds nothing, it is a cookbook
    LINE number, not a section id. Resolve it:
    `.venv/bin/python tools/cookbook_index.py --resolve 12479`.
  * read_file the destination TU: if it already declares a symbol, copy that declaration EXACTLY
    (same type, arity, volatile, struct name). Only if absent, type by access width
    (lb/lbu->s8/u8, lh/lhu->s16/u16, lw->s32, sw->s32).
  * match_one as often as you like. It is free, local, and gives you a per-instruction diff.
  * submit when you are done.

THE LAWS THAT MATTER MOST:
1. SPELL EVERY SYMBOL FROM YOUR TARGET. Every D_########, func_########, jtbl_######## you write
   must appear in the TARGET .s's own relocation lines. Never carry a seed's or a neighbour's
   per-location symbols. Curated/PsyQ names too: if the .s says `jal RotMatrixY`, call it that.
1c. match_one MASKS jal/HI16/LO16 relocations -- it verifies instruction SHAPE, NOT SYMBOL IDENTITY.
   A draft that calls the WRONG function reports a clean MATCH. After MATCH, walk the .s once more
   and check every symbol you wrote against its own relocation lines.
2. A seed or twin gives you the SHAPE, never the symbols, and never the literals. Re-read both.
3. IF YOUR CARD NAMES A LEVER, grep the cookbook for the § its crib cites BEFORE you draft. And a
   plateaued diff whose class says [permuter] is DONE: submit NEAR with the class rather than
   spending ten more compiles on a 2-instruction register swap the search cannot reach from C.
4. AN ARGUMENT YOU INVENTED CHANGES SCHEDULING (§263). If your only residual is one stolen delay
   slot holding a `move $aN,$sN`, you gave a no-argument callee a parameter — check its arity
   against decl_prior before touching a fence or the permuter, which cannot change call arity.

Work until match_one says MATCH, or until you have genuinely exhausted your levers -- then submit
with an honest status and say what the cookbook did NOT already tell you."""


# THE LEVER CRIB (P31 S59). The card used to state its lever as a bare label and nothing else, and
# the label is a word this project's 750-section cookbook DOES NOT CONTAIN: measured over the tells
# waves, 108 failure transcripts grepped `extend-tell` and 28 grepped `swaprepeat` for zero hits
# while the knowledge sat at §172a/§172b/§264 under different words. A label the drafter cannot look
# up is not fuel; it is a dead end that costs a grep and buys nothing. Each entry below states what
# the tell MEANS, names the § to grep, and gives the C spellings — all byte-proven (§264).
LEVER_CRIB = {
    'extend-tell': (
        "extend-tell = §172b-1 + §264 (grep 'sll/sra-16 pair tell'). The target promotes\n"
        "REGISTER-held s16 values. Four placements, four C spellings:\n"
        "  * naked sll/sra pair  = a MULTI-DEF s16/u16 variable merged across branches — write it\n"
        "    on BOTH paths mirroring the mem slot (`x[i] = w = ...`), then compare (s16)w;\n"
        "  * plain lh            = one promoted use — read the s16 memory DIRECTLY, no temp;\n"
        "  * sll before a jal, sra IN its delay slot = the (s16) cast written INLINE in the call\n"
        "    argument (a temp kills the delay-slot fill);\n"
        "  * lhu + separate sll/sra = the value is ALSO used as u16 — keep the u16 variable.\n"
        "Sign test (s16)t < 0 emits sll+bgez only (the sra is elided).\n"
        "NO register pins first — §17 is the last resort; pins block the parm-copy and arg-copy\n"
        "shapes. If a parameter is copied to $aN, type the PARAMETER and use it everywhere rather\n"
        "than inventing `self = arg0`.\n"),
    'swaprepeat-tell': (
        "swaprepeat-tell = §172a + §172b-2 (grep 'swapped-arm select tell'). Textual REPEATS are\n"
        "load-bearing: a repeated compare/select re-emits its own slt+branch, so write the repeat\n"
        "TEXTUALLY — nested macros repeat their operands, inline functions collapse them.\n"
        "A range check is plain `if (-lim < x && x < lim)`; the second slt rides the first beqz's\n"
        "delay slot for free.\n"),
    's16-div-tell': (
        "s16-div-tell = §172b-4 (grep 'Division-by-constant sign-correction'). For s16/K magic\n"
        "multiplies keep the promotion as an EXPRESSION, never a temp, so the sign-sra can reuse\n"
        "the <<16 intermediate; the magic pairs for K are in §167-25 and the odd-part table.\n"),
}


def _fuel(t, card):
    """THE CARD FUEL, in the wave's own proven wording (P31 S56).

    Until now this module handed a model only the .s path and the TU path -- i.e. it drafted BLIND to
    everything the wave harness spent three sessions learning to put on a card. Wave Z's first result
    was "the card is the cheapest place in the pipeline to put a fact": `seed_ref` banked 51/51 on
    wave U's draw where `exemplar` banked 0/73, `tu_ref` reaches 48-64 cards a wave, and `decl_prior`
    answers the arity question §195-A proved the asm cannot answer. A cheap model without that fuel
    is not being compared to a wave agent -- it is being compared to a wave agent's worst day.
    """
    if not card:
        return ''
    out = []
    sr = card.get('seed_ref')
    if sr:
        out.append(f"\n⭐ YOUR CARD'S BANKED TWIN: {sr['binary']}:{sr['fn']} ({sr['nins']} ins"
                   + (f", skeleton similarity {card['seed_sim']}" if card.get('seed_sim') else '') + ").")
        out.append(f"   This is MATCHED C sitting in the tree RIGHT NOW. Find it with")
        out.append(f"       grep(pattern='{sr['fn']}', path='src/{sr['binary']}')")
        out.append( "   then read_file the body in full. At similarity >=0.9 it is frequently a")
        out.append( "   line-for-line relative of your target: same guards, same block copies, same")
        out.append( "   tail. It is the highest-value 60 seconds in this task (§193-A).")
    else:
        out.append("\nThis card has NO banked twin — derive the structure from the .s.")
    tr = card.get('tu_ref') or []
    if tr:
        out.append("\n⭐ AND READ THE NEIGHBOUR IN YOUR OWN TU — the highest-yield source measured")
        out.append("(§194-E: 62% of targets have one). Already-banked C in the very file your draft")
        out.append("lands in, sharing symbols with YOUR target's relocations:")
        for r in tr:
            out.append(f"     {r['fn']}  ({r.get('shared')} shared: {', '.join(r.get('symbols') or [])})")
        out.append("   It shows this TU's house style: how it declares these exact globals and")
        out.append("   callees, which struct spellings it uses. Adopting that spelling IS law 2,")
        out.append("   and law 2 is the single biggest cause of bank failures.")
    dp = card.get('decl_prior') or []
    if dp:
        out.append("\n⭐ THE DECLARATIONS ARE ALREADY DECIDED — do not guess a callee's arity or return")
        out.append("type, and do not spend a compile on a two-arity A/B (§195-A: the asm has NO tell).")
        out.append("Signatures print as (return, (params...)). '?' means an UNSPECIFIED parameter list,")
        out.append("which is compatible with any prototype in C89 and is NEVER a conflict — do not")
        out.append("'fix' it. A row with a `tu` field is AUTHORITATIVE for you: copy it verbatim.")
        for r in dp[:24]:
            bits = [f"sym={r['sym']}"]
            for k in ('tu', 'def', 'fleet'):
                if r.get(k):
                    bits.append(f"{k}={r[k]}")
            if r.get('n'):
                bits.append(f"n={r['n']}")
            if r.get('rivals'):
                bits.append(f"rivals={'; '.join(r['rivals'][:2])}")
            if r.get('fleet_note'):
                bits.append("⚠ FUNCTION POINTER — this rendering is NOT valid C; write the spelling "
                            "yourself from the .s, do not paste it")
            if r.get('def_absent'):
                bits.append(f"(no def: {r['def_absent']})")
            out.append('     ' + '  '.join(bits))
    sb = card.get('sibs') or []
    if sb:
        worth = t['nins'] + sum(x['n'] for x in sb)
        out.append(f"\n⭐ THIS CARD IS WORTH {worth} INSTRUCTIONS, NOT {t['nins']}: {len(sb)} other still-open")
        out.append(f"function(s) share your skeleton ({', '.join(x['b'] + ':' + x['f'] for x in sb)}) and are")
        out.append( "remapped from your draft MECHANICALLY once it banks. So law 1 matters twice as much:")
        out.append( "spell YOUR target's symbols exactly — no seed leftovers.")
        out.append( "⚠ Do NOT hunt in `sibs` for a body to read: they are drawn from the OPEN set by")
        out.append( "construction, so they are stubs 100% of the time. They tell you what your work is")
        out.append( "WORTH, not where an answer is.")
    # 6.3 TELL COUNTS (P31 S60). Counts derived from the TARGET's own bytes by atlas_features,
    # joined onto the card by build_wave_atlas. They are a CHECKLIST, not a hint: the target
    # provably contains this many sites, so a draft that produces fewer has missed some.
    _t = card.get('tells') or {}
    _bits = []
    if _t.get('extpair'):
        _bits.append(f"{_t['extpair']} sign-extend pair site(s) (sll/sra, §172b EXTPAIR)")
    if _t.get('dupselect'):
        _bits.append(f"{_t['dupselect']} repeated two-arm select(s) (§172b SELECT)")
    if _t.get('magic_div'):
        _bits.append(f"{_t['magic_div']} magic-division site(s)")
    if _t.get('sign_lh'):
        _bits.append("signed halfword load(s) (lh, not lhu)")
    if _t.get('sign_lb'):
        _bits.append("signed byte load(s) (lb, not lbu)")
    if _bits:
        out.append("\nTELLS COUNTED IN THE TARGET (from its bytes, not a guess) — expect: "
                   + "; ".join(_bits) + ".")
        out.append("If your draft emits fewer of these than the count says, you have missed "
                   "sites — find them before spending a turn on anything else.")
    if card.get('lever'):
        out.append(f"\nThe atlas labels this card's lever: {card['lever']}.")
        crib = LEVER_CRIB.get(card['lever'])
        if crib:
            out.append(crib)
            out.append("Universal fold-blockers when a shape refuses: name the inner term of a "
                       "nested +/- as a temp (keeps association); hold a non-slti constant bound "
                       "in a LOCAL assigned right before its `if` (defeats the 0xFFFF "
                       "canonicalization and lets the arm's store reuse its register); hold a "
                       "global base in a pointer local when it must live in an $sN across calls.")
    return '\n'.join(out)


def prior_transcript(t, budget=240000):
    """The most recent prior CONVERSATION for this function, trimmed to a character budget.

    Replayed as real assistant/tool turns rather than summarized: the tool results carry the .s
    excerpts, cookbook sections and match_one diffs the last attempt paid to fetch, and a summary
    of "it read the cookbook" is worth far less than the section it actually read. The opening
    user turn is dropped (the new run builds its own, with fresher cards) and the oldest middle
    turns are trimmed first, keeping the most recent exchanges where the reasoning converged.
    """
    newest, path = None, None
    for p in sorted(glob.glob(f".run/wave_*/shard*/{t['name']}.messages.json"),
                    key=lambda x: -os.path.getmtime(x)):
        try:
            newest = json.load(open(p)); path = p; break
        except (OSError, json.JSONDecodeError):
            continue
    if not newest:
        return None, None, None
    msgs = [m for m in newest.get('messages', []) if m.get('role') != 'system'][1:]
    while msgs and sum(len(json.dumps(m)) for m in msgs) > budget:
        del msgs[0]
        while msgs and msgs[0].get('role') == 'tool':      # never orphan a tool result
            del msgs[0]
    return msgs, path, newest


def gate_feedback(t):
    """WHY the last attempt did not bank, from the gate's own ledgers — added S61 once the verdicts
    became class-accurate (before that the dominant reasons were misattributed harness faults, and
    feeding them to a retry would have taught it wrong). Two sources, both keyed by (binary, fn) --
    never bare name (overlays share names):
      * the latest backlog row -> verdict class + closeness + where_stuck;
      * the latest reloc_rejects row with shape MATCH -> the EXACT symbol mismatches (mechanically
        fixable: the instruction stream already matched; only names were wrong).
    Harness-fault classes (BASELINE-RED / TU-BROKEN) are stated as NOT the draft's fault so the
    retry resubmits with minimal change instead of mangling a possibly-correct body."""
    b, fn = t.get('binary'), t['name']
    out = []
    try:
        last = None
        for src in ('.run/backlog.jsonl', '.run/auto/bulk/%s.backlog.jsonl' % b):
            if not os.path.exists(src):
                continue
            for line in open(src, errors='replace'):
                try:
                    r = json.loads(line)
                except Exception:
                    continue
                if r.get('name') == fn and r.get('binary') == b:
                    last = r
        if last:
            ws = (last.get('where_stuck') or '')[:260]
            cl = last.get('closeness')
            if 'BASELINE-RED' in ws or 'TU-BROKEN' in ws:
                out.append("LAST GATE VERDICT: the rejection was the HARNESS's fault (%s) -- the binary or its "
                           "TU was broken when your predecessor was judged. The draft may be fully correct: "
                           "verify against the .s and resubmit with MINIMAL changes." % ws)
            else:
                out.append('LAST GATE VERDICT: %s%s' % (('closeness %s (instructions still wrong) -- ' % cl)
                                                        if cl is not None else '', ws))
    except Exception:
        pass
    try:
        best = None
        if os.path.exists('.run/reloc_rejects.jsonl'):
            for line in open('.run/reloc_rejects.jsonl', errors='replace'):
                try:
                    r = json.loads(line)
                except Exception:
                    continue
                if r.get('fn') == fn and r.get('binary') == b and r.get('shape') == 'MATCH':
                    best = r
        if best and best.get('mismatches'):
            ms = best['mismatches'][:6]
            out.append('SYMBOL MISMATCHES from the last shape-MATCH attempt (your instruction stream already '
                       'matched; ONLY these names were wrong -- fix the names, change nothing else):\n' +
                       '\n'.join('  i=%s %s: draft named %s but the target references %s%s'
                                  % (m.get('i'), m.get('kind'), m.get('draft_symbol'), m.get('target_addr'),
                                     (' = ' + m['target_name']) if m.get('target_name') else '')
                                  for m in ms))
    except Exception:
        pass
    return ('\n\n'.join(out)) if out else None


def prior_draft(t):
    """The best body a PREVIOUS attempt on this function reached, if one is on disk.

    A retry currently starts cold and re-derives everything the last attempt already worked out.
    That is pure waste at any time and acute now: --retry-unbanked returned 1,763 drawn-but-unbanked
    cards to the pool (P31 S58), every one of which has a saved draft. It is also the only recovery
    path for work lost to transport — one shard reached "near 19" on func_801833E8 and a 502 ended
    the run; the conversation is gone (nothing persists it) but the body survived.

    Deliberately NOT presented as correct: a saved draft is by definition one the byte-gate has not
    accepted, so it is offered as a starting point to improve or discard, never as a seed to trust.
    """
    best, where = None, None
    # LAW 1c FOR WARM STARTS (P31 S62 T4): drafts are stored by function NAME, and the same name at
    # the same address in a DIFFERENT overlay is usually a different function. 22 of 60 probe agents
    # reported "the warm-start body was a different function entirely" — a strong model discards
    # it, a weak one follows it, so the warm start was confounding the arms. Accept a candidate
    # only when the symbols it references overlap the target .s's own relocations.
    try:
        tgt = set(re.findall(r'\b(?:func_|D_|jtbl_|a[A-Z0-9]+_)[0-9A-Fa-f]{8}\b', open(os.path.join(REPO, t['asm'])).read()))
    except Exception:
        tgt = None
    skipped = 0
    for pat in (f".run/wave_*/shard*/{t['name']}.c", f".run/*/{t['name']}.c"):
        for p in sorted(glob.glob(pat), key=lambda x: -os.path.getmtime(x)):
            try:
                body = open(p).read()
            except OSError:
                continue
            if not body.strip():
                continue
            if tgt is not None:
                syms = set(re.findall(r'\b(?:func_|D_|jtbl_|a[A-Z0-9]+_)[0-9A-Fa-f]{8}\b', body)) - {t['name']}
                # TIGHTENED (P31 S70). The old test was `len(syms) >= 2 and overlap*2 < len(syms)`
                # and had TWO holes, both measured live in the S70 wave:
                #   * `len(syms) >= 2` exempted every body referencing 0 or 1 symbols — exactly the
                #     small-function case. func_80182438 (21 ins, ONE symbol) sailed through carrying
                #     ov_SC02_028's body for the same address, and its agent reported that as the
                #     reason its PRIOR attempt failed.
                #   * needing a strict majority foreign meant a body sharing half its symbols passed.
                # A correct draft can only reference what the target's .s actually relocates, so ANY
                # foreign symbol disqualifies. Negative-controlled over all 50 S70 targets: admits 42,
                # rejects 4 — and the 4 are precisely the bodies four independent agents reported as
                # "a different function entirely" (func_80182438, func_800D0664, func_801831D0,
                # func_80185F4C). No collateral rejections. R48: never key by bare function name.
                if syms - tgt:
                    skipped += 1
                    continue          # another overlay's same-named function — not this body
            best, where = body, p
            break
        if best:
            break
    if skipped:
        print(f"  {t['name']}: skipped {skipped} same-named draft(s) whose symbols do not match this .s (law 1c)", flush=True)
    return best, where


def user_msg(t, card=None):
    base = f"""TARGET: {t['name']} · {t['nins']} instructions · binary {t.get('binary','?')}
  target asm     : {t['asm']}
  destination TU : {t.get('tu','(unknown)')}
{_fuel(t, card)}

Start by reading the asm in full. Then work. Call submit when done."""
    if not COOKBOOK_FULL:
        return base
    # PRELOAD THE WHOLE COOKBOOK (Drew, P31 S56). Only worth doing on a model whose context can
    # hold it -- ~568k tokens of the ~22,000-line knowledge base -- e.g. nemotron-3-ultra's 1M
    # window. The question this asks is a real one: the Claude agent's edge came from GREPPING the
    # index selectively (16 tool calls, ~60k tokens total). Does having everything resident from
    # turn 0 beat searching on demand, or does it bury the two sections that matter in 22,000 lines
    # of everything else? Costs ~568k input tokens on EVERY turn, so use it only where input is free.
    book = open(os.path.join(REPO, 'docs', 'matching-cookbook.md'), errors='replace').read()
    return (base + "\n\nThe ENTIRE matching cookbook follows — every idiom this project has "
            "learned. You still have the grep tool, but you should not need it for the cookbook: "
            "read what is relevant below. The .s is still the only ground truth.\n\n"
            "===== docs/matching-cookbook.md =====\n" + book)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--targets', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--max-turns', type=int, default=24)
    ap.add_argument('--brief', help='path to a task brief prepended to the first user message. '
                    'Lets api_agent run ANALYSIS tasks (e.g. an autopsy: "classify why this does '
                    'not remap") rather than only "byte-match this function", with the same tools '
                    'and the same oracle available as evidence.')
    ap.add_argument('--max-cost', type=float, default=0.0,
                    help='TOTAL USD ceiling for this run (OpenRouter usage.cost, summed across every '
                         'call). 0 = no ceiling. Borrowed from OpenRouter Agent SDK\'s maxCost stop '
                         'condition, which is a better bound than a turn cap: a turn is not a unit '
                         'of money, and the runs that hurt are the ones that grind many cheap turns.')
    ap.add_argument('--max-cost-per-fn', type=float, default=0.0,
                    help='USD ceiling for ONE function before moving on. 0 = no ceiling. This is the '
                         'per-item bound the batch economics actually need: GLM burned $1.10 on a '
                         'single rung-3 failure -- 5x its successful match -- and a turn cap could '
                         'not have stopped it.')
    ap.add_argument('--cards', help='wave card file (e.g. .run/wave_aa_cards.json). Injects the '
                    'card fuel a wave agent gets: seed_ref / tu_ref / decl_prior / sibs / lever. '
                    'Without it the model drafts BLIND to everything the wave harness knows.')
    a = ap.parse_args()
    targets = json.load(open(a.targets))
    cards = {}
    if a.cards:
        raw = json.load(open(a.cards))
        _rows = raw if isinstance(raw, list) else raw.get('cards', [])
        # A CARD FILE OF THE WRONG SHAPE MUST REFUSE, NOT CRASH (R43, P31 S60). This was
        # `{c['fn']: c for c in _rows}` and died with KeyError: 'fn' when idiom_serial passed
        # .run/aprop_cards.json — a FAMILY-card file (family/members/seed, no per-function key).
        # The traceback killed the agent at turn 0, so every serial-lane target logged "no-draft"
        # and the lane read as a model failure. The R32 warning two lines below already existed to
        # catch exactly this ("ZERO matched — wrong card file?") and was unreachable behind the
        # crash. Accept 'fn' or 'name', skip rows with neither, and let that warning do its job.
        cards = {}
        _skipped = 0
        for c in _rows:
            k = c.get('fn') or c.get('name') if isinstance(c, dict) else None
            if k:
                cards[k] = c
            else:
                _skipped += 1
        if _skipped:
            print(f'card fuel: {_skipped} row(s) in {a.cards} carry no fn/name key — '
                  f'is this a per-function card file?')
        hit = sum(1 for t in targets if t['name'] in cards)
        # R32: say what fraction of the batch actually got fuel. A card file that silently matches
        # nothing would look exactly like a model that ignored it.
        print(f'card fuel: {hit}/{len(targets)} targets matched in {a.cards}'
              + ('' if hit else '  ⚠ ZERO matched — wrong card file?'))
    outdir = os.path.join(REPO, a.out)
    os.makedirs(outdir, exist_ok=True)
    print(f'api_agent: {AD.MODEL} @ {AD.API_BASE} -> {len(targets)} target(s), max {a.max_turns} turns')

    stop_all = False
    for t in targets:
        if stop_all:
            print(f'  {t["name"]}: SKIPPED — run cost ceiling already reached')
            continue
        state = {'best': (None, 10 ** 9), 'calls': 0, 'submitted': None, 'nudges': 0,
                 'recent': []}
        um = user_msg(t, cards.get(t['name']))
        pd, pdwhere = prior_draft(t)
        if pd:
            um += ("\n\nA PREVIOUS ATTEMPT on this exact function left this body behind "
                   f"({pdwhere}). The whole-binary byte-gate did NOT accept it, so it is wrong "
                   "somewhere — but it is usually wrong in ONE place, and re-deriving the other "
                   "90% from scratch wastes the turns you need for the real difference. Read it "
                   "against the .s, keep what matches, and fix what does not. Discard it entirely "
                   "if it is a different function's body.\n\n```c\n" + pd.strip() + "\n```\n")
            print(f'  {t["name"]}: warm start from {pdwhere}', flush=True)
        gf = gate_feedback(t)
        if gf:
            um += '\n\n' + gf + '\n'
            print(f'  {t["name"]}: gate feedback attached', flush=True)
        if a.brief:
            um = open(a.brief).read().rstrip() + '\n\n' + um
        messages = [{'role': 'system', 'content': SYS}, {'role': 'user', 'content': um}]
        # RESUME rather than restart: splice the previous attempt's turns in after the new opening
        # message, then tell the model plainly what it is looking at. Its own prior tool results —
        # the .s excerpts, the cookbook sections, the match_one diffs — come back with it, so the
        # retry begins where the last one stopped instead of re-buying the same context.
        prev, prevpath, prevmeta = prior_transcript(t)
        if prev:
            messages += prev
            messages.append({'role': 'user', 'content':
                f"RESUMING. Everything above is YOUR OWN previous attempt on {t['name']}, replayed "
                f"from {os.path.basename(prevpath)}. It ended at "
                f"{prevmeta.get('verdict','an unknown verdict')} after "
                f"{prevmeta.get('oracle_calls','?')} oracle call(s) — so it did NOT bank, and "
                "somewhere in there is a wrong assumption. Do not repeat the searches and reads you "
                "already did; their results are above. Start from the best body you reached, decide "
                "what is still unexplained in the .s, and go at THAT. If the previous line of attack "
                "was a dead end, say so and take a different one."})
            print(f'  {t["name"]}: RESUMING from {prevpath} '
                  f'({len(prev)} prior turns, ended {prevmeta.get("verdict")})', flush=True)
        spent_at_start = AD._COST[0]
        for turn in range(a.max_turns):
            spent_fn = AD._COST[0] - spent_at_start
            if a.max_cost_per_fn and spent_fn >= a.max_cost_per_fn:
                print(f'  {t["name"]} turn {turn}: PER-FN COST CEILING '
                      f'${spent_fn:.4f} >= ${a.max_cost_per_fn:.4f} — moving on', flush=True)
                break
            if a.max_cost and AD._COST[0] >= a.max_cost:
                print(f'  {t["name"]} turn {turn}: RUN COST CEILING '
                      f'${AD._COST[0]:.4f} >= ${a.max_cost:.4f} — stopping the whole run', flush=True)
                stop_all = True
                break
            try:
                msg, finish = call(messages, TOOLS)
            except Exception as e:                       # noqa: BLE001 - report, never crash the run
                print(f'  {t["name"]} turn {turn}: API error {type(e).__name__} {str(e)[:120]}')
                break
            tcs = msg.get('tool_calls') or []
            messages.append({k: v for k, v in msg.items()
                             if k in ('role', 'content', 'tool_calls')} or {'role': 'assistant', 'content': ''})
            if not tcs:
                # A TURN WITH NO TOOL CALL IS NOT NECESSARILY THE END (P31 S56). The first version
                # broke here, and that silently ended two runs for opposite reasons:
                #   * deepseek-v4-flash rung 1 came back finish='length' -- TRUNCATED at the output
                #     cap mid-reply -- on the turn AFTER it had just read the two cookbook sections
                #     that bear on its residual (§164-20, §205), with 27 of 40 turns unspent and a
                #     score still improving (74 -> 73 -> 70). Reported as "gave up". It did not.
                #   * kimi-k3 came back finish='stop' with a plateaued diff -- a real surrender.
                # Both deserve a nudge with their own best draft back in hand; only a model that
                # keeps declining after NUDGE_MAX of them has actually finished.
                code = AD.extract_code(msg.get('content') or '')
                if code.strip():
                    print(f'  {t["name"]} turn {turn}: replied with code and no tool call — scoring it')
                    print('   ', run_tool('submit', {'code': code, 'status': 'UNKNOWN'}, t, outdir, state).splitlines()[0])
                    break
                state['nudges'] += 1
                if state['nudges'] > NUDGE_MAX:
                    print(f'  {t["name"]} turn {turn}: no tool call (finish={finish}); '
                          f'{NUDGE_MAX} nudges spent — stopping')
                    break
                best_code, best_score = state['best']
                where = ('MATCH' if best_score == 0 else
                         f'near {best_score}' if best_score < 10 ** 7 else 'no compiling draft yet')
                why = ('Your last reply was CUT OFF at the output limit before you finished — that is '
                       'a budget accident, not a dead end. Reply again, SHORTER: think less, call one '
                       'tool.' if finish == 'length' else
                       'You stopped without calling a tool. You are not done unless match_one says '
                       'MATCH.')
                back = (f'{why}\n\nYour best draft so far scores {where}. It is below — continue '
                        f'from it. You have {NUDGE_MAX - state["nudges"] + 1} continuation(s) left and '
                        f'{a.max_turns - turn - 1} turn(s). Call match_one with an improved version, '
                        f'grep the cookbook for the residual you are stuck on, or call submit if you '
                        f'genuinely have no lever left.\n\n```c\n{(best_code or "(none)")}\n```')
                print(f'  {t["name"]} turn {turn}: no tool call (finish={finish}) — '
                      f'NUDGE {state["nudges"]}/{NUDGE_MAX}, best={where}')
                messages.append({'role': 'user', 'content': back})
                continue
            # REPEATED-CALL GUARD (P31 S56). A model can loop forever on VALID tool calls and no
            # existing bound catches it: NUDGE_MAX only fires on a turn with NO tool call, and
            # --max-cost is meaningless for a $0 model. Measured: stealth/ox-alpha spent 56 turns on
            # func_8018568C -- 46 greps, 10 reads, ZERO compiles -- repeating the same cookbook grep
            # six turns running, and produced no draft at all. Unattended, that burns a whole run.
            sig = tuple(sorted((tc['function']['name'], tc['function'].get('arguments') or '')
                               for tc in tcs))
            state['recent'].append(sig)
            del state['recent'][:-REPEAT_MAX]
            if len(state['recent']) == REPEAT_MAX and len(set(state['recent'])) == 1:
                nm = tcs[0]['function']['name']
                print(f'  {t["name"]} turn {turn}: REPEATED the identical {nm} call '
                      f'{REPEAT_MAX}x — breaking the loop', flush=True)
                messages.append({'role': 'user', 'content':
                    f'STOP. You have made the identical {nm} call {REPEAT_MAX} times in a row and '
                    f'it is not advancing you. Do something DIFFERENT now: call match_one with your '
                    f'best attempt at the C (even an incomplete one — the diff is information), or '
                    f'read the target .s again, or call submit with an honest NEAR/IMMOVABLE status '
                    f'and say what blocked you. Do not repeat that search.'})
                state['recent'].clear()
                continue
            for tc in tcs:
                fn = tc['function']['name']
                try:
                    args = json.loads(tc['function'].get('arguments') or '{}')
                except json.JSONDecodeError:
                    args = {}
                try:
                    res = run_tool(fn, args, t, outdir, state)
                except Exception as e:                      # noqa: BLE001 - a tool fault is DATA
                    # NO TOOL ERROR IS FATAL. Four runs died tonight to unhandled conditions the
                    # model could have worked around if it had been told: a directory read, a 502
                    # with no `choices`, a truncated HTTP body, a turn with no tool call. Hand the
                    # exception back as a tool result and let the model choose again.
                    res = (f'TOOL ERROR {type(e).__name__}: {str(e)[:300]}\n'
                           f'That call failed. Fix the arguments and try again, or use a different '
                           f'tool — this is not fatal and you have turns remaining.')
                    print(f'  {t["name"]} turn {turn}: {fn} raised {type(e).__name__} '
                          f'— returned to the model as feedback', flush=True)
                first = res.splitlines()[0] if res else ''
                print(f'  {t["name"]} turn {turn}: {fn}({str(args)[:70]}) -> {first[:90]}')
                messages.append({'role': 'tool', 'tool_call_id': tc.get('id'), 'name': fn, 'content': res})
            if state['submitted']:
                break
        best, score = state['best']
        if best is not None:
            open(os.path.join(outdir, t['name'] + '.c'), 'w').write(best if best.endswith('\n') else best + '\n')
        # PERSIST THE TRANSCRIPT. Until now only the final body survived a run, so a retry restarted
        # cold and re-derived every read, every grep and every rejected hypothesis. The body says
        # WHAT the last attempt concluded; the transcript says WHY, and which approaches were already
        # ruled out. Acute with --retry-unbanked returning 1,763 drawn-but-unbanked cards to the pool.
        try:
            json.dump({'fn': t['name'], 'binary': t.get('binary'), 'score': score,
                       'verdict': 'MATCH' if score == 0 else
                                  (f'near {score}' if score < 10 ** 7 else 'no compiling draft'),
                       'oracle_calls': state['calls'], 'model': AD.MODEL, 'messages': messages},
                      open(os.path.join(outdir, t['name'] + '.messages.json'), 'w'))
        except Exception:
            pass
        verdict = 'MATCH' if score == 0 else (f'near {score}' if score < 10 ** 7 else 'no compiling draft')
        print(f'  {t["name"]}: {verdict} after {state["calls"]} oracle call(s), '
              f'${AD._COST[0] - spent_at_start:.4f}, {state["submitted"] or "no submit"}')
    print(f'api_agent done. cost ${AD._COST[0]:.4f}')


if __name__ == '__main__':
    main()
