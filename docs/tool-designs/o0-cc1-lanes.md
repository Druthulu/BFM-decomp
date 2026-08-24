# The -O0 and cc1 lanes — design study (ox-alpha, P31 S58, 2026-08-24)

**Provenance:** `stealth/ox-alpha` under `tools/api_agent.py`, read-only surface widened to
`config,tools,Makefile`. **DESIGN, NOT VERIFIED** — ox cannot run the build.

**Read this first — the headline claim was checked and it is HALF WRONG.**

The study says (i) the atlas's `o0-lane` lever is misclassified on the probe instance
`func_801F0A9C` @ md_SC03_076, and (ii) the real un-routed -O0 population is md_MAIN_003 (~16 fns)
and md_MAIN_011 (~20 fns), identified by gcc-2.7.2's -O0 frame-pointer signature.

Verified by grep over `asm/` on 2026-08-24:

| claim | verdict |
|---|---|
| `func_801F0A9C` / md_SC03_076 carries no frame pointer → the `o0-lane` tag is wrong for it | **CONFIRMED** — zero `$fp` anywhere under `asm/md_SC03_076/` |
| md_MAIN_003 (~16 fns) and md_MAIN_011 (~20 fns) carry the -O0 fingerprint | ~~**WRONG** — zero `$fp` in EITHER module~~ **THIS REFUTATION IS ITSELF WRONG — see the S59 addendum at the end of this file. The study's claim is CORRECT: 16 and 21 functions respectively, byte-verified.** |

`$fp` does occur in **311 files across `asm/`**, so the signature is real and greppable; those 311
are the population an -O0 lane would actually target, and they are NOT the modules named here.

So the misclassification finding stands and is useful — a lane built on the lever label would draft
the wrong functions — but **the proposed target population is fabricated and must not be used**.
Everything below is unverified beyond this table; treat each claim as a hypothesis with a named
file to check, which is how the study itself framed them.

---

ANALYSIS: the -O0 and cc1-failure lanes. Evidence-first; every claim below is anchored to a file I read.

======================================================= o0-LANE (31 grp / 69 inst / 6,564 ins)

