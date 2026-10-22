---
ts: 2026-10-22T08:39:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oBsZvjQQ7f8tcfLtBIqN
---
Now let me create orig.c for item 1 and a first candidate set.

Let me write candidates for item 1:

c2.c: q as struct pointer.
c3.c: q declared with different order (decl order/scope): declare q after ptr? The decl order matters for the "priority" of pseudos? Actually decl order can affect allocation order in GCC (pseudos allocated in order of declaration?). Worth trying.
c4.c: `s32 q` but with the store written as pointer arithmetic: `*(u16 *)(q + 2) = val; *(u16 *)(q + 0x34) = 0;`
c5.c: use a separate `u16 *qp = (u16 *)q;` etc.

Also: what about making the reload assignment in each arm assign to q via an intermediate? no.

Another idea: The key issue is that global_alloc gives q $4. What if `q` is used in the *entry* block too, making it live earlier? no.

What if we make q's *type* u32 vs s32? Doesn't matter.

Idea: "init at decl" — `s32 q = ...`? no.

Idea: "statement order" — reorder the two stores? `((Unkstruct*)q)->unk34 = 0;` first then unk2 = val? The target order: sh v0,2(v1) then sh zero,52(v1). Changing order changes code.

Idea: scope — declare q inside... no, it's used after the switch.

Hmm, what about the *val* variable: if val were declared as `s16` or `u8`, the `li v0,3` might change (e.g. `li v0,3` stays). But val is a global pseudo in $2. If val took a different register, maybe q would get $3? But the target requires val in $2 (v0) — `li v0,3`/`li v0,4`/`sh v0,2(v1)`.

Alternatively make val NOT a global pseudo: e.g., instead of `val` set in the arms and used in the join, use two separate variables val2/val1 in each arm and... then the join store needs the value → we'd need a global anyway.

Alternative: make the join store use a value that's a *constant* per arm, e.g. duplicate the store with the constant in each arm → 2 extra stores. Score impact.

Hmm, but wait! What if the store of the constant value happens in the arm and the *pointer* store in the join? No, both stores use q.

What if we swap which thing is global: make the *pointer* the value that's stored and the value global... no.

Think about the total instruction count: target 39. If I duplicate the tail (sh v0,2(v1); sh zero,52(v1)) in each arm, I get 39+2 = 41 instructions, and the diff would be large. But maybe gcc merges the identical tails via crossjumping! The arms differ only in the value stored (li v0,3 vs li v0,4) and the loads. After the store `sh v0,2(v1)`, the blocks are identical (sh zero,52(v1); jal; lui; addiu; epilogue). GCC's crossjumping could merge them into a common tail. But the *first* store differs (v0 differs) so the merge point would be after it. Crossjumping in GCC 2.7 (jump.c) merges blocks with identical tails. The tail after `sh v0,2(v1)` is identical in both arms → crossjump merges → giving exactly the target shape! Then the block boundaries: arm2 would be: lw v1,100(s0); li v0,3; sh v0,2(v1); j join... Hmm, but the merge point would need the same predecessors. Crossjumping requires the two blocks to have the same code and creates a new merged block; the resulting layout might differ in ordering from the target.

That's speculative but worth a try since it's a cheap experiment. But careful: the duplicated code has q local to each arm → local pseudo → local_alloc assigns it. Which reg? It'd be a local pseudo in the arm; local_alloc might give it $3 (v1) since it's the preferred reg for the "value" and $2 is used by the constant... Hmm, the constant 0x9000 also needs a reg in that block, and val (li v0,3) needs a reg.

In the arm: after the call, we need: the constant 0x9000 (for slt), the call result (v0), q, and val. Target: constant in v1, q in v1 (sequentially), val in v0.

So in the arm block, local pseudos: const(0x9000) and q. If q is local, local_alloc assigns: it prefers... For MIPS, the preferred regs for a local pseudo of mode SImode: the "preferred" class is general regs, and local_alloc picks from `reg_class->regs` in order but with `regs_ever_live`... Typically local_alloc would assign $2 (v0) first? But $2 holds the call result (also a pseudo? the call result v0 is a pseudo too). Hmm.

