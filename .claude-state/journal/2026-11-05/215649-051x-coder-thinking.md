---
ts: 2026-11-06T04:56:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1dxCkFZwGJrfFn2b7TG2
---
Confirmed: reloc operand (symbol+addend) equality is required. So I cannot change the symbol references: the store must be `D_80078EA4` and the load `D_80078EA6`.

Therefore I need a dependency between them without changing the relocs. Hmm.

Wait — but the *target* has the load after the store, so the target's source had something that created the dependency. The barrier is a memory clobber. Is there real C that creates an alias? 

Since EA4 and EA6 are separate extern symbols, GCC's alias analysis treats them as distinct objects. Unless... we access them through a pointer derived from one another? But the reloc must remain.

Hmm, what about the order of *statements*? In the target the load is after the store. In C: `D_80078EA4 += a1; if (D_80078EA6 >= 0xA1)`. The RTL order is store then load. sched1 moved the load up because it's independent. What makes sched1 keep the order? A memory dependency. The memory clobber.

Alternatively — maybe it's not sched1 but the *RTL order itself* that differs: maybe the candidate's load is before the store even before sched1 (e.g., due to cse/combine). Hmm, the candidate's addu is after the load. In the target, the order is lw, addu, sw, lh.

Could a different C spelling produce lw, addu, sw, lh without a barrier? E.g., if the comparison uses the *stored value*:

```
s32 v = D_80078EA4 + a1;
D_80078EA4 = v;
if ((s16)D_80078EA6 >= 0xA1) ...
```
Same.

What if the comparison is written to depend on v: `if ((s16)D_80078EA6 >= 0xA1)` — no.

What if the store is a *volatile* access? That's a lever (barrier-like).

Hmm. What about the fact that D_80078EA4 is `extern s32` and D_80078EA6 is `extern u16`? The header declares `extern u16 D_80078EA6;`. The code does `(s16)D_80078EA6 >= 0xA1` → lh. 

What if we make the compiler believe the load may alias by using `__builtin_memcpy`? no.

Let me reconsider: maybe the dependency can come from the *same* address computed through a local pointer variable that both accesses use:

```
s32 *p = &D_80078EA4;   // reloc D_80078EA4
s16 *q = (s16 *)p;      // same object!
*p += a1;
if (q[1] >= 0xA1)       // q[1] = offset 2 from D_80078EA4
```
The reloc for q[1] would be D_80078EA4 + 2, not D_80078EA6. Mismatch.

Unless... the compiler sees `q[1]` as an access to the same object at offset 2 → overlap → dependence → order kept. But the reloc differs.

Hmm, so this can't match unless the scorer resolves symbol+addend equality semantically. It compares strings. D_80078EA4+2 vs D_80078EA6 → different strings.

Wait, actually, let me check what the assembler emits. If I write `*(s16 *)((u8 *)&D_80078EA4 + 2)`, GCC's RTL is a MEM with address `(symbol_ref "D_80078EA4") + 2`. The assembler (GNU as) emits a reloc `R_MIPS_LO16 D_80078EA4` with the addend folded into the instruction (e.g., `lh v0,2(v0)`)! In MIPS, the addend is in the immediate field, not in the reloc. So the reloc operand would be "D_80078EA4" and the instruction would be `lh v0,2(v0)`. The target has `lh v0,0(v0)` with reloc D_80078EA6. The *word* differs (immediate 2 vs 0) and the reloc operand differs (D_80078EA4 vs D_80078EA6). Mismatch on both.

OK so that's out.

Think about it from the target's perspective: the original source (with the asm barrier) is what we must reproduce without the asm. The asm memory clobber is what created the dependency. Is there a real-C construct that creates a memory dependency between two distinct global symbols without an asm? 

Yes! If the compiler can't prove the two accesses don't alias. GCC 2.7.2's alias analysis: two MEMs alias if their addresses are "may_alias" — for symbol_refs, it uses `alias_sets` from the declaration's type (TBAA was introduced in 2.7?). In 2.7.2, `alias_sets` exist (`-fstrict-aliasing` was added in 2.7? Actually strict aliasing came in 3.0; 2.7 had `alias_sets` for C++ maybe). For C, `true_dependence` uses `memrefs_conflict_p`, which for two symbol_refs compares: if they're the same symbol and offsets overlap → conflict; different symbols → no conflict (unless one is a pointer that may alias).

So: if one of the accesses is through a *pointer* whose target is unknown, it may alias anything. E.g., a pointer parameter or a pointer loaded from memory. But our accesses are both direct symbol references.

