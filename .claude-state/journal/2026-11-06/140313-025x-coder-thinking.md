---
ts: 2026-11-06T21:03:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_j3cAZxZ0JaXqNhWgSZs9
---
So find_free_reg picks the first free reg in reg_alloc_order (or 0..n). For MIPS, REG_ALLOC_ORDER likely defined in mips.h. Let's check mips.h REG_ALLOC_ORDER.

If reg_alloc_order starts with 0,1,2,3... then a0 (reg 4) comes before a1 (reg 5). So the first allocated qty gets a0. Target gives off a1 and e a0 → meaning e was allocated FIRST (higher priority) and got a0, off second got a1.

So in target, e has higher local-alloc priority than off. In mine, off has higher priority than e.

Priority = floor_log2(n_refs)*n_refs*size/live_length. Let me compute. In target: e wins → e's pri > off's.

Hmm but in source both variants produce same RTL order? Let me check n_refs. In RTL, off is defined by a SET and used twice. e defined and used once (the two occurrences in the || condition are the same CSE'd value? Actually `*(s16*)((u8*)e + off + 2)` appears twice textually, but cse combines them into one load. So e used once (in addu) after cse).

But wait — local-alloc runs after cse? Order of passes: cse (cse1), then loop, then cse2, then flow, combine, then local-alloc? Let me recall GCC 2.7 pass order: ... `cse`, `loop`, `cse` (2nd), `flow`, `combine`, `regscan`, `local-alloc`, `global-alloc`, ... Yes local-alloc after combine.

So by local-alloc, e and off: off has 2 uses (addu at; addu v0), e has 1 use. So off pri > e pri → off allocated first → a0. That matches MINE, not target.

But target has e first. So in the target, e must have had more refs — the launder `__asm__("" : "=r"(e) : "0"(e))` gives e an extra def and ties it, raising n_refs. That's exactly why the launder was needed! The launder is a 2nd set of e.

So to crack it lever-free, we need a real-C 2nd set of e (C0414-style), or otherwise raise e's refs. Since e is `(s16*)D_801E8F78` — a constant pointer. A "real 2nd set" would be assigning e twice. E.g.:

```
e = (s16 *)D_801E8F78;
...
e = (s16 *)D_801E8F78;  // 2nd set
```
But combine/cse might merge the two identical sets. If they're adjacent or no use between, cse removes the dead first set.

Alternatively, make e's value depend on something so the 2nd set is not redundant: e.g. `e = (s16 *)D_801E8F78;` then later `e = (s16 *)((u8 *)D_801E8F78);` identical → merged.

C0414 dead-reset: `e = 0;` after its last use — this kills cse's class so later uses rematerialize. But e's last use is inside the block; a dead reset after the call? But e is dead at the call already.

Hmm. Let me think differently: the barrier removal + launder. The barrier `__asm__ __volatile__("")` is a memory barrier; its removal might change cse of the loads. But score 4 only shows the a0/a1 swap, so barrier removal is fine (no other diff). Good.

So only the launder's effect (2nd set of e → higher refs → a0) is needed.

Real-C ways to give e an extra reference/set:
1. Use e twice in a way that's real and value-preserving: e.g. compute `lim` through e AND use e in the condition. But that changes the address computation (would use e as base instead of D_801E8F78). Actually that might be EXACTLY what target does? Let's check: target lim load address is `lui at, D_801E8F78; addu at,at,a1` where a1=off. It doesn't use a0 (e). So lim is not loaded via e. So no.

2. Add a 2nd assignment to e that's genuinely live: e.g. `e = (s16 *)D_801E8F78;` then reassign `e = (s16 *)((u8 *)e);` — identity cast, might be optimized.

3. Make e assigned from a temp: `e = (s16 *)D_801E8F78;` and before that `p = D_801E8F78;`? no.

4. Use a conditional: `if (t < lim) ...` — e used in condition. What if we make e also used in the `if (idx >= 0)` arm? E.g. `p = D_801E8F98[idx];` no.

Let me reconsider: maybe increase n_refs of e by using it in the condition twice without cse merging. The two textual occurrences: `*(s16 *)((u8 *)e + off + 2)`. If we write it as two different expressions that cse can't merge, e gets 2 uses. But cse would merge same address. Could use `e[off/2 + 1]`? off is s32, `(u8*)e + off + 2` = e + (off+2). Since off = idx*4, off+2 is not a multiple of 2? off is multiple of 4, +2 → half-word aligned. `e[(off+2)/2]` = e[idx*2+1]. That's `e[idx*2+1]`! Because off/2 = idx*2. So `*(s16*)((u8*)e+off+2)` == `e[idx*2+1]`.

So write: `if (e[idx*2+1] == 0 || (func_80029178(e[idx*2+1]) & 0xFF) == 0)`. cse would still merge the two e[idx*2+1] loads? They are identical loads (same address), and there's no intervening store, so cse merges them. Hmm, but the call is in between? No — `A || B` where A = `e[idx*2+1]==0`, B = `func(...e[idx*2+1]...)`. The second load is before the call in the same expression evaluation, so cse merges.

Original already has them identical and cse merges into one load (target shows lh a0,2(v0) once). So e's use count is 1 from the condition.

So how did the launder raise e's refs? It adds `__asm__("" : "=r"(e) : "0"(e))` which is an insn with e as both input and output → +1 use, +1 set → n_refs maybe 2 or 3. That raised e above off.

To emulate with real C: make e's definition have 2 refs. E.g. a real 2nd set that's not redundant. What about:

```
e = (s16 *)D_801E8F78;
...
e = (s16 *)((u8 *)e + off - off);  // value-preserving but not obviously identity? combine will simplify
```
Identity launder — prohibited and also won't survive optimization.

What about using a struct/union? Hmm.

Alternative: lower off's priority by reducing its refs or increasing its live length. off has 2 uses. If we can make off's live length longer (it spans the call?), priority drops. But off dies before the call.

Wait, actually: what if we use `off` for the second occurrence differently so cse doesn't share, making off have 2 uses but e 2 uses as well? Hmm.

Let me reconsider the target: maybe in target, off is NOT idx*4 but something else. Let me re-examine: target at 80 `sll a1,s0,0x2`. s0 = idx (loaded lbu s0 at 78). So a1 = idx*4 = off. Yes.

Alternatively, maybe in target the pseudo for `D_801E8F78` constant is used in BOTH the lim address and e (2 uses), while off is idx*4 used twice. Hmm! In the target, the constant D_801E8F78 appears as `lui at` (for lim address) and `lui a0/addiu` (for e). These are two separate materializations. In RTL, `D_801E8F78` as an address is probably a SYMBOL_REF used in two places; each use may be a separate pseudo or shared. Hmm.

Actually, the crucial insight: target's `e` (a0) is the bare address `D_801E8F78`, and the lim address uses `at` = D_801E8F78 + off. So the constant D_801E8F78 has 2 uses. In target, a0 gets the bare constant (e), at gets constant+off. In mine, a1 gets bare constant, a0 gets off.

Hmm so it's still e vs off.

Let me try: increase e's refs by making `lim` read through a separate pointer that is e? `lim = e[idx*2]` — that uses e as base for lim! But target's lim address is `at` = D_801E8F78 + off, which is exactly e + off (since e = D_801E8F78). So `lim = e[idx*2]` would compute e + idx*2... = e + off/2. Not the same offset: D_801E8F78[idx][0] is at byte offset idx*4 = off. e[idx*2] is at byte offset idx*4 = off! Since e is s16*, e[idx*2] = *(s16*)((u8*)e + idx*2*2) = *(s16*)((u8*)e + idx*4) = D_801E8F78[idx][0]. Yes! So `lim = e[idx*2]` is equivalent.

Then the lim address = e + off. Target computes `at = D_801E8F78 + off` (i.e., using the symbol + off, not e). If e is in a0 and off in a1, then `e + off` would be addu v0,a0,a1 → same as the condition's addu! Actually cse might share the address: `e[idx*2]` and `e[idx*2+1]` share base+off. Then lim load and the condition load use the same address computation `addu v0,a0,a1`. But target has TWO addu: `addu at,at,a1` (at = sym + off, using at = lui sym) and `addu v0,a0,a1` (a0 = e = sym). So target does NOT share: lim address uses `at` (lui at, D_801E8F78; addu at,at,a1) and the condition uses `addu v0,a0,a1` where a0 is the addiu'd e.

Interesting: target materializes the symbol twice: `lui at` (plain lui, no addiu) for lim, and `lui a0; addiu a0` for e. So the lim address is sym+off via at (lui+addu), and e is a full addiu address. This is because in RTL, the lim load uses SYMBOL_REF+off directly (a HIGH/LO sum), while e is a separate pseudo holding the full address (needed because it's used as a pointer value in arithmetic `(u8*)e + off`).

So if I write `lim = e[idx*2]`, the lim load would use e's pseudo (a0) + off → addu v0,a0,a1, reusing the same address as the condition → one addu instead of two. That would change instruction count. So no.

OK so back to: need e to have higher local-alloc priority than off. Since priority = floor_log2(refs)*refs*size/live_length, and off has 2 uses + def, e has 1 use + def. 

What if we make e have 2 uses by using it in a way that produces the SAME code? For example, use e in the condition twice but via a temporary that cse doesn't merge... but cse merges.

What about giving e a 2nd set that survives: 
```
e = (s16 *)D_801E8F78;
...
if (...) {
   ...
}
```
Hmm.

C0414 dead-reset idea: after using e in the condition, set `e = 0;`? But that would be dead and flow removes it. Unless it's after a call so it's live-ish. Actually C0414: "dead reset mp = 0; after the call empties cse's class so the store base rematerialises". The dead reset is a real set that flow may keep if it's not obviously dead? Actually flow does dead-code elimination. Hmm, but these dead resets work in practice per the log, because flow only removes sets of pseudos that are dead, and a set of a pseudo that has no later use IS removed... unless it's a MEM or volatile. Hmm, but the moves log shows many `x = 0;` dead resets working. Maybe flow keeps them when the pseudo is used later? No.

Wait, C0414 "dead reset": the reset is *not* dead in the sense that the pseudo is used later — it's used later at a different point, and the reset forces a re-materialization. Let me re-read: "C0414 dead reset mp = 0; after the func_800233CC(mp,0x80) call empties cse's &D_801D0FC0 class, so the store base rematerialises". So mp is used BEFORE and AFTER the reset, and setting mp=0 in between forces the later use to rematerialize the address. It's "dead" in that the value 0 is never used, but the set itself is live because mp is used later.

In our case, e is used only in the condition; there's no later use. So a dead reset after the condition won't help.

We need to raise e's n_refs. Add an extra use of e that doesn't change codegen... but any use changes refs.

Hmm, what about reordering so that off's live_length is longer (reducing its priority)? Priority divides by live_length. If off's live range is extended, its priority drops below e's. E.g., define off much earlier (before the call to func_8017EF64 or at the top), so live_length is large. But then the sll would be scheduled/placed earlier — might change code. Actually off is computed as idx*4 where idx = D_801E8F50[...] which requires the call result? No, idx is loaded after t=func_80029504(). idx loaded at 78 (lbu s0), off computed at 80. Could we define off right after idx? That's the same place.

What if we define off at the top from param_2? No, idx depends on the load.

Alternatively reduce off's refs from 2 to 1: If the lim address uses the symbol+off, and the condition uses e+off, both use off. To use off once... no.

Alternatively: increase e's `size`? e is a pointer (4 bytes) and off s32 (4 bytes). Same.

Hmm, what about making e a `s32` instead of `s16*`? Then size same. But maybe the mode/class differs? No.

Let me reconsider: maybe I mis-identified which pseudo is which. Let me get the actual lreg dump for my candidate and the target... target RTL unavailable. But I can dump mine and see qty priorities.

Let me create the candidate TU. --keep prints the scratch TU/object path. Let me run --try with --keep.
