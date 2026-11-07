---
ts: 2026-11-06T05:12:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DqvSX04WCGZnadgsPFLc
---
Now I understand the target. Differences:

1. Target frame 56, a=16, b=24, out=32..39 (frame 40 + ra/s0/s1 = 56). Candidate frame 72: because out is at 32, a=16, b=24 — same offsets, but frame 72 vs 56. The extra 16 bytes in candidate: candidate's out copy uses `lwl/lwr` from 32..39 and stores, same. Hmm why 72? Maybe because candidate has 2 more values live, causing spills? Wait, frame is determined at final, spills into stack. The candidate has more live values? Actually candidate needs stack for something... Hmm, the candidate at a91c `move a0,v1` and at a914 `move a1,v0` — these are because the values v0/v1 are live across the branch, and they're caller-saved, so the scheduler needs them in regs. But no stack.

Wait: frame 72 vs 56 difference of 16. Maybe out array is 8 bytes but with the memory clobber... no. Let me think: In the target, out at sp+32 (8 bytes, 32-39), total frame 56 = 40 + 16 (saved regs 3*4=12 + pad). Candidate: out also at 32. So same locals. But candidate frame 72 = 40+32? Hmm.

Maybe the candidate allocates `a`, `b`, `out` at 16,24,32 = 40 bytes total; frame needs 40 + 3 saved regs (12) + alignment. 40+12 = 52 → round to 56. Target 56. Candidate 72 means locals = 56? Or spills.

Ah, maybe the candidate has stack spills of live values. Since the candidate's `v0`/`v1` values (a+2, b+2) need to be live across the branch, but they get moved into a1/a0 (caller-saved, but no call between). Not stack.

Hmm, what about `move a1,v0` — the compiler moved the loaded a+2 into a1 because... v0 gets clobbered. Not stack.

Let me get the frame info from the RTL dump. But first, key insight: the target reloads each array element separately (lhu v0,16(sp); nop; sh). The candidate cse'd: it kept v0/v1 across, and also, the extra 6 insns in target are nops after loads (delay slots) + reloads.

Actually the target has 95 insns, candidate 89: target has 3 extra nops after loads in then-arm (3) + 2 nops in else-arm? Let me count: target then-arm: lhu v0,16; nop; sh; lhu v0,18; nop; sh; lhu v0,20; nop; sh = 3 extra nops and 3 reloads vs candidate's 2 loads+sh and moves. Hmm.

Candidate then-arm: lhu v0,16(sp); sh a1,122(s0); sh v0,120(s0); lhu v0,20(sp); nop; sh v0,124(s0). So candidate uses `a1` (loaded a+2 before the branch) for the 122 store, and reuses v0.

So the core: target reloads a+2 from stack inside the then-arm (`lhu v0,18(sp)`), candidate keeps it in a register (a1). Similarly else-arm target reloads b+2 (`lhu v0,26(sp)`).

What real C move forces a reload? The barrier (memory clobber) makes cse invalidate the memory location, so the value can't be forwarded. Without it, cse knows sp+18 has a+2 and the value loaded at a90c (lh v0,18(sp)) is still valid... but wait, in the candidate it does `move a1,v0` at a914 then uses a1 at a928. So cse (or combine) turned the reload into a register copy.

The real C move could be: change the comparison so the value is not held across the branch, i.e. re-read a[2] inside the arm in a way that cse can't forward. Options:
- Make the comparison use a different variable than the store, so no copy is needed. E.g. compare `*(s16*)(a+2)` (loaded), then inside the arm store `*(u16*)(a+2)` — cse still knows the memory location.
- Use a volatile? No — volatile is a lever of kind "barrier"? The kinds are "barrier". Volatile might count as barrier-ish. Actually the constraint says lever-free = no pin, launder, barrier, keepalive macro or asm; no new lever of any kind. `volatile` is a barrier-type lever. Not allowed.

Hmm, what real C move? The target's pattern of reloading suggests the original source had something that blocked cse. Perhaps the original code compared and stored via different expressions that cse doesn't equate. Or the original used a temp variable assignment that kills the equivalence: e.g.

```
s16 av = *(s16 *)(a+2);
s16 bv = *(s16 *)(b+2);
if (av < bv) {
   store a[0], a[2], a[4]
```

Hmm that's the same.

