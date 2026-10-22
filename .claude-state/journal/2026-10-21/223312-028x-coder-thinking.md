---
ts: 2026-10-22T04:33:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_7NtClMswKtGdgaQAZPc1
---
nopin: 40 ins. `result` got $3 (v1), call result in $2 (v0), and at the end `move v0,v1` copies result ($3) into the return reg.

So in nopin, `result` (the local var) got v1 ($3) and the RESULT_DECL is $2 with a copy at the end.

Hmm. So the local `result` got $3 and the call result $2. So the priority ordering put the call-result pseudo first.

Why? Because the RESULT_DECL prefers v0 (hard preference), and gcc gives the preferred reg to the highest priority pseudo.

Idea: What if `result` (the local) is the RESULT_DECL, i.e. we return it in a way that gcc treats it as the result? If the function's only return is `return result;` and result is a local, gcc does copy.

What if instead we make the local the returned value directly: e.g.

```
int result = 0;
...
if (ret != 0) { if (ret & 0x8000) result = (...); }
return result;
```
Still a copy.

Hmm, but wait — in the TARGET, the copy at the end is absent: the boolean is computed directly into $2 (lbu v0, xori v0, sltiu v0). And the zero path has `move v0,zero`. So in the target, the RESULT_DECL is $2 and the boolean expression is computed into the RESULT_DECL directly (no intermediate). That's the "return <expr>" form: `return *(u8*)... == 0x15;` computes the comparison into the RESULT_DECL ($2) directly.

And in the "direct return" form (P1/P2 = current win.c), the RESULT_DECL is set in each branch, and gcc computed the comparison into $2 directly (lbu v0, xori v0, sltiu v0) — yes mine does that. The issue is only the call result being in $2 and hence no `move v1,v0`.

