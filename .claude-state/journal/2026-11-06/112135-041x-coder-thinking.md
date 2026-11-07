---
ts: 2026-11-06T18:21:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bvXsj18tysHcbJjj4dsA
---
find_reg: it finds the lowest free reg (best_reg), then if there's a *copy* preference, it may override best_reg with the preferred copy reg (only if free). Then normal preferences can override best_reg too. So 76: best_reg = $3 (since $2 used), then hard_reg_preferences[76] = {4} → $4 is free and same class → best_reg = $4. Hence $4.

So if we could make 76's preference NOT include 4, or make $4 used (`used` includes hard_reg_conflicts[76] and regs_used_so_far and regs_someone_prefers), 76 would take $3.

`used` = used1 (fixed regs etc + hard_reg_conflicts[76]) ∪ complement(regs_used_so_far) ∪ regs_someone_prefers[76]. In pass 0, registers used by *conflicting higher-priority* allocnos are excluded. regs_someone_prefers[76]: registers preferred by conflicting lower-priority allocnos (72 is lower priority than 76! order 75 76 72 74). prune_preferences: for i from last to first (least important first): for allocno at i, merge prefs of conflicting lower-priority ones into regs_someone_prefers[allocno].

So regs_someone_prefers[76] would include $4 if 72 (lower priority) conflicts with 76 and prefers $4. But 72 doesn't conflict with 76 (as established). So no exclusion.

If 72 and 76 DID conflict, then:
- expand_preferences wouldn't merge prefs (requires no conflict) → 76 wouldn't prefer 4 at all → best_reg $3, no pref → $3. 
- Also regs_someone_prefers[76] would include $4 → excluded.

So making 72 and 76 conflict solves it. How? 72 must be live at insn 32 when 76 is born — i.e., 72 must be live-out of the arm blocks (or at least not die at the load).

Simplest: use a0 AFTER the load in the same arm block. The only statement after the load in each arm is `v0 = 2` (or the store in block 5). But the target's arm blocks end right after the load; adding a use would add an instruction unless it's free.

Hmm, what real C use of a0 after the load could be free? 

Wait — actually, the target *itself* has the same structure, so the pinned version also has 72 and 76 not conflicting; the pin overrides. For a lever-free crack, we need a different real-C structure that produces the same instructions. 

Alternative: make the load's base be a DIFFERENT pseudo than the param copy 72, one that is live across the load. E.g., introduce `p = a0;` (a copy) and use p for the loads. Then 72 (param copy, dead at entry) and p... p would be the new base. But that adds a move $4→p; global-alloc would coalesce p with 72? p's only def is from 72, so copy coalescing: p gets $4 and the copy is deleted. Then we're back.

Unless the copy can't be coalesced: e.g., p is used in all 3 arms (like 72), same. Hmm.

Alternative: make a0 (the param) itself the load base without the param copy — i.e., avoid the copy by making the parameter's pseudo... impossible in this compiler? Actually, why does the copy exist? PARM_DECL a0 is assigned a pseudo and the prologue copies $4 into it. That's standard. But in many cracked functions, the arg is used directly as a hard reg... e.g., in the .lreg dump of the pinned orig, would there be a copy? Let me check: the pinned version has `void *a0` used 3 times — the same copy. Yes.

OK so another approach: **change 76's live range so that it conflicts with 72**. If 76 were live at the *start* of an arm block (i.e., used before set in a later arm)? Not possible.

**Change which pseudo is the load result**: what if v1 is a *different* variable per arm and the store uses a value passed through... no.

**Make the load's dest conflict with 72 by making 72 live-out**: put the store inside each arm? Then the target would have the store duplicated — not the target.

Hmm. Wait, maybe there's a completely different angle: make the load NOT be `(set (reg) (mem (plus (reg 72) 204)))` but `(set (reg) (mem (reg 72)))` where 72 = a0+204 computed earlier. That is, compute `v1 = (s32)a0 + 0xCC` before the branches (one addiu, hoisted), then in each arm `v1 = *(s32*)v1`? No, that changes v1's value and adds an insn.

What about a pointer variable `Unkstruct_80184B70 *p = a0;` used in the arms? same.

Let me think about the real source: maybe the original code used a local pointer variable, e.g.:

```
s32 v1;
...
v1 = ((Unkstruct *)a0)->unkCC;
```
The target's registers are what they are because of the pin. For lever-free, we need a real-C change that makes gcc pick $3. Since 76's pref for $4 is the obstacle, and it comes from the param-copy allocno 72's pref via expand_preferences (REG_DEAD 72 at the load)...

