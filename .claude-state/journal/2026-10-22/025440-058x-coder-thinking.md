---
ts: 2026-10-22T08:54:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Jmc1Lvnvoytg4kGfCnYe
---
The join block in the .lreg dump (pre-local-alloc) has NO copy of r73 into a0. The stores use the pseudo directly.

So the "73 preferences: 4" must come from something else. Hmm! Maybe the dump's "preferences" line is NOT about a0 but about the allocno 4 — hmm, but 4 isn't in the alloc list.

Hmm, wait. Maybe the dump prints the "copy preferences" as pairs: ";; %d preferences: %d" where the second number is the *preferred allocno*? Since the allocnos are 72,73,74,76,83 and the hard reg 4 — hmm.

Hmm, hold on! Maybe the number is a REGNO (pseudo number) that is a *hard reg* (4 = a0). The preference mechanism (global.c set_preference) is called from `record_preferences`? Hmm.

Let me look at GCC 2.7's global.c more carefully from memory:

```c
/* Set the preference for REGNO to be PREFERRED_REGNO... */
static void
set_preference (regno, preferred_regno)
{
  ...
}
```
called from `global_alloc`:
```c
  /* Process all the insns in the function, looking for copies to set preferences. */
  FOR_EACH_INSN (insn)
    {
      ...
      if (GET_CODE (PATTERN (insn)) == SET
	  && GET_CODE (SET_SRC (PATTERN (insn))) == REG
	  && GET_CODE (SET_DEST (PATTERN (insn))) == REG)
	{
	  r1 = REGNO (SET_SRC (PATTERN (insn)));
	  r2 = REGNO (SET_DEST (PATTERN (insn)));
	  if (r1 != r2 && r1 < FIRST_PSEUDO_REGISTER && r2 >= FIRST_PSEUDO_REGISTER)
	    {
	      /* Copy from a hard reg to a pseudo: the pseudo prefers the hard reg. */
	      set_preference (r2, r1);
	    }
	  ...
	}
    }
```
Hmm, in our RTL, is there a copy from a HARD reg to a pseudo? Looking at the join block: no. In the arms: `(set (reg:SI 4 a0) (reg/v:SI 74))` — that's from a pseudo (74) to a hard reg (a0). The reverse direction: "copy from hard reg to pseudo" — hmm, the pattern is (set DEST=SRC?) Let me be careful: in RTL, (set DEST VALUE). So insn 22: DEST = (reg:SI 4 a0), VALUE = (reg/v:SI 74) → a copy FROM pseudo 74 TO hard reg a0. In GCC's set_preference terms: r1 = REGNO(SET_SRC) = 74 (pseudo), r2 = REGNO(SET_DEST) = 4 (hard). The code above: `if (r1 < FIRST_PSEUDO_REGISTER && r2 >= FIRST_PSEUDO_REGISTER)` → r1=74 is a pseudo → no. The other direction: `if (r1 >= FIRST_PSEUDO_REGISTER && r2 < FIRST_PSEUDO_REGISTER) set_preference (r1, r2)` → r1=74 (pseudo), r2=4 (hard) → set_preference(74, 4) → pseudo 74 prefers hard reg 4 ✓✓ — that matches "74 preferences: 4"!

So for "73 preferences: 4", there must be a copy (set (reg:SI 4 a0) (reg/v:SI 73)) somewhere in the RTL at global_alloc time. But the .lreg dump (pre-local-alloc) doesn't show one...

UNLESS the copy is created by local_alloc! Local alloc's "combine_regs" coalescing: it can merge a copy's src/dest. Hmm, that removes copies, not adds.

Hmm, but local_alloc ALSO can create copies? Hmm.

OR: the copy is created by *sched1* (which runs before local_alloc)? The .lreg dump is printed at the start of local_alloc, so a copy created by sched1 would appear. Not there.

