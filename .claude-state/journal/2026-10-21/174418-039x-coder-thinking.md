---
ts: 2026-10-21T23:44:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YGihpEoKT3PHE3Xmz2Lv
---
Same. So gcc folds p1+4 back to the same expression (or the address pseudo is still shared).

Interesting: mine[5] = `addiu s0,sp,24` — so the address sp+24 is in s0. But p1 (= sp+16) didn't show up as a separate insn. So gcc folded p1 → the frame address and then p1+4 → sp+24, and CSE'd.

So gcc's cse DID unify p1+4 with sp10+4. Meaning simplify_rtx does the lookup_reg fold. Confirmed.

New approach: I need to defeat that fold. The fold is: (plus (reg p1)(const 8)) with p1's reg_equiv = (symbol_ref sp10) → (plus (symbol_ref sp10)(const 8)).

To defeat: make p1's reg_equiv NOT a symbol_ref but something that doesn't fold, yet still reloads to sp+16. Hmm, e.g. if p1's value is (plus (reg sp)(const 16))? That's what reload does. If the rtx is (plus (reg p1)(const 8)) and p1's reg_equiv = (plus (reg sp)(const 16)) then simplify gives (plus (reg sp)(const 24)) — a DIFFERENT rtx from (plus (symbol_ref sp10)(const 8))! And (plus (reg sp)(const 24)) reloads to `addiu a1,sp,24` ✓.

But when would p1's reg_equiv be (plus (reg sp)(const 16)) rather than (symbol_ref sp10)? If p1 is assigned from a pointer that is already in the frame-pointer form... e.g., if p1 is assigned from another pointer variable that has that form. Hmm, in RTL before reload, frame addresses are symbol_refs.

Hmm.

OK let me step back and think about the problem completely differently.

**What if we get rid of the need for a second computation by restructuring the two calls?**

Target:
```
3 addiu a0,sp,16
4 addiu a1,sp,24
5 li a2,1
...
12 jal func_800D20C0
...
14 jal func_800D23D0
15 addiu a0,sp,24
```

What if in our C the second call's argument is a pointer to a DIFFERENT array element that happens to be at sp+24 — i.e., we use a *different array* that overlaps? Not possible.

What if we change the array declaration so that the two pointers have different offsets but the same address? IMPOSSIBLE.

**What if the two calls are actually different in the C?** E.g., what if call2's argument in the ORIGINAL game code was `sp10 + 4` and call1's second arg was `sp10 + 4` — same.

Hmm.

**RADICAL: What if we change the FUNCTION SPELLING of one call so that the argument is passed differently?** E.g., the second call `func_800D23D0(sp10+4)` — what if we pass a *value* instead? No.

OK, let me now consider the possibility that this is a genuine WALL, and check the other items, which might be easier (the 6 items are all "launder"). Let me look at the other functions' targets — maybe some have a simpler launder (e.g. a launder that's clearly removable).

Actually, hold on! Let me reconsider the target once more:

```
3 addiu a0,sp,16     <- a0 = sp10
4 addiu a1,sp,24     <- a1 = sp10+4
```

What if the ORIGINAL source was:

```
u16 *p = sp10 + 4;
func_800D20C0(sp10, p, 1);
func_800D23D0(p);
```
and the original compiler allocated p to... hmm, the original compiler would have had to keep p somewhere. The target has no register. So the original compiler rematerialized.

Hmm, alternatively the original source:
```
func_800D20C0(sp10, &sp10[4], 1);
func_800D23D0(&sp10[4]);
```

OK whatever.

**IMPORTANT NEW THOUGHT**: What if we DON'T need the two addiu's to come from the same C expression, because the SECOND `addiu a0,sp,24` could come from a completely different C construct: e.g., a pointer to a *different* stack slot that is at sp+24? We established gcc won't place two objects at the same address.

BUT WAIT: what about the FRAME LAYOUT? What if the array is NOT at sp+16 in our C, but the *scalar* that we pass is? I.e., what if we declare the array differently so that the layout has the array at sp+16 and... no, gcc's layout is what it is.

Hmm, but here's a thought: what if we declare SIX separate u16 scalars w0..w5 (at sp+16,18,20,22,24,26 if gcc lays them out consecutively) and then:
- call1: func_800D20C0(&w0, &w4, 1) → a0 = &w0 → `addiu a0,sp,16`; a1 = &w4 → `addiu a1,sp,24`
- call2: func_800D23D0(&w4) → same rtx as a1's → cse unifies → ugh, same problem.

BUT!!! What if call2's arg is `&w4` and call1's second arg is `w2 + 2` or something? Same rtx.

The fundamental issue: two references to the same address → same rtx → cse unifies → one pseudo.

Hmm, so how did the ASM version avoid it? Because the asm's output is a hard register: cse can't create a pseudo for a hard reg. And the value in the hard reg is the address — computed by an addiu into that reg. So the target's `addiu a1,sp,24` IS the materialization for the asm's output register!! And the asm itself is a no-op (zero instructions) but it forces the value into a register.

