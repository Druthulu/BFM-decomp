---
ts: 2026-10-22T08:51:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EwlCZwSBcn3dWSKJmuQe
---
In the .jump dump (pre-allocation), the join block (98) has:
- insn 101: `(set (mem/s:HI (plus:SI (reg/v:SI 73) 2)) ...)`
- insn 104: `(set (mem/s:HI (plus:SI (reg/v:SI 73) 0x34)) ...)`

No copy of r73 into a0! The address uses the pseudo directly.

So the "73 preferences: 4" must come from elsewhere. Hmm! But the .jump dump is BEFORE the "expand"? No — expand runs before jump. Hmm, so the RTL here is post-expand.

So where does the preference for a0 come from?!

AH WAIT. Maybe I've got the format wrong. Let me reconsider: maybe the format is ";; %d preferences: %d" where the number after is the *pseudo* that this pseudo prefers (a copy preference between two pseudos), not a hard reg. So "73 preferences: 4" means pseudo 73 prefers pseudo 4?? Hmm, but pseudo 4 is a hard reg ($4 = a0) in this numbering! Note: in the .rtl dump, hard regs are shown as (reg:SI 4 a0) and pseudos as (reg/v:SI 72). So the number 4 = hard reg a0 in both readings.

Hmm, so "preferences: 4" = a0 either way.

So there IS a copy of r73 into a0 at global-alloc time. But the .jump dump (pre-alloc) shows no such copy. Between the jump pass and global_alloc, the passes are: loop, cse2, flow2, combine, sched, local_alloc, global_alloc. Hmm, and "sched" (sched1) might create copies! sched1 (scheduling) can insert moves? Hmm, sched1 does "scheduling" which may create copies for register constraints? Hmm.

Hmm, and local_alloc! local_alloc can create copies (the "qty" coalescing). Hmm.

Wait, actually — I wonder: maybe the "preference" mechanism in global.c `set_preference` is called for the *pseudo* when it's connected to a hard reg via a copy — and the copy is created by local_alloc? Hmm.

Hmm, alternatively: maybe I misread and the preference line belongs to a different pseudo. The dump format from GCC 2.7's global.c:

```c
static void
dump_global_alloc (file)
     FILE *file;
{
  int i, j, k, n;
  int regno;

  n = n_global_allocnos;
  fprintf (file, "\n;; %d regs to allocate:", n);
  for (i = 0; i < n; i++)
    fprintf (file, " %d", regno_order[i]);
  fprintf (file, "\n");

  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      fprintf (file, ";; %d conflicts:", regno);
      for (j = 0; j < n; j++)
	if (i != j && conflicts_test[j][regno])
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
    }

  /* Print the preferences.  */
  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      ...
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)   /* ??? */
```
Hmm, in GCC 2.7's global.c, `reg_preferred` is `short *reg_preferred` — "reg_preferred[i] is the reg that pseudo i prefers". And the dump:

```c
  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      ...
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
```
That would print ";; 73 preferences: 74" if pseudo 74 prefers 73. Hmm! But we see "73 preferences: 4" and "74 preferences: 4" — the number 4 is a HARD reg (a0), which is not in the regno_order list (73 74 76 83 72). So this variant of the print can't be it (4 isn't in the order list).

So the format must be ";; %d preferences: %d" = (pseudo, preferred hard reg). And r73's preferred hard reg = 4 (a0).

Hmm, but in the .jump dump there's no copy of r73 into a0. Let me check the .lreg (local-alloc) dump — maybe local_alloc created the copy. Local alloc's dump shows the qty allocation and the copies it made.

Let me look at the .lreg section for this function.
