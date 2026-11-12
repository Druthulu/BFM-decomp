# 3.43 T4 — 2026-11-10: hard-reg pin wall probes (the 9 expand-hardreg-var rows)

The 9 `wall:expand-hardreg-var` rows of 3.43 T4 (plus the func_8017EC90 `__param` variant body), probed by dropping the
`$4`-`$7` register pins and diffing the per-pass RTL dumps of the pinned (orig) and unpinned (nopin) bodies.
Regenerate: `/usr/bin/python3 tools/wall_probe.py --out DIR <file> <func>` per row (the tu path is the first line of
each probe dir's `tu`), then `--passdiff DIR/<row>` (add `--body FILE` for the `__param` row). Technique: C0568.
Below: each probe dir's analysis.txt, then T4's rtl_diffs.txt, c_body.md and passdiff_all.txt verbatim.

## func_80148824__func_80148824

```
try orig score=0 match=True ; nopin score=12 match=False ; dropped $5,$4
skip orig self-copy uids: 
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 77: alloc=none hard=- live_at_entry=False | no lreg line
pin $5 -> pseudo 76: alloc=global hard=6 live_at_entry=False | Register 76 used 2 times across 2 insns in block 8; pref LO_REG, else GR_REGS.
greg first hard-reg diff insn #3: orig (set (r5) (r3)) | nopin (set (r2) (and:SI (r2) (const_int 255)))
first divergent pass: rtl
survives combine: True
```

## func_80177F84__func_80177F84

```
try orig score=0 match=True ; nopin score=21 match=False ; dropped $6,$4,$4
skip orig self-copy uids: 
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 82: alloc=none hard=- live_at_entry=False | no lreg line
pin $4 -> pseudo 88: alloc=local hard=4 live_at_entry=False | Register 88 used 4 times across 4 insns in block 4; GR_REGS or none.
pin $6 -> pseudo 76: alloc=global hard=7 live_at_entry=False | Register 76 used 7 times across 27 insns; dies in 0 places; GR_REGS or none; pointer.
greg first hard-reg diff insn #0: orig (set (r5) (r5)) | nopin (set (r4) (r4))
first divergent pass: rtl
survives combine: True
```

## func_8017D8E8__ov_SC03_108_jr_8017BEBC

```
try orig score=0 match=True ; nopin score=22 match=False ; dropped $4,$5
skip orig self-copy uids: 67
decisive struct pass: sched
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine== sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 78: alloc=local hard=2 live_at_entry=False | Register 78 used 4 times across 3 insns in block 1; GR_REGS or none.
pin $5 -> pseudo 79: alloc=local hard=5 live_at_entry=False | Register 79 used 12 times across 7 insns in block 1; GR_REGS or none.
greg first hard-reg diff insn #4: orig (set (r4) (ashift:SI (r16) (const_int 10))) | nopin (set (r2) (sign_extend:SI (mem/s:HI (plus:SI (r17) (const_int 112)))))
first divergent pass: rtl
survives combine: False
```

## func_8017DE00__ov_SC02_039_jr_8017BEBC

```
try orig score=0 match=True ; nopin score=22 match=False ; dropped $4,$5
skip orig self-copy uids: 67
decisive struct pass: sched
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine== sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 78: alloc=local hard=2 live_at_entry=False | Register 78 used 4 times across 3 insns in block 1; GR_REGS or none.
pin $5 -> pseudo 79: alloc=local hard=5 live_at_entry=False | Register 79 used 12 times across 7 insns in block 1; GR_REGS or none.
greg first hard-reg diff insn #4: orig (set (r4) (ashift:SI (r16) (const_int 10))) | nopin (set (r2) (sign_extend:SI (mem/s:HI (plus:SI (r17) (const_int 112)))))
first divergent pass: rtl
survives combine: False
```

## func_8017EC90__ov_SC03_007_jr_8017AE2C

```
try orig score=0 match=True ; nopin score=9 match=False ; dropped $4,$5
skip orig self-copy uids: 
decisive struct pass: cse
struct vector: rtl== jump== cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 74: alloc=global hard=18 live_at_entry=True | Register 74 used 1 times across 5 insns; GR_REGS or none.
pin $5 -> pseudo 75: alloc=global hard=3 live_at_entry=True | Register 75 used 2 times across 8 insns; GR_REGS or none.
greg first hard-reg diff insn #0: orig (set (r18) (r4)) | nopin (set (r2) (const_int -262144))
first divergent pass: cse
survives combine: True
```

## func_8017EC90__ov_SC03_007_jr_8017AE2C__param

```
try orig score=0 match=True ; nopin score=2 match=False ; dropped $4,$5,variant .run/P40/t20/param_8017EC90.c
skip orig self-copy uids: 
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 74: alloc=none hard=- live_at_entry=False | no lreg line
pin $5 -> pseudo 75: alloc=none hard=- live_at_entry=False | no lreg line
greg first hard-reg diff insn #0: orig (set (r18) (r4)) | nopin (set (r5) (r5))
first divergent pass: rtl
survives combine: True
```

## func_8017F4A0__ov_SC04_016_jr_8017F03C

```
try orig score=0 match=True ; nopin score=2 match=False ; dropped $4,$5
skip orig self-copy uids: 63
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 77: alloc=none hard=- live_at_entry=False | no lreg line
pin $5 -> pseudo 78: alloc=none hard=- live_at_entry=False | no lreg line
greg first hard-reg diff insn #10: orig (set (r4) (r18)) | nopin (set (r2) (asm_operands/v ("addiu %0,$0,0x3000") ("=r") 0 () () ("/home/musashi/bfm-decomp/.run/3.43/t4/probe/func_8017F4A0__ov_SC04_016_jr_8017F03C/tu.c") 2910
first divergent pass: rtl
survives combine: True
```

## func_801806F8__ov_SC03_013_jr_801806F8

```
try orig score=0 match=True ; nopin score=40 match=False ; dropped $4
skip orig self-copy uids: 
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 74: alloc=global hard=5 live_at_entry=False | Register 74 used 6 times across 7 insns in block 1; dies in 2 places; GR_REGS or none.
greg first hard-reg diff insn #0: orig (set (r5) (r4)) | nopin (set (r4) (r4))
first divergent pass: rtl
survives combine: True
```

## func_8018298C__ov_SC04_000_jr_801818E8

```
try orig score=0 match=True ; nopin score=2 match=False ; dropped $4,$5
skip orig self-copy uids: 79
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 77: alloc=none hard=- live_at_entry=False | no lreg line
pin $5 -> pseudo 78: alloc=none hard=- live_at_entry=False | no lreg line
greg first hard-reg diff insn #14: orig (set (r4) (r18)) | nopin (set (r2) (asm_operands/v ("addiu %0,$0,3") ("=r") 0 () () ("/home/musashi/bfm-decomp/.run/3.43/t4/probe/func_8018298C__ov_SC04_000_jr_801818E8/tu.c") 3489))
first divergent pass: rtl
survives combine: True
```

## func_8018DBF0__ov_SC04_011_jr_8017D494

```
try orig score=0 match=True ; nopin score=2 match=False ; dropped $4,$5
skip orig self-copy uids: 79
decisive struct pass: rtl
struct vector: rtl=X jump=X cse=X loop=X cse2=X flow=X combine=X sched=X lreg=X greg=X sched2=X jump2=X dbr=X
pin $4 -> pseudo 77: alloc=none hard=- live_at_entry=False | no lreg line
pin $5 -> pseudo 78: alloc=none hard=- live_at_entry=False | no lreg line
greg first hard-reg diff insn #14: orig (set (r4) (r18)) | nopin (set (r2) (asm_operands/v ("addiu %0,$0,3") ("=r") 0 () () ("/home/musashi/bfm-decomp/.run/3.43/t4/probe/func_8018DBF0__ov_SC04_011_jr_8017D494/tu.c") 14393))
first divergent pass: rtl
survives combine: True
```

## rtl_diffs.txt

```
##### 801806F8
29c29
<             (label_ref 205)
---
>             (label_ref 203)
56c56
< (insn (set (reg:SI P)
---
> (insn (set (reg/v:SI 74)
63c63
<         (reg:SI P)) -1 (nil)
---
>         (reg/v:SI 74)) -1 (nil)
##### 8017D8E8
20c20
< (insn (set (reg:SI P)
---
> (insn (set (reg/v:SI 78)
24,26d23
< (insn (set (reg/v:SI 4 a0)
<         (reg:SI P)) -1 (nil)
<     (nil))
63c60
< (insn (set (reg:SI P)
---
> (insn (set (reg/v:SI 79)
##### 8018298C
79c79
< (insn (set (reg/v:SI 4 a0)
---
> (insn (set (reg/v:SI 77)
82c82
< (insn (set (reg/v:SI 5 a1)
---
> (insn (set (reg/v:SI 78)
120c120
<         (zero_extend:SI (reg:HI 5 a1))) -1 (nil)
---
>         (zero_extend:SI (subreg:HI (reg/v:SI 78) 0))) -1 (nil)
##### 8018DBF0
79c79
< (insn (set (reg/v:SI 4 a0)
---
> (insn (set (reg/v:SI 77)
82c82
< (insn (set (reg/v:SI 5 a1)
---
> (insn (set (reg/v:SI 78)
120c120
<         (zero_extend:SI (reg:HI 5 a1))) -1 (nil)
---
>         (zero_extend:SI (subreg:HI (reg/v:SI 78) 0))) -1 (nil)
##### 8017F4A0
62c62
< (insn (set (reg/v:SI 4 a0)
---
> (insn (set (reg/v:SI 77)
65c65
< (insn (set (reg/v:SI 5 a1)
---
> (insn (set (reg/v:SI 78)
95c95
<         (zero_extend:SI (reg:HI 5 a1))) -1 (nil)
---
>         (zero_extend:SI (subreg:HI (reg/v:SI 78) 0))) -1 (nil)
##### 80148824
23c23
< (insn (set (reg/v:SI 5 a1)
---
> (insn (set (reg/v:SI 76)
34c34
< (insn (set (reg/v:SI 4 a0)
---
> (insn (set (reg/v:SI 77)
52c52
<         (neg:SI (reg/v:SI 4 a0))) -1 (nil)
---
>         (neg:SI (reg/v:SI 77))) -1 (nil)
##### 80177F84
23c23
< (insn (set (reg:SI P)
---
> (insn (set (reg/v:SI 76)
27,29d26
< (insn (set (reg/v:SI 6 a2)
<         (reg:SI P)) -1 (nil)
<     (nil))
50c47
< (insn (set (reg/v:SI 4 a0)
---
> (insn (set (reg/v:SI 82)
```

## c_body.md

```
- C0542's "first divergent pass" is not the wall when the diff at that pass dies later. Read the diff content at each pass up to combine, not only the per-pass equal/differ vector.
- 3.43 T4, 9 `expand-hardreg-var` rows. Every vector read `rtl=X ... combine=X`, yet in 3 rows the rtl temp+copy is gone at cse and a new diff takes its place: cse forwards pseudo arg copies to the call, while the hard-reg var keeps them early (cse-copy-merge). In 2 rows combine is equal, and sched1 re-diverges because a hard-reg var carries dependencies a pseudo lacks (sched1-hoist-sink).
- Canonicaliser trap (3.40 probe.py): orig uids skipped as self-copies at `.rtl` (`$4=$4` arg copies) stayed skipped in later passes, but combine folds a constant into them (`$4=409`), so a phantom one-insn diff appeared. Skip a uid only while it is still a self-copy in that pass.
- Tools (scratch): .run/3.43/t4/bin/probe.py (fixed copy), passdiff.py (per-pass canonical diff), ctxdiff.py (one pass, with context).
```

## passdiff_all.txt

```
##### func_80148824__func_80148824
== rtl orig 43 nopin 42
  -(parallel ((set (p9) (mult:SI (p6) (p6))) (clobber (scratch:SI)) (clobber (scratch:SI))))
  -(set (VAR) (p9))
  +(parallel ((set (VAR) (mult:SI (p6) (p6))) (clobber (scratch:SI)) (clobber (scratch:SI))))
  -(set (p10) (h2))
  -(set (h2) (and:SI (p10) (const_int 255)))
  +(set (p9) (h2))
  +(set (h2) (and:SI (p9) (const_int 255)))
== jump orig 36 nopin 35
  -(parallel ((set (p9) (mult:SI (p6) (p6))) (clobber (scratch:SI)) (clobber (scratch:SI))))
  -(set (VAR) (p9))
  +(parallel ((set (VAR) (mult:SI (p6) (p6))) (clobber (scratch:SI)) (clobber (scratch:SI))))
  -(set (p10) (h2))
  -(set (h2) (and:SI (p10) (const_int 255)))
  +(set (p9) (h2))
  +(set (h2) (and:SI (p9) (const_int 255)))
== cse orig 36 nopin 34
  -(set (VAR) (p6))
  -(set (p7) (neg:SI (VAR)))
  +(set (p7) (neg:SI (p6)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
  +(set (h2) (and:SI (p6) (const_int 255)))
  -(set (p8) (neg:SI (VAR)))
  +(set (p8) (neg:SI (p4)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
== loop orig 36 nopin 34
  -(set (VAR) (p6))
  -(set (p7) (neg:SI (VAR)))
  +(set (p7) (neg:SI (p6)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
  +(set (h2) (and:SI (p6) (const_int 255)))
  -(set (p8) (neg:SI (VAR)))
  +(set (p8) (neg:SI (p4)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
== cse2 orig 36 nopin 34
  -(set (VAR) (p6))
  -(set (p7) (neg:SI (VAR)))
  +(set (p7) (neg:SI (p6)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
  +(set (h2) (and:SI (p6) (const_int 255)))
  -(set (p8) (neg:SI (VAR)))
  +(set (p8) (neg:SI (p4)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
== flow orig 36 nopin 33
  -(set (VAR) (p4))
  -(set (VAR) (p6))
  -(set (p7) (neg:SI (VAR)))
  +(set (p7) (neg:SI (p6)))
  -(set (h2) (and:SI (VAR) (const_int 255)))
  +(set (h2) (and:SI (p6) (const_int 255)))
  -(set (p8) (neg:SI (VAR)))
  +(set (p8) (neg:SI (p4)))
== combine orig 32 nopin 30
  -(set (VAR) (p2))
  -(set (VAR) (p4))
  -(set (p5) (neg:SI (VAR)))
  +(set (p5) (neg:SI (p4)))
  -(set (h2) (zero_extend:SI (VAR)))
  +(set (h2) (zero_extend:SI (sub:QI (p4))))
  -(set (p6) (neg:SI (VAR)))
  +(set (p6) (neg:SI (p2)))
##### func_80177F84__func_80177F84
== rtl orig 52 nopin 53
  -(set (p15) (sub:HI (p5)))
  -(set (p16) (and:SI (VAR) (sub:SI (p15))))
  -(set (p17) (sub:HI (p16)))
  -(set (p18) (ior:SI (sub:SI (p2)) (sub:SI (p17))))
  -(set (mem:HI (plus:SI (VAR) (const_int -2))) (sub:HI (p18)))
  +(set (p15) (VAR))
  +(set (p16) (sub:HI (p5)))
  +(set (p17) (and:SI (sub:SI (p15)) (sub:SI (p16))))
== jump orig 39 nopin 40
  -(set (p15) (sub:HI (p5)))
  -(set (p16) (and:SI (VAR) (sub:SI (p15))))
  -(set (p17) (sub:HI (p16)))
  -(set (p18) (ior:SI (sub:SI (p2)) (sub:SI (p17))))
  -(set (mem:HI (plus:SI (VAR) (const_int -2))) (sub:HI (p18)))
  -(set (p19) (ashift:SI (sub:SI (p3)) (const_int 16)))
  -(set (p20) (ashiftrt:SI (p19) (const_int 16)))
  -(set (p21) (lt:SI (p20) (const_int 5)))
== cse orig 37 nopin 36
  -(set (p9) (plus:SI (VAR) (const_int 20)))
  -(set (VAR) (p9))
  -(set (p10) (plus:SI (sub:SI (p3)) (const_int 1)))
  -(set (p3) (sub:HI (p10)))
  -(set (p11) (mem:HI (plus:SI (VAR) (const_int -2))))
  -(set (VAR) (zero_extend:SI (p11)))
  -(set (p12) (zero_extend:SI (h3)))
  -(set (p13) (ashift:SI (p12) (const_int 3)))
== loop orig 37 nopin 38
  +(set (p6) (plus:SI (VAR) (const_int -2)))
  -(set (p6) (ashiftrt:SI (p1) (const_int 16)))
  -(set (h2) (and:SI (p6) (const_int 15)))
  +(set (p7) (ashiftrt:SI (p1) (const_int 16)))
  +(set (h2) (and:SI (p7) (const_int 15)))
  -(set (p7) (ashift:SI (sub:SI (p3)) (const_int 16)))
  -(set (p8) (ashiftrt:SI (p7) (const_int 16)))
  -(set (pc) (if_then_else (eq:SI (p8) (p4)) (label_ref) (pc)))
== cse2 orig 37 nopin 39
  +(set (p6) (plus:SI (p0) (const_int 10)))
  -(set (p6) (ashiftrt:SI (p1) (const_int 16)))
  -(set (h2) (and:SI (p6) (const_int 15)))
  +(set (p7) (ashiftrt:SI (p1) (const_int 16)))
  +(set (p8) (and:SI (p7) (const_int 15)))
  +(set (h2) (p8))
  -(set (p7) (ashift:SI (sub:SI (p3)) (const_int 16)))
  -(set (p8) (ashiftrt:SI (p7) (const_int 16)))
== flow orig 37 nopin 38
  +(set (p6) (plus:SI (p0) (const_int 10)))
  -(set (p6) (ashiftrt:SI (p1) (const_int 16)))
  -(set (h2) (and:SI (p6) (const_int 15)))
  +(set (p7) (ashiftrt:SI (p1) (const_int 16)))
  +(set (p8) (and:SI (p7) (const_int 15)))
  +(set (h2) (p8))
  -(set (VAR) (h2))
  -(set (p7) (ashift:SI (sub:SI (p3)) (const_int 16)))
== combine orig 34 nopin 36
  -(set (p0) (h5))
  -(set (p1) (const_int 256))
  +(set (p0) (VAR))
  +(set (p1) (h5))
  +(set (p2) (const_int 256))
  +(set (p3) (const_int 0))
  +(set (p4) (const_int 5))
  +(set (p5) (const_int -257))
##### func_8017D8E8__ov_SC03_108_jr_8017BEBC
== rtl orig 31 nopin 32
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p11) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (p11))
  -(set (p11) (lt:SI (p2) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p11) (const_int 0)) (label_ref) (pc)))
  +(set (p12) (lt:SI (p2) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p12) (const_int 0)) (label_ref) (pc)))
== jump orig 25 nopin 26
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p11) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (p11))
  -(set (p11) (lt:SI (p2) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p11) (const_int 0)) (label_ref) (pc)))
  +(set (p12) (lt:SI (p2) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p12) (const_int 0)) (label_ref) (pc)))
== cse orig 23 nopin 25
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (const_int 409))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== loop orig 23 nopin 25
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (const_int 409))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== cse2 orig 23 nopin 25
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (const_int 409))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== flow orig 23 nopin 24
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== combine orig 20 nopin 20
##### func_8017DE00__ov_SC02_039_jr_8017BEBC
== rtl orig 31 nopin 32
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p11) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (p11))
  -(set (p11) (lt:SI (p2) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p11) (const_int 0)) (label_ref) (pc)))
  +(set (p12) (lt:SI (p2) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p12) (const_int 0)) (label_ref) (pc)))
== jump orig 25 nopin 26
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p11) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (p11))
  -(set (p11) (lt:SI (p2) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p11) (const_int 0)) (label_ref) (pc)))
  +(set (p12) (lt:SI (p2) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p12) (const_int 0)) (label_ref) (pc)))
== cse orig 23 nopin 25
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (const_int 409))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== loop orig 23 nopin 25
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (const_int 409))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== cse2 orig 23 nopin 25
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (const_int 409))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== flow orig 23 nopin 24
  +(set (p9) (ashiftrt:SI (VAR) (const_int 16)))
  -(set (VAR) (ashiftrt:SI (VAR) (const_int 16)))
  +(set (VAR) (p9))
  -(set (p9) (lt:SI (p1) (const_int 4)))
  -(set (pc) (if_then_else (ne:SI (p9) (const_int 0)) (label_ref) (pc)))
  +(set (p10) (lt:SI (p1) (const_int 4)))
  +(set (pc) (if_then_else (ne:SI (p10) (const_int 0)) (label_ref) (pc)))
== combine orig 20 nopin 20
##### func_8017EC90__ov_SC03_007_jr_8017AE2C
== rtl orig 107 nopin 107
== jump orig 97 nopin 97
== cse orig 86 nopin 85
  -(set (p0) (VAR))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
  -(set (p5) (mem/u:SI (p4)))
  -(parallel ((set (pc) (p5)) (use (label_ref))))
== loop orig 86 nopin 85
  -(set (p0) (VAR))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
  -(set (p5) (mem/u:SI (p4)))
  -(parallel ((set (pc) (p5)) (use (label_ref))))
== cse2 orig 86 nopin 85
  -(set (p0) (VAR))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
  -(set (p5) (mem/u:SI (p4)))
  -(parallel ((set (pc) (p5)) (use (label_ref))))
== flow orig 86 nopin 85
  -(set (p0) (VAR))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
  -(set (p5) (mem/u:SI (p4)))
  -(parallel ((set (pc) (p5)) (use (label_ref))))
== combine orig 74 nopin 73
  -(set (p0) (VAR))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (ashift:SI (p0) (const_int 2)))
  -(set (p3) (mem/u:SI (plus:SI (p2) (label_ref))))
  -(parallel ((set (pc) (p3)) (use (label_ref))))
  +(set (p0) (ltu:SI (VAR) (const_int 5)))
  +(set (pc) (if_then_else (ne:SI (p0) (const_int 0)) (pc) (label_ref)))
##### func_8017EC90__ov_SC03_007_jr_8017AE2C__param
== rtl orig 107 nopin 109
  +(set (VAR) (p0))
  +(set (VAR) (p1))
== jump orig 97 nopin 101
  +(set (p0) (VAR))
  +(set (p1) (VAR))
  +(set (VAR) (p0))
  +(set (VAR) (p1))
  -(set (p0) (VAR))
  +(set (p2) (VAR))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
== cse orig 86 nopin 87
  -(set (h18) (VAR))
  +(set (p1) (VAR))
  +(set (h18) (p0))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
== loop orig 86 nopin 87
  -(set (h18) (VAR))
  +(set (p1) (VAR))
  +(set (h18) (p0))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
== cse2 orig 86 nopin 87
  -(set (h18) (VAR))
  +(set (p1) (VAR))
  +(set (h18) (p0))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
== flow orig 86 nopin 87
  -(set (h18) (VAR))
  +(set (p1) (VAR))
  +(set (h18) (p0))
  -(set (p1) (ltu:SI (p0) (const_int 5)))
  -(set (pc) (if_then_else (ne:SI (p1) (const_int 0)) (pc) (label_ref)))
  -(set (p2) (label_ref))
  -(set (p3) (ashift:SI (p0) (const_int 2)))
  -(set (p4) (plus:SI (p3) (p2)))
== combine orig 74 nopin 74
  +(set (p0) (VAR))
  -(set (p0) (VAR))
##### func_8017F4A0__ov_SC04_016_jr_8017F03C
== rtl orig 33 nopin 34
  -(set (VAR) (zero_extend:SI (VAR)))
  +(set (p4) (zero_extend:SI (VAR)))
  +(set (VAR) (p4))
== jump orig 32 nopin 33
  -(set (VAR) (zero_extend:SI (VAR)))
  +(set (p4) (zero_extend:SI (VAR)))
  +(set (VAR) (p4))
== cse orig 32 nopin 31
  -(set (VAR) (p2))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p2))
== loop orig 32 nopin 31
  -(set (VAR) (p2))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p2))
== cse2 orig 31 nopin 31
  -(set (VAR) (p2))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p2))
  +(set (VAR) (const_int 128))
== flow orig 31 nopin 31
  -(set (VAR) (p2))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p2))
  +(set (VAR) (const_int 128))
== combine orig 30 nopin 30
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
  +(set (VAR) (const_int 128))
##### func_801806F8__ov_SC03_013_jr_801806F8
== rtl orig 73 nopin 73
  -(set (p9) (minus:SI (p7) (p8)))
  -(set (p10) (p9))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (plus:SI (p11) (p9)))
  -(set (p13) (ashift:SI (p12) (const_int 1)))
  -(set (VAR) (minus:SI (p5) (p13)))
  +(set (VAR) (minus:SI (p7) (p8)))
  +(set (p9) (VAR))
== jump orig 69 nopin 69
  -(set (p9) (minus:SI (p7) (p8)))
  -(set (p10) (p9))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (plus:SI (p11) (p9)))
  -(set (p13) (ashift:SI (p12) (const_int 1)))
  -(set (VAR) (minus:SI (p5) (p13)))
  +(set (VAR) (minus:SI (p7) (p8)))
  +(set (p9) (VAR))
== cse orig 65 nopin 64
  -(set (p8) (minus:SI (p6) (p7)))
  -(set (p9) (ashift:SI (p8) (const_int 1)))
  -(set (p10) (plus:SI (p9) (p8)))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (minus:SI (p4) (p11)))
  -(set (VAR) (p12))
  +(set (VAR) (minus:SI (p6) (p7)))
  +(set (p8) (ashift:SI (VAR) (const_int 1)))
== loop orig 65 nopin 64
  -(set (p8) (minus:SI (p6) (p7)))
  -(set (p9) (ashift:SI (p8) (const_int 1)))
  -(set (p10) (plus:SI (p9) (p8)))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (minus:SI (p4) (p11)))
  -(set (VAR) (p12))
  +(set (VAR) (minus:SI (p6) (p7)))
  +(set (p8) (ashift:SI (VAR) (const_int 1)))
== cse2 orig 65 nopin 64
  -(set (p8) (minus:SI (p6) (p7)))
  -(set (p9) (ashift:SI (p8) (const_int 1)))
  -(set (p10) (plus:SI (p9) (p8)))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (minus:SI (p4) (p11)))
  -(set (VAR) (p12))
  +(set (VAR) (minus:SI (p6) (p7)))
  +(set (p8) (ashift:SI (VAR) (const_int 1)))
== flow orig 65 nopin 64
  -(set (p8) (minus:SI (p6) (p7)))
  -(set (p9) (ashift:SI (p8) (const_int 1)))
  -(set (p10) (plus:SI (p9) (p8)))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (minus:SI (p4) (p11)))
  -(set (VAR) (p12))
  +(set (VAR) (minus:SI (p6) (p7)))
  +(set (p8) (ashift:SI (VAR) (const_int 1)))
== combine orig 58 nopin 58
  -(set (p8) (minus:SI (p6) (p7)))
  -(set (p9) (ashift:SI (p8) (const_int 1)))
  -(set (p10) (plus:SI (p9) (p8)))
  -(set (p11) (ashift:SI (p10) (const_int 1)))
  -(set (p12) (minus:SI (p4) (p11)))
  -(set (mem:SI (symbol_ref:SI ("D_801AD3E4"))) (p12))
  -(set (p13) (ashift:SI (p12) (const_int 1)))
  -(set (p14) (sign_extend:SI (mem/s:HI (plus:SI (p13) (symbol_ref:SI ("D_801A52C8"))))))
##### func_8018298C__ov_SC04_000_jr_801818E8
== rtl orig 34 nopin 35
  -(set (VAR) (zero_extend:SI (VAR)))
  +(set (p4) (zero_extend:SI (VAR)))
  +(set (VAR) (p4))
== jump orig 33 nopin 34
  -(set (VAR) (zero_extend:SI (VAR)))
  +(set (p4) (zero_extend:SI (VAR)))
  +(set (VAR) (p4))
== cse orig 33 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
== loop orig 33 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
== cse2 orig 32 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
  +(set (VAR) (const_int 128))
== flow orig 32 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
  +(set (VAR) (const_int 128))
== combine orig 31 nopin 31
  -(set (VAR) (p0))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p0))
  +(set (VAR) (const_int 128))
##### func_8018DBF0__ov_SC04_011_jr_8017D494
== rtl orig 34 nopin 35
  -(set (VAR) (zero_extend:SI (VAR)))
  +(set (p4) (zero_extend:SI (VAR)))
  +(set (VAR) (p4))
== jump orig 33 nopin 34
  -(set (VAR) (zero_extend:SI (VAR)))
  +(set (p4) (zero_extend:SI (VAR)))
  +(set (VAR) (p4))
== cse orig 33 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
== loop orig 33 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
== cse2 orig 32 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
  +(set (VAR) (const_int 128))
== flow orig 32 nopin 32
  -(set (VAR) (p1))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p1))
  +(set (VAR) (const_int 128))
== combine orig 31 nopin 31
  -(set (VAR) (p0))
  -(set (VAR) (const_int 128))
  +(set (VAR) (p0))
  +(set (VAR) (const_int 128))
```

