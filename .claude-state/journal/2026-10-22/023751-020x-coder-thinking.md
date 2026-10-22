---
ts: 2026-10-22T08:37:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JHcg6vAJxAsvdKs1Zk0o
---
Good. Now let me set up the item dir and start experiments.

Let me create orig.c (copy of the src def) and check it matches. Then write candidates.

Note the brief: "at each item's start diff <dir>/orig.c against the def in the current src file (src moves as earlier batches bank); if it differs, regenerate orig.c/nopin.c from src and say so in notes.md". There's no orig.c yet in the dir, so I create it.

Let me write orig.c = exact src def (lines 5030-5058).

Then experiments. Let me create a scratch dir .run/P40/T11/RM1x/<item>/cand/ for candidates? The brief says every file under .run/P40/T11/RM1x/. Fine, put candidates in the item dir.

Let me do this for item 1.

Candidates for item 1:
- c2.c: q as struct pointer type.
- c3.c: q with extra use (can't, changes code).
- c4.c: val as u16, q as s32, etc.

Let me think harder about the register allocation, since blind search is expensive.

The target asm again:
```
 3fa8 addiu sp,sp,-24
 3fac sw s0,16(sp)
 3fb0 move s0,a0
 3fb4 sw ra,20(sp)
 3fb8 lw a0,100(s0)      ; ptr = arg->unk64
 3fbc nop
 3fc0 lhu v1,2(a0)       ; st
 3fc4 li v0,1
 3fc8 beq v1,v0,3ffc
 3fcc li v0,2            ; delay slot
 3fd0 bne v1,v0,4030
 3fd4 move v0,zero       ; delay slot: return 0
 3fd8 jal func_8012BD14
 3fdc nop
 3fe0 li v1,0x9000
 3fe4 slt v1,v1,v0
 3fe8 bnez v1,4030
 3fec move v0,zero
 3ff0 lw v1,100(s0)      ; q
 3ff4 j 401c
 3ff8 li v0,3            ; val=3 (delay slot)
 3ffc jal func_8012BD14
 4000 nop
 4004 li v1,0x9000
 4008 slt v1,v1,v0
 400c bnez v1,4030
 4010 move v0,zero
 4014 lw v1,100(s0)      ; q
 4018 li v0,4            ; val=4
 401c sh v0,2(v1)
 4020 jal func_80178BF8
 4024 sh zero,52(v1)     ; delay slot
 4028 lui v0,0x0 (func_80172710)
 402c addiu v0,v0,0
 4030 lw ra,20(sp)
 4034 lw s0,16(sp)
 4038 addiu sp,sp,24
 403c jr ra
 4040 nop
```
Interesting: in the case-1 arm, `li v0,4` at 4018 is right after `lw v1,100(s0)` at 4014, and the join is at 401c. In case-2 arm, `li v0,3` is in the delay slot of the j.

Now in mine (lever-free), the differences are only q in a0. So mine:
```
 lw a0,100(s0)   ; q
 sh v0,2(a0)
 sh zero,52(a0)
```
Wait, but then in mine, is `a0` also the call arg? The call `jal func_8012BD14` takes ptr in a0 (loaded at 3fb8). After the call, a0 is free, so q reuses a0. In the target, q is in v1 because a0 was... hmm, in the target a0 is free too after the call. So why doesn't the target use a0 for q? Because q is pinned to $3.

So in mine, gcc's global_alloc chose a0 for q. Question: why a0 and not v1($3)? Because in the global allocation, priority ordering. GCC 2.7 global_alloc: it iterates over global pseudos in priority order (from `allocno`? no, for globals it's `reg_alloc_order`?), and assigns to the first available hard reg from the class's REGS list, with conflict checks.

Hmm, in GCC 2.7 alloc.c, global_alloc():
- It computes `global_conflict_sets` for each global pseudo.
- Then it processes global pseudos in order of `regs_ever_live`? Let me recall the code:

