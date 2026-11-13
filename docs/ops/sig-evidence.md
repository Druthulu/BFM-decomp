# sig-evidence — the asm signature census (3.44 T3)

`tools/sig_evidence.py` measures every function's calling contract from the original bytes: whether its return is
used, how many arguments it reads and its callers set, and the width and sign evidence on each. It never reads the C
(the comparison with declarations is T4's `--compare`). Every verdict cites instructions as `<binary>:<vaddr> <insn>`.

```
PY tools/sig_evidence.py -j 16          # full census -> build/sig_evidence/ (gitignored, constraint R74)
PY tools/sig_evidence.py --selftest     # one synthetic fixture per rule below
PY tools/sig_evidence.py --show <binary>:<vaddr>   # print the row holding that instance
```

The interpreter re-executes itself under `.venv/bin/python` when `rabbitizer` is not importable (rabbitizer 1.16.2,
requirements-python.txt:21). gcc cites are file:line in tools/reference/gcc-2.7.2 (the tree of R3.44-001).

## Inputs

- The 218 binaries of Makefile:59 (`BINARIES`), each alias's `_EXE`, `_VRAM_BASE` (Makefile, config/overlays.mk,
  config/modules.mk). File offset = vaddr - `_VRAM_BASE`.
- Each alias's `_SIG` file (`.run/sig.<alias>.jsonl`, written by tools/sig_image.py from the original bytes). Rows with
  `nins` 0 are skipped: `src` IMPORTED, and 7 DEFAULT rows in main (nbytes 0, the empty-body hash, placeholders at jal
  targets outside main's image; they made T1's count 363,349 / 92,646 against 363,342 / 92,645 here). A function
  instance is (binary, vaddr); its body is the image slice `[vaddr, vaddr + nbytes)`; instances with equal `h_exact` are
  one class and are decoded once.
- Symbol stacks: the alias's splat yaml `symbol_addrs_path`. A stack file names a binary (`symbols.us.txt` = main,
  `symbols.resident.txt` = resident, `symbols.<alias>.txt` = the alias); other files (`symbols.us.ram.txt`) are not
  binaries. The stack decides which binaries a `jal` may land in (with a fleet-wide fallback, below) and the instance
  names (own file first, then the sig row's name). Names are per binary (C0571): everything keys on (binary, vaddr).
  Asserted at startup: every alias's stack holds its own file.

## Control flow (per body)

- Decoding: `rabbitizer.Instruction`, cop2 words with the GTE category (tools/sig_image.py:37). GPR sets come from
  rabbitizer's reads/modifies flags (fixture-checked): `mfc2`/`cfc2` write rt, `mtc2`/`ctc2` read it, `lwc2`/`swc2`
  read only the base, `mfhi`/`mflo` write rd, `jalr` reads rs and writes rd ($ra). `lwl`/`lwr` write rt and do not
  read it: the compiler's unaligned pair overwrites the whole register (counting the merge as a read made 1025
  classes falsely `ret64`).
- Delay slots: a branch's or jump's delay slot executes before the transfer, on both arms of a conditional branch.
  A `jal`/`jalr` delay slot executes before the call, so a value read there is never that call's return (C0244).
  -mips1 has no branch-likely instructions (R3.44-001; Makefile:1044 `-mips1`).
- Edges: conditional branch -> target and fall-through; `j` inside the body -> target; `j` outside the body -> a
  tail-jump site (below); `jr $ra` -> function exit; `jr <reg>` -> the jump table's targets when the table resolves
  (a `lui`/`%lo` pair forming the table address, words read from the representative instance's image while each lies
  in the body), else an unresolved jump; running past the last instruction -> path leaves body.
- Call event: after a `jal`/`jalr`/`bal`-family site and its delay slot, $v0, $v1, $a0-$a3, $t0-$t9, $at and $ra are
  clobbered (caller-saved, mips.h:1203 CALL_USED_REGISTERS; C0185; R3.44-001 item 3: no promotion around calls, mips.h,
  PROMOTE_FUNCTION_RETURN undefined).
- Frame: $sp offset from entry tracked through `addiu $sp,$sp,imm`; `move/addu/or $fp,$sp,...` copies it to $fp
  (-O0 frames, Makefile:920, 1078-1079, 1082, 1111, 1119). A memory access off $sp or $fp is converted to an
  entry-$sp offset; where the offset is not known on every path the access is `frame unresolved`.

