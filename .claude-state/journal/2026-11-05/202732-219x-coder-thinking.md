---
ts: 2026-11-06T03:27:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EuNVhP7Lz770DKNE6xjv
---
This dump looks like it's the WRONG function or the r1 body (it has mem/s at the start). Hmm, the dump for s1 shows mem/s:HI (reg 69) stores — that looks like a different function (maybe the dump's function section is off, or the scratch TU is stale). The s1 body should have `u16 *q` store. The mem/s:HI suggests a struct store — maybe the scratch TU is r1 (stale p-dir issue again!).

Ugh, the p-dir issue. Let me get the right scratch dir: the --keep output gave the object path; I used `td=$(dirname $out)`. That should be right. But the dump shows mem/s. Hmm, maybe cc1_dumps_tu.sh on that TU compiles the WHOLE TU and the function section grep is right, but the function I'm looking at isn't func_8018110C? I grep "Function func_8018110C". Let me check the s1 body in the scratch TU.

Actually wait: the dump file dumps_s1/s1.i.rtl — the awk prints from the function header. The first lines show mem/s:HI (plus (reg/v:SI 72) ...) which are the svec stores (unk6/unkA/unkE at 6/10/14) — those are in-struct stores, correct. Then insn 13/18/23 mem/s:HI (reg 69)?? Hmm, those could be the svec_in writes? No.

This is taking too long. Let me step back.

The cse refs = 2 for s1 as well. So cse1 still forwarded. Why? Maybe the pointer q's address at cse1 is already a PLUS because the front end folds `q = obj + 20; *q` into a PLUS when q is used once? GCC's `expand_expr` for `*q` where q is a pointer variable: the address is (reg q); it doesn't fold the assignment into the use at RTL expansion. But cse1 might substitute q's value (obj+20) into the store's address via its copy propagation, turning (reg q) into (plus obj 20) BEFORE processing the store — and then the store's address is a PLUS → nonscalar. Hmm, cse processes insns in order: the SET q = obj+20 is recorded; at the store, cse replaces (reg q) with its equivalent (plus obj 20)? cse's `find_best_addr`/`cse_insn` might do this substitution. Then the store's address becomes a PLUS → nonscalar.

So any pointer-based spelling gets folded back to a PLUS by cse.

Hmm. What if the pointer q is *modified* (dead-reset) so cse can't fold? E.g., `q = (u16*)(obj+0x14); *q = ...; q = 0;` — but the store happens before the reset, and cse would still know q's value at the store.

What if q is loaded from a global? That adds code.

What if we make the store's address a register that cse can't fold: e.g., q = a function argument? The only function argument is a0.

What if the address is (reg q) where q is computed via a *non-foldable* expression, e.g., `q = (u16*)((s32)obj + 0x14 + d)` where d = 0? cse folds d=0.

Hmm. What if the store's MEM is *not* in a struct and the address is a REG that cse can't resolve because the register is set in a different basic block? E.g., compute q before a label? Then cse's EBB would... Hmm.

Alternatively, use a store address that is a MINUS or something not PLUS: e.g., `*(u16*)((u8*)obj - (-0x14))`? The compiler folds.

What about an address with a different structure: `(mem (plus (reg obj) (reg idx)))` where idx is a variable known 0? cse might fold idx=0 but the address is (plus obj 0) → PLUS → nonscalar.

Hmm, we need `all=1`: the address must vary and NOT be a PLUS and NOT in-struct. The only such address is (reg r) where r is a pseudo cse can't fold.

What if the store is through a *parameter-derived pointer* that's also used for something else so cse keeps it in a register? E.g., `u16 *q = (u16*)(obj + 0x14); func-like use`? 

What if q is used in a way that prevents folding: e.g., `q = (u16*)(obj + 0x14); if (q) *q = ...;` — the `if (q)` adds a branch.

What if q is stored to a local and reloaded (memory)? e.g., `u16 **pq = &q;` — adds loads.

Hmm.

Wait — maybe the target's reload comes not from cse invalidation but from the *barrier* forcing a reload in the same way. The barrier is an ASM_INPUT with a memory clobber. In cse, an asm with a clobber `(clobber (mem:BLK (scratch)))` sets everything → invalidate all. The target's C likely had something that cse treated as all=1.

Given the difficulty, let me consider the *other* direction: make the first global load happen AFTER the store, so cse can't merge them. E.g., restructure the source so the first use of D_80126B78 is after the obj store. But the store's value depends on the first load — no.

