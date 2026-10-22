---
ts: 2026-10-22T12:22:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jJ8aRC6RzGjF7rIb7cCu
---
The append works: `cat X >> Y`.

So I can:
1. Write the new lines to a temp file with the Write tool.
2. `cat temp >> moves.md`.

Let me verify the results.tsv now has 2 lines (I duplicated it). Let me fix: I need results.tsv to have the header + 5 rows. Let me just rewrite it with the Write tool (after Reading it).

Let me Read results.tsv (now 3 lines: header, header, and maybe more).

Hmm, `cat results.tmp >> results.tsv` duplicated the header → results.tsv now has the header twice. Let me Read and Write it properly.

Let me now write all the deliverables:
1. Read results.tsv → Write the final version.
2. Write the moves.md append lines to a temp file → cat >> moves.md.
3. Write the notes.md appends (4 items + item 2) — append via the same cat trick.
4. Write the log file (new file → Write directly).
5. Delete the dumps.

Let me do the Reads first: results.tsv.

Also, for the notes.md appends, I need the new content as temp files.

Let me prepare the content.

=== RESULTS.TSV ===
```
# dir	file	func	kinds	result	best	tries	wall	evidence
func_8017DE84__ov_SC02_039_jr_8017BEBC	src/ov_SC02_039/ov_SC02_039_jr_8017BEBC.c	func_8017DE84	launder	WALL	6	51	cse-join-fold	gcc-2.7.2: s16 v1 restores the copy (89 ins exact); residual = the arms' equal unk20 loads fold to ONE load at the join
func_8017E780__ov_SC03_092_jr_8017AE2C	src/ov_SC03_092/ov_SC03_092_jr_8017AE2C.c	func_8017E780	launder	WALL	2	61	sched1-call-group	gcc-2.7.2 sched1: the load's pseudo coalesces into a0 and lands after li a1,320; the re-tie's REG_DEP_OUTPUT pinned it before
func_80180054__ov_SC03_030_jr_8017AE2C	src/ov_SC03_030/ov_SC03_030_jr_8017AE2C.c	func_80180054	launder	WALL	40	30	cse-copy-merge	gcc-2.7.2 cse: u16 xa keeps a SUBREG copy (41 @101 ins exact); the target's move a2,v0 / move a1,v1 copies stay folded
func_801832A8__ov_SC02_026_jr_8017C180	src/ov_SC02_026/ov_SC02_026_jr_8017C180.c	func_801832A8	launder	WALL	14	31	sched1-birth-boost	gcc-2.7.2 sched1: the vol compound division puts the VOL chain first (237 exact) but 0x66666667 is born before its mult, not at the tail top
func_80185380__ov_SC03_014_jr_801848E4	src/ov_SC03_014/ov_SC03_014_jr_801848E4.c	func_80185380	launder	WALL	16	32	reload-rematerialise	gcc-2.7.2: unk6C via char* keeps 111 ins exact; the target holds &D_80190048 in v1, lever-free reload rematerialises it into at
```

Hmm, the evidence must be ≤ 140 chars. Let me count roughly — each is around 120-135. Let me trim to be safe.

Let me finalize the evidence strings (aim ≤ 135 chars):
1. "gcc-2.7.2: s16 v1 keeps the copy (89 ins exact); the arms' equal unk20 loads still fold to one load at the join" — 108 ✓
2. "gcc-2.7.2 sched1: the load coalesces into a0 and lands after li a1,320; the re-tie's REG_DEP_OUTPUT pinned it first" — 115 ✓
3. "gcc-2.7.2 cse: u16 xa keeps a SUBREG copy (41 @101 ins exact); the target's move a2,v0 / move a1,v1 stay folded" — 112 ✓
4. "gcc-2.7.2 sched1: the vol compound division puts VOL first (237 exact) but 0x66666667 is born before its mult" — 114 ✓
5. "gcc-2.7.2: unk6C via char* keeps 111 ins exact; the target holds &D_80190048 in v1, lever-free reload rematerialises it" — 121 ✓

=== MOVES.MD APPEND (5 lines) ===
```
launder | func_8017DE84 | WALL cse-join-fold — cse: s16 v1 restores the target's copy (89 ins exact) but the two arms' equal unk20 loads fold to ONE load at the join (RM2x)
launder | func_8017E780 | WALL sched1-call-group — sched1: the re-tie's REG_DEP_OUTPUT on the arg-setup pins the load before li a1,320; lever-free the load coalesces into a0 and lands after it (RM2x)
launder | func_80180054 | WALL cse-copy-merge — cse: u16 xa keeps a SUBREG copy (101 ins exact) but the target's move a2,v0 / move a1,v1 copies stay folded (RM2x)
launder | func_801832A8 | WALL sched1-birth-boost — sched1: the vol compound division restores the VOL chain first (237 exact) but the magic 0x66666667 is born before its mult, not at the tail top (RM2x)
launder | func_80185380 | WALL reload-rematerialise — reload: unk6C via char* keeps 111 ins exact but &D_80190048 is rematerialised into at instead of held in v1 (RM2x)
```

