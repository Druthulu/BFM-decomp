# 3.45 T14 — the source census (`struct_twins.py --sources`)

Measures, without changing src/ or include/, every struct-view and raw pointer cast by the pointer it casts (its *source*),
what flows into and out of that source, the candidate parent of every cast placeholder type, the families of types the
casts tie together, and the cast-view metric that T5 (series) and T8 (gate) read.

## Run
- `PY tools/struct_twins.py --sources [--out-dir .run/3.45/t14] [-j N]`: builds the census, prints the block below,
  writes the tables (scratch, never committed).
- `PY tools/struct_twins.py --sources --check`: the same build, prints the block only, exit 0 (T8 adds the gate).
- `PY tools/struct_twins.py --selftest`: the T2 fixtures plus five planted source cases (ST_* tree; T14.c2: a hub helper, a bodiless prototyped callee).
- Inputs: those of `--links` (built fleet, `tools/sig_evidence.py -j 16`'s census, type_census's walk); the
  struct ledger `config/struct_dispositions.tsv`; restruct's ledger `.run/P37/restruct/ledger.jsonl` (RESIDUAL coverage).
- Built on `links_inputs()` + `links_build()`: the same walk, function join, bindings (`bind_of`), callee placement
  (`callee_defs`), effective slot types (`eff` / `effl`, the eff.tsv logic) and cast-view widths (`wm`).

## Definitions
- **Site**: a type_census walk site of form C `((T *)b)->f`, P `*(T *)(…)`, I `*(T *)x`, X `((T *)e)[i]`, M `M2C_FIELD(b, T *, k)`.
  Form K (kept-cast macros `CAST_*`, `LOBU`…`LOWU`, `RET_AS`, `KR_AS`) is counted apart, by macro name.
- **Region** by file: `src/shared/` shared; `src/*.c`, `src/resident/` main+resident; `src/md_*/` md_*; `src/ov_MAIN_*/`
  ov_MAIN; `src/ov_SC0N_*/` ov_SC0N; `include/` header; anything else other.
- **Source key** (census bclass): param / local -> `tu:fn:base`; global -> `name@binary` (binary_of(tu)), gaddr ->
  `&name@binary` (the object's address is a different pointer from its value); a census "local" bound at file scope (or
  undeclared in the function and extern-declared in a visible file) is a global; nested / member -> `tu:fn:<base text>`
  kind field; other / addr-of / abs / func -> `tu:fn:<base text>` kind arith. A site outside any function span, or
  with no parsed base, still gets a text key; the block counts them ("could not place").
- **Local kind refinement**: a local's assignments `x = rhs;` in its function body (the blanked text) are classified
  param-copy (a parameter), global (a D_ / file-scope name or `&name`), ret-of (a call), field (`((T *)b)->f`,
  `b->f`, `*(T **)(…)`, `M2C_FIELD(b, T **, k)`: the read type_census's field flow misses), arith (binary `+ - << >> & |`),
  local / other. One refined kind among param-copy, ret-of, field, global, arith -> that kind; two or more -> mixed;
  none -> local.
- **Site columns**: `type` is the inventory key of the cast's pointee (depth 1), else `-` (a scalar or unknown pointee);
  `off` the offset from the source pointer (base offset, plus the member offset for C); `width` / `sign` the accessed
  leaf (C: the member's, `agg` for an aggregate member; P/I/X/M: the census's).
- **Flows** (per source; `type` an inventory key or `-`, `how` decl | eff | untyped | poly | depth n | unplaced):
  - `decl`: the source's own declared type (typed param / local; a global's declaration, by `&` depth).
  - `arg-in` (param): every placed call site passing an argument into this slot, with the argument's declared type
    (`bind_of`) or effective type (`eside`).
  - `arg-out`: the source passed to a callee: the callee's declared parameter type, or its effective slot type. A callee
    with no placed C body (T14.c2) is typed by its prototype(s) in scope: the TU's own `extern` declarations (file scope,
    or block scope in the calling function) and those of its visible files (`.d` deps; a header outside the walk, e.g.
    `include/psyq/*.h`, is scanned with type_census's `EXTERN_FN`). A typed slot gives `how` = `proto` (inventory key) or
    `proto depth n` / `proto other` (typed, no struct key); only a `void *` / byte pointer / scalar slot (`untyped_param`),
    a K&R `()` prototype, a missing slot (variadic, too few params) or no prototype is untyped (`proto untyped` /
    `unplaced`). The `gte_*` macros of `include/gte_inline.h` declare no operand types: their arguments stay untyped.
    A kept-cast macro (`tc.KEPT_MACROS`: CAST_SIGN/WIDTH/ALIAS/MISALIGNED/NONSTRUCT) parses as a call in the flows:
    its argument is a form-K cast, `how` = `kept-cast`, never an untyped slot (T14 expert; untyped-arg 26,209 → 22,219).
  - `assign-in:<sub>` (local): the assignments above, with the right side's type (a callee's declared return for ret-of,
    the member type for field).
  - `assign-out`: `y = x` with y's declared or effective type; `return`: `return x;` with the function's return type.
