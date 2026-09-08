# The matching workflow — draft → gate → bank

> **Which tool answers which need:** the [tool index](../tool-index.md) lists every tool by the need it answers, with what proved it and what it hard-codes.

## The definition

A function is **matched** when its compiled output is instruction-identical to the original, register allocation
included, *and* the whole binary still hashes to its recorded SHA1 with that function compiled from source (rule G3).
"Functionally equivalent" is never matched; a passing-looking diff is never matched; a closeness score is never matched.
Every other signal in the workflow is a filter feeding that gate, and each filter is blind to something.

## The oracle ladder

| Oracle | What it proves | What it cannot see |
|---|---|---|
| [`tools/match_one.py`](../../tools/match_one.py) — compile ONE function standalone with the pinned triple, mask relocations (`jal`/`j` targets, `%hi`/`%lo` immediates), compare to the target's bytes from splat's `.s` | the instruction **shape** matches | symbol identity (masked), the declarations the real translation unit imposes, the file's optimization level |
| [`tools/rtu_match.py`](../../tools/rtu_match.py) — splice the candidate into the WHOLE split `.c` with every other function's `INCLUDE_ASM` neutralized, compile the real TU | the body matches *in its real declaration context* (types, the canonical-signature layer, file-scope globals) — far closer to the gate than a standalone compile | link-time symbol identity |
| **The whole-binary gate** — substitute the draft, build the binary, compare its SHA1 to `config/check.<alias>.sha` | **everything** | nothing; this is the arbiter |

The two failure modes the table exists to prevent were both observed: a clean standalone MATCH that could not link
(it named a symbol that does not exist — the mask hid it), and a standalone mismatch on every instruction because the
probe compiled at the wrong optimization level. An oracle must state what it cannot see, in its own output.

## The gates

- **Overlays and modules** are gated in parallel, each in its own git worktree, so one carving worker cannot corrupt
  another's `asm/` ([`tools/parallel_gate.py`](../../tools/parallel_gate.py); the older per-draft loop is
  [`tools/harvest_verify.py`](../../tools/harvest_verify.py), which bisects a batch on failure). A gate that starts on a
  dirty tree cannot tell your edits from its own, so the tree must be clean first.
- **The main executable is gated only by a clean rebuild** ([`tools/gate_main.py`](../../tools/gate_main.py)). Its extract
  step rewrites the linker script, so an incremental build after a source change produces a *false diff* — this cost the
  campaign a night and a written-up "linker defect" that did not exist, until a control with no draft at all reproduced
  the same wrong hash. One clean rebuild verifies a whole batch of drafts (about 15 s when the batch is clean), bisecting
  when it is not.
- **After any bank, the fleet is verified from clean** — `make clean && make extract-all && make check-all` — never with
  a bare incremental `make check-all` (rule R22; an incremental check once reported a false 211/213). Propagation to other
  binaries is not itself byte-gated, so a propagating bank is followed by the fleet run.

**Bank = commit immediately** (rule R42): before the next command that can touch `src/` — a gate is one. A gate once
destroyed 61 uncommitted banks. "Banked" is written only from the tool's printed success line (R66), never from the
intent to bank.

## Where drafts come from

1. **Free work first.** A function that already exists byte-identically in another binary is a remap, not a draft
   ([The dedup engine](The-dedup-engine.md)); a same-shape sibling is a family remap; a stored draft that once matched a
   twin is re-verified rather than redrafted. The twin graph changes after every bank, so
   [`tools/twin_rescan.py`](../../tools/twin_rescan.py) runs after every gate that banked. Every project has this
   zero-token tier; it is run before any paid one.
2. **A scaffold.** m2c over Ghidra's decompilation, seeded with the project's names; useful as a starting shape, rarely
   byte-exact on its own for this compiler.
