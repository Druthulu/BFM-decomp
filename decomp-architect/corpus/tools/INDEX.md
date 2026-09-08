# corpus/tools/INDEX.md — the tool dictionary (the files beside this index are the source project's tools, verbatim)

> **Generated** by the source project's `tools/tool_census.py --manifest` from its tool dictionary (the same data as its tool index);
> never edited by hand. **What this is, and what it is not.** The kit installs no tools (its README says so). Each row is a task for
> the phase that needs it: build the tool for your target from its description, using the verbatim copy under `corpus/tools/<phase>/`
> as the reference implementation and the *Adapt* column as the list of what to change. Rows whose *Adapt* says "none" or names only
> the instruction set are copy-after-adaptation candidates; rows that name the source repository's layout, its compiler triple or
> its platform SDK need the marked adaptation. The last table lists the tools that are project-only in code (their *shape* is a task;
> their code does not transfer). *TODO(platform): the MIPS and PlayStation SDK hard-codes are the ones another platform replaces first.*
>
> **Coverage:** 293 tool files in scope (submodules, vendored and downloaded code excluded), of which 293 live rows
> below; per phase: P1 2 · P2 26 · P3 17 · P4 9 · P5 27 · P6 52 · P7 20 · P8 86 · P9 26 · P10 12 · PROJECT-ONLY 16. Superseded tools appear only as pointers to their successor (28 pointer rows); one-offs are omitted. Table rows in all: 321 (the installer checks its copy against this figure).

## P1 — extraction + manifest

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `bfm_extract/manifest.py` | build and verify a deterministic sorted checksum manifest of an extraction tree | Builds and verifies a deterministic sorted SHA1 manifest of an extraction tree | the extraction output root |
| `bfm_extract/iso9660.py` | walk a raw data track's filesystem and extract files by name | Reusable reader for a raw 2352-byte-sector data track; walks the filesystem and extracts files by name | none |

## P2 — the oracles + the load map

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `ghidra_scripts/DecompileFunctions.java` | batch-decompile an address list into one source file per function | Headless batch decompile of an address list into one C file per function | none |
| `prefetch_fleet.py` | batch-decompile one representative per distinct open class into a cache | Batch headless decompilation of one representative per distinct open class into a cache | repo paths, binary registry |
| `ram_probe.py` | capture and diff live console memory across scenarios to type struct fields | Captures, diffs and reads emulator main RAM over its web API for field typing | emulator host/port, 2 MB console RAM map |
| `ghidra_mcp_stop.sh` | close the analysis program cleanly so its edits actually persist | Clean save-and-close via a sentinel file; the only persistence event | repo paths, project name |
| `ghidra_scripts/DefineFunctions.java` | create functions at externally validated entry points listed in a file | Disassembles and creates functions at externally validated entry points listed in a file | repo scratch path |
| `ghidra_scripts/DecompileAt.java` | decompile one function at a given address straight from the analysis database | Headless script decompiling the function at one address and printing its C | default address |
| `ghidra_annotations_delta.py` | derive the hand-authored annotations by subtracting a fresh analysis baseline | Derives the hand-authored annotation rows by subtracting a fresh rebuild baseline | repo paths |
| `ghidra_scripts/DumpFunctionSignatures.java` | dump per-function fingerprints in three hash tiers for cross-binary correspondence | Read-only per-function fingerprint dump in three hash tiers for cross-binary correspondence | none |
| `main_seed_ends.py` | emit function start and length seeds for the executable's own code objects | Emits function start/length seeds for the executable's game-code objects, derived from the build | repo build paths |
| `ghidra_export_annotations.sh` | export a program's annotations to byte-stable line-delimited records, read-only | Read-only export of a program's annotations to byte-stable line-delimited JSON | repo paths |
| `ghidra_scripts/ExportSymbols.java` | export the analysis database's hand-authored symbols to a committable text file | Exports user-defined symbols to a committable text file so annotations are version-controlled | none |
| `find_addr_refs.py` | find code that materializes an absolute address, tracking registers rather than pairing windows | Register-tracked scan for code that materializes an absolute address; never window-paired | MIPS encodings, repo binary registry |
| `ghidra_roster.py` | generate and check a roster of committed analysis programs from the registry | Generates and checks a roster of committed analysis programs from the build registry | repo config paths |
| `ghidra_import_raw.sh` | import a flat headerless blob at a given base with the right processor spec | Headless import of a flat headerless blob at a given base with the right processor spec | PS1 processor spec, project name |
| `ghidra_import.sh` | import and auto-analyze a console executable headlessly with the platform loader | Headless import and auto-analysis of a console executable with the platform loader | PS1 executable loader, project name |
| `ghidra_scripts/ImportAnnotations.java` | import annotations back into a program, comparing before writing | Idempotent compare-before-write import of the annotation JSONL back into a program | none |
| `split_indicator.py` | name the code segments that must be split before their switch functions carve | Names code segments that must be split before their switch functions can be sectioned | repo config layout |
| `ghidra_scripts/DumpProgramInfo.java` | print a program's language, compiler spec, image base and function count | Prints program metadata: language, compiler spec, image base, function count, properties | none |
| `ghidra_scripts/GetSymbolAt.java` | print the symbol name at one address for scripted persistence checks | Prints the function or symbol name at one address for scripted persistence checks | none |
| `payload_base_evidence.py` | rank candidate load addresses for a payload that was never onboarded | Ranks candidate load addresses for an unonboarded payload from pointers, self-calls and upper-half reach | the source game's payload map |
| `ghidra_mcp_verify.sh` | re-open read-only to confirm a symbol edit survived the save | Read-only re-open confirming a symbol edit actually persisted after save-shutdown | repo paths, project name |
| `ghidra_rebuild.sh` | rebuild an analysis program from committed text plus extracted bytes, proving equality | Rebuilds one analysis program from committed text plus extracted bytes, and proves equality | repo paths, project layout |
| `ghidra_scripts/ImportPsyqGdt.java` | resolve a vendor SDK type archive into the program's type manager | Headlessly resolves a vendor SDK type archive into the program's type manager | PS1 SDK type archive name |
| `ghidra_scripts/ExportAnnotations.java` | serialize types, signatures, data, comments and labels to stable records | Read-only serialization of types, signatures, data, comments, bookmarks and labels to stable JSONL | none |
| `ghidra_scripts/BfmMcpServer.java` | serve the analysis tool over an automation protocol, saving on a sentinel stop | The headless MCP server itself; holds an open transaction and saves on a sentinel stop | repo sentinel path, server port |
| `ghidra_mcp_start.sh` | start the disassembler's automation server detached on a fixed local port | Starts the headless disassembler MCP server detached on a fixed local port | repo paths, project name, port |

