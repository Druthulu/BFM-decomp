# tools/MANIFEST.md — the source project's portable tools, by ladder phase, as tasks

> **What this is, and what it is not.** The kit installs no tools (its README says so). This manifest lists every tool the
> source project built, grouped by the phase of the ladder in `intake.decomp.md` Part B that needs it, with one line on
> what it does and one on what it hard-codes. **Until the source project's tools are de-specialised and split out, each
> row is a task for that phase:** build the tool for your target from its description, using the source project's file
> (named by its file name) as the reference implementation. Rows whose hard-codes read "none" or name only the
> instruction set are copy-after-the-split candidates; rows that hard-code the source repository's layout, its compiler
> triple or its platform SDK need the marked adaptation. The last table lists the tools that are project-only in code
> (their *shape* is a Phase-1/2 task; their code does not transfer).
>
> **Coverage (a read-only survey on 2026-09-07):** 325 tool files classified of 325 found under the source project's
> `tools/` (top-level 266, lanes 19, disassembler scripts 12, the extractor package 11, the history-rewrite package 10,
> the permuter wrappers 3, the signature tool 3, an oracle 1); submodules, vendored third-party code, the vendor SDK, the
> reference compiler sources and downloaded binaries are excluded and not listed. Per phase: P1 2 · P2 26 · P3 17 ·
> P4 9 · P5 32 · P6 59 · P7 25 · P8 102 · P9 25 · P10 12 · project-only 16. *TODO(platform): the MIPS and PlayStation
> SDK hard-codes are the ones another platform replaces first.*

## P1 — extraction + manifest

| Tool | What it does | Hard-codes |
|---|---|---|
| `iso9660.py` | Reusable reader for a raw 2352-byte-sector data track; walks the filesystem and extracts files by name | none |
| `manifest.py` | Builds and verifies a deterministic sorted SHA1 manifest of an extraction tree | the extraction output root |

*The extractor itself, the container and compression decoders and the disc-completeness partition are project-only in code
(last table) and Phase-1 tasks in shape: a deterministic walker over the medium, a decoder implementing the GAME's
semantics with a length cross-check, a committed manifest, and a partition that accounts for every byte of the medium.*

## P2 — the oracles + the load map

| Tool | What it does | Hard-codes |
|---|---|---|
| `ghidra_mcp_start.sh` | Starts the headless disassembler MCP server detached on a fixed local port | repo paths, project name, port |
| `ghidra_mcp_stop.sh` | Clean save-and-close via a sentinel file; the only persistence event | repo paths, project name |
| `ghidra_mcp_verify.sh` | Read-only re-open confirming a symbol edit actually persisted after save-shutdown | repo paths, project name |
| `ghidra_import.sh` | Headless import and auto-analysis of a console executable with the platform loader | PS1 executable loader, project name |
| `ghidra_import_raw.sh` | Headless import of a flat headerless blob at a given base with the right processor spec | PS1 processor spec, project name |
| `ghidra_rebuild.sh` | Rebuilds one analysis program from committed text plus extracted bytes, and proves equality | repo paths, project layout |
| `ghidra_export_annotations.sh` | Read-only export of a program's annotations to byte-stable line-delimited JSON | repo paths |
| `ghidra_annotations_delta.py` | Derives the hand-authored annotation rows by subtracting a fresh rebuild baseline | repo paths |
| `ghidra_roster.py` | Generates and checks a roster of committed analysis programs from the build registry | repo config paths |
| `prefetch_fleet.py` | Batch headless decompilation of one representative per distinct open class into a cache | repo paths, binary registry |
| `ram_probe.py` | Captures, diffs and reads emulator main RAM over its web API for field typing | emulator host/port, 2 MB console RAM map |
| `find_addr_refs.py` | Register-tracked scan for code that materializes an absolute address; never window-paired | MIPS encodings, repo binary registry |
| `payload_base_evidence.py` | Ranks candidate load addresses for an unonboarded payload from pointers, self-calls and upper-half reach | the source game's payload map |
| `split_indicator.py` | Names code segments that must be split before their switch functions can be sectioned | repo config layout |
| `main_seed_ends.py` | Emits function start/length seeds for the executable's game-code objects, derived from the build | repo build paths |
| `BfmMcpServer.java` | The headless MCP server itself; holds an open transaction and saves on a sentinel stop | repo sentinel path, server port |
| `DecompileAt.java` | Headless script decompiling the function at one address and printing its C | default address |
| `DecompileFunctions.java` | Headless batch decompile of an address list into one C file per function | none |
| `DefineFunctions.java` | Disassembles and creates functions at externally validated entry points listed in a file | repo scratch path |
| `DumpFunctionSignatures.java` | Read-only per-function fingerprint dump in three hash tiers for cross-binary correspondence | none |
| `DumpProgramInfo.java` | Prints program metadata: language, compiler spec, image base, function count, properties | none |
| `ExportAnnotations.java` | Read-only serialization of types, signatures, data, comments, bookmarks and labels to stable JSONL | none |
| `ExportSymbols.java` | Exports user-defined symbols to a committable text file so annotations are version-controlled | none |
| `GetSymbolAt.java` | Prints the function or symbol name at one address for scripted persistence checks | none |
| `ImportAnnotations.java` | Idempotent compare-before-write import of the annotation JSONL back into a program | none |
| `ImportPsyqGdt.java` | Headlessly resolves a vendor SDK type archive into the program's type manager | PS1 SDK type archive name |

