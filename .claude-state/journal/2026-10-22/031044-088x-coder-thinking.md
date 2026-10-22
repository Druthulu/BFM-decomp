---
ts: 2026-10-22T09:10:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GFEUwUrR8VZzmgkaGxau
---
All the s16-flag variants give 24. The score is dominated by the ot/w swap.

Now let me focus on the ot/w swap: I need ot's priority > w's.

Current: ot (r72) pri 4225 (refs 10, live 71); w0 (r73) pri 4500 (refs 15, live 100).

Levers:
(a) ot refs +1 → 4650 ✓
(b) ot live ≤ 66
(c) w refs 14 → 4200 ✓
(d) w live ≥ 107

Hmm! For (c): w's refs = 15. What are they? The param copy (w0 → a1 = 1 ref?), the 13 field accesses, hmm.

Hmm, wait: in family A (w0 used directly), w0's refs = 15. Hmm, in family B (w = w0 kept), the `w` pseudo has 15 refs (the field accesses) and w0 has 1.

Hmm! In family B, the global would be `w` (15 refs, live 100) and w0 (1 ref, dead early → not global). So the pri is the same (4500). Hmm, but the *live length*: `w`'s live = from the copy (insn ~6) to the last use → ~100. Same.

Hmm.

OK, lever (a): +1 ref to ot. Let me think about the *loop*: `ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);` — the loop body. The refs are loop-depth weighted: if the loop depth is 1, the weight is 1. Hmm, but what if the loop is *nested*? The `for(;;)` with a break — gcc's loop depth for that block might be 1. Hmm, the target's asm shows the loop body.

Hmm, what if the source had the loop body mention ot once more? E.g.:
```
ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
```
→ 2 mentions (1 use + 1 def). What if:
```
ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
```
Hmm.

What about the *first* two calls:
```
ot = func_800D2650(ot, sp18, w0->f10, w0->f12, 1, flag != 0 ? ...);
ot = func_80188F14(ot, w0->f18, idx, w0->f8, flag2 != 0 ? ...);
```
ot: 1 def + 1 use each = 4 mentions.

And the final: `func_800D27DC(flag4 != 0, ot, w0->f4, w0->fC, 0)` → 1 use.

Total: the param def (1) + 3 defs + 4 uses = 8? The table says 10 (with loop weighting).

Hmm. To add a ref: what if the source used ot in a way that's redundant but not folded? Hmm, forbidden (identity launder).

Hmm! What about this: the loop's call could take `ot` twice? no.

Hmm, what about the *order* of the two assignments: if `ot` were assigned in a way that the compiler keeps 2 pseudos...

Hmm, hold on! What about the *return*? The function returns `func_800D29F8(...)` — its result. What if the source assigned the result to `ot` and returned ot? I said that adds a `move v0,ot` ✗. Hmm, BUT: what if the result is assigned to ot and the *return* is `return ot;` — the compiler needs the return value in v0. ot is a global in s1 → `move v0,s1` ✗ (an extra insn).

Hmm, unless ot is NOT global... no.

Hmm. OK, lever (b): ot's live length ≤ 66 (from 71). ot's live = from the param def (insn 4) to the last use (the func_800D27DC call near the end, insn ~1250). The function is 115 insns. Hmm, live 71 — hmm, the live length counts the insns in the live range (71 insns from the def to the last use).

To shorten it: hmm, the def is at the entry. The last use is at the end. Hmm, 71 of 115.

Hmm, what if ot's *first* def were later? I.e., ot's param is used early (`ot = func_800D2650(ot, ...)` — the first use of the param ot is early) → the param's live starts at the entry.

Hmm, so the live range is fixed by the structure.

Lever (d): w's live ≥ 107 (from 100). Hmm, w's live = from the param def (the entry) to the last use (w0->fE, near the end). 100 of 115. To get 107+, the def would need to be earlier (impossible) or the last use later (impossible).

Hmm!! Unless... the *live length* is computed differently: `REG_LIVE_LENGTH` = the number of insns in the live range. Hmm.

Hmm, hmm. OK, so lever (a) — ot's refs — is the main one. Let me think harder.

ot's refs = 10. The mentions of ot in the source:
1. param
2. `ot = func_800D2650(ot, ...)` → 2
3. `ot = func_80188F14(ot, ...)` → 2
4. loop: `ot = func_800D2650(ot, ...)` → 2 (×loop depth)
5. `func_800D27DC(..., ot, ...)` → 1
Total = 1+2+2+2+1 = 8, with the loop weighted (depth 1 → 2) = 8. Hmm, the table says 10. Maybe the RTL has extra mentions (the copies).

