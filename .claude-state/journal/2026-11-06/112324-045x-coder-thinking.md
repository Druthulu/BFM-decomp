---
ts: 2026-11-06T18:23:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iTnY0vphhELURGKVQA6g
---
Dispositions: 72 in 4, 76 in 4 — both in $4 again! But order says 76 before 72. 76 takes $4 (pref). Then 72: pref $4 (used by 76? 72 conflicts with 76? "72 conflicts: 72 74 75 2 5 6 29" — no 76; "76 conflicts: 75 76 29" — no 72). So 72 can also take $4. And it does (pref). So both in $4.

Interesting: 72 doesn't conflict with 76 even now.

To break: we need 72 to NOT get $4. If 76 takes $4 and 72's pref $4 is excluded (because `used` includes $4 from regs_used_so_far — but only if $4 is in `used`, which it is: `IOR_COMPL_HARD_REG_SET (used, regs_used_so_far)` → $4 is used → excluded!). Wait, then 72 couldn't get $4... but disposition says 72 in 4. Hmm, unless the pass-0 exclusion is bypassed: in find_reg, pass 0 excludes regs_used_so_far; pass 1 (if no reg found) doesn't. And the pref override at the end: `AND_COMPL_HARD_REG_SET (hard_reg_preferences[allocno], used)` — `used` here is the pass-1 or pass-0 set? After the loop, `used` holds the pass-1 set (used1, without regs_used_so_far). So the pref override can pick a reg used by a non-conflicting allocno (pass 1 allows it). So 72 → $4.

So both 72 and 76 in $4 — they don't conflict, so it's legal.

Now the residual: both dest and base are $4. Hmm.

To fix: we need 76 NOT to prefer $4, i.e., kill the pref. Since expand_preferences merges at the load (REG_DEAD 72), and 72 and 76 don't conflict.

What if 76 had NO pref: then 76 → best_reg $3 (pass 0, since $2 used by 75) → $3. Then 72 → $4. Match!

So: kill the pref on 76. The pref comes from expand_preferences merging 72's prefs because at the load insn, 72 dies and sets 76.

expand_preferences condition: `REG_NOTE_KIND(link) == REG_DEAD && GET_CODE(XEXP(link,0)) == REG && reg_allocno[REGNO(XEXP(link,0))] >= 0 && !CONFLICTP(...)`.

So if 72 were NOT a global allocno (reg_allocno < 0), no merge. When is a pseudo not a global allocno? `reg_allocno[i] = -1` when the pseudo is not worth global allocation: global.c's `global_alloc` first calls `local_alloc()` and then computes which pseudos get global allocnos: a pseudo gets an allocno only if it is live across basic blocks (not local to one block). 72 is live across blocks → allocno.

Alternatively, if 72 CONFLICTS with 76, no merge. We established they don't conflict because 72 dies at the load in each arm.

Can we make 72 live after the load in the same block? What if the store block used a0? Then 72 would be live-out of the arms → conflict. How can the store use a0 for free? Hmm.

Wait — what about the OTHER direction: make 76 conflict with 72 by making 76 live *before* the load in some block. 76 is v1; if v1 were used before being set... no.

What about making the loads use *different* variables so that 72's death at each load doesn't coincide with 76's birth? E.g., in each arm: `v1 = a0->unkCC` — the birth coincides.

Hmm, what if we introduce an intermediate: `s32 t; t = a0->unkCC; v1 = t;` → the load sets t (local), then v1 = t (copy). The copy at the join... Actually the copy would be in the arm block; combine would coalesce t and v1 (copy propagation) → same. But cse's copy propagation happens before global-alloc; likely merged.

What about `v1 = *(s32 *)((char *)a0 + 0xCC)` — the load's dest 76, base 72; REG_DEAD 72. Same.

**What if the base is not 72 but a pseudo that does NOT die at the load?** E.g., make the loads use a *different* copy of a0 that is live across the whole function, like 72 but not dying at the load. The param copy 72 dies at the load (last use per path). If a0 had another use later (e.g., in the store block), 72 wouldn't die at the loads → no REG_DEAD at the load → no pref merge → 76 gets $3!

So: add a use of a0 after the store. That adds an insn. Unless... the use is in the store block and combines into an existing insn.

Hmm! What if the store is written using a0 as well: e.g., 
```
((Unkstruct_80184B70 *)a0)->unkB0 = ... 
```
no, the store is to v1+0xB0.

Hmm, what if we make the last arm's load NOT be the last use: e.g., use a0 in the else branch's *store*? no.

**What if the whole body stores to a field of a0-derived pointer and the loaded pointer is only used... ** no, target.

Let me reconsider: maybe use a different expression for the load that doesn't make 72 die at the load. For example, if the load address is `(plus (reg 72) 204)` and 72 has another use later in the SAME block. The arm block is: li v0,1; lw v1; j. If the block ended with something using a0... 