## P3 — the all-assembly baseline

| Tool | What it does | Hard-codes |
|---|---|---|
| `new_binary.sh` | One-command onboarding of any flat blob: config from template, registry entry, first build | repo config/template paths, the source game's payload classes |
| `mk_write.py` | The only safe writer of the generated binary-registry makefile; validates before replacing | repo config path |
| `gen_lib_subsegs.py` | Generates segment lines and a stub list for a multi-block vendor library region | repo config layout, PS1 SDK libs |
| `ld_interleave.py` | Reorders a generated linker script to reproduce the original section interleaving | repo build paths |
| `split_src_region.py` | Splits a source file at object boundaries, preserving matched code and stub blocks | repo src/config layout |
| `reorder_passthrough.py` | Restores the assembler-reorder build path for the objects originally assembled that way | pinned assembler flags, repo build paths |
| `verify_binary.py` | The correct hand verification of one binary: full re-extract plus rebuild, then hash compare | repo make targets |
| `psyq_lib_split.py` | Splits a vendor linker-format library archive into its member objects | PS1 SDK archive format |
| `psyq_build_libs.sh` | Converts vendor library members to ELF and archives them per library | PS1 SDK, repo scratch paths |
| `psyq_identify.py` | Locates where vendor library objects are linked in a target image via relocation-masked patterns | PS1 SDK objects |
| `psyq_link.py` | Links one vendor object at a fixed address so its code is byte-identical to the target | PS1 SDK, repo build paths |
| `psyq_link_lib.py` | Driver linking every used object of a library and byte-verifying each | PS1 SDK, repo paths |
| `psyq_link_region.py` | Links a whole library's objects in place of stubs, placing non-code sections as no-load | PS1 SDK, repo paths |
| `psyq_integrate.py` | Wires real library objects into the split build, replacing stub subsegments | repo config/build paths |
| `psyq_bss_probe.py` | Asks whether an object's scattered zero-init section can be split and placed byte-exactly | PS1 SDK object shape |
| `psyq_bss_split.py` | Rewrites an ELF object, splitting one zero-init section into per-base no-bits pieces | ELF32 REL layout |
| `psyq_libs_from_disc.py` | Extracts vendor SDK library files from the vendor's runtime-library disc image | vendor disc layout, PS1 SDK |

## P4 — the compiler pinned; the probes

| Tool | What it does | Hard-codes |
|---|---|---|
| `match_one.py` | Compiles one function standalone with the pinned toolchain, masks relocations, compares to target bytes | compiler triple, repo build flags |
| `masked_diff.py` | Shared relocation-masked instruction comparison used by the matcher and the permuter scorer | MIPS relocation encodings |
| `rtu_match.py` | Splices a candidate into a copy of the real translation unit and checks the same bytes | repo src layout, compiler triple |
| `rtu_second_chance.py` | Re-judges standalone compile-failures against their real translation unit before dropping them | repo scratch paths |
| `decompile.py` | Wrapper locating a function's disassembly and running the C-scaffold generator on it | repo asm paths, decompiler target name |
| `decompme_replica.sh` | Runs a function through an external reference toolchain build and compares words against the target | pinned toolchain versions, network fetch |
| `cc1_dumps.sh` | Dumps every compiler pass file for a self-contained draft into a private directory | compiler triple, repo scratch paths |
| `cc1_dumps_tu.sh` | Same pass dumps for the spliced real translation unit, the faithful compile | absolute repo path, compiler triple |
| `draft_prechecks.py` | Static pre-checks that skip a draft doomed to fail before any compile is spent | repo symbol/config sources |

## P5 — the census, the harness, the reports

