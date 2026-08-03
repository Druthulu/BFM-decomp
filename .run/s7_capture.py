#!/usr/bin/env python3
"""S7 blocker capture — the any-overlay, any-draft-dir generalization of .run/uc_capture.py.

WHY THIS EXISTS (the S29 law, re-confirmed every wave since): agents CANNOT run the whole-binary
gate, so a `match_one`-MATCH draft that dies on `conflicting types for D_800A5E88` looks to them
like a codegen wall. Hand a reconcile agent the compiler's OWN error line and the lane runs 12/12;
hand it "the gate refused" and it re-derives the function from scratch and usually still fails.

Per target: splice the draft over its INCLUDE_ASM (TU derived from corpus.stubs, never asserted),
build THAT overlay, keep the error lines, REVERT the TU unconditionally.

  .venv/bin/python .run/s7_capture.py .run/s7_gate4a_derived.json      # the failed set
"""
import sys, os, re, json, subprocess
sys.path.insert(0, 'tools')
import cdecl, corpus

src = sys.argv[1] if len(sys.argv) > 1 else '.run/s7_gate4a_derived.json'
targets = json.load(open(src))['failed']

out = {}
for ov, fn in targets:
    draft = f'.run/s8/{ov}/{fn}.c'
    if not os.path.exists(draft):
        out[fn] = {'ov': ov, 'blocker': '(no draft on disk)'}
        print(f"{fn:<16} {ov:<14} (no draft)", flush=True)
        continue
    addr = int(fn.split('_')[1], 16)
    st = corpus.stubs(ov)
    if addr not in st:
        out[fn] = {'ov': ov, 'blocker': '(not a live stub — banked since?)'}
        print(f"{fn:<16} {ov:<14} (not a live stub)", flush=True)
        continue
    tu = st[addr].path
    orig = open(tu).read()
    body = cdecl.strip_provided_typedefs(open(draft).read(), cdecl.typedef_names(tu))
    m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{fn}\);', orig)
    if not m:
        out[fn] = {'ov': ov, 'tu': tu, 'blocker': '(INCLUDE_ASM line not found in the derived TU)'}
        print(f"{fn:<16} {ov:<14} (no INCLUDE_ASM in {tu})", flush=True)
        continue
    try:
        open(tu, 'w').write(orig[:m.start()] + body + orig[m.end():])
        b = subprocess.run(f"make --no-print-directory build BINARY={ov}",
                           shell=True, capture_output=True, text=True)
        txt = b.stdout + b.stderr
        # DERIVE the class from the INVARIANT (did the compile produce an object?), do NOT
        # pattern-match error prose. Matching phrasings cost me twice: an exit-status branch that
        # was unreachable, then a regex that missed `too many arguments to function` and filed a
        # plain arity conflict as UNKNOWN. cc1's diagnostic vocabulary is open-ended; "make deleted
        # the .o" is closed and true.
        compile_failed = bool(re.search(r'^make: \*\*\* \[.*\] Error \d+', txt, re.M)
                              and 'Deleting file' in txt)
        # Still collect the diagnostic lines — the reconcile agent needs them verbatim — but they
        # no longer DECIDE the class. Keep the warning filter: `conflicting types` also appears
        # benignly as a warning for builtins and external-decl mismatches.
        err = [l for l in txt.splitlines()
               if 'warning' not in l.lower()
               and re.search(r'\berror\b|conflicting|undefined|previous declaration|redeclar'
                             r'|too (many|few) arguments|parse error|undeclared|incompatible', l)]
        # CLASSIFY ON THE OUTPUT, NEVER ON THE EXIT STATUS. `make build` runs `check`, so a draft
        # that COMPILES PERFECTLY and merely produces different bytes also exits non-zero — an
        # `rc == 0 -> DIFF` branch is unreachable and silently mislabels every real byte-DIFF as
        # "unknown". (Caught this session; the S28 law "a tool's exit status is never the oracle".)
        sha_fail = re.search(r'^\s*\[FAIL\].*\n\s*got\s+(\w+)\n\s*want\s+(\w+)', txt, re.M)
        if compile_failed:
            verdict = (" || ".join(err[:5]) if err
                       else "compile FAILED but no diagnostic line matched — read the log by hand")
            klass = 'PLUMBING'
        elif sha_fail:
            verdict = (f"compiles clean; SHA mismatch got {sha_fail.group(1)[:12]}… "
                       f"want {sha_fail.group(2)[:12]}… -> a GENUINE BYTE DIFF, not a declaration problem")
            klass = 'DIFF'
        elif b.returncode == 0:
            verdict = "BUILD OK and byte-identical -> should have banked; re-gate"
            klass = 'BANKED?'
        else:
            verdict = "(non-zero build, neither a compiler error nor a SHA mismatch matched)"
            klass = 'UNKNOWN'
    finally:
        open(tu, 'w').write(orig)          # revert ALWAYS — a killed process performs no undo
    out[fn] = {'ov': ov, 'tu': tu, 'klass': klass, 'blocker': verdict}
    print(f"{fn:<16} {ov:<14} [{klass}] {verdict[:130]}", flush=True)

json.dump(out, open('.run/s7_blockers.json', 'w'), indent=1)
n = {}
for v in out.values():
    n[v.get('klass', 'n/a')] = n.get(v.get('klass', 'n/a'), 0) + 1
print("\nCLASSIFIED:", n)
print("-> .run/s7_blockers.json  (feed each agent its OWN blocker line, verbatim)")
