---
ts: 2026-11-07T00:26:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ssgqnyq9keJcnur5bOUy
---
Score 11 — matches the note in notes.md: "T10 S11 cse-const-addr best 11, 6 tries". So this is the cse-const-addr wall: cse folds/substitutes the constant address (D_80126B78) load.

Interesting: in the target, the address of D_80126B78 is loaded fresh (lui/lw) at each use (target[25:29]: lui v0; lw v0; lhu v1,42(s0); lhu a0,18(v0)) — so the target does NOT keep D_80126B78 in a2 across. My lever-free body loads it once into a2 (lui a2; lw a2) early.

The barrier prevented cse from... hmm, actually the issue: mine holds the D_80126B78 pointer in a2 from early (insn 18-19), target rematerialises it at each use. The barrier made cse not reuse the pointer? No — the barrier doesn't stop the pointer reuse (the pointer is a register value from lw a2,0(a2)).

Hmm, in my w1, `lui a2,0x0; lw a2,0(a2)` at 18-19, then uses a2 at 28 and 33. Target rematerialises at each of the two uses (25-28 and 33-36).

The barrier between the two uses broke the cse equivalence so the second use reloaded... but the target reloads at BOTH uses (the first use too). Let me look at the target more carefully: target[25:29] = lui v0; lw v0; lhu v1,42(s0); lhu a0,18(v0). So the target loads the pointer in the first use too, right there at the site, not early.