| Tool | What it does | Hard-codes |
|---|---|---|
| `corpus.py` | The single derived model of the source tree: open, matched or shared, per function | repo src/config layout |
| `audit_digest.py` | Recomputes headline metrics from the current tree and fails if the committed digest disagrees | repo docs paths |
| `audit_frontier.py` | Checks that the independent "what remains" views agree with the corpus oracle | repo paths |
| `audit_binaries.py` | Gate asserting every consumer knows about each newly onboarded binary | repo config/registry paths |
| `audit_header_sigs.py` | Finds shared-header declarations that contradict the banked definition | repo shared-header paths |
| `audit_text_sources.py` | Every tracked C source must be plain text, or text searches silently skip it | repo src paths |
| `difficulty.py` | Ranks unmatched functions easiest-first by size, control flow, table presence and call count | repo asm layout |
| `dup_report.py` | Reports byte-identical and structurally identical function groups within and across binaries | repo signature files |
| `burndown.py` | Tracks per-session yield and velocity so a diminishing-returns close is visible | repo ledger paths |
| `backlog.py` | Near-miss ledger: every close-but-not-matching attempt, ranked for hand sessions | repo scratch/doc paths |
| `worklist.py` | Joins the target pool and the near-miss ledger into one byte-weighted ranked queue | repo scratch paths |
| `strand_census.py` | Lists every draft already on disk whose function is still open, with its blocker | repo scratch paths |
| `frontier_classify.py` | Classifies every remaining open function by its true blocker, deterministically | repo paths |
| `atlas.py` | Partitions all open functions into exactly one lever-labelled work group | repo scratch paths |
| `atlas_features.py` | Extracts one deterministic feature record per function across all registered binaries | repo signature files |
| `wall_taxonomy.py` | Census-classifies every unmatched residual by blocker class to size each avenue | canonical source binary name |
| `wall_sweep.py` | Enumerates fleet-wide instances of one known assembler-level blocker class | repo asm layout, toolchain quirk |
| `plumbing_groups.py` | Groups recorded declaration-conflict failures into sweepable work groups from the ledgers | repo ledger paths |
| `blocker_probe.py` | Read-only two-oracle explanation of why a byte-correct draft fails the whole-binary gate | repo build paths |
| `symcheck.py` | Pre-gate guard diffing the symbol set a draft references against the target's | repo build paths |
| `reloc_identity.py` | Disagreeing oracle checking the symbol identity the masked comparison deliberately hides | repo build paths |
| `reloc_verify.py` | Resolves every relocation in a draft and compares the resolved words to the target | repo build paths |
| `oracle_reorder.py` | Decides whether a near-miss residual is a source defect or an assembler artifact | pinned assembler flags |
| `rtu_shadow.py` | Runs the real-translation-unit check in shadow beside the gate to measure gate inversion | repo scratch paths |
| `ab_score.py` | Re-scores every draft of two experiment arms with the standalone matcher as ground truth | repo scratch paths |
| `p16_improve.py` | Known-answer loop: reverts matched functions to stubs and measures the real pipeline | repo src/build paths |
| `p16_known_answer.py` | Graduated known-answer validation of the scaffold pipeline across difficulty bands | repo paths |
| `stub_invariant_audit.py` | Negative control: for every stub the built object must equal the target assembly exactly | repo build paths |
| `test_jtbl_parse_config.py` | Regression plus negative control for the table-carve configuration parser | repo config fixtures |
| `test_o0_detect.py` | Negative control for the matcher's optimization-level auto-detection | repo paths |
| `test_reconcile_ledger.py` | Targeted proof of the propagation ledger guard the full control never exercised | repo paths |
| `test_residual_class.py` | Synthetic hand-encoded unit tests for the deterministic residual classifier | MIPS encodings |

## P6 — the multipliers: signatures, dedup, families, the reconcile ladder, the carve chain

