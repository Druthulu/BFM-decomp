---
ts: 2026-11-06T01:34:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TrsnGNTKeOYQ9DNTbHXm
---
Let me look at the cookbook entry C0535 mentioned in MOVES+ and also search for real-C cross-jump defeat. Actually maybe there's a specific technique: "store in the delay slot differs" etc.

Rather than research forever, let me start experimenting. Time budget 20-30 min per item; 5 items. Let me be efficient.

Experiment plan for item 1:
Variants (each a body file, score with sc.sh):
a) t = 0x1D; unk1C = t;   (temp)
b) unk1C = 0x1D; via do-while: do { unk1C = 0x1D; } while (0);
c) reorder: sh zero,244 after sw? (expect wrong)
d) use `r = 0x1D; unk1C = r;` where r used elsewhere? 
e) dec via do-while.
f) Make zero's store through `t` and ALSO make the store not the tail: append a dead statement? no.

Actually think again about rtx_renumbered_equal_p. Let me find gcc 2.7.2 source online from memory... In jump.c 2.7.2:

```
/* Return 1 if X and Y are identical-looking rtx's, except for
   register numbers, which are compared using reg_renumber.
   ... */
static int
rtx_renumbered_equal_p (x, y)
```

I recall in 2.7.2 jump.c there is:
```
static int
rtx_renumbered_equal_p (x, y)
     rtx x, y;
{
  register int i;
  register enum rtx_code code = GET_CODE (x);

  if (code != GET_CODE (y))
    return 0;

  switch (code)
    {
    case REG:
      /* Two registers are equal if they have the same register number,
	 or if one is a pseudo and the other is a hard register and
	 the pseudo is allocated to that hard register.  */
      return (REGNO (x) == REGNO (y)
	      || (reg_renumber[REGNO (x)] >= 0
		  && reg_renumber[REGNO (x)] == REGNO (y))
	      || (reg_renumber[REGNO (y)] >= 0
		  && reg_renumber[REGNO (y)] == REGNO (x)));
```
That's BEFORE allocation, so reg_renumber is -1, so two different pseudos are NOT equal! Then how did the merge happen? Because the store's value register... hmm.

Wait, maybe the two stores genuinely use the same pseudo. How? In zero: `unk1C = 0x1D` where unk1C is `s32` member. The RTL: (set (mem (plus (reg s0) 28)) (const_int 29))? If MIPS movsi for constant to memory is a single insn pattern? On MIPS, `movsi` with const_int to mem isn't valid; the expander emits `li` + store. Actually the MIPS md has movsi expanding const to reg via gen_move_insn; for memory dest, it might use `(set (mem) (const_int))` and let reload? No—expand_expr for a store of a constant calls emit_move_insn which for MIPS produces (set (reg pseudo) (const)) then (set (mem) (reg pseudo)).

Hmm. But maybe the two stores share a pseudo because of cse's register equivalence: cse assigns the same "qty" for the value 29? No, the value differs (29 vs unk1C-1).

Wait, actually the merged instruction in the target-like comparison: mine has j 1800 where 1800 is `sw v0,28(s0)`, and the *zero* block's sw is at 1800. dec jumps there. But dec's store is `sw v0,28(s0)` where v0 came from addiu. After cross-jump, dec's block lost its own store. The pseudo in dec's store is the same pseudo as the addiu dest (loaded value). Zero's store pseudo is the li dest. Different pseudos. So rtx_renumbered_equal_p must allow renaming after all.

Let me just find gcc 2.7.2 jump.c source text. Maybe pip has it? Or maybe the repo has a reference copy: docs mention `tools/reference/gcc-2.7.2/jump.c`. Check.
