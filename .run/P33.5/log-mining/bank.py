#!/usr/bin/env python3
"""Bank the log-mining harvest into the kit's kernels (DK-69 … DK-80) and emit the harvest table for the phase log.

Reads HARVEST.md (slice → candidate → cited log line), applies the ASSIGN map below (every candidate exactly once, or DROP with
a reason), writes the kernel section text with a generated `provenance:` line per kernel, inserts it into decomp-kernels.md
before the museum, updates the Coverage lines, and writes HARVEST_TABLE.md (candidate · verdict · where).
"""
import pathlib, re, sys

D = pathlib.Path(__file__).resolve().parent
REPO = D.parents[2]
K = REPO / "decomp-architect" / "corpus" / "decomp-kernels.md"

# ---- the assignment: kernel -> [(slice, C)] ; DROP -> [(slice, C, reason)]
ASSIGN = {
 "DK-69": [("Phase26","C1"),("Phase26","C2"),("Phase26","C3"),("Phase29-2of4","C1"),("Phase29-3of4","C5"),("Phase33","C4"),("Phase30-1of2","C12"),("Phase29-4of4","C4"),("Phase33","C5"),("Phase33","C6")],
 "DK-70": [("Phase30-2of2","C2"),("Phase30-1of2","C4"),("Phase30-1of2","C5"),("Phase30-2of2","C3"),("Phase29-4of4","C1"),("Phase23-27","C6"),("Phase31-2of3","C1"),("Phase31-2of3","C2"),("Phase31-3of3","C6"),("Phase31-1of3","C10"),("Phase31-2of3","C9"),("Phase31-2of3","C8")],
 "DK-71": [("Phase29-3of4","C3"),("Phase31-2of3","C3"),("Phase29-2of4","C2"),("Phase29-1of4","C4"),("Phase30-2of2","C5"),("Phase30-2of2","C4"),("Phase30-1of2","C1"),("Phase30-1of2","C3"),("Phase31-2of3","C7"),("Phase29-4of4","C2"),("Phase28-32","C3"),("Phase8-13","C1")],
 "DK-72": [("Phase29-1of4","C1"),("Phase29-2of4","C6"),("Phase31-1of3","C6"),("Phase29-4of4","C5"),("Phase30-1of2","C10"),("Phase29-2of4","C4"),("Phase29-3of4","C6"),("Phase7","C2"),("Phase7","C3"),("Phase28-32","C2"),("Phase30-1of2","C13"),("Phase21","C3"),("Phase21","C2")],
 "DK-73": [("Phase17-18","C1"),("Phase25","C1"),("Phase30-1of2","C11"),("Phase31-2of3","C10"),("Phase31-1of3","C5"),("Phase19-20-22","C1"),("Phase17-18","C6"),("Phase15-16","C5"),("Phase15-16","C1"),("Phase29-4of4","C6"),("Phase29-2of4","C5"),("Phase7","C5"),("Phase24","C2"),("Phase19-20-22","C2")],
 "DK-74": [("Phase23-27","C2"),("Phase23-27","C3"),("Phase23-27","C4"),("Phase31-1of3","C1"),("Phase30-1of2","C8"),("Phase23-27","C1"),("Phase31-2of3","C6"),("Phase24","C1"),("Phase24","C3"),("Phase17-18","C4"),("Phase29-2of4","C3"),("Phase15-16","C3"),("Phase31-1of3","C12")],
 "DK-75": [("Phase23-27","C5"),("Phase15-16","C6"),("Phase31-3of3","C4"),("Phase31-3of3","C1"),("Phase29-1of4","C5"),("Phase33","C15"),("Phase21","C1"),("Phase29-1of4","C2"),("Phase29-1of4","C3"),("Phase31-1of3","C8"),("Phase31-1of3","C9"),("Phase31-1of3","C2"),("Phase25","C2")],
 "DK-76": [("Phase30-2of2","C1"),("Phase31-1of3","C7"),("Phase31-2of3","C4"),("Phase30-1of2","C2"),("Phase31-3of3","C7"),("Phase28-32","C6"),("Phase31-1of3","C11"),("Phase31-1of3","C3"),("Phase30-2of2","C6"),("Phase30-1of2","C9"),("Phase33","C16"),("Phase30-1of2","C7")],
 "DK-77": [("Phase24","C4"),("Phase29-2of4","C7"),("Phase29-1of4","C6"),("Phase31-1of3","C4"),("Phase31-2of3","C5"),("Phase15-16","C4"),("Phase15-16","C8"),("Phase31-3of3","C5"),("Phase28-32","C4"),("Phase29-3of4","C4"),("Phase28-32","C5"),("Phase7","C4"),("Phase31-2of3","C11"),("Phase28-32","C1")],
 "DK-78": [("Phase15-16","C2"),("Phase15-16","C7"),("Phase7","C1"),("Phase30-1of2","C6"),("Phase29-3of4","C1"),("Phase17-18","C3"),("Phase17-18","C2"),("Phase8-13","C2"),("Phase8-13","C3"),("Phase33","C7")],
 "DK-79": [("Phase17-18","C5"),("Phase29-4of4","C3"),("Phase23-27","C7"),("Phase31-3of3","C2"),("Phase31-3of3","C3"),("Phase29-3of4","C2"),("Phase33","C14"),("Phase23-27","C8"),("Phase28-32","C7"),("Phase33","C8")],
 "DK-80": [("Phase33","C3"),("Phase33","C9"),("Phase33","C10"),("Phase33","C11"),("Phase33","C12"),("Phase33","C13"),("Phase33","C1"),("Phase33","C2"),("Phase25","C3")],
}
DROP = [("Phase8-13", "C4", "the miner's own verdict: low value — a refactoring generality with no measured cost")]