## Return evidence

- Caller read (rule RET-READ): at a call site, the first instruction after the call event that reads $v0 on some path
  before $v0 is written on that path ($v0 is GP_RETURN, mips.h:1876; R3.44-001 item 4). Its existence makes the callee's
  `ret` `used`, citing it. The read kind is recorded: `andi:<mask>`, `sll:<n>`, `sb`, `sh`, else `full` (any other read,
  unextended).
- 64-bit read (rule RET-V1): $v1 read after the call event before written. 64-bit values return in $v0:$v1
  (R3.44-001 item 4; mips.h:1255-1257, 1876, 1891-1897). It also makes `ret` `used`, with `ret64` set.
- Dead (rule RET-DEAD): $v0 written before any read, or clobbered by the next call event (a tail `j` included), on
  every path (mips.h:1203, 1876).
- Tail (rule RET-TAIL): $v0 reaches the caller's own `jr $ra` unread. `f();` and `return f();` emit the same caller
  code (R3.44-001 item 6), so the site's use is the caller's own `ret`, settled by the fixed point below. A `j` to a
  function start outside the body is a tail-jump site: its use is the jumping function's `ret` likewise.
- Tail fixed point (rule RET-FIX): the tail graph (callee class -> caller class) is processed in strongly connected
  component order, callers first (it follows from RET-TAIL, R3.44-001 item 6). A class is `used` when a direct site
  reads or a tail site's caller class is `used`; a component of two or more classes, or a self-loop, with no `used` is
  `unknown:recursion`. A class whose tail caller is `unknown:recursion` gets `recursion`, not
  `tail position unresolved`.
- Verdict: `used` when any site of any instance reads (RET-READ, RET-V1, or RET-FIX through a `used` caller).
  Otherwise `unknown:<reason>` when any reason below applies (the first in list order is the verdict; all are listed
  in `reasons`). Otherwise `unused`: every call site is known and none reads.
- Callee exit (rule RET-EXIT): for each `jr $ra`, the writers of $v0 reaching it (reaching definitions, the jr's own
  delay slot included): an instruction, `call <target>` (a callee's return passed through), or `entry` ($v0 not
  written on that path). Narrowing writers (`andi $v0,..,0xff/0xffff`, `lbu/lb/lhu/lh $v0`, `sra`/`srl $v0` after
  `sll`, the W-ARG-SITE classifier)
  are the callee's own width evidence; no promotion of the return exists (R3.44-001 item 3).

## Argument evidence

- Callee reads (rule ARG-READ): $a0-$a3 read on some path from entry before written ($a_k is argument k;
  mips.h:1881-1886), and loads from entry $sp+16+4k, argument 4+k (mips.c:2931-2937, the 16-byte caller-owned home area
  mips.h:1809-1828). `arity_lb` = highest argument index read + 1 (cookbook/INDEX.md:620 addendum: a callee's arity
  lower bound from its own stack-argument reads).
- Pass-through (rule ARG-PASS): an incoming $a_k still unwritten at a call event or tail jump may be forwarded without
  a read instruction (mips.h:1881-1886); recorded apart, not counted in `arity_lb`.
- Site setup (rule ARG-SITE): at each site, the $a0-$a3 written on every path since entry or the previous call event,
  delay slot included, and the stores to the caller's $sp+16+4k in the same window. A stack slot counts only when the
  function never loads it back (else it is a local or a register save, e.g. `sw $ra,0x10($sp)`), lies below the lowest
  address-taken local (`addiu rX,$sp,off`: GCC puts outgoing args below locals), and continues a contiguous run from
  $sp+16 (C0584; mips.h:1785 ACCUMULATE_OUTGOING_ARGS, 1809-1828). Site arity = highest set argument index + 1. Per
  callee class: min and max over its sites. An argument-register copy in the `jal`'s own delay slot is a setup for that
  call (C0284).
- DImode and double arguments start on an even register (mips.c:2890-2891, 2925-2928); function_arg_partial_nregs
  disagrees at arg_words 3 (mips.c:3017-3023): the asm decides, the census reports registers only.
- Struct returns (pcc, calls.c:919-921, toplev.c:328-334) put the hidden pointer in $a0: the census reports it as
  argument 0, it does not detect struct returns.
