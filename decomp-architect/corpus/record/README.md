# The inherited record — the source project's distilled records and its phase-by-phase record, verbatim

The files beside this page are copied byte for byte from the source project by its census tool and asserted equal on every
health check; nothing here is edited by hand. The kit's rules, kernels and methodology were DISTILLED from these files; this
folder is the source they were distilled from, so that a reader can go back to the evidence instead of trusting the summary.
Read this page first; it says what each file is and how to read it.

## What is here

| Folder / file | What it is | How to read it |
|---|---|---|
| `how-to/` (13 chapters) | the transferable method written for the next project: governance, the byte gate, the bootstrap order, oracles and instruments, cards/lanes/waves, the knowledge base, the compiler's source, models and budgets, the economics as measured, integration and propagation, publishing, and the failure museum | in order, from chapter 00; it is the long form of the kit's methodology, with the measurements |
| `docs/decision-log.md` | the WHY of every strategic pivot, appended while it hurt: context and belief → what failed → the pivot → the measurement-grounded why → a hindsight "better path" | by date or by the phase named in a heading; the hindsight sections are what the retrospective mined |
| `docs/accelerators.md` | what was learned late that a future project should know on day one — each entry with when it was found, when it could have been found, and what it would have saved | whole; every entry is cited by a kernel or dispositioned (the kit's coverage check asserts this) |
| `docs/retrospective.md` | what was believed, what failed, what it cost, what to do sooner — mined by tool from the decision log's hindsight bullets and every phase-end's deviations table | whole |
| `docs/story.md` | the narrative, phase by phase, for a reader who was not there | whole, once |
| `docs/wave-playbook.md` | THE procedure for a drafting wave — draw, cards, packs, draft, gate, twin sweep, harvest, checkpoint — each guard paired with the measurement behind it | when you run your first wave; the kit's playbook skeleton is this file with the measurement column emptied |
| `docs/effort-map.md` | the effort doctrine as it was actually operated: which task gets the deepest reasoning, which gets breadth, and why | before your first phase plan |
| `docs/gen3-standards.md`, `docs/gen3-handoff.md` | the readability charter (the community's bar, the four house rules, the use-of-AI conduct, a definition of done) and the census of what 100% looked like before it | when you set your own bar — the kit's Part C inversions come from here |
| `phase-ends/DIGEST.md` | one page per phase (what it delivered, its key finding, its rules) and every rule of the source project in full | the entry point to the phase record: read a synopsis, then the PhaseEnd it names |
| `build/tools-health.mk` | the source project's HEALTH CHAIN — the ordered `tools-health` (and `audit-digest`) recipe of its Makefile, extracted verbatim by the census tool, a comment per rung naming the incident that earned it: signatures fresh, the corpus oracle, the declaration audit, the binary census, the report and its lint, the digest freshness, the wall-clock and work-evidence guards, the docs and kit checks | when you build your own health target (Phase 3 onward): keep the ORDER and the reasons, swap in your tools rung by rung as they exist; sample by default, keep the exhaustive form behind its own name |
| `phase-ends/PhaseEnd_*.md` (every phase) | the durable record of each phase: the build log, the literal verification results, the milestone and its proof, the deviations from the plan, the rules proposed, and — from the later phases — "what we believed, what failed, what we would do sooner" | on demand, never whole: the digest names the phase; open that file for the detail |

## What is deliberately NOT here

- **The phase worklogs** (the source project's `phase-ends/logs/`, some 30,000 lines). They are the raw per-task trail and are
  on-demand archives even in the source project. Their lessons reached the records above at the time (its rule: capture while
  it hurts), and a dedicated pass at the end read every log once more for anything that had not — those findings were banked
  into the kernels and the accelerators, so nothing in the logs is missing from this folder's distillation.
- **The cookbook, its symptom index and the codegen map** — the sibling folder `../cookbook/` (its own front page says what
  transfers per compiler). **The tools** — `../tools/` with its need-keyed index.
- **The project-specific references** (the memory map, the disc formats, the environment reference, the symbol files): they
  describe one game and one machine and do not transfer.

## The vocabulary you will meet

These files are the source project's and use its names: its rules by number, its phases and sessions, its tools by file name,
its functions by address, its binaries by alias. The kit's rules (`templates/registry-E.decomp.md`) and kernels
(`decomp-kernels.md`) are the translation; each carries a `provenance:` line pointing back into this record.
