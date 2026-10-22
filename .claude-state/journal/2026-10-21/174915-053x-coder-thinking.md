---
ts: 2026-10-21T23:49:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_V2hxlW8MxR2GMGH8lq6X
---
Let me try the retriever for the gcc 2.7 rule — actually the retriever is a code lookup tool; the gcc source may not be in the repo. Let me instead use the dumps: the .lreg dump for the function shows local-alloc's decisions. Let me look at what it says about c and d.

Actually, better idea: let me EXPERIMENT rather than theorize. I'll write several variants and check the register allocation via the score diff's "register pairs" line.

Let me set up an efficient loop: write variant files, then run sweep.py score on all of them (each ~1-2s).

Variants to try:
V2: `s32 a = param_2;` init at decl; `s32 b = (s16)param_1;` etc. — probably same.
V3: declare in order c,d,a,b,e.
V4: split e into e1/e2.
V5: use `u8` for e? e = 291B4(d)&0xFF → could be u8. Then e's refs change.
V6: reorder statements.

Hmm, let me think about which is most likely to work.

KEY REALIZATION attempt: Let me reconsider what determines "local" vs "global" in gcc 2.7. I'm now recalling gcc 2.7's local.c `allocate_local_regions`:

```c
static int
allocate_local_regions (max_reg, max_reg_num, reg_last_freq)
{
  ...
  for (reg = 0; reg < max_reg; reg++)
    if (reg != REG_FRAME_POINTER && reg != FRAME_POINTER)
      for (reg2 = 0; reg2 < FIRST_PSEUDO_REGISTER; reg2++)
	if (reg != reg2
	    && regs_ever_live[reg]
	    && ! regs_ever_live[reg2])
	  {
	    ...
	    /* Make a reg2 entry for this reg.  */
	    ...
	    /* If the reg is live across a call, ... */
```
Hmm.

Actually here's the gcc 2.7 code I remember more concretely (local.c):

```c
	  /* Now allocate a register for each local variable.  */
	  ...
	  /* If the local register is live across a call, it must be
	     allocated to a callee-saved register... */
```

and importantly:
```c
	      /* Don't use a register that is live across a call if the
		 variable is set more than once (that would require
		 the register to be saved around each set).  */
```

Hmm, I actually DO now recall something like this in gcc 2.7's local.c:

```c
	    /* If the variable is set more than once and is live across
	       a call, we can't allocate it to a local register, since
	       the register would have to be saved and restored around
	       each set... */
```

Hmm, no. Actually in gcc 2.7, `allocate_local_regions` has:

```c
	  /* We should not allocate a register to a variable that is
	     live across a call and has more than one set, ... */
```

I'll test empirically. But how do I make a multi-set local without changing the code? 

Hmm, actually here's the thing: even if I could, making c,d multi-set would change the "crosses calls" analysis.

DIFFERENT STRATEGY — let me reconsider the problem from the "what did the original source look like" angle. The target was compiled by the ORIGINAL game source (with $16/$17 pins presumably, since this is a pin item marked "NEEDED DIFFERS"). Hmm, actually the pin site says "!FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)". So the pins in the current src are FAKE and the real source did NOT have them; the pin was added to make the code match. The task is to find the real source without the pin.

So the real source produced a=s0,b=s1,c=s2,d=s3,e=s4 WITHOUT pins. How?!

Since local-alloc gives locals the lowest free regs, c,d (locals) would get $16,$17 unless the globals a,b got them first. Which happens if global-alloc runs BEFORE local-alloc... 

OR if c,d are NOT locals in the real source! Maybe in the real source, c and d were declared differently — e.g. as globals? No.

OR: maybe in the real source, c and d had MULTIPLE sets, making them globals!

Interesting! E.g., if the real source was:
```c
d = b + 0x2F;
...
c = a + 0x2F;
```
Hmm.

Wait — maybe the real source used different variables such that a,b,c,d,e were ALL globals and the priority order was a,b,c,d,e.

Let's test that hypothesis numerically: if all 5 are globals with the priorities I computed (a=5000, b=4615, c=4285, d=3000, e=3636), the order would be a,b,c,e,d → a=$16,b=$17,c=$18,e=$19,d=$20. Target has d=$19,e=$20.

So the real source must have had different refs/live for d and e. 

What if `e` had a LONGER live range (live > 26.67 → pri < 3000)? e's live is 22. If e were live 28+, pri(e) = 2*4/28*1e4 = 2857 < d's 3000 ✓.

How to make e's live longer? e = 291B4(d) & 0xFF is set at insn 19 and used at 30 (move a1,s4). If e were set EARLIER... e depends on d which is set at 13. Hmm, e's live is already from 19 to 30.

What if the SECOND e (e = 291DC(b)) were kept in a different variable so e's live extends? Hmm.

Alternatively make d's live SHORTER (≤8 → pri 3750 > e's 3636). d live 10 → 8. d's live: from `addu $17,$19,47` (insn 13) to `move $4,$17` (insn 25). If the assignment of d were moved later... d is used at insn 14 (move a0,s1 for the first call). So d's live starts at 13 and ends at 25 = 13 insns; measured 10.