So in the direct-return form (win.c), the RESULT_DECL is in $2 and the call result is ALSO in $2 (they don't conflict since the call result dies before the RESULT_DECL is set... wait, the RESULT_DECL in the direct-return form is set in the branch after the call result dies? The RESULT_DECL's live range starts where it's set: in the `ret != 0` branch it's `return 0` or `return expr`. Hmm, the RESULT_DECL is a single pseudo with multiple definitions merged at the end — gcc's "return" creates a copy into RESULT_DECL at each return point, and RESULT_DECL is live from the first definition to the epilogue. Since the "return 0" in the else branch (ins 33 `move v0,zero`) is before the boolean path... the RESULT_DECL's live range might start early.

Hmm, but mine[24] `beqz v0` shows the call result tested in $2 while the RESULT_DECL is $2 later. So no conflict (call result dies at ins 26).

To force the call result into $3, we need a conflict: another pseudo live in [24..26] that grabs $2. The natural candidate: a variable live from before the call through the tests. But a variable live across a call must be in a callee-saved reg → changes the prologue (the target has only s0 and ra).

Hmm! Unless... the variable's live range across the call is only "pseudo-live" in a way gcc can handle: e.g. if the variable is only assigned in the branch after the call — like `result` in nopin — but that gave $3 to result.

So the real issue is the PRIORITY: which pseudo gets $2 (the preferred reg). In nopin, `result` got $3. Why? Priority: the RESULT_DECL prefers v0, `result` (local var) prefers... a local var with 3 refs; the call-result pseudo prefers v0 too.

Hmm. Both `result` and the call result want $2, and they conflict (result live in the branch while call result live at the tests). So one gets $2 and the other $3. Currently the call result wins.

To flip, we need `result` (or whatever holds $2) to have higher priority than the call-result pseudo. GCC's global.c allocno priority (GCC 12+):

```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;  ...
```
Hmm no. Let me recall the actual code (gcc/global.c, GCC 12):

```
/* Return the priority of allocation node N.  */
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  else
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
```
I'm clearly not recalling. But the notes have concrete numbers: pri 10000 for both (lever-free), and the tie-break at global.c:607 decides.

Let me look at the actual gcc source available? The project uses gcc 2.7.2 (ancient!). gcc 2.7.2's global.c has:

```
/* Return the priority of allocation node N ... */
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  if (reg == 0) return 0;
  ...
  /* compute priority based on number of references and length of live range */
  pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  ...
```
Actually gcc 2.7.2 global.c:

```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  ...
```
Hmm no; in gcc 2.7.2 the priority function is:

```
static int
allocno_priority (n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  if (REGNO (reg) >= FIRST_PSEUDO_REGISTER) ...
```

Let me look at the actual gcc 2.7.2 source if it's in the repo (tools/ has a toolchain?). Actually the important known fact: the notes say "pri 10000" and the tie-break is at global.c:607. In gcc 2.7.2 global.c, there's:

```
/* Return true if allocno N is live across a call ... */
...
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* Values of pseudo-regs are typically "used" once, but ... */
  ...
  if (reg) pri += ...;
  ...
  /* Adjust for the number of references */
  ...
}
```

I recall gcc 2.x global.c:
```
#define PRIO_FREQ_MAX 10000  ?
```
The number 10000 strongly suggests a fixed max priority: `allocno_priority` returns something scaled to 10000.

In gcc 2.7.2 global.c:
```
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* ignore register number 0 */
  ...
  pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;   /* no */
```

OK forget the source. Let's use the empirical approach: the tie-break at global.c:607 in gcc 2.7.2 is in the function that sorts allocnos:

gcc 2.7.2 global.c contains:

```
/* Sort by priority ... */
static int
allocno_compare (a, b)
     int *a, *b;
{
  ...
}
```
Hmm, actually I do recall gcc 2.x global.c:

```
static int
allocno_compare (a, b)
     int *a, *b;
{
  int apri = allocno_priority (*a);
  int bpri = allocno_priority (*b);

  if (apri != bpri)
    return apri - bpri;

  /* Prefer to allocate later-numbered pseudo-regs first.  */
  return *b - *a;
}
```
Hmm, if the tie-break is "prefer later-numbered pseudo-regs first", then the RESULT_DECL (created later? or earlier?) — the RESULT_DECL is created early in gcc (at function entry, it's the first pseudo). Actually the RESULT_DECL pseudo is created at the start of the function (gimplify creates it in the middle of the function body → the pseudo number is created early).

The call-result pseudo is created at the call site → later pseudo number.

If the tie-break prefers later-numbered pseudos first, the call result would win $2 (later number) — consistent with observations! And the RESULT_DECL loses.

So to flip: make the RESULT_DECL's pseudo number LATER than the call-result pseudo? Impossible for RESULT_DECL (created first).

Alternatively make the priority of `result` (the local variable) higher than 10000 — but priority is capped at 10000? The notes say "pri 10000" for both, but the pinned one had "pri 7500" for r73 and "pri 11428" for the call result. So pri can exceed 10000 (11428). So the formula isn't capped.

So pri = f(refs, live?). Data: (refs 4, live 7) → 11428; (refs 3, live 4) → 7500; and lever-free both 10000?? That doesn't fit a monotonic formula... unless the numbers 10000 came from a different dump (maybe .greg "Register dispositions" vs alloc table). Hmm, notes say: "lever-free r73 = RESULT_DECL (pri 10000, refs 3, live 3, prefers v0), call-result pseudos r79/r82/r84 (pri 10000, refs 2, live 2)".

Hmm so with refs 3/live 3 → 10000 and refs 2/live 2 → 10000? Then pri doesn't depend on refs/live in that dump, but in the pinned dump refs 3/live 4 → 7500 and refs 4/live 7 → 11428. Inconsistent... unless the pri in the dump is "REG_FREQ_PRIORITY" based (frequency), which saturates at 10000 (REG_FREQ_MAX=10000) for hot pseudos.

In gcc 2.7.2, REG_FREQ_PRIORITY values are frequencies scaled to REG_FREQ_MAX = 10000. And allocno_priority in gcc 2.x:

```
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* Try to figure out how often this pseudo is used ... */
  ...
}
```

Honestly, in gcc 2.7.2 global.c, I'm fairly confident of this code:

```
/* Return the priority of allocation node N. ... */
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;  ???
```

Let me try a different route: the actual gcc 2.7.2 source might be available in the toolchain dir. Let me look for it: tools/ has a mips gcc? `which mipsel-linux-gnu-gcc`? The project mentions gcc 2.7.2. Let me check.

If I can find global.c's allocno_priority, I can compute what makes pri higher. That's the scientific approach. But the source might not be present.

Alternative empirical approach: try MANY spellings. Since scoring is 1.7s, I can try 50 variants in ~2 minutes. Let me generate variants programmatically.

Ideas to raise the priority of the $2-holder:
1. More references to the variable: e.g. use `result` more times (but that changes the code).
2. Shorter live range → in gcc, priority = REG_FREQ-based; frequency of the pseudo's references in the estimated profile. Without profile info, gcc uses the "REG_FREQ_PRIORITY" computed from the number of references and loop depth? In gcc 2.x, freq is estimated via flow analysis: basic block frequencies. A pseudo referenced in a hot block gets higher freq.

Hmm, in gcc 2.7.2, `allocno_priority` is:

```
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  if (REGNO (reg) >= FIRST_PSEUDO_REGISTER) ...
```

I'll stop guessing.

PRACTICAL PLAN: brute force spelling variants. The scoring is fast. Let me write a generator that produces variants of the body and score them with sc.sh (one line per candidate). I need variants that change:

(a) the number of refs of the $2-holder: e.g. use `result` in the test as well.
(b) the live range: make `result` live earlier/later.
(c) decl order.
(d) types.

But note the constraint: the body must be a real C move, and must produce the same semantics.

Hmm, think about the semantics: function returns 1 iff call result != 0, (call result & 0x8000) != 0, and byte at buf2+6 == 0x15; else 0.

Alternative spellings:
```
if (ret != 0 && (ret & 0x8000) != 0)
    return (u8)((char*)buf2 + 6)[0] == 0x15;
return 0;
```
That was the &&-fold (score 6).

What about using the call result twice in a way that forces a copy? E.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret & 0x8000) { ... }
```
Hmm, `ret != 0` and `ret & 0x8000`: note that if (ret & 0x8000) != 0 then ret != 0. So the `ret != 0` test is redundant! The ROM has both tests though. The &&-fold would remove one test — the notes said the && fold scored 6.

Wait, actually the ROM's semantics: `if (ret != 0) { result = 0; if (ret & 0x8000) result = (byte) == 0x15; } else result = 0;`. Since ret & 0x8000 != 0 implies ret != 0, the outer test is redundant → the &&-fold `if (ret != 0 && (ret & 0x8000) != 0)` is semantically equivalent but drops the `beqz` for ret != 0? No — `ret != 0 && (ret & 0x8000) != 0` still needs both tests (the second implies the first but the compiler doesn't know that since ret is signed int: ret & 0x8000 != 0 implies ret < 0 → ret != 0 — the compiler DOES know that! For signed int, (ret & 0x8000) != 0 means the sign bit is set → ret < 0 → ret != 0. Does gcc 2.7.2 fold that? The notes said the && fold scored 6, and "only a runtime-derived 1 (the boolean) survives, and it costs the sltiu/beqz pair" — hmm, that was about func_8014C308.

Let me now think about what the ROM code shape is, to reverse-engineer the original C:

```
move v1,v0        <- ret copied to v1
beqz v1, +0x88    <- if (ret == 0) goto ret0
andi v1,v1,0x8000 <- delay slot: ret & 0x8000 computed in v1
beqz v1, +0x8c    <- if ((ret & 0x8000) == 0) goto ret0 (with move v0,zero in delay slot)
lbu v0,30(sp)
nop
xori v0,v0,0x15
j +0x8c
sltiu v0,zero,v0  <- result = (byte == 0x15)
ret0: move v0,zero
```

Interesting: the `andi v1,v1,0x8000` is in the delay slot of the first beqz — so the AND is computed speculatively before the branch. And the tests are on v1 (the copy).

In the original source (as written in the header with the pin), the code is:
```
ret = func_80133784(...);
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = (byte)buf2[6] == 0x15;
    }
} else {
    result = 0;
}
return result;
```
With the pin, gcc produced the ROM. So the ROM's structure with `move v1,v0` arises from `ret` being in v1 while `result` is pinned to v0.

For a lever-free version to produce the same code, we need `ret` in $3 and `result`/RESULT_DECL in $2 with the same instruction count.

The key question: can we make gcc allocate the call-result pseudo to $3 by giving another pseudo a higher priority for $2?

In gcc 2.7.2's global.c, I now recall more concretely:

```
/* Return the priority of allocation node N.  The larger the return value, the
   more important the node is... */
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* ignore the priority of hard registers... */
  ...
  if (REG_FREQ_PRIORITY...)