| Tool | What it does | Hard-codes |
|---|---|---|
| `sig_image.py` | Disassembler-free per-function signer for a flat image at a known base, field-identical to the dumper | MIPS encodings, repo scratch paths |
| `sig_unify.py` | Unifies a draft's callee externs and its own definition signature to the banked-canonical set | repo shared-header paths |
| `xsig.py` | Relocation-masked per-function signatures for cross-project code identification | MIPS/relocation model only |
| `test_xsig.py` | Property tests for the signature tool on committed fixtures, needing no compiler | fixture paths |
| `make_fixtures.sh` | Regenerates the signature-tool fixtures with the pinned toolchain | compiler triple, repo tool paths |
| `match_protos.py` | Joins per-function signature dumps of two related builds into a function correspondence | repo signature files |
| `dedup_integrate.py` | Byte-honesty validator for the code-share registry; fails closed on signature drift | repo config registry path |
| `dedup_propagate.py` | Lifts one matched body into a shared macro and instantiates it at every duplicate site | repo shared-header/src layout |
| `dedup_extend.py` | Extends the existing share registry to newly onboarded binaries | repo config/src layout |
| `inject_capped_externs.py` | Frees high-reach inline matches skipped as not self-contained by injecting their file-scope externs | repo shared-header layout |
| `restore_dropped_decls.py` | Puts back file-scope declarations a share propagation deleted with the body | repo src layout |
| `macro_draft.py` | Materializes a shared macro body back into a compilable standalone draft | repo shared-header layout |
| `demacroize.py` | Per-binary local escape from a shared-header declaration conflict by unmacroizing one body | repo shared-header layout |
| `exemplar_miner.py` | Routes every residual stub to its lever and ranks the highest-reach work | census file paths, canonical source binary |
| `exclude_audit.py` | Classifies every exclude-list entry by its current blocker and regenerates the list | repo config path |
| `family_hseq.py` | Ranked clustering of the unmatched frontier by mnemonic-skeleton hash | repo signature files |
| `family_manifest.py` | Ranked structural-family target manifest naming the one exemplar to draft per family | repo signature files |
| `family_cousins.py` | Similarity clustering one tier looser than exact skeleton hashing over the open frontier | repo signature files |
| `family_remap.py` | Mechanically remaps a matched exemplar's C onto a structural sibling by positional symbol pairing | repo src layout |
| `family_align.py` | Length-tolerant aligned classifier plus the mechanical constant-expansion engine for drifted members | repo scratch paths |
| `family_sweep.py` | Sweeps a matched exemplar across every same-structure sibling, gate-arbitrated | repo src/config layout |
| `twin_sweep.py` | Banks every open stub that has an already-banked structural twin, for near-zero tokens | repo signature files |
| `twin_rescan.py` | After a bank, reports which open stubs just became mechanical remaps instead of drafts | repo signature files |
| `bank_exemplar.py` | Banks one cracked exemplar through the carve, splice and staged-recovery ladder | repo src/config layout |
| `aprop_autodraft.py` | Mechanically drafts a family member from the seed body plus a positional symbol rebase | repo scratch paths |
| `aprop_symfix.py` | Rebases stale seed symbols in a mechanically adapted draft onto the target's own symbols | repo symbol/config sources |
| `weave_sweep.py` | Applies one known prologue-scheduling lever everywhere the bytes say it belongs | repo src layout, compiler behaviour |
| `cdecl.py` | The single recursive-descent C declarator parser every declaration tool shares | C89 grammar only |
| `canon_draft_decls.py` | Canonicalizes a draft's extern and data declarations to the banked-consistent set | repo shared-header paths |
| `canon_resident_calls.py` | Rewrites address-named calls in a draft to the curated symbol name when one exists | repo symbol file path |
| `conform_decls.py` | Conforms every declaration of a function fleet-wide to its byte-true definition | repo src/shared-header layout |
| `gen_engine_decls.py` | Declares every shared function and data symbol once, canonically, in a generated header | repo shared-header path |
| `decl_from_use.py` | Infers a minimal extern for a data symbol a draft uses but its destination does not declare | repo src layout |
| `decl_prior.py` | Computes the fleet's consensus declaration for every symbol, as card fuel | repo src layout |
| `sync_tu_decls.py` | Banks a refused draft by copying the destination unit's own declarations into it | repo src layout |
| `normalize_self_decls.py` | Normalizes a function's own declaration when a templated definition lands in a new unit | repo src layout |
| `reconcile_slate.py` | Drives a whole batch to declaration-compatible before any rebuild is spent | repo src layout |
| `reconcile_tu.py` | Conforms a draft's data declarations to what the destination translation unit can actually see | repo src layout |
| `fix_arity_callers.py` | Repairs the shared-caller argument-count conflict for the no-prototype failure class | repo shared-header layout |
| `fix_header_decl.py` | Rewrites a shared-header caller declaration to a draft's byte-true signature | repo shared-header path |
| `fix_decl_mirror.py` | Binds a void definition to its symbol when the destination declares a value return | repo src layout |
| `fix_tu_ret_decls.py` | Retypes a binary's own stale forward declarations to a draft's byte-true return, revert-on-fail | repo src layout |
| `cast_self_callers.py` | Lets a unit keep calling, through a per-site cast, the function it is about to define | repo src layout |
| `scope_data_externs.py` | Places a templated body's data externs at the scope the destination unit can accept | repo src layout |
| `scope_tu_externs.py` | Moves a unit's own file-scope data externs down into their consumers to legalize a block-scope type | repo src layout |
| `scope_demote_drafts.py` | The scope-demote step, wired as a rung of the recovery ladder | repo src layout |
| `jtbl_carve.py` | Sets up the read-only-data carve for a binary's matched jump-table functions | repo config/build layout |
| `jtbl_rodata_pads.py` | Post-assembler filter reproducing the original inter-table padding in a multi-table carve | compiler/assembler behaviour, repo build paths |
| `jtbl_pads_fix.py` | Repairs a stale padding spec by search plus byte proof, never by guessing | repo config layout |
| `jtbl_family_bank.py` | Banks a matched jump-table exemplar across its structural siblings, revert-on-fail | repo config/src layout |
| `pads_audit.py` | Derives each object's padding spec from the bytes instead of searching for it | repo build/config layout |
| `interleave_check.py` | Asserts the carve interleave order equals the segment sequence, position by position | repo config layout |
| `jr_isolate.py` | Isolates one switch function into its own code segment for an independent table carve | repo config/src layout |
| `jr_isolate_all.py` | One-shot multi-cut resegment isolating every switch function in a binary | repo config/src layout |
| `overlay_src_split.py` | Comment-state-aware partition of a source file, the oracle for the split chain | repo src layout |
| `o0_detect.py` | The single place that answers whether a function was built unoptimized, from its prologue | compiler prologue shape |
| `o0_boundary.py` | Finds and banks unoptimized functions stranded at the end of an unoptimized region | repo config layout |
| `o0_subsplit.py` | Routes an unoptimized address range that sits inside an otherwise optimized object | repo config layout |
| `rollout_o0.py` | Generalized two-file atomic rollout of an unoptimized definition across every binary carrying it | repo src/config layout |

## P7 — the codegen map, the dumps, the permuter