To add a ref: hmm! What if the *loop* body were deeper (loop depth 2)? Then ot's refs in the loop would be 2×2 = 4 → total 10 → hmm, that's what it is now (10). Hmm.

Hmm, so what if the loop's depth were higher? E.g., if the source had the loop inside an `if` inside a loop? That changes the code ✗.

Hmm, what if ot's *uses* were increased by one legitimately? Hmm.

Hmm, hmm. What about the *first* call: `func_80024054(w0->f14, sp18);` — no ot.

Hmm, what about the *order* of the statements: `ot = func_800D2650(ot, ...)` — the arg `ot` and the dest `ot` are the same variable. What if the source were:
```
ot = func_800D2650(ot, sp18, w0->f10, w0->f12, 1, flag != 0 ? 0x585858 : 0x808080);
```
Hmm.

What if I split the loop's assignment so that ot is mentioned 3 times in the loop body? E.g.:
```
ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
```
→
```
s32 *ot2 = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
ot = ot2;
```
ot's mentions in the loop: the arg (1) + the assignment `ot = ot2` (1) = 2 (same). Hmm, no gain. Unless the compiler doesn't optimize `ot = ot2` away (it would: the copy is coalesced/removed, but the *mention* count in the RTL... hmm, if the copy is removed by combine/cse, the mention disappears ✗).

Hmm. What if the split were:
```
ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
ot = ot;  // forbidden
```
no.

Hmm, what about the *other* direction: reduce w's refs by 1 via a *local copy of a field* — I dismissed it because of the extra move. Hmm, but let me check: `s32 f4 = w0->f4;` — the load `lw a2,4(s2)` in the target is the arg-passing. With a local f4, the RTL would be: `(set (reg/v:SI f4) (mem (plus (reg w0) 4)))` then the call arg copy `(set (reg:SI 5 a2) (reg/v:SI f4))`?? Hmm, wait, f4 is the 3rd arg → a2. So the call's arg setup: `lw a2,4(s2)` (a direct load into a2) in the target. With a local: `lw v0,4(s2)` (or some reg) + `move a2,v0` ✗ — an extra move.

Hmm, unless local-alloc gives f4 the reg a2 directly (the load's dest = a2) — then the asm is `lw a2,4(s2)` ✓✓ and no extra move! local-alloc's find_reg picks the lowest free call-clobbered reg: at that point, a0 (the flag4 test), a1 (ot), a2 (free?), a3 (w0->fC) — hmm, the args are set up in order: a0 = flag4, a1 = ot, a2 = f4, a3 = w0->fC. The local f4 would be assigned... hmm, local-alloc assigns the load's dest a reg; the "preferred" reg for a call arg is the arg reg (via the copy preference) — the copy (set (reg a2) (reg f4)) creates the preference a2 for f4 → f4 → a2 ✓✓!! (That's the "copy preference" mechanism: a pseudo used as a call arg prefers that arg reg.)

So `s32 f4 = w0->f4;` might produce exactly `lw a2,4(s2)` ✓ and reduce w0's refs by 1 (15 → 14) → pri 4200 < ot's 4225 ✓✓✓ → ot allocated before w → ot → s1, w → s2 ✓!!

Hmm! But careful: the *live length* of w0 would also change? No (still used at the end).

And the ORDER of the load: the source would be:
```
    flag4 = flag2;
    f4 = w0->f4;
    return func_800D29F8(flag4, func_800D27DC(flag4 != 0, ot, f4, w0->fC, 0), w0->f8, w0->fE, 0);
```
Hmm, but the *evaluation order* of the args: func_800D27DC's args are evaluated before func_800D29F8's args. In the target's asm, the order is: flag4 test → a0, the `sw zero,16(sp)`, then `lw a2,4(s2)` (f4) → a2, then the call. So the f4 load happens before the call ✓. With `f4 = w0->f4;` before the return statement, the load would be at the same place ✓ (just before the return's arg setup).

Hmm, but the ORDER of the loads: in the target, `lw a2,4(s2)` (f4) comes BEFORE `lh a3,14(s2)` (fE) and `lw a2,8(s2)` (f8) — i.e. the inner call's args are set up first ✓. With the local f4 loaded before the return statement, the load would happen before the flag4 test (a0) maybe? Hmm: the source order would be: f4 = w0->f4 (the load), then the return statement (the flag4 test → a0, then the inner call's args: a1 = ot, a2 = f4 (already in a2 ✓), a3 = w0->fC).

