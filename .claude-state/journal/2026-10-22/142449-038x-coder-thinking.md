---
ts: 2026-10-22T20:24:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qukScwyMDNuOVlOHi0GZ
---
All 19 — cse merges regardless (the address pseudo is created for the movstr dest and reused).

Let me check v2's disasm: does it still have s1? Probably.

New idea: make the movstr's dest not a stack constant address. What if m is accessed through a *union with a larger struct* so the address fp+16 isn't a direct movstr dest? no.

What if the copy is a *memcpy-like* explicit 8 loads/stores written so gcc's movstr doesn't kick in, e.g., scalar copies (score-0 shape) but with the source as a struct pointer variable — the cse folding issue. Hmm, what about reading the source with `D_800AE620.w0` etc. directly (global member accesses)? Then there's no pointer variable at all; cse sees symbol+offset addresses. Does cse create a base register for a symbol address used 8 times? Classic gcc: for a global array accessed many times, it emits one lui + offsets (yes, cse creates a base reg for the symbol). The n1 case created a base? No — n1 had `lui v0,0x0; lw v0,12(v0)` per load — but that's because the address came from a pseudo with a constant value and cse substituted symbol+offset, then each `lw` got its own lui... Hmm, that suggests cse didn't create a base for symbol addresses in n1.

But wait: n1's source is `src[i]` where src = &D_800AE620 (a pseudo assigned a constant). cse replaced src by the constant, giving 8 loads with symbol+const addresses. Each address is a distinct constant → reload emits lui per load (lui+lo for each). To get one base + offsets, cse must create a base reg for the symbol_ref. gcc's cse_insn does do this: when a `symbol_ref` appears in an address multiple times it creates a base register... apparently not here.

Hmm, but the target's movstr source clearly uses one base. That's the movstr pattern (a single mem:BLK source address).

So the movstr is required for the source. And the movstr's dest store address creates the base pseudo.

Unless the movstr dest is not fp+16 in the RTL but a pseudo that is *different* from the call address pseudo. In c_struct, cse equated them. If the movstr dest were a pseudo that cse can't equate (e.g., a function argument), the call address would stay a constant and fold.

Can I make the copy destination a pointer parameter? No signature changes allowed.

What about copying INTO m through a `Mat32 *` variable that's assigned from a *non-constant* expression cse can't fold, e.g. `dp = (Mat32 *)((int)m & ~3);`? That's an identity-ish address spelling (mask 3 = no-op). Disallowed as identity.

What about `dp = (Mat32 *)((char *)m + 0);`? identity.

Hmm. What about using `m + (i - i)`? identity.

Let me step back and consider: maybe the target isn't a movstr at all. Maybe the target's source base in a1 comes from a *pointer variable pinned/held* naturally because the loads are volatile? No.

Alternative: maybe the target C reads the global as a struct into m via `m[0] = D_800AE620.w0;` etc. and cse creates the base because the addresses are (symbol + const) with a *common base* recorded in cse's `reg_eqv` table via `(symbol_ref)` plus const folding? Let me just test the direct global member reads. Mat32 fields: w0,w4,w8,wC,h10,hpad,t0,t1,t2. 8 words: w0,w4,w8,wC,(h10,hpad as one int),t0,t1,t2.

m[0]=D_800AE620.w0; m[1]=D_800AE620.w4; m[2]=D_800AE620.w8; m[3]=D_800AE620.wC;
m[4]=*(int*)&D_800AE620.h10; — ugly. Better: cast the global: `((int *)&D_800AE620)[0]` — that's the n1 folding case.

But direct named members: the loads would be `lw v0,D_800AE620+0`, `lw v1,D_800AE620+4`, etc. cse might create a base. Test it.

Actually, hmm, let me look at the target's copy more carefully: `lui a1,0x0; addiu a1,a1,0` — a1 = &D_800AE620, then loads at 0,4,8 / 12,16,20 / 24,28. If the C were 8 separate `m[i] = D_800AE620.wX`, gcc would likely emit lui/addiu a1 for the base and use offsets — this is exactly what gcc does for repeated accesses to one global symbol (it creates a base register via cse). n1's failure was different: the address came from a *variable* with a known constant, and cse substituted the constant into the address of each load (the constant substitution path), giving `lui v0; lw v0,off(v0)` per load. Direct symbol accesses may take the "base register" path.

Worth testing: v11 with direct member reads. But the member types: w0,w4,w8,wC are s32; h10,hpad are s16; t0,t1,t2 s32. Copying into `int m[8]`: m[4] = *(int *)&D_800AE620.h10 (a cast of a member address — identity-ish but a real type pun). Or declare m as a Mat32! `Mat32 m; m.w0 = D_800AE620.w0; ...` — then the final `*(Mat32 *)(obj+0x34) = m;` and calls `(void *)&m`.

Let me test:
v11: Mat32 m; m.w0=D_800AE620.w0; m.w4=...; m.w8; m.wC; *(int*)&m.h10 = *(int*)&D_800AE620.h10; m.t0..t2; calls (void*)&m; store *(Mat32*)(obj+0x34) = m;
Hmm, `*(int*)&m.h10` — that's a pointer cast on a member; cse-wise fine, and it's real C (type pun), not an identity address spelling of the call arg.

Actually simpler: keep `int m[8]` and write:
```
m[0] = D_800AE620.w0; m[1] = D_800AE620.w4; m[2] = D_800AE620.w8; m[3] = D_800AE620.wC;
m[4] = *(int *)&D_800AE620.h10;
m[5] = D_800AE620.t0; m[6] = D_800AE620.t1; m[7] = D_800AE620.t2;
```
This is real C. Let me test it, plus a variant with the temps (t0,t1,t2 grouped 3 at a time as in src).

Also v12: `m[0] = D_800AE620.w0;` etc. but grouped exactly as the target's 3-load pattern: m[0..2], m[3..5], m[6..7] using t0,t1,t2 temps — like src's scalar form but with direct member reads.

Let me test a few.
