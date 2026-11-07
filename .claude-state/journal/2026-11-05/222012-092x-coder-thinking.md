---
ts: 2026-11-06T05:20:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tcULcW2jqj5nhBdJkqH5
---
The target's sequence:
```
lhu v1,6(a2)      ; t = arg0[3] (u16)
nop
sh v1,24(sp)      ; b[0] = t
lhu v0,10(a2)     ; 
subu v1,v1,a0     ; t = t - u88
addiu v0,v0,-16
sh v0,26(sp)      ; b[1] = ...
lhu v0,14(a2)
subu a0,a0,v1     ; u88 = u88 - t
sh v1,24(sp)      ; b[0] = t
sh a0,24(sp)      ; b[0] = u88
sh v0,28(sp)      ; b[2] = t2
subu v0,v0,a1     ; t2 = t2 - u8C
subu a1,a1,v0     ; u8C = u8C - t2
sh v0,28(sp)      ; b[2] = t2
sh a1,28(sp)      ; b[2] = u8C
```

So the target keeps the intermediate stores: `sh v1,24` (b[0]=t) BEFORE `subu a0,a0,v1`, then again `sh v1,24` after. Wait, there are two `sh v1,24(sp)`! One at the start (b[0]=t) and one after subu. So the source `b[0] = t;` appears twice? Looking at the source:

```
t = *(u16 *)(arg0 + 6);
b[0] = t;             <- first store
b[1] = *(u16 *)(arg0 + 0xA) - 0x10;
t = t - u88;
t2 = *(u16 *)(arg0 + 0xE);
u88 = u88 - t;
b[0] = t;             <- second store
BARRIER
b[0] = u88;           <- third store
b[2] = t2;            <- fourth
BARRIER
t2 = t2 - u8C;
u8C = u8C - t2;
b[2] = t2;            <- fifth
BARRIER
b[2] = u8C;           <- sixth
```

Yes! The source itself has b[0]=t twice and b[2]=t2 twice. So the target's stores are all from the source. Without barriers, cse removes the duplicate/dead stores.

The barriers are between: b[0]=t and b[0]=u88 (barrier 1); b[2]=t2 and the next group (barrier 2); b[2]=t2 and b[2]=u8C (barrier 3).

Hmm, actually barrier 1 is after `b[0] = t;` (the second one) and before `b[0] = u88;`. Barrier 2 after `b[2] = t2;` before the t2/u8C computation. Barrier 3 after `b[2] = t2;` before `b[2] = u8C;`.

So the barriers separate stores to the same location (b[0], b[2]) so cse can't delete the earlier ones.

Real-C ways to keep a dead store:
1. Make the store's address opaque (can't prove same location). E.g., store via a pointer whose value cse can't track. But the code must be `sh X,24(sp)` — the address is sp+24, a fixed offset from the frame pointer. Any C spelling of `b[0]` gives that.
2. Make the stored value different... no.
3. Use a `volatile` store (lever).
4. Use a call between them (adds insns).

