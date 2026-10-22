---
ts: 2026-10-22T08:40:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Vu3MoBjhkVcpnx7QRSWd
---
Very interesting! c3 (duplicated stores in the arms) produced EXACTLY the target shape except q is in a0 instead of v1! Wait — the stores are at the join (401c) even in c3? Yes: gcc merged the tails via crossjumping (the identical tail after the store). Actually wait, c3 has the stores in each arm with different values (3 and 4) — but the asm shows `sh v0,2(a0)` at the join with v0 = 3 or 4. So gcc did NOT duplicate the stores; it kept val as a global pseudo and merged. Hmm, actually gcc recognized the pattern? The arms now are: lw a0,100(s0); sh v0,2(a0)... no, the asm shows at 3ff0: lw a0,100(s0); j 401c; delay li v0,3 — so gcc turned the constant store into a global val pseudo and put the store at the join! That's gcc's "if-conversion"/tail merging or just the fact that storing a constant 3 and 4 → gcc kept `val` as a variable? Hmm, weird but the shape is identical to the target except the register of q.

Wow, so c3 gives the same 39 instructions and the same layout as the target, with q in a0.

So the entire problem reduces to: get q into $3 (v1).

In c3, the value is a global pseudo (val) and q is a global pseudo. Both globals. gcc allocated val → $2, q → $4.

Note the target: val → $2, q → $3, ptr → $4.

So in the target, the global allocation gave $2 to val, $3 to q, $4 to ptr. In mine, $2 to val, $4 to ptr and q, i.e. $3 was skipped for q!

Why would $3 be skipped? Because the block-local constant 0x9000 uses $3! And global_alloc... hmm, but global_alloc runs before local_alloc. Unless in GCC 2.7 the order is: local_alloc for blocks first? Let me check GCC 2.7's alloc.c order.

GCC 2.7.2 alloc.c `allocate()`:
```
  /* Now allocate the hard regs... */
  ...
  /* Perform global register allocation */
  global_alloc ();
  ...
  /* Now do local allocation */
  local_alloc ();
```
Hmm, I'm fairly sure global comes first in GCC 2.x. But actually there's a subtlety: in GCC 2.7's global_alloc, there's a step where globals that are live in only a few blocks and whose conflict sets are computed "per block". The global conflict computation `global_conflict_sets` computes for each global pseudo the set of hard regs it conflicts with, based on the regs live in the blocks where it's live. The constant 0x9000 is a LOCAL pseudo, not hard, so it doesn't conflict at global_alloc time.

Then global_alloc allocates q → $3 (if $3 free). Then local_alloc, in the arm block, needs a reg for the constant 0x9000; $3 is occupied by the global q → the block-granular availability says $3 is unavailable in that block (since q is live at block start? no...). Actually GCC 2.7's local_alloc computes for each hard reg whether it's available at the start of the block: `local_alloc` uses `regs_ever_live` and the hard reg's "global" usage. There's a function `find_reg` which checks `reg_availability` per block. For a hard reg allocated to a global pseudo, the availability is computed by `local_alloc`'s call to `allocate_available_regs`...

Hmm, GCC 2.7 has in local_alloc:
```
	  /* Mark the register as unavailable if it is occupied by a global
	     pseudo that is live in this block.  */
```
It uses `reg_availability` computed by `local_alloc`'s initialization:
```
  for (i = FIRST_PSEUDO_REGISTER; i < FIRST_PSEUDO_REGISTER + ...; i++)
```
Actually I recall in GCC 2.7 alloc.c local_alloc:
```
  /* Find the first register in the class that is available... */
  ...
  /* If we have a hard register that is used by a global pseudo, we can only
     use it if the global pseudo is not live at the start of this block... */
```
Hmm.

Empirically: In my version, the constant took $3, meaning $3 was free during local_alloc → so q was NOT allocated $3 in global_alloc. So global_alloc gave q something else. What? $4 (a0). But $4 was also ptr's reg. Both ptr and q in $4 sequentially? That means global_alloc assigned q → $4 as well?! Two globals can't have the same hard reg unless their live ranges don't overlap — global_alloc handles that: a hard reg can be assigned to multiple globals if they don't conflict (conflict computed block-wise with liveness). ptr's live range ends at the call in the arm block, q's begins after → they don't conflict within blocks?? But global conflict sets are block-granular: in the arm block, both ptr and q are live (in different sub-ranges) → they'd conflict.

Hmm, unless global_alloc uses a more precise liveness. GCC 2.7's global_alloc has two phases: first it assigns regs to globals that are live in ALL blocks (the "global register" candidates), then for the rest it uses "one reg per global" with conflict sets computed by `global_conflict_sets` which uses `CONFLICT_INFO` per block...

OK, enough theory. Empirical approach: try to make q get $3.

Observations to exploit: In the target, the order of globals: val→$2, q→$3, ptr→$4. So the allocation order (priority) seems: val first ($2), then q ($3), then ptr ($4)? Or the reg order is $2,$3,$4 and the priority order is val, q, ptr.

