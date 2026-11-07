---
ts: 2026-11-06T08:44:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UsoH7svg2FW7lBKNnleT
---
Score 33/35, same count but different order (the load moved). So sched1 didn't hoist it back.

Hmm. Different approach: keep the fifth load where it is but make `off`'s value needed later via a real computation that produces no extra insn... 

Wait. What if instead of off, we extend the a0-copy's refs. The a0 copy is used 5 times. What's the 5th? Let me check the w1 lreg uses of r72: lines 108,135,162 (three lhu) and 187 (move a1,a3 = call arg). That's 4 uses + 1 def = 5 "refs"? REG_N_REFS counts both sets and uses? In flow.c: `reg_n_refs[regno]++` for each use, and reg_n_sets separately. The comment: "Count (weighted) references, stores, etc. This counts a register twice if it is modified". So refs = uses + sets? The def is a set (counted in reg_n_sets, but the dump says "used 5 times" which is reg_n_refs). Hmm.

For r72: def at insn 4 (set), uses at 67, 76, and the third lhu, plus the call-arg move = 4 uses + 1 set = 5 refs. So refs = 5 includes the set.

To raise refs to 6, add a 5th use (a use that doesn't add an insn). 

Hmm, what if we use `a0` in the sp10 store of the call: `func_8012C51C(sp10, (s32)a0)` — the call insn uses the copy once. If the second argument were `(s32)a0 + (s32)a0 - (s32)a0`... cse would simplify? Actually that's an identity launder, disallowed and would add insns.

What about making the lhu address use the copy twice? e.g. `*(u16*)((s32)a0 + 6)` vs `((Unkstruct*)a0)->unk6`. Same.

Alternatively reduce r72's live length by making the copy die earlier and re-copying later? The target has a single copy in a2 used throughout. If we wrote `(Unkstruct*)a0` freshly in each of the 3 h updates, gcc creates one pseudo anyway (the param copy). 

Hmm, what if we avoid the param copy and use a0 (hard reg $4) directly for the three lhu's? Then no pseudo; but the target has `move a2,a0` — so there IS a copy.

Think about the second option: t3 live 6. The live length counted by flow is the number of insns where the reg is live (per flow.c line 2073 increment per insn where live). r77 t3 live 5 in w1: insns 39 (set), 42, 45, 48, 51 (use) = 5 insns where live? Actually the reg is live over 39..51; the increments happen in the loop over insns where it's in the live set. 5 insns: 39,42,45,48,51. To get 6, we'd need it live at one more insn. In the target's instruction order there is no extra insn between. So impossible via liveness in target order.

Unless... the pre-local-alloc RTL order differs from the final order! Local-alloc runs after sched1 (pre-reload), and then reload/sched2 can reorder. If the pre-local-alloc order has t3's store one insn later (e.g., after t4's load), then live=6 and r72 gets a2; and sched2 could then reorder to the final target order. In c1, I moved the store after the t4 load; the result lost the nop and kept t3=a2. Hmm, so at local-alloc time the store was already back at target position? c1's score 10 COUNT with 46 insns.

Maybe in c1 the pre-alloc order changed but the allocation didn't (t3 still a2) and then the missing nop appeared. Let me check c1's lreg dump to see t3's live length. Actually let me dump c1 and compare. But each dump is heavy (2 files ~?). Disk is capped at 4 GB free; dumps are large (the lreg file is 67k lines ≈ maybe 4 MB). Fine, but delete after.

Actually, let me reconsider the problem. Maybe the intended solution is much simpler: the keepalive exists to keep `off`/`t3` alive. A real C move: use the `off` value in the h[] computations by *reusing the address computation*. For example:

```
    off = a1 * 20;
    ...
    h[0] = h[0] + ((Unkstruct_800B5CB8 *)a0)->unk6;
```
What if we restructure to compute the fifth load from `off` but store t4 to sp10[4] later? That's c3/c4 — order changed.

Alternatively, restructure the loads so that t3 and t4 are both loaded early, then stored: c2 gave 16 (46 insns).

Hmm, what about the declaration order / init at decl? E.g., `s32 off = a1 * 20;` at the top. That changes the order of the off computation relative to the param copy? Let's try small variations:
- init at decl for off.
- declare t0..t4 as separate lines.
- use `s32 sp10[5];` before temps.
- compute `h = (u16*)sp10;` early (before loads).

Actually, wait. Let me reconsider the problem from the "what did the keepalive do" angle: it made `off` a register-allocated pseudo (r77 in w2, 3 refs, live 18) with pri 1666, which is BELOW r72's 3333. Then r72 got a2 and r77 got a3. But hold on — in w2, r77 is the pseudo that took a3, and its pri is 1666. In w1, t3 took a2 with pri 4000. The a0 copy r72 in w1 has 3703. If instead of adding a pseudo, we simply lower t3's priority... but we established live must be 6.