What if the load base is not 72 but a pseudo that has NO preference? E.g., if the base were computed as a separate variable: `void *p = (void *)((char *)a0 + 0xCC); v1 = *(s32*)p;` — combine folds the addiu into the load → base is p, and p's pref? p would be a copy/arith from a0: `(set p (plus 72 204))` → set_preference(p, plus) → src = plus → not REG → no pref. But combine would fold `addiu p,72,204; lw v1,0(p)` into `lw v1,204(72)` and delete p. Then base = 72 again.

Unless the addiu is used elsewhere too (so it can't fold). Hmm.

**Alternative: use a union/struct field offset that combine can't fold?** No.

**Alternative: make the param copy die before the arms** by using a0 only in the first arm? no.

**Alternative: get a *copy preference* for $3 on 76.** find_reg prefers copy preferences over normal ones, and copy prefs are tried first (the copy-pref block runs before the normal-pref block and `goto no_prefs` on success). If 76 had a copy preference for $3, it would win over the normal pref $4 (the copy block comes first and jumps to no_prefs). How to give 76 a copy preference? A reg-reg copy involving 76 where the other is hard reg $3... impossible without a pin.

But wait: expand_preferences merges copy prefs from a dying allocno when `XEXP(link) == SET_SRC(set)` (a real copy). Not our case.

**Alternative: make 72's pref different.** 72's pref $4 comes from the prologue copy. expand_preferences merges it. Could we make 72 conflict with $4? It IS $4.

**Alternative: allocate 72 locally** (block-local). If 72 were local to block 0 only... it's used in blocks 2,3,4.

**Alternative: reduce a0's uses to fit in fewer blocks?** No.

Hmm, let me reconsider: what if we make the three arms share ONE load by hoisting it? Then a0 is used once, in block 0/1, and v1 is live across all arms. Target has two loads (after jump2 merge) — but a single hoisted load would produce `lw v1` before the compare, then no loads in the arms. That's 1 insn fewer... but wait, target has TWO loads (d24, d30) because two arms merged. Hmm, so target = 2 loads.

Actually, could a hoisted load give the same? Target: lw in two blocks. No.

**Alternative: swap the roles — make v0 the loaded pointer and v1 the flag?** No, that changes regs.

Let me look at the problem from the other direction: maybe make 76's priority LOWER than 72's, so 72 is allocated first. Order would be 75 72 76 74 (if 76's pri < 72's 8000). Then:
- 75 → $2.
- 72 (pref $4) → $4.
- 76: best_reg $3 (since $2 used; $4 used by 72 via regs_used_so_far → excluded in pass 0). Pref $4 is in `used` (regs_used_so_far) → pruned → $3. MATCH!

So if 72 is allocated before 76, 76 gets $3. 72's pri = 8000, 76's = 10000. Need 76's pri < 8000 while keeping the same insns. 76: refs 4, live 8 → pri = floor_log2(4)*4/8*10000*4 = 2*4/8*10000*4 = 40000? Hmm, the table said 10000 for r76 and 8000 for r72. Formula: floor_log2(n_refs)*n_refs/live*10000*size. r76: floor_log2(4)=2, 2*4=8, /8=1 → 10000*4(size)=40000? The table says 10000. Hmm, the alloc_table's pri column might use a different formula (without size). Whatever: 76 > 72.

To lower 76's pri: increase its live length or reduce refs. 76 has refs 4, live 8. If live became 11+, pri = 2*4/11 = 0.72*... < 8000. How to increase 76's live length without changing the code? Make 76 live from an earlier point... e.g., define 76 earlier (hoist one load?) no.

Or reduce 76's refs: refs 4 = 3 defs + 1 use. Can't.

Or increase 72's pri: 72 refs 4, live 10. Increase refs of 72? Add a use of a0... would add insns.

Hmm, what about making 76's live length longer by having the store in a later position? The store block is at the end. If there were more code after the load before the store... no.

Hmm, what about the dead value: maybe an extra (dead) definition of 76 in an earlier block would increase its live length? Dead defs get removed by flow.

Let me reconsider the structure. Maybe there's a much simpler route: the target's `v1` in the arms. What if the source uses `s32 v1` but the load is `v1 = ((Unkstruct*)a0)->unkCC;` where the struct field unkCC is `u32` and v1 is `u32`? Type changes don't change RTL.

What if we change `void *a0` usage to `(Unkstruct_80184B70 *)a0` cast at the parameter level: `void func_80184B70(void *a0, ...)` — the signature can't change.

What if we use a *global* temporary? no.

Hmm, let me look at whether the target function's original (pre-lever) source exists somewhere — maybe in a doc/notes for this shard. The item dir has notes? No notes.md yet. Let me check the W48 shard notes or other shards' notes for this func. Search .run/P40/T11 for "80184B70".

Also check the moves.md line 44/45 area for W48: "cse-copy-canonical | cse | cse canonicalises a reg copy onto the older pseudo; target keeps the pinned reg (W48)". That's for a different item maybe.

Let me grep moves.md for 80184B70.
