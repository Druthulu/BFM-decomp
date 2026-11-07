---
ts: 2026-11-06T01:33:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eCiMhHv03vb4uzKDbPCc
---
No source. But the notes cite jump.c:2440 SYMBOL_REF name string pointer compare. Let me recall gcc 2.7.2 jump.c rtx_renumbered_equal_p:

```
/* Return 1 if X and Y are identical-looking rtx's.
   ... 
   REGs are compared by their reg numbers if ... else by their "renumbered" ...
*/
static int
rtx_renumbered_equal_p (x, y, reg_map)
```

Actually in 2.7.2:
```
static int
rtx_renumbered_equal_p (x, y)
     rtx x, y;
{
  int i;
  enum rtx_code code = GET_CODE (x);

  if (code != GET_CODE (y))
    return 0;

  if (code == REG)
    {
      /* Two registers are equal if they have the same number or if
	 one is a pseudo-register and the other is a hard register
	 that it has been assigned to ... */
      return (REGNO (x) == REGNO (y)
	      || (reg_renumber[REGNO(x)] >= 0 && ...));
```
Hmm, not sure about renaming. The line-240 note said "jump2 cross-jump renames regs so const-vs-var stores do not differ" meaning it does allow renaming. Let me check the actual gcc source from memory: jump.c has `rtx_renumbered_equal_p` with a static `reg_map`? In 2.7.2, I believe:

```
/* Return nonzero if X and Y are identical-looking rtx's, considering
   registers equal if they are both regs and their REGNO are equal
   modulo the renumbering...  */
static int
rtx_renumbered_equal_p (x, y)
```

I recall it has:
```
  if (code == REG)
    {
      if (x == y) return 1;
      /* Compare the reg numbers, but allow a pseudo to match a hard reg
         if renumbered... */
```

Let's just experiment. Fastest path: try candidate moves and score.

Key insight from the notes: the way people defeat cross-jump is by making the two tails *structurally* different:
1. Different symbol string (for SYMBOL_REF).
2. Different polarity of preceding branch.
3. Different instruction count (e.g., gas-macro folded form two insns vs one).

For our store, the operands are (mem (plus reg const)) and (reg). rtx_renumbered_equal_p compares constants exactly. Both offsets 28. Both base regs renameable. Both value regs renameable.

Idea: make zero's store address use a different constant *offset* that folds to 28? No.

Idea: make zero's store source a *hard* register while dec's is a pseudo → renumbered_equal_p may only match pseudo-hard if assigned... at jump2 time, hard regs are e.g. the frame pointer, stack pointer. If zero's value came from a call return (v0 hard?) — no, call returns are hard regs at RTL! Wait: in zero, the store value 0x1D is a constant → li pseudo. In dec, the value is loaded from memory → pseudo.

Hmm what if in zero we get the constant via a function call? No, target has li.

Alternative: reorder zero so that the sw is followed by another instruction that dec lacks, and the sw is not the tail. But target order is fixed: li, sh, sw, then epilogue. The only way the sw isn't the tail is if something after it... there is nothing.

Hmm wait — actually, does find_cross_jump match the *last* insns of each block, requiring the matched region to end at the block end? Yes, it compares backwards from the jump/target. The target label is the epilogue .L; the block before it is zero's block. dec's block ends with j .L. It compares dec's insns before the j with zero's insns before the label. The last before j is sw; last before label is sw. Match, continue backwards: dec has addiu v0,-1; zero has sh zero,244 → differ. Stop. Match length 1.

minimum=1 because one side falls through. So to block: make the two `sw` not equal.

What if the zero store uses a *different register mode*: e.g. store the constant as s16? No, unk1C is s32.

What if the store in zero is `((Unk*)a0)->unk1C = t;` where t is a *local s32* that is set earlier and used elsewhere? Then cse... The RTL would be (set mem (reg t_pseudo)) and dec's (set mem (reg v_pseudo)). rtx_renumbered_equal_p would match these under renaming (if renaming allowed). The note says renaming allowed. But maybe renumbering only applies when both are pseudos in the *same* block? Hmm.

Actually, let me reconsider: in the target, why did the original compiler NOT merge them? The original C source produced target. So there IS a real-C shape that prevents the merge. The target dec block has `nop` at 17c0 (delay slot of j? no—target dec: 17bc lw; 17c0 nop; 17c4 addiu; 17c8 j; 17cc sw). Wait the target dec's j delay slot has sw. The nop at 17c0 is the load-delay slot for lw.

So target was produced by some C that prevented the merge. What C? The barrier comment says the current src needs the barrier because without it the merge happens. So the reconstructor didn't find the C. Our job to find it.

Possibility: the two stores differ because in the real source, dec's store is through a different expression that the compiler keeps in a different pseudo AND the renaming check fails because... Let me look at rtx_renumbered_equal_p for real. Maybe I can find gcc 2.7.2 source in pip/cache? Search project for "rtx_renumbered_equal_p".