Hmm, what if d's assignment were moved to just before its first use? It already is.

Hmm, what if the FIRST call were moved later? The statement order:
```
a = param_2;
b = (s16)param_1;
d = b + 0x2F;
e = func_800291B4(d) & 0xFF;
a = (s16)a;
c = a + 0x2F;
func_800291A0(d, func_800291B4(c) & 0xFF);
func_800291A0(c, e);
...
```
The target's instruction order matches this.

OK so d's live is 10 and e's is 22 with refs 3 and 4. pri(d)=3000, pri(e)=3636.

For d > e, I need d's pri up or e's down.

Hmm, what if e had only 3 refs? e's 4 refs: set, use, set, use. What if the second `e = func_800291DC(b)` were written to reuse a different variable and the final use `func_800291C8(a, (s16)e)` used that variable? Then we'd have e (2 refs: set+use) and e2 (2 refs: set+use) — two variables. But then e2 would be a separate register → mismatch with the target (both in $20).

Hmm, unless e2's live range doesn't overlap e's and local-alloc gives them the same reg. But e2 would be single-set → local; e (first value) single-set → local. Both local → local-alloc gives them $16,$17 (or the same reg if non-overlapping!). Hmm, if they don't overlap, local-alloc can give both $16. But then the prologue would save $16 once... but they'd both need saving. Hmm, actually if they share the reg, the save/restore is once.

But the target has e in $20, and $20 is the LAST callee-saved reg. With locals c,d,e1,e2 → $16,$17 and (e1,e2 sharing) hmm.

This is getting really complicated. Let me consider that this item may be a WALL, and move on to other items, then come back if time permits.

Actually wait. Let me reconsider ONE more idea, which I think is promising:

What if the number of locals changes such that local-alloc's assignment order shifts? Specifically: local-alloc assigns regs to locals in the order of the "local reg" list, but WHICH locals get which reg depends on `local_size` ordering.

Actually here's the thing I keep coming back to: in the TARGET, c→$18 and d→$19. If c,d were globals with the right priorities, global-alloc would give them $18,$19 given a→$16,b→$17 pinned... 

Hmm! In the target, a and b are PINNED to $16/$17 — pinned hard regs are excluded from local-alloc's pool. So c,d (locals) get $18,$19.

For the natural version, if a and b are globals WITHOUT hard-reg preferences, local-alloc gives c,d $16,$17.

⇒ The real source must have had a,b as LOCALS too, or c,d as globals.

If a,b were locals: a is multi-set. Hmm, unless the criterion for global isn't multi-set.

You know what? Let me just TEST the criterion. Quick experiment: take the current candidate and make `d` multi-set in a code-neutral way, then see if d becomes global (i.e., appears in the "N regs to allocate" list).

Code-neutral multi-set for d: 
```c
d = b + 0x2F;
d = d;        /* identity → forbidden & folded */
```
Hmm.

What about making c multi-set via:
```c
c = a + 0x2F;
...
c = c + 0;    
```
folded.

Hmm. What if I write `d = b + 0x2F;` and later `d = b + 0x2F;` again (recompute)? CSE would merge them (same expression) → 1 set.

What if I write it as `d = b + 0x2F;` and later `d = (s16)b + 0x2F;`? That's a different expression → 2 sets, 2 addiu instructions → code mismatch. Unless gcc CSEs it (b+0x2F vs (s16)b+0x2F — the (s16)b is the same value as b? b IS (s16)param_1, so (s16)b == b in value but gcc doesn't know that without value-range propagation; gcc 2.7 does have VRP? No.).

OK, let me try yet another approach: EMPIRICALLY test whether "multi-set" is the criterion, using `a`: if I make `a` single-set... impossible.

Hmm, hold on! What about the reverse experiment: make `c` multi-set by using a DIFFERENT but equivalent formulation that gcc folds to the same code:
```c
c = a + 0x2F;
```
vs
```c
c = a + 47;
```
same.

What about:
```c
c = a + 0x2F;
c = c + 0x2F - 0x2F;  
```
→ gcc folds to c = c → 1 set.

Hmm.

OK, let me try the "e split" experiment to learn the rule, and also try the "declaration order" experiment, etc. Let me be time-efficient: write ~8 variants, score them all, and look at the register pairs.

Actually, hold on. Let me reconsider the problem completely differently!

What if the real source didn't have variables c and d at all, but the target's $18/$19 are just temporaries? Let's re-look:

```
addiu s3,s1,47     <- d
move a0,s3
...
addiu s2,s0,47     <- c
move a0,s2
move a0,s3
jal 291A0
```
So d is computed into $19 (s3) and used later at `move a0,s3` for the call 291A0(d, ...). And c into $18.

If d weren't a variable, the compiler would compute `addiu a0,s1,47` right before the call — but the target has it early (before the first call) and keeps it in $19. So d IS a variable.