TITLES = {
 "DK-69": "An instrument's blind spots: the tests that pass by construction",
 "DK-70": "A verdict has three staleness axes, and the health suite asserts the work was done",
 "DK-71": "What earns belief: applicability, independence, prediction, and the refusal as a finding",
 "DK-72": "Denominators, units and labels — the number must say what it counts",
 "DK-73": "Leverage is not tractability; scope a campaign by verdicts, invariants and kill criteria",
 "DK-74": "Models and prompts: targeted context, named degenerate outputs, two-sided caps, tiers by what they can learn",
 "DK-75": "The unattended run: a crash is a pause, a stop is a file, a limit is an epoch",
 "DK-76": "Agents and the tree: write-isolation is architecture, never a sentence in a prompt",
 "DK-77": "Edits that keep their proofs: repair the caller, land changes separately, draft before you carve",
 "DK-78": "The search harness and the compiler as evidence: same context, own corpus, a sibling's silence proves nothing",
 "DK-79": "Maintaining the knowledge base and the record: contradictions are work items, edits are verified by section",
 "DK-80": "Hosts and services: the small facts that each cost an hour",
}

BODIES = {
"DK-69": """- **Kernel:** a check that cannot fail is not a check, and several common shapes cannot. A round-trip selftest of a
  partition or rewrite tool is a serialisation check, not a coverage check — it passes by construction when a missed item is
  absorbed into its neighbour's span, so every such tool needs an independent detector of items it failed to anchor. A set
  that gates work must be reconstructible from committed artifacts; a roster kept in ignored scratch is an unversioned oracle,
  silently wrong for anything it was not named after and blind after a fresh clone. A guard allowed to sit red and uncalled
  does not exist: its value is zero until it is green on the head commit and invoked by the standing report, and a docstring
  claiming it is wired is not wiring. A verification flag that short-circuits the tool's write path leaves the stale artifact
  in place and still exits zero. A status line a script prints unconditionally is not a measurement — derive every conclusion
  the script emits from the command's own output. A coverage instrument that infers its denominator from *open* work inverts
  at 100% (a complete map read as everything missing): carry the scanned denominator in the artifact and test the instrument
  at both endpoints. A metric that re-parses source is blind to a body banked through an include; trust the metric derived
  from the stub oracle. A name grep is not a "defined here" oracle — a declaration carrying the name reads as a definition.
  An annotator that writes into the text it reads must never treat its own output as evidence, and regex-extracted evidence
  needs a structural marker or prose becomes data.
- **When it applies:** every selftest, health line, coverage figure and "is it banked" query — at the moment it is written.
- **Cost:** a parser defect that survived eight sessions under a green selftest; a rename-drift failure undetected across two
  phases beside a red detector; a decision document nine days stale under a green flag.""",
"DK-70": """- **Kernel:** a stored verdict can be stale because the DRAFT changed, because the BASELINE changed — or because the
  INSTRUMENT changed. When a tool is repaired, every verdict it produced becomes a hypothesis again; re-gate the drafts the
  repair's blast radius plausibly touched, scoped by that radius and never the whole ledger. A ledger row with no draft
  artifact is a rumour, not a result. Count agent completions from the run journal's result records, never from artifact
  existence — an agent writes its deliverable early and then iterates, so the file proves nothing. A clean-looking verdict
  that appears immediately after your own repair transform is a suspect, not a result: re-measure the artifact the transform
  produced before routing the residual. The aggregate check target is proven fail-closed before checks are added to it, and
  every audit oracle has a dependent that would notice its absence. The health suite asserts that a tool DID its work, not
  only that the data is intact: zero inputs, an impossible wall-clock and a missing persistent effect are each a defect. A
  health check that cannot finish is not a check — keep the health target sampled and fast, and put the exhaustive form behind
  its own name. Incremental gates never exercise the extraction step, so regeneration rot is undated and invisible for weeks —
  sweep it on a schedule. A validity stamp must be honoured by every downstream consumer, and a wrong write-side label cannot
  be repaired by a correct read key. Every status claim in an agent's context is expiry-checked against live state, or agents
  report it back as an observation.
- **When it applies:** after any tool repair; in every health target; in every ledger read by a fresh session.
- **Cost:** four byte-correct drafts banked unchanged a month late; a health target that had never completed; three agents
  reporting a red baseline that was a stale note in their pack.""",
"DK-71": """- **Kernel:** an oracle that can always be RUN is not always APPLICABLE — state the applicability precondition beside the
  recipe, or a coarse run returns a large number that reads as a verdict. "Independent" names the instrument, not the input:
  two refusals of two separately-written drafts from one tool is one test repeated. A diagnosis earns belief when it predicts
  its own residual membership, not when it explains the failures already seen. A defect reasoned into a sibling tool is latent
  until a run shows its signature; do not patch on theory right after that tool produced a clean run. A failure that will not
  reproduce earns a negative-control-proven detector, not a speculative fix — and every abort path proves its revert by diffing
  the worktree against a baseline captured at the start of the run. A derived claim outranks a heuristic verdict; when two
  heuristics disagree, take the union and queue the disagreements — under-reporting hides work, over-reporting only costs
  review. An instrument's refusal is a finding, not an obstacle: overriding it means explaining why the instrument is wrong,
  never finding another route. Read the first ten results of a long run before trusting the other hundreds, and
  negative-control any new refusal against everything that already succeeded. A refusal names the branch the caller entered,
  not the subject — make the applier consult the classifier it already has. Classify a harness fix as a logic defect or a
  path-reachability gap and price it accordingly; only the logic defect generalises. Re-verify a task's premise in the code at
  execution time — roadmap lines, audit findings and even an audit's own correction footer go stale, and the document that
  named a defect is usually the first to. A toolchain-version detector's verdict is a hypothesis until a placement count backs
  it; when a version stamp and a byte probe disagree, the probe wins and the refuted stamp is un-banked.
- **When it applies:** every diagnosis, every disagreement between two instruments, every premise inherited from a document.
- **Cost:** a "genuine codegen" verdict that was a size mismatch; a classifier verdict that overrode a hash match and
  understated a whole bucket; a version stamp banked for a phase against the bytes.""",
"DK-72": """- **Kernel:** a number that does not say what it counts will be read as the wrong thing. A stop/continue instrument
  aggregates at exactly the unit the decision is made in; one that averages a finer unit manufactures a false "we are at the
  floor". A reach-weighted gain (size × copies) is not a size — every figure says which of the two it is. Sibling count and
  never-drafted count are different denominators; conflating them overstates free leverage and hides that the remaining mass
  is singletons. A yield estimator that counts "unclaimed at the moment it runs" ranks correctly and over-projects absolutely;
  never plan off its absolute numbers. Do not cross-price two economies: a conversion rate measured on the residue queue does
  not price a fresh wave. When two blockers are orthogonal, a classifier's if-chain order silently becomes the label —
  cross-tabulate, never bucket. Measure what fraction of a cycle a parallelism knob can actually touch before adopting it. A
  milestone counted in matched functions excludes the splitter's auto-generated empty bodies, defined at the moment the bar
  is set. A duplicate census run before the vendor library is linked out is contaminated — the groups are library fragments
  and epilogues. The file a function lives in is not evidence of its class; read the recorded attribute, never the hosting
  split. Keep a glossary line for any term two documents use in opposite senses. Say which currency a wave buys — percentage
  or idioms — before launching it, and judge it in that currency; and a class-distribution assessor only sees the population
  already attempted, so "analyse all remaining work" is a cheap triage pass, not a static analysis.
- **When it applies:** every plan figure, every ledger column, every verdict of "at the floor".
- **Cost:** a phase nearly closed on an artifact of the wrong unit; a leverage estimate three times too high; a thirty-fold
  mis-scope risk from one term meaning two things.""",
"DK-73": """- **Kernel:** the most-duplicated functions are systematically the hardest — leverage and tractability are
  anti-correlated — so a leverage-first queue front-loads hand-tier work, and its early bank rate is not a harness fault.
  Carry a measured closeness read per target and never let reach × size stand in for "crackable"; the reach ranking finds the
  most-DONE work first, so derive the target pool from the build's own invariant. Yield clusters by binary, not across the
  fleet — draw per binary once two independent lanes concentrate in the same place. A cracked idiom transfers within its
  family and not across it: price a lane by families, not by class size. An open-ended grind phase's milestone is invariants
  held plus a clean checkpoint, never a percentage; a research phase is scoped by a per-class verdict (a validated lever or a
  falsifiable wall verdict per class), not by a percentage either. Write numeric kill criteria into the plan before the data
  exists, and let them fire. Measure a pipeline's yield on the residual, not on solved functions: a known-answer ladder (revert
  a match to a stub, make the pipeline re-derive it) sets the ceiling, and the gap to the unmatched tail is the real number.
  Declare a mechanical lever spent only on a positive, three-part measurement — every built lever applied and returning zero,
  the residue split by structure, and the decay curve priced against what remains. Sequence a phase so the cheapest thing that
  can invalidate everything below it runs first; when a foundation task hits a structural wall mid-phase, bank the tractable
  wins and re-scope the wall as its own sub-project. Inside one leverage class, schedule by measured remaining effort and pull
  the payoff-dominating outlier out for an immediate cheap triage. Choose the exemplar for cracking a codegen class by the
  size of its residual: the one-instruction mismatches are the cleanest real-function isolates.
- **When it applies:** the draw, the phase plan, the campaign's close.
- **Cost:** a phase priced by percentage that could only be closed by verdicts; a mega-leverage "freebie" that was a
  stack-switcher; a lane priced by class that cost forty turns of learning per family.""",
"DK-74": """- **Kernel:** give a drafting model a targeted slice of the knowledge base, never the whole — full context measurably made
  a model worse. Name the degenerate output in the prompt: an empty body compiles, so "translate every instruction, never an
  empty body" is a required instruction. The output-token cap is a two-sided knob and both failure modes read as "the model is
  bad"; more budget is not more quality — measure it as a paired A/B and treat truncation as recoverable, not as a defect
  signal. When A/B-ing any harness knob, ship a positive control that the knob actually moved. Mine new idioms from fresh
  cracks, never from the failed backlog — the failure pile re-teaches what you already know — while the harvest SELECTOR must
  still be able to see failed attempts, or it learns from the easy half. Escalations to the expensive tier run strictly serial
  with idiom-banking between them; only the tier that cannot learn is run in parallel. The wall-breaker tier is a match tier,
  not a plumbing tier: work a deterministic arbiter can judge does not need the expensive model. Accelerate the stage that is
  the bottleneck — a byte-exact search loop costs a compile plus a whole-binary gate per candidate, so hardware brute force
  buys nothing. Make the drafter run the pre-gate guard and return the NAMED banking prerequisite; a batch of diagnosed
  candidates is worth more than a batch of opaque matches. Before concluding a pipeline is weak, histogram the compiler's
  error text: most failures were one missing declaration, fixed once. Keep prompt and law text in data, never inside the
  launcher's source template.
- **When it applies:** the pack builder, the routing table, every model experiment.
- **Cost:** a local model made worse by more context; eight diagnosed matches revealing one lever the opaque batch had
  hidden; a wave killed at launch by a quote character inside a template.""",
"DK-75": """- **Kernel:** build the unattended campaign so a crash is a pause — probe the dependency at the top of each cycle, commit
  per cycle, persist the tried-set and each confirmed result the moment it is confirmed; a long stateless batch that writes
  only at the end loses everything to a kill. Design it for a human with no agent session: a STOP file honoured at a safe
  boundary, a supervisor that tells a clean exit from a crash, a status one-liner, and crash-resume proven by a deliberate kill
  before the first real run. Never wrap a project tool in a timeout shorter than its own budget — you pre-empt its recovery
  handler and lose its buffered output. Sweep for orphaned worker processes at every session boundary: a dead-pipe compiler
  holds a core forever and nothing reports it, and a harness's low-memory guard silently kills long background jobs. A run
  that looks throttled is usually blocked on an interactive approval prompt — check the pending prompt before diagnosing the
  provider. Batch size is a risk lever, not a token lever: isolated agents cost about N times one agent whether concurrent or
  serial, so size a batch by the unverified spend you are willing to lose before the next measurement. A repair mode whose
  cost is exceptions × population is gated on a measured exception count; for a broadly divergent set, drop rather than
  recover. A free or preview model tier can be withdrawn mid-campaign without notice — a fleet-wide 404 is an epoch event, not
  N model failures — and a metered key's own cap is a separate limit from the account's credit. In a pipelined
  drafter/gater, "still open" is not "not yet attempted": consecutive waves re-drafted the wave still in flight. A fan-out
  script generated by an orchestrator runs sandboxed without the repository: it is self-contained, so target selection
  belongs to the generator, not the workers.
- **When it applies:** every lane that runs while nobody watches.
- **Cost:** a thirteen-hour orphaned compiler; three gates with no verdict and half-applied propagations from one timeout;
  a six-hour "throttle" that was a permission prompt.""",
"DK-76": """- **Kernel:** drafting agents must never be ABLE to write the build tree; every agent artifact lands in a scratch directory,
  so a killed or racing campaign costs build cycles and zero paid work. "Never modify the source tree" in a prompt is a
  request, not an enforcement — snapshot the tree status around every agent and name the offender. Never adopt a subagent's
  worktree wholesale: it is a snapshot of an older tree and may predate a bank; re-gate its artifacts against the head. The
  generated disassembly tree is shared mutable state — a fleet verify/clean chain and the per-function instruments cannot run
  at the same time. A probe that splices the tree in order to measure it must restore it, or the progress oracle counts the
  splices as banks. Snapshot every target's disassembly before gating: a successful bank prunes it, and harvest and recovery
  need both sides. Never let model-authored prose reach the shell inside double quotes — a backticked command in a commit
  message executed; use a quoted heredoc. Keep the wave harness in the repository with its contracts; a harness rebuilt from
  memory each run silently goes stale. A `cd` in one agent shell call persists into the next. Never test a helper by importing
  its module: a tool with no main guard runs its whole pipeline on import.
- **When it applies:** the day the first agent is launched, as architecture; then every wave.
- **Cost:** two tree corruptions recovered with one checkout only because the drafts lived outside the tree; a real extract
  run by a commit message; a download landing inside a submodule.""",
"DK-77": """- **Kernel:** when a byte-proven body will not integrate, the repair moves the CALLER's declaration to the definition's
  signature — never the definition to the caller's — and only where the change is width-compatible. A repair ladder probes
  whether each stage is needed before applying it, or it silently escalates a binary-local bank into a fleet-shared edit. Land
  a pure rename and a semantic or layout change as separate gated edits, so a gate failure attributes itself. Draft first,
  then carve: a build-unit split is safe only when the new unit is immediately populated with proven bodies. A proven
  transform that is not a rung of the ladder the drafts actually pass through does not exist for those drafts. Re-run the
  deterministic declaration canonicaliser over old quarantined drafts after every large bank — recovery odds rise as the
  banked corpus grows and the pile costs nothing to keep. An idempotency guard keyed on presence freezes every record created
  before the system matured; key it on completeness, and make regenerated artifacts idempotent by replacement, never by
  skipping. A hard-coded assumption fixed in one tool survives in its siblings: grep the tree for the literal and fix every
  twin in the same change. Before a fleet-wide mechanical edit, census the whole population for the exact preconditions the
  edit assumes — uniformity is the licence, non-uniformity the design input. A batch gate that bisects on failure re-runs the
  singleton against an unchanged baseline: special-case one, or pay a duplicate build on the hot path. A byte-identical
  baseline is proven only when the whole gate is green from clean across several independent sessions. A build-system
  conditional that expands at parse time makes its own negative control vacuous. Never round-trip a curated configuration
  through a serializer: every oracle you own measures bytes, so a formatting-destructive write is invisible to all of them.
- **When it applies:** every integration repair, every carve, every fleet-wide edit.
- **Cost:** a registry's forty-seven comment lines destroyed under green gates; a fleet edit taken by a bank that needed a
  local one; a duplicate build on every single-draft gate.""",
"DK-78": """- **Kernel:** a search harness must compile in the SAME declaration context as the real build; an isolated context does not
  merely fail to verify, it makes the search converge on the wrong answer. The search unit is the C expression — it cannot
  freeze the instructions already right, because register allocation couples them. A decompiler's "unaffected register"
  output means it decompiled one entry path of a multi-entry function and handed you a fragment: an instrument limit, never
  evidence the function is hard. Check group identity from the signature files before probing a family — if the members are
  structurally identical, a zero result is a compile-error certainty, not evidence about codegen. Vendor compiler sources
  carry form-feed page separators, which a scripting language's line splitter honours and grep does not, so a line-number
  checker over the source drifts and blames the wrong line. Your own corpus of byte matches is an experiment already run on
  the toolchain: settle "is my rebuilt compiler faithful?" from it before installing the original vendor tools. Another
  project's unmatched stubs are a record of what they did not crack, never proof that a class is uncrackable —
  cross-project corroboration multiplies confidence in a wrong verdict as readily as a right one. Histogram a secondary
  binary's call targets by address range before assuming it carries its own copy of anything; a raw blob's load address is a
  hypothesis whose free confirmation is arithmetic against the next known segment's base. A relocation-interleaved
  disassembly is produced only for object files; a linked image lists relocations separately with a shifted address column.
- **When it applies:** the permuter's base file, the first probe of any family, every cross-project citation.
- **Cost:** an overnight run that "closed" forty per cent of its near-misses and gated zero; a class written off on a
  neighbour's silence.""",
"DK-79": """- **Kernel:** a contradiction between two entries of your own knowledge base is a work item, not noise — replay the levers
  already written down, under the correct oracle, before commissioning new research. A wrong prescription left in the base is
  worse than no entry: when evidence refutes an entry, correct that entry in place, in the same session, carrying the
  refutation. A document that cites a repository path is an untested claim about the repository — lint it. A programmatic
  edit to a long-lived knowledge document silently truncates or duplicates it; verify the sections, never the commit. The
  live hand-off block is strictly appended at the end of its file — file order is the only recency signal a fresh session
  has. Never restructure a proven tool with blind string replaces at the end of a long session; specify it as the next
  session's first task. A miner over your own records finds only what its pattern anticipates — measure the widened pattern's
  yield. Assert that the work ledger partitions the live work, and treat a row the invariant refutes as a lie a fresh session
  will act on. Write the phase synthesis in a fresh session that re-reads the committed state cold; the cold read is what
  catches stale artifacts. A derive-then-apply pipeline over a live repository needs a freshness guard and a stated sequencing
  law.
- **When it applies:** every harvest, every close, every programmatic edit of a document that outlives the session.
- **Cost:** a cookbook section silently deleted for a session; a day-older hand-off read as the live one; a class re-researched
  because two entries disagreed and nobody replayed either.""",
"DK-80": """- **Kernel:** small facts about hosts and services, each learned at the cost of an hour. `git check-ignore` is silent for
  tracked paths, so an ignore-coverage audit run before the untracking passes vacuously — use its no-index form. A
  content-hash "no forbidden bytes" audit collides on zero-length files. A mirror push does not push the stash ref. Route a
  host purge request through the flow that actually exists; the obvious form is a trap. A host feature can be gated on the
  very flip it was meant to precede — read the settings page, do not infer. A public scratch service's compiler image is not
  your pinned toolchain; rebuild it locally and prove byte-identity before asking for a preset. A disassembler's script
  directory compiles as one bundle, so a single non-compiling script disables every script in it and the error names a
  working one. The same tool refuses a project path containing a component that starts with a dot, so a scratch project
  cannot live under a dot-directory. Run reference-compiler dump passes from a scratch working directory, or the dumps land
  in the repository root and later read as committed artifacts.
- **When it applies:** the first time each host or service is touched.
- **Cost:** an hour each, and one flip-gate misread.""",
}