| Tool | What it does | Hard-codes |
|---|---|---|
| `gccmap_cites.py` | Tags every compiler-source citation in the codegen-map docs with the tree it refers to | repo doc/reference paths |
| `sweep_citations.py` | Deterministically localizes every compiler-source citation in a document against the pinned sources | repo reference tree paths |
| `verify_map_findings.py` | Machine-checks a codegen-map audit's findings against the actual compiler sources | repo reference tree paths |
| `reg_renumber_swap.sh` | Mechanized oracle separating a register-allocation swap from a scheduling reorder | compiler triple, repo scratch paths |
| `alloc_table.py` | Prints each pseudo's refs, live length, block and allocation priority from compiler pass dumps | compiler pass-dump format, repo dump root |
| `ghost_census.py` | Frame-residue oracle: finds pseudos with references but no remaining occurrences, and their slots | compiler pass-dump format |
| `autopsy.py` | Materializes the residual corpus by recompiling every open draft and classifying its failure | repo scratch/build paths |
| `residual_class.py` | Deterministic decoder-based classifier mapping a residual to a named codegen class | MIPS encodings |
| `residual_rules.py` | Turns a measured residual into the specific documented lever that addresses it | repo doc paths |
| `residual_rules_b.py` | Independent second implementation of residual-shape to rule classification, for head-to-head | repo doc paths |
| `diff_regions.py` | Classifies where a remapped member's compiled bytes diverge from its target | repo build paths |
| `diff_autopsy.sh` | Reproduces exactly what the gate saw, then decodes the diverging words and restores the tree | repo src/build paths |
| `main_diff_locate.py` | Turns a red whole-binary result into a named list of divergent symbols | repo build/config layout |
| `len_tells.py` | Classifies a length-drift near-miss against its own target and builds the routing card | repo scratch paths |
| `lenmiss_route.py` | Routes the length-drift near-miss pile through the documented lenses, re-verified against the tree | repo scratch paths |
| `masked_scorer.py` | Drop-in permuter scorer scoring true relocation-masked code closeness instead of mnemonic diff | permuter internals, repo module paths |
| `run_masked.py` | Runs the permuter with the masked scorer rebound before its entry point, without patching it | permuter internals, repo module paths |
| `compile.sh` (permuter) | The permuter's compile command, mirroring the build rule exactly so objects are build-faithful | compiler triple, repo build flags |
| `compile_o0.sh` (permuter) | Unoptimized variant of the same permuter compile command | compiler triple, repo build flags |
| `p16_permute.py` | Per-function permuter driver building base, target and settings, then reporting closeness | repo scratch paths, permuter layout |
| `permuter_weights.py` | Directs permuter mutation toward the lever family the residual class implies | permuter settings format |
| `permuter_ils.py` | Iterated-local-search wrapper warm-restarting the permuter from the best waypoint each cycle | permuter layout, repo scratch paths |
| `permuter_sweep.py` | Hands a batch's near-misses to the permuter, but only the ones worth the CPU | repo scratch paths |
| `grinder.py` | Token-free permuter daemon grinding the closest near-misses and banking through the gate | repo scratch paths |
| `warmstart.py` | Feeds the permuter warm-start drafts built from banked exemplars and routed fuel | repo scratch paths |

## P8 — the campaign: cards, lanes, gates, recovery, harvest