Hmm! What about the "reload" pass? The doc says reload runs AFTER global_alloc. Hmm, but in GCC 2.7 the actual order is: ... → sched → local_alloc → global_alloc → reload? Let me check the doc's pass order: "flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr". OK so reload after global alloc.

Hmm, so where's the copy?

Hmm, maybe the "preferences" print is something else entirely: maybe it prints the *hard regs that the allocno prefers* derived from `reg_preferred[]`, which is set by set_preference as above. Hmm.

Wait — maybe I should look at the .greg dump of the PINNED version again: "74 preferences: 4" and the pinned RTL has the same call-arg copy (set (reg:SI 4 a0) (reg/v:SI 74)). Hmm, but in the pinned version, r74 might be a different pseudo (the val?). Let me check the pinned .rtl: in the pinned version, the q is hard $3, so the pseudo numbering shifts: r72=arg, r73=ptr?, r74=val?, ...

In the pinned version's .greg: "74 conflicts: 72 74 83 2 29; 74 preferences: 4" and "76 conflicts: 76 3 29" and "83 conflicts: 72 74 83 2 29".

Hmm, in the pinned version, the "preferences: 4" is on r74. If in the pinned version r74 = the ptr (the call-arg copy) → consistent with the lever-free version's r74 = ptr ✓. And the pinned version has no "73 preferences" line — because in the pinned version r73 = the val (no copy) or something.

So in the lever-free version, r73 = q and it has a preference for a0. And r74 = ptr with a preference for a0 (the call-arg copy ✓).

So there are TWO copies into a0 in the lever-free version: one for ptr (call arg) and one for q (???).

The q copy into a0... hmm! What if it's the *address* copy created by local_alloc? Hmm.

Hmm, hold on: what about the *second* call in the function: `func_80178BF8()` — no args.

Hmm, what about `(set (reg:SI 4 a0) (reg/v:SI 73))` — maybe it's created by the *reload* pass for the store's address, and reload runs BEFORE global_alloc in gcc 2.7! Let me check: GCC 2.7's toplev.c order:

```
  /* Perform the first half of the "front end" ... */
  ...
  cse ();           /* cse1 */
  ...
  loop ();          /* loop optimization */
  ...
  jump ();          /* optimize jumps */
  cse2 ();          /* cse2 */
  flow2 ();         /* flow analysis */
  combine ();       /* combine */
  sched ();         /* schedule */
  local_alloc ();   /* local register allocation */
  global_alloc ();  /* global register allocation */
  reload ();        /* reload */
  ...
```
Hmm, in GCC 2.7, `reload` is called from `allocate()`? No... In GCC 2.7's toplev.c:

```c
  /* Do the register allocation.  */
  ...
  dump_flow_info (0);
  /* Local register allocation.  */
  local_alloc ();
  /* Global register allocation.  */
  global_alloc ();
  ...
```
and reload happens inside `allocate()`? In GCC 2.7, `reload()` is called from `toplev` after `allocate()`? The doc in this project says: "flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr". So reload is after global_alloc. OK.

So the copy into a0 for q must exist at global_alloc time, i.e. it was created by expand/sched1/local_alloc. The .lreg dump (printed at local_alloc's start? or end?) — hmm! Maybe the .lreg dump is printed at the END of local_alloc, after local allocation has created copies. Hmm, in the .lreg RTL, the local pseudos (r78, r79) are still pseudos → so the dump is BEFORE the local allocation.

Hmm, so the .lreg RTL is pre-local-alloc, and the .greg RTL is post-global-alloc. The copy into a0 for q could be created by local_alloc itself!

Local alloc creates copies when? In local_alloc, when a qty's hard reg conflicts... Hmm, actually local_alloc doesn't create copies; it *coalesces* them (combine_regs).

Hmm, but wait: what about the *sched* pass (sched1)? It's before local_alloc, so no.

So the copy must exist in the .lreg RTL... but I searched and found none. Let me search the whole .lreg function section for "(reg:SI 4 a0)" occurrences to see all copies into a0.

Let me do that.
