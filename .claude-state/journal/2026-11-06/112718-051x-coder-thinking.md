---
ts: 2026-11-06T18:27:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bTeOj2PNDFoynJyF9TBP
---
Time: 11:27, started 11:11 → 16 minutes on item 3. I've done ~32 scored tries. The WALL needs ≥20 min and ≥30 scored tries. I have 32 tries but 16 min. Let me continue a bit more with a couple more ideas to pass 20 min, or decide.

Actually, wait. Let me reconsider one promising route I haven't tried: making the *parameter use* block-local by computing the base pointer in the prologue block. Specifically:

```
void func_80184B70(void *a0, s32 a1, s32 a2) {
    s32 v0;
    s32 v1;
    s32 base;

    base = (s32)a0;      // block 0 use of a0
    v0 = D_80078EB1;
    if (...) { v1 = ((Unk*)base)->unkCC; ... }
```
Here `base = (s32)a0` is a copy; global-alloc coalesces base with 72? The param copy 72 is `(set 72 (reg 4 a0))`, then `base = 72` — cse would propagate base = 72 (same value), so base IS 72. No change.

What if base is computed with an offset: `base = (s32)a0 + 0xCC;` then loads `*(s32*)base`? Then:
- block 0: `addiu base, a0, 0xCC` (1 insn), a0 used once in block 0 → 72 might become block-local! Then base is the global used in the arms; the loads `(set 76 (mem (reg base)))` — the base is a global pseudo (no pref!). 76 would get no pref → $3! But we'd have an extra addiu insn → 16 insns vs 15. Unless combine folds the addiu into the loads (it's used 2-3 times; combine won't delete it if multi-use).

Hmm, but maybe the extra insn gets deleted? No.

Unless... the loads could use `base` where base = a0 + 0xCC and the store uses base too... target has no addiu.

Not a match.

OK, another idea: **make the param copy's preference for $4 not merge because the load's base is a hard reg**. If a0 were used directly as a hard reg in the load (no pseudo), the load would be `(set 76 (mem (plus (reg 4) 204)))` with REG_DEAD(4) — expand_preferences requires the dead reg to have an allocno (reg_allocno >= 0); hard reg 4 has no allocno → no merge. Then 76: hard_reg_conflicts would include 4? The load uses hard reg 4 → record_one_conflict(4) at the load? For hard regs, conflicts are recorded when the hard reg becomes live: `mark_reg_live` for the base reg at the load → records conflict of hard reg 4 with all live allocnos at that point. 76 is born at the same insn (after the death processing, the use marking happens after stores?). Hmm, if hard reg 4 conflicts with 76, the pref is moot.

But how do we get a0 used as a hard reg? When the parameter has only ONE use, GCC might still copy. Actually, in this compiler, does `assign_parms` always copy? Let me check a function in the codebase where a param is used directly... In the .lreg dump of our function, 72 exists. Let me check whether other functions' dumps show a param used as a hard reg directly. Hmm.

Let me look at function.c's assign_parms for the pseudo creation. Search for "parm_reg_stack_loc" or "copy". Actually, GCC 2.7.2's assign_parms:

```
  /* If the parameter is passed in a register, and we want to use that register,
     ... */
```
I recall:
```
      if (GET_CODE (entry_parm) != REG
	  || nominal_mode != mode)
	/* ... copy */
```
and later
```
	  /* If this is a memory-ref parm, ... */
```

Let me grep function.c for "assign_parms" and look at the copy logic.