=== NOTES.MD APPENDS ===
For each item, append a section with the new findings. Let me keep them concise.

Item 1 notes append:
```

## RM2x retry (2026-10-22, 46 tries, best 6, 89 ins exact)
- `s16 v1;` (instead of `s32 v1;`) is the big win: 13 -> 6 with the instruction count EXACT (89).
  The narrow type keeps a SUBREG copy that cse cannot fold, so the target's `move v1,v0` reappears and the
  equality chain no longer becomes a case table. `u16 v1` gives 8 (the compare becomes `sltiu`, the target has
  `slti`); `s8 v1` gives 6 as well.
- Residual (6): the target keeps ONE `lw v1,32(s0)` per arm (case0 at ins 36, case1 at ins 45); lever-free the
  two arms' identical unk20 loads fold into ONE load placed at the join, and a nop appears where case0's load was.
  The launder's re-tie is what makes case1's `e` a distinct set, so the two loads cannot fold.
- Tried and no help: the unk20 load re-spelled (`*(s32*)((u8*)s0+0x20)`, `((s32*)s0)[8]`, `*(s32*)((void*)s0+0x20)`)
  in either arm, `e = e;` in either arm, the case0/case1 blocks swapped, the chain re-spelled (else-if, !=,
  reordered tests, `v1 < 4`), `u32 e`, in-place `|=` in the shared block, the store/copy swapped, decl order.
- Wall tag: cse-join-fold.
```
Hmm, that's long. Let me keep it but it's valuable.

Item 2 notes append:
```

## RM2x retry (2026-10-22, 57 tries, best 2, 200 ins exact)
- The residual is a pure 2-insn ORDER swap: the target has `lw a0,32(s0)` then `li a1,320`; lever-free the load
  lands after the `li`. Pre-sched RTL: the re-tie's asm output creates a REG_DEP_OUTPUT on the a1/a2 arg-setup
  (the asm may clobber caller-saved regs), so the whole call-arg group is pinned after the asm and the load
  (which feeds the asm) is pinned before it. Without the asm the load's pseudo coalesces into the hard reg a0
  (set a0 = mem) and sched1 orders the block [a1=320, load, a2=240, call].
- Tried and no help (57 bodies): the load re-spelled (char*/s32*/short* base, arg0 base), the call re-spelled
  (cast function pointer, comma expr, init-at-decl, inlined load), the 2nd/3rd arg re-spelled (self-minus,
  self-xor, and-0, mul-0, neg, shift - all folded at the front end), `t = t;`, an extra copy temp, goto/label,
  do-while(0), while(1)+break, switch(0), if(t==t), `t || 1`, `t = t ? t : t`, self-cmp tests.
- No plain-C spelling of a REG_DEP_OUTPUT on the call-arg setup was found: the asm's clobber is what pins it.
- Wall tag: sched1-call-group.
```

Item 3 notes append:
```

## RM2x retry (2026-10-22, 27 tries, best 40, 101 ins exact at 41)
- `u16 xa;` / `s16 xa;` is the win: 48 -> 41 with the instruction count EXACT (101). The narrow type keeps a
  SUBREG copy cse cannot fold, so the target's `move` for `xa = a` has a chance to reappear.
- Residual (41/40): the target's `move a2,v0` (xa=a) and `move a1,v1` (xb=b) are still folded away, and the
  target's branch polarity is `bltz` where lever-free gives `bgez`; the rest is register transposition.
- Tried and no help: `xb` as u16/s16 (keeps the $5 pin), `a` as s16, `b` as u16, `d1/d2` as s32, the if/else arms
  swapped (`a - b < 0` first), `d1 = xa - b` / `d1 = b - xa`, `if (a >= b)`, `xa = (s32)a`, `xa = xa`,
  `xb = xb`, `p = p + 2`, `if (d1 < best)`, `if (d2 < d1)`.
- Wall tag: cse-copy-merge.
```

Item 4 notes append:
```

## RM2x retry (2026-10-22, 19 tries, best 14, 237 ins exact)
- Confirmed the previous best: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` (the compound division gives vol a
  real second set, so the VOL chain stays first) -> 14 with 237 ins EXACT.
