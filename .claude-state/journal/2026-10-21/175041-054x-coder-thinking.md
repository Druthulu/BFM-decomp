---
ts: 2026-10-21T23:50:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PigOSHs8IgYhL2k5jORJ
---
c3 has a parse error — because the header body is spliced into the header file and `s32 c = a + 0x2F;` after statements is C89-invalid (declaration after statement). Right! The header is compiled as C89. So no init-at-decl after statements. But init at decl at the TOP is fine (c3's error was at line 13 = `s32 c = a + 0x2F;` — a declaration after statements). Let me fix c3 to only init at decl for the first ones.

Hmm, but actually more importantly: the header file is spliced into the real header src/shared/ov/func_801415C0.h which has `void func_801415C0(s32 param_1, s32 param_2) {` — my body replaces it. C89 → declarations must come first.

OK, c1, c2, c5 all score 40. c4 (e split) 45, c6 (u8 e) 45.

I need the register-pair feedback. Let me get the diff for c2/c5 to see if the register assignment changed at all.

Actually, all score 40 = same as c1, so the allocation is unchanged.

Let me now think differently and consider that maybe the local-alloc assigns $16,$17 to c,d because of the ORDER in which locals are processed, and the ORIGINAL source might have had MORE locals so that c,d fall later.

Hmm, what if the original source had a local for the `(s16)` cast values? E.g.:

```c
s16 t = (s16)param_1;   /* hmm */
```

Let's think about what would make c and d land in $18/$19 while a,b,e take $16,$17,$20 — as LOCALS? No: a,b,e are globals.

OK so globals must get $16,$17,$20 and locals $18,$19. Global-alloc gives a,b,e $16,$17,$20 — skipping $18,$19?! That's impossible unless $18,$19 are taken by locals.

⇒ local-alloc MUST give c,d $18,$19. So local-alloc must skip $16,$17. Local-alloc skips regs that are hard-reg preferences of globals.

⇒ The globals a and b must have hard-reg preferences $16 and $17 — which is exactly the pin. Without a pin, how?

Hmm! What if a and b are preferred to specific hard regs for another reason? In gcc 2.7, hard reg preferences come from:
1. register asm vars (the pin).
2. **A call to a function whose address is taken**? no.
3. **A global variable with a fixed register**? no.
4. **The function's own "hard reg" usage**: if the function contains an asm with register constraints, the clobbered regs are excluded.
5. **A "global register variable"** in the TU.

Hmm, #5! If the TU has a global register variable declared (e.g., `register s32 x __asm__("$16")` at file scope), that would pin $16. But that's a lever (pin) and also not present.

Hmm.

OK. What about the possibility that local-alloc skips $16,$17 because they're "used" by something else in the function — e.g. the incoming parameters? No, params come in a0/a1.

Hmm, what about this: local-alloc processes locals and assigns the FIRST local to the LAST register? Let's check: in my candidate c→$16, d→$17. If sorted by something, c first.

What if I add a 3rd local that takes $16 (allocated first), and c,d take $17,$18 → then e (global) takes $19, a→$20, b→$21? That doesn't match either (target: a=$16,b=$17,c=$18,d=$19,e=$20).

Hmm, but wait: if there were extra locals taking $16 and $17, then globals a,b,e would get $18,$19,$20 → a=$18,b=$19,e=$20. Target wants a=$16. ✗.

So the only consistent story: locals c,d get $18,$19 and globals a,b,e get $16,$17,$20.

For globals to get $16,$17, they must be allocated before locals. In gcc 2.7, is it possible that global-alloc runs BEFORE local-alloc? Let's check the evidence: my candidate has locals c,d at $16,$17 and globals a,b,e at $18,$19,$20. If global-alloc ran first, globals would take $16,$17,$18.

Hmm, unless global-alloc's reg choice for globals prefers regs NOT used by locals, and local-alloc ran first (assigning c→$16,d→$17), so globals got $18+.

So local-alloc first. Confirmed.

⇒ In the target, local-alloc had $16,$17 unavailable.

Hmm, hold on!! What if in the target, local-alloc assigned $16,$17 to... the pin? YES: the pins are hard-reg preferences, and gcc's local-alloc knows the globals' hard reg preferences (from the .greg dump "preferences"). In gcc 2.7, `allocate_local_regions` avoids regs that are "preferred" by global allocnos. Actually, gcc 2.7's local.c:

```c
	  /* Now, allocate a register for each local variable.  */
	  ...
	  /* Don't allocate a register that is a hard reg preference of some
	     global allocno ... */
```
Hmm, hmm. There IS something in gcc 2.7: `local.c: allocate_local_regions` uses `hard_reg_preferences`? 

Hmm, actually I remember: gcc 2.7's local.c has:

```c
/* Return true if we should avoid allocating REGNO as a local register... */
```
and `global.c` has `hard_reg_preferences` computed in `global_alloc` via `find_reg`... but that's AFTER local-alloc.

Hmm, BUT: gcc 2.7 has a pass BEFORE local-alloc: in final.c, there's

```c
      /* Find the register preferences... */
      if (flag_pic ...) 
```
Hmm.

WAIT. Actually — gcc 2.7's local.c `allocate_local_regions` computes:
```c
  /* Find the registers that are not used by the globals. */
```
Hmm.

OK, let me look at it from the gcc 2.7 source. Let me try to find the source. The gcc-2.7.2-psx build is in tools/bin. Maybe there's a source tarball or the source is in the repo under a vendor dir. Let me search.

Actually, I could search the web knowledge: gcc 2.7.2 local.c `allocate_local_regions`:

```c
static int
allocate_local_regions (max_reg, max_reg_num, reg_last_freq)
{
  int i, j, k, m, reg, pass, reg2;
  int conflict;
  struct allocno *a;
  struct allocno *a2;
  int *local_size;
  ...
  for (i = 0; i < local_max_reg; i++)
    local_set[i] = 0;
  ...
  /* Now, we have to check to see if any of the local registers are
     live across a call... */
```
I honestly don't remember.

PRAGMATIC DECISION: This item has consumed ~50 min. The brief says 20-30 min per item; I'm over. But before giving up, let me consider the possibility that a much simpler source shape produces the target.

Let me think about what source would make gcc put c→$18, d→$19, a→$16, b→$17, e→$20 naturally.

Since a,b,e are globals and c,d locals, and local-alloc gives locals the low regs... For locals to get $18,$19, the locals must be allocated AFTER something else takes $16,$17. What if there are MORE locals? Then some local takes $16,$17 and c,d take $18,$19 — but then there'd be 6+ variables and the globals would need $20,$21,$22. Unless the extra locals are short-lived and in caller-saved regs (like the arg copies).

Hmm! The 6 arg-copy pseudos (r79, r81, r85, r87, r90, r92) — one of them (r81) got $16! Maybe in the original source, an arg copy got $16 and $17, pushing c,d to $18,$19.

r81: refs 2, live 2, hard s0. Which copy is that? In the asm, `move $4,$17` (d into a0) etc. Hmm, `move $16,$5` — the copy of param_2 (a1) into a's reg $18? no.

Hmm! Actually maybe r81 IS `a`'s... no, a=r74.

Let me look at the lreg dump to see the pseudo↔reg mapping more concretely. The .lreg dump has the local-alloc view with pseudo names? gcc dumps show `(reg:SI 74)` for pseudos. Let me grep the .lreg section for "reg:SI 7" patterns.

Hmm, this is a deep rabbit hole. Let me make a decision:

Given the complexity, and that I have 6 more items to do, let me:
1. Record func_801415C0 as a WALL (or come back later).
2. Move to the other items, which may be easier (some are non-header, smaller).

Hmm, but wait. Actually, let me reconsider ONE more time, because I think there's a neat trick.

What if the local-alloc reg choice depends on `reg_last_freq` — the frequency of the LAST USE of each register. In gcc 2.7's local.c `allocate_local_regions`, the register choice for a local is made by `find_reg` which uses `reg_last_freq` to prefer registers that are "dead" soon.

Hmm, the local's choice among available callee-saved regs: gcc tries them in the order of the local reg list, subject to conflicts. $16,$17 are the first two. So c,d get them.

UNLESS $16,$17 are excluded because `regs_ever_live` says they're used by the globals. Hmm.

OK WAIT. What about `reg_alloc_order`? In gcc 2.7, `reg_alloc_order` lists hard regs in a preferred order for LOCAL allocation: it's typically: ARG_REGS, CALLER_SAVED_REGS... and LOCAL_REGNO set. The "local regs" for the local-alloc pool are the ones in `reg_alloc_order` that are not "hard reg preferences of globals".

In gcc 2.7's final.c before local_alloc:
```c
      /* Get the maximum register number... */
      ...
      /* Find the last use of each register.  */
      ...
      local_alloc (insn, max_reg, max_reg_num, reg_last_freq);
```
and in local.c `allocate_local_regions`:
```c
  /* Find the registers that are hard reg preferences of the globals
     and exclude them from the local pool.  */
```
Hmm.

OK. I'm going to try ONE specific experiment that tests whether local-alloc respects globals' hard-reg preferences: I can't add pins. 

Hmm, alternatively — what if the ORDER of the globals' allocation matters and a,b could get $16,$17 if they had higher priority AND local-alloc left $16,$17 free...

No. local-alloc runs FIRST. Period.

⇒ c,d (locals) get $16,$17 unless there are other locals before them.

⇒ For the target, c,d must NOT be locals.

⇒ c,d must be globals: multi-set.

So: I need c and d to have 2+ sets. Is there a source formulation where c and d have 2 sets and the generated code is unchanged?

IDEA! What if `c` and `d` are assigned in a way that the second set is the SAME value but expressed differently so that gcc's CSE doesn't merge but the code is identical?

E.g.:
```c
d = b + 0x2F;
...
d = b + 0x2F;
```
CSE (cse.c find_duplicate_insn) would find the second expression identical and reuse the first → 1 set. Probably.

What about:
```c
d = b + 0x2F;
d = d;    /* explicit self-assign */
```
gcc's cse would propagate d→d (same pseudo) → still 1 set.

What about making the second set come from a different but provably-equal expression: `d = b + 47;` vs `d = b + 0x2F;` — identical constants → CSE merges.

Hmm, `d = b + 0x2F` vs `d = b + 0x30 - 1`: gcc's combine would fold b+0x30-1 into b+0x2F → merged.

Hmm.

What about making c,d's second set come from a memcpy-like pattern... no.

OK so multi-set for c,d seems unreachable in a code-neutral way.

⇒ Let me question the "multi-set ⇒ global" hypothesis. Maybe the real criterion is different, e.g.:
- a,b,e are globals because they're used as call ARGUMENTS in a nested-call position? c and d are also call args.
- a,b,e are globals because their live range crosses MORE calls.
- Or because their pseudo has a "copy" relationship.

Actually here's another hypothesis: gcc 2.7's local-alloc can allocate a local to a callee-saved reg ONLY if the local is not live across a call OR ... hmm, c IS live across calls.

Hmm, hmm. Let me actually verify the c/d-are-locals claim by an experiment: dump c2 (same allocation) — no. Let me instead dump a variant where c is multi-set and see if "N regs to allocate" becomes 4.

Test: 
```c
c = a + 0x2F;
c = c;     /* hoping to create a 2nd set */
```
Hmm, gcc will fold.

Alternative test: make `d` multi-set in a way that DOES change the code, just to learn the rule (I don't care about the score for this test):
```c
d = b + 0x2F;
d = d + 0;
```
Same as identity.

Let me use a semantically-visible change: `d = b + 0x2F; ... d = d - 0;` same.

OK how about: `c = a + 0x2F;` then later `c = a + 0x2F;` but with the two separated by a call — CSE would still merge them (cse handles calls conservatively but for non-volatile memory it merges).

Hmm.

DIFFERENT TEST: make `a` single-set by using the parameter directly and see if a becomes a local:
```c
void func_801415C0(s32 param_1, s32 param_2) {
    ...
    param_2 = (s16)param_2;  /* hmm still 2 sets (copy + sext) */
```

Hmm, what if the parameter is never assigned: use `param_2` read-only and compute the two uses separately?
```c
c = (s16)param_2 + 0x2F;    /* separate sext */
...
func_800291C8(param_2 * 2 + 0x14, ...);
```
Then param_2's pseudo: copy-in (1 set) + 2 reads. Single-set! Would it become a local? It crosses calls → needs a callee-saved reg. If local, it'd get $16! And then a's target reg $16 = param_2's reg... but the target's s0 holds param_2 RAW then sexted in place then *2+0x14 in place. With separate expressions, we'd get:
- c = (s16)param_2 + 0x2F → `sll v0,a1,16; sra v0,v0,16; addiu v0,v0,47` (3 insns) — the target has `sll s0,s0,0x10; sra s0,s0,0x10; addiu s2,s0,47`. So the target computes the sext into s0 (a persistent reg) then adds 47 into s2. So the sext result must live in a register across the first call → it IS a variable.

So a (or a2 = (s16)param_2) is a variable live across the first call.

Hmm, unless the sext result is in param_2's own register (s0) — in-place. Which means param_2's pseudo is modified in place → multi-set.

OK.

DECISION: I'll try a couple more things then move on.

One more idea: what if I write the function so that there are exactly 5 variables and ALL are globals by giving c and d a second set via an innocuous but non-foldable expression that produces the SAME code?

What if d's second set is `d = b + 0x2F` where b is the SAME variable but the expression is `d = b + 0x2F;` vs `d = (s16)b + 0x2F;`? b is already (s16)param_1, so (s16)b == b numerically but gcc would generate `sll v0,b,16; sra v0,v0,16; addiu v0,v0,47` — extra insns ✗.

What if the second set is `d = d` written as `d = (s32)(s16)d`? d = b+0x2F which may not fit in s16 → different value ✗.

OK. Multi-set for c/d is out.

FINAL IDEA for this item: maybe the original source had SIX variables with one being an arg-copy that grabbed $16/$17, and c,d landed at $18,$19 while a,b,e got... no, then a,b,e would get $20,$21,$22.

Hmm, unless the 6th variable is such that a,b,e get $16,$17,$20 — i.e., locals take $18,$19 only.

⇒ locals = exactly {c, d}. ⇒ global-alloc gives a,b,e three regs, and they must be $16,$17,$20 with $18,$19 skipped by locals. So local-alloc gave c→$18, d→$19, meaning $16,$17 were skipped.

WHY would local-alloc skip $16,$17? 

AH WAIT!!! Maybe because $16 and $17 were used by the ARGUMENT COPIES! Look at the target's asm:
```
move s0,a1      <- copy param_2 (a1) to s0
```
If the "a" variable is the parameter copy... hmm.

Hmm, let me look at this from the "hard reg used" angle: in the target, hard regs used: 2 4 5 16 17 18 19 20 31. In my candidate: 2 4 5 16 17 18 19 20 31. Same set.

Hmm OK.

Let me try: maybe local-alloc's reg choice depends on `reg_last_freq`, which is computed from the register usage frequencies — and the choice isn't simply "first free". If the original source had different statement ordering, c,d might get $18,$19 even though $16,$17 are free!

That's plausible! local-alloc's `find_reg` uses `reg_last_freq` to pick among conflicting regs: it prefers the reg whose last use is least frequent... Hmm, but $16/$17 vs $18/$19 — all are callee-saved and equally used.

Hmm, but actually in gcc 2.7's local.c `allocate_local_regions`, the choice is made by `find_reg` in local.c:
```c
static int
find_reg (local_size, local_reg, ...)
```
Hmm.

You know what? The candidate c5 (d computed later) gave the same score 40 — so no change.

Let me try a broader sweep with many structural variants at once. But I don't have a good hypothesis space.

TIME CHECK: I should move on to other items. Let me record func_801415C0 as a candidate WALL for now (best 40) and come back at the end if time permits.

Hmm, but the brief says every item needs exactly one results.tsv row, and I should append to moves.md. I can do that at the end. Let me first survey the other items quickly to see which are more tractable, then allocate my remaining effort.

Let me look at the other 6 items' sources.

Actually, hold on. Let me reconsider the problem once more, because something nags me: the target's prologue interleaving:
```
addiu sp,sp,-40
sw s0,16(sp)
move s0,a1
sw s1,20(sp)
sll s1,a0,0x10
sra s1,s1,0x10
sw s3,28(sp)
addiu s3,s1,47
move a0,s3
sw ra,36(sp)
sw s4,32(sp)
jal 291B4
sw s2,24(sp)
andi s4,v0,0xff
sll s0,s0,0x10
sra s0,s0,0x10
addiu s2,s0,47
jal 291B4
move a0,s2
move a0,s3
jal 291A0
...
```
The `sw s2,24(sp)` comes AFTER the jal (in the delay slot)! And `sw s0,16(sp)` before `move s0,a1`. This is the classic gcc-2.7 prologue-insertion interleaved with the body, and the ORDER of the sw's reflects the order in which the registers were allocated (s0 first, then s1, s3, then ra, s4, s2).

Interesting: the save order is s0, s1, s3, ra, s4, s2. So the register allocation order was: s0 (a), s1 (b), s3 (d), then ra, s4 (e), s2 (c)!

Hmm! That's a different order: a, b, d, e, c. Hmm.

In MY candidate the saves are: sw $16,16(sp) [c], sw $17,20(sp) [d], sw $19,28(sp) [b], sw $31,36(sp) [ra], sw $20,32(sp) [e], sw $18,24(sp) [a].

So mine: c, d, b, ra, e, a. Target: a, b, d, ra, e, c.

Hmm, the target's save order a,b,d,...,e,c. If the saves are emitted in the order the registers were allocated (local-alloc first for locals, then globals?) hmm.

In the target, the save order is s0(a), s1(b), s3(d), ra, s4(e), s2(c). So d is 3rd and c is LAST. That's odd if c,d are locals (they'd be saved first).

Hmm! Unless the save order reflects the order the prologue insns were inserted, which is by register number within groups.

Hmm, this is interesting: in the target, s0 and s1 are saved FIRST (before the body), then s3, then ra, s4, then s2 (in the delay slot of the first jal).

Hmm, the prologue in gcc 2.7 is emitted at function entry as a block; but here the sw's are interleaved with the body, meaning gcc's "prologue" was partially scheduled by sched. The scheduling (sched1) moved things around. So the order reflects scheduling, not allocation.

OK. Let me move on to other items. I'll come back.

Let me look at the other items now. Let me read all 6 remaining sources at once (they're small-ish: 25-61 lines).

Actually, first let me record the time. Let me be efficient and look at all remaining sources.
