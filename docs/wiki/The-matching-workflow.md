# The matching workflow — draft → gate → bank

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
