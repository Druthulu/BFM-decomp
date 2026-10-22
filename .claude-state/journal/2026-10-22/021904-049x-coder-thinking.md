---
ts: 2026-10-22T08:19:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AvexVbV88g27HxxeLIK2
---
c3 (s16 c) → score 10 (the copies vanished). c4/c5 (split vars) → score 11 (worse).

Let me look at c4's diff to see what's happening (score 11 with 38 ins).

Hmm. Let me think differently.

The issue: the compare's operand must be the ORIGINAL (v0) while the copy is v1.

In x1 (the isolated harness), the compare read the original ✓ and the copy went to a1. So in isolation the shape works! The difference in the real function must be the register pressure/ordering.

In x1 the regs were: load→v1, copy→a1. In the real function: load→v0, copy→v1, and the compare read v1 (the copy).

Hmm! In x1, the copy went to a1 (a higher reg) and the compare read v1 (the load). In the real function, the copy got v1 and the compare read v1 → the compare read the COPY.

So in the real function gcc substituted; in x1 it didn't. Hmm, but the structures look the same...

OH WAIT. Maybe in the real function the substitution is in the other direction: maybe the load is in v0 and the copy in v1, and the compare reads... hmm, the compare MUST read the load's value (v). If gcc substituted v→c, the compare reads the copy's reg (v1).

Hmm, why would gcc substitute in the real function but not in x1?

Difference: the real function's SECOND arm. In the second arm, `v` is reloaded and `c` is redefined. cse's equivalence classes: after the second `c = tmp`, c is redefined. But the FIRST compare's use of v is before that.

Hmm, cse processes the whole function. The reg_equiv_content for `c`... The first `c = tmp` sets reg_equiv_content[c] = tmp. The second `c = tmp` overwrites it. The first compare (which comes before the second copy) — cse would use the equivalence in effect at that point.

Hmm, but the copy direction: cse rewrote the compare's `v` to `c` — that means c was canonical at that point.

Hmm, hmm. cse's canonicalization rule: in `make_regs_eqv`, after setting reg_equiv_content, gcc decides which reg is canonical based on the number of references and the live ranges:

gcc 2.7's cse.c make_regs_eqv (I'll reconstruct):
```c
      /* If we are setting a reg to a reg, and the reg is a pseudo-reg,
	 and the source is a pseudo-reg, ... */
      ...
      /* If the source reg is dead after this insn and the destination
	 reg is live, then we should reverse the copy: substitute the
	 destination for the source in the source's definition.  */
```
Hmm, the G02 note says exactly this: "iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg)".

So the rule: if the SOURCE (t) is dead after the copy and the DEST (iVar1) is live → reverse: rewrite t's uses to iVar1 → iVar1 becomes canonical.

In our case: the copy is `c = tmp` (not `c = v`!). The source is tmp, which is dead right after the copy. And the dest c is live. So the reverse applies: tmp's uses are rewritten to c. And tmp's uses = the copy's own use? Hmm, tmp's use is the copy itself.

Hmm, but v == tmp (the round trip). So gcc's equivalence class is {v, tmp, c}. When the copy `c = tmp` is processed, tmp is dead after → reverse → rewrite tmp's uses to c → and v's uses? v's uses include the compare (after the copy). Hmm, if v is also dead after the copy... v is NOT dead (it's used in the compare and reassigned later).

Hmm, so the equivalence class {v, tmp, c}: the reverse-copy rule fires for the (v → tmp) relation when tmp is dead → rewrite v's uses to tmp → then the (tmp → c) relation → rewrite tmp's uses to c → so v's uses (the compare) get rewritten to c! ✗ That's the substitution.

In 80182ED4: `t = load; tmp = (s16)t; u = tmp; if (t == 0)`. Same chain: t's uses → tmp → u. So the compare's t should be rewritten to u... but it wasn't!

Hmm, unless in 80182ED4 the reverse rule didn't fire because t is NOT dead after the copy (t is used in the compare — a use AFTER the copy!). Wait: the compare `if (t == 0)` comes AFTER the copy in the source. So t IS used after the copy → t is not dead → the reverse rule doesn't fire → t stays canonical ✓✓.

And in 8018302C, the compare `if (v >= 0x801)` ALSO comes after the copy... so v is used after the copy → not dead → the reverse shouldn't fire.

Hmm! So why the substitution?

Hmm, unless the equivalence direction is different. Hmm.

Hmm, let me look at the c4 diff (score 11) to see what's happening — maybe the split changed things.

Actually, let me try a more direct approach: let me EXPERIMENT with the harness to find a shape where the compare reads the original AND the copy survives, in the presence of the SECOND arm (which might be the trigger).

Let me build a harness test with two arms:
```c
int y1(short *p) { int v; int c; short tmp; v = *(short*)p; tmp = (short)v; c = tmp; if (v >= 0x801) { v = c - 0x200; *(short*)p = v; } v = *(short*)(p+1); tmp = (short)v; c = tmp; if (v >= 0x801) { v = c - 0x200; *(short*)(p+1) = v; } return v; }
```
Let me see if the compare reads the copy there.

Let me also try variants with the frame_pad / more pressure.

Let me run the harness with a few of these.
