# 06 — The knowledge base: the flywheel and its laws

Workers discover things. If discoveries do not reach the *next* workers, you re-buy the same lesson forever. The
knowledge base is the project's compounding asset — and it is **per-compiler**: BFM's is some 500 sections of gcc 2.7.2
behaviour; yours will be about your compiler. The machine that builds it is what transfers.

## The layers

| Layer | BFM's instance | What it holds |
|---|---|---|
| **The cookbook** | [`docs/matching-cookbook.md`](../matching-cookbook.md) (3.5 MB; grep it by section, never read it whole) | one section per idiom or law, each **byte-proven** on a named function with the diff before and after; the compiler-internals laws; the integration classes; the wall proofs and their later refutations |
| **The symptom index** | [`docs/cookbook-index.md`](../cookbook-index.md), derived by a self-asserting tool | *symptom → section*: what a residual looks like in the diff, and where the lever is |
| **The codegen map** | [`docs/gcc-2.7.2-map/`](../gcc-2.7.2-map/) by compiler pass | pass → residual pattern → C-level lever, from reading the compiler's source ([chapter 07](07-compiler-source.md)) |
| **The pinned triple and the permuter recipes** | the build, `tools/permuter/` | the executable form of the same knowledge: what the tools try before an agent is asked |
| **The journal** | per-function past-attempt notes | what every earlier agent tried on *this* function — pack fuel |
| **The meta layer** | the decision log, the accelerators, the rules | why the project pivoted; what would have been faster; what must never happen again |

**Rule R16 — the flywheel:** consult the base *before* each match (the pinned triple, the cookbook, the permuter
harness, the decompiler's context), and *after* each match feed the generalizable lesson back into **both** the cookbook
**and** the tooling, so the next similar function is a one-shot. Don't over-encode one-offs.

## The loop

```
gate accepts a function  →  harvest the worker's note   (only for BYTE-PROVEN results)
   →  distil into the base (a human + a mid-tier reviewer)
      →  the next workers grep it from their next card
```

Four things learned the hard way:

1. **Harvest only from proven results.** A note attached to an unverified draft is a lesson about a function you did
   not reproduce.
2. **Extraction is not distillation.** BFM harvested automatically and correctly for weeks while the ore piled up
   unread; only what reaches the base changes behaviour. The agent journals were a labelled corpus written for thirty
   phases and read in the thirty-first.
3. **Expect ~85% of harvested claims to be already covered.** That is not waste — a fast, correct "already known, see
   §N" is most of the value, and it stops the base bloating with duplicates.
4. **One in three credited levers is inert.** Workers stack edits; when the match closes, the last-added edit gets the
   credit, and byte-inert riders *survive into the accepted result precisely because they are inert*, which then reads
   as proof. **Before a lever enters the base, strip it from the accepted body and recompile.** Measured twice: 4 of 8,
   then 6 of 19.

**Accept the one-wave lag.** Wave N's lessons land while wave N+1 is in flight, so N+2 is the first that can use them.
Pausing production to think costs more than the lag.

## Harvest is a pipeline step, not hygiene

Never draft a new wave until the last one's idioms are banked **and** any mechanical one has become a sweep that banks
the free functions. New idioms do two things: they make the next exemplar easier, and they retroactively convert
already-open functions into free banks — but only if a tool is widened to see them. That is the project thesis. Harvest
*periodically*, not per bank: the highest-value entry of one session was only visible because four independent
instances appeared in one wave; one function at a time cannot see it.

## Vocabulary decides findability

The first distillation should be done by hand, because its vocabulary decides whether anyone finds it later. A card may
not name a lever the base does not contain (R44). The index is keyed by *symptom* — what the diff looks like — because
that is what the worker has in front of it, not the name of the pass. And the base needs its own coverage assertion:
the index tool checks that every section is indexed and every index entry resolves, in the pre-work health check.

## Two laws about siblings

- **R71 — When a same-family sibling is banked, port its SPELLING before touching a dial on the draft.** Two of the last
  four functions matched on the first try once a banked sibling's exact source shape was ported — one of them after
  3,360 sweep variants had failed on the "correct" draft.
- **R72 — A similarity score is not a shape oracle.** The atlas scored the exact same-shape sibling at 0.55 ("weak
  cousin"). A hand pass opens with a grep for the idiom's literal constants across the source and an objdump of each
  hit's window against the target — before any similarity tool, and before any dial.

## Seed it before the first match

Two sources exist before any function is matched ([`docs/generic-decomp-package.md`](../generic-decomp-package.md)):
the compiler's own source (BFM's highest-value late idioms — reload rematerialization, copy capture, a scheduler bound,
the `asm` priority — came from reading four files of it, and none required a matched function), and sibling projects
on the same compiler (same-generation idioms transfer; a same-compiler sibling can also be worked deliberately to
surface idioms when your own well runs dry). Carry a cookbook across as the starting corpus and adapt it, rather than
rebuilding it.

## Capture while it is fresh

The terse "what changed" record survives a context boundary; the *why* — the judgment behind a pivot, the byte evidence
behind a crack — evaporates. Write cookbook entries, byte-verified findings and doc corrections **during the session
that produced them** (R30); defer only mechanical, continuable work. A fresh session has only compressed summaries.