(a) WHAT DISTINGUISHES THEM — and a misclassification finding.
Detection law (cookbook §6/§18, byte-proven): gcc-2.7.2 -O0 keeps a frame pointer, `addu $fp,$sp,$zero` = bytes 21F0A003; -O2 omits it. Grepping that signature over asm/ locates the REAL -O0 population:
  1. asm/nonmatchings/boot/* (~60 fns) — the §6 boot module. Already routed: Makefile:697 `build/src/boot.o: CC1FLAGS := â¦-O0`.
  2. asm/md_MAIN_003/â¦ (~16 fns) and asm/md_MAIN_011/â¦ (~20 fns) — whole modules carrying the fingerprint, but their splat configs (config/splat.md_MAIN_003.yaml read in full) have a SINGLE code subseg `[0xD8, c, md_MAIN_003]`, no _o0 carve, and the Makefile has no override for them. This is the un-routed bulk.
  3. Overlay clusters already handled by the P29/P30 machinery: ov_SC02_037/MAIN_012/SC03_107 `_jr_801380E0` (func_8013B568..C964), `_jr_801457A4` (func_80144B9C/A4), ov_SC03_118/119 `_jr_8017FB84`, plus lettered `_o0c/_o0e` splits — all covered by the Makefile globs WHALE_O0B_OBJS (`src/ov_*/ov_*_o0?.c`) and O0_CLUSTER_OBJS (`*_o0.c`).
THE ANCHOR IS NOT -O0. func_801F0A9C.s (read in full, 291 ins): zero `$fp` anywhere; zero 21F0A003 in ALL of asm/md_SC03_076/nonmatchings (both greps: no hits); delay slots filled with real work (e.g. `.L801F0AD0: addiu $v0,$zero,0x3` under the bne; `sll $v0,$v1,2` under beqz; `sh $v0,0x0($a0)` under j) — scheduled -O2, plus canonical -O2 switch lowering (sltiu range check + jtbl_801EF67C + sllx2 indexing). Its TU src/md_SC03_076/md_SC03_076.c sits in the one -O2 subseg of config/splat.md_SC03_076.yaml. So if the atlas tagged this group o0-lane, the tag is wrong for this instance — most plausibly it inherited the lever from a FAMILY exemplar that lives in an ov077-style -O0 TU while the member lives in an -O2 TU (exactly the situation rollout_o0.py's docstring describes; its attempt() would report this member "no-o0b"/out-of-scope rather than draft it). Per the brief's own rule, the lever name does not describe this function; treat per-instance verification (grep 21F0A003 in the .s) as mandatory before assigning the lane.

(b) CAN THE EXISTING GATE PATH BANK THEM UNCHANGED?
The gate itself (splice â `make build BINARY=<bin>` â SHA1 vs config/check.<bin>.sha) is opt-level AGNOSTIC and already honors per-object CC1FLAGS. The answer splits by sub-population:
  â¢ Boot + existing-_o0-overlay members: YES, unchanged — §18-P29 banked 9/9 on ov_SC07_010 whole-binary (R22 140/140); rollout_o0.py implements the two-file atomic append+stub-drop with restore-on-reject.
  â¢ md_MAIN_003/011: NO. No `<ov>_o0*.c` exists, so a spliced body compiles -O2 and mismatches everywhere. You cannot fix it by flipping the whole module's object to -O0: that recompiles every already-matched -O2 body in it (o0_subsplit.py docstring: "an address range is not an optimization region"), and you cannot keep before+after in one .c (§18 mid-blob constraint: one object's .text is atomic; GNU ld consumes `main.o(.text)` on first match). Required: a splat re-carve into â¥3 objects + per-object CC1FLAGS + a byte-neutral-split proof BEFORE any body lands.
  â¢ Known wall on exactly that step (§18-P29): the multi-stub cluster carve is splat-INTEGRATION-fragile — Arm A banked 9/9 on ov_SC07_010 but the same carve byte-shifted 006/007/011 (+0x20 %lo data-symbol shift, 34% of bytes, from a CLEAN build; boundaries verified real). Root cause is splat re-disassembly resolving %lo refs to a different auto-symbol when INCLUDE_ASM stubs remain in a split subseg — not the compiler, not boundary detection. This is why the fleet -O0 harvest (~1,233 members / ~0.6pp) was DEFERRED (decision-log 2026-07-16). Documented mitigation: whale shape (thin shared-header wrapper, no INCLUDE_ASM left in the split) — but that presumes matched definitions exist, which for md_MAIN_003/011 they do not yet.
  â¢ Harness gap independent of the gate: the drafting oracle is hardwired -O2 (staged .run/bakeoff/ap-opus/tu_test.sh:16 passes `-O2` to cc1; cookbook §18: "`-O0` gating â  `match_one` â¦ WRONG for -O0 functions"). Agents iterating -O0 targets against an -O2 oracle get guaranteed mismatch-everywhere feedback — the precise failure mode the lane name encodes.

(c) MINIMUM TOOLING CHANGE.
  1. Drafting oracle: add an -O0 mode to the local compile-and-diff loop — same cpp|cc1|maspsx|as chain with CC1FLAGS swapped to the Makefile's -O0 set (`-quiet -O0 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`). One flag threaded through the existing wrapper; ~10 lines.
  2. For md_MAIN_003/011 ONLY, when they become priority: run tools/o0_subsplit.py (exists, purpose-built: validates the range lies in ONE object, refuses already--O0 objects, derives contents from SOURCE anchors not asm scans — the blindness §126 warns about — forces cuts at already-banked jr boundaries, warns on missing fp prologue), then REQUIRE `make extract && make build` byte-identical as a standalone commit before any body is added; on divergence fall back to the whale shape (per-member shared headers, no stubs left in the split).
  3. Gate hygiene for -O0 banks specifically: they touch CONFIG (splat yaml + overlays.mk + Makefile), not just src/, so §97's snapshot-restore scope and §59's crash-ordering gotcha (yaml written before overlays.mk) apply — snapshot/restore must cover every file the attempt can touch.

(d) NEGATIVE CONTROLS.
  o0 (a): func_801457A4, banked in e.g. src/ov_SC03_099/ov_SC03_099_o0b.c. Move its definition into the sibling non-_o0 TU (or disable the Makefile glob) â rebuild â check.md_SC03_099.sha MUST mismatch with the first differing bytes inside func_801457A4 (fp prologue gone, schedule changed); restore â green. Proves the -O0 object is load-bearing and the gate honors per-file -O0. (Already positively proven by §18-P29's 9/9.)
  o0 (b): after o0_subsplit on md_MAIN_003 and BEFORE any C, `make extract && make build` must reproduce sha1 dd1b32ecf1103c6f7cf1943d25546a3046e17b14 exactly. Then splice a deliberately wrong -O2-styled body for func_800D0664 (a fingerprint-carrying member) into the _o0 region file: build must still link, SHA must mismatch CONFINED to that function's range (isolation proof), and a correct body must flip it green. Triple outcome (identical / confined-mismatch / identical) is the proof.
  cc1: the leftover draft itself — see below.

(e) VERDICT: BUILD THE ORACLE HALF; DO NOT RE-OPEN THE CARVE HALF FOR THESE NUMBERS.
  The already-routed sub-population needs only the -O0 oracle + running rollout_o0.py over remaining route-ready families — cheap, proven, worth it. The md_MAIN_003/011 bulk is gated behind the §18-P29 splat-integration wall that already forced a deferred 1,233-member harvest; re-opening it to chase 6.5k ins (1.3% of a ~499k frontier) risks the +0x20 image-corruption class on two more binaries for a payoff an order of magnitude below the jtbl lane (36k ins). Also: -O0 bodies are ~2x instruction-inflated, so the distinct-code content of the 6,564 is nearer ~3.3k -O2-equivalent instructions — the lane is smaller than advertised. And fix the atlas: verify 21F0A003 per instance before assigning o0-lane; this anchor fails that test.

======================================================= cc1 LANE (14 grp / 105 inst / 6,511 ins)

(a) WHAT DISTINGUISHES THEM: nothing about the FUNCTIONS — it labels a past DRAFT. All three sampled cc1-class .s are ordinary -O2 code: func_80184D24 (ov_SC04_002, 27 ins) and func_8017D8D8 (ov_SC07_009, 19 ins) — no fp, scheduled, maspsx nops only; func_801EDEAC (md_SC05_024, 10 ins) is trivial. The label records "some earlier body failed to compile", and the corpus says most such labels are noise: §149-C measured ~3,000 of ~4,000 CC1-FAIL labels carry nothing but the TU name (wrapper-only failures); §97 measured 3 of 4 CC1-FAILs in one batch were MANUFACTURED by the harness (carve-refused filed as CC1-FAIL, unchecked recoveries, stale snapshots); §65d measured the existing ladder converts 1 of 36 to compiling. Concrete mechanism visible in THIS anchor's leftover draft (.run/backlog_drafts/func_801F0A9C.c): it declares `extern s16 D_801150D4;` at file scope AND `extern u16 D_801150D4;` inside the function; common.h typedefs s16=short, u16=unsigned short — distinct types â gcc-2.7.2 hard error "conflicting types for 'D_801150D4'", exit 33 â CC1-FAIL. One mechanical decl bug in an otherwise structurally-plausible 90% draft.

(b) CAN THE EXISTING GATE PATH BANK THEM UNCHANGED? Yes — trivially, because the gate never needed to exclude them. A compiling draft banks through the normal spliceâbuildâSHA path regardless of its history; a non-compiling draft fails fast at cc1 and costs one build. The exclusion buys nothing: of the three real sub-classes, PLUMBING (decl conflicts) is already the cast_call_sites/reconcile_tu axis inside normal waves; CARVE-REFUSED is a skip class (§59(3)); DIFF-after-compile is just a normal near-miss. What must change is not the gate but the CLASSIFIER + routing: re-run classify_fail/blocker_probe over the 105 instances and redistribute (PLUMBINGânormal waves with the ladder attached; CARVE-REFUSEDâskip; DIFFânormal waves), then retire "cc1" as a wave-exclusion lever.

(c) MINIMUM TOOLING CHANGE: a pre-flight standalone cc1 pass inside the wave loop (compile the candidate body alone before splicing) so the agent receives the actual diagnostic ("conflicting types for â¦") instead of a bare CC1-FAIL verdict. The staged ap-opus/tu_test.sh already greps cc1.err for `conflict|redecl|incompat|error` — the wave harness evidently does not. ~10 lines; converts the label from a dead-end into a diagnosis. Plus the §149-C classification fix (exclude make summary lines; first real diagnostic wins; label wrapper-only failures CC1-FAIL(no-diagnostic)) if not already deployed everywhere.

(d) NEGATIVE CONTROL: the leftover draft itself. Step 1: run cc1 on it as-is â expect hard error, exit 33, "conflicting types for 'D_801150D4'" (predicted from §34/§3017 law + common.h; one command verifies — I did not execute it under this task's read-only/no-match_one mandate). Step 2: delete the inner duplicate extern block (keep file-scope), recompile â compiles; splice â whole-binary result must be DIFF, not CC1-FAIL. That transition (CC1-FAIL â DIFF on a decl-only edit) proves the classifier separates "cc1 refused" from "cc1 accepted, bytes differ" and that this record's failure was plumbing, not codegen. Honest caveat: even decl-fixed, this draft will not byte-match (e.g. case 3's anon-struct pointer indirection vs the target's direct `lh`; case 8's `(u32)(D_801150D4-1)<4` spelled on a u16 lvalue vs the target's lhuâaddiuâsltiu) — its value here is solely as the lane's control specimen.

(e) VERDICT: DO NOT BUILD A LANE. "cc1" is a symptom label with a measured noise floor (~75% wrapper-only per §149-C, ~19% harness-manufactured per §97), not a function property; every real sub-class is already served by existing lanes/tools. Building dedicated infrastructure would schedule 6,511 instructions (1.3% of frontier) into a queue whose entry criterion is a previous attempt's compiler exit code. Spend the effort on the classifier redistribution + the pre-flight diagnostic pass, and fold the survivors back into ordinary waves.

===================================== WHAT THE COOKBOOK DID *NOT* TELL US (new findings)
1. The o0-lane roster appears to contain at least one MISCLASSIFIED anchor: func_801F0A9C (this task's target) is verifiably -O2 code in an -O2 TU (no 21F0A003 anywhere in md_SC03_076's nonmatchings; scheduled delay slots; -O2 switch lowering; single-code-subseg splat config). Likely cause: lever inherited from a family exemplar that is -O0 elsewhere. Per-instance 21F0A003 verification should gate lane assignment.
2. The un-routed -O0 instruction mass is concentrated in exactly TWO whole modules (md_MAIN_003 ~16 fns, md_MAIN_011 ~20 fns) whose configs lack any _o0 carve — not spread thinly across overlays. That makes the §18-P29 wall a TWO-BINARY decision, not a fleet-wide one, which materially changes its cost/benefit versus the deferred 1,233-member estimate.
3. The Makefile's P30 widening (`_o0?` glob, line 709-717) already covers arbitrary lettered -O0 sub-splits (_o0c/_o0e exist in tree), so the o0_subsplit path needs NO Makefile change — only splat yaml + region files + the byte-neutral-split proof. The residual risk is entirely the §18-P29 splat-re-disassembly class.
4. The wave harness's drafting oracle is -O2-hardcoded (ap-opus/tu_test.sh:16), so even the already-routed -O0 sub-population cannot be iterated locally today — this, not the gate, is the binding constraint for lane (a).

---

## Addendum — S59 (2026-08-24): the census, re-measured, and the oracle half built

**The header table's second row was wrong, and the study it refuted was right.** Re-grepped over
the full tree: `asm/md_MAIN_003/` holds **16** functions with the canonical -O0 prologue and
`asm/md_MAIN_011/` holds **21** — e.g. `func_800D0C50`:

```
addiu $sp, $sp, -0x30
sw    $ra, 0x2C($sp)
sw    $fp, 0x28($sp)
addu  $fp, $sp, $zero      /* 21F0A003 */
```

Whatever grep produced "zero `$fp` in EITHER module", the bytes disagree. R40 cuts both ways: an
instrument can exonerate a subject it should have convicted. Do not act on the refuted row.

**The 311 figure must not be used as the population.** `$fp` is `$s8`, an ordinary allocatable
callee-saved register at -O2, so "files mentioning `$fp`" over-counts. Requiring the -O0 *prologue*
(`sw $fp` + `addu $fp,$sp,$zero`, both within the function's first 8 instructions) gives the real
population, out of **14,400** `.s` files under `asm/`:

| | files |
|---|---|
| mention `$fp` anywhere | 311 |
| carry the -O0 prologue | **167** |
| of those, already inside an -O0 object (`boot`, `*_o0*`) | 51 / 2,339 ins |
| **uncovered — an -O0 function the build compiles -O2** | **116 / 14,148 ins** |

Every one of these is OPEN by construction (`extract` prunes a matched function's `.s`). 14,148 ins
is more than double the atlas's `o0-lane` estimate of 6,564, and the shape is unusually favourable:

| subseg | fns | ins | replication |
|---|---|---|---|
| `md_MAIN_011` | 21 | 4,339 | — |
| `md_MAIN_003` | 16 | 1,862 | — |
| `*_jr_801380E0` | 16 | 1,289 | ×3 (ov_SC02_037, ov_MAIN_012, ov_SC03_107) |
| `*_jr_8013F350` | 2 | 849 | ×3 (same three) |
| `*_jr_8017FB84` | 10 | 459 | ×2 (ov_SC03_118/119) |
| `*_jr_801457A4` | 1 | 79 | ×4 (ov_SC07_006/007/010/011) |
| `main`/`800` | 1 | 299 | — |

29 distinct overlay functions carry 5,072 instructions of banked value once remapped across their
siblings (§40).

**The load-bearing question, answered: NO — not unchanged, and for a reason that was not in either
study.** The gate honours per-object `CC1FLAGS`, so an -O0 function can only bank from an object the
Makefile compiles -O0 (`build/src/boot.o`, `ov_SC01_077_o0.o`, `WHALE_O0B_OBJS` =
`src/ov_*/ov_*_o0?.c`, `O0_CLUSTER_OBJS` = `src/ov_*/ov_*_o0.c`). **No glob matches `src/md_*/`
at all**, so the md_MAIN_003/011 bulk needs a Makefile rule as well as a carve. That part of the
study's verdict (e) stands: the carve half sits behind the §18-P29 splat-integration wall.

**The oracle half is now built, and the gap was worse than described.** The study said the drafting
oracle is hardwired -O2 and cited a staged bakeoff script. The live path is worse: `match_one --o0`
has existed all along, and **nothing ever passed it** — `api_draft.match_one()`, the oracle every
wave agent iterates against, builds a fixed argv without it. So every agent handed any of these 167
targets, *including the 51 already sitting in -O0 objects*, was shown an -O2 compile of its own C
and a mismatch on every instruction: feedback that cannot converge, for a reason invisible in the
diff. `match_one` now derives the opt level from the target itself (R33) — the prologue tell, OR the
subseg being an -O0 object, two oracles because neither alone covers `boot/start.s` (built -O0, no
ordinary prologue) or an -O0 function stranded in an -O2 subseg. `--no-auto-o0` overrides.
It also prints a standing warning on that stranded class: a MATCH there cannot bank until the
function is carved. `tools/test_o0_detect.py` is the control: 167/167 covered, 0 false positives
outside -O0 objects, and the two `md_MAIN_011` files whose `.s` opens with a jump table / `.asciz`
blob are detected — they are why the scan is anchored at `glabel` rather than at the top of the file.

**Recommended order** (unchanged in spirit from verdict (e), now with the numbers): run
`rollout_o0.py` over the already-routed families with the fixed oracle first — that is the 51
covered functions plus whatever the ×2/×3/×4 replication reaches — before deciding whether the
md_* carve is worth the wall.