Hmm, the target's order: `sltu a0,zero,s0` (the flag4 test) at 1244, then `sw zero,16(sp)` at 1248, then `lw a2,4(s2)` at 124c. So the flag4 test comes BEFORE the f4 load. With the local, the f4 load would come first (it's earlier in the source) → the order changes → a different insn order → the diff might grow (the masked diff might still match since it's a permutation? no, the masked diff is order-sensitive).

Hmm. Risky. But worth a try!

Hmm, alternatively: which w0 field could be moved into a local without changing the order? The fields used in the final call: f4 (a2 of the inner call), fC (a3 of the inner call), f8 (a2 of the outer call), fE (a3 of the outer call). The order in the asm: f4 (a2) → the inner call → fE (a3) → f8 (a2) → the outer call.

Hmm, the inner call's args: (flag4!=0 → a0, ot → a1, f4 → a2, fC → a3). So f4 → a2 and fC → a3.

If I made a local for fC (the last inner-call arg), the load would move earlier (before the flag4 test) ✗ same problem.

Hmm. What about a field used EARLIER in the function, e.g. w0->f14 (the first call)? `func_80024054(w0->f14, sp18);` — the target: `lw a0,20(s2)` at 1114 ✓. If I made a local `s32 f14 = w0->f14;` before that call — the load would be at the same place (just before the call) ✓✓ and the order preserved! But: the call `func_80024054(w0->f14, sp18)` — f14 is the 1st arg → a0. With a local, the local f14 would prefer a0 (the copy preference) → `lw a0,20(s2)` ✓ (the same insn!).

Hmm! But careful: the load's position relative to the other insns: the target has:
```
 1114 lw a0,20(s2)      ; w0->f14 → a0
 1118 xor s0,s0,a2       ; the flag computation
 111c sltu s0,zero,s0
 1120 negu s0,s0
 1124 jal func_80024054
 1128 andi s0,s0,0xff
```
Hmm! The load (1114) comes BEFORE the flag computation (1118-1120) even though the source has `flag = -(D_8011511A != idx) & 0xFF;` BEFORE `func_80024054(w0->f14, sp18);`. So the scheduler moved the load earlier (sched1) ✓. With a local f14, the load might be scheduled differently (it depends on the local's def). Hmm, if the source is:
```
s32 f14 = w0->f14;
flag = ...;
func_80024054(f14, sp18);
```
the load would be before the flag computation in the source → probably the same asm ✓. Hmm, but the scheduler might place it differently.

Hmm, hmm. And this reduces w0's refs by 1 → 14 → pri 4200 < 4225 ✓.

Hmm! But hold on: the flag computation `flag = -(D_8011511A != idx) & 0xFF` mentions D_8011511A and idx — not w0 ✓.

Let me try a few variants:
V_a: `s32 f14 = w0->f14;` before the flag computation, and `func_80024054(f14, sp18);`.
V_b: `s32 f4 = w0->f4;` before the return.
V_c: both.
V_d: the return split (`ot = func_800D29F8(...); return ot;`).

Hmm, and also: what about a local for w0->fC (the inner call's 4th arg)? Same issue as f4.

Let me also consider: reducing w0's refs by 1 might be enough (4200 vs 4225 — a narrow margin!). Risky but let's try.

Also: increasing ot's refs by 1: hmm, what if the *first* call `func_80024054(w0->f14, sp18)` — no ot.

Hmm! What about: `ot = func_800D2650(ot, ...)` — the *first* one. What if the source were:
```
ot = func_800D2650(ot, sp18, w0->f10, w0->f12, 1, flag != 0 ? 0x585858 : 0x808080);
```
Hmm, 2 mentions.

Hmm, what if I split the ternary into a local?
```
s32 col = flag != 0 ? 0x585858 : 0x808080;
ot = func_800D2650(ot, sp18, w0->f10, w0->f12, 1, col);
```
That doesn't change ot's refs but reduces... hmm, no.

OK, let me just try the variants. Let me write them.

Actually, hold on! Let me reconsider the *live length* lever for ot: ot's live = 71. The def is the param (insn 4) and the last use is the func_800D27DC call. Hmm, what if the *last use* of ot were earlier? It's the last use in the source. Hmm.

And what about w's live = 100: the def is the param (insn 4-6) and the last use is w0->fE (insn ~1258). Hmm.

Hmm, hmm: what if the *order* of the two final calls' args were swapped? no.

Let me try the variants now. Time: 2h40m. I should wrap up within ~30 more minutes for item 2, then do item 3 (which is a twin — I can reuse the levers), then write the logs.

Let me write the variants for item 2.
