---
ts: 2026-10-22T08:45:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vY2dJhGv4aFi3zBkEqAG
---
Very important: r73 is defined in BOTH block 40 (case 2, const 3) and block 71 (case 1, const 4)! Two definitions of the same pseudo r73 (that's the classic GCC 2.x non-SSA "multiple definitions" — a pseudo defined in two blocks).

So r73 = q (one pseudo, 2 defs), r76 = the const 3/4 pseudo (also 2 defs: insn 46 and insn 77), r74 = ptr.

So globals: r72 (arg), r73 (q), r74 (ptr), r76 (val). Plus r83 = the zero-extended switch value (pseudo 83 defined at insn 89 — used in the dispatch, entry block only... but it's in the "regs to allocate" list, so it's global? It's defined in the entry block and used in the entry block → local. Hmm, but "83 in 3" disposition and it's in the allocate list. Hmm, maybe because the switch dispatch... whatever.

Now the .greg conflicts:
- 73 conflicts: 73 76 29 → q conflicts with val (76) and sp.
- 74 conflicts: 72 74 83 2 29 → ptr conflicts with arg(72), 83, v0, sp.
- 76 conflicts: 73 76 29 → val conflicts with q and sp.
- 83 conflicts: 72 74 83 2 29
- 72 conflicts: 72 74 83 2 3 4 29 → arg conflicts with v0, v1, a0!

And preferences: 73 prefers 4 (a0)?? and 74 prefers 4.

Where does 73's preference for a0 come from? Hmm, in the .rtl, is there a copy involving r73? The join block: insn 101: `(set (mem/s:HI (plus:SI (reg/v:SI 73) 2)) (reg/v:HI 76))` — a store, no copy.

Hmm, so where? GCC's global.c `dump_global_alloc` prints "preferences" from the copy preference list built by `make_reg_preferred` in `global_alloc`? Actually the preferences are computed in global.c's `record_preferences`? Hmm, in GCC 2.7 global.c, there's a function `dump_global_alloc` that prints:

```
  for (i = 0; i < n; i++) ...
      fprintf (dump_file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++) if (reg_preferred[j] == regno) ...
```
Hmm no.

Let me look at the actual GCC 2.7 source for the preferences. In global.c:

```
  /* Now allocate the hard regs to the globals.  */
  ...
  for (i = 0; i < nglobals; i++)
    {
      ...
      /* See if this pseudo has a preference for a particular register. */
```
The "preferences" come from `reg_preferred` — the "preferred register" per pseudo, computed in `global_alloc` via `make_reg_preferred`? Hmm.

In GCC 2.7's global.c, `global_alloc()` has:

```
  /* Process all the globals... */
  ...
  for (i = 0; i < n; i++)
    {
      ...
      /* If the pseudo has a preference (from a copy), use it. */
```
and `dump_global_alloc` prints:
```
      fprintf (dump_file, ";; %d preferences:", regno);
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == regno) ...
```
Hmm, `reg_preferred` is an array indexed by regno giving the preferred reg. So "73 preferences: 4" might print the *preferred reg* of pseudo 73 = 4 (a0).

`reg_preferred` is set in `global.c` by `record_preferences`? Hmm, actually in GCC 2.7 alloc.c/global.c:

```
/* Record a preference for REGNO to be allocated to preferred_regno... */
static void
make_reg_preferred (regno, preferred_regno)
```
called from `global_alloc` when it sees a copy between two pseudos: "if a copy (set (reg P) (reg Q)) exists and one of them is a hard reg, then the other prefers that hard reg".

In our RTL, the copies are: insn 22 `(set (reg:SI 4 a0) (reg/v:SI 74))` → r74 prefers 4 (a0) ✓ (matches "74 preferences: 4").
And insn 53 `(set (reg:SI 4 a0) (reg/v:SI 74))` → same.

But what about r73 (q)? There must be a copy involving r73 and a0 somewhere. Hmm... Let me search the RTL for r73.

In the join block:
```
(insn 101 98 104 (set (mem/s:HI (plus:SI (reg/v:SI 73) (const_int 2))) (reg/v:HI 76))
(insn 104 101 107 (set (mem/s:HI (plus:SI (reg/v:SI 73) (const_int 0x34))) (const_int 0))
```
No copy.

Hmm, so where's the preference for r73? Maybe the dump line ";; 73 preferences: 4" is actually listing the *copies* of pseudo 73? Hmm.

Wait, maybe I mis-assigned. Let me re-read the .greg dump lines:

```
;; 5 regs to allocate: 73 74 76 83 72
;; 72 conflicts: 72 74 83 2 3 4 29
;; 73 conflicts: 73 76 29
;; 73 preferences: 4
;; 74 conflicts: 72 74 83 2 29
;; 74 preferences: 4
;; 76 conflicts: 73 76 29
;; 83 conflicts: 72 74 83 2 29
```

Hmm, "73 preferences: 4" — maybe the format is: for each pseudo, print its preferences (the list of regs it prefers). r73 prefers 4.

Alternatively, maybe the format prints the *copy preferences* — i.e., the pseudos that this pseudo is connected to via copies. Hmm, "preferences: 4" = 4 is a hard reg.

Actually in GCC 2.7 global.c:

```
static void
dump_global_alloc (file)
{
  int i, j, k, n;
  ...
  for (i = 0; i < n; i++)
    {
      r = regno_order[i];
      ...
      fprintf (file, ";; %d conflicts:", r);
      for (j = 0; j < n; j++)
	if (i != j && conflicts_test[j][r]) ...
      /* Print the preferences.  */
      for (j = 0; j < n; j++)
	if (reg_preferred[j] == r) ...
```
Hmm, that would print the *pseudos* that prefer r, not r's preferred reg.

Whatever the exact semantics, both r73 and r74 end up in a0.

The critical question: how do I get r73 (q) into v1 ($3)?

Facts:
- Local alloc ran first and gave v1 to the block-local pseudos: r78/r79 (case 2's const 36864 and slt), r81/r82 (case 1's), and r83 (the switch value, in the entry block).
- Global alloc then assigns: r73 → a0, r74 → a0, r76 → v0, r83 → v1, r72 → s0.

Wait, r83 → v1?! r83 is the zero-extended switch value pseudo, defined in the entry block, used in the entry block. Why is it in the "regs to allocate" list? Because... hmm, r83 is the destination of insn 89 `(set (reg:SI 83) (zero_extend:SI (reg/v:HI 75)))` — a pseudo that is live across a basic block boundary? The switch dispatch: the value is used in insn 92 (jump) and insn 95 (jump) — both in the entry block. Hmm, but GCC's flow analysis might treat the value as live-out of the entry block into... no.

Hmm, whatever. r83 → v1 (allocated globally, since it's in the list). And that's the `lhu v1,2(a0)` + `move v1,v1`? The final asm has `lhu v1,2(a0)` — the zero-extend is folded into the lhu. OK.

So the global allocation order: 73 74 76 83 72. This is the order in which globals are processed. Let me figure out the priority: alloc_table said:
- r73: pri 10000, refs 4, live 8
- r74: pri 10000, refs 4, live 8
- r76: pri 6000, refs 3, live 5
- r83: pri 6000, refs 3, live 5
- r72: pri 4444, refs 4, live 18

So r73 (q) has the HIGHEST priority (10000). Yet it got a0 instead of v1! Why? Because v1 was already taken by the local alloc (r83? no, r83 is global and got v1 later).

Order: r73 processed first. Available regs for it: it conflicts with {73,76,29} → so v0, v1, a0, ... are all free from a conflict standpoint. But the local alloc already gave v1 to r78/r79/r81/r82 (block-local). So at global_alloc time, v1 is "occupied" in the blocks where those locals are live — and r73 (q) is live in those blocks (block 40 and 71 are the arm blocks where the const 36864 lives!). So r73 conflicts with v1 (block-granular) → v1 unavailable → r73 takes a0 (its preference) or the first available.

And in the pinned version, r74 (which is val there, since q is hard) conflicts {72,74,83,2,29} and prefers 4 → a0.

So in the pinned version, the globals are: 74 (=val?), 76, 83, 72. Hmm: in the pinned version, q is hard $3, so the pseudo structure differs: the q loads write directly to $3? Let's check the pinned .rtl.

Actually, more important: in the pinned version, which pseudo got v1? Dispositions: 74 in 4 (a0), 76 in 2 (v0), 83 in 3 (v1). So the same: r83 (switch value) → v1. And the constant 0x9000 in v1 (local). And the q loads → v1 (hard reg).

So in the pinned version, the q pseudo doesn't exist; the load writes to hard reg $3 directly (because q is declared as a register variable with asm("$3")).

So: to get the same, we need the load `lw v1,100(s0)` — the destination must be v1.

Since v1 is "occupied" in the arm block by the local constant 0x9000 (r78/r81) — but the constant dies before the q load, so a *local* q could take v1!

KEY INSIGHT: if q were a LOCAL pseudo (not global), local_alloc could assign it v1 in the arm block, since the constant's v1 dies before q's def. But q is used in the join block (after the switch) → global.

BUT: what if the store to q is moved into each arm (so q is local)? We saw c3 (duplicated stores) still produced a global q... because gcc kept a global val. Hmm, in c3, the value stored was a constant 3/4, and gcc apparently created a global pseudo for the value and kept the stores in the join. Interesting: gcc's "if-conversion"/tail-merging (crossjumping) merged the two arms' tails.

Hmm, in c3 the shape was IDENTICAL to the target except q's reg. So gcc turned my duplicated stores back into the join form. That means gcc recognized the common tail.

Hmm OK. So how else can we get v1 for q?

Option: make the arm blocks' local constant NOT use v1. If the constant 0x9000 were in a different reg (say v0 or a1), then v1 would be free for the global q in the arm blocks.

But the target has the constant in v1! So that's a no-go... unless the constant's reg in the target is v1 because in the target, v1 is FREE for it (q being hard $3 doesn't block it). Hmm, in the target, both the constant and q are in v1 — that requires local_alloc to reuse v1 for the constant (before q's def).

Hmm, so in the target: local const → v1 (local), q → v1 (hard reg). In the lever-free: local const → v1, q → a0.

For the lever-free version to have q → v1, global_alloc must find v1 available for r73. v1 is blocked because the local pseudos r78/r79 (const 36864 and slt) are in v1 in the same block where r73 is live.

What if the constant 0x9000 were NOT in the arm block but computed elsewhere? E.g., hoist the comparison? That changes the code.

What if the slt used a different reg for the constant? The local const gets v1 because local_alloc picks the first available reg in the class order... The local const 36864 could go to v0? But v0 holds the call result. Hmm.

So how to free v1 in the arm block for q? The constant occupies v1 there.

IDEA: What if the comparison is restructured so the constant 0x9000 doesn't need a register at all? E.g. `if (func_8012BD14(ptr) > 0x9000)` → the slt needs the constant in a reg. But what if written as `if (0x9000 < func_8012BD14(ptr))` — same. What about `if (func_8012BD14(ptr) - 0x9000 > 0)`? Different code.

Hmm, what about using an unsigned comparison: `if ((u32)func_8012BD14(ptr) > 0x9000)` → the constant is still needed in a reg.

What if 0x9000 is a *global* constant (e.g. `s32 lim = 0x9000;` at file scope)? Then it'd be in memory, loaded → different code.

Hmm. What if the constant is in a variable that's ALSO used elsewhere, making it a global pseudo? Then global_alloc would assign it a reg... but then it wouldn't be v1-local. Hmm, but wait: what if the constant pseudo becomes global and gets a reg, and the *slt* result...

Let's think about the target shape again: the constant 0x9000 and the slt result are both in v1, and the q load also writes v1 (after the slt). In the lever-free version, the constant and slt are in v1 and q is in a0.

What if we could make the q load write to v1 by making q's *reload* be a copy of something in v1? Hmm.

Alternative idea: make the ARM BLOCKS not contain the constant. What if the comparison is done BEFORE the switch? No — the call is inside the arm.

Alternative: what if we make the *call* not be in the arm? E.g. compute `ret = func_8012BD14(ptr);` before the switch? That changes the code (the call would be before the switch) — different insn order → score.

Hmm.

Alternative: swap the roles: make the *value* (val) the thing that's global and the *pointer* local. Wait — the pointer q must be live in the join (used by the stores). Unless the stores move into the arms (c3 did that but gcc re-merged).

Hmm, in c3 gcc re-merged the tails. But what if the arm bodies were *different enough* that gcc can't merge, yet the resulting code still matches the target? Impossible: the target has one store pair in the join.

What if the stores stay in the join but the *pointer* is computed differently so that the pointer pseudo is not the same across arms? E.g., use a common pointer variable that is set in the entry block? The reload after the call is the issue: the value arg->unk64 must be re-read after the call.

Hmm! What if we read it into a *local* variable in each arm, and then the join uses... no, the join needs the pointer.

What if the pointer is stored in a *global* variable (memory)? Then the join would load it → different code.

Hmm. What about: the join's stores use a pointer that is a *copy* of a local? E.g.:
```
case 2: ... q = ...; val = 3; break;
```
where `q` is declared in an outer scope — that's what we have.

OK here's another thought: what if the number of refs/live of q changes so that its global priority changes... but v1 is blocked by the local const regardless of priority. Actually WAIT. Is it? Let me re-check GCC's global_alloc: when allocating a global pseudo to a hard reg, it checks conflicts with other globals AND with local pseudos? The .greg "conflicts" list for r73 = {73, 76, 29} — it does NOT include 3 (v1). So the conflict computation at the global level doesn't know about v1.

But the *allocation* still avoided v1. Why? Because in global_alloc, when it tries to allocate a reg to a global pseudo, it must ensure the reg is available in all blocks where the pseudo is live — and the local alloc already used v1 in the arm block. In GCC 2.7's global_alloc there's a step:

```
  /* If the global pseudo is live in a block where the hard reg is used by
     a local pseudo, we can't use it. */
```
That's the "block-granular" conflict the note mentions. So v1 is out for r73 because the arm blocks use v1 (by the local const).

And in the pinned version, r73 doesn't exist, so no conflict.

So the lever must free v1 in the arm block. But the target's arm block DOES use v1 (the const 0x9000 and the slt). Hmm, so how could the lever-free version have q in v1 in the arm block? Because the local const's v1 and the global q's v1 would conflict in the arm block... unless the q pseudo is allocated v1 and the local const is allocated something else!

But the target has the const in v1 AND q in v1. In the pinned version, that's possible because q is a hard reg and the local const can reuse v1 where q isn't live (the const dies before q's def) — GCC handles hard-reg pseudos at instruction granularity.

For a global pseudo in v1, the conflict is block-granular, so the local const can't ALSO be in v1 in that block. Hence the lever-free version can never have both the const in v1 and q in v1 in the same arm block...

UNLESS the local const is not in the arm block! I.e., the arm block contains only the q load and the slt result?? Hmm: the const 0x9000 must be in the arm block for the slt.

Hmm, wait. What if the slt is restructured so that the *constant* is in a register that's live across the block... no.

Alternatively: what if the q load happens BEFORE the comparison? I.e., in the arm: `q = arg->unk64;` then `if (func_8012BD14(ptr) > 0x9000) return 0;`. Then in the arm block, the order is: lw q; jal; li const; slt. The q (global, in v1) would be live across the call — then it must be in a callee-saved reg (since it crosses a call) → the target has q in v1 across the call? No! In the target, the q load is AFTER the call.

Hmm, so the target's q load is after the call in the arm, and the const 0x9000 is also in the arm. So both are in the arm block, and in the pinned version they share v1 sequentially.

For a lever-free version, q is a global pseudo in the arm block. Global alloc assigns it a reg; local alloc then assigns the const a reg; they conflict block-granular.

BUT: what if the local const is allocated v1 and the global q is allocated a *different* reg... that's what we have (a0).

What if we could make the *local* const use a reg that's NOT v1, and then global q takes v1? Then the const would be in, say, v0/a1 — but the target has the const in v1. Mismatch → score.

Hmm, unless the const could be in v1 in the *pinned* version for a different reason. Hmm.

Wait wait. Let's reconsider: maybe the local const 0x9000 could be in a different reg in BOTH versions and still match the target? The target IS the pinned version, whose const is in v1. So no.

Therefore: for item 1, the target requires (in the arm block): const in v1, slt result in v1, q in v1. With q as a global pseudo, the block-granular conflict with the local const in v1 makes this impossible... unless the const pseudo is NOT local but global!

What if the constant 0x9000 were a global pseudo (live across blocks)? Then global_alloc would assign it a reg, and the q (also global) would get another. We need both in v1 — impossible for two globals (they'd conflict).

Hmm, unless... the const 0x9000 and q are the SAME pseudo? Ha.

OK so, what if the *value* 0x9000 comparison is done via a different mechanism where the constant is materialized in v1 but is a "hard-reg-only" temporary? Hmm.

What about the possibility of making the q load's destination a hard reg by making q a *function parameter* or something? Not allowed (no signature change).

What about: making q a *local* variable in each arm and having the join use a *different* variable that is global? E.g.:
```
s32 qg;   // global
switch(st) {
case 2: q = arg->unk64; qg = q; val = 3; break;
```
That's still global (qg).

What if the join's stores use a value that comes from a global *pointer* variable, and the per-arm load feeds a local? E.g.:
```
case 2: { s32 ql = arg->unk64; qg = ql; val = 3; break; }
```
qg is still global.

The fundamental issue: the value must flow from the arm to the join → some pseudo is live across the join → global → block-granular conflict with the local const in v1.

Hmm, but wait! Is the conflict really with the const? Let me test: what if the local const were in a1 instead of v1 — then q could take v1. But the target needs the const in v1.

Hmm, hold on. What if the *global* q is allocated v1 and the *local* const is also v1, and GCC allows it because the local const's live range doesn't overlap q's *global* live range? The global q's live range in the arm block starts at its def (the load) — and the const is before that. But the block-granular rule says: a hard reg is unavailable in a block if a global pseudo allocated to it is live *in that block*. Hmm, but here's the thing: is the global q "live in the arm block" at the block level? Yes (it's defined there).

BUT: GCC 2.7's global_alloc has a special case! I recall in global.c:

```
  /* If the global pseudo is not live at the START of a block, we can still
     use the register there... */
```
Hmm, GCC 2.7 global.c has this in `global_alloc`:

```
	  /* If this is a global pseudo that is not live in all blocks... */
```
and there's the concept of "global_reg" for pseudos live in all blocks.

Actually here's the relevant GCC 2.7 code in global.c (function `global_alloc`):

```
  /* Now find the regs to allocate.  */
  ...
  for (i = 0; i < n; i++)
    {
      r = regno_order[i];
      ...
      /* Find a reg to put it in.  */
      for (j = 0; j < n; j++)
	{
	  ...
	}
```
Hmm.

I recall there IS a mechanism: `local_alloc` in GCC 2.7 has a function `find_reg` that checks `reg_availability` and there's the concept of a hard reg being available in a block if the global pseudo using it is not live at the START of the block. GCC's local_alloc computes, for each block, which hard regs are available (`local_alloc` → `allocate_available_regs`), using `regs_ever_live` and the block's live-in info. For hard regs assigned to globals, the availability in a block where the global is live is REG_UNAVAILABLE — but the code in GCC 2.7 local_alloc:

```
      /* Mark the hard registers as unavailable if they are live at the start
	 of this block.  */
```
Hmm.

So the block-granular rule is real.

Given all this, item 1 may be a WALL. But wait — the note says "q cannot become a local pseudo (its two definitions are in two different blocks), and the local constant 0x9000 owns $3 in both of them." That's the prior agent's conclusion. It's a WALL candidate. The task says: "each item was walled before after too few tries; read <dir>/notes.md first, then try new moves." So I need ≥30 scored tries and ≥20 min for a WALL.

Hmm, but let me think about whether there's a clever lever.

Think about the target once more:
```
3fe0 li v1,0x9000
3fe4 slt v1,v1,v0
3fe8 bnez v1,4030
3fec move v0,zero
3ff0 lw v1,100(s0)     <- q in v1
3ff4 j 401c
3ff8 li v0,3
```

What if the q value were loaded in the *entry* block (before the switch) into a register that is callee-saved, and after the call reloaded...? no.

What if the *value* stored (val) is what's global and the pointer is local — i.e., we swap which variable crosses the join? But the stores in the join need the pointer.

Hmm, what if the join's stores are done via a *pointer that is a copy of a local*, i.e. the pointer is passed through a global that's assigned...

Hmm, alternatively: what if the stores happen in the arms, and the *call* func_80178BF8() and the return stay in the join? Then the arm blocks end with the two stores and jump to the join. The join: jal func_80178BF8; lui/addiu; epilogue.

The target: join = `sh v0,2(v1); jal func_80178BF8 (delay: sh zero,52(v1)); lui v0; addiu v0;` then epilogue.

If the stores were in the arms, the code would be: arm2: lw v1,100(s0); li v0,3; sh v0,2(v1); sh zero,52(v1); j join; arm1: same with 4. That's 2 extra instructions and a different structure → score > 0.

Unless gcc's crossjumping merges the arms' tails into the join — which is exactly what happened in c3! In c3 the result had the stores in the join. So gcc's crossjumping (jump.c) merged the identical tails. But then the q pseudo became global again (r73 defined in both arms) and the problem returned.

Hmm, but hold on: in c3, why did gcc keep the stores in the join? Because the arms were identical after the store... The merge happened at the block level, so the q pseudo is still defined in 2 blocks.

Hmm, what if we make the arms' tails *different* so no crossjumping happens, but the code still matches the target? Impossible.

What if we avoid the crossjump by making the two arms' *stores* differ (e.g. val 3 vs 4 stored at different points) — but the target has the same shape.

OK, alternative approach: what if `q` is not a variable at all but the *expression* is repeated? I.e.:

```
case 2:
   ...
   ((Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64)->unk2 = 3;
   break;
```
Then the join has no pointer... but the stores must be in the join (target shape). Hmm, but if each arm stores directly, the shape changes (2 stores in arms). But maybe crossjumping merges them → back to the same.

Hmm, but here's the thing: if the stores are in the arms, then each arm's q is a LOCAL pseudo → local_alloc assigns it v1 (if free in that block — the const 0x9000 is in v1 but dies before the q load... wait, order in the arm: call, li const, slt, bnez, (then) lw q, li val, sh v0,2(q), sh zero,52(q)). The const's v1 dies at the slt, so the local q can take v1! And the local val (3) would take v0? The const is in v1 (live at slt), the call result in v0, so val=3 would need another reg... In the target, `li v0,3` is after the call result v0 dies (the slt consumed it) → v0 is free. So local val → v0.

So a local q in the arm would land in v1! And the shape would be:
```
 arm2: lw v1,100(s0); li v0,3; sh v0,2(v1); sh zero,52(v1); j join
```
Hmm, but wait: if the store is in the arm, the join has only the call and the return. The target's join has the stores. So the code differs → score.

Unless gcc's crossjumping re-merges. In c3, gcc DID merge (the stores ended up in the join) and produced the exact target shape except q's reg. Interesting!! So c3's result: `lw a0,100(s0)` (q in a0) and the stores at the join.

Hmm, so in c3, after crossjumping, the q pseudo became global (defined in 2 arms) → global alloc → a0.

Hmm, so what if the arms' tails are NOT identical so crossjumping doesn't happen, but... no.

What if there's only ONE arm that reaches the join with a q? E.g., restructure the switch so that the q load happens in ONE place? The target has the load in both arms (2 loads). So no.

Hmm, what if the two arms' q loads are the same pseudo but the pseudo is *local*? A pseudo defined in 2 blocks can't be local.

What if the q load in the second arm is a *copy* from the first? no.

OK, so item 1 looks like a genuine wall. But the brief wants me to spend ≥20 min and ≥30 tries before calling it a wall. Let me think about other angles:

Angle A: Make the arm block NOT contain the local const 0x9000 — impossible without changing the code.

Angle B: Make the global q NOT live in the arm block: the q load is in the arm block. Its live range starts there. Unavoidable.

Angle C: Make the *global* q's assigned reg v1 by changing the local const's reg — but the target requires v1.

Hmm, wait! Actually — hold on. What if the local const 0x9000 in the arm block could be assigned to v1 AND the global q also v1, if the global q is allocated v1 and the local const is then forced elsewhere... but the target says the const is in v1.

Unless the local const in the target is in v1 for a *different* reason: in the pinned version, the local const's v1 assignment is allowed because the hard reg $3 is free at that point (q's hard $3 is born later in the block). If in a lever-free version the const were in, say, a1 and q in v1, the asm would differ from the target in the const's insn (`li a1,0x9000` vs `li v1,0x9000`) → score.

Hmm, so the ONLY way to have both in v1 is if q is a hard reg (the pin) — the very thing we're removing.

UNLESS: q's pseudo is a LOCAL pseudo in a block where the const is also local, and the two are sequential. The q pseudo must be local → defined and used in one block → the stores must be in the arm → shape changes... but the crossjumping re-merges. Hmm, but what if the crossjump merge does NOT happen? Then the shape differs.

Hmm, hold on! What if we could get BOTH: the stores in the arms (local q in v1) AND the merged shape? The merge (crossjumping) is what makes it global again. Is there a way to prevent crossjumping while keeping the target shape? The target shape has ONE store pair in the join. If the stores are in the arms, crossjumping merges them into the join — but then the q pseudo is defined in 2 blocks → global. Hmm, but does crossjumping really *merge* the blocks, or does it just *reorder* them? GCC's crossjumping (jump.c `cross_jump`/`tail_merge`) merges identical blocks: it finds two blocks with identical tails and redirects one to the other. The resulting code has ONE copy of the tail (the join), and the q pseudo is defined in both arms (each arm still has its own load).

Right: the q pseudo has 2 definitions (one per arm) regardless. So it's global. The crossjump doesn't change that.

So: for q to be local, q must be defined in only ONE block. The target has 2 loads → 2 definitions → global. Unless... one of the loads is a *reload* of the same pseudo? Still 2 defs.

Hmm, BUT: what if the two loads are in the same block? They're in different arms (blocks 40 and 71). What if the source were restructured so that the two loads are in ONE block? E.g.:

```
switch (st) {
case 2:
    if (call > 0x9000) return 0;
    val = 3;
    /* fallthrough to common code */
case 1:
    if (call > 0x9000) return 0;
    val = 4;
}
q = arg->unk64;   // common, one block
stores...
```
But the target has the load in BOTH arms (2 loads: at 3ff0 and 4014). If the source has one load, gcc emits one load → the instruction count differs (39 vs 40) → score. Unless gcc duplicates it (it can't).

Hmm. So the target's 2 loads are inherent. Both arms load. So q has 2 defs → global.

Therefore, the q pseudo is global and the block-granular conflict with the local const in v1 blocks v1.

Hmm, unless the conflict is computed differently: GCC's global_alloc checks whether the reg is "available" in the blocks where the global is live. If the global q is live in blocks 40 and 71 (and 98), and v1 is used by locals in blocks 40 and 71 → v1 unavailable.

What if q were live in only ONE of those blocks? E.g., if the q load in one arm were dead? No.

OK, so what if we make the *other* arm's q load not exist but keep the instruction count? No.

Alright: maybe the answer for item 1 is a WALL with a precise mechanism. But before that, let me consider: maybe the target's `q` in $3 could be achieved by a different global alloc order where the *value* pseudo (r76) takes v1 and q takes... no, the target has the value in v0.

Hmm, let me reconsider the whole thing. What if we ELIMINATE the val pseudo and the const pseudo, e.g., by restructuring the switch so that the arms are:

```
case 2: if (call > 0x9000) return 0; val = 3; q = load; break;
```
The global pseudos would be q and val. Their allocation: q (higher priority) gets the first reg. If the first reg is v0, then q → v0 (wrong).

Honestly, let me try a bunch of variants empirically and see if any gets closer than 4. The score metric: 4 = 4 differing instructions. Can we get to a state where only the const's register differs? That's still 4ish.

Let me think about what "PARTIAL" means here: the kinds are "pin" only, so PARTIAL would be a body that keeps the pin... no: PARTIAL:<kinds still kept> = "win.c scores 0 keeping only those levers". For kind=pin, PARTIAL:pin means the win.c keeps the pin and scores 0 — that's the original def (trivial). Hmm, but the pin is what we're removing. So PARTIAL isn't useful here; we need MATCH (score 0 with no pin) or WALL.

So item 1: aim for MATCH; else WALL with the best score.

Before declaring the wall, let me try a bunch of real variants. Let me list candidate ideas:

1. q as `Unkstruct_801815AC_3 *` (pointer) — tried (c4): score 4.
2. Inline ptr (c2): score 4.
3. Duplicate stores (c3): score 4.
4. Declare q before ptr / after val (decl order).
5. Make val a u8/u16/s16 (widths).
6. Use `s16` for st.
7. Restructure the switch to if/else (no switch) — changes the dispatch code → different insns.
8. Make q a `u32`.
9. Init at decl: `s32 q = 0;`
10. Pointer reuse: use a `u16 *` for the stores.
11. Change the store order.
12. Use `arg` directly instead of ptr.
13. Make the call result comparison use a temp: `s32 r = func_8012BD14(ptr); if (r > 0x9000)`.
14. Combine the two arms' loads: `q = arg->unk64;` before the switch (changes shape).
15. Make the function use a local `s32 base = (s32)arg;`.

Let me try a batch of these and observe. Each takes ~1s to score. Cheap. Let me do 10-15 variants.

Actually, first, an important consideration: does the *pin* variant (the original) still score 0? Let me verify that the current src def (with the pin) scores 0 — that's the baseline for "MATCH = score 0". Let me score orig.c. If orig.c doesn't score 0, then the build is stale vs src and I'd need to regenerate. Let me check that now — important!
