# 3.45 T2 — struct merge evidence: the method of `struct_twins.py --links`

The merge-evidence census links placeholder struct types (config/struct_dispositions.tsv rows; T1's inventory) by
cited evidence only, forms components, and proposes one disposition per placeholder. Layout look-alikes are never
evidence (G62, R122, docs/struct-map-decisions.md:30 "per type, not per layout"). Generated results:
`docs/ops/p345-struct-merge-report.md` (`--links --report`); the per-link tables are scratch under `.run/3.45/t2/`.

```
PY tools/struct_twins.py --links [--out-dir .run/3.45/t2]   # links, components, refusals, DECL-PARAM; summary on stdout
PY tools/struct_twins.py --links --propose                  # also writes the proposed dispositions into the ledger
PY tools/struct_twins.py --links --report                   # also writes docs/ops/p345-struct-merge-report.md
PY tools/struct_twins.py --selftest                         # planted fixtures (below)
```
Prerequisites: a built tree (build/**/*.d, the linked ELFs) and fresh `.run/sig.<alias>.jsonl` (sig_evidence -j 16).
A missing input is a loud exit 2, never a silent empty class.

## Joins (C0586, G41: never a name alone)
- File -> binaries: build/src/*.d and build/src/<alias>/*.d (normpath), as sig_evidence.load_tus. A header line
  belongs to every binary whose objects list the header.
- Name -> address: each binary's ELF symtab (sig_evidence.elf_syms). An object is (owner, vaddr): owner = the first
  image holding vaddr in the binary's own-then-stack order (sig_evidence place()); main-resident addresses are one
  object fleet-wide, overlay addresses are one object per overlay image. A name not in the symtab, or with several
  addresses, is unplaced and counted by reason.
- Function identity: (owner, vaddr) as above; the definition is placed by the same join (sig_evidence compare_core's
  def_at); h_exact from the sig row at (owner, vaddr). Empty bodies (nins 0) carry no h_exact identity.
- Type identity: a spelling (`T`, `struct T`, `union T`, a plain alias typedef) resolves to one inventory key
  (inventory_defs' names + alias chains). PsyQ and ledgered types resolve too (they can be targets, never folded).

## Link endpoints
A link joins two different inventory keys seen at the same pointer depth (`A *` with `B *`, `A` with `B`, `A **` with
`B **`; an array decays one level). A void, scalar, char or u8 pointer side is never an endpoint: no link passes
through it (no transitive flow through an untyped slot).

## The four evidence classes
1. global: one object (owner, vaddr) declared or defined with type A in one file and B in another (`extern A D_x;`,
   `A D_x[N];`, `A *D_x` vs `B *D_x` links the pointees). Cite: `<owner>/0x<vaddr>` + both declaration file:line.
   A cast of the object's address (`(B *)&D_x`) binds too, sub-kind `global-view`, counted apart.
2. pointer: a value of type A reaches a slot of type B. Sub-kinds, each cited by both sides' file:line:
   `arg` (a call argument whose identifier is bound to A, the callee placed through the join, its definition's
   parameter i is B), `ret` (`return a;` with a: A in a function declared to return B), `ret-of` (`a = f()`),
   `assign` (`b = a`, `b = (B *)a`), `field` (a load or store of a member whose declared type is B *), `store-global`
   (`D_x = a`, D_x declared B *), `decl` (a placed declaration whose parameter or return names A where the placed
   definition names B: the DECL-PARAM pairs below). Guards (refused, counted, listed):
   - multisource: a local assigned from more than one distinct source in its function (type_census.py:858-874).
   - conduit: a callee parameter its own body never dereferences (type_census typed_params).
   - hub: a slot (callee parameter, return, member, global) whose linked types conflict among themselves at an
     accessed offset (width), or that links >= HUB_K = 4 types while its own accesses touch <= HUB_OFFS = 2 offsets
     (a pool, list or header helper). Every link through a hub is refused; the hub is listed with its types.
   - view: `((B *)a)->f` with a bound to A at a dereference is counted, not linked (a cast spelling may be a
     codegen lever, C0507; T2's review decides whether views become evidence).
3. body: one h_exact class (nins >= MIN_BODY_INS = 10) whose placed C copies type the same slot (parameter i, return,
   a local of the same name) with A in one copy and B in another. Cite: h_exact[:12] + both copies file:line.
   Smaller classes are refused as `tiny-body` (coincident short bodies are look-alikes).
4. widths: not a link; the settle-and-veto data. For each type, each accessed member (lexical `x->f`, `x.f`,
   `x[i].f`, member chains resolved through the definitions, x bound to the type) gives (offset, width, sign) from the
   definition's layout (tc.Resolver) with one access cite. In byte-matched C the declared member type equals the
   original load or store (R22). Unaccessed members are layout, not evidence: listed, never in conflict.
   Conflict between two types at an accessed offset: different widths, partially overlapping ranges, or (1- and
   2-byte members) different signs. Stores and 4-byte accesses carry no sign evidence.

## Size verdict
A type's size is load-bearing when one of these is cited: `sizeof(T)` / `sizeof(*p)` with p: T *; an array of T
(global, local, member); pointer arithmetic on a T * (`p++`, `p--`, `p + k`, `p - k`, `p += k`, `p[i]` with i not the
literal 0, pointer differences); a copy of a T (`*a = *b`, a struct assignment, a struct-typed member copied whole);
T by value (parameter, return, a local `T x;` in a frame, a defined non-extern global). A component's size is the
load-bearing size of its members; two load-bearing members of different sizes, or a member whose accessed extent
passes the load-bearing size, is a size veto. With no load-bearing member the merged size is the largest member's.

## Components
Union-find over the accepted links in one fixed order: class global, body, pointer (decl, arg, ret, ret-of, assign,
field, store-global), then by cite text. Each union first merges the two groups' accessed-width maps and size facts;
a conflict or a size veto refuses that link (listed with the offset and both access cites). Two runs on one tree
give identical output (C0582: inputs walked in sorted order, no cache-order dependence, no timestamps).
Merged layout: per offset, the members' (width, sign, field name) with one cite each.
Proposed target (the Rationale): a PsyQ member, else a ledgered member, else the member with the highest
reach(T) (docs/leverage-types.tsv), ties to the lowest file:line. Projected reach of a survivor is the sum of its
members' reach (an upper bound: reach counts distinct bodies per type).

## Dispositions proposed (config/struct_dispositions.tsv; column `class` added after `target`)
- fold: a component member other than its target. target = the component's target; class = global|pointer|body of
  the link that admitted it; evidence = `C<n>: ` + that link's cites.
- apart: a type kept as its own type, with a cause naming an address or a cite: a component target (`own`: its own
  objects), a type with placed objects and no accepted link (`own`), a type refused by a conflict, size veto or hub
  (`conflict`, `size`, `hub`, cites of the refusal).
- no-evidence: no placed object and no access to judge by; reason names what exists (no users, member of X only,
  macro only, unplaced: <reason>).
Proposals are rewritten on each `--propose`; a disposition marked applied by a later task (T7) is never rewritten.

## Twins re-judged
Each of docs/struct-twins.md's `### <lhash>` classes is re-judged: `linked` (two or more of its names in one
component: fold proposed, the class leaves the list after the fold), `split` (linked across two components), or
`apart holds` (no link among its names; the listed cause stands). docs/struct-twins.md is not edited by T2.

## DECL-PARAM (outcome R179)
Every placed declaration/definition pair (sig_evidence --compare's join) compared per parameter position: both
sides name struct types (after alias resolution) and they differ -> a row (name, owner/vaddr, i, declaration
file:line and type, definition file:line and type, resolved by the proposed folds: yes, or why not). A struct on one
side against void or a scalar on the other is counted apart (not DECL-PARAM). T8 turns this into a gated rule.

## Selftest fixtures
A synthetic tree with its own symtab, .d map and sig rows: a look-alike pair (equal layouts and access widths, no
link) stays unlinked; a shared-global pair links (class global); the same address in two overlay images does not;
a pointer-flow pair (arg into a dereferenced parameter) links (class pointer); a width conflict (u16 vs u32 accessed
at one offset) refuses the fold and both stay apart; a hub slot refuses its links; two runs print identical output.