- Residual (14): the shared magic 0x66666667 is materialised (lui/ori) right before its first `mult`; the target
  births it at the TOP of the tail block (ins 198/199, in a0) and uses it for both divisions. The candidate's
  constant is born at ins 202/203 (in v0); everything else in the tail is instruction-identical.
- Pre-sched RTL (both bodies): the magic pseudo is set right before the VOL `mult` and has 2 uses (the VOL and
  the PAN mult). In the re-tie body the two divisions' magic pseudos are already one pseudo at sched time; in the
  compound-division body they are not, so the scheduler has no 2-use constant to hoist.
- Tried and no help: sx as s16, vol as u16, the sx division as a compound assignment, `av` as a ternary, an
  extra `vol` local, decimal constants, the decl order, `sx` chain first, `vol` self-copies, `sx = sx<<8` vs
  `sx = sx*256`.
- Wall tag: sched1-birth-boost.
```

Item 5 notes append:
```

## RM2x retry (2026-10-22, 27 tries, best 16, 111 ins exact)
- Win: spelling the SECOND `unk6C` read as `o = *(s32 *)((u8 *)param_1 + 0x6C);` (instead of the struct member
  read) gives 16 with 111 ins EXACT (the plain lever-free body is 39 @110).
- Residual (16): the target holds `&D_80190048` in a register (v1: lui/addiu then `sh v0,0(v1)`), lever-free
  reload rematerialises the address into `at` at each use (lui at; sh v0,0(at)) and the tail's two stores move.
  The re-tie's memory clobber is what keeps p10 in a register.
- Tried and no help: `p10 = p10;` (2nd set), `p10 = (u16*)&D_80190048`, `*(u16*)p10 = v6`, `*(u16*)(p10+8)`,
  dropping the g5e temp, the v6 load via char*, `state` as s32/u16, `switch((s32)state)`, `unk34` via char*,
  the unkA/unk5A constants in decimal, `(u32)` cast on the unkCC argument.
- The p10 re-tie also keeps the switch from becoming a case table (6814 ins when it is removed) - no plain-C
  spelling of that found.
- Wall tag: reload-rematerialise.
```

Hmm, that's a lot of writing. Let me keep the notes reasonably concise but informative.

=== LOG FILE === phase-ends/current/logs/T11.cRM2x.md
Timeline per item with dates, minutes, tries, moves that cracked, walls with evidence.

Let me write it now.

Also: delete the cc1 dumps (disk cap). The dumps are at:
.run/P40/T11/RM2x/func_801832A8__ov_SC02_026_jr_8017C180/dumps/ (dumps_cand, dumps_origd, dumps_w4d)
I need to remove them. `rm -rf` — is that allowed? The constraint says "cc1 dumps ... are deleted (rm -rf that dump dir) as soon as you have read them". So rm -rf is expected. Let me try.

Also the orig_tu.c/w4_tu.c copies (small).

Let me also check the shard dir size.

Let me now execute:
Message 1: Read results.tsv (to enable Write) + Write the new moves.md lines temp + Write the notes temp files... hmm, the notes appends need 5 temp files + a cat >> each. That's 5 Bash calls. Hmm.

Alternative for the notes: since notes.md is small (1-2 KB), I could Read + Write each. 5 Reads + 5 Writes = 10 calls but no Bash.

Hmm, the cat-append route: 1 Write (temp) + 1 Bash per file = 10 calls too. Same. But the Write of the temp file has the content in the tool call either way.

Hmm, the Read of notes.md adds tokens to the context (5 notes files ≈ 6KB). The temp-file approach avoids reading them. Let me use the temp-file approach: Write temp + Bash append.

Actually, I can batch: Write 6 temp files (results.tmp2, moves_lines, notes1..5) in ONE message (6 Write calls), then 6 Bash append calls in one message. That's 2 messages.

But the Write for results.tsv needs the Read first. Hmm — the results.tsv is tiny; let me use the same trick: Write the 5 rows + header to a temp, then `cat temp > results.tsv` (overwrite, not append). Hmm, `cat X > Y` works ✓.

So:
Message A: 7 Write calls (results_new.tsv, moves_lines.txt, n1.txt..n5.txt) + 1 Read (moves.md? not needed).
Message B: 7 Bash calls (cat results_new > results.tsv; cat moves_lines >> moves.md; cat nK >> notes.md ×5).

Then:
Message C: Write the log file + delete the dumps + a size check.

Let me go. Note: for the notes, I must be careful that the append doesn't duplicate. Fine.

Let me write the content now.
