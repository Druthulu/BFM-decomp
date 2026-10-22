---
ts: 2026-10-22T08:49:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vcuCctHObGSdUFz9HZ4x
---
The -dq flag didn't produce a reload dump file (c1.i.rtl is the -dr dump). In GCC 2.7, the reload dump file might be named differently. Let me check the dump names: the .i files with suffixes. -dr → .rtl. For reload, gcc 2.7's dump_file_id: reload → DUMP_RELOAD? Let me check what flags exist: `cc1 --help`? Let me try -dA (all dumps) and see the file names. That could be big. Alternatively check the c1.err output for the dump file list.

Actually gcc 2.7 dump_file_id enum:
DUMP_CSE, DUMP_CSE2, DUMP_CSE3, DUMP_COMBINE, DUMP_COPY, DUMP_EXPAND, DUMP_FLOW, DUMP_FLOW2, DUMP_GLOBAL, DUMP_JUMP, DUMP_JUMP2, DUMP_LOCAL, DUMP_LOOP, DUMP_RTL, DUMP_SCHED, DUMP_SCHED2, DUMP_SCCP, DUMP_STORE_MOTION, DUMP_TOP, DUMP_WHIRL, ...
The reload dump in gcc 2.7 is enabled by -dq? The names: .combine, .cse, .cse2, .flow, .global (greg), .jump, .jump2, .local (lreg), .loop, .rtl, .sched, .sched2, .top, .whirl...

The files in dumps_c1 were: combine, cse, cse2, dbr, flow, greg, jump, jump2, loop, lreg, rtl, sched, sched2 — matching the flags -dc? hmm -dbr is delayed branch. There's no "reload" dump in 2.7 I think. GCC 2.7's reload.c does have a dump file? Looking at the list: no reload file. So no reload dump.

Alternative: look at the .rtl dump after reload = the .greg dump's RTL (which is post-reload). The .greg dump's RTL showed the copies. Let me grep the .greg section for copies involving pseudo 73... but the .greg RTL is post-allocation (hard regs). Hmm, the .greg dump prints the RTL at the time of the dump — the dispositions are printed at the end of global_alloc, but the RTL dump might be printed BEFORE the allocation (the dump function is called at the start of global_alloc with the pre-allocation RTL?).

Looking at the .greg output: it printed the conflicts, preferences, then "Register dispositions" (final), then "Hard regs used", then the RTL. Since the RTL shown has hard regs (e.g. `(set (reg:SI 4 a0) (mem ...))` for the q load), the RTL is post-allocation. So the copy `(set (reg:SI 4 a0) (reg/v:SI 73))` is not visible.

But the *preference* tells us it existed. Fine.

Now: how do I make the reload pick v1 instead of a0 for the address base? Hmm, alternatively: eliminate the reload copy entirely!

Idea: if the store's address pseudo is a *hard reg* — no.

Idea: what if the store address is `(plus (reg q) 2)` and MIPS folds the offset — the reload still needs the base in a reg. The reload copy `(set (reg a0) (reg q))` — MIPS's reload might instead compute `(set (reg a0) (plus (reg q) 2))`. Either way a copy into a0.

Which reg does reload pick? In reload.c, for a reload of a pseudo into a hard reg, the function `choose_as_reload_operand` picks based on the class and the "reload_inp" priority. For MIPS with -O2, reload regs are the "call-clobbered" ones? The reload pass allocates reload registers from a set determined by `reload_class` and the machine's `reloadable_regs`... In reload.c, `reload_inp[i].r` is chosen by `find_reg`/`choose_as_reload_operand` iterating over the class's REGS in the order of `reg_alloc_order`?

The specific choice of a0 ($4) over v1 ($3): reload.c's `choose_as_reload_operand`:
```
  for (i = 0; i < n; i++) { r = reg_class->regs[i]; if (ok) ... }
```
Hmm, but it uses `reload_reg->` and the "preferred" order comes from `regclass` + `regs_ever_live`. In reload.c there's a loop over `reload_regs` and it prefers regs that are not live.

Whatever the mechanism, how do I change it? Make a0 live at that point! In the join block, is a0 live? The call func_80178BF8() has no args → a0 is dead.

Hmm. What if the join block had a use of a0? E.g., if the code called a function with an argument (a0)... The target's join calls func_80178BF8() with no args. If I passed an argument, the code would change.

Hmm! But hold on: what about the *order* of the reloads? The reload pass allocates reload regs considering ALL reloads in the function. The a0 copy might be a *different* reload: e.g., the call argument copy for `func_8012BD14(ptr)` in the arms — that's `(set (reg:SI 4 a0) (reg/v:SI 74))` — a *call argument* copy, which in reload/expand is done in a hard reg (a0 is the standard arg reg) — that's not a reload, it's a "call arg copy" done by expand.

Hmm! Wait: maybe the preference "73 prefers 4" does NOT come from a reload copy of q into a0, but from the *call argument* copy! Look: in the arms, the call is `func_8012BD14(ptr)` where ptr = r74. The call-arg copy is `(set (reg:SI 4 a0) (reg/v:SI 74))` → preference for r74 = 4 ✓ ("74 preferences: 4").

But "73 preferences: 4" — r73 is q. Is there a call with q as an argument? NO...