In mine: val→$2, then $3 skipped for q (taken by local const later?), ptr→$4... but then q → ? If the reg order is $2,$3,$4 and priority order val,q,ptr: val→$2, q→$3, ptr→$4 = target. But mine has q→$4 and ptr→$4? Can't both be $4.

Unless in mine, ptr is NOT a global! Let me check: in mine the `lw a0,100(s0)` at 3fb8 → a0 holds ptr, used at 3fc0 (lhu) and at the call (jal at 3fd8/3ffc). The call is in the arm blocks → ptr is live in the arm blocks → ptr is global. Hmm.

Unless the call arg is a *separate* pseudo from ptr (the copy for the call arg). GCC creates a copy of ptr for the call argument if needed. If ptr is not modified, the call arg is just ptr itself.

Hmm, in the target: `jal` at 3fd8 has the arg in a0 — but a0 at that point holds... the initial ptr load was `lw a0,100(s0)` at 3fb8 → a0 = ptr. Then at the call, a0 = ptr (no move needed). But wait, in the arm block, ptr is still in a0 → so a0 is live across the branch → ptr global in $4.

Then q also in $4 in mine? The stores use a0, and the loads use a0. But there's no move between them: `lw a0,100(s0)` reloads q into a0. So q's value is loaded into a0 directly. So q is in $4 = a0, and ptr is in $4 = a0, sequentially. Both are globals in $4? That can happen if global_alloc assigns $4 to a *group* of globals that don't conflict... but they do conflict in the arm block (ptr live until the call, q live after). Actually no! They don't overlap in life even within the block: ptr dies at the call (its last use is the call arg at 3fd8), q is born at 3ff0. So they don't conflict even at instruction granularity. But global conflict sets are block-granular in GCC 2.7 → they'd be considered conflicting → different regs.

Unless GCC's global_alloc in 2.7 does use finer granularity... The target has ptr→$4 and q→$3 (different), mine has ptr→$4 and q→$4 (same). So in mine, GCC merged them; in the target (pinned), q is $3 hard.

So in mine, global_alloc gave q → $4 (sharing with ptr) and skipped $3. Why skipped $3? Because $3 was taken by a global that conflicts with q? Which global could be in $3? `st`? st is u16, defined in entry, used in entry only → local. But hmm, maybe st IS global: the switch dispatch... no, entry block only.

Wait — maybe `val` is not in $2 as a global but the call result? `li v0,3`/`li v0,4` — val is a global in $2.

Hmm, so globals: ptr, val, q. $2→val, $3→?, $4→ptr+q.

What if $3 was given to `st`?! st is u16 in $3: `lhu v1,2(a0)` at 3fc0 → v1 = $3. If st were global, it'd take $3 and conflict with q → q goes to $4. And in the target, st is ALSO in $3 (lhu v1,2(a0) — same instruction!) and q is in $3 too. Hmm, so in the target st and q share $3 — but st dies before q is born, so if st were global in $3, the pinned q ($3 hard) would conflict... but the pinned q is a hard reg, and the compiler allows the hard-reg q to reuse $3 where st ($3, local?) isn't live.

So st is LOCAL (block-local in the entry block) — it gets $3 from local_alloc (or from the class order). And the constant 0x9000 also gets $3 in the arm blocks (local). So local_alloc gives $3 to st (entry) and to the constant (arms).

Now the question stands: why does global_alloc skip $3 for q?

Possibility: global_alloc processes globals in priority order and tries regs in the class order; $3 might be tried but rejected due to the *conflict set* of q computed by global_conflict_sets, which uses the regs live in the blocks where q is live... but $3 isn't live there at global_alloc time (the constant is a pseudo, not a reg, at that point).

Alternatively, GCC's global_alloc has a rule: a global pseudo may only be assigned a hard reg that is not "used by a local pseudo in the blocks where the global is live"? That's not computed at global_alloc time either.

Hmm, but there's the `global_conflict_sets` mechanism in GCC 2.7: it computes, for each global pseudo, the set of hard regs that conflict with it, using the "reg class" and `CONFLICT_INFO` — the info comes from the "conflict matrix" built during flow analysis, where hard regs are recorded as conflicting with pseudos if they're live in the same block. Since the constant is a pseudo at that time, no conflict.

OK here's another thought: maybe global_alloc's assignment for globals is not "first free reg" but a more complex algorithm with `reg_alloc_order` and a "conflict" check via `regs_ever_live`. If $3 is "ever live" in the function (it is: st in $3, constant in $3 — but those are assigned later by local_alloc...).

Hmm, wait. Actually! In GCC 2.7, `global_alloc` is called AFTER `local_alloc`? Let me verify with the actual gcc 2.7 source. Maybe I can find gcc source in the repo (e.g., in tools/bin/gcc-2.7.2-psx or disks). Let me check.

Actually, easier: use cc1 dump! The task mentions tools/cc1_dumps_tu.sh and tools/alloc_table.py, and .run/P40/T10/hdump.sh for "header pass dumps". These produce gcc -dump-* output which shows the allocation decisions. Let me look at tools/cc1_dumps_tu.sh and tools/alloc_table.py.

That could tell me exactly why q got $4. Let's check thosetools.
