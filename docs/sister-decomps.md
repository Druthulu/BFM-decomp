# Sister decomps — cross-project knowledge transfer (notes for later)

> **Status:** parked notes / ideas, NOT active work. Captured 2026-07-01 (R30, while fresh). These are
> *recommendations and rationale*, not decided plans — the repo layout below is pending Drew's call.
> Sibling docs: `docs/community-matching-model-plan.md` (publishing the drafter), `docs/matching-cookbook.md`
> (the idioms), `docs/SETUP.md §5.6` (the read-only reference clones).

## Why sister decomps matter to BFM

BFM's matching loop runs on **gcc-2.7.2-psx -O2 -G0 + maspsx 2.56**. The Phase-21 collaboration sweep
byte-verified that **our `cc1` IS the psx lineage**, and identified **4 gcc-2.7.2-psx twins**: **Vagrant
Story (CC0)**, **Xenogears**, **Tomba**, and the psx `cc1` source itself. Same compiler ⇒ the entire
`§17–§28` toolkit, the permuter harness, the byte-gate methodology, and even the v3 model transfer at the
**byte level**, not just structurally.

Two distinct reasons to engage a sibling:

1. **Contribute (give back).** Apply BFM's industrialized loop to a sibling — most useful on **Vagrant
   Story** (CC0 = licensing-clean, freely contributable + poolable). v3 drafts VS functions out of the box
   (same compiler); VS's own pairs train a VS adapter or pool into the universal model.

2. **[THE WAY-LATER IDEA — Drew, 2026-07-01] Cross-project idiom discovery as a ceiling-breaker.** The
   cookbook flywheel feeds on hard-won near-misses that teach new gcc-2.7.2 idioms. One codebase eventually
   **exhausts its variety** — BFM stops producing *novel* idiom-generating functions and the residual is
   the known intrinsic scheduler/regalloc walls. At that point, a **same-compiler sibling with different
   code patterns** becomes a fresh source of compiler behaviors, and **any idiom learned there transfers
   straight back to BFM**. So if BFM matching stalls on "no new idioms, only intrinsic walls," harvest
   *idioms* (not just matches) from VS/Xenogears and re-apply to BFM's tail. Memory:
   `cross-project-idiom-discovery`.

## Recommended layout (pending decision)

Drew's instinct — co-locate the sibling gitignored inside this repo — is right and matches the existing
`tools/reference/xenogears-decomp` precedent (a gitignored clone). One adjustment, because we'd *write* to
VS (branches/PRs), not just read it:

- **Clone YOUR FORK** (not upstream) so you can branch + PR.
- **Add the `.gitignore` entry first** (e.g. `/sister-decomps/`) so BFM never tracks a byte of it; the
  sibling keeps its own `.git` pushing to your fork → upstream.
- Suggested location: **`/sister-decomps/vagrant-story/`** at the repo root (signals "peer project," not a
  BFM read-only reference).
- BFM is the **read-only knowledge base** the sibling references by path (cookbook + `tools/`, ported into
  the sibling where a clean PR needs them — the sibling gets its own copies, not BFM imports).
- **Alternative** (textbook, if you'd rather avoid a nested working repo's git foot-gun): a true sibling
  `~/vagrant-story/` next to `~/bfm-decomp/`.

## Discipline (non-negotiable if we do this)

- **Content firewall.** BFM is private + ROM-derived; VS is public + CC0. Nothing BFM-private or
  ROM-derived ever lands in a sibling commit. Tools are code (ROM-free) → fine to port.
- **Governance separation.** The BFM phase-gate/PhaseEnd system governs *this* project only. Sibling work
  is a separate track — its own loop, its own gate, no BFM phase ceremony. It is NOT "Phase 24."
- **Licensing of ported tools.** Drew owns the BFM tools and can license his own work into a CC0 project as
  he wishes; settle this before contributing tool code upstream.

## What the transfer buys a sibling (e.g. VS)

The byte-gate (the sibling has its own `check`/asm-differ), the gcc-2.7.2 idiom toolkit (§17–§28), the
decomp-permuter harness, `inject_capped_externs`-style shared-code propagation, and a same-compiler LLM
drafter (v3 now; a sibling adapter or the universal model later). That's most of an industrialized matching
loop dropped onto a sibling codebase.

## Next step (when Drew greenlights — not now)

Provide the VS fork URL (or "fork it for me" → use `gh`), then: add the `.gitignore` entry, clone
co-located, and survey VS's current state (build/gate setup, % matched, the unmatched queue) to see where
our toolkit lands first. Keep a one-line cross-project pointer here so the knowledge link is recorded.
