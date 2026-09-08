# Log mining — Phase31-2of3
Files/ranges: `phase-ends/logs/Phase31.md:2903-5804` (context read 2873-5834)  ·  Lines read: 2902 of 2902 (assigned range; 2962 including the ±30 context)
Candidates considered: 52 · NEW: 11 · ALREADY-BANKED: 41

**Grep harness.** `$D` below = the ten distilled paths named in the BRIEF:
`docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md`.
Harness verified against a known-true case first (`grep -c -i 'byte gate' $D` → 41 across 12 files;
`grep -n -i 'exonerate the instrument' $D` → 5) before any zero was believed.

---

## NEW

### C1 — The health suite must assert that a tool DID ITS WORK, not only that the data is intact: zero inputs, an impossible wall-clock and a missing persistent effect are each a DEFECT, not a result
- **Evidence:** `phase-ends/logs/Phase31.md:5122-5128` —
  > `* assert_inputs — zero readable inputs is a DEFECT, not a zero-yield result. **"0 of 0" is a fact`
  > `  about the HARNESS; "0 of 57" is a fact about the SUBJECT**, and reporting the first as the second`
  > `  cost a 35-binary batch. * assert_floor — work claiming a compile/gate cannot beat physics.`
- **What happened / what it cost:** `parallel_gate` resolved a relative `--drafts` path inside its worktree, found 0 drafts, banked 0 and exited **rc=0** — 35 binaries / 57 drafts "banked 0" in **1–2 seconds each** while the same drafts gated in-tree banked 15/16 (`:4901-4909`). The only tell was the runtime. `make tools-health` ran five audits and **every one asserted DATA integrity; none asserted that a tool did the work it claims** (`:5106-5108`). The answer was one module — `assert_inputs` / `assert_floor` / `assert_effect` — negative-controlled 11/11 in both directions and wired into the gate tools and the health target (`:5122-5136`).
- **Not banked — greps:** `grep -n -i 'work_evidence' $D` → 0; `grep -n -i 'assert_floor' $D` → 0; `grep -n -i 'cannot beat physics' $D` → 0; `grep -n -i 'fact about the harness' $D` → 0; `grep -n -i 'too fast' $D` → 0; `grep -n -i 'zero readable inputs' $D` → 0. (`grep -n -i '0 of 0' $D` → 1, cookbook:29606, a different subject — an agent wave filing 0 verdicts.) Accelerator #15's differential-oracle harness runs the same QUESTION down two paths; it has no "did the tool run at all" pair, and its table (`docs/accelerators.md:330-337`) does not contain one.
- **Proposed home:** DK (a kernel, section 2 "Instruments"), with a G-rule pointer from G19/G28
- **Portable because:** every decomp harness has tools whose "0 banked / exit 0" is indistinguishable from real work; inputs, a runtime floor and a persistent trace are assertable on any platform, from day one.

### C2 — A health check that cannot finish is not a check: keep the health target sampled and fast, and put the exhaustive form behind its own name
- **Evidence:** `phase-ends/logs/Phase31.md:5175-5181` —
  > `**S70 — `make tools-health` WAS UNRUNNABLE AND IS NOW 333s GREEN.** … `audit-cdecl` re-parsed`
  > `**every declaration in all 4,168 TUs** … ~787s of pure-Python collection before the first cc1`
  > `call … `--limit` already existed, its own help calls it "a fast smoke run", and nothing used it.`
- **What happened / what it cost:** a full-corpus regression test was living inside a health target, so `tools-health` **had never once completed** in the project's life; sampling it by default took it to 61 s and the whole target to 333 s green. The companion defect: the sample takes the FIRST 60 translation units, so the smoke run always tests the same files (`:5239-5240`), and parallelising the target exposed a latent fixed-temp-filename race that was safe only while serial (`:5183-5187`).
- **Not banked — greps:** `grep -n -i 'tools-health' $D` → 5 (all are "X now runs in tools-health", none about its runnability); `grep -n -i 'never completed' $D` → 0; `grep -n -i 'health target' $D` → 0; `grep -n -i 'smoke run' $D` → 0.
- **Proposed home:** DK (a kernel) or accelerator; the G-rule neighbourhood is G30 ("a guard not running is not a guard")
- **Portable because:** every decomp accumulates audits; the first one that costs ten minutes silently converts the whole suite into something nobody runs, and the fix (sample by default, exhaustive form as a separate target, randomise the sample) is platform-free.