Hmm! What if we make the store go through a local pointer that we set from the symbol, and the load direct? Then the store is a MEM with a register address (unknown base) → it may alias the direct load → dependency → order kept! But the store's address would be a register (computed by `lui/addiu` into a register) rather than the assembler's `at` expansion... Actually the target's store uses `lui at; sw v0,0(at)` (assembler macro). If we use a local pointer `s32 *p = &D_80078EA4; *p += a1;`, gcc would compute the address into a register (e.g., `lui v1; addiu v1,v1` or `lui at; sw 0(at)`?). Hmm, gcc 2.7.2 MIPS with -O2 typically uses `lui at; sw v0,%lo(sym)(at)` for a direct symbol store (the assembler macro). For a pointer variable, gcc might still use the assembler macro if it can fold. Let me test: write `s32 *p = &D_80078EA4; *p = *p + a1;` and see the output.

But careful: the load `*p` would also be through the pointer, and the reloc for the load would be D_80078EA4 (same symbol) — that's fine for the load (target's load reloc is D_80078EA4). And the store `*p = ...` would also reference D_80078EA4 → target's store reloc is D_80078EA4. Good!

But would the *address materialization* differ? Target: `lui v0, D_80078EA4; lw v0,0(v0)` (for the load) and `lui at, D_80078EA4; sw v0,0(at)` (for the store). With a pointer variable p, gcc might emit `lui v1, D_80078EA4; lw v0,0(v1)` and `lui at; sw v0,0(at)` — using a register v1 for the address instead of the assembler macro. Hmm, actually for a direct symbol load gcc uses `lui v0; lw v0,0(v0)` (the macro uses the destination register). For a pointer, it may use the same expansion.

Let me just test empirically: body with `s32 *p = &D_80078EA4; *p += a1; if ((s16)D_80078EA6 >= 0xA1) ...`.

Wait, but there's a subtlety: if p is used for the store and the load, the two accesses are through the same pointer → dependence (same base object) → order kept. And the load of EA6 is a direct symbol → may it alias the pointer store? A pointer store with unknown base vs a symbol load: `memrefs_conflict_p` — if the pointer's alias set is 0 (unknown), it conflicts with everything → the load stays after the store. That's what we want!

Actually, more precisely, sched1's dependency check uses `true_dependence` on the mems. A store through a register base and a load from a symbol: in 2.7.2, `true_dependence` calls `memrefs_conflict_p (xsize, x_addr, ysize, y_addr)`; for a SYMBOL_REF vs a register, it likely returns 1 (can't prove) unless the symbol is a constant pool. So the order is kept.

But would that also prevent other reorderings (e.g., the load being hoisted in the second half)? We'll see.

Let me try this for item 2. Also, the same trick might be needed for the `+=` blocks in all 6 places.

Actually, wait. Let me reconsider — maybe simpler: use a *volatile* pointer? No, volatile is a lever.

Another thought: `D_80078EA4 += a1;` — what if we write `*(s32 *)&D_80078EA4 += a1;`? Same symbol, same code.

Let me test the pointer idea. Also test: `s32 v = D_80078EA4; D_80078EA4 = v + a1;` etc.

But hold on — if the pointer store prevents the EA6 load hoist, we also need the *store* itself to keep its position relative to the load of EA4. Fine.

Let me try a batch of item-2 variants. But first, let me check the second half of the function: the target's second half uses `base + 0x60` / `base + 0x62` where base = D_80078E78. Since the store (4 bytes at 0x60) and load (2 bytes at 0x62) overlap, the dependency exists → the order is kept naturally. Good, so the second half may already match.

Let me now write item 2 candidates:
p1: pointer for the EA4 access:
```
s32 *p = (s32 *)&D_80078EA4;
...
*p += a1;
if ((s16)D_80078EA6 >= 0xA1) D_80078EA4 = 0xA00000;
```
But `D_80078EA4 = 0xA00000` would be a direct symbol store (target uses `lui v0,0xa0` → `lui at; sw`). Hmm, target: `lui v0,0xa0; j join; nop` and presumably `sw v0,0(at)` somewhere? Wait, target's block: `slti v0,v0,161; bnez v0,6160; lui v0,0xa0; j 6158; nop`. Where's the store of 0xA00000? It must be at 6158 (the j target), shared: at 6158 there's probably `lui at; sw v0,0(at)` common to both halves! Yes — the target shares the store `D_80078EA4 = 0xA00000` at 6158 between the two blocks (that's why there are jumps).

Interesting: so the constant is loaded in the delay slot (lui v0,0xa0) and the store is shared at 6158. That's a cross-jump/merge.

Hmm, this is getting complex. The diff showed mine[18:19] `bnez v1,6144` vs target[16:21] (lui v0; lh v0; nop; slti; bnez). So the target's first block continues into the second block's code? Wait no.