```

Nope. Let me look for the actual gcc 2.7.2 global.c in the environment (maybe under a toolchain dir). Let me search the filesystem for "allocno_priority" (fast find). If the source is present, great.

Let me do that search, plus check for the gcc toolchain location.

Actually — alternative: rather than the priority, consider making the call result NOT a call-result pseudo. What if we call through a function pointer with a different return type? E.g.:

```
ret = ((int (*)(int, void *, int))func_80133784)(1, buf1, (int)buf2);
```
Same thing.

What if the call result is stored to memory and reloaded? That'd add instructions.

What if we use the call result in a way that requires a copy? E.g. `if ((unsigned)ret != 0)`? no.

What about making `ret` a `short`? `short ret = func_80133784(...)` → truncation requires an explicit copy: `move v1,v0` + `andi`? Actually the value gets truncated to 16 bits: gcc would do `move v1,v0; andi v1,v1,0xffff`? or `sll/sra`? That adds instructions (target has none).

Hmm, but wait: what if `ret` is `unsigned short`? Then `ret & 0x8000` and `ret != 0` work. The truncation: the call returns int; assigning to unsigned short requires masking → extra insn. Unless gcc knows the value fits — it doesn't.

What about `long`? On mips 32-bit, long = int.

Hmm.

What if the call result is used in a context requiring the value in a different register — e.g. the call result is compared against a constant using a `sltiu`? no.

Alternative: what if there are TWO calls after the call, so the call result must survive a call → callee-saved reg? No, that changes the code a lot.

Let me think about the "priority" from gcc 2.7.2's global.c. I'm now fairly convinced the code is:

```
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* The following is a heuristic ... */
  ...
  if (REGNO (reg) == 0) ...
```

I'll just search the disk for the source.

Actually — better idea! I recall that in gcc 2.x, `allocno_priority` was:

```
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  ...
```
No.

FINE. Empirical it is. But let me consider what levers exist in C to change priority:

gcc 2.x global.c `allocno_priority` (I'll reconstruct from the .alloc dump fields the previous coder saw: "pri", "refs", "live", "blk"). I bet the formula is:

pri = (number of references) * something + (liveness) ...

Data points (pinned dump): call-result pseudo: refs 4, live 7 → pri 11428. RESULT_DECL: refs 3, live 4 → pri 7500.
Ratio: 11428/7500 = 1.52.

Try pri = refs * live * k: (4*7)=28 vs (3*4)=12 → ratio 2.33. No.
Try pri = refs^2 * live: 16*7=112 vs 9*4=36 → 3.1. No.
Try pri = (refs * 10000)/live: 4*10000/7 = 5714; 3*10000/4=7500. No (11428 > 7500 with more refs).
Try pri = refs*10000/live*? hmm 11428 = 80000/7 = 11428.57 → YES! 80000/7 = 11428.57 → 11428. And 7500 = 30000/4 = 7500 → refs*10000/live = 3*10000/4 = 7500. YES!

So pri = refs * 10000 / live (i.e., REG_FREQ_MAX * refs / live). Let me verify with the lever-free dump: RESULT_DECL refs 3, live 3 → 3*10000/3 = 10000 ✓. Call-result pseudos refs 2, live 2 → 2*10000/2 = 10000 ✓.

So priority = refs * 10000 / live (frequency-based: refs per live range). Now: to make the $2-holder beat the call-result pseudo (refs 2, live 2 → 10000), we need pri > 10000, i.e. refs/live > 1. E.g. refs 3, live 2 → 15000. Or refs 4, live 3 → 13333.

Hmm wait, but which pseudo holds $2? We want a pseudo X (holding the RESULT/final value) with pri > 10000, conflicting with the call-result pseudo (which must then take $3).

But note: the call result pseudo has refs 2 live 2 → pri 10000. If our `result` var has pri > 10000, `result` wins $2.

But hold on — the note says the call-result pseudo in the pinned dump has refs 4, live 7 → pri 11428 and it beat the RESULT_DECL's 7500. In the lever-free dump, both are 10000 and the tie goes to the call result (later pseudo number? or earlier?). Hmm — in gcc 2.x, the tie-break "prefer later-numbered pseudo-regs first"? The call result pseudo (r79/r82/r84) has a HIGHER number than the RESULT_DECL (r73). And it won. So the tie-break prefers HIGHER pseudo numbers (allocated first). That matches "prefer to allocate later-numbered pseudo-regs first" — yes, I'm now fairly confident gcc 2.x global.c has:

```
  /* Prefer to allocate later-numbered pseudo-regs first.  */
  return *b - *a;