3. **Agents with a card.** The unit handed to a model is a *card*: the target's disassembly and destination file, what
   that file already declares, the project-wide declaration consensus for every callee, a matched sibling when one
   exists, the function's own past-attempt history, and the lever the atlas believes applies — with where to read
   about it. Cards are assembled deterministically at zero token cost
   ([`tools/claude_wave_packs.py`](../../tools/claude_wave_packs.py)); the procedure, each guard paired with the
   measurement that earned it, is [`docs/wave-playbook.md`](../wave-playbook.md). Models are routed by size (a cheap
   tier up to ~50 instructions, a mid tier to ~120, the strongest above), and their verdicts are filters, never the gate.
4. **The permuter for near-misses.** [decomp-permuter](../../tools/decomp-permuter/) with the project's relocation-masked
   scorer and warm-restart wrapper ([`tools/permuter/`](../../tools/permuter/)): LLM-free, CPU-bound, it randomizes the C
   of a close draft to close register-allocation and scheduling residuals. A permuter score is not a closeness until its
   diff is read (R63).
5. **Reading the compiler.** For a residual no lever reaches, the answer was found by reading the gcc 2.7.2 pass that
   emits it — the codegen map ([`docs/gcc-2.7.2-map/`](../gcc-2.7.2-map/), cookbook §31) names the pass, the residual
   pattern and the C-level lever, and the last functions of the project fell to five-line reproducers compiled with
   `-da` dumps rather than to more variants of the 500-instruction function ([chapter 07](../how-to-ai-decomp/07-compiler-source.md)).

## Matching by hand

Most of the fleet was matched by agents under the wave machinery; the hand loop is what those agents ran inside, and it
is what a person runs on the residue. It was written down mid-project as a guide for the struct-heavy engine core
(cookbook §16 and §17, the compiler-quirk toolkit); this is the part of it that stayed true.

**Two decompiles, and the assembly as arbiter.** Use both Ghidra's whole-program decompile and m2c's, not one chained
pipeline: Ghidra resolves locals against globals and callee identities from the whole binary, which m2c lacks; m2c
gives the better starting shape. They disagree, and the assembly decides — one made a struct of what the other made
separate globals, and the reuse of one `lui` base settled it. Two mechanics that cost time: the MCP server must be
serving the *overlay* (`tools/ghidra_mcp_start.sh <alias>`, then `/mcp`, R29) and its decompile is asynchronous (poll
the task); and the decompile wrapper hardcodes the main executable, so an overlay is decompiled by calling m2c
directly (`tools/m2c/m2c.py -t mipsel-gcc-c -f <function> --context <ctx> <file.s>`).

**The loop.** Standalone probe (`tools/match_one.py <fn> --c <draft> --asm-subdir asm/<alias>/nonmatchings/<alias>`)
until the shape matches; the real-TU probe; the gate. A red gate is a hash, not a diagnosis — substitute the draft into
a copy of the destination file and read the compiler's first conflict:
`make build BINARY=<alias> 2>&1 | grep -iE 'conflicting|redefin|error'`.

**The five signature moves.** The wall the project first called "fundamental" was a *signature-consistency* problem,
and it dissolved under byte-neutral canonical widening plus the codebase's own cast idioms, applied surgically — a
blanket declarations header broke loose matches (Phase 16); per-callee, byte-gated canonicalisation worked.
1. *Return widening.* A function with no explicit `return` compiles identically as `void` or `s32`, so widening the
   canonical return type is free fleet-wide; the mechanizable predicate: a `void` function whose result some call site
   uses → widen to `s32` everywhere.
2. *The sign cast at the use site.* Keep the canonical `s16`; write `(u16)D_X` where the assembly loads `lhu`.
3. *The arity cast.* `((ret (*)(argtypes))func_X)(args)` at a call whose arity the canonical signature does not carry.
   Its boundary is default argument promotion: pointer arguments cast safely, narrow scalars did not — until the K&R
   `s16`-parameter definition form dissolved that wall too (cookbook §43).
4. *Canonical-matching the target's own parameters.* If the consensus signature passes an address as `s32`, take it as
   `s32` and access through `*(s32 *)(arg + 0xNN)` — the int-to-pointer cast is byte-neutral.
5. *Function-pointer-table typing.* `extern void (*D_x[])(argtypes);` turns an indirect-dispatch residual class from
   "cannot express" into "compiles".
