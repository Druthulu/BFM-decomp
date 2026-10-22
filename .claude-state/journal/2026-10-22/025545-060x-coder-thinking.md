---
ts: 2026-10-22T08:55:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jQMB5lm8xuo7tK6kQ7Ys
---
In the post-alloc .greg RTL, the store's address is `(plus:SI (reg/v:SI 4 a0) 52)` — so r73 was assigned to hard reg a0 and the store uses it directly (no copy). So the preference for r73 → a0 exists but the copy isn't visible (it was consumed).

So where does the preference come from? Hmm! Maybe from the *param copy* chain? Hmm.

OK, let me try a DIFFERENT experiment to nail the mechanism: use the .greg dump of a variant where I remove the call-arg copy (e.g. inline ptr into the call: `func_8012BD14(arg->unk64)`) — hmm, that changes the code (the call arg would be a reload). Hmm, actually `func_8012BD14(((Unkstruct_801815AC_2 *)arg)->unk64)` — the arg is loaded into a0 for the call → the same copy (set a0 (reg r_ptr)) — hmm, but then the pseudo for the load would be a *new* pseudo (not the global ptr), so the global ptr might disappear → the globals change.

Let me test: v2 = inline ptr in the call AND keep ptr for st:
```
st = ((Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64)->unk2;
...
if (func_8012BD14(((Unkstruct_801815AC_2 *)arg)->unk64) > 0x9000)
```
Hmm, but then the load of arg->unk64 for st and the call arg would be CSE'd into one load (the same expression) → the load is before the call → the call arg copy would be from the same pseudo. Hmm.

Actually, c2 (inlined ptr entirely) scored 4 as well. Let me check c2's .greg to see if the preference changed. That's a dump cycle (~1 min). Hmm.

Let me step back and think about the TIME BUDGET. I've spent ~50 minutes on item 1. The brief: 20-30 min per item, and a WALL needs ≥20 min and ≥30 scored tries. I have ~12 scored tries so far (c0-c4, v05-v10, w1-w4, orig, win). I need 30+ tries for a WALL.

Given the mechanism (q is a global pseudo; the target needs it in $3; the scan would give v0 (wrong) and the preference gives a0), the levers that could work:
(L1) Make val (r76) allocated before q (r73) → val → v0, q → v1. Requires val's density > q's density: val refs 4 (or live ≤3) vs q refs 4/live 8.
(L2) Make q's density < val's: q refs 3 (→3750) or live ≥ 14.
(L3) Make the preference of q be v1 (hard to control).

For L1: val's refs = 3 (2 defs + 1 use). Hmm! What if val were defined ONCE and used ONCE... it already is minimal.

Hmm, what about the *live length* of val: 5 insns. pri = 1*3/5*10000 = 6000. If live were 2: 1*3/2 = 15000 > 10000 ✓. Live length = the number of insns from the def to the use. val's def is at insn 46 (block 4) and the use at insn 101 (block 9) — but "live across 5 insns" is the count of insns in the live range (flow's REG_LIVE_LENGTH?). Hmm, "Register 76 used 3 times across 5 insns" — the "across N insns" is the live length.

To reduce val's live length, the def must be closer to the use. The def is in the arm block (4/7) and the use in the join (9). The distance is fixed by the structure. Hmm, unless the *value* is passed differently.

Hmm, what about the *other* direction (L2): q's live length is 8. q's def at insn 43 (block 4) and last use at insn 104 (block 9) — "across 8 insns". To make it ≥14, hmm.

Hmm! What about q's REFS: 4. The refs are counted by flow.c: reg_n_refs[regno] += loop_depth per mention. q is mentioned: 2 loads (defs) + 2 stores (uses) = 4.

What if one of the mentions were not a "mention" of q? E.g. if the second store's address were computed from a *different* pseudo that has the same value... e.g.:

```
case 2: q = arg->unk64; val = 3; break;
...
q->unk2 = val;
((Unkstruct_801815AC_3 *)arg->unk64)->unk34 = 0;   // reload instead of using q
```
Hmm! That would reload arg->unk64 for the second store: `lw a0,100(s0); sh zero,52(a0)` — an EXTRA instruction (the target has no second load) → score.

Hmm.

What about: the *value* of q being used in only ONE place by making the two stores use the same address computation? e.g.
```
u16 *p = (u16 *)q; p[1] = val; p[0x1A] = 0;
```
Here q is mentioned once (in the initialization of p) and p twice → q's refs = 3 (2 loads + 1 use)! And p is a new global (refs 2, live ~?) → hmm, p's density: refs 2 → floor_log2(2)=1 → 1*2/live*10000. p's live = from its def (block 9) to its last use (block 9) → live ~2-3 → pri = 1*2/3*10000 = 6667 < 10000. Hmm, so q (pri = 1*3/8*10000 = 3750) vs val (6000) vs p (6667).