Hmm, unless the numbering differs: in the .greg dump, the pseudo numbers are the same as the .rtl (72..85). r73 = q (defined at insn 43 and 74). r74 = ptr.

So "73 preferences: 4" — hmm.

OH WAIT. Maybe the preferences line in the dump means something different: it might list the *copies* of the pseudo, i.e. the pseudos that are copy-connected. Hmm, "4" could be a pseudo number 4? But pseudo 4 isn't in this function's range... The .rtl dump showed pseudos 72-85 only. So 4 must be a hard reg.

Hmm, let me look at GCC 2.7's global.c dump code. I recall:

```c
static void
dump_global_alloc (file)
     FILE *file;
{
  int i, j, k, n;
  int regno;

  n = n_global_allocnos;
  fprintf (file, "\n;; %d regs to allocate:", n);
  ...
  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      ...
      /* Print the conflicts. */
      ...
      /* Print the preferences: */
      for (j = 0; j < n; j++)
        if (reg_preferred[j] == regno) ...
```
Hmm, in that case "73 preferences: 4" would print the *pseudos* that prefer 73 → "4" would be a pseudo number. But pseudo 4 doesn't exist here.

Alternatively, the format could be ";; %d preferences: %d" = the pseudo and its preferred reg.

Since r73's preferred reg = 4 (a0) and r74's = 4 (a0): for r74 (ptr) the call-arg copy explains it. For r73 (q): the store's address reload into a0 explains it.

Hmm, but why would the reload pick a0 for the address? Because in reload.c, for an address reload, MIPS's reload might use a0 as a "scratch"? Hmm, MIPS defines TARGET_ADDRESS_REGS? Or maybe the reload copy is not for the address but for something else.

Whatever. The question: how to make the preference be v1 (3)?

Option: if a0 were occupied at the reload point, reload would pick another reg (maybe v1). What occupies a0 in the join block? Nothing.

Option: change the *order* of the two stores? The reload pass allocates reload regs in order; the first reload gets the preferred reg. If there were two address reloads (for the two stores) they'd share one reg (CSE) — hmm, actually the two stores have different offsets but the same base, so reload computes the base once.

Hmm, what if the two stores used *different* bases (e.g. via two pointer variables)? Then two reloads → two different regs (a0 and something else). The preference for q would still be a0 (the first).

Hmm. What if the pointer used in the store is a *different* pseudo than the one loaded? E.g.:

```
case 2: q = arg->unk64; qp = q; val = 3; break;
```
Then the store's address uses qp (global) and the reload copy would be into a0 → preference qp prefers 4 → qp → a0, and q → ? q is also global. Hmm, the target's store base is v1 = q's reg. If qp is a copy of q, the asm would have an extra move → different.

Let me test the hypothesis that the preference is what decides, by an experiment: add a dummy statement that makes the reload pick a different reg... hmm, hard.

ALTERNATIVE EXPERIMENT: check the .greg dump of the PINNED version to see if there's a "preferences" entry for the hard reg 3. In the pinned version: "74 preferences: 4" and no 73. So the pinned q has no preference (it's a hard reg).

Let me try a few things empirically that could shift the reload's reg choice:
(a) Make the *second* store use a different base spelling: e.g. `*(u16 *)(q + 0x34) = 0;` vs `((Unkstruct_801815AC_3 *)q)->unk34 = 0;` — same RTL.
(b) Reverse the order of the two stores → the reload order changes → maybe the first reload gets a0 and the second gets v1? But the base is the same pseudo → one reload.
(c) Add a third use of q?

Hmm.

Let me think about the reload pass more concretely. In GCC 2.7's reload.c, `reload_inp[i].out` is chosen by `choose_as_reload_operand (i, j)`, which does:

```c
  /* If we have a reload of a pseudo into a hard reg, ... */
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      if (! TEST_HARD_REG_BIT (regclass->regs, r) ...)
      ...
    }
```
and there's a preference for regs that are not "reload regs" of other insns, plus the `reload_reg` order.

Also reload.c has a notion: if the reload is for an address, the reg is a "scratch" — MIPS might have `TARGET_ADDRESS_REGS`? Hmm.

Wait, actually — maybe the copy into a0 is NOT a reload but the *expand* pass's handling of the store's address on MIPS: MIPS's patterns for `sh` with a memory operand require the address in a register, and `mips.md` has a pattern that computes the address into a "scratch" register chosen by the machine description (e.g. `%v0`?). Hmm.

The fact that it's a0 ($4) and MIPS's arg regs are a0-a3 → maybe expand chose a0 for the address because the address pseudo's reg...

Let me test the hypothesis empirically with a cheap experiment: make the store base be a pseudo that is *also* used as a call argument elsewhere (so the reload might pick a different reg)... meh.

BETTER IDEA: let me look at the .greg dump RTL of the *lever-free* version again for the join block, and check whether the address base is a0 in the final asm: yes, `sh v0,2(a0)`.

Experiment: what if the store were `((Unkstruct_801815AC_3 *)q)->unk2 = val;` where q is a *pointer type* (c4) — scored 4 too. Let me look at c4's asm to see if the base reg changed (maybe still a0).

