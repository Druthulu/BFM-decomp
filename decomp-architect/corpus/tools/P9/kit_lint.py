#!/usr/bin/env python3
"""kit_lint.py — the day-one decomp kit (decomp-architect/) stays free of the source project's names, paths, addresses and
rule numbers, honours its own placeholder contract, and ships scripts that parse (P33.5 task 11; in tools-health).

    tools/kit_lint.py                 # the whole package: every file under decomp-architect/
    tools/kit_lint.py --paths a b …   # an explicit file list (the checks that make sense per file)
    tools/kit_lint.py --selftest      # the R39 control: a planted leak line and a planted unlisted placeholder MUST fail

Six checks, each printed with its denominator (R41), exit 1 on any finding, exit 2 when the package is absent (R43):
  1. LEAK — no line outside a ```calibration fence and off a `provenance:` line matches the pattern
     `SLUS|Musashi|BFM|Druthulu|func_80|ov_SC|/home/musashi|/mnt/z|172\\.17\\.|\\bR[0-9]{1,2}\\b|§[0-9]+` (the kit refers to rules
     by G-id, to kernels by DK-id, to sections by "step N"; source-project figures live only inside calibration fences).
     The fence-aware form matters: `grep -v calibration` drops only the lines containing that WORD, not the fence contents.
  2. PLACEHOLDERS — the set of `{{NAME}}` tokens used anywhere under the package equals the set listed (backticked) in
     templates/PLACEHOLDERS.md; a used-but-unlisted or listed-but-unused placeholder fails (the contract tasks 11/12 honour).
  3. SYNTAX — every `*.sh` passes `bash -n`; every `*.py` compiles (the `compile` builtin, in memory — no bytecode is written into the kit); every `*.yml`/`*.json` block parses
     (JSON only for files whose whole content is JSON).
  4. GITIGNORE — templates/gitignore.decomp equals the ROM-firewall wiki page's fence (delegated to
     tools/gitignore_template_check.py; rc 0 required).
  5. TODO counts — `TODO(platform)` and `TODO(phase-N)` occurrences, informational, with the file count as denominator
     (the README says how many remain).
  6. COVERAGE — the number of files scanned is printed; zero files is a failure, never a pass.
Controls (R39): `--selftest` writes a leak line, a fenced (allowed) line, a provenance (allowed) line and an unlisted
placeholder into a scratch file under .run/ and asserts checks 1 and 2 catch exactly the two planted defects.
"""
import json
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
KIT = REPO / "decomp-architect"
PLACEHOLDERS_MD = KIT / "templates" / "PLACEHOLDERS.md"
LEAK_RE = re.compile(r"SLUS|Musashi|BFM|Druthulu|func_80|ov_SC|/home/musashi|/mnt/z|172\.17\.|\bR[0-9]{1,2}\b|§[0-9]+")
PH_RE = re.compile(r"\{\{[A-Z_0-9]+\}\}")
PH_LISTED_RE = re.compile(r"`(\{\{[A-Z_0-9]+\}\})`")


CORPUS_DIRS = (KIT / "corpus" / "tools", KIT / "corpus" / "cookbook")   # verbatim evidence: exempt from LEAK + PLACEHOLDERS (coverage is tool_census --check's)


def is_corpus(p):
    return any(d in p.parents for d in CORPUS_DIRS)


def kit_files():
    return sorted(p for p in KIT.rglob("*") if p.is_file() and "__pycache__" not in p.parts)


def leak_lines(text):
    """(lineno, line) for every leak outside a calibration fence and off a provenance line."""
    out, in_cal = [], False
    for i, line in enumerate(text.splitlines(), 1):
        if line.startswith("```"):
            if in_cal:
                in_cal = False
                continue
            if line.strip().startswith("```calibration"):
                in_cal = True
                continue
        if in_cal or "provenance:" in line:
            continue
        if LEAK_RE.search(line):
            out.append((i, line))
    return out


def placeholders_used(files):
    used = {}
    for p in files:
        for m in PH_RE.findall(p.read_text(encoding="utf-8", errors="replace")):
            used.setdefault(m, set()).add(p)
    return used


def placeholders_listed():
    if not PLACEHOLDERS_MD.exists():
        sys.exit(f"kit_lint: {PLACEHOLDERS_MD.relative_to(REPO)} missing — the placeholder contract cannot be checked (R43)")
    return set(PH_LISTED_RE.findall(PLACEHOLDERS_MD.read_text(encoding="utf-8")))


def check_syntax(files):
    bad = []
    for p in files:
        try:
            if p.suffix == ".sh":
                r = subprocess.run(["bash", "-n", str(p)], capture_output=True, text=True)
                if r.returncode:
                    bad.append((p, r.stderr.strip().splitlines()[-1] if r.stderr.strip() else "bash -n failed"))
            elif p.suffix == ".py":
                compile(p.read_text(encoding="utf-8"), str(p), "exec")   # in memory: never writes bytecode into the kit
            elif p.suffix == ".json":
                json.loads(p.read_text(encoding="utf-8"))
            elif p.suffix in (".yml", ".yaml"):
                try:
                    import yaml  # noqa: F401
                except ImportError:
                    continue
                yaml.safe_load(p.read_text(encoding="utf-8"))
        except Exception as e:  # noqa: BLE001 — the message is the finding
            bad.append((p, str(e).splitlines()[0]))
    return bad