Order would be: p (6667), val (6000), q (3750)? Hmm, wait, and the arg (4444) and the switch value (r83: refs 3, live 5 → 6000).

Hmm, so with p: the globals would be p, val(6000), r83(6000), arg(4444), q(3750). Order: p, val, r83, arg, q (ties by allocno).
- p → first fit: v0? p's conflict set: p is live only in block 9 → v0 free? p doesn't conflict with v0 → p → v0. Hmm, but the target has val in v0. ✗.

Hmm. But wait, would the asm change? `u16 *p = (u16 *)q; p[1] = val; p[0x1A] = 0;` → the asm would be: lw a0,100(s0) (q); move a1,a0? (p = q) — an extra move! ✗ (the target has no move).

Hmm, unless gcc coalesces the copy (p = q) — but gcc's global.c has NO coalescing (K8) → an extra move insn. ✗.

OK. Hmm.

Let me reconsider (L1): val's refs 4. How about making the *value* a 2-use thing: e.g. `q->unk2 = val;` and the value ALSO used in... hmm.

What about making val's live length smaller by using the value EARLIER? The value is used in the join (the store). The def is in the arms. Fixed.

Hmm, what about (L2) q's live ≥ 14: q's live length is 8 insns — the "live length" in flow.c is computed as (last use insn - first def insn)?? Hmm, "across 8 insns" for a range from insn 43 to 104 — that's not 61. So the live length counts something else (the number of insns in the live range in the "live" sense = the count of insns where the reg is live). Hmm.

Hmm, alternatively: q's live length could grow if q were live in MORE blocks. E.g., if q were live in the *entry* block too (defined earlier) — that changes the code.

Hmm, hmm. What about a completely different approach to get q into $3: what if the q pseudo were NOT global but the *value* pseudo were? I.e., swap: make the *pointer* local to the join and the *value* global? The pointer is used in the join (2 uses) and defined in the arms. The value likewise. Symmetric — no.

Hmm, what if the pointer were defined in the ENTRY block (one load) — then the pointer is global but with 1 def; the value is global with 2 defs. But the target has 2 loads ✗.

OK, let me look at this from yet another angle: what if the *order* of the two q loads in the arms could make gcc treat q as a pseudo with 1 def? E.g., if the case-2 arm assigned q and the case-1 arm did NOT assign q (using the value from case 2)? The control flow: case 2 and case 1 are exclusive. If q were assigned only in case 2, the case-1 path would use an undefined q ✗ (and the target has 2 loads).

Alright. Let me consider the possibility that the answer is a WALL for item 1, and use my remaining time to:
1. Run more tries to (a) satisfy the ≥30 tries requirement, and (b) maybe find a surprise.
2. Write it up with the mechanism.

Actually, hold on. Let me reconsider the PREFERENCE mechanism once more. The preference "73 prefers 4" — what if it's NOT about a copy but about the *conflict* matrix? Let me look at GCC 2.7's global.c `dump_global_alloc` — I'll try to recall harder:

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
      ...
      fprintf (file, ";; %d conflicts:", regno);
      for (j = 0; j < n; j++)
	if (i != j && conflicts_test[j][regno])
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
    }
```
Hmm, the "conflicts" lists include 2 3 4 29 (hard regs) → so the print covers both allocnos and hard regs.

And then:
```c
  /* Print the preferences.  */
  for (i = 0; i < n; i++)
    {
      ...
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
    }
```
If reg_preferred[j] is the *hard reg* that pseudo j prefers, then this print would list, for each hard reg, the pseudos that prefer it — but the label would be the hard reg number, and the entries would be allocno numbers. So "73 preferences: 4" doesn't fit (73 is an allocno, 4 would be an allocno).

Hmm! Unless the print is:
```c
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)
```
where reg_preferred[j] is the *allocno* that pseudo j prefers (a copy preference between two globals). Then "73 preferences: 4" means pseudo 73 prefers allocno 4?? But 4 is a hard reg.

OK, alternative: maybe the print is:
```c
  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)   /* j's preferred reg is regno */
	  fprintf (file, " %d", j);
      fprintf (file, "\n");
    }