I think the target's structure: the a2!=0 arm ends with a jump to 6158 (shared store). The fall-through 60c4 is the else arm (call check). So the two arms share the tail at 6158.

OK. Let me just try the pointer move and see the score.

Actually, let me reconsider whether sched1 is really the cause. Maybe the reordering comes from *cse* (which can move insns? no) or from `flow`/`combine`. sched1 is the most likely.

Alternatively, maybe the difference is caused by the memory clobber in a different way: the asm is *between* the store and the load in the source:
```
D_80078EA4 += a1;
__asm__("" ::: "memory");
if ((s16)D_80078EA6 >= 0xA1) ...
```
So the barrier is exactly between the store and the load. Yes.

A real-C equivalent that orders the store before the load: make the load address depend on the store's value? No...

What if we write the comparison using the *same* variable after the store:
```
D_80078EA4 += a1;
if ((s16)D_80078EA6 >= 0xA1) ...
```
No dependency.

Hmm, what about writing the store via a pointer that is then also used to compute the load address? The reloc problem again.

OK, the pointer-store idea is the best bet. Let me test it.

Actually, wait! There's an even simpler idea: use a *local pointer variable* for the EA6 load, e.g.:
```
s16 *q = &D_80078EA6;   // reloc D_80078EA6
D_80078EA4 += a1;
if (*q >= 0xA1) ...
```
The store is a direct symbol store; the load is through a pointer q. Does a symbol store conflict with a pointer load? If gcc can prove q points to D_80078EA6 (it was just assigned &D_80078EA6), it may know the address... In 2.7.2, pointer tracking is weak; the load's address would be `(reg q)` → memrefs_conflict_p with a symbol store → conflict → order kept. But the address materialization: `lui v0, D_80078EA6; lh v0,0(v0)` (target) vs with a pointer, gcc might emit the same macro into a register. Let me test.

Similarly, the pointer store `s32 *p = &D_80078EA4; *p += a1;` — the load `*p` and store `*p` through the same pointer.

Let me test several variants:

p1: pointer for both EA4 accesses (load+store through p), EA6 direct.
p2: EA4 direct, EA6 load through a pointer q.
p3: both through pointers.
p4: EA4 store through p, load direct.
p5: use `register` — forbidden.

Let me write them. The body has 6 occurrences (3 in each half). I'll apply the transformation to the first half's three blocks and the second half's three blocks.

Wait, the second half uses base+0x60/0x62 (overlapping) — the target there keeps the order. So only the first half (EA4/EA6) needs the fix. But the target's second half is compiled from `base + 0x60` etc. If the second half already matches, leave it.

Let me write p1-p3.

Body template:

```c
void func_8014B944(s32 a0, s32 a1, s32 a2)
{
    u8 *base = D_80078E78;
    s32 *p = (s32 *)&D_80078EA4;   // p1
    if (a2 != 0) {
        *p += a1;
        if ((s16)D_80078EA6 >= 0xA1) {
            *p = 0xA00000;
        }
    } else {
        ...
    }
    ...
}
```

Hmm, but `*p = 0xA00000` might change the code vs `D_80078EA4 = 0xA00000` (target uses a shared store). Let me keep the constant store as `D_80078EA4 = ...` to preserve the reloc and expansion; the pointer p is only for the += store.

Actually the += store and the constant store both target D_80078EA4; using p for one and the symbol for the other is fine (both reloc D_80078EA4).

p1:
```
s32 *p = (s32 *)&D_80078EA4;
...
*p += a1;
if ((s16)D_80078EA6 >= 0xA1) { D_80078EA4 = 0xA00000; }
```

p2:
```
s16 *q = (s16 *)&D_80078EA6;
D_80078EA4 += a1;
if (*q >= 0xA1) { D_80078EA4 = 0xA00000; }
```

p3: both.

Also the third block (else arm) has `if ((s16)D_80078EA6 < 0x80) { D_80078EA4 += a1; if (D_80078EA6 >= 0x81) D_80078EA4 = 0x800000; }`.

Let me generate these with a script that does a textual replacement on the barrier-free body.

Actually simpler: write the full body explicitly for each variant. The function is ~45 lines. Let me write a generator that takes the original and applies replacements.

Replacement 1: `D_80078EA4 += a1;` → `*p += a1;` (3 occurrences in the first half).
Replacement 2: `(s16)D_80078EA6` → `*q` (3 occurrences).

Let me write gen_item2.py that produces variants.

Also consider: maybe the *whole* difference is just the hoist in the 6 blocks; the second half's hoist doesn't happen because of the overlap. Let me verify by checking the candidate's second half. From the earlier diff, the differences continued into the third block (mine[25:44] vs target[27:28]) — that's the first half's third block. Let me look at the second half diff (after line 60). Let me print the rest of the diff.