## P3 — the all-assembly baseline

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `psyq_bss_probe.py` | ask whether an object's scattered zero-init section can be placed byte-exactly | Asks whether an object's scattered zero-init section can be split and placed byte-exactly | PS1 SDK object shape |
| `verify_binary.py` | byte-verify one binary by hand the only correct way, re-extract included | The correct hand verification of one binary: full re-extract plus rebuild, then hash compare | repo make targets |
| `psyq_build_libs.sh` | convert vendor library members to the linker's format and archive them | Converts vendor library members to ELF and archives them per library | PS1 SDK, repo scratch paths |
| `psyq_libs_from_disc.py` | extract vendor SDK library files from the vendor's runtime-library disc | Extracts vendor SDK library files from the vendor's runtime-library disc image | vendor disc layout, PS1 SDK |
| `gen_lib_subsegs.py` | generate segment lines and a stub list for a multi-block vendor library region | Generates segment lines and a stub list for a multi-block vendor library region | repo config layout, PS1 SDK libs |
| `psyq_link_region.py` | link a whole library's objects in place of stubs, placing data no-load | Links a whole library's objects in place of stubs, placing non-code sections as no-load | PS1 SDK, repo paths |
| `psyq_link_lib.py` | link every used object of a vendor library and byte-verify each | Driver linking every used object of a library and byte-verifying each | PS1 SDK, repo paths |
| `psyq_link.py` | link one vendor object at a fixed address so its code is byte-identical | Links one vendor object at a fixed address so its code is byte-identical to the target | PS1 SDK, repo build paths |
| `psyq_identify.py` | locate where vendor library objects are linked in a target image | Locates where vendor library objects are linked in a target image via relocation-masked patterns | PS1 SDK objects |
| `new_binary.sh` | onboard any flat blob in one command: config, registry entry, first build | One-command onboarding of any flat blob: config from template, registry entry, first build | repo config/template paths, the source game's payload classes |
| `ld_interleave.py` | reorder a generated linker script to reproduce the original section interleaving | Reorders a generated linker script to reproduce the original section interleaving | repo build paths |
| `reorder_passthrough.py` | restore the assembler-reorder build path for objects originally assembled that way | Restores the assembler-reorder build path for the objects originally assembled that way | pinned assembler flags, repo build paths |
| `split_src_region.py` | split a source file at object boundaries, preserving matched code and stubs | Splits a source file at object boundaries, preserving matched code and stub blocks | repo src/config layout |
| `psyq_lib_split.py` | split a vendor library archive into its member objects | Splits a vendor linker-format library archive into its member objects | PS1 SDK archive format |
| `psyq_bss_split.py` | split one zero-init section of an object into per-base no-bits pieces | Rewrites an ELF object, splitting one zero-init section into per-base no-bits pieces | ELF32 REL layout |
| `psyq_integrate.py` | wire real library objects into the split build, replacing stub subsegments | Wires real library objects into the split build, replacing stub subsegments | repo config/build paths |
| `mk_write.py` | write the generated binary-registry makefile safely, validating before replacing | The only safe writer of the generated binary-registry makefile; validates before replacing | repo config path |

## P4 — the compiler pinned; the probes

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `masked_diff.py` | compare instructions with relocations masked, shared by matcher and scorer | Shared relocation-masked instruction comparison used by the matcher and the permuter scorer | MIPS relocation encodings |
| `match_one.py` | compile one function standalone and compare its masked bytes to the target | Compiles one function standalone with the pinned toolchain, masks relocations, compares to target bytes | compiler triple, repo build flags |
| `cc1_dumps.sh` | dump every compiler pass file for a self-contained draft | Dumps every compiler pass file for a self-contained draft into a private directory | compiler triple, repo scratch paths |
| `cc1_dumps_tu.sh` | dump every compiler pass file for the spliced real translation unit | Same pass dumps for the spliced real translation unit, the faithful compile | absolute repo path, compiler triple |
| `rtu_second_chance.py` | re-judge standalone compile failures against their real translation unit before dropping | Re-judges standalone compile-failures against their real translation unit before dropping them | repo scratch paths |
| `decompme_replica.sh` | reproduce an external reference toolchain locally and compare its words to target | Runs a function through an external reference toolchain build and compares words against the target | pinned toolchain versions, network fetch |
| `draft_prechecks.py` | skip a draft doomed to fail before any compile is spent | Static pre-checks that skip a draft doomed to fail before any compile is spent | repo symbol/config sources |
| `rtu_match.py` | splice a candidate into a copy of its real translation unit and compare bytes | Splices a candidate into a copy of the real translation unit and checks the same bytes | repo src layout, compiler triple |
| `decompile.py` | turn one function's disassembly into a C scaffold to start a match | Wrapper locating a function's disassembly and running the C-scaffold generator on it | repo asm paths, decompiler target name |

## P5 — the census, the harness, the reports

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `corpus.py` | answer from one derived model whether each function is open, matched or shared | The single derived model of the source tree: open, matched or shared, per function | repo src/config layout |
| `audit_binaries.py` | assert every consumer knows about each newly onboarded binary | Gate asserting every consumer knows about each newly onboarded binary | repo config/registry paths |
| `audit_text_sources.py` | assert every tracked source is plain text so text searches never skip it | Every tracked C source must be plain text, or text searches silently skip it | repo src paths |
| `audit_frontier.py` | check that the independent what-remains views agree with the corpus oracle | Checks that the independent "what remains" views agree with the corpus oracle | repo paths |
| `reloc_identity.py` | check the symbol identity the masked comparison deliberately hides | Disagreeing oracle checking the symbol identity the masked comparison deliberately hides | repo build paths |
| `strand_census.py` | check whether an open target already has a draft on disk | Lists every draft already on disk whose function is still open, with its blocker | repo scratch paths |
| `oracle_reorder.py` | decide whether a near-miss residual is a source defect or an assembler artifact | Decides whether a near-miss residual is a source defect or an assembler artifact | pinned assembler flags |
| `tool_census.py` | derive the tool census, the need-keyed index, the kit manifest and the verbatim corpora from one dictionary | Derives the tool census, the need-keyed tool index, the kit manifest and the verbatim corpora from one dictionary, coverage-asserted both ways | repo layout (tools/, docs/SETUP.md rows, the kit paths) |
| `wall_sweep.py` | enumerate fleet-wide every instance of one known assembler-level blocker class | Enumerates fleet-wide instances of one known assembler-level blocker class | repo asm layout, toolchain quirk |
| `test_reconcile_ledger.py` | exercise a guarded repair path the full negative control never reaches | Targeted proof of the propagation ledger guard the full control never exercised | repo paths |
| `blocker_probe.py` | explain with two oracles why a byte-correct draft fails the whole-binary gate | Read-only two-oracle explanation of why a byte-correct draft fails the whole-binary gate | repo build paths |
| `atlas_features.py` | extract one deterministic feature record per function across every registered binary | Extracts one deterministic feature record per function across all registered binaries | repo signature files |
| `worklist.py` | join the target pool and near-miss ledger into one byte-weighted queue | Joins the target pool and the near-miss ledger into one byte-weighted ranked queue | repo scratch paths |
| `backlog.py` | keep a ranked ledger of every close-but-not-matching attempt | Near-miss ledger: every close-but-not-matching attempt, ranked for hand sessions | repo scratch/doc paths |
| `frontier_classify.py` | name the true blocker of every remaining open function, deterministically | Classifies every remaining open function by its true blocker, deterministically | repo paths |
| `stub_invariant_audit.py` | negative-control the comparer: every stub's built object must equal its target | Negative control: for every stub the built object must equal the target assembly exactly | repo build paths |
| `test_o0_detect.py` | negative-control the detector that decides a function's optimization level | Negative control for the matcher's optimization-level auto-detection | repo paths |
| `atlas.py` | partition every open function into exactly one lever-labelled work group | Partitions all open functions into exactly one lever-labelled work group | repo scratch paths |
| `difficulty.py` | rank unmatched functions easiest-first by size, control flow and call count | Ranks unmatched functions easiest-first by size, control flow, table presence and call count | repo asm layout |
| `ab_score.py` | re-score both arms of an experiment with the standalone matcher as ground truth | Re-scores every draft of two experiment arms with the standalone matcher as ground truth | repo scratch paths |
| `audit_digest.py` | recompute headline metrics and fail if the committed digest disagrees | Recomputes headline metrics from the current tree and fails if the committed digest disagrees | repo docs paths |
| `test_jtbl_parse_config.py` | regression-test the table-carve configuration parser with a negative control | Regression plus negative control for the table-carve configuration parser | repo config fixtures |
| `dup_report.py` | report byte-identical and structurally identical function groups within and across binaries | Reports byte-identical and structurally identical function groups within and across binaries | repo signature files |
| `reloc_verify.py` | resolve every relocation in a draft and compare the resolved words to target | Resolves every relocation in a draft and compares the resolved words to the target | repo build paths |
| `p16_improve.py` | revert known answers to stubs and categorize every harness failure it exposes | Known-answer loop: reverts matched functions to stubs and measures the real pipeline | repo src/build paths |
| `burndown.py` | track per-session yield and velocity so a diminishing-returns close is visible | Tracks per-session yield and velocity so a diminishing-returns close is visible | repo ledger paths |
| `test_residual_class.py` | unit-test a residual classifier on hand-encoded words, not its own decoder | Synthetic hand-encoded unit tests for the deterministic residual classifier | MIPS encodings |