```
  /* Now allocate the hard registers among the globals.  The globals are
     considered in the order of their priority (number of references). */
  for (i = 0; i < n; i++) { ... }
```
Actually GCC 2.7's global_alloc has two phases: first it handles globals that are "not live in all blocks" with the "global_reg" stuff, then:

```
  /* Now allocate the hard regs to the globals.  */
  ...
  for (pass = 0; pass < 2; pass++)
    for (i = 0; i < nglobals; i++)
      {
        r = reg_alloc_order[i];
        if (reg_renumber[r] < 0 && ! conflicts) ...
```
It allocates based on `reg_alloc_order` which is sorted by "priority" (number of refs × ...). Then it picks the first reg in the class's REGS list that isn't taken.

The order of the REGS list for the class: for MIPS general regs, the allocatable order is typically $2,$3,$4,...,$15,$24,$25 (v0,v1,a0-a3,t0-t9,s8) or with a preference. Actually GCC's global register preference ordering via `REG_ALLOC_ORDER` in mips.h sets specific ordering.

But important: the constant 0x9000 is a *local* pseudo (block-local) so it doesn't participate in global_alloc. Then local_alloc runs and assigns $3 to the constant. But global_alloc ran BEFORE local_alloc and would have assigned $3 to q... unless q wasn't eligible.

Unless: global_alloc assigned q to $4 because $2 (v0) and $3 (v1) were already taken by other globals: val (v0) and st (v1)?!

st is `u16 st` — it's live from the load (3fc0) to the switch comparison (3fc8/3fd0). It's block-local? It's defined in the entry block and used in the entry block → local pseudo. But maybe global because... it's used only in entry block → local.

val is defined in two arms, used in join → global pseudo! val in $2 (v0). So global_alloc assigned val → $2. Then q → next free = $3? But mine gave q → $4.

Hmm, so something took $3 in global_alloc. Maybe the `st` pseudo or the constant? The constant 0x9000 might be a global pseudo if the comparison is in a block... it's in the arm blocks, defined and used there → local.

Hmm, but GCC's `global_alloc` may consider pseudos live in multiple blocks as global: q is global (def in 2 blocks, use in join). val is global. So global_alloc assigned val→$2, q→$3? But mine has q in $4.

Wait, maybe global_alloc assigned q → $3 and then local_alloc found the constant needed $3 in the blocks where q is live... no wait, the constant is BEFORE q's def within the block. But local_alloc works on a per-block basis with the "live at block start" info: for a global pseudo in hard reg $3, at the start of the arm block, is $3 live? q's global live range starts at its def (in the arm). GCC's local_alloc: for a block-local pseudo, it can use a hard reg if the hard reg is not live at that point. The hard reg's live range = the global pseudo's live range. In the arm block, at the block start, $3 is not live (q is defined later), so the constant can take $3 at the top of the block. Then when q is defined at 3ff0, $3 is live from there.

But in mine, the constant took $3 AND q got $4. So maybe global_alloc picked $3 for q but then discovered the conflict with... no.

Alternative explanation: GCC's global_alloc in 2.7 has this logic: for each global pseudo, it computes the set of conflicting hard regs via `global_conflict_sets`. If the pseudo's conflict set is all regs, it's not allocated. For a pseudo that's live in only a few blocks, the conflicts are computed... Then there's the "one register might be allocated to a global pseudo and also to a local pseudo in a block where they don't overlap" case handled by local_alloc.

Hmm, but actually here's a thought: in GCC 2.7, global_alloc's assignment loop has a special rule: it prefers to allocate a global pseudo to a register that is NOT live in the blocks where the pseudo is defined, etc.

Let me instead check gcc 2.7 source. Is the source available? Let me look for it in the repo (maybe under disks/ or tools/bin). Probably not.

Alternative empirical approach: try many C-level variants and see. Let's think about what C-level changes might alter q's register:

Variant A: q as pointer type `Unkstruct_801815AC_3 *q;` — q's value is a pointer; global_alloc might treat pointer pseudos with a different priority/reg class ordering (pointers often prefer callee-saved $s regs!). In the target q is in $3 (call-clobbered) — if I make q a pointer, gcc might put it in s3 (callee-saved) → worse.

