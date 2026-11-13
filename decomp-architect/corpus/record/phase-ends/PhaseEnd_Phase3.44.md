# PhaseEnd — Phase 3.44: Signatures from evidence (implements Gen 3.44)
Approved: 2026-11-12 | Closed: 2026-11-13 | Planner: claude-opus-5-5/medium | Tasks: 14 done, 0 superseded

## Milestone
Milestone: a fleet-wide asm signature census (`tools/sig_evidence.py`, one row per function or share class over all 218 binaries) records whether the return is used (a caller reads `$v0` after the call), the argument count (registers the callee reads, registers callers set, stack slots) and argument and return widths and signs, each with its cited instructions, and `unknown` with a reason where the asm cannot decide (indirect calls, liveness); every declaration and definition agrees with its measured contract or carries a ledgered exception whose cited instructions the tool verifies against the bytes (0 unledgered disagreements, gated in `make tools-health`), `config/lying_exceptions.tsv` causes included; the no-`return` functions parked from 3.43 T3 resolved (a byte-neutral `return` or a `$v0` comment from the census); R22 218/218; ghidra `--proof` PASS
Confirmed by the developer at the close.

## Tasks
- T1 — phase-start baselines and signature counts | Done: the 3.44 baselines and signature counts are measured at one HEAD, 46ae5c20a6. R22 is 218/218, tools-health is OK, and the I5 set is 356 names, the expected figure. Summary: The build and the full tool suite are green at the phase's starting commit. Every count the later signature tasks will be measured against is now recorded at that commit. The 356 return-less functions parked by 3.43 are exactly the ones the old scan listed, with no renames in between to account for. The sig-file numbers match the planner's exactly. The declaration scanner turned out to miss about 3,000 declaration lines, which the census work must cover. | commit: 46ae5c20a6 | tasks/T1.md | logs/T1.md
- T2 — type_census struct_map tie-break | Done: type_census's struct map no longer depends on which files hit its walk cache; cold, warm and partial-cache runs print the same `struct_map:` line (14376 types / 770 conflicts) and write a byte-identical docs/struct-map.md. Summary: The struct map's counts changed from run to run because the census merged its evidence in a different order depending on which source files had been re-read and which came from its cache. The merge is order-sensitive, since it refuses some merges based on what was merged before. The census now always processes files in one fixed order, and fresh and cached results have the same shape. The generated document also dropped its timestamp, so two runs on the same commit produce identical files. | commit: 23125e7899 | tasks/T2.md | logs/T2.md
- T3 — the asm signature census (tools/sig_evidence.py) | Done: tools/sig_evidence.py measures every function class's return use, arguments and width evidence from the original bytes over all 218 binaries in about 17 s, deterministically, with a 29-check selftest; rules and reasons in docs/ops/sig-evidence.md. Summary: The project now has a tool that reads the original machine code of every function and records, with the exact instruction as proof, whether callers use its return value, how many arguments it reads and its callers pass, and any sign that a value is a byte or a short. It is the measured contract that the next tasks compare the C against. Hand checks against the disassembler found one real bug (calls from modules into overlays were missed), which is fixed. One control assumed every known return lie narrows inside the callee; the bytes show six of them are conversions on the caller's side, now recorded in the lying ledger. 146 functions in main and resident are missing from the tool's input; closing that gap is the next task's first step. | commit: 231f3e07af | tasks/T3.md | logs/T3.md
- T4 — the C comparison, the exception ledger and the measured buckets | Done: `sig_evidence.py --compare` matches every census row to its C definitions and declarations in all 218 binaries, under six written rules; `--check` verifies the ledger's cites against the bytes. The buckets for T5-T8 are measured below. Summary: The tool that reads the original machine code now also reads our C. For every function it finds where each binary defines and declares it, and lists every place where the C contradicts the measured contract, citing the instruction. The 19 known exceptions now carry instruction cites that the tool re-checks against the game's bytes. There are about 198,000 disagreement rows over roughly 1,500 names, in six kinds; each kind has a proposed fix and a home among T5-T8. One kind looked twice its real size, because an empty function shared by 726 unrelated addresses counted as returning a value; that is now excluded with a written rule. | commit: 4c7567aa57 | tasks/T4.md | logs/T4.md
- T5 — the 19 width and sign return lies: one prototype and marked casts | Done: every function declaration (asm-label aliases included) now takes its definition's return type. 1,504 calls whose shipped caller read the return differently go through `RET_AS(T, fn, params)`, backed by 25 verified rows. DECL-RET is at 0 unledgered (8 ledgered SHARED-DECL-SPLIT rows), R22 218/218, tools-health OK. Summary: A function used to be declared with one return type in the callers and another at its definition. Now every declaration says what the definition says. Where the original game's compiled callers treated the result as a different width or sign, the call carries a small marked cast that names the view they used and is backed by cited instructions. Measuring through the asm-label aliases first grew the list from 27 names to 116, and all of them are now fixed or ledgered with evidence. Every build stays byte-identical. | commit: e4132c2252 | tasks/T5.md | logs/T5.md
- T6 — arity inconsistencies: one prototype and marked casts for `()` declarations | Done: every callee in T4's `()` bucket now has its one prototype at its declarations, with `KR_AS(T, fn)` at the 2,040 calls whose shipped caller passed a different count; the rest keep `()` with verified ledger rows. DECL-EMPTY 0 unledgered, R22 218/218, tools-health OK. Summary: Many functions were declared with empty parentheses, which tells the compiler nothing about their arguments. Each now carries the same full prototype as its definition, so a modder can trust it. Where the original game's code called a function with fewer or more arguments than it takes, the call is written through a small marked cast that keeps the old unchecked call, and every such function has a ledger row citing the instructions that prove it. A few declarations could not take one prototype (shared headers serving overlays whose definitions disagree, or a clashing wrong prototype elsewhere in the same file); those stay as they were, ledgered with evidence. Every build stays byte-identical. | commit: 594b66691e | tasks/T6.md | logs/T6.md
- T7 — I5: the parked non-void functions with no return | Done: every return-less non-void definition (I5's 356 names, RET-NONE 392 names / 8,966 sites) now returns a byte-neutral value, is `void`, or carries a `$v0 at exit:` comment; --compare RET-NONE 0; R22 218/218; tools-health OK. Summary: Many functions were declared as returning a value but never returned one. Where the value was already sitting in the return register, the function now says so with a real `return`, and the compiled bytes are unchanged. Where no caller in the original game ever looks at the value, the function is now `void` everywhere it is declared, again without changing a byte. Where neither was possible without changing the game's code, a comment at the function says what the return register holds and which instruction a fix would move. | commit: 74f9e81813 | tasks/T7.md | logs/T7.md
- T8 — the remaining measured disagreements | Done: every T4 disagreement outside T5-T7 is fixed or ledgered with verified cites: `sig_evidence --check` rc 0 (0 unledgered, 0 failed cites, 0 unused rows); the 13 PsyQ library names' declarations match the PsyQ 4.0 headers; R22 218/218; tools-health OK. Summary: Functions written as returning nothing, whose result the original game's callers did read, now return a value everywhere they are declared, mostly by passing on the result of the function they end with. Declarations that listed more or fewer arguments than the function takes now list exactly what its definition takes, and definitions that read arguments they did not declare now declare them. The few odd calls the shipped game really made are kept through a marked cast. The Sony library functions are now declared as Sony's own headers declare them. Every build stays byte-identical. | commit: 5dea03cae7 | tasks/T8.md | logs/T8.md
- T9 — the signature gate in tools-health | Done: `make tools-health` runs sig_evidence --selftest, a fresh census and --check after type_census, and is OK; the gate is proven to fail on a retyped declaration and on an altered ledger cite. Summary: The check that every function declaration agrees with what the original machine code shows is now a standing gate, run in the project's health ritual, so any future edit that breaks a prototype or a cited exception fails at once. It costs about a minute and a half of a twenty-minute run. The project's standards now carry this bar as rule 6, and the tool's doc explains how to read a failure and how to add a verified exception. | commit: 1eb2443f9e | tasks/T9.md | logs/T9.md
- T10 — milestone gate (Phase 3.44) | Done: every 3.44 milestone leg is green at one commit, 8bac8eee31, from a clean source tree. The readability, lever and timeline series carry the "P3.44 T10: milestone gate" rows, and the ledgers are backed up. Summary: The whole game still rebuilds byte-identical (218 of 218), and every health check passes, including the new one: each function declaration agrees with what the original machine code shows, or has an exception whose cited instructions are re-checked against the game's bytes. The six Ghidra databases rebuild and prove identical to the hand-made record. The public-file audit is clean. Of the 206 shared-body exceptions that were blocked because copies disagreed on a return type, 88 no longer disagree. Only one of those was fixed by this phase; the other 87 were fixed earlier. All 88 can be retried for sharing later. | commit: 8bac8eee31 | tasks/T10.md | logs/T10.md
- T11 — phase-close docs: story, retrospective, wiki, README (Phase 3.44) | Done: story §10 has its Phase 44 part and §11 the P3.44-close snapshot; retrospective §7 runs to Phase 44 in all four paragraphs; the wiki carries Phase 44 in next-steps rule 4 and a modder section on the signature census; how-to 03 gains the measure-from-asm lesson; timeline and progress regenerated; doc_links --strict 0/0. Summary: The public record now tells the signature phase in plain words: what a signature census is, why matching bytes never proved the prototypes, what `unknown` means and how the 198,029 disagreements came to zero. A modder has a wiki section explaining each census verdict, how to regenerate it, and how to read an exception row and its cited instructions. The day-1 guide tells a new project to measure prototypes from the assembly from the start, and that a narrowing beside a call is the C's own conversion under this compiler. | commit: - | tasks/T11.md | logs/T11.md
- T12 — phase cleanup (Phase 3.44) | Done: the one reusable piece of .run/3.44/ (the per-object scratch-compile compare harness) is the tool tools/scratch_cmp.py with a dictionary row and corpus copy; the rest of .run/3.44/ (11 GB of scratch) is deleted except logs/. Summary: Every signature batch this phase was checked by compiling each touched object twice, once from the last commit and once from the edited tree, and comparing the bytes. Each coder re-copied the same small scripts to do this, about twelve times. That check is now one project tool, so the next phase's struct merges can run it directly. Everything else left in the phase's scratch folder was one-off measurement whose results already live in the task summaries, the cookbook or tracked logs, so it was deleted. | commit: - | tasks/T12.md | logs/T12.md
- T13 — backfill 3.43's naming lessons into the day-1 guide and wiki; a names series and README graph | Done: how-to 03/10 and the wiki carry 3.43's naming lessons; the readability series has names columns (cited, guess_, other, placeholders, with unit denominators) and a README graph, all generated by readability_progress.py. Summary: The day-1 guide now tells a new project to start a names ledger from its first match. A name is cited only from a recorded source, and every name a model words is a marked guess with its basis. The rename tool must handle one binary at a time before the first rename, every scan needs a time limit, and a naming phase should be planned only after counting how many names have outside evidence. The readability series now also counts names: of 92,486 distinct function bodies, 513 are cited, 285 are guesses and 91,460 still have placeholder names. Of 98,448 data units, 39 are cited, 108 are guesses and 98,095 are placeholders. A new graph beside the timeline in the README shows these counts. | commit: 4a933a37cd | tasks/T13.md | logs/T13.md
- T14 — a signatures series and README graph, and the day-1 prevention lesson (rule T5) | Done: the readability series carries 10 signature columns from `sig_evidence --check`, backfilled for T4-T8 and T10, with a README graph; how-to 03/10 and retrospective §7 P44 say how a new decomp prevents the signature debt from day 1. Summary: The project's readability record now tracks how far the C's function declarations disagreed with the original machine code. It starts at about 198,000 disagreements when the measurement landed and falls to none left unexplained by the end of the phase, with the explained exceptions counted beside it. A new graph in the README shows that drop. The guide for new decomp projects now says how to avoid the debt from the first day: one shared header with one prototype per function, the machine-code signature check gating from the first matched function, no empty-parenthesis or old-style declarations, and every deliberate odd call written through a marked, recorded cast. | commit: 1243e3dd69 | tasks/T14.md | logs/T14.md

## Decisions that still bind
- T4 — the C is joined to binaries through build/src[/<alias>]/*.d (object -> files) and each binary's ELF symtab (name -> address); never by name alone (C0571, C0586).
- T4 — RET-VOID-READ needs a produced value: a class with exits and every exit writer `entry` returns nothing (C0587). Rows dropped: 106,202, all the empty body func_80014554's class.
- T5 — a callee's one prototype is its definition's. A different shipped view is written `RET_AS(T, fn, (params))` only at calls whose object needs it, and gets a ret_view_casts row with cites (exit writer plus caller read). Mismatches the cast cannot resolve stay in lying_exceptions. Documented in docs/ops/sig-evidence.md (Return views).
- T6 — a callee's one prototype is its definition's (asm-only: the census contract, arity max(arity_lb, sites.min), s32 or void * params). A call whose shipped caller passed a different count is `KR_AS(<def ret>, fn)(args)`, backed by a kr_view_casts row with cites (callee read of the missing arg or caller setup of the extra arg, plus the caller's jal).
- T6 — ledger def_file `-` means the callee has no C definition (lying_exceptions and kr_view_casts).
- T7 — the void rung's unit is all units of one name that share a declaration file, voided all-or-nothing; blocked when a declaration file also serves a binary with no unit of that name (R104 with C0571).
- T8 — a `void` callee whose $v0 callers read is widened with every declaration to the readers' type (one unit, R104); its body returns its tail call where neutral, else a `$v0 at exit:` comment.
- T8 — a struct/union returned by value counts one hidden argument word in $a0 (sig_evidence ARG-OVER).
- T8 — PsyQ library prototypes come from tools/reference/psyq-sdk/PSX/INCLUDE (4.0, the version main links).
- T9 — tools-health regenerates the census (`-j 16`) before `--check`, since make clean deletes build/sig_evidence/.
-

## Rules proposed
- T3 — none
- T4 — none
- T6 — none
- T7 — none
- T8 — none
- T9 — none
- T10 — none
- T12 — none

## Cookbook entries added
C0581 | C-declaration scanners: nested-paren and multi-line externs, KR heads, backtracking | declarations,arity,census,KR,scanner | 2026-11-12 | 3.44/T1 | 3.44 T1 counts
C0582 | A per-file walk cache must not decide the merge order: rebuild results in input order | determinism,cache,type_census,lever_census,union-find | 2026-11-12 | 3.44/T2 | -
C0583 | lwl/lwr in an asm data-flow: rt is a full write, not a read (false $v1 return reads) | asm,dataflow,rabbitizer,sig-evidence,census | 2026-11-12 | 3.44/T3 | P3.44 T3.c1
C0584 | Outgoing stack arguments from asm: a $sp+16 store counts only if never reloaded, below address-taken locals, contiguous | asm,arity,stack-args,sig-evidence,census | 2026-11-12 | 3.44/T3 | P3.44 T3.c1
C0585 | Cross-image calls: a module's splat stack omits its overlay; resolve outside-stack jal targets by function start | asm,call-graph,splat,md,overlay,sig-evidence | 2026-11-12 | 3.44/T3 | P3.44 T3.c2
C0586 | Join C files to binaries through build/ .d files and the ELF symtab | declarations,census,join,symbols | 2026-11-12 | 3.44/T4 | 3.44 T4.c1 --compare
C0587 | A body whose exits only pass entry $v0 through has no return to contradict void | return-type,census,void,delay | 2026-11-12 | 3.44/T4 | 3.44 T4 RET-VOID-READ profile
C0588 | Asm-label prototypes declare the label: parse ') __asm__("SYM");' tails, skip object labels | declarations,asm-label,census,parser,return-type | 2026-11-12 | 3.44/T5 | 3.44 T5.c1
C0589 | Scratch-compile a decl batch vs a HEAD baseline: make -n -B commands, exit-checked shards | bytes,scratch,compile,declarations,baseline,gate | 2026-11-12 | 3.44/T5 | 3.44 T5.c2
C0590 | Normalize .d dep paths (src/<b>/../shared) before matching edited headers | bytes,scratch,compile,dependencies,headers | 2026-11-12 | 3.44/T5 | -
C0591 | Import venv-re-exec tools only under .venv; type_census --check-casts needs --residue | tools,venv,sig_evidence,type_census,gate | 2026-11-12 | 3.44/T5 | -
C0592 | Return-type lies: one prototype = definition's; RET_AS(T,fn,params) marks shipped caller views | declarations,return-type,lying,bytes,macro,ret-view | 2026-11-12 | 3.44/T5 | -
C0593 | Asm-label definitions are invisible to name-keyed tools; registering them unmasks hidden arity rows | asm-label,declarations,argcheck,arity,return-type,tools | 2026-11-12 | 3.44/T5 | -
C0594 | KR_AS unprototyped view: one prototype for () callees, marked short/over calls | declarations,arity,k-and-r,macro,kr-view,bytes | 2026-11-12 | 3.44/T6 | 3.44 T6.c1
C0595 | Return-less defs at scale: driver loop, cast-view tail returns, if/else single return, census join traps | return-type,return,bytes,scratch,census | 2026-11-13 | 3.44/T7 | 3.44 T7.c1
C0596 | Voiding an unused-return function fleet-wide: joined units over shared decls, compile-error fallback, traps | return-type,void,declarations,bytes,scratch | 2026-11-13 | 3.44/T7 | 3.44 T7.c3
C0597 | RET-VOID-READ: widen a read void callee with its declarations, tail chains, trampolines | return-type,void,declarations,bytes,shared | 2026-11-13 | 3.44/T8 | 3.44 T8.c1
C0598 | Arity fixes: widen def vs narrow decls, pins to params, struct-return hidden word, residue bclass keys | arity,declarations,kr-view,residue,bytes | 2026-11-13 | 3.44/T8 | 3.44 T8.c2-c3
C0599 | Narrow over-count declarations to the def: () defs write (void), one kr row per name | arity,declarations,kr-view,bytes | 2026-11-13 | 3.44/T8 | 3.44 T8.c4
C0600 | PsyQ library prototypes from the 4.0 SDK headers; new SDK typedef traps | psyq,declarations,library,typedef,bytes | 2026-11-13 | 3.44/T8 | 3.44 T8.c5
C0601 | Prove a C-vs-bytes gate bites in a scratch worktree with no rebuild | worktree,gate,sig_evidence,fault-injection,check | 2026-11-13 | 3.44/T9 | P3.44 T9.c1
C0602 | tool_dictionary phase column: roadmap ids P1-P10 or PROJECT-ONLY, never P3.44 | kit-corpus,tool_dictionary,tools-health | 2026-11-13 | 3.44/T12 | 3.44 T12.c1

## Research
R3.44-001 | phase 3.44 planner, "Signatures from evidence": which ABI facts let an asm reader count args, widths, signs, and return use. | Calling-convention facts that decide asm signature measurement (gcc 2.7.2 MIPS, project flags) | gcc-2.7.2, mips, calling-convention, signatures, phase-3.44 | retriever-code | 2026-11-12 | 39 lines
R3.44-002 | 3.44 planner, Interfaces section (signatures from evidence) | Decl/def checking today and plug points for an asm-contract gate (3.44) | argcheck, type_census, lying_exceptions, dedup_exceptions, CAST macros, decl-rewrite tools, tools-health | retriever-code | 2026-11-12 | 64 lines
R3.44-003 | phase 3.44 Interfaces section: what inputs exist to read all 218 binaries and find callers per function | Inputs for tools/sig_evidence.py (fleet-wide per-function callers) | binaries, makefile, splat, sig, share-census, callers | retriever-code | 2026-11-12 | 80 lines
R3.44-004 | Digest of return-lie, return-less, and signature-fix records for planning phase 3.44 (Signatures from evidence) | Return-type lies, return-less non-void functions, signature fixes: facts for phase 3.44 | return-type,lying,lying_exceptions,argcheck,void-to-s32,return-less,I4,type_census,byte-neutral,cookbook | retriever-digest | 2026-11-12 | 53 lines
R3.44-005 | extract retrospective facts (wrong beliefs, failures, costs, end numbers, lessons) for docs/retrospective.md §7 P44 and docs/story.md §10 Phase 44 | Phase 3.44 retrospective facts from T2, T3, T5-T9 summaries | phase-3.44, retrospective, sig-evidence, RET_AS, KR_AS, tools-health | retriever-digest | 2026-11-13 | 68 lines

## Audit
- seed: median 29k, max 30k, n=15 (phase 3.44)
- previous phase 3.43: median 26k, growth 10.3%
- CLAUDE.md: 1304 bytes (unchanged)
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes (unchanged)
- .claude/skills/d1-snapshot/SKILL.md: 1396 bytes (unchanged)
- .claude/skills/pa-external-agents/SKILL.md: 11144 bytes (unchanged)
- .claude/skills/pa-planning/SKILL.md: 8419 bytes (+142)
- .claude/skills/project-architect/SKILL.md: 13748 bytes (unchanged)
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes (unchanged)
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes (unchanged)
- .claude/skills/tools-edit-kit-corpus/SKILL.md: 990 bytes (unchanged)
- .claude-state/memory/MEMORY.md: 60 bytes (unchanged)
- HOW_WE_WORK.md: 9867 bytes
- cookbook/INDEX.md: 259248 bytes
- rules/INDEX.md: 15941 bytes
### Carry audit — phase 3.44 (2026-11-12T17:40:36Z → open UTC, 1 sessions, 2711 requests)

| file (read) | chars | n |
|---|---|---|
| sig_evidence.py | 288.2k | 51 |
| rename_scan.py | 120.3k | 26 |
| argcheck.py | 106.2k | 17 |
| share_body.py | 89.1k | 8 |
| sig-evidence.md | 83.1k | 10 |
| type_census.py | 81.1k | 27 |
| readability_progress.py | 76.7k | 5 |
| TASK_PROGRESS.md | 64.3k | 4 |
| rename_sym.py | 52.2k | 7 |
| share_census.py | 39.3k | 15 |
| file (write) | chars | n |
|---|---|---|
| sig_evidence.py | 95.4k | 30 |
| phase-3.44.md | 49.2k | 1 |
| readability_progress.py | 21.0k | 14 |
| sig-evidence.md | 13.7k | 9 |
| count.py | 12.3k | 1 |
| cand.py | 11.5k | 2 |
| T4.md | 9.5k | 1 |
| T3.c2.md | 9.5k | 1 |
| result kind | chars | n |
|---|---|---|
| bash other | 2.5M | 1463 |
| Read | 1.8M | 443 |
| Grep | 641.7k | 326 |
| tools/plan_edit.py | 326.8k | 26 |
| tools/sig_evidence.py | 310.9k | 177 |
| run.sh | 182.6k | 250 |
| tools/type_census.py | 179.3k | 84 |
| tools/outline.py | 118.7k | 20 |
| tools/argcheck.py | 60.2k | 25 |
| tools/readability_progress.py | 42.6k | 12 |
- spilled: 6 results, 1.9M chars on disk, 0 read whole
- whole reads over 20.0k: 0
- seed floor: retriever-code 7,203 (n 21, prev 7,203) · retriever-digest 6,914 (n 14, prev 6,914) · retriever-web 5,367 (n 2, prev 5,367)
- outline credit: 36 outlines · 19 followed by a ranged read · 1.1M chars credited
- warm pings: 85 pings over 22 runs, 32 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 0, cost: pings $2.5566 + relay $0.0000 + re-arm $0.0000 = $2.5566 vs rewrites replaced $20.0478, cheaper than one rewrite: yes, undelivered 0
- toasts by cause (waiting): question 2, review 0, replan 0, permission 0, input 12, crash 9, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 751, relay 0, re-arm 0, other 10, relay cost $0.0000
- retriever re-asks: 0 of 1 retriever briefs repeat a lookup of the same run
- noise: 170 lines 13.5k chars — usage: : 134 lines/10.9k, No such file or directory: 36 lines/2.7k
- price: read $0.20/Mtok · 1h write $8.00/Mtok · output $19.99/Mtok (phase model mix)
- median requests after a read: 0
- carry/request: 2420 chars, 2711 requests (prev 3534 chars, 4141 requests, growth -31.5%)
- flag: 229 tool-source reads by pa-claude, pa-coder, pa-expert, retriever-code, retriever-digest
  /home/musashi/bfm-decomp/tools/sig_evidence.py  10.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  582 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  5.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  11.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ram_probe.py  1.2k chars  retriever-digest
  /home/musashi/bfm-decomp/tools/sig_evidence.py  5.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  5.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  4.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  7.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  14.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.2k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  5.7k chars  pa-expert
  /home/musashi/bfm-decomp/tools/decl_from_use.py  4.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/decl_from_use.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  3.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  13.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  4.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  4.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  9.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  9.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  1.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  1.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  10.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  56 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  13.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  8.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  11.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  9.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  14.9k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  1.2k chars  pa-claude
  /home/musashi/bfm-decomp/tools/lever_census.py  17.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  471 chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  19.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/readability_progress.py  23.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  8.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/readability_progress.py  23.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  8.0k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  4.2k chars  pa-claude
  /home/musashi/bfm-decomp/tools/progress.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/delever.py  1.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  8.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  5.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  8.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  5.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  23.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  149 chars  pa-coder
  /home/musashi/bfm-decomp/tools/readability_progress.py  14.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/timeline.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/readability_progress.py  14.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/timeline.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/readability_progress.py  170 chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  5.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/corpus.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  849 chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.1k chars  pa-coder
  /home/musashi/bfm-decomp/.claude/skills/d1-snapshot/SKILL.md  989 chars  retriever-code
  /home/musashi/bfm-decomp/tools/timeline.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/leverage_rank.py  292 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  4.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  7.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  12.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  14.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_mcp_start.sh  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_stop.sh  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_verify.sh  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_import.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_apply_symbols.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  2.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  10.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  10.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  3.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/DumpFunctionSignatures.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/decl_from_use.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  513 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  8.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  4.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  15.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  17.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  26.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  882 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  6.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  12.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  4.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  729 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.c  2.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.c  1.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  425 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  159 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  156 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/c-typeck.c  558 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/calls.c  499 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.c  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/calls.c  492 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/calls.c  430 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/calls.c  387 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/function.c  350 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/config/mips/mips.h  455 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  6.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  546 chars  pa-coder
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  3.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_apply_symbols.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_rebuild.sh  10.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_call.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_export_annotations.sh  968 chars  retriever-code
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  9.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  11.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/DumpFunctionSignatures.java  797 chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_rebuild.sh  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ImportAnnotations.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/sig_evidence.py  7.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  7.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  6.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  4.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  5.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  806 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  214 chars  retriever-code
  /home/musashi/bfm-decomp/tools/sig_image.py  7.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_image.py  7.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  4.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  3.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/dedup_integrate.py  833 chars  retriever-code
  /home/musashi/bfm-decomp/tools/shared_lock.py  736 chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  2.3k chars  pa-expert
  /home/musashi/bfm-decomp/tools/share_body.py  19.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  5.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  5.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  3.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  5.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  5.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  5.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  3.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/sig_evidence.py  7.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  2.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  757 chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  2.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  757 chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.4k chars  pa-coder

## Agent runs
- T1 | pa-claude | partner | claude-opus-5-5 | medium | ctx 181k | $5.074 | saved $21.20 | completed | parent 252d32b5
- T1 | pa-expert | expert | claude-opus-5-5 | medium | ctx 64k | $0.918 | saved $3.52 | completed | parent 252d32b5
- T1 | pa-coder | coder | claude-opus-5-5 | medium | ctx 78k | $2.001 | saved $0.61 | completed | parent a9234cc4
- T2 | pa-expert | expert | claude-opus-5-5 | medium | ctx 76k | $1.237 | saved $0.15 | completed | parent 252d32b5
- T5 | pa-claude | partner | claude-opus-5-5 | medium | ctx 139k | $2.640 | saved - | completed | parent 252d32b5
- T3 | pa-expert | expert | claude-opus-5-5 | medium | ctx 149k | $4.543 | saved $7.06 | completed | parent 252d32b5
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 137k | $3.156 | saved - | completed | parent a68cd759
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 169k | $3.964 | saved - | completed | parent a68cd759
- T4 | pa-expert | expert | claude-opus-5-5 | medium | ctx 168k | $3.471 | saved $21.54 | completed | parent 252d32b5
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 143k | $3.367 | saved $3.00 | completed | parent a86e7dad
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 96k | $2.224 | saved $1.85 | completed | parent a86e7dad
- T5 | pa-expert | expert | claude-opus-5-5 | medium | ctx 134k | $2.799 | saved $13.34 | completed | parent 252d32b5
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 91k | $1.513 | saved $2.88 | completed | parent ab4c2416
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 48k | $0.732 | saved - | completed | parent ab4c2416
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 76k | $1.244 | saved - | completed | parent ab4c2416
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 44k | $0.380 | saved - | completed | parent ab4c2416
- T14 | pa-claude | partner | claude-opus-5-5 | medium | ctx 137k | $3.063 | saved - | completed | parent 252d32b5
- T5 | pa-expert | expert | claude-opus-5-5 | medium | ctx 144k | $3.557 | saved $31.05 | completed | parent 252d32b5
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 106k | $2.650 | saved $1.48 | completed | parent ae6dda2b
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 175k | $5.102 | saved $0.03 | completed | parent ae6dda2b
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 40k | $0.491 | saved $0.32 | completed | parent ae6dda2b
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 72k | $3.100 | saved - | completed | parent ae6dda2b
- T6 | pa-expert | expert | claude-opus-5-5 | medium | ctx 127k | $2.779 | saved $20.92 | completed | parent 252d32b5
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 118k | $2.316 | saved $0.41 | completed | parent a15ccf70
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 175k | $4.355 | saved - | completed | parent a15ccf70
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 147k | $3.451 | saved $0.61 | orphaned | parent a15ccf70
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 62k | $0.962 | saved - | completed | parent a15ccf70
- T7 | pa-expert | expert | claude-opus-5-5 | medium | ctx 131k | $3.517 | saved $24.70 | completed | parent 252d32b5
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 88k | $1.800 | saved - | completed | parent aeb4ee89
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 78k | $1.608 | saved $0.06 | completed | parent aeb4ee89
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 115k | $2.868 | saved $1.72 | completed | parent aeb4ee89
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 41k | $0.592 | saved $0.24 | completed | parent aeb4ee89
- T8 | pa-expert | expert | claude-opus-5-5 | medium | ctx 140k | $3.356 | saved $33.36 | completed | parent 252d32b5
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 135k | $3.241 | saved - | completed | parent ac673f52
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 310k | $13.489 | saved $1.22 | completed | parent ac673f52
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 100k | $2.251 | saved - | completed | parent ac673f52
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 82k | $1.422 | saved - | completed | parent ac673f52
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 134k | $4.304 | saved $1.83 | completed | parent ac673f52
- T9 | pa-expert | expert | claude-opus-5-5 | medium | ctx 95k | $1.516 | saved $0.71 | completed | parent 252d32b5
- … 10 more: PY ~/.claude/pa3/pa_ledger.py report

## Discussions
- I7 | -> Gen 4 Name the text-slot helpers func_8001534C, func_800153CC, func_80015498 and the sweep test func_80133784 (3.43 T | deferred:gen4

## Deferred
- from T14: `--snapshot` now runs `sig_evidence --check -j 16` (~1 min; census first if build/sig_evidence/census.jsonl is missing, as after `make clean`). (unconsumed)
- I7 (deferred:gen4): -> Gen 4 Name the text-slot helpers func_8001534C, func_800153CC, func_80015498 and the sweep test func_80133784 (3.43 T

## Changes
- 2026-11-12 router: T1 next -> done
- 2026-11-12 planner: added T13 — backfill 3.43's naming lessons into the day-1 guide and wiki; a names series and README graph
- 2026-11-12 router: T2 next -> done
- 2026-11-12 claude: T3 question: control (4) part one accepted as measured: the census agrees with objdump on all 19 lying callees; 11 show callee narrowing, and for 8 (func_8002A27C/4C8/738/9A8, func_800167F0, func_801633A8, func_80188F10, guess_RequestSound) the bytes show a caller-side conversion instead, so their ledger cause is caller-side. The 146 functions with no sig row (main 73, resident 73; e.g. main 0x8002A26C-0x8002A28C) go to T4 as its first step: give them census rows before the bucketing.
- 2026-11-12 router: T3 next -> done
- 2026-11-12 router: T4 review: T5 first extends sig_evidence --compare to asm-label aliases (__asm__ declarations and aF*/ta* definitions, C0223) and re-measures; then DECL-RET in 3 batches: func_80028D9C probe, the 18 other ledgered, the 8 new (func_80145CEC, func_80178BF8, func_8017BE60, func_80139BE0, func_8017BEBC, func_8017ED5C, func_8017F730, func_80173544)
- 2026-11-12 router: T4 review: T6 = DECL-EMPTY in 2 batches: A unmarked () 255 names / 28,795 lines (definition prototype; marked cast where callers pass fewer), B K&R-marked 205 names / 4,937 lines (marked casts)
- 2026-11-12 router: T4 review: T7 = RET-NONE 392 names / 8,963 defs (I5 356 + 38 SHARED_FN own names - 2): batches by census verdict used 29, unused 67 (void rung under R104), unknown 302 in 3 chunks
- 2026-11-12 router: T4 review: T8 = RET-VOID-READ 73 names / 91,633 decl lines; DECL-ARITY 607 names / 6,871 lines (widen def: 192 names; narrow decls: 432 names); ARG-OVER 30 names (widen def; GsTMD* PsyQ prototype; split-row artifacts ledgered). The 40 PsyQ IMPORTED names in main (59,467 decls) get no census rows; instead T8 checks every declaration of them against the PsyQ library headers' prototypes (developer 2026-11-12) and fixes or ledgers any disagreement, counted apart. The rule table in docs/ops/sig-evidence.md is approved with the empty-body amendment.
- 2026-11-12 router: T4 next -> done — developer approved the T4 review
- 2026-11-12 router: T5 next -> done
- 2026-11-13 router: T6 next -> done
- 2026-11-13 router: T7 next -> done
- 2026-11-13 router: T8 next -> done
- 2026-11-13 router: T9 next -> done
- 2026-11-13 router: T10 next -> done
- 2026-11-13 planner: added T14 — a signatures series and README graph, and the day-1 prevention lesson (rule T5)
- 2026-11-13 router: T11 next -> done
- 2026-11-13 router: T12 next -> done
- 2026-11-13 router: T13 next -> done
- 2026-11-13 router: T14 next -> done