Wait: in the target, the values are loaded at a90c/a910 (`lh v0,18(sp)`, `lh v1,26(sp)`) for the comparison, then inside the then-arm reloaded (`lhu v0,18(sp)`). So the comparison loads are separate from the store loads. The memory clobber forced the store loads to be fresh. To reproduce without the barrier, we need cse to not know that the comparison loads and store loads are the same memory. But they're the same expression `*(s16*)(a+2)` vs `*(u16*)(a+2)` — cse handles lh vs lhu? cse uses MEM with mode; a HImode mem with same address — cse might treat lh and lhu as different (different mode is same HImode; SIGN_EXTEND vs zero? In 2.7.2 cse, `lh` and `lhu` are different rtx (sign_extend/zero_extend) but cse's canon_hash on the mem... For a load, the memory is HImode; the sign extension is applied. cse records (mem:HI (plus ...)) with an address; both lh and lhu are sign/zero extend of the same HImode mem, so cse should equate the memory part? Hmm, cse stores the whole SET source, which for lh is (sign_extend:SI (mem:HI ...)) and for lhu (zero_extend:SI (mem:HI ...)) — different. But cse has a special "memory" handling: it invalidates by address.

Wait, but in candidate, the comparison loads `lh v0,18(sp)` and `lh v1,26(sp)` — then it moves them. In the target too, the comparison loads are `lh`. The store loads are `lhu`. So different extensions, but cse's memory table is keyed on the address, so after a store to a different address, the value at sp+18 is unchanged. Hmm.

Actually candidate's `move a1,v0` at a914 is not a reload of memory; it's moving the comparison value. In the target, after the branch, `lhu v0,18(sp)` reloads. Why does target reload instead of using the comparison value? Because the barrier clobbered memory equivalence — cse forgets everything after an asm with memory clobber, so the value must be reloaded.

To force that in pure C, we need cse to invalidate the memory equivalence without asm. A store to a possibly-aliasing location would do it! If between the comparison and the store we write to memory that might alias sp+18, cse invalidates the mem. But then it would also need to reload...

Hmm, but that's a "launder"-ish trick. The constraint says real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse). So we can't use aliasing stores as a lever.

Maybe simpler: the difference arises from how the comparison is written. If the comparison uses `*(u16*)` and the store uses `*(u16*)`, maybe the codegen differs. Let's think about what makes target NOT forward.

Alternative: split the condition. Target:
```
lh v0,18(sp)   # a[2]
lh v1,26(sp)   # b[2]
nop
slt v0,v0,v1
beqz v0, else
nop
then: lhu v0,16; nop; sh 120; lhu v0,18; nop; sh 122; lhu v0,20; nop; sh 124
```
Note `slt v0,v0,v1` then `beqz v0` — the branch on the slt result. So the target is `if (a2 < b2)`.

Candidate:
```
lh v0,18(sp)
lh v1,26(sp)
move a1,v0
slt v0,v0,v1
beqz v0, else
move a0,v1
then: lhu v0,16; sh a1,122; sh v0,120; ...
```
The candidate keeps a1/v1 in regs.

What if we write the condition to consume the values differently, e.g., store into local temps first:
```
s32 av = *(s16*)(a+2);
s32 bv = *(s16*)(b+2);
if (av < bv) { ... }
```
That's basically the same.

Hmm — what if the comparison is done on the *stored* values (the e->0x7a field)? No.

Let me consider: the reason target reloads may be that the memory clobber makes the compiler treat a and b as clobbered, so the values in regs are dead, forcing reload. Pure C: if the arrays were declared `volatile`, reloads happen — but volatile is a barrier lever.

Alternatively, maybe the target's reload comes from a *different* source structure: e.g., the store writes `*(s16*)(e+0x7a) = *(u16*)(a+2)` where the value expression is used and the comparison uses a *copy* stored earlier. Hmm.

Wait, here's a thought: the comparison loads at a90c/a910 are `lh` (signed). The stores reload with `lhu` (unsigned). If the code reads the comparison from a variable and the stores from a fresh expression, cse would still equate. But if the comparison uses a `s16` variable and stores use `u16` expression... same address, cse's memory equivalence is per-address, so it would forward.