## P6 — the multipliers: signatures, dedup, families, the reconcile ladder, the carve chain

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `o0_detect.py` | answer from a prologue whether a function was built unoptimized | The single place that answers whether a function was built unoptimized, from its prologue | compiler prologue shape |
| `weave_sweep.py` | apply one proven codegen lever everywhere the bytes say it belongs | Applies one known prologue-scheduling lever everywhere the bytes say it belongs | repo src layout, compiler behaviour |
| `interleave_check.py` | assert a read-only-data carve's interleave order equals the segment sequence | Asserts the carve interleave order equals the segment sequence, position by position | repo config layout |
| `jtbl_family_bank.py` | bank a matched jump-table exemplar across its siblings, reverting on failure | Banks a matched jump-table exemplar across its structural siblings, revert-on-fail | repo config/src layout |
| `sync_tu_decls.py` | bank a refused draft by copying the destination unit's own declarations into it | Banks a refused draft by copying the destination unit's own declarations into it | repo src layout |
| `twin_sweep.py` | bank every open stub that already has a banked structural twin | Banks every open stub that has an already-banked structural twin, for near-zero tokens | repo signature files |
| `fix_decl_mirror.py` | bind a void definition to a symbol the destination declares as returning a value | Binds a void definition to its symbol when the destination declares a value return | repo src layout |
| `family_align.py` | classify drifted structural siblings by aligned words and expand their constants | Length-tolerant aligned classifier plus the mechanical constant-expansion engine for drifted members | repo scratch paths |
| `exclude_audit.py` | classify every exclude-list entry by its current blocker and regenerate the list | Classifies every exclude-list entry by its current blocker and regenerates the list | repo config path |
| `family_cousins.py` | cluster the open frontier one tier looser than exact skeleton hashing | Similarity clustering one tier looser than exact skeleton hashing over the open frontier | repo signature files |
| `decl_prior.py` | compute the fleet's consensus declaration for every symbol, as card fuel | Computes the fleet's consensus declaration for every symbol, as card fuel | repo src layout |
| `reconcile_tu.py` | conform a draft's data declarations to what its destination unit can see | Conforms a draft's data declarations to what the destination translation unit can actually see | repo src layout |
| `conform_decls.py` | conform every declaration of a function fleet-wide to its byte-true definition | Conforms every declaration of a function fleet-wide to its byte-true definition | repo src/shared-header layout |
| `scope_demote_drafts.py` | demote declaration scope as one rung of the recovery ladder | The scope-demote step, wired as a rung of the recovery ladder | repo src layout |
| `pads_audit.py` | derive an object's inter-table padding spec from the bytes instead of searching | Derives each object's padding spec from the bytes instead of searching for it | repo build/config layout |
| `aprop_autodraft.py` | draft a family member mechanically from a seed body and symbol rebase | Mechanically drafts a family member from the seed body plus a positional symbol rebase | repo scratch paths |
| `demacroize.py` | escape a shared-header declaration conflict locally by unmacroizing one body | Per-binary local escape from a shared-header declaration conflict by unmacroizing one body | repo shared-header layout |
| `dedup_extend.py` | extend an existing code-share registry to newly onboarded binaries | Extends the existing share registry to newly onboarded binaries | repo config/src layout |
| `o0_boundary.py` | find and bank unoptimized functions stranded at an optimized region's boundary | Finds and banks unoptimized functions stranded at the end of an unoptimized region | repo config layout |
| `inject_capped_externs.py` | free duplicate matches a share propagation skips as not self-contained | Frees high-reach inline matches skipped as not self-contained by injecting their file-scope externs | repo shared-header layout |
| `decl_from_use.py` | infer a minimal extern for a data symbol the destination unit does not declare | Infers a minimal extern for a data symbol a draft uses but its destination does not declare | repo src layout |
| `jr_isolate_all.py` | isolate every switch function in a binary in one multi-cut resegment | One-shot multi-cut resegment isolating every switch function in a binary | repo config/src layout |
| `match_protos.py` | join two related builds' signature dumps into a function correspondence | Joins per-function signature dumps of two related builds into a function correspondence | repo signature files |
| `cast_self_callers.py` | let a unit keep calling, through per-site casts, the function it now defines | Lets a unit keep calling, through a per-site cast, the function it is about to define | repo src layout |
| `dedup_propagate.py` | lift one matched body into a shared macro and instantiate it everywhere | Lifts one matched body into a shared macro and instantiates it at every duplicate site | repo shared-header/src layout |
| `macro_draft.py` | materialize a shared macro body back into a compilable standalone draft | Materializes a shared macro body back into a compilable standalone draft | repo shared-header layout |
| `scope_tu_externs.py` | move a unit's file-scope data externs down into their consumers | Moves a unit's own file-scope data externs down into their consumers to legalize a block-scope type | repo src layout |
| `family_manifest.py` | name the one exemplar to draft per structural family, ranked | Ranked structural-family target manifest naming the one exemplar to draft per family | repo signature files |
| `normalize_self_decls.py` | normalize a function's own declaration when a templated definition lands in a new unit | Normalizes a function's own declaration when a templated definition lands in a new unit | repo src layout |
| `cdecl.py` | parse C declarators once, for every declaration tool to share | The single recursive-descent C declarator parser every declaration tool shares | C89 grammar only |
| `overlay_src_split.py` | partition a source file at object boundaries, aware of comment state | Comment-state-aware partition of a source file, the oracle for the split chain | repo src layout |
| `scope_data_externs.py` | place a templated body's data externs at a scope the destination accepts | Places a templated body's data externs at the scope the destination unit can accept | repo src layout |
| `xsig/tests/test_xsig.py` | property-test the signature tool on committed fixtures, needing no compiler | Property tests for the signature tool on committed fixtures, needing no compiler | fixture paths |
| `family_hseq.py` | rank clusters of the unmatched frontier by mnemonic-skeleton hash | Ranked clustering of the unmatched frontier by mnemonic-skeleton hash | repo signature files |
| `aprop_symfix.py` | rebase a remapped draft's stale seed symbols onto the target's own | Rebases stale seed symbols in a mechanically adapted draft onto the target's own symbols | repo symbol/config sources |
| `xsig/tests/make_fixtures.sh` | regenerate the signature tool's fixtures with the pinned toolchain | Regenerates the signature-tool fixtures with the pinned toolchain | compiler triple, repo tool paths |
| `family_remap.py` | remap a matched exemplar's source onto a structural sibling by positional symbol pairing | Mechanically remaps a matched exemplar's C onto a structural sibling by positional symbol pairing | repo src layout |
| `fix_arity_callers.py` | repair a shared caller's argument-count conflict for the no-prototype failure class | Repairs the shared-caller argument-count conflict for the no-prototype failure class | repo shared-header layout |
| `jtbl_pads_fix.py` | repair a stale padding spec by search plus byte proof, never by guessing | Repairs a stale padding spec by search plus byte proof, never by guessing | repo config layout |
| `twin_rescan.py` | report which open stubs became mechanical remaps the moment one was banked | After a bank, reports which open stubs just became mechanical remaps instead of drafts | repo signature files |
| `jtbl_rodata_pads.py` | reproduce the original inter-table padding in a multi-table carve | Post-assembler filter reproducing the original inter-table padding in a multi-table carve | compiler/assembler behaviour, repo build paths |
| `restore_dropped_decls.py` | restore file-scope declarations a share propagation deleted with the body | Puts back file-scope declarations a share propagation deleted with the body | repo src layout |
| `fix_tu_ret_decls.py` | retype a unit's stale forward declarations to a draft's byte-true return, reverting on failure | Retypes a binary's own stale forward declarations to a draft's byte-true return, revert-on-fail | repo src layout |
| `canon_resident_calls.py` | rewrite address-named calls in a draft to their curated symbol names | Rewrites address-named calls in a draft to the curated symbol name when one exists | repo symbol file path |
| `rollout_o0.py` | roll an unoptimized definition atomically across every binary carrying it | Generalized two-file atomic rollout of an unoptimized definition across every binary carrying it | repo src/config layout |
| `o0_subsplit.py` | route an unoptimized address range sitting inside an otherwise optimized object | Routes an unoptimized address range that sits inside an otherwise optimized object | repo config layout |
| `jtbl_carve.py` | set up the read-only-data carve for a binary's matched jump-table functions | Sets up the read-only-data carve for a binary's matched jump-table functions | repo config/build layout |
| `sig_image.py` | sign every function of a flat image at a known base, without a disassembler | Disassembler-free per-function signer for a flat image at a known base, field-identical to the dumper | MIPS encodings, repo scratch paths |
| `xsig/xsig.py` | sign functions with relocations masked for cross-project code identification | Relocation-masked per-function signatures for cross-project code identification | MIPS/relocation model only |
| `family_sweep.py` | sweep a matched exemplar across every same-structure sibling, gate-arbitrated | Sweeps a matched exemplar across every same-structure sibling, gate-arbitrated | repo src/config layout |
| `sig_unify.py` | unify a draft's callee externs and its own signature to the banked-canonical set | Unifies a draft's callee externs and its own definition signature to the banked-canonical set | repo shared-header paths |
| `dedup_integrate.py` | validate a code-share registry byte-honestly, failing closed on signature drift | Byte-honesty validator for the code-share registry; fails closed on signature drift | repo config registry path |