OH. OH! I see it now! The asm `__asm__("" : "=r"(p1) : "0"(p1))` forces gcc to have the address in a REGISTER at that point. The register chosen would be a1 (since the next use is the call arg). So gcc computes `addiu a1,sp,24` and the asm is a no-op. Then the SECOND use of the address (for call2) is a separate expression → cse can't unify with the hard-reg value → another `addiu a0,sp,24`.

So the lever forces the value into a register at the use site. Without it, gcc's cse creates a shared pseudo.

**KEY REALIZATION**: to get `addiu a1,sp,24` (value directly in the arg register, no pseudo), we need the value to be USED ONCE (so no CSE pseudo is created) — OR the value to be in a hard register.

So: what if the two uses are NOT the same expression because one of them is derived from a *variable* whose value is a hard... no.

**What if the two uses have different RTL because one is `&w4` (symbol_ref) and the other is `w4_array + 4`?** We need two objects at the same address. IMPOSSIBLE in C...

...UNLESS! The second "object" is not a local but the SAME local accessed through a *different pointer type with a different offset base*, e.g.:

```
u16 sp10[6];
...
func_800D20C0(sp10, &sp10[4], 1);      // (plus (symbol_ref sp10)(const 8))
func_800D23D0((u16 *)((u8 *)sp10 + 8)); // (plus (symbol_ref sp10)(const 8))
```
Same.

What about using a **struct with a nested array**:
```
struct { u16 x[4]; u16 y[2]; } s;
func_800D20C0(&s.x[0], &s.y[0], 1);   // (plus (symbol_ref s)(const 0)) and (plus (symbol_ref s)(const 8))
func_800D23D0(&s.y[0]);                 // (plus (symbol_ref s)(const 8)) -- same as a1!
```
Still same.

Hmm, so within one object, same offset → same rtx.

**The only escape: the two uses must have different base symbols.** Two distinct objects at the same address is impossible... but what about a global?! A global has a fixed address; a local is on the stack. Different.

Hmm, what about the possibility of the compiler placing a local at a *known* address matching another? no.

OK OK OK. Let me flip to: **maybe the fix is to make the first call's SECOND argument a non-address!** Look at the target: `addiu a1,sp,24`. What if our C's first call has args (sp10, sp10+4, 1) — the second arg is a pointer. Yes.

**What if the first call's second argument is passed as a *different* kind of value that gcc materializes as addiu a1,sp,24 — e.g. an array-to-pointer decay of a 1-element array at sp+24?** Same address.

Alright. Let me try the completely different tack: maybe the answer involves the *second* call's argument being `sp10 + 4` while the first call's is `p1` where p1 is a pointer variable **that is never used again** — i.e., a one-shot copy. We tested c1 (p1 used twice) and t5 (p1 = sp10).

Let me test: p1 = sp10 + 4 used ONLY in call1, and call2 uses sp10 + 4:
```
p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
func_800D23D0(sp10 + 4);
```
This is c1-like but with p1 used once. Since p1's value = the address, and it's used once, gcc would substitute it → same rtx → unified with the second use. Probably 29. Cheap to test? Meh.

Hmm, what if p1 is used once AND is assigned in a way that yields a *distinct* rtx: p1 = sp10 + 4 where the "+4" is done via a char pointer: p1 = (u16 *)((u8 *)sp10 + 8) → same rtx.

I keep concluding the same.

*** COMPLETELY NEW ANGLE ***

What if we exploit the fact that gcc's cse does NOT unify expressions across a call when the expression is "cheap" and gcc decides to rematerialize? Specifically, cse.c has this (I'm now fairly confident):

```c
	      /* If this is a constant, ... */
	      ...
	  /* Don't try to CSE an expression that is a "simple" arithmetic
	     operation on a register, if the register is a "cheap" one... */
```

Hmm, actually here's a REAL rule I remember from cse.c:

```c
	  /* If the expression is a REG, ... */
	  ...
      /* If we are processing a tablejump, ... */
```
and
```c
	  /* If this is a load, ... */
```

I also remember cse.c's `record_cse`:
```c
	  if (n == 0)
	    {
	      ...
	      /* If we have a plus of a reg and a constant, and the reg is
		 the frame pointer, we can use an addiu... */
```

Hmm, no.

BUT there IS a known gcc behavior: **gcc does not create a CSE pseudo for an expression whose value is in a register that will die immediately** — actually cse always creates a pseudo.

Hmm, EXCEPT: cse.c has a special case for "reg + const" where the base reg is the FRAME POINTER! In `record_cse`:
```c
	      /* If this is a plus of a reg and a constant, and the reg is
		 the frame pointer, then the value is a constant address and
		 we can just record it... */
```
I don't remember.

Let me try an entirely different practical approach: **use the delever_search R-rule sweep**. The brief mentions "R3.40-013 helpers" and the completed item's notes mention "delever R2/R3/R4/R6/R9/R12/R27 sweep over the lever-free body". So delever_search has a built-in move catalog (R1..R40) that can sweep a body and try many variations automatically! That could crack this.

How do I run a sweep? The tool has --plan/--run/--try/--explain etc. The R-rules are probably applied in a "run" mode over the bank. Let me look for the R catalog in the tool. Let me grep delever_search.py for "R2" or "moves".

Let me check its size and look for the catalog.
