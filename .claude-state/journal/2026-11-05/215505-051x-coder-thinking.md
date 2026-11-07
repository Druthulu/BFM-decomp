---
ts: 2026-11-06T04:55:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n3LLFeJNu3TaLqH3R077
---
The store into memory is recorded in the table later via `sets[i].dest_hash` and `sets[i].src_elt`, and cse will replace a later load of the same MEM with the source register if it finds the dest in the table. To prevent, the classic move is to make the address hash differ between store and load, e.g., use a *different base pointer variable* that cse can't canonicalize to the same expression, or reorder so the load's address is computed differently.

In the source, the store is `*p = v0;` with p = &D_80127524, and the load is `*p` again (same expression!). If we write the call as `func_80138C30(D_80127524);` (direct symbol access), cse may still hash to the same (mem (symbol_ref)) after fold_rtx, since p is known to be &D_80127524. But maybe fold_rtx doesn't substitute p because p is a register... Actually `p = &D_80127524;` then `*p` — cse would have a REG_EQUAL for p = &D_80127524 and fold the address. Hmm.

But note target's call arg is loaded via a0 = &D_80127524 (a0 still holds the address). Target's store also via a0. So both use the same address; the only thing preventing the forward is the barrier.

Alternative: use a volatile-free different *type* for the load so the MEM modes differ. The store is `*p = v0` (s32). The load for the call arg is also s32. If the call arg were loaded as e.g. `*(u32 *)p` — same mode SImode. If we load it as a different mode (e.g., u16), that changes semantics.

Hmm. Another angle: kill the cse equivalence by reassigning v0 after the store. Source:
```
v0 = D_80127528;
D_80127528 = 0;
*p = v0;
if (v0 != 0) {
    *(s16 *)(D_80127524 + 0x1A) = 1;
    func_80138C30(*p);
}
```
After `*p = v0`, v0 is still used in `if (v0 != 0)` — but the if test is evaluated... source order has the if after the store; the test uses v0. If we reorder: `if (v0 != 0)` first? It already is after the store. The test `v0 != 0` happens after the store, and cse can forward *p -> v0 for the call arg.

If we reassign v0 inside the if body before the call, cse's equivalence of *p with v0 might be killed if v0 is set to something else. But reassigning v0 would add a real insn unless it's dead. E.g.:

```
if (v0 != 0) {
    *(s16 *)(D_80127524 + 0x1A) = 1;
    v0 = D_80127524;      // reload; then call func_80138C30(v0)
    func_80138C30(v0);
}
```
This is a real C move: explicitly load *p into v0 and pass it. But would it emit the same as target? Target: `lw a0,0(a0)` (load *p into a0) then jal. If we write `v0 = D_80127524; func_80138C30(v0);` the reload would be emitted (not cse'd, because the explicit assignment... wait, cse could still replace the load with the stored value since it tracks memory! The assignment `v0 = D_80127524` is a load; cse will forward it to the stored value register. Unless the register holding the stored value was killed.

Hmm. cse store-forwarding replaces the load with the source of the store. So writing the load explicitly doesn't help.

What kills the cse memory equivalence? `note_mem_written` invalidates the table for overlapping stores. So if we insert a store to a possibly-aliasing location between the store and the load, cse invalidates the D_80127524 entry. The moves list has examples: "launder: store between tmp9 set and lvl copy blocks cse.c:7440 swap". So an intermediate *store* to an aliasing/unknown location invalidates the memory entry.

In target, the intermediate store is `*(s16 *)(D_80127524 + 0x1A) = 1;` — a store to D_80127524+0x1A. Does that invalidate the s32 store to D_80127524 (offset 0)? They don't overlap (offset 0..3 vs 26..27), so cse knows they don't alias and keeps the forwarding. In target, the reload happens after this sh — and it's a reload (not forwarded). So the barrier is what stopped it.

To invalidate in real C: make the intermediate store's address *varying* or aliasing so cse must invalidate. E.g., store through a pointer with unknown offset. But the target instruction is `sh v0,26(v1)` — fixed offset 26.

Hmm, what if the store `*p = v0` and the load `*p` differ because between them `p` is reassigned? Target's p is in a0 and the reload uses a0. If we reassign a *different pointer variable* to the same address and use it for the load, cse might not equate the MEM because the address expression is a different pseudo... but cse hashes the folded address; if it knows both equal &D_80127524, it folds.

Unless the pointer is *loaded from memory* rather than a constant. E.g., load p from somewhere: `s32 **pp = &D_80127524`? no.

Let's look at the actual wall tag "cse-store-forward — cse1 forwards a store into a reload and combine drops the dead store (G18x)". This is listed in walls.txt as a known wall. But we must try ≥30 tries for a WALL. Let's try moves that historically cracked cse forwards.

From moves.md: 
- func_8018C2D8 MATCH — reuse m for next ptr and m1 for col: reassignment kills the cse sym class.
- func_801902EC MATCH — per-segment q reassignment kills cse addr class.
- func_80131CF4 etc.

Here the value is stored and reloaded. What about making the store value come from a *different* register than the one cse records, by copying: 
```
s32 v0 = D_80127528;
s32 t = v0;         // copy
D_80127528 = 0;
*p = t;             // store t
if (v0 != 0) { ... call(*p) }
```
cse records (mem) -> t. The reload *p becomes t. But target wants a reload. Unless t is dead after the store... then cse still forwards but combine might delete the copy? Actually if t is a copy of v0 and only used in the store, cse/combine would coalesce t into v0. Hmm.

What if the stored value is computed such that cse's src_elt is not a simple register — e.g., store an expression with memory? No.

What if we make the store *volatile*? That's a lever (not allowed).

What if the reload is not of *p but of a *field*: target loads the full word `*p` for the call. If we write the call arg as `*(s32 *)p` — same.

What if we use the value via a struct member: `((Unkstruct *)p)->unk0`? Same MEM.

Hmm. What about making the *store* target a different but equivalent expression so that cse's dest_hash differs from the load's hash? cse's hash of a MEM is the address rtx hash. If the store uses `*p` (address = p) and the load uses `*(s32 *)((u8 *)p)` (address = p) — same. If the store uses `*(s32 *)(D_80127524 + 0)` and the load `*p`... cse folds both to the same symbolic address.

Unless the pointer p's value isn't a known constant. E.g., if p is assigned from `&D_80127524` but then cse loses track because p is used in a context where... no.

Wait, actually in target the reload exists but cse did NOT forward because the barrier invalidated the table (asm memory clobber = CLOBBER of MEM). In real C, an intervening function call also clobbers memory. But the call is the very thing we're setting up.

What about an intervening store to an unknown/aliasing address that is *real* in the target? The target has the `sh v0,26(v1)` store between. If we could make that store's address unknown to cse (e.g., via a pointer that cse can't resolve), cse would invalidate the *p entry. But the target code has a fixed offset 26 from the D_80127524 pointer. If we write it as `*(s16 *)((u8 *)p + 0x1A) = 1;` where p is the same register... cse still knows the offset and non-overlap.

What if we write it as `*((s16 *)p + 0xD) = 1;`? Same.

Hmm what if the store is through a `s16 *` variable derived from a *different* base that cse can't prove? For instance, `s16 *q = (s16 *)(D_80127524 + 0x1A);` — same.

Let me look at cse's note_mem_written: for a store to a MEM with a fixed offset, it invalidates only aliasing entries. Since the s32 store at offset 0 and sh at offset 26 don't alias, the entry survives. To force invalidation, the intermediate store must be to an address that may alias offset 0 — e.g., offset 0 with a different mode! A store to D_80127524 as a *byte* or *halfword* at offset 0 would alias the word store.

But target's intermediate store is at +0x1A. We can't change that.