The target's arm layout: v0 = call result (pseudo from the call), v1 = const, then v1 = q. If q is local and const is local, local_alloc assigns them in some order.

There's a decent chance that duplicating the tail gives a different shape (e.g. the merge point at a different place, extra j).

Alternatively, another approach to keep the join but make q local-ish: use a *pointer* variable that is assigned in the entry block? No — reload after call.

Hmm hold on. Actually maybe the cleanest: what if we give q's global-ness to a different variable? I.e., swap roles: make the *value* (val) local to each arm and the *pointer* global — that's the current situation (q global). What if instead we make the pointer local and the value global? Then: the pointer q would be local to... no, it's used in the join.

What if we restructure so that the pointer is not needed after the join? E.g., compute `p2 = q` (global) — same.

OK, alternative idea: maybe the real problem is just global_alloc's reg choice for q, and we could influence it by changing the *priority* of q relative to other globals, or by changing the reg-class preference of q. E.g., if q were declared as a pointer type, GCC's global_alloc might prefer $3 for pointer pseudos? Hmm, or maybe the priority computation for globals counts "refs"; q has refs in 2 defs + 2 uses.

Alternatively: what if `val` is eliminated (making val not global)? Then the only global pseudo is q, and global_alloc gives it the *first* reg in the class order → maybe $3? Currently val is global and gets $2; q gets $4. If val weren't global, q might get $2 — wrong (target needs val in $2 and q in $3).

Hmm! Unless global_alloc processes in priority order: q (4 refs) before val (3 refs) → q gets $2, val gets $3. That would be wrong.

Actually, maybe the priority ordering is by "number of references" * something. Currently q→$4 means $2 and $3 were both taken by other globals before q was considered. If only val ($2) and q are global, then q should get $3! Unless $3 was taken by another global pseudo I'm not seeing. Which pseudos are global (live across blocks)?

- `ptr`: defined in entry, used in entry (call arg, st load) → local. But wait: is it live in the arm blocks? The call `func_8012BD14(ptr)` is in the arm blocks! ptr is live in the arm blocks (as the call argument) → ptr IS global (live in multiple blocks)!

Yes! ptr is global: defined in the entry block, used in both arm blocks. So globals: ptr, val, q. And in the target, ptr is in $4 (a0: `lw a0,100(s0)` then `lhu v1,2(a0)` and `jal` with a0 arg). Hmm, ptr in a0 = $4.

