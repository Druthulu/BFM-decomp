# Where the project goes next

The matching is finished: 218 binaries rebuild byte for byte and the frontier is empty. What remains is in two parts.
The first is short and mostly administrative — the public flip and the close of the second generation. The second is the
third generation: making code that *matches* into code a maintainer would call *finished*.

## Phase 34 — the flip and the Gen2 exit (2026-09-08)

The repository's history was rewritten before publication to remove every game-derived byte and force-pushed in place;
the flip waited on GitHub Support purging the old objects, because the host's Activity view still served every
pre-force-push tip ([The ROM firewall](The-ROM-firewall.md)). The probe of the old hashes printed PASS on 2026-09-07 and
again immediately before the flip, and **the repository went public on 2026-09-08**, with a ruleset that forbids
force-pushing or deleting `main` from then on.

The same day, in order: the after-flip probe and the Actions runs on the public repository; the progress card on
decomp.dev, read from the workflow's report artifact; this wiki, published from `docs/wiki/` and the how-to; the
decomp.me preset request with a scratch that matches at 100%; the note to the neighbouring Archipelago project; the
tool announcement and the Decompedia rows; and the maintainer's own decisions on what a public tree carries (the sent
outreach drafts and the document archive left it — the Archive index is the record). The phase closes at **v2.0.0**,
the Gen2 exit, with a PhaseEnd that lists by name what is still pending on third parties (the preset's creation, a
reply from Archipelago, frogress). Its seed, with every task, actor and effort level, is
[`docs/phase34-seed.md`](../phase34-seed.md).

## Gen3 — readability, on a byte-exact floor

**The floor.** Accuracy is not a Gen3 concern; it is the floor Gen3 stands on. "Matched" means instruction-identical
including register allocation *and* a whole-binary hash equal to the original, checked inside every build of every
binary, with a clean rebuild after every batch. Nothing functionally equivalent has ever been counted, and what is not
the project's own C is stated: 1,256 Sony library objects linked byte-identical into the executable, and the original's
hand-written assembly routines kept verbatim (27 as of 2026-09-09 — the Phase-36 census found the twenty-two per-overlay
stack-switch trampolines that the file-scope detector behind the manifest had never seen).

**The bar.** The community's expectations are written down, and the project adopts sotn-decomp's style guide as its
baseline: `camelCase` locals, `g_PascalCase` globals, `PascalCase` types and functions, the project's own `u8…u32`
types, clang-format at 4 spaces and 80 columns, decimal for counts and hexadecimal for addresses and masks,
`// !FAKE:` on anything that exists only to force a match, functions in assembly order in the file of the system they
implement — and, ranked first, *"if you are not sure what something does, it is better to leave it unnamed than name it
wrongly."* To that the project adds four rules of its own, because its code was produced by a machine at scale:

1. **Every name carries evidence** — a string, a cross-reference chain, the debug menu, a live-RAM datapoint, a community
   label with provenance — recorded the way addresses are. A model may propose a name; it may never assert one.
2. **Every register pin goes**, or stays with a `// !FAKE:` line naming the residual. The count is a published metric until
   it is zero — *Phase 36 (2026-09-09 → 2026-09-11): 53,234 register pins and asm statements → 4,010, every survivor marked with the
   compiler pass that needs it and the instrument that judged it; the rest is the structs phase's (see [levers.md](../levers.md) and
   cookbook §457).*
3. **Shared engine functions live as C, not as macros** — *done at Phase 35 (2026-09-08): one plain-C header per shared body under `src/shared/`, included at each site; see [The dedup engine](The-dedup-engine.md)* — the dedup engine's macro bodies become `.c` files per system,
   byte-neutrally, proven per family.
4. **Types come from the code, names from observation** — structure from the access patterns the compiler locked into the
   bytes; the 1,232 struct definitions unified before any field is named.

**The gap, as measured.** The starter census below was derived on 2026-09-07 with the commands in
[`docs/gen3-handoff.md`](../gen3-handoff.md) §3 — re-derive it, do not trust it:

| Quantity | Value | Note |
|---|---|---|
| Raw address casts `*(T *)0x80…` | 143 | the last of a class the type-lift tools already handle |
| Distinct `D_80xxxxxx` data symbols | 61,898 | most are fields of a handful of structures the engine indexes |
| Distinct `func_80xxxxxx` names | 16,335 | across 4,287 C files |
| Register-pin declarations | ~~43,925~~ **2,141** (+ 1,869 asm statements; Phase 36, 2026-09-11) | `tools/lever_census.py --check`; 37,720 pins + 15,514 asm statements at the phase's own census (2026-09-09) → 4,010 sites in 1,980 functions, all `// !FAKE:`-marked with their pass; the series is `docs/lever-progress.tsv` |
| Shared bodies living as macros | ~~5,147~~ **0** (Phase 35, 2026-09-08) | every shared body is one plain-C header under `src/shared/`, included at its sites; 3,173 registry groups; see [The dedup engine](The-dedup-engine.md) |
| Struct definitions | 1,232 | many drafter-invented variants of one type |
| Curated names in the symbol files | 1,083 | the names the build already knows |

**The one invariant.** Every Gen3 edit is gated exactly like a match was: the per-binary check for every binary a change
touches, and the clean fleet run after anything that touches a shared body, a shared header or the executable. A rename
is a symbol-file change mirrored into Ghidra by the headless script, never a hand edit of assembly. A shared body is one
source and up to 138 binaries, so the gate runs on all of them. Types are a comprehension lever, not a byte lever — the
compiler does not care what a field is called — which is exactly why struct work is safe and exactly why it still goes
through the gate.

**The order of work:** pins off → the macro bodies into shared C files → struct unification → names with evidence →
formatting and comments. Three things the record says to do first: measure the shape (which structures own most of the
data symbols, which families own most of the pins — with a self-asserting scanner checked against a known case), build
the differential harness for the new question ("is this edit byte-neutral?" has two paths, and a scanner must assert
every reference to a renamed symbol was rewritten), and batch by leverage — a pin in a shared body comes off for 138
binaries at once.

**The levers Gen3 inherits** are tools already in the tree: the fleet-wide type lift, the call-site cast and canonical-
signature tools, the declaration layer of the reconcile ladder, the allocation-order and RTL-dump readers to consult
before touching a pin, the propagation and registry machinery that keeps 2,220 dedup groups consistent through a rename,
the headless symbol mirror into Ghidra, and the atlas for grouping candidates. The table with each lever's purpose is
[`docs/gen3-handoff.md`](../gen3-handoff.md) §5.

**The use of AI — conduct.** The project is openly machine-carried and says so once, at the project level. The rules that
keep that from being a liability: the byte gate is the only claim of success; names and types are evidence-based, never
guessed; outward text is written by a person, the way a developer writes, after reading the target project's own AI
policy; no automated traffic against community infrastructure; agents assist, a person owns. They are stated in full on
the [Contributing](Contributing-and-the-no-ROM-policy.md) page and in [`docs/gen3-standards.md`](../gen3-standards.md) §3.

**Shiftability, honestly scoped.** Overlays are position-locked at one slot by the loader; LZSS recompression is not
byte-stable, so a rebuilt disc verifies by booting, not by hash; the executable's Sony regions are linked objects.
The order that follows: symbolic references first (byte-neutral, gated), then a shifted overlay that boots in the
emulator, then the disc rebuild. Parked beyond that, each with its state recorded in the handoff: asset export and a
native rebuild, a PC port, randomizer-grade tooling, the community matching model (pipeline published; data and weights
wait on a licensing decision), the Japanese release and the prototypes as extra versions, the Sony libraries from source.

## What a new project takes from this

The order this project would use if it started again — and the firewall, the conventions and the conduct rules above —
are packaged as a day-one kit for the next decompilation: [Start a new decomp project](Start-a-new-decomp-project.md).
