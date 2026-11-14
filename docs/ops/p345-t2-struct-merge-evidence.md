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
  addresses, is unplaced and counted by reason. A data address past an image's file bytes (main's bss symbols are
  absolute in the ELF) belongs to the nearest image below it in that order (C0604). Unplaced counts are reported per
  binary instance and per unique site (a header extern unused by a binary is absent from its symtab).
- Function identity: (owner, vaddr) as above; the definition is placed by the same join (sig_evidence compare_core's
  def_at); h_exact from the sig row at (owner, vaddr). Empty bodies (nins 0) carry no h_exact identity.
- Type identity: a spelling (`T`, `struct T`, `union T`, a plain alias typedef) resolves to one inventory key
  (inventory_defs' names + alias chains). PsyQ and ledgered types resolve too (they can be targets, never folded).

## Link endpoints
A link joins two different inventory keys seen at the same pointer depth (`A *` with `B *`, `A` with `B`, `A **` with
`B **`; an array decays one level). A void, scalar, char or u8 pointer side is never an endpoint: no link passes
through it, except through its effective type (below).

## Effective type of an untyped slot (T2.c2)
A parameter whose declared type is void *, a scalar or a char/u8 pointer has effective type M when its own function
dereferences it (>= 1 access) and every typed use of it is M: a cast view `((M *)p)->f`, `*(M *)p`, or a whole
assignment to a single-source local of type M (`M *m = (M *)p;`, `m = p`). A call passing a value of type A into it
links A~M, sub-kind `arg-eff` (cites: the call, the parameter, one typed use). Two or more struct types on one slot:
a `poly` slot, listed, its links refused (a dispatcher). A global's effective type is class 1's global-view.
`eff-flow` (T2.c3): the same flow kinds as class 2 (arg, ret, ret-of, assign, field, store-global) where either side
is an untyped identifier with an effective type in its own function (a caller's `s32 p` cast only to A, passed to a
parameter typed or effective B). Same guards (multisource, conduit, hub, poly). Policy effective includes it.

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
     Slot identity for the hub test (T2.c4): the copies of one routine are one slot, keyed by (h_exact class,
     parameter i | return) when the function has a sig row, else (owner, vaddr, i); a member slot is (type, offset).
   - hub type (T2.c4): a type whose pointer-class partners (arg, arg-eff, eff-flow, assign, field, ret, ret-of,
     store-global, view) number >= HUB_K and include two that conflict at an accessed offset or by size is a
     header/conduit type (c3: Unkstruct_800B5CB8 drew a 112-type star through per-overlay helper copies; it is the
     map's known `suspect` merge, docs/struct-map-decisions.md:15). All its pointer-class links are refused and
     listed; its global and body links stand, except a link between two hub types (any class), which is refused
     and left to review.
   - body links at a hub slot (T2, expert): a body or body-view link at parameter i of one h_exact class joins
     that routine's slot (h_exact, i) in the hub test and is refused with it; a slot carrying only body links is a
     hub on a width conflict only (its own accesses are not counted, so the type-count test does not apply).
   - view: `((B *)a)->f` with a bound to A at a dereference. Not a link under the default policy (a cast spelling
     may be a codegen lever, C0507); policy `views` admits it as sub-kind `view` under every guard, the hub test
     taking the view type as the slot (a type viewed from >= HUB_K types through <= HUB_OFFS offsets is a header hub).
3. body: one h_exact class (nins >= MIN_BODY_INS = 10) whose placed C copies type the same slot (parameter i, return,
   a local of the same name) with A in one copy and B in another. Cite: h_exact[:12] + both copies file:line.
   Smaller classes are refused as `tiny-body` (coincident short bodies are look-alikes).
   Sub-kind `body-view` (T2.c3): the copies' texts, with every inventory type spelling masked, are token-identical;
   the k-th masked type position spelled A in one copy and B in another links A~B (cast views included: the same
   instruction in byte-identical bodies is one original type). Cite: h_exact[:12] + both tokens' file:line. Copies
   whose masked texts differ fall back to the slot comparison (parameter i, return, same-named local, each slot's
   declared or effective type). This is the class that reaches the cast-only band types (c2: 2,973 of 3,240
   no-evidence rows are used only through casts).
4. widths: not a link; the settle-and-veto data. For each type, each accessed member (lexical `x->f`, `x.f`,
   `x[i].f`, member chains resolved through the definitions, x bound to the type) gives (offset, width, sign) from the
   definition's layout (tc.Resolver) with one access cite. In byte-matched C the declared member type equals the
   original load or store (R22). Unaccessed members are layout, not evidence: listed, never in conflict.
   Conflict between two types at an accessed offset: disjoint width sets at the offset, a partial overlap the same
   side does not also cover at that offset (a union's own members never conflict), or disjoint 1- and 2-byte load
   signs. Stores and 4-byte accesses carry no sign evidence.
   Hub own accesses: a parameter slot's are the offsets accessed through it in its definitions, a global's those
   through its name; a return or member slot has none (so >= HUB_K types on one is always a hub).

## Policies (T2.c2)
`--policy typed` (classes 1-3 typed slots), `effective` (typed + `arg-eff`; the default for `--propose`), `views`
(effective + local views). One run computes all three; the summary and the report project each (components by band,
folded, apart, no-evidence); `--propose` writes the ledger from the chosen one.

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
