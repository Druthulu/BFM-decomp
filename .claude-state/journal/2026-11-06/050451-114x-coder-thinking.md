---
ts: 2026-11-06T12:04:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jzA6lwuUiZuGwlQKsnIN
---
Target:
```
4180: andi v1,v1,0x7f
4184: lui at, D_8011F83A
4188: sb v1,0(at)         ; D_8011F83A = idx
418c: sll v1,v1,0x2
4190: lui at, D_8018DB2C
4194: addu at,at,v1
4198: lw a0,0(at)          ; D_8018DB2C[idx]
419c: jal func_80024054
41a0: addiu a1,sp,24       ; delay slot: local
```
Mine:
```
4180: andi v1,v1,0x7f
4184: sll v0,v1,0x2         ; <-- hoisted before the store
4188: lui at, D_8018DB2C
...
```
So mine computes the index address before the sb, using v0. The barrier (memory clobber) prevented the load/address computation from moving above the store.

Hmm, actually the *address computation* (sll/lui/addu) is pure arithmetic; only the `lw` must stay after the store. The target computes `sll v1,v1,0x2` after the sb; mine before.

Why? sched1 moves the address computation earlier (it has no memory dependency). The target (with the barrier) has a scheduling barrier between the store and the load, so sched1 can't move the load; but the address computation could still move... unless the barrier also splits the block.

The barrier `asm volatile("" ::: "memory")` is a *volatile* asm → it's a scheduling barrier (sched.c splits regions at volatile asm? or at asm with memory clobber). So the address computation can't move above it.

Real C: can I make the address computation depend on the store? E.g., compute the index from `idx` after storing... it already does (`idx` is the value).

Hmm, what if I write:
```
D_8011F83A = idx;
((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018DB2C)[D_8011F83A & 0x7F], local);
```
i.e., re-read D_8011F83A instead of using idx? That would add a load. Hmm, but it would create a dependency on the store → the address computation can't hoist. But it adds an lbu (extra insn).

Alternatively, use the store's value via a volatile read? adds code.

Hmm. What if `idx` is declared volatile? Lever-ish.

Let me look at what exactly needs to happen: target computes the address after the sb. Mine before. The difference is 2 insns (sll at 4184 vs 418c). Actually the diff said the 4-insn block moved: mine[134:138] vs target[136:140]. So the sll/lui/addu/lw block moved 2 insns earlier in mine.

Wait, in mine the `lw` — let me see mine's 4184-4198. Mine: 4184 sll v0,v1,0x2; 4188 lui at; 418c addu?; 4190 lw?; then sb? Let me see.

Hmm, the store `sb v1,0(at)` in mine would be at 4194 or so.

The target has the store at 4188 then the address computation. So mine moved the whole block (including the lw!) above the store. That means cse/sched doesn't see a dependency between the store to D_8011F83A and the load from D_8018DB2C[idx] — because `idx` is derived from D_8011F83A's *loaded* value (lbu at 4178), and the store writes a value to a different address. The load `D_8018DB2C[idx]` and the store `D_8011F83A` — gcc's alias analysis says they don't alias (different symbols, and the load address is symbol+reg... hmm).

Actually, sched1 might treat them as independent because D_8018DB2C is an array of pointers and the address is `symbol + reg*4`; true_dependence between `(mem (plus (symbol_ref D_8018DB2C) (reg)))` and `(mem (symbol_ref D_8011F83A))`... In gcc 2.7.2, `true_dependence` checks if the addresses may overlap; for two distinct symbol_refs with an offset, it might determine they don't alias.

Hmm, so the barrier is needed.

Real C: force a dependency. Idea: store `D_8011F83A = idx;` and then read it back into a variable used in the index: 
```
D_8011F83A = idx;
idx = D_8011F83A & 0x7F;   // re-read
... D_8018DB2C[idx]
```
That adds an lbu (extra insn) — but maybe cse keeps the value? If cse forwards the store to the load, the load is eliminated → no dependency. Hmm.

