# 02 — The byte gate: the one non-negotiable

**A function is done when the whole binary still hashes correctly with that function compiled from source. Nothing else
counts.** Not "looks equivalent", not a passing test, not a local diff of zero, not a closeness score, not an agent's
verdict. Every other signal in the system is a *filter* feeding this gate, and each filter is blind to something. This
is what makes heavy automation *safe*: a weak model or a buggy tool is a throughput risk, never a correctness risk,
because a wrong answer cannot land.

## Build it first

The first thing to establish — before writing a line of C — is a build that reassembles the original disassembly into a
byte-identical binary, with the hash check wired into the build so there is **no third state** between "identical" and
"failed". BFM had this on day five (an all-`INCLUDE_ASM` build of the executable, SHA1-identical); every claim of
progress after that was measured against an incorruptible oracle. The two things that were correctly done first, in
this order: deterministic extraction with a committed manifest, then the all-assembly byte-identical baseline — the
first two rungs of the order [chapter 03](03-bootstrap-order.md) argues for.

The mechanics on BFM: one SHA1 contract file per binary (`config/check.<alias>.sha`), a Makefile whose `check` target
builds and compares and exits non-zero on any mismatch, a `NON_MATCHING` guard so that logically-correct-but-unmatched
C can never enter the default build (G4), and `INCLUDE_ASM` stubs whose bytes come from the disc for everything not yet
matched.

## What the gate is blind to — and the rules that cover it

The gate answers one question perfectly and every other question not at all. Each blind spot below was found by
falling into it.

| Blind to | What happened | Rule |
|---|---|---|
| **Coverage.** The gate is green at 0% decompiled, because the fallback pastes the original bytes. It can prove what landed is correct, never what you failed to attempt | a corpus scanner that could not answer returned an empty set; the tool reported a complete decomp from a swallowed error | R32 assert your coverage; R34 a second, disagreeing oracle ([chapter 04](04-oracles-and-instruments.md)) |
| **Which hash.** A gate that compares against the wrong contract is green for the wrong reason | for a month the shared gate compared one binary against *another binary's* hash — every draft of the main executable read "near" | R50 periodic whole-fleet verification; R56 a gate verdict measures the draft only while the binary's baseline is green |
| **Whether the build ran.** A failed build leaves the previous binary in place | `make build; sha1sum` read green on a stale file, twice in one hour | R53 verify a build from its exit code, not its output file |
| **Incremental state.** Some binaries' extract step rewrites the linker script | an incremental gate produced a false diff on the executable; a night went to a "linker defect" that a no-draft control disproved | R22 verify from a clean rebuild; the executable is gated *only* by a clean rebuild (`gate_main`) |
| **Whether the body is C.** Assembly pasted into a `__asm__` body matches perfectly | one "finished" function was the original assembly pasted back in; a whole class of 199 such bodies was found later | R62 a bank whose body is `__asm__` is a verbatim, not a bank; a manifest of the genuinely hand-written originals, audited for drift |
| **What was propagated.** A gate verifies the source binary; propagation writes N others | a deleted declaration layer left one propagated overlay red while the fleet read green | run the clean fleet after any propagating gate |
| **What was committed.** A gate substitutes drafts into the tree | a gate destroyed 61 uncommitted banks; later two more | R42 commit banked work the moment it exists, before the next command that can touch the source |

## Cheap gates, expensive gates, and how to run both

Populations differ. BFM had ~216 small overlay binaries (build ≈ seconds, one per worktree, gated in parallel) and one
large executable (must rebuild wholly, ≈15 s clean when the batch is right, bisects when it is not).

- **Parallel by default, never serial.** Overlays gate in git worktrees so a worker that carves (splits a translation
  unit at a jump table) writes only inside its own tree — a carving worker corrupts a shared `asm/` — and under a
  per-binary lock, so two lanes never gate the same binary at once (the worktree gives isolation; the lock gives
  mutual exclusion; a gate needs both to run as a lane). Sixteen binaries
  gated serially to protect one carving job cost an hour where the parallel form takes ten minutes; the project's
  standing bar became *a slow gate is a bug*. Pass `-j` to every build (a single-binary build without it is
  single-threaded: measured 7.2 s → 1.2 s).
- **Batch the expensive one.** One clean rebuild verifies a whole batch of drafts; on failure, bisect so one bad draft
  cannot sink the rest. Two conditions make batching work: a pre-filter strong enough that most of the batch is right
  ([chapter 04](04-oracles-and-instruments.md)'s real-TU probe), and the bisect. Measure the gate before you fear it:
  BFM's was believed to cost 40–60 minutes and cost ~15 seconds when clean; the stalls were bisects. One case where the
  bisect blames the wrong draft: parallel drafters declare a shared callee two different ways, and the batch's failure
  is the clash, not either draft — one early wave's whole gap between standalone matches and banks was such conflicts
  (compile errors, zero codegen mismatches). Normalise the declarations before the gate, gate one draft at a time
  when the failure class is conflicts, and keep a recovery pass that re-normalises the failures and re-gates.
- **A red gate is a hash, not a diagnosis.** Turn it into a named symbol with two commands: substitute the draft into
  a copy of its destination file and read the compiler's first `conflicting`/`redefinition` line. Propagation is a
  gate too — a fail-closed one that byte-gates every member, writes the shared body and registers the group — and a
  propagated body ships its signature change to every member; its sweep mode also catches earlier matches never
  propagated, which is the "banked in one binary only" drift the table above names.
- **Give the expensive population its own lane** rather than excluding it. Excluded "for a good reason", the main
  executable got no attention at all for weeks while the fast loop ran at a quarter of capacity for lack of work items
  ([chapter 05](05-cards-lanes-waves.md)).
- **A gate that starts on a dirty tree cannot tell your edits from its own.** Clean tree first; the disassembler's
  database churn is the one thing `git status` is allowed to show.

## "Banked" is a printed line, not an intention

Two ledger messages in one session claimed banks that had not happened (a helper that did nothing on an empty list and
exited 0; a wrong draft directory). Rule R66: write "banked" only from the tool's printed success line — the gate's
`BANKED` line, the bank script's `sha == config` line. Rule R68: a helper must refuse an empty work list. And count banks
from the *source*, never from a ledger: a tool once reported "12 banked of 12" because it compared function names
against a set keyed by address — always true, therefore always banked.

## The last word

The byte gate does not shrink the hard tail and does not find the bugs in your scanners. What it does is make every
other decision cheap: any drafter can be trusted, any propagation can be attempted, any refactor can be tried, because
the worst case is a red line, never a wrong binary. Build it before the drafting. It is what makes everything after it
safe.