- Varargs (rule ARG-VARARGS): the callee stores incoming $a_k .. $a3 (contiguous, through $a3) to entry $sp+4k
  (mips.c:4996-5017). -O0 frames store named parameters to the same home slots, so the flag is read with `frame`:
  a `fp` frame with all four stored is not distinguishable from a 4-parameter -O0 function.

## Width and sign evidence

Soft float (Makefile:1044 `-msoft-float`; mips.c:2874-2898, mips.h:1877): FP values travel in GP registers and are not
told apart. PROMOTE_PROTOTYPES (mips.h:1153; c-typeck.c:1740-1744) makes the caller widen char/short by the C type's
sign; PROMOTE_FUNCTION_ARGS and PROMOTE_FUNCTION_RETURN are undefined, so the callee neither re-extends an argument
nor its return (R3.44-001 items 2-3). Evidence therefore supports a type and rarely proves one.

- Argument, caller side (rule W-ARG-SITE; mips.h:1153, c-typeck.c:1740-1744): the last writer of $a_k before the site:
  `lb` s8, `lbu` u8, `lh` s16, `lhu` u16, `andi 0xff` u8, `andi 0xffff` u16, `sra 24/16` (after `sll`) s8/s16,
  `srl 24/16` (after `sll`) u8/u16.
- Argument, callee side (rule W-ARG-USE): the first read of incoming $a_k: `andi`, `sll`, `sb`, `sh`; with
  PROMOTE_FUNCTION_ARGS undefined (R3.44-001 item 2) such a narrowing is the body's use, not a re-extension.
- Return (rule W-RET): RET-EXIT narrowing writers (callee) and RET-READ kinds (callers) (R3.44-001 item 3).
- None of these: `unknown:no width evidence` (R3.44-001 items 2-3: evidence is optional by construction).

## Unknown reasons (closed list, precedence order)

Reasons 1-8 decide `ret.verdict` and are listed in `ret.reasons`; 9-10 are listed in `args.reasons` and never make the
return verdict `unknown` (a class with no width evidence can still be `unused`).

1. `indirect call` — no direct site, but the address is taken: reached only through a pointer (`jalr`), whose reads
   no callee can be credited with (C0124: an address-taken use has no call site).
2. `address taken` — direct sites none reading, but the address is taken (an indirect caller may read; C0124).
   Address taken: the function's start appears as an aligned word in the image of any binary whose stack holds this
   binary, or is formed by a `lui`/`addiu` (or `ori`) pair in such a binary's code. A value that lies outside every
   image of the referring binary's stack marks every binary with a row starting there (fallback below).
3. `tail position unresolved` — a tail site's caller class is itself `unknown` (not by recursion; R3.44-001 item 6).
4. `recursion` — a tail-graph cycle with no `used` (RET-FIX; R3.44-001 item 6).
5. `jump table with $v0 live` — $v0 pending at a `jr <reg>` whose table did not resolve (C0009; absolute SImode
   entries, mips.h:2570).
6. `path leaves body` — $v0 pending where a path runs past the body's end (the `_SIG` row's bounds, Makefile:74).
7. `cross-binary target unresolved` — a `jal` target two or more binaries of the caller's stack claim (the address is
   inside each one's image), or, outside every stack image, two or more classes start there (fallback below); every
   claimant instance at that address gets the reason (C0571: names and code are per binary).
8. `no callers` — no direct site and the address is not taken (C0124).
9. `frame unresolved` — (arguments) a stack access whose entry offset is not known on every path (mips.h:1809-1828).
10. `no width evidence` — (widths) none of the W- rules fired (R3.44-001 items 2-3).

Fallback (rule OUTSIDE-STACK): a module's stack holds main, resident and itself, not the overlay loaded beside it, so
its `jal`s into overlay space land in no stack image (md extern rows, C0571). Such a target is resolved fleet-wide by
function start, since a `jal` lands on a function start: exactly one class starting there is credited as a direct
site; two or more get reason 7; none is counted (`sites outside stack: no sig row at target`). A target inside a stack
image with no sig row is counted (`sites target has no sig row`); it credits no callee.

## Output (build/sig_evidence/)