## P7 — the codegen map, the dumps, the permuter

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `len_tells.py` | classify a length-drift near-miss against its own target and build its routing card | Classifies a length-drift near-miss against its own target and builds the routing card | repo scratch paths |
| `residual_rules_b.py` | classify a residual's shape to its documented lever, as an independent implementation | Independent second implementation of residual-shape to rule classification, for head-to-head | repo doc paths |
| `diff_regions.py` | classify where a remapped sibling's compiled bytes diverge from its target | Classifies where a remapped member's compiled bytes diverge from its target | repo build paths |
| `permuter/compile.sh` | compile a permuter candidate exactly as the build rule does | The permuter's compile command, mirroring the build rule exactly so objects are build-faithful | compiler triple, repo build flags |
| `permuter/compile_o0.sh` | compile a permuter candidate unoptimized, exactly as the build rule does | Unoptimized variant of the same permuter compile command | compiler triple, repo build flags |
| `oracle/reg_renumber_swap.sh` | decide whether a residual reorder is scheduling or a register-grant consequence | Mechanized oracle separating a register-allocation swap from a scheduling reorder | compiler triple, repo scratch paths |
| `p16_permute.py` | drive the permuter per function, building base, target and settings | Per-function permuter driver building base, target and settings, then reporting closeness | repo scratch paths, permuter layout |
| `ghost_census.py` | find pseudo-registers with references but no remaining occurrences, and their frame slots | Frame-residue oracle: finds pseudos with references but no remaining occurrences, and their slots | compiler pass-dump format |
| `diff_autopsy.sh` | find which words diverge when the whole-binary gate says different but not where | Reproduces exactly what the gate saw, then decodes the diverging words and restores the tree | repo src/build paths |
| `grinder.py` | grind the closest near-misses with the permuter and bank through the gate | Token-free permuter daemon grinding the closest near-misses and banking through the gate | repo scratch paths |
| `permuter_sweep.py` | hand a batch's near-misses to the permuter, only the ones worth CPU | Hands a batch's near-misses to the permuter, but only the ones worth the CPU | repo scratch paths |
| `alloc_table.py` | list each pseudo-register's refs, live length and allocation priority from compiler dumps | Prints each pseudo's refs, live length, block and allocation priority from compiler pass dumps | compiler pass-dump format, repo dump root |
| `residual_class.py` | map a residual to a named codegen class by decoding its words | Deterministic decoder-based classifier mapping a residual to a named codegen class | MIPS encodings |
| `autopsy.py` | recompile every open draft and classify its failure into a residual corpus | Materializes the residual corpus by recompiling every open draft and classifying its failure | repo scratch/build paths |
| `permuter/run_masked.py` | run the permuter with a masked scorer rebound, without patching it | Runs the permuter with the masked scorer rebound before its entry point, without patching it | permuter internals, repo module paths |
| `masked_scorer.py` | score permuter candidates on true masked code closeness, not mnemonic diff | Drop-in permuter scorer scoring true relocation-masked code closeness instead of mnemonic diff | permuter internals, repo module paths |
| `permuter_weights.py` | steer permuter mutation toward the lever family the residual class implies | Directs permuter mutation toward the lever family the residual class implies | permuter settings format |
| `gccmap_cites.py` | tag every compiler-source citation with the source tree it refers to | Tags every compiler-source citation in the codegen-map docs with the tree it refers to | repo doc/reference paths |
| `main_diff_locate.py` | turn a red whole-binary result into a named list of divergent symbols | Turns a red whole-binary result into a named list of divergent symbols | repo build/config layout |
| `permuter_ils.py` | warm-restart the permuter from its best waypoint each cycle | Iterated-local-search wrapper warm-restarting the permuter from the best waypoint each cycle | permuter layout, repo scratch paths |