What if we swap the operands: compute the unk2A difference first, then the obj store:
```
u16 dv = unk2A - D_80126B78[0x12];
obj[0x14] += dv;
[barrier]
unk2A = D_80126B78[0x12];
```
Now the first load is before the store, same as before. cse merges.

What if the second load is written differently, e.g., through a different symbol alias? The cookbook's symbol-alias trick (two declarations of the same symbol under different asm labels): if the second load uses a distinct SYMBOL_REF string, cse can't merge them! And the codegen emits the same `lui/lw` relocations to the same symbol. That's the §5a alias trick used for cross-jump (ov_SC03_099 after.c).

So: declare `extern s32 *aD80126B78 __asm__("D_80126B78");` and use `aD80126B78` for the second load. The two loads reference different SYMBOL_REF strings → cse can't CSE them → both loads emitted! And the relocations point to D_80126B78.

But wait: the target's first load and second load both reference D_80126B78; using an alias gives the same symbol bytes. The alias declaration is a real-C-ish lever? The cookbook calls it "a symbol alias defeating cross-jump" and considers it acceptable (it's an asm label, not a codegen lever). The brief's constraints: "no new lever of any kind", "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had may stay, never added". Hmm, adding an asm-label alias is arguably a new lever (an `__asm__` label). The brief says no `__asm__`? It says "no `register` vars, no `__asm__`" — under CONSTRAINTS: "no signature or decl change outside the body (callers stay as they are); no `register` vars, no `__asm__`". So `__asm__` aliases are forbidden.

Hmm. OK.

What about declaring a second *variable* at the same address? Not possible without asm.

What about using a pointer that cse can't fold: e.g., take the address of the global into a local pointer variable and use it for the second load: `s32 *g = D_80126B78; ... unk2A = *(u16*)((u8*)g + 0x12);`. The load's address is (reg g) — cse might fold g to D_80126B78 (a copy). Hmm, but the first load uses D_80126B78 directly; if the second uses a copy in a register, cse might propagate. Let me test: assign `s32 *g = D_80126B78;` BEFORE the store, use g after. cse would know g = D_80126B78 and merge. Unless g is assigned after the store? Then the load of D_80126B78 happens after the store anyway (same as before).

Hmm.

What about making the second load happen through a *different* expression: `*(u16*)((u8*)D_80126B78 + 0x12)` vs `*(u16*)((u8*)D_80126B78 + 0x12)` — same.

What if we use `D_80126B78[0x12/2]` (array indexing) vs pointer arithmetic? The front end folds to the same.

What if we use a cast through a `u8*` vs `s32*`? The address (symbol_ref + 18) is the same.

Hmm. What about making the first load's address a register (unfoldable) so cse keeps two separate expressions? E.g., first use via a local pointer `p = D_80126B78;` and second via D_80126B78 directly. cse might fold p.

Let me test a few:
t1: local pointer p = D_80126B78; first use via p, second via D_80126B78.
t2: first via D_80126B78, second via a local pointer q = D_80126B78 assigned before the store.
t3: second via `(u8*)D_80126B78` cast to u16* with an index variable.
t4: use `*(u16*)((u8*)D_80126B78 + 0x12)` vs `*((u16*)((u8*)D_80126B78 + 0x10) + 1)` — different expression, same address; cse folds? The address (plus symbol 16) then +2? The front end folds constants → same.
t5: compute the second load's address via a variable offset: `s32 off = 0x12; *(u16*)((u8*)D_80126B78 + off)` — cse might fold off=0x12 (constant propagation) → same. But maybe the extra `li off,18` would appear (bad).

Hmm.

Actually, hold on: maybe the *simplest* explanation is that the target's second load is not the same expression because the original C used a *different struct type* for the second access: e.g., the first via `*(u16*)((u8*)D_80126B78 + 0x12)` and the second via a struct field at 0x12 of a struct type. The addresses: (symbol + 18) both → identical MEM rtx → cse merges. Unless one is MEM_IN_STRUCT and the other not — cse's table key ignores the flag? `canon_hash`/`exp_equiv_p` may include MEM_IN_STRUCT? In cse, `exp_equiv_p` for MEM compares the address only (plus flags?). Hmm, cse's `exp_equiv_p` has `case MEM: ... if (MEM_VOLATILE_P...)`. Let me check whether it compares MEM_IN_STRUCT_P. If it does, a struct-typed second access would differ → no merge → reload! And the codegen is identical (lhu v0,18(v0)).

Let me check cse.c's exp_equiv_p / canon_hash for MEM.