Hmm. But wait — maybe cse doesn't delete the stores; maybe it's `flow`/`dce`? In GCC 2.7.2, dead store elimination happens in cse (`cse_insn`: if a store is to a location that is later overwritten before use, it's deleted). Also `flow` (dead code elimination) can remove stores to dead stack slots? Hmm.

Let me check which pass removes them: the v1 has 42 insns, the target 45. Three missing stores. Let me look at the cse dump.

Alternative idea: make the *intermediate* stores not dead by making the subsequent stores go to a *different alias class* so cse can't prove they overwrite the same location. E.g., write the earlier store through a struct member (MEM_IN_STRUCT_P) and the later through a plain scalar. Per §425/§469, struct vs scalar alias behavior differs! If cse can't prove the two stores are to the same location, it keeps both.

The generated code must be `sh v1,24(sp)` and `sh a0,24(sp)` — both halfword stores to the same address. If one is a struct-member store and the other a scalar store, the code is identical (sh) but cse's MEM flags differ → no dead-store elimination.

That's the same class of move as item 2 (alias class). Let me try it.

How to write a struct-member store to b[0]? b is a local `s16 b[3]`. A struct-member access would need a cast of &b[0]... e.g., `((struct S2 *)b)->v = t;`. That's an address cast — identity address spelling again. Hmm.

But maybe I can declare `b` as a struct instead of an array! E.g.:
```
struct S3 { s16 x, y, z; } b;
...
b.x = t;   // MEM_IN_STRUCT
b.x = u88;
```
The target's stack layout: a at sp+16, b at sp+24 (x at 24, y at 26, z at 28). The source uses `a[3]` and `b[3]` arrays passed to functions as `s16 *`. If I change b to a struct, the calls `func_8014E284(arg0, a, b)` would need casts `(s16 *)&b`. The declarations are inside the body? `s16 a[3]; s16 b[3];` — yes, local. I can change them to structs (decl changes inside the body are allowed).

But the function calls pass `a` and `b` as `s16 *`. With structs, I'd write `(s16 *)&a`. That might change codegen (address computation).

Hmm, but the target uses `addiu a1,sp,16` and `addiu a2,sp,24` — the addresses of a and b. With structs, the same.

Let me try: declare
```
struct P3 { s16 x, y, z; } a, b;
```
and use a.x etc. The stores to b.x are MEM_IN_STRUCT. The stores to b.z are MEM_IN_STRUCT. Then cse sees both as in-struct stores to the same address → still deletes. Hmm, both would be in-struct, so no difference.

I need a *difference* between the two stores to the same location. E.g., one store via a struct member and the other via a plain s16. Then cse's alias/equivalence may not match them.

Per §425: "sb aliases scalar globals while sh/sw struct stores do not". So a struct store does NOT alias a scalar load. If store1 is a scalar store and store2 is a struct store, cse's `exp_equiv_p`/`memrefs_conflict_p` might treat them as different.

Let me test:
- `b[0] = t;` (scalar) and later `((struct S2 *)b)->v = u88;` (struct) — the second is an address cast (identity), hmm.
- Or make the array a struct and one store scalar via a cast.

Both directions require a cast somewhere.

Hmm, wait. Actually, let me check what the real difference is: maybe it's not dead-store elimination but *scheduling* (sched1 merging the store groups). Let me look at the .cse dump for v1 to see if the stores survive cse.

Let me run hdump on v1 for item 3 and grep the cse output.

Actually, let me first check the simplest hypothesis: are the 3 missing insns the dead stores? 42 vs 45 = 3 insns. Yes: `sh v1,24` (b[0]=t first), `sh v0,28` (b[2]=t2 first), and... let me count the target's stores: 24 appears 3 times (v1, a0, and the initial v1?) — target has `sh v1,24` twice (initial and after subu), `sh a0,24`, `sh v0,28` twice (t2 initial and after), `sh a1,28`. Source: b[0]=t (1), b[0]=t (2), b[0]=u88 (3), b[2]=t2 (4), b[2]=t2 (5), b[2]=u8C (6). Target: sh v1,24 (t), sh v1,24 (t), sh a0,24 (u88), sh v0,28 (t2), sh v0,28 (t2), sh a1,28 (u8C) = 6 stores. Mine has 3 stores (b[0]=u88, b[2]=u8C, and one more). So 3 dead stores removed.

So we need to keep the dead stores. Real-C: cse's dead-store elimination for stack slots.

Hmm, in GCC 2.7.2's cse.c, dead stores are deleted in `cse_insn` via `set` handling: "If this is a store to a memory location that is not used, delete it." Actually, the relevant code is in `cse_insn`:

```
/* If this is a store into a memory location, and the location is not
   used before the next store, delete it. */
```

Hmm, but for *stack* slots (frame-relative), gcc knows the addresses don't escape except through the calls. The calls (func_8014E284) take `b` — but those calls happen after all the stores.

Wait, actually, cse deletes a store only if it's certain it's dead. For stack slots, `b[0] = t; b[0] = u88;` — the first is dead.

With the memory clobber, the asm could read b[0] → the store is live.

Real C: is there any construct that reads b[0] without emitting code? No.

BUT: maybe we can make cse think the store is live by making the address *not provably* the same. E.g., if the two stores use different pointer expressions that cse can't prove equal. For stack slots, cse tracks `(plus (reg sp) (const 24))` — exact.

What if the array index is a variable? e.g., `b[i] = t;` where i=0 — cse would know i=0 via propagation? Maybe not! If the index is a variable that cse can't prove is 0, the addresses differ → both stores kept. But then the code would use a computed address (lw/addu), not `sh v1,24(sp)`. Hmm, unless gcc constant-propagates.

What if we use a pointer `s16 *p = b;` and store `p[0]`? The address is the same.

Hmm.

What about making the stores go through *different base pointers* that alias: `s16 *p = b; s16 *q = b;` — cse may track both as b.

What about `p = b + 0;` vs `q = b;` — same.

Hmm, what if one store is through `(s16 *)((u8 *)b)` and the other through `b`? Same address expression after folding.

Let me look at the cse dump to understand exactly what's deleted and by which pass. Let me run hdump on v1.

Actually, let me first try the struct/scalar alias-class idea empirically. The key per §425: struct stores don't alias scalar loads/stores. So if I make the *later* store a struct store and the earlier a scalar store, cse may keep both.

How to write a struct store to b[0] without an address cast? Declare b as a struct and write `b.x = u88;`, and for the scalar store use a cast... hmm, one of them needs a cast.

Alternatively, declare a union/struct overlay *variable*:
```
struct S3 { s16 x, y, z; };
struct S3 *bp = (struct S3 *)b;   // pointer to b
```
Still a cast.

Hmm, everything involves a cast of the stack address. Is a cast of a *local stack array* an "identity address spelling"? Probably yes, but it's a local variable, not a global. The prohibition examples were about value/address identity. A cast to a struct type changes MEM_IN_STRUCT_P, which is a real codegen-relevant type change (§425/§469) — the project accepts these as real moves (the W03 precedent).

Let me just try a few variants and see if any scores 0.

Variants:
y1: declare `struct S3 { s16 x,y,z; } a, b;` and use `a.x`/`b.x` etc. (all in-struct). Calls: `func_8014E284(arg0, (s16 *)&a, (s16 *)&b)`.
y2: keep arrays, but make the *later* stores struct stores: `((struct S1 { s16 v; } *)b)->v = u88;` etc.
y3: make only the intermediate stores struct.

Let me first check how the target's calls pass a/b: `addiu a1,sp,16` (a) and `addiu a2,sp,24` (b). With structs, `(s16 *)&a` should give the same.

Let me write y1 carefully. The source with structs:

```
struct P3 { s16 x, y, z; } a, b;
s32 u88, u8C, t, t2;
u88 = *(u16 *)(arg0 + 0x88);
a.x = u88;
a.y = *(u16 *)(arg0 + 0x8A) - 0x10;
u8C = *(u16 *)(arg0 + 0x8C);
a.z = u8C;
t = *(u16 *)(arg0 + 6);
b.x = t;
b.y = *(u16 *)(arg0 + 0xA) - 0x10;
t = t - u88;
t2 = *(u16 *)(arg0 + 0xE);
u88 = u88 - t;
b.x = t;
b.x = u88;
b.z = t2;
t2 = t2 - u8C;
u8C = u8C - t2;
b.z = t2;
b.z = u8C;
if (*(s32 *)(arg0 + 0x170) == 0) func_8014E284(arg0, (s16 *)&a, (s16 *)&b);
else func_8014E048(arg0, (u16 *)&a, (u16 *)&b);
```

This has no barriers. Let me score it. If cse still deletes the dead stores, we need the mixed alias class.

Let me also prepare y2: mixed — first store scalar (`b[0]`), later struct (`((struct S1 *)b)->v`).

Let me test y1 first.