### C3 — "Independent" names the INSTRUMENT, not the input: two refusals of two separately-written drafts from one tool is one test repeated
- **Evidence:** `phase-ends/logs/Phase31.md:3589-3590` —
  > `**"Independent" means a DIFFERENT INSTRUMENT, not a different input.** Two runs of one tool on two`
  > `drafts is one test repeated. R40, sharpened.`
- **What happened / what it cost:** `ov_SC06_022:func_80181664` was ledgered a WALL after "two independent gate refusals" — **both came from `parallel_gate`, the one gate that structurally cannot host a jump-table carve** (its worktree `asm/` is a symlink). Running the class through the SERIAL gate banked **16 of 32**, including functions `parallel_gate` had refused (`:3582-3588`, `:3671-3676`).
- **Not banked — greps:** `grep -n -i 'different instrument' $D` → 2 (both unrelated: a compiler-dump battery, and a cookbook lever "same instrument as §153"); `grep -n -i 'not a different input' $D` → 0; `grep -n -i 'two runs of one tool' $D` → 0; `grep -n -i 'two independent gate refusals' $D` → 0. Adjacent but not the same: G21 (a second *disagreeing* oracle) and G33 (a verdict names its instrument) both leave "two refusals from one gate" reading as corroboration; `docs/decision-log.md:1196` asks whether corroboration came "through the same tool you just fixed" — a tool that CHANGED, not a tool that was always the wrong instrument for the class.
- **Proposed home:** G (sharpen G21/G33 with the independence test) and DK-17
- **Portable because:** it is the acceptance criterion for every "wall" verdict on any project — count instruments, not attempts.

### C4 — A drafting agent must run where it CANNOT write the source tree; "never modify src/" in a prompt is a request, not an enforcement
- **Evidence:** `phase-ends/logs/Phase31.md:2879-2882` —
  > `* **A wave agent WROTE to `src/` and then `git checkout`-reverted it** (SYS_OBJ_2264, self-reported).`
  > `It was harmless ONLY because R42 meant every bank was already committed. The prompt's "never modify`
  > `src/" is a request, not an enforcement`
- **What happened / what it cost:** a drafting agent edited a live source file and then reverted it with a blanket `git checkout` — the exact reflex that destroyed 61 banks in an earlier session. It cost nothing only because every bank was already committed; the agent self-reported it, so the harness had no independent way to know. Raised as a rule candidate twice (`:2879-2883`, `:2986-2988`) and never ratified.
- **Not banked — greps:** `grep -n -i 'must not be able to write' $D` → 0; `grep -n -i 'cannot write the tree' $D` → 0; `grep -n -i "agent .{0,20}wrote to .{0,10}src" $D` → 0; `grep -n -i 'read-only' $D` → 6 (the purge probe R57, read-only survey agents, "never an agent that…" in chapter 08 — none grants or denies a drafting agent write access to the tree). DK-35 bounds an agent's *cleanup* to its own directory; it does not deny write access to the source tree.
- **Proposed home:** G (a conduct/harness rule beside G47/G48) and DK-35
- **Portable because:** any harness that fans out drafting agents over a repository can give them a sandbox, a worktree or a read-only mount; the alternative is trusting a paragraph of prose with the only copy of the banked work.

### C5 — A proven transform that is not a rung of the ladder the agents' drafts actually pass through does not exist for those drafts
- **Evidence:** `phase-ends/logs/Phase31.md:3810-3814` —
  > ``scope_data_externs.fix()` (§8d) has been byte-proven since Phase 26 and is used by `family_sweep` /`
  > ``bank_exemplar` / `jtbl_family_bank` — but **nothing in `gate_stage`'s ladder ever called it**, so a`
  > `draft written by a wave agent had never seen it. … went from **21 residuals to ZERO**.`