The layer lives in the overlay's own `.c` file, never in the shared header (a reach-1 name would collide across 134
overlays). Two width facts: **types are byte-neutral for matching** — the compiler reads the access width off the
instruction (`lh`, `lbu`, `lw`), not off a struct, so recovered structures help comprehension and not the byte-close —
while **the widths of locals and parameters are not**: a value loaded with `lh` wants an `s32` local, because an `s16`
local adds a redundant `sll`/`sra` re-extension.

**Choosing what to hand-match.** Sorting candidates by *ascending* scaffold mismatch selects for the compiler-quirk
tail (the scaffold already got the structure right, so only a codegen quirk remains); clean closes came from
function-pointer calls, relocation-free few-call bodies, and mis-structured-but-fixable scaffolds. The tractable shape
was ≤ 80 instructions and ≤ 4 calls. The progress metric was function-count-weighted, so a giant banks more bytes for
the same percentage — "fewest largest" has no edge — and declaration work removes friction without unlocking matches:
there was no "magic five that unlock hundreds". Match shared callees before their callers, so the definition fixes the
signature fleet-wide, and watch for the circular callee — a residual that is also a callee in other drafts broke three
of them at once.

**Running it as a wave.** Parallel agents manufacture signature conflicts: one wave's whole gap between standalone
matches (60%) and whole-binary banks (33%) was compile errors — every one a callee declared differently by two drafts
in the same translation unit, and zero codegen mismatches. Hence the order *draft → normalise the declarations
(`tools/sig_unify.py`) → gate*, a gate that batches at chunk size 1 when the failure class is signature conflicts
(a batched bisect blames a good draft for another draft's clash), and a recovery pass that re-normalises the failures
and re-gates. Pre-decompile the targets headlessly rather than through live MCP contention (stop the server, then
`analyzeHeadless … -noanalysis -postScript DecompileFunctions.java`; rename Ghidra's lowercase `FUN_` outputs to the
project's `func_` form; Ghidra's program ids are opaque, so map the alias first). The harness's workflow `args`
channel does not transit arrays — embed the target list in the script. Filter agent scratch (`_try`, `_v2`) to the
canonical draft name before gating, and make "no draft" a valid result: agents told to write a file *only on a
standalone match* diagnosed twelve of thirty quirk walls precisely and correctly wrote nothing. Propagation is itself a
fail-closed byte gate — it authors the shared macro body, registers the group, and its `--auto-from` sweep catches any
earlier inline match never propagated — and a propagated body ships its signature change to every member.

## The knowledge base, and feeding it

Before each match, consult [`docs/matching-cookbook.md`](../matching-cookbook.md) (grep it by symptom through
[`docs/cookbook-index.md`](../cookbook-index.md)); after each match, write the generalizable lesson back into the
cookbook *and* into the tooling, so the next similar function is a one-shot (rule R16). Two laws learned at cost: only
harvest lessons from byte-proven results, and strip a credited lever from the accepted body and recompile before it
enters the base — one in three credited levers was byte-inert.

## Integration is the bottleneck

Once cracking became systematic, the dominant cost was **banking** a byte-correct body past the real translation unit:
declaration conflicts, file placement, symbol spellings, jump-table carves, mixed optimization levels. At one measurement
about 92% of drafts were byte-correct and about 27% banked. The reconcile ladder — declaration sync, callee casts,
canonical-signature reconciliation, carve tools — is the part every project under-budgets;
[chapter 10](../how-to-ai-decomp/10-integration-and-propagation.md) is about it.

## What this means for a contributor today

The frontier is empty; there is nothing left to match. Every change to `src/` — a struct in place of a raw address, a
name in place of `func_80144B9C`, a reshaped loop — is held to the same invariant: `make check BINARY=<alias>` stays
green for every binary the change touches, and the clean fleet run stays 218/218. The gate is what makes readability
work safe: a wrong edit cannot land. [Contributing](Contributing-and-the-no-ROM-policy.md) has the mechanics.