But note: cse forwards only if the *mode* matches? In GCC 2.7.2 cse, `cse_insn` for a load: it checks `MEM` with `cse_process_notes`... The canonicalization: `(sign_extend:SI (mem:HI (reg)))` vs `(zero_extend:SI (mem:HI (reg)))`. The memory reference itself is `mem:HI` — same. cse's hash table entries are keyed by the full rtx including the extension? For a load insn, cse_insn records the destination register's value as the SET_SRC, which includes sign_extend or zero_extend. So `lh` → sign_extend:SI(mem:HI), `lhu` → zero_extend:SI(mem:HI). These are different rtx → different hash. So cse would NOT forward an `lh` value into an `lhu` use. But the candidate's `move a1,v0` suggests combine or reload did something.

Hmm, in candidate, the comparison uses `lh` and store uses `lhu`; yet it forwards via `move a1,v0`? That would be combining the lhu into the lh because it knows the value is non-negative? Actually `move a1,v0` copies the lh result; then `sh a1,122`. The store needs HImode; cse/combine could convert the store to use the HImode subreg of the lh result. Since `lh` result in v0 has the value sign-extended, and storing HImode takes the low 16 bits — same bits. So combine sees `sh` of `(subreg:HI (sign_extend:SI (mem:HI)))` and can store directly from the mem? It'd need the mem value. Actually it turned it into a register move because the value was in v0.

OK, the mechanism is subtle. Rather than reverse-engineering deeply, let me try candidate C moves empirically. The task expects this. Let me try several quick variants:

1. Reorder: do the comparison as `if (*(s16 *)(a + 2) < *(s16 *)(b + 2))` but store `a[0]` etc. through fresh expressions — same as now.
2. Use separate local variables for the compare: `s32 t = *(s16*)(a+2); if (t < *(s16*)(b+2))`.
3. Make the comparison read a *different* location: no.
4. Change the order of the then-arm stores: target stores 0x78=a0, 0x7a=a2, 0x7c=a4. Currently that's the order.
5. Use `*(u16*)` for the compare instead of `*(s16*)`. Then target's `lh` would become `lhu` — changes.

Hmm, wait. Let me look at the diff more carefully:

target then-arm:
```
a924: lhu v0,16(sp); nop; sh v0,120(s0)
a930: lhu v0,18(sp); nop; sh v0,122(s0)
a93c: lhu v0,20(sp); nop; sh v0,124(s0)
```
These reloads are exactly the same value as loaded at a8ac/a8c4/a8d8 (`sh v0,16/18/20(sp)`)? Wait no: a8ac stores v0 to 24(sp) and 16(sp), a8c0/a8c4 to 26/18, a8d8 to 20, a8d0 to 28. So a[0] at 16, a[2] at 18, a[4] at 20; b[0] at 24, b[2] at 26, b[4] at 28. The target reloads a[0], a[2], a[4] from stack in the then-arm and b[0],b[2],b[4] in the else-arm. Because calls may have modified a and b! The arrays are passed to func_801502EC(a, out) and func_80150460(b) — so the calls may write them. So the reload is semantically required. The compiler with the barrier (memory clobber) knows memory changed. Without the barrier, why would it NOT reload? Because... cse's memory equivalence: the calls are opaque calls; GCC must invalidate memory at calls. Unless it knows the callee doesn't write? It can't.

Hold on — maybe without the barrier, the compiler *did* reload but then combine/cse folded the reload into the already-live register? Let's look at candidate then-arm:
```
a924: lhu v0,16(sp)   # reload a[0] — yes reloaded
a928: sh a1,122(s0)   # a1 = a[2] (from comparison load, NOT reloaded)
a92c: sh v0,120(s0)
a930: lhu v0,20(sp)   # reload a[4]
a938: sh v0,124(s0)
```
So candidate reloads a[0] and a[4] but NOT a[2]; it uses a1 (the comparison value). Why would a[2] not be reloaded? Because a1 was loaded after the call? No — the comparison load is at a90c, after both calls. And the reload at a930 is also after. So the comparison load of a[2] at a90c is *after the calls*, so it's a valid current value, and cse can forward it into the store. The target doesn't forward it — why? The barrier invalidates cse knowledge so the load at a90c isn't recorded for forwarding? No wait, the barrier is inside the if-arm (after the comparison), so at the time of the comparison load (before the barrier), cse records it, then the barrier (memory clobber) flushes cse's memory table, so the store can't reuse it. That's exactly the mechanism: cse-store-forward.

In the target, the comparison `lh v0,18(sp)` result would be reusable for `sh ...122`, but the memory-clobber barrier between them flushes cse's table, forcing a reload.