```

Hmm, wait. Actually I recall in gcc's global.c (2.x):
```
static int
allocno_compare (a, b)
     int *a, *b;
{
  int apri = allocno_priority (*a);
  int bpri = allocno_priority (*b);

  if (apri != bpri)
    return apri - bpri;

  /* Prefer to allocate later-numbered pseudo-regs first.  */
  return *b - *a;
}
```
Yes! I'm quite confident about "Prefer to allocate later-numbered pseudo-regs first." in gcc 2.x global.c. Great.

So the RESULT_DECL (r73, created early) loses ties. To win, we need pri strictly greater.

Now, how do we get the pseudo holding $2 to have refs/live > 1?

The RESULT_DECL in the direct-return form: refs? live? In the direct-return form (win.c) each branch sets the RESULT_DECL. Hmm, the notes' lever-free dump was for the nopin form presumably.

Let's think about the nopin form: `result` is a local var, assigned 0 in the then-branch, assigned the boolean in the inner branch, assigned 0 in the else branch, and returned. That's refs: def 0, def bool, def 0, use in return → 4 refs? live range: from the first def (in the then branch) to the return → but the branches are disjoint; gcc's live range for `result` spans the whole region.

In nopin, `result` got $3 and the call result got $2, so `result`'s pri ≤ 10000 (tie) and the call result won by number.

Now what if we make `result` have MORE refs (e.g. refs 5, live 4 → 12500)? Refs can be increased by using the variable more times, but that changes the code... unless the extra uses are dead (e.g. `if (0) result = 1;`? gcc would eliminate it → no extra refs).

Alternatively DECREASE the live range of `result` — pri = refs*10000/live. Shorter live range → higher pri. Live range of `result` = from its first def to its use. If the first def is later (e.g. inside the branch) the live range is short.

Hmm, but in the nopin form the first def is inside the `ret != 0` branch (ins 25+) and the use is the return (ins 33) → live ~8. refs 4 → pri 5000? But the notes said the RESULT_DECL had live 3.

Hmm, careful: in nopin, `result` is a local variable, and `return result;` creates a copy to the RESULT_DECL. The RESULT_DECL (r73) is the one with pri 10000 refs 3 live 3, and it got $2 (the copy `move v0,v1` at the end shows the RESULT_DECL in $2 = v0, and `result` in $3 = v1).

So in nopin, the RESULT_DECL is $2 and `result` (the local) is $3! And the call result is $2 too (beqz v0 tests the call result in $2). Hmm, wait: the call result pseudo and the RESULT_DECL are both $2? The call result is live [24..26], the RESULT_DECL live [..  epilogue]. They overlap? The RESULT_DECL is set at ins 27/33/34 — after the call result dies at 26. So no conflict → both can be $2. OK.

So in nopin the local `result` got $3 and the call result got $2. To get the call result into $3, we need the LOCAL `result` (not the RESULT_DECL) to have pri > 10000 so it takes $2 before the call result... but wait, in nopin the local `result` is $3 and the call result is $2 — they conflict (the local's live range [25..33] overlaps the call result's [24..26]). Both pri = 10000? The local `result` pseudo: refs = 3 (two defs of 0? hmm) and live = ?

To flip, make the local `result` have pri > 10000: e.g. refs 4, live 3 → 13333; or refs 3, live 2 → 15000.

How to get more refs for `result` without changing the code? Use it more:
```
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = (*(u8*)((char*)buf2+6) == 0x15);
    }
} else {
    result = 0;
}
return result;
```
refs: def(result=0) ×2 + def(bool) + use(return) = 4 refs, live ~9 → pri = 4*10000/9 = 4444 < 10000. Hmm, that's low. But the notes said the RESULT_DECL had pri 10000 refs 3 live 3.

Hmm — but the local `result` might not be in the alloc dump the coder looked at (they looked at r73 = RESULT_DECL). The local `result` would be another pseudo.

OK: the plan is to control the LOCAL variable's priority. But wait — if the local `result` wins $2, then the RESULT_DECL copy at the end would be `move v0,v1`-ish... no: RESULT_DECL prefers v0 ($2) but $2 is taken by the local `result` during the overlap → RESULT_DECL would get another reg and the final copy `move v0, vX` appears → extra instruction vs target. Unless the RESULT_DECL is coalesced...

Hmm! Unless the function's return value IS the local variable, i.e. gcc's "return result" where result is the only var → gcc might use the RESULT_DECL directly if the local is not otherwise used? No, gcc always copies to RESULT_DECL at the return statement (unless the return value is a "return slot" optimization: `-fipa-*`? In gcc 2.7.2, there's no such optimization).

Hmm, but actually: gcc 2.7.2's gimplify for `return expr;` creates a copy to RESULT_DECL. But the RTL "return slot" optimization (assigning directly to the return slot) exists in gcc? The "return slot" optimization was added around gcc 4.x. In 2.7.2 no.

But hold on — in the PINNED version, the local `result` is pinned to $2 and the RESULT_DECL is also $2 → the copy `move v0, v0` is coalesced away (both in v0, copy eliminated). That's why the target has no copy at the end.

So lever-free, we want: the local `result` in $2 (winning over the call result) AND the RESULT_DECL also in $2 (so the final copy coalesces). But the RESULT_DECL is live from the return point to the epilogue, while the local `result` is live until the return → they overlap → conflict → RESULT_DECL would get another register → extra copy. Unless the RESULT_DECL has higher pri (it prefers v0 = hard preference!). Hmm — hard preferences matter a lot in gcc's global allocation: a pseudo with a hard reg preference gets a bonus. In gcc 2.x, `allocno_priority` includes the hard-reg preference bonus? The notes mention "prefers v0" / "conflicts v0, prefers v1" in the .greg dump.

OK. This is getting deep. Let me do the pragmatic thing: generate many variants and score them. The variants to try:

1. nopin with the local `result` given more refs (e.g. `result = 0;` then use result in a way that doesn't change semantics... hard).

2. Different structure: what if the function's returned value is computed as an expression assigned to a variable that is used multiple times?

3. What if we drop the local and use a different spelling where the value returned is a single expression:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return *(unsigned char *)((char *)buf2 + 6) == 0x15;
    }
    return 0;
}
return 0;
```
= win.c (score 6). Here the RESULT_DECL is set in 3 places → refs 3? and live...

4. What about making the boolean a variable:
```
int b;
...
b = (*(u8*)((char*)buf2+6) == 0x15);
return b;
```
Adds a copy.

Let me think about the target's structure from the "pri" angle: In the pinned dump, the call-result pseudo had pri 11428 (refs 4, live 7) — interesting: refs 4? The call result pseudo (the copy of the call's return) — refs 4 means 4 references to it (2 tests + ?).

Hmm hold on. In the pinned version, `ret` (the local int) holds the call result and is used in 2 tests. The call-result pseudo is the RTL pseudo for the call's return value. Its refs: the call insn's output + the copy + ... = 4 refs.

