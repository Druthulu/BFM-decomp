---
ts: 2026-10-22T08:58:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vXe8C7Xh0I9mxeVqIFyt
---
The tool parses ";; N preferences: <list of numbers>" as a list of preferred REGS. So "73 preferences: 4" = q prefers reg 4 (a0). And the tool author claims the preferences decide the assignment.

So the preference for a0 on the q pseudo is real per the dump. And the copy that creates it isn't in the .lreg/.sched RTL... which means it was created by LOCAL_ALLOC (which runs between the .lreg dump and global_alloc).

Local alloc DOES create copies! In local-alloc.c, when a qty's reg conflicts... hmm. Actually, local_alloc's "combine_regs" merges a copy's operands (removing copies). But there's also the case where local_alloc *inserts* a copy to satisfy a register constraint: e.g., for the call-arg copy... hmm, that already exists.

Hmm, what if local_alloc, when assigning a hard reg to a local pseudo, and a global pseudo is live there, creates a copy? Hmm.

Hmm, wait. Actually! Maybe the preference for a0 on r73 comes from a copy that was created by local_alloc for the *join block's* address: the local alloc might have decided that the store's address needs a hard reg (a0) and created a copy from r73 to a0 (as an "output reload" prep). Hmm.

Whatever the origin, the practical question: how to change it.

Let me try an entirely different lever: the *order of the two stores*. In w1 (swapped), the score was 4 with the class MIXED, and the base was still a0. So no.

New idea: what if the join block's store used q via a *memory* expression that doesn't need a hard reg? Hmm, the base must be in a reg.

