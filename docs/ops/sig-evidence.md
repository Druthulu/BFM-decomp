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
requirements-python.txt:21).

## Inputs

- The 218 binaries of Makefile:59 (`BINARIES`), each alias's `_EXE`, `_VRAM_BASE` (Makefile, config/overlays.mk,
  config/modules.mk). File offset = vaddr - `_VRAM_BASE`.
- Each alias's `_SIG` file (`.run/sig.<alias>.jsonl`, written by tools/sig_image.py from the original bytes). Rows with
  `src` IMPORTED (nins 0) are skipped. A function instance is (binary, vaddr); its body is the image slice
  `[vaddr, vaddr + nbytes)`; instances with equal `h_exact` are one class and are decoded once.
- Symbol stacks: the alias's splat yaml `symbol_addrs_path`. A stack file names a binary (`symbols.us.txt` = main,
  `symbols.resident.txt` = resident, `symbols.<alias>.txt` = the alias); other files (`symbols.us.ram.txt`) are not
  binaries. The stack decides which binaries a `jal` may land in (below) and the instance names (own file first, then
  the sig row's name). Names are per binary (C0571): everything keys on (binary, vaddr). Asserted at startup: every
  alias's stack holds its own file.

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
  clobbered (caller-saved; R3.44-001 item 3: no promotion around calls, mips.h, PROMOTE_FUNCTION_RETURN undefined).
- Frame: $sp offset from entry tracked through `addiu $sp,$sp,imm`; `move/addu/or $fp,$sp,...` copies it to $fp
  (-O0 frames, Makefile:920, 1078-1079, 1082, 1111, 1119). A memory access off $sp or $fp is converted to an
  entry-$sp offset; where the offset is not known on every path the access is `frame unresolved`.

## Return evidence

- Caller read (rule RET-READ): at a call site, the first instruction after the call event that reads $v0 on some
  path before $v0 is written on that path. Its existence makes the callee's `ret` `used`, citing it. The read kind is
  recorded: `andi:<mask>`, `sll:<n>`, `sb`, `sh`, else `full` (any other read, unextended).
- 64-bit read (rule RET-V1): $v1 read after the call event before written. 64-bit values return in $v0:$v1
  (R3.44-001 item 4; mips.h:1255-1257, 1876, 1891-1897). It also makes `ret` `used`, with `ret64` set.
- Dead (rule RET-DEAD): $v0 written before any read, or clobbered by the next call event (a tail `j` included), on
  every path.
- Tail (rule RET-TAIL): $v0 reaches the caller's own `jr $ra` unread. `f();` and `return f();` emit the same caller
  code (R3.44-001 item 6), so the site's use is the caller's own `ret`, settled by the fixed point below. A `j` to a
  function start outside the body is a tail-jump site: its use is the jumping function's `ret` likewise.
- Tail fixed point (rule RET-FIX): the tail graph (callee class -> caller class) is processed in strongly connected
  component order, callers first. A class is `used` when a direct site reads or a tail site's caller class is `used`;
  a component of two or more classes, or a self-loop, with no `used` is `unknown:recursion`. A class whose tail
  caller is `unknown:recursion` gets `recursion`, not `tail position unresolved`.
- Verdict: `used` when any site of any instance reads (RET-READ, RET-V1, or RET-FIX through a `used` caller).
  Otherwise `unknown:<reason>` when any reason below applies (the first in list order is the verdict; all are listed
  in `reasons`). Otherwise `unused`: every call site is known and none reads.
- Callee exit (rule RET-EXIT): for each `jr $ra`, the writers of $v0 reaching it (reaching definitions, the jr's own
  delay slot included): an instruction, `call <target>` (a callee's return passed through), or `entry` ($v0 not
  written on that path). Narrowing writers (`andi $v0,..,0xff/0xffff`, `lbu/lb/lhu/lh $v0`, `sra`/`srl $v0` after
  `sll`, the W-ARG-SITE classifier)
  are the callee's own width evidence; no promotion of the return exists (R3.44-001 item 3).

## Argument evidence

- Callee reads (rule ARG-READ): $a0-$a3 read on some path from entry before written ($a_k is argument k; mips.h:1881-1886),
  and loads from entry $sp+16+4k, argument 4+k (mips.c:2931-2937, the 16-byte caller-owned home area mips.h:1809-1828).
  `arity_lb` = highest argument index read + 1 (cookbook/INDEX.md:620 addendum: a callee's arity lower bound from its
  own stack-argument reads).
- Pass-through (rule ARG-PASS): an incoming $a_k still unwritten at a call event or tail jump may be forwarded without
  a read instruction; recorded apart, not counted in `arity_lb`.
- Site setup (rule ARG-SITE): at each site, the $a0-$a3 written on every path since entry or the previous call event,
  delay slot included, and the stores to the caller's $sp+16+4k in the same window. A stack slot counts only when the
  function never loads it back (else it is a local or a register save, e.g. `sw $ra,0x10($sp)`), lies below the lowest
  address-taken local (`addiu rX,$sp,off`: GCC puts outgoing args below locals), and continues a contiguous run from
  $sp+16. Site arity = highest set argument index + 1. Per callee class: min and max over its sites. An
  argument-register copy in the `jal`'s own delay slot is a setup for that call (C0284).
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

- Argument, caller side (rule W-ARG-SITE): the last writer of $a_k before the site: `lb` s8, `lbu` u8, `lh` s16,
  `lhu` u16, `andi 0xff` u8, `andi 0xffff` u16, `sra 24/16` (after `sll`) s8/s16, `srl 24/16` (after `sll`) u8/u16.
- Argument, callee side (rule W-ARG-USE): the first read of incoming $a_k: `andi`, `sll`, `sb`, `sh`.
- Return (rule W-RET): RET-EXIT narrowing writers (callee) and RET-READ kinds (callers).
- None of these: `unknown:no width evidence`.

## Unknown reasons (closed list, precedence order)

Reasons 1-8 decide `ret.verdict` and are listed in `ret.reasons`; 9-10 are listed in `args.reasons` and never make the
return verdict `unknown` (a class with no width evidence can still be `unused`).

1. `indirect call` — no direct site, but the address is taken: reached only through a pointer (`jalr`), whose reads
   no callee can be credited with.
2. `address taken` — direct sites none reading, but the address is taken (an indirect caller may read).
   Address taken: the function's start appears as an aligned word in the image of any binary whose stack holds this
   binary, or is formed by a `lui`/`addiu` (or `ori`) pair in such a binary's code.
3. `tail position unresolved` — a tail site's caller class is itself `unknown` (not by recursion).
4. `recursion` — a tail-graph cycle with no `used` (RET-FIX).
5. `jump table with $v0 live` — $v0 pending at a `jr <reg>` whose table did not resolve.
6. `path leaves body` — $v0 pending where a path runs past the body's end.
7. `cross-binary target unresolved` — a `jal` target two or more binaries of the caller's stack claim (the address is
   inside each one's image); every claimant instance at that address gets the reason.
8. `no callers` — no direct site and the address is not taken.
9. `frame unresolved` — (arguments) a stack access whose entry offset is not known on every path.
10. `no width evidence` — (widths) none of the W- rules fired.

A `jal` target inside no stack binary's image, or at an address with no sig row, is counted in the summary's site
statistics; it credits no callee.

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