| Tool | What it does | Hard-codes |
|---|---|---|
| `claude_wave_packs.py` | Builds the per-function prompt packs an agent wave drafts from | repo scratch paths, agent harness |
| `journal_notes.py` | Mines per-function past-attempt notes out of the agent journals into card fuel | agent transcript paths |
| `seed_ref.py` | For an open stub, finds the already-banked body that matches it, including near and contained tiers | repo signature files |
| `neighbor_ref.py` | For an open stub, ranks already-matched functions worth reading as worked examples | repo signature files |
| `wave_card_fuel.py` | The single library computing the per-target card fuel a pack carries | repo scratch paths |
| `t5_cards.py` | Builds the card fuel for one wave's own targets, keyed correctly per binary | repo scratch paths |
| `t5_targets.py` | Draws one routed slate from the frontier classes | repo scratch paths |
| `t5_distill_args.py` | Builds the post-wave distillation slate from a wave's directories | repo scratch paths |
| `t5_bank.sh` | Post-draft half of an agent wave: refuse if unsafe, judge each arm, bank the union | repo paths, lane conventions |
| `t7_bank.py` | Batch banking driver applying reconcile-at-bank-time plus the whole-binary gate | repo src/config layout |
| `draw_waves.py` | Draws several drafting waves off the open frontier, cheapest-first | repo scratch paths |
| `build_wave.py` | Builds the next wave from a card pool, ranked by fleet leverage | repo scratch paths |
| `build_wave_atlas.py` | Builds a wave from the frontier atlas, optimized for gate throughput | repo scratch paths |
| `build_wave_args.py` | Emits workflow arguments for a wave from the target manifest, resolving each path | repo asm/scratch layout |
| `wave_args.py` | Emits the exact workflow arguments for a wave, asserting every target is open | repo scratch paths |
| `wave_targets.py` | Selects a worker-wave target batch from the target manifest with cache filters | repo scratch paths |
| `wave_snapshot.py` | Gives a wave its own immutable copy of the disassembly files its agents read | repo asm paths |
| `wave_judge.py` | Per-arm whole-binary gate with tree reset between arms, then gates the best-of union | repo scratch/src layout |
| `build_fuel_manifest.py` | Unifies live stubs into one ranked, class-tagged, cache-annotated target pool | canonical source binary, repo scratch paths |
| `gen_harvest_targets.py` | Generates a callee-signature-aware target manifest with per-function fleet reach | canonical source binary, repo paths |
| `validate_targets.py` | The validity gate every target list must pass before agents are spawned | repo scratch paths |
| `launch_check.py` | Refuses to launch an agent at a target that is already banked | repo src layout |
| `lane_inflight.py` | The authoritative ledger of which drafting agents are currently live | repo scratch paths |
| `work_evidence.py` | Assertions that a tool actually did the work it reports | repo scratch paths |
| `campaign_status.py` | One status view covering every lane, not only the loud one | lane names, repo scratch paths |
| `triage_ladder.py` | Zero-token pass deciding whether a target needs an agent at all, before and after drafting | repo scratch paths |
| `gap_triage.py` | Pre-filters a wave's knowledge-gap reports against the existing documentation | repo doc paths |
| `fragment_check.py` | Refuses drafts that subsume a neighbouring symbol, the enclosing-function trap | repo asm layout |
| `gate_stage.py` | The shared deterministic recovery, gate and log ladder every producer calls | repo src/config layout |
| `gate_lane.py` | The wave gate driver, accepting either result shape and an explicit draft path | repo scratch paths |
| `gate_wave.py` | Gates a whole wave by splitting table-bearing drafts off and running both lanes concurrently | repo scratch/config layout |
| `gate_triage.py` | Routes a gate result set to the repair tool its own verdict names | repo scratch paths |
| `gate_main.py` | Gates a batch of executable drafts the only trustworthy way: a clean rebuild with bisect | repo build/make targets |
| `gate_main_parallel.py` | Discovers the executable's bankable drafts concurrently, then banks them once, serially | repo build/make targets |
| `parallel_gate.py` | Gates many binaries concurrently in isolated worktrees and merges only the passers | repo worktree/build layout |
| `sweep_parallel.py` | Gates pre-staged draft directories across distinct binaries in parallel | repo scratch paths |
| `gater_lane.py` | Continuous gater draining a wave's finished drafts into the parallel gate, grouped by binary | repo scratch paths |
| `harvest_verify.py` | The whole-binary byte gate: substitute, build, keep only if identical, else revert | repo src/build layout |
| `pregate_check.py` | Validates a batch without building it, in seconds instead of minutes | repo src layout |
| `restage_matching.py` | Re-stages only the drafts that compile and match in their real unit, so one failure is isolated | repo src layout |
| `bisect_slate.py` | Isolates the byte-wrong drafts in a batch, with a null control first | repo build paths |
| `blast_radius.py` | Measures a change's write set and names the verification it actually requires | repo tree layout |
| `r22_verify.sh` | Exclusive clean-tree fleet verification that also clears deferred-check debt | repo make targets |
| `verify_worktree.py` | Checks a commit into its own worktree, provisions build deps, and verifies it there | repo worktree/build layout |
| `shared_lock.py` | One reader/writer lock over the shared source state for concurrent lanes | repo lock paths |
| `treelock.sh` | The mutex wrapper for tree-writing campaigns, with status and stale detection | repo lock paths |
| `jtbl_lane.py` | Carve, draft and bank lane for jump-table functions, with the carve deliberately outside it | repo config/src layout |
| `main_lane.py` | The executable's own draft, gate and commit cadence beside the other lanes | repo build/make targets |
| `main_queue_rebuild.py` | Rebuilds the executable lane's queue from the tree, never from a stale list | repo src layout |
| `integration_resolver.py` | Zero-token lane re-judging drafts that are already byte-correct and banking them | repo scratch paths |
| `scan_leftovers.py` | Re-verifies every draft already on disk and banks the free wins | repo scratch paths |
| `recover_drafts.py` | Recovers agent-written draft files from a run's transcripts after they were deleted | agent transcript paths |
| `agent_drafts_restore.py` | Replays an agent's writes from its transcript to rebuild its final deliverable | agent transcript paths |
| `agent_reports.py` | Saves each subagent's full final prose report to one file per target | agent transcript paths |
| `agent_verdicts.py` | Pulls the final structured verdict out of subagent transcripts | agent transcript paths |
| `transcript_dump.py` | Condenses a session transcript into readable text for a successor session | agent transcript paths |
| `recover_rejects.py` | Turns pre-gate rejects back into bankable drafts for zero model tokens | repo scratch paths |
| `recover_route.py` | Given a drop verdict, names the one recovery tool that actually applies | repo scratch paths |
| `recover_giant.py` | Canonical-extern recovery for a large draft rejected only on declaration plumbing | repo shared-header layout |
| `recover_integration.py` | Batch integration recovery driver over a wave directory of correct-but-rejected drafts | repo scratch/src layout |
| `bulk_harvest.py` | Phase-separated bulk drafting plus a parallel gate farm, for throughput | repo scratch paths, GPU endpoint |
| `lora_grind.py` | Mass-run driver rotating binaries, drafting small stubs with a served model, gating, propagating | repo scratch paths, model endpoint |
| `orchestrator.py` | The deterministic half of the unattended loop: pick the pool, emit the batch, record the cycle | repo scratch paths |
| `auto_driver.py` | Autonomous model-free driver looping a stub worklist through scaffold, draft and gate | canonical source binary, repo paths |
| `auto_supervisor.sh` | Keeps an unattended driver alive across crashes until a clean or requested exit | repo scratch paths |
| `auto_stop.sh` | Requests a safe exit of the unattended run via a stop sentinel | repo scratch paths |
| `auto_status.sh` | Prints the unattended run's heartbeats and recent progress for a remote check-in | repo scratch paths |
| `ox_campaign.py` | The unattended wave loop: draw, draft, pre-filter, gate, commit, ledger, repeat | repo scratch paths, provider config |
| `api_agent.py` | Gives an external chat model the same multi-turn tool harness an agent gets | provider endpoint, repo doc paths |
| `api_draft.py` | Provider-agnostic single-shot drafting worker against any chat completions endpoint | provider endpoint, repo doc paths |
| `api_rate.py` | Reports measured request rate and rate-limit attribution from append-only telemetry | repo telemetry path |
| `glm_parallel.sh` | Splits a target list into slices and runs concurrent drafting workers against one endpoint | provider endpoint, repo paths |
| `glm_reconcile.py` | Aims a reasoning model at the declaration wall and captures its reasoning for reuse | provider endpoint, repo paths |
| `idiom_harvest.py` | Pulls the newly learned idioms out of a wave's shard logs into candidate notes | repo log paths |
| `idiom_hunt.py` | Uses a reasoning model on grouped near-misses to discover new compiler idioms | provider endpoint, repo paths |
| `idiom_loop.py` | Never-ending meta-loop: drain the easy fuel, learn the next idiom, hand off | repo scratch paths |
| `idiom_serial.py` | The serial idiom-learning lane where each step inherits what the previous learned | repo scratch paths |
| `distill_scan.py` | One pass of the distillation lane deciding which harvested waves still need mining | repo scratch paths |
| `export_pairs.py` | Mines gate-verified assembly-to-source pairs into a fine-tuning corpus | repo src/build layout |
| `format_finetune.py` | Turns the mined pairs into a chat-template instruction dataset | dataset paths, model chat template |
| `train_lora.py` | Fine-tunes a code model into a matching specialist and saves the adapter | dataset paths, training venv |
| `eval_lora.py` | Gate-true evaluation of a fine-tuned model on held-out banked functions | dataset paths, repo corpus |
| `serve_local.py` | Serves the fine-tuned model locally behind a chat-completions endpoint | training venv, GPU assumptions |
| `bounce_drafter_on_queue.sh` | Waits for the in-flight wave to queue, then restarts the drafting process | lane script paths |
| `campaign.sh` | Dual-pool campaign lane: two drafting pools, one serial gate | provider config, repo paths |
| `distill.sh` | The distillation lane, running beside drafting and never in front of it | repo scratch paths |
| `drafter.sh` | The drafting lane that must never stop; touches only scratch state | repo scratch paths, provider config |
| `elastic.sh` | Spends spare provider capacity on extra work when the main lane cannot | provider config, repo paths |
| `forever.sh` | Keeps the wave campaign running indefinitely across caps and crashes | repo scratch paths |
| `gater.sh` | The restartable gating lane, safe to kill and relaunch at any time | job count, repo paths |
| `grinder_lane.sh` | Runs the model-free permuter grinder beside a saturated gater | repo scratch paths |
| `launch_ox.sh` | Launcher for a sharded campaign run with a tag and shard count | provider key file, repo paths |
| `main.sh` | The executable's own lane loop, on its clean-rebuild cadence | repo make targets |
| `maintenance.sh` | The maintenance lane running the free recovery and re-judgement passes | repo scratch paths |
| `relaunch_drafter_shell.sh` | Waits for a wave to queue, then restarts the drafting lane's shell so new arguments apply | lane script paths |
| `resolver_lane.sh` | The zero-token resolver lane: re-judge, verify twice, stage, gate, commit | repo scratch paths |
| `restart_gater_when_idle.sh` | Restarts the gating lane's shell once the current gate finishes | lane script paths |
| `restart_main_lane_when_idle.sh` | Restarts the executable lane's shell at its one safe boundary | lane script paths |
| `sibling_lane.sh` | The free sibling lane driving structural sweeps with synthesized declarations | repo paths |
| `stallguard.sh` | Detects and repairs lane stalls on measured conditions every minute, logging each action | lane names, repo paths |
| `toolwork.sh` | Runs tooling-design briefs against an external model with build config as context | provider config, repo paths |
| `wait_distill.sh` | Blocks until the distillation lane raises the next batch, then exits | repo scratch paths |