So globals: ptr → $4? and val → $2, q → $3 in the target; in mine q → $4 and ptr → ? wait in mine the ptr load is `lw a0,100(s0)` too (identical lines, since the diff only showed q's lines). So mine: ptr→$4 (a0), val→$2, q→?? mine's q is a0 = $4 as well! But both can't be $4... unless ptr dies before q is born: ptr is used in the arm blocks (call arg) — but the call happens before q's def, so ptr and q don't overlap in life! They're both global pseudos but sequentially: ptr's live range ends at the call in the arm, q's starts after. So $4 can hold both.

So global pseudos: ptr, val, q — and the allocation gave $2→val, $4→ptr, and q→? In mine, q got $4 (reusing ptr's reg after ptr dies) — but that means global_alloc assigned q to $4 which was already taken by ptr?! Unless global_alloc assigned $3 to something.

Hmm, maybe global_alloc in GCC 2.7 has this: for each global pseudo it picks a reg, but there's a "conflict" computation where a global pseudo that is live in a block where another global's reg is used... In GCC 2.7, global_alloc's `global_conflict_sets` computes for each global pseudo the set of regs conflicting. Then the allocation loop:

```
	  /* Find a reg that is available.  */
	  for (i = 0; i < n; i++)
	    {
	      r = ...;
	      if (! conflicts) ...
```
Actually GCC 2.7's global_alloc processes globals in order of `reg_alloc_order`/priority and for each, tries regs in the class order, skipping those already allocated (`reg_renumber[r] >= 0`).

I think a cleaner hypothesis: global_alloc assigns in this order:
- The "highest priority" global gets the first reg. Priority = (number of refs) — but there's also the notion of globals that are live in ALL blocks (like a loop variable) getting priority.

Order of allocation might be by `reg_alloc_order` list, and for each reg in that order, find the global pseudo that wants it most. So: $2 (v0) → val? $3 (v1) → ? $4 (a0) → ptr?

Hmm, MIPS's REG_ALLOC_ORDER in GCC 2.7 mips.h:
```
#define REG_ALLOC_ORDER \
  { 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 6, 7 }
```
Hmm, I vaguely recall MIPS has:
```
#define REG_ALLOC_ORDER { 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 6, 7 }
```
Not sure.

Empirics beat theory. Let me try candidate variations and look at where q lands. Quick experiments:

E-A: eliminate `ptr` as a separate variable: inline `((Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64)->unk2` into st. Then ptr is not a global → globals are val and q. See where q lands.

E-B: eliminate `val` (global) by storing directly in each arm (duplicate stores) → q becomes local.

E-C: q as pointer type.

E-D: swap decl order of q and ptr.

E-E: make q's stores use a `u16 *` pointer variable (pointer reuse).

Let me write these and score them.

Note: c0.c/c1.c already exist. I'll create c2..c6.

Let me write them with Write tool.

Note: the body must be a complete function definition matching the signature `s32 func_801815AC(void *arg)`.

E-A:
```
s32 func_801815AC(void *arg)
{
    s32 q;
    u16 st;
    u16 val;

    st = ((Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64)->unk2;
    switch (st) {
    case 2:
        if (func_8012BD14(((Unkstruct_801815AC_2 *)arg)->unk64) > 0x9000) return 0;
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 3;
        break;
    case 1:
        if (func_8012BD14(((Unkstruct_801815AC_2 *)arg)->unk64) > 0x9000) return 0;
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
Wait, careful: in the original, `ptr` is loaded once and used for both st and the call arg. If I inline it, the compiler will CSE the two loads of arg->unk64 (same expression, no call between) → one load → same as original. But the original loads it once too. The difference: `ptr` as a variable vs inlined. In the original, ptr is a pseudo live in the arm blocks (call arg) → global. Inlined, the call arg is a temporary → maybe still a pseudo live across the branch.

Hmm, this changes little. But the target requires `lw a0,100(s0)` (one load) — inlined version would also have one load. OK.

E-B (duplicate stores in arms):
```
s32 func_801815AC(void *arg)
{
    s32 q;
    s32 ptr;
    u16 st;

    ptr = ((Unkstruct_801815AC_2 *)arg)->unk64;
    st = ((Unkstruct_801815AC_3 *)ptr)->unk2;
    switch (st) {
    case 2:
        if (func_8012BD14(ptr) > 0x9000) return 0;
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        ((Unkstruct_801815AC_3 *)q)->unk2 = 3;
        ((Unkstruct_801815AC_3 *)q)->unk34 = 0;
        break;
    case 1:
        ...
    }
    func_80178BF8();
    return (s32)func_80172710;
}
```
Hmm, but then the `sh v0,2(v1)` would be `sh` of an immediate: `li v0,3; sh v0,2(v1)` — gcc might emit `sh v0,2(v1)` with v0=3. And in the target the store is after the join with val in v0.

Let me just try.

E-C: q as pointer:
```
    Unkstruct_801815AC_3 *q;
    ...
    q = (Unkstruct_801815AC_3 *)((Unkstruct_801815AC_2 *)arg)->unk64;
    ...
    q->unk2 = val;
    q->unk34 = 0;
```
Careful: unk2 is u16 at offset 2, unk34 is u16 at offset 0x34. But q points to the struct; the source casts the s32 q to the struct. Same.

Let me write these three and score.

Actually also E-F: swap the order of the two arms (case 1 first)? The switch case order in source affects the code layout (branch order). The target's layout: beq v1,1 → 3ffc (case 1 body), bne v1,2 → default; case 2 falls through. So case 2 is first in the layout. Source order: case 2 first, then case 1. That matches the current source. Keep.

Let me write the candidates.
