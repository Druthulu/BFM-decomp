---
ts: 2026-10-22T06:09:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EBk5aMDMRPL4QeZn1h0B
---
No gcc source pointer. Let me check docs/ops for the toolchain. Actually, let me search within the project for a gcc source copy.

Actually, rather than dig for gcc source, let me think about the mechanism from the "how" angle using the project's own tools: `tools/cc1_dumps_tu.sh` + `tools/alloc_table.py` give cc1 dumps. But the relevant pass is reorg/sched2.

Alternative approach: think about what determines the delay-slot choice. Let me look at the difference between mine and the target once more, in terms of the RTL the compiler sees.

Actually! NEW IDEA. Look at the target's andi at cc4 — the jal's delay slot — and mine has the same. And the target's bne delay slot = sll. In mine, the bne delay slot = andi (a copy).

What if in the target, the andi was NEVER a candidate because the RTL order placed the sll immediately after the branch, and reorg copies the FIRST instruction after the branch? In mine, why is the andi chosen instead of the sll?

Hmm! Maybe because in mine, the sll is NOT immediately after the branch in the RTL: the RTL might be
```
bne a2,v0, L_join
<nothing in fallthrough>
L_join: sll a2,a2,8
```
and the search finds the sll. Hmm.

Let me try yet another approach: examine what happens with the delay slot if I make the argument mask NOT an andi. E.g., what if the argument is masked as `(u16)`? Then the compiler emits `andi a1,a1,0xffff` too. What if I write the mask as `& 0xFFFF` on a u16 variable? Same.

What if I could get the compiler to compute the mask with a different instruction? Not possible for a 16-bit mask.

What if the mask is applied to the *vol* term only? As discussed, semantically different in unreachable cases but the compiler can't tell... but wait, the compiler CAN'T prove vol ≥ 0, so it would emit different code (masking vol: andi a1,a1,0xffff then ori 0x3000 then or a2). The emitted instruction count is the same (one andi). The andi would then be earlier in the RTL (right after vol) and would be a candidate for the delay slot even more so. Hmm, but the target's andi is at the END (on the whole arg). So no.

Let's flip the question: what if the difference is in the *scheduling* of the `sll` relative to the branch? In the target, the sll is a separate instruction that got copied. In mine, the sll is at cb0, in the join. Same.

Hmm, hold on! Let me re-examine. In the target:
```
ca4: bne a2,v0,cb4    ; cb4 = li a0,2533
ca8: sll a2,a2,0x8
cac: li a2,15
cb0: sll a2,a2,0x8
cb4: li a0,2533
```
The fallthrough path: ca8 (sll, dead), cac (li a2,15), cb0 (sll) → cb4.
The branch path: ca8 (sll, live), → cb4.

Now here's the thing: in the target, the branch target cb4 SKIPS cb0. In mine, the branch target IS cb0.

For gcc to redirect the branch past cb0, it must know that the sll at cb0 is duplicated in the delay slot. This is the "reorg bypass" optimization.

Now, in mine, the delay slot has the andi. So the andi was chosen as the copy candidate.

Why would gcc prefer the andi (which is in a LATER block, the call group) over the sll (in the NEXT block, the join)? That's backwards from a "first candidate" search. Unless the sll was REJECTED as a candidate.

Why would the sll be rejected? Because it modifies a2, which the branch uses! In gcc's reorg.c, when filling a delay slot for a conditional branch, the candidate instruction must not modify a register that the branch reads — UNLESS the machine says the branch's operands are already latched. Hmm, but the target has it!

Unless... in the TARGET, the branch's condition register is NOT a2 in the RTL! I.e., in the target's RTL, the comparison was on a different pseudo (say `v1` or a temp), and the `sll` was on a2, and after register allocation they ended up as the same register $a2? No — a2 = the same value.

Hmm, wait. What if in the target's RTL, the comparison is `t == 16` where t is a pseudo that got allocated to a2, and the shift is on a DIFFERENT pseudo (also allocated to a2)? Then the sll (on the shift pseudo) doesn't modify the *comparison* pseudo, so gcc's check "doesn't modify a register used by the branch" passes! And in mine, the comparison and the shift are the SAME pseudo (a2), so the sll modifies the branch's operand → rejected → gcc picked the andi instead!

That's a very promising hypothesis! In C, that means the source used TWO variables for the quotient: one compared, one shifted.