So in the target, the D_80126B78 pointer is NOT cached across the first call (func_8012F14C) — it's loaded fresh after the call. Well of course: the call clobbers a-regs. And in my w1, `lui a2; lw a2` at 18-19 is also after the call. Then the target re-loads it again for the second use (33-36) because... the store to obj+0x14 (nonscalar) or the s0 fields? Actually the target's two uses are: (1) in the increment expression `- *(u16*)((u8*)D_80126B78+0x12)`, (2) the store `a0->unk2A = *(u16*)(...)`. In the target, the pointer itself is reloaded for use (2), meaning the target's compiler didn't keep the pointer in a reg across the store to obj+0x14 (nonscalar store invalidates the... no, the pointer load is a scalar symbol load; a nonscalar store would invalidate the MEM for D_80126B78 (scalar) too if cse treats it as possibly aliasing... in cse 2.7.2, a nonscalar store sets cse around, invalidating all non-scalar entries but scalar symbol loads survive? Hmm.

Actually cse's `cse_insn` for a store to a PLUS address with register base: `invalidate_memory` — for nonscalar stores, it clears the whole table (or entries with `!rtx_varies_p`?). In gcc 2.7.2, `invalidate_memory(qty, dest, dest_hash, insn, dest_mode)` clears all memory entries, except with the "scalar" case. Hmm, then the pointer load (MEM (symbol)) would be invalidated too — but that's the value of a symbol's contents, a scalar load of D_80126B78. A nonscalar store might alias D_80126B78 too (pointer stored elsewhere?).

Anyway: the empirical fact is the target reloads the pointer at both sites. My lever-free body caches it. To force reload, real-C moves:
- Make the second use spell the address differently so cse doesn't equate? But cse works on RTL, and `*(u16 *)((u8 *)D_80126B78 + 0x12)` twice is identical RTL. In the target, they're separate loads because the store to obj+0x14 invalidates... but my body has that same store! Yet cse keeps the pointer in a2 across it. Hmm, so cse in my compile considered D_80126B78 (a scalar symbol, in cse terms `(mem:SI (symbol_ref))`... wait, D_80126B78 is `extern s32 *D_80126B78` so the load is `(mem:SI (symbol_ref "D_80126B78"))` — a scalar MEM with a constant address. cse's invalidate_memory with a nonscalar store clears all entries whose address `rtx_varies_p`? Actually the rule in gcc 2.7.2 cse.c invalidate_memory: if the store is not scalar (`!dest || !MEM_P(dest) || !scalar`), it deletes all entries with `!rtx_varies_p (x->exp, 0)`? Let me read the source. tools/reference/gcc-2.7.2/cse.c.

But wait — the target's behavior may be explained by the barrier's placement in the src body: the barrier is between the increment store and the unk2A store, i.e., between the two uses. With the barrier (memory clobber), cse invalidates everything at the asm, so the second use reloads. But the FIRST use also reloads the pointer in the target (mine[18:21] delete lui a2; lw a2 — my early load before insn 20). Hmm, my load at 18-19 is right after the call, and target's first use loads at 25-27 (after `lhu v1,42(s0)`). Both are after the call; the difference is placement relative to the s0 loads and the store.

Hmm wait: mine[18:21] delete lui a2; lw a2; lhu v1,42(s0) — mine loads the pointer BEFORE lhu v1,42(s0). Target does lhu v1,42(s0) first, then loads the pointer. This is a scheduling order thing. Since the pointer load's result isn't needed until the lhu a0,18(v0)... hmm, actually the lw a2 is a load whose result feeds the lhu address — dependency forces the lhu a0,18(a2) after.

Score 11 with 4 diff hunks. The wall note says cse-const-addr best 11. The kinds=barrier means the crack requires removing the barrier; maybe a real-C move can replace the barrier.

What real C would make cse not forward the second use? Ideas:
1. Read the angle through a pointer variable that is reassigned between uses: e.g.
   ```
   u16 *ang = (u16 *)((u8 *)D_80126B78 + 0x12);
   ... use *ang ...
   ang = (u16 *)((u8 *)D_80126B78 + 0x12);  // re-set
   a0->unk2A = *ang;
   ```
   Hmm, cse would still CSE the two identical address computations... but a 2nd set of `ang` kills the equivalence of the reg, forcing a reload of the pointer? Not necessarily the pointer value.

2. Reassign D_80126B78 itself: `D_80126B78 = D_80126B78;`? that's a real 2nd set/store.

3. The known move: "pv = *p; pv &= mask" — no.

4. Dead-reset: `p = 0;` between uses breaks the cse class of the pointer.

Since the target reloads the symbol pointer at each use, the C-level trick is to make the pointer not live: e.g., use a function-call-shaped expression? Or use a different spelling for the second use: `*(u16 *)((u8 *)D_80126B78 + 0x12)` vs `((Unkstruct_800B5CB8*)D_80126B78)->unk12`? The latter would be the same RTL if unk12 is at 0x12... Actually for a different type width it would differ. Hmm.

Wait, more important: what exactly does the barrier fix? With barrier (orig), score 0. Without, score 11 with the pointer cached. So the barrier stops cse from caching the pointer across the barrier. A real-C alternative that stops cse from caching across: a call! Or a store that cse considers aliasing.

Key insight from cse.c: a store to `(mem (plus (reg) (const)))` where the base reg is a pointer variable of unknown type — that's a nonscalar store, which in gcc 2.7.2 cse invalidates memory. Let me actually read cse.c's invalidate_memory.

Let me check what RTL the store to CAST_WIDTH(u16,obj,0x14) produces: obj is s32; CAST_WIDTH(u16, obj, 0x14) = *(u16*)(obj+0x14). Store: (set (mem:HI (plus:SI (reg obj) (const 0x14))) (plus ...)). This is a store to memory with varying address → nonscalar.

In gcc 2.7.2 cse.c, invalidate_memory:
```
static void
invalidate_memory (qty, dest, dest_hash, insn, dest_mode)
...
  /* If we are storing into memory at a varying address, then all memory is invalidated... */
  if (! dest || ! MEM_P (dest) || dest_mode == BLKmode)
    ...
```
Hmm I should read the actual code.

Let me grep cse.c for invalidate_memory.

Actually — an easier approach: use the cse invalidations more cleverly. The target reloads the pointer at both uses. Mine caches across. Since the barrier is at the point between the two uses, the barrier breaks the cache for the second use only. But the first use in mine is also a load (lui a2/lw a2 at 18-19), so both are loads; the difference is that in the target the second use re-loads.

Hmm wait, look at the diff again:
- mine[18:21] = lui a2; lw a2; lhu v1,42(s0) vs target -- -- -- (target has nothing there)
- mine[28:29] = lhu a0,18(a2) vs target[25:29] = lui v0; lw v0; lhu v1,42(s0); lhu a0,18(v0)

So target's sequence: ... lui v0; lw v0; lhu v1,42(s0); lhu a0,18(v0). Mine: lui a2; lw a2; lhu v1,42(s0); ... lhu a0,18(a2).

Then:
- mine[33:34] = lhu v0,18(a2) vs target[33:35] = lui v0; lw v0
- mine[35:36] = nop vs target[36:37] = lhu v0,18(v0)

So target loads the pointer fresh at both uses. Mine loads once (a2) and reuses, so my second use is a bare lhu, leaving a nop in the delay slot.

So: target reloads pointer twice. To force that in C, I need to break the cse cache of the pointer between the uses. The barrier did that (memory clobber invalidates everything).

Real-C options:
(a) Dead-reset the pointer: declare `s32 *gp;` then `gp = D_80126B78; ...use gp...; gp = 0; gp = D_80126B78; ...use gp...`? A store to a local var doesn't invalidate memory in cse... but a 2nd SET of gp kills the cse entry for gp, so the second use would re-load D_80126B78? Actually cse's memory table entry for `(mem (symbol_ref D_80126B78))` persists regardless of gp. Unless the store to gp... no.

Hmm. What actually invalidates `(mem (symbol_ref "D_80126B78"))` in cse? A call (invalidate_memory at calls) or a nonscalar store. The store to obj+0x14 IS a nonscalar store, but it happens BEFORE the first use? Let's see the order in the source:

```
obj = a0->unk20;
obj[0x14] = obj[0x14] + (a0->unk2A - *(u16*)(D_80126B78+0x12));   // use 1 (load pointer)
// barrier
a0->unk2A = *(u16*)(D_80126B78+0x12);   // use 2
```

So the store to obj+0x14 comes before use 1 in source order; then use 1 loads the pointer; then (barrier); use 2.

In mine (no barrier): use 1 loads pointer into a2 at 18-19 (hoisted above lhu v1,42(s0) by sched1); use 2 reuses a2.

In target: use 1 loads pointer (lui v0; lw v0) at the use site; use 2 loads pointer again.

So the difference is entirely about the barrier between uses. Real C must break cse between use1 and use2 in a way that forces re-materialization of the symbol pointer.

The classic lever-free trick from the catalog: a store that cse treats as potentially aliasing D_80126B78. What if the store to a0->unk2A (the second use's destination) were... no, it's after.

What about a real second set of a pointer variable with a value that varies? Hmm.

What about the "struct member" trick in reverse: make use 2 read via a different expression that isn't cse-equal to use 1. cse compares the RTL of the MEM expression. `*(u16 *)((u8 *)D_80126B78 + 0x12)` twice = identical. If I make use 2 read `((Unkstruct_800B5CB8 *)D_80126B78)->unk12` and unk12 is u16 at 0x12 — identical RTL (plus const). Unless the offset is not constant-folded: e.g. use an index variable: `((u16*)((u8*)D_80126B78 + 0x12))[0]` — same.

Better: the pointer itself: use 1 = `(s32)D_80126B78 + 0x34` for the call... no that's earlier.

Hmm, another idea: make use 2's pointer load *not* CSE-able because use 1's expression has a different type/size. cse entries key on the full expression including mode. `*(u16 *)((u8 *)D_80126B78 + 0x12)` — the MEM is HImode either way.

What if I add a dead store through a `volatile`? Not allowed (that's a lever? volatile is a real C qualifier; the brief says no pin/launder/barrier/keepalive/asm; volatile isn't listed as a lever kind. But "no new lever of any kind" — a volatile would be a barrier-ish lever. Better avoid).

The catalog mentions C0414 dead-reset cse-breaker and C0535 do-while(0). Also "struct-member read forces cse reload" (func_80175820: the nonscalar ptr store invalidates it, cse re-loads).

Wait — in the target, use 1 loads the pointer at 25-27, i.e., AFTER `lhu v1,42(s0)`. Hmm, that's just sched1 order.

Let me consider: maybe the real trick is that the *whole expression* `*(u16 *)((u8 *)D_80126B78 + 0x12)` is loaded fresh twice because in the target the compiler sees two separate *statements* with a memory-clobbering... no, the target is the ground truth compiled from some C we're trying to reconstruct; the barrier in our src is a fake added because plain C merged them.

To break cse with real C: a dead store to a global (e.g. `D_80126B78 = D_80126B78;`)? That is a store to a scalar symbol; cse's invalidate for a scalar store only invalidates entries that alias (same address + same mode) — i.e., the D_80126B78 memory entry itself! That's exactly what we want: a store to D_80126B78 invalidates the cached `(mem (symbol_ref D_80126B78))`. But it would emit an actual store instruction (extra insn) — unless it's dead and flow deletes it. A dead store to a global can't be deleted (extern).

Hmm, but a store to a local temp: `p = 0;` where p is a local pointer — cse's invalidate_memory for a scalar store to a stack slot: it invalidates entries with `x->exp` being a MEM at the same address or entries whose address varies. The D_80126B78 entry is at a constant address, so it's not invalidated. But — importantly — the cse *equivalence* for the loaded pointer value: after `p = 0;`, if the previous value in p was D_80126B78's content... cse table entry `(mem (symbol_ref D_80126B78))` maps to reg a2. A store to a stack slot `p` doesn't invalidate it.

Hmm. What if the dead reset is on the pointer variable holding the loaded value: `gp = D_80126B78;` ... `gp = 0;` ... `gp = D_80126B78;`. The 2nd set of gp: cse will process `gp = 0` (set), then `gp = D_80126B78` — cse checks its memory table for `(mem (symbol_ref D_80126B78))`; if it's still valid, it replaces the load with a register copy of a2 — still cached. Unless the cse table entry was invalidated by... the store to gp? No.

OK, so what invalidates cse's memory entries in gcc 2.7.2? Let me actually read cse.c. Let me grep for invalidate_memory.

Also — importantly — maybe the barrier isn't about cse of the pointer at all; maybe with the barrier removed, sched1 hoists the load early (18-19) and reuses it; the *barrier* forced a reload. But we need the same effect with real C.

Alternative real-C move: the do-while(0) trick (C0535) splits the EBB so sched1 doesn't hoist the pointer load across. If the load isn't hoisted, then... hmm, but the caching is cse, not sched.

Hmm wait, actually: does cse cache the pointer across a call? The call func_8012F14C is before. After the call, cse's table is cleared of memory entries (calls invalidate memory). So the pointer load in use 1 is fresh. Then cse records `(mem (symbol_ref D_80126B78))` → a2. Then the store to obj+0x14 — a nonscalar store. If that store does NOT invalidate (because cse treats stores to `(plus (reg) (const))`... hmm, it's a MEM with a varying address, so nonscalar → invalidates everything? But then use 2 would reload too.

Wait, order matters: the store to obj+0x14 happens BEFORE use 1. So after the store, the table is cleared; then use 1 loads the pointer (fresh, cse records it); then use 2 — no store in between except the store to obj+0x14 itself (which precedes use 1). Hmm, but the *store* in the statement `obj[0x14] = obj[0x14] + ...` is sequenced: load obj+0x14, load pointer, load pointer[0x12], load a0->unk2A, subtract, add, store to obj+0x14. So the store happens AFTER use 1's load. That's the key: the store to obj+0x14 (nonscalar) comes after use1 and before use2, invalidating the cse memory table → use 2 should reload!

But in my compiled output, use 2 uses a2 (cached). So cse did NOT invalidate at that store. Why? Maybe because the store's address is `(plus (reg) (const))` and gcc 2.7.2's invalidate_memory only invalidates entries whose address "varies" when the store is at a varying address... let me read.

Let me look at cse.c invalidate_memory.