Let me run a batch of experiments and check where the base ends up. Actually, all score 4, so the base is a0 in all.

NEW IDEA: What if the store's address base is not a pseudo but a *hard reg* because the pointer is copied to a hard reg earlier? Hmm.

NEW IDEA 2: Since the preference is "73 prefers 4" and GCC honors the preference, maybe I can create a SECOND copy of q into a different hard reg, making the preference list have multiple entries and letting global_alloc pick... no, the preference is per-pseudo (one reg).

Hmm, but what if the copy were into v1 instead? Then "73 prefers 3" → q → v1 (if not blocked). How to get a copy of q into v1?

What if q is passed to a function as an argument in a position that maps to... no, MIPS args are a0-a3.

What if q is assigned to a variable declared with a specific... no.

What if the store is done through a *pointer cast* such that MIPS's expand picks a different reg? Hmm.

Let me look at the problem from the "what does the target do" angle once more. In the target, the store base is v1 = the hard reg $3 (the pin). So the pin IS the answer for the original game. The question is whether a lever-free C body can produce a store base in $3 with a *pseudo* pointer.

Since the reload copy chooses a0, and the target needs v1...

What if the *store* used a base that's a hard reg because the pointer was copied into a hard reg for another reason? E.g., if the pointer were ALSO the argument to a call in the join block, it'd be copied to a0 (not v1).

Hmm, what if there were a call in the join block taking the pointer as an argument? The target's join calls func_80178BF8() with no args. But the C source could pass an argument that the compiler eliminates? No, it can't eliminate a call arg.

OK. Let me consider: maybe the wall is real but the "best" score could be improved from 4 to something smaller? The score is the number of differing instructions (masked diff). Currently 4 (the 4 q uses in a0 vs v1). Could a variant produce a smaller diff? E.g., if q were in a0 for the loads but v1 for the stores? That'd still be 4.

Alternatively, maybe a variant could produce a *different* register assignment that's closer: e.g. if q were in v0 (2 differences? no, still 4 sites).

So the best is 4. The wall tag: something like "global-alloc-reload-pref" — the q pseudo is global (2 defs) and global_alloc gives it $4 because the reload's address copy creates the a0 preference; $3 is unavailable (block-granular: the local 0x9000/slt pseudos hold $3 in the arm blocks — hmm, but the q load is in a different block...).

Hmm, wait. Now I need to re-examine: is v1 actually blocked for r73? Let me test: if the preference were absent, would r73 get v1? The order of globals: r73 (q) first. Available: v0 (blocked? the local call result uses v0 in the arm blocks; the q load is in block 40 which is after the branch; the call result v0 is live in the pre-branch block, not in block 40 → maybe not blocked!), v1 (the local const/slt are in the pre-branch blocks too → maybe not blocked in block 40).

Hmm! So the local const/slt are in the *pre-branch* blocks (19 and 50), while q's def is in blocks 40 and 71. The global q is live in blocks 40, 71, 98. So the locals using v1 are in blocks 19, 50 — disjoint! So v1 might NOT be blocked for the global q!

Then the only reason q got a0 is the PREFERENCE (73 prefers 4).

If that's true, the lever is to make the reload's copy go into v1 instead of a0! Then "73 prefers 3" → q → v1 → MATCH!

But hold on: would the local const/slt in the pre-branch blocks then conflict with the global q in v1? The global q is live in blocks 40,71,98; the locals in 19,50 — disjoint, so no conflict.

But there's a subtlety: in GCC 2.7, the conflict computation for a hard reg vs a global pseudo is done via `global_conflict_sets` — the .greg dump showed "73 conflicts: 73 76 29" (no 3=v1) — CONFIRMING that v1 does NOT conflict with q! Similarly "76 conflicts: 73 76 29" (val doesn't conflict with v1 either).

So v1 was NOT blocked for q. The preference decided it.

So: how do I get the reload's address copy to go into v1 ($3) instead of a0 ($4)?

Ideas:
1. Make a0 unavailable at the reload point → the reload picks the next reg. What if the pointer is ALSO used as a call argument somewhere in the join block? no.

2. Change the *order* of the reloads: if the q address reload happens after another reload that takes a0, then q's reload takes the next reg (maybe v1). Hmm, what other reload is there? The call argument copy for func_8012BD14 (a0) — but that's in the arms, and the reload pass allocates regs globally per function... The call-arg copy `(set (reg:SI 4 a0) (reg/v:SI 74))` is done by expand (not reload) and it's a *hard* reg assignment — expand's call-arg copies use the standard arg regs. So a0 is used there but that's not a "reload reg".

Hmm, but reload.c's `reload_inp` allocation considers the whole function: the reload regs must not conflict with other reloads. So the q address reload is the only reload → it gets the most preferred reg = a0.

3. What determines the preference order? In reload.c, `choose_as_reload_operand` iterates over the class's registers in the order given by `reg_class->regs` (for GR_REGS on MIPS: probably $2,$3,$4,$5,... or with a specific order) and picks the first that is "ok" (not live, not a reload reg of another insn). If GR_REGS' order is $2(v0),$3(v1),$4(a0),..., then why a0 and not v0/v1? Because v0 and v1 might be "not ok": v0 is the call result reg (live at the reload point? the reload is in the join block after the last call → v0 is dead). Hmm, but reload.c's `reload_inp` allocation avoids regs that are "live" in the insn's block (regs_ever_live?).