Variant B: Make q's def in the two arms *different* (e.g. use two variables q1, q2)? Then no join use → not global... but then the stores would be duplicated. Hmm: 
```
case 2: ... q2 = arg->unk64; val=3; break;
```
and in the join we need one q. Nope.

Variant C: Restructure so the switch has a single exit path and q is assigned before the switch? Not possible (reload after call).

Hmm wait — actually is it necessary to reload after the call? The compiler must reload because the call may modify memory. But if the source said `q = ptr;` (copy of the already-loaded value) instead of reloading `arg->unk64`, then gcc would keep q = ptr's value... but ptr is in a0 and would need to survive the call → it'd be saved in s0? no, s0 holds arg. It'd be spilled or moved to another callee-saved reg → different asm (no `lw v1,100(s0)` after the call, but a move instead). Target has the reload, so the source must reload. Since the current src reloads, keep it.

Variant D: Change the *order* of the stores, or use `((Unkstruct_801815AC_3 *)q)->unk2 = val;` vs a pointer variable.

Variant E: Make `q` used in the comparison too? no.

Variant F: What if we introduce an extra global pseudo that competes for $3, pushing... no, we want q in $3.

Variant G: The note says the constant owns $3 in both arms. What if the constant were spelled so that gcc uses a different register for it, e.g. `if (func_8012BD14(ptr) > 36864)` (decimal)? Same value, same code.

What if the comparison constant is loaded via a variable that gcc keeps in a callee-saved reg? No, that changes code.

Hmm, so the target has the constant in $3 AND q in $3 — that requires the pinned behavior (hard reg). Because with a pseudo q, gcc's global_alloc picks a reg for q first (before local_alloc assigns the constant) — so q should get $3 unless global_alloc skipped $3.

Wait... maybe global_alloc's order: it processes globals and there's a rule that a global pseudo can only be assigned a hard reg that is not "conflicting" — and the conflict set for q includes $3 because of the constant?? No, the constant isn't a global.

Alternatively maybe global_alloc assigns q → $3 but then the *conflict* with the block-local constant is detected and it moves q to another reg? Hmm, in GCC 2.7's global_alloc, after allocating there's a step: "If a global pseudo was allocated a hard reg that conflicts with local pseudos in some block, ..." Actually there IS such a mechanism! In GCC 2.7 alloc.c global_alloc():

```
  /* If a global pseudo is allocated a hard register that is not available in
     all the blocks where it is live, we need to check... */
```
Hmm. I recall `local_alloc` handles the case where a local pseudo and a global pseudo want the same hard reg: local_alloc's `find_reg` with `reg_availability` — for hard regs used by globals, the availability in a block is computed by `local_alloc` from the global's live range... The constant pseudo needs a reg and all "preferred" regs might be unavailable because $2, $3 are taken by globals (val in $2, q in $3) — but they're not live at that point in the block! GCC's local_alloc does compute per-block availability of hard regs: `local_alloc` for a block uses `reg_availability` and for hard regs occupied by globals, the "REG_AVAILABLE" status. There's code in GCC 2.7 local_alloc:

```
	  /* If the hard register is occupied by a global pseudo which is live
	     at the start of the block, ... */
```
And in `local_alloc` there's the notion that a hard reg allocated to a global pseudo is only unavailable in blocks where the global is live at that point... but GCC 2.7 computes this at block granularity! Yes — that's exactly the note's "its conflict set is block-granular". In GCC 2.7, `local_alloc` calls `find_reg` which uses `reg_availability` initialized per block from `regs_ever_live`/`reg_live_at_block_start` — block-granular. So a global pseudo in $3 makes $3 unavailable for the whole block (since it's live at block start? no, q isn't live at block start of the arm...).

Hmm, but if q is in $3 and q is defined in the arm block, then at the block start $3 is not live. Unless GCC's block-granular check uses the global's live range spanning blocks: q's live range covers from its def in the arm to the join, so in the *entry* block q is not live. In the arm block, q is live from the def.