OK here's another thought experiment: the difference between pinned and lever-free isn't just priority — in the pinned version, `result` has a FIXED register ($2), which in gcc's global allocation is a hard constraint: the allocno for `result` is tied to reg 2, and the conflict graph excludes reg 2 from other pseudos' candidate sets. The RESULT_DECL is a separate pseudo though. Hmm, in the pinned dump r73 was the RESULT_DECL with "conflicts v0, prefers v1" — meaning the RESULT_DECL prefers v1?? and conflicts v0 (because the pinned result holds v0).

So in the pinned version: RESULT_DECL conflicts v0 (pinned result), prefers v1 → it goes to v1 ($3). And the local `result` is pinned to v0 ($2) — where's the local `result` pseudo? It's the pinned one, allocated to reg 2 directly.

Then the call-result pseudo: refs 4 live 7 pri 11428 → it wants v0 but v0 is occupied by the pinned `result`... it takes v1 ($3)?? But the RESULT_DECL also prefers v1. Hmm, then one of them takes $3 and the other $4?

Ugh, this is deep. Let me instead do the empirical brute-force but smart: I'll write a generator of ~30-60 spelling variants and score them all (1.7s each ≈ 2 min). Then iterate.

Variants to generate for func_8014FD54 (all semantically identical to the ROM):

Base templates:
T1: nopin (local result, if/else with two zeros) — score 9.
T2: direct returns (win.c) — 6.
T3: local result, but `result = 0` only once at the top (before the call? no, that changes live range)...

Let me think about which variants could plausibly flip the allocation:

(a) Move `result = 0;` out of the branches: e.g.
```
int result = 0;
ret = call();
if (ret != 0) { if (ret & 0x8000) result = (...); }
return result;
```
`result` live across the call → callee-saved → changes prologue. Probably bad but worth 1 try.

(b) Use the result variable with a "u8"/"char" type to change refs.

(c) Increase refs of the $2-holder by assigning it twice: e.g.
```
if (ret != 0) {
    result = 0;
    if (ret & 0x8000) { result = (...); }
    else { result = 0; }   /* extra def → extra ref */
} else result = 0;
```
That changes the code (extra branch) — probably worse.

(d) Reduce the live range of the local `result`: e.g. assign and return within the branch:
```
if (ret != 0) {
    if (ret & 0x8000) return (...);
    return 0;
}
return 0;
```
= win.c (score 6). Here the RESULT_DECL is the $2 holder with pri = refs*10000/live. refs: 3 defs (return 0, return bool, return 0) + ... live: from the first def (ins ~27) to the epilogue. Hmm, that's live ~10, refs ~4 → pri 4000. Yet it got $2. Because of the hard preference v0?

Hmm, in the lever-free win.c the RESULT_DECL got $2 (v0) — because of the hard reg preference (prefers v0) which in gcc's global allocation gives a bonus. So the RESULT_DECL wins $2 in win.c; the problem is that the CALL RESULT also wants $2 and the RESULT_DECL's live range doesn't overlap the call result's... so the call result gets $2 too (no conflict). The problem: no conflict → no reason for the call result to be in $3.

So we need a pseudo that (1) is live at the call-result's live range [after call .. tests], and (2) has $2 as its reg, forcing the call result to $3.

In win.c, the RESULT_DECL is live from ins ~27 (after the first test) — hmm, when is the RESULT_DECL first set? The `return 0` in the else branch (ins 33 in target) and the `return 0` inside the branch (ins 28 target). The first def in program order... The RESULT_DECL's live range starts at the earliest def. In the target, the defs are at ins 28 (move v0,zero in the delay slot) and 33/34. So the RESULT_DECL is live from ~ins 27 onward. The call result is live [24..26]. No overlap → no conflict → the call result could be $2.

To create the overlap, the RESULT_DECL (or some pseudo) must be live BEFORE the call and still live at the tests. But then it must survive the call → callee-saved. Unless it's live before the call but its live range is... no, if it's live across the call it needs a callee-saved reg.

Hmm! Unless the pseudo is live before the call but DEAD after the call — then no conflict.