## P8 — the campaign: cards, lanes, gates, recovery, harvest

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `work_evidence.py` | assert that a tool actually did the work it reports | Assertions that a tool actually did the work it reports | repo scratch paths |
| `lanes/wait_distill.sh` | block until a background lane raises its next batch, without polling | Blocks until the distillation lane raises the next batch, then exits | repo scratch paths |
| `build_wave_atlas.py` | build a wave from the frontier atlas, optimized for gate throughput | Builds a wave from the frontier atlas, optimized for gate throughput | repo scratch paths |
| `t5_cards.py` | build the card fuel for one wave's own targets, keyed per binary | Builds the card fuel for one wave's own targets, keyed correctly per binary | repo scratch paths |
| `claude_wave_packs.py` | build the per-function prompt packs a drafting agent wave works from | Builds the per-function prompt packs an agent wave drafts from | repo scratch paths, agent harness |
| `jtbl_lane.py` | carve, draft and bank jump-table functions as their own lane | Carve, draft and bank lane for jump-table functions, with the carve deliberately outside it | repo config/src layout |
| `verify_worktree.py` | check a commit out into its own worktree and verify it there | Checks a commit into its own worktree, provisions build deps, and verifies it there | repo worktree/build layout |
| `wave_card_fuel.py` | compute in one library the per-target card fuel a prompt pack carries | The single library computing the per-target card fuel a pack carries | repo scratch paths |
| `transcript_dump.py` | condense a session transcript into readable text for a successor session | Condenses a session transcript into readable text for a successor session | agent transcript paths |
| `triage_ladder.py` | decide before and after drafting whether a target needs an agent at all | Zero-token pass deciding whether a target needs an agent at all, before and after drafting | repo scratch paths |
| `distill_scan.py` | decide which harvested waves still need mining into the technique document | One pass of the distillation lane deciding which harvested waves still need mining | repo scratch paths |
| `lanes/stallguard.sh` | detect and repair lane stalls automatically on measured conditions | Detects and repairs lane stalls on measured conditions every minute, logging each action | lane names, repo paths |
| `gate_main_parallel.py` | discover an executable slate's bankable drafts concurrently, then bank once serially | Discovers the executable's bankable drafts concurrently, then banks them once, serially | repo build/make targets |
| `idiom_hunt.py` | discover new compiler idioms from grouped near-misses with a reasoning model | Uses a reasoning model on grouped near-misses to discover new compiler idioms | provider endpoint, repo paths |
| `api_draft.py` | draft one function against any chat-completions endpoint, provider-agnostic | Provider-agnostic single-shot drafting worker against any chat completions endpoint | provider endpoint, repo doc paths |
| `gater_lane.py` | drain finished drafts into the gate continuously while drafting still streams | Continuous gater draining a wave's finished drafts into the parallel gate, grouped by binary | repo scratch paths |
| `draw_waves.py` | draw several drafting waves off the open frontier, cheapest-first | Draws several drafting waves off the open frontier, cheapest-first | repo scratch paths |
| `gate_lane.py` | drive a wave's gate accepting either result shape and an explicit draft path | The wave gate driver, accepting either result shape and an explicit draft path | repo scratch paths |
| `recover_integration.py` | drive batch integration recovery over a directory of correct-but-rejected drafts | Batch integration recovery driver over a wave directory of correct-but-rejected drafts | repo scratch/src layout |
| `lanes/sibling_lane.sh` | drive structural sibling sweeps with synthesized declarations, free of model tokens | The free sibling lane driving structural sweeps with synthesized declarations | repo paths |
| `wave_args.py` | emit the exact drafting-workflow arguments, asserting every target is still open | Emits the exact workflow arguments for a wave, asserting every target is open | repo scratch paths |
| `eval_lora.py` | evaluate a fine-tuned matching model gate-truthfully on held-out banked functions | Gate-true evaluation of a fine-tuned model on held-out banked functions | dataset paths, repo corpus |
| `seed_ref.py` | find an already-banked body that matches an open stub, near and contained tiers | For an open stub, finds the already-banked body that matches it, including near and contained tiers | repo signature files |
| `train_lora.py` | fine-tune a code model into a matching specialist on a mined corpus | Fine-tunes a code model into a matching specialist and saves the adapter | dataset paths, training venv |
| `gate_wave.py` | gate a whole wave by splitting table-bearing drafts off and running lanes concurrently | Gates a whole wave by splitting table-bearing drafts off and running both lanes concurrently | repo scratch/config layout |
| `wave_judge.py` | gate each arm on the whole binary with a tree reset between arms | Per-arm whole-binary gate with tree reset between arms, then gates the best-of union | repo scratch/src layout |
| `validate_targets.py` | gate every target list for validity before agents are spawned | The validity gate every target list must pass before agents are spawned | repo scratch paths |
| `parallel_gate.py` | gate many binaries concurrently in isolated worktrees and merge only passers | Gates many binaries concurrently in isolated worktrees and merges only the passers | repo worktree/build layout |
| `sweep_parallel.py` | gate pre-staged draft directories across distinct binaries in parallel | Gates pre-staged draft directories across distinct binaries in parallel | repo scratch paths |
| `gate_main.py` | gate the executable's drafts the only trustworthy way: a clean rebuild with bisect | Gates a batch of executable drafts the only trustworthy way: a clean rebuild with bisect | repo build/make targets |
| `gen_harvest_targets.py` | generate a callee-signature-aware target manifest with per-function fleet reach | Generates a callee-signature-aware target manifest with per-function fleet reach | canonical source binary, repo paths |
| `wave_snapshot.py` | give a wave its own immutable copy of the disassembly its agents read | Gives a wave its own immutable copy of the disassembly files its agents read | repo asm paths |
| `api_agent.py` | give an external chat model the same multi-turn tool harness an agent gets | Gives an external chat model the same multi-turn tool harness an agent gets | provider endpoint, repo doc paths |
| `shared_lock.py` | hold one reader/writer lock over the shared source state for concurrent lanes | One reader/writer lock over the shared source state for concurrent lanes | repo lock paths |
| `lanes/forever.sh` | keep an unattended campaign loop alive across run caps and crashes | Keeps the wave campaign running indefinitely across caps and crashes | repo scratch paths |
| `auto_supervisor.sh` | keep an unattended driver alive across crashes until a clean exit | Keeps an unattended driver alive across crashes until a clean or requested exit | repo scratch paths |
| `lanes/drafter.sh` | keep drafting running continuously, touching only scratch state | The drafting lane that must never stop; touches only scratch state | repo scratch paths, provider config |
| `lane_inflight.py` | know authoritatively which drafting agents are currently live | The authoritative ledger of which drafting agents are currently live | repo scratch paths |
| `idiom_serial.py` | learn idioms serially so each target inherits what the previous one taught | The serial idiom-learning lane where each step inherits what the previous learned | repo scratch paths |
| `auto_driver.py` | loop a stub worklist through scaffold, draft and gate without any model | Autonomous model-free driver looping a stub worklist through scaffold, draft and gate | canonical source binary, repo paths |
| `ox_campaign.py` | loop draw, draft, pre-filter, gate, commit and ledger unattended | The unattended wave loop: draw, draft, pre-filter, gate, commit, ledger, repeat | repo scratch paths, provider config |
| `bulk_harvest.py` | mass-draft small stubs with a served model and gate them in parallel | Phase-separated bulk drafting plus a parallel gate farm, for throughput | repo scratch paths, GPU endpoint |
| `blast_radius.py` | measure a change's write set and name the verification it actually requires | Measures a change's write set and names the verification it actually requires | repo tree layout |
| `api_rate.py` | measure a drafting provider's real request rate and rate-limit attribution | Reports measured request rate and rate-limit attribution from append-only telemetry | repo telemetry path |
| `journal_notes.py` | mine each function's own past-attempt history out of agent journals | Mines per-function past-attempt notes out of the agent journals into card fuel | agent transcript paths |
| `export_pairs.py` | mine gate-verified assembly-to-source pairs into a fine-tuning corpus | Mines gate-verified assembly-to-source pairs into a fine-tuning corpus | repo src/build layout |
| `recover_route.py` | name the one recovery tool that actually applies to a drop verdict | Given a drop verdict, names the one recovery tool that actually applies | repo scratch paths |
| `orchestrator.py` | pick the pool, emit the batch and record the cycle, deterministically | The deterministic half of the unattended loop: pick the pool, emit the batch, record the cycle | repo scratch paths |
| `gap_triage.py` | pre-filter agents' knowledge-gap reports against the existing technique document | Pre-filters a wave's knowledge-gap reports against the existing documentation | repo doc paths |
| `auto_status.sh` | print an unattended run's heartbeats and recent progress for a remote check-in | Prints the unattended run's heartbeats and recent progress for a remote check-in | repo scratch paths |
| `idiom_harvest.py` | pull newly learned idioms out of a wave's logs into candidate notes | Pulls the newly learned idioms out of a wave's shard logs into candidate notes | repo log paths |
| `agent_verdicts.py` | pull the final structured verdict out of each subagent transcript | Pulls the final structured verdict out of subagent transcripts | agent transcript paths |
| `neighbor_ref.py` | rank already-matched functions worth reading as worked examples for an open stub | For an open stub, ranks already-matched functions worth reading as worked examples | repo signature files |
| `integration_resolver.py` | re-judge already byte-correct drafts and bank them for zero model tokens | Zero-token lane re-judging drafts that are already byte-correct and banking them | repo scratch paths |
| `lanes/resolver_lane.sh` | re-judge, verify twice, stage and gate correct drafts for zero tokens | The zero-token resolver lane: re-judge, verify twice, stage, gate, commit | repo scratch paths |
| `restage_matching.py` | re-stage only drafts that match in their real unit so one failure is isolated | Re-stages only the drafts that compile and match in their real unit, so one failure is isolated | repo src layout |
| `agent_drafts_restore.py` | rebuild an agent's final draft by replaying its transcript writes | Replays an agent's writes from its transcript to rebuild its final deliverable | agent transcript paths |
| `main_queue_rebuild.py` | rebuild the executable lane's queue from the tree, never from a stale list | Rebuilds the executable lane's queue from the tree, never from a stale list | repo src layout |
| `recover_giant.py` | recover a large draft rejected only on declaration plumbing, with canonical externs | Canonical-extern recovery for a large draft rejected only on declaration plumbing | repo shared-header layout |
| `fragment_check.py` | refuse a draft that swallows a neighbouring symbol inside one function's range | Refuses drafts that subsume a neighbouring symbol, the enclosing-function trap | repo asm layout |
| `launch_check.py` | refuse to launch an agent at a target that is already banked | Refuses to launch an agent at a target that is already banked | repo src layout |
| `campaign_status.py` | report every concurrent lane with its own metrics, not only the loud one | One status view covering every lane, not only the loud one | lane names, repo scratch paths |
| `auto_stop.sh` | request a safe exit of an unattended run through a stop sentinel | Requests a safe exit of the unattended run via a stop sentinel | repo scratch paths |
| `lanes/relaunch_drafter_shell.sh` | restart the drafting lane's shell at a queue boundary so new arguments apply | Waits for a wave to queue, then restarts the drafting lane's shell so new arguments apply | lane script paths |
| `lanes/restart_main_lane_when_idle.sh` | restart the executable lane's shell at its one safe boundary | Restarts the executable lane's shell at its one safe boundary | lane script paths |
| `lanes/restart_gater_when_idle.sh` | restart the gating lane's shell between gates so a jobs change lands | Restarts the gating lane's shell once the current gate finishes | lane script paths |
| `lora_grind.py` | rotate binaries drafting small stubs with a served model, gating and propagating | Mass-run driver rotating binaries, drafting small stubs with a served model, gating, propagating | repo scratch paths, model endpoint |
| `gate_triage.py` | route a gate result set to the repair tool its own verdict names | Routes a gate result set to the repair tool its own verdict names | repo scratch paths |
| `lanes/gater.sh` | run a restartable gating lane that is safe to kill at any time | The restartable gating lane, safe to kill and relaunch at any time | job count, repo paths |
| `lanes/distill.sh` | run distillation beside drafting so learned idioms reach the next wave | The distillation lane, running beside drafting and never in front of it | repo scratch paths |
| `main_lane.py` | run the executable's own draft, gate and commit cadence beside other lanes | The executable's own draft, gate and commit cadence beside the other lanes | repo build/make targets |
| `lanes/main.sh` | run the executable's own lane loop on its clean-rebuild cadence | The executable's own lane loop, on its clean-rebuild cadence | repo make targets |
| `lanes/maintenance.sh` | run the free recovery and re-judgement passes whenever the gate is idle | The maintenance lane running the free recovery and re-judgement passes | repo scratch paths |
| `gate_stage.py` | run the one shared recovery, byte-gate and log ladder every producer calls | The shared deterministic recovery, gate and log ladder every producer calls | repo src/config layout |
| `lanes/grinder_lane.sh` | run the token-free permuter grinder beside a saturated gate | Runs the model-free permuter grinder beside a saturated gater | repo scratch paths |
| `lanes/campaign.sh` | run two drafting pools against one serial gate | Dual-pool campaign lane: two drafting pools, one serial gate | provider config, repo paths |
| `agent_reports.py` | save each subagent's full final report to one file per target | Saves each subagent's full final prose report to one file per target | agent transcript paths |
| `wave_targets.py` | select a worker wave's target batch from the manifest with cache filters | Selects a worker-wave target batch from the target manifest with cache filters | repo scratch paths |
| `serve_local.py` | serve a fine-tuned model locally behind a chat-completions endpoint | Serves the fine-tuned model locally behind a chat-completions endpoint | training venv, GPU assumptions |
| `lanes/elastic.sh` | spend spare provider capacity on other work when the gate is the constraint | Spends spare provider capacity on extra work when the main lane cannot | provider config, repo paths |
| `harvest_verify.py` | substitute, build, keep only if byte-identical, else revert | The whole-binary byte gate: substitute, build, keep only if identical, else revert | repo src/build layout |
| `format_finetune.py` | turn mined pairs into a chat-template instruction dataset | Turns the mined pairs into a chat-template instruction dataset | dataset paths, model chat template |
| `recover_rejects.py` | turn pre-gate rejects back into bankable drafts for zero model tokens | Turns pre-gate rejects back into bankable drafts for zero model tokens | repo scratch paths |
| `build_fuel_manifest.py` | unify live stubs into one ranked, class-tagged, cache-annotated target pool | Unifies live stubs into one ranked, class-tagged, cache-annotated target pool | canonical source binary, repo scratch paths |
| `pregate_check.py` | validate a batch's declaration compatibility in seconds without building it | Validates a batch without building it, in seconds instead of minutes | repo src layout |
| `r22_verify.sh` | verify the whole fleet exclusively on a clean tree and clear deferred debt | Exclusive clean-tree fleet verification that also clears deferred-check debt | repo make targets |