- **What happened / what it cost:** a fix proven five phases earlier and wired into three mechanical tools was absent from the one path every agent-written draft travels. Wiring it as an `_xform` rung took the `conflicting types for D_*` class from 21 residuals to zero, and recovered automatically the very function a previous session's audit had named as its byte-proven instance.
- **Not banked — greps:** `grep -n -i 'ladder ever called' $D` → 0; `grep -n -i 'not wired into' $D` → 0; `grep -n -i 'every proven transform' $D` → 0; `grep -n -i 'scope_demote' $D` → 4 (all usage instructions: which rung to run for which symptom, never the audit lesson); `grep -n -i 'residuals to zero' $D` → 0. Adjacent: DK-24 / G40 require every *verdict layer* to be consumed — this is about a *repair* that no lane applied.
- **Proposed home:** DK (extend DK-24 from verdict layers to repair rungs) or G40
- **Portable because:** every decomp accumulates deterministic repairs faster than it wires them; the audit ("is each proven transform reachable from the pipeline the agents' output enters?") is a one-time enumeration on any project.

### C6 — The knowledge-harvest selector must be able to see FAILED attempts; a filter that can only read banked work learns from the easy half
- **Evidence:** `phase-ends/logs/Phase31.md:3236-3240` —
  > `**The distill novelty selector was INVERTED** … `'no cookbook lever'` matched "no cookbook lever`
  > `*needed*" (a TRIVIAL note) and was the only pick of 24 … **and it structurally could not see`
  > `UNBANKED functions at all**, which is where the hardest functions write their richest notes`