def run_checks(files, do_gitignore=True):
    findings = 0
    n = len(files)
    if n == 0:
        print("kit_lint: 0 files to check — refusing to pass on an empty package (R43)")
        return 2
    corpus = [p for p in files if is_corpus(p)]
    files = [p for p in files if not is_corpus(p)]
    print(f"kit_lint: {len(corpus)} corpus files under corpus/tools + corpus/cookbook are verbatim evidence — exempt from the leak and placeholder checks (their coverage and equality are tool_census --check's)")
    # 1 LEAK
    leaks = 0
    for p in files:
        for ln, line in leak_lines(p.read_text(encoding="utf-8", errors="replace")):
            leaks += 1
            print(f"  LEAK {p.relative_to(REPO)}:{ln}: {line.strip()[:110]}")
    print(f"kit_lint: leak check — {leaks} finding(s) over {n} files (calibration fences + provenance lines exempt)")
    findings += leaks
    # 2 PLACEHOLDERS
    used = placeholders_used(files)
    listed = placeholders_listed()
    extra, unused = sorted(set(used) - listed), sorted(listed - set(used))
    for ph in extra:
        print(f"  PLACEHOLDER used but not listed in PLACEHOLDERS.md: {ph} ({', '.join(str(q.relative_to(REPO)) for q in sorted(used[ph])[:3])})")
    for ph in unused:
        print(f"  PLACEHOLDER listed but used nowhere: {ph}")
    print(f"kit_lint: placeholders — used {len(used)}, listed {len(listed)}, unlisted {len(extra)}, unused {len(unused)}")
    findings += len(extra) + len(unused)
    # 3 SYNTAX (the corpus copies included — they are real scripts)
    bad = check_syntax(files + corpus)
    for p, why in bad:
        print(f"  SYNTAX {p.relative_to(REPO)}: {why}")
    n_scripts = sum(1 for p in files + corpus if p.suffix in (".sh", ".py", ".json", ".yml", ".yaml"))
    print(f"kit_lint: syntax — {len(bad)} failure(s) over {n_scripts} script/config files")
    findings += len(bad)
    # 4 GITIGNORE
    if do_gitignore:
        r = subprocess.run([sys.executable, str(REPO / "tools" / "gitignore_template_check.py")], capture_output=True, text=True)
        print(f"kit_lint: gitignore template — {(r.stdout.strip().splitlines() or ['(no output)'])[-1]}")
        if r.returncode:
            findings += 1
    # 5 TODO counts (informational)
    text = "\n".join(p.read_text(encoding="utf-8", errors="replace") for p in files)
    print(f"kit_lint: TODO(platform) {text.count('TODO(platform)')}, TODO(phase-N) {len(re.findall(r'TODO\(phase-\d+\)', text))} over {n} files")
    return 1 if findings else 0


def selftest():
    scratch = REPO / ".run" / "kit_lint_selftest"
    scratch.mkdir(parents=True, exist_ok=True)
    f = scratch / "planted.md"
    f.write_text(
        "# planted control\n"
        "a leak line that names the source project: BFM and its rule R32\n"          # MUST be caught
        "```calibration\nsource project: BFM 218/218, R22 after every batch\n```\n"    # allowed
        "provenance: BFM R32 (Phase 26)\n"                                            # allowed
        "an unlisted placeholder {{NOT_IN_THE_CONTRACT}}\n",                          # MUST be caught
        encoding="utf-8")
    leaks = leak_lines(f.read_text(encoding="utf-8"))
    used = placeholders_used([f])
    extra = set(used) - placeholders_listed()
    ok = len(leaks) == 1 and leaks[0][0] == 2 and extra == {"{{NOT_IN_THE_CONTRACT}}"}
    print(f"kit_lint --selftest: leak lines caught {len(leaks)} (expected 1, at line 2: {leaks[0][0] if leaks else '-'}), "
          f"unlisted placeholders caught {sorted(extra)} (expected ['{{{{NOT_IN_THE_CONTRACT}}}}']) → {'OK' if ok else 'FAIL'}")
    f.unlink()
    return 0 if ok else 1


def main(argv):
    if "--selftest" in argv:
        return selftest()
    if not KIT.is_dir():
        print(f"kit_lint: {KIT.relative_to(REPO)} does not exist — nothing to lint (R43)")
        return 2
    if "--paths" in argv:
        files = [pathlib.Path(a).resolve() for a in argv[argv.index("--paths") + 1:]]
        return run_checks(files, do_gitignore=False)
    rc = run_checks(kit_files())
    print("kit_lint: OK" if rc == 0 else f"kit_lint: FAIL (rc {rc})")
    return rc


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
