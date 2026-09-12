# corpus/record/build/tools-health.mk — the source project's health chain, extracted VERBATIM from its Makefile by
# tools/tool_census.py --corpus (never edited by hand; asserted equal by --check). Each rung's comment names the
# incident that earned it; the tools it calls are in ../../tools/<phase>/ with their dictionary rows. A new project
# rebuilds this chain rung by rung as its tools exist — sampled by default, the exhaustive form behind its own name.
# The variables ($(VENV_PY), the aliases, the paths) are the source project's; the SHAPE is what transfers.

audit-digest:
	$(VENV_PY) tools/audit_digest.py
	# P33 D3: the published DATA must describe the current tree too — docs/progress.json, the README's
	# generated block and the badge files (the same numbers as the digest; R51: never typed)
	$(VENV_PY) tools/progress.py --json --readme --check
	# P33.5 task 7: the committed timeline must match what the digests generate (it used to be wired to nothing and sat stale)
	$(VENV_PY) tools/timeline.py --check

tools-health:
	# Regenerate the byte-derived boundary oracles FIRST (they're gitignored/regenerable), so the
	# audit checks CURRENT sigs and never crashes on an absent one — the resident audit (T10) needs
	# the sig_image resident sig, and a fresh clone has neither it nor the overlay sigs.
	$(MAKE) --no-print-directory sig-overlays
	$(MAKE) --no-print-directory sig-resident
	$(MAKE) --no-print-directory sig-modules
	# main's independent oracle (P31 S77, contract §1.3). Regenerated here for the same reason as
	# the others: it is derived and gitignored, and an oracle wired into nothing runs for nobody —
	# neighbor_ref sat MANUAL from S68 to S77 while the playbook called it the biggest cost lever
	# in the wave. Without this line sig_is_independent("main") silently reverts to False on a
	# fresh clone and main's boundary blind spot comes back with the audit still green.
	$(MAKE) --no-print-directory sig-main-oracle
	# P33 A2: main's build-derived game-code sig — the one the fleet digest weighs main by. Regenerated
	# here for the R51 reason: progress.py prefers it, so a stale copy would be a stale denominator.
	$(MAKE) --no-print-directory sig-main
	# P33 A3: the with/without-SDK dual (contract §1.2). Skipped, loudly, on a machine without the SDK
	# objects — there every build already IS the without leg, and running it twice would prove nothing.
	if [ -d "$(LIBCD_ELF)" ] && [ -d "$(LIBPAD_ELF)" ]; then
		$(MAKE) --no-print-directory sdk-dual
	else
		echo "[skip] sdk-dual: no SDK objects on this machine — the default build IS the no-SDK leg"
	fi
	$(MAKE) --no-print-directory audit-corpus
	$(MAKE) --no-print-directory audit-cdecl
	$(MAKE) --no-print-directory audit-binaries
	$(MAKE) --no-print-directory audit-text-sources
	# Phase 35 T7: the S1 invariant — one source per unique function — as a gate (R36): the census self-test (7 verdicts), then the
	# strict check by exit code (R97): no same-address class unshared unless ledgered in config/dedup_exceptions.tsv, no DEFINE_func_
	# site under src/ (--strict-macros), and the sig-blind second oracle (--strict-text). Runs BEFORE report so progress.py reads a
	# fresh .run/P35/census/share_census.json for its duplicate-copy fields.
	$(VENV_PY) tools/share_census.py --selftest
	$(VENV_PY) tools/share_census.py --check --strict-macros --strict-text --quiet
	# P36 S103: the hand-asm manifest has no drift. It ran ONLY in CI, so a DECOMPILE-NOW row converted by T4 batch tus10
	# (cb2fb5e6d, 2026-09-09) turned CI red for a day while every local chain stayed green (R54: a guard that is not
	# running locally is not a guard). Fix a GONE row with `tools/verbatim_check.py --update` (a one-row diff since S103).
	$(VENV_PY) tools/verbatim_check.py --strict
	# P36 T8: the lever census's self-test and its gate — every surviving register pin / asm statement outside the GTE header
	# carries a `// !FAKE:` marker (0 UNMARKED) and no marker is an orphan; a marker on a kept ordinary-C fake (do-while,
	# dead-init) is counted apart. `--strict` (0 pins, 0 asm) is the STRUCTS phase's finish line (Drew, S104), not this rung's.
	$(VENV_PY) tools/lever_census.py --selftest
	$(VENV_PY) tools/lever_census.py --check -j 16 --quiet
	$(MAKE) --no-print-directory report BINARY=main
	# AFTER report (which regenerates the digest), so this asserts the freshly-written digest agrees
	# with the tree — and, on a tree whose digest was committed stale, says so instead of staying green.
	$(MAKE) --no-print-directory audit-digest
	# The cookbook index is DERIVED (R33) and self-asserts its coverage (R32). Stale = agents can't
	# find documented idioms and re-derive them at full token cost (measured, P30 wave 1).
	$(VENV_PY) tools/cookbook_index.py --check
	$(VENV_PY) tools/gccmap_cites.py --check
	# P33 B5: the Ghidra roster is DERIVED from config/ghidra/*.jsonl (R33); a stale roster misreports
	# which programs' RE work is tracked as text. Pure text check, no Ghidra needed.
	$(VENV_PY) tools/ghidra_roster.py --check
	# P33 D5 (+ P33.5 task 7): every relative link in the public-facing docs resolves (pending pages are listed, and must be
	# gone by gate 2); nothing links into docs/sunset/; a wiki page links into docs/ only at a Reference-index/README target;
	# every docs/ file is covered by one; a wiki page cites only TRACKED paths. The render selftest also asserts every page
	# is reachable from the sidebar.
	$(VENV_PY) tools/doc_links.py
	$(VENV_PY) tools/wiki_render.py --selftest
	# P33.5 task 7: the ROM-firewall page's ```gitignore fence IS the kit's template (one source, two copies). Skips loudly
	# until the kit's template exists (task 11); exit 2 from the tool = "nothing to compare", never a pass (R43).
	if [ -f decomp-architect/templates/gitignore.decomp ]; then
		$(VENV_PY) tools/gitignore_template_check.py
	else
		echo "[skip] gitignore-template: decomp-architect/templates/gitignore.decomp does not exist yet (Phase 33.5 task 11)"
	fi
	# P33.5 task 11: the day-one decomp kit stays free of this project's names/paths/addresses/rule numbers (fence-aware),
	# honours its placeholder contract, and its scripts parse; the selftest is the R39 control (a planted leak MUST fail).
	$(VENV_PY) tools/kit_lint.py --selftest
	$(VENV_PY) tools/kit_lint.py
	# P33.5 task 13.5: the tool census — the two enumerations agree (find == git ls-files), every tool has a dictionary row and
	# every row a file, the need-keyed docs/tool-index.md and the kit's MANIFEST are fresh, the three verbatim corpora under
	# decomp-architect/corpus/ are byte-equal to their sources (regenerate with `make kit-corpus`).
	$(VENV_PY) tools/tool_census.py --check
	# P33.5 task 14.5 (Drew: "the whole of our experience?"): the kit's distillation cites or dispositions EVERY rule (R1..RN from
	# the digest) and EVERY accelerator entry; an uncovered one fails here unless config/kit_coverage_map.tsv says where it went.
	$(VENV_PY) tools/kit_coverage.py
	$(VENV_PY) tools/xsig/tests/test_xsig.py 2>&1 | tail -1 | grep -q '^OK' && echo 'xsig tests: OK (8)' || { echo 'xsig tests: FAIL'; exit 1; }
	# Behavioural guards (P31 S70): tools-health audits DATA integrity; these assert that a tool
	# ACTUALLY DID the work it reports. A guard that is not running is not a guard (R54).
	$(VENV_PY) tools/work_evidence.py --selftest
	# P31 S72: a code subseg owning raw jump tables in >1 non-adjacent span makes every switch
	# function outside the one carveable span UNBANKABLE — `main` sat in that state from Phase 7 to
	# Phase 31 and eleven functions were written off as "PROVEN gate-rejects" because of it. The
	# evidence is derivable from the raw image on day one; nothing was comparing it. 3.7s fleet-wide.
	$(VENV_PY) tools/split_indicator.py --self-test
	# P31 S74: A HARD GATE NOW, exactly as the informational form said it would become. The four
	# violations it was waiting on (ov_SC01_084, ov_SC02_005, ov_SC02_011, ov_SC03_105 — 16 open
	# fns / 3,613 ins) are split, so the fleet is 213/213 OK and any NEW subseg owning raw tables
	# in >1 non-adjacent span is a regression that must fail here rather than be echoed past.
	$(VENV_PY) tools/split_indicator.py --quiet
	echo "tools-health: OK — sigs fresh; corpus(+resident) + cdecl + binaries + report(lint+dedup) + cookbook-index all green."