Wait — but is the reload actually prevented by the barrier, or by something else? Let me test: remove the barrier but keep everything else and see if the residual is only the cse forward. The a1 diff showed many register differences; let me get the actual cse behavior. Mine at 224c: `lui v1,D_80127524; lw v1,0(v1)` — that's a reload of D_80127524 for the store base (the sh target), then `sh v0,26(v1)` — wait that's the sh store using a reloaded pointer. And the call arg a0 = the value (no reload). So mine reloaded D_80127524 to get the address for the sh (because the a0 pointer got overwritten by the value?).

In target: a0 = &D_80127524 persists; sh uses v1 = reloaded *p? No: target 224c lui v1; 2250 lw v1,0(v1) → v1 = *p (the value stored, i.e., D_80127528's old value); 2258 sh v0,26(v1) → store 1 at (value+26)?? Wait that would be wrong! Let me re-read.

Target:
```
221c lui a0, D_80127524
2220 addiu a0
2224 lw v0,0(a0)          ; v0 = *p
222c bne v0,s0            ; if (*p != s0) goto 2268
2234 lui v0, D_80127528
2238 lw v0,0(v0)          ; v0 = D_80127528
223c lui at, D_80127528
2240 sw zero,0(at)        ; D_80127528 = 0
2244 beqz v0, 2268
2248 sw v0,0(a0)          ; *p = v0
224c lui v1, D_80127524
2250 lw v1,0(v1)          ; v1 = *p  (reload)
2254 li v0,1
2258 sh v0,26(v1)         ; *(s16*)(*p + 26) = 1
225c lw a0,0(a0)          ; a0 = *p (reload)
2260 jal func_80138C30
2264 nop
```
Ah I misread the source. The C is `*(s16 *)(D_80127524 + 0x1A) = 1;` where D_80127524 is a *variable* holding a pointer? Let's check: `extern s32 D_80127524;` and `p = &D_80127524;` so D_80127524 is an s32 at a fixed address. `*(s16 *)(D_80127524 + 0x1A)` — D_80127524's *value* + 0x1A. So it reloads D_80127524 (the pointer value) and stores at +26. And `*p` = D_80127524 (value). So D_80127524 is a pointer variable stored in memory.

So the target: after `*p = v0` (D_80127524 = v0), it reloads D_80127524 twice: once for the sh base (v1), once for the call arg (a0). Both reloads. cse would forward both from the store value v0.

So the store is `*p = v0`, and then two loads of *p: one used as a pointer (for the sh), one as the call arg. Without the barrier, cse forwards both: sh uses v0+0x1A? No wait, mine: `lw v1,0(v1)` reloads for the sh base, and the call arg uses a0 = value (forwarded). Let me re-read mine:

Mine:
```
2234 lui a0, D_80127528
2238 lw a0,0(a0)     ; a0 = D_80127528 value
223c lui at,D_80127528
2240 sw zero,0(at)
2244 beqz a0,2260
2248 sw a0,0(v1)     ; *p = a0 (v1 = &D_80127524)
224c lui v1,D_80127524
2250 lw v1,0(v1)     ; v1 = *p (reload)
2254 li v0,1
2258 jal func_80138C30
225c sh v0,26(v1)    ; delay slot: store 1 at *p+26
```
So mine also reloads *p for the sh base (v1), and the call arg is a0 = the stored value (forwarded, no reload). Target reloads for both.

So the difference: one reload (call arg) got cse-forwarded in mine. The barrier prevented that.

So: how to prevent cse from forwarding the store into the call-arg load while keeping the sh's reload? The sh's load is *not* forwarded in either version — why? Because the sh base load is `*p` used as an address; cse's store-forwarding might not apply to a load used in an address? Or maybe it's a different MEM (s32 load) but the value... Hmm, cse forwards loads of memory from a previous store regardless of use. Why did the sh's load survive in mine? Maybe because between the store and that load, there's the `if (v0 != 0)` branch — cse works per extended basic block; a branch ends the EBB? cse1 processes each basic block; store-forwarding across the branch wouldn't happen if the branch splits the block. Wait the code:

```
*p = v0;
if (v0 != 0) {
   sh ...(*p + 0x1A) = 1;
   call(*p);
}
```
The store is before the branch; the loads are inside the if block (a different basic block). cse1 runs on EBBs; a conditional jump splits. So cse can't forward across the branch anyway!

Then why is the call arg forwarded in mine but not target? Hmm. Maybe it's not cse but local-alloc/global-alloc reusing the register. Or maybe the load *is* forwarded by cse within the if block? There's no store inside the if block before the loads, so no forwarding.

Wait, actually maybe the store and the loads are in the same basic block: `if (v0 != 0) { ... }` — the branch is on v0. The store `*p = v0` is before the branch. The loads are after the branch (inside). Different blocks. Unless gcc's cse1 processes EBBs and the branch... no.

Hmm, so what does the barrier do then? Let me look again at the diff: mine lacks `lw a0,0(a0)` before the jal, and the target has `sh v0,26(v1)` before the reload while mine puts the sh in the delay slot after the jal. The register differences: v1->a0 x5, a0->v0 x4.

Maybe the real effect of the barrier is on *scheduling* (sched1/sched2) rather than cse. The asm memory barrier also prevents sched reordering. Without it, the scheduler moved the `sh` into the call delay slot and reused a0 for the call arg (a0 already held the value). With it, the sh must stay before the load.

Actually the call arg: `func_80138C30(*p)` — the load of *p. In mine, is there a load at all? a0 = value from the store. Maybe combine/global-alloc coalesced the reload with the stored register. Since the value is in a0 (the same register that held D_80127528's value), and the call needs it in a0, the reload was CSE'd/coalesced to the existing a0.

So it's a register-reuse artifact: the stored value is in a0, the call arg wants a0, so the load is optimized to a0. In target, the stored value is in v0 and a0 holds the pointer &D_80127524, so the call arg reload is needed.

So the difference is *which register holds the stored value*. In target, v0; in mine, a0. That's global-alloc. With the barrier, the allocation differs.

Hmm, so maybe the crack is to change the code so the stored value lands in v0 and the pointer in a0. The barrier achieves it by... limiting the live range/scheduling.

Let's try real-C moves that change allocation:
- Reorder `v0 = D_80127528; D_80127528 = 0; *p = v0;` — maybe `*p = v0` then `D_80127528 = 0`? Semantics: target stores 0 to D_80127528 before the check `if (v0 != 0)`. If we reorder the store of 0 after `*p = v0`, semantics unchanged (different locations). That could change scheduling/allocation. Let's try.
- Use a different temp name for the value.
- Store `*p = D_80127528;` before zeroing: `v0 = D_80127528; D_80127528 = 0; *p = v0;` vs `*p = D_80127528; D_80127528 = 0;` — the latter's store source is a load from D_80127528; target loads it into v0 first then stores v0. Writing `*p = D_80127528;` might produce a direct load/store pair, likely different.

Let's test a batch on includer 0 only (fast), then verify on all 141 for the winner.

Batch h:
h1: swap `D_80127528 = 0;` and `*p = v0;`
h2: `*p = D_80127528; D_80127528 = 0;` and `if (v0 != 0)` where v0 loaded before? Need v0 for the if. Write:
```
v0 = D_80127528;
*p = v0;
D_80127528 = 0;
if (v0 != 0) {...}
```
h3: v0 declared as a separate variable? it's s32 v0 already.
h4: use `p` for the sh: `*(s16 *)((s32)p + 0x1A) = 1;`? no, D_80127524's value.
h5: write the call as `func_80138C30(D_80127524);` instead of `*p`.

Also maybe restructure to force the reload: `((void (*)(s32))func_80138C30)(D_80127524);` (cast the call arg type). Hmm.

Let me test h1..h5.