def parse_harvest():
    text = (D / "HARVEST.md").read_text(encoding="utf-8")
    out = {}
    slice_ = None
    cur = None
    for ln in text.splitlines():
        m = re.match(r"^=+ (\S+):", ln)
        if m:
            slice_ = m.group(1); continue
        m = re.match(r"^  (C\d+) — (.*)", ln)
        if m:
            cur = (slice_, m.group(1)); out[cur] = {"title": m.group(2), "log": None}; continue
        m = re.match(r"^      LOG (phase-ends/logs/\S+?):(\d+):", ln)
        if m and cur:
            out[cur]["log"] = f"{m.group(1)}:{m.group(2)}"
    return out


def main():
    cands = parse_harvest()
    assigned = {}
    for dk, lst in ASSIGN.items():
        for s, c in lst:
            key = (s, c)
            assert key in cands, f"unknown candidate {key}"
            assert key not in assigned, f"{key} assigned twice ({assigned[key]} and {dk})"
            assigned[key] = dk
    for s, c, why in DROP:
        assert (s, c) in cands and (s, c) not in assigned
        assigned[(s, c)] = f"DROP: {why}"
    missing = [k for k in cands if k not in assigned]
    assert not missing, f"unassigned candidates: {missing}"
    print(f"bank: {len(cands)} candidates, {sum(1 for v in assigned.values() if v.startswith('DK'))} banked into {len(ASSIGN)} kernels, {len(DROP)} dropped")
    # section text
    sec = []
    for dk in ASSIGN:
        cites = "; ".join(f"{cands[(s, c)]['log']} ({s} {c})" for s, c in ASSIGN[dk])
        sec.append(f"### {dk} — {TITLES[dk]}\n{BODIES[dk]}\nprovenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry \"P33.5 S92\"): {cites}\n")
    section = "\n".join(sec)
    k = K.read_text(encoding="utf-8")
    old_head = "## 8. Added by the coverage pass — the record's residue\n\n*The kit's coverage check derives every rule and every hindsight entry of the source project and refuses one that is neither\ncited by a provenance line nor dispositioned. These are the lessons that check found in the record and nowhere in the kit.*\n"
    assert k.count(old_head) == 1
    new_head = ("## 8. Added by the coverage and log-mining passes — the record's residue\n\n"
                "*The kit's coverage check derives every rule and every hindsight entry of the source project and refuses one that is neither\n"
                "cited by a provenance line nor dispositioned; the three kernels after it are what that check found in the record and nowhere in\n"
                "the kit. The twelve after those come from a pass that read every phase worklog of the source project once more (some thirty\n"
                "thousand lines, one read-only agent per slice) for lessons banked in none of its distilled records — 777 candidates, 634 already\n"
                "banked, 143 new, clustered here by theme. Each provenance line names the worklog lines the lessons came from.*\n")
    k = k.replace(old_head, new_head)
    anchor = "\n---\n\n## 9. The failure museum, condensed — what looked right at the time\n"
    assert k.count(anchor) == 1
    k = k.replace(anchor, "\n" + section + anchor)
    old_cov = "- **Added by the coverage pass:** DK-66 … DK-68 — 3 kernels.\n- **In all:** DK-1 … DK-68 — 68 kernels"
    assert k.count(old_cov) == 1
    k = k.replace(old_cov, "- **Added by the coverage pass:** DK-66 … DK-68 — 3 kernels.\n- **Added by the log-mining pass:** DK-69 … DK-80 — 12 kernels (143 worklog lessons, clustered).\n- **In all:** DK-1 … DK-80 — 80 kernels")
    K.write_text(k, encoding="utf-8")
    n = len(re.findall(r"^### DK-", k, re.M))
    print("kernels now:", n)
    # harvest table
    rows = ["| Slice | C | Lesson | Log line | Verdict |", "|---|---|---|---|---|"]
    for (s, c), v in sorted(cands.items(), key=lambda kv: (kv[0][0], int(kv[0][1][1:]))):
        rows.append(f"| {s} | {c} | {v['title'][:110]} | `{v['log']}` | {assigned[(s, c)]} |")
    (D / "HARVEST_TABLE.md").write_text("# Harvest table — every NEW candidate of the log-mining pass, its verdict and its home\n\n" + "\n".join(rows) + "\n", encoding="utf-8")
    print("table rows:", len(rows) - 2)


if __name__ == "__main__":
    main()