- **What happened / what it cost:** the flywheel's own harvesting tool selected exactly the wrong note out of 24 and was blind by construction to every failed attempt — the population that produces the new laws. Fixed with `--with-unbanked`, carrying `banked=False` through to the verifier so what comes from a gate-refused draft is banked marked UNPROVEN rather than dropped (`:3236-3240`, `:3495-3496`).
- **Not banked — greps:** `grep -n -i 'only ever learns' $D` → 0; `grep -n -i 'unbanked' $D` → 6 (all are counts of unbanked drafts in specific waves, not the selector lesson); `grep -n -i 'novelty' $D` → 6 (harvest rounds, false-novelty claims, the "retrieval not content" reading — none names the selector's blindness). Note the tension worth recording with it: **G45** says "harvest only from byte-proven results", which is right for what may ENTER the base and wrong as a filter on what may be READ.
- **Proposed home:** G (a qualifier on G45) + DK-32
- **Portable because:** every project that has agents write notes will build a selector over them; if it keys on success it will never see the wall classes, which is the only place new laws come from.

### C7 — A refusal names the branch the caller entered, not the subject — make the applier consult the classifier it already has
- **Evidence:** `phase-ends/logs/Phase31.md:3346-3348` —
  > `**None was a real wall. Each was a tool describing its own confusion in the language of a limit** —`
  > `§401's law … generalised: *a refusal names the branch you entered, not the function you asked about.*`
- **What happened / what it cost:** the §322b carve route had **three stacked blockers**, and three full gate passes booked the same functions CARVE-REFUSED. The terminal refusal ("the carve model covers jump tables only, not an island of mixed included data") read as a permanent toolchain wall and was a ROUTING error: `island_probe` **already classified that same function `'tail'`** and its own detail named the right lane, but the refusal path never consulted it (`:5324-5338`). Consulting the probe first banked, immediately, the function three gate passes had refused. The same shape appeared inside the tools: "the tool's own error message pointed at the layer that was working" (`:5594-5595`).
- **Not banked — greps:** `grep -n -i 'names the branch' $D` → 0; `grep -n -i 'the language of a limit' $D` → 0; `grep -n -i 'routing error' $D` → 0; `grep -n -i "wearing a .{0,20}wall" $D` → 0. Adjacent and inverse: DK-26 makes the cheap probe call the real planner; this is the applier failing to call the probe.
- **Proposed home:** DK (pair it with DK-26) and the failure museum
- **Portable because:** every decomp pipeline grows multi-branch appliers with a cheap classifier beside them; the class of "wall" that is really an unrouted branch is universal, and the audit is to make every refusal name the branch and cite the classifier's verdict.

### C8 — Every status claim in an agent's context must be expiry-checked against live state, or agents will report it back to you as an observation
- **Evidence:** `phase-ends/logs/Phase31.md:5394-5396` —
  > `**stale BASELINE-RED verdict** — OPEN. THREE agents reported a red baseline on binaries I verified`
  > `BYTE-IDENTICAL; the third revealed the source: *"the pack's last gate verdict was BASELINE-RED"* —`
  > `they read it off the card. Cost me two phantom-regression chases.`
- **What happened / what it cost:** a historical gate verdict printed on a wave card came back as three independent agent reports of a live regression, and cost two phantom-regression investigations. The shipped repair (`:5511-5524`) reads the same live red union the gate itself consults and reports an expired claim as EXPIRED — measured over the real ledgers: **173 expired claims retired, 981 pairs gained a best-measured residual they were previously denied**.
- **Not banked — greps:** `grep -n -i 'BASELINE-RED' $D` → 4 (all about `gate_stage` refusing red-listed binaries' drafts — the producer side, never the card republishing a stale verdict); `grep -n -i 'read it off the card' $D` → 0; `grep -n -i "stale .{0,15}card" $D` → 0.
- **Proposed home:** G (extend G44 — a card names only what the knowledge base contains — to "and every status claim on it is expiry-checked") + DK-39
- **Portable because:** any agent given a status line will treat it as an observation and report it; the fix is that a card carries no present-tense claim it cannot re-derive at build time.

### C9 — A validity stamp must be honoured by every downstream consumer; and a wrong write-side label cannot be repaired by a correct read key
- **Evidence:** `phase-ends/logs/Phase31.md:5437-5442` —
  > ``gate_feedback` gated on `shape=='MATCH'` when reloc_identity's binding condition is **`aligned`** …`
  > `Below that bar reloc_identity itself downgrades status to `MISMATCH?` and stamps the row **ADVISORY**`
  > `— and gate_feedback republished it as a binding per-index instruction.`
- **What happened / what it cost:** **15 of 130** wave cards carried the block; **15 of 15 were not index-aligned**, so each "the target references 0x…" line was arithmetic against a different stream — **55 of 66 printed lines (83%) named a value that is not an address**, and 4 of 4 checkable cases named symbols the target never relocates. The second half stayed open upstream: the row's binary was stamped from a bare-name dict, so 2,317 of 42,655 drafts (5.4%) carried the wrong binary — **"a correct read key cannot repair a wrong write-side stamp"**, which is why the shipped fix validates against the target's own bytes rather than the label (`:5447-5451`, `:5481-5489`).
- **Not banked — greps:** `grep -n -i 'advisory' $D` → 3 (cookbook §176e's own producer-side "mark advisory when the shapes differ", and a rewrite rule — none about a consumer stripping the stamp); `grep -n -i 'republish' $D` → 0; `grep -n -i 'write-side' $D` → 0; `grep -n -i 'aligned=False' $D` → 0. G41 banks the bare-name key; it does not bank the consumer-side stamp obligation.
- **Proposed home:** DK (instruments) or a G-rule beside G41
- **Portable because:** any pipeline that computes a hint with a precondition will eventually have a consumer that reads the value and drops the precondition — and the consumer here is the model's own context.

### C10 — Yield is clustered by binary, not spread over the fleet: draw per-binary once two independent lanes concentrate in the same place
- **Evidence:** `phase-ends/logs/Phase31.md:5040-5043` —
  > `**20 of 52 twin remaps banked (38%)** … and **all 20 in `ov_SC06_011`**, the same binary that carried`
  > `15 of the 21 standalone banks. Two lanes, same concentration … the fleet's remaining work is NOT`
  > `uniformly distributed. **Draw future waves per-binary, not fleet-wide.**`
- **What happened / what it cost:** **35 of the session's 44 banks came from one binary**, reached by two mechanically independent lanes (a standalone-match sweep and a twin-remap sweep). The forecast built on the first cluster probed had been ~45–55 banks from 86 candidates and delivered 22, because that cluster was the least representative (`:4880-4882`). The next-session instruction became "find the next cluster by twin density + open-stub count per binary rather than drawing fleet-wide" (`:5235-5236`).
- **Not banked — greps:** `grep -n -i 'per-binary, not fleet-wide' $D` → 0; `grep -n -i 'not uniformly distributed' $D` → 0; `grep -n -i 'clustered, not uniform' $D` → 0; `grep -n -i "draw .{0,12}per.binary" $D` → 0; `grep -n -i 'concentrat' $D` → 6 (DK-42 / chapter 09 concentrate targets per binary to cut **rebuild wall-clock** — a cost argument, not a yield-distribution argument).
- **Proposed home:** DK-42 (add the yield half) or the wave playbook's draw step
- **Portable because:** on any fleet of overlays/objects sharing an engine, the residue concentrates where one module's tail is nearly finished; a per-binary draw finds it and a fleet-wide draw averages it away.

### C11 — (minor) A build-system conditional that expands at PARSE time makes its own negative control vacuous
- **Evidence:** `phase-ends/logs/Phase31.md:5155-5158` —
  > `*Make gotcha worth keeping: my first patch used `ifeq ($(filter $*,...))`, which make evaluates at`
  > `PARSE time when `$*` is empty — it would have silently always taken the maspsx branch and the`
  > `"byte-inert" result would have been vacuous. `$(if ...)` expands per-target*`
- **What happened / what it cost:** the per-object assembler switch that unlocked six "compiler wall" functions was verified BYTE-INERT against the whole fleet — a verification that would have proved nothing, because the conditional selecting the new branch could never be true. Caught before shipping; the rule's value is that the *control* was the thing at risk, not the change.
- **Not banked — greps:** `grep -n -i 'parse time' $D` → 0; `grep -n -i 'ifeq' $D` → 1 (a cookbook line describing an existing `ifeq ($(BINARY),main)` block, not the hazard); `grep -n -i 'vacuous' $D` → 4 (P31 S58's vacuous *checks* and P29's vacuous *probes* — neither is the make-expansion-time hazard).
- **Proposed home:** accelerator / cookbook (build-system section)
- **Portable because:** every matching decomp drives a per-TU flag matrix through make, and a byte-inert claim measured under a branch that never fires is the cheapest possible false green.

---

## ALREADY-BANKED (one line each)

- A self-report is not a bank; read the judge's artifact, never the agent's note — `decomp-architect/corpus/decomp-kernels.md:868` (DK-68); `docs/how-to-ai-decomp/12-failure-museum.md` #33
- A standalone closeness-0 proves the BODY, never that the TU accepts the SIGNATURE (§376) — `docs/accelerators.md:362` (#16), DK-20, G10
- A sampling filter ships with its denominator; a headline % ships its remainder — `decomp-architect/templates/registry-E.decomp.md:183` (G27), DK-30
- A stage that REWRITES the artifact it measures must gate the ORIGINAL first (raw-first ladder, §313) — `docs/matching-cookbook.md:30199`
- A killed/aborted gate's dirty tree is adjudicated by the byte gate, never blind-reverted — `decomp-architect/templates/registry-E.decomp.md:238` (G37)
- The half-fix that manufactures a false wall ("K&R converts only 4/26" — those 22 were the half-fix) — `docs/matching-cookbook.md:30966`
- A fleet tool that composes a path from a binary NAME encodes the layout; pass the fact you have, never reconstruct it (§363) — `docs/matching-cookbook.md:31707-31722`
- A cheap probe that does not model the applier's real step (the carve) is optimistic; the gate is the arbiter — `decomp-architect/corpus/decomp-kernels.md:353` (DK-26); `docs/accelerators.md:287` (#14)
- A verdict produced inside a worktree describes the worktree; a gitignored input turns a whole class into "refused" — `decomp-architect/corpus/decomp-kernels.md:291` (DK-21); `docs/accelerators.md:462` (#19)
- A worker's per-function verdict rows die with its worktree unless copied out (produced-but-not-consumed) — `decomp-architect/corpus/decomp-kernels.md:377` (DK-28)
- The five things a fresh worktree lacks; negative-control an UNMODIFIED binary first — `docs/wave-playbook.md:620-628`
- A carve writes three things and the merge must carry all three; splice one binary's block of the shared make fragment — `docs/wave-playbook.md:626-631`; G43
- Never `xargs -P` a tool that mutates shared state; one writer and one committer per shared file — `decomp-architect/corpus/decomp-kernels.md:316` (DK-23); `docs/accelerators.md:246`
- Never pattern-match the process table for a string your own command line contains; monitor by artifact — `docs/accelerators.md:196` (harness wound 2); DK-22
- Launch detached and wait in a separate invocation — a shared process group hands the job to your tool timeout — `docs/wave-playbook.md:738-739`
- Read tool output unfiltered (`tail`), never through a keyword grep that can swallow a traceback — `docs/accelerators.md:203-217`; DK-22
- Pass the payload the tool computed; never hand-type a path/arg into a workflow launch — `docs/wave-playbook.md` (`wave_args` step); G49
- `-j` on every build; parallelism across binaries is a different knob — `decomp-architect/corpus/decomp-kernels.md:433` (DK-33)
- Distinguish "judged and failed" from "not judged" (the gater ledgering a draft at STAGE time, skipped forever after) — `decomp-architect/templates/registry-E.decomp.md:226` (G35); `phase-ends/DIGEST.md:247` (R61)
- A rate-limited `NO-DRAFT` is a harness verdict, not a verdict on the target — `docs/how-to-ai-decomp/12-failure-museum.md` #36; `docs/accelerators.md:322`
- The agents did not have the laws file (`SYS.md` one directory below where they were told to read) — `docs/how-to-ai-decomp/12-failure-museum.md` #21; DK-39
- "No banked twin" on a card that is false of the world; rescan twins after every bank — museum #22; G44, G46
- An exclude/wall list records what the TOOLING could not do and goes stale the day the tooling improves — museum #20; G38
- The byte gate is structurally blind to LINKED library subsegs — a draft there gates GREEN while wrong — `docs/wave-playbook.md:87`; `docs/accelerators.md:310`
- A carve-config bank is RED until you re-extract, and that looks exactly like a false bank (§384) — `docs/cookbook-index.md:832`
- `match_one`/`rtu_match` compare `.text` ONLY, so a jump table is invisible to them (§405-A) — `docs/matching-cookbook.md:33099`, `:35010`
- A scan over `asm/` is a scan over UNMATCHED code only; "no banked function does X" is an empty-world answer — `docs/matching-cookbook.md:33206-33207`
- A declaration fix that only turns CC1-FAIL into DIFF has bought nothing; revert it — `docs/matching-cookbook.md:32995`
- The build is the batch verdict: one bad draft in a unit's slate fails its siblings — `decomp-architect/corpus/decomp-kernels.md:465` (DK-36)
- Difficulty is the residual class, not instruction count — route the model tier off history (§413) — `docs/cookbook-index.md:1787`
- Your own matched corpus is a labelled ground-truth corpus — mine the draft→final diff for the fix that actually worked, instead of authoring rules from prose (with the 1,062-sections-vs-13-coded-rules asymmetry and the fire-rate-by-band measurement) — `docs/decision-log.md:2624-2665`
- A shape census is symmetric and prices both polarities; re-derive the selector from the mine-vs-target residual (§406/§408) — `docs/decision-log.md:2666-2700`
- Read the recorded verdicts/journals before designing a new probe — `decomp-architect/templates/registry-E.decomp.md:166` (G24)
- A ledger's ordering/tie-break IS part of the instrument (recency sort discarding an earlier real measurement) — `decomp-architect/corpus/decomp-kernels.md:839` (DK-66)
- Pair every finding with an adversarial skeptic told to refute it — `docs/matching-cookbook.md:3708`, `:11051`; DK-43
- A byte gate is a null oracle for "is this C?" (a draft that restores its own `INCLUDE_ASM` builds identical and counts as a bank) — `decomp-architect/corpus/decomp-kernels.md:384` (DK-29)
- Extrapolating a class's yield from n=1 / the least representative member — `docs/decision-log.md:1162`; `docs/matching-cookbook.md:9316`
- A restore that prints success while its consumer sees nothing; a confident zero from a fresh scanner — `docs/accelerators.md:297-337` (#15)
- Verify a fix FIRES before reporting it landed (a fix parsing a line the tool never prints) — `docs/how-to-ai-decomp/12-failure-museum.md` #33 (R66/R68); DK-68
- Enumerate every lane that may write the tree before a fleet verification; liveness is recorded, never inferred — `decomp-architect/templates/registry-E.decomp.md:199` (G30, R54/R55)
- Harvest before the next wave, then toolify the mechanical idioms — `decomp-architect/templates/registry-E.decomp.md:285` (G45)