Actually, in reload.c, `reload_inp[i].out` selection uses `reload_reg` and the "reg not live at that point" check via `regs_ever_live` / `reg_occupancy`. In GCC 2.7, reload.c's choose_as_reload_operand:

```c
  /* Prefer a register that is not used in the insn... */
  ...
  for (i = 0; i < n; i++)
    {
      r = regclass->regs[i];
      if (reload_inp[j].r == r) ...
      if (reg_ever_live ...) 
```
Hmm.

Actually, in GCC 2.7 reload.c, the function is:

```c
static int
choose_as_reload_operand (i, j)
{
  ...
  /* Try to find a register that is not live at the insn ... */
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      if (! TEST_HARD_REG_BIT (regclass->regs, r))
	continue;
      if (reload_inp[j].r == r) continue;
      if (reg_occupied[j] ...) 
      ...
      /* Avoid registers which are live at that point */
      if (! regs_ever_live ...) 
```
I recall the loop tries the class's regs in order, and picks the first that is not "occupied" by another reload and not live. MIPS's GR_REGS order in mips.h: `MIPS_GENERAL_REGS`? The reg order for GR_REGS in GCC 2.7 mips.h is:

```
#define MIPS_GENERAL_REGS \
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 }
```
Hmm, that's all regs. But the *allocatable* order is defined by `REG_ALLOC_ORDER` in mips.h:

I recall MIPS's REG_ALLOC_ORDER is:
```
#define REG_ALLOC_ORDER \
  { 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 6, 7 }
```
Hmm. But reload.c doesn't use REG_ALLOC_ORDER; it uses `regclass->regs` order? In reload.c, `choose_as_reload_operand` iterates over `regclass->regs` — hmm, but there's also `reload_reg->` ordering by `reload_priority`.

OK, empirics again. Practical experiments to shift the reload's choice:
(E1) Make the pointer's address used in a *second* store with a different base spelling so that two reloads occur and the second picks a different reg — but the preference for q is set by the copy; if the first copy is into a0, the preference stays a0.

Hmm, what if the store base reload happens for a *different* pseudo that is then copied to q?

(E2) What if the store is `*(u16 *)q = ...`? Hmm, q is s32; `*(u16 *)q` → the address is the pseudo q with no offset → reload copy (set (reg a0) (reg q)) → same.

(E3) What if the store's address is a *constant* + the pseudo, where the constant is 0? Same.

(E4) Add a use of q in the join block that forces a copy into a different reg? Hmm.

(E5) **Make the pointer value also be an operand of a comparison or arithmetic in the join**, e.g. `if (q == 0) ...` — no, changes code.

(E6) What if the *stores* were to a struct field via a *different pointer variable* that is a copy of q made in the arm? Then the store base reload copies that pseudo into a0 → the preference is on that pseudo. And q (global) would be allocated... hmm, the copy pseudo would be global too and get a0. The asm would have an extra move → mismatch.

Hmm.

(E7) What if the *load* of q in the arm is written so that the result is used directly as the address...

Let me think about the *actual* asm of the target again: `lw v1,100(s0)` then `sh v0,2(v1)`. The base v1 = q. In the lever-free version, the base a0 = q. The difference is only which hard reg holds the pointer.

What if the pointer were held in a *callee-saved* reg? The target has v1. no.