- `census.jsonl`: one row per h_exact class (singletons included), sorted by the representative instance (the least
  (binary, vaddr)); keys sorted, fixed separators; every list sorted with fixed tie-breaks (R70). Fields: `h`, `nins`,
  `instances` [[binary, vaddr, name]], `ret` {verdict, reasons, cite (least reading caller cite), reads {kind: n},
  ret64, tail [caller class reps `binary:vaddr`]}, `exit` [[jr cite, [writer cite | `call <vaddr>` | `call jalr` |
  `entry`]]], `ret_width` [`exit:<w>`, `read:<kind>`], `args` {read [[k, first-read cite]], arity_lb, passthrough [k],
  sites {n, min, max} (n counts caller instances), widths {site {k: {w: n}}, use {k: kind}}, reasons},
  `varargs_spill` (k or null), `frame` {kind `sp`|`fp`, unresolved [cites]}. Callee-side cites use the representative
  instance.
- `summary.txt`: rows per verdict, per unknown reason, site statistics. No timestamps (two runs are byte-identical).

Known artifacts (3.44 T3 run): `frame unresolved` (2684 classes) is mostly the scratchpad stack switch
(`$sp` = 0x1F8003FC .. `lw $sp,0($sp)`), which this rule correctly leaves unresolved; arity_lb in the hundreds comes from
sig rows that split one function (a fragment whose epilogue reads its parent's frame, e.g. main 0x80041E64 inside
0x80041E2C).

## Comparison (3.44 T4)

`--compare` sets the C beside the census: every definition and `extern` declaration in a linked TU is joined to its
census class and checked against six rules. It reads `build/sig_evidence/census.jsonl` and needs no ROM bytes outside
build/ (R74).

```
PY tools/sig_evidence.py --compare -j 16   # -> build/sig_evidence/{compare.jsonl,compare.txt}; two runs are byte-identical
```

Census input: the census also holds instances for linked-ELF function symbols that have no `nins` > 0 sig row (sized
`t`/`T`, inside the image, the fleetgap filter: no `.L`/`L8`/`D_`/`jtbl`/`jr_` prefix, no `.NON_MATCHING` suffix). Body =
the image slice `[vaddr, vaddr+size)`, h = sha1(raw) as tools/sig_image.py:185, so equal bodies join existing classes.
Unaligned or overrunning symbols (data objects typed `t` in .text) are skipped and counted (`summary.txt`).

Inputs and the join:
- TUs: per binary B, `build/src/*.d` (main, top level) or `build/src/<B>/*.d`. A TU's files are the `src/` and `include/`
  paths of its first rule, normalized (the .d spells `src/<B>/../shared/x.h`). Each file is parsed once.
- Parse (comment-masked, `lc.sc.mask_text`, C0206): argcheck's DEF and KR_DEF (+ kr_params); a head inside a body is
  skipped. Declarations: a balanced-paren `extern ret name(...)`, `;`-terminated, so the nested-paren and multi-line forms
  DECL misses are included (C0581). Returns via argcheck `norm_ret`, with an empty spelling read as `int`. Asm labels
  (3.44 T5, C0223): a prototype `[extern] <ret> CNAME(<params>) __asm__("SYM");` is a declaration of SYM (the symbol the
  jal targets), ret and params from the C head; it also maps CNAME -> SYM for every TU that includes the file, so a
  definition of CNAME (aF*/ta*/`_impl`/`_body` names) is joined as SYM (`definition instances ... joined by asm
  label`). An object label `extern T obj __asm__("S");` is no function declaration: skipped and counted (`asm-label C
  names (per file)` line). Rows name the label; `decl_text` keeps the C spelling. SHARED_BIND
  (`#define SHARED_FN <own>` + `#include`) makes the header's SHARED_FN body `<own>`'s definition in that TU: `def_file`
  = the header holding the text, `bind_tu` = the binding TU.
- Name to address: B's ELF symtab (`mipsel-linux-gnu-nm -S --defined-only`, absolute included; main
  build/us/SLUS_007.26.elf, others build/<B>/<B>.elf). Owner: B's own image, else the first image of B's splat stack
  holding the address, else fleet-wide by function start (OUTSIDE-STACK, unique class only). Then the class is looked up
  by (owner, vaddr). A definition must land in B's own image.
- A declaration's definition = the placed definitions at (owner, vaddr). If they disagree on (ret, arity, varargs), the
  declaration is counted apart and not compared.

Rules (a row per (binary, definition site) or per (binary, declaration line)):