Alternatively: restructure so that ONE of the loads is in the same block as a later a0 use. E.g., make the store block also use a0: `*(s32 *)(v1 + 0xB0) = v0` — no.

What if the branch structure changes so the load happens in the *same block* as the compare (the a0 use)? Hmm.

Alternatively: **make 76 not global**: if the store were duplicated into each arm, 76 would be block-local... but then the target's shared store block wouldn't match. Hmm, but wait: if the store is duplicated in the source arms, jump2 (cross-jump) might merge the identical arm tails into a shared block — that's what produced the target's shared block! And if the load+store are in each arm... Let's think: source:
```
if (!(v0<a1)) {
  if (v0<a2) { v0=1; v1=load; }
  else { v1=load; v0=2; }
} else { v1=load; v0=2; }
store;
```
The store is outside. The target's block d38 (store) is shared. With cross-jump merging the two `v1=load; v0=2` arms (post-reload), we get the target's asm. OK.

What if instead the store is inside each arm: 
```
if (...) { v0=1; v1=load; store; }
else if (...) { v0=1; v1=load; store; }  -- hmm
```
The target's asm has `j d38` from d24 with delay `nop`, and d30 falls through to d38. If the store were in each arm, jump2 would need to merge the tails.

Actually the target IS consistent with the store being in a shared block (as the source has it). Fine.

OK here's another idea: make 72 die at the load but give 76 NO possibility to take $4 by making $4 *conflict* with 76 — via a hard reg conflict. Hard reg 4 conflicts with 76 if a0 is live during 76's range. a0 (hard reg) is live only at insn 4 (the param copy). If the parameter were used directly in some way that keeps the hard reg live...

Hmm, what if we add a *second* parameter use in the prologue area? No.

Let me try the *simplest* structural change: use `a0` directly in the load expressions but declare v1 differently, or reorder so that 72's death comes later.

Actually, WAIT. What about making the store use a0 in the address computation in a way that combine folds? E.g.:
```
*(s32 *)(v1 + 0xB0) = v0;
```
→
```
*(s32 *)((char *)a0 + ((char *)v1 - (char *)a0) + 0xB0) = v0;
```
launder — forbidden.

Hmm.

**Alternative: change the branch structure so the load result 76 is born in the same block where 72 is still needed after.** E.g., invert: make the `if (v0<a2)` test occur AFTER the load:
```
v0 = D_80078EB1;
if (!(v0 < a1)) {
    v1 = ((Unkstruct*)a0)->unkCC;   // load first
    if (v0 < a2) { v0 = 1; }
    else { v0 = 2; }
} else {
    v1 = ((Unkstruct*)a0)->unkCC;
    v0 = 2;
}
```
But the target's asm order: in the `v0<a2` arm, `li v0,1` comes BEFORE `lw v1` (d20 li v0,1; d24 lw). Hmm, that's just scheduling (sched1 may reorder). Also the branch layout would differ: target has the a2 test before the load (d18 slt; d1c beqz; d20 li; d24 lw). If the load were before the a2 test, the RTL order would be load then slt. sched1 could reorder. Risky but worth trying: with this structure, the load is in a block where 72 is used again? No — 72's use is the load itself; after the load, 72 is dead in that block.

Hmm, but here's the thing: if the load is hoisted before the inner if, then the inner if blocks (v0=1 / v0=2) come after the load. 72 dies at the load; 76 is born at the load. Same coincidence.

**Alternative: make the load use an address based on a *different* variable that doesn't die**: e.g., precompute `s32 base = (s32)a0;` at the top (one addiu/move) and use `*(s32*)(base + 0xCC)`. base = 72 (the param copy) — same.

Hmm, what if we make the loads use a variable `p` that is set from a0 ONCE and is used in all arms, so p = 72... same pseudo.

OK, completely different: what if we prevent the merge by making the REG_DEAD at the load belong to a *different* allocno than 72? The REG_DEAD at the load is for 72 (the base). If the base were a *hard* reg ($4 directly, no pseudo), there'd be no merge — but the param is always a pseudo.

Unless... we can make the parameter used directly without a pseudo copy by having the function take the pointer as a different kind? The signature can't change.

Hmm, hold on: what about the `register` keyword in the body? Forbidden (no register vars).

What if a0 is used exactly once in the whole function? Then expand might keep the hard reg? No — PARM_DECL always gets a pseudo + prologue copy in this build (the copy at insn 4 exists regardless; for a single use it might be optimized? The copy `(set 72 (reg 4))` is always emitted in expand; flow/cse might propagate if 72 has one use...).

Let me test: what if a0 is used once (single load hoisted)? Not target.

New idea: **make 72 conflict with 76 by making 76 live into an arm block**. If the store were moved into the arms... no.

Hmm, let me look at this from the "known crack" angle: moves.md has many pin cracks. The relevant tags: lreg-copy-pref-dying-base (local-alloc), global-copy-pref, cse-copy-canonical. For a *global* pref from expand_preferences... Let me search moves.md for "expand_preferences" or "pref".