Alternatively, use a volatile read: `idx = *(volatile u8*)&D_8011F83A & 0x7F;` — adds lbu.

Hmm. What about making the *store* address computation depend on the load? No.

Let me look at the actual C:
```
idx = D_8011F83A & 0x7F;
D_8011F83A = idx;
<barrier>
((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018DB2C)[idx], local);
```

The target's code: `lbu v1,D_8011F83A; andi v1,0x7f; sb v1,D_8011F83A; sll v1,v1,2; ...; lw a0,0(at)`.

Interesting: the target uses v1 (the same reg) for both the sb and the sll. So `idx` is in v1.

Without the barrier, the sll moves above the sb (using v0, a different reg).

Hmm, if I make `idx`'s value live across the store in a way that pins it... 

What if I write the index expression inline:
```
((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018DB2C)[idx], local);
```
→ `((s32 *)D_8018DB2C)[(D_8011F83A = idx)]`? That's an assignment inside the subscript — a real C trick to force the store to precede the load! Let me think: `((s32 *)D_8018DB2C)[(D_8011F83A = idx, idx)]` — hmm, the comma operator.

Actually: `D_8018DB2C[idx = idx]`? no.

What about: 
```
D_8011F83A = idx;
((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018DB2C)[D_8011F83A], local);
```
Using `D_8011F83A` as the index would force a load from it after the store (or cse would forward the stored value → no load, but the *dependency* would exist in the RTL: cse replaces the load with the stored value... then the dependency is only on the register, not memory).

Hmm.

What about a real C store to a memory location that the load must depend on? 

Alternative: use a volatile pointer for the load:
```
((void (*)(s32, u8 *))func_80024054)(*(volatile s32 **)&((s32 *)D_8018DB2C)[idx], local);
```
Ugly and probably adds code.

Hmm. What about reordering the C: put the store AFTER the load? No — the target has the store first.

Hmm, actually — is the barrier's effect really needed, or is the 8-point diff acceptable? Score 8 = not a match.

Let me think about the launder too: w1 (real assignment) = 30, +3 insns. The launder makes `base` rematerialize. Real C equivalent: the C0414 dead reset! Let me try `base = (u8*)&D_8011F7F0;` then after `arr = base - 0x48;` do `base = 0;` (dead reset). Actually the launder is a re-set of base to the same value. A dead reset would be `base = 0;` after the last use of base? base is used many times (lines 3970, 3971, 3980, 3981, 3987, 3988).

Hmm, the launder is at the start: `__asm__("" : "=r"(base) : "0"(&D_8011F7F0));` sets base = &D_8011F7F0, breaking the cse class so that later `*(u16*)(base-0x34)` etc. rematerialize `addiu` from the constant instead of a register.

Real C: `base = (u8*)&D_8011F7F0;` directly. That's w1 = 30. The extra 3 insns come from base living in a register.

Hmm. Maybe: declare base and use `&D_8011F7F0` directly in the expressions? E.g., replace `*(u16*)(base - 0x34)` with `*(u16*)((u8*)&D_8011F7F0 - 0x34)` — the compiler would fold to a symbol address. That's probably what the target does (rematerialized addiu). Let me look at the target code for base.

Target: `lui at, D_8011F7F0`? Let me look at the target's start.

Actually, the C has `base` used as a pointer with offsets. The target rematerializes `addiu aN,sp,N`? no, it's a global address: `lui at,0x0; addiu at,at,0` for D_8011F7F0, then `lhu a2,-52(at)`.

Let me look at the target's beginning (the L1 region).

Given time, let me try a few things for item 4:
- x1: C0414 dead reset for base: `base = (u8*)&D_8011F7F0; arr = base - 0x48; base = 0;`? But base is used later. Hmm, base must stay valid.

Hmm, the launder re-sets base to the same value; it's not a dead reset, it's a "re-tie". The real-C equivalent might be to use the constant expression at each site (no base variable).

Let me look at the target code first.
