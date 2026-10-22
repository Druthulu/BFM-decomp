---
ts: 2026-10-22T08:36:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_XK19se8vPHEAc9ul1GQQ
---
Interesting! Note the target's asm does NOT have a nop after `lw v1,100(s0)`? It has "nop" after the first lw a0,100(s0) but the second `lw v1,100(s0)` at 3ff0 is followed by `j` (delay slot filled with the jump target?). Actually `j 401c` with delay slot R_MIPS_26 .text — that's the assembler branch-likely.

Also note the "target" here is the build object = current src compiled with pin? Wait, the target shows `lw v1,100(s0)` — q in v1, and no pin visible obviously (pins are compile-time). But hold on: does the build object correspond to the pinned src? The explain diff showed target has v1 for q, which matches the pin. Good.

Wait, but the target asm I dumped is from build/, which is the pinned version? The build might be stale. Anyway, the target for scoring = build's version.

Interesting observations:
- Target has `q` loaded twice (once per switch arm) into v1. And the constant 0x9000 also in v1.
- Note that the target's `sh v0,2(v1)` and `sh zero,52(v1)` — the join block.

Hmm wait, in the target asm, case 2 path: at 3ff0 lw v1,100(s0) then jump to 401c (the join). And val = 3 is set... hmm, `li v0,3` at 3ff8 is in the delay-slot-ish position. The switch is on `st` (u16). Cases: st==1 → case 1 (val 3), st==2 → case 2 (val 4)? Actually source: case 2: val=3; case 1: val=4. The switch value comparison: `li v0,1; beq v1,v0` → case 1 label at 3ffc (which is case 1 → val=4? at 4018 li v0,4). Yes: beq → 3ffc which is "case 1" body with li v0,4 at 4018. And bne v1,2 → 4030 default; fallthrough 3fd8 is case 2 (li v0,3 at 3ff8 in delay slot of jal? no, 3ff8 is after jal at 3fd8 with delay 3fdc). Hmm, 3ff8 li v0,3 is the case-2 val assignment placed in the delay slot of the jal? jal at 3fd8, delay slot 3fdc is nop. Then 3fe0 li v1,0x9000. So `li v0,3` at 3ff8 is at a weird spot — it's the target of the jal? No. Let me re-read: the jal at 3fd8 is `jal func_8012BD14` with delay 3fdc nop. Then 3fe0..3ff4. Then 3ff8: li v0,3 — that's between the j at 3ff4 (delay slot 3ff8). Yes! `j 401c` at 3ff4 with delay slot 3ff8 = `li v0,3`. So the val=3 assignment is in the delay slot of the jump to the join.

OK. So the target's structure is: val in v0 ($2), q in v1 ($3), constant 0x9000 in v1.

Now mine (lever-free) has q in a0. Interesting: mine still uses v1 for the 0x9000 constant? The explain diff only listed 4 differing lines (18,19 / 27,28 / 29,30 / 31,32) — so in mine the constant 0x9000 is in v1 too, and `li v1,0x9000` matches.

So the difference is purely where q goes: a0 vs v1.

Key: in the target, q is a *global* pseudo (defined in two blocks, used after join). gcc's local-alloc assigned $3 to the block-local constant; then global-alloc: for a global pseudo, the "conflict" set is computed across the whole function in blocks... The note says global-alloc may not reuse $3 for the global q because its conflict set is block-granular (q's conflict with the constant is only in those blocks).

Hmm, but in the target, q IS in $3 and the constant also in $3 — because with the pin, q is a hard reg so the constant gets it only when q isn't live.

Without a pin, gcc's global-alloc picks a pseudo reg for q: since q is live in multiple blocks, it's global. Global-alloc has a priority and conflict computation.

So to get q into $3 lever-free, we need q to be a *local* pseudo (defined and used in a single block) — but then the join use... Alternatively, restructure so the stores happen inside each case arm (no join use), making q local to each block. But that changes the code shape: the target does the stores after the join (sh v0,2(v1); sh zero,52(v1)), and case 1 vs case 2 differ only in val.