OK, let me now consider the possibility that the preference is not the deciding factor but rather that the *first* free reg in the class order is a0 for other reasons. Test: create a variant where the q pseudo has NO preference (e.g., by making the store's address not need a reload copy). When would the address not need a reload? If the base is already a hard reg...

Hmm! What if the pointer is loaded into a variable that is ALSO used in a way that forces it into a hard reg? no.

What about making the store's address expression involve a *hard reg* directly? E.g. `((Unkstruct_801815AC_3 *)arg)->unk64` — no.

Hmm, let me look at this from yet another angle: what if the pointer variable q is declared as `u8 *` and the stores are `q[2] = ...`? Then the address is (plus (reg q) 2) — same.

What if the stores are done on a *u16* pointer: `u16 *qp; qp = (u16 *)q; qp[1] = val; qp[0x1A] = 0;` → address (plus (reg qp) 2) and (plus (reg qp) 0x34) → 2 reloads? Reload would CSE the base? The two addresses have different offsets, so reload computes two different addresses: (plus qp 2) and (plus qp 0x34) — but MIPS folds the offset into the instruction, so reload just needs the base in a reg → one copy. Hmm, but the *pseudo* is qp, not q → the preference is on qp → qp → a0 and q → ? (also global). The asm would show an extra move (qp = q) → mismatch.

Hmm.

OK, radical: maybe I can influence the reload's reg choice by changing the *number of arguments* to the call in the join? no.

Let me try a completely different lever: what if the function had an extra local variable that occupies a0 in the join block? E.g. a local variable that's live in the join block and gets a0 → then the reload would pick another reg (v1?).

But an extra local would change the code (unless it's dead/optimized away).

Hmm, what about the call `func_80178BF8()`? If it took an argument, a0 would be occupied in the join block... but that changes the code (the target's call has no arg). Hmm, but what if the argument is a *constant*? `func_80178BF8(0)`? Then the asm would have `li a0,0` before the call → different insns → score.

Hmm! Unless... the call's arg copy is folded? No.

What about a *variable* that's dead? no.

OK, let me look at the reload pass's actual choice by testing: does the *order* of the stores matter? Let me try swapping the two stores (unk34=0 first, then unk2=val). The target has unk2 first. That changes the asm order → mismatch, but it tells me whether the reload reg changes.

Better test: let me check if the preference is really what decides, by an experiment that removes the preference: what if the pointer is used in the join ONLY as an address (which is the case)...

Hmm, alternatively let me test the hypothesis "the global q's reg is decided by the reload-copy preference" by looking at a variant where the pointer's address in the store is offset 0 vs 2, or where the pointer is used in two different addresses. Let me look at the *pinned* .greg: r74 prefers 4 (a0) and got a0 — that's the call-arg copy. And in the lever-free version, r74 (ptr) also prefers 4 → a0 ✓. And r73 (q) prefers 4 → a0.

So both q and ptr get a0 because of a0-preferences. If q's preference were 3 (v1), q would get v1 (assuming no conflict).

Now: how does the reload pick a0 for the q address? Because reload picks the first available reg in the class order, and for MIPS the class order might be a0 first (MIPS's REG_ALLOC_ORDER starts with... hmm).

Wait — actually! Maybe the a0 copy for q's address is NOT a reload but an *expand*-generated copy. In MIPS, the store `sh` with a symbolic/offset address: expand's "move_operand" would need the address in a register; the machine description's output pattern for `sh` is:
```
(define_insn "sh"
  [(set (mem:HI (match_operand:HI 0 "address_operand" ...))
        (match_operand:HI 1 "register_operand" ...))]
```
and the address_operand can be a "plus:HI (register) (const_int)" → the address is computed by expand into a register (a "move") — expand would use a scratch register chosen by... the pseudo-reg allocation for the address pseudo. Hmm.

The address in the RTL after expand is `(plus:SI (reg r73) 2)` — the "plus" with a constant offset. Expand's `expand_expr` for a PLUS with a constant → it creates a new pseudo for the sum?? But then the final asm folds the offset. Hmm, MIPS has a pattern for `sh` with `(plus (reg) (const_int))` — "address_operand" allows that. So no extra pseudo.

Then the reload: the operand is a memory with a non-constant address → reload must put the address in a register → reload_inp for the address → choose_as_reload_operand picks a reg.

In GCC 2.7's reload.c, `choose_as_reload_operand`:
```c
  /* Try to find a reload register that is not live at the insn ... */
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      ...
      /* Avoid registers which are call-clobbered if the reload is across a call... */
```
Hmm, there's a known GCC behavior: reload prefers to use the same reg as the "reload_inp" of the insn's other operand, and it avoids regs that are live.

Honestly, let me just try a bunch of variants and observe the base reg. The empirical loop is ~1s per variant. Let me try:

V1: `((Unkstruct_801815AC_3 *)q)->unk34 = 0;` first, then unk2 = val. (order swap)
V2: pointer reuse with u16*: `u16 *qp = (u16 *)q; qp[1] = val; qp[0x1A] = 0;`
V3: q declared as `u8 *qp` with `qp[2] = val; qp[0x34] = 0;`
V4: store via `*(u16 *)(q + 2) = val; *(u16 *)(q + 0x34) = 0;`
V5: the whole switch replaced by if/else (different dispatch, probably worse)
V6: q as a `void *`?
V7: Make the *ptr* variable the one stored (i.e. swap: store to ptr instead of q) — no, semantics.

Hmm, V2/V3 change the pseudo structure (extra copy) → likely an extra move insn.

Let me think about which is most likely to shift the reload's reg: making the *address* expression a "plus" with a constant vs a plain reg. If the address is just the pseudo (offset 0), maybe reload uses a different path. In the target, one store has offset 2 and the other 0x34 — both non-zero.

Hmm, what if the store offset were 0 for one of them? Not possible (unk2 is at 2).

What about making the *base* a plus of two pseudos? e.g. `q2 = q + 0;`? The "init at decl"/"pointer reuse" catalog mentions "identity address spellings do NOT count as a crack" — so the project already knows this trick doesn't work (the brief says: identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack). Interesting! So `q2 = q + 0` style is disallowed.

Hmm, that note ("identity address spellings") suggests previous agents tried making the address a computed pseudo — and it doesn't count as a crack (and probably doesn't change the score).

OK. Let me now step back and consider the time budget. I've used ~20 min on item 1. The task wants 20-30 min per item and ≥30 tries for a wall. I have 3 items; total budget maybe 1.5-2 hours. Let me be efficient: run a batch of ~10 variants per item, and for item 1, if the preference theory holds, I might find a working lever.

Let me first test the preference theory more directly: I'll write a variant where the pointer is stored via a *pointer-typed* variable that is directly loaded in the arm:

```
Unkstruct_801815AC_3 *qp;
...
qp = (Unkstruct_801815AC_3 *)arg->unk64;
...
qp->unk2 = val; qp->unk34 = 0;
```
That's c4 (score 4). Let me look at c4's asm to see if the base is a0 or something else. If c4's base is still a0, then the reload picks a0 regardless.

Let me also try: what if the pointer is used in the join block in a way that requires the reg to be copied to a *specific* reg...

Actually — HOLD ON. Big idea: what if the *store* is done through a pointer that is ALSO an argument to the call in the join block? Then the copy for the call arg would be into a0 (arg reg) — same.

Another big idea: what if the *q* value is copied into a callee-saved register explicitly by the source (e.g. `s32 qq = q;` — no, that's a copy pseudo).

Hmm, hmm. What about the ordering: the reload allocates its reg preferring regs NOT used elsewhere in the function ("reload regs are chosen to avoid conflicts"). The load `q = arg->unk64` in the arms: the load's destination is a pseudo (no reload needed). The store's address needs a reload.

What if there were ANOTHER reload in the function that would take a0 first, and the q address reload takes the next reg (v1)? For instance, the call `func_8012BD14(ptr)` — the arg copy is to a0 but that's expand's doing, not a reload. Hmm, but in reload, a call's arg register is "occupied" — reload's `reg_occupied` marks a0 as occupied at the call insn, so a reload at the call can't use a0. But our reload is in the join block, after the call.

What if the join block's reload came AFTER another reload in the same block? The only other reload in the join block would be... none.

Hmm, what about the *first* store's address and the second store's address: both use q → the same reload.

What if the two stores used *different* pointers (e.g. q and q+2)? Then two reloads: the first gets a0, the second gets... the second address is (plus (reg q) 2) — hmm, same base.

OK, let me try the empirical route with a batch of variants. Let me write them.

Actually, one more important idea!! What about the *slt* constant: in the target, the const 0x9000 is in v1. In the lever-free version, the const is ALSO in v1 (local alloc). Both fine.

And what about the *value* (val) in v0? In the lever-free version, r76 (val) → v0 ✓ (target: val in v0 ✓).

And r83 (the switch value) → v1 ✓ (target: st in v1 ✓).

So EVERYTHING matches except q's reg. The global allocation order is 73(q) 74(ptr) 76(val) 83(st) 72(arg):
- q → a0 (preference), ptr → a0 (preference), val → v0, st → v1, arg → s0.

In the pinned version: 74(val?) 76 83 72 → hmm.

So the only problem: q prefers a0.

Let me test the theory by trying to make the reload's reg choice different. IDEA: what if the pointer's store used a *negative* offset or a *double-word* alignment? no.

IDEA: What if the base of the store is the *same* pseudo as something else that's in v1? E.g. if the pointer q were the SAME pseudo as the switch value st (no).

IDEA: What if the *call* `func_80178BF8()` were called with the pointer as an argument? Then a0 would be occupied at the call, and the reload (which happens before the call, in the same block) would pick a different reg (v1?). But the call with an arg changes the asm (li a0, ... + jal). Hmm, unless the arg is the pointer itself: `func_80178BF8(q)` — hmm, func_80178BF8's signature is void(void) presumably; passing an arg would be a compile error or a mismatch.

Hmm! But what about a DIFFERENT call? No, we can't add calls.

IDEA: What if the *order* of the two stores is such that the first store's address reload is in a block where a0 is occupied? Hmm, the join block: a0 is dead.

OK OK. Let me think about the reload's reg choice in GCC 2.7 reload.c. I'll reason from the code I remember:

```c
/* Choose a reload register for the reload INPUT number I... */
static int
choose_as_reload_operand (i, j)
{
  int r, reg;
  ...
  /* Try to find a reload reg that is not live ... */
  if (regclass_size == 0) return 0;
  ...
  /* Compute the number of hard regs in the class. */
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      if (! TEST_HARD_REG_BIT (regclass->regs, r)) continue;
      if (reload_inp[j].r == r) continue;
      ...
      /* If the register is not live at the reload point, use it. */
      if (! live_at_insn) ...
```
Hmm, GCC 2.7's reload.c actually does:

```c
  /* Determine which regs are free at the insn. */
  ...
  for (i = 0; i < n; i++) {
      r = regclass->regs[i];
      if (reload_inp[j].r == r) continue;
      if (reg_occupied[j] ... )
      if (REGNO (SET_SRC (PATTERN (insn))) == r) ... 
```
and then it prefers a reg whose "reload_inp" doesn't conflict.

The class order for GR_REGS on MIPS in GCC 2.7: `mips.h` has:
```
#define MIPS_GENERAL_REGS ...
```
and the regclass for GR_REGS is defined in mips.md:
```
(define_reg_class "general" "GENERAL_REGS"
  (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31)
  (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31))
```
Hmm. If the class order were 0,1,2,3,... then the first free would be v0 ($2) — but v0 is live? At the join block, v0 is dead. Hmm, but reload wouldn't use v0 because... hmm.

Actually! In reload.c, when the reload is for an *address* (mem operand), the reload reg must not be a register that's "used" by the insn. And crucially, in GCC 2.7's reload, `reload_inp[j].r` for an address gets a reg from the "reload class" but the *choice* is influenced by `reload_reg` availability. There's also a rule: "if the reload is in a block after a call, prefer a call-clobbered reg"...

I recall GCC's reload.c `choose_as_reload_operand` has this important part:

```c
      /* If this is a reload of a pseudo that is not live across a call, 
         and the register is used by the insn... */
```
and
```c
  /* Prefer a register that is not used in the insn */
```

You know what? Let me just try empirically: make the join block have a0 live! How? The *call* `func_80178BF8()` — no args. Hmm.

What about the ORDER of the reload vs the call: the reload (address) happens BEFORE the call in the block. The call clobbers a0-a3, v0-v1. Hmm.

What if the store came AFTER the call? The target's order: `sh v0,2(v1); jal func_80178BF8 (delay: sh zero,52(v1))`. So the first store is before the call, the second is in the delay slot. If the source order were reversed (unk34 first, then unk2), the reload for the first store would be after the call → and the call clobbers a0 → so the reload would pick a different reg! Interesting!! But the store order change → the asm order changes → score ≠ 0? Let's see: the target has `sh v0,2(v1)` then `jal` then `sh zero,52(v1)`. If the source stores unk34 first, the asm would be `sh zero,52(v1); jal; sh v0,2(v1)` → the diff would be 2 instructions (mismatch) but maybe fewer than 4? The score might be 2 or 3. Hmm, interesting but not a MATCH.

Hmm, but wait: it might reveal the mechanism. If after the call the reload picks v1 → then the base would be v1 and the *other* store (before the call) would use a0... The diff would then be: `sh zero,52(v0)` vs `sh v0,2(v1)` — mismatched.

Hmm, so what if the source order is unchanged but the reload is forced after the call? Not possible.

OK, let me try yet another angle: maybe the reload's reg choice is influenced by which regs are "occupied" by OTHER reloads *earlier in the function* — reload.c allocates reload regs in order of the reload inputs, and the *first* reload in the function gets the most preferred reg. If there were another reload earlier (e.g. a reload of a value needed by the call), it might take a0 and our q address would get the next reg (v1?).

What reload could exist earlier? E.g., if the call's argument needed a reload (a pseudo arg → a0 is the arg reg; that's expand's copy, not a reload).

Hmm! What if a value used in the arm needed a reload? Like `if (func_8012BD14(ptr) > 0x9000)` — the comparison constant 36864 is a pseudo (r78) → local_alloc gave it v1 (not a reload). Hmm.

OK, empirical batch time. Let me write ~8 variants and look at the asm of the best ones. Let me be systematic: variants that change the *store* structure:

w1: store order swapped (unk34 first).
w2: u16* pointer reuse.
w3: u8* pointer reuse with byte stores: `qp[2] = (u8)val;` — hmm, unk2 is u16; storing a byte then a byte? `qp[2] = val & 0xff; qp[3] = val >> 8;` → different insns. no.
w4: stores via `*(u16 *)(q + 2) = val;`
w5: q as `void *`? then casts.
w6: the two stores written as a struct assignment? no.

Let me also try:
w7: `q` used in a condition in the join: no.

And a completely different idea:
w8: make the *value* global and the *pointer* local by moving the stores into the arms — but with the stores written so that gcc's crossjumping CANNOT merge them, yet the final asm still has one store pair in the join? Impossible.

Hmm, w9: What if the arms assign to a global *pointer* variable that is also used in the join? That's q itself.

Let me look at this from the "what does the target's asm require" angle once more:
- `lw v1,100(s0)` — q's load in v1. The load's destination is q's reg.
- `sh v0,2(v1)` — the store's base is v1 (the SAME reg as q).

In the lever-free version, both the load's destination and the store's base are a0 (the same reg). So the reload copy and the load agree. The only difference: a0 vs v1.

Since the load's destination is the pseudo q and the store's base is the pseudo q, the *reload* is what pins the base to a hard reg, and the preference then assigns q to that reg.

So: if the reload picked v1, everything would match. The reload picked a0.

Now: in the PINNED version, there's no reload (the base is the hard reg $3) — and the load writes directly to $3.

Hmm, so what if the pointer were a hard reg for a different reason — e.g., if the pointer were the result of a call (a call result is in v0) — no, that changes the code.

Hmm, what if the pointer value were *spilled* to the stack and reloaded? no.

Let me try to find what makes reload pick v1. In GCC 2.7's reload.c, I now recall the function:

```c
/* Choose a reload register for the reload INPUT number I... 
   J is the reload input we are considering.  */
static int
choose_as_reload_operand (i, j)
     int i, j;
{
  int r;
  int reg = reload_inp[j].r;
  ...
  /* We are looking for a register to hold the reload.  */
  ...
  if (regclass_size == 0)
    return 0;
  ...
  /* Find the register to use.  */
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      if (! TEST_HARD_REG_BIT (regclass->regs, r))
	continue;
      if (reload_inp[j].r == r)
	continue;
      if (reg_occupied[j] ...)
	...
      /* Don't use a register that is live at this point. */
      ...
      /* Prefer a register that is not a call-clobbered register if the reload
	 is not across a call... */
```
I honestly recall that GCC's reload has this heuristic: it prefers a register that is NOT live at the reload point, and among those, the first in the class order that isn't needed by another reload.

MIPS's GR_REGS class order: in mips.md, `(define_reg_class "general" "GENERAL_REGS" (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31) ...)`. Hmm, if the order were 0,1,2,3,4..., the first candidate would be $0 (zero) — not allocatable; $1 (at) — not; $2 (v0) — but v0 is live? At the join block, the store's insn is `sh v0,2(base)` — v0 holds val! So v0 is live at that point → skip. Then $3 (v1) — is v1 live at that point? Hmm, in the lever-free version at the join: v1 is used by the switch value (dead by then) — so v1 should be free! But reload picked a0 ($4). Hmm, so v1 must have been excluded for another reason.

Possibly: reload avoids regs that are "reload regs" of other insns, or regs that are live *somewhere* in the function (regs_ever_live). v1 is used by the const 0x9000 and the switch value → regs_ever_live includes v1. But a0 is also used (the call arg) → also ever-live. Hmm.

Maybe reload's rule: don't use a reg that is live at the *start* of the block or "call-clobbered across a call"? Hmm.

OK, enough theorizing — let me get DATA. I'll look at the reload decisions by dumping the RTL after reload: the .greg dump's RTL is post-reload (global alloc happens after reload). But the .greg dump's RTL is post-allocation. Hmm. What about the .jump dump (.i.jump) — the jump pass runs after allocation. The .sched dumps? The order of passes in gcc 2.7: flow, combine, expand, jump, ..., reload, ..., global/local alloc, ..., sched.

So the .jump dump is BEFORE reload (jump runs before reload? In gcc 2.7: `jump_optimize` runs in `jump` pass which is after `expand` and before `reload`? The pass order: ... "jump" (after "expand"), "loop", "cse2", "flow2", "reload", "global+local alloc", "sched"...

So the .jump dump shows the RTL before reload. And the .greg dump shows after reload+alloc.

To see the post-reload RTL, I'd want a dump between reload and global alloc. There's no such dump flag in 2.7 (I think). But the .greg dump's RTL is post-alloc.

Hmm, but the *preference* tells me the copy was to a0. Fine.

Let me try the experiment: swap the store order and see if the base reg changes (and what the score is). Also try the u16* pointer reuse. Let me write a batch.

Actually, WAIT. A much better idea!!! What if we make the *value* (val) and the *pointer* swap roles in the join, i.e. what if the pointer is NOT used in the join at all, and the join's stores use a *pointer expression* computed from...

Hmm, no. Let me think about "what if the store's base pseudo is a DIFFERENT global that has a v1 preference"?

The preference comes from a copy into a hard reg. Which hard regs can a copy target? a0-a3 (call args), v0 (call result), or any hard reg via expand.

What if the pointer q were passed to a *call* as an argument? Then expand would copy it into a0 (the arg reg) → preference a0. Not v1.

Hmm, what if q were used in a *division* or something needing a specific reg? no.

What if the source had `q = q;`? no (identity launder, disallowed anyway).

OK, so what hard-reg copy could target v1? A copy into v1 happens when... hmm, the switch value st is in v1 (lhu). What if the *pointer* were copied into the same pseudo as st? Ha.

Alternatively: the *load* of q could be made to write into a hard reg if the load's destination is a hard reg — that's the pin.

Hmm, hmm. Let me look at the problem from the "the target's q is in $3" angle: the pin says `register s32 q __asm__("$3")`. In the original game's source, the code presumably was `register s32 q __asm__("$3")`? Hmm, no: the pin was ADDED by the project to match the target asm. The original PSX source was probably plain C, and the target asm has q in $3 because of the original compiler's allocation. The project re-created it with a pin. The question: can plain C reproduce it? Maybe the original source was different from the current src! E.g. maybe the original had the pointer as a `u16 *` or the struct field access spelled differently, leading to a different RTL shape.

Hmm! That's a thought: the current src is the project's reconstruction; the original game source might have had e.g. `q` as an `int` with a different usage pattern.

Let me look at the target asm once more for clues about the original source:

```
 3fb8 lw a0,100(s0)     ; ptr = arg->unk64
 3fc0 lhu v1,2(a0)      ; st = ptr->unk2
 ...
 3ff0 lw v1,100(s0)     ; q = arg->unk64
 401c sh v0,2(v1)       ; q->unk2 = val
 4024 sh zero,52(v1)    ; q->unk34 = 0
```

Hmm, `sh v0,2(v1)` — v1 holds the base. And `li v0,3`/`li v0,4` for the value.

What if the original source stored the value as a *u16*? Same.

What if the original source's `q` was `s32` but the *stores* were done via a `u16 *`? Then the base would still be a reg.

Hmm, what if the original source's q was an `Unkstruct *` (pointer type)? Then the load `lw v1,100(s0)` and the stores `sh v0,2(v1)` — the same. And the register allocation for a POINTER global pseudo: pointers have higher priority in GCC's allocation (they're "address" pseudos)?! In GCC, pointer pseudos are still normal pseudos. Hmm, but there's a subtlety: GCC's local/global allocation treats address pseudos normally, but *reload* of an address into a reg is the same.

Hmm, c4 (pointer type) scored 4. Let me look at c4's asm: does the base stay a0?

Let me now run a batch of variants and inspect. Let me write them via a python script for compactness.