## P9 — publish

| Tool | What it does | Hard-codes |
|---|---|---|
| `verify_contract.sh` | The recorded end-to-end verification run of the byte-identity contract, step by step | repo make targets, output dir |
| `bootstrap.sh` | Idempotent fresh-clone setup: check packages, create environments, fetch pinned tools | repo layout, package names |
| `fetch_psyq.sh` | Optional acquisition and checksum verification of vendor SDK pieces for the linked build | PS1 SDK sources, repo paths |
| `compile_only.py` | Compiles every eligible translation unit with the pinned toolchain, without any game bytes | compiler triple, repo makefile parsing |
| `audit_public.py` | The first-push gate: no derived bytes among tracked files, four independent checks | repo purge-set and path lists (the kit's template reads `config/firewall.txt` instead) |
| `progress.py` | Computes and publishes the progress metrics as report, JSON and per-binary breakdowns | repo src/config layout |
| `objdiff_report.py` | Converts the progress JSON into the external progress-report schema | external report schema |
| `frogress_upload.py` | Posts the progress JSON to a hosted progress service, dry-run by default | service URL, project/version names |
| `timeline.py` | Builds a progress timeline from the repository's own committed digests, with a self-check | repo doc paths |
| `mine_hindsight.py` | Gathers every recorded hindsight with file and line anchors into one document | repo doc paths |
| `cookbook_index.py` | Generates a symptom-keyed index of the large technique document | repo doc paths |
| `doc_links.py` | Checks that every relative link in the public docs resolves and the link policy holds | repo doc paths |
| `gitignore_template_check.py` | Asserts the ignore-file template in the docs equals the kit's template byte for byte | repo doc and template paths |
| `wiki_render.py` | Renders the doc trees into wiki page names with every relative link rewritten deterministically | repo doc paths |
| `wiki_sync.sh` | Renders and publishes the docs to the hosted wiki, replacing its pages | wiki remote URL, repo paths |
| `common.py` (history rewrite) | Shared purge rules, derived hash sets and helpers for the history-rewrite package | repo scratch paths |
| `hash_dict.py` | Builds the private dictionary mapping every old commit hash to an inert token | repo scratch paths |
| `scrub.py` | The single scrub function of the history rewrite, plus its sample and self-test | purge rules, repo scratch paths |
| `run_filter.py` | Composes and runs the history rewrite inside a bare clone, refusing to run elsewhere | rewrite tool version, repo scratch paths |
| `gate_scan.py` | History gate: no derived blob reachable from the given refs, four derived checks | repo declaration files |
| `verify_rewrite.py` | Pairwise proof that the rewrite changed only what it was told to change | repo scratch paths |
| `build_commit_map.py` | Emits the public ordinal-to-new-hash map and the private old-to-new map | repo doc/scratch paths |
| `resolve_tokens.py` | Turns ordinal tokens back into shortest-unique hashes at the rewritten tip | repo tracked text files |
| `absent_scan.py` | Asserts nothing purged remains in any object, message or ref | repo scratch paths |
| `probe_github.sh` | Probes whether old commit hashes still resolve on the hosting service after a purge | hosting service API, repo name |

*The history-rewrite package exists because the source project committed game-derived files while private; a project that
holds the firewall from commit one never needs it. It is listed so the procedure is known, not as a task.*

## P10 — readability

| Tool | What it does | Hard-codes |
|---|---|---|
| `lift_types.py` | Lifts a named list of types fleet-wide into the shared type header | repo shared-header path |
| `build_engine_types.py` | Extracts inline-defined named types and typedefs from a source file into a shared header | repo shared-header path |
| `uniquify_type.py` | Gives each conflicting camp of a same-named type its own name so every camp becomes liftable | repo src layout |
| `cast_call_sites.py` | Adds per-site function-pointer casts so a draft can call a differently typed callee | repo src layout |
| `canon_sig_reconcile.py` | Reconciles a definition's typed signature with what its destination unit already declares | repo src layout |
| `ghidra_apply_symbols.sh` | Mirrors the curated symbol file into the analysis program headlessly, with a real save | repo symbol path, project name |
| `ApplySymbols.java` | The in-tool half of that mirror: apply curated names and signatures, save on exit | none |
| `lint_symbol_refs.py` | Flags address-named references in committed sources whose address now has a curated name | repo symbol/src paths |
| `verbatim_check.py` | Regression guard that every inline-assembly body still reproduces its target bytes | repo src layout |
| `asm_verbatim.py` | Emits the file-scope inline-assembly body form from a disassembly file | repo asm layout |
| `verbatim_target_s.py` | Regenerates a splitter-format target disassembly for a function that is no longer a stub | repo build/asm layout |
| `verbatim_to_stub.py` | Turns an inline-assembly body back into an include-assembly stub | repo src/asm layout |

## Project-only in code (the shape is a task; the code does not transfer)

| Tool | Why it does not transfer |
|---|---|
| `bfm_extract/__init__.py` | Package entry for one title's disc pipeline; names its own container stages |
| `bfm_extract/extract.py` | Full-disc extractor bound to one disc's root file list and audio-track handling |
| `bfm_extract/extract_exe.py` | Hard-validates one executable's exact name, size, hash and header field values |
| `bfm_extract/extract_proto_exe.py` | Companion for one title's prototype discs and their specific deviations |
| `bfm_extract/cd_archive.py` | Reader for one game's bespoke container table-of-contents format |
| `bfm_extract/pac.py` | Parser for one game's bespoke archive-chain header format |
| `bfm_extract/lzss.py` | Decoder for one game's non-generic compression semantics, verified against its own decompressor |
| `bfm_extract/test_lzss.py` | Unit tests for that game-specific compression variant |
| `bfm_extract/crosscheck.py` | Cross-validates against a third-party tool written for that specific game |
| `disc_audit.py` | Byte partition over one disc, importing the game-specific container and compression modules — the partition itself (every byte of the medium accounted for, residue zero) is a Phase-1 task |
| `idxtab_map.py` | Decodes one game's on-disc index table and its payload-to-binary naming convention — the load map itself is a Phase-2 task |
| `cdtrace.py` | Reads one game's loader request structures at fixed RAM addresses |
| `new_overlay.sh` | Takes one game's container and file-index naming as its command-line contract |
| `make_libgs.sh` | Hard-codes one executable's exact vendor object list and address blocks |
| `make_snd_used.py` | Hard-codes one executable's sound-library address window and per-address exclusions |
| `make_apicard_used.py` | Hard-codes one executable's interface-library address window and object roster |