Without the barrier, cse forwards. So we need a pure-C way to stop cse from forwarding the comparison load into the store. The C0505 catalog: "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse". None obviously flushes cse. But maybe we can restructure so the comparison value is loaded into a *different mode* than the store, such that cse can't forward. Currently the store of a[2] uses `*(u16*)(a+2)` (lhu) and comparison uses `*(s16*)(a+2)` (lh). cse shouldn't forward lh into lhu... yet it does (as a `move`). Hmm, maybe it's not cse but combine: `sh` of `(subreg:HI (reg))` where reg holds sign_extend — combine can use the reg directly since HImode truncation of the SI value equals the mem. Yes! combine knows that storing HImode of a sign-extended HImode load = the original memory value, and since the value is in a register, it uses it.

So to block that, we need the stored value to not be a simple truncation of the comparison register. Hmm.

Alternatively — and this is the key — maybe restructure so the comparison result register is not available: e.g., the comparison could be written as `(s16)a[2] < (s16)b[2]` where a[2] is loaded as u16. Then target uses lhu for compare, and the store's lhu would be cse-forwarded... Hmm.

Let me step back and consider the practical approach: this is a search task. We have 5 items, 20-30 min each. Let me try a handful of variants quickly per item, guided by what the diff says.

For item 1, variants to try:
A. Reorder the arm's stores (a4, a0, a2) — affects scheduling not cse.
B. Use a temp for the comparison: `s32 c = *(s16*)(a+2) - *(s16*)(b+2); if (c < 0)`.
C. Compute the comparison before the calls (hoist the lh loads above the calls)? Can't, values change.
D. Store via a pointer variable: `s16 *pa = (s16*)a; ... *(s16*)(e+0x7a) = pa[1];` — pointer reuse might make cse's address differ (pa[1] vs a+2 same base though).
E. Store the a[2] value through a variable assigned after the branch: `s32 t2 = *(u16*)(a+2);` inside the arm — cse forwards from the comparison load.
F. Write the comparison as `if (*(u16*)(a+2) < *(u16*)(b+2))` (unsigned compare). Then target has lhu for comparison; the store lhu would be forwarded (same mode!) → worse.

Hmm, what about making the comparison operate on the values *before* they're stored to stack? i.e. use the original s16 values from e: `s16 av = *(u16*)(e+6); s16 bv = ...`. But the values are stored into a and b and then possibly modified by the calls, so the target loads from stack.

Alternative approach: the difference could be resolved by an *additional* real statement that stores to the arrays between the comparison and the arm stores, forcing cse to reload. For example, the target could have had `b[2] = 0x7fff` (the r6==0 case) — no.

Actually! Notice the target's then-arm: it reloads ALL THREE a values. The candidate only fails on a[2]. And in the else-arm, target reloads all three b values; candidate fails on b[2]. So only the *compared* value is forwarded. To block forwarding of exactly that value, we could make the store use a value computed by a different expression that combine can't fold. E.g., `*(s16*)(e+0x7a) = *(u16*)(a+2) & 0xffff;` — the & 0xffff might force a zero-extend and store. Hmm, target does `sh` of lhu (which is zero-extended, store takes low 16). If we write `*(u16*)(a+2)` for the store... it's already u16.

What if the comparison uses `s16` but the store expression is `*(s16*)(a+2)`? Then store is `sh` of sign-extended load — still forwards.

What about making the store read a *different but equal* address spelling, e.g. `a[2]` where `a` is `u8[]` vs `*(u16*)(a+2)` — same.

Hmm, cse forwarding is per-address. Any spelling with the same address forwards.

To stop it without volatile/asm: introduce a *potential* aliasing store between the comparison and the store. E.g., write something to `out[]` or to a stack array between them. But that's exactly what the target doesn't have. Hmm.

Wait — maybe the *original* code structure that generates the target is different: perhaps the comparison is `if (*(s16*)(a+2) < *(s16*)(b+2))` but the arm stores use `a[0], a[2], a[4]` where the *loads* are reloaded because the barrier is a "memory" clobber. The P36 rung B added the barrier to make it match. Our job is to find the original real-C structure that makes it match without the barrier. This is a decompiler-reconstruction problem: the actual original code probably had something like separate statements that the compiler couldn't optimize.

Given the difficulty, let me look at the other items first — they may be easier (the 75820/758FC/759D8 family are near-identical, and 80D38). If I crack the family pattern, that's 3 items. Let me look at those.

Actually let me check their barrier-free scores first. That tells me the size of the problem.