```
Then "73 preferences: 4" would mean "the pseudo 4 prefers 73" — but 4 is a hard reg; the loop is over j < n (allocnos). ✗.

I give up on the exact format. Let me do an EXPERIMENT to determine whether the preference is what gives q → a0: I'll create a variant where the call-arg copy into a0 is *eliminated* (so a0 is not used at all in the function) and see where q lands. E.g., make the call argument a *constant*? No — the call is `func_8012BD14(ptr)`.

Hmm, what if the call argument were `arg` itself (a0)?! I.e. `func_8012BD14((s32)arg)` — then the copy (set a0 (reg r72)) would be a copy of the ARG pseudo into a0 → and the ptr pseudo would still exist for the st load. Hmm, but that changes the semantics (the function would receive arg instead of arg->unk64) — but this is a scratch experiment to learn the mechanism, not a candidate for the match. Hmm, but it changes the code shape.

Hmm, better experiment: add a *second* use of a0 in the join block? Not possible.

Let me try a different diagnostic: compile a variant where the *q* pointer is used as a call argument somewhere (so a copy of q into a0 definitely exists) vs. not. Hmm.

Actually — HOLD ON. What about this: the preference might come from the copy `(set (reg:SI 4 a0) (reg/v:SI 74))` where 74 is the PTR, and the *preference* is inherited: since the ptr and the q are BOTH loaded from the same address (arg->unk64) — hmm, no, they're different pseudos.

Hmm, hmm! But actually — WAIT. What if the preference is inherited through the "copy chain" r73 ← r74? Look: the call-arg copy takes the ptr (r74) into a0. And r73 (q) is loaded from the SAME address. Hmm, no copy chain.

Hmm, what if gcc's cse *merged* the two loads? No, they're in different blocks (a call between them).

OK, let me look at the problem from the "which pseudo got which reg" angle once more:
dispositions: 72 in 16 (arg→s0), 73 in 4 (q→a0), 74 in 4 (ptr→a0), 76 in 2 (val→v0), 83 in 3 (switch value→v1).

The scan order (v0, v1, a0, a1, ...):
- r73 (q) allocated FIRST: scan → v0? But v0 is not in r73's conflict list. Hmm, but the *local* allocation had already assigned v0 to some local (r84/r85 = the consts 1 and 2 in blocks 0/1; r77/r80 = the call results). Hmm! r77 (the call result) is a local in block 2/5 → local_alloc gave it v0 (the call result reg is v0 naturally). So v0 is occupied by locals in blocks 2/5.

Is that a conflict for r73? r73 is live in blocks 4,7,9; the locals holding v0 are in blocks 2,5,0,1 → disjoint! But gcc's global_alloc might not know the block granularity of the *local* allocation. Hmm, but the .greg conflict computation should have.

Hmm, and r76 (val) → v0 too (val is live in blocks 4,7,9 as well) — the same blocks as r73. And r73 and r76 CONFLICT with each other (they're both live in blocks 4,7,9) — but both got... r73 → a0, r76 → v0. OK.

So the scan for r73 skipped v0 and v1. Why?
- v1: used by the locals r78/r79 (block 2) and r81/r82 (block 5) — disjoint from r73's blocks (4,7,9) → shouldn't block. Unless the conflict computation is coarser.

Hmm! Wait, maybe the "blocks" I think r73 is live in are wrong. Let me re-read the lreg block info:
- Basic block 4: first insn 40, last 48; registers live at start: 29 30 72 → so in block 4, the live regs at start are sp, fp, and 72 (arg). The q (73) is defined in block 4 (insn 43) and the val (76) too (insn 46).
- Basic block 9 (join): live at start: 29 30 73 76 → q and val are live at the start of the join ✓.

So r73's live range: blocks 4 (from insn 43), 7 (from insn 74), 9.

And the locals in v1: r78/r79 in block 2, r81/r82 in block 5. Disjoint from 4,7,9 ✓.

So v1 should be available for r73! But the scan gave a0. Therefore the preference (a0) must have overridden the scan. OK, so the preference IS decisive, and it comes from somewhere I can't see in the dumps.

Hmm, so what if I could make the preference be v1? Or remove it?

Hmm, here's a thought: what if the *number* of hard-reg uses matters — the preference could come from the fact that the q pseudo is "connected" to a0 via the *address* in the store: `(mem/s:HI (plus:SI (reg/v:SI 73) (const_int 2)))` — the "plus" with a constant. Hmm, in global.c's set_preference, only copies count.

WAIT!!! Maybe the preference comes from a copy created by *local_alloc* in a DIFFERENT function... no.

Hmm, let me look at the .sched (sched1) dump — sched1 runs before local_alloc and may create copies? Let me grep the .sched section for "(reg/v:SI 73)" with a copy.

Let me do that. The .sched file: dumps_c1/c1.i.sched.