E.g.:
```
s32 t = (sx + 0xA0) / 0x14;
if (t == 0x10) t = 0xF;
sx = t << 8;
```
Here the comparison is on t and the shift is on t too (same variable). Hmm, that's the same pseudo.

But:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
```
also the same.

What if:
```
s32 t;
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
t = sx;      /* copy */
sx = t << 8;
```
The copy would be coalesced by cse.

Hmm, but wait: how do we get the comparison on a different register than the shift while the value flows? The comparison result is used to select 0xF vs the value. The classic C:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) {
    sx = 0xF;
}
sx = sx << 8;
```

The RTL: compare sx==16 → branch. Then arm: sx = 15. Join: sll sx,8.

The branch's condition pseudo IS sx. So the sll modifies the branch's operand.

Unless gcc's check is about the *hard reg* usage at the RTL level: at RTL (pre-RA) everything is a pseudo, and the branch condition is a pseudo. gcc 2.7's reorg check for delay slot candidates:

In gcc 2.7 reorg.c, `reorg_fill_slots`:
```c
	  /* If this is a conditional branch, and the delay slot is empty,
	     then we may be able to fill it with an instruction from
	     the block that follows... */
```
and there's a function:

```c
/* Return true if we can move INSN into the delay slot of BRANCH.  */
static int
can_move_insn (rtx insn, rtx branch) ...
```

Hmm, in gcc 2.7 reorg.c there IS this (I'm now recalling the actual code):

```c
/* If we are filling a delay slot with an instruction, and the
   instruction modifies a register that the branch uses, we must
   ensure that the branch's operands are read before the delay slot
   instruction executes.  On machines like the MIPS this is true.  */
```

And in mips.c:
```c
/* Return 1 if the branch at BRANCH reads its operands before the
   delay slot instruction is executed.  */
```

OK, if MIPS says "the branch reads its operands before the delay slot executes", then the sll modifying a2 IS acceptable. So that's not the blocker.

Hmm. But then why?

Let me look at this from yet another angle: maybe the difference isn't the delay-slot choice but the *scheduling* of the andi. In mine, the andi (mask) is computed early — before the branch. Look at the final layout: the andi copy at ca8. But the "real" andi is at cc4 (jal delay). If the mask had been computed early (before the branch) in the RTL, then the jal delay slot wouldn't need it...

Ugh. Let me try to get empirical data on what makes the difference by trying more structural variants, especially:
(a) making the comparison use a different variable than the shift;
(b) changing the ORDER of the arg computation relative to the shift.

For (a): in C, how do we compare with one var and shift another? 

```
s32 q = (sx + 0xA0) / 0x14;
if (q == 0x10) { q = 0xF; }
sx = q << 8;
```
The compare is on q, the shift is on q. Same pseudo.

Hmm, but what if the shift's result goes to a different variable:
```
s32 q = (sx + 0xA0) / 0x14;
if (q == 0x10) { q = 0xF; }
sx = q << 8;
```
The shift reads q and writes sx. So the shift does NOT modify the branch's operand q! In the RTL, the branch compares q, and the sll is `sx = q << 8` — different destination pseudo! gcc's check "the candidate must not modify a register used by the branch" would PASS (it modifies sx, not q).

In my current code, `sx = sx << 8` modifies sx which IS the branch's operand → REJECTED.

That's exactly the hypothesis! And the C is natural:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
```
→ change to:
```
{ s32 q = (sx + 0xA0) / 0x14;
  if (q == 0x10) { q = 0xF; }
  sx = q << 8; }
```
Hmm, but that's exactly my s3 variant! ("temp for the quotient": `s32 t = (sx+0xA0)/0x14; if (t==0x10) t=0xF; sx = t << 8;`) which scored 5 (MIXED) — worse than 2. Hmm. But maybe cse coalesced t and sx, or the regalloc merged them. Let me look at what r_u16_s3 produced (5, MIXED) — a MIXED class means some register differences. Let me disassemble it to see if the delay slot changed.

Let me check the disassembly of r_u16_s3 and r_u16_s1 to see the delay slot content.

Let me do that now — compile with --keep and dump.

Actually, faster: let me write a small script that, for a given body file, compiles it and prints the region around the bne. I can use delever_search --try --keep then objdump.

Let me check s3 first.
