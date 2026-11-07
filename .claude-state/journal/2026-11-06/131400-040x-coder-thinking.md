---
ts: 2026-11-06T20:14:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GKS3JDZdN2qtCJ8caXaG
---
`count_loop_regs_set` counts real insns. So 28.

Given the 1-insn margin, another idea: make `threshold` smaller by... hmm, n_non_fixed_regs is global.

BUT: `fix_register` is called for `__asm__` register variables. What about other ways GCC fixes a register from C source? `-ffixed-` is a flag. There's no C construct besides `register ... asm`. The brief forbids pins.

Hmm, but what about making `loop_has_call` false and reducing n_non_fixed_regs? No.

Wait — actually, is `threshold` maybe affected by `n_non_fixed_regs` only? Yes.

Alternatively: reduce `m->lifetime` below 1? No.

Alternatively: make `insn_count` bigger by making the loop *contain* an extra insn that survives loop.c but is deleted by combine. Let's find a combine-able construct whose final code is identical.

The store `*(s16*)(*p + 0xA) = -0x400;` → `lw v1,0(s1); li v0,-1024; sh v0,10(v1)`. Wait, actually the reload `lw v1,0(s1)` comes from `*p`. In target: `lw v1,0(s1); li v0,-1024; sh v0,10(v1)`.

Idea: write the store with an explicit byte-address temp: `u8 *b = (u8 *)*p; *(s16*)(b + 0xA) = -0x400;` The RTL: lw reg; addiu? No — the offset 0xA folds into the mem. But the temp `b` adds a copy that cse1 propagates away. So no extra insn at loop.c.

Idea: make the address computation involve an add that combine folds into the store: e.g., `*(s16*)((u8*)*p + 0x8 + 2) = -0x400;` — constant folding at tree level → 0xA.

Idea: use a variable offset: `s32 o = 0xA; ... = *(s16*)((u8*)*p + o);` — then loop.c sees an extra `li o,0xA` (invariant, hoistable) plus the add — combine can fold `addiu v1, v1, 10` into the mem offset? Combine can fold a constant add into a mem address (yes, `plus` of reg + const folded into the mem). But the `li o,10` would be hoisted by loop.c or cse'd. Hmm, this changes things unpredictably but worth a try: if `o=0xA` is a const pseudo used once, loop.c might hoist it, giving li s? ... not matching.

Idea: make the *store* address computation produce an extra insn that combine folds: `s32 a = (s32)*p; a += 0xA; *(s16*)a = -0x400;` → lw; addiu a,a,10; sh → combine folds addiu into sh's offset → lw; li; sh. So at loop.c time: lw, addiu, li, sh = 4 insns instead of 3, giving insn_count 29! Then no hoist. After combine: addiu folded into the sh offset → identical final code!

But wait: the `a += 0xA` where a = *p — but the source uses `*p` reloaded each time. Let's write:
```
{
    s32 a = *p;
    a += 0xA;
    *(s16 *)a = -0x400;
}
```
Hmm, but `a += 0xA` with a being a byte address? `*p` is s32, `a += 0xA` then store s16 at a — that's a byte offset of 10, same as target's `sh v0,10(v1)`. Good.

But there's a catch: cse1 might already fold the addiu? No, cse doesn't do address folding; combine does (after loop). Also, could the add be hoisted by loop.c as invariant? No, it depends on `*p` which varies.

Also: the extra insn `addiu` would be counted by count_loop_regs_set → 29 → threshold 28 < 29 → no hoist of -1024. 

But: with the -1024 not hoisted, it's `li v0,-1024` in the loop. Then combine folds addiu into sh. The register allocation might differ: `a` is a temp; after combine, the sh uses v1 (the lw dest) with offset 10 — same as target.

Risk: the addiu and li might be scheduled differently, and sched1 runs after combine so the folded code is what sched1 sees. Should be fine.

Also risk: cse1 might turn `a = *p; a += 10` into something else? cse1 does copy propagation but not arithmetic folding. combine is after loop.

Wait, but does cse1 see `lw a,0(s1); addiu a,a,10; sh ...`? Yes. cse1 won't fold.

Also, will the `a` variable's live range interfere? After combine, a is gone (folded). Good.

Let me try this variant. Also a variant using the address temp for a different store (the -0x92 store at the end, `CAST_NONSTRUCT(s16,*p,0x8A) = -0x92;` → `li v0,-146; sh v0,138(v1)`). Target keeps -146 in-loop too ("not desirable" per the dump because threshold 28 >= 28? it said not desirable — interesting: insn 136 const -146 "not desirable" while -1024 was moved. Both have savings 1, lifetime 1. Why the difference? Maybe -146's lifetime is 0? or the condition differs. Hmm, in the vA dump: insn 96 moved, insn 136 not desirable. Both consts. Maybe insn 136 is the p++ addiu? "possible biv, reg 97, const = -146" — that's the li -146 which is used in a biv? Odd. Anyway.)

Let me test the address-temp variant.

Also consider: the same trick could add the extra insn at the -0x400 store only.

Let me write vG:
replace
```
            CAST_NONSTRUCT(s16, *p, 0xA) = -0x400;
```
with
```
            a = *p;
            a += 0xA;
            *(s16 *)a = -0x400;
```
and declare `s32 a;`. But `a` might clash with a name; use `z`? z is unused. Use a new `s32 a;`.

Hmm wait: `a = *p; a += 0xA;` — a is s32; the store `*(s16*)a` — the compiler sees `a` as an int address. It will emit lw a,0(s1); addiu a,a,10; sh. Good.

But careful: `*p` is `s32 *p` — `a = *p;` gives the pointer value. Then `a += 0xA` adds 10 bytes. `*(s16*)a` — target's sh v0,10(v1) where v1 = *p. Yes.

Let me test.