But GCC 2.7's local_alloc computes availability of hard regs at the start of each block; a hard reg allocated to a global pseudo is considered unavailable in blocks where the pseudo is live (i.e., blocks in its live range) — but here the live range starts mid-block, so GCC's block-granular approximation makes $3 unavailable for the whole arm block. So the constant would NOT get $3... but the target shows it does!

Contradiction. Unless in the target case, the constant pseudo isn't given $3 by local_alloc but... hmm.

Hmm, wait. Let's re-read: in the target, `li v1,0x9000` — v1 is $3. And q is $3. But q is a *hard* reg in the target (pinned). When q is pinned to $3, gcc's global_alloc doesn't allocate it (it's already a hard reg); the constant pseudo then goes to local_alloc which can use $3 in the arm block only if $3 is not live at block start... same problem! But the target shows it IS used.

Unless GCC's local_alloc, when a hard reg is occupied by a *hard-reg pseudo* (not a global pseudo), can use it when the pinned pseudo isn't live yet within the block (finer granularity for hard regs?). Actually yes! In GCC 2.7 local_alloc there's a distinction: hard regs used by *local* pseudos vs globals. Since q is pinned (a hard-reg pseudo), the conflict is computed within the block at instruction granularity, allowing the constant to use $3 before q's def.

Whereas if q is a global pseudo assigned $3 by global_alloc, then $3 is "occupied" for the whole block (block-granular), so the constant can't use $3 → and then... hmm, but then why did the constant get $3 in MY version? In my version q got $4 and the constant got $3. So in mine, $3 was free for the constant (since q is in $4) and $3 was the natural choice for the constant.

And in the target, $3 is occupied by q but the constant still gets $3 (because a pinned hard-reg pseudo allows intra-block reuse).

OK so the mechanism is clear-ish. Now: how to get q (a pseudo) into $3 in a lever-free way?

Option 1: Make q NOT a global pseudo — make it local to a block. Then global_alloc doesn't touch it, and local_alloc allocates it... but local_alloc prefers to use the "preferred reg" list and for a local pseudo it may choose $3 (v1) if free at block granularity. But q is defined in one arm and used in the join → global. Unless we restructure so the store happens in the arm.

Restructure idea: duplicate the tail stores in both arms, then q becomes local to each arm. Then each arm: `q = arg->unk64; ...; ((Unkstruct*)q)->unk2 = val; ((Unkstruct*)q)->unk34 = 0;` But then the call func_80178BF8() and the return must also be duplicated or the arms jump to a common tail. The target's join block does: sh v0,2(v1); jal func_80178BF8 (delay sh zero,52(v1)); lui/addiu v0; then falls to the epilogue.

If we duplicate the stores into each arm but keep a common tail for the call+return, we'd get: arm2: lw v1,100(s0); sh v0,2(v1); sh zero,52(v1); j tail... The instruction count would differ from the target (the target has 2 store instructions total; we'd have 4). Score = number of differing instructions... Actually the score metric counts mismatched instructions in a diff alignment; adding instructions gives score > 0.

Hmm. Unless the duplicated version can be merged by gcc (tail merging / crossjumping) back into the target shape! GCC 2.7 does crossjumping (tail merging) in the `jump` pass — it merges identical blocks. But the arms differ in `val` (3 vs 4), so the blocks aren't identical... but after the store, the code is the same except the value stored.

Hmm. What if we restructure so that the store value is computed per-arm but the *pointer* is the same expression, and gcc's tail merging merges the identical tails?

Alternative: keep the switch but compute val in each arm and let a single join do the stores — that's the current structure.

Option 2: Make the *constant* not compete: what if the comparison `func_8012BD14(ptr) > 0x9000` is written so that gcc generates the same instructions but the constant pseudo is not live in the same block... it's inherently in the same block.

Option 3: What if q is not a pseudo but rather gcc keeps it in a hard reg because it's used as a *call argument*? No.

Option 4: Change the *number* of global pseudos so that global_alloc gives $3 to q. In mine, q got $4 — meaning $2 and $3 were both unavailable/prioritized to others. $2 = val (global). $3 = ? Something else took $3 in global_alloc. What global pseudos exist? ptr (a0 - loaded at 3fb8, used for call arg and st → dies in entry block → local), st (u16, entry block → local), val (global, $2), q (global).