New idea: what if the value stored (val) were stored via a *different* mechanism so that the join block has only ONE use of q? That reduces q's refs to 3 → pri 3750 < val's 6000 → the order becomes val(6000), r83(6000), arg(4444), q(3750) → val → v0 ✓, then q → v1 ✓ (if v1 is free and the preference doesn't override) — but the preference (a0) would still override the scan → q → a0 ✗.

Hmm, unless with the lower priority, q is allocated later and the scan... the preference still wins.

Hmm, unless the preference only applies within the class scan and the conflict check: is a0 conflicting for q? q's conflict list: {73, 76, 29} — a0 not included. But r74 (ptr) is in a0 — does q conflict with r74? q's conflict list doesn't include 74 → so q CAN share a0 with ptr (as it does).

OK so the preference is the blocker. I need to know where the copy comes from. Let me find it by dumping the RTL right before global_alloc. The .greg dump's RTL is post-alloc. Hmm, but I can reconstruct: the copy (set (reg:SI 4 a0) (reg/v:SI 73)) would have been folded into the store's address, so the post-alloc RTL wouldn't show it.

Hmm! Alternatively, maybe the copy is the *store's address* handling by MIPS's expand: in mips.md, the "sh" instruction's address operand might require a register, and expand creates a copy into a hard reg. But the .lreg dump (post-expand, pre-local-alloc) shows the address as (plus (reg/v:SI 73) 2) — no copy. Hmm, so expand did NOT create a copy.

So the copy must come from local_alloc. Let me verify by looking at the .lreg dump for the "copies" section: local_alloc's dump prints the qtys and the "hard reg" choices, and at the end it may print the RTL after local allocation. Hmm, in GCC 2.7, local-alloc.c's dump_local_alloc prints the qty table and the RTL? The .lreg dump I read had the RTL with pseudos → that's the pre-alloc RTL printed by dump_local_alloc at the start.

Hmm, so where?!

Hold on, hold on. What about *sched2*? No, that's after.

What about the *reload* pass? The doc says reload runs after global_alloc. Hmm, but is that right for gcc 2.7? Let me check the doc again: "Pass order (relevant slice): flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr."

Hmm OK. But WAIT: in GCC 2.7, is there a pass that creates the address copy BEFORE global_alloc? What about the *combine* pass? Or "cse2"? Hmm, all before sched1.

Hmm, what about *expand*? It's before jump. The .jump dump showed the address as (plus (reg/v:SI 73) 2) with no copy.

So between the .jump/.lreg dump and global_alloc, the only pass is local_alloc. And local_alloc CAN create copies! In local-alloc.c, `allocate_available_regs` and the "conflict" handling: when a qty is assigned a hard reg and a global pseudo is live there, local_alloc may create a copy to preserve the global's value... Hmm.

Actually YES: I recall local-alloc.c has a function `reg_overlap_related_live_p` and in `allocate_available_regs` there's code that, when a local qty wants a hard reg that is occupied by a global pseudo in that block, creates a copy. Hmm.

Hmm, but here the local qty (the const 36864) wants v1, and v1 is... hmm, is v1 occupied by a global? No global is in v1 at that point (r83 → v1 is decided later).

Hmm! Hmm. Alternatively, local_alloc's "coalesce" (combine_regs) may have created the copy in the other direction: e.g. the copy `(set (reg:SI 4 a0) (reg/v:SI 74))` (the call-arg copy) was coalesced with... hmm.

OK OK. Let me try yet another approach to the whole problem — maybe there's a C-level lever that avoids the issue entirely: what if the pointer were a **pointer type** (`Unkstruct_801815AC_3 *`)? Then the address (plus (reg q) 2) is the same. Tried (c4, w4): score 4.

What if the pointer were a `u8 *`? Then the stores would be byte stores ✗.

Hmm, what about making the *value* (val) a `u16` vs `s16`? Tried.

Let me try a few "shape" levers that could change the *number of globals* or their density:
(1) Make the two q loads share ONE pseudo by making the arms converge earlier: e.g., use a goto to a common block that does the load:
```
case 2: if (...) return 0; val = 3; goto L;
case 1: if (...) return 0; val = 4; goto L;
L: q = arg->unk64; stores...
```
→ 1 load ✗ (39 vs 38 insns).

(2) Hmm! What about making the *value* global and the *pointer* global but with the pointer having 3 refs? Discussed: needs an extra move.

(3) What about `u16 val` → the value's mode is HI (2 bytes) — what if the value were stored as a *different* width? The target stores `sh v0,2(v1)` (16-bit) ✓.

Hmm, let me look at the problem from the score's perspective: is there any variant that gets the score below 4? The 4 differing insns are the 2 loads and 2 stores using a0 vs v1. If a variant put q in a0 for the loads but v1 for the stores (or vice versa), the score might be 2? Hmm, that would be weird.

Hmm, what if the q load's destination were v1 and the store's base a0? That'd need q in two regs → an extra move → more diffs.

OK. Let me now consider the possibility that the score-0 solution requires the q pseudo to be allocated v1 via the "preference" mechanism, i.e. the copy must go into v1. And the copy's target reg (a0) is decided by... the *address* handling.

Hmm! IDEA: what if the *store* were to a struct field at offset 0? Then the address is just the pseudo (no "plus") — maybe then the copy (if any) goes elsewhere. Hmm, but the target stores at offsets 2 and 0x34.

Hmm, hold on! What about the SECOND store: `q->unk34 = 0` at offset 0x34 — the address (plus (reg q) 0x34). And the first store at offset 2.

What if the source used a *different struct type* where the fields are at offsets 0 and 0x32? That changes the offsets in the asm ✗.

OK, let me try to settle the "where does the a0 copy come from" question empirically with a cheap test: compile a variant with the *join* block's stores replaced by something that doesn't use q as an address — e.g., a variant where q is only loaded (not used) — then see if the a0 copy/preference disappears. Diagnostic only.

Actually, better use of time: let me try a bunch of *plausible candidate* variants in a batch and see if any scores 0. Even if I don't understand the mechanism, a MATCH is a MATCH. Let me brainstorm C-level variants that could plausibly shift the allocation:

B1: Declare q *after* val (decl order changes the allocno order! K1: creation order = declaration order → the pseudo numbering changes → the tie-breaks change). Since q (r73) and val (r76) have different priorities, decl order doesn't change their order... but it changes their *regnos*, which affects the tie-break and the "copy preference" inheritance. v06 (q after ptr) was score 4.

Hmm, what if val is declared BEFORE q? Then val = r73 and q = r74! Then the order (by priority) is still q first (10000) then val (6000). Hmm, but the allocno *numbers* change: q=r74, val=r73. The order line would be "74 73 76 ..."? The order is by priority, so q (10000) first regardless.

Hmm! But the tie-break... no tie.

Hmm, so decl order doesn't change the priority order here. BUT: the *preference*! Hmm.

B2: What if the *value* is declared as `s16`? Then its mode is SI (sign-extended) → the store `sh` would need a truncation → the asm might change ✗ (v07 scored 4, so the asm was the same).

B3: What if `q` is declared as `u32`? (v09, score 4).

B4: What if the *stores* are done through a `u16 *` cast of q (w2, typo'd; w3 = `*(u16*)(q+2)` score 4).

B5: What if the two stores are merged into a struct assignment? no.

B6: What if the *q* variable is declared *inside* the switch? no.

B7: What if the source uses `arg` directly instead of `ptr` for the st load (so ptr is only the call arg)? c2-ish.

B8: What if the call is made with the *q* value instead of ptr? I.e. `func_8012BD14(q)` where q is loaded before the call? That changes the load's position (before the call) ✗.

Hmm, B9: what if the *q* load were written as `q = arg->unk64;` where `arg` is used directly (not via the s0 copy)? The `arg` param is copied to s0 (r72) at the entry: `move s0,a0`. The load is `lw v1,100(s0)` — the base is s0 = the arg copy. If the source used `((Unkstruct_801815AC_2 *)arg)->unk64` — the same thing (arg is the param in a0, copied to s0 because it's live across calls). ✓ same.

OK. Let me try a batch of "diagnostic + candidate" variants:
- x1: q loaded but never used (diagnostic: does the a0 copy disappear?).
- x2: the store's base spelled as `*(u16 *)q` (offset 0) — diagnostic of the copy's origin.
- x3: val declared before q.
- x4: the whole body with the two arms' q loads removed (diagnostic).

Hmm, x1/x4 are diagnostics that don't score meaningfully.

Let me think about the TIME. It's now ~1h into the task, item 1 not cracked. I have 2 more items (both "pin $18 (w) and $0 (zr)" twins with notes saying they're hard). The brief says 20-30 min per item, and I should not stop between items. I need to allocate time: maybe 25 min more on item 1, then ~30 min each on items 2 and 3. Total ~1.5-2h. That's acceptable (the brief's budget is per item, 20-30 min).

Let me be smart: for item 1, let me run a batch of ~10 more variants (cheap, ~1s each) covering the most promising structural ideas, and count the tries. If none works, write the WALL with the mechanism.

Promising batch for item 1 (all real C moves):
m1: val declared before q (decl order).
m2: q declared first, val last.
m3: the two stores via a `u16 *` local initialized in the join (pointer reuse) — w2 fixed.
m4: the call argument spelled inline (`func_8012BD14(((Unkstruct_801815AC_2 *)arg)->unk64)`) while st uses ptr — hmm, that would reload arg->unk64 for the call (the ptr load is before the call; the expression arg->unk64 would be CSE'd with the ptr load → same pseudo) → probably identical.
m5: `q` assigned via a temp: `t = arg->unk64; q = t;` (extra pseudo, likely an extra move ✗ but let's see).
m6: the value stored via a `u16` variable: `u16 v = val; q->unk2 = v;` (extra copy ✗).
m7: the switch replaced by if/else (different dispatch ✗ but cheap).
m8: `q` as `s32` but the stores via `((Unkstruct_801815AC_3 *)q)->unk2 = (u16)val;`
m9: the two arms' `q` loads moved to the top of each arm (before the call)? That changes the code (the load before the call) ✗.
m10: `st` as `u32`? The switch value: `lhu v1,2(a0)` — with u32 the zero-extend is the same. Hmm, `st` is u16 and the switch does `lhu` + zero-extend. If st were u32, the load would be `lw` ✗ (different insn).
m11: `val` as `u16` and `q->unk2 = val` with val declared as `u16` — same as now.

Hmm, m5-m6 add copies → likely extra insns.

Honestly, the most promising lever per the K2 density analysis: make the *value* (val) have a higher density than q, or q's lower. Since q's refs are fixed at 4 and live 8, and val's at 3/live 5, the only way is val live ≤ 3 (pri 10000 — tie, loses) or ≤ 2 (pri 15000 ✓).

val's live length = 5 insns. "across 5 insns" — the live length counts the insns in the live range. val is defined at insn 46 (block 4) and used at insn 101 (block 9). The live range spans blocks 4, 7, 9 → the "live length" counts... hmm, 5.

Could I shorten val's live range? The def is in the arm; the use is in the join. If the arms were *shorter* (fewer insns between the def and the join), the live length would shrink. Hmm! The live length = the number of insns from the def to the use, counted in the insn stream of the *live* range. Since the def is the last insn of block 4 and the use is the first insn of block 9, the live length counts the insns in blocks 4 (after the def), 7, 9 (up to the use) → that's why it's 5.

Hmm, to shorten it: fewer insns in the arms after the val def. The arm block 4: insn 43 (q load), 46 (val=3), 48 (jump). Hmm.

What if the value were defined LATER in the arm? It's already last.

What if the arms were reordered so that the val def is in the *last* block? no.

Hmm, what if the value were defined in the JOIN block? Then it couldn't differ per arm... unless the join recomputes it from something. Hmm! What if the value were derived from `st`?! E.g. the value 3 or 4 could be computed as a function of st: `val = 3 + (st == 1)`. Hmm, that changes the code (extra ops).

Hmm, what about: the value could be `st + 1` (case 2 → 3, case 1 → 2)? no: case 2 → 3, case 1 → 4. So val = st + 1 for st=2 → 3 ✓, but st=1 → 2 ✗ (need 4).

Hmm: val = 3 + (st == 1) → for st=2: 3 ✓; st=1: 4 ✓. In C: `val = (st == 1) ? 4 : 3;` — but that's computed in the join (once) → the value is NOT a global → the arm's value assignment disappears → the code changes (no `li v0,3` in the arms) ✗ — the target has `li v0,3` in the arm-2 path and `li v0,4` in the arm-1 path.

Hmm, wait. Actually let me re-read the target:
```
 3ff0 lw v1,100(s0)      ; q
 3ff4 j 401c
 3ff8 li v0,3            ; val=3 (delay slot of the j)
 4014 lw v1,100(s0)      ; q (case 1)
 4018 li v0,4            ; val=4
 401c sh v0,2(v1)
```
So yes, each arm sets the value.

OK. So val must be a global with 2 defs.

Hmm, so pri(val) = 1*3/5*10000 = 6000 and pri(q) = 2*4/8*10000 = 10000. To flip, I need val's live length ≤ 3 (pri 10000, tie → q wins by allocno... hmm, unless q's allocno > val's!).

AH WAIT! The tie-break is by allocno (= regno = creation order = declaration order)! If val is declared BEFORE q, then val's regno < q's regno → on a tie, val wins!

So: if val's live length were 3 (pri = 10000) AND val is declared before q, then val is allocated first → v0 ✓, and q → v1 (if the preference doesn't override).

Hmm, but the preference for q (a0) is still the problem. Hmm! Unless the preference is actually a consequence of the *order* (e.g., the preference might be set on the *second* pseudo...).

Hmm, hmm. Let's test the hypothesis that the preference is what gives a0: try a variant where the *q* pseudo has NO copy to a0. What creates it? I couldn't find it. So maybe the "preferences: 4" print is not about a copy at all, and the a0 choice comes from the scan order for a different reason.

Hmm! IDEA: maybe the scan order for r73 skipped v0 and v1 because of "regs_used_so_far" + the *conflict sets of the LOCAL allocation* — i.e., the hard-reg conflict list of r73 in the .greg dump is {73, 76, 29} — hmm, that lists only sp.

Hmm, but the .greg "conflicts" print might only show the *allocno* conflicts + a few hard regs.

Ugh, I'm going in circles. Let me do a DIRECT experiment to find out what reg q gets when the preference is absent: I'll write a variant where the *ptr* (which has the call-arg copy → a0 preference) is eliminated, so a0 has no copy at all. If q then lands in v0 or v1, the preference was the cause.

How to eliminate the ptr's call-arg copy: call the function with an argument that is NOT a pseudo — e.g. `func_8012BD14((s32)arg)`?? That changes the semantics but is a diagnostic. Hmm, but the *load* of arg->unk64 for st would still exist.

Hmm, alternatively: keep ptr but make the call argument a *constant*? e.g. `func_8012BD14(0)`? That changes the code (li a0,0) ✗ but it's a diagnostic.

Let me do the diagnostic: variant d1: `func_8012BD14((s32)arg)` (no ptr pseudo for the call). Actually, hmm, `arg` is the param (a0) → the call arg copy (set a0 (reg r72)) → a0 still has a copy (of the arg pseudo, r72) → and r72 (arg) is global (live across calls) → so a0 would be "preferred" by r72. Hmm, and the arg ends up in s0 anyway (call-crossing).

Hmm, that's not clean either. Let me do: d1: remove the `ptr` variable entirely and use `arg->unk64` inline for st, and call `func_8012BD14(arg->unk64)` — hmm, that's c2 (score 4). Let me just dump c2's .greg and see the preferences! If in c2 the q's preference is still 4 (a0), the preference is intrinsic to the q/address relationship. If it changed, then the ptr's copy is the donor.

That's a decisive 2-minute experiment. Let me do it: generate the candidate TU for c2 (from the delever --keep scratch) and dump it.

Actually, I realize there might be a MUCH better approach: the delever tool has a "moves" catalog (C0505 catalog) and maybe a search mode (--run with --moves) that could find the answer automatically. The brief mentions `delever_search.py --try` for scoring, but the tool also has a search mode (--plan/--run) that hill-climbs over move families! Hmm, but the brief says to write bodies by hand. The search might be slow/heavy. Hmm, but it could be a good fallback.

Hmm, the brief says: "For each item ... write a lever-free body of `func` in RM1x/<dir>/win.c". And "R3.40-013 helpers" are mentioned. The `--run` mode of delever_search does a beam search over moves — that might find a match! But it may also be a shared tool with its own tree (writing to .run/P36/engine/...). The brief says I may only write under my shard dir. Hmm, --run writes to the engine's tree. Risky (other coders). Let me check --plan/--run semantics... Actually, the brief's BUILD/TEST says: bin/dt.sh per candidate; green = score 0. So the search is not required.

Let me do the c2 .greg comparison quickly, since understanding the mechanism is the only way to find the lever.

Actually, WAIT. Let me reconsider something much simpler! What if the *preference* comes from the copy `(set (reg:SI 4 a0) (reg/v:SI 74))` — the CALL-ARG copy — and the "preference" is recorded not for the copy's source but for the *pseudo that the copy's source is connected to*...

Hmm, hmm. Let me look at the c2 dump. Let me generate the c2 candidate TU.

Actually, I realize there might be a shortcut: the delever tool's own "moves" catalog (C0505) might include a move for exactly this: "the pointer used as a store base gets a0" → the move "field-direct" or "struct-typed ptrs" (from moves.md: "pin | func_801F033C | MATCH — struct-typed ptrs + store via ((Unkstruct *)a0)->unkFC (mem/s: sched1 lifts store over loads...)").

Interesting! That entry says: for a *pin* item, using struct-typed pointers + a store via a struct field made the pin unnecessary. Hmm! So maybe for item 1, "struct-typed ptrs" (c4/w4) plus something else works. c4 and w4 scored 4.

Hmm, in that entry the mechanism was "mem/s: sched1 lifts store over loads; equal lives, qty tie gives a v1, b a0" — a *sched1* effect.

Let me look at the moves.md entries for similar "pin" items where the crack was "u16 t (HImode copy escapes cse equiv) + u = arg2 + 0xD40 late" etc.

OK, let me just do the c2 .greg dump comparison to settle the preference's origin. Actually, better: let me do a *targeted* experiment: a variant where the call's argument is a *constant* (0) so that NO pseudo is copied into a0 (the call arg becomes `li a0,0`). Diagnostic only (the asm will differ), but the .greg will show whether q still prefers 4.

Let me do that: d1.c:
```
s32 func_801815AC(void *arg)
{
    s32 q;
    s32 ptr;
    u16 st;
    u16 val;

    ptr = ((Unkstruct_801815AC_2 *)arg)->unk64;
    st = ((Unkstruct_801815AC_3 *)ptr)->unk2;
    switch (st) {
    case 2:
        if (func_8012BD14(0) > 0x9000) { return 0; }
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 3;
        break;
    case 1:
        if (func_8012BD14(0) > 0x9000) { return 0; }
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 4;
        break;
    default:
        return 0;
    }
    ((Unkstruct_801815AC_3 *)q)->unk2 = val;
    ((Unkstruct_801815AC_3 *)q)->unk34 = 0;
    func_80178BF8();
    return (s32)func_80172710;
}
```
Then dump and look at the preferences. Hmm, but with `func_8012BD14(0)`, the ptr variable is still used for st.

Let me do this: generate the TU for d1 via delever --keep, dump it, read the .greg. ~2 min. Let's go.

Hmm, wait. Actually, let me reconsider the whole thing ONE more time, because there might be a MUCH simpler explanation for "73 preferences: 4" that I keep missing:

**The preference might be for the CALL-ARG copy of the PTR — and the ptr pseudo (r74) might be the SAME allocno as the q pseudo (r73)?** No, they're distinct regnos.

Hmm, OR: the .greg "preferences" print might be listing, for each *hard reg*, the allocnos that prefer it — and the "73 preferences: 4" line might actually be a mis-parse: the print might be ";; %d preferences: %d" = (hard reg 73?? no)...

Hmm, what if the print is: for each ALLOCNO i: ";; %d preferences:" listing the hard regs it prefers — and the numbers 4 for r73 and 4 for r74 mean both prefer a0.

Fine, that's my reading. And a0 is where both copies went... The only copy to a0 is from r74. Hmm, unless the copy to a0 is `(set (reg:SI 4 a0) (reg/v:SI 73))` created by local_alloc for the JOIN block's address.

AH WAIT!!! THAT'S IT! Local_alloc! Here's the thing: local_alloc assigns the *local* pseudos to hard regs. The join block (9) has a store whose address is the pseudo r73 (a global). For the store's address to be emitted, the base must be in a HARD reg at that point. Local_alloc (or the final RTL expansion) needs to copy the global pseudo r73 into a hard reg — and it picks a0!

Hmm, but the local_alloc dump shows the address as (plus (reg/v:SI 73) 2) — the pseudo is used directly in the mem. In the FINAL RTL (post-alloc), the store's address was (plus (reg/v:SI 4 a0) 52) — the pseudo was REPLACED by the hard reg a0 (because r73 was allocated a0). So no copy was needed.

So the "preference" for r73 → a0 must have come from a copy that existed... circular.

OK, hmm, what if the preference is created by the *reload* pass and the .greg dump is printed at the END of global_alloc but the RTL... no, the preference print is at the start.

Hmm, hmm. What if the "preferences" print in GCC 2.7's global.c is:

```c
  /* Print the preferences of each allocno: the allocnos it is connected to by copies. */
  for (i = 0; i < n; i++)
    {
      regno = regno_order[i];
      fprintf (file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno)   /* j prefers regno */
	  fprintf (file, " %d", regno_order[j]);
      fprintf (file, "\n");
    }
```
With reg_preferred[j] = the hard reg preferred by pseudo j. Then ";; 73 preferences: 4" would print the *hard reg* 4 for which some pseudo prefers... no, the label is the allocno and the entries are allocnos.

Hmm, so "73 preferences: 4" = allocno 73 has the entry "4". If the entries are hard regs → q prefers a0. If the entries are allocnos → 4 isn't one.

So: q prefers a0. And the mechanism creating it: in GCC 2.7's global.c, the preferences are set by `set_preference` — and where's set_preference called? In `global_alloc`:

```c
  /* Now scan the insns of the function, looking for copies that connect
     a global pseudo to a hard register.  */
  FOR_EACH_INSN (insn)
    {
      ...
      if (GET_CODE (PATTERN (insn)) == SET
	  && GET_CODE (SET_SRC (PATTERN (insn))) == REG
	  && GET_CODE (SET_DEST (PATTERN (insn))) == REG)
	{
	  r1 = REGNO (SET_SRC (PATTERN (insn)));
	  r2 = REGNO (SET_DEST (PATTERN (insn)));
	  if (r1 != r2)
	    {
	      if (r1 < FIRST_PSEUDO_REGISTER && r2 >= FIRST_PSEUDO_REGISTER)
		/* copy from hard reg to pseudo: the pseudo prefers the hard reg */
		set_preference (r2, r1);
	      else if (r1 >= FIRST_PSEUDO_REGISTER && r2 < FIRST_PSEUDO_REGISTER)
		/* copy from pseudo to hard reg: the pseudo prefers the hard reg */
		set_preference (r1, r2);
	    }
	}
    }
```
So a copy (set (reg:SI 4 a0) (reg/v:SI 73)) → set_preference(73, 4) ✓.

So there IS such a copy at global_alloc time. It must be created by local_alloc (which runs before global_alloc).

**local_alloc creates copies!** YES: in local-alloc.c, when a local qty is assigned a hard reg that is occupied by a global pseudo in that block, local_alloc inserts a copy to preserve the global's value. Hmm, or: local_alloc's `combine_regs` (coalescing) — when a copy's dest and src can share a reg, it merges them.

AH, here's a likely story: the copy `(set (reg:SI 4 a0) (reg/v:SI 74))` (the call-arg copy, dest a0, src r74) — local_alloc's coalescing (combine_regs) tried to merge a0 with r74's reg. Hmm.

OR: local_alloc, when assigning the *local* qty for the address... hmm, there's no local qty for the address.

Hmm, what about this: local_alloc handles the pseudo r73?? No, r73 is global (multi-block).

Hmm, what if local_alloc created a copy `(set (reg:SI 4 a0) (reg/v:SI 73))` for the *store's address* because local_alloc wants the address in a hard reg (a0) — the "hard reg copy" for a memory operand. In local-alloc.c there IS such a thing: `local_alloc` has the concept of "hard reg copies" for operands that must be in hard regs at an insn (e.g., the address of a memory operand, or the operands of a call). YES! In local-alloc.c, `find_reg` / `allocate_available_regs` handles the case where an operand must be in a hard reg: it creates a copy into a hard reg (the "hard_reg_copy" mechanism) — I recall `local_alloc` inserting copies for the operands of calls and for addresses.

So: the store's address (r73) must be in a hard reg → local_alloc creates a copy into a hard reg, choosing a0 (the first free call-clobbered reg in the block?). And that copy creates the preference q → a0 → global_alloc then gives q the reg a0 → the copy is deleted (the pseudo IS a0) → the store's address is a0 ✓.

So the chain: local_alloc picks a0 for the address copy; that copy's reg becomes q's preference; global_alloc honors it.

Now: can I influence local_alloc's choice of a0 for the address copy? The address copy's reg must be a hard reg that is free at that point. In the join block, the hard regs in use: v0 (the value), sp, fp, and the *global* q (r73) which will get a reg. Hmm, a0 is free at that point; v0 is used by the value; v1 is free!

Why did local_alloc pick a0 over v1? Because of the "reg_alloc_order" scan (K3: plain regno order: v0, v1, a0, ...) — hmm, v0 is used (the value), v1 is free → it should pick v1!

Hmm! Unless v1 was considered occupied: in the join block, is v1 occupied? The lreg dump says "Registers live at start: 29 30 73 76" for block 9 → v1 is NOT live at the start of the join. Hmm, but local_alloc's availability check might be function-wide ("regs_ever_live"): v1 IS used elsewhere (by the const/st in blocks 2/5 and the switch value). Hmm, but a0 is used too (the call args).

Hmm, in local-alloc.c, the hard-reg copy for an operand: the function `find_reg`/`allocate_available_regs` picks a reg from the class, checking `reg_occupied` and `regs_ever_live`? If it prefers a reg not used elsewhere, then a0 (used twice) vs v1 (used 4+ times)... a0 would win!

Per the doc: "Reload's version: order_regs_for_reload sorts spill candidates by total pseudo refs; the least-referenced reg is confiscated". And "hard_reg_use_compare :3822 ... by ascending use count". So the preference is by ASCENDING USE COUNT — the least-used reg first!

So: v1's use count vs a0's use count in this function. If a0 is used less than v1, a0 wins. Let's count the hard-reg uses in the RTL at that point:
- v0: the call results (2), the consts 1/2 (2), the value... hmm, v0 is used a lot.
- v1: the const 36864 (2), the slt results (2), the switch value (1) → ~5 uses.
- a0: the call-arg copies (2) → 2 uses.
So a0 (2 uses) < v1 (5 uses) → a0 is chosen ✓✓✓ That fits!

So the lever: make v1 LESS used than a0, or a0 MORE used, so that the address copy's reg becomes v1!

Hmm! But wait: the target has the const 0x9000 and the slt in v1 (fixed by the target) and the call args in a0 (fixed). So the use counts are fixed... UNLESS the *counting* is per hard reg and I can add uses of a0 elsewhere (e.g. an extra call argument? no) or reduce v1's uses (the switch value's uses are fixed).

Hmm. Hmm! But hold on: the use count is of HARD REGS in the RTL. In the lever-free version, the RTL has hard regs: v0 (call results, consts 1/2, the value), v1 (hmm, at that point in the RTL, are the const/slt in v1? NO! At the .lreg stage, the const 36864 (r78) and the slt (r79) are PSEUDOS, not v1!). The hard regs in the RTL before allocation: a0 (the call-arg copies), v0 (the call results, the consts 1/2, the return value). v1 is NOT used at all in the pre-allocation RTL!

Hmm, so v1's use count = 0 and a0's = 2 → v1 should win! But a0 won. Hmm, contradiction.

Unless the *reload* pass (which runs after global alloc) is what creates the address copy, and the .greg "preferences" are computed... no.

Hmm, hmm. OK, at this point I've spent a lot of time on item 1. Let me make a decision:

DECISION: Run a batch of ~12 more variants (cheap), then, if no MATCH, declare a WALL for item 1 with the best score (4) and the mechanism I've established:
- The q pseudo is global (2 defs in 2 arms + 2 uses in the join) → global-alloc.
- Its conflict set excludes $3; the scan would take $2 (v0) — wrong (the target needs val in v0) — and the copy-preference (the store's address copy into $4) overrides the scan to $4.
- To land in $3, either the preference must be $3 (the address copy's reg) or the allocation order must put val first (val density 6000 < q 10000, and q's density can't be lowered without changing the code).
- The address copy's reg is chosen by local_alloc/reload's ascending-use-count rule; the target's own use counts (a0 = 2 call-arg copies, v1 = 0) should favour $3 → but $4 wins, so the choice is not purely use-count.

Hmm, I should be careful to state only what I verified. Let me do a couple of decisive experiments to pin the mechanism, because a good wall tag with evidence is what the brief wants.

DECISIVE EXPERIMENT A: does the q pseudo's reg change if a0 is "busier"? I can test by making the call have MORE arguments (e.g. calling func_8012BD14 with 2 args? the function takes 1 → compile error). Hmm.

DECISIVE EXPERIMENT B: does the q pseudo's reg change if v1 is busier? v1's use count is 0 in the RTL...

Hmm, hmm. Hold on, let me reconsider: maybe the address copy's reg is chosen by local_alloc's *own* scan (K3: plain regno order: v0, v1, a0, ...) — the first free reg. In the join block: v0 is occupied (the value r76 → hmm, r76 is global, allocated later; at local_alloc time, the value r76 is a global pseudo, not a hard reg). Hmm! So at local_alloc time, in the join block, the hard regs in use: a0? (the call args are in other blocks), v0 (the return value at the end? that's in block 9! insn 110: `(set (reg/i:SI 2 v0) (symbol_ref func_80172710))` — yes, v0 is used in the join block for the return value).

So in the join block: v0 is used (the return value). v1 free. a0 free. The scan order (v0, v1, a0) → v0 is taken → v1 should be chosen!! But a0 was chosen. Hmm!!

Unless the "address copy" is created by the RELOAD pass (after global alloc) — in which case the preference in the .greg dump wouldn't exist... but the .greg dump DOES show the preference and the disposition 73 in 4.

Hmm, so the preference existed at global_alloc time, i.e. BEFORE the address copy (which is what I'm inferring).

So the copy into a0 existed at global_alloc time. Its source: a copy (set (reg:SI 4 a0) (reg/v:SI 73)).

WAIT!!! What about the SECOND q load? Hmm no.

What about... OH!!! WAIT. What about the *param copy*?! `(insn 4 2 5 (set (reg/v:SI 72) (reg:SI 4 a0))` — the arg copy. And the arg (r72) is a global → it's allocated s0. Fine, no.

Hmm, what about the *return value*? `(insn 110 107 120 (set (reg/i:SI 2 v0) (symbol_ref ...))` — v0 is hard.

Hmm, what about a copy `(set (reg/v:SI 73) (reg:SI 4 a0))` (the REVERSE direction: a0 → r73)?! THAT would be set_preference(73, 4)!! (copy from a hard reg to a pseudo → the pseudo prefers the hard reg).

Where would `(set (reg/v:SI 73) (reg:SI 4 a0))` come from? A *reload* of the address: "the address must be in a reg; the value in a0 (from the call arg copy) is copied into r73"?? Hmm, no.

Hmm, but actually: the *local* qty for the address! In local_alloc, the address (plus (reg r73) 2) requires the base in a hard reg → local_alloc creates a *local qty* (a new pseudo) for the address and assigns it a hard reg, with a copy from r73 → the local qty. That's a copy (set (reg/v:SI NEW) (reg/v:SI 73)) — pseudo to pseudo, no preference.

Hmm, but if the local qty got a0, and then... hmm, the copy (set (reg/v:SI 73) (reg:SI 4 a0)) could arise from the REVERSE: the local qty for the address is a0, and then local_alloc's coalescing merges the address qty with r73 (both in a0) → the copy is removed and r73 effectively "prefers" a0. And global.c's set_preference is called on the *remaining* copies...

Hmm, but if the copy was removed by coalescing, the preference wouldn't be recorded.

Hmm, unless the coalescing happens in local_alloc but the preference is recorded in global_alloc from a copy that was re-created.

You know what? There's a much simpler possibility I haven't considered: **the preference is recorded from the CALL-ARG copy `(set (reg:SI 4 a0) (reg/v:SI 74))`, and r74 = ptr... but maybe the .greg dump's allocno numbering differs from the .lreg regno numbering!** In global.c, the allocnos are renumbered! `regno_order[i]` are the *regnos* though...

Hmm, hmm. But what if the .greg "regs to allocate" list is in a different numbering than the .lreg? Both show 72,73,74,76,83 — the same set. If global.c's numbering were the same, then r73 = q and r74 = ptr. But what if global.c's "73" is actually the *ptr* and "74" is the *q*?! I.e. the .greg dump's numbers are ALLOCNO numbers (global.c's own counter), not regnos!

In GCC 2.7's global.c, there's `regno_order` (a permutation of the global regnos) and the dump prints... hmm. But the allocno numbering: global.c renumbers the global pseudos via `gen_reg_rtx`? Hmm, in GCC 2.7's global.c, the global allocation uses the actual regnos (not renumbered) — the "allocno" concept is from GCC 2.8+.

Hmm, but the .greg dump's "Register dispositions: 72 in 16 73 in 4 74 in 4 76 in 2 78 in 3 ..." — the numbers 78, 79, 81, 82, 84, 85 are the LOCAL pseudos (r78 = the const in block 2, etc.) — so the dump's numbers ARE regnos ✓ (the local pseudos appear with their hard reg assignments).

So r73 = q (defined at insn 43/74) and r74 = ptr.

Hmm, so the q prefers a0. There's a copy (set (reg/v:SI 73) (reg:SI 4 a0)) somewhere.

OK, ONE more hypothesis: the store's address. In the RTL, the store is `(set (mem/s:HI (plus:SI (reg/v:SI 73) 2)) (reg/v:HI 76))`. For MIPS, the "mem" operand with a "plus" address: the *reload* pass must put the address in a reg. But BEFORE reload, the RTL is as shown.

Hmm, but what about the *expand* pass: for the store, expand might have created a copy for the address. The .jump dump (post-expand) shows no copy. So no.

=> The copy must be created by LOCAL_ALLOC. And local-alloc.c DOES create copies: in `allocate_available_regs`, when a local qty is assigned a hard reg that conflicts with a global pseudo live in that block, it inserts a copy to save the global's value. Hmm.

You know what? There's a cleaner possibility: local_alloc's `combine_regs` — the coalescing of the *call-arg copy* `(set (reg:SI 4 a0) (reg/v:SI 74))`: the dest is a0 (hard) and the src is r74 (pseudo, global). Coalescing a global with a hard reg isn't done (global.c has no coalescing, but local-alloc's combine_regs can handle the case where the *src* is global? hmm).

OK. DECISION TIME. I've spent ~1h10m on item 1. Let me now:
1. Run a final batch of ~10 variants for item 1 (to reach ≥30 tries).
2. If no MATCH, record a WALL.
3. Move to items 2 and 3 with the remaining time.

For the batch, let me include the most plausible levers:
b1: val declared before q (decl order → allocno order).
b2: q declared after val AND ptr.
b3: the stores via a `u16 *` local in the join (w2 fixed).
b4: the store of the value via `q->unk2 = (u16)val` with val as u16 (done).
b5: the whole thing with `arg` used directly (no ptr) for st: `st = ((Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64)->unk2;` and the call with ptr → hmm, c2 was fully inlined.
b6: the call arg = ptr but ptr declared after q.
b7: `q` as `s32` with the stores done via a `Unkstruct_801815AC_3 *` local assigned in the join (w4, done).
b8: the two arms swapped in the source order (case 1 first, case 2 second) → different layout ✗ but cheap.
b9: `val` as `u8`? (v08 done)
b10: the value stored via a temp `u16 v = val;` (extra copy).
b11: `q` used in a `while(0)`? no.
b12: the switch → `if (st == 2) {...} else if (st == 1) {...}` (different dispatch, but maybe the same code? The target's dispatch is beq/bne — an if/else would produce the same branch structure! Actually `if (st==2) A else if (st==1) B else C` compiles to: `beq st,2,A; bne st,1,C; B:...` hmm, the target has `beq v1,1,3ffc` FIRST (the case-1 body) then `bne v1,2,default`. So the target's dispatch tests st==1 first! But the source has case 2 first! Interesting — gcc reorders the switch cases by frequency/heuristics. Hmm, so the source order doesn't map 1:1 to the layout.

Hmm! That's interesting: the target tests `st == 1` first (branch to 3ffc = the case-1 body) and then `bne st, 2 → default`. So the fallthrough is the case-2 body. With the source `switch (st) { case 2: ...; case 1: ...; }` — gcc's switch conversion emits the comparisons in the *source* order usually (case 2 first: `beq st,2,case2`?). Hmm, but the target compares with 1 first. So gcc's switch code chose to test 1 first (maybe because of the "jump table" optimization for a dense case range, or the case ordering heuristic).

Whatever, our current source reproduces the target's dispatch exactly (the diff showed only the 4 q lines), so the dispatch is fine.

Let me write the batch and score. Let me include some "shape" ideas:
- The `q` load in the arms could be moved to the *end* of the arm (after val = 3): the source order `val = 3; q = arg->unk64;` — hmm! That changes the order of the two insns in the arm: the target has `lw v1,100(s0)` then `li v0,3` — so the load comes first ✓ current. If I swap, the asm order changes ✗.

- What about `q = arg->unk64; val = 3;` → the current. ✓.

Hmm. Let me think about the "preference" once more: if the preference is created by a copy from a0 to r73, maybe I can *prevent* that copy by making the store's address not need a hard reg...

What if the two stores were merged so that only ONE store mentions q? E.g., if the value 0 store were done as part of a struct assignment? no.

Hmm, what if the second store (unk34 = 0) were done via a *different* base expression that mentions r73 in the same way? no.

OK, what if the *value* store used a *different* pseudo for the base: e.g. the source:
```
((Unkstruct_801815AC_3 *)q)->unk2 = val;
((Unkstruct_801815AC_3 *)q)->unk34 = 0;
```
Both mention q. What if instead:
```
u16 *p2 = (u16 *)q;
p2[1] = val;
p2[0x1A] = 0;
```
q mentioned once → q's refs = 3 (2 loads + 1 use) → pri 3750; p2 is a new global (refs 2, live 2-3) → pri ~6667-10000. Hmm, and p2 would get the reg (the address copy!) → the address copy for p2 → p2 prefers a0 → p2 → a0, and q → ? (its pri is lowest → allocated last → the scan → v0? but v0 is taken by val (r76) → v1 ✓!!). And p2 → a0 (preference). But the asm would have an extra move (p2 = q) ✗ — unless gcc coalesces... global.c has no coalescing → an extra `move`.

Hmm, but wait: would the copy `p2 = q` even be emitted? p2 is a global (live in block 9 only — hmm, p2 is defined and used in block 9 → it's LOCAL (single block, dies once) → local_alloc handles it → local_alloc COALESCES the copy (p2 = q) with q's reg if compatible (K8: local-alloc coalesces op0's dest into a dying input). q is global and dies at the store... The copy (set (reg p2) (reg q)) — local_alloc's combine_regs would merge p2 into q's reg (if q dies there and the classes match) → NO extra move ✓✓!

So: `u16 *p2 = (u16 *)q; p2[1] = val; p2[0x1A] = 0;` might produce:
- q's refs = 3 → pri 3750
- p2: local (block 9), refs 2 (def + 2 uses = 3?) hmm.
- val: pri 6000, allocated 2nd → v0 ✓
- q: pri 3750 → allocated after val → the scan: v0 (taken by val, and q conflicts with val? q and val are both live in blocks 4,7,9 → they conflict → v0 excluded) → v1 ✓ (if the preference doesn't override!)

But the preference for q: is there a copy into a0 for q? If the address copy is now for p2 (not q), then q has no preference → q → v1 ✓✓✓!!!

And the asm: the stores would use q's reg (v1) as the base (since p2 is coalesced into q) → `sh v0,2(v1)` ✓ and `sh zero,52(v1)` ✓!!!

That could be the MATCH! Let me test it! (This is the "pointer reuse" move from the catalog!)

Let me write it:
```
s32 func_801815AC(void *arg)
{
    s32 q;
    s32 ptr;
    u16 st;
    u16 val;

    ptr = ((Unkstruct_801815AC_2 *)arg)->unk64;
    st = ((Unkstruct_801815AC_3 *)ptr)->unk2;
    switch (st) {
    case 2:
        if (func_8012BD14(ptr) > 0x9000) { return 0; }
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 3;
        break;
    case 1:
        if (func_8012BD14(ptr) > 0x9000) { return 0; }
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 4;
        break;
    default:
        return 0;
    }
    {
        u16 *p2 = (u16 *)q;
        p2[1] = val;
        p2[0x1A] = 0;
    }
    func_80178BF8();
    return (s32)func_80172710;
}
```
Note: p2[1] = *(p2 + 2) ✓ and p2[0x1A] = *(p2 + 0x34) ✓ (0x1A*2 = 0x34 ✓).

Let me test this and variants!