| id | condition | cited | source |
|---|---|---|---|
| RET-VOID-READ | class `ret.verdict` `used`, at least one census `exit` writer other than `entry` or no `exit` at all (tail/leave only) (else skipped and counted in coverage as `RET-VOID-READ skipped: no value produced` rows/functions: an empty body reads garbage, C0587), and a `void` definition (row per def) or `void` declaration (row per line) | `ret.cite` (null when `used` only through RET-FIX: `tail` given) | C0543, C0587, R3.44-001 item 4 |
| RET-NONE | non-void definition (`void *` counts) whose masked body has no `return <expr>` and no `$v0 at exit:` comment in the body or the comment lines directly above the head | the definition | C0567 |
| DECL-RET | declaration `norm_ret` != its definition's (all declarations, `()` included) | both spellings | C0548, C0552 |
| DECL-EMPTY | `()` declaration; `kr_marked` when the line has `// K&R:` | the line | C0508 |
| ARG-OVER | census `args.arity_lb` > the definition's argument words (1 per parameter; double / long long / s64 / u64 2 from an even register; K&R float = double); by-value struct skipped and counted; varargs never | `args.read` entry of the highest k | R3.44-001 items 2-3 |
| DECL-ARITY | non-`()` declaration whose `arity()` (`(void)` = 0) != the definition's (K&R: names); varargs definition only when fewer than its named count | both arities | C0508, C0581 |

Unplaced, counted by reason and never guessed: file in no TU, file missing, name not in the symtab, name has several
addresses, definition address outside own image, address in no class, >1 class (OUTSIDE-STACK), SHARED_FN header not in
the TU. Placed declarations whose callee has no placed C definition (INCLUDE_ASM) only feed RET-VOID-READ and DECL-EMPTY.
Known blind spot: a by-value parameter of an anonymous-struct typedef (`typedef struct {...} SVECTOR;`) is not in
argcheck's typedef map, so it counts as one word.

Outputs:
- `compare.jsonl`: one row per disagreement, sorted (rule, binary, vaddr, def_file, decl_file, name), keys sorted. Fields:
  rule, binary (the C's binary), owner (the instance's binary), vaddr, h, name, def_file `path:line`, bind_tu, def_ret,
  decl_file, decl_text, decl_ret, kr_marked, cite, objects (TUs including the file in that binary); ARG-OVER: arity_lb,
  def_words, def_params; DECL-ARITY: decl_args, def_args, def_params; RET-VOID-READ: tail.
- `compare.txt` (also printed): per rule rows, functions (classes), names, def sites, declaration lines, files, objects,
  and RETURN-LIE rows of config/dedup_exceptions.tsv whose h_exact is a touched class. Then the coverage block: files, TUs,
  definitions (sites, names, K&R heads, SHARED_FN bodies), declaration lines by shape (`(void)`, `()` unmarked, `()`
  K&R-marked, nested-paren, multi-line, other; per file line, so a header line counts once), placements, unplaced by reason,
  and src files in no .d (named).

## Ledger (3.44 T4)

`config/lying_exceptions.tsv` (hand-edited config): tab-separated `callee def_file kind cause task cites`; `#` lines and
the header skipped. Fields 0-2 are the key type_census `--check` reads (type_census.py `lying_exceptions()`, share_body.py
reads 0-2 too). `kind` `return` means DECL-RET; any other kind is a rule id above. `cites`: `<binary>:0x<vaddr> <insn>`
items, `; `-separated, in exactly the census `cite()` text (rabbitizer, whitespace collapsed): the callee's narrowing
exit writer(s), or where there is none the exit writer and the caller-side conversion read, plus one caller read (2-4).

```
PY tools/sig_evidence.py --check -j 16     # runs --compare, then -> build/sig_evidence/check.txt (also printed)
```

`--check`: (a) every cite is re-decoded from the extracted binary (`<alias>_EXE`, offset vaddr - `_VRAM_BASE`) with the
census decoder and `cite()`, compared whitespace-normalized: a mismatch, an unknown binary, an address outside the image
or a row with no cites is a failed cite; (b) a row is used when a current disagreement matches it: `name` == callee,
`def_file` path or `bind_tu` == def_file, rule == kind; an unmatched row is an unused row; (c) a disagreement matched by
no row is unledgered. Prints the three counts (unledgered per rule) and the first 20 of each. Exit 1 on any failed cite,
unused row or unledgered disagreement, else 0. Not in tools-health yet (3.44 T9).
def_file `-` (3.44 T6) = no C definition (asm-only callee): the row matches a disagreement of its callee+kind whose
def_file is None.

## Return views (3.44 T5)

