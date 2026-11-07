---
ts: 2026-11-06T04:08:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_df7KMM364yjOoC3BLTEg
---
Volatile gave 60 ins and changed the load to lhu + sll/sra (sign extension from volatile u16?) — volatile makes it a plain HImode load that then needs sign extension? Odd: it emitted `lhu` then sll/sra. Because volatile load is HImode and assigning to s32 x2 requires sign-extension, done via lhu+sll+sra? Actually lhu zero-extends; then sll 16, sra 16 sign-extends the low 16 bits. That's 3 insns.

So volatile isn't the mechanism either (the target has plain lh).

OK. The target's second load is `lh` (sign-extending load) — a direct HImode load into a register used as s32. That means the C expression is `*(s16*)...` used directly in a signed context. So the second load IS a normal `s16` load.

So cse did not forward it. In the original source, something prevented it. What if the first load and second load are in **different basic blocks**? cse flushes the table at the end of an extended basic block (a label that is a branch target). Is there a branch in the target between 77cc and 77d8? No. But cse's EBB can end at a `CODE_LABEL` even without a branch? cse_basic_block is called with a range from block start to block end; block boundaries are labels that are branch targets or after jumps. No branch between.

Wait — what about a **NOTE_INSN_LOOP_BEG**? c1 (do-while around x2) created a loop and cse still forwarded. Hmm, but maybe cse_around_loop only handles invariant moves, not invalidation.

What about a **BARRIER**/jump? no.

Could the original have had the two loads in different **functions** inlined? no.

Let me reconsider: maybe the first `lh v0,46(s0)` at 77cc is a load whose value is used by `subu`, and the second `lh v0,46(s0)` at 77d8 is a load whose value is used by `sll`. Both into v0! Same register. If cse forwarded, it would use one register for both. The target uses v0 for both but reloads. Hmm.

What if the original C had `x` as a **`register` variable**? banned (no register vars).

What if the two accesses have different **modes in the C type**: the first is `s16`, the second is `u16` cast to `s16`: `(s16)*(u16*)(s0+0x2E)` → lhu + sign-extend (sll/sra) not lh.

What if the second is `*(s16*)((s32)s0 + 0x2E)` but the first is a **32-bit access that got split**: e.g., `*(s32*)((s32)s0 + 0x2C) >> 16`? Target would be lw + sra. No.

Hmm, what if the first load is from `((s16*)s0)[23]` where the index 23 comes from a `u8` variable? no.

Let me look at whether cse's `do_not_record` is set by something other than volatile/asm: a MEM whose address contains a `PRE_INC` etc. no.

Alternatively, maybe the original source had the **first access inside a loop** (a real loop) and the second outside, and cse couldn't forward out of the loop? If the first load is inside a `do{}while(0)` (loop), cse_around_loop might treat the value as loop-invariant and hoist... c2 tested do-while around the diff block → one load, 60 ins.

What about a real `for` loop? That would add code.

Let me consider the possibility that this is a WALL. The best lever-free is 8. But we haven't tried 30 tries. Let me try a batch of quick variants systematically (pointer reuse, different temp, s16 width, decl order, statement order, separate blocks, do-while in different places, init at decl). Each is cheap via sc.sh. Let me generate ~12 variants with a script and score.

Actually, let me reconsider the problem once more. What if the ORIGINAL source used **`s16` for the diff load through a `Unkstruct` field** and **a raw cast for the second**, and cse DID distinguish because of `MEM_IN_STRUCT_P` in the HASH? Let me re-read the hash: 
```
case MEM:
  if (MEM_VOLATILE_P) ...
  if (! RTX_UNCHANGING_P) { hash_arg_in_memory=1; if (MEM_IN_STRUCT_P) hash_arg_in_struct=1; }
  hash += (unsigned) MEM;
  x = XEXP (x, 0);
  goto repeat;
```
So in_struct doesn't change the hash. But the LOOKUP compares candidates in the same bucket via exp_equiv_p, which ignores in_struct. So no.

BUT: there's `invalidate_memory`: `nonscalar && p->in_struct` — a store with a PLUS address sets nonscalar, and removes entries that are in_struct. If the second load is a struct load (in_struct=1) and a store to 0xE happens before it... still store after.

Hmm, what if the ORDER in the original source is:
```
x2 = *(s16*)(s0+0x2E);        // struct load (in_struct)
*(u16*)(s0+0xE) += (x2<<6);
```
and the FIRST load is a raw load. Both recorded.

I keep coming back to needing a store/call between.

Wait wait. Let me re-examine the target instruction order once more. Maybe the store to 0xE happens BETWEEN the two loads in the ORIGINAL RTL, and sched1 moved it later! The scheduler can move the store later (it's a store, sched1 can sink it? sched1 schedules the block; it can reorder stores relative to loads if no alias). The target instruction stream shows the store at 77e8, after both loads — but that's the *scheduled* order. The RTL order (pre-sched) could have been: load 0x2E (diff), load 0xE, store 0xE, load 0x2E (x2)?? But the store needs x2's value... unless the store is a DIFFERENT store.

Hmm, what if the original source had:
```
*(u16 *)((s32)s0 + 0xE) = something;   // first store
...
x2 = *(s16*)(s0+0x2E);
```
No.

Let me look at the cse pass ORDER: cse1 runs after jump but BEFORE sched1. So cse sees the RTL order. The store to 0xE in RTL is after the second load (since the second load feeds it). So no.

Unless the original wrote the `+=` as TWO separate operations where the load of 0xE and the store happen in a different order... `+=` expansion in GCC 2.7.2: for `a += b`, expand computes `a = a + b` — the store is last.

OK, radical: maybe the original source had a **function call between the loads** that was inlined by the compiler? No.

Or the original used a **`?:` / `&&` fold** that creates a branch (EBB split) between the loads? E.g., the diff computation with a conditional? The target has no branch.

I think this may genuinely be a WALL: cse-load-forward. But the wall tag should be a new one like `cse-load-forward`. The walls.txt has `cse-const-addr`, `cse-store-forward`, `cse-copy-merge`, `cse-join-fold`, `cse-fixed-global-cache`. A new tag `cse-load-forward` fits.

But before declaring WALL, let me do a proper batch of ≥30 tries? The brief: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". That's a lot. Let me first do a systematic batch of ~15 variants, then decide.

Actually, wait. Let me reconsider the exact C. Let me look at the *original* decompilation of this function elsewhere: maybe another overlay has the same function (twin). Search src for `unk2E` and `unk1A` patterns? Let me search for the exact store sequence in other files: `unk1A = t;` and `unk18 = t;`. Maybe a twin exists that was cracked lever-free.

Let me grep for "diff -= " or the distinctive `<< 6`.