Wait, the conflict needs: pseudo X live at [24..26] (the call-result's range) and X ≠ call-result. And X must hold $2.

X could be a pseudo whose live range covers ins 24-26 and which is assigned $2 by priority. But X must be live across the call (ins 22-23) → callee-saved... unless X's live range starts AFTER the call: X is defined after the call and live at 24-26. Then X conflicts with the call result, and X wins $2 if it has higher pri.

What could be defined after the call and live across the tests? The RESULT_DECL is defined in the branches (after the tests). Hmm.

What if the code were:
```
ret = call();
result = 0;            /* defined right after the call, live until the return */
if (ret != 0) { if (ret & 0x8000) result = (...); }
return result;
```
Here `result` is defined right after the call (ins 24) and live until the return → its live range [24..33] overlaps the call result's [24..26] → conflict! And `result` is not live across the call → it can stay in a caller-saved reg ($2 or $3).

Now who wins $2? `result` (refs: def 0, def bool, use return = 3 refs; live ~9 → pri 3333) vs the call-result pseudo (refs 2 live 2 → pri 10000). The call result wins → `result` gets $3. Hmm, same as nopin.

To boost `result`'s priority we need refs/live > 1 → e.g. refs 4, live 3. Live 3 means the live range is ~3 instructions. Hmm.

Alternatively, boost by making the live range shorter: e.g. `result` defined right after the call and used right after (short live). But the structure requires it live until the return.

Alternatively: reduce the call-result pseudo's priority: it has refs 2, live 2 → 10000 (max for 1 ref/live). Could the call result have live 3+? E.g. if the call result's live range were longer (spanning more instructions), its pri drops. The call result's live range in the current code is [24..26] = 3 insns (live 2?). If we could make the call result live longer — e.g. use `ret` again later — its live range grows, pri drops below 10000, and then `result` (pri 3333?) — no, still below.

Hmm, pri = refs*10000/live. The call result with refs 2 live 2 = 10000. If the call result had refs 2 live 3 → 6667. Then `result` with refs 3, live 2 → 15000 wins! But how to make `result`'s live range 2 and the call result's 3?

Alternatively make `result` have many refs: e.g. `result` assigned in a loop? no.

Hmm, what about the `&&`/`||` folds: `if (ret != 0 && (ret & 0x8000) != 0)` — the call result's live range grows (used in 2 tests), refs grow.

Let me reconsider: maybe there's a much simpler route: the notes' "moves that cracked" for similar items in other shards. E.g. "pin | func_8017EEB0 | MATCH — the first call's result moves to its own var w (2 uses); the stored value keeps the short live range and wins $2, the pin is gone (G06)".

So the mechanism: giving the value a short live range and 2 uses makes it win $2.

Here the analogous move: the call result must be in $3 while the final value is in $2. Hmm.

Another thought: what if we make the RESULT_DECL (the returned value) have a SHORT live range and the call result a LONG one? The final value is computed at the very end (ins 28-32) and returned at 35-39. Its live range is long.

What if the function returns the value via a different structure: e.g. compute the boolean FIRST into a variable, then return it? no, the code order is fixed.

Hmm, let's think about which pseudo the target's $2 holds at ins 24-26: nothing! In the target, at ins 24-26, $2 holds the call result (hard reg v0, copied to v1 at ins 24). The copy `move v1,v0` means: the call-result pseudo is in $3 (v1) and the hard reg $2 still holds the raw value. So the conflict isn't with $2 at all!

The call-result pseudo (the copy) got $3, not $2, even though $2 was free at that point (the RESULT_DECL's live range starts later). Why $3 and not $2? Because in the PINNED version $2 was reserved (the pin). In the lever-free version the call-result pseudo gets $2 (no copy needed).

So the difference: lever-free, gcc coalesces the call-result pseudo with the hard reg $2 (no copy). The target has the copy because the pseudo is elsewhere.

So what we need: the call-result pseudo NOT be coalesced with $2 — i.e., something else in $2 at that time.

Alternatively: the copy could come from a different mechanism — e.g. if the call result is assigned to a variable of a DIFFERENT type than int (requiring a conversion copy) — but the target's copy is a plain `move v1,v0` with no conversion.

Hmm, what if the call result is used in a context that requires it in a register other than the return reg? E.g. `ret = func_80133784(...)` where func_80133784's return type is `unsigned int`? The header declares `extern s32 func_80133784(s32 a0, void *a1, s32 a2);` — s32 = int. If we changed the declaration... but we can't change the header's declarations? The constraint says "no signature or decl change outside the body" — the body only. The declarations are outside the body. Hmm, but our candidate body file replaces the function definition in the TU; the extern decls come from the header (unchanged).

But wait: the scoring compiles the candidate body in place of the function definition in the TU — the extern decls remain as in the header. However! If the body file is the whole TU replacement... "--body: FILE holds the function's definition only" — so the tool replaces the function definition in the TU, keeping the externs.

Could we declare a local shadow? e.g. inside the body:
```
{
    extern unsigned int func_80133784(s32, void *, s32);  // conflicting decl → error
```
No.

Alternatively, cast the call result: `ret = (unsigned int)func_80133784(...)` — the conversion int→unsigned is a no-op, no extra insn, but it might change the pseudo's nature? Probably not.

What about `(s16)`? That adds masking.

Hmm, what if we take the address of the call result or pass it somewhere? no.

New idea: what if we introduce a local variable that is live across the call and is stored/loaded in a way that doesn't need a callee-saved reg — e.g. a variable whose live range crosses the call but gcc spills it to the stack? That adds instructions.

New idea: What if the call result is used in the delay slot context... no.

New idea: what if there are two calls to func_80133784? No, that changes semantics.

Let me look at this from the "what did the ROM actually compile from" angle. The ROM's structure (move v1,v0 then tests on v1) with `result` pinned to $2 suggests the original source was:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = (u8)((char*)buf2 + 6) == 0x15;
    }
} else {
    result = 0;
}
return result;
```
where `result` was pinned to $2 (the FAKE). The real original probably had something that produced $2 for the result naturally — e.g. the original had a `switch` or a different structure, or the ROM's code came from a different original source (the ROM is the ground truth; the original source is unknown).

Since the ROM is ground truth, our lever-free body must produce the same code. The question is whether a lever-free spelling exists at all. This is what the task explores; a WALL is an acceptable outcome.

But wait — maybe there's a much better trick: the call-result pseudo is in $2 because gcc coalesces it with the hard reg. What if the call result is stored to a variable and the variable is used in a way that gcc puts it in $3 — e.g. by using `ret` in a comparison with a 64-bit type? no.

Alternatively: what if we make the call result's uses require TWO different registers? E.g. use `ret` in the test `ret != 0` and also in `ret & 0x8000` — same reg.

Hmm, here's a thought: the call result is used in 2 tests. What if we use it 3 times or in a way that increases its live range, dropping its pri below the local `result`'s pri?

Let me compute pri for various forms:
- `result` local with def right after the call, live until the return: live ~9, refs 3 → 3333.
- call-result pseudo: refs 2 (the copy + ...), live 2 → 10000.

To beat it, `result` needs refs*10000/live > 10000 → refs > live. E.g. refs 4, live 3.

How to get a local with refs 4 and live 3? A variable defined and used 3 times within a 3-instruction window...

Alternative: reduce the call-result's pri instead. Its pri = refs*10000/live = 10000 (refs 2, live 2). To reduce: increase its live range or reduce refs. If the call result's live range were [24..30] (live 6) with refs 2 → 3333, then `result` with pri 3333 ties → tie-break favors the higher pseudo number. The call-result pseudo is created later (higher number) than `result`? `result` is created at its declaration (early), the call-result pseudo at the call (later). So the call result still wins ties. Hmm, unless `result` is created LATER than the call — e.g. if `result` is declared inside a block after the call!

Ooh: in C89, declarations must be at the start of a block. We could do:

```
ret = func_80133784(1, buf1, (int)buf2);
{
    int result = 0;
    if (ret != 0) { if ((ret & 0x8000) != 0) result = (...); }
    return result;
}
```
Hmm, a nested block: `result` is declared after the call → its pseudo number is HIGHER than the call-result pseudo → in a tie, the higher number wins → `result` gets $2, and the call result gets $3!

But wait: does the nested block change the semantics/structure? The `return result;` inside the block is fine.

Hmm, but does declaring `result` after the call really make its pseudo number higher? Pseudo numbers are assigned in RTL generation order, which follows the statement order. The call is before the block → the call-result pseudo gets a lower number than `result`'s pseudo.

But: with the tie-break favoring higher numbers, `result` would take $2 (prefers v0 hard pref) and the call result $3. Then the copy `move v1,v0` appears! And the RESULT_DECL copy at the end: RESULT_DECL is created at function start (lowest number) and prefers v0 but conflicts with `result` ($2) → RESULT_DECL would get... hmm, it prefers v0 but v0 is taken by `result` in the overlapping range → RESULT_DECL gets $3? and the final copy `move v0,v1` appears → extra instruction.

Hmm. But wait: maybe not. In the nopin form, the RESULT_DECL got $2 and the local `result` got $3, with a final `move v0,v1`. If the roles swap (local `result` gets $2, RESULT_DECL gets $3), the final copy is still one instruction: `move v0,v1`. So the nopin form would give: call result $3 (copy move v1,v0), local result $2, RESULT_DECL $3?? — conflict between local result and RESULT_DECL (they overlap) → one gets $2, the other $3; the call result needs a third register → $4? Then the tests would be on $4, not $3. Target has the tests on $3.

Hmm! In the target, `result` (the pinned pseudo) IS in $2 and the RESULT_DECL... in the pinned dump, "r73 = RESULT_DECL (pri 7500, refs 3, live 4, conflicts v0, prefers v1)" — so the RESULT_DECL went to v1 ($3) in the pinned version! And the local `result` (pinned) is $2. And the call-result pseudo also wanted v1? It has pri 11428 > 7500 → the call result got $3 (v1) and the RESULT_DECL got... hmm, both can't have v1.

Let me re-read: "pinned r73 = pri 7500, refs 3, live 4, 'conflicts v0, prefers v1', and the hard reg $2 is reserved for the whole function." And "the call-result pseudo (refs 4, live 7 -> pri 11428; 'prefers v0', it is the call's hard-reg copy) outranks the RESULT_DECL (refs 3, live 4 -> pri 7500, also 'prefers v0')".

Hmm, the note says the RESULT_DECL "prefers v0" in the first sentence and "conflicts v0, prefers v1" in the second. Confusing. Note r73 might be the RESULT_DECL in one dump and the local in another.

Anyway: in the pinned target, at the end there's NO copy `move v0,v1`. The final value is in $2 = the pinned `result`. The RESULT_DECL's copy to v0 is coalesced because the RESULT_DECL is in $2 as well? But then the RESULT_DECL conflicts with the pinned result (both $2) — unless the RESULT_DECL's copy was coalesced into the pinned result's register (gcc's copy coalescing: the copy RESULT_DECL ← result with both in $2 → the copy becomes a no-op).

Right! In the pinned version, the pinned `result` is in $2 and the RESULT_DECL is a copy of it; gcc's coalescing eliminates the copy by putting the RESULT_DECL in $2 too (they're the same value). Since the pinned pseudo is a hard reg ($2), the RESULT_DECL copy gets $2 as well.

So in the target, effectively: the "value" pseudo (pinned) is $2 and the RESULT_DECL is $2, and the call result is $3.

For a lever-free version, we want: the value pseudo = $2, the RESULT_DECL = $2 (coalesced), the call result = $3. But the value pseudo (a local var) and the RESULT_DECL are copies of each other → gcc coalesces them into ONE pseudo → so the local `result` and the RESULT_DECL are the same register (no copy at the end) as long as they're both free.

In nopin, the local `result` got $3 and the RESULT_DECL got $2 with a final `move v0,v1` — so they were NOT coalesced there. Hmm, because the local result is live longer/different range.

Hmm OK. In the target, is the local `result` (pinned) really the same as the RESULT_DECL? The pinned `result` is a separate variable; `return result;` copies it to the RESULT_DECL. The copy is coalesced because both are $2.

So in a lever-free version, we want the local `result` and the RESULT_DECL both in $2 and the call result in $3.

Now, the local `result` in nopin got $3 (not $2) — because it lost the priority battle to the call-result pseudo (which prefers v0 and has pri 10000 vs the local's lower pri).

So the key: make the local `result` have pri > 10000, OR make the call-result pseudo have pri < local's.

Ideas to increase the local's pri = refs*10000/live:
- Increase refs: the local `result` is referenced at: def(0), def(bool), def(0 in else), use(return) = 4 refs. live: from the first def to the return = ~9-10 insns → pri ~4000-4400.
- Decrease live: if `result`'s first def were later (e.g. only defined in the inner branch) its live range shrinks. But it must be defined on all paths.

Alternatively: increase the CALL RESULT's live range so its pri drops below the local's. The call result is used in 2 tests, both right after the call. Its live range [24..26]. If we add a use of `ret` later (e.g. in the else branch), the live range extends → pri drops.

Hmm! But the ROM's code doesn't have a later use of ret. But wait — the pri only matters for allocation, and if the local `result` gets $2 while the call result gets $3, the call-result's live range doesn't change in the code (the copy is at ins 24). The extra use of `ret` would appear in the code though (e.g. an extra test). Unless the extra use is dead code that gcc removes but still counts refs? No — gcc removes it before regalloc.

Hmm. What if `ret` is used in a way that doesn't change the code: e.g. `if (ret != 0)` where ret is used twice: `if (ret != 0 && ret != 0)`. Silly but might increase refs without changing the code? gcc would fold it.

What about `ret = func_80133784(...); if (ret != 0) { ... }` where the assignment's value is also used: `if ((ret = func_80133784(...)) != 0)`. That's the same.

OK, let's think about the tie-break route: make the local `result`'s pseudo number HIGHER than the call-result pseudo, so that in a pri tie it wins $2. But then the RESULT_DECL (created at function entry, lowest number) loses ties to both → it gets $3/$4 → the final copy `move v0,vX` appears (extra insn) → but wait, in nopin that copy IS present (mine[34] `move v0,v1`) — that's the 9-score version with 40 ins. Hmm! nopin has 40 ins (same as target) but a different arrangement.

So in nopin: call result $2, local result $3, RESULT_DECL $2 (copy `move v0,v1` at the end).

Wait, that's inconsistent: the RESULT_DECL is in $2 but the local `result` in $3, and the copy is `move v0,v1` — RESULT_DECL ← local result. But the RESULT_DECL's live range starts at the return point (after the local dies) → no conflict → RESULT_DECL can be $2. And the local result got $3 because it conflicted with the call result ($2).

If instead the local result took $2 (beating the call result), the RESULT_DECL would then conflict with the local result? The local result's live range ends at the return; the RESULT_DECL's starts there → they overlap only at the copy point → gcc's coalescing would handle it: the copy RESULT_DECL ← result with result in $2 → coalesce RESULT_DECL into $2 → no copy at all! Then the final code would be: call result $3 with copy `move v1,v0`, the boolean computed into $2 (the local result's reg = $2), and the RESULT_DECL in $2 → NO copy at the end. That's EXACTLY the target!

So the plan: make the local `result` win $2 over the call-result pseudo.

For that, either pri(local) > pri(call-result), or (tie and) the local's pseudo number > the call-result's.

The local `result` is declared at the top → low pseudo number → loses ties. But we can declare it in a nested block AFTER the call → higher pseudo number → wins ties!

Wait, but does the pseudo number follow the declaration order in the C source? The RTL is generated per statement in order. A block scope declaration creates the pseudo at the point of the declaration in the RTL (the pseudo is created when the decl is gimplified). If the declaration appears after the call statement in the source, its pseudo number is higher.

But hmm: gcc 2.7.2 might allocate pseudo numbers for all locals at function entry (in gimplify, decls are created when encountered). Yes, gimplify processes statements in order; the decl statement creates the pseudo at that point.

So candidate:
```
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    buf1[0] = 0; ...
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf2, buf2);
    ret = func_80133784(1, buf1, (int)buf2);
    {
        int result = 0;
        if (ret != 0) {
            if ((ret & 0x8000) != 0) {
                result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        } else {
            result = 0;
        }
        return result;
    }
}
```
Hmm, careful with the structure: the original has result=0 in the then-branch and in the else-branch. With `int result = 0;` at the block start, the then-branch's `result = 0` becomes redundant → gcc might keep it (it's a redundant store to a local; gcc 2.7.2 -O would likely remove it? It's a dead store — gcc's store-merging might remove it). Removing it changes the code? No — the redundant `result = 0` doesn't appear in the ROM anyway (the ROM's `move v0,zero` at ins 28 is the return 0 path). Actually in the ROM, the "result = 0" in the then-branch and the `move v0,zero` at ins 28 — the ins 28 `move v0,zero` is in the delay slot of the second beqz, which is the "mask test failed" path (returns 0). And the else path (ret==0) is ins 34 `move v0,zero`. So the ROM has TWO `move v0,zero` — one at ins 28 and one at 34. In the nopin form, mine[27] `move v1,zero` and mine[33] `move v1,zero` — consistent.

OK, let's just try variants and see. Let me write the variants and score them.

Variant list for func_8014FD54 (file wNN.c):
1. block-decl result after the call, with `int result = 0;` and the original if/else structure minus the redundant `result=0` in the then branch:
```
    ret = func_80133784(1, buf1, (int)buf2);
    {
        int result = 0;
        if (ret != 0) {
            if ((ret & 0x8000) != 0) {
                result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
            }
        }
        return result;
    }