What if t3's refs drop to... no, refs≥2.

What if we make t3's *size* 2? qty_size is the number of words of the pseudo's mode. If t3 were a 64-bit (DImode) value, size 2 → pri doubles. That raises, not lowers.

What if t3 is not a separate pseudo but part of a multi-reg? no.

Alternatively make t2 or t1 take a2 instead of t3: order among ties is by qty number ascending. If we reorder the loads so that t3 is created (in RTL) BEFORE t2, then t3 gets a2? No wait, tie order is ascending qty number; the lowest qty gets first pick. If t3's qty number < t2's, then t3 gets a2 (still a2). We want t3 to get a3, i.e., t2 (or another) to take a2 first. Order: t1 (r75) → a0, t2 (r76) → a1, t3 (r77) → a2. To give a2 to t2 instead: t2 would need to be allocated after a0,a1 are taken and get a2 — that happens if t2's qty number is between t1's and t3's... it already is: 75 < 76 < 77. The registers are tried in allocation order: v0 (taken by r84), v1 (taken by t0? t0 pri 2000 comes later)... hmm wait, who took v1? In w1: r78 (t4) 10000 → v0? The dispositions: 78 in 2 (v0), 74 in 3 (v1), 75 in 4, 76 in 5, 77 in 6. So order: r84 (12000) → v0? but 84 in 2 too (v0, different range). r78 (10000) → v0. r75 (4000) → a0. r76 (4000) → a1. r77 (4000) → a2. r72 (3703) → a3. r74 (2000) → v1.

If t0 (r74) had pri > 4000, it would be allocated before r75..r77. t0's pri = 2*2/live = 2000 (live 10). To get pri > 4000, live must be < 5: e.g., live 4 → 5000. Then order: r84 v0, r78 v0? (r78 10000, but v0 taken by r84? their ranges don't overlap: r84 dies at the last load, r78 is t4 born at the last load — as discussed they can share v0? In w1 r78 got v0 and r84 got v0. Yes.) Then r74 (5000) → v1? v1 free (t0 can't take v0 since r84 lives across t0's range). So t0 → v1. Then r75 → a0, r76 → a1, r77 → a2. Still t3 a2.

To get t3 → a3, we need something to take a2 before r77. The candidates allocated before r77: anything with pri > 4000 or tie with lower qty. t1/t2/t3 all 4000, order 75,76,77. If we insert a pseudo with qty number lower than 77 and pri between 4000 and ... it would take a2 (if allocated before 77). For instance, if t0's pri became > 4000 AND t0 is allocated after a0,a1... no: t0 would take v1 first.

What if there were 5 temps with pri 4000 and the register order puts the 4th at a3? We have t1,t2,t3 at 4000 (3 of them) taking a0,a1,a2. If a 4th pseudo at 4000 existed with lower qty than 77, it'd take a2 and t3 → a3. Which pseudo? t0 could be made pri 4000 (live 5): order r75? ties sorted by qty: r74 < r75 < r76 < r77. r74 → a0, r75 → a1, r76 → a2, r77 → a3! Then the a0 copy (3703) gets... v1? Hmm no, r84 v0, r78 (10000) → ? Let me redo: pri: r84 12000 → v0; r78 10000 → v0 (share); r74,r75,r76,r77 = 4000 → a0,a1,a2,a3 in qty order; r72 3703 → v1? But then the a0 copy would be v1, not a2. Target wants a2.

Hmm no good.

OK, the w2 route: r72 at 3333 allocated BEFORE the other pseudo (1666), taking a2; the other takes a3. For this, the pseudo that takes a3 must have pri < 3333 and be allocated after r72. In target, t3 takes a3 with pri 4000 — but t3 is allocated before r72 (4000 > 3703)! Contradiction with w1... unless in the target's actual RTL, t3's priority is lower than 3703. We don't have the target's dumps (only the source that produces it is unknown!). The w2 body (off keepalive) produces the target code; its dumps show r72 pri 3333 and r77 1666 → r72 before r77. But w2's r77 is the off pseudo, not t3. In w2, where did t3 go? The dispositions: 72 in 6, 74 in 3, 75 in 4, 76 in 5, 77 in 7, 78 in 3, 79 in 4, 84 in 2. Which is t3? Maybe r79 (2 refs/7, pointer?) or... The loads: t0=r74, t1=r75, t2=r76, t3=?, t4=r78. r79 (2 refs, 7 insns, pointer) is probably t3? But pointer? t3 = *(s32*)((char*)&D_801A546C + off) — it's a loaded value, not pointer. Hmm, "pointer" may come from its use in sp10[3] = t3? no.

Let me look at w2's RTL to identify r77 and r79. Let me grep the w2 lreg dump around insn 39.