Hmm, but if we duplicate the tail into each arm, the asm would have `sh v0,2(v1)` in each arm, and no join — that would be 2 extra instructions vs 1 (the target has one sh in the join). Actually target: join block at 401c: sh v0,2(v1); jal func_80178BF8 with delay sh zero,52(v1). If we duplicate, we'd have sh v0,2(v1); sh zero,52(v1) in each arm = 2 extra insns total. Score would count instruction mismatch → score > 0.

Alternative: keep the join but make the value q a local? Not possible since defined in two blocks.

Alternative: make q's value come from a common place: e.g., `q = ...` computed before the switch? No, target loads it inside each arm.

Hmm wait: in the target, both arms do `lw v1,100(s0)` — the same value `arg->unk64`! Both arms load the same expression. So actually q is redundant — it's `((Unkstruct_801815AC_2 *)arg)->unk64` in both arms, same as `ptr`? No wait: ptr = arg->unk64 initially (loaded at 3fb8 into a0). Then in the arms, q = arg->unk64 again — same value! The compiler re-loaded it because arg (s0) is unchanged... Actually gcc reloaded because between the load and the use there was a call (func_8012BD14) which could clobber memory (arg->unk64 is not const). So gcc reloads.

So q == ptr semantically. But the compiler can't know that unless... well, it can: ptr = arg->unk64 is a load; q = arg->unk64 reload after a call — gcc's CSE doesn't merge across a call (the call may modify memory).

So the source has this redundancy. In the target, `ptr` is in a0 initially (used for the call arg and the lhu st), and after the call the value is reloaded into v1.

Now, what does mine do? Mine: same shape but q in a0. Interesting that mine reuses a0 for q, since a0 was the call arg (dead after the call).

Why does the target use v1 and mine a0? Because in the target, q is a hard register $3; the constant 0x9000 is also assigned $3 by local-alloc... wait, but they conflict in life within the block! Unless: the constant is used for slt comparison right after the call, and q is defined after. In local-alloc, within a block, if q is hard reg $3 and the constant is a pseudo needing a reg, the pseudo can't take $3 in that block since q (hard) is live there... Hmm, actually local-alloc gives $3 to the constant and q (hard reg) also claims $3 → conflict? But the target shows both in $3!