```
Hmm, this drops the `result = 0` in the then branch — the redundant store might have been in the ROM? The ROM shows `move v0,zero` at ins 28 (delay slot of the mask-test branch) — that's the "mask==0 → return 0" path. In the nopin form, gcc produced `move v1,zero` at ins 27 (delay slot) and `move v1,zero` at 33. So the two zeros correspond to: (a) the then-branch's `result = 0` (which becomes the delay-slot move? no...).

Hmm, in the target: ins 27 `beqz v1,a500` (mask test) with delay slot ins 28 `move v0,zero`. The branch target a500 = ins 34 (`move v0,zero` at 34? no). Let me map addresses: target ins 27 at 8014fdc0 `beqz v1,8014fde0` → jumps to 8014fde0 = ins 35 (lw ra). And the delay slot ins 28 at 8014fdc4 = `move v0,zero`. So the "mask==0" path sets v0=0 and jumps to the epilogue. And ins 25 `beqz v1,8014fddc` → 8014fddc = ins 34 `move v0,zero` → the "ret==0" path.

So the two `move v0,zero` = the two "return 0" paths. Good, matching nopin's structure (`result = 0` in the then-branch → the delay-slot move at ins 28? hmm, nopin's mine[27] `move v1,zero` is the delay slot of the mask beqz at 26 → that's the then-branch's `result = 0` merged with the "return 0" path).

OK whatever, the compiler figures it out.

2. Same but the block-decl without init:
```
    {
        int result;
        if (ret != 0) { result = 0; if (...) result = (...); } else result = 0;
        return result;
    }
```
3. Same as 2 but the block placed after the call with `result` assigned in both branches.
4. A variant where the value is returned directly but the RESULT_DECL is created later? Can't.

Also: what if we declare `result` at the top but assign it right after the call? Pseudo number still early.

Let's also consider: gcc might not even give the local `result` a pseudo number after the call... it will.

Let me create these variants and score them. Let me write a small script to generate + score. I'll use sc.sh with multiple files.

Let me write the files now. Base body (from orig, with the pin removed).

I'll write:
w1.c: block-decl result after call, init 0, minimal branches.
w2.c: block-decl result after call, no init, original branches.
w3.c: block-decl result after call, no init, original branches but `result` declared at the top? (no)
w4.c: top-level decl result but assigned right after the call (result = 0 right after the call, then the branches).
w5.c: like w1 but the block also encloses the calls? no.

Also variants where the value's uses increase.

Let me write them.

Note the file format: the body file holds the function definition only, and the tool replaces the definition in the TU. The extern decls come from the header. So my body file must not redeclare func_80149290/func_80133784 — the orig.c body file (as copied) doesn't. Good, orig.c is exactly the body without the pin? No: orig.c HAS the pin (it's the copy of the current def in src). Right.

Let me write the variants.