## Plain-English Recap
Phase 3.44 (Signatures from evidence) is closed with its milestone met. The gate passed at 8bac8eee31: R22 218/218 run alone; tools-health OK, now including the signature gate; sig_evidence --check 0 failed, 0 unused, 0 unledgered; type_census unledgered lying 0; share_census strict OK; lever_census --check --strict --residue OK; ghidra_rebuild --proof PROOF PASS on all six programs; doc_links and audit_public clean; ledger_backup run (archive commit 05feeb4, unpushed).

What it built: tools/sig_evidence.py, an asm signature census over all 218 binaries (about 17 s at -j 16; 92,716 classes: used 11,345, unused 18,026, unknown 63,345, each unknown with a reason). --compare checks every C declaration and definition against it under six rules, and --check verifies every ledger cite against the bytes. The 198,029 disagreements T4 measured went to 0 unledgered:
- T5: return widths (116 names after the asm-label fix), with RET_AS marked casts backed by config/ret_view_casts.tsv;
- T6: `()` declarations, with KR_AS backed by config/kr_view_casts.tsv;
- T7: 392 non-void functions with no return, given a byte-neutral return, void, or a `$v0 at exit:` comment;
- T8: void-read, arity, arg-over, and the PsyQ declarations aligned to the PsyQ 4.0 headers.
3,264 ledger rows remain, all facts about the shipped game (mostly SHARED-DECL-SPLIT `()` declarations). The signature gate runs inside tools-health and adds about 86 s. Other work: type_census's struct_map tie-break was fixed so its counts are deterministic (T2); tools/scratch_cmp.py was promoted from twelve coder copies (T12); the readability series gained names columns and signature columns, each with a README graph (T13, T14); the day-1 guide gained 3.43's naming lessons and 3.44's measurement and prevention lessons; story §10, retrospective §7 and the wiki run to Phase 44, and the wiki has a modder section on reading the census.

Open items:
- 88 RETURN-LIE dedup rows are now cleared for sharing; recommended to retarget to 3.46 (layout) rather than 3.45.
- lever_census.py:864-875 has the same cache-order nondeterminism T2 fixed (C0582).
- The ram_probe scenario list (R128) is still owed to the developer.
- After the close, Claude runs tools/ghidra_mcp_start.sh and asks the developer for /mcp.
- The developer pushes the repo and the archive clone (05feeb4).