Look: `li v1,0x9000` at 3fe0, `slt v1,v1,v0` at 3fe4 — so the constant occupies v1, and v1 is dead after the slt. Then `lw v1,100(s0)` at 3ff0 defines q in v1. So no overlap in life. OK so q (hard $3) and the constant pseudo ($3) — local-alloc assigned the pseudo to $3 because $3 is free at that point? No — global-alloc does hard regs first, then local-alloc gives pseudo registers, and hard reg $3's live range... gcc's local-alloc can use a hard reg for a pseudo if the hard reg isn't live in that region. But q IS $3 globally and live from 3ff0 onwards; the constant is at 3fe0-3fe4, before. So in the block, q's hard reg $3 is not live yet (q's live range starts at its def). GCC's local-alloc processes block-local pseudos and can use hard regs whose "global" live range doesn't cover... hmm, actually for a hard reg, the conflict is handled by the "hard reg live" tracking.

Anyway, the empirical fact: with pin q=$3, gcc produces exactly the target. Without the pin, q lands in a0.

Why does q land in a0 rather than v1 or v0? Global-alloc assigns global pseudos to registers by priority; but here q is the only global pseudo? Others: ptr (a0?), st (v1?), val (v0?).

Actually mine (lever-free) has same instruction count 39, and only q's register differs. So in mine: the constant 0x9000 is in v1, st in v1, val in v0, and q in a0.

Hmm, interesting: In mine, q in a0. In target, q in v1 (with the constant also in v1). So local-alloc gave $3 to the constant in both cases. Then global-alloc had to put q somewhere: available $2 (v0, used by val and call results), $3 (taken by constant, conflict block-granular), $4 (a0, free after call).

The fix: make the constant 0x9000 NOT be in $3, so global-alloc can use $3 for q. E.g., compare `func_8012BD14(ptr) > 0x9000` differently so the constant isn't a materialized register... e.g. `0x9000` used in `slt v1,v1,v0` — the pattern is `li v1,0x9000; slt v1,v1,v0; bnez v1,default`. That's `if (ret > 0x9000) return 0;` compiled as slt.

Alternative spellings of the same comparison that produce different registers:
- `if (0x9000 < func_8012BD14(ptr))` — same.
- `if (func_8012BD14(ptr) >= 0x9001)` — would produce li 0x9001 and sltiu? Different instruction. No good.

Hmm. What if the constant 0x9000 is stored in a variable of type u16? Then `li v1,0x9000` might become `li v1,0x9000` still (0x9000 fits in u16, and the comparison would need sign/zero extension → maybe `li v1,0x9000` then `slt` requires SImode; u16 would be extended to 0x9000 (positive) so `slt` still. But gcc would need to zero-extend: `li v1,0x9000` is exactly 0x9000; the extension is free (already fits). So the code may be identical! But it may also introduce a `andi 0xffff` if gcc doesn't see the value.

Hmm, but wait — we need the *target*'s code: constant in v1 ($3) and q also in v1. The target has constant in $3 and q in $3. If in my version the constant goes elsewhere (e.g. $4 or $5), then q could take $3 → then score might be 0 for q but the constant's line differs → score counts differing instructions. The scoring is instruction-level diff (masked). So the constant must also be in $3.

Ugh. So we need BOTH the constant and q in $3, with the constant first.

So the requirement: gcc must assign q to $3 and the block-local constant 0x9000 also to $3 (in the same block where they're sequential).

With the pin, gcc does exactly that. Without the pin, gcc's global-alloc chose $4 for q because $3 was "conflicted" by the constant's block-granular conflict set.

Hmm, the note says: "local-alloc runs first and gives $3 to the block-local constant 0x9000, and global-alloc then may not reuse $3 for the global q (its conflict set is block-granular)".

So: global-alloc assigns globals AFTER local-alloc? Actually in GCC, global-alloc runs first (allocates global pseudos to hard regs), then local-alloc. Hmm, but the note says local-alloc runs first. Let me check GCC 2.7.2 order: in alloc.c, allocate() calls ... global_alloc() is called before local_alloc()? Let me recall: `allocate()` → `find_parm_named`... The order in GCC 2.7: global_alloc() is called first, then local_alloc()? Actually in GCC's alloc.c:

```
  /* Do global register allocation first, then local register allocation... */
```
Hmm, in GCC 2.x alloc.c: `allocate (void)` does: ... `global_alloc ()` is called inside `allocate` after `build_regclass`? Let me check the source. tools/bin/gcc-2.7.2-psx has cc1 binary only, but maybe gcc source is available in the repo? Let me check for gcc source.

Rather than theorize, let's experiment: write candidate bodies and score them. Empirically find what makes gcc pick $3 for q.

Ideas:
(a) Make q's *use* pattern different so global-alloc prefers $3: e.g. q used in more places, or q declared as `s32` (already). Since global-alloc picks by priority (number of refs, live range), maybe making q have more refs (e.g., using it twice) changes the reg choice. But the target has exactly 4 uses of q (lw in 2 arms + 2 stores). Actually the 4 uses counted by the explain: a0->v1 x4.

(b) Use a different temp structure so that q's pseudo is *local* to a block. Hmm.

(c) Force the constant 0x9000 to not be a separate pseudo but reuse a global register that isn't $3? No, target has it in $3.

Hmm, wait. Actually maybe the trick: make q a *parameter-like* or make q's pseudo not conflict with the constant. The conflict arises because both live in the same block and gcc's conflict detection is coarse (block-granular). If q were live in *more* blocks, the conflict might be weaker? Actually the note says the opposite.

Let's think about GCC 2.7 alloc.c: global_alloc assigns global pseudos (those live across blocks) to hard registers. It uses `global_conflict_sets` and computes for each global pseudo its "conflict" with hard regs. If q conflicts with $3 in the block containing the constant, global_alloc will not assign $3 to q. The conflict set is computed per block; for a hard reg, the conflict is "the pseudo is live in a block where the hard reg is used".

So how did the pinned version get $3? Because with a pin, q IS the hard reg $3 (not a pseudo), and the constant pseudo gets $3 in local_alloc only where $3 is not live (constant before q's def). GCC's local_alloc with hard regs: it can assign a pseudo to a hard reg if the pseudo's live range doesn't overlap the hard reg's live range *within that block*. Since q ($3) is live from its def onward in the block, and the constant dies before, local_alloc gives the constant $3. That's the "born-after" trick.

So the question is: how to make gcc's global_alloc pick $3 for q, given that a block-local pseudo also takes $3.

Option: Eliminate the separate constant pseudo. The constant 0x9000 must be in $3 at the point of the slt. What if the constant is loaded as part of q's value? No.

Option: Make the constant a global pseudo rather than block-local, so global_alloc assigns them differently... Hmm.

Option: Make the *comparison* not need a separate constant register: e.g., `if (func_8012BD14(ptr) > 0x9000)` → the compiler emits `li v1,0x9000; slt v1,v1,v0`. What if written as `0x9000 - ret < 0`? That'd be different code. What about unsigned comparison? ret is s32; `> 0x9000` signed.

Hmm what if 0x9000 is spelled as a hex constant vs decimal? No difference.

Option: Change the order — make the constant 0x9000 defined *before* the switch in a way that it's live across blocks (global). Then global_alloc would assign it a global reg... but target has the constant in $3 in the block — with the pinned q, the constant is a global pseudo too? Hmm, if the constant were global, global_alloc would assign it to a hard reg and it couldn't be $3 (conflict with q's hard reg $3 in blocks where q is live... q live after the constant's uses, but the constant is live from its def to the slt, which is before q's def → no conflict within block, but global_alloc's conflict is block-granular → the constant conflicts with q's $3 if any block has both live. Since q is defined in both arms and live to the join, and the constant would be defined in the entry block live into both arms → they'd conflict. So global_alloc would give the constant a different reg. Not $3. So the constant must remain block-local.

So: we need the constant to be a block-local pseudo that local_alloc assigns $3, AND q (global pseudo) to be assigned $3 by global_alloc. global_alloc must not see a conflict.

Wait — is it global_alloc that assigns q? q is live across blocks (defined in arm, used in join) → it's a global pseudo. global_alloc processes global pseudos in priority order and assigns them hard regs (from the global regs list, typically $2..$15 or so). At the time global_alloc considers q, has the constant been assigned $3? global_alloc runs BEFORE local_alloc, and local_alloc assigns block-local pseudos afterwards. So during global_alloc, $3 was free → q should have gotten $3 by global_alloc!

Unless global_alloc skipped q due to a conflict with something else. Hmm. But then why did mine put q in $4?

Hmm, maybe the order is local first then global in GCC 2.7? Let me check: in GCC 2.7's alloc.c `allocate()`:

```
  /* Perform a pseudo register allocation... */
  ...
  global_alloc ();
  ...
  local_alloc ();
```
Hmm I believe global comes first. But actually there's a subtlety: in GCC 2.7 alloc.c, `allocate()` calls:
```
  /* Now allocate the register for each pseudo... */
  ...
  /* Free the pseudos... */
```
I recall the sequence: `build_regclass()`, `allocate()` → `global_alloc()` is called from `allocate()`? Let me look for gcc source in the repo. Maybe under tools/bin/gcc-2.7.2-psx or disks/. Let me check.

Actually, a more productive route: experiment. The task says each item gets 20-30 min and ≥30 tries for a WALL. Let's do quick experiments.

For item 1, key idea candidates:
1. Make q used more times (extra refs) → changes global_alloc priority.
2. Declare q as `register s32 q;` without asm — that's a "register" var which the constraint forbids ("no `register` vars"). Hmm, "no `register` vars" — so can't use register keyword at all.
3. Use `s32 q` vs `int q` — same.
4. Restructure so q is not global: e.g., compute the stores in each arm. As computed, that duplicates instructions → score>.

Hmm wait, actually let's reconsider: maybe restructuring so q is defined in the entry block (global, live everywhere) changes things. E.g.:

```
q = arg->unk64;  // before switch? no, target loads in each arm after the call
```
No.

5. What about making the two arm loads into a single load before the switch? Then q is defined in the entry block → global pseudo live in all blocks → global_alloc assigns $3? But then the target's two `lw v1,100(s0)` instructions would become one → instruction count differs → score.

Hmm. Unless... the load in the entry block is `lw v1,100(s0)` and after the call gcc must reload (memory clobbered) → it would reload anyway in each arm! Since the call may modify arg->unk64, gcc must reload after the call. If we hoist `q = arg->unk64` before the switch, gcc would still reload after the call because the value may have changed. Actually gcc reloads only if it uses the value after the call; it would keep the pre-call value in a callee-saved reg or reload. Hmm, that changes the code.

Actually, wait. In the current source, `ptr` is loaded before the switch and used in the arms only for the call arg and st. The `q` reload happens after the call. If we wrote `q = arg->unk64` at the top (before the switch), then gcc has q's value live across the call → it would need to preserve it in a callee-saved register (s3?) → different code. Not good.

So the structure must stay: reload after the call in each arm.

6. What about making the value used for the store different? Like `((Unkstruct_801815AC_3 *)q)->unk2 = val;` — the target stores to q+2 and q+52.

Alternative: change `q` to a pointer type `Unkstruct_801815AC_3 *q;` — then `q->unk2 = val` and `q->unk34 = 0`. The load becomes `lw v1,100(s0)` same. The stores: `sh v0,2(v1)` and `sh zero,52(v1)` same. But with a pointer type, gcc may add a null check or use different addressing. Also the pointer might be kept in a different reg class. But the asm should be identical if no alignment issues... Actually with `s32 q` and cast `(Unkstruct_801815AC_3 *)q`, gcc computes the address as q+0 in a reg? It might do `sh v0,2(v1)` — the cast is free since offsets are constants. Same.

But: with pointer type, gcc may treat q as a pointer → global_alloc might assign it to a callee-saved reg (like s3)? Hmm, pointers are not usually preferred to callee-saved in this gcc? Actually GCC prefers to keep pointers in callee-saved regs sometimes. The note in moves.md: "pin | func_801F033C | MATCH — struct-typed ptrs + store via ((Unkstruct *)a0)->unkFC". So struct-typed ptrs is a known move.

7. Another idea: give `q` a *second* use or make its lifetime longer so global_alloc gives it a higher priority → gets $3 instead of $4? But the conflict with the constant pseudo is the issue... though if global_alloc runs first, there's no conflict.

Let me just get facts: use tools/alloc_table.py or cc1 dumps to see the allocation decisions. But first, cheap experiments.

Let me set up the item dir: create orig.c (copy of current src def), then try candidates.

Actually wait. Note the important detail: the target I dumped is from build/ which may be stale vs src. The build's compiled function is the reference. Since the src has the pin and the build shows q in $3, build is current enough.

Let me now write candidate bodies. Note the body file passed to --body must contain the function definition only. Existing win.c is that.

Experiment set for item 1:
E1: q as pointer type: `Unkstruct_801815AC_3 *q;` — need to know the struct definition. It's in the TU. The body is compiled together with the TU? Let me check how --body works: it replaces the function in the TU and compiles the whole TU. So the struct types are available.

Let me check the struct definitions in the TU: Unkstruct_801815AC_2 and _3.

Let me grep.
