# T7, one agent at a time — the brief (Phase 36 S101, Drew 2026-09-09: "spawn one agent at a time, hone the methodology each time one lands")

You are given ONE residue exemplar of the Brave Fencer Musashi decompilation (PS1, gcc 2.7.2 `-O2 -G0 -mips1 -mcpu=3000 -msoft-float`).
Repository: /home/musashi/bfm-decomp. Your pack is `PACK` (a directory). Read every file in it first:
`tu.txt` (the translation unit and the function), `body_tree.c` (the function as the tree has it — the `register … __asm__("$N")` pins
and `__asm__` statements are the LEVERS, each marked `// !FAKE:`), `body_free.c` (the same function with every lever rewritten away —
your STARTING TEXT), `residual.txt` (what the lever-free function compiles to versus the original bytes: the score is an edit distance
over the instructions, the class says whether registers, the instruction count or the order differ, and every differing block is
printed as mnemonics, mine | target), `sites.txt` (which levers the byte oracle judged NEEDED), `history.txt` (what the mechanical
search already tried — every move that reached the best score).

THE GOAL: a spelling of this function in plain C — no register pin, no `asm` statement of any kind, no `volatile` ADDED (a `volatile`
cast or declaration already present in `body_free.c` may stay), no `__builtin_*` added — whose compiled instructions are byte-identical
to the original's. Readability counts: this is a readability phase; prefer the smallest, most natural source change that reaches the
bytes (a declaration's width or order, a temp named or inlined, two statements exchanged, a parameter routed through a local, a block).

HOW TO WORK (the method we are honing — follow it and report where it fell short):
0. **READ `PACK/neighbours.txt` FIRST.** It carries the comment headers of the already-matched functions next to yours in
   the same translation unit, and every `@class:` / `@stuck:` / `@crack:` note in that file. This project has been leaving
   itself notes for months: one agent closed its body on its FIRST `--try` because a sibling's header spelled the whole
   crack out in English. Also `grep -n <a global your body touches> <the tu>` to find the other functions that use it.
1. READ THE RESIDUAL before touching the source. Name what differs: which registers, which instruction is extra or missing, what
   moved. Then name the compiler decision that produces it and the pass it lives in, from the compiler's own source:
   `tools/reference/gcc-2.7.2/` (the exact source of the pinned cc1) — `local-alloc.c` (`block_alloc`, `combine_regs`, `qty_compare`,
   `update_equiv_regs`), `global.c` (`allocno_compare`, `find_reg`), `cse.c` (`insert_regs`, `canon_reg`, `find_best_addr`,
   `note_mem_written`), `combine.c` (`can_combine_p`, `try_combine`), `sched.c` (`rank_for_schedule`, `adjust_priority`,
   `birthing_insn_p`), `reorg.c`, `flow.c`, `reload1.c` — and the project's map of it: `docs/gcc-2.7.2-map/` and, above all,
   `.run/P36/engine/residual_moves.md` (58 residual-class → source-move rows, each with the pass, the decision `file:line`, the
   mechanism and how to test it; its Verification ledger at the end says which were proven on bytes). Grep the cookbook by section for
   the byte-proven idioms: `grep -n '^## §455\|^## §454\|^## §501' docs/matching-cookbook.md` then `sed -n` the range (the file is
   3.5 MB — never read it whole); §455 is this engine, §454 its instrument lessons, §501-E/P/Q/R the Phase-32 crack methods (a
   reproducer battery before the real function; the allocation ORDER read before any register lever: **`tools/alloc_table.py
   <tag> <fn> <dump_root>`**, fed by **`tools/cc1_dumps_tu.sh`**). **READ THE ALLOCATION TABLE FIRST FOR ANY REGISTER
   RESIDUAL.** It prints every pseudo with refs, live length, block, conflicts, copy preferences and `allocno_compare`'s
   priority, and it asserts its own coverage against the `.greg` order line — four agents in S102's burst asked for exactly
   this and two were handed an empty table by the old version, which only ever printed callee-saved holders. It settles
   arguments the residual cannot: one body closed by moving a priority 6524 past 6666, another by shortening a live length
   from 44 to 43 — arithmetic on these columns, not a search. Note the `.greg` dump carries the INPUTS to global allocation
   (order, conflicts, preferences) and not the final assignment, so a global allocno's hard register prints as `-`.
   Also: the residual text alone cannot tell you whether an INSTRUCTION IS MISSING or the REGISTERS ARE WRONG — one agent
   chased a register lever for hours when the defect was a cse store-to-load forward that deleted a load. Count first.
2. TEST EVERY HYPOTHESIS ON BYTES, in your own scratch, never in the tree: write the whole function to `PACK/body.c` and run
   `.venv/bin/python tools/delever_search.py --try <tu> <fn> PACK/body.c --body` — it compiles a scratch copy of the translation
   unit through the real build recipe and prints the score and the mnemonic diff; score 0 = the function is byte-identical (the
   coordinator then banks it through the whole-object gate). One compile is ~0.3 s; try as many spellings as the reading suggests.
   Dumps of the compiler's passes for a hypothesis: copy the TU to a scratch dir and run cpp + cc1 with `-dl -dg -dS -dc -dj -df`
   (the command shape is in `.run/P36/engine/micro/dowhile/` and `tools/cc1_dumps_tu.sh`); the `.lreg`/`.greg` dumps show the
   allocation order and `used N times across M insns`, `.sched` the priorities.
3. WRITE YOUR DELIVERABLES EARLY and keep rewriting them (an agent lost to a limit has to be resumed; the one that wrote first banked):
   `PACK/body.c` — your best function text so far (whole definition, header to closing brace), updated after every improvement;
   `PACK/mechanism.md` — (a) the residual in one sentence, (b) the pass and the decision with `file:line` you read, (c) the source
   move(s) that closed it (or got closest), (d) a GENERATOR PROPOSAL: the mechanical rule a tool could apply to other functions with
   this residual class ("when the diff is <shape>, try <rewrite> on <which statement/declaration>") — this is what turns your one crack
   into a family, (e) what you tried that did NOT work and why (byte evidence), (f) where the method above fell short.
   Every claim about a pass is a hypothesis until `--try` shows the bytes; say which claims you proved and which you did not.
4. Do NOT: run `make`, edit anything under `src/`, `tools/`, `docs/` or `config/`, run any git command that changes state, write
   outside PACK. **This includes your own helper scripts, dumps and probe directories: put them in `PACK/scratch/`, never in the
   session scratchpad or any shared `/tmp`-like directory.** Agents run in PARALLEL and share those directories: three agents in
   S102's burst had their helper scripts overwritten mid-run by another agent, and two of them scored candidates against ANOTHER
   agent's function before `--try`'s echo of the TU and function name gave it away. If a `--try` fails with an error that is not
   about your own text (an unrelated header, a function that is not yours), RETRY IT ONCE before believing it. If the bytes will not close, stop at your best score with the mechanism written — a precise reading of why is worth
   more than a lever put back.

Report back: the final score, the move(s) in one line each, the mechanism (pass + `file:line`), the generator proposal in one
sentence, and the paths of `PACK/body.c` and `PACK/mechanism.md`.
