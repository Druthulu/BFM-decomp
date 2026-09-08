# The inherited knowledge base — the source project's cookbook, its symptom index and its codegen map, verbatim

The files beside this page are copied byte for byte from the source project by its census tool and asserted equal on every
health check; nothing here is edited by hand. They are one project's knowledge base for ONE compiler family (the gcc 2.7.2
era that shipped with the PlayStation SDK), and they are shipped so that a new project can look a symptom up instead of
re-deriving it. Read this page first; it says what transfers.

| File | What it is | How to read it |
|---|---|---|
| `matching-cookbook.md` | some five hundred numbered sections, each an idiom or a law proven on a named function: the residual, the mechanism (the compiler pass, with the source file that implements it), the lever, the byte proof — and the integration classes, the instrument findings, the wall proofs and their refutations | **never whole** (it is several megabytes); grep it by section number from the index, or by a symptom phrase |
| `cookbook-index.md` | the symptom-keyed index the source project's tool derives from the cookbook: what a residual looks like in the diff → the section that explains it | the entry point: search it for the tell you see in your diff |
| `gcc-2.7.2-map/` | the codegen map by pass group (scheduling, register allocation and reload, the loop optimiser, common-subexpression elimination and expression generation): pass → residual pattern → byte-proven C lever, with the experiment that proved each and a citation into the compiler's source | the triage table at its head first; then the pass group your tell belongs to |

## What transfers, by compiler

- **Your target was built by the same compiler family (gcc 2.7.2 era).** The idioms apply directly: look the symptom up, apply
  the lever, and — still — re-prove it on your own bytes before the idiom enters YOUR cookbook. Harvest only from proven results
  applies to inherited lessons too; a project differs in its layout, its flags and its per-module optimisation levels, and an
  idiom that held on one game's functions is a hypothesis until it holds on yours.
- **Your target was built by another compiler.** The levers do not transfer; the STRUCTURE of every entry does. An idiom is a
  symptom, a named pass, a lever and a byte proof, and the post-map sections name the pass and the source files that produce the
  behaviour. So the translation is: find your tell in the index → read which pass the source project attributed it to → read the
  same pass in YOUR compiler's source (or, without source, probe it) → build a five-line reproducer that shows the symptom on your
  toolchain → find your lever → write your own entry in the same shape. The inherited idiom tells your agent exactly what to read;
  it does not tell it the answer. (The kit's rule: translate through the pass, never copy the lever.)
- **In both cases** the compiler-agnostic parts apply unchanged and are also distilled elsewhere in the kit: the integration
  classes (a byte-correct body that will not bank because of its file), the instrument findings (a tool that reports a true
  number about a narrower world), the harvest laws (one credited lever in three is inert — strip and recompile before it enters
  the base), the verbatim class (pasted assembly is not C), and the segmentation law (translation-unit boundaries at the build's
  forced boundaries).

## The vocabulary you will meet

The sections cite the source project's rules by number and its tools by file name; both are the source project's. The tools are in
`../tools/` with their own index; the rules the kit distilled from them are its registry seed (`templates/registry-E.decomp.md`) and
the kernels its corpus (`decomp-kernels.md`). A section that names a function by address names one of the source project's; the
byte proof is the point, not the function.