## P9 — publish

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `fetch_psyq.sh` | acquire and checksum-verify vendor SDK pieces for a linked build | Optional acquisition and checksum verification of vendor SDK pieces for the linked build | PS1 SDK sources, repo paths |
| `gitignore_template_check.py` | assert a documented ignore-file template equals the shipped template byte for byte | Asserts the ignore-file template in the docs equals the kit's template byte for byte | repo doc and template paths |
| `public_rewrite/absent_scan.py` | assert nothing purged remains in any object, message or ref | Asserts nothing purged remains in any object, message or ref | repo scratch paths |
| `timeline.py` | build a progress timeline from the repository's own committed digests | Builds a progress timeline from the repository's own committed digests, with a self-check | repo doc paths |
| `doc_links.py` | check that every relative link in the public docs resolves | Checks that every relative link in the public docs resolves and the link policy holds | repo doc paths |
| `compile_only.py` | compile every eligible translation unit with the pinned toolchain, using no derived bytes | Compiles every eligible translation unit with the pinned toolchain, without any game bytes | compiler triple, repo makefile parsing |
| `progress.py` | compute and publish progress metrics as report, machine data and per-binary breakdowns | Computes and publishes the progress metrics as report, JSON and per-binary breakdowns | repo src/config layout |
| `objdiff_report.py` | convert progress metrics into an external progress-report schema | Converts the progress JSON into the external progress-report schema | external report schema |
| `public_rewrite/build_commit_map.py` | emit the public ordinal-to-hash map and the private old-to-new map | Emits the public ordinal-to-new-hash map and the private old-to-new map | repo doc/scratch paths |
| `audit_public.py` | gate a first push: prove no derived bytes among tracked files | The first-push gate: no derived bytes among tracked files, four independent checks | repo purge-set and path lists (the kit's template reads `config/firewall.txt` instead) |
| `mine_hindsight.py` | gather every recorded hindsight into one document with file and line anchors | Gathers every recorded hindsight with file and line anchors into one document | repo doc paths |
| `cookbook_index.py` | generate a symptom-keyed index of a large technique document | Generates a symptom-keyed index of the large technique document | repo doc paths |
| `kit_lint.py` | keep a portable starter kit free of one project's names, paths and numbers | Keeps the day-one kit free of the source project's names, paths, addresses and rule numbers, honours its placeholder contract, and syntax-checks its scripts | the kit path and the source project's leak pattern |
| `public_rewrite/hash_dict.py` | map every old commit hash to an inert token, privately | Builds the private dictionary mapping every old commit hash to an inert token | repo scratch paths |
| `public_rewrite/probe_github.sh` | probe whether old commit hashes still resolve on the hosting service | Probes whether old commit hashes still resolve on the hosting service after a purge | hosting service API, repo name |
| `public_rewrite/gate_scan.py` | prove no derived blob is reachable from the refs about to be pushed | History gate: no derived blob reachable from the given refs, four derived checks | repo declaration files |
| `public_rewrite/verify_rewrite.py` | prove pairwise that a rewrite changed only what it was told to | Pairwise proof that the rewrite changed only what it was told to change | repo scratch paths |
| `verify_contract.sh` | prove the whole byte-identity contract end to end, step by step | The recorded end-to-end verification run of the byte-identity contract, step by step | repo make targets, output dir |
| `frogress_upload.py` | publish progress metrics to a hosted progress service | Posts the progress JSON to a hosted progress service, dry-run by default | service URL, project/version names |
| `wiki_sync.sh` | render and publish the docs to a hosted wiki, replacing its pages | Renders and publishes the docs to the hosted wiki, replacing its pages | wiki remote URL, repo paths |
| `wiki_render.py` | render doc trees into wiki page names, rewriting every relative link | Renders the doc trees into wiki page names with every relative link rewritten deterministically | repo doc paths |
| `public_rewrite/run_filter.py` | run a history rewrite inside a bare clone, refusing to run elsewhere | Composes and runs the history rewrite inside a bare clone, refusing to run elsewhere | rewrite tool version, repo scratch paths |
| `public_rewrite/scrub.py` | scrub one text with the rewrite's rules, with a sample and self-test | The single scrub function of the history rewrite, plus its sample and self-test | purge rules, repo scratch paths |
| `bootstrap.sh` | set up a fresh clone idempotently: packages, environments, pinned tools | Idempotent fresh-clone setup: check packages, create environments, fetch pinned tools | repo layout, package names |
| `public_rewrite/common.py` | share the purge rules and derived hash sets across the rewrite package | Shared purge rules, derived hash sets and helpers for the history-rewrite package | repo scratch paths |
| `public_rewrite/resolve_tokens.py` | turn ordinal tokens back into shortest-unique hashes at the rewritten tip | Turns ordinal tokens back into shortest-unique hashes at the rewritten tip | repo tracked text files |

## P10 — readability

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `cast_call_sites.py` | add per-site function-pointer casts so a draft can call a differently typed callee | Adds per-site function-pointer casts so a draft can call a differently typed callee | repo src layout |
| `ghidra_scripts/ApplySymbols.java` | apply curated names and signatures inside the analysis tool and save | The in-tool half of that mirror: apply curated names and signatures, save on exit | none |
| `asm_verbatim.py` | emit a function's target assembly as an inline-assembly body | Emits the file-scope inline-assembly body form from a disassembly file | repo asm layout |
| `build_engine_types.py` | extract inline-defined types and typedefs from a source file into a shared header | Extracts inline-defined named types and typedefs from a source file into a shared header | repo shared-header path |
| `lint_symbol_refs.py` | flag address-named references whose address now has a curated name | Flags address-named references in committed sources whose address now has a curated name | repo symbol/src paths |
| `uniquify_type.py` | give each conflicting camp of a same-named type its own name | Gives each conflicting camp of a same-named type its own name so every camp becomes liftable | repo src layout |
| `verbatim_check.py` | guard that every inline-assembly body still reproduces its target bytes | Regression guard that every inline-assembly body still reproduces its target bytes | repo src layout |
| `lift_types.py` | lift a named list of types fleet-wide into the shared type header | Lifts a named list of types fleet-wide into the shared type header | repo shared-header path |
| `ghidra_apply_symbols.sh` | mirror the curated symbol file into the analysis database with a real save | Mirrors the curated symbol file into the analysis program headlessly, with a real save | repo symbol path, project name |
| `canon_sig_reconcile.py` | reconcile a definition's typed signature with what its destination unit declares | Reconciles a definition's typed signature with what its destination unit already declares | repo src layout |
| `verbatim_target_s.py` | regenerate a splitter-format target disassembly for a function no longer stubbed | Regenerates a splitter-format target disassembly for a function that is no longer a stub | repo build/asm layout |
| `verbatim_to_stub.py` | turn an inline-assembly body back into a stub the toolchain can reach | Turns an inline-assembly body back into an include-assembly stub | repo src/asm layout |

## PROJECT-ONLY — project-only in code (the shape is a task; the code does not transfer)

| Tool | When you need to… | What it does | Adapt |
|---|---|---|---|
| `disc_audit.py` | account for every byte of the medium, leaving zero unexplained residue | Byte partition over one disc, importing the game-specific container and compression modules — the partition itself (every byte of the medium accounted for, residue zero) is a Phase-1 task | project-only |
| `make_libgs.sh` | assemble a vendor graphics library's object list and address blocks for linking | Hard-codes one executable's exact vendor object list and address blocks | project-only |
| `bfm_extract/crosscheck.py` | cross-validate an extraction against an independent third-party tool | Cross-validates against a third-party tool written for that specific game | project-only |
| `bfm_extract/lzss.py` | decode a bespoke compression format, cross-checked against its own length field | Decoder for one game's non-generic compression semantics, verified against its own decompressor | project-only |
| `idxtab_map.py` | decode an on-disc index table into a payload-to-binary naming map | Decodes one game's on-disc index table and its payload-to-binary naming convention — the load map itself is a Phase-2 task | project-only |
| `bfm_extract/__init__.py` | expose a disc extraction pipeline's stages as one package | Package entry for one title's disc pipeline; names its own container stages | project-only |
| `bfm_extract/extract_proto_exe.py` | extract a prototype build's executable, allowing for its known deviations | Companion for one title's prototype discs and their specific deviations | project-only |
| `bfm_extract/extract_exe.py` | extract the console executable and hard-validate its name, size and header | Hard-validates one executable's exact name, size, hash and header field values | project-only |
| `make_snd_used.py` | list a sound library's address window and per-address exclusions | Hard-codes one executable's sound-library address window and per-address exclusions | project-only |
| `make_apicard_used.py` | list the interface library's objects and address window the executable actually links | Hard-codes one executable's interface-library address window and object roster | project-only |
| `cdtrace.py` | observe a live loader's requests to learn which payload loads where | Reads one game's loader request structures at fixed RAM addresses | project-only |
| `new_overlay.sh` | onboard one payload by its container and file-index naming | Takes one game's container and file-index naming as its command-line contract | project-only |
| `bfm_extract/pac.py` | parse a bespoke archive-chain header format | Parser for one game's bespoke archive-chain header format | project-only |
| `bfm_extract/cd_archive.py` | read a bespoke container's table of contents to locate its files | Reader for one game's bespoke container table-of-contents format | project-only |
| `bfm_extract/test_lzss.py` | unit-test a bespoke compression decoder against known cases | Unit tests for that game-specific compression variant | project-only |
| `bfm_extract/extract.py` | walk the whole medium and extract every file deterministically | Full-disc extractor bound to one disc's root file list and audio-track handling | project-only |

## Superseded — pointers only

| Tool | Superseded by | What it did |
|---|---|---|
| `audit_header_sigs.py` | `conform_decls.py` | Finds shared-header declarations that contradict the banked definition |
| `bank_exemplar.py` | `gate_stage.py` | Banks one cracked exemplar through the carve, splice and staged-recovery ladder |
| `bisect_slate.py` | `gate_main_parallel.py` | Isolates the byte-wrong drafts in a batch, with a null control first |
| `build_wave.py` | `draw_waves.py` | Builds the next wave from a card pool, ranked by fleet leverage |
| `build_wave_args.py` | `wave_args.py` | Emits workflow arguments for a wave from the target manifest, resolving each path |
| `canon_draft_decls.py` | `sig_unify.py` | Canonicalizes a draft's extern and data declarations to the banked-consistent set |
| `exemplar_miner.py` | `atlas.py` | Routes every residual stub to its lever and ranks the highest-reach work |
| `fix_header_decl.py` | `conform_decls.py` | Rewrites a shared-header caller declaration to a draft's byte-true signature |
| `gen_engine_decls.py` | `conform_decls.py` | Declares every shared function and data symbol once, canonically, in a generated header |
| `glm_parallel.sh` | `ox_campaign.py` | Splits a target list into slices and runs concurrent drafting workers against one endpoint |
| `idiom_loop.py` | `idiom_serial.py` | Never-ending meta-loop: drain the easy fuel, learn the next idiom, hand off |
| `jr_isolate.py` | `jr_isolate_all.py` | Isolates one switch function into its own code segment for an independent table carve |
| `lanes/bounce_drafter_on_queue.sh` | `lanes/relaunch_drafter_shell.sh` | Waits for the in-flight wave to queue, then restarts the drafting process |
| `p16_known_answer.py` | `p16_improve.py` | Graduated known-answer validation of the scaffold pipeline across difficulty bands |
| `plumbing_groups.py` | `gate_triage.py` | Groups recorded declaration-conflict failures into sweepable work groups from the ledgers |
| `reconcile_slate.py` | `pregate_check.py` | Drives a whole batch to declaration-compatible before any rebuild is spent |
| `recover_drafts.py` | `agent_drafts_restore.py` | Recovers agent-written draft files from a run's transcripts after they were deleted |
| `residual_rules.py` | `residual_rules_b.py` | Turns a measured residual into the specific documented lever that addresses it |
| `scan_leftovers.py` | `integration_resolver.py` | Re-verifies every draft already on disk and banks the free wins |
| `sweep_citations.py` | `gccmap_cites.py` | Deterministically localizes every compiler-source citation in a document against the pinned sources |
| `symcheck.py` | `reloc_verify.py` | Pre-gate guard diffing the symbol set a draft references against the target's |
| `t5_bank.sh` | `gate_wave.py` | Post-draft half of an agent wave: refuse if unsafe, judge each arm, bank the union |
| `t5_distill_args.py` | `distill_scan.py` | Builds the post-wave distillation slate from a wave's directories |
| `t5_targets.py` | `draw_waves.py` | Draws one routed slate from the frontier classes |
| `t7_bank.py` | `gate_stage.py` | Batch banking driver applying reconcile-at-bank-time plus the whole-binary gate |
| `treelock.sh` | `shared_lock.py` | The mutex wrapper for tree-writing campaigns, with status and stale detection |
| `wall_taxonomy.py` | `frontier_classify.py` | Census-classifies every unmatched residual by blocker class to size each avenue |
| `warmstart.py` | `permuter_sweep.py` | Feeds the permuter warm-start drafts built from banked exemplars and routed fuel |
