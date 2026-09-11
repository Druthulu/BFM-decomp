# func_8017E35C (ov_SC06_000_jr_8017AE2C.c) — e12, P36 T7 S104

**Score: 58 (sweep best 48) -> 0, zero levers.** The `__asm__ __volatile__ ("" :: "r" (nparts))` keepalive is deleted;
ONE statement moved: `g.opz = za;` is written at the end of BOTH arms of the TRI (FT3) depth-max if/else instead of once
after it. Not a signature change (the keepalive is mid-function, on `nparts`, not a `v0` return keepalive).

## (a) Residual
Register-only (plus the spill/reload shape that follows): `nparts` and `&vbuf` swap between `$fp` and a stack slot
(target: nparts in `$fp`, `&vbuf` spilled to 0x108 and reloaded as `lw s4,264(sp)` before the `lwc2`s; free: the
reverse), and `&g.flag`/`&g.opz` (sp+236/sp+240) swap `$s5`/`$s6`. Count 720 vs 719 only because of the spill reload.

## (b) Pass and decision (PROVEN: scratch/dumps_free, dumps_tree, dumps_body; .lreg "used N times across L insns")
global.c `allocno_compare` (gcc-2.7.2 global.c:586-607): priority = `(int)(floor_log2(refs)*refs/live * 10000)`, ties by
allocno number. The four contenders are all live across the WHOLE outer loop:

| pseudo | what | refs | live free -> body | priority free -> body |
|---|---|---|---|---|
| r80  | nparts | 4 | 554 -> 555 | 144 -> 144 |
| r224 | &vbuf (loop-hoisted) | 4 | 551 -> 552 | 145 -> **144** (tie, r80 first) |
| r241 | &g.flag | 7 | 550 -> 551 | 254 -> 254 |
| r243 | &g.opz  | 7 | 549 -> 550 | 255 -> **254** (tie, r241 first) |

The INTEGER truncation of the priority does it: one more insn inside the loop (live length +1 for every loop-live pseudo,
sched.c:3846-3861 recomputes lengths over the scheduled insns, :4946-4947 stores them) makes both pairs tie, and the tie
goes to the lower allocno. `.greg` order line: free `… 243 241 82 224 80 73`, body `… 241 243 82 80 224 73` = the tree's.
The keepalive worked the same way (its asm insn is the +1; its +2 refs on nparts are incidental). Diagnostic on bytes:
one empty `asm("")` anywhere in the loop nest -> 0; two -> 58; five -> 0 — exactly the arithmetic (k in {1,5,9,…}).

The +1 insn has to vanish from the output: the duplicated `g.opz = za;` store is a common TAIL of the two arms, which the
post-reload cross-jump pass re-merges (toplev.c:3142 `jump_optimize (insns, 1, 1, 0)`, `find_cross_jump` jump.c:2371) —
the target already shows the original's cross-jump of this same if/else (`j 3c70` into the shared
`if (za < g.sz2) za = g.sz2` tail). Pre-reload the loop is one insn longer; the bytes keep one store.

## (c) Move
```c
if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; g.opz = za; }
else               { za = g.sz1; if (za < g.sz2) za = g.sz2; g.opz = za; }
if (code == 7) g.opz = za + 0x50;
```

## (d) Generator proposal
When a keepalive/empty-asm lever's only effect is a global-alloc ORDER flip between loop-live pseudos whose integer
`allocno_compare` priorities differ by one unit, compute the live-length shifts k that tie them (all loop-live pseudos
shift together) and try source moves that add k pre-reload insns the post-reload cross-jump deletes: copy the statement
that FOLLOWS an if/else join into the end of both arms (and the inverse, hoist a duplicated arm tail out, for negative k).

## (e) What did not work (bytes)
~110 single spellings, all 58 or worse unless they change the insn count: declaration/statement reorders of nparts
(its birth cannot move far enough — the entry test `blez nparts` pins it; -2 at most, the tie needs -3), `continue`
forms, nested ifs, inlining the min/max temps, else-if splits (43-56, 718-719 ins), s16 cull extents (68-98), align-2
vertex types (58, same bytes — `SVec35C vbuf[3]` would be an equally-good spelling of the V8 copies). The FT4
depth-max as an if/else (`if (g.sz2 < g.sz3) zb = g.sz3; else zb = g.sz2;` and 23 other combinations) reaches 2: it also
adds the +1 insn (a copy) but the copy is not tied, so a real `move` remains.

## (f) Method
The allocation table (step 4) plus the integer truncation in allocno_compare was the whole story; the cheap diagnostic
that settled it was inserting an EMPTY asm at several places and counts (1/2/5) — a position-independent +k test the
method does not list. The "duplicate the join statement into both arms" move is S103 c6's cross-jump fact turned around
(c6 raised refs; here the duplicate raises the loop's insn count).

## (g) Structs
`g` already is a body-local struct; typing `vtx`/`prim` records or the vertex buffer (`SVec35C`) does not touch the
decision (58 unchanged, tested with three vertex types). The lever is an allocation-order tie, not an aliasing question.

## Stale header
The TU's comment block above the function ("THE FIVE DECISIVE LEVERS", item 5) describes the keepalive; with this body
item 5's first half is obsolete (the giv-order half, `prim` before `nprim`, still holds).