Fine.

NEW IDEA: What if the real source used MORE variables (e.g., separate temps) such that the local set is bigger? E.g. what if the real source was:

```c
void func_801415C0(s32 param_1, s32 param_2) {
    s32 a = param_2;
    s32 b = (s16)param_1;
    s32 d = b + 0x2F;
    s32 e = func_800291B4(d) & 0xFF;
    a = (s16)a;
    s32 c = a + 0x2F;
    ...
}
```
Same.

Hmm, let me try to think about what the local-alloc does with 3+ locals. 

Hmm, hmm. Actually, WAIT A MOMENT. What if local-alloc assigns $16,$17 to c,d because they're the locals — but what if the ORIGINAL source had a,b,c,d,e ALL as locals because the original function had a different structure? For instance, what if the original used `s16` types so that a,b weren't multi-set?

Look: `b = (s16)param_1;` — the (s16) cast creates a separate pseudo for the sign-extended value! In gcc, `(s16)param_1` produces a new pseudo (HImode→SIMode) — so b is a NEW pseudo with 1 set at that point, and then `b = b * 2 + 0x14` is a SECOND set. So b is multi-set.

Hmm, unless gcc's "combine" turns `(s16)param_1` into a shift of param_1 and then the sext pseudo IS param_1's pseudo → b = param_1 in place → then b has 1 set (the copy) + 1 set (b*2+0x14) = 2 sets. Still multi.

Hmm what if b's second use were inlined: `func_800291C8(b * 2 + 0x14, ...)` — then b would have 1 set... but the target has `sll s1,s1,0x1; addiu s1,s1,20` — that's b*2+0x14 computed in $17, which is b's register. If b*2+0x14 were inlined as an expression, gcc would compute it into a temp (v0) → `sll v0,s1,1; addiu v0,v0,20; move a0,v0` — 3 instructions instead of 2. ✗

So b must be a variable with the update in place.

OK. I'm now fairly convinced this item is hard. Let me look at the OTHER items first (6 remaining), then come back. Time check: I've used maybe 40 minutes on item 1. The brief says 20-30 min per item. Let me move on.

Actually, let me do a couple of quick cheap experiments first (5 min), since the machinery is set up.

Experiment set:
- c2: declaration order changed (c,d first).
- c3: `s32 a = param_2;` init at decl; and `b` init at decl.
- c4: e split into e1/e2 (learn the local/global rule).
- c5: statements reordered so that d is computed later.

Let me write these and score them.

Actually, the most informative single experiment: c4 (e split) — tells me whether single-set multi-call vars are locals. But actually I already know: c,d are single-set and local. The question is whether MULTI-set is what makes a,b,e global. Let me instead test: make `c` multi-set somehow.

Hmm, here's a code-neutral way to give c a second set: assign c from a DIFFERENT but equal expression... 

OR: change the ORDER so that c is assigned twice with the same value:
```c
c = a + 0x2F;
...
c = a + 0x2F;   /* recomputed */
```
gcc's CSE would likely merge the two identical expressions into one (cse does PRE). Then c has 1 set. But if cse doesn't merge (because the first is used in a call?), c would have 2 sets AND 2 addiu instructions. The target has 1 addiu. So ✗.

OK, alternative: test whether local-alloc's reg choice for c,d can be shifted by adding a THIRD local that overlaps them. Let me construct: a local `t` that is live across a call and single-set, overlapping c's range, but generates NO extra code. Hmm, hard.

What about `t` being a variable that gcc keeps in a register across a call but stores nowhere — e.g. `t = some_call_result;` where the call's result is used later. E.g.:

```c
s32 t = func_800291B4(c) & 0xFF;   // hmm this is the 2nd call's result
func_800291A0(d, t);
```
But the target computes `andi a1,v0,0xff` directly as the argument (no separate t). If t were a variable, gcc would compute it into a register and then copy to a1 — the target has `andi a1,v0,0xff` (directly into a1). Hmm, if t is a local live across a call, it'd be in a callee-saved reg → `andi t,v0,0xff; move a1,t` = extra instruction ✗.

Hmm, but WAIT: what if t is live across a call but the call is AFTER its last use? Then t doesn't need a callee-saved reg.

OK, let me think about the local-alloc reg choice order once more. In gcc 2.7's local.c `allocate_local_regions`, the locals are processed and for each, `find_reg` picks the best register based on:
- the "local size" (number of regs needed)
- `reg_last_freq` — prefers registers whose last use is infrequent?

Hmm.

You know what — let me try the simplest possible experiment that could crack this: change the ORDER of the local-alloc-relevant structure by declaring c and d with `s16`/`u16` types, or by moving d's computation.

Let me just write 6 variants and run them. Empiricism.

Let me write them now. I'll write a python script that writes the variant files (avoiding many Write calls).

Actually, Write calls are cheap-ish. But a script is better. Let me write a generator script with all variants as strings.

Let me do it.