Hmm, so why did q get $4 and not $3? Maybe because global_alloc assigns in priority order and the reg preference: q is `s32`, and the reg preference order for MIPS might be $4(a0) before $3? GCC's REG_ALLOC_ORDER for mips:
```
#define REG_ALLOC_ORDER \
  { 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, ... }
```
Hmm, MIPS has a REG_ALLOC_ORDER in mips.h listing a0..a3, t0..t9, s0..s7, etc. Actually, GCC's global_alloc for a class picks regs in the order of the class's REGS array (reg_class->regs), not REG_ALLOC_ORDER... but global_alloc does use `reg_alloc_order` for globals I think.

In GCC 2.7 alloc.c global_alloc:
```
  /* Now allocate the hard regs to the globals.  */
  ...
      for (i = 0; i < n; i++)
	{
	  ...
	  if (reg_renumber[r] < 0 && ...)
```
Hmm, I recall in GCC 2.7:
```
  /* Sort the globals by priority.  */
  qsort (regno, nglobals, sizeof (regno[0]), regno_compare);
  ...
  for (i = 0; i < n; i++)
    {
      r = regno[i];
      ...
      for (j = 0; j < n; j++) ...
```
Honestly, experimenting is faster.

Note the moves.md entry: "pin | func_80184F18 | MATCH — u16 t (HImode copy escapes cse equiv) + u = arg2 + 0xD40 late: arg2 parm live long, &mtx wins s1 (W01)". And "pin | func_80188680 | WALL lreg-v0-local-first".

Let me think about what levers are available per the constraint list: "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)".

So the move space is limited. For item 1 (pin $3 for q), we need q to land in $3.

Hmm, what about "pointer reuse": use a pointer variable for q:
```
Unkstruct_801815AC_3 *q;
...
q = (Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64;
...
q->unk2 = val; q->unk34 = 0;
```
This makes q a pointer pseudo. Pointer pseudos in GCC get higher priority in local alloc (they're often "address" pseudos?). Hmm.

Actually here's a thought: global_alloc priority is based on the number of references (refs). Currently q has 4 refs (2 defs + 2 uses)? and val has 2 refs. If q had MORE refs (e.g. more uses of q), its priority would rise and it might get $3 instead of $4 — but the reg choice order matters.

But wait, why did q skip $3? Maybe because $3 was taken by ANOTHER global pseudo that I haven't noticed. Let's check: in mine, `st` is u16 loaded via lhu v1,2(a0) — st is in v1 ($3)! Yes!! In the target, `lhu v1,2(a0)` — st is in $3 too! And the constant 0x9000 is also in $3 (sequentially). So $3 in the target holds: st (entry block), constant (arm blocks), q (arm+join).

In mine, the same: st in $3, constant in $3, and q in $4.

So in global_alloc, st and q are both global? st is used only in the entry block (2 uses) → local pseudo. Hmm.

But wait — maybe st is a *global* pseudo: it's defined in the entry block, and the switch's case dispatch uses it. Still entry block. Local.

Hmm, but the lhu result in $3 in the target: local_alloc gave $3 to st (block-local). And q in $4.

So who took $3 in global_alloc? If nobody, q would get $3 (if the reg order prefers $3 over $4). Since q got $4, either $3 was taken by a global pseudo in global_alloc, or the reg order prefers $4.

Possibility: the global pseudos are val and q. Global_alloc assigns them in priority order: val first (higher priority: more refs? val has 2 defs + 1 use = 3; q has 2 defs + 2 uses = 4?). Hmm, q should have higher priority then, and get the first reg.

Ugh, speculation. Let me do the empirical thing: build variants and look at the output asm. I'll write a small script that compiles a body and dumps the asm for the function, so I can iterate quickly without the full scoring.

How does delever_search compile? Let me look at tools/delever.py's compile function to replicate. Let me grep for "cpp" and "as" in delever.py.