- **Non-cast use** (param / local only, in its function body after `{`): integer arithmetic (`x + k`, `x++`, `x += k`,
  `k + x`, outside a pointer cast `(T *)x` / `(T *)(x + k)` or M2C_FIELD), comparison (`x < y`, `x == y`; a test against
  0 / NULL is not one: it holds for any pointer), or an argument passed to an untyped slot (a callee parameter with no
  inventory type and no single effective type, a poly slot, or an unplaced callee).
- **Verdict**: *mechanical* = at most one struct cast type, every typed flow names one type (that type is the parent:
  the casts become member accesses), no non-cast use, and some type (cast or flow) at all; *judgment* otherwise, with
  reasons `N cast types`, `conflicting flows (A/B…)`, `raw casts only, no flow type`, `non-cast <arith|compare|untyped-arg> <cite>`.
- **Candidates** (per cast placeholder P): flow parents first (types P's sources' flows name, by number of sources, then
  key; containment offset = the smallest cast base offset of P on that source), then layout fits. Accessed leaves of P:
  its `layout_of_fields` leaves `(off, width, sign)` at the offsets accessed through C sites or in `wm` (bound and
  cast-view accesses). A fit is a parent A (PsyQ, ledgered, or a placeholder with more fields than P) with a leaf of the
  same width and sign at `off + k` for every accessed leaf, k in {0} ∪ P's cast base offsets (k = 0 ranked first), found
  through an inverted leaf index. fit_score = accessed leaves / A's leaves (tighter first); ties PsyQ, ledgered,
  placeholder, then key. A layout look-alike never outranks a flow. At most FIT_CAP (5) fits are listed; `fits_total`
  counts all. A flow parent's score is `nofit` when its layout does not fit at its containment offset.
- **Families**: union-find over the cast types and flow types of each source; a family is one component, ids F00001…
  by size descending, then the smallest key; its casts are those of its sources, by region. Hub guard (T14.c2, T2's
  `HUB_K` = 4, `HUB_OFFS` = 2; nothing it names joins, each is a row of `family_hubs.tsv`):
  - hub *source*: its cast + flow types number >= HUB_K while its own accesses (its sites' offsets, plus links_build's
    `own_offs` for a parameter) touch <= HUB_OFFS offsets, or it is a parameter at a links_build hub slot (policy
    effective, copies by h_exact class); it joins nothing, and stays judgment with reason `hub`;
  - hub *flow slot*: arg-out flows grouped by the callee parameter they reach (a placed definition `(file, fline, i)`,
    or `callee#i` of a prototype); the slot's types are each flowing source's cast and decl types plus the slot type;
    >= HUB_K types with <= HUB_OFFS own accesses (the callee parameter's `own_offs` and cast offsets; a prototype has
    none), or a links_build hub slot: those flows do not join;
  - hub *type*: a links_build hub type (policy effective) joins nothing (a singleton family).
  Join edges per source: anchor = its smallest cast type (else its smallest join type), one edge to every other join
  type, kind `co-cast` or the smallest flow kind naming it (`decl`, `arg-in`, `arg-out`, `assign-in:<sub>`, …). A
  source belongs to its anchor's family.
- **Projection** (types left to trace after T7): placeholders − ledger `fold` rows − non-representatives (all but the
  smallest key) of exact-layout twin groups (layout_hash) whose members have 3+ non-pad fields − non-representatives of
  recurring dense small value shapes (leaves from 0 cover the size, size ≤ 32, 2+ members).

## Tables (`.run/3.45/t14/`, sorted, cites `path:line`)
- `casts.tsv`: `region form source kind ctype type off width sign cite`, one row per site.
- `sources.tsv`: `source kind region types n_casts verdict reasons flows` (flows: `kind=type xN`).
- `flows.tsv`: `source flow peer type how cite`.
- `types.tsv`: `placeholder n_sources sources cocast accessed_leaves candidates fits_total`; candidates ranked,
  `parent 0xK flow|fit score [xN flow sources]`.
- `families.tsv`: `family size types n_sources mechanical judgment casts_by_region join_edges top_joining`; join_edges
  `kind:n`; top_joining the 5 sources joining the most types (`source (n types) cite`).
- `family_hubs.tsv`: `kind source n_types types why cite`; kind source | slot | type.

## The printed block (what T5 and T8 read)
`struct_twins --sources: <sites> cast sites (C · P · I · X · M) · <sources> sources · K <n> apart`, then by source
kind (sites and sources), by region, by target type (top 50 ctypes), K sites by macro, `raw sites P/X/I/M: covered
RESIDUAL a · uncovered b` (restruct `residue_match` over the latest ledger rows, forms P, X, I, M), sources
mechanical / judgment with reason counts, families by size bucket (1, 2, 3-5, 6-20, 21-100, 101+) and the largest,
family hubs by kind, `largest families` (top 20: id, size, casts, mechanical/judgment sources, anchor = highest-cast type),
candidate coverage, the sites the source key could not place, and the projection line. Two runs on one tree print the
same block and tables (C0582): every output is sorted with fixed tie-breaks.