`RET_AS(T, fn, params)` (include/common.h, after `CAST_*`) is `((T (*)params)(fn))`: a call through `fn` cast to a function
returning `T`. Rule: the one prototype of `fn` is its definition's (the C says what the callee returns); `RET_AS(T, …)` is
written only at a call where the shipped caller read the return as `T`, measured in the census (e.g. `$v0` read unextended
after a callee that exits `andi 0xff`). The `jal` is kept: the cast call is proven byte-identical by the build. One ledger
row per (callee, view), with cites. A callee whose mismatch the cast cannot resolve (bytes move either way) stays in
`config/lying_exceptions.tsv`.

Ladder per callee (3.44 T5, C0592): (1) every declaration, asm-label alias prototypes included, takes the definition's
type; (2) an object that then differs or fails to compile gets `RET_AS(<old declared type>, …)` at its calls (value calls;
a discarded call only if the object still differs, cause `RET-VIEW-REGALLOC`); (3) a `void` definition whose callers read
`$v0` (RET-VOID-READ) is widened to the declarations' type with a `/* $v0 at exit: … */` comment above the head, unless
that turns its many `void` declarations into new DECL-RET rows; (4) else a lying_exceptions row. `SHARED-DECL-SPLIT`: one
declaration in a shared header serves per-overlay definitions that disagree; no single type fits, so the row stays.
A `RET_AS` on an asm-label alias `CNAME` (`… CNAME(…) __asm__("SYM");` in the same file) names `SYM`; a SHARED_FN bind
(`#define SHARED_FN own` + `#include`) defines `own` in the binding file, so a row's def_file may be that file (both in
sig_evidence `--check` and type_census `--check-casts`).

`config/ret_view_casts.tsv` (hand-edited config): tab-separated `callee def_file view cause task cites`, header comment in
lying_exceptions.tsv's style; `cites` as there (the callee's exit writer and one caller read).

`--check` also: (a) re-decodes every ret-view cite (same decoder, same failed-cite test); (b) finds every
`RET_AS(T, fn, params)` site in the parsed C (comments masked; a `#define RET_AS` line is not a site); a site with no row
(fn, T) is unbacked; (c) a row with no site is unused; (d) a row whose `def_file` is not a file defining `fn` is a wrong
def_file. check.txt gains `ret-view rows/cites/RET_AS sites` and the four counts (first 20 of each); any nonzero exits 1.
type_census `--check-casts` counts RET_AS as macro class `RET-VIEW` (K form, no base/off; restruct ignores it) and backs a
site only by a row (callee, view) of this file, never the restruct ledger.

## Unprototyped views (3.44 T6)

`KR_AS(T, fn)` (include/common.h, after `RET_AS`) is `((T (*)())(fn))`: a call through `fn` cast to an unprototyped function
returning `T`, where `T` is the definition's return type. Rule: every `()` declaration of `fn` takes its one prototype (the
definition's; an asm-label `CNAME(…) __asm__("SYM")` line keeps its label); a call whose shipped caller passed fewer
arguments than the callee reads (census `args.read` / `args.arity_lb`) is written `KR_AS(T, fn)(args)`, so it stays the
K&R call it was. One ledger row per callee, with cites; proven byte-identical per object by scratch compile vs HEAD (C0589).
A callee whose objects still differ keeps its `()` declarations and gets a lying_exceptions row instead.

`config/kr_view_casts.tsv` (hand-edited config): tab-separated `callee def_file cause task cites` (no view column: `T` is
pinned by the definition), header comment in ret_view_casts.tsv's style; `cites` = the callee's read of the missing
argument register or slot and one short caller's `jal`.

`--check` also runs the ret-view checks over it (shared code, `check_ret_views(kr=True)`): cites re-decoded; every `KR_AS`
site (comments masked, `#define` lines skipped, asm-label aliases name the label) needs a row for `fn`; a row with no site is
unused; a row whose `def_file` does not define `fn` is a wrong def_file. check.txt gains `kr-view rows/cites/KR_AS sites` and
the four counts; any nonzero exits 1. type_census `--check-casts` counts KR_AS as macro class `KR-VIEW` (K form, no
base/off; restruct ignores it) and backs a site only by a row (callee) of this file.
def_file `-` = asm-only callee (no C definition): the def_file check passes iff no parsed file defines `fn`; type_census
backs on callee alone, so a `-` row backs its sites there too.
