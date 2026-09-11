# func_8017F10C (ov_SC06_010_jr_8017A4AC.c) — T7 e14, P36 S104

**Score 0, ZERO levers** (free start 5 = regen best 5). Tree levers: 1 pin ($18 on `sid`) -> 0. No copies elsewhere
(`(d * 0x7F) / 0x900`, `D_80126B66 - t;` and `func_8002D4C8(sid & 0xFFFF` occur only in this TU).

The move (one declaration):
```
-    register s32 sid __asm__("$18");   /* or plain `s32 sid;` in body_free */
-    ...
-    sid = a1;
+    u16 sid = a1;
     ...
-                func_8002D4C8(sid & 0xFFFF, ...);
+                func_8002D4C8(sid, ...);
```
Readability tidies, each also 0 on bytes: the `snd` local deleted (`func_8004914C(&D_800AF648)` twice — cse merges the
two address loads into `$s0`, which is what the target has here, unlike d34's func_80181408), and the `flg` block written
as `(d | (0x3000 | x)) & 0xFFFF`. `u16 sid;` + `sid = a1;` at the old position also scores 0; the declaration
initialiser is the more natural spelling and is body.c.

## (a) The residual
Same 91 instructions; one ORDER defect in the prologue block: the parameter copy `move s2,a1` sat in the first free
load-delay slot (after `lw v0,76(v0)`), where the target has it last, right before `jal func_8004914C`.

## (b) The passes and decisions (read in the dumps under scratch/dumps_free, dumps_tree, dumps_v3)
1. **cse deletes the SImode copy `sid = a1`.** In the free body the `.rtl` has insn 6 `(set r73 a1)` (the parameter
   copy) and insn 37 `(set r74 r73)` (`sid = a1`); `.cse` has only insn 6 — the same-mode REG copy is folded
   (cse.c:7440-7474, METHOD S103 c4) and r73 itself becomes `sid`, living in `$s2`.
2. **sched1 never moves a parameter copy; sched2 puts it last by LUID.** `schedule_block` skips the leading
   `(set pseudo hard-reg)` insns of block 0 before reload (sched.c:3189-3212), so insn 6 stays at the top. In sched2
   (f.sched2, T-12..T-18) insn 6 (`move s2,a1`, priority 1) ties with `move a0,s0`, `lw`s and the `snd` load at the same
   priority and loses every tie on `INSN_LUID` (`rank_for_schedule`, sched.c:2425-2428) because it is the lowest-numbered
   insn: the reverse list scheduler takes it last, i.e. places it earliest.
3. **A HImode destination keeps the copy as its own insn.** With `u16 sid`, `.rtl` insn 13 is
   `(set (reg/v:HI 74) (subreg:HI (reg/v:SI 73) 0))`; combine folds the parameter copy into it (`.combine`: insn 6
   deleted, insn 13 = `(set (reg:HI 74) (reg:HI 5 a1))`), so the only `a1` read is now an ordinary insn after
   NOTE_INSN_FUNCTION_BEG. sched1 schedules it: it births a register with no REG_DEAD note in the list -> `adjust_priority`
   raises it to the block maximum (`birthing_insn_p`, sched.c:2469-2545; v3.sched shows `13 (7f000001)` at T-12) and it is
   launched directly before call 42 (`insn 13 37 42`). sched2 then sees it with a high LUID and keeps it there. The use
   `andi a0,s2,0xffff` is the zero-extension of the u16 argument, so `& 0xFFFF` in the source is redundant and dropped.
   Proven on bytes (v_u16 = body_free with only the width change: 5 -> 0; s16 instead: 5 — not dumped; presumably the
   sign extension at the use changes what combine keeps — unproven) and on dumps (dumps_v3: `.combine` insn 13, `.sched` placement).

The pin was faking (3): a hard-register destination is not a pseudo, so cse could not fold `sid = a1` either, and the
copy was scheduled at its source position.

## (c) The move that closed it
- `u16 sid = a1;` (the width the call's argument proves — the callee takes the id masked to 16 bits) and pass `sid`
  without the mask.

## (d) GENERATOR PROPOSAL
**R-param-copy-width**: when the residual is a lone `move sN,aK` (a parameter copy) scheduled EARLIER than the target
(same count, ORDER class, in the entry block), and the parameter's every use is masked/cast to 16 (or 8) bits, route
the parameter through a local of that width (`u16 v = aK;`, drop the mask at the uses): the narrow copy survives cse,
absorbs the parameter copy in combine and becomes a schedulable birthing insn (sched.c:3189-3212 exempts only the
parameter copy itself). Enumerate u16/s16/u8/s8 for each parameter that the residual's `move sN,aK` names.

## (e) What did not work (bytes)
- body_free (SImode `sid = a1` late): 5. `s16 sid`: 5.
- All R2–R38 families: best 5 (history.txt) — R6 inline sid, R10 param-alias, R9/R18 moves are all SImode; no family
  changes a local's WIDTH to a narrower type than its source.

## (f) Where the method fell short / what helped
- METHOD step 3 (S103 c4, "a copy deleted because two locals shared a WIDTH") was the answer, but its trigger is
  "MISSING moves / second andi"; here nothing is missing — the copy exists and is only MISPLACED, because cse's fold
  turned it into the unschedulable parameter copy. Worth a line: "a parameter copy scheduled too early = the copy was
  folded into the entry copy; give the local a narrower width".
- The `.sched`/`.sched2` ready-list traces settled it in one reading (the LUID tie at T-12..T-18), as step 12 said.
- The TU header over this function (lever 3, "pinning the carrier to $s2") now describes a lever that is gone; it should
  read "the carrier is a `u16` local (`u16 sid = a1;`), whose HImode copy survives cse and is scheduled before the call".

## (g) Structs
No. The decision is a scalar local's MODE (SImode copy folded by cse vs HImode SUBREG move kept), in the prologue
block, before any memory access is involved. Typing `a0` as an actor struct (`a0->parent->pos`, `a0->f0E`) or `L` as
an SVECTOR/DVECTOR pair does not touch the `sid` copy or the parameter-copy exemption; the `expr.c:4568-4577`
aggregate channel is not in play (the reordered insn is a register move). Not tested on bytes — the plain-C close
made it moot.
